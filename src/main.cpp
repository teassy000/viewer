#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

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


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
int main(void)
{
	GLFWwindow* window;
	GLuint vertex_buffer;
	GLint vpos_location;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(1280, 720, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	// NOTE: OpenGL error checks have been omitted for brevity
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	Shader* vert =  new Shader(GL_VERTEX_SHADER);
	vert->LoadFromFile("..\\shaders\\default.vs.glsl");
	vert->Compile();
	
	Shader* frag = new Shader(GL_FRAGMENT_SHADER);
	frag->LoadFromFile("..\\shaders\\default.fs.glsl");
	frag->Compile();


	ShaderProgram* program = new ShaderProgram();
	program->AttachShader(*vert);
	program->AttachShader(*frag);
	program->Link();

	vpos_location = program->AddAttribute("vPos");

//	program = glCreateProgram();
//	glAttachShader(program, vex->GetId());
//	glAttachShader(program, frag->GetId());
//	glLinkProgram(program);

//	vpos_location = glGetAttribLocation(program, "vPos");
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 2, (void*)0);

	while (!glfwWindowShouldClose(window))
	{

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		program->Use();

		glDrawArrays(GL_POLYGON, 0, 4);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}