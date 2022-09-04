#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION 

#ifndef		_E_GRAPHIC_CORE_ALREADY_LINKED_
	#define _E_GRAPHIC_CORE_ALREADY_LINKED_
	#include "NoSimpleWayAPI[v2]/EGraphicCore.h"
#endif


/**/
#ifndef		_E_INPUT_CORE_ALREADY_LINKED_
	#define _E_INPUT_CORE_ALREADY_LINKED_
	#include "NoSimpleWayAPI[v2]/EInputCore.h"
#endif

#ifndef		_E_GUI_CORE_ALREADY_LINKED_
	#define _E_GUI_CORE_ALREADY_LINKED_
	#include "NoSimpleWayAPI[v2]/EGUICore.h"
#endif


#ifndef		_E_MAIN_WINDOW_ALREADY_LINKED_
	#define _E_MAIN_WINDOW_ALREADY_LINKED_
	#include "EWindowMain.h"
#endif


/**/
#ifndef		_HELPERS_ALREADY_LINKED_
	#define	_HELPERS_ALREADY_LINKED_
	#include "NoSimpleWayAPI[v2]/Helpers.h"
#endif
/**/

#include <algorithm>
#include <iterator>
#include <chrono>

//#pragma execution_character_set( "utf-8" )
//extern GLFWwindow* main_window{ nullptr };



