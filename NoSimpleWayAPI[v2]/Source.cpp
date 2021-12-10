#include <iostream>
#include <string>

#include "NoSimpleWayAPI[v2]/EGraphicCore.h"
#include "NoSimpleWayAPI[v2]/EInputCore.h"


//extern GLFWwindow* main_window{ nullptr };



int main()
{
	

// glfw window creation
// --------------------


	EGraphicCore::initiate_graphic_core();
	std::cout << "[1]window is:" << (EGraphicCore::main_window) << std::endl;
	std::cout << "[1]batcher is:" << (EGraphicCore::default_batcher_for_texture_atlas) << std::endl;
	EInputCore::initiate_input_core();
	
	
	

	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);

	//logger_param("max_texture_size:", max_tex_size);

	glfwSwapInterval(1);

	Batcher* batcher = new Batcher();

	while (!glfwWindowShouldClose(EGraphicCore::main_window))
	{
		glfwPollEvents();

		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(EGraphicCore::main_window);
		//processInput(EGraphicCore::main_window);

		EInputCore::LAST_INPUTED_CHAR	=	NULL;
		EInputCore::scroll_direction	=	0;
	}

	return 0;

}