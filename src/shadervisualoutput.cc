#include "shadervisualoutput.h"



ShaderVisualOutput::ShaderVisualOutput()
	: program_(std::make_unique<ShaderProgram>())
{

}


ShaderVisualOutput::~ShaderVisualOutput()
{
	delete_framebuffer();
}


void ShaderVisualOutput::load(std::string vertex_src, std::string fragment_src)
{
	load_vertexbuffer();

	set_source(vertex_src, ShaderType::vertexshader);
	set_source(fragment_src, ShaderType::fragmentshader);
	load_shader();

	load_framebuffer();
}


bool ShaderVisualOutput::load_shader()
{	
	bool result = false;
	// load and compile shader
	std::unique_ptr<Shader> vert(new Shader(GL_VERTEX_SHADER));
	vert.get()->load_from_buffer(vertex_source_);
	result = vert.get()->compile();
	if (!result)
		return false;

	std::unique_ptr<Shader> frag(new Shader(GL_FRAGMENT_SHADER));
	frag.get()->load_from_buffer(fragment_source_);
	result = frag.get()->compile();
	if (!result)
		return false;

	//link
	std::unique_ptr<ShaderProgram> program(new ShaderProgram);
	program.get()->attach_shader(*(vert.get()));
	program.get()->attach_shader(*(frag.get()));
	result = program.get()->link();
	if (!result)
		return false;

	//if everything is correct, then set the program_
	program_.get()->disable();
	program_.reset(new ShaderProgram);
	program_ = std::move(program);


	return true;
}


void ShaderVisualOutput::set_source(std::string source, ShaderType shadertype)
{
	if (shadertype == ShaderType::vertexshader)
		vertex_source_ = source;

	if (shadertype == ShaderType::fragmentshader)
		fragment_source_ = source;
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


void ShaderVisualOutput::delete_framebuffer()
{
	glDeleteTextures(1, &texture_);
}


bool ShaderVisualOutput::reload()
{
	program_->del();
	return load_shader();
}


void ShaderVisualOutput::render()
{
	program_->use();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(0);
}