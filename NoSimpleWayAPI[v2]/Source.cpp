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
	EInputCore::initiate_input_core();
	
	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
	//logger_param("max_texture_size:", max_tex_size);

	glfwSwapInterval(1);

		ERenderBatcher* batcher = new ERenderBatcher();
			batcher->set_total_attribute_count(8);

			batcher->register_new_vertex_attribute(2);//position
			batcher->register_new_vertex_attribute(4);//color
			batcher->register_new_vertex_attribute(2);//uv texture

			batcher->set_shader(new Shader("data/#default.vs", "data/#default.fs"));
			
			batcher->set_transform_screen_size
			(
				EGraphicCore::SCREEN_WIDTH,
				EGraphicCore::SCREEN_HEIGHT
			);



		ETextureGabarite* gudron = EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", EGraphicCore::default_texture_atlas);
		gudron = EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", EGraphicCore::default_texture_atlas);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glDisable(GL_DEPTH_TEST);
		glBlendEquation(GL_FUNC_ADD);

		glViewport(0, 0, EGraphicCore::SCREEN_WIDTH, EGraphicCore::SCREEN_HEIGHT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, EGraphicCore::default_texture_atlas->get_colorbuffer());

		//EGraphicCore::shader_texture_atlas_putter->setInt("texture1", 0);
		batcher->set_color(EColorCollection::COLOR_WHITE);

		
	while (!glfwWindowShouldClose(EGraphicCore::main_window))
	{
		clock_t time = clock();
		EGraphicCore::delta_time = (time - EGraphicCore::saved_time_for_delta) / 1000.0;
		EGraphicCore::saved_time_for_delta = time;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//


//		EGraphicCore::shader_texture_atlas_putter->use();

		EGraphicCore::make_transform_from_size(batcher, EGraphicCore::SCREEN_WIDTH, EGraphicCore::SCREEN_HEIGHT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);

		glfwPollEvents();

		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		
		
		for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			ERenderCollection::fill_vertex_buffer_textured_rectangle_real_size
			(
				batcher->vertex_buffer,
				batcher->last_vertice_buffer_index,

				j * 210.0f + 5.0f,
				i * 110.0f + 5.0f,

				gudron
			);

			if (batcher->last_vertice_buffer_index + 32 >= MAX_SHAPES_COUNT * 32) { batcher->draw_call();}
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