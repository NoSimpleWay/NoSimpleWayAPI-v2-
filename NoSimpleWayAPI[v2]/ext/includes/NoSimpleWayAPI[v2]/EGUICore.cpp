#pragma once
#ifndef _E_GUI_CORE_ALREADY_LINKED_
#define _E_GUI_CORE_ALREADY_LINKED_
#include "EGUICore.h"
#endif

std::vector<EWindow*> EWindow::window_list;

EButtonGroup* EButtonGroup::focused_button_group = nullptr;
EButtonGroup* EButtonGroup::focused_button_group_for_select = nullptr;
EButtonGroup* EButtonGroup::focused_button_group_mouse_unpressed = nullptr;
EButtonGroup* EButtonGroup::catched_group_for_translation = nullptr;
//EButtonGroup*				EButtonGroup::super_focus_on_this_group = nullptr;
std::vector <EButtonGroup*>	EButtonGroup::super_focus_list;

EButtonGroupFastMessage* EButtonGroup::pointer_to_fast_message_group = nullptr;


EButtonGroup* EButtonGroup::vector_moving_group = nullptr;
EButtonGroup* EButtonGroup::parent_vector_moving_group = nullptr;



EButtonGroup* EButtonGroup::parent_for_selected_groups = nullptr;
EButtonGroup* EButtonGroup::first_selected_element = nullptr;
EButtonGroup* EButtonGroup::last_selected_element = nullptr;
std::vector<EButtonGroup*>		EButtonGroup::selected_groups;

MoveVectorMethod				EButtonGroup::move_vector_mode = MoveVectorMethod::METHOD_DRAG;



EButtonGroupConfirmAction* EButtonGroupConfirmAction::confirm_decline_group = nullptr;

//EButtonGroup* EButtonGroup::focused_button_group;
EButtonGroup* EButtonGroup::focused_button_group_with_slider = nullptr;


EButtonGroup* EButtonGroup::add_content_to_filter_block_group = nullptr;



EButtonGroupSoundList* EButtonGroup::sound_list_group = nullptr;

std::vector<FreshCreatedGroup*>	EButtonGroup::fresh_created_block_list;

constexpr float BUTTON_GROUP_Y_DISTANCE = 0.0f;



void EWindow::update_default(float _d)
{

}

void EWindow::update_additional(float _d)
{
}

