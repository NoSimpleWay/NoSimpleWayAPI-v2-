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


EButtonGroup* EButtonGroup::color_editor_group = nullptr;
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
	for (int i = 0; i < button_group_list.size(); i++)
		if ((button_group_list[i] != nullptr) && (button_group_list[i]->need_remove))
		{
			if (!disable_deleting)
			{
				delete button_group_list[i];
			}

			EInputCore::logger_simple_success("Need remove [" + std::to_string(i) + "] element of button group list");

			button_group_list.erase(button_group_list.begin() + i);

			i--;

			//any_remove = true;
		}


	int catched_group_id = -1;



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
			if ((!EButtonGroup::parent_vector_moving_group->group_list[i]->suppressed) && (EButtonGroup::catched_by_mouse(EButtonGroup::parent_vector_moving_group->group_list[i])))
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

					EButtonGroup::parent_vector_moving_group->group_list.insert(catched_iterator, EButtonGroup::vector_moving_group);

					//EButtonGroup::change_group(EButtonGroup::parent_vector_moving_group);
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

					//		if focused not selection vector
					if (catched_iterator == EButtonGroup::selected_groups.end())
					{

						EButtonGroup::parent_vector_moving_group->group_list.erase(start_erasing, min(end_erasing + 1, EButtonGroup::parent_vector_moving_group->group_list.end() - 1));

						catched_iterator = std::find(EButtonGroup::parent_vector_moving_group->group_list.begin(), EButtonGroup::parent_vector_moving_group->group_list.end(), catched_group);


						EButtonGroup::parent_vector_moving_group->group_list.insert(catched_iterator, EButtonGroup::selected_groups.begin(), EButtonGroup::selected_groups.end());

						//EButtonGroup::change_group(EButtonGroup::parent_vector_moving_group);
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

		//EButtonGroup::parent_vector_moving_group = nullptr;
		//EButtonGroup::vector_moving_group = nullptr;
	}


	for (EButtonGroup* b_group : button_group_list)
		if
			(
				(b_group != nullptr)
				&&
				(b_group->button_group_is_visible())
				&&
				(b_group->region_gabarite->world_position_y <= b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y)
				&&
				(b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y >= b_group->region_gabarite->world_position_y)
				)
		{
			EButtonGroup::get_last_focused_group(b_group);
		}

	//RESET GROUP SELECTION
	if (EInputCore::key_pressed_once(GLFW_KEY_LEFT_SHIFT))
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

	)
	{
		if (EButtonGroup::first_selected_element == nullptr)
		{
			EButtonGroup::first_selected_element = EButtonGroup::focused_button_group_for_select;
			EButtonGroup::last_selected_element = EButtonGroup::focused_button_group_for_select;

			EButtonGroup::parent_for_selected_groups = EButtonGroup::focused_button_group_for_select->parent_group;
		}
		else
		{
			if (EButtonGroup::parent_for_selected_groups->root_group == EButtonGroup::focused_button_group_mouse_unpressed->root_group)
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


		//if (b_group->button_group_is_active)
		{
			//if ((b_group->need_recalcualte_culling_lines) || (EInputCore::key_pressed_once(GLFW_KEY_RIGHT_ALT)))
			//{
			//	//b_group->phantom_translate_if_need();
			//	EButtonGroup::calculate_culling_lines(b_group, true);
			//	b_group->need_recalcualte_culling_lines = false;
			//}

			b_group->background_update(_d);
		}

		//for (EButtonGroup* b_group : button_group_list)
		if
		(
				(b_group != nullptr)
				&&
				(b_group->button_group_is_visible())
				&&
				(b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y >= 0.0f)
				&&
				(b_group->region_gabarite->world_position_y <= NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)
				//&&
				//(b_group->can_see_this_group())	
		)
		{
			b_group->lower_culling_line = b_group->region_gabarite->world_position_y;
			b_group->higher_culling_line = b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y;

			b_group->button_group_update(_d);


			id++;
		}




	}

	//for (int i = 0; i < button_group_list.size(); i++)
	//{
	//	if (button_group_list[i]->need_refresh)
	//	{
	//		//recursive_phantom_translate_if_need();
	//		EButtonGroup::refresh_button_group(button_group_list[i]);

	//		button_group_list[i]->need_refresh = false;
	//	}

	//	if (button_group_list[i]->need_change)
	//	{
	//		//recursive_phantom_translate_if_need();
	//		EButtonGroup::change_group(button_group_list[i]);

	//		button_group_list[i]->need_change = false;
	//	}
	//}
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
				(b_group->button_group_is_visible())
				&&
				(b_group->can_see_this_group())
		)
		{
			b_group->draw_button_group();
		}

		if (false)
		{
			if (EButtonGroup::focused_button_group != nullptr)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 1.0f);
				ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);

				NS_ERenderCollection::add_data_to_vertex_buffer_rama
				(
					NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
					NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

					EButtonGroup::focused_button_group->region_gabarite->world_position_x + EButtonGroup::focused_button_group->region_gabarite->phantom_translate_x,
					EButtonGroup::focused_button_group->region_gabarite->world_position_y + EButtonGroup::focused_button_group->region_gabarite->phantom_translate_y,

					EButtonGroup::focused_button_group->region_gabarite->size_x,
					EButtonGroup::focused_button_group->region_gabarite->size_y,

					2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			if (EButtonGroup::focused_button_group_mouse_unpressed != nullptr)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_YELLOW, 1.0f);
				ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);

				NS_ERenderCollection::add_data_to_vertex_buffer_rama
				(
					NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
					NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

					EButtonGroup::focused_button_group_mouse_unpressed->region_gabarite->world_position_x + 1.0f + EButtonGroup::focused_button_group_mouse_unpressed->region_gabarite->phantom_translate_x,
					EButtonGroup::focused_button_group_mouse_unpressed->region_gabarite->world_position_y + 1.0f + EButtonGroup::focused_button_group_mouse_unpressed->region_gabarite->phantom_translate_y,

					EButtonGroup::focused_button_group_mouse_unpressed->region_gabarite->size_x - 2.0f,
					EButtonGroup::focused_button_group_mouse_unpressed->region_gabarite->size_y - 2.0f,

					2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			if (EButtonGroup::focused_button_group_with_slider != nullptr)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_PINK, 1.0f);
				ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);

				NS_ERenderCollection::add_data_to_vertex_buffer_rama
				(
					NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
					NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

					EButtonGroup::focused_button_group_with_slider->region_gabarite->world_position_x + 2.0f + EButtonGroup::focused_button_group_with_slider->region_gabarite->phantom_translate_x,
					EButtonGroup::focused_button_group_with_slider->region_gabarite->world_position_y + 2.0f + EButtonGroup::focused_button_group_with_slider->region_gabarite->phantom_translate_y,

					EButtonGroup::focused_button_group_with_slider->region_gabarite->size_x - 4.0f,
					EButtonGroup::focused_button_group_with_slider->region_gabarite->size_y - 4.0f,

					2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}
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

void EButtonGroup::recursive_set_suppressed()
{
	suppressed = true;

	for (EButtonGroup* group : group_list)
	{
		group->recursive_set_suppressed();
	}
}

bool EButtonGroup::button_group_is_visible()
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
			EntityButton*
				but = all_button_list[i];

			if (!disable_deleting) {
				delete but;
			}

			all_button_list.erase(all_button_list.begin() + i);

			i--;
		}
	}
	workspace_button_list.clear();
	workspace_button_list.shrink_to_fit();
}

void EButtonGroup::button_group_update(float _d)
{
	//clickable_area->update(_d);

	//subgroup
	//EButtonGroup* prev_group = nullptr;


	//invisible elements become visible



		/*if (row->header_button_group != nullptr)
		{
			row->header_button_group->update(_d);
		}*/
	if (highlight_time > 0.0f) { highlight_time -= _d; }
	bool any_remove = false;

	for (int i = 0; i < group_list.size(); i++)
		if ((group_list[i] != nullptr) && (group_list[i]->need_remove))
		{
			if (!disable_deleting)
			{
				//delete group_list[i];
			}
			EInputCore::logger_simple_success("Need remove [" + std::to_string(i) + "] child element of button group list");

			group_list.erase(group_list.begin() + i);

			i--;

			//if (parent_group != nullptr)
			//{
			//	change_group(parent_group);
			//}

			any_remove = true;
		}

	if (any_remove)
	{
		need_change = true;
		//EButtonGroup::change_group(this);
	}

	if (need_refresh)
	{
		//recursive_phantom_translate_if_need();
		EButtonGroup::refresh_button_group(this);

		need_refresh = false;
	}

	if (need_change)
	{
		//recursive_phantom_translate_if_need();
		EButtonGroup::change_group(this);

		need_change = false;
	}

	bool any_button_order_change = false;

	if (!all_button_list.empty())
		for (unsigned int i = 0; i < all_button_list.size(); i++)
			if (all_button_list[i]->need_remove)
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

	//if (need_recalculate_culling_lines)
	{
		//recalculate_culling_lines();

		//need_recalculate_culling_lines = false;
	}

	//if (need_recalcualte_culling_lines)
	//{
	//	//phantom_translate_if_need();
	//	EButtonGroup::calculate_culling_lines(this, false);
	//	//need_recalcualte_culling_lines = false;
	//}

	if
		(
			(button_group_is_visible())//group not deactivated
			&&
			(can_see_this_group())//in visible gabarites
		)
	{

		//
		phantom_translate_if_need();

		//if (parent_group != nullptr)
		//{
		//	lower_culling_line = max(region_gabarite->world_position_y, parent_group->lower_culling_line);
		//	higher_culling_line = min(region_gabarite->world_position_y + region_gabarite->size_y, parent_group->higher_culling_line);
		//}

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
				if ((!suppressed) || (but == slider))
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

		for (int i = 0; i < group_list.size(); i++)
		{
			group_list[i]->button_group_update(_d);
		}
	}



}

