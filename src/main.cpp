#include "precomp.h"
#include "glGraphicManager.h"
#include "imgui_glfw_impl.h"



static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
 
  	if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
 		glGraphicManager::getInstance()->Reload();
}


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	std::cout << "GL version "  << GLVersion.major << "." 
		<< GLVersion.minor  << "is loaded" << std::endl;


	glGraphicManager::getInstance()->Load();
	ImGui_ImplGlfwGL3_Init(window, true);


	while (!glfwWindowShouldClose(window))
	{
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.5f, 0.3f, 0.0f, 1.0f);

		ImGui_ImplGlfwGL3_NewFrame();
		glGraphicManager::getInstance()->Render();

		{
			ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Title");
			ImGui::Text("Hello, world!");

			ImGui::End();
		}


		// ImGui functions end here
		ImGui::Render();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}