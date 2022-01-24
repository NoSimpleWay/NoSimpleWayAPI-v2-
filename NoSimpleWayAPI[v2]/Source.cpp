#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION 
#include "NoSimpleWayAPI[v2]/EGraphicCore.h"
#include "NoSimpleWayAPI[v2]/EInputCore.h"
#include "NoSimpleWayAPI[v2]/EGUICore.h"
#include "EWindowMain.h"

#include <algorithm>
#include <iterator>
#include <chrono>

//extern GLFWwindow* main_window{ nullptr };



int main()
{
	

// glfw window creation
// --------------------
	/*Entity* ent = nullptr;
	std::cout << "entity pointer: " << ent << std::endl;

	ent = new Entity();
	std::cout << "entity pointer: " << ent << std::endl;*/

	NS_EGraphicCore::initiate_graphic_core();
	EInputCore::initiate_input_core();

	
	
	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
	//logger_param("max_texture_size:", max_tex_size);

	glfwSwapInterval(1);




			
			NS_EGraphicCore::default_batcher_for_drawing->set_transform_screen_size
			(
				NS_EGraphicCore::SCREEN_WIDTH,
				NS_EGraphicCore::SCREEN_HEIGHT
			);



		//ETextureGabarite* gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);
		//gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);


		//EGraphicCore::shader_texture_atlas_putter->setInt("texture1", 0);
		NS_EGraphicCore::default_batcher_for_drawing->set_active_color(NS_EColorUtils::COLOR_WHITE);


		EWindowMain::link_to_main_window = new EWindowMain();
		EWindow::window_list.push_back(EWindowMain::link_to_main_window);

		/*
		
		float *d_array = new float[100'000];
		float s_array[100'000]{};

		//EInputCore::logger_param("zzz elements", sizeof(zzz));
		

		for (int i = 0; i < 100'000; i++)
		{
			d_array[i] = i;
		}

		auto start = std::chrono::high_resolution_clock::now();
		for (int z = 0; z < 100; z++)
		{
			memcpy(s_array, d_array, 100'000 * sizeof * d_array);
		}
		auto finish = std::chrono::high_resolution_clock::now();
		EInputCore::logger_param("copy using [memcpy]", std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1'000'000.0f);
		
		for (int z = 0; z < 50; z++)
		{
			EInputCore::logger_param("[" + std::to_string(z) + "]", s_array[z]);
		}
		*/

	while (!glfwWindowShouldClose(NS_EGraphicCore::main_window))
	{

		//GLFW_KEY_1
		clock_t time = clock();

		NS_EGraphicCore::delta_time = (time - NS_EGraphicCore::saved_time_for_delta) / 1000.0;
		NS_EGraphicCore::saved_time_for_delta = time;

		

		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP_TO_EDGE, GL_LINEAR);
		NS_EGraphicCore::gl_set_blend_mode_default();
		
		
		for (EWindow* w : EWindow::window_list)
		{
			w->update_default(NS_EGraphicCore::delta_time);
			w->update_additional(NS_EGraphicCore::delta_time);

			w->GUI_update_default(NS_EGraphicCore::delta_time);
			w->GUI_update_additional(NS_EGraphicCore::delta_time);
		}

		for (EWindow* w : EWindow::window_list)
		{
			w->draw_default(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();

			w->draw_additional(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();

			w->GUI_draw_default(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();

			w->GUI_draw_additional(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();
		}
		
		///reset input states
		glfwSwapBuffers(NS_EGraphicCore::main_window);

		for (int i = 0; i < 512; i++)
		{
			if (EInputCore::key_state[i] != GLFW_RELEASE)
			{
				EInputCore::key_hold_time[i] += NS_EGraphicCore::delta_time;
			}
			else
			{
				EInputCore::key_hold_time[i] = 0.0f;
			}
					
		}

		EInputCore::LAST_INPUTED_CHAR	=	0;
		EInputCore::scroll_direction	=	0;
		EInputCore::MOUSE_SPEED_X = 0.0;
		EInputCore::MOUSE_SPEED_Y = 0.0;
		///////
	}

	return 0;

}