void EButtonGroup::background_update(float _d)
{
}

void EButtonGroup::draw_button_group()
{
	//clickable_area->draw();

	//EInputCore::logger_simple_success("draw button group");
	if
		(
			(can_see_this_group())
			&&
			(button_group_is_visible())
		)
	{
		//bool visibility = button_group_is_visible();

		//if (visibility)
		{
			if (group_phantom_redraw)
			{
				//EButtonGroup::change_group(this);

				EButtonGroup::generate_vertex_buffer_for_group(this, NSW_ONLY_TARGET);
				//highlight_this_group();
				group_phantom_redraw = false;
				//highlight_time = 1.0f;
				//EInputCore::logger_simple_info("Phantom redraw!");
			}

			//batcher_for_default_draw->draw_call();



			//BLURED SHADOW
			if ((have_shadow) && (root_group == this))
			{

				batcher_for_default_draw->draw_call();

				glDisable(GL_SCISSOR_TEST);

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

				batcher_for_default_draw->draw_call();


			}

			//batcher_for_default_draw->draw_call();

			//BEGIN DRAW SCISSORED ELEMENTS
			
			if ((!EInputCore::key_pressed(GLFW_KEY_SLASH)) && (true)) { glEnable(GL_SCISSOR_TEST); }

			if (parent_group != nullptr)
			{
				glScissor
				(
					region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
					lower_culling_line * NS_EGraphicCore::current_zoom,

					region_gabarite->size_x * NS_EGraphicCore::current_zoom,
					max(0.0f, higher_culling_line - lower_culling_line) * NS_EGraphicCore::current_zoom
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
			if ((background_sprite_layer != nullptr) && (have_bg))
			{
				background_sprite_layer->transfer_vertex_buffer_to_batcher();
			}

			if (have_rama)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_DARK_GRAY, 1.0f);
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

			//DEBUG HIGHLIGHT - FOCUSED BUTTON GROUP
			if ((EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL)) && (EButtonGroup::focused_button_group == this))
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
			if ((EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL)) && (EButtonGroup::focused_button_group_mouse_unpressed == this))
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
			if ((EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL)) && (EButtonGroup::focused_button_group_with_slider == this))
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

			glScissor
			(
				region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
				(lower_culling_line + border_bottom)* NS_EGraphicCore::current_zoom,

				region_gabarite->size_x* NS_EGraphicCore::current_zoom,
				max(0.0f, higher_culling_line - lower_culling_line - border_bottom - border_up)* NS_EGraphicCore::current_zoom
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
						if
							(but->have_phantom_draw)
						{
							but->have_phantom_draw = false;
							//generate vertex buffer for buttons

							for (change_style_action csa : but->action_on_generate_vertex_buffer)
							{
								csa(but, selected_style);
							}

							but->set_world_positions(but->world_position_x, but->world_position_y, but->world_position_z);
							but->generate_vertex_buffer_for_all_sprite_layers();

							//but->highlight_time = but->max_highlight_time;
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

								but->button_gabarite->size_x + 1.0f,
								but->button_gabarite->size_y + 1.0f,

								3.0f,

								NS_DefaultGabarites::texture_gabarite_white_pixel

							);
						}
					}
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


			for (EClickableArea* clickable_area : clickable_area_list)
			if (clickable_area != nullptr)
			{clickable_area->draw();}

			NS_EGraphicCore::pbr_batcher->draw_call();//draw pbg bg
			batcher_for_default_draw->draw_call();//draw text to default batcher



			//recursive draw


			for (EButtonGroup* group : group_list) { group->draw_button_group(); }




			//draw call to prepare for header
			//NS_EGraphicCore::test_batcher->draw_call();
			NS_EGraphicCore::pbr_batcher->draw_call();




			glDisable(GL_SCISSOR_TEST);

			if (EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL))
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
			}

			if ((EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT)) && (EButtonGroup::focused_button_group == this))
			{
				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_CYAN);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					region_gabarite->world_position_x + 0.0f,
					lower_culling_line + 2.0f,

					region_gabarite->size_x,
					2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);

				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_YELLOW);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					region_gabarite->world_position_x + 0.0f,
					higher_culling_line - 2.0f,

					region_gabarite->size_x - 0.0f,
					2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);

				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_RED);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + final_highest_point_y + scroll_y,

					region_gabarite->size_x - 0.0f,
					2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);

				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_PINK);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					region_gabarite->world_position_x + 0.0f,
					region_gabarite->world_position_y + highest_point_y_for_buttons + scroll_y,

					region_gabarite->size_x - 0.0f,
					2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
			{
				for (EButtonGroup* group : group_list)
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

			//slider debug highlight
			if ((EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL)) && (EButtonGroup::focused_button_group_with_slider == this))
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
					(!suppressed)
					&&
					(
						(parent_group != nullptr)
						&&
						(parent_group == EButtonGroup::parent_vector_moving_group)
						)
					&&
					(EButtonGroup::catched_by_mouse(this))
					&&
					(true)
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

			if ((highlight_time > 0.0f) && (max_highlight_time > 0.0f))
			{

				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, min(highlight_time / max_highlight_time, 1.0f) * 0.65);
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
		//lower_culling_line	= max(region_gabarite->world_position_y,							parent_group->lower_culling_line);
		//higher_culling_line = min(region_gabarite->world_position_y + region_gabarite->size_y,	parent_group->higher_culling_line);
	}






	EButtonGroup* prev_group = nullptr;

	prev_group = nullptr;

	//stretch row
	for (EButtonGroup* group : group_list)
	if (group->button_group_is_visible())
	{
		//OFFSET TO BASE
		if (prev_group == nullptr)
		{
			group->region_gabarite->offset_x = border_left;

			switch (child_align_direction)
			{
				case (ChildElementsAlignDirection::BOTTOM_TO_TOP):
				{
					group->region_gabarite->offset_y = border_bottom;
					break;
				};
		
				case (ChildElementsAlignDirection::TOP_TO_BOTTOM):
				{
					group->region_gabarite->offset_y = region_gabarite->size_y - group->region_gabarite->size_y - border_up;
					break;
				}
			}

		}
		else//OFFSET BY PREV GROUP
		{
			if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
			{
				group->region_gabarite->offset_x = border_left;

				if (child_align_direction == ChildElementsAlignDirection::BOTTOM_TO_TOP)
				{group->region_gabarite->offset_y = prev_group->region_gabarite->offset_y + prev_group->region_gabarite->size_y + group->additional_y_distance;}
				else
				if (child_align_direction == ChildElementsAlignDirection::TOP_TO_BOTTOM)
				{group->region_gabarite->offset_y = prev_group->region_gabarite->offset_y - group->region_gabarite->size_y - group->additional_y_distance;}
			}
			else
			if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
			{
				group->region_gabarite->offset_x = prev_group->region_gabarite->offset_x + prev_group->region_gabarite->size_x + 0.0f;
				group->region_gabarite->offset_y = prev_group->region_gabarite->offset_y;
			}
		}
		




		group->region_gabarite->world_position_x = round(region_gabarite->world_position_x + group->region_gabarite->offset_x);
		group->region_gabarite->world_position_y = round(region_gabarite->world_position_y + group->region_gabarite->offset_y + scroll_y);
		group->region_gabarite->world_position_z = round(region_gabarite->world_position_z + group->region_gabarite->offset_z);

		highest_point_y_for_groups = max(highest_point_y_for_groups, group->region_gabarite->offset_y + group->region_gabarite->size_y + group->additional_y_distance);
		
		prev_group = group;


	}
	else
	{
		group->region_gabarite->offset_x = 0.0f;
		group->region_gabarite->offset_y = 0.0f;

		group->region_gabarite->world_position_x = 0.0f;
		group->region_gabarite->world_position_y = 0.0f;
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





}
//void EButtonGroup::calculate_culling_lines(EButtonGroup* _group, bool _recursive)
//{
//	
//
//	if (_group->parent_group == nullptr)
//	{
//
//
//		_group->higher_culling_line = _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
//		_group->lower_culling_line = _group->region_gabarite->world_position_y;
//
//		_group->higher_culling_line_for_bg = _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
//		_group->lower_culling_line_for_bg = _group->region_gabarite->world_position_y;
//
//		//minimal_culling_line_top	= *higher_culling_line;
//		//minimal_culling_line_bottom	= *lower_culling_line;
//	}
//
//	if
//		(
//			(*_group->culling_lines_method == CullingLinesCalcMethod::CLCM_BY_HIMSELF)
//			&&
//			(_group->root_group != nullptr)
//			)
//	{
//
//
//		_group->higher_culling_line = _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
//		_group->lower_culling_line = _group->region_gabarite->world_position_y;
//
//		_group->higher_culling_line_for_bg = _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
//		_group->lower_culling_line_for_bg = _group->region_gabarite->world_position_y;
//	}
//
//
//
//	//for (EButtonGroupRow*	row:	_group->group_row_list)
//	for (EButtonGroup* group : _group->group_list)
//	{
//		group->higher_culling_line_for_bg = min
//		(
//			group->region_gabarite->world_position_y + group->region_gabarite->size_y,
//			_group->region_gabarite->world_position_y + _group->region_gabarite->size_y - _group->border_up
//		);
//
//		group->higher_culling_line_for_bg = min
//		(
//			group->higher_culling_line_for_bg,
//			_group->higher_culling_line_for_bg
//		);
//
//
//
//		group->lower_culling_line_for_bg = max
//		(
//			group->region_gabarite->world_position_y,
//			_group->region_gabarite->world_position_y + _group->border_bottom
//		);
//
//		group->lower_culling_line_for_bg = max
//		(
//			group->lower_culling_line_for_bg,
//			_group->lower_culling_line_for_bg
//		);
//
//
//
//		group->higher_culling_line = min
//		(
//			group->region_gabarite->world_position_y + group->region_gabarite->size_y - group->border_up,
//			_group->region_gabarite->world_position_y + _group->region_gabarite->size_y - _group->border_up
//		);
//
//		group->higher_culling_line = min
//		(
//			group->higher_culling_line,
//			_group->higher_culling_line
//		);
//
//
//		group->lower_culling_line = max(group->region_gabarite->world_position_y + group->border_bottom, _group->region_gabarite->world_position_y + _group->border_bottom);
//		group->lower_culling_line = max(group->lower_culling_line, _group->lower_culling_line);
//
//		//EButtonGroup::calculate_culling_lines(group);
//	}
//
//	if (_recursive)
//	{
//		for (EButtonGroup* group : _group->group_list)
//		{
//			//group->phantom_translate_if_need();
//			EButtonGroup::calculate_culling_lines(group, true);
//		}
//	}
//	//_group->need_recalcualte_culling_lines = false;
//	//_group->need_recalcualte_culling_lines = false;
//}

