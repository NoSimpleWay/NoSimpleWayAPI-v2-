#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION 

/**/#include "NoSimpleWayAPI[v2]/ETextCore.h"

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


#include "NoSimpleWayAPI[v2]/Helpers.h"


#include <algorithm>
#include <iterator>
#include <chrono>

/**/
#ifndef _ESOUND_ALREADY_LINKED_
#define _ESOUND_ALREADY_LINKED_
#include <NoSimpleWayAPI[v2]/ESound.h>
#endif
/**/



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

	ESound::irrKlang_initiate_sound_engine();
	ESound::engine->play2D(ESound::shootSound);



	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
	EInputCore::logger_param("max_texture_size:", max_tex_size);

	glfwSwapInterval(1);





	NS_EGraphicCore::default_batcher_for_drawing->set_transform_screen_size
	(
		NS_EGraphicCore::SCREEN_WIDTH,
		NS_EGraphicCore::SCREEN_HEIGHT
	);


	NS_EGraphicCore::default_batcher_for_drawing->set_active_color(NS_EColorUtils::COLOR_WHITE);


	EWindowMain::link_to_main_window = new EWindowMain();
	EWindow::window_list.push_back(EWindowMain::link_to_main_window);


	srand(time(nullptr));

	//ACCEPT/DECLINE GROUP
	EButtonGroup*
		whole_close_group = new EButtonGroup(new ERegionGabarite(350.0f, 150.0f));
	whole_close_group->root_group = whole_close_group;
	whole_close_group->is_active = false;

	EButtonGroup::confirm_decline_group = whole_close_group;

	whole_close_group->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_darken_bg);


	EButtonGroup*
		close_group_workspace_part = whole_close_group->add_close_group_and_return_workspace_group(new ERegionGabarite(100.0f, 20.0f), EGUIStyle::active_style);
	close_group_workspace_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);


	EButtonGroup*
		bottom_part_for_buttons = close_group_workspace_part->add_group(new EButtonGroup(new ERegionGabarite(250.0f, 30.0f)));
	bottom_part_for_buttons->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_with_slider, bgroup_darken_bg);
	bottom_part_for_buttons->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);
	bottom_part_for_buttons->button_size_x_override = 150.0f;

	EButtonGroup*
		top_part_for_description = close_group_workspace_part->add_group(new EButtonGroup(new ERegionGabarite(250.0f, 50.0f)));
	top_part_for_description->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_with_slider, bgroup_darken_bg);
	top_part_for_description->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);


	//text area
	ELocalisationText l_text;

	EClickableArea*
		c_area_for_group = EClickableArea::create_default_clickable_region(top_part_for_description->region_gabarite, top_part_for_description);

	ETextArea*
		text_area_for_group = ETextArea::create_centered_text_area(c_area_for_group, EFont::font_list[0], "123");

	c_area_for_group->text_area = text_area_for_group;
	text_area_for_group->localisation_text.localisations[NSW_localisation_EN] = "Warning! Unsaved changes!\\n\\nIf you continue, you lost unsaved data!";
	text_area_for_group->localisation_text.localisations[NSW_localisation_RU] = "Внимание! Несохранённые изменения!\\n\\nЕсли вы продолжите, вы потеряете несохранённые данные!";
	text_area_for_group->change_text(text_area_for_group->localisation_text.localisations[ELocalisationText::active_localisation]);
	text_area_for_group->set_color(1.0f, 0.75f, 0.5f, 1.0f);
	top_part_for_description->clickable_area_list.push_back(c_area_for_group);
	//


	l_text.localisations[NSW_localisation_EN] = "Close program";
	l_text.localisations[NSW_localisation_RU] = "Выйти из программы";
	EntityButtonConfirmAction*
	button_yes = new EntityButtonConfirmAction();
	button_yes->stored_action = &EDataActionCollection::action_close_program;

	button_yes->make_default_button_with_unedible_text
	(
		new ERegionGabarite(100.0f, 25.0f),
		bottom_part_for_buttons,
		&EDataActionCollection::action_invoke_stored_confirm_action,
		l_text.localisations[ELocalisationText::active_localisation]
	);

	button_yes->main_text_area->set_color(1.0f, 0.2f, 0.1f, 1.0f);
	button_yes->main_text_area->localisation_text = l_text;
	bottom_part_for_buttons->add_button_to_working_group(button_yes);





	l_text.localisations[NSW_localisation_EN] = "Cancel";
	l_text.localisations[NSW_localisation_RU] = "Отмена";
	EntityButtonConfirmAction*
		button_no = new EntityButtonConfirmAction();
	button_no->make_default_button_with_unedible_text
	(
		new ERegionGabarite(100.0f, 25.0f),
		bottom_part_for_buttons,
		&EDataActionCollection::action_invoke_stored_confirm_action,
		l_text.localisations[ELocalisationText::active_localisation]
	);
	button_no->main_text_area->localisation_text = l_text;
	button_no->stored_action = &EDataActionCollection::action_cancel_closing_program;
	bottom_part_for_buttons->add_button_to_working_group(button_no);


	EButtonGroup::refresh_button_group(whole_close_group);
	EWindowMain::link_to_main_window->button_group_list.push_back(whole_close_group);

	while
		(
			(!glfwWindowShouldClose(NS_EGraphicCore::main_window))
			||
			(EInputCore::NSW_have_unsave_changes)
			)
	{
		if
			(
				(EInputCore::NSW_have_unsave_changes)
				&&
				(!EButtonGroup::confirm_decline_group->is_active)
				&&
				(glfwWindowShouldClose(NS_EGraphicCore::main_window))
				)
		{
			EButtonGroup::confirm_decline_group->move_to_foreground_and_center();
			EButtonGroup::confirm_decline_group->is_active = true;
		}

		if (!ETextureGabarite::incomplete_gabarites_list.empty())
		{
			for (int i = 0; i < min(16, ETextureGabarite::incomplete_gabarites_list.size()); i++)
			{
				NS_EGraphicCore::complete_texture_gabarite(ETextureGabarite::incomplete_gabarites_list[0 + i]);
				ETextureGabarite::incomplete_gabarites_list.erase(ETextureGabarite::incomplete_gabarites_list.begin() + i);
			}
		}

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

		NS_EGraphicCore::current_zoom = round(NS_EGraphicCore::stored_zoom * 50.0f) / 50.0f;
		NS_EGraphicCore::current_zoom = max(NS_EGraphicCore::current_zoom, 0.5f);

		if (!EInputCore::MOUSE_BUTTON_LEFT)
		{
			EButtonGroup::focused_button_group = nullptr;
			EButtonGroup::focused_button_group_mouse_unpressed = nullptr;
			EButtonGroup::catched_group_for_translation = nullptr;
			EClickableArea::active_clickable_region = nullptr;
			//EButtonGroup::vector_moving_group							= nullptr;
		}

		//if (EInputCore::key_pressed_once(GLFW_KEY_LEFT_SHIFT))
		//{
		//	for (EButtonGroup* group : EButtonGroup::selected_groups)
		//	{
		//		group->is_selected = false;
		//	}

		//	EButtonGroup::selected_groups.clear();
		//}

		if (EInputCore::MOUSE_SPEED_X * EInputCore::MOUSE_SPEED_X + EInputCore::MOUSE_SPEED_Y * EInputCore::MOUSE_SPEED_Y > 0)
		{
			EButtonGroup::focused_button_group_with_slider = nullptr;
		}

		//if (!EInputCore::MOUSE_BUTTON_LEFT) { EClickableArea::active_clickable_region = nullptr; }
		/*if (*EClickableArea::active_clickable_region->parent_entity->disable_draw)
		{

		}*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

		if ((!EInputCore::MOUSE_BUTTON_LEFT) && (EButtonGroup::move_vector_mode == MoveVectorMethod::METHOD_DRAG))
		{
			EButtonGroup::vector_moving_group = nullptr;
			EButtonGroup::parent_vector_moving_group = nullptr;
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
				1024.0f,
				512.0f
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

		EInputCore::LAST_INPUTED_CHAR = 0;
		EInputCore::scroll_direction = 0;
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