void EWindow::GUI_update_default(float _d)
{

	//DELETE
	bool any_remove = false;

	for (int i = 0; i < button_group_list.size(); i++)
		if ((button_group_list[i] != nullptr) && (button_group_list[i]->block_need_remove))
		{
			if (!disable_deleting)
			{
				delete button_group_list[i];
			}

			EInputCore::logger_simple_success("Need remove [" + std::to_string(i) + "] element of button group list");

			button_group_list.erase(button_group_list.begin() + i);

			i--;

			any_remove = true;
		}




	int catched_group_id = -1;

	if (window_need_refresh)
	{
		window_need_refresh = false;

		NS_EGraphicCore::refresh_autosize_groups(this);

		for (EButtonGroup* group : button_group_list)
		{
			EButtonGroup::refresh_button_group(group);
		}
	}

	//MOVING
	if
		(
			(EButtonGroup::parent_vector_moving_group != nullptr)
			&&
			(EButtonGroup::vector_moving_group != nullptr)
			&&
			(
				(
					(EButtonGroup::move_vector_mode == MoveVectorMethod::METHOD_DRAG)
					&&
					(!EInputCore::MOUSE_BUTTON_LEFT)
					)
				||
				(
					(EButtonGroup::move_vector_mode == MoveVectorMethod::METHOD_PRESS)
					&&
					(EInputCore::MOUSE_BUTTON_LEFT)
					&&
					(EClickableArea::active_clickable_region == nullptr)
					)
				)
			)
	{

		EButtonGroup* catched_group = nullptr;

		for (int i = 0; i < EButtonGroup::parent_vector_moving_group->group_list.size(); i++)
			if
				(
					(!EButtonGroup::parent_vector_moving_group->group_list[i]->group_is_suppressed)
					&&
					(!EButtonGroup::parent_vector_moving_group->group_list[i]->is_blocked_by_superfocus())
					&&
					(EButtonGroup::catched_by_mouse(EButtonGroup::parent_vector_moving_group->group_list[i]))
				)
			{
				catched_group = EButtonGroup::parent_vector_moving_group->group_list[i];
			}

		if (catched_group != nullptr)
		{
			if (EButtonGroup::selected_groups.empty())
			{
				int moved_group_id = -1;

				//VECTOR MOVING ID
				for (int i = 0; i < EButtonGroup::parent_vector_moving_group->group_list.size(); i++)
					if (EButtonGroup::parent_vector_moving_group->group_list[i] == EButtonGroup::vector_moving_group)
					{
						moved_group_id = i;
						break;
					}



				if ((catched_group != nullptr) && (catched_group != EButtonGroup::vector_moving_group))
				{


					EButtonGroup::parent_vector_moving_group->group_list.erase(EButtonGroup::parent_vector_moving_group->group_list.begin() + moved_group_id);

					std::vector<EButtonGroup*>::iterator catched_iterator = std::find(EButtonGroup::parent_vector_moving_group->group_list.begin(), EButtonGroup::parent_vector_moving_group->group_list.end(), catched_group);

					if (catched_iterator != std::end(EButtonGroup::parent_vector_moving_group->group_list))
					{
						EButtonGroup::parent_vector_moving_group->group_list.insert(catched_iterator, EButtonGroup::vector_moving_group);
					}


					EButtonGroup::parent_vector_moving_group->need_change = true;

					EButtonGroup::parent_vector_moving_group = nullptr;
					EButtonGroup::vector_moving_group = nullptr;


				}
			}
			else
			{


				//if (catched_group_id <= EButtonGroup::parent_vector_moving_group->group_list.size() - EButtonGroup::selected_groups.size() + 1)
				{
					std::vector<EButtonGroup*>::iterator start_erasing = std::find(EButtonGroup::parent_vector_moving_group->group_list.begin(), EButtonGroup::parent_vector_moving_group->group_list.end(), EButtonGroup::selected_groups.front());
					std::vector<EButtonGroup*>::iterator end_erasing = std::find(EButtonGroup::parent_vector_moving_group->group_list.begin(), EButtonGroup::parent_vector_moving_group->group_list.end(), EButtonGroup::selected_groups.back());
					std::vector<EButtonGroup*>::iterator catched_iterator = std::find(EButtonGroup::selected_groups.begin(), EButtonGroup::selected_groups.end(), catched_group);

					//if ((first_moved_group_id != -1) && (last_moved_group_id != -1) && (catched_group_id != -1))
					if
						(
							(start_erasing != std::end(EButtonGroup::parent_vector_moving_group->group_list))
							&&
							(end_erasing != std::end(EButtonGroup::parent_vector_moving_group->group_list))
							&&
							(catched_iterator != std::end(EButtonGroup::parent_vector_moving_group->group_list))
							)
					{
						//		if focused not selection vector
						if (catched_iterator == EButtonGroup::selected_groups.end())
						{

							EButtonGroup::parent_vector_moving_group->group_list.erase(start_erasing, min(end_erasing + 1, EButtonGroup::parent_vector_moving_group->group_list.end() - 1));

							catched_iterator = std::find(EButtonGroup::parent_vector_moving_group->group_list.begin(), EButtonGroup::parent_vector_moving_group->group_list.end(), catched_group);


							EButtonGroup::parent_vector_moving_group->group_list.insert(catched_iterator, EButtonGroup::selected_groups.begin(), EButtonGroup::selected_groups.end());


							EButtonGroup::parent_vector_moving_group->need_change = true;

							EButtonGroup::parent_vector_moving_group = nullptr;
							EButtonGroup::vector_moving_group = nullptr;

							for (EButtonGroup* group : EButtonGroup::selected_groups)
							{
								group->is_selected = false;
							}

							EButtonGroup::selected_groups.clear();

							EButtonGroup::first_selected_element = nullptr;
							EButtonGroup::last_selected_element = nullptr;

							EButtonGroup::parent_for_selected_groups = nullptr;
						}
					}
				}
			}
		}

		//EButtonGroup::parent_vector_moving_group = nullptr;
		//EButtonGroup::vector_moving_group = nullptr;
	}


	for (EButtonGroup* b_group : button_group_list)
		if
			(
				(b_group != nullptr)
				&&
				(b_group->is_this_group_active())
				&&
				(!b_group->block_need_remove)
				&&
				(b_group->region_gabarite->world_position_y <= b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y)
				&&
				(b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y >= b_group->region_gabarite->world_position_y)
				)
		{
			EButtonGroup::get_last_focused_group(b_group);
		}

	//RESET GROUP SELECTION
	if
		(
			(EInputCore::key_pressed_once(GLFW_KEY_LEFT_SHIFT))
			||
			(EInputCore::key_pressed_once(GLFW_KEY_ESCAPE))
			)
	{
		for (EButtonGroup* group : EButtonGroup::selected_groups)
		{
			group->is_selected = false;
		}

		EButtonGroup::selected_groups.clear();

		EButtonGroup::first_selected_element = nullptr;
		EButtonGroup::last_selected_element = nullptr;

		EButtonGroup::parent_for_selected_groups = nullptr;

	}

	//SELECT BUTTON GROUP BLOCKS
	if
		(
			(EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
			&&
			(EButtonGroup::focused_button_group_for_select != nullptr)
			&&
			(EButtonGroup::focused_button_group_for_select->root_group == EButtonGroup::focused_button_group_mouse_unpressed->root_group)
			)
	{
		if
			(EButtonGroup::first_selected_element == nullptr)
		{
			EButtonGroup::first_selected_element = EButtonGroup::focused_button_group_for_select;
			EButtonGroup::last_selected_element = EButtonGroup::focused_button_group_for_select;

			EButtonGroup::parent_for_selected_groups = EButtonGroup::focused_button_group_for_select->parent_group;
		}
		else
		{
			if
				(
					(EButtonGroup::focused_button_group_mouse_unpressed != nullptr)
					&&
					(EButtonGroup::parent_for_selected_groups->root_group == EButtonGroup::focused_button_group_mouse_unpressed->root_group)
					)
			{
				EButtonGroup::last_selected_element = EButtonGroup::focused_button_group_for_select;
			}
		}

		for (EButtonGroup* group : EButtonGroup::selected_groups)
		{
			group->is_selected = false;
		}

		EButtonGroup::selected_groups.clear();

		if ((EButtonGroup::first_selected_element != EButtonGroup::last_selected_element) && (EButtonGroup::parent_for_selected_groups != nullptr))
		{


			int first_id = -1;
			int last_id = -1;

			for (int i = 0; i < EButtonGroup::parent_for_selected_groups->group_list.size(); i++)
			{
				if (EButtonGroup::parent_for_selected_groups->group_list[i] == EButtonGroup::first_selected_element) { first_id = i; break; }
			}

			for (int i = 0; i < EButtonGroup::parent_for_selected_groups->group_list.size(); i++)
			{
				if (EButtonGroup::parent_for_selected_groups->group_list[i] == EButtonGroup::last_selected_element) { last_id = i; break; }
			}

			if ((first_id != -1) && (last_id != -1))
			{
				int first_element = min(first_id, last_id);
				int last_element = max(first_id, last_id);

				for (int i = first_element; i <= last_element; i++)
				{
					EButtonGroup::parent_for_selected_groups->group_list[i]->is_selected = true;
					EButtonGroup::selected_groups.push_back(EButtonGroup::parent_for_selected_groups->group_list[i]);
				}
			}
		}
	}

	//UNPRESSED LMB
	//GET FOCUSED BUTTON CLICKABLE REGION IN FOCUSED GROUP
	if
		(
			((EButtonGroup::focused_button_group_mouse_unpressed != nullptr))
			&&
			(!EInputCore::MOUSE_BUTTON_LEFT)
			)
	{
		//EButtonGroup::focused_button_group_mouse_unpressed->highlight_this_group();

		for (EntityButton* but : EButtonGroup::focused_button_group_mouse_unpressed->all_button_list)
			if ((but->be_visible_last_time) && (but->entity_is_active()))
				for (ECustomData* data : but->custom_data_list)
					for (EClickableArea* c_area : data->clickable_area_list)
					{

						if (EClickableArea::overlapped_by_mouse(c_area, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
						{
							EClickableArea::active_clickable_region = c_area;
						}
						else
						{
							if ((c_area->debug_updating) && (EInputCore::mouse_button_pressed_once(GLFW_MOUSE_BUTTON_LEFT)))
							{
								//not overlap by mouse
								if (!EClickableArea::overlapped_by_mouse(c_area, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
								{
									EInputCore::logger_simple_error("area not overlapepd by mouse");
								}

								//not active
								if (but->entity_is_active())
								{
									EInputCore::logger_simple_error("entity is not active");
								}
							}

						}
					}
	}



	int id = 0;
	for (int i = 0; i < button_group_list.size(); i++)
	{
		EButtonGroup* b_group = button_group_list[i];


		b_group->background_update(_d);

		//for (EButtonGroup* b_group : button_group_list)
		if
			(b_group == nullptr)
		{
			//
		}
		else
			if//group active and in visible gabarites
				(
					(b_group->is_this_group_active())
					&&
					(b_group->is_in_visible_diapason())
					&&
					(!b_group->block_need_remove)
					/*(b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y >= 0.0f)
					&&
					(b_group->region_gabarite->world_position_y <= NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)*/
					//&&
					//(b_group->can_see_this_group())	
					)
			{
				b_group->recursive_recalculate_culling_lines();
				//b_group->lower_culling_line = b_group->region_gabarite->world_position_y;
				//b_group->higher_culling_line = b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y;

				b_group->button_group_update(_d);


				id++;
			}
			else
			{
				b_group->try_vipe_data(_d);
			}




	}


}

void EWindow::GUI_update_additional(float _d)
{
}

void EWindow::draw_default(float _d)
{
}

void EWindow::draw_additional(float _d)
{
}

void EWindow::GUI_draw_default(float _d)
{


	for (EButtonGroup* b_group : button_group_list)
		if
			(
				(b_group != nullptr)
				&&
				(b_group->is_this_group_active())
				&&
				(b_group->is_in_visible_diapason())
				&&
				(!b_group->block_need_remove)
				)
		{
			b_group->draw_button_group();
		}



	for (EButtonGroup* b_group : button_group_list)
	{
		b_group->draw_button_group_debug_overlay();
	}

}

void EWindow::GUI_draw_additional(float _d)
{
}

void EWindow::GUI_draw_second_pass(float _d)
{
	//glDisable(GL_SCISSOR_TEST);

	//for (EButtonGroup* b_group : group_list)
	//{
	//	b_group->draw_second_pass();

	//	if (b_group->header_button_group != nullptr)
	//	{b_group->header_button_group->draw_second_pass();}
	//}

	//EInputCore::logger_simple_info(a"@");

	//int counter = 0;
	//for (EButtonGroup* b_group : button_group_list)
	//if ((b_group != nullptr) && (b_group->button_group_is_active))
	//{
	//	b_group->draw_second_pass();
	//	counter++;
	//}

}

void EWindow::action_on_close()
{
}

void EButtonGroup::recursive_set_suppressed()
{
	group_is_suppressed = true;

	for (EButtonGroup* group : group_list)
	{
		group->recursive_set_suppressed();
	}
}

void EButtonGroup::recursive_unsuppress()
{
	group_is_suppressed = false;

	for (EButtonGroup* group : group_list)
	{
		group->recursive_unsuppress();
	}
}

bool EButtonGroup::is_blocked_by_superfocus()
{

	//if (silicon_idiot)
	//{
	//	root_group = root_group;
	//}


	return	!(
		(EButtonGroup::super_focus_list.empty())
		||
		(EButtonGroup::super_focus_list.back() == this)
		||
		(EButtonGroup::super_focus_list.back() == this->root_group)
		);
}

bool EButtonGroup::is_this_group_active()
{

	return (button_group_is_active) && (group_search_status != GroupSearchStatus::SEARCH_STATUS_REJECTED);
}

EButtonGroup::EButtonGroup(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y)
{
	if (region_gabarite == nullptr)
	{
		ERegionGabarite::set_region_gabarite
		(&region_gabarite, new ERegionGabarite(_offset_x, _offset_y, _size_x, _size_y));
	}
	else
	{
		region_gabarite->set_region_offset_and_size(_offset_x, _offset_y, _offset_z, _size_x, _size_y);
	}
}

EButtonGroup::EButtonGroup(ERegionGabarite* _region)
{
	ERegionGabarite::set_region_gabarite(&region_gabarite, _region);
	//region_gabarite = _region;
}

EButtonGroup::EButtonGroup()
{
}

EButtonGroup::~EButtonGroup()
{
	unmake_this_group_superfocused();

	if (debug_deleting) { EInputCore::logger_simple_success("Destructor [for button group] called"); }

	//EInputCore::logger_simple_success("Destroy button group");

	if ((region_gabarite != nullptr))
	{
		region_gabarite->pointers_to_this_object--;

		if (region_gabarite->pointers_to_this_object <= 0)
		{
			if (!disable_deleting)
			{
				delete region_gabarite;
			}
		}
	}

	for (int i = 0; i < all_button_list.size(); i++)
	{
		if (!disable_deleting)
		{
			if (debug_deleting) EInputCore::logger_simple_info("try delete button");

			delete all_button_list[i];
		}

	}
	all_button_list.clear();
	all_button_list.shrink_to_fit();

	workspace_button_list.clear();
	workspace_button_list.shrink_to_fit();

	if (!disable_deleting)
		for (EClickableArea* c_area : clickable_area_list)
		{
			delete c_area;
		}
	clickable_area_list.clear();
	clickable_area_list.shrink_to_fit();

	if (!disable_deleting) {
		delete background_sprite_layer;
	}


	for (int i = 0; i < group_list.size(); i++)
	{
		if (!disable_deleting)
		{
			delete group_list[i];
		}

		//i--;
	};
	group_list.clear();
	group_list.shrink_to_fit();

	delete data_container;

}

void EButtonGroup::delete_exact_button(EntityButton* _button)
{

	all_button_list.erase(std::find(all_button_list.begin(), all_button_list.end(), _button));
	workspace_button_list.erase(std::find(workspace_button_list.begin(), workspace_button_list.end(), _button));

	if (!disable_deleting) { delete _button; }
}

void EButtonGroup::remove_all_workspace_buttons()
{
	for (int i = 0; i < all_button_list.size(); i++)
	{
		if (!all_button_list[i]->cannot_be_auto_deleted)
		{

			if (!disable_deleting) {
				delete all_button_list[i];
			}

			all_button_list.erase(all_button_list.begin() + i);

			i--;
		}
	}
	workspace_button_list.clear();
	workspace_button_list.shrink_to_fit();
}

void EButtonGroup::try_vipe_data(float _d)
{
	if (vipe_timer > 0.0f)
	{
		vipe_timer -= _d;

		if ((vipe_timer <= 0.0f) && (!is_viped))
		{
			is_viped = true;

			destroy_all_vertex_buffer_data();

			group_phantom_redraw = true;
		}
	}
}

void EButtonGroup::close_this_group()
{
	button_group_is_active = false;
	destroy_all_vertex_buffer_data();
	need_refresh = true;

	unmake_this_group_superfocused();

	recursive_close_process();
}

void EButtonGroup::recursive_close_process()
{

	unmake_this_group_superfocused();

	for (EntityButton* but : all_button_list)
	{
		but->destroy_attached_description();
		but->hover_time = 0.0f;

		for (ECustomData* c_data : but->custom_data_list)
			for (EClickableArea* c_area : c_data->clickable_area_list)
			{
				//c_area->catched_body	= false;
				//c_area->catched_side_down = false;
				c_area->hover_time = 0.0f;

				if (EClickableArea::active_clickable_region == c_area)
				{
					EClickableArea::active_clickable_region = nullptr;
				}
			}

	}

	for (EButtonGroup* group : group_list)
	{
		group->recursive_close_process();
	}
}

void EButtonGroup::destroy_all_vertex_buffer_data()
{
	//all clickalbe areas
	for (EClickableArea* c_area : clickable_area_list)
	{
		for (ESpriteLayer* s_layer : c_area->sprite_layer_list)
		{
			s_layer->destroy_vertex_buffer();
		}

		if (c_area->text_area != nullptr)
		{
			c_area->text_area->sprite_layer->destroy_vertex_buffer();
		}
	}

	if (background_sprite_layer != nullptr)
	{
		background_sprite_layer->destroy_vertex_buffer();
	}

	for (EntityButton* but : all_button_list)
	{
		if ((!but->sprite_layer_list.empty())&&(but->sprite_layer_list[0]->total_capacity > 100000))
		{
			but = but;
		}
		but->destroy_all_vertex_buffer_data();
	}

	group_phantom_redraw = false;

	for (EButtonGroup* child : group_list)
	{
		child->destroy_all_vertex_buffer_data();
	}
}

void EButtonGroup::make_this_group_superfocused()
{
	EButtonGroup::super_focus_list.push_back(this);
}

void EButtonGroup::unmake_this_group_superfocused()
{
	if
		(
			std::find
			(
				EButtonGroup::super_focus_list.begin(),
				EButtonGroup::super_focus_list.end(),
				this
			)
			!=
			EButtonGroup::super_focus_list.end()
			)
	{
		EButtonGroup::super_focus_list.erase
		(
			std::find
			(
				EButtonGroup::super_focus_list.begin(),
				EButtonGroup::super_focus_list.end(),
				this
			)
		);
	}
	/*if (EButtonGroup::super_focus_list.empty())
	{

	}
	else
	if (EButtonGroup::super_focus_list.size() == 1)
	{
		EButtonGroup::super_focus_list.clear();
	}
	else
	{
		std::remove(EButtonGroup::super_focus_list.begin(), EButtonGroup::super_focus_list.end(), this);
	}*/



}


void EButtonGroup::button_group_update(float _d)
{
	//clickable_area->update(_d);

	//subgroup
	//EButtonGroup* prev_group = nullptr;


	//invisible elements become visible

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
		&&
		(EButtonGroup::focused_button_group_mouse_unpressed == this)
	)
	{
		float dir = 0.0f;

		if (EInputCore::key_pressed(GLFW_KEY_UP)) { dir = 1.0f; }
		if (EInputCore::key_pressed(GLFW_KEY_DOWN)) { dir = -1.0f; }

		if (dir != 0.0f)
		{
			region_gabarite->size_y += 32.0f * dir * _d;
			base_height += 32.0f * dir * _d;

			if (root_group != nullptr)
			{
				root_group->need_change = true;
			}
			else
			{
				need_change = true;
			}
		}


	}

	if
		(
			(EInputCore::key_pressed_once(GLFW_KEY_RIGHT_SHIFT))
			&&
			(EButtonGroup::focused_button_group_mouse_unpressed == this)
			)
	{

		recursive_get_info();
	}



	if (autodelete_time >= 0.0f)
	{
		autodelete_time -= _d;

		if (autodelete_time <= 0.0f)
		{
			block_need_remove = true;
		}
	}



	/*if (row->header_button_group != nullptr)
	{
		row->header_button_group->update(_d);
	}*/
	//if (highlight_time > 0.0f) { highlight_time -= _d; }
	//EInputCore::logger_param("wtf", (group_list.size()) - 1);

	if (!group_list.empty())
		for (int i = 0; i < (int)(group_list.size()) - 1; i++)
			if ((!group_list[i]->block_need_remove) && (group_list[i]->swap_to_next))
			{


				group_list[i]->swap_to_next = false;

				EButtonGroup*
					swap = group_list[i];

				group_list[i] = group_list[i + 1];
				group_list[i + 1] = swap;

				swap->highlight_this_group_green_info();
				need_refresh = true;
			}


	//update_highlights

	if (!highlight_list.empty())
	{
		using namespace std::chrono;
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		for (int i = 0; i < highlight_list.size(); i++)
		{
			HighlightStruct*
				pointer_to_highlight = &highlight_list[i];

			//std::cout << "current: " << (ms) << " stored: " << pointer_to_highlight->highlight_timestamp << std::endl;;

			if (ms - pointer_to_highlight->highlight_timestamp > (milliseconds)(1000))
			{
				pointer_to_highlight->time_remaining = 0.001f;
			}

			if (pointer_to_highlight->time_remaining > 0.0f)
			{
				pointer_to_highlight->time_remaining -= _d;

				if (pointer_to_highlight->time_remaining <= 0.0f)
				{
					highlight_list.erase(highlight_list.begin() + i);

					i--;
				}
			}
		}
	}

	bool any_remove = false;
	for (int i = 0; i < group_list.size(); i++)
		if ((group_list[i] != nullptr) && (group_list[i]->block_need_remove))
		{
			if (!disable_deleting)
			{
				delete group_list[i];
			}
			EInputCore::logger_simple_success("Need remove [" + std::to_string(i) + "] child element of button group list");

			group_list.erase(group_list.begin() + i);

			i--;


			any_remove = true;
		}

	if (any_remove)
	{
		need_change = true;
	}

	if (need_refresh)
	{
		EButtonGroup::refresh_button_group(this);

		need_refresh = false;


	}

	if (need_change)
	{
		EButtonGroup::change_group(this);

		need_change = false;
	}

	bool any_button_order_change = false;

	if (!all_button_list.empty())
		for (unsigned int i = 0; i < all_button_list.size(); i++)
			if (all_button_list[i]->entity_need_remove)
			{
				any_button_order_change = true;

				if (debug_deleting) { EInputCore::logger_simple_info("Detect 'need remove', try remove"); }

				delete_exact_button(all_button_list[i]);

				i--;

			}

	if (any_button_order_change)
	{
		EButtonGroup::change_group(this);
	}



	if
		(
			(is_this_group_active())//group not deactivated
			&&
			(is_in_visible_diapason())//in visible gabarites
			&&
			(!block_need_remove)
		)
	{

		phantom_translate_if_need();


		for (EntityButton* but : all_button_list)
		{
			//can see this button
			if
				(
					(but->entity_is_active())
					&&
					(but->button_in_culling_gabarites())
					)
			{
				//visible last time?

				but->be_visible_last_time = true;

				//phantom translation
				if (but->button_gabarite->have_phantom_translation)
				{
					but->button_gabarite->have_phantom_translation = false;

					but->translate_entity
					(
						but->button_gabarite->phantom_translate_x,
						but->button_gabarite->phantom_translate_y,
						but->button_gabarite->phantom_translate_z,
						true
					);

					but->button_gabarite->phantom_translate_x = 0.0f;
					but->button_gabarite->phantom_translate_y = 0.0f;
					but->button_gabarite->phantom_translate_z = 0.0f;
				}

				//update
				if
				(
					(
						(!group_is_suppressed)
						||
						(but == slider)
					)
					&&
					(!is_blocked_by_superfocus())
				)
				{
					but->update(_d);
				}
			}
			else
			{
				but->be_visible_last_time = false;
				but->hover_time = 0.0f;
			}

			//destroy attached descripton if button dont vsible
			if (!but->be_visible_last_time)
			{
				but->destroy_attached_description();
			}
		}

		//move group by mouse
		if
			(
				(EInputCore::MOUSE_BUTTON_LEFT)
				&&
				(root_group != nullptr)
				&&
				(root_group->can_be_moved)
				&&
				(EButtonGroup::focused_button_group_mouse_unpressed == this)
				&&
				(EClickableArea::active_clickable_region == nullptr)
				&&
				(
					(EButtonGroup::catched_group_for_translation == root_group)
					||
					(EButtonGroup::catched_group_for_translation == nullptr)
					)
				)
		{
			if (EButtonGroup::catched_group_for_translation == nullptr)
			{
				EButtonGroup::catched_group_for_translation = root_group;
				root_group->move_to_foreground();
			}


			root_group->translate_group(EInputCore::MOUSE_SPEED_X / NS_EGraphicCore::current_zoom, EInputCore::MOUSE_SPEED_Y / NS_EGraphicCore::current_zoom, 0.0f, true);
			//root_group->recursive_recalculate_culling_lines();
			//root_group->need_recalculate_culling_lines = true;
		}
		else
		{
			if (debug_translation)
			{
				if (root_group == nullptr) { EInputCore::logger_simple_error("root group is null!"); }
				else
					if (!root_group->can_be_moved) { EInputCore::logger_simple_error("group cannot be moved!"); }
					else
						if (EButtonGroup::focused_button_group != this) { EInputCore::logger_simple_error("this group not focused"); }
						else
							if
								(EClickableArea::active_clickable_region != nullptr)
							{
								EInputCore::logger_simple_error("focused some clickable region");

								EInputCore::logger_param("x", EClickableArea::active_clickable_region->region_gabarite->world_position_x);
								EInputCore::logger_param("y", EClickableArea::active_clickable_region->region_gabarite->world_position_y);
							}
			}
		}

		for (group_update_action gua : actions_on_update)
		{
			gua(this);
		}

		for (EClickableArea* group_clickable_area : clickable_area_list)
			if ((group_clickable_area != nullptr) && (group_clickable_area->clickable_region_is_active))
			{
				group_clickable_area->update(_d);
			}

		for (int i = 0; i < group_list.size(); i++)
		{
			group_list[i]->button_group_update(_d);
		}
	}
	else
	{
		try_vipe_data(_d);
	}



}

void EButtonGroup::background_update(float _d)
{
}

void EButtonGroup::recursive_get_info()
{
	EInputCore::logger_param("HPYb:", highest_point_y_for_buttons);
	EInputCore::logger_param("HPYg:", highest_point_y_for_groups);

	EInputCore::logger_param("group size y", region_gabarite->size_y);
	EInputCore::logger_param("group base y", base_height);

	EInputCore::logger_param("offset_x", region_gabarite->offset_x);
	EInputCore::logger_param("offset_y:", region_gabarite->offset_y);

	EInputCore::logger_param("offset_left:", group_offset_for_content_left);
	EInputCore::logger_param("offset_right:", group_offset_for_content_right);
	EInputCore::logger_param("offset_up:", group_offset_for_content_right);
	EInputCore::logger_param("offset_bottom:", group_offset_for_content_bottom);

	EInputCore::logger_param("world_x:", region_gabarite->world_position_x);
	EInputCore::logger_param("world_y:", region_gabarite->world_position_y);


	EInputCore::logger_param("phantom translate x:", region_gabarite->phantom_translate_x);
	EInputCore::logger_param("phantom translate y:", region_gabarite->phantom_translate_y);

	EInputCore::logger_param("scroll_y", scroll_y);

	std::cout << std::endl << std::endl;

	if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
		for (EButtonGroup* child : group_list)
		{
			child->recursive_get_info();
		}
}

void EButtonGroup::draw_button_group()
{
	//clickable_area->draw();

	//EInputCore::logger_simple_success("draw button group");
	if
	(
			(is_in_visible_diapason())
			&&
			(is_this_group_active())
			&&
			(!block_need_remove)
	)
	{
		//bool visibility = is_this_group_active();

		//if (visibility)
		{
			if (group_phantom_redraw)
			{

				EButtonGroup::generate_vertex_buffer_for_group(this, NSW_RECURSIVE);
				//highlight_this_group();
				group_phantom_redraw = false;

				if (DebugNamespace::is_debug_element_active(DebugStructID::PHANTOM_HIGHLIGHT_FOR_GROUPS))
				{
					highlight_this_group_green_info();
				}

				//EInputCore::logger_simple_info("Phantom redraw!");
			}

			//batcher_for_default_draw->draw_call();


			glDisable(GL_SCISSOR_TEST);

			//SUPERFOCUS BACKROUND FULLSCREEN SHADE
			if
				(
					(!EButtonGroup::super_focus_list.empty())
					&&
					(EButtonGroup::super_focus_list.back() == this)
					)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_DARK_GREY, 0.64f);
				ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					0.0f,
					0.0f,

					NS_EGraphicCore::SCREEN_WIDTH * NS_EGraphicCore::current_zoom,
					NS_EGraphicCore::SCREEN_HEIGHT * NS_EGraphicCore::current_zoom,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);

			}

			//BLURED SHADOW
			if ((have_shadow) && (root_group == this))
			{

				batcher_for_default_draw->draw_call();



				NS_EGraphicCore::set_active_color(0.01f, 0.02f, 0.04f, 1.0f);
				ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 8);
				NS_ERenderCollection::add_data_to_vertex_buffer_shade
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x,
					region_gabarite->world_position_y,
					region_gabarite->size_x,
					region_gabarite->size_y,
					shadow_size,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);




			}
			batcher_for_default_draw->draw_call();
			//batcher_for_default_draw->draw_call();

			//BEGIN DRAW SCISSORED ELEMENTS

			if (!DebugNamespace::is_debug_element_active(DebugStructID::DISABLE_GL_SCISSOR))
			{
				glEnable(GL_SCISSOR_TEST);
			}

			if (parent_group != nullptr)
			{
				glScissor
				(
					region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
					lower_culling_line_for_group * NS_EGraphicCore::current_zoom,

					region_gabarite->size_x * NS_EGraphicCore::current_zoom,
					max(0.0f, higher_culling_line_for_group - lower_culling_line_for_group) * NS_EGraphicCore::current_zoom
				);
			}
			else
			{
				glScissor
				(
					region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
					region_gabarite->world_position_y * NS_EGraphicCore::current_zoom,

					region_gabarite->size_x * NS_EGraphicCore::current_zoom,
					region_gabarite->size_y * NS_EGraphicCore::current_zoom
				);
			}

			//BG
			if ((background_sprite_layer != nullptr) && (group_have_background))
			{
				background_sprite_layer->transfer_vertex_buffer_to_batcher();
			}

			//////		DRAW BUTTON LINE BG		//////
			if ((button_size_x_override > 0.0f) || (group_have_button_lines))
				for (EButtonGroupLine line : button_line_list)
					if
						(
							(region_gabarite->world_position_y + line.offset_y <= higher_culling_line_for_group)
							&&
							(region_gabarite->world_position_y + line.offset_y + line.line_size_y >= lower_culling_line_for_group)
							)
					{
						NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLACK, 0.32f);
						ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);

						NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
						(
							NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
							NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

							region_gabarite->world_position_x,
							region_gabarite->world_position_y + line.offset_y,

							region_gabarite->size_x,
							line.line_size_y,

							NS_DefaultGabarites::texture_gabarite_white_pixel

						);
					}





			//DEBUG HIGHLIGHT - FOCUSED BUTTON GROUP
			if
				(
					(DebugNamespace::is_debug_element_active(DebugStructID::GROUP_GABARITES))
					&&
					(EButtonGroup::focused_button_group == this)
					)
			{

				if (button_group_is_active)
				{
					NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.13f);
				}
				else
				{
					NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_RED, 0.13f);;
				}

				if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + 0.0f,
					region_gabarite->size_x - 0.0f,
					region_gabarite->size_y - 0.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);


			}

			//DEBUG HIGHLIGHT - FOCUSED UNPRESSED MOUSE BUTTON GROUP
			if
				(
					(DebugNamespace::is_debug_element_active(DebugStructID::GROUP_GABARITES))
					&&
					(EButtonGroup::focused_button_group_mouse_unpressed == this)
					)
			{

				if (button_group_is_active)
				{
					NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLUE, 0.13f);
				}
				else
				{
					NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_RED, 0.13f);;
				}

				if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + 0.0f,
					region_gabarite->size_x - 0.0f,
					region_gabarite->size_y - 0.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			//DEBUG HIGHLIGHT - FOCUSED SLIDER GROUP
			if
				(
					(DebugNamespace::is_debug_element_active(DebugStructID::GROUP_GABARITES))
					&&
					(EButtonGroup::focused_button_group_with_slider == this)
					)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLUE, 0.16f);
				if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + 0.0f,
					region_gabarite->size_x - 0.0f,
					region_gabarite->size_y - 0.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);


			}

			//draw call to append GL_scissor
			NS_EGraphicCore::pbr_batcher->draw_call();//draw pbg bg
			batcher_for_default_draw->draw_call();//draw text to default batcher

			//NS_EGraphicCore::test_batcher->draw_call();

			//gl_scissor for buttons
			glScissor
			(
				region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
				(lower_culling_line_for_elements)*NS_EGraphicCore::current_zoom,

				region_gabarite->size_x * NS_EGraphicCore::current_zoom,
				max(0.0f, higher_culling_line_for_elements - lower_culling_line_for_elements) * NS_EGraphicCore::current_zoom
			);





			//DRAW BUTTONS
			{
				for (EntityButton* but : all_button_list)
					if
						(
							(but->be_visible_last_time)
							&&
							(but->entity_is_active())
							)
					{
						//PHANTOM REDRAW
						if (but->have_phantom_draw)
						{
							but->have_phantom_draw = false;
							//generate vertex buffer for buttons



							but->set_world_positions(but->world_position_x, but->world_position_y, but->world_position_z);

							for (generate_vertex_buffer gvb : but->action_on_generate_vertex_buffer)
							{
								gvb(but, selected_style);
							}
							but->generate_vertex_buffer_for_all_sprite_layers();

							if (DebugNamespace::is_debug_element_active(DebugStructID::PHANTOM_HIGHLIGHT_FOR_BUTTONS))
							{
								but->set_highlight(1.0f, 1.0f);
							}
						}

						but->draw();

						//select rama
						if (selected_button == but)
						{
							NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_YELLOW, 1.0f);
							ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);

							NS_ERenderCollection::add_data_to_vertex_buffer_rama
							(
								NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
								NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

								but->button_gabarite->world_position_x - 1.0f,
								but->button_gabarite->world_position_y - 1.0f,

								but->button_gabarite->size_x + 2.0f,
								but->button_gabarite->size_y + 2.0f,

								3.0f,

								NS_DefaultGabarites::texture_gabarite_white_pixel

							);

							NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_YELLOW, 0.2f);
							ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);

							NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
							(
								NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
								NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

								but->button_gabarite->world_position_x + 1.0f,
								but->button_gabarite->world_position_y + 1.0f,

								but->button_gabarite->size_x - 2.0f,
								but->button_gabarite->size_y - 2.0f,

								NS_DefaultGabarites::texture_gabarite_white_pixel

							);
						}
					}
			}

			if (have_rama)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_DARK_GREY, 1.0f);
				ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);

				NS_ERenderCollection::add_data_to_vertex_buffer_rama
				(
					NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
					NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

					region_gabarite->world_position_x,
					region_gabarite->world_position_y,

					region_gabarite->size_x,
					region_gabarite->size_y,

					1.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel

				);
			}

			//BUTTONS SECOND PASS DRAW
			{
				for (EntityButton* but : all_button_list)
					if
						(
							(but->be_visible_last_time)
							&&
							(but->entity_is_active())
							)
					{
						but->draw_second_pass();
					}
			}


			for (EClickableArea* group_clickable_area : clickable_area_list)
				if ((group_clickable_area != nullptr) && (group_clickable_area->clickable_region_is_active))
				{
					group_clickable_area->draw();
				}

			NS_EGraphicCore::pbr_batcher->draw_call();//draw pbg bg
			batcher_for_default_draw->draw_call();//draw text to default batcher



			//recursive draw


			for (EButtonGroup* group : group_list) { group->draw_button_group(); }




			//draw call to prepare for header
			//NS_EGraphicCore::test_batcher->draw_call();
			NS_EGraphicCore::pbr_batcher->draw_call();




			glDisable(GL_SCISSOR_TEST);

			if (DebugNamespace::is_debug_element_active(DebugStructID::GROUP_GABARITES))
			{
				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_GREEN);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_rama
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + 0.0f,
					region_gabarite->size_x - 0.0f,
					region_gabarite->size_y - 0.0f,
					1.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);

				ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_RED, 0.2f);;
				NS_ERenderCollection::add_data_to_vertex_buffer_rama
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					region_gabarite->world_position_x + group_offset_for_content_left,
					region_gabarite->world_position_y + group_offset_for_content_bottom,

					region_gabarite->size_x - group_offset_for_content_left - group_offset_for_content_right,
					region_gabarite->size_y - group_offset_for_content_bottom - group_offset_for_content_up,

					1.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}




			if
				(
					(EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
					&&
					(false)
					)
			{
				for (EButtonGroup* group : group_list)
				{

					if
						(
							(EButtonGroup::focused_button_group == group)
							||
							(EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL))
							)
					{


						NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_RED);
						//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
						ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
						NS_ERenderCollection::add_data_to_vertex_buffer_rama
						(
							batcher_for_default_draw->vertex_buffer,
							batcher_for_default_draw->last_vertice_buffer_index,
							group->region_gabarite->world_position_x + 0.0f,
							group->region_gabarite->world_position_y + 0.0f,
							group->region_gabarite->size_x - 0.0f,
							group->region_gabarite->size_y - 0.0f,
							1.0f,
							NS_DefaultGabarites::texture_gabarite_white_pixel
						);

						//EInputCore::logger_param("size y", group->region_gabarite->size_y);
						//batcher_for_default_draw->draw_call();
					}
				}
			}

			//slider debug highlight
			if
				(
					(DebugNamespace::is_debug_element_active(DebugStructID::GROUP_GABARITES))
					&&
					(EButtonGroup::focused_button_group_with_slider == this)
					)
			{
				if (!slider->entity_is_active())
				{
					NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_RED, 0.9f);
				}
				else
				{
					NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLUE, 0.9f);
				}

				if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					slider->button_gabarite->world_position_x + 0.0f,
					slider->button_gabarite->world_position_y + 0.0f,
					max(slider->button_gabarite->size_x - 0.0f, 10.0f),
					max(slider->button_gabarite->size_y - 0.0f, 10.0f),
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);

				//EInputCore::logger_param("world x slider", slider->button_gabarite->world_position_x);
				//EInputCore::logger_param("world y slider", slider->button_gabarite->world_position_y);

				//EInputCore::logger_param("size x slider", slider->button_gabarite->size_x);
				//EInputCore::logger_param("size y slider", slider->button_gabarite->size_y);

			}

			if (is_selected)
			{

				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.20f);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + 0.0f,
					region_gabarite->size_x - 0.0f,
					region_gabarite->size_y - 0.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			if
				(
					(!group_is_suppressed)
					&&
					(
						(parent_group != nullptr)
						&&
						(parent_group == EButtonGroup::parent_vector_moving_group)
						)
					&&
					(EButtonGroup::catched_by_mouse(this))
					&&
					(!is_blocked_by_superfocus())
					)
			{
				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_GREEN);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + region_gabarite->size_y - 8.0f,
					region_gabarite->size_x - 0.0f,
					8.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			if
				(
					(EButtonGroup::vector_moving_group == this)
					&&
					(EButtonGroup::selected_groups.empty())
					)
			{

				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.33f);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + 0.0f,
					region_gabarite->size_x - 0.0f,
					region_gabarite->size_y - 0.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			for (int i = 0; i < highlight_list.size(); i++)
			{
				HighlightStruct*
					pointer_to_highlight = &highlight_list[i];

				if (pointer_to_highlight->time_remaining > 0.0f)
				{
					//set highlight color, less time exist = less opacity
					NS_EGraphicCore::set_active_color_custom_alpha
					(
						pointer_to_highlight->highlight_color,
						pointer_to_highlight->highlight_color[3] * min(pointer_to_highlight->time_remaining / pointer_to_highlight->max_time, 1.0f)
					);

					//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
					ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
					NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
					(
						batcher_for_default_draw->vertex_buffer,
						batcher_for_default_draw->last_vertice_buffer_index,
						region_gabarite->world_position_x + 0.0f,
						region_gabarite->world_position_y + 0.0f,
						region_gabarite->size_x - 0.0f,
						region_gabarite->size_y - 0.0f,
						NS_DefaultGabarites::texture_gabarite_white_pixel
					);

				}

				//pointer_to_highlight->time_remaining -= _d;


			}

			if (group_is_suppressed)
			{

				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREY, 0.25);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + 0.0f,
					region_gabarite->size_x - 0.0f,
					region_gabarite->size_y - 0.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);


			}

			for (EButtonGroup* group : group_list) { group->post_draw(); }


			//NS_EGraphicCore::pbr_batcher->draw_call();
			batcher_for_default_draw->draw_call();
			//NS_EGraphicCore::test_batcher->draw_call();

			if ((!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT)) && (true)) { glEnable(GL_SCISSOR_TEST); }
			glScissor
			(
				region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
				region_gabarite->world_position_y * NS_EGraphicCore::current_zoom,
				region_gabarite->size_x * NS_EGraphicCore::current_zoom,
				region_gabarite->size_y * NS_EGraphicCore::current_zoom
			);
			for (group_draw_action gda : actions_on_draw)
			{
				gda(this);
			}

			NS_EGraphicCore::pbr_batcher->draw_call();
			batcher_for_default_draw->draw_call();
			//NS_EGraphicCore::test_batcher->draw_call();
			glDisable(GL_SCISSOR_TEST);







			NS_EGraphicCore::pbr_batcher->draw_call();
			batcher_for_default_draw->draw_call();
			//draw_second_pass();
		}
		//else
		//{

			//NS_EGraphicCore::set_active_color(1.0f * is_active, 1.0f * disable_gabarite, 1.0f * hidden_by_search, 0.53f);;

			//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			//NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			//(
			//	batcher_for_default_draw->vertex_buffer,
			//	batcher_for_default_draw->last_vertice_buffer_index,
			//	region_gabarite->world_position_x + 0.0f,
			//	region_gabarite->world_position_y + 0.0f,
			//	region_gabarite->size_x - 0.0f,
			//	region_gabarite->size_y - 0.0f,
			//	NS_DefaultGabarites::texture_gabarite_white_pixel
			//);

			//batcher_for_default_draw->draw_call();
		//}
	}
}