void EButtonGroup::generate_vertex_buffer_for_group(EButtonGroup* _group, bool _recursive)
{

	if
		(
			(_group->button_group_is_visible())
			&&
			(_group->can_see_this_group())
			//&&
			//(_group->region_gabarite->world_position_y <= NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)
			//&&
			//(_group->region_gabarite->world_position_y + _group->region_gabarite->size_y >= 0.0f)
		)
	{
		_group->group_phantom_redraw = false;

		//	
		
		//_group->highlight_time += 0.2f;

		EButtonGroup::generate_brick_textured_bg(_group);
		_group->need_redraw = false;

		if (_group->background_sprite_layer != nullptr)
		{
			_group->background_sprite_layer->sprite_layer_set_world_position
			(
				_group->region_gabarite->world_position_x,
				_group->region_gabarite->world_position_y,
				_group->region_gabarite->world_position_z
			);

			_group->background_sprite_layer->generate_vertex_buffer_for_sprite_layer("Button group background");
		}

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
				for (change_style_action csa : but->action_on_generate_vertex_buffer)
				{
					csa(but, _group->selected_style);
				}

				but->set_world_positions(but->world_position_x, but->world_position_y, but->world_position_z);
				but->generate_vertex_buffer_for_all_sprite_layers();

				but->have_phantom_draw = false;
			}
			else
			{
				but->have_phantom_draw = true;
			}

		if (_recursive)
		{
			for (EButtonGroup* group : _group->group_list) { EButtonGroup::generate_vertex_buffer_for_group(group, NSW_ONLY_TARGET); }
		}
	}
	else
	{
		_group->group_phantom_redraw = true;
	}
}


