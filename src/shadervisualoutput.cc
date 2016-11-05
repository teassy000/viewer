#include "shadervisualoutput.h"



ShaderVisualOutput::ShaderVisualOutput()
	: program_(std::make_unique<ShaderProgram>())
{
}


ShaderVisualOutput::~ShaderVisualOutput()
{

}


void ShaderVisualOutput::load()
{
	load_shader();
	load_framebuffer();
}


void ShaderVisualOutput::load_shader()
{
	// generate and bind the vertex buffer.
	const vec2 vertices[6] =
	{
		{ -1.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, -1.0f },
		{ -1.0f, 1.0f },
		{ 1.0f, -1.0f },
		{ -1.0f, -1.0f },

	};


	glGenBuffers(1, &vertexbuffer_);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	
	// load and compile shader
	std::unique_ptr<Shader> _vert(new Shader(GL_VERTEX_SHADER));
	_vert.get()->load_from_file("..\\..\\shaders\\default.vs.glsl");
	_vert.get()->compile();

	std::unique_ptr<Shader> _frag(new Shader(GL_FRAGMENT_SHADER));
	_frag.get()->load_from_file("..\\..\\shaders\\default.fs.glsl");
	_frag.get()->compile();

	
	program_.get()->attach_shader( *(_vert.get()) );
	program_.get()->attach_shader( *(_frag.get()) );
	program_.get()->link();

	return;
}


void ShaderVisualOutput::load_framebuffer()
{
	glGenFramebuffers(1, &framebuffer_);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;
}


void ShaderVisualOutput::reload()
{
	program_.get()->disable();
	program_.reset(new ShaderProgram);

	load_shader();
}


void ShaderVisualOutput::render()
{
	program_.get()->use();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(0);
}