void EButtonGroup::draw_button_group_debug_overlay()
{

	EButtonGroup* t_group = EButtonGroup::focused_button_group;
	if
		(
			(t_group != nullptr)
			&&
			(DebugNamespace::is_debug_element_active(DebugStructID::HIGHEST_POINT_Y))
			)
	{

		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_RED);
		//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
		ERenderBatcher::if_have_space_for_data(t_group->batcher_for_default_draw, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			t_group->batcher_for_default_draw->vertex_buffer,
			t_group->batcher_for_default_draw->last_vertice_buffer_index,

			t_group->region_gabarite->world_position_x + 0.0f,
			t_group->region_gabarite->world_position_y + t_group->highest_point_y_for_groups + t_group->scroll_y,

			t_group->region_gabarite->size_x - 0.0f,
			2.0f,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);


		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_PINK);
		//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
		ERenderBatcher::if_have_space_for_data(t_group->batcher_for_default_draw, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			t_group->batcher_for_default_draw->vertex_buffer,
			t_group->batcher_for_default_draw->last_vertice_buffer_index,

			t_group->region_gabarite->world_position_x + 0.0f,
			t_group->region_gabarite->world_position_y + t_group->highest_point_y_for_buttons + t_group->scroll_y,

			t_group->region_gabarite->size_x - 0.0f,
			2.0f,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);

		t_group->batcher_for_default_draw->draw_call();


	}

	if
		(
			(DebugNamespace::is_debug_element_active(DebugStructID::CULLING_LINES))
			&&
			(t_group != nullptr)
			)
	{
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_CYAN);
			//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				t_group->batcher_for_default_draw->vertex_buffer,
				t_group->batcher_for_default_draw->last_vertice_buffer_index,

				t_group->region_gabarite->world_position_x + 0.0f,
				t_group->lower_culling_line_for_group + 0.0f,

				t_group->region_gabarite->size_x,
				1.0f,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}

		//if (false)
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_YELLOW);
			//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				t_group->batcher_for_default_draw->vertex_buffer,
				t_group->batcher_for_default_draw->last_vertice_buffer_index,

				t_group->region_gabarite->world_position_x + 0.0f,
				t_group->higher_culling_line_for_group - 0.0f,

				t_group->region_gabarite->size_x - 0.0f,
				1.0f,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}
	}
	//if (EButtonGroup::focused_button_group != nullptr)
	//{
	//	EButtonGroup::focused_button_group->highlight_this_group();
	//}

}

void EButtonGroup::post_draw()
{
}

void EButtonGroup::draw_second_pass()
{


	for (EntityButton* but : all_button_list)
		if
			(
				(but->entity_is_active())
				&&
				(but->be_visible_last_time)
				)
		{
			but->draw_second_pass();
		}

	for (EButtonGroup* group : group_list) { group->draw_second_pass(); }
}



void EButtonGroup::align_groups()
{
	region_gabarite->have_phantom_translation = false;
	region_gabarite->phantom_translate_x = 0.0f;
	region_gabarite->phantom_translate_y = 0.0f;
	region_gabarite->phantom_translate_z = 0.0f;

	highest_point_y_for_groups = 0.0f;
	//float minimal_culling_line_top		= 10000.0f;
	//float minimal_culling_line_bottom	= -10000.0f;

	if (parent_group == nullptr)
	{
		region_gabarite->world_position_x = round(region_gabarite->offset_x);
		region_gabarite->world_position_y = round(region_gabarite->offset_y);

		//lower_culling_line	= max(region_gabarite->world_position_y,							0.0f);
		//higher_culling_line = min(region_gabarite->world_position_y + region_gabarite->size_y,	NS_EGraphicCore::SCREEN_HEIGHT);
	}
	else
	{
		//region_gabarite->offset_x = 0.0f;
		//region_gabarite->offset_y = 0.0f;
		//lower_culling_line	= max(region_gabarite->world_position_y,							parent_group->lower_culling_line);
		//higher_culling_line = min(region_gabarite->world_position_y + region_gabarite->size_y,	parent_group->higher_culling_line);
	}






	EButtonGroup* prev_group = nullptr;

	//prev_group = nullptr;

	//stretch row
	for (EButtonGroup* child : group_list)
		if
			(
				(child->is_this_group_active())
				&&
				(!child->block_need_remove)
				)
		{

			//OFFSET TO BASE
			if (prev_group == nullptr)
			{
				child->region_gabarite->offset_x = group_offset_for_content_left;



				switch (child_align_direction)
				{
				case (ChildElementsAlignDirection::BOTTOM_TO_TOP):
				{
					child->region_gabarite->offset_y = group_offset_for_content_bottom;
					break;
				};

				case (ChildElementsAlignDirection::TOP_TO_BOTTOM):
				{
					child->region_gabarite->offset_y = region_gabarite->size_y - child->region_gabarite->size_y - group_offset_for_content_up - additional_fake_start_offset;

					break;
				}
				}

			}
			else//OFFSET BY PREV GROUP
			{

				////if (prev_group->clickable_area_list.empty())
				//{
				//	prev_group->clickable_area_list.clear();

				//	EClickableArea*
				//	clickable_area_for_group = EClickableArea::create_default_clickable_region(prev_group->region_gabarite, prev_group);
				//	prev_group->clickable_area_list.push_back(clickable_area_for_group);

				//	ELocalisationText
				//	ltext = ELocalisationText::generate_localisation("size_y: " + std::to_string(prev_group->region_gabarite->size_y));

				//	ETextArea*
				//	text_area_for_group = ETextArea::create_centered_to_up_text_area(clickable_area_for_group, EFont::font_list[0], ltext.localisations[ELocalisationText::active_localisation]);
				//	text_area_for_group->localisation_text = ltext;
				//	text_area_for_group->can_be_edited = false;
				//	text_area_for_group->offset_by_gabarite_size_y	= 1.0f;
				//	text_area_for_group->offset_by_text_size_y		= -1.0f;
				//	clickable_area_for_group->text_area = text_area_for_group;

				//	prev_group->highlight_this_group();
				//}

				if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
				{
					child->region_gabarite->offset_x = group_offset_for_content_left;

					if (child_align_direction == ChildElementsAlignDirection::BOTTOM_TO_TOP)
					{
						child->region_gabarite->offset_y = prev_group->region_gabarite->offset_y + prev_group->region_gabarite->size_y + child->additional_y_distance;


					}
					else
						if (child_align_direction == ChildElementsAlignDirection::TOP_TO_BOTTOM)
						{
							child->region_gabarite->offset_y = prev_group->region_gabarite->offset_y - child->region_gabarite->size_y - child->additional_y_distance;
						}
				}
				else
					if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
					{
						child->region_gabarite->offset_x = prev_group->region_gabarite->offset_x + prev_group->region_gabarite->size_x + 0.0f;
						child->region_gabarite->offset_y = prev_group->region_gabarite->offset_y;
					}
			}





			child->region_gabarite->world_position_x = round(region_gabarite->world_position_x + child->region_gabarite->offset_x);
			child->region_gabarite->world_position_y = round(region_gabarite->world_position_y + child->region_gabarite->offset_y + scroll_y);
			child->region_gabarite->world_position_z = round(region_gabarite->world_position_z + child->region_gabarite->offset_z);

			highest_point_y_for_groups = max(child->region_gabarite->offset_y + child->region_gabarite->size_y, highest_point_y_for_groups);

			prev_group = child;


		}
		else
		{
			child->region_gabarite->offset_x = 0.0f;
			child->region_gabarite->offset_y = 0.0f;

			child->region_gabarite->world_position_x = 0.0f;
			child->region_gabarite->world_position_y = 0.0f;
		}




	if (prev_group != nullptr)
	{
		if (child_align_direction == ChildElementsAlignDirection::BOTTOM_TO_TOP)
		{
			highest_point_y_for_groups
				=
				max
				(
					prev_group->region_gabarite->offset_y
					+
					prev_group->region_gabarite->size_y
					-
					0.0f
					,
					highest_point_y_for_groups
				);
		}
		else
			if (child_align_direction == ChildElementsAlignDirection::TOP_TO_BOTTOM)
			{
				highest_point_y_for_groups
					=
					max
					(
						region_gabarite->size_y
						-
						prev_group->region_gabarite->offset_y
						,
						highest_point_y_for_groups
					);
			}

		//highest_point_y_for_groups += 40.0f;

	}


	if (slider != nullptr)
	{
		slider->button_gabarite->size_y = region_gabarite->size_y;
	}

	//for (EButtonGroup* group : group_list) { group->align_groups(); }

	//highest_point_y_for_groups *= 1.0f;

	highest_point_y_for_groups += additional_fake_y_point;

}

