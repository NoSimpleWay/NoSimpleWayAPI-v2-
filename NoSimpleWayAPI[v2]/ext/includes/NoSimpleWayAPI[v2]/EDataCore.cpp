#pragma once

/**/
#ifndef	_DATA_CORE_ALREADY_LINKED_
#define	_DATA_CORE_ALREADY_LINKED_
#include "EDataCore.h"
#endif
/**/

/**/
#ifndef _E_INPUT_CORE_ALREADY_LINKED_
#define _E_INPUT_CORE_ALREADY_LINKED_
#include "EInputCore.h"
#endif
/**/

#ifndef _E_DATA_ENTITY_ALREADY_LINKED_
/**/#define _E_DATA_ENTITY_ALREADY_LINKED_
/**/#include "EDataEntity.h"
#endif


#include "Helpers.h"

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/


EClickableArea* EClickableArea::active_clickable_region = nullptr;

ERegionGabarite* ERegionGabarite::temporary_gabarite = new ERegionGabarite();

void EDataActionCollection::action_log_text(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//if (EDataCore::overlapped_by_mouse()
	EInputCore::logger_param
	(
		"Message",
		*
		(
			(
				(EDataContainerMessage*)_custom_data->data_container
				)->message
			)
	);
}



void EDataActionCollection::action_update_vertical_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonVerticalSlider* slider = static_cast<EntityButtonVerticalSlider*>(_entity);

	if
	(
		(EInputCore::key_pressed_once(GLFW_KEY_LEFT_SHIFT))
		&&
		(EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
		&&
		(EButtonGroup::focused_button_group_with_slider == slider->parent_button_group)
	)
	{
		//EInputCore::logger_param("HPYb:", slider->parent_button_group->highest_point_y_for_buttons);
		//EInputCore::logger_param("HPYg:", slider->parent_button_group->highest_point_y_for_groups);

		//EInputCore::logger_param("group_size_y", slider->parent_button_group->region_gabarite->size_y);

	}

	//slider->degree += _d * 45.0f;

	slider->current_value = *((float*)slider->pointer_to_target_value);

	if ((EButtonGroup::focused_button_group_with_slider == slider->parent_button_group) && (EInputCore::scroll_direction != 0))
	{
		float scroll_speed = 5.0f;

		slider->scroll_speed += pow(EInputCore::scroll_direction, 3.0) * scroll_speed * -1.0f;
	}

	float total_value = slider->max_value - slider->min_value;

	if (!slider->is_rotator)
	{
		//left click drag
		if
			(
				(EInputCore::MOUSE_BUTTON_LEFT)
				&&
				(EClickableArea::active_clickable_region == slider->main_clickable_area)
				)
		{

			slider->scroll_speed = 0.0f;

			slider->current_value = (EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom - slider->button_gabarite->world_position_y) / slider->workspace_height;
			slider->current_value = slider->min_value + slider->current_value * total_value;
		}
	}
	else
	{
		if
			(
				((EInputCore::MOUSE_BUTTON_LEFT) || (EInputCore::MOUSE_BUTTON_RIGHT))
				&&
				(EClickableArea::active_clickable_region == slider->main_clickable_area)
				)
		{
			float addition = (EInputCore::MOUSE_BUTTON_LEFT) ? (1.0f) : (-1.0f);
			slider->scroll_speed = addition * 64.0f * _d;


			//slider->current_value += _d * 0.000000000f;
			//slider->current_value = slider->min_value + slider->current_value * total_value;
		}
	}

	
	if
	(
		(
			(EInputCore::MOUSE_BUTTON_LEFT)
			&&
			(EClickableArea::active_clickable_region == slider->main_clickable_area)
		)
		||
		(slider->scroll_speed != 0.0f)
		||
		(
			(slider->min_value < slider->max_value)
			&&
			(
				(slider->current_value < slider->min_value)
				||
				(slider->current_value > slider->max_value)
			)
		)
		||
		(
			(slider->min_value >= slider->max_value)
			&&
			(
				(slider->current_value > slider->min_value)
				||
				(slider->current_value < slider->max_value)
			)
		)
	)
	{
		//EInputCore::logger_param("slider gabarite size y", slider->button_gabarite->size_y);
		//EInputCore::logger_param("highest point y for buttons", slider->parent_button_group->highest_point_y_for_buttons);
		//EInputCore::logger_param("region y", slider->parent_button_group->region_gabarite->size_y);
		
		//EInputCore::logger_param("min", slider->min_value);
		//EInputCore::logger_param("max", slider->max_value);
		//EInputCore::logger_param("highest_point", slider->parent_button_group->final_highest_point_y);

		float multiplier = 1.0f;
		

		float old_value = *((float*)slider->pointer_to_target_value);

		//float value = 0.0f;

		


		slider->current_value += slider->scroll_speed;
		//slider->current_value = (slider->current_value);
		
		//RESET SCROLL SPEED ON BOUND VALUE
		//if (!NSW_APRIL_FOOL)
		{
			if
				(
					(slider->min_value < slider->max_value)
					&&
					(
						(slider->current_value <= slider->min_value)
						||
						(slider->current_value >= slider->max_value)
					)
				)
			{
				slider->scroll_speed = 0.0f;
			}

			if
				(
					(slider->min_value > slider->max_value)
					&&
					(
						(slider->current_value >= slider->min_value)
						||
						(slider->current_value <= slider->max_value)
						)
					)
			{
				slider->scroll_speed = 0.0f;
			}
		}

		slider->degree += slider->scroll_speed * 10.0f;
		//clamp border values
		slider->current_value = std::clamp(slider->current_value, min(slider->min_value, slider->max_value), max(slider->min_value, slider->max_value));


		multiplier = 1.0f;
		*((float*)slider->pointer_to_target_value) = (slider->current_value);
		*((float*)slider->pointer_to_target_value) = round(*((float*)slider->pointer_to_target_value));

		//*((float*)slider->pointer_to_target_value) = round(*((float*)slider->pointer_to_target_value));
		

		if (old_value != *((float*)slider->pointer_to_target_value))
		{
			float translate_value = (*((float*)slider->pointer_to_target_value) - old_value);
		
			slider->parent_button_group->translate_group_content(0.0f, round(translate_value * multiplier) , 0.0f, false);
			//slider->parent_button_group->recursive_recalculate_culling_lines();
		}

		
		//slider->parent_button_group->need_recalculate_culling_lines = true;

		//EButtonGroup::change_group(slider->parent_button_group);
	}

	slider->scroll_speed *= pow(0.01f, _d);
	if ((slider->scroll_speed * slider->scroll_speed) < 0.05f) { slider->scroll_speed = 0.0f; }

	
	slider->current_value_percent = (slider->current_value - slider->min_value) / total_value;
	

}



//void EDataActionCollection::action_change_style(Entity* _entity, ECustomData* _custom_data, float _d)
//{
//	//cast to button entity
//	EntityButton*	target_button = ((EntityButton*)_entity);
//
//	//get "slider" sprite
//	ESprite*		target_sprite = target_button->get_sprite_from_entity(0, 0, 0);
//
//	if (target_sprite != nullptr)
//	{													
//		target_sprite->set_texture_gabarite
//		(
//			target_button->			//button, which change style
//			parent_button_group->	//group, which contain this button
//			selected_style->		//style, used by group
//			slider_bg->				//"brick style" for sliders
//			main_texture,			//texture from "brick style"
//			nullptr,
//			nullptr
//		);
//	}									
//
//}

void EDataActionCollection::action_highlight_button_if_overlap(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if
	(
		(!static_cast<EntityButton*>(_entity)->parent_button_group->group_is_suppressed)
		&&
		(
			(EButtonGroup::focused_button_group == ((EntityButton*)_entity)->parent_button_group)
			&&
			(((EntityButton*)_entity)->button_gabarite->overlapped_by_mouse())
		)
		&&
		(
			(static_cast<EntityButton*>(_entity)->suppressor == nullptr)
			||
			(*static_cast<EntityButton*>(_entity)->suppressor)
		)
		//||
		//(((EntityButton*)_entity)->button_gabarite->have_phantom_translation)
		//||
		//(((EntityButton*)_entity)->have_phantom_draw)
	)
	{
		//NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.15f);
		//NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.15f);
		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			((EntityButton*)_entity)->button_gabarite->world_position_x,
			((EntityButton*)_entity)->button_gabarite->world_position_y,

			((EntityButton*)_entity)->button_gabarite->size_x,
			((EntityButton*)_entity)->button_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel

		);

	}
}

void EDataActionCollection::action_select_this_style(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EGUIStyle::active_style = ((EntityButton*)_entity)->parent_button_group->selected_style;
	
	for (EWindow* window : EWindow::window_list)
	{
		

		for (EButtonGroup* group : window->button_group_list)
		{
			EButtonGroup::recursive_change_style(group, ((EntityButton*)_entity)->parent_button_group->selected_style);
		}

		window->window_need_refresh = true;
	}
}

void EDataActionCollection::action_close_root_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup* _group = ((EntityButton*)_entity)->parent_button_group;

	if
	(
		(_group != nullptr)
		&&
		(_group->root_group != nullptr)
	)
	{
		_group->root_group->close_this_group();

		EClickableArea::active_clickable_region = nullptr;

		for (group_close_action aoc : _group->root_group->actions_on_close)
		{
			aoc(_group->root_group);
		}

		//for (ECustomData* dt:_group->region_gabarite
		//if (EClickableArea::active_clickable_region == *(((EntityButton*)_entity)->parent_button_group)
	}
}

void EDataActionCollection::action_delete_entity(Entity* _entity, ECustomData* _custom_data, float _d)
{
	_entity->entity_need_remove = true;

	EInputCore::logger_simple_info("try mark as removed");
}

void EDataActionCollection::action_switch_description(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (((EntityButton*)_entity)->button_gabarite->overlapped_by_mouse())
	{
		_custom_data->disable_custom_data_draw = false;
	}
	else
	{
		_custom_data->disable_custom_data_draw = true;
	}

}

