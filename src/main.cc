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

	
	ShaderSource::get_instance()->read_vertex_src_fromfile("..\\..\\shaders\\default.vs.glsl");
	ShaderSource::get_instance()->read_fragment_src_fromfile("..\\..\\shaders\\default.fs.glsl");

	{
		std::string vert, frag;
		vert = ShaderSource::get_instance()->get_vertex_source();
		frag = ShaderSource::get_instance()->get_fragment_source();
		glGraphicManager::get_instance()->load(vert, frag);
	}

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
			
			std::string str = ShaderSource::get_instance()->get_fragment_source();

			const static size_t BUFFER_SIZE = 4096;
			static char text[BUFFER_SIZE];
			strncpy_s(text, str.c_str(), sizeof(text));
			text[sizeof(text) - 1] = '\0';


			ImGui::InputTextMultiline("##source", &text[0], (size_t)BUFFER_SIZE, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 44), ImGuiInputTextFlags_AllowTabInput);

			ImGui::End();

			std::string str_after(text);
			set_frag_str(str_after);
		}


		// ImGui functions end here
		ImGui::Render();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	ImGui_ImplGlfwGL3_Shutdown();
	glGraphicManager::get_instance()->shutdown();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}