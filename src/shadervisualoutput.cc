#include "shadervisualoutput.h"



ShaderVisualOutput::ShaderVisualOutput()
	: program_(std::make_unique<ShaderProgram>())
{
}


ShaderVisualOutput::~ShaderVisualOutput()
{

}


void ShaderVisualOutput::Load()
{
	LoadShader();
	LoadFramebuffer();
}


void ShaderVisualOutput::LoadShader()
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
	_vert.get()->LoadFromFile("..\\..\\shaders\\default.vs.glsl");
	_vert.get()->Compile();

	std::unique_ptr<Shader> _frag(new Shader(GL_FRAGMENT_SHADER));
	_frag.get()->LoadFromFile("..\\..\\shaders\\default.fs.glsl");
	_frag.get()->Compile();

	
	program_.get()->AttachShader( *(_vert.get()) );
	program_.get()->AttachShader( *(_frag.get()) );
	program_.get()->Link();


}


void ShaderVisualOutput::LoadFramebuffer()
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


void ShaderVisualOutput::Reload()
{
	program_.get()->Disable();
	program_.reset(new ShaderProgram);

	LoadShader();
}


void ShaderVisualOutput::Render()
{
	program_.get()->Use();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(0);
}