void EButtonGroup::generate_vertex_buffer_for_group(EButtonGroup* _group, bool _recursive)
{

	if
		(
			(_group->is_this_group_active())
			&&
			(_group->is_in_visible_diapason())
			&&
			(!_group->block_need_remove)
			//&&
			//(_group->region_gabarite->world_position_y <= NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)
			//&&
			//(_group->region_gabarite->world_position_y + _group->region_gabarite->size_y >= 0.0f)
			)
	{
		_group->is_viped = false;
		_group->vipe_timer = 1.0f;
		_group->group_phantom_redraw = false;

		//	

		//_group->highlight_time += 0.2f;

		EButtonGroup::generate_brick_textured_bg(_group);
		_group->need_redraw = false;


		for (EClickableArea* clickable_area : _group->clickable_area_list)
		{
			if (clickable_area->text_area != nullptr)
			{
				clickable_area->text_area->change_text(clickable_area->text_area->original_text);
			}

			for (ESpriteLayer* s_layer : clickable_area->sprite_layer_list)
				if (s_layer != nullptr)
				{
					s_layer->generate_vertex_buffer_for_sprite_layer("Clickable region sprite layer");
				}
		}

		//button visible, go generate vertex!
		for (EntityButton* but : _group->all_button_list)
			if
				(
					(but->be_visible_last_time)
					&&
					(but->entity_is_active())
					)
			{


				but->set_world_positions(but->world_position_x, but->world_position_y, but->world_position_z);
				for (generate_vertex_buffer csa : but->action_on_generate_vertex_buffer)
				{
					csa(but, _group->selected_style);
				}
				but->generate_vertex_buffer_for_all_sprite_layers();



				but->have_phantom_draw = false;
			}
			else
			{
				but->have_phantom_draw = true;
			}

		if (_recursive)
		{
			for (EButtonGroup* group : _group->group_list) { EButtonGroup::generate_vertex_buffer_for_group(group, true); }
		}
	}
	else
	{
		_group->group_phantom_redraw = true;
	}
}


void EButtonGroup::recursive_group_stretch_childs_x()
{
	float			constant_element_sizes_x = 0.0f;
	float			summ_size = 0.0f;
	float			target_size = 0.0f;
	float			final_size = 0.0f;

	float			slider_effect = 0.0f;



	unsigned int	dynamic_elements_count = 0;

	if ((slider != nullptr) && (slider->entity_is_active()))
	{
		slider_effect = slider->brick_style_active_slider->main_texture->size_x_in_pixels;
	}

	float shrink_size = 0.0f;
	//if (!*have_bg) { shrink_size = 0.0f; }

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{


		target_size = region_gabarite->size_x - group_offset_for_content_left - group_offset_for_content_right - (group_list.size() - 1) * 0.0f - shrink_size;
		target_size -= slider_effect;

		for (EButtonGroup* group : group_list)
			if
				(
					(group->is_this_group_active())
					&&
					(!group->block_need_remove)
					)
			{
				if (group->stretch_x_by_parent_size)
				{
					dynamic_elements_count++;
				}
				else
				{
					target_size -= group->region_gabarite->size_x;
					constant_element_sizes_x += group->region_gabarite->size_x;
				}
			}
	}

	if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{
		target_size = region_gabarite->size_x - group_offset_for_content_left - group_offset_for_content_right - shrink_size;
		target_size -= slider_effect;

		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0) { final_size = target_size / float(dynamic_elements_count); }



	//final_size = 100.0f;
	for (EButtonGroup* group : group_list)
		if
			(
				(group->is_this_group_active())
				&&
				(!group->block_need_remove)
				)
		{
			if ((group->stretch_x_by_parent_size) && (group->region_gabarite->size_x != final_size))
			{
				group->region_gabarite->size_x = round(final_size);
				group->need_redraw = true;
			}
		}
		else
		{
			//group->region_gabarite->size_x = 0.0f;
			//group->region_gabarite->size_y = 0.0f;
		}

	//for (EButtonGroup* group : group_list) { group->group_stretch_x(); }


}

void EButtonGroup::recursive_group_stretch_childs_y()
{
	float			constant_element_sizes_y = 0.0f;
	float			summ_size = 0.0f;
	float			target_size = 0.0f;
	float			final_size = 0.0f;



	unsigned int	dynamic_elements_count = 0;

	float shrink_size = 0.0f;
	if (!group_have_background) { shrink_size = 0.0f; }

	//for (EButtonGroup* child : group_list)
	//if (child->is_this_group_active())
	//{
	//	if (child->can_be_stretched_by_child)
	//	{
	//		child->region_gabarite->size_y	= get_child_total_y_size();
	//		child->base_height				= child->region_gabarite->size_y;
	//	}
	//}

	if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{

		target_size = max(region_gabarite->size_y, min_size_y) - group_offset_for_content_bottom - group_offset_for_content_up - (group_list.size() - 1) * BUTTON_GROUP_Y_DISTANCE - shrink_size - 0.0;

		for (EButtonGroup* child : group_list)
			if
				(
					(child->is_this_group_active())
					&&
					(!child->block_need_remove)
					)
			{
				/*if (child->can_be_resized_to_highest_point_y)
				{
					child->resize_group_to_highest_point_y();
				}*/

				child->region_gabarite->size_y = max(child->region_gabarite->size_y, child->min_size_y);

				if (child->dynamic_size_y)
				{
					dynamic_elements_count++;
				}
				else
				{
					target_size -= child->region_gabarite->size_y;
					constant_element_sizes_y += child->region_gabarite->size_y;
				}
			}
	}

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{

		target_size = region_gabarite->size_y - group_offset_for_content_bottom - group_offset_for_content_up - shrink_size + 0.0f;
		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0)
	{
		final_size = round(target_size / float(dynamic_elements_count));
	}
	//if (dynamic_elements_count == 1) { final_size = round(target_size + 1.0f); }



	//final_size = 100.0f;
	for (EButtonGroup* child : group_list)
	{

		if
			(
				(child->is_this_group_active())
				&&
				(!child->block_need_remove)
				)
		{

			if ((child->dynamic_size_y))
			{
				child->region_gabarite->size_y = round(max(final_size, child->min_size_y));
				//group->region_gabarite->size_y = round(max(final_size, 0.0f));
				//group->region_gabarite->size_y = round(final_size);
			}

			//group->region_gabarite->size_y = round(max(group->region_gabarite->size_y, min_size_y));

			child->need_redraw = true;
		}
	}

	//for (EButtonGroup* group : group_list) { group->group_stretch_y(); }
}

bool EButtonGroup::check_slider()
{

	//if (slider != nullptr)
	//{
	//	slider->entity_disabled = true;
	//}

	float child_elements_height_summ = 0.0f;
	float max_y = 0.0f;
	{
		//if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
		//{
		//	child_elements_height_summ = ((float)group_list.size() - 1) * BUTTON_GROUP_Y_DISTANCE;

		//	for (EButtonGroup* group : group_list)
		//	{child_elements_height_summ += group->region_gabarite->size_y;}
		//}

		//if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
		//{

		//	for (EButtonGroup* group : group_list)
		//	{max_y = max(max_y, group->region_gabarite->size_y);}

		//	child_elements_height_summ += max_y;
		//}



		if
			(
				(
					(highest_point_y_for_groups > region_gabarite->size_y - group_offset_for_content_up)
					//||
					//(highest_point_y_for_buttons > region_gabarite->size_y - group_offset_for_content_up)
					//(can_be_stretched_by_child)
					)
				//||
				//(true)
				)
		{
			if (slider != nullptr)
			{
				//slider become enabled
				if (slider->entity_disabled)
				{
					slider->entity_disabled = false;
					have_slider = true;

					for (EButtonGroup* group : group_list)
					{
						group->parent_have_slider = true;
					}//parent have no slider

					scroll_y = slider->current_value;

					return true;
				}
				else
				{
					//no changes
					return false;
				}
			}
		}
		else
		{

			if (slider != nullptr)
			{
				//slider become disabled
				if (!slider->entity_disabled)
				{
					slider->entity_disabled = true;
					have_slider = false;

					for (EButtonGroup* group : group_list)
					{
						group->parent_have_slider = false;
					}

					return true;
				}
				else
				{
					//no changes
					return false;
				}
			}
		}
	}
}

void EButtonGroup::check_slider_and_call_recursive_pass_if_need()
{
}

void EButtonGroup::recursive_expand_to_workspace_size()
{
	//if (EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	//{
	//	group_offset_for_content_bottom = 10.0f;
	//	group_offset_for_content_up = 10.0f;
	//	group_offset_for_content_left = 10.0f;
	//	group_offset_for_content_right = 10.0f;
	//}

	if (can_resize_to_workspace_size_x)
	{
		region_gabarite->size_x = base_width + group_offset_for_content_left + group_offset_for_content_right;

	}

	if (can_resize_to_workspace_size_y)
	{
		if (fake_borders_id < 0)
		{
			region_gabarite->size_y
				=
				base_height
				+
				group_offset_for_content_bottom
				+
				group_offset_for_content_up;
		}
		else
		{
			region_gabarite->size_y
				=
				base_height
				+
				selected_style->brick_style[fake_borders_id].offset_for_elements_bottom
				+
				selected_style->brick_style[fake_borders_id].offset_for_elements_up;
		}

		//std::cout << std::endl << std::endl;

		//EInputCore::logger_param("base", base_height);
		//EInputCore::logger_param("bottom", selected_style->brick_style[brick_style_id].offset_for_elements_bottom);
		//EInputCore::logger_param("up", selected_style->brick_style[brick_style_id].offset_for_elements_up);
	}

	for (EButtonGroup* group : group_list)
	{
		group->recursive_expand_to_workspace_size();
	}
}

void EButtonGroup::recursive_set_recalculate_culling_lines()
{
	//need_recalcualte_culling_lines = true;

	for (EButtonGroup* b_group : group_list)
	{
		//b_group->need_recalcualte_culling_lines = true;
	}
}

void EButtonGroup::button_group_prechange()
{

}



void EButtonGroup::change_group(EButtonGroup* _group)
{
	_group->recursive_reset_phantom_translate();

	//_group->highlight_this_group_green_info();

	if
		(
			(_group->is_this_group_active())
			&&
			((_group->is_in_visible_diapason()) || (true))
			&&
			(!_group->block_need_remove)
			)
	{
		recursive_change_group_first_pass(_group);
		//recursive_change_group_first_pass(_group);

		change_group_second_pass(_group);

	}
	else
	{
		_group->need_change = true;
	}

	_group->button_group_postchange();


}

void EButtonGroup::recursive_change_group_first_pass(EButtonGroup* _group)
{
	int style_id = _group->brick_style_id;
	if (_group->fake_borders_id >= 0) { style_id = _group->fake_borders_id; }


	//set boredr offset
	if ((style_id >= 0) && (_group->group_have_background))
	{
		_group->group_border_texture_left = _group->selected_style->brick_style[style_id].border_texture_size_left;
		_group->group_border_texture_right = _group->selected_style->brick_style[style_id].border_texture_size_right;

		_group->group_border_texture_bottom = _group->selected_style->brick_style[style_id].border_texture_size_bottom;
		_group->group_border_texture_up = _group->selected_style->brick_style[style_id].border_texture_size_up;
	}
	else
	{
		_group->group_border_texture_left = 0.0f;
		_group->group_border_texture_right = 0.0f;

		_group->group_border_texture_bottom = 0.0f;
		_group->group_border_texture_up = 0.0f;
	}

	if
		(
			(_group->is_this_group_active())
			&&
			(!_group->block_need_remove)
			)
	{
		_group->need_change = false;
		_group->need_refresh = false;

		_group->button_group_prechange();

		//base highest point y
		_group->highest_point_y_for_groups = _group->group_offset_for_content_bottom;
		_group->highest_point_y_for_buttons = _group->group_offset_for_content_bottom;
		//stretch child to parent size

		_group->recursive_group_stretch_childs_y();
		_group->highest_point_y_for_groups = _group->get_highest_point_y_for_groups();

		_group->check_slider();

		_group->recursive_group_stretch_childs_x();

		for (EButtonGroup* child : _group->group_list)
		{
			if (child->can_be_resized_to_highest_point_y)
			{
				child->resize_group_to_highest_point_y();
			}
		}

		_group->highest_point_y_for_groups = _group->get_highest_point_y_for_groups();

		//previvous calculation out of date, recalculate
		bool slider_appear = _group->check_slider();
		//if (slider_appear)
		//{
		//	_group->recursive_group_stretch_childs_y();
		//	_group->highest_point_y_for_groups = _group->get_highest_point_y_for_groups();

		//	_group->recursive_group_stretch_childs_x();

		//	for (EButtonGroup* child : _group->group_list)
		//	{
		//		if (child->can_be_resized_to_highest_point_y)
		//		{
		//			child->resize_group_to_highest_point_y();
		//		}
		//	}
		//}


		for (EButtonGroup* child : _group->group_list)
		{
			recursive_change_group_first_pass(child);
		}

		_group->highest_point_y_for_groups = _group->get_highest_point_y_for_groups();
		if (_group->can_be_stretched_by_child)
		{
			_group->region_gabarite->size_y = _group->highest_point_y_for_groups + _group->group_offset_for_content_bottom + _group->group_offset_for_content_up;
		}

		//_group->highest_point_y_for_groups = _group->get_highest_point_y_for_groups();
		if (true)
		{
			for (EButtonGroup* child : _group->group_list)
			{
				soft_recursion_first_pass(child);
			}
		}



	}
	else
	{
		_group->need_change = true;
	}
}

void EButtonGroup::change_group_second_pass(EButtonGroup* _group)
{
	if
		(
			(_group->is_this_group_active())
			&&
			(!_group->block_need_remove)
			)
	{


		//_group->highest_point_y_for_groups = _group->get_highest_point_y_for_groups();

		//_group->check_slider();

		//align group in parent gabarite
		_group->align_groups();

		//calculate culling lines for GL_SCISSOR
		_group->recalculate_culling_lines();


		//buttons process
		_group->reset_buttons_phantom_translate();
		_group->set_base_size_x();
		_group->put_buttons_to_lines();

		_group->activate_slider_if_need();

		_group->stretch_all_buttons();
		_group->calculate_group_lines();
		_group->set_buttons_offset();
		_group->align_buttons_in_lines();


		_group->final_highest_point_y = max(_group->highest_point_y_for_buttons, _group->highest_point_y_for_groups);

		_group->calculate_world_coordinates_for_buttons();

		EButtonGroup::generate_vertex_buffer_for_group(_group, NSW_ONLY_TARGET);

		for (EButtonGroup* child : _group->group_list)
		{
			change_group_second_pass(child);
		}
	}
}