void EDataActionCollection::action_update_radial_button(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//*_custom_data->get_sprite_by_id(0, 0, 1, 0)->offset_x = (rand() % 100) * 1.0f;
	//_entity->

	EDataContainerRadialButton* data_container = (EDataContainerRadialButton*)_custom_data->data_container;
	void* d_pointer = data_container->value_pointer;



	//if (EClickableArea::active_clickable_region != nullptr)
	//{*EClickableArea::active_clickable_region->region_gabarite->size_x += 10.0f * _d;}






	if
		(
			(d_pointer != nullptr)
			&&//button pressed or first draw
			(
				(((EntityButton*)_entity)->force_draw)
				||
				(
					(EInputCore::MOUSE_BUTTON_LEFT)
					&&
					(EClickableArea::active_clickable_region == _custom_data->clickable_area_list.at(0))
					)
				)
			)
	{
		float size = ((EntityButton*)_entity)->button_gabarite->size_y;
		float value = 0.0f;
		float shift_multiplier = 1.0f;
		float direction_x = 1.0f;

		ESprite* radial_sprite = _custom_data->get_sprite_by_id(0, 0, 0, 0);
		ESprite* dot_sprite = _custom_data->get_sprite_by_id(0, 0, 1, 0);

		if (EInputCore::MOUSE_SPEED_X < 0.0f) { direction_x = -1.0f; }

		if
			(
				(EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
				||
				(EInputCore::key_pressed(GLFW_KEY_RIGHT_SHIFT))
				)
		{
			shift_multiplier = 0.1f;
		}

		((EntityButton*)_entity)->force_draw = false;

		if (data_container->stored_type == StoredPointerType::STORED_TYPE_FLOAT)
		{
			//if (EInputCore::MOUSE_POSITION_X <= *radial_sprite->world_position_x + size / 2.0f)
			//{*(float*)(d_pointer) += (EInputCore::MOUSE_SPEED_Y) * 0.002f;}
			//else
			//{*(float*)(d_pointer) -= (EInputCore::MOUSE_SPEED_Y) * 0.002f;}

			//if (EInputCore::MOUSE_POSITION_Y <= *radial_sprite->world_position_y + size / 2.0f)
			//{*(float*)(d_pointer) -= (EInputCore::MOUSE_SPEED_X) * 0.002f;}
			//else
			//{*(float*)(d_pointer) += (EInputCore::MOUSE_SPEED_X) * 0.002f;}

			*(float*)(d_pointer) += pow(EInputCore::MOUSE_SPEED_X, 2) * direction_x * 0.001f * shift_multiplier;

			*(float*)(d_pointer) = min(*(float*)(d_pointer), data_container->max_value);
			*(float*)(d_pointer) = max(*(float*)(d_pointer), data_container->min_value);

			dot_sprite->offset_x
				=
				size / 2.0f
				-
				dot_sprite->size_x / 2.0f
				+
				sin(*(float*)(d_pointer) * 6.28f * 0.8f + 0.628f) * (size / 2.0f - 8.0f);




			dot_sprite->offset_y
				=
				size / 2.0f
				-
				dot_sprite->size_x / 2.0f
				+
				cos(*(float*)(d_pointer) * 6.28f * 0.8f + 0.628f) * (size / 2.0f - 8.0f);

			_custom_data->clickable_area_list[0]->text_area->change_text(data_container->text + "\\n" + std::to_string(*(float*)(d_pointer)));

		}


		_entity->set_world_positions(_entity->world_position_x, _entity->world_position_y, _entity->world_position_z);
		_entity->generate_vertex_buffer_for_all_sprite_layers();
	}




}

void EDataActionCollection::action_type_search_data_entity_text(ETextArea* _text_area)
{
	if ((_text_area != nullptr) && (_text_area->get_root_group() != nullptr))
	{
		EDataContainer_Group_DataEntitiesSearch* data_container = (EDataContainer_Group_DataEntitiesSearch*)_text_area->get_root_group()->data_container;
		
		data_container->pointer_to_group_with_data_entities->scroll_y = 0.0f;
		static_cast<EntityButtonVerticalSlider*>(data_container->pointer_to_group_with_data_entities->slider)->current_value = 0.0f;
		static_cast<EntityButtonVerticalSlider*>(data_container->pointer_to_group_with_data_entities->slider)->current_value_percent = 0.0f;

		//EClickableArea::active_clickable_region = nullptr;

		if
			(
				(data_container != nullptr)
				&&
				(data_container->pointer_to_group_with_data_entities != nullptr)
				&&
				(data_container->target_rule != nullptr)
			)
		{
			//data_container->pointer_to_group_with_data_entities->scroll_y = 0.0f;

			for (EntityButton* but : data_container->pointer_to_group_with_data_entities->workspace_button_list)
			{
				EDataEntity* target_data_entity = but->pointer_to_data_entity;
				bool matched = false;

				matched = EFilterRule::matched_by_filter_rule(target_data_entity, data_container->target_rule, _text_area->original_text);

				if (matched)
				{ but->button_hidden_by_search = false; }
				else
				{
					but->button_hidden_by_search = true;
					but->destroy_attached_description();
				}
			}

			//EButtonGroup::refresh_button_group(data_container->pointer_to_group_with_data_entities->root_group);
			data_container->pointer_to_group_with_data_entities->root_group->need_refresh = true;;

		}
		else
		{
			if
				(data_container == nullptr) {
				EInputCore::logger_simple_error("data container is NULL!");
			}
			else if
				(data_container->pointer_to_group_with_data_entities == nullptr) {
				EInputCore::logger_simple_error("target button group is NULL!");
			}
			else if
				(data_container->target_rule == nullptr) {
				EInputCore::logger_simple_error("filter rule is NULL!");
			}
		}

		data_container->pointer_to_add_as_item_button->description_container->replacer_list.clear();
		data_container->pointer_to_add_as_item_button->description_container->replacer_list.push_back(EStringReplacer("%a", _text_area->original_text));
	}
	else
	{
		if (_text_area == nullptr) { EInputCore::logger_simple_error("text area is NULL!"); }
		else
			if (_text_area->get_root_group() == nullptr) { EInputCore::logger_simple_error("root group is NULL!"); }
	}
}

void EDataActionCollection::action_type_text_multiblock_searcher(ETextArea* _text_area)
{
	if (_text_area->parent_entity_for_text_area != nullptr)
	{
		auto		multisearch_data_container = static_cast<EntityButtonMultiSearch*>(_text_area->parent_entity_for_text_area);
		std::string	inputed_text = _text_area->original_text;

		bool match = false;

		//std::string inputed_text = EStringUtils::to_lower(target_text);

		//try search any text field with suitable text
		//for every group in multisearch vector
		for (EButtonGroup* button_group : multisearch_data_container->target_group_list)
		{
			//for every workcspace button in group
			for (EntityButton* but : button_group->workspace_button_list)
			{
				match = false;

				//every clickable region
				for (ECustomData* c_data : but->custom_data_list)
					for (EClickableArea* c_area : c_data->clickable_area_list)
						if (c_area->text_area != nullptr)
						{
							//stored text (inputed on field)
							if (EStringUtils::A_contains_B_ignore_case(c_area->text_area->original_text, inputed_text))
							{
								match = true;
							}

							//search on localisations text
							for (int i = 0; i < NSW_languages_count; i++)
							{
								if (EStringUtils::A_contains_B_ignore_case(c_area->text_area->localisation_text.localisations[i], inputed_text))
								{
									match = true;
								}
							}

							//base name
							if (EStringUtils::A_contains_B_ignore_case(c_area->text_area->localisation_text.base_name, inputed_text))
							{
								match = true;
							}
						}


				//type any search
				if (inputed_text != "")
				{
					//result
					switch (but->button_search_mode)
					{
					case ButtonSearchMode::DEFAULT:
					{
						but->button_hidden_by_search = !match;

						//if (!match)
						//{but->destroy_attached_description();}

						break;
					}

					case ButtonSearchMode::ALWAYS_HIDDEN:
					{
						but->button_hidden_by_search = true;

						break;
					}


					case ButtonSearchMode::ALWAY_SHOW:
					{
						but->button_hidden_by_search = false;

						break;
					}
					}
				}
				else
				{
					but->button_hidden_by_search = false;
				}

				//button_group->scroll_y = 0.0f;

			}

			//EButtonGroup::change_group(button_group);
			button_group->need_change = true;
		}
	}
}

void EDataActionCollection::action_deactive_text_area(ETextArea* _text_area)
{
	EInputCore::logger_simple_info("deactivated");
	_text_area->deactivate_this_text_area();
	_text_area->can_be_edited = false;
	
}

void EDataActionCollection::action_change_localisation_for_color_button(ETextArea* _text_area)
{
	if ((_text_area != nullptr) && (_text_area->parent_entity_for_text_area != nullptr))
	{
		EntityButtonColorButton*
		color_button = static_cast<EntityButtonColorButton*>(_text_area->parent_entity_for_text_area);

		color_button->parent_color_collection->localised_name = ELocalisationText::generate_localization_with_base_name(_text_area->original_text);


	}
	else
	{
		EInputCore::logger_simple_error("text_area or parent for text area is NULL!");
	}


}


std::vector<EFilterRule*> EFilterRule::registered_global_filter_rules(RegisteredFilterRules::_RDEF_LAST_ELEMENT_);
std::vector<EFilterRule*> EFilterRule::registered_filter_rules_for_list;



void EDataActionCollection::action_open_color_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//if (_custom_data->data_container != nullptr)
	{
		

		EntityButtonColorButton*			clicked_button			= static_cast<EntityButtonColorButton*>(_entity);
		EDataContainer_Group_ColorEditor*	group_data				= static_cast<EDataContainer_Group_ColorEditor*>(EButtonGroup::color_editor_group->data_container);
		EntityButtonColorButton*			target_button_for_group	= group_data->target_color_button;

		//clicked_button->parent_button_group->selected_button = clicked_button;
		clicked_button->parent_button_group->select_this_button(clicked_button);

		//set target button to button group
		if (clicked_button->selected_mode == ColorButtonMode::CBM_OPEN_WINDOW)
		{
			group_data->pointer_to_color_collection_sector->selected_button = nullptr;
			group_data->target_color_button = clicked_button;

			//if (group_data->pointer_to_color_collection_sector != nullptr)
			//	for (EntityButton* but : group_data->pointer_to_color_collection_sector->workspace_button_list)
			//	{
			//		//color collection on color editor								button which open editor
			//		if (static_cast<EntityButtonColorButton*>(but)->stored_color == clicked_button->stored_color)
			//		{
			//			group_data->pointer_to_color_collection_sector->selected_button = but;
			//			break;
			//		}
			//	}
			//else
			//{
			//	EInputCore::logger_simple_error("pointer to color group is null!");
			//}

			target_button_for_group = group_data->target_color_button;
			group_data->work_color = target_button_for_group->stored_color;

			EButtonGroup::color_editor_group->activate_move_to_foreground_and_center();
		}

		//color data container from target button
		//if (group_data->target_data_container_with_color != nullptr)
		//{
			//master_color = group_data->target_data_container_with_color->stored_color;
		//}



		//set new color to master_button
		if ((clicked_button->selected_mode == ColorButtonMode::CBM_SELECT_COLOR) && (target_button_for_group->stored_color != nullptr))
		{
			if
			(
				(
					(EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
					||
					(EInputCore::key_pressed(GLFW_KEY_RIGHT_SHIFT))
				)
				&&
				(false)
			)
			{
				//if color not from collection, remove personal color
				if (!target_button_for_group->stored_color->is_from_collection)
				{
					target_button_for_group->stored_color->is_from_collection = true;
					if (!disable_deleting) { delete target_button_for_group->stored_color; }
				}

				//pointer to this color already exist in color collection pointers list?
				bool pointer_to_color_already_exist = false;
				for (HSVRGBAColor* HRA_color : clicked_button->parent_color_collection->pointers_to_this_collection)
				{
					if (HRA_color == target_button_for_group->stored_color) { pointer_to_color_already_exist = true; break; }
				}

				//add this color to pointer list
				if (!pointer_to_color_already_exist)
				{ clicked_button->parent_color_collection->pointers_to_this_collection.push_back(target_button_for_group->stored_color); }

				target_button_for_group->stored_color = clicked_button->stored_color;

				group_data->pointer_to_color_collection_sector->selected_button = static_cast<EntityButton*>(_entity);
				group_data->work_color = clicked_button->stored_color;
			}
			else
			{
				//if color from collection, create personal color
				if (target_button_for_group != nullptr)
				{
					if (target_button_for_group->stored_color->is_from_collection)
					{
						target_button_for_group->stored_color = new HSVRGBAColor();
						target_button_for_group->stored_color->is_from_collection = false;
					}

					target_button_for_group->stored_color->set_color(clicked_button->stored_color);
					//button_data->stored_color->set_color(button_data->stored_color);

					group_data->pointer_to_color_collection_sector->selected_button = nullptr;

					group_data->work_color = target_button_for_group->stored_color;
				}
			}
		}

		//set work color from button


		group_data->crosshair_slider_data_container->target_pointer_x = &group_data->work_color->h;
		group_data->crosshair_slider_data_container->target_pointer_y = &group_data->work_color->s;

		group_data->slider_data_value_container->pointer_to_value = &group_data->work_color->v;
		group_data->slider_data_alpha_container->pointer_to_value = &group_data->work_color->a;



	}
}

void EDataActionCollection::action_add_item_to_group_receiver(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EInputCore::logger_simple_info("try add new button");

	EButtonGroup* parent_group = ((EntityButton*)_entity)->parent_button_group;
	EButtonGroup* root_group = parent_group->root_group;
	EDataContainer_Group_DataEntitiesSearch* data = (EDataContainer_Group_DataEntitiesSearch*)root_group->data_container;
	EButtonGroup* receiver = data->pointer_to_group_item_receiver;
	EDataContainer_DataEntityHolder* data_entity_holder = (EDataContainer_DataEntityHolder*)_custom_data->data_container;

	EntityButton* jc_button = EntityButton::create_item_button
	(
		new ERegionGabarite(45.0f, 45.0f),
		receiver,
		data_entity_holder->stored_data_entity
	);

	receiver->add_button_to_working_group(jc_button);
	//receiver->button_list.clear();
	//EButtonGroup::refresh_button_group(receiver->root_group);
	receiver->root_group->need_refresh = true;
}


void EDataActionCollection::action_update_crosshair_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EDataContainer_CrosshairSlider* data = static_cast<EDataContainer_CrosshairSlider*>(_custom_data->data_container);

	float value = (*data->target_pointer_x) / data->max_x;
	value = max(value, 0.0f);
	value = min(value, 1.0f);
	data->current_value_x = value;

	value = (*data->target_pointer_y) / data->max_y;
	value = max(value, 0.0f);
	value = min(value, 1.0f);
	data->current_value_y = value;

	if
		(
			//(((EntityButton*)_entity)->force_draw)
			//||
			(
				(EInputCore::MOUSE_BUTTON_LEFT)
				&&
				(EClickableArea::active_clickable_region == _custom_data->clickable_area_list.at(0))
				)
			)
	{
		((EntityButton*)_entity)->force_draw = false;

		ERegionGabarite* gab = _custom_data->clickable_area_list[0]->region_gabarite;


		float value = (EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom - gab->world_position_x) / gab->size_x;
		value = max(value, 0.0f);
		value = min(value, 1.0f);

		data->current_value_x = value;
		*data->target_pointer_x = value * data->max_x;



		value = (EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom - gab->world_position_y) / gab->size_y;
		value = max(value, 0.0f);
		value = min(value, 1.0f);
		*data->target_pointer_y = value * data->max_y;

		static_cast<EDataContainer_CrosshairSlider*>(_custom_data->data_container)->current_value_y = value;

	}

}

