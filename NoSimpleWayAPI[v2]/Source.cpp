#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION 
#include "NoSimpleWayAPI[v2]/EGraphicCore.h"
#include "NoSimpleWayAPI[v2]/EInputCore.h"


//extern GLFWwindow* main_window{ nullptr };



int main()
{
	

// glfw window creation
// --------------------


	EGraphicCore::initiate_graphic_core();
	//std::cout << "[1]window is:" << (EGraphicCore::main_window) << std::endl;
	//std::cout << "[1]batcher is:" << (EGraphicCore::default_batcher_for_texture_atlas) << std::endl;
	EInputCore::initiate_input_core();
	
	
	

	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);

	//logger_param("max_texture_size:", max_tex_size);

	glfwSwapInterval(0);

		Batcher* batcher = new Batcher();
		batcher->set_total_attribute_count(8);

		
		batcher->register_new_vertex_attribute(2);//position
		batcher->register_new_vertex_attribute(4);//color
		batcher->register_new_vertex_attribute(2);//uv texture

	while (!glfwWindowShouldClose(EGraphicCore::main_window))
	{
		clock_t time = clock();
		EGraphicCore::delta_time = (time - EGraphicCore::saved_time_for_delta) / 1000.0;
		EGraphicCore::saved_time_for_delta = time;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//


		EGraphicCore::shader_texture_atlas_putter->use();

		EGraphicCore::make_transform_from_size(EGraphicCore::SCREEN_WIDTH, EGraphicCore::SCREEN_HEIGHT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);

		glfwPollEvents();

		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		
		batcher->reset();
		for (int i = 0; i <= 10000; i++)
		{
			EGraphicCore::fill_vertex_buffer_default(batcher->vertex_buffer, batcher->last_vertice_buffer_index, rand() % 1800, rand() % 1000, 20.0f, 10.0f);

			if (batcher->last_vertice_buffer_index + 32 >= TOTAL_MAX_VERTICES_COUNT) { batcher->draw_call(); }
			//EGraphicCore::fill_vertex_buffer_default(batcher->vertex_buffer, batcher->last_vertice_buffer_index, batcher, 300.0f, 400.0f, 200.0f, 100.0f);
		}
		batcher->draw_call();
		//std::cout << "Delta time(ms): " << std::to_string(EGraphicCore::delta_time * 1000.0f) << std::endl;


		//std::cout << "Last vertex buffer id: " << std::to_string(batcher->get_last_id()) << std::endl;

		

		glfwSwapBuffers(EGraphicCore::main_window);
		//processInput(EGraphicCore::main_window);

		EInputCore::LAST_INPUTED_CHAR	=	NULL;
		EInputCore::scroll_direction	=	0;
	}

	return 0;

}