void EButtonGroup::soft_recursion_first_pass(EButtonGroup* _group)
{
	_group->recursive_group_stretch_childs_y();

	_group->highest_point_y_for_groups = _group->get_highest_point_y_for_groups();
	_group->check_slider();

	_group->recursive_group_stretch_childs_x();





	for (EButtonGroup* child : _group->group_list)
	{
		soft_recursion_first_pass(child);
	}

}

void EButtonGroup::button_group_postchange()
{

	for (EButtonGroup* child : group_list)
	{
		child->button_group_postchange();
	}
}



void EButtonGroup::refresh_button_group(EButtonGroup* _group)
{
	if
		(
			(_group->is_this_group_active())
			&&
			(!_group->block_need_remove)
			)
	{
		_group->recursive_expand_to_workspace_size();
		change_group(_group);

		//_group->button_group_postchange();
	}
	else
	{
		_group->need_refresh = true;
	}
}

void EButtonGroup::refresh_button_group_forceful(EButtonGroup* _group)
{
}


void EButtonGroup::recalculate_culling_lines()
{
	if (parent_group == nullptr)
	{
		lower_culling_line_for_group = region_gabarite->world_position_y + region_gabarite->phantom_translate_y;
		higher_culling_line_for_group = region_gabarite->world_position_y + region_gabarite->size_y + region_gabarite->phantom_translate_y;

		lower_culling_line_for_elements = region_gabarite->world_position_y + region_gabarite->phantom_translate_y + group_border_texture_bottom;
		higher_culling_line_for_elements = region_gabarite->world_position_y + region_gabarite->size_y + region_gabarite->phantom_translate_y - group_border_texture_up;
	}
	else
	{
		lower_culling_line_for_group = max(region_gabarite->world_position_y + region_gabarite->phantom_translate_y, parent_group->lower_culling_line_for_group);
		higher_culling_line_for_group = min(region_gabarite->world_position_y + region_gabarite->phantom_translate_y + region_gabarite->size_y, parent_group->higher_culling_line_for_group);

		lower_culling_line_for_elements
			=
			max
			(
				region_gabarite->world_position_y + region_gabarite->phantom_translate_y + group_border_texture_bottom,
				parent_group->lower_culling_line_for_group
			);

		higher_culling_line_for_elements
			=
			min
			(
				region_gabarite->world_position_y + region_gabarite->phantom_translate_y + region_gabarite->size_y - group_border_texture_up,
				parent_group->higher_culling_line_for_group
			);
	}
}

void EButtonGroup::recursive_recalculate_culling_lines()
{
	recalculate_culling_lines();

	if
		(
			(region_gabarite->world_position_y + region_gabarite->phantom_translate_y + region_gabarite->size_y >= 0.0f)
			&&
			(region_gabarite->world_position_y + region_gabarite->phantom_translate_y <= NS_EGraphicCore::SCREEN_HEIGHT)
			)
	{
		for (EButtonGroup* child : group_list)
			if
				(
					(child->region_gabarite->world_position_y + child->region_gabarite->phantom_translate_y + child->region_gabarite->size_y >= 0.0f)
					&&
					(child->region_gabarite->world_position_y + child->region_gabarite->phantom_translate_y <= NS_EGraphicCore::SCREEN_HEIGHT)
					)
			{

				child->recursive_recalculate_culling_lines();
			}
	}
}
void EButtonGroup::recursive_reset_phantom_translate()
{
	region_gabarite->have_phantom_translation = false;

	region_gabarite->phantom_translate_x = 0.0f;
	region_gabarite->phantom_translate_y = 0.0f;
	region_gabarite->phantom_translate_z = 0.0f;

	for (EButtonGroup* child : group_list)
	{
		child->recursive_reset_phantom_translate();
	}
}
void EButtonGroup::calculate_group_lines()
{
	float	max_y = 0.0f;
	float	offset_y = group_offset_for_content_bottom;

	for (int i = 0; i < button_line_list.size(); i++)
	{
		button_line_list[i].offset_y = offset_y;
		offset_y += button_line_list[i].line_size_y;
	}

}

void EButtonGroup::activate_slider_if_need()
{
	//final_highest_point_y = max(highest_point_y_for_buttons, highest_point_y_for_groups);

	if
		(
			(slider != nullptr)
			&&
			(
				(highest_point_y_for_buttons > region_gabarite->size_y - group_offset_for_content_up)
				//||
				//(highest_point_y_for_groups > region_gabarite->size_y - group_offset_for_content_up)
				)
			)
	{

		//EInputCore::logger_param("highest_point_y_for_buttons", highest_point_y_for_buttons);
		//EInputCore::logger_param("highest_point_y_for_groups", highest_point_y_for_buttons);
		//EInputCore::logger_param("region_gabarite->size_y", region_gabarite->size_y - group_offset_for_content_up);
		//std::cout << std::endl << std::endl;

		slider->entity_disabled = false;
		have_slider = true;
		//slider->workspace_height = 250.0f;
		//have_slider = true;

		//set "parent have slider" for every child
		for (EButtonGroup* group : group_list)
		{
			group->parent_have_slider = true;
		}




		put_buttons_to_lines();
	}
	else
	{

		if ((slider != nullptr) && (highest_point_y_for_groups <= region_gabarite->size_y - group_offset_for_content_up))
		{
			slider->entity_disabled = true;
			have_slider = false;
			//slider->workspace_height = 250.0f;
			//have_slider = true;

			//set "parent have slider" for every child
			for (EButtonGroup* group : group_list)
			{
				group->parent_have_slider = false;
			}

		}

		if
			(
				(slider == nullptr)
				||
				(slider->entity_disabled)
				)
		{
			scroll_y = 0.0f;
		}
	}
}

void EButtonGroup::stretch_all_buttons()
{
	float	free_space = 0.0f;
	int		stretchable_elements_count = 0;
	float	total_button_size = 0.0f;
	int		additional_space_for_each_button = 0;
	float	slider_additional = 0.0f;
	float	max_x = 0.0f;

	if ((slider != nullptr) && (have_slider))
	{
		slider_additional = slider->brick_style_active_slider->main_texture->size_x_in_pixels;
	}

	//free_space = region_gabarite->size_x - border_left - border_right - slider_additional;

	for (int i = 0; i < button_line_list.size(); i++)
	{
		free_space = region_gabarite->size_x - group_offset_for_content_left - group_offset_for_content_right - slider_additional;
		total_button_size = 0.0f;
		stretchable_elements_count = 0;

		if ((button_size_x_override == 0.0f) || (i == 0))
		{

			for (EntityButton* but : button_line_list[i].button_list)
				if (but->entity_is_active() || but->align_even_if_hidden)
				{
					if (but->can_be_stretched)
					{
						stretchable_elements_count++;

						but->button_gabarite->size_x = but->base_size_x;
					}

					total_button_size
						+=
						but->button_gabarite->size_x
						+
						(
							(!but->disable_force_field && !ignore_buttons_force_field)
							?
							(but->force_field_left + but->force_field_right)
							:
							(0.0f)
							)
						+
						0.0f;
				}

			if (stretchable_elements_count > 0)
			{
				free_space = free_space - total_button_size;
				additional_space_for_each_button = floor(free_space / (float)stretchable_elements_count);

				for (EntityButton* but : button_line_list[i].button_list)
					if (but->entity_is_active() || but->align_even_if_hidden)
					{
						if
							(
								(but->can_be_stretched)
								//&&
								//(additional_space_for_each_button > 0.0f)
								)
						{
							but->button_gabarite->size_x += min(additional_space_for_each_button, but->base_size_x * but->max_stretch_factor);
							//but->button_gabarite->size_x =	but->button_gabarite->size_x, but->base_size_x * but->max_stretch_factor);
						}


					}
			}
		}
		else
		{
			for (EntityButton* but : button_line_list[i].button_list)
				if ((but->entity_is_active() || but->align_even_if_hidden) && (!button_line_list[i - 1].button_list.empty()))
				{
					but->button_gabarite->size_x = button_line_list[i - 1].button_list[0]->button_gabarite->size_x;
				}
		}
	}
}

void EButtonGroup::align_buttons_in_lines()
{
	float slider_effect = 0.0f;
	float push_value = 0.0f;

	if (have_slider) {
		slider_effect = slider->brick_style_active_slider->main_texture->size_x_in_pixels;
	}

	for (int i = 0; i < button_line_list.size(); i++)
	{
		float free_space = region_gabarite->size_x - group_offset_for_content_left - group_offset_for_content_right - slider_effect;

		for (EntityButton* but : button_line_list[i].button_list)
			if (but->entity_is_active() || but->align_even_if_hidden)
			{
				free_space -= but->button_gabarite->size_x + ((!but->disable_force_field && !ignore_buttons_force_field) ? (but->force_field_left + but->force_field_right) : (0.0f));
			}

		switch (button_align_type)
		{
		case (ButtonAlignType::BUTTON_ALIGN_LEFT):
		{
			push_value = 0.0f;
			break;
		};

		case (ButtonAlignType::BUTTON_ALIGN_MID):
		{
			push_value = free_space / 2.0f;
			break;
		};

		case (ButtonAlignType::BUTTON_ALIGN_RIGHT):
		{
			push_value = free_space;
			break;
		};
		}

		for (EntityButton* but : button_line_list[i].button_list)
			if (but->entity_is_active() || but->align_even_if_hidden)
			{
				but->offset_x += push_value;

				for (EntityButton* but : all_button_list)
					for (ECustomData* cd : but->custom_data_list)
						for (EClickableArea* ca : cd->clickable_area_list)
						{
							ca->region_gabarite->align_all_clild_gabarites();
						}
			}
	}


}

void EButtonGroup::calculate_world_coordinates_for_buttons()
{
	for (EntityButton* but_temp : all_button_list)
	{
		if ((but_temp->fixed_position) && (true))
		{
			but_temp->world_position_x = round(but_temp->parent_button_group->region_gabarite->world_position_x + but_temp->offset_x);
			but_temp->world_position_y = round(but_temp->parent_button_group->region_gabarite->world_position_y + but_temp->offset_y);
		}
		else
		{
			but_temp->world_position_x = round(but_temp->parent_button_group->region_gabarite->world_position_x + but_temp->offset_x + but_temp->parent_button_group->scroll_x + 0.0f);
			but_temp->world_position_y = round(but_temp->parent_button_group->region_gabarite->world_position_y + but_temp->offset_y + but_temp->parent_button_group->scroll_y);
		}
	}
}

void EButtonGroup::resize_group_to_highest_point_y()
{
	//if (!_group->resize_to_highest_point)
	{
		//highest_point_y_for_buttons = group_offset_for_content_bottom;
		reset_buttons_phantom_translate();
		set_base_size_x();
		put_buttons_to_lines();

		activate_slider_if_need();

		//highest_point_y_for_buttons = 60.0f;

		//min_size_y				= highest_point_y_for_buttons * 1.0f;
		float maximal_size_y = max(highest_point_y_for_buttons, highest_point_y_for_groups);

		region_gabarite->size_y = std::clamp(maximal_size_y * 1.0f, min_size_y, max_size_y);
		base_height = region_gabarite->size_y;
	}
}

float EButtonGroup::get_child_total_y_size()
{
	float total_y_size = group_offset_for_content_bottom + group_offset_for_content_up;

	for (EButtonGroup* child : group_list)
	{
		//child->min_size_y = 30.0f;
		if (child->can_be_resized_to_highest_point_y)
		{
			child->resize_group_to_highest_point_y();

			total_y_size += child->region_gabarite->size_y;
		}
		else
		{
			//dynamic_syze_y
			if (child->dynamic_size_y)
			{
				total_y_size += child->min_size_y;
			}
			else
			{
				total_y_size += child->region_gabarite->size_y;
			}
		}

		//total_y_size += group_offset_for_content_bottom;

		if
			(
				(
					(child_align_direction == ChildElementsAlignDirection::TOP_TO_BOTTOM)
					&&
					(child == group_list.front())
					)
				||
				(
					(child_align_direction == ChildElementsAlignDirection::BOTTOM_TO_TOP)
					&&
					(child == group_list.back())
					)
				)
		{
			total_y_size += child->additional_y_distance;
		}
	}

	return total_y_size;
}

float EButtonGroup::get_highest_point_y_for_groups()
{

	float total_size = group_offset_for_content_bottom;

	if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{

		for (EButtonGroup* child : group_list)
			if
				(
					(child->is_this_group_active())
					&&
					(!child->block_need_remove)
					)
			{
				total_size += child->region_gabarite->size_y + child->additional_y_distance;


			}
	}

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{

		for (EButtonGroup* child : group_list)
			if
				(
					(child->is_this_group_active())
					&&
					(!child->block_need_remove)
					)
			{

				total_size = max(child->region_gabarite->size_y, total_size);
			}
	}

	total_size += additional_fake_y_point;
	return total_size;
}

void EButtonGroup::slide_to_this_group(EButtonGroup* _group)
{

	scroll_y = max(-_group->region_gabarite->offset_y, 0.0f);
	slider->current_value = scroll_y;

	EButtonGroup::refresh_button_group(this);
}

void EButtonGroup::scroll_down(float _value)
{
	scroll_y -= _value;
}

void EButtonGroup::scroll_up(float _value)
{
	scroll_y += _value;
}

void EButtonGroup::set_base_size_x()
{

	for (EntityButton* but : workspace_button_list)
	{
		if (button_size_x_override > 0.0f)
		{
			but->button_gabarite->size_x = button_size_x_override;
			but->base_size_x = button_size_x_override;
		}
		else
		{
			if (but->can_be_stretched)
			{
				but->button_gabarite->size_x = but->base_size_x;
			}
		}
	}
}

void EButtonGroup::put_buttons_to_lines()
{
	highest_point_y_for_buttons = group_offset_for_content_bottom;

	button_line_list.clear();

	float	slider_effect = 0.0f;
	float	total_size = group_offset_for_content_left;
	float	button_max_y = 0.0f;
	int		lines_count = 0;
	float	this_button_size = 0.0f;

	if ((slider != nullptr) && (slider->entity_is_active()))
	{
		slider_effect = slider->brick_style_active_slider->main_texture->size_x_in_pixels;
	}

	EButtonGroupLine
		jc_line;





	for (EntityButton* but : workspace_button_list)
		if
			(
				(but->entity_is_active())
				||
				(but->align_even_if_hidden)
				)
		{


			this_button_size
				=
				but->button_gabarite->size_x
				+
				(
					(!but->disable_force_field && !ignore_buttons_force_field)
					?
					(but->force_field_left + but->force_field_right)
					:
					(0.0f)
					);
			//size all buttons on line
			total_size += this_button_size;

			//new line
			if
				(
					(
						(but->new_line_method == NewLineMethod::WHEN_OUT_OF_GABARITE)
						&&
						(total_size > region_gabarite->size_x - group_offset_for_content_right - slider_effect)

						)
					||
					(but->new_line_method == NewLineMethod::FORCIBLY)
					)
			{
				//current line
				jc_line.line_size_y = button_max_y;
				highest_point_y_for_buttons += button_max_y;
				button_line_list.push_back(jc_line);


				//new line
				lines_count++;
				jc_line.button_list.clear();


				total_size = this_button_size + group_offset_for_content_left;
				//but->highlight_time = 1.0f;

				button_max_y = 0.0f;
			}

			//but->highlight_time - 0.0f;
			button_max_y
				=
				max
				(
					button_max_y,
					but->button_gabarite->size_y
					+
					(
						(!but->disable_force_field && !ignore_buttons_force_field && !ignore_vertical_buttons_force_field)
						?
						(but->force_field_bottom + but->force_field_up)
						:
						(0.0f)
						)
				);

			jc_line.button_list.push_back(but);





		}

	if (!jc_line.button_list.empty())
	{
		jc_line.line_size_y = button_max_y;
		button_line_list.push_back(jc_line);
	}
	//if (lines_count == 0){ button_line_list.push_back(jc_line); }


	highest_point_y_for_buttons += button_max_y;
	highest_point_y_for_buttons += additional_fake_y_point;
	//if
	//(
	//	(is_in_visible_diapason())
	//	&&
	//	(is_this_group_active())
	//)
	//{
	//	EInputCore::logger_param("highest_point_y", highest_point_y_for_buttons);
	//}


}

void EButtonGroup::set_buttons_offset()
{
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	//EInputCore::logger_param("size", button_line_list.size());

	for (int i = 0; i < button_line_list.size(); i++)
	{
		//EInputCore::logger_param("buttons in line[" + std::to_string(i) + "]", button_line_list[i].button_list.size());
		offset_x = group_offset_for_content_left;
		offset_y = button_line_list[i].offset_y;

		for (EntityButton* but : button_line_list[i].button_list)
			if (but->entity_is_active() || but->align_even_if_hidden)
			{
				but->offset_x = offset_x + ((!but->disable_force_field && !ignore_buttons_force_field) ? (but->force_field_left) : (0.0f));

				but->offset_y
					=
					offset_y
					+
					(
						(!but->disable_force_field && !ignore_buttons_force_field && !ignore_vertical_buttons_force_field)
						?
						(but->force_field_bottom)
						:
						(0.0f)
						);

				offset_x += but->button_gabarite->size_x + ((!but->disable_force_field && !ignore_buttons_force_field) ? (but->force_field_left + but->force_field_right) : (0.0f));
			}
			else
			{
				//but->offset_x = -999999.0f;
				//but->offset_y = -999999.0f;
			}


	}

	if (slider != nullptr)
	{
		slider->offset_x
			=
			region_gabarite->size_x
			-
			group_border_texture_right
			-
			slider->brick_style_active_slider->main_texture->size_x_in_pixels;

		//slider->offset_x = 0.0f;


		slider->offset_y
			=
			group_border_texture_bottom;
	}
}