void EDataActionCollection::action_draw_crosshair_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_WHITE, 1.00f);
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		((EntityButton*)_entity)->button_gabarite->world_position_x + ((EntityButton*)_entity)->button_gabarite->size_x * ((EDataContainer_CrosshairSlider*)_custom_data->data_container)->current_value_x,
		((EntityButton*)_entity)->button_gabarite->world_position_y,

		1.0f,
		((EntityButton*)_entity)->button_gabarite->size_y,

		NS_DefaultGabarites::texture_gabarite_white_pixel
	);


	//___
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		((EntityButton*)_entity)->button_gabarite->world_position_x,
		((EntityButton*)_entity)->button_gabarite->world_position_y + ((EntityButton*)_entity)->button_gabarite->size_y * ((EDataContainer_CrosshairSlider*)_custom_data->data_container)->current_value_y,

		((EntityButton*)_entity)->button_gabarite->size_x,
		1.0f,

		NS_DefaultGabarites::texture_gabarite_white_pixel
	);

	NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLACK, 1.00f);
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		((EntityButton*)_entity)->button_gabarite->world_position_x + ((EntityButton*)_entity)->button_gabarite->size_x * ((EDataContainer_CrosshairSlider*)_custom_data->data_container)->current_value_x,
		((EntityButton*)_entity)->button_gabarite->world_position_y + ((EntityButton*)_entity)->button_gabarite->size_y * ((EDataContainer_CrosshairSlider*)_custom_data->data_container)->current_value_y - 2.0f,

		1.0f,
		5.0f,

		NS_DefaultGabarites::texture_gabarite_white_pixel
	);


	//___
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		((EntityButton*)_entity)->button_gabarite->world_position_x + ((EntityButton*)_entity)->button_gabarite->size_x * ((EDataContainer_CrosshairSlider*)_custom_data->data_container)->current_value_x - 2.0f,
		((EntityButton*)_entity)->button_gabarite->world_position_y + ((EntityButton*)_entity)->button_gabarite->size_y * ((EDataContainer_CrosshairSlider*)_custom_data->data_container)->current_value_y,

		5.0f,
		1.0f,

		NS_DefaultGabarites::texture_gabarite_white_pixel
	);
}

void EDataActionCollection::action_update_horizontal_named_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EDataContainer_VerticalNamedSlider*
	data = static_cast<EDataContainer_VerticalNamedSlider*>(_custom_data->data_container);

	float
	original_slider_value = 0.0f;

	if (data->pointer_to_value != nullptr)
	{
		if ((data->pointer_to_digit_text_area != nullptr) && (data->pointer_to_digit_text_area->text_area_active))
		{
			*data->pointer_to_value = EStringUtils::safe_convert_string_to_number
			(
				data->pointer_to_digit_text_area->original_text,
				data->min_value,
				data->max_value
			);
		}
		
		if (*data->pointer_to_value <= data->min_value)
		{
			original_slider_value = 0.0f;
		}
		else
		if (*data->pointer_to_value >= data->max_value)
		{
			original_slider_value = 1.0f;
		}
		else
			if (*data->pointer_to_value < data->mid_value)
			{
				original_slider_value = (*data->pointer_to_value - data->min_value) / (data->mid_value - data->min_value);
				original_slider_value *= 0.5f;
			}
			else
				if (*data->pointer_to_value >= data->mid_value)
				{	
					//				(1.0						-	1.0)			/	(10.0f			-		1.0)
					//				0.0												/	(9.0)
					original_slider_value = (*data->pointer_to_value - data->mid_value) / (data->max_value - data->mid_value);
					//original_value -= 0.5f;
					//original_value *= 2.0f;
					original_slider_value *= 0.5f;
					original_slider_value += 0.5f;

					//original_value = 0.5f;


				}


		{
			if (original_slider_value != data->current_slide_value)
			{
				data->current_slide_value = std::clamp(original_slider_value, 0.0f, 1.0f);

				float result_value = 0.0f;
				if (data->current_slide_value < 0.5)
				{
					result_value
						=
						(1.0f - data->current_slide_value * 2.0f) * data->min_value
						+
						data->current_slide_value / 0.5f * data->mid_value;
				}
				else
				{
					result_value
						=
						(1.0f - (data->current_slide_value - 0.5f) * 2.0f) * data->mid_value
						+
						(data->current_slide_value - 0.5f) * 2.0f * data->max_value;
				}

				if ((data->pointer_to_digit_text_area != nullptr) && (!data->pointer_to_digit_text_area->text_area_active))
				{
					if (data->rounded_numbers)
					{
						data->pointer_to_digit_text_area->change_text(std::to_string((int)round(result_value)));
					}
					else
					{
						data->pointer_to_digit_text_area->change_text(Helper::float_to_string_with_precision(result_value, 100.0f));
					}
				}
			}
		}
	}


	if
		(
			(EInputCore::MOUSE_BUTTON_LEFT)
			&&
			(EClickableArea::active_clickable_region == _custom_data->clickable_area_list.at(0))
			//&&
			//(EInputCore::MOUSE_SPEED_X != 0.0)
		)
	{
		if
			(
				(EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
				||
				(EInputCore::key_pressed(GLFW_KEY_RIGHT_SHIFT))
				||
				(data->force_shift)
			)
		{
			data->current_slide_value += (EInputCore::MOUSE_SPEED_X / NS_EGraphicCore::current_zoom * 0.1f) / data->operable_area_size_x;
		}
		else
		{
			data->current_slide_value
			=
			(
				EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom
				-
				data->pointer_to_brick_line_sprite_layer->world_position_x
				-
				33.0f
				-
				data->slider_style->brick_style[BrickStyleID::ROUND_SLIDER].main_texture->size_x_in_pixels / 2.0f
			)/data->operable_area_size_x;
		}

		data->current_slide_value = max(data->current_slide_value, 0.0f);
		data->current_slide_value = min(data->current_slide_value, 1.0f);

		float result_value = 0.0f;

		if (data->current_slide_value < 0.5)
		{
			result_value
			=
			(1.0f - data->current_slide_value * 2.0f)	* data->min_value
			+ 
			data->current_slide_value / 0.5f			* data->mid_value;
		}
		else
		{
			result_value
			=
			(1.0f - (data->current_slide_value - 0.5f) * 2.0f)	* data->mid_value 
			+
			(data->current_slide_value - 0.5f) * 2.0f				* data->max_value;
		}

		//change text to [stored_text] + slider value * max_value. Example: "Gloss: 0.75"

		//SET TARGET VALUE
		if (data->pointer_to_value != nullptr)
		{
			*data->pointer_to_value = result_value;
		}

		//ADDITIONAL ACTIONS ON SLIDE
		if (data->additional_action_on_slide != nullptr)
		{
			data->additional_action_on_slide(_entity, _custom_data, _d);
		}

		//CHANGE HEAD TEXT
		if (data->pointer_to_text_area != nullptr)
		{
			data->pointer_to_text_area->change_text(data->stored_text);
		}

		//CHANGE DIGIT TEXT
		if (data->pointer_to_digit_text_area != nullptr)
		{
			if (data->rounded_numbers)
			{
				data->pointer_to_digit_text_area->change_text(std::to_string((int)round(result_value)));
			}
			else
			{
				data->pointer_to_digit_text_area->change_text(Helper::float_to_string_with_precision(result_value, 100.0f));
			}
		}
		//EInputCore::logger_param("Value", data->current_value);
	}



}

void EDataActionCollection::action_draw_horizontal_named_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EDataContainer_VerticalNamedSlider* data = static_cast<EDataContainer_VerticalNamedSlider*>(_custom_data->data_container);
	EntityButton* button = static_cast<EntityButton*>(_entity);
	if (data->slider_style != nullptr)
	{

		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_YELLOW, 0.16f);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			data->pointer_to_brick_line_sprite_layer->world_position_x + 33.0f,
			data->pointer_to_brick_line_sprite_layer->world_position_y + 3.0f,

			data->operable_area_size_x * data->current_slide_value + data->slider_style->brick_style[BrickStyleID::ROUND_SLIDER].main_texture->size_x_in_pixels / 2.0f,
			data->slider_style->brick_style[BrickStyleID::ROUND_SLIDER].main_texture->size_y_in_pixels,


			NS_DefaultGabarites::texture_gabarite_white_pixel
		);

		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_real_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,
			data->pointer_to_brick_line_sprite_layer->world_position_x + data->operable_area_size_x * data->current_slide_value + 33.0f,
			data->pointer_to_brick_line_sprite_layer->world_position_y + 3.0f,
			data->slider_style->brick_style[BrickStyleID::ROUND_SLIDER].main_texture
		);



	}
}

void EDataActionCollection::action_draw_vertical_named_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonVerticalSlider* slider = static_cast<EntityButtonVerticalSlider*>(_entity);

	if
		(
			(slider->slider_inactive != nullptr)
			&&
			(slider->slider_inactive->main_texture != nullptr)
			&&
			(slider->slider_inactive->normal_map_texture != nullptr)
			&&
			(slider->slider_inactive->gloss_map_texture != nullptr)
		)
	{


		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::pbr_batcher, 1);

		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
		if (!slider->is_rotator)
		{
			NS_ERenderCollection::add_data_to_vertex_buffer_texture_gabarite_PBR
			(
				NS_EGraphicCore::pbr_batcher->vertex_buffer,
				NS_EGraphicCore::pbr_batcher->last_vertice_buffer_index,

				slider->world_position_x,
				slider->world_position_y + slider->workspace_height * slider->current_value_percent,

				slider->slider_inactive->main_texture->size_x_in_pixels,
				slider->slider_inactive->main_texture->size_y_in_pixels,

				slider->slider_inactive->main_texture,
				slider->slider_inactive->gloss_map_texture,
				slider->slider_inactive->normal_map_texture
			);
		}
		else
		{
			float subdegree = 0.0f;
			if (slider->slider_inactive->main_texture->size_y_in_pixels >= slider->slider_inactive->main_texture->size_x_in_pixels)
			{
				subdegree = slider->slider_inactive->main_texture->size_x_in_pixels / slider->slider_inactive->main_texture->size_y_in_pixels * 45.0f;
			}
			else
			{
				subdegree = 90.0f - slider->slider_inactive->main_texture->size_y_in_pixels / slider->slider_inactive->main_texture->size_x_in_pixels * 45.0f;
			}

			subdegree = 45.0f;

			NS_ERenderCollection::add_data_to_vertex_buffer_rotated_square_PBR
			(
				NS_EGraphicCore::pbr_batcher->vertex_buffer,
				NS_EGraphicCore::pbr_batcher->last_vertice_buffer_index,

				slider->world_position_x,
				slider->world_position_y,

				slider->brick_style_active_slider->main_texture->size_x_in_pixels,
				slider->brick_style_active_slider->main_texture->size_y_in_pixels,

				slider->degree,
				subdegree,

				slider->brick_style_active_slider->main_texture,
				slider->brick_style_active_slider->gloss_map_texture,
				slider->brick_style_active_slider->normal_map_texture
			);
		}
	}
	else
	{
		//EInputCore::logger_simple_error("NULL textures on slider head!");
	}
}

void EDataActionCollection::action_convert_HSV_to_RGB(EButtonGroup* _group)
{
	//EInputCore::logger_simple_info("?");
	Helper::hsv2rgb(static_cast<EDataContainer_Group_ColorEditor*>(_group->data_container)->work_color);
}

void EDataActionCollection::action_forcibly_redraw_specific_buttons(EButtonGroup* _group)
{
	EDataContainer_Group_ColorEditor*
	data = static_cast<EDataContainer_Group_ColorEditor*>(_group->data_container);

	if (data->target_color_button != nullptr)
	{
		EntityButtonColorButton*
		color_button = static_cast<EntityButtonColorButton*>(data->target_color_button);


		for (EntityButton* but : color_button->list_of_forcibly_redrawing_buttons)
		{
			but->have_phantom_draw = true;
		}
	}
}

void EDataActionCollection::action_set_new_color_to_button(EButtonGroup* _group)
{
	EInputCore::logger_simple_info("@");
	static_cast<EDataContainer_Group_ColorEditor*>(_group->root_group->data_container)->target_color_button->stored_color
		=
		static_cast<EDataContainer_Group_ColorEditor*>(_group->root_group->data_container)->work_color;
}