void EButtonGroup::group_stretch_x()
{
	float			constant_element_sizes_x = 0.0f;
	float			summ_size = 0.0f;
	float			target_size = 0.0f;
	float			final_size = 0.0f;

	float			slider_effect = 0.0f;



	unsigned int	dynamic_elements_count = 0;

	if ((slider != nullptr) && (slider->entity_is_active()))
	{
		slider_effect = slider->button_gabarite->size_x + 3.0f;
	}

	float shrink_size = 0.0f;
	//if (!*have_bg) { shrink_size = 0.0f; }

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{


		target_size = region_gabarite->size_x - border_left - border_right - (group_list.size() - 1) * 0.0f - shrink_size;
		target_size -= slider_effect;

		for (EButtonGroup* group : group_list)
			if (group->button_group_is_visible())
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
		target_size = region_gabarite->size_x - border_left - border_right - shrink_size;
		target_size -= slider_effect;

		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0) { final_size = target_size / float(dynamic_elements_count); }



	//final_size = 100.0f;
	for (EButtonGroup* group : group_list)
		if (group->button_group_is_visible())
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

void EButtonGroup::group_stretch_y()
{
	float			constant_element_sizes_y = 0.0f;
	float			summ_size = 0.0f;
	float			target_size = 0.0f;
	float			final_size = 0.0f;



	unsigned int	dynamic_elements_count = 0;

	float shrink_size = 0.0f;
	if (!have_bg) { shrink_size = 0.0f; }

	if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{

		target_size = max(region_gabarite->size_y, min_size_y) - border_bottom - border_up - (group_list.size() - 1) * BUTTON_GROUP_Y_DISTANCE - shrink_size - 0.0;

		for (EButtonGroup* group : group_list)
			if (group->button_group_is_visible())
			{
				group->region_gabarite->size_y = max(group->region_gabarite->size_y, group->min_size_y);

				if (group->stretch_y_by_parent_size)
				{
					dynamic_elements_count++;
				}
				else
				{
					target_size -= group->region_gabarite->size_y;
					constant_element_sizes_y += group->region_gabarite->size_y;
				}
			}
	}

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{

		target_size = region_gabarite->size_y - border_bottom - border_up - shrink_size + 0.0f;
		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0) { final_size = round(target_size / float(dynamic_elements_count)); }
	//if (dynamic_elements_count == 1) { final_size = round(target_size + 1.0f); }

	//final_size = 100.0f;
	for (EButtonGroup* group : group_list)
		if (group->button_group_is_visible())
		{
			if (group->stretch_y_by_parent_size)
			{
				group->region_gabarite->size_y = round(max(final_size, group->min_size_y));
				//group->region_gabarite->size_y = round(max(final_size, 0.0f));
				//group->region_gabarite->size_y = round(final_size);
			}

			//group->region_gabarite->size_y = round(max(group->region_gabarite->size_y, min_size_y));

			group->need_redraw = true;
		}

	//for (EButtonGroup* group : group_list) { group->group_stretch_y(); }
}

void EButtonGroup::check_slider()
{
	have_slider = true;//have no slider by default
	scroll_y = 0.0f;

	if (slider != nullptr)
	{
		slider->entity_disabled = true;
	}

	float child_elements_height_summ = 0.0f;
	float max_y = 0.0f;
	//stretchable group cannot have slider
	//if (*can_be_stretched_by_child)
	//{
	//	for (EButtonGroup* group : group_list)
	//	{*group->parent_have_slider = false;}//parent have no slider
	//}
	//else//potentially, can have slider
	{
		if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
		{
			child_elements_height_summ = ((float)group_list.size() - 1) * BUTTON_GROUP_Y_DISTANCE;

			for (EButtonGroup* group : group_list)
				//if (!*group->stretch_y_by_parent_size)//constant size
			{
				child_elements_height_summ += group->region_gabarite->size_y;//*szOID_ROOT_PROGRAM_AUTO_UPDATE_CA_REVOCATION
			}
		}

		if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
		{

			for (EButtonGroup* group : group_list)
				//if (!*group->stretch_y_by_parent_size)//constant size
			{
				max_y = max(max_y, group->region_gabarite->size_y);//*szOID_ROOT_PROGRAM_AUTO_UPDATE_CA_REVOCATION
			}

			child_elements_height_summ += max_y;
		}



		if ((child_elements_height_summ - 0.0f > region_gabarite->size_y - border_bottom - border_up) || (false))
		{
			if (slider != nullptr)
			{
				slider->entity_disabled = false;
				have_slider = true;


				//EInputCore::logger_param("summ", child_elements_height_summ);
				//EInputCore::logger_param("size y", *region_gabarite->size_y - 6.0f - *border_bottom - *border_up);
				//std::cout << std::endl;

				for (EButtonGroup* group : group_list)
				{
					//EInputCore::logger_param("group size y", *group->region_gabarite->size_y);
					group->parent_have_slider = true;
				}//parent have no slider

				scroll_y = slider->current_value;
			}
			else
			{
				//is_active = false;
			}
		}
		else
		{
			if (slider != nullptr)
			{
				slider->entity_disabled = true;
				have_slider = false;

				for (EButtonGroup* group : group_list)
				{
					group->parent_have_slider = false;
				}

				//reset scroll_y, because no slider = no scroll
				//scroll_y = 0.0f; //parent have no slider
			}
		}
	}

	//for (EButtonGroup* group : group_list) { group->check_slider(); }
}

void EButtonGroup::recursive_expand_to_workspace_size()
{
	if (can_resize_to_workspace_size_x)
	{
		region_gabarite->size_x = base_width + border_left + border_right;

	}

	if (can_resize_to_workspace_size_y)
	{
		region_gabarite->size_y = base_height + border_bottom + border_up;
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
	//_group->recursive_phantom_translate_if_need();
	if (_group->button_group_is_visible())
	{
		_group->button_group_prechange();

		//stretch to parent sizes
		_group->group_stretch_y();
		_group->check_slider();
		_group->group_stretch_x();

		//align group in parent gabarite
		_group->align_groups();
		_group->recalculate_culling_lines();

		//buttons process
		_group->reset_buttons_phantom_translate();
		_group->override_button_size();
		_group->put_buttons_to_lines();

		_group->activate_slider_if_need();

		_group->stretch_all_buttons();
		_group->set_buttons_offset();

		_group->calculate_world_coordinates_for_buttons();

		//if (!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
		//{
			EButtonGroup::generate_vertex_buffer_for_group(_group, NSW_ONLY_TARGET);
		//}


		for (EButtonGroup* child : _group->group_list)
		{
			change_group(child);
		}
	}
}



void EButtonGroup::refresh_button_group(EButtonGroup* _group)
{
	_group->recursive_expand_to_workspace_size();
	change_group(_group);
}


void EButtonGroup::recalculate_culling_lines()
{
	if (parent_group == nullptr)
	{
		lower_culling_line = region_gabarite->world_position_y + region_gabarite->phantom_translate_y;
		higher_culling_line = region_gabarite->world_position_y + region_gabarite->size_y + region_gabarite->phantom_translate_y;
	}
	else
	{
		lower_culling_line = max(region_gabarite->world_position_y + region_gabarite->phantom_translate_y, parent_group->lower_culling_line);
		higher_culling_line = min(region_gabarite->world_position_y + region_gabarite->phantom_translate_y + region_gabarite->size_y, parent_group->higher_culling_line);
	}
}

void EButtonGroup::recursive_recalculate_culling_lines()
{
	recalculate_culling_lines();

	for (EButtonGroup* child : group_list)
	{
		child->recursive_recalculate_culling_lines();
	}
}

void EButtonGroup::align_buttons_to_lines()
{
	highest_point_y_for_buttons = 0.0f;


	button_line_list.clear();

	float set_offset_x	= border_left;
	float set_offset_y	= border_bottom;
	float next_x		= 0.0f;
	float slider_effect = 0.0f;
	float max_y			= 0.0f;

	if ((slider != nullptr) && (!slider->entity_disabled))
	{ slider_effect = slider->button_gabarite->size_x; }
	
	EButtonGroupLine
	jc_button_line;

	for (EntityButton* but : workspace_button_list)
	if
	(
		(!but->fixed_position)
		&&
		(but->entity_is_active())
	)
	{
		max_y = max(max_y, but->button_gabarite->size_y);
		but->offset_x = set_offset_x + ((!but->disable_force_field)	? (but->force_field_left)	: (0.0f));
		but->offset_y = set_offset_y + ((!but->disable_force_field)	? (but->force_field_bottom)	: (0.0f));
		
		next_x = but->offset_x + but->button_gabarite->size_x + ((!but->disable_force_field) ? (but->force_field_right) : (0.0f));
		
		highest_point_y_for_buttons = max(highest_point_y_for_buttons, but->offset_y + but->button_gabarite->size_y);

		//not new lined
		if ((next_x + but->button_gabarite->size_x <= region_gabarite->size_x - border_right - slider_effect) || (false))
		{
			set_offset_x = next_x;
			jc_button_line.button_list.push_back(but);
		}
		else
		{
			button_line_list.push_back(jc_button_line);

			jc_button_line.button_list.clear();

			set_offset_x = border_left;
			set_offset_y += max_y;
			max_y = 0.0f;
		}
	}

}

void EButtonGroup::calculate_group_lines()
{
	float	max_y = 0.0f;
	float	offset_y = border_bottom;

	for (int i = 0; i < button_line_list.size(); i++)
	{
		max_y = 0.0f;

		for (EntityButton* but: button_line_list[i].button_list)
		{
			max_y = max(max_y, but->button_gabarite->size_y + ((!but->disable_force_field) ? (but->force_field_bottom + but->force_field_up) : (0.0f)));
		}

		button_line_list[i].line_size_y = max_y;
		button_line_list[i].offset_y = offset_y;

		offset_y += max_y;
	}

}

void EButtonGroup::activate_slider_if_need()
{
	final_highest_point_y = max(highest_point_y_for_buttons, highest_point_y_for_groups);

	if
	(
		(slider != nullptr)
		&&
		(highest_point_y_for_buttons > region_gabarite->size_y - border_up)
		&&
		(slider->entity_disabled)
	)
	{
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

	if (slider != nullptr)
	{
		slider->offset_x
			=
			region_gabarite->size_x
			-
			slider->button_gabarite->size_x
			-
			border_right;



		slider->world_position_x
			=
			slider->offset_x
			+
			region_gabarite->world_position_x;

		slider->offset_y = border_bottom;
		slider->world_position_y = region_gabarite->world_position_y + border_bottom;

		if (slider != nullptr)
		{
			//slider->button_gabarite->size_y = region_gabarite->size;
		}

		slider->world_position_y = region_gabarite->world_position_y;
	}
}

void EButtonGroup::stretch_all_buttons()
{
	float	free_space							= 0.0f;
	int		stretchable_elements_count			= 0;
	float	total_button_size					= 0.0f;
	int		additional_space_for_each_button	= 0;

	free_space = region_gabarite->size_x - border_left - border_right;

	for (int i = 0; i < button_line_list.size(); i++)
	{
		free_space					= region_gabarite->size_x - border_left - border_right;
		total_button_size			= 0.0f;
		stretchable_elements_count	= 0;


		for (EntityButton* but : button_line_list[i].button_list)
		{
			if (but->can_be_stretched) {stretchable_elements_count++;}

			total_button_size += but->button_gabarite->size_x + ((!but->disable_force_field) ? (but->force_field_left + but->force_field_right) : (0.0f)) + 2.0f;
		}

		if (stretchable_elements_count > 0)
		{
			free_space = free_space - total_button_size;
			additional_space_for_each_button = (round)(free_space / stretchable_elements_count);

			for (EntityButton* but : button_line_list[i].button_list)
			{
				if (but->can_be_stretched) {but->button_gabarite->size_x += max(additional_space_for_each_button, -100.0f);}
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

void EButtonGroup::override_button_size()
{
	if (button_size_x_override > 0)
	for (EntityButton* but : workspace_button_list)
	{
		but->button_gabarite->size_x = button_size_x_override;
	}
}

void EButtonGroup::put_buttons_to_lines()
{
	highest_point_y_for_buttons = 0.0f;

	button_line_list.clear();

	float slider_effect	= 0.0f;
	float total_size	= 0.0f;
	float button_max_y	= 0.0f;
	int lines_count		= 0;
	if ((slider != nullptr) && (slider->entity_is_active()))
	{
		slider_effect = slider->button_gabarite->size_x;
	}

	EButtonGroupLine
	jc_line;

	



	for (EntityButton* but : workspace_button_list)
	{

		//size all buttons on line
		total_size += but->button_gabarite->size_x + ((!but->disable_force_field) ? (but->force_field_left + but->force_field_right) : (0.0f));

		//new line
		if (total_size > region_gabarite->size_x - border_left - border_right - slider_effect)
		{
			//current line
			jc_line.line_size_y = button_max_y;
			highest_point_y_for_buttons += button_max_y;



			//new line
			lines_count++;
			jc_line.button_list.clear();
			button_line_list.push_back(jc_line);
			jc_line.button_list.push_back(but);

			total_size		= 0.0f;
		}
		else
		{
			jc_line.button_list.push_back(but);
		}

		button_max_y
		=
		max
		(
			button_max_y,
			but->button_gabarite->size_y + ((!but->disable_force_field) ? (but->force_field_bottom + but->force_field_up) : (0.0f))
		);

		
	}

	if (lines_count == 0){ button_line_list.push_back(jc_line); }
	

	highest_point_y_for_buttons += button_max_y;


}

void EButtonGroup::set_buttons_offset()
{
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	EInputCore::logger_param("size", button_line_list.size());

	for (int i = 0; i < button_line_list.size(); i++)
	{
		EInputCore::logger_param("buttons in line[" + std::to_string(i) + "]", button_line_list[i].button_list.size());
		offset_x = border_left;
		offset_y = button_line_list[i].offset_y;

		for (EntityButton* but : button_line_list[i].button_list)
		{
			but->offset_x = offset_x + ((!but->disable_force_field) ? (but->force_field_left)	: (0.0f));
			but->offset_y = offset_y + ((!but->disable_force_field) ? (but->force_field_bottom)	: (0.0f));

			offset_x += but->button_gabarite->size_x + ((!but->disable_force_field) ? (but->force_field_right) : (0.0f));
		}

		
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

void EButtonGroup::add_button_to_additional_group(EntityButton* _button)
{
	_button->parent_button_group = this;

	all_button_list.push_back(_button);
	//workspace_button_list.push_back(_button);
}

void EButtonGroup::realign_all_buttons()
{
	highest_point_y_for_buttons = 0.0f;
	final_highest_point_y = 0.0f;

	if ((slider != nullptr) && (have_slider))
	{
		scroll_y = slider->current_value;

		if (child_align_direction == ChildElementsAlignDirection::TOP_TO_BOTTOM)
		{
			scroll_y = min(scroll_y, slider->min_value);
		}
		else
			if (child_align_direction == ChildElementsAlignDirection::BOTTOM_TO_TOP)
			{
				scroll_y = max(scroll_y, slider->max_value);
			}

	}
	else
	{
		scroll_y = 0.0f;
	}

	EntityButton* prev_button = nullptr;

	float slider_additional = 0.0f;

	std::vector<EntityButton*> button_vector;

	float	total_available_x_space;
	float	total_button_gabarite_x;
	int		button_capacity;
	float	free_space_for_buttons;
	float	buttons_need_additional_size;

	if ((slider != nullptr) && (slider->entity_is_active()) && (have_slider))
	{
		slider_additional = slider->button_gabarite->size_x + 3.0f;
	}
	else
	{
		slider_additional = 0.0f;
	}

	//size override and autostrectch
	if (button_size_x_override > 0.0f)
	{
		total_available_x_space = region_gabarite->size_x - border_left - border_right - slider_additional;

		total_button_gabarite_x = button_size_x_override + BUTTON_FORCE_FIELD_SIZE * 0.0f;
		button_capacity = floor(total_available_x_space / total_button_gabarite_x);

		if (button_capacity > 0)
		{
			free_space_for_buttons = total_available_x_space - total_button_gabarite_x * button_capacity;
			buttons_need_additional_size = floor(free_space_for_buttons / button_capacity);

			for (EntityButton* but : all_button_list)
				if (but != slider)
				{
					float
					force_field_addition = ((!but->disable_force_field) ? (but->force_field_left + but->force_field_right) : (0.0f));
					//force_field_addition = 0.0f;

					but->button_gabarite->size_x = button_size_x_override + (buttons_need_additional_size - force_field_addition);

					//for (ECustomData* custom_data : but->custom_data_list)
					//	for (EClickableArea* clickable_area : custom_data->clickable_area_list)
					//	{
					//		if (clickable_area->text_area != nullptr)
					//		{
					//			if (clickable_area->text_area->localisation_text.base_name != "")
					//			{
					//				//clickable_area->text_area->change_text(clickable_area->text_area->localisation_text.localisations[ELocalisationText::active_localisation]);
					//			}
					//		}
					//	}
				}
		}
		else
			for (EntityButton* but : all_button_list)
				if (but != slider)
				{
					but->button_gabarite->size_x = button_size_x_override;

					for (ECustomData* custom_data : but->custom_data_list)
						for (EClickableArea* clickable_area : custom_data->clickable_area_list)
						{
							if (clickable_area->text_area != nullptr)
							{
								if (clickable_area->text_area->localisation_text.base_name != "")
								{
									//clickable_area->text_area->change_text(clickable_area->text_area->localisation_text.localisations[ELocalisationText::active_localisation]);
								}
							}
						}

				}
	}

	//reset phantom traslations and region catchs
	for (EntityButton* but : all_button_list)
	{
		if (but->button_gabarite->have_phantom_translation)
		{
			but->button_gabarite->have_phantom_translation = false;

			but->button_gabarite->phantom_translate_x = 0.0f;
			but->button_gabarite->phantom_translate_y = 0.0f;
			but->button_gabarite->phantom_translate_z = 0.0f;
		}

		for (ECustomData* cd : but->custom_data_list)
		for (EClickableArea* c_area : cd->clickable_area_list)
		{
			c_area->catched_body = false;
			c_area->catched_side_down = false;
			c_area->catched_side_up = false;
			c_area->catched_side_left = false;
			c_area->catched_side_right = false;
			c_area->catched_side_mid = false;
		}
	}

	//align buttons in group
	for (EntityButton* but : all_button_list)
	{
		if
		(
			(
				(!but->fixed_position)
			)
			&&
			(
				(but->entity_is_active())
				||
				(but->align_even_if_hidden)
			)
		)
		{

			bool new_lined = false;
			if (prev_button != nullptr)
			{
				if (!but->fixed_position)
				{
					button_vector.push_back(prev_button);
				}


				but->offset_x = prev_button->offset_x + prev_button->button_gabarite->offset_x + prev_button->button_gabarite->size_x;
				but->offset_y = prev_button->offset_y;

				if (!but->disable_force_field)
				{
					but->offset_x += but->force_field_left;
				}

				if (!prev_button->disable_force_field)
				{
					but->offset_x += prev_button->force_field_right;
				}




				//new line
				if
				(
					but->offset_x
					+
					but->button_gabarite->size_x
					//+
					//((!but->disable_force_field) ? (but->force_field_right) : (0.0f))
					>
					region_gabarite->size_x - border_right - slider_additional
				)
				{
					float max_size_y = 0.0f;

					for (EntityButton* bbb : button_vector)
					{
						float
						force_field_addition = ((!but->disable_force_field) ? (but->force_field_bottom + but->force_field_up) : (0.0f));

						max_size_y				= max(bbb->button_gabarite->size_y + force_field_addition, max_size_y);
					}

					but->offset_x	=	but->parent_button_group->border_left;
					but->offset_y	+=	max_size_y + 0.0f;

					if (!but->disable_force_field)
					{
						but->offset_x	+= but->force_field_left;
						but->offset_y	+= but->force_field_bottom;
					}



					new_lined = true;



					//button_vector.clear();
				}
				else
				{
					//button_vector.push_back(but);
				}


			}
			else
			{
				but->offset_x = but->parent_button_group->border_left;
				but->offset_y = but->parent_button_group->border_bottom;

				if (!but->disable_force_field)
				{
					but->offset_x += but->force_field_left;
					but->offset_y += but->force_field_bottom;
				}

				

				//button_vector.push_back(but);
			}





			if ((new_lined))
			{

				align_button_in_gabarite(button_vector, slider_additional);
				//EInputCore::logger_simple_info("invoke);

				new_lined = false;
			}

			if (!but->fixed_position)
			{
				float
				force_field_addition = 0.0f;
				/*
				force_field_addition = ((!but->disable_force_field) ? (but->force_field_bottom + but->force_field_up) : (0.0f));
				*/

				highest_point_y_for_buttons = max(highest_point_y_for_buttons, but->offset_y + but->button_gabarite->size_y + 0.0f + force_field_addition);
			}

			//scroll_y		= min(scroll_y, highest_point_y);



			prev_button = but;
		}
		else
		{
			//but->update(0.1f);
		}
	}

	//add prev_button to button vector
	if (prev_button != nullptr)
	{
		if (!prev_button->fixed_position)
		{
			button_vector.push_back(prev_button);
			align_button_in_gabarite(button_vector, slider_additional);
		}
	}

	//autoalign clickable area region gabarites
	for (EntityButton* but : all_button_list)
		for (ECustomData* cd : but->custom_data_list)
			for (EClickableArea* ca : cd->clickable_area_list)
			{
				ca->region_gabarite->align_all_clild_gabarites();
			}


	

	if (slider != nullptr)
	{
		slider->offset_x
			=
			region_gabarite->size_x
			-
			slider->button_gabarite->size_x
			-
			border_right;



		slider->world_position_x
			=
			slider->offset_x
			+
			region_gabarite->world_position_x;

		slider->offset_y = 0.0f;
		slider->world_position_y = region_gabarite->world_position_y + border_bottom;

		if (slider != nullptr)
		{
			//slider->button_gabarite->size_y = region_gabarite->size;
		}
	}

	if (slider != nullptr)
	{
		//slider become active, get additional border in right side
		if ((!have_slider) && (highest_point_y_for_buttons > region_gabarite->size_y))
		{
			slider->entity_disabled = false;

			//if (!have_slider)
			//{
			have_slider = true;
			this->realign_all_buttons();

			//have_slider = false;
			//slider->entity_disabled = true;
			//}

			//EInputCore::logger_simple_info("activate slider");
				//scroll_y = slider->current_value;

			for (EButtonGroup* group : group_list) { group->parent_have_slider = true; }
		}
		//else//no slider, no additional right border, if have any scroll, reset and realign
		//{
		//	slider->entity_disabled = true;
		//	have_slider = false;

		//	for (EButtonGroup* group : group_list) { group->parent_have_slider = false; }
		//}

		//scroll_y = slider->current_value;
	}

	final_highest_point_y = max(highest_point_y_for_groups, highest_point_y_for_buttons);
	


	//for (EButtonGroup* group : group_list) { group->realign_all_buttons(); }
}

void EButtonGroup::align_button_in_gabarite(std::vector<EntityButton*>& button_vector, float slider_additional)
{
	float total_width = 0.0f;

	//EInputCore::logger_param("slider_additional", slider_additional);

	int id = 0;
	for (EntityButton* but_temp : button_vector)
		if (!but_temp->fixed_position)
		{
			total_width += but_temp->button_gabarite->size_x + ((!but_temp->disable_force_field) ? (but_temp->force_field_left + but_temp->force_field_right) : (0.0f));

			//EInputCore::logger_param("button[" + std::to_string(id) + "]", but_temp->button_gabarite->size_x);
			id++;
		}

	float free_space = 0.0f;
	if (button_align_type == ButtonAlignType::BUTTON_ALIGN_MID) { free_space = (region_gabarite->size_x - slider_additional - total_width) / 2.0f; }
	if (button_align_type == ButtonAlignType::BUTTON_ALIGN_RIGHT) { free_space = (region_gabarite->size_x - slider_additional - total_width); }


	for (EntityButton* but_temp : button_vector)
	{
		if ((but_temp->fixed_position) && (true))
		{
			but_temp->world_position_x = round(but_temp->parent_button_group->region_gabarite->world_position_x + but_temp->offset_x);
			but_temp->world_position_y = round(but_temp->parent_button_group->region_gabarite->world_position_y + but_temp->offset_y);
		}
		else
		{
			but_temp->world_position_x = round(but_temp->parent_button_group->region_gabarite->world_position_x + but_temp->offset_x + but_temp->parent_button_group->scroll_x + free_space);
			but_temp->world_position_y = round(but_temp->parent_button_group->region_gabarite->world_position_y + but_temp->offset_y + but_temp->parent_button_group->scroll_y);
		}

		but_temp->button_gabarite->world_position_x = but_temp->world_position_x + but_temp->button_gabarite->offset_x;
		but_temp->button_gabarite->world_position_y = but_temp->world_position_y + but_temp->button_gabarite->offset_y;
		but_temp->button_gabarite->world_position_z = but_temp->world_position_z + but_temp->button_gabarite->offset_z;
	}

	button_vector.clear();
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
				_button_group->selected_style->slider_inactive->main_texture->size_x_in_pixels,
				_button_group->region_gabarite->size_y - _button_group->border_bottom - _button_group->border_up
			),
			_button_group,
			nullptr
		);

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

			if (_button_group->selected_style->slider_active != nullptr) { but->slider_active = _button_group->selected_style->slider_active; }
			if (_button_group->selected_style->slider_inactive != nullptr) { but->slider_inactive = _button_group->selected_style->slider_inactive; }
		}
		but->fixed_position = true;

		//but->sprite_layer->generate_vertex_buffer_for_sprite_layer("scroll bar sprite layer");
		_button_group->add_button_to_additional_group(but);
	}

}

void EButtonGroup::set_offset_borders(EButtonGroup* _group, float _left, float _right, float _bottom, float _up)
{
	_group->border_left = _left;
	_group->border_right = _right;

	_group->border_bottom = _bottom;
	_group->border_up = _up;
}

void EButtonGroup::apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style)
{
	//_group->translate_child_elements
	//(
	//	_group->region_gabarite->phantom_translate_x,
	//	_group->region_gabarite->phantom_translate_y,
	//	_group->region_gabarite->phantom_translate_z
	//);

	//_group->region_gabarite->have_phantom_translation = false;

	//_group->region_gabarite->phantom_translate_x = 0.0f;
	//_group->region_gabarite->phantom_translate_y = 0.0f;
	//_group->region_gabarite->phantom_translate_z = 0.0f;



	//_group->need_redraw = true;
	//_group->recursive_phantom_translate_if_need();

	if (_group->can_change_style) { _group->selected_style = _style; }

	if ((EGUIStyle::active_style != nullptr) && (_group->can_change_style))
	{

		if (_group->have_bg)
		{
			if ((*_group->button_group_type == ButtonGroupType::BGT_REGULAR) && (_style->button_group_main != nullptr))
			{
				EBrickStyle::apply_brick_parameters_to_button_group(_group, _style->button_group_main);
			}

			if ((*_group->button_group_type == ButtonGroupType::BGT_DARKEN) && (_style->button_group_darken != nullptr))
			{
				EBrickStyle::apply_brick_parameters_to_button_group(_group, _style->button_group_darken);
			}

			//EButtonGroup::generate_brick_textured_bg(_group);
		}
		else
		{
			EButtonGroup::set_offset_borders
			(
				_group,
				0.0f,
				0.0f,
				0.0f,
				0.0f
			);
		}

		//set slider head size
		if (_group->slider != nullptr)
		{
			//_group->slider->button_gabarite->size_x = _group->selected_style->slider_inactive->main_texture->size_x_in_pixels;
			//_group->slider->button_gabarite->size_y = _group->selected_style->slider_inactive->main_texture->size_y_in_pixels;
		}

		//_group->refresh_button_group(_group);
	}






}

void EButtonGroup::generate_brick_textured_bg(EButtonGroup* _group)
{
	if ((_group != nullptr) && (_group->selected_style != nullptr) && (_group->background_sprite_layer != nullptr))
	{
		if (_group->seed == 0) { _group->seed = rand() % 70000; }

		NS_ERenderCollection::temporary_sprites = true;

		if
		(
			(*_group->button_group_type == ButtonGroupType::BGT_DARKEN)
		)
		{


			NS_ERenderCollection::set_brick_borders_and_subdivisions
			(
				*_group->selected_style->button_group_darken->side_size_left,
				*_group->selected_style->button_group_darken->side_size_right,
				*_group->selected_style->button_group_darken->side_size_bottom,
				*_group->selected_style->button_group_darken->side_size_up,

				*_group->selected_style->button_group_darken->subdivision_x,
				*_group->selected_style->button_group_darken->subdivision_y
			);

			NS_ERenderCollection::generate_brick_texture
			(
				_group->region_gabarite,
				_group->background_sprite_layer,
				_group->selected_style->button_group_darken->main_texture,
				_group->selected_style->button_group_darken->normal_map_texture,
				_group->selected_style->button_group_darken->gloss_map_texture
			);
		}
		else //if (*_group->button_group_type == ButtonGroupType::BGT_REGULAR)
		{
			NS_ERenderCollection::set_brick_borders_and_subdivisions
			(
				*_group->selected_style->button_group_main->side_size_left,
				*_group->selected_style->button_group_main->side_size_right,
				*_group->selected_style->button_group_main->side_size_bottom,
				*_group->selected_style->button_group_main->side_size_up,

				*_group->selected_style->button_group_main->subdivision_x,
				*_group->selected_style->button_group_main->subdivision_y
			);

			srand(_group->seed);
			NS_ERenderCollection::generate_brick_texture
			(
				_group->region_gabarite,
				_group->background_sprite_layer,
				_group->selected_style->button_group_main->main_texture,
				_group->selected_style->button_group_main->normal_map_texture,
				_group->selected_style->button_group_main->gloss_map_texture
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

void EButtonGroup::change_style(EButtonGroup* _group, EGUIStyle* _style)
{
	EButtonGroup::apply_style_to_button_group(_group, _style);

	//recursive down to child elements
	for (EButtonGroup* group : _group->group_list)
		if (group != nullptr)
		{
			EButtonGroup::change_style(group, _style);
		}

	//if (_group->parent_group == nullptr) { EButtonGroup::refresh_button_group(_group); }
}

bool EButtonGroup::catched_by_mouse(EButtonGroup* _group)
{
	if
		(
			//(_group->higher_culling_line_for_bg * NS_EGraphicCore::current_zoom > _group->lower_culling_line_for_bg * NS_EGraphicCore::current_zoom)
				//&&
			(_group->button_group_is_visible())
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

	{
		region_gabarite->world_position_x += (round(_x));
		region_gabarite->world_position_y += (round(_y));
		region_gabarite->world_position_z += (round(_z));

		//higher_culling_line += round(_y);
		//lower_culling_line += round(_y);
		recalculate_culling_lines();

		if (_move_positions)
		{
			region_gabarite->offset_x += (round(_x));
			region_gabarite->offset_y += (round(_y));
			region_gabarite->offset_z += (round(_z));
		}
	}



	if
	(
			(
				(button_group_is_visible())
				&&
				(can_see_this_group())
			)
	)
	{
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
	}

	//if (_move_positions) { EButtonGroup::calculate_culling_lines(this, true); }
	







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
		//if (c_area->text_area != nullptr) { c_area->text_area->translate(_x, _y, _z, false); }
	}

	for (EntityButton* button : all_button_list)
	if ((_move_slider) || (button != slider))
	{
		if
		(
			(button_group_is_visible())
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

bool EButtonGroup::can_see_this_group()
{
	if (EInputCore::key_pressed(GLFW_KEY_TAB))
	{
		return true;
	}

	if
		(
			//(is_active)
			//&&
			(parent_group == nullptr)
			&&
			(region_gabarite->world_position_x + region_gabarite->phantom_translate_x <= NS_EGraphicCore::SCREEN_WIDTH / NS_EGraphicCore::current_zoom)
			&&
			(region_gabarite->world_position_x + region_gabarite->phantom_translate_x + region_gabarite->size_x > 0.0f)
			&&
			(region_gabarite->world_position_y + region_gabarite->phantom_translate_y <= NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)
			&&
			(region_gabarite->world_position_y + region_gabarite->phantom_translate_y + region_gabarite->size_y > 0.0f)
		)
	{
		return true;
	}

	if
	(
		//(is_active)
		//&&
		(parent_group != nullptr)
		&&
		(region_gabarite->world_position_y + region_gabarite->phantom_translate_x <= parent_group->region_gabarite->world_position_y + parent_group->region_gabarite->size_y)
		&&
		(region_gabarite->world_position_y + region_gabarite->size_y + region_gabarite->phantom_translate_x >= parent_group->region_gabarite->world_position_y)
	)
	{
		return true;
	}

	return false;




}

void EButtonGroup::phantom_translate_if_need()
{
	if (region_gabarite->have_phantom_translation)
	{
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

	EInputCore::logger_simple_info("invoke all select action in group");
	for (group_select_action gsa : actions_on_select_button)
	{
		EInputCore::logger_simple_info("invoke select action");
		gsa(this);
	}
}

EButtonGroup* EButtonGroup::set_parameters(ChildAlignMode _child_align_mode, bool _autosize_x, bool _autosize_y)
{
	child_align_mode = _child_align_mode;

	stretch_x_by_parent_size = _autosize_x;
	stretch_y_by_parent_size = _autosize_y;

	return this;
}

void EButtonGroup::activate_move_to_foreground_and_center()
{
	if (!button_group_is_active)
	{
		move_to_foreground_and_center();
		button_group_is_active = true;
	}
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

		for (int i = target_id + 1; i < parent_window->button_group_list.size() - 1; i++)
			if (parent_window->button_group_list[i]->can_change_position_in_vector)
			{
				last_id = i;
			}

		if ((target_id >= 0) && (last_id >= 0))
		{
			EButtonGroup* swap_group = this;

			for (int i = target_id; i < last_id; i++)
			{
				parent_window->button_group_list[i] = parent_window->button_group_list[i + 1];
			}

			parent_window->button_group_list[last_id] = swap_group;
		}

		//parent_window->button_group_list.
	}
}

void EButtonGroup::move_to_foreground_and_center()
{
	float new_postition_x = round(NS_EGraphicCore::SCREEN_WIDTH		/ 2.0f / NS_EGraphicCore::current_zoom - region_gabarite->size_x / 2.0f);
	float new_postition_y = round(NS_EGraphicCore::SCREEN_HEIGHT	/ 2.0f / NS_EGraphicCore::current_zoom - region_gabarite->size_y / 2.0f);

	translate_group(new_postition_x - region_gabarite->offset_x, new_postition_y - region_gabarite->offset_y, 0.0f, true);
	recursive_recalculate_culling_lines();
	//need_recalculate_culling_lines = true;

	move_to_foreground();
}

void EButtonGroup::highlight_this_group()
{
	highlight_time = max_highlight_time;
}

void EButtonGroup::recursive_change_localisation(int _localisaton_id)
{
	for (EntityButton* b : all_button_list)
		for (ECustomData* d : b->custom_data_list)
			for (EClickableArea* c : d->clickable_area_list)
				if ((c->text_area != nullptr) && (!c->text_area->can_be_edited))
				{
					c->text_area->original_text = c->text_area->localisation_text.localisations[ELocalisationText::active_localisation];
				}

	for (EClickableArea* c : clickable_area_list)
		if ((c->text_area != nullptr) && (!c->text_area->can_be_edited))
		{
			c->text_area->original_text = c->text_area->localisation_text.localisations[ELocalisationText::active_localisation];
		}


	for (EButtonGroup* g : group_list)
	{
		g->recursive_change_localisation(_localisaton_id);
	}


}

void EButtonGroup::add_default_clickable_region_with_text_area(ELocalisationText* _text)
{
	EClickableArea*
	new_clickable_area = EClickableArea::create_default_clickable_region(region_gabarite, this);
	main_clickable_area = new_clickable_area;

	clickable_area_list.push_back(new_clickable_area);

	ETextArea*
	new_text_area = ETextArea::create_centered_text_area(new_clickable_area, EFont::font_list[0], _text->localisations[ELocalisationText::active_localisation]);
	new_text_area->localisation_text = *_text;
	new_text_area->parent_group = this;
	new_text_area->can_be_edited = false;

	new_clickable_area->text_area = new_text_area;
}

void EButtonGroup::init_as_root_group(EWindow* _window)
{
	parent_window	= _window;
	root_group		= this;

	init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_darken_bg);
}

void EButtonGroup::init_as_fast_message(EWindow* _window, ELocalisationText* _text)
{
	init_as_root_group(_window);
	ELocalisationText ltext;
	add_default_clickable_region_with_text_area(_text);
}

void EButtonGroupConfirmAction::init_as_confirm_decline_group()
{
	init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_darken_bg);

	root_group = this;
	button_group_is_active = false;
	can_change_position_in_vector = false;




	pointer_to_workspace_part = add_close_group_and_return_workspace_group(new ERegionGabarite(100.0f, 20.0f), EGUIStyle::active_style);
	pointer_to_workspace_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);


	EButtonGroup*
		bottom_part_for_buttons = pointer_to_workspace_part->add_group(new EButtonGroup(new ERegionGabarite(250.0f, 30.0f)));
	bottom_part_for_buttons->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_with_slider, bgroup_darken_bg);
	bottom_part_for_buttons->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);
	bottom_part_for_buttons->button_size_x_override = 150.0f;
	bottom_part_for_buttons->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

	EButtonGroup*
		top_part_for_description = pointer_to_workspace_part->add_group(new EButtonGroup(new ERegionGabarite(250.0f, 50.0f)));
	top_part_for_description->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_with_slider, bgroup_darken_bg);
	top_part_for_description->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);


	//text area
	ELocalisationText
		l_text;

	EClickableArea*
		c_area_for_group = EClickableArea::create_default_clickable_region(top_part_for_description->region_gabarite, top_part_for_description);

	pointer_to_description_text_area = ETextArea::create_centered_text_area(c_area_for_group, EFont::font_list[0], "123");
	pointer_to_description_text_area->can_be_edited = false;
	c_area_for_group->text_area = pointer_to_description_text_area;

	pointer_to_description_text_area->localisation_text.localisations[NSW_localisation_EN] = "Warning! Unsaved changes!\\n\\nIf you continue, you lost unsaved data!";
	pointer_to_description_text_area->localisation_text.localisations[NSW_localisation_RU] = "Внимание! Несохранённые изменения!\\n\\nЕсли вы продолжите, вы потеряете несохранённые данные!";

	pointer_to_description_text_area->change_text(pointer_to_description_text_area->localisation_text.localisations[ELocalisationText::active_localisation]);
	pointer_to_description_text_area->set_color(1.0f, 0.75f, 0.5f, 1.0f);
	top_part_for_description->clickable_area_list.push_back(c_area_for_group);
	//






	l_text.localisations[NSW_localisation_EN] = "Close, dont save";
	l_text.localisations[NSW_localisation_RU] = "Выйти, не сохранять";

	EntityButtonConfirmAction*
		button_yes = new EntityButtonConfirmAction();
	pointer_to_confirm_button = button_yes;

	button_yes->stored_action = &EDataActionCollection::action_close_program;

	button_yes->make_default_button_with_unedible_text
	(
		new ERegionGabarite(200.0f, 25.0f),
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
	pointer_to_decline_button = button_no;

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


	//EButtonGroup::refresh_button_group(this);
	this->need_refresh = true;
}

void EButtonGroup::get_last_focused_group(EButtonGroup* _group)
{
	//only active and visible groups can be focused
	if
	(
		(_group->button_group_is_visible())
		&&
		(_group->can_see_this_group())
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
			if (!EInputCore::MOUSE_BUTTON_LEFT) {focused_button_group_mouse_unpressed = _group;}

			//focus for group what can be selected
			if (_group->focusable_for_select)
			{EButtonGroup::focused_button_group_for_select = _group;}

			//focus last group with slider
			if
			(
				(_group->slider != nullptr)
				&&
				(_group->slider->entity_is_active())
				&&
				(EInputCore::MOUSE_SPEED_X * EInputCore::MOUSE_SPEED_X + EInputCore::MOUSE_SPEED_Y * EInputCore::MOUSE_SPEED_Y > 0)
			)
			{focused_button_group_with_slider = _group;}

			//repeat for each parent
			for (EButtonGroup* group : _group->group_list)
			{get_last_focused_group(group);}
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

EButtonGroup* EButtonGroup::create_color_editor_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* main_group = create_root_button_group(_region, _style);
	main_group->root_group = main_group;
	HSVRGBAColor* HRA_color = &Helper::registered_color_list[rand() % Helper::registered_color_list.size()]->target_color;


	main_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	main_group->actions_on_draw.push_back(&EDataActionCollection::action_draw_color_rectangle_for_group);
	main_group->actions_on_update.push_back(&EDataActionCollection::action_convert_HSV_to_RGB);


	EButtonGroup* workspace_group = main_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), _style);
	workspace_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

	EDataContainer_Group_ColorEditor* data = new EDataContainer_Group_ColorEditor();
	data->work_color = HRA_color;
	//
	//data->pointer_to_H		= new float(1.0f);
	//data->pointer_to_S		= new float(1.0f);
	//data->pointer_to_V		= new float(1.0f);
	//data->pointer_to_alpha	= new float(1.0f);

	main_group->data_container = data;

	//**********************************************************************************************************************************************
	//**********************************************************************************************************************************************
	EButtonGroup* left_part = workspace_group->add_group(create_default_button_group(new ERegionGabarite(265.0f, 285.0f), _style));
	left_part->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	left_part->stretch_x_by_parent_size = false;
	left_part->stretch_y_by_parent_size = true;


	//**********************************************************************************************************************************************
	EButtonGroup* value_and_alpha_part = left_part->add_group(create_default_button_group(new ERegionGabarite(265.0f, 100.0f), _style));
	value_and_alpha_part->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	value_and_alpha_part->stretch_x_by_parent_size = true;
	value_and_alpha_part->stretch_y_by_parent_size = true;

	// // // // // // //
	EntityButton*
		jc_button = EntityButton::create_horizontal_named_slider(new ERegionGabarite(240.0f, 40.0f), value_and_alpha_part, EFont::font_list[0], EGUIStyle::active_style, "Прозрачность");
	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &HRA_color->a;
	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
	value_and_alpha_part->add_button_to_working_group(jc_button);

	data->slider_data_alpha_container = static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container);
	// // // // // // //

	// // // // // // //

	jc_button = EntityButton::create_horizontal_named_slider(new ERegionGabarite(240.0f, 40.0f), value_and_alpha_part, EFont::font_list[0], EGUIStyle::active_style, "Яркость");
	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &HRA_color->v;
	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
	value_and_alpha_part->add_button_to_working_group(jc_button);

	data->slider_data_value_container = static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container);
	// // // // // // //


//**********************************************************************************************************************************************
	EButtonGroup* hue_part = left_part->add_group(create_default_button_group(new ERegionGabarite(265.0f, 260.0f), _style));
	hue_part->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	hue_part->stretch_x_by_parent_size = true;
	hue_part->stretch_y_by_parent_size = false;

	// // // // // // //
	jc_button = EntityButton::create_default_crosshair_slider
	(
		new ERegionGabarite(256.0f, 256.0f),
		hue_part,
		&HRA_color->h,
		&HRA_color->s,
		"hue_saturation"
	);

	EDataContainer_CrosshairSlider* crosshair_data = (EDataContainer_CrosshairSlider*)EntityButton::get_last_custom_data(jc_button)->data_container;
	crosshair_data->min_x = 0.0f;
	crosshair_data->max_x = 360.0f;

	crosshair_data->min_y = 0.0f;
	crosshair_data->max_y = 1.0f;

	data->crosshair_slider_data_container = crosshair_data;

	hue_part->add_button_to_working_group(jc_button);
	// // // // // // //


	//**********************************************************************************************************************************************
	//**********************************************************************************************************************************************
	EButtonGroup* color_box = workspace_group->add_group(create_default_button_group(new ERegionGabarite(35.0f, 10.0f), _style));
	//right_part->debug_translation = true;
	color_box->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	color_box->stretch_x_by_parent_size = false;
	color_box->stretch_y_by_parent_size = true;
	data->pointer_to_color_box_sector = color_box;

	//**********************************************************************************************************************************************
	//**********************************************************************************************************************************************
	EButtonGroup* color_collection_frame = workspace_group->add_group(create_default_button_group(new ERegionGabarite(256.0f, 100.0f), _style));
	//right_part->debug_translation = true;
	color_collection_frame->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	color_collection_frame->stretch_x_by_parent_size = true;
	color_collection_frame->stretch_y_by_parent_size = true;


	EButtonGroup* control_button_segment = color_collection_frame->add_group(create_default_button_group(new ERegionGabarite(256.0f, 50.0f), _style));
	control_button_segment->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	control_button_segment->stretch_x_by_parent_size = true;
	control_button_segment->stretch_y_by_parent_size = false;

	//button "unbind color"
	jc_button = new EntityButton();
	jc_button->make_as_default_clickable_button(new ERegionGabarite(180.0f, 30.0f), control_button_segment, &EDataActionCollection::action_unbing_color);

	ETextArea* jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Отвязать от шаблона");
	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
	control_button_segment->add_button_to_working_group(jc_button);

	//button "register new color"
	jc_button = new EntityButton();
	jc_button->make_as_default_clickable_button(new ERegionGabarite(180.0f, 30.0f), control_button_segment, &EDataActionCollection::action_create_new_color);

	jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Создать шаблон цвета");
	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
	control_button_segment->add_button_to_working_group(jc_button);



	EButtonGroup*
		color_collection_segment = color_collection_frame->add_group(create_default_button_group(new ERegionGabarite(256.0f, 40.0f), _style));
	color_collection_segment->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	color_collection_segment->stretch_x_by_parent_size = true;
	color_collection_segment->stretch_y_by_parent_size = true;
	data->pointer_to_color_collection_sector = color_collection_segment;
	color_collection_segment->actions_on_select_button.push_back(&EDataActionCollection::action_set_new_color_to_button);

	for (int i = 0; i < Helper::registered_color_list.size(); i++)
	{
		// // // // // // //// // // // // // //// // // // // // //
		HRA_color_collection* HRA_collection = Helper::registered_color_list[i];
		HSVRGBAColor* HRA_color = &HRA_collection->target_color;
		//HRA_color->h = rand() % 360;
		//HRA_color->s = 1.0f - pow((rand() % 100) / 100.0f, 1.0);
		//HRA_color->v = 1.0f - pow((rand() % 100) / 100.0f, 3.0);
		//HRA_color->a = 1.0f - pow((rand() % 100) / 100.0f, 4.0);


		//std::cout << Helper::registered_color_list[0] << std::endl;
		EntityButtonColorButton* color_button = EntityButton::create_named_color_button
		(
			//*color_collection->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

			new ERegionGabarite(120.0f, 38.0f),
			color_collection_segment,
			EFont::font_list[0],
			EGUIStyle::active_style,
			HRA_collection->name,
			HRA_collection,
			HRA_color,
			ColorButtonMode::CBM_SELECT_COLOR
		);

		//std::cout << HRA_color << std::endl;
		//Entity::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_button);

		color_collection_segment->add_button_to_working_group(color_button);
		// // // // // // //// // // // // // //// // // // // // //
	}

	return main_group;
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
	workspace_group->stretch_y_by_parent_size = true;

	add_group(workspace_group);

	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
	EButtonGroup* close_group =
		EButtonGroup::create_default_button_group
		(
			new ERegionGabarite(30.0f, _region->size_y),
			_style
		);

	close_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	close_group->stretch_x_by_parent_size = true;
	close_group->stretch_y_by_parent_size = false;

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

	close_group_left->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	close_group_left->stretch_x_by_parent_size = true;
	close_group_left->stretch_y_by_parent_size = true;


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
	close_group_right->stretch_y_by_parent_size = true;

	EntityButton* jc_button = new EntityButton();
	jc_button->make_as_default_clickable_button
	(
		new ERegionGabarite(20.0f, 20.0f),
		close_group_right,
		&EDataActionCollection::action_close_root_group
	);

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
	close_group_right->add_button_to_working_group(jc_button);



	return workspace_group;
}

EButtonGroup* EButtonGroup::create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg)
{

	EButtonGroup* just_created_button_group = new EButtonGroup(_region);
	just_created_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	just_created_button_group->base_width = _region->size_x;
	just_created_button_group->base_height = _region->size_y;

	if (_default_bg)
	{
		*just_created_button_group->button_group_type = ButtonGroupType::BGT_REGULAR;
	}
	else
	{
		*just_created_button_group->button_group_type = ButtonGroupType::BGT_DARKEN;
	}

	just_created_button_group->have_bg = _have_bg;

	if (_have_bg)
	{
		just_created_button_group->background_sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
		just_created_button_group->background_sprite_layer->make_as_PBR();

		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);
	}
	else
	{
		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);

		just_created_button_group->border_bottom = 0.0f;
		just_created_button_group->border_left = 0.0f;
		just_created_button_group->border_right = 0.0f;
		just_created_button_group->border_up = 0.0f;
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
		*button_group_type = ButtonGroupType::BGT_REGULAR;
	}
	else
	{
		*button_group_type = ButtonGroupType::BGT_DARKEN;
	}

	have_bg = _have_bg;

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

		border_bottom = 0.0f;
		border_left = 0.0f;
		border_right = 0.0f;
		border_up = 0.0f;

		//have_rama = true;
	}


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
	*_brick->side_size_left = _left;
	*_brick->side_size_right = _right;
	*_brick->side_size_bottom = _bottom;
	*_brick->side_size_up = _up;
}