void EButtonGroup::reset_buttons_phantom_translate()
{
	for (EntityButton* but : all_button_list)
	{
		but->button_gabarite->have_phantom_translation = false;

		but->button_gabarite->phantom_translate_x = 0.0f;
		but->button_gabarite->phantom_translate_y = 0.0f;
		but->button_gabarite->phantom_translate_z = 0.0f;

		//but->be_visible_last_time = false;
	}
}

void EButtonGroup::reset_slider()
{
	if (slider != nullptr)
	{
		slider->entity_disabled = true;
		have_slider = false;

		for (EButtonGroup* group : group_list)
		{
			group->parent_have_slider = false;
		}
	}
}




void EButtonGroup::add_button_to_working_group(EntityButton* _button)
{
	_button->parent_button_group = this;

	all_button_list.push_back(_button);
	workspace_button_list.push_back(_button);
}

void EButtonGroup::add_button_to_working_group_and_expand_y(EntityButton* _button)
{
	_button->parent_button_group = this;

	all_button_list.push_back(_button);
	workspace_button_list.push_back(_button);

	//float
	//addition = _button->button_gabarite->size_y + _button->force_field_bottom + _button->force_field_up;
	
	region_gabarite->size_y	+= _button->button_gabarite->size_y + _button->force_field_bottom + _button->force_field_up;
	//base_height				+= addition;
}

void EButtonGroup::add_button_to_additional_group(EntityButton* _button)
{
	_button->parent_button_group = this;

	all_button_list.push_back(_button);
	//workspace_button_list.push_back(_button);
}

void EButtonGroup::add_vertical_scroll_bar(EButtonGroup* _button_group)
{
	if (true)
	{
		EntityButtonVerticalSlider*
			but = new EntityButtonVerticalSlider();
		but->cannot_be_auto_deleted = true;
		but->make_as_default_clickable_button
		(
			new ERegionGabarite
			(
				_button_group->selected_style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture->size_x_in_pixels,
				_button_group->region_gabarite->size_y - _button_group->group_offset_for_content_bottom - _button_group->group_offset_for_content_up
			),
			_button_group,
			nullptr
		);

		but->is_rotator = _button_group->selected_style->is_rotator;
		_button_group->slider = but;

		//custom_data->actions_on_update.push_back(EDataActionCollection::action_update_slider);

		//action on generate vertex buffer

		but->action_on_generate_vertex_buffer.push_back(action_generate_vertex_for_vertical_slider);

		//action on draw
		but->main_custom_data->actions_on_draw.push_back(&EDataActionCollection::action_draw_vertical_named_slider);

		//action on update
		but->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_update_vertical_slider);

		but->pointer_to_target_value = &_button_group->scroll_y;
		//_button_group->scroll_y = 99999.9f;
		but->current_value_percent = 1.0f;

		if (_button_group->selected_style != nullptr)
		{
			but->brick_style_active_slider = &_button_group->selected_style->brick_style[BrickStyleID::SLIDER_ACTIVE];
			but->slider_inactive = &_button_group->selected_style->brick_style[BrickStyleID::SLIDER_INACTIVE];
		}
		but->fixed_position = true;

		//but->sprite_layer->generate_vertex_buffer_for_sprite_layer("scroll bar sprite layer");
		_button_group->add_button_to_additional_group(but);
	}

}

void EButtonGroup::set_offset_borders(EButtonGroup* _group, float _left, float _right, float _bottom, float _up)
{
	_group->group_offset_for_content_left = _left;
	_group->group_offset_for_content_right = _right;

	_group->group_offset_for_content_bottom = _bottom;
	_group->group_offset_for_content_up = _up;
}

void EButtonGroup::apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style)
{
	apply_style_to_button_group(_group, _style, _group->brick_style_id);
}

void EButtonGroup::apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style, BrickStyleID _brick_style_id)
{
	if (_group->can_change_style)
	{
		_group->selected_style = _style;

	}

	if ((EGUIStyle::active_style != nullptr) && (_group->can_change_style))
	{
		if ((_brick_style_id != BrickStyleID::NONE) && (_group->group_have_background))
		{
			EBrickStyle::apply_brick_parameters_to_button_group(_group, &_style->brick_style[_brick_style_id]);
		}
		else
		{
			EButtonGroup::set_offset_borders(_group, 0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	if ((_group->can_change_style) && (_group->slider != nullptr))
	{
		_group->slider->brick_style_active_slider = &_style->brick_style[BrickStyleID::SLIDER_ACTIVE];
		_group->slider->slider_inactive = &_style->brick_style[BrickStyleID::SLIDER_INACTIVE];
		_group->slider->is_rotator = _style->is_rotator;
		//_group->slider->button_gabarite->size_x = _group->selected_style->slider_inactive->main_texture->size_x_in_pixels;
		//_group->slider->button_gabarite->size_y = _group->selected_style->slider_inactive->main_texture->size_y_in_pixels;
	}
}

void EButtonGroup::generate_brick_textured_bg(EButtonGroup* _group)
{
	if (_group == nullptr)
	{
		EInputCore::logger_simple_error("group is NULL!");
	}
	else if (_group->selected_style == nullptr)
	{
		EInputCore::logger_simple_error("group [" + _group->debug_name + "] style is NULL!");
	}
	else if (_group->background_sprite_layer == nullptr)
	{
		if (_group->group_have_background) { EInputCore::logger_simple_error("group [" + _group->debug_name + "] have no background sprite layer"); }
	}
	else if ((_group->region_gabarite->size_x <= 0.0f) || (_group->region_gabarite->size_y <= 0.0f))
	{
		//EInputCore::logger_simple_error
		//(
		//	"group ["
		//	+
		//	_group->debug_name
		//	+
		//	"] have wrong gabarite size: x["
		//	+
		//	std::to_string(_group->region_gabarite->size_x)
		//	+
		//	"] y:["
		//	+
		//	std::to_string(_group->region_gabarite->size_y)
		//);
	}
	else
	{
		if (_group->seed == 0) { _group->seed = rand() % 70000; }

		NS_ERenderCollection::temporary_sprites = true;

		srand(_group->seed);

		if
			(_group->brick_style_id > BrickStyleID::NONE)
		{


			NS_ERenderCollection::set_brick_borders_and_subdivisions(_group->selected_style->brick_style[_group->brick_style_id]);

			NS_ERenderCollection::generate_brick_texture
			(
				_group->region_gabarite,
				_group->background_sprite_layer,
				_group->selected_style->brick_style[_group->brick_style_id].main_texture,
				_group->selected_style->brick_style[_group->brick_style_id].normal_map_texture,
				_group->selected_style->brick_style[_group->brick_style_id].gloss_map_texture
			);
		}
	}
}

//EButtonGroupRow* EButtonGroup::add_default_row_to_group(EButtonGroup* _group, ERegionGabarite* _region)
//{
//	EButtonGroupRow* jc_row = new EButtonGroupRow(_region);
//	jc_row->parent_button_group = _group;
//
//	jc_row->root_group = _group->root_group;
//	//_group->parent_group_row = jc_row;
//
//	_group->group_row_list.push_back(jc_row);
//
//	return jc_row;
//}

//EButtonGroupRow* EButtonGroup::get_last_created_row(EButtonGroup* _group)
//{
//	if
//	(
//		(_group != nullptr)
//		&&
//		(!_group->group_row_list.empty())
//	)
//	{return _group->group_row_list[_group->group_row_list.size() - 1]; }
//	else
//	{return nullptr;}
//}

void EButtonGroup::recursive_change_style(EButtonGroup* _group, EGUIStyle* _style)
{
	EButtonGroup::apply_style_to_button_group(_group, _style);

	//recursive down to child elements
	for (EButtonGroup* group : _group->group_list)
		if (group != nullptr)
		{
			EButtonGroup::recursive_change_style(group, _style);
		}

	//if (_group->parent_group == nullptr) { EButtonGroup::refresh_button_group(_group); }
}

bool EButtonGroup::catched_by_mouse(EButtonGroup* _group)
{
	if
		(
			//(_group->higher_culling_line_for_bg * NS_EGraphicCore::current_zoom > _group->lower_culling_line_for_bg * NS_EGraphicCore::current_zoom)
				//&&
			(_group->is_this_group_active())
			&&
			(!_group->block_need_remove)
			&&
			(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom >= _group->region_gabarite->world_position_x + _group->region_gabarite->phantom_translate_x)
			&&
			(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom <= _group->region_gabarite->world_position_x + _group->region_gabarite->size_x + _group->region_gabarite->phantom_translate_x)
			&&
			(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom >= _group->region_gabarite->world_position_y + _group->region_gabarite->phantom_translate_y)
			&&
			(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom <= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y + _group->region_gabarite->phantom_translate_y)
			)
	{
		return true;
	}

	return false;
}

EButtonGroup* EButtonGroup::add_group(EButtonGroup* _new_group)
{
	_new_group->parent_group = this;
	group_list.push_back(_new_group);
	_new_group->root_group = root_group;

	return _new_group;
}

EButtonGroup* EButtonGroup::add_group_scecific_position(EButtonGroup* _new_group, int _specific_position)
{
	_new_group->parent_group = this;

	_new_group->root_group = root_group;

	if
		(
			(_specific_position >= 0)
			&&
			(_specific_position < group_list.size())
			)
	{
		group_list.emplace(group_list.begin() + _specific_position, _new_group);
	}

	//group_list.push_back(_new_group);

	return _new_group;
}

void EButtonGroup::translate_group(float _x, float _y, float _z, bool _move_positions)
{
	//need_recalcualte_culling_lines = true;

	//if (abs(_y) > 10000.0f)
	//{
	//	EInputCore::logger_simple_error("translate _y too big");
	//}	
	if (_move_positions)
	{
		region_gabarite->offset_x += (round(_x));
		region_gabarite->offset_y += (round(_y));
		region_gabarite->offset_z += (round(_z));
	}


	//higher_culling_line += round(_y);
	//lower_culling_line += round(_y);



	if
		(
			(
				(is_this_group_active())
				&&
				(is_in_visible_diapason())
				&&
				(!block_need_remove)

				)
			)
	{




		region_gabarite->world_position_x += (round(_x));
		region_gabarite->world_position_y += (round(_y));
		region_gabarite->world_position_z += (round(_z));

		recalculate_culling_lines();

		translate_group_content(round(_x), round(_y), round(_z), true);
	}
	else
	{
		//if (region_gabarite->pointers_to_this_object <= 1))
		{
			region_gabarite->have_phantom_translation = true;

			region_gabarite->phantom_translate_x += round(_x);
			region_gabarite->phantom_translate_y += round(_y);
			region_gabarite->phantom_translate_z += round(_z);
		}

		//for (EButtonGroup* group : group_list)
		//{
		//	group->translate_group(_x, _y, _z, false);
		//}
	}

}

void EButtonGroup::translate_group_content(float _x, float _y, float _z, bool _move_slider)
{
	//need_recalcualte_culling_lines = true;
	//if (abs(_y) > 10000.0f)
	//{
	//	EInputCore::logger_simple_error("content translate _y too big");
	//}



	if ((background_sprite_layer != nullptr) && (_move_slider))
	{
		background_sprite_layer->translate_sprite_layer(_x, _y, _z, false);
	}



	for (EClickableArea* c_area : clickable_area_list)
	{
		c_area->translate_clickable_region(_x, _y, _z, false);
	}





	for (EntityButton* button : all_button_list)
		if ((_move_slider) || (button != slider))
		{
			if
				(
					(is_this_group_active())
					&&
					(!block_need_remove)
					&&
					(
						(
							(button->entity_is_active())
							&&
							(button->be_visible_last_time)
							)
						||
						(button == slider)

						)
					)
			{
				button->translate_entity(_x, _y, _z, true);
			}
			else
			{
				button->button_gabarite->have_phantom_translation = true;

				button->button_gabarite->phantom_translate_x += _x;
				button->button_gabarite->phantom_translate_y += _y;
				button->button_gabarite->phantom_translate_z += _z;
			}
		}

	for (EButtonGroup* group : group_list)
	{
		group->translate_group(_x, _y, _z, false);
	}
}

bool EButtonGroup::is_in_visible_diapason()
{
	//if (EInputCore::key_pressed(GLFW_KEY_TAB))
	//{
	//	return true;
	//}

	if
		(
			//(is_active)
			//&&

			//too right
			(region_gabarite->world_position_x + region_gabarite->phantom_translate_x > NS_EGraphicCore::SCREEN_WIDTH / NS_EGraphicCore::current_zoom)
			||
			//too left
			(region_gabarite->world_position_x + region_gabarite->phantom_translate_x + region_gabarite->size_x < 0.0f)
			||
			//too up
			(region_gabarite->world_position_y + region_gabarite->phantom_translate_y > NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)
			||
			//too bottom
			(region_gabarite->world_position_y + region_gabarite->phantom_translate_y + region_gabarite->size_y < 0.0f)
			)
	{
		return false;
	}

	if
		(
			//(is_active)
			//&&
			(parent_group != nullptr)
			&&
			(
				(region_gabarite->world_position_y + region_gabarite->phantom_translate_y + region_gabarite->size_y < parent_group->region_gabarite->world_position_y)
				||
				(region_gabarite->world_position_y + region_gabarite->phantom_translate_y > parent_group->region_gabarite->world_position_y + parent_group->region_gabarite->size_y)
			)
		)
	{
		return false;
	}

	return true;




}

void EButtonGroup::phantom_translate_if_need()
{
	if (region_gabarite->have_phantom_translation)
	{
		recalculate_culling_lines();

		region_gabarite->world_position_x += region_gabarite->phantom_translate_x;
		region_gabarite->world_position_y += region_gabarite->phantom_translate_y;
		region_gabarite->world_position_z += region_gabarite->phantom_translate_z;



		translate_group_content
		(
			region_gabarite->phantom_translate_x,
			region_gabarite->phantom_translate_y,
			region_gabarite->phantom_translate_z,
			true
		);

		region_gabarite->have_phantom_translation = false;

		region_gabarite->phantom_translate_x = 0.0f;
		region_gabarite->phantom_translate_y = 0.0f;
		region_gabarite->phantom_translate_z = 0.0f;

		recalculate_culling_lines();


	}
}

void EButtonGroup::recursive_phantom_translate_if_need()
{
	phantom_translate_if_need();

	for (EButtonGroup* group : group_list)
	{
		group->recursive_phantom_translate_if_need();
	}
}

void EButtonGroup::select_this_button(EntityButton* _but)
{
	selected_button = _but;

	//EInputCore::logger_simple_info("invoke all select action in group");
	for (group_select_action gsa : actions_on_select_button)
	{
		//EInputCore::logger_simple_info("invoke select action");
		gsa(this);
	}
}

EButtonGroup* EButtonGroup::set_parameters(ChildAlignMode _child_align_mode, bool _autosize_x, bool _autosize_y)
{
	child_align_mode = _child_align_mode;

	stretch_x_by_parent_size = _autosize_x;
	dynamic_size_y = _autosize_y;

	return this;
}

void EButtonGroup::activate_move_to_foreground_and_center()
{
	if ((parent_window != nullptr) && (unique_id != ""))
	{
		for (EButtonGroup* group : parent_window->button_group_list)
			if ((group != this) && (unique_id == group->unique_id))
			{
				group->close_this_group();
			}
	}
	move_to_foreground_and_center();

	if (!button_group_is_active)
	{
		//move_to_foreground_and_center();
		button_group_is_active = true;
	}
	else
	{
		//move_to_foreground();
	}

	if (auto_superfocused)
	{
		make_this_group_superfocused();
	}

	need_refresh = true;
}

void EButtonGroup::move_to_foreground()
{
	//button_group_is_active = true;

	if ((can_change_position_in_vector) && (parent_window != nullptr))
	{
		//EButtonGroup* target_group = nullptr;

		int target_id = -1;
		int last_id = -1;

		for (int i = 0; i < parent_window->button_group_list.size(); i++)
			if (parent_window->button_group_list[i] == this)
			{
				target_id = i;

				break;
			}

		for (int i = target_id + 1; i < parent_window->button_group_list.size(); i++)
		{
			if (parent_window->button_group_list[i]->can_change_position_in_vector)
			{
				last_id = i;
			}
			else
			{
				break;
			}
		}

		if ((target_id >= 0) && (last_id >= 0))
		{


			for (int i = target_id; i < last_id - 1; i++)
				//if ((parent_window->button_group_list[i + 1]->can_change_position_in_vector) && (parent_window->button_group_list[i]->can_change_position_in_vector))
			{
				EButtonGroup*
					swap_group = this;
				parent_window->button_group_list[i] = parent_window->button_group_list[i + 1];
				parent_window->button_group_list[i + 1] = swap_group;
			}


		}

		//parent_window->button_group_list.
	}
}

void EButtonGroup::move_to_foreground_and_center()
{
	float new_postition_x = round(NS_EGraphicCore::SCREEN_WIDTH / 2.0f / NS_EGraphicCore::current_zoom - region_gabarite->size_x / 2.0f);
	float new_postition_y = round(NS_EGraphicCore::SCREEN_HEIGHT / 2.0f / NS_EGraphicCore::current_zoom - region_gabarite->size_y / 2.0f);

	//translate_group(new_postition_x - region_gabarite->offset_x, new_postition_y - region_gabarite->offset_y, 0.0f, true);
	region_gabarite->offset_x = new_postition_x;
	region_gabarite->offset_y = new_postition_y;

	recursive_recalculate_culling_lines();
	//need_recalculate_culling_lines = true;

	move_to_foreground();
}

void EButtonGroup::highlight_this_group(float _r, float _g, float _b, float _a, HighlightID _id, float _time)
{
	float existed_highlight = -1;

	for (int i = 0; i < highlight_list.size(); i++)
	{
		//do not create new highlight, just update
		if (highlight_list[i].highlight_id == _id)
		{
			existed_highlight = i;
		}
	}

	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	//no existed highlight, create new
	if (existed_highlight == -1)
	{
		highlight_list.push_back(HighlightStruct::create_new_highlihght(_r, _g, _b, _a, _id, _time));
		highlight_list.back().highlight_timestamp = ms;
	}
	else
	{
		highlight_list[existed_highlight].set_color(_r, _g, _b, _a);

		highlight_list[existed_highlight].max_time = _time;
		highlight_list[existed_highlight].time_remaining = _time;
		highlight_list[existed_highlight].highlight_timestamp = ms;

	}
}

void EButtonGroup::highlight_this_group_green_info()
{
	highlight_this_group(0.1f, 0.9f, 0.2f, 0.8f, HighlightID::GREEN_INFO, 0.5f);
	//highlight_time = max_highlight_time;


}

void EButtonGroup::highlight_this_group_red_warning()
{
	highlight_this_group(0.8f, 0.4f, 0.2f, 0.5f, HighlightID::RED_WARNING, 0.2f);
}

void EButtonGroup::recursive_change_localisation(int _localisaton_id)
{
	for (EntityButton* b : all_button_list)
		for (ECustomData* d : b->custom_data_list)
			for (EClickableArea* c : d->clickable_area_list)
				if ((c->text_area != nullptr) && (!c->text_area->can_be_edited) && (c->text_area->can_change_localisation))
				{
					c->text_area->original_text = c->text_area->localisation_text.localisations[ELocalisationText::active_localisation];
				}

	for (EClickableArea* c : clickable_area_list)
		if ((c->text_area != nullptr) && (!c->text_area->can_be_edited) && (c->text_area->can_change_localisation))
		{
			c->text_area->original_text = c->text_area->localisation_text.localisations[ELocalisationText::active_localisation];
		}


	for (EButtonGroup* g : group_list)
	{
		g->recursive_change_localisation(_localisaton_id);
	}


}

void EButtonGroup::add_default_clickable_region_with_text_area(ELocalisationText _text)
{
	EClickableArea*
	new_clickable_area = EClickableArea::create_default_clickable_region(region_gabarite, this);
	main_clickable_area = new_clickable_area;

	clickable_area_list.push_back(new_clickable_area);

	ETextArea*
	new_text_area = ETextArea::create_centered_text_area(new_clickable_area, EFont::font_list[0], _text);
	new_text_area->localisation_text = _text;
	new_text_area->parent_group = this;
	new_text_area->can_be_edited = false;
	new_text_area->change_text(new_text_area->original_text);

	new_text_area->text_have_background = true;

	new_clickable_area->text_area = new_text_area;
}

void EButtonGroup::init_as_root_group(EWindow* _window)
{
	parent_window = _window;
	root_group = this;

	init_button_group(EGUIStyle::active_style, BrickStyleID::GROUP_DARKEN, bgroup_with_slider);
}

void EButtonGroup::init_as_fast_message(EWindow* _window, ELocalisationText _text)
{
	init_as_root_group(_window);

	add_default_clickable_region_with_text_area(_text);
}

void EButtonGroup::clear_group_selection()
{
	for (EButtonGroup* group : selected_groups)
	{
		group->is_selected = false;
	}

	selected_groups.clear();

	parent_vector_moving_group = nullptr;
	vector_moving_group = nullptr;

	first_selected_element = nullptr;
	last_selected_element = nullptr;

	parent_for_selected_groups = nullptr;
}

void EButtonGroupConfirmAction::init_as_confirm_decline_group(EWindow* _window)
{
	init_button_group(EGUIStyle::active_style, BrickStyleID::GROUP_DARKEN, bgroup_with_slider);

	root_group = this;
	button_group_is_active = true;
	//can_change_position_in_vector = false;
	close_this_group();
	parent_window = _window;

	unique_id = "global confirm group";

	pointer_to_workspace_part = add_close_group_and_return_workspace_group(new ERegionGabarite(100.0f, 20.0f), EGUIStyle::active_style);
	pointer_to_workspace_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
	add_caption_by_localistation_key("window_header_confirm_action");

	EButtonGroup*
		bottom_part_for_buttons = pointer_to_workspace_part->add_group(new EButtonGroup(new ERegionGabarite(250.0f, 30.0f)));

	bottom_part_for_buttons->init_button_group(EGUIStyle::active_style, BrickStyleID::NONE, bgroup_with_slider);
	bottom_part_for_buttons->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);
	bottom_part_for_buttons->button_size_x_override = 150.0f;
	bottom_part_for_buttons->group_have_button_lines = true;
	bottom_part_for_buttons->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

	EButtonGroup*
		top_part_for_description = pointer_to_workspace_part->add_group(new EButtonGroup(new ERegionGabarite(250.0f, 50.0f)));
	top_part_for_description->init_button_group(EGUIStyle::active_style, BrickStyleID::NONE, bgroup_with_slider);
	top_part_for_description->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);


	//text area
	ELocalisationText
		l_text;

	EClickableArea*
		c_area_for_group = EClickableArea::create_default_clickable_region(top_part_for_description->region_gabarite, top_part_for_description);

	pointer_to_description_text_area = ETextArea::create_centered_text_area(c_area_for_group, EFont::font_list[0], ELocalisationText::get_localisation_by_key("warning_unsave_changes"));
	pointer_to_description_text_area->can_be_edited = false;
	c_area_for_group->text_area = pointer_to_description_text_area;

	pointer_to_description_text_area->change_text(pointer_to_description_text_area->localisation_text.localisations[ELocalisationText::active_localisation]);
	pointer_to_description_text_area->set_color(1.0f, 0.75f, 0.5f, 1.0f);
	top_part_for_description->clickable_area_list.push_back(c_area_for_group);
	//






	EntityButtonConfirmAction*
		button_yes = new EntityButtonConfirmAction();
	pointer_to_confirm_button = button_yes;

	button_yes->stored_action = &EDataActionCollection::action_close_program;

	button_yes->make_default_button_with_unedible_text
	(
		new ERegionGabarite(200.0f, 25.0f),
		bottom_part_for_buttons,
		&EDataActionCollection::action_invoke_stored_confirm_action,
		ELocalisationText::get_localisation_by_key("button_accept_unsave")
	);
	button_yes->can_be_stretched = true;
	button_yes->main_text_area->set_color(1.0f, 0.2f, 0.1f, 1.0f);
	bottom_part_for_buttons->add_button_to_working_group(button_yes);





	EntityButtonConfirmAction*
		button_no = new EntityButtonConfirmAction();
	pointer_to_decline_button = button_no;

	button_no->make_default_button_with_unedible_text
	(
		new ERegionGabarite(100.0f, 25.0f),
		bottom_part_for_buttons,
		&EDataActionCollection::action_invoke_stored_confirm_action,
		ELocalisationText::get_localisation_by_key("button_cancel")
	);
	button_no->can_be_stretched = true;
	button_no->stored_action = &EDataActionCollection::action_cancel_closing_program;
	bottom_part_for_buttons->add_button_to_working_group(button_no);

	close_button->main_clickable_area->actions_on_click_list.insert
	(
		close_button->main_clickable_area->actions_on_click_list.begin(),
		&EDataActionCollection::action_cancel_closing_program
	);


	//EButtonGroup::refresh_button_group(this);
	this->need_refresh = true;
}

void EButtonGroup::get_last_focused_group(EButtonGroup* _group)
{
	//only active and visible groups can be focused
	if
		(
			(_group->is_this_group_active())
			&&
			(!_group->block_need_remove)
			&&
			(_group->is_in_visible_diapason())
			&&
			(!_group->group_is_suppressed)
			&&
			(!_group->is_blocked_by_superfocus())
			)
	{
		if
			(
				EButtonGroup::catched_by_mouse(_group)
				&&
				(_group->can_be_focused)
				)
		{
			//default focus
			focused_button_group = _group;

			//focus non[left mouse pressed]
			if (!EInputCore::MOUSE_BUTTON_LEFT) { focused_button_group_mouse_unpressed = _group; }

			//focus for group what can be selected
			if (_group->focusable_for_select)
			{
				EButtonGroup::focused_button_group_for_select = _group;
			}

			//focus last group with slider
			if
				(
					(_group->slider != nullptr)
					&&
					(_group->slider->entity_is_active())
					&&
					(EInputCore::MOUSE_SPEED_X * EInputCore::MOUSE_SPEED_X + EInputCore::MOUSE_SPEED_Y * EInputCore::MOUSE_SPEED_Y > 0)
					)
			{
				focused_button_group_with_slider = _group;
			}

			//repeat for each parent
			for (EButtonGroup* group : _group->group_list)
			{
				get_last_focused_group(group);
			}
		}
	}






	//return nullptr;
}

//void EButtonGroup::get_focused_group(EButtonGroup* _group)
//{
//	if
//	(
//		(EButtonGroup::catched_by_mouse(_group))
//	)
//	{
//		focused_button_group = _group;
//	}
//
//	for (EButtonGroupRow* row : _group->group_row_list)
//	for (EButtonGroup* group : row->button_group_list)
//	{
//		get_focused_group(group);
//	}
//	//return nullptr;
//}

EButtonGroup* EButtonGroup::create_default_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_with_bg,
		bgroup_with_slider,
		bgroup_default_bg
	);

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_root_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_with_bg,
		bgroup_with_slider,
		bgroup_darken_bg
	);

	just_created_button_group->root_group = just_created_button_group;

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_header_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_with_bg,
		bgroup_without_slider,
		bgroup_darken_bg
	);

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_invisible_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_without_bg,
		bgroup_without_slider,
		bgroup_darken_bg
	);

	//*just_created_button_group->can_be_focused = false;

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_button_group_without_bg(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_without_bg,
		bgroup_with_slider,
		bgroup_default_bg
	);

	just_created_button_group->can_be_focused = true;

	return just_created_button_group;
}

