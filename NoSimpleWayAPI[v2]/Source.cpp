#include <iostream>
#include <string>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

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
#include "Source.h"
#endif
/**/




//#pragma execution_character_set( "utf-8" )
//extern GLFWwindow* main_window{ nullptr };"













void register_debug_structs()
{
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::GROUP_GABARITES].icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_debug_show_region_borders");
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::GROUP_GABARITES].localisation_text = ELocalisationText::get_localisation_by_key("debug_button_show_region_border");

	DebugNamespace::NSW_registered_debug_struct[DebugStructID::CULLING_LINES].icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_debug_show_culling_lines");
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::CULLING_LINES].localisation_text = ELocalisationText::get_localisation_by_key("debug_button_show_culling_lines");
	
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::HIGHEST_POINT_Y].icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_debug_show_highest_point_y");
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::HIGHEST_POINT_Y].localisation_text = ELocalisationText::get_localisation_by_key("debug_button_show_highest_point_y");
	
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::ENTITY_GABARITES].icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_debug_show_entity_gabarites");
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::ENTITY_GABARITES].localisation_text = ELocalisationText::get_localisation_by_key("debug_button_show_entity_gabarites");
	
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::DISABLE_GL_SCISSOR].icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_debug_disable_GL_SCISSOR");
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::DISABLE_GL_SCISSOR].localisation_text = ELocalisationText::get_localisation_by_key("debug_button_disable_gl_scissor");
	
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::PHANTOM_HIGHLIGHT_FOR_GROUPS].icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_debug_highlight_phantom_draw");
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::PHANTOM_HIGHLIGHT_FOR_GROUPS].localisation_text = ELocalisationText::get_localisation_by_key("debug_button_highlight_groups");
	
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::PHANTOM_HIGHLIGHT_FOR_BUTTONS].icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_debug_highlight_phantom_draw");
	DebugNamespace::NSW_registered_debug_struct[DebugStructID::PHANTOM_HIGHLIGHT_FOR_BUTTONS].localisation_text = ELocalisationText::get_localisation_by_key("debug_button_highlight_buttons");

	/////////////////////////////////////////////////////
	{
		EButtonGroup*
		whole_debug_group = new EButtonGroup(new ERegionGabarite(260.0f, 600.0f));
		whole_debug_group->init_as_root_group(EWindowMain::link_to_main_window);
		EWindowMain::link_to_main_window->button_group_list.push_back(whole_debug_group);
		whole_debug_group->move_to_foreground_and_center();
		whole_debug_group->close_this_group();
		DebugNamespace::NSW_pointer_to_debug_window = whole_debug_group;

		EButtonGroup* workspace_part = whole_debug_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), EGUIStyle::active_style);
		whole_debug_group->add_caption_by_localistation_key("window_header_debug_window");
		for (int i = 0; i < DebugStructID::DEBUG_STRUCT_ID_LAST_ELEMENT; i++)
		{
			EntityButtonDebugStructButton*
			debug_button = new EntityButtonDebugStructButton();
			workspace_part->add_button_to_working_group(debug_button);

			debug_button->make_as_default_router_variant_button (new ERegionGabarite(180.0f, 40.0f));
			debug_button->main_text_area->localisation_text = DebugNamespace::NSW_registered_debug_struct[i].localisation_text;
			debug_button->can_be_stretched = true;
			//debug_button->new_line_method = NewLineMethod::WHEN_OUT_OF_GABARITE;

			//
			RouterVariant*
			router_variant	= new RouterVariant();

			router_variant->router_localisation	= DebugNamespace::NSW_registered_debug_struct[i].localisation_text;
			router_variant->texture = DebugNamespace::NSW_registered_debug_struct[i].icon;
			router_variant->text_color = new HSVRGBAColor();
			router_variant->text_color->set_color_RGBA(0.5f, 0.4f, 0.3f, 1.0f);

			debug_button->router_variant_list.push_back(router_variant);
			//

			//
			router_variant = new RouterVariant();

			
			router_variant->router_localisation	= DebugNamespace::NSW_registered_debug_struct[i].localisation_text;
			router_variant->texture = DebugNamespace::NSW_registered_debug_struct[i].icon;
			router_variant->text_color = new HSVRGBAColor();
			router_variant->text_color->set_color_RGBA(0.2f, 1.0f, 0.4f, 1.0f);


			debug_button->router_variant_list.push_back(router_variant);
			//

			debug_button->select_variant(0);
			debug_button->stored_debug_struct = &DebugNamespace::NSW_registered_debug_struct[i];
			DebugNamespace::NSW_registered_debug_struct[i].associated_button_router = debug_button;





			//EntityButton* switch_button;
			//switch_button = new EntityButtonForFilterBlock();
			//switch_button->make_default_bool_switcher_button
			//(
			//	new ERegionGabarite(20.0f, 20.0f),
			//	workspace_part,
			//	EDataActionCollection::action_switch_boolean_value,
			//	NS_DefaultGabarites::texture_bool_switcher_activated_box,
			//	NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
			//	&(NSW_registered_debug_struct[i].flag_status)
			//);
			//switch_button->new_line_method = NewLineMethod::WHEN_OUT_OF_GABARITE;

			//workspace_part->add_button_to_working_group(switch_button);
		}

		EButtonGroup::refresh_button_group(whole_debug_group);
		
	}
	/////////////////////////////////////////////////////

}
int main()
{
	#ifndef  _DEBUG
		FreeConsole();
	#endif //  _DEBUG

	setlocale(LC_CTYPE, "Russian");
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
	if (ESound::engine != nullptr) { ESound::engine->play2D(ESound::shootSound); }



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

	register_debug_structs();
	EWindowMain::header_line->pointer_to_debug_button->target_group = DebugNamespace::NSW_pointer_to_debug_window;


	srand(time(nullptr));









	//fast message
		EButtonGroupFastMessage*
		fast_message_button_group = new EButtonGroupFastMessage(new ERegionGabarite(350.0f, 40.0f));
		fast_message_button_group->init_as_root_group(EWindowMain::link_to_main_window);
		EButtonGroup::pointer_to_fast_message_group = fast_message_button_group;
		//EButtonGroup*
		//	inner_group = fast_message_button_group->add_group(new EButtonGroup(new ERegionGabarite(100.0f, 100.0f)));
		//inner_group->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_without_slider, bgroup_default_bg);
		//inner_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

		EClickableArea*
		clickable_area_for_group = EClickableArea::create_default_clickable_region(fast_message_button_group->region_gabarite, fast_message_button_group);

		ETextArea*
		text_area_for_group = ETextArea::create_centered_text_area(clickable_area_for_group, EFont::font_list[0], ELocalisationText::get_localisation_by_key("welcome_to_DaD_editor"));
		text_area_for_group->can_be_edited = false;

		clickable_area_for_group->text_area = text_area_for_group;

		fast_message_button_group->clickable_area_list.push_back(clickable_area_for_group);


		EWindowMain::link_to_main_window->button_group_list.push_back(fast_message_button_group);

		//fast_message_button_group->need_refresh = true;
		EButtonGroup::refresh_button_group(fast_message_button_group);
		fast_message_button_group->move_to_foreground_and_center();
		fast_message_button_group->button_group_is_active = false;
	//



	//ACCEPT/DECLINE GROUP
		EButtonGroupConfirmAction*
		whole_close_group = new EButtonGroupConfirmAction(new ERegionGabarite(350.0f, 150.0f));

		whole_close_group->init_as_confirm_decline_group(EWindowMain::link_to_main_window);
		EButtonGroupConfirmAction::confirm_decline_group = whole_close_group;
		whole_close_group->silicon_idiot = true;
		EWindowMain::link_to_main_window->button_group_list.push_back(whole_close_group);
	//


	

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::default_texture_atlas->get_framebuffer());
		glGenerateMipmap(GL_TEXTURE_2D);


	while
	(
		(!glfwWindowShouldClose(NS_EGraphicCore::main_window))
		||
		(EInputCore::NSW_have_unsave_changes)
	)
	{

		if (NS_EGraphicCore::changed_resolution)
		{
			NS_EGraphicCore::changed_resolution = false;

			glViewport(0, 0, NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);


			float resize_x_factor = NS_EGraphicCore::SCREEN_WIDTH	/ (float)NS_EGraphicCore::old_w;
			float resize_y_factor = NS_EGraphicCore::SCREEN_HEIGHT	/ (float)NS_EGraphicCore::old_h;

			//std::cout << "Resize event width:" << NS_EGraphicCore::SCREEN_WIDTH << " height: " << NS_EGraphicCore::SCREEN_HEIGHT << std::endl;

			NS_EGraphicCore::recalculate_correction();

			for (EWindow* w : EWindow::window_list)
			{
				for (EButtonGroup* group : w->button_group_list)
				{
					float real_gabarite_x = float(NS_EGraphicCore::old_w) - group->region_gabarite->size_x;
					float additional_real_gabarite_x = float(NS_EGraphicCore::SCREEN_WIDTH) - group->region_gabarite->size_x;
					float percent_x = group->region_gabarite->offset_x / (real_gabarite_x);

					group->region_gabarite->offset_x = additional_real_gabarite_x * percent_x;
					group->region_gabarite->offset_x = min(group->region_gabarite->offset_x, NS_EGraphicCore::SCREEN_WIDTH - 64.0f);
					group->region_gabarite->offset_x = max(group->region_gabarite->offset_x, -group->region_gabarite->size_x + 64.0f);




					float real_gabarite_y				= float(NS_EGraphicCore::old_h)			- group->region_gabarite->size_y;
					float additional_real_gabarite_y	= float(NS_EGraphicCore::SCREEN_HEIGHT)	- group->region_gabarite->size_y;

					float percent_y = group->region_gabarite->offset_y / (real_gabarite_y);

					group->region_gabarite->offset_y = additional_real_gabarite_y * percent_y;
					group->region_gabarite->offset_y = min(group->region_gabarite->offset_y, NS_EGraphicCore::SCREEN_WIDTH - 64.0f);
					group->region_gabarite->offset_y = max(group->region_gabarite->offset_y, -group->region_gabarite->size_y + 64.0f);






					//group->region_gabarite->offset_y = (group->region_gabarite->offset_y / old_h) * height;

					//group->need_refresh = true;
					//EButtonGroup::refresh_button_group(group);
				}


				NS_EGraphicCore::refresh_autosize_groups(w);

				for (EWindow* w : EWindow::window_list)
				{
					for (EButtonGroup* group : w->button_group_list)
					{
						EButtonGroup::refresh_button_group(group);
						//group->need_change = true;
					}
				}


			}
		}
		//make_skydome_textures(NS_DefaultGabarites::texture_gabarite_skydome);

		if
			(
				(EInputCore::NSW_have_unsave_changes)
				&&
				(!EButtonGroupConfirmAction::confirm_decline_group->button_group_is_active)
				&&
				(glfwWindowShouldClose(NS_EGraphicCore::main_window))
			)
		{
			EButtonGroupConfirmAction::confirm_decline_group->pointer_to_confirm_button->stored_action = &EDataActionCollection::action_close_program;
			EButtonGroupConfirmAction::confirm_decline_group->activate_move_to_foreground_and_center();

			EButtonGroupConfirmAction::confirm_decline_group->make_this_group_superfocused();

			//float x = 0.0;
		}

		if (!ETextureGabarite::incomplete_gabarites_list.empty())
		{

			//EInputCore::logger_simple_info("[" + std::to_string(min(16, ETextureGabarite::incomplete_gabarites_list.size())) + "] delayed textures loaded!");

			for (int i = 0; i < min(16, ETextureGabarite::incomplete_gabarites_list.size()); i++)
			{
				NS_EGraphicCore::complete_texture_gabarite(ETextureGabarite::incomplete_gabarites_list[0 + i]);
				//NS_EGraphicCore::complete_texture_gabarite(ETextureGabarite::incomplete_gabarites_list[0 + i]);
				ETextureGabarite::incomplete_gabarites_list.erase(ETextureGabarite::incomplete_gabarites_list.begin() + i);
			}

			if (ETextureGabarite::incomplete_gabarites_list.empty())
			{
				

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::default_texture_atlas->get_framebuffer());

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//texture filtering
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

				glGenerateMipmap(GL_TEXTURE_2D);

				
			}
			else
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, NS_EGraphicCore::default_texture_atlas->get_framebuffer());
				//glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glfwPollEvents();

		//NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP_TO_EDGE, GL_NEAREST);
		NS_EGraphicCore::gl_set_blend_mode_default();

		NS_EGraphicCore::current_zoom = round(NS_EGraphicCore::stored_zoom * 20.0f) / 20.0f;
		NS_EGraphicCore::current_zoom = max(NS_EGraphicCore::current_zoom, 0.5f);

		//NS_EGraphicCore::stored_zoom = NS_EGraphicCore::current_zoom;

		if (!EInputCore::MOUSE_BUTTON_LEFT)
		{
			EButtonGroup::focused_button_group = nullptr;
			EButtonGroup::focused_button_group_mouse_unpressed = nullptr;
			EButtonGroup::catched_group_for_translation = nullptr;
			EClickableArea::active_clickable_region = nullptr;
			//EButtonGroup::vector_moving_group							= nullptr;
		}

		//if (EButtonGroup::super_focus_on_this_group != nullptr) { EButtonGroup::super_focus_on_this_group->highlight_this_group(); }
		//if ((EButtonGroup::super_focus_on_this_group != nullptr) && (!EButtonGroup::super_focus_on_this_group->is_this_group_active()))
		//{
		//	EButtonGroup::super_focus_on_this_group = nullptr;
		//}

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

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

			w->GUI_draw_second_pass(NS_EGraphicCore::delta_time);
			NS_EGraphicCore::pbr_batcher->draw_call();
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();

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

		//NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP, GL_NEAREST);
		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);

		if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
		for (int i = 0; i < texture_skydome_levels; i++)
		{
			if (EInputCore::key_pressed(GLFW_KEY_1 + i))
			{
				NS_EGraphicCore::set_source_FBO(GL_TEXTURE0, NS_EGraphicCore::skydome_texture_atlas[i]->get_colorbuffer());


				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

		if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT) && (EInputCore::key_pressed(GLFW_KEY_0)))
		{
			NS_EGraphicCore::default_batcher_for_drawing->draw_call();
			NS_EGraphicCore::default_batcher_for_drawing->set_active_color(NS_EColorUtils::COLOR_WHITE);
			NS_EGraphicCore::set_source_FBO(GL_TEXTURE0, NS_EGraphicCore::default_texture_atlas->get_colorbuffer());
			
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
				NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,
				0.0,
				0.0f,
				1024.0f,
				512.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);

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
		glFlush();
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

				fcg->just_created_group->need_change = true;
				fcg->target_group->need_change = true;

				//EButtonGroup::change_group(fcg->just_created_group);
				//EButtonGroup::change_group(fcg->target_group);



			};

			EButtonGroup::fresh_created_block_list.clear();
			EButtonGroup::fresh_created_block_list.shrink_to_fit();

		}
		///////

		//EInputCore::logger_param("data calls", ESpriteLayer::data_copy_calls);
		//EInputCore::logger_param("data copied", ESpriteLayer::data_copies_count);

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			EInputCore::logger_simple_error("GL ERROR: " + std::to_string(err));// Process/log the error.
		}
	}

	for (EWindow* w : EWindow::window_list)
	{
		w->action_on_close();
	}

	return 0;

}