void EBrickStyle::set_offset_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up)
{
	*_brick->side_offset_left = _left;
	*_brick->side_offset_right = _right;
	*_brick->side_offset_bottom = _bottom;
	*_brick->side_offset_up = _up;
}

void EBrickStyle::set_subdivisions(EBrickStyle* _brick, int _x, int _y)
{
	*_brick->subdivision_x = _x;
	*_brick->subdivision_y = _y;
}

EBrickStyle::EBrickStyle()
{
}

EBrickStyle::EBrickStyle(std::string _file_name)
{
	*file_name = _file_name;
}

EBrickStyle::~EBrickStyle()
{
}

void EBrickStyle::apply_brick_parameters_to_button_group(EButtonGroup* _group, EBrickStyle* _brick)
{
	_group->border_left = *_brick->side_offset_left;
	_group->border_right = *_brick->side_offset_right;
	_group->border_bottom = *_brick->side_offset_bottom;
	_group->border_up = *_brick->side_offset_up;
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

	main_group->init_button_group(EGUIStyle::active_style, true, true, false);
	main_group->root_group = main_group;
	main_group->actions_on_close.push_back(&EDataActionCollection::action_delete_vertical_router_variants_group);
	main_group->target_router_button = _router_button;


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
	workspace_group->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//		CREATE VARIANTS BUTTON
	int id = 0;
	for (RouterVariant* rv : _router_button->router_variant_list)
	{
		EntityButtonVariantRouterSelector*
			variant_button = new EntityButtonVariantRouterSelector();

		std::string text = rv->localisation->localisations[ELocalisationText::active_localisation];

		if ((rv->localisation_for_select_window != nullptr) && (rv->localisation_for_select_window->localisations[ELocalisationText::active_localisation] != ""))
		{
			text = rv->localisation_for_select_window->localisations[ELocalisationText::active_localisation];
		}

		variant_button->make_as_default_button_with_icon_and_text
		(
			new ERegionGabarite(_router_button->button_gabarite->size_x, _router_button->button_gabarite->size_y),
			workspace_group,
			&EDataActionCollection::action_select_rotate_variant_from_list,
			rv->texture,
			text
		);

		if (rv->localisation_for_select_window != nullptr)
		{
			variant_button->main_text_area->localisation_text = *rv->localisation_for_select_window;
		}

		variant_button->id = id;
		variant_button->parent_router_group = main_group;

		variant_button->main_text_area->stored_color = *rv->color;
		variant_button->main_text_area->color = *rv->color;

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

		if (exist_time < 0.0f)
		{
			

			if (delete_when_expire) { need_remove = true; } else { button_group_is_active = false; }
		}
	}
}