EButtonGroupSimpleColorEditor* EButtonGroupSimpleColorEditor::registered_color_editor_group = nullptr;
EButtonGroupSimpleColorEditor* EButtonGroupSimpleColorEditor::create_color_editor_group(ERegionGabarite* _region, EGUIStyle* _style, EWindow* _window)
{
	EButtonGroupSimpleColorEditor*
	color_editor_group = new EButtonGroupSimpleColorEditor(_region);

	color_editor_group->auto_superfocused = true;


	color_editor_group->init_as_root_group(_window);

	EDataContainer_VerticalNamedSlider* pointer_to_data;

	EButtonGroup*
		workspace_part = color_editor_group->add_close_group_and_return_workspace_group(new ERegionGabarite(100.0f, 20.0f), EGUIStyle::active_style);
	workspace_part->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

	//GROUP HORIZONTAL left		colors configurer [hair slier][named sliders]
	////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
	left_part = workspace_part->add_group(new EButtonGroup(new ERegionGabarite(150.0f, 256.0f)));
	left_part->init_button_group(EGUIStyle::active_style, BrickStyleID::GROUP_DEFAULT, bgroup_without_slider);
	left_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);
	////////////////////////////////////////////////////////////////////////////




	//GROUP	VERICAL bottom		[Value]	[Alpha]
	////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
	value_alpha_part = left_part->add_group(EButtonGroup::create_button_group_without_bg(new ERegionGabarite(150.0f, 70.0f), EGUIStyle::active_style));
	value_alpha_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);

	color_editor_group->pointer_to_VA_slider_group = value_alpha_part;
	////////////////////////////////////////////////////////////////////////////






	//GROUP	VERICAL top			[hair slider->(Hue) (Saturation)]
	////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
	hair_HS_slider_part = left_part->add_group(EButtonGroup::create_button_group_without_bg(new ERegionGabarite(150.0f, 150.0f), EGUIStyle::active_style));
	hair_HS_slider_part->init_button_group(EGUIStyle::active_style, BrickStyleID::NONE, bgroup_without_slider);
	hair_HS_slider_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);

	color_editor_group->pointer_to_hair_slider_group = hair_HS_slider_part;
	////////////////////////////////////////////////////////////////////////////


			//GROUP VERICAL right	color patterns
			////////////////////////////////////////////////////////////////////////////
			EButtonGroup*
			right_part = workspace_part->add_group(new EButtonGroup(new ERegionGabarite(150.0f, 256.0f)));
			right_part->init_button_group(EGUIStyle::active_style, BrickStyleID::GROUP_DEFAULT, bgroup_with_slider);
			right_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
			////////////////////////////////////////////////////////////////////////////

					//GROUP VERTICAL bottom		control buttons
					////////////////////////////////////////////////////////////////////////////
					EButtonGroup*
					color_pattern_control_part = right_part->add_group(new EButtonGroup(new ERegionGabarite(150.0f, 25.0f)));
					color_pattern_control_part->init_button_group(EGUIStyle::active_style, BrickStyleID::NONE, bgroup_with_slider);
					color_pattern_control_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);
					////////////////////////////////////////////////////////////////////////////

					//GROUP VERTICAL up			color pattern buttons
					////////////////////////////////////////////////////////////////////////////
					EButtonGroup*
					color_patterns_button_group = right_part->add_group(new EButtonGroup(new ERegionGabarite(150.0f, 25.0f)));
					color_patterns_button_group->init_button_group(EGUIStyle::active_style, BrickStyleID::GROUP_DEFAULT, bgroup_with_slider);
					color_patterns_button_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

					color_editor_group->pointer_to_color_pattern_group = color_patterns_button_group;
					////////////////////////////////////////////////////////////////////////////





	//add group to group list
	color_editor_group->need_refresh = true;



	////////////////////////////////////////////////////////////////////////////
	//buttons for SA group
	////////////////////////////////////////////////////////////////////////////
	
	//ALPHA
	////////////////////////////////////////////////////////////////////////////
	EntityButton*
	alpha_slider = EntityButton::create_horizontal_named_slider
	(

		new ERegionGabarite(350.0f, 35.0f),
		value_alpha_part,
		EFont::font_list[0],
		EGUIStyle::active_style,
		ELocalisationText::get_localisation_by_key("slider_color_a")
	);
	color_editor_group->color_slider_alpha = alpha_slider;

	alpha_slider->can_be_stretched = true;
	pointer_to_data = static_cast<EDataContainer_VerticalNamedSlider*>(alpha_slider->main_custom_data->data_container);

	pointer_to_data->pointer_to_value = new float(1.0f);
	pointer_to_data->min_value = 0.0f;
	pointer_to_data->mid_value = 0.5f;
	pointer_to_data->max_value = 1.0f;

	value_alpha_part->add_button_to_working_group(alpha_slider);
	////////////////////////////////////////////////////////////////////////////


	//VALUE
	////////////////////////////////////////////////////////////////////////////
	EntityButton*
		value_slider = EntityButton::create_horizontal_named_slider
		(

			new ERegionGabarite(350.0f, 35.0f),
			value_alpha_part,
			EFont::font_list[0],
			EGUIStyle::active_style,
			ELocalisationText::get_localisation_by_key("slider_color_v")
		);
	color_editor_group->color_slider_value = value_slider;

	value_slider->can_be_stretched = true;
	pointer_to_data = static_cast<EDataContainer_VerticalNamedSlider*>(value_slider->main_custom_data->data_container);

	pointer_to_data->pointer_to_value = new float(1.0f);
	pointer_to_data->min_value = 0.0f;
	pointer_to_data->mid_value = 0.5f;
	pointer_to_data->max_value = 1.0f;

	value_alpha_part->add_button_to_working_group(value_slider);
	////////////////////////////////////////////////////////////////////////////







	//CROSSHAIR HUE SATURATION
	////////////////////////////////////////////////////////////////////////////
	EntityButton*
		crosshair_slider = EntityButton::create_default_crosshair_slider
		(
			new ERegionGabarite(150.0f, 150.0f),
			hair_HS_slider_part,
			new float(180.0f),
			new float(0.55f),
			"hue_saturation"
		);
	crosshair_slider->can_be_stretched = true;
	color_editor_group->color_hair_slider_hue_saturation = crosshair_slider;

	EDataContainer_CrosshairSlider* crosshair_data = (EDataContainer_CrosshairSlider*)EntityButton::get_last_custom_data(crosshair_slider)->data_container;
	crosshair_data->min_x = 0.0f;
	crosshair_data->max_x = 360.0f;

	crosshair_data->min_y = 0.0f;
	crosshair_data->max_y = 1.0f;

	hair_HS_slider_part->add_button_to_working_group(crosshair_slider);
	////////////////////////////////////////////////////////////////////////////


	//CREATE NEW COLOR PATTERN
	////////////////////////////////////////////////////////////////////////////
	EntityButtonNewColorPattern*
	new_color_button = new EntityButtonNewColorPattern();
	new_color_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(150.0f, 20.0f),
		color_pattern_control_part,
		&EDataActionCollection::action_create_new_color,
		ELocalisationText::get_localisation_by_key("button_create_color_pattern")

	);
	new_color_button->can_be_stretched = true;

	new_color_button->target_button_group = color_patterns_button_group;
	new_color_button->pointer_to_color = &(color_editor_group->target_color);

	color_pattern_control_part->add_button_to_working_group(new_color_button);


	color_editor_group->generate_color_pattern_buttons();

	return color_editor_group;
}

