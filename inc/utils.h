#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <shaderProgram.h>
#include <shader.h>


struct vec2
{
	float x, y;
};
static const vec2 vertices[4] =
{
	{ -1.0f, 1.0f },
	{ -1.0f, -1.0f },
	{ 1.0f, -1.0f },
	{ 1.0f, 1.0f },
};

static ShaderProgram* program;

static void LoadShader()
{
	GLuint vertex_buffer;
	GLint vpos_location;

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	Shader* vert = new Shader(GL_VERTEX_SHADER);
	vert->LoadFromFile("..\\shaders\\default.vs.glsl");
	vert->Compile();

	Shader* frag = new Shader(GL_FRAGMENT_SHADER);
	frag->LoadFromFile("..\\shaders\\default.fs.glsl");
	frag->Compile();


	program = new ShaderProgram();
	program->AttachShader(*vert);
	program->AttachShader(*frag);
	program->Link();

	vpos_location = program->AddAttribute("vPos");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 2, (void*)0);
}


static void ReloadShader()
{
	program->Diable();
	program = NULL;

	LoadShader();
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
		ReloadShader();
}


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


