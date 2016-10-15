#include "shaderVisualOutput.h"

static const vec2 vertices[4] =
{
	{ -1.0f, 1.0f },
	{ -1.0f, -1.0f },
	{ 1.0f, -1.0f },
	{ 1.0f, 1.0f },
};

ShaderVisualOutput::ShaderVisualOutput()
	: m_program(std::make_unique<ShaderProgram>())
{
}


ShaderVisualOutput::~ShaderVisualOutput()
{
}


void ShaderVisualOutput::Load()
{
	// generate and bind the vertex buffer.
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// load and compile shader
	std::unique_ptr<Shader> up_vert(new Shader(GL_VERTEX_SHADER));
	up_vert.get()->LoadFromFile("..\\shaders\\default.vs.glsl");
	up_vert.get()->Compile();

	std::unique_ptr<Shader> up_frag(new Shader(GL_FRAGMENT_SHADER));
	up_frag.get()->LoadFromFile("..\\shaders\\default.fs.glsl");
	up_frag.get()->Compile();

	
	m_program.get()->AttachShader( *(up_vert.get()) );
	m_program.get()->AttachShader( *(up_frag.get()) );
	m_program.get()->Link();

	GLuint vpos = m_program.get()->AddAttribute("vPos");

	glEnableVertexAttribArray(vpos);
	glVertexAttribPointer(vpos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
}


void ShaderVisualOutput::Reload()
{
	m_program.get()->Disable();
	m_program.reset(new ShaderProgram);

	Load();
}


void ShaderVisualOutput::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_program.get()->Use();
	glDrawArrays(GL_POLYGON, 0, 4);
}