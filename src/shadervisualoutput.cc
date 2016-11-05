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
	load_vertexbuffer();
	load_shader();
	load_framebuffer();
}


void ShaderVisualOutput::load_shader()
{	
	bool result = false;
	// load and compile shader
	std::unique_ptr<Shader> vert(new Shader(GL_VERTEX_SHADER));
	vert.get()->load_from_file("..\\..\\shaders\\default.vs.glsl");
	result = vert.get()->compile();
	if (!result)
		return;

	std::unique_ptr<Shader> frag(new Shader(GL_FRAGMENT_SHADER));
	frag.get()->load_from_file("..\\..\\shaders\\default.fs.glsl");
	result = frag.get()->compile();

	if (!result)
		return;

	std::unique_ptr<ShaderProgram> program(new ShaderProgram);
	program.get()->attach_shader(*(vert.get()));
	program.get()->attach_shader(*(frag.get()));
	result = program.get()->link();
	if (!result)
		return;

	// if everything is correct, then set the program_
	program_.get()->disable();
	program_.reset(new ShaderProgram);
	program_ = std::move(program);
}


void ShaderVisualOutput::load_vertexbuffer()
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