void EDataActionCollection::action_resize_to_full_window(EButtonGroup* _group)
{
	_group->region_gabarite->size_x = (NS_EGraphicCore::SCREEN_WIDTH / NS_EGraphicCore::current_zoom);
	_group->region_gabarite->size_y = (NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom);

	_group->base_width = (NS_EGraphicCore::SCREEN_WIDTH / NS_EGraphicCore::current_zoom);
	_group->base_height = (NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom);

	//if (EButtonGroup::header_line != nullptr)
	//{
	//	_group->base_height -=				EButtonGroup::header_line->base_height;
	//	_group->region_gabarite->size_y -=	EButtonGroup::header_line->base_height;
	//}

	//EButtonGroup::refresh_button_group(_group);
	_group->need_refresh = true;
	//EInputCore::logger_simple_info("group resized");

	//EButtonGroup::change_style(_group, _group->selected_style);
	////EButtonGroup::apply_style_to_button_group(_group, _group->selected_style);
	//EButtonGroup::refresh_button_group(_group);
}

void EDataActionCollection::action_resize_to_full_window_only_x(EButtonGroup* _group)
{

	_group->region_gabarite->size_x = ((NS_EGraphicCore::SCREEN_WIDTH) / NS_EGraphicCore::current_zoom);
	_group->base_width = _group->region_gabarite->size_x;

	_group->recursive_expand_to_workspace_size();


	_group->region_gabarite->offset_y = NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom - _group->region_gabarite->size_y;
	
	//EButtonGroup::change_group(_group);
	_group->need_change = true;
	//EInputCore::logger_simple_info("group resized");

	//EButtonGroup::change_style(_group, _group->selected_style);
	////EButtonGroup::apply_style_to_button_group(_group, _group->selected_style);
	//EButtonGroup::refresh_button_group(_group);
}

void EDataActionCollection::action_draw_boolean_switcher(Entity* _entity, ECustomData* _custom_data, float _d)
{
	auto data_container = static_cast <EDataContainer_Button_BoolSwitcher*> (_custom_data->data_container);
	bool highlight = *data_container->target_value;
	if (data_container->reverse_mode) { highlight = !highlight; }


		NS_EGraphicCore::set_active_color(1.0f, 1.0f, 1.0f, 1.0f);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			((EntityButton*)_entity)->button_gabarite->world_position_x,
			((EntityButton*)_entity)->button_gabarite->world_position_y,

			((EntityButton*)_entity)->button_gabarite->size_y,
			((EntityButton*)_entity)->button_gabarite->size_y,

			(highlight) ? (data_container->texture_gabarite_on) : (data_container->texture_gabarite_off)
		);


}

void EDataActionCollection::action_draw_color_rectangle_for_group(EButtonGroup* _group)
{
	if ((_group != nullptr) && (_group->data_container != nullptr))
	{
		//EInputCore::logger_simple_info("?");
		EDataContainer_Group_ColorEditor* data = static_cast<EDataContainer_Group_ColorEditor*>(_group->data_container);
		NS_EGraphicCore::set_active_color
		(
			data->work_color->r,
			data->work_color->g,
			data->work_color->b,
			data->work_color->a
		);

		if (_group->batcher_for_default_draw->last_vertice_buffer_index + _group->batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { _group->batcher_for_default_draw->draw_call(); }
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			_group->batcher_for_default_draw->vertex_buffer,
			_group->batcher_for_default_draw->last_vertice_buffer_index,
			data->pointer_to_color_box_sector->region_gabarite->world_position_x + 0.0f,
			data->pointer_to_color_box_sector->region_gabarite->world_position_y + 0.0f,
			data->pointer_to_color_box_sector->region_gabarite->size_x - 0.0f,
			data->pointer_to_color_box_sector->region_gabarite->size_y - 0.0f,
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
	}
}

void EDataActionCollection::action_draw_stored_color_as_box(Entity* _entity, ECustomData* _custom_data, float _d)
{
	

	//if ((_custom_data != nullptr))
	{
		EntityButtonColorButton* data = static_cast<EntityButtonColorButton*>(_entity);
		EntityButton* button = static_cast<EntityButton*>(_entity);

		EBrickStyle* style = &button->parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG];

		float size_y = button->button_gabarite->size_y - style->offset_for_elements_bottom - style->offset_for_elements_up - 15.0f;

		if (data->stored_color != nullptr)
		{

			NS_EGraphicCore::set_active_color
			(
				data->stored_color->r,
				data->stored_color->g,
				data->stored_color->b,
				data->stored_color->a
			);

			ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);

			if (size_y > 12.0f)
			{
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
					NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

					button->button_gabarite->world_position_x + style->offset_for_elements_left + 1.0f,
					button->button_gabarite->world_position_y + style->offset_for_elements_bottom + 1.0f,

					button->button_gabarite->size_x - style->offset_for_elements_left - style->offset_for_elements_right - 2.0f,
					size_y - 2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}
			else
			{
				size_y += 15.0f;

				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
					NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

					button->button_gabarite->world_position_x + button->button_gabarite->size_x - style->offset_for_elements_right - size_y + 1.0f,
					button->button_gabarite->world_position_y + style->offset_for_elements_bottom + 1.0f,

					size_y - 2.0f,
					size_y - 2.0f,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}
		}

	}
}

void EDataActionCollection::action_active_text_area(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton* but = static_cast<EntityButton*>(_entity);

	if (but->main_text_area != nullptr)
	{
		but->main_text_area->can_be_edited = true;
		but->main_text_area->activate_this_text_area();
	}
}

void EDataActionCollection::action_delete_vertical_router_variants_group(EButtonGroup* _group)
{
	EButtonGroupRouterVariant* group_vertical_variant = static_cast<EButtonGroupRouterVariant*>(_group);

	group_vertical_variant->block_need_remove = true;
	group_vertical_variant->target_router_button->opened_router_group = nullptr;
}

void EDataActionCollection::action_transfer_pointer_to_color_data_container(Entity* _entity, ECustomData* _custom_data, float _d)
{
	static_cast<EDataContainer_Group_ColorEditor*>(EButtonGroup::color_editor_group->data_container)->target_color_button
	=
	static_cast<EntityButtonColorButton*>(_entity);
}

void EDataActionCollection::action_unbing_color(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup* parent_group = static_cast<EntityButton*>(_entity)->parent_button_group;
	EButtonGroup* root_group = parent_group->root_group;
	EDataContainer_Group_ColorEditor* group_data = static_cast<EDataContainer_Group_ColorEditor*>(root_group->data_container);
	EntityButtonColorButton* target_button_data = group_data->target_color_button;

	//get current color
	HSVRGBAColor* original_color = target_button_data->stored_color;

	//create non-binded color
	HSVRGBAColor* HRA_color = new HSVRGBAColor();
	HRA_color->set_color(original_color);//apply old color to non-binded
	HRA_color->is_from_collection = false;
	target_button_data->stored_color = HRA_color;

	group_data->crosshair_slider_data_container->target_pointer_x = &HRA_color->h;
	group_data->crosshair_slider_data_container->target_pointer_y = &HRA_color->s;

	group_data->slider_data_value_container->pointer_to_value = &HRA_color->v;
	group_data->slider_data_alpha_container->pointer_to_value = &HRA_color->a;

	group_data->work_color = HRA_color;






	//static_cast<EDataContainer_Button_StoreColor*>(_custom_data->data_container)->stored_color = HRA_color;

	//clear selected button, because new color is not belong to any collection
	if (parent_group != nullptr)
	{
		group_data->pointer_to_color_collection_sector->selected_button = nullptr;
	}

}
class EntityButtonColorButton;
void EDataActionCollection::action_create_new_color(Entity* _entity, ECustomData* _custom_data, float _d)
{

	EButtonGroup* parent_group = static_cast<EntityButton*>(_entity)->parent_button_group;
	EButtonGroup* root_group = parent_group->root_group;
	EDataContainer_Group_ColorEditor* group_data = static_cast<EDataContainer_Group_ColorEditor*>(root_group->data_container);
	EntityButtonColorButton* button_data = group_data->target_color_button;

	//get current color
	HSVRGBAColor* original_color = group_data->work_color;

	//create non-binded color
	HSVRGBAColor			HRA_color;
	HRA_color_collection*	HRA_collection = new HRA_color_collection();

	HRA_color.set_color(original_color);//apply old color to non-binded
	HRA_collection->target_color = HRA_color;

	//button_data->stored_color = &HRA_color;



	Helper::registered_color_list.push_back(HRA_collection);

	//group_data->crosshair_slider_data_container->target_pointer_x = &HRA_color.h;
	//group_data->crosshair_slider_data_container->target_pointer_y = &HRA_color.s;

	//group_data->slider_data_value_container->pointer_to_value = &HRA_color.v;
	//group_data->slider_data_alpha_container->pointer_to_value = &HRA_color.a;

	//group_data->work_color = &HRA_color;

	ELocalisationText l_text;
	l_text.localisations[NSW_localisation_EN] = "Color";
	l_text.localisations[NSW_localisation_RU] = "Цвет";

	HRA_collection->localised_name = l_text;

	EntityButtonColorButton* jc_button = EntityButton::create_named_color_button
	(
		//*color_collection->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

		new ERegionGabarite(150.0f, 38.0f),
		group_data->pointer_to_color_collection_sector,
		EFont::font_list[0],
		EGUIStyle::active_style,
		l_text,
		HRA_collection,
		&HRA_collection->target_color,
		ColorButtonMode::CBM_SELECT_COLOR
	);
	//Entity::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_button);
	group_data->pointer_to_color_collection_sector->add_button_to_working_group(jc_button);
	EButtonGroup::refresh_button_group(root_group);
	root_group->need_refresh = true;//

	//group_data->pointer_to_color_collection_group->selected_button = jc_button;



	//static_cast<EDataContainer_Button_StoreColor*>(_custom_data->data_container)->stored_color = HRA_color;
}

void EDataActionCollection::action_convert_HSV_to_RGB(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup* root = static_cast<EntityButton*>(_entity)->parent_button_group->root_group;

	if ((root != nullptr) && (root->data_container != nullptr) && (static_cast<EDataContainer_Group_ColorEditor*>(root->data_container)->work_color != nullptr))
	{
		Helper::hsv2rgb(static_cast<EDataContainer_Group_ColorEditor*>(root->data_container)->work_color);
	}
}

void EDataActionCollection::action_select_this_button(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (static_cast<EntityButton*>(_entity)->parent_button_group != nullptr)
	{
		static_cast<EntityButton*>(_entity)->parent_button_group->select_this_button(static_cast<EntityButton*>(_entity));
		//static_cast<EntityButton*>(_entity)->parent_button_group->selected_button = static_cast<EntityButton*>(_entity);
	}
	else
	{
		EInputCore::logger_simple_error("parent group is null!");
	}
}

void EDataActionCollection::action_force_resize_callback(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if
	(
		(EInputCore::MOUSE_BUTTON_LEFT)
		&&
		(EClickableArea::active_clickable_region == _custom_data->clickable_area_list.at(0))
	)
	{
		for (EWindow* w : EWindow::window_list)
		{
			NS_EGraphicCore::refresh_autosize_groups(w);
		}



		for (EWindow* window : EWindow::window_list)
			for (EButtonGroup* group : window->button_group_list)
			{
				EButtonGroup::refresh_button_group(group);

				//group->need_refresh = true;
				//group->group_phantom_redraw = true;
			}


	}
}

void EDataActionCollection::action_invoke_data_entity_group_action(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//EInputCore::logger_simple_info("wtf");
	if
	(
		(static_cast<EntityButton*>(_entity)->parent_button_group != nullptr)
		&&
		(static_cast<EntityButton*>(_entity)->parent_button_group->root_group != nullptr)
		&&
		(static_cast<EDataContainer_Group_DataEntitiesSearch*>(static_cast<EntityButton*>(_entity)->parent_button_group->root_group->data_container)->action_on_select_for_button != nullptr)
	)
	{
		//data container in root group							//cast to button
		static_cast<EDataContainer_Group_DataEntitiesSearch*>(static_cast<EntityButton*>(_entity)->parent_button_group->root_group->data_container)->
		action_on_select_for_button(_entity, _custom_data, _d);
	}
}

void EDataActionCollection::action_set_button_group_as_active(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (((EntityButtonButtonGroupActivator*)_entity)->target_group != nullptr)
	{
		//EDataContainer_Button_OpenButtonGroup* button_data = static_cast<EDataContainer_Button_OpenButtonGroup*>(_custom_data->data_container);
		((EntityButtonButtonGroupActivator*)_entity)->target_group->activate_move_to_foreground_and_center();
	}
	else
	{
		EInputCore::logger_simple_error("target group is NULL");
	}
}

void EDataActionCollection::action_switch_boolean_value(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (static_cast<EDataContainer_Button_BoolSwitcher*>(_custom_data->data_container)->target_value != nullptr)
	{
		*(static_cast<EDataContainer_Button_BoolSwitcher*>(_custom_data->data_container)->target_value)
			=
			!*(static_cast<EDataContainer_Button_BoolSwitcher*>(_custom_data->data_container)->target_value);
	}
}