EButtonGroup* EButtonGroup::add_close_group_and_return_workspace_group(ERegionGabarite* _region, EGUIStyle* _style)
{

	child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

	EButtonGroup* workspace_group =
		EButtonGroup::create_button_group_without_bg
		(
			new ERegionGabarite(100.0f, 100.0f),
			_style
		);

	workspace_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	workspace_group->stretch_x_by_parent_size = true;
	workspace_group->dynamic_size_y = true;

	add_group(workspace_group);

	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
	EButtonGroup* close_group =
		EButtonGroup::create_default_button_group
		(
			new ERegionGabarite(30.0f, _region->size_y),
			_style
		);

	close_section = close_group;
	close_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	close_group->stretch_x_by_parent_size = true;
	close_group->dynamic_size_y = false;

	add_group(close_group);
	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
	EButtonGroup* close_group_left =
		close_group->add_group
		(
			EButtonGroup::create_button_group_without_bg
			(
				new ERegionGabarite(30.0f, _region->size_y),
				_style
			)
		);
	close_section_left_part = close_group_left;
	close_group_left->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	close_group_left->stretch_x_by_parent_size = true;
	close_group_left->dynamic_size_y = true;


	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
	EButtonGroup* close_group_right =
		close_group->add_group
		(
			EButtonGroup::create_button_group_without_bg
			(
				new ERegionGabarite(20.0f, _region->size_y),
				_style
			)
		);

	close_group_right->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	close_group_right->stretch_x_by_parent_size = false;
	close_group_right->dynamic_size_y = true;

	EntityButton* jc_button = new EntityButton();
	jc_button->make_as_default_clickable_button
	(
		new ERegionGabarite(20.0f, 20.0f),
		close_group_right,
		&EDataActionCollection::action_close_root_group
	);
	//jc_button->main_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_cancel_closing_program);
	jc_button->sprite_layer_list.push_back
	(
		ESpriteLayer::create_default_sprite_layer_with_size_and_offset
		(
			NS_EGraphicCore::load_from_textures_folder("button_close"),

			0.0f,
			0.0f,
			0.0f,

			20.0f,
			20.0f,
			00.0f
		)
	);

	jc_button->disable_force_field = true;
	close_button = jc_button;
	close_group_right->add_button_to_working_group(jc_button);



	return workspace_group;
}

void EButtonGroup::add_caption_by_localistation_key(std::string _key)
{
	if (close_section_left_part != nullptr)
	{
		close_section_left_part->add_default_clickable_region_with_text_area(ELocalisationText::get_localisation_by_key(_key));

		close_section_left_part->clickable_area_list[0]->text_area->font = EFont::font_list[1];

	}
}

void EButtonGroup::add_help_button(ETextureGabarite* _texture_gabarite, std::string _key)
{
	if (close_section_left_part != nullptr)
	{
		EntityButton*
			but = new EntityButton;

		but->make_as_default_button_with_icon
		(
			new ERegionGabarite(close_section_left_part->region_gabarite->size_y, close_section_left_part->region_gabarite->size_y),
			close_section_left_part,
			nullptr,
			_texture_gabarite
		);

		but->add_default_description_by_key(_key);

		close_section_left_part->add_button_to_working_group(but);
	}
}

void EButtonGroup::scroll_to_this_button(EntityButton* _button)
{
	float
		original_scroll = scroll_y;



	float new_scroll = _button->offset_y - (region_gabarite->size_y - group_offset_for_content_up) + _button->button_gabarite->size_y;
	new_scroll = max(new_scroll, 0.0f);
	//translate_group_content(0.0f, (new_scroll - original_scroll), 0.0f, false);
	EInputCore::logger_param("button name", _button->main_text_area->localisation_text.base_name);
	EInputCore::logger_param("button offset y", _button->offset_y);
	EInputCore::logger_param("region size y", region_gabarite->size_y);
	EInputCore::logger_param("new scroll", new_scroll);


	slider->current_value = -new_scroll;
	scroll_y = slider->current_value;

	need_change = true;

	//_button->highlight_time = _button->max_highlight_time;
}

EButtonGroup* EButtonGroup::create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg)
{

	EButtonGroup* just_created_button_group = new EButtonGroup(_region);
	just_created_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	just_created_button_group->base_width = _region->size_x;
	just_created_button_group->base_height = _region->size_y;

	if (_default_bg)
	{
		just_created_button_group->button_group_type = ButtonGroupType::BGT_REGULAR;
	}
	else
	{
		just_created_button_group->button_group_type = ButtonGroupType::BGT_DARKEN;
	}

	just_created_button_group->group_have_background = _have_bg;

	if (_have_bg)
	{
		just_created_button_group->background_sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
		just_created_button_group->background_sprite_layer->make_as_PBR();

		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);
	}
	else
	{
		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);

		just_created_button_group->group_offset_for_content_bottom = 0.0f;
		just_created_button_group->group_offset_for_content_left = 0.0f;
		just_created_button_group->group_offset_for_content_right = 0.0f;
		just_created_button_group->group_offset_for_content_up = 0.0f;
	}

	if (_have_slider)
	{
		EButtonGroup::add_vertical_scroll_bar(just_created_button_group);
	}


	return just_created_button_group;
}

void EButtonGroup::init_button_group(EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg)
{
	batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	base_width = region_gabarite->size_x;
	base_height = region_gabarite->size_y;

	if (_default_bg)
	{
		button_group_type = ButtonGroupType::BGT_REGULAR;
	}
	else
	{
		button_group_type = ButtonGroupType::BGT_DARKEN;
	}

	group_have_background = _have_bg;

	if (_have_bg)
	{
		background_sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
		background_sprite_layer->make_as_PBR();

		EButtonGroup::apply_style_to_button_group(this, _style);

		//have_rama = false;
	}
	else
	{
		EButtonGroup::apply_style_to_button_group(this, _style);

		group_offset_for_content_bottom = 0.0f;
		group_offset_for_content_left = 0.0f;
		group_offset_for_content_right = 0.0f;
		group_offset_for_content_up = 0.0f;

		//have_rama = true;
	}


	if (_have_slider)
	{
		EButtonGroup::add_vertical_scroll_bar(this);
	}

}

void EButtonGroup::init_button_group(EGUIStyle* _style, BrickStyleID _brick_style_id, bool _have_slider)
{
	batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	base_width = region_gabarite->size_x;
	base_height = region_gabarite->size_y;


	brick_style_id = _brick_style_id;

	group_have_background = (_brick_style_id != BrickStyleID::NONE);

	background_sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
	background_sprite_layer->make_as_PBR();

	EButtonGroup::apply_style_to_button_group(this, _style, _brick_style_id);

	if (_have_slider)
	{
		EButtonGroup::add_vertical_scroll_bar(this);
	}

}


EGUIStyle* EGUIStyle::active_style = nullptr;
int EGUIStyle::number = 0;


std::vector<EGUIStyle*> EGUIStyle::style_list;
//EButtonGroupRow* EButtonGroupRow::create_default_row(ERegionGabarite* _region, EGUIStyle* _style)
//{
//	return nullptr;
//}

//EButtonGroupRow::EButtonGroupRow(ERegionGabarite* _region)
//{
//	ERegionGabarite::set_region_gabarite(&gabarite, _region);
//}

//EButtonGroupRow::EButtonGroupRow()
//{
//}

//EButtonGroup* EButtonGroupRow::add_group(EButtonGroup* _group)
//{
//	/*EButtonGroup* jc_group = EButtonGroup::create_default_button_group
//	(
//		new ERegionGabarite()
//	)*/
//
//	//correct region size
//
//	if ((_group != nullptr) && (*_group->region_gabarite->size_y > *gabarite->size_y))
//	{
//		*gabarite->size_y = *_group->region_gabarite->size_y;
//	}
//
//	_group->root_group = root_group;
//	group_list.push_back(_group);
//	_group->parent_group_row = this;
//
//	return _group;
//}

//EButtonGroup* EButtonGroupRow::get_last_group(EButtonGroupRow* _row)
//{
//	if((_row != nullptr) && (!_row->group_list.empty()))
//	{
//		return _row->group_list[_row->group_list.size() - 1];
//	}
//	else
//	{return nullptr;}
//}

//void EButtonGroupRow::stretch_parent_group(EButtonGroupRow* _row, float _new_y_size)
//{
//	EButtonGroup* p_group = _row->parent_button_group;
//
//	if (*p_group->gabarite_size_mode_y == GroupStretchMode::EXACT_STRETCH)
//	{
//		*p_group->region_gabarite->size_y = _new_y_size;
//		EButtonGroup::generate_brick_textured_bg(p_group);
//	}
//
//	//*_group->parent_group_row
//	if 
//	(
//		(p_group != nullptr)
//		&&
//		(p_group->parent_group_row != nullptr)
//		&&
//		(*p_group->region_gabarite->offset_y + *p_group->region_gabarite->size_y > *p_group->parent_group_row->gabarite->size_y)
//	)
//	{
//		EButtonGroup::stretch_parent_group
//		(
//			p_group,
//			*p_group->region_gabarite->offset_y + *p_group->region_gabarite->size_y
//		);
//	}
//}

void EBrickStyle::set_border_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up)
{
	_brick->border_texture_size_left = _left;
	_brick->border_texture_size_right = _right;
	_brick->border_texture_size_bottom = _bottom;
	_brick->border_texture_size_up = _up;

}

void EBrickStyle::set_offset_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up)
{
	_brick->offset_for_elements_left = _left;
	_brick->offset_for_elements_right = _right;
	_brick->offset_for_elements_bottom = _bottom;
	_brick->offset_for_elements_up = _up;
}

void EBrickStyle::set_subdivisions(EBrickStyle* _brick, int _x, int _y)
{
	_brick->subdivision_x = _x;
	_brick->subdivision_y = _y;
}

EBrickStyle::EBrickStyle()
{
}

EBrickStyle::EBrickStyle(std::string _file_name)
{
	file_name = _file_name;
}

EBrickStyle::~EBrickStyle()
{
}

void EBrickStyle::apply_brick_parameters_to_button_group(EButtonGroup* _group, EBrickStyle* _brick)
{
	_group->group_offset_for_content_left = _brick->offset_for_elements_left;
	_group->group_offset_for_content_right = _brick->offset_for_elements_right;
	_group->group_offset_for_content_bottom = _brick->offset_for_elements_bottom;
	_group->group_offset_for_content_up = _brick->offset_for_elements_up;
}

EGUIStyle::EGUIStyle()
{
}

EGUIStyle::EGUIStyle(std::string _folder)
{
	*folder = _folder;
}

EGUIStyle::~EGUIStyle()
{
}

void EGUIStyle::set_color_multiplier(float _r, float _g, float _b, float _a)
{
	text_color_multiplier[0] = _r;
	text_color_multiplier[1] = _g;
	text_color_multiplier[2] = _b;
	text_color_multiplier[3] = _a;
}

//void EGUIStyle::set_color_array(unsigned int _id, float _r, float _g, float _b, float _a)
//{
	/*text_color_array[_id][0] = _r;
	text_color_array[_id][0] = _g;
	text_color_array[_id][1] = _b;
	text_color_array[_id][2] = _a;*/
	//}

EButtonGroupRouterVariant* EButtonGroupRouterVariant::create_router_variant_button_group(EWindow* _target_window, EntityButtonVariantRouter* _router_button)
{
	int elements_count = ceil(_router_button->router_variant_list.size() / (float)(_router_button->height_division));

	float y_size = min(elements_count * _router_button->button_gabarite->size_y + BUTTON_FORCE_FIELD_SIZE * 2.0f * elements_count + 40.0f, 310.0f);
	//EInputCore::logger_simple_info("ZZZ");

	//		MAIN GROUP
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroupRouterVariant*
		main_group = new EButtonGroupRouterVariant
		(
			new ERegionGabarite
			(
				_router_button->button_gabarite->world_position_x,
				min(_router_button->button_gabarite->world_position_y, NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom - y_size - 30.0f),

				_router_button->button_gabarite->size_x * _router_button->height_division + 6.0f,
				y_size
			)
		);

	//main_group->region_gabarite->offset_x -= main_group->region_gabarite->size_x + 5.0f + *EGUIStyle::active_style->button_group_darken->side_offset_left + *EGUIStyle::active_style->button_group_darken->side_offset_right;

	main_group->init_button_group(EGUIStyle::active_style, BrickStyleID::GROUP_DARKEN, bgroup_with_slider);
	main_group->root_group = main_group;
	main_group->actions_on_close.push_back(&EDataActionCollection::action_delete_vertical_router_variants_group);
	main_group->target_router_button = _router_button;

	main_group->make_this_group_superfocused();

	main_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_static_autosize);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//_router_button->opened_router_group = main_group;


	//		WORKSPACE GROUP
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup* workspace_group = main_group->add_close_group_and_return_workspace_group
	(
		new ERegionGabarite(1.0f, 20.0f),
		EGUIStyle::active_style
	);
	workspace_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
	//workspace_group->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//		CREATE VARIANTS BUTTON
	int id = 0;
	for (RouterVariant* rv : _router_button->router_variant_list)
	{
		EntityButtonVariantRouterSelector*
			variant_button = new EntityButtonVariantRouterSelector();

		std::string
			text = rv->router_localisation.localisations[ELocalisationText::active_localisation];

		//set specific localisation [for window], if exist
		if ((rv->localisation_for_select_window.localisations[ELocalisationText::active_localisation] != ""))
		{
			text = rv->localisation_for_select_window.localisations[ELocalisationText::active_localisation];
		}

		//create button for window
		variant_button->make_as_default_button_with_icon_and_text
		(
			new ERegionGabarite(_router_button->button_gabarite->size_x, _router_button->button_gabarite->size_y),
			workspace_group,
			&EDataActionCollection::action_select_rotate_variant_from_list,
			rv->texture,
			text
		);

		//if (rv->localisation_for_select_window != nullptr)
		{
			variant_button->main_text_area->localisation_text = rv->localisation_for_select_window;
		}

		variant_button->id = id;
		variant_button->parent_router_group = main_group;

		if (rv->text_color != nullptr)
		{
			variant_button->main_text_area->stored_color = *rv->text_color;
			variant_button->main_text_area->color = *rv->text_color;
		}
		else
		{
			variant_button->main_text_area->color.set_color_RGBA(0.9f, 0.8f, 0.7f, 1.0f);
		}

		

		workspace_group->add_button_to_working_group(variant_button);

		id++;
	}

	_target_window->button_group_list.push_back(main_group);

	//EButtonGroup::refresh_button_group(main_group);
	main_group->need_refresh = true;



	return main_group;
}

EButtonGroupRouterVariant::~EButtonGroupRouterVariant()
{
	target_router_button->opened_router_group = nullptr;
}

void EButtonGroupFastMessage::button_group_update(float _d)
{
	EButtonGroup::button_group_update(_d);

	if (exist_time > 0.0f)
	{
		exist_time -= _d;

		if (exist_time <= 0.0f)
		{


			if (delete_when_expire)
			{
				block_need_remove = true;
			}
			else
			{
				close_this_group();
			}
		}
	}
}

namespace DebugNamespace
{
	EDebugStruct	NSW_registered_debug_struct[DebugStructID::DEBUG_STRUCT_ID_LAST_ELEMENT];
	EButtonGroup* NSW_pointer_to_debug_window = nullptr;

	bool is_debug_element_active(DebugStructID _id)
	{
		if (NSW_registered_debug_struct[_id].associated_button_router->selected_variant == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

HighlightStruct::HighlightStruct()
{

}

void HighlightStruct::set_color(float _r, float _g, float _b, float _a)
{
	highlight_color[0] = _r;
	highlight_color[1] = _g;
	highlight_color[2] = _b;
	highlight_color[3] = _a;
}

HighlightStruct HighlightStruct::create_new_highlihght(float _r, float _g, float _b, float _a, HighlightID _id, float _time)
{
	HighlightStruct
		pointer_to_highlight;

	pointer_to_highlight.set_color(_r, _g, _b, _a);

	pointer_to_highlight.max_time = _time;
	pointer_to_highlight.time_remaining = _time;

	pointer_to_highlight.highlight_id = _id;

	return pointer_to_highlight;
}