int main()
{
	
	//SetConsoleOutputCP(65001);
	//printf("Testing unicode -- English -- Ελληνικά -- Español -- Русский. aäbcdefghijklmnoöpqrsßtuüvwxyz\n");
	// 
	// 
	// 
	// 
	//std::string drunk = "you drunk?";
	//std::cout << drunk;
	// glfw window creation
	// 
	// 
	//`	EInputCore::logger_simple_info(EStringUtils::to_lower("ZaLuPa АЯая"));
// --------------------
	/*Entity* ent = nullptr;
	std::cout << "entity pointer: " << ent << std::endl;

	ent = new Entity();
	std::cout << "entity pointer: " << ent << std::endl;*/

	NS_EGraphicCore::initiate_graphic_core();
	EInputCore::initiate_input_core();

	
	
	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
	EInputCore::logger_param("max_texture_size:", max_tex_size);

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

		//std::vector<<ETestObject 
	
		//for (int i = 0; i < 1'000'000; i++)
		//{
		//	ETestObject::test_object_vector.push_back(new ETestObject());
		//}

		//auto start = std::chrono::high_resolution_clock::now();
		//	for (int i = 0; i < 1'000'000 - 1; i++)
		//	{
		//		*ETestObject::test_object_vector[i + 1]->b = *ETestObject::test_object_vector[i]->b + 1;
		//	}
		//auto finish = std::chrono::high_resolution_clock::now();
		//EInputCore::logger_param("pointer", std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1'000'000.0f);

		//start = std::chrono::high_resolution_clock::now();
		//for (int i = 0; i < 1'000'000 - 1; i++)
		//{
		//	ETestObject::test_object_vector[i + 1]->a = ETestObject::test_object_vector[i]->a + 1;
		//	
		//}
		//finish = std::chrono::high_resolution_clock::now();
		//EInputCore::logger_param("non-pointer", std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1'000'000.0f);
		//EInputCore::logger_param("max texture_size", GL_MAX_TEXTURE_SIZE);
		srand(time(nullptr));
	while (!glfwWindowShouldClose(NS_EGraphicCore::main_window))
	{
		ESpriteLayer::data_copies_count = 0;
		ESpriteLayer::data_copy_calls = 0;

		//Sleep(1.0f);
		//GLFW_KEY_1
		clock_t time = clock();

		NS_EGraphicCore::delta_time = (time - NS_EGraphicCore::saved_time_for_delta) / 1000.0;
		NS_EGraphicCore::saved_time_for_delta = time;

		NS_EGraphicCore::time_total += NS_EGraphicCore::delta_time;
		//EInputCore::logger_param("size", EButtonGroup::fresh_created_block_list.size());


		//glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClearColor(0.025f, 0.0375f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		//NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP_TO_EDGE, GL_LINEAR);
		NS_EGraphicCore::gl_set_blend_mode_default();
		
		if (!EInputCore::MOUSE_BUTTON_LEFT) { EButtonGroup::focused_button_group = nullptr; }
		if (EInputCore::MOUSE_SPEED_X * EInputCore::MOUSE_SPEED_X + EInputCore::MOUSE_SPEED_Y * EInputCore::MOUSE_SPEED_Y > 0)
		{
			EButtonGroup::focused_button_group_with_slider = nullptr;
		}
		if (!EInputCore::MOUSE_BUTTON_LEFT) { EClickableArea::active_clickable_region = nullptr; }
		/*if (*EClickableArea::active_clickable_region->parent_entity->disable_draw)
		{

		}*/

		for (EWindow* w : EWindow::window_list)
		{
			
			w->update_default(NS_EGraphicCore::delta_time);
			w->update_additional(NS_EGraphicCore::delta_time);

			w->GUI_update_default(NS_EGraphicCore::delta_time);
			w->GUI_update_additional(NS_EGraphicCore::delta_time);
		}

		NS_EGraphicCore::current_zoom = max(NS_EGraphicCore::current_zoom, 0.5f);

		for (EWindow* w : EWindow::window_list)
		{
			w->draw_default(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();

			w->draw_additional(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();

			w->GUI_draw_default(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::pbr_batcher->draw_call();
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();
			
			//w->GUI_draw_second_pass(NS_EGraphicCore::delta_time);
			//NS_EGraphicCore::pbr_batcher->draw_call();
			//NS_EGraphicCore::default_batcher_for_drawing->draw_call();

			w->GUI_draw_additional(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();
			//NS_EGraphicCore::pbr_batcher->draw_call();
		}
		
		for (EWindow* w : EWindow::window_list)
		{


		}
		
			//NS_EGraphicCore::gl_set_texture_filtering(GL_MIRRORED_REPEAT, GL_LINEAR);
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);

			for (int i = 0; i < texture_skydome_levels; i++)
			{
				if (EInputCore::key_pressed(GLFW_KEY_1 + i))
				{
					NS_EGraphicCore::set_source_FBO(GL_TEXTURE0, NS_EGraphicCore::skydome_texture_atlas[i]->get_colorbuffer());

					NS_ERenderCollection::add_data_to_vertex_buffer_default
					(
						NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
						NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,
						0.0,
						0.0f,
						1024.0f,
						1024.0f
					);

					NS_EGraphicCore::default_batcher_for_drawing->draw_call();
				}

				
			}

			if (EInputCore::key_pressed(GLFW_KEY_0))
			{
				NS_EGraphicCore::set_source_FBO(GL_TEXTURE0, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());

				NS_ERenderCollection::add_data_to_vertex_buffer_default
				(
					NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
					NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,
					0.0,
					0.0f,
					1000.0f,
					1000.0f
				);

				NS_EGraphicCore::default_batcher_for_drawing->draw_call();
			}
	
		

	//	NS_EGraphicCore::set_source_FBO(GL_TEXTURE0, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());//1
		///reset input states
		glfwSwapBuffers(NS_EGraphicCore::main_window);

		for (int i = 0; i < EInputCore::key_count; i++)
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

		for (int i = 0; i < EInputCore::mouse_key_count; i++)
		{
			if (EInputCore::mouse_button_state[i] != GLFW_RELEASE)
			{
				EInputCore::mouse_hold_time[i] += NS_EGraphicCore::delta_time;
			}
			else
			{
				//EInputCore::mouse_unhold_save_time[i] = EInputCore::mouse_hold_time[i];
				EInputCore::mouse_hold_time[i] = 0.0f;
			}
		}

		EInputCore::LAST_INPUTED_CHAR	=	0;
		EInputCore::scroll_direction	=	0;
		EInputCore::MOUSE_SPEED_X = 0.0;
		EInputCore::MOUSE_SPEED_Y = 0.0;

		if (!EButtonGroup::fresh_created_block_list.empty())
		{
			for (FreshCreatedGroup* fcg : EButtonGroup::fresh_created_block_list)
			{
				fcg->target_group->add_group(fcg->just_created_group);

				EButtonGroup::change_group(fcg->just_created_group);
				EButtonGroup::change_group(fcg->target_group);



			};

			EButtonGroup::fresh_created_block_list.clear();
			EButtonGroup::fresh_created_block_list.shrink_to_fit();

		}
		///////

		//EInputCore::logger_param("data calls", ESpriteLayer::data_copy_calls);
		//EInputCore::logger_param("data copied", ESpriteLayer::data_copies_count);
	}

	return 0;

}