void EDataActionCollection::action_rotate_variant(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EInputCore::logger_simple_info("call [action_rotate_variant]");
	EntityButtonVariantRouter* button_variant_router = (EntityButtonVariantRouter*)_entity;
	
	if (button_variant_router->rotate_variant_mode == RotateVariantMode::SELECT_NEXT)
	{
		//select next variant
		button_variant_router->selected_variant++;

		//full cycle passed, reset to start
		if (button_variant_router->selected_variant >= button_variant_router->router_variant_list.size())
		{
			button_variant_router->selected_variant = 0;
		}

		button_variant_router->select_variant(button_variant_router->selected_variant);
	}
	else
	if (button_variant_router->rotate_variant_mode == RotateVariantMode::OPEN_CHOOSE_WINDOW)
	{
		if (button_variant_router->opened_router_group == nullptr)
		{
			button_variant_router->opened_router_group = EButtonGroupRouterVariant::create_router_variant_button_group(button_variant_router->parent_button_group->root_group->parent_window, button_variant_router);
		}
	}

	if (button_variant_router->target_bool_value != nullptr)
	{
		*button_variant_router->target_bool_value = (bool)(button_variant_router->selected_variant);
	}

	if (button_variant_router->target_int_value != nullptr)
	{
		*button_variant_router->target_int_value = button_variant_router->selected_variant;
	}
}

void EDataActionCollection::action_select_rotate_variant_from_list(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonVariantRouterSelector*
	router_selector_button = static_cast<EntityButtonVariantRouterSelector*>(_entity);

	EButtonGroupRouterVariant*
	target_group = router_selector_button->parent_router_group;

	EntityButtonVariantRouter*
	target_button = target_group->target_router_button;



	target_button->select_variant(router_selector_button->id);
	target_group->block_need_remove = true;
	target_group->close_this_group();

	for (data_action_pointer dap : target_button->action_on_choose_variant_from_window)
	{
		dap(_entity, _custom_data, _d);
	}
}

void EDataActionCollection::action_invoke_stored_confirm_action(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonConfirmAction*
	confirm_button = static_cast<EntityButtonConfirmAction*>(_entity);

	if (confirm_button->stored_action != nullptr)
	{
		confirm_button->stored_action
		(
			(confirm_button->target_entity_button != nullptr)	? (confirm_button->target_entity_button)	: (_entity),
			(confirm_button->target_custom_data != nullptr)		? (confirm_button->target_custom_data)		: (_custom_data),
			_d
		);
	}
}

void EDataActionCollection::action_close_program(Entity* _entity, ECustomData* _custom_data, float _d)
{
	glfwSetWindowShouldClose(NS_EGraphicCore::main_window, 1);
	EInputCore::NSW_have_unsave_changes = false;

	//static_cast<EntityButtonFilterBlockTab*>(EWindowMain::header_line->pointer_to_bottom_tabs_section->selected_button)->unsave_changes
}

void EDataActionCollection::action_cancel_closing_program(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//EInputCore::logger_simple_info("action_cancel_closing_program");
	//static_cast<EntityButton*>(_entity)->parent_button_group->root_group->button_group_is_active = false;
	static_cast<EntityButton*>(_entity)->parent_button_group->root_group->close_this_group();

	glfwSetWindowShouldClose(NS_EGraphicCore::main_window, 0);
}

void EDataActionCollection::action_set_unsaved_changes(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EInputCore::NSW_have_unsave_changes = true;

}

void EDataActionCollection::action_open_url(Entity* _entity, ECustomData* _custom_data, float _d)
{
	ShellExecute(0, 0, static_cast<EntityButtonOpenURL*>(_entity)->stored_url.c_str(), 0, 0, SW_SHOW);
}

void EDataActionCollection::action_out_main_text_area(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (static_cast<EntityButton*>(_entity)->main_text_area != nullptr)
	{
		EInputCore::logger_param("text area: ", static_cast<EntityButton*>(_entity)->main_text_area->original_text);
	}
}

//void EDataActionCollection::action_active_filter_block(Entity* _entity, ECustomData* _custom_data, float _d)
//{
//	if (((EntityButtonButtonGroupActivator*)_entity)->target_group != nullptr)
//	{
//		((EntityButtonButtonGroupActivator*)_entity)->target_group->is_active = true;
//	}
//}




//void EDataActionCollection::action_type_text(Entity* _entity, ECustomData* _custom_data, float _d)
//{
//
//}

/*
bool EClickableRegion::overlapped_by_mouse(EClickableRegion* _region)
{
	return false;
}
*/

EClickableArea::EClickableArea()
{


}

EClickableArea::~EClickableArea()
{
	if (debug_deleting) { EInputCore::logger_simple_info("deleting clickable area"); }

	if (region_gabarite != nullptr)
	{
		(region_gabarite->pointers_to_this_object)--;

		if (debug_deleting) EInputCore::logger_param("pointers left", region_gabarite->pointers_to_this_object);

		if (region_gabarite->pointers_to_this_object <= 0)
		{
			if (!disable_deleting) { delete region_gabarite; }
			if (debug_deleting) EInputCore::logger_simple_success("deleting clickable area");
		}
	}

	if (text_area != nullptr)
	{
		if (!disable_deleting) { delete text_area; }
	}
}

bool EClickableArea::overlapped_by_mouse(EClickableArea* _region, float _offset_x, float _offset_y, float _zoom)
{
	if
		(
			(
				(_region != nullptr)
				&&
				(_region->parent_entity != nullptr)
				)
			&&
			(
				(EInputCore::MOUSE_POSITION_X >= ((double)_region->region_gabarite->world_position_x + (double)_offset_x) * _zoom)
				&&
				(EInputCore::MOUSE_POSITION_X <= ((double)_region->region_gabarite->world_position_x + (double)_region->region_gabarite->size_x + _offset_x) * _zoom)

				&&

				(EInputCore::MOUSE_POSITION_Y >= ((double)_region->region_gabarite->world_position_y + _offset_y) * _zoom)
				&&
				(EInputCore::MOUSE_POSITION_Y <= ((double)_region->region_gabarite->world_position_y + _region->region_gabarite->size_y + _offset_y) * _zoom)
				)
			)
	{
		return true;
	}

	return false;
}

bool EClickableArea::catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance)
{

	if
		(
			(EInputCore::MOUSE_POSITION_X >= (_x + _offset_x) * _zoom - _catch_distance)
			&&
			(EInputCore::MOUSE_POSITION_X <= (_x + _size_x + _offset_x + 2.0f) * _zoom + _catch_distance)

			&&

			(EInputCore::MOUSE_POSITION_Y >= (_y + _offset_y) * _zoom - _catch_distance)
			&&
			(EInputCore::MOUSE_POSITION_Y <= (_y + _size_y + _offset_y) * _zoom + _catch_distance)
			)
	{
		return true;
	}

	return false;
}

void EClickableArea::check_all_catches()
{
	//bool previvous_state = false;
	bool any_catch = false;

	if (!EInputCore::MOUSE_BUTTON_LEFT)
	{
		if (can_catch_side[ClickableRegionSides::CRS_SIDE_LEFT])
		{
			catched_side_left = catched_side_by_mouse
			(
				region_gabarite->world_position_x,
				region_gabarite->world_position_y,

				0.0f,
				region_gabarite->size_y,

				NS_EGraphicCore::current_offset_x,
				NS_EGraphicCore::current_offset_y,
				NS_EGraphicCore::current_zoom,

				5.0f
			);
		}
		else
		{
			catched_side_left = false;
		}



		if (can_catch_side[ClickableRegionSides::CRS_SIDE_RIGHT])
		{

			catched_side_right = catched_side_by_mouse
			(
				region_gabarite->world_position_x + region_gabarite->size_x,
				region_gabarite->world_position_y,

				0.0f,
				region_gabarite->size_y,

				NS_EGraphicCore::current_offset_x,
				NS_EGraphicCore::current_offset_y,
				NS_EGraphicCore::current_zoom,

				5.0f
			);
		}
		else
		{
			catched_side_right = false;
		}



		if (can_catch_side[ClickableRegionSides::CRS_SIDE_DOWN])
		{
			catched_side_down = catched_side_by_mouse
			(
				region_gabarite->world_position_x,
				region_gabarite->world_position_y,

				region_gabarite->size_x,
				0.0f,

				NS_EGraphicCore::current_offset_x,
				NS_EGraphicCore::current_offset_y,
				NS_EGraphicCore::current_zoom,

				5.0f
			);
		}
		else
		{
			catched_side_down = false;
		}


		if (can_catch_side[ClickableRegionSides::CRS_SIDE_UP])
		{
			catched_side_up = catched_side_by_mouse
			(
				region_gabarite->world_position_x,
				region_gabarite->world_position_y + region_gabarite->size_y,

				region_gabarite->size_x,
				0.0f,

				NS_EGraphicCore::current_offset_x,
				NS_EGraphicCore::current_offset_y,
				NS_EGraphicCore::current_zoom,

				5.0f
			);
		}
		else
		{
			catched_side_up = false;
		}

		if (can_catch_side[ClickableRegionSides::CRS_SIDE_MID])
		{
			catched_side_mid = catched_side_by_mouse
			(
				region_gabarite->world_position_x + region_gabarite->size_x / 2.0f,
				region_gabarite->world_position_y + region_gabarite->size_y / 2.0f,

				0.0f,
				0.0f,

				NS_EGraphicCore::current_offset_x,
				NS_EGraphicCore::current_offset_y,
				NS_EGraphicCore::current_zoom,

				7.0f
			);
		}
		else
		{
			catched_side_mid = false;
		}

		if ((can_catch_side[ClickableRegionSides::CRS_SIDE_BODY]) && (!any_catch))
		{
			catched_body = catched_side_by_mouse
			(
				region_gabarite->world_position_x,
				region_gabarite->world_position_y,

				region_gabarite->size_x,
				region_gabarite->size_y,

				NS_EGraphicCore::current_offset_x,
				NS_EGraphicCore::current_offset_y,
				NS_EGraphicCore::current_zoom,

				1.0f
			);
		}
		else
		{
			catched_body = false;
		}

		catch_offset_x = EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom - region_gabarite->world_position_x;
		catch_offset_y = EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom - region_gabarite->world_position_y;
	}
	else
	{

		if (catched_side_left)
		{
			region_gabarite->size_x -= EInputCore::MOUSE_SPEED_X;
			translate_clickable_region(EInputCore::MOUSE_SPEED_X, 0.0f, 0.0f, true);
		}

		if (catched_side_right)
		{
			region_gabarite->size_x += EInputCore::MOUSE_SPEED_X;
			redraw_text();
		}

		if (catched_side_down)
		{
			translate_clickable_region(0.0f, EInputCore::MOUSE_SPEED_Y, 0.0f, true);
			region_gabarite->size_y -= EInputCore::MOUSE_SPEED_Y;
		}

		if (catched_side_up)
		{
			region_gabarite->size_y += EInputCore::MOUSE_SPEED_Y;
			redraw_text();
		}

		if (catched_side_mid)
		{
			translate_clickable_region(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f, true);
		}

		if ((catched_side_left) || (catched_side_right) || (catched_side_up) || (catched_side_down) || (catched_side_mid))
		{


		}
	}



	if
		(
			(
				(catched_side_left)
				||
				(catched_side_right)
				||
				(catched_side_up)
				||
				(catched_side_down)
				||
				(catched_side_mid)
				||
				(catched_body)
			)
			&&
			(EInputCore::MOUSE_BUTTON_LEFT)
		)
	{
		//EClickableArea::active_clickable_region = this; 
	}
	else
	{
		//if (EClickableArea::active_clickable_region == this) { EClickableArea::active_clickable_region = nullptr; }
	}

}

void EClickableArea::translate_clickable_region(float _x, float _y, float _z, bool _move_offset)
{
	if (region_gabarite != nullptr)
	{
		if ((parent_group == nullptr) || (parent_group->region_gabarite != region_gabarite))
		//if (region_gabarite->pointers_to_this_object <= 1)
		{
			region_gabarite->world_position_x += _x;
			region_gabarite->world_position_y += _y;
			region_gabarite->world_position_z += _z;

			if (_move_offset)
			{
				region_gabarite->offset_x += _x;
				region_gabarite->offset_y += _y;
				region_gabarite->offset_z += _z;
			}
		}
	}

	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr) { s_layer->translate_sprite_layer(_x, _y, _z, false); }

	if (text_area != nullptr) { text_area->translate(_x, _y, 0.0f, false); }
}

EClickableArea* EClickableArea::create_default_clickable_region(ERegionGabarite* _gabarite, Entity* _parent_entity, ECustomData* _custom_data)
{
	EClickableArea* jc_clickable_area = new EClickableArea();

	ERegionGabarite::set_region_gabarite(&jc_clickable_area->region_gabarite, _gabarite);

	jc_clickable_area->parent_entity = _parent_entity;
	jc_clickable_area->parent_custom_data = _custom_data;

	jc_clickable_area->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	return jc_clickable_area;
}

EClickableArea* EClickableArea::create_default_clickable_region(ERegionGabarite* _gabarite, EButtonGroup* _parent_button_group)
{
	EClickableArea*
	jc_clickable_area = new EClickableArea();

	ERegionGabarite::set_region_gabarite(&jc_clickable_area->region_gabarite, _gabarite);

	jc_clickable_area->parent_group = _parent_button_group;

	jc_clickable_area->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	return jc_clickable_area;
}

void EClickableArea::update(float _d)
{
	//if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
	//if
	//(
	//	(EButtonGroup::focused_button_group_with_slider->region == this->region)
	//)
	{
		check_all_catches();
	}

	if ((debug_updating)&&(EInputCore::mouse_button_pressed_once(GLFW_MOUSE_BUTTON_LEFT)))
	{
		EInputCore::logger_simple_info("update clickable area");
	}

	if (EClickableArea::active_clickable_region == this)
	{
		hover_time += _d;
	}
	else
	{
		hover_time = 0.0f;
	}

	//if ((hover_time > 0.5f) && ())

	//left click
	{
	
		if 
		(
			(EInputCore::mouse_button_pressed_once(GLFW_MOUSE_BUTTON_LEFT))
			&&
			(EClickableArea::active_clickable_region == this)
		)
		{
			//EInputCore::logger_param("size of DAP", actions_on_click_list.size());

			for (data_action_pointer dap : actions_on_click_list)
				if
					(
						(dap != nullptr)
						&&
						(parent_entity != nullptr)
						//&&
						//(EButtonGroup::focused_button_group_mouse_unpressed == ((EntityButton*)parent_entity)->parent_button_group)
						//&&
						//(overlapped_by_mouse(this, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
						&&
						(EClickableArea::active_clickable_region == this)
					)
				{
					EInputCore::logger_simple_info("call [actions on click list]");
					dap(parent_entity, parent_custom_data, _d);
				}
				else
				{
					if (debug_updating)
					{
						if (EInputCore::mouse_button_pressed_once(GLFW_MOUSE_BUTTON_LEFT))
						{
							if (dap == nullptr) { EInputCore::logger_simple_error("DAP is NULL"); }
							if (parent_entity == nullptr) { EInputCore::logger_simple_error("parent entity is NULL"); }
							//if (EButtonGroup::focused_button_group_mouse_unpressed != ((EntityButton*)parent_entity)->parent_button_group) { EInputCore::logger_simple_error("parent group not focused"); }
							if (EClickableArea::active_clickable_region != this) { EInputCore::logger_simple_error("this clickable region not active"); }
						}
					}
				}
		}
	}

	//right click
	{
		for (data_action_pointer dap : actions_on_right_click_list)
			if
				(
					(dap != nullptr)
					&&
					(parent_entity != nullptr)
					&&
					(EButtonGroup::focused_button_group_mouse_unpressed == ((EntityButton*)parent_entity)->parent_button_group)
					&&
					(overlapped_by_mouse(this, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
					&&
					(EInputCore::mouse_button_pressed_once(GLFW_MOUSE_BUTTON_RIGHT))
				)
			{
				dap(parent_entity, parent_custom_data, _d);
			}
	}

	//if
	//(
	//	(EButtonGroup::focused_button_group_mouse_unpressed == ((EntityButton*)parent_entity)->parent_button_group)
	//	&&
	//	(overlapped_by_mouse(this, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
	//	&&
	//	(EInputCore::key_pressed_once(GLFW_KEY_APOSTROPHE))
	//)
	//{
	//	EInputCore::logger_simple_info("GLFW_KEY_APOSTROPHE");
	//}



	if (text_area != nullptr)
	{
		text_area->update(_d);
	}
}

void EClickableArea::draw()
{
	//if ((parent_custom_data != nullptr)&&(*parent_custom_data->is_second_pass)) { EInputCore::logger_simple_info("idiot?"); }
	if
	(
		(draw_only_is_specific_region_overlapped == nullptr)
		||
		(draw_only_is_specific_region_overlapped->overlapped_by_mouse())
	)
	{
		if (!sprite_layer_list.empty())
		{
			for (ESpriteLayer* s_layer : sprite_layer_list)
			{
				s_layer->transfer_vertex_buffer_to_batcher();
			}
		}

		if (active_clickable_region == this)
		{
			//NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.15f);
			NS_EGraphicCore::set_active_color(0.5f, 0.8f, 0.2f, 0.32f);

			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				region_gabarite->world_position_x,
				region_gabarite->world_position_y,

				region_gabarite->size_x,
				region_gabarite->size_y,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}


		if
		(
			(batcher_for_default_draw != nullptr)
			&&
			(DebugNamespace::is_debug_element_active(DebugStructID::ENTITY_GABARITES))
		)
		{
			if (active_clickable_region == this)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.75f);

				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					region_gabarite->world_position_x,
					region_gabarite->world_position_y,

					region_gabarite->size_x,
					region_gabarite->size_y,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}
			//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
			NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, catched_side_left));
			//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_left)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
			//if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
			if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				region_gabarite->world_position_x - 0.0f,
				region_gabarite->world_position_y,

				2.0f,
				region_gabarite->size_y,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
			//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
			NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, catched_side_right));
			//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_right)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
			if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				region_gabarite->world_position_x + region_gabarite->size_x - 2.0f,
				region_gabarite->world_position_y,

				2.0f,
				region_gabarite->size_y,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
			//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
			NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, catched_side_down));
			//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_down)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
			if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				region_gabarite->world_position_x - 0.0f,
				region_gabarite->world_position_y - 0.0f,

				region_gabarite->size_x,
				2.0f,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
			//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
			NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, catched_side_up));
			//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_up)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
			if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				region_gabarite->world_position_x - 0.0f,
				region_gabarite->world_position_y + region_gabarite->size_y - 2.0f,

				region_gabarite->size_x,
				2.0f,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
			//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
			NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, catched_side_mid));
			//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_mid)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
			if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				region_gabarite->world_position_x + region_gabarite->size_x / 2.0f - 3.0f,
				region_gabarite->world_position_y + region_gabarite->size_y / 2.0f - 3.0f,

				6.0f,
				6.0f,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);

			//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
			NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, catched_body));
			//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_body)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
			if
				(
					(active_clickable_region == this)
					)
			{
				NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_PINK, 0.5f);
			}

			if ((catched_body) && (EInputCore::MOUSE_BUTTON_LEFT))
			{
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);
				NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,

					region_gabarite->world_position_x,
					region_gabarite->world_position_y,

					region_gabarite->size_x,
					region_gabarite->size_y,

					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
			}

			//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 >= 39000) { batcher_for_default_draw->draw_call(); }
		}
		else
		{
			if (batcher_for_default_draw == nullptr) { EInputCore::logger_simple_error("batcher for default draw is null!"); }
		}

		if (text_area != nullptr)
		{
			//if (*parent_custom_data->is_second_pass) { EInputCore::logger_simple_info(*text_area->stored_text); }

			text_area->draw();
		}
	}


}

void EClickableArea::redraw_text()
{
	//for (ETextArea* t_area:text_area)
	if (text_area != nullptr)
	{
		text_area->generate_rows();
		text_area->generate_text();
	}
}

void EClickableArea::clickable_region_set_world_positions(float _x, float _y, float _z)
{
	region_gabarite->world_position_x = round(_x + region_gabarite->offset_x);
	region_gabarite->world_position_y = round(_y + region_gabarite->offset_y);
	region_gabarite->world_position_z = round(_z + region_gabarite->offset_z);

	for (ESpriteLayer* s_layer : sprite_layer_list)
		if (s_layer != nullptr)
		{
			s_layer->sprite_layer_set_world_position(region_gabarite->world_position_x, region_gabarite->world_position_y, region_gabarite->world_position_z);
		}
}

//void EClickableArea::set_color(const float(&_color)[4])
//{
//	color
//}

ERegionGabarite::ERegionGabarite()
{
}

ERegionGabarite::~ERegionGabarite()
{

}

ERegionGabarite::ERegionGabarite(float _offset_x, float _offset_y, float _size_x, float _size_y)
{
	offset_x = _offset_x;
	offset_y = _offset_y;

	size_x = _size_x;
	size_y = _size_y;
}

ERegionGabarite::ERegionGabarite(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y)
{
	offset_x = _offset_x;
	offset_y = _offset_y;
	offset_z = _offset_z;

	world_position_x = _offset_x;
	world_position_y = _offset_y;
	world_position_z = _offset_z;

	size_x = _size_x;
	size_y = _size_y;
}

ERegionGabarite::ERegionGabarite(float _size_x, float _size_y)
{
	size_x = _size_x;
	size_y = _size_y;
}

void ERegionGabarite::translate(float _x, float _y)
{
	offset_x += _x;
	offset_y += _y;

	world_position_x += _x;
	world_position_y += _y;
}

void ERegionGabarite::set_region_offset_and_size(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y)
{
	offset_x = _offset_x;
	offset_y = _offset_y;
	offset_z = _offset_z;

	world_position_x = _offset_x;
	world_position_y = _offset_y;
	world_position_z = _offset_z;

	size_x = _size_x;
	size_y = _size_y;

}

bool ERegionGabarite::overlapped_by_mouse()
{
	if
		(
			(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom >= world_position_x)
			&&
			(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom <= world_position_x + size_x)
			&&
			(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom >= world_position_y)
			&&
			(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom <= world_position_y + size_y)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ERegionGabarite::set_region_gabarite(ERegionGabarite** _target_region, ERegionGabarite* _source_region)
{
	//EInputCore::logger_simple_try("set region");




	if (*_target_region != _source_region)
	{

		//target region lose 1 owner, because target region change owner
		if (*_target_region != nullptr)
		{
			(*_target_region)->pointers_to_this_object--;
		}

		//source region get pointer
		(_source_region->pointers_to_this_object)++;

		//if (_source_region->parent_region == nullptr)
		//{
		//	_source_region->parent_region = _source_region;
		//}

		

		//if pointers more that 1, this region is "clone"
		//if (_source_region->pointers_to_this_object > 1)
		//{
		//	(*_target_region)->parent_region = _source_region;
		//}
	}
	else
	{
		//EInputCore::logger_simple_error("target = source");
	}

	*_target_region = _source_region;
	

}

void ERegionGabarite::add_child_to_this_region(ERegionGabarite* _child)
{
	child_gabarite_list.push_back(_child);
	_child->parent_gabarite = this;
}

void ERegionGabarite::align_all_clild_gabarites()
{
	for (ERegionGabarite* rg : child_gabarite_list)
	{
		rg->offset_x = offset_x;
		rg->offset_y = offset_y;
		rg->offset_z = offset_z;

		rg->offset_x += size_x * rg->offset_by_parent_size_x + rg->size_x * rg->offset_by_size_x + rg->offset_by_pixels_x;
		rg->offset_y += size_y * rg->offset_by_parent_size_y + rg->size_y * rg->offset_by_size_y + rg->offset_by_pixels_y;
	}
}

ECustomData::ECustomData()
{
}

ECustomData::~ECustomData()
{
	for (EClickableArea* clickable_area : clickable_area_list)
	{
		if (clickable_area != nullptr)
		{
			if (!disable_deleting) {delete clickable_area;}
			//clickable_area = nullptr;
		}
	}
	clickable_area_list.clear();
	clickable_area_list.shrink_to_fit();


	//for (data_action_pointer dap : actions_on_change_style)	{delete &dap;}
	actions_on_generate_vertex.clear();
	actions_on_generate_vertex.shrink_to_fit();


	//for (data_action_pointer dap : actions_on_draw)			{delete	&dap;}
	actions_on_draw.clear();
	actions_on_draw.shrink_to_fit();

	//for (data_action_pointer dap : actions_on_update)		{delete &dap;}
	actions_on_update.clear();
	actions_on_update.shrink_to_fit();

	if (data_container != nullptr)
	{
		if (!disable_deleting) {delete data_container;}
	}

}

void ECustomData::custom_data_draw()//(if (but->description_data != nullptr) { but->description_data->draw(); })
{


	if ((!disable_custom_data_draw) && (!is_second_pass))
	{

		//if (_second_pass) { EInputCore::logger_simple_info("???"); }
		for (data_action_pointer dap : actions_on_pre_draw)
			if (dap != nullptr)
			{
				dap(parent_entity, this, 0.1f);
			}

		for (EClickableArea* clickable_area : clickable_area_list)
		if (clickable_area != nullptr)
		{
				clickable_area->draw();
		}

		for (data_action_pointer dap : actions_on_draw)
			if (dap != nullptr)
			{
				dap(parent_entity, this, 0.1f);
			}
	}
}

void ECustomData::draw_second_pass()
{

	//if (*is_second_pass)
	//{
	//	EInputCore::logger_simple_info("draw second pass");
	//}
	//else
	//{
	//	EInputCore::logger_simple_info("you drunk?");
	//}

	//std::cout << std::endl;

	if ((!disable_custom_data_draw) && (is_second_pass))
	{

		//if (*is_second_pass)
		//{
		//	EInputCore::logger_simple_info("draw custom data");
		//}
		for (data_action_pointer dap : actions_on_draw)
			if (dap != nullptr)
			{
				dap(parent_entity, this, 0.1f);
			}

		for (EClickableArea* clickable_area : clickable_area_list)
			if (clickable_area != nullptr)
			{

				clickable_area->draw();
			}
	}
}

void ECustomData::update(float _d)
{
	for (data_action_pointer action_on_update_pointer : actions_on_update)
	{
		if ((action_on_update_pointer != nullptr) && (parent_entity != nullptr))
		{
			action_on_update_pointer(parent_entity, this, _d);
		}
	}

	for (EClickableArea* cl_region : clickable_area_list)
	{
		if (cl_region != nullptr)
		{
			cl_region->update(_d);
		}
	}


}

void ECustomData::translate_custom_data(float _x, float _y, float _z, bool _move_offset)
{
	for (EClickableArea* cl_region : clickable_area_list)
		if (cl_region != nullptr)
		{
			cl_region->translate_clickable_region(_x, _y, _z, false);
		}
}

ESprite* ECustomData::get_sprite_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id, unsigned int _frame)
{
	ESpriteFrame* s_frame = get_sprite_frame_by_id(_clickable_region_id, _sprite_layer_id, _frame_id);

	if
		(
			(s_frame != nullptr)
			&&
			(!s_frame->sprite_list.empty())
			)
	{
		return s_frame->sprite_list.at(_frame);
	}
	else
	{
		return nullptr;
	}
}

ESpriteLayer* ECustomData::get_sprite_layer_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id)
{
	if
		(
			(!clickable_area_list.empty())
			&&
			(!clickable_area_list.at(_clickable_region_id)->sprite_layer_list.empty())
			)
	{
		return clickable_area_list.at(_clickable_region_id)->sprite_layer_list.at(_sprite_layer_id);
	}
	else
	{
		return nullptr;
	}
}

ESpriteFrame* ECustomData::get_sprite_frame_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id)
{
	ESpriteLayer* s_layer = get_sprite_layer_by_id(_clickable_region_id, _sprite_layer_id);

	if
		(
			(s_layer != nullptr)
			&&
			(!s_layer->sprite_frame_list.empty())
			)
	{
		return s_layer->sprite_frame_list.at(_frame_id);
	}
	else
	{
		return nullptr;
	}
}

EDataContainerMessage::~EDataContainerMessage()
{
	if (!disable_deleting) {delete message;}
}

EDataContainerScrollBar::~EDataContainerScrollBar()
{
	if (!disable_deleting) {delete max_value; delete value_pointer; delete current_percent;}
}

//static registere section
std::string		ETextParser::data_array[1000];
std::string		ETextParser::action_text_buffer;
std::string		ETextParser::value_text_buffer;

EDataEntity* ETextParser::last_created_data_entity;
EDataTag* ETextParser::last_created_data_tag;
//




void ETextParser::data_entity_parse_file(std::string _file)
{
	std::ifstream file;
	std::string str;

	file.open(_file);

	bool raw_text_mode = false;
	bool new_line_not_finalize_data_mode = false;

	std::string buffer_text = "";
	/*std::string action_text_buffer = "";
	std::string value_text_buffer = "";*/

	unsigned int active_mode = ActiveParserMode::READ_CAPS_ACTION;

	unsigned char raw_char = 0;
	char readable_char = 0;

	while (std::getline(file, str))
	{
		buffer_text = "";

		//EInputCore::logger_param("direct read", str);
		//EInputCore::logger_param("string lenght", str.length());
		for (int i = 0; i < str.length(); i++)
		{
			readable_char = 0;
			raw_char = str.at(i);

			//fill buffer_text
			if
				(
					(
						(raw_char != '"')// ["] is never can be readable
						&&
						(raw_char != '\r')//new line
						&&
						(raw_char != '\n')//new line
						)
					&&
					(
						(raw_text_mode)
						||
						(
							(raw_char != '[')//action (example: [add new entity])
							&&
							(raw_char != '{')//[reserved]
							&&
							(raw_char != '\t')//tab separator (just for formatting)
							&&
							(raw_char != ' ')//space separator (jsut for formatting)
							)
						)
					&&
					(
						(raw_char != ']')//action (example: [add new entity])
						||
						(
							(raw_text_mode)
							&&
							(active_mode != ActiveParserMode::READ_ACTION)
							)
						)
					)
			{
				if (!raw_text_mode)
				{
					if ((raw_char == ']')) { EInputCore::logger_simple_error("** ] **"); }
					if ((raw_char == '[')) { EInputCore::logger_simple_error("** [ **"); }
				}


				buffer_text += raw_char;
				//std::cout << "raw_char " << raw_char << std::endl;
				//EInputCore::simple_logger_with_parameter("buffer_text", buffer_text);
				//readable_char = raw_char;
			}

			if (!raw_text_mode)
			{
				if
					//one of screen symbols
					(
						(raw_char == ' ')
						||
						(raw_char == '\t')
						||
						(raw_char == '[')
						||
						(raw_char == '"')
						||
						(raw_char == '\r')
						||
						(raw_char == '\n')
						||
						(i + 1 >= str.length())
					)
				{
					//if (buffer_text != "")
					//execute action without parameters
					{

						if ((active_mode == ActiveParserMode::READ_CAPS_ACTION) && (buffer_text != ""))
						{
							//if (i + 1 >= str.length()) { buffer_text += raw_char; }

							std::string ss(1, raw_char);

							//EInputCore::logger_param("do action by CAPS, symbol", ss);
							do_action(buffer_text, "");
						}

						buffer_text = "";
					}

				}
			}





			//add new char to readable buffer
			if (readable_char != 0)
			{

			}


			//start or finalise read to "value text buffer"
			if
			(
				(raw_char == '"')
			)
			{
				//if (action_text_buffer != "") {do_action}
				//any char is readable char
				//raw_text_mode = !(raw_text_mode);
				//EInputCore::logger_simple_info("switch raw mode by \"");
				//start fill parameter buffer
				if (raw_text_mode)
				{
					raw_text_mode = false;




					active_mode = ActiveParserMode::READ_CAPS_ACTION;


					value_text_buffer = buffer_text;

					//EInputCore::logger_simple_info("do action by \"");
					do_action(action_text_buffer, value_text_buffer);

				}
				else
					//
				{
					raw_text_mode = true;

					//mode = read parameter
					active_mode = ActiveParserMode::READ_VALUE;

					//action_text_buffer = "";

				}

				buffer_text = "";
				value_text_buffer = "";
			}

			//start read action text

			if ((raw_char == '[') && (!raw_text_mode))
			{
				//EInputCore::logger_simple_info("raw text mode ON by [");
				active_mode = ActiveParserMode::READ_ACTION;
				raw_text_mode = true;

				action_text_buffer = "";
				buffer_text = "";
			}

			//end read action text, action text = buffer_text
			if
				(
					(raw_char == ']')
					&&
					(
						(!raw_text_mode)
						||
						(active_mode == ActiveParserMode::READ_ACTION)
						)
					)
			{
				//EInputCore::logger_simple_info("raw text mode OFF by ]");
				active_mode = ActiveParserMode::READ_CAPS_ACTION;
				raw_text_mode = false;
				action_text_buffer = buffer_text;
				buffer_text = "";


			}


			if ((i + 1 >= str.length()) && (raw_text_mode))
			{
				EInputCore::logger_param_with_warning("missed \" at end in string", str);
				raw_text_mode = false;

				active_mode = ActiveParserMode::READ_CAPS_ACTION;
				value_text_buffer = buffer_text;

				do_action(action_text_buffer, value_text_buffer);

				buffer_text = "";
				value_text_buffer = "";

			}

		}

		

	}

	file.close();


	//for (EDataEntity* data_entity : EDataEntity::data_entity_list)
	//{
	//	for (EDataTag* data_tag : data_entity->tag_list)
	//	{
	//		EInputCore::logger_param("Tag name", *data_tag->tag_name);

	//		for (std::string* str : data_tag->tag_value_list)
	//		{
	//			EInputCore::logger_param("Tag value", *str);
	//		}

	//		EInputCore::logger_simple_info("");
	//	}
	//	EInputCore::logger_simple_info("-------");
	//}
	//EInputCore::logger_simple_info("");
}

void ETextParser::data_read_explicit_file_and_generate_data_entity(std::string _file)
{
	std::ofstream writabro;
	writabro.open("data_entity_for_enchantment.txt");

	std::ifstream file;
	std::string str;

	file.open(_file);

	std::string	temp_string = "";
	char		target_sym = 0;

	std::string temp_array[256];
	int temp_array_id = 0;

	while (std::getline(file, str))
	{
		temp_array_id = 0;

		for (int i = 0; i < str.length(); i++)
		{

			target_sym = str[i];

			//end of line
			if (i + 1 >= str.length())
			{
				temp_string += target_sym;

				temp_array[temp_array_id] = temp_string;
				temp_string = "";

				temp_array_id++;
			}
			else//not separator, symbol
				if (target_sym != '\t')
				{
					temp_string += target_sym;
				}
				else//separator
				{
					temp_array[temp_array_id] = temp_string;
					temp_string = "";

					temp_array_id++;
				}
		}

		//for (int i = 0; i < temp_array_id; i++)
		{
			writabro << std::endl;
			writabro << "ADD_NEW_DATA_ENTITY" << std::endl;
			//writabro << std::endl;
			writabro << "\t[tag]\"data type\"\t[value]\"Enchantment\"" << std::endl;
			writabro << std::endl;
			writabro << "\t[tag]\"base name\"\t[value]\"" << temp_array[0] << "\"" << std::endl;
			writabro << std::endl;
			writabro << "\t[tag]\"name EN\"\t\t[value]\"[" << temp_array[1] << "]" << temp_array[2] << "\"" << std::endl;
			writabro << "\t[tag]\"name RU\"\t\t[value]\"[" << temp_array[4] << "]" << temp_array[5] << "\"" << std::endl;
			writabro << std::endl;
			writabro << "\t[tag]\"icon path\"\t[value]\"Active\"" << std::endl;
		}
	}

	file.close();



	//for 
	writabro.close();
}

void ETextParser::split_data_entity_list_to_named_structs()
{
	//std::vector<EDataEntity*>* target_named_list = nullptr;
	DataEntityNamedStruct* target_named_struct	= nullptr;\
	std::string data_type_name					= "";
	std::string data_entity_name				= "";
	std::string base_name						= "";

	int arr[256] = {};

	std::string
	explicit_array[2048];

	int collision_count[2048]{};

	//for (EDataEntity* data_entity : EDataEntity::data_entity_global_list)
	for (int i = 0; i < EDataEntity::data_entity_global_list.size(); i++)
	{
		EDataEntity*
		data_entity = EDataEntity::data_entity_global_list[i];

		if (data_entity != nullptr)
		{
			int index = 0;

			data_type_name	= DataEntityUtils::get_tag_value_by_name(0, "data type", data_entity);
			base_name		= DataEntityUtils::get_tag_value_by_name(0, "base name", data_entity);

			data_entity_name = DataEntityUtils::get_tag_value_by_name(0, "key", data_entity);


			if (data_entity_name == "") { data_entity_name = DataEntityUtils::get_tag_value_by_name(0, "base name", data_entity); }
			if (data_entity_name == "") { data_entity_name = DataEntityUtils::get_tag_value_by_name(0, "name EN", data_entity); }

			if (data_entity_name != "")
			{
				//EInputCore::logger_param("Hash of [" + data_entity_name + "]", std::to_string(EStringUtils::hashFunction(data_entity_name) & 0x000000000000000F));

				index = EStringUtils::get_id_by_hash(data_entity_name);

				arr[index]++;

				//if (DataEntityUtils::get_tag_value_by_name(0, "key", data_entity) != "") { EInputCore::logger_param(data_entity_name, index); }
			}

			if (data_type_name != "")
			{
				EDataEntity::data_entity_hash_struct.data_entity_list[index].push_back(data_entity);


				

				if (data_type_name == "Explicit")
				{
					
					for (int i = 0; i < 2048; i++)
					{
						
						if (base_name == explicit_array[i])
						{
							collision_count[i]++;
							break;

						}
						else
						if (explicit_array[i] == "")
						{
							explicit_array[i] = base_name;
							break;
						}
					}

					
					std::ofstream writabro;
					writabro.open("-ExplicitCollisionCheck-.txt");
						for (int i = 0; i < 2048; i++)
						{
							if (explicit_array[i] != "")
							{
								writabro << explicit_array[i];
								
								if (collision_count[i] > 0)
								{
									writabro << "\t[" << std::to_string(collision_count[i]) << "]";
								}
								else
								{
									writabro << "\tno collision";
								}

								writabro << std::endl;
							}
						}
					writabro.close();
				}
			}
		}
		else
		{
			EInputCore::logger_simple_error("data entity is NULL");
		}

	}
	

	for (int i = 0; i < 256; i++)
	{
		EInputCore::logger_param("id [" + std::to_string(i) + "]", arr[i]);
	}
}


void ETextParser::do_action(std::string _action_text, std::string _value)
{
	//EInputCore::logger_simple_info("do action");
	//EInputCore::simple_logger_with_parameter("action:", _action_text);
	//EInputCore::simple_logger_with_parameter("value:", _value);

	//std::vector<DataEntityNamedList*>* pointer_to_named_list = nullptr;

	if (_action_text == "ADD_NEW_DATA_ENTITY")
	{
		last_created_data_entity = new EDataEntity();

		EDataEntity::data_entity_global_list.push_back(last_created_data_entity);
	}
	else
		if (_action_text == "tag")
		{
			last_created_data_tag = new EDataTag();
			*last_created_data_tag->tag_name = _value;

			last_created_data_entity->tag_list.push_back(last_created_data_tag);
		}
		else
			if (_action_text == "value")
			{
				last_created_data_tag->tag_value_list.push_back(new std::string(_value));
			}
}

EDataContainerRadialButton::~EDataContainerRadialButton()
{
	if (!disable_deleting)
	{

	}
}

std::string	EStringUtils::string_array[512];

std::string EStringUtils::to_lower(std::string _text)
{
	std::string output_string = "";
	unsigned char char_id;

	//EInputCore::logger_param("drunk?", _text.length());
	for (unsigned short i = 0; i < _text.length(); i++)
	{
		char_id = (unsigned char)_text[i];
		//std::string drunker = "" + _text[i];

		//EInputCore::logger_param("char", drunker);
		//EInputCore::logger_param("id", char_id);
		//std::cout << " " << _text[i] << std::endl;

		if
		(
				//latin characters set [A-Z]
				(
					(char_id >= 65)
					&&
					(char_id <= 90)
				)
				||
				//cyryllic characters set [А-Я](без Ё)
				(
					(char_id >= 192)
					&&
					(char_id <= 223)
				)
		)
		{
			output_string += (unsigned char)(char_id + 32);
		}
		else
		{
			//Ё
			if (char_id == 168)
			{ output_string += (unsigned char)(184); }
			else//no changes
			output_string+= _text[i];
		}
	}

	//EInputCore::logger

	//output_string;

	return output_string;
}

bool EStringUtils::compare_ignoring_case(std::string _text1, std::string _text2)
{

	return to_lower(_text1) == to_lower(_text2);
}

bool EStringUtils::A_contains_B_ignore_case(std::string _text_A, std::string _text_B)
{

	return to_lower(_text_A).find(to_lower(_text_B)) != std::string::npos;
}

std::string EStringUtils::UTF8_to_ANSI(std::string _text)
{

		char sInvalid[1024];
		strcpy_s(sInvalid, _text.c_str());
		//комментарии

		int size = strlen(sInvalid) + 1;
		wchar_t* wsValid = new wchar_t[size];
		char* sValid = new char[size];

		MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
		WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);

		std::string final_string = sValid;

		delete[] wsValid;
		delete[] sValid;

		return final_string;
		//MultiByteToWideChar(CP_UTF8, 0, sInvalid, -1, wsValid, size);
		//WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, sValid, size, NULL, NULL);
		/*if (_debug) std::cout << "### " << _text << std::endl;
		if (_debug) std::cout << "==== INPUT method: MB_COMPOSITE" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;

		if (_debug) std::cout << "==== INPUT method: MB_ERR_INVALID_CHARS" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;

		if (_debug) std::cout << "==== INPUT method: MB_PRECOMPOSED" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;

		if (_debug) std::cout << "==== INPUT method: MB_USEGLYPHCHARS" << std::endl;
		MultiByteToWideChar(CP_UTF8, MB_USEGLYPHCHARS, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_COMPOSITECHECK}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_ERR_INVALID_CHARS}" << std::endl;

		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, sInvalid, -1, wsValid, size);
			WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wsValid, -1, sValid, size, NULL, NULL);
			if (_debug) std::cout << "convert from [" << _text << "] to [" << sValid << "] using method: {WC_NO_BEST_FIT_CHARS}" << std::endl;*/


	//std::string _t = "";
	//for (int i = 0; i < _text.length(); i++)
	//{
	//	int inputed_c = (int)_text.at(i);


	//	if (inputed_c == 1025) { inputed_c = 168; }
	//	else
	//		if (inputed_c == 1105) { inputed_c = 184; }
	//		else
	//			if (inputed_c > 255) { inputed_c -= 848; }

	//	_t += (char)inputed_c;
	//}


	//return std::string();
}

bool EStringUtils::if_text_is_number(std::string _text)
{
	if
	(
		((_text).length() == 0)
		||
		(_text == "")
	)
	{ 
		//EInputCore::logger_param("symbol is empty", _text);
		return false;
	}

	for (int i = 0; i < _text.length(); i++)
	{
		if ((i > 0) && (_text[i] == '-')) { return false; }// minus can be only on start

		if
		(
			!(
				(_text[i] == '-')
				||
				(_text[i] == '0')
				||
				(_text[i] == '1')
				||
				(_text[i] == '2')
				||
				(_text[i] == '3')
				||
				(_text[i] == '4')
				||
				(_text[i] == '5')
				||
				(_text[i] == '6')
				||
				(_text[i] == '7')
				||
				(_text[i] == '8')
				||
				(_text[i] == '9')
			)
		)
		{
			//EInputCore::logger_param("symbol [" + _text.substr(i, 1) + "] is not valid", _text.substr(i, 1));
			return false;
		}
	}

	//EInputCore::logger_simple_success(_text + " is valid!");
	return true;
}

int EStringUtils::safe_convert_string_to_number(std::string _text, int _min, int _max)
{
	if (if_text_is_number(_text))
	{
		int num = std::stoi(_text);

		return std::clamp(num, _min, _max);
	}
	else
	{
		return _min;
	}
	
}

const int PRIME_CONST = 431;
void EStringUtils::split_line_to_array(std::string _line, bool _ignore_spaces)
{
	for (int i = 0; i < 512; i++) { string_array[i] = ""; }

	bool terminator = false;
	int id = 0;
	std::string buffer = "";
	bool space_is_not_separator = false;
	//int l = _line.length();

	//EInputCore::logger_param("idiot?", l);

	for (int i = 0; i < _line.length(); i++)
	{
	

		char sym = _line[i];

		if (sym == '"')
		{
			space_is_not_separator = !space_is_not_separator;
		}

		if
		(
			((sym == ' ') && (!space_is_not_separator) && (!_ignore_spaces))
			||
			(sym == '\t')
			||
			(i + 1 >= _line.length())

		)
		{
			terminator = true;
		}

		if (terminator)
		{
			if
			(
				(i + 1 >= _line.length())
				&&
				(sym != '"')
				&&
				(sym != '\t')
			)
			{ buffer += sym; }

			string_array[id] = buffer;
			buffer = "";
			id++;

			terminator = false;
		}
		else
		{
			if (sym != '"') { buffer += sym; }
		}
	}
}

int EStringUtils::hashFunction(std::string _input)
{
	int hashCode = 0;

	for (int i = 0; i < _input.length(); i++)
	{
		hashCode += (_input[i] * (int)pow(PRIME_CONST, i) % 1337) ;
	}

	return hashCode % 278;
}

int EStringUtils::get_id_by_hash(std::string _input)
{
	int
	index = EStringUtils::hashFunction(_input) & 0x00000000000000FF;
	index = min(index, 255);
	index = max(index, 0);

	return index;
}

bool EFilterRule::matched_by_filter_rule(EDataEntity* _data_entity, EFilterRule* _filter_rule, std::string _search_text)
{
	std::string tag_value = "";
	std::string search_text = "";

	bool tag_search_mode = false;
	bool cost_search_mode = false;




	bool matched_by_input = false;
	bool required_tag_match = true;
	bool required_tag_value_match = true;
	bool any_match_with_banned = false;
	//if (EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{

		if (true)
			for (DataEntityTagFilter banned_tag_filter : _filter_rule->banned_tag_list)
			{
				//potentially fail match

				//2 ways to fail match:
				//1) item have no required tag
				//2) item have required tag, but value of this tag not math with no one suitable tag list
				//EInputCore::logger_param("target_tag_name", banned_tag_filter->target_tag_name);
				//EInputCore::logger_param("suitable_values_list", banned_tag_filter->suitable_values_list[0]);

				//for every banned tag
				for (EDataTag* data_entity_tag : _data_entity->tag_list)
				{
					tag_value = *data_entity_tag->tag_value_list[0];

					//compare data entity tag and require tag from filter rule
					if ((EStringUtils::compare_ignoring_case(*data_entity_tag->tag_name, banned_tag_filter.target_tag)))
					{

						for (DETF_Value suitable_str : banned_tag_filter.banned_tags)//one of suitable list
						{
							//EInputCore::logger_param("data_entity_tag", tag_value);


							//if (suitable_str == "Deleted") { return false; }

							if
							(
									//empty suitable text means 'any value suitable'
									(suitable_str.target_value_key == "")
									||
									(EStringUtils::compare_ignoring_case(suitable_str.target_value_key, tag_value))
							)
							{
								//even one match with banned tag return false
								return false;
							}
						}
					}
				}



				//{ *but->disable_draw = false; } else { *but->disable_draw = true; }
			}

		//search by input
		if (_search_text != "")
		{
			search_text = EStringUtils::to_lower(_search_text);

			//search by tags
			if (search_text[0] == '*')
			{
				tag_search_mode = true;
				search_text = search_text.substr(1);
			}

			//search by cost
			if (search_text[0] == '$')
			{
				cost_search_mode = true;
				search_text = search_text.substr(1);
			}

			for (EDataTag* data_entity_tag : _data_entity->tag_list)
				if (!matched_by_input)
				{
					tag_value = EStringUtils::to_lower(*data_entity_tag->tag_value_list[0]);
					//if (*data_entity_tag->tag_name == "name EN") {EInputCore::logger_param("name EN", ) }
					if ((*data_entity_tag->tag_name == "base name") && (tag_value.find(search_text) != std::string::npos)) { matched_by_input = true; }
					else
						if ((*data_entity_tag->tag_name == "name EN") && (tag_value.find(search_text) != std::string::npos)) { matched_by_input = true; }
						else
							if ((*data_entity_tag->tag_name == "name RU") && (tag_value.find(search_text) != std::string::npos)) { matched_by_input = true; }
				}
		}
		else
		{
			matched_by_input = true;
		}

		//for every required tag
		for (DataEntityTagFilter required_tag_filter : _filter_rule->required_tag_list)
			if ((required_tag_match) && (required_tag_value_match) && (matched_by_input))//if tag match still not failed
			{
				//potentially fail match
				required_tag_match = false;
				required_tag_value_match = false;
				//2 ways to fail match:
				//1) item have no required tag
				//2) item have required tag, but value of this tag not math with no one suitable tag list


				//for every data entity tag
				for (EDataTag* data_entity_tag : _data_entity->tag_list)
				{
					tag_value = *data_entity_tag->tag_value_list[0];

					//compare data entity tag and requaire tag from filter rule
					if ((EStringUtils::compare_ignoring_case(*data_entity_tag->tag_name, required_tag_filter.target_tag)))
					{
						//EInputCore::logger_param("tag name", *data_entity_tag->tag_name);
						required_tag_match = true;

						//empty suitable list means what any value is acceptable
						if (required_tag_filter.suitable_values.empty())
						{
							//EInputCore::logger_simple_info("set as suitable because required list id EMPTY");
							required_tag_value_match = true;
						}
						else
							for (DETF_Value suitable_DETF : required_tag_filter.suitable_values)//one of suitable list
							{
								if
								(
									//empty suitable text means 'any value suitable'
									(suitable_DETF.is_active)
									&&
									(
										(suitable_DETF.target_value_key == "")
										||
										(EStringUtils::compare_ignoring_case(suitable_DETF.target_value_key, tag_value))
									)
								)
								{

									//EInputCore::logger_param("suitable value", tag_value);

									required_tag_value_match = true;

									break;
								}
							}
					}
				}



				//{ *but->disable_draw = false; } else { *but->disable_draw = true; }
			}

	}

	return (matched_by_input && required_tag_match && required_tag_value_match);
}

//void EFilterRule::add_default_banned_tag()
//{
//	//filter "item tag" by 
//	DataEntityFilter*
//	jc_filter = new DataEntityFilter();
//
//	jc_filter->target_tag_name = "item tag";
//	jc_filter->suitable_values_list.push_back("Deleted");
//
//	banned_tag_list.push_back(jc_filter);
//
//}

