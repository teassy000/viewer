#include "precomp.h"
#include "glgraphicmanager.h"
#include "imgui_glfw_impl.h"
#include "shadersource.h"

#include <vector>



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
	
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	std::cout << "GL version "  << GLVersion.major << "." 
		<< GLVersion.minor  << "is loaded" << std::endl;

	ShaderSource vertex_src = ShaderSource();
	vertex_src.readfromfile("..\\..\\shaders\\default.vs.glsl");

	ShaderSource fragment_src = ShaderSource();
	fragment_src.readfromfile("..\\..\\shaders\\default.fs.glsl");

	glGraphicManager::get_instance()->load(vertex_src.get_source(), fragment_src.get_source());

	ImGui_ImplGlfwGL3_Init(window, true);


	while (!glfwWindowShouldClose(window))
	{
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.5f, 0.3f, 0.0f, 1.0f);

		ImGui_ImplGlfwGL3_NewFrame();
		glGraphicManager::get_instance()->render();

		{
			ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("source code");
			
			std::string str = fragment_src.get_source();

			static std::vector<char> text(str.begin(), str.end());
			text.push_back('\0');

			ImGui::InputTextMultiline("##source", &text[0], text.size(), ImVec2(-1.0f, ImGui::GetTextLineHeight() * 88), ImGuiInputTextFlags_AllowTabInput);
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