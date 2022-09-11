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

/**/
#ifndef	_HELPERS_ALREADY_LINKED_
#define	_HELPERS_ALREADY_LINKED_
#include "Helpers.h"
#endif
/**/

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

void EDataActionCollection::action_player_control(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//int number = rand() % 1000000;

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_W))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{
		_entity->translate_entity(0.0f, 1000.0f * _d, 0.0f, true);

	};

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_S))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{
		_entity->translate_entity(0.0f, -1000.0f * _d, 0.0f, true);

	};

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_Z))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{ 
		
		//NS_ERenderCollection::generate_brick_texture(_custom_data->clickable_area_list[0]->region_gabarite, _entity->sprite_layer_list[0], NS_DefaultGabarites::texture_lead_and_gold, nullptr, nullptr);
		_entity->set_world_position(_entity->world_position_x, _entity->world_position_y, _entity->world_position_z);
		_entity->generate_vertex_buffer_for_all_sprite_layers();
		
		
	}
}

void EDataActionCollection::action_update_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton* entity_button = ((EntityButton*)_entity);
	EDataContainerScrollBar* data_bar = ((EDataContainerScrollBar*)_custom_data->data_container);

	//EInputCore::logger_simple_success("@");

	entity_button->button_gabarite->size_y = entity_button->parent_button_group->region_gabarite->size_y;



	_entity->offset_x
	=
	entity_button->parent_button_group->region_gabarite->size_x
	-
	entity_button->button_gabarite->size_x
	-
	entity_button->parent_button_group->border_right;



	_entity->world_position_x
	=
		_entity->offset_x
	+
	entity_button->parent_button_group->region_gabarite->world_position_x;

	*data_bar->max_value
	=
	max
	(
		0.0f,
		entity_button->parent_button_group->highest_point_y
		-
		(
			entity_button->parent_button_group->region_gabarite->size_y
			-
			//*entity_button->parent_button_group->border_bottom
			//-
			entity_button->parent_button_group->border_up
		)
	);

	//*data_bar->max_value = 1000.0f;
	
	
	if (*data_bar->max_value > 0.0f)
	{
		//*_entity->disable_draw = false;
	}
	else
	{
		//*_entity->disable_draw = true;
	}

	if
	(
		(
			(EClickableArea::active_clickable_region == nullptr)
			||
			(EClickableArea::active_clickable_region == _custom_data->clickable_area_list.at(0))
			||
			(EButtonGroup::focused_button_group_with_slider == entity_button->parent_button_group)
		)
		&&
		(
			(*_custom_data->clickable_area_list.at(0)->catched_body)
			||
			(EButtonGroup::focused_button_group_with_slider == entity_button->parent_button_group)
		)
		&&
		(*data_bar->max_value > 0.0f)
	)
	{

		

		

		if (*_custom_data->clickable_area_list.at(0)->catched_body)
		{
			if (EInputCore::mouse_button_state[GLFW_MOUSE_BUTTON_LEFT] != GLFW_RELEASE)
			{
				_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y += EInputCore::MOUSE_SPEED_Y;
			}

			if (*_custom_data->get_sprite_frame_by_id(0, 0, 0)->active_frame_id != 1)
			{
				*_custom_data->get_sprite_frame_by_id(0, 0, 0)->active_frame_id = 1;

				_entity->set_world_position(_entity->world_position_x, _entity->world_position_y, _entity->world_position_z);
				_entity->generate_vertex_buffer_for_all_sprite_layers();
			}
		}

		if
		(
			(EInputCore::scroll_direction != 0)
			&&
			(EButtonGroup::focused_button_group_with_slider == entity_button->parent_button_group)
			&&
			(entity_button->parent_button_group->region_gabarite->size_y > 10.0f)
		)
		{
			_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
			+=
			(EInputCore::scroll_direction * EInputCore::scroll_direction * EInputCore::scroll_direction * 2)
			*
			(entity_button->parent_button_group->region_gabarite->size_y  / *data_bar->max_value)
			*
			10.0f;
		}

		if
		(
			(
				(EInputCore::mouse_button_state[GLFW_MOUSE_BUTTON_LEFT] != GLFW_RELEASE)
				&&
				(EInputCore::MOUSE_SPEED_Y != 0.0)
				&&
				(*_custom_data->clickable_area_list.at(0)->catched_body)
			)
			||
			(
				(EInputCore::scroll_direction != 0)
				&&
				(EButtonGroup::focused_button_group_with_slider == entity_button->parent_button_group)
			)
		)
		{
			_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
				=
				max(entity_button->parent_button_group->border_bottom, _custom_data->clickable_area_list.at(0)->region_gabarite->offset_y);

			_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
				=
				min
				(
					entity_button->parent_button_group->region_gabarite->size_y
					-
					_custom_data->clickable_area_list.at(0)->region_gabarite->size_y
					-
					entity_button->parent_button_group->border_up,
					_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
				);

			*data_bar->current_percent
				=
				//head position (990 - 7) = 983
				(
					_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
					-
					entity_button->parent_button_group->border_bottom
					)
				/
				(
					entity_button->parent_button_group->region_gabarite->size_y//1000
					-
					_custom_data->clickable_area_list.at(0)->region_gabarite->size_y//39
					-
					entity_button->parent_button_group->border_up
					-
					entity_button->parent_button_group->border_bottom//7
					);

			*data_bar->current_percent = min(*data_bar->current_percent, 1.0f);

			float old_value = *data_bar->value_pointer;
			*data_bar->value_pointer
				=
				
				(
					*data_bar->current_percent
					*
					*data_bar->max_value
					*
					-1.0f
				);
			float new_value = *data_bar->value_pointer;
			float diff = new_value - old_value;

			//EInputCore::logger_param("HPy", *entity_button->parent_button_group->highest_point_y);
			//EButtonGroup::refresh_button_group(entity_button->parent_button_group);
			entity_button->parent_button_group->translate_content(0.0f, diff, 0.0f, false);
			//for (EButtonGroup* group : entity_button->parent_button_group->group_list)
			//{
			//	group->translate(0.0f, diff, 0.0f, true);
			//}

			//for (EntityButton* button : entity_button->parent_button_group->button_list)
			//if (button != entity_button)
			//{
			//	button->translate_entity(0.0f, diff, 0.0f, true);
			//}

			////EButtonGroup::calculate_culling_lines(entity_button->parent_button_group);

			//for (EButtonGroup* group : entity_button->parent_button_group->group_list)
			//{
			//	//group->phantom_translate_if_need();

			//}
			//_entity->set_world_position(*_entity->world_position_x, *_entity->world_position_y, *_entity->world_position_z);
			
			_entity->set_world_position(_entity->world_position_x, _entity->world_position_y, _entity->world_position_z);
			entity_button->generate_vertex_buffer_for_all_sprite_layers();
			
			//EButtonGroup::generate_vertex_buffer_for_group(entity_button->parent_button_group);
			
			//entity_button->parent_button_group->realign_all_buttons();
			//entity_button->parent_button_group->align_groups();
			//EButtonGroup::calculate_culling_lines(entity_button->parent_button_group);
		}
	}
	else
	{
		
	}

	if
		(
			(!*_custom_data->clickable_area_list.at(0)->catched_body)
			&&
			(_custom_data->get_sprite_frame_by_id(0, 0, 0) != nullptr)
		)
	{
		if (*_custom_data->get_sprite_frame_by_id(0, 0, 0)->active_frame_id != 0)
		{
			*_custom_data->get_sprite_frame_by_id(0, 0, 0)->active_frame_id = 0;

			_entity->set_world_position(_entity->world_position_x, _entity->world_position_y, _entity->world_position_z);
			_entity->generate_vertex_buffer_for_all_sprite_layers();
		}

	}


	//*_entity->world_position_x = *entity_button->parent_button_group->region->world_position_x + *entity_button->parent_button_group->region->size_x - *entity_button->button_gabarite->size_x;
	//*_entity->world_position_y = *entity_button->parent_button_group->region->world_position_y;

	//_entity->custom_data_list.at(0)->get_sprite_by_id(0, 0, 0, 0)->generate_vertex_buffer_for_sprite_layer("");
	
	//_custom_data->clickable_region_list.at(0)->sprite_layer_list.at(0)->generate_vertex_buffer_for_sprite_layer("");



	//_custom_data->get_sprite_layer_by_id(0, 0)->generate_vertex_buffer_for_sprite_layer("");
	
	

	//_entity->

	//*_entity->world_position_y = *entity_button->parent_button_group->region->world_position_y + *_entity->offset_y;
	//_entity->set_world_position(*_entity->world_position_x, *_entity->world_position_y, *_entity->world_position_z);
	//_entity->generate_vertex_buffer_for_all_sprite_layers();
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
		(EButtonGroup::focused_button_group == ((EntityButton*)_entity)->parent_button_group)
		&&
		(((EntityButton*)_entity)->button_gabarite->overlapped_by_mouse())
	)
	{
		NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.15f);
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
	for (EWindow* window : EWindow::window_list)
	for (EButtonGroup* group:window->button_group_list)
	{
		EButtonGroup::change_style (group,((EntityButton*)_entity)->parent_button_group->selected_style);
	}
}

void EDataActionCollection::action_close_root_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup* _group = ((EntityButton*)_entity)->parent_button_group;

	if
	(
		( _group != nullptr )
		&&
		( _group->root_group != nullptr )
	)
	{
		_group->root_group->is_active = false;

		EClickableArea::active_clickable_region = nullptr;

		//for (ECustomData* dt:_group->region_gabarite
		//if (EClickableArea::active_clickable_region == *(((EntityButton*)_entity)->parent_button_group)
	}
}

void EDataActionCollection::action_delete_entity(Entity* _entity, ECustomData* _custom_data, float _d)
{
	_entity->need_remove = true;
	//_entity->translate_entity(20.0f, 20.0f, 20.0f);
	//((EWindowMain*)EWindow::window_list[0])->

	//for (TestObject* to : EWindow::window_list[0]->test_vector)
	//{
	//	delete to;
	//}

	//EInputCore::logger_simple_try("set 'need remove' flag");
}

void EDataActionCollection::action_switch_description(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (((EntityButton*)_entity)->button_gabarite->overlapped_by_mouse())
	{
		*_custom_data->disable_draw = false;
	}
	else
	{
		*_custom_data->disable_draw = true;
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

		if (*data_container->stored_type == StoredPointerType::STORED_TYPE_FLOAT)
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

			*(float*)(d_pointer) = min(*(float*)(d_pointer), *data_container->max_value);
			*(float*)(d_pointer) = max(*(float*)(d_pointer), *data_container->min_value);

			dot_sprite->offset_x
			=
			size / 2.0f
			- 
			dot_sprite->size_x / 2.0f
			+
			sin(*(float*)(d_pointer) * 6.28f * 0.8f + 0.628f ) * (size / 2.0f - 8.0f);




			dot_sprite->offset_y
			=
			size / 2.0f
			-
			dot_sprite->size_x / 2.0f
			+
			cos(*(float*)(d_pointer) * 6.28f * 0.8f + 0.628f) * (size / 2.0f - 8.0f);

			_custom_data->clickable_area_list[0]->text_area->change_text(data_container->text + "\\n" + std::to_string(*(float*)(d_pointer)));
			
		}


		_entity->set_world_position(_entity->world_position_x, _entity->world_position_y, _entity->world_position_z);
		_entity->generate_vertex_buffer_for_all_sprite_layers();
	}



	
}

void EDataActionCollection::action_type_text(ETextArea* _text_area)
{
	//EInputCore::logger_param("stored text",  * _text_area->stored_text);

	
	//(
	//	(_text_area != nullptr)
	//	&&
	//	(_text_area->parent_clickable_region != nullptr)
	//	&&
	//	(_text_area->parent_clickable_region->parent_custom_data != nullptr)
	//	&&
	//	(_text_area->parent_clickable_region->parent_custom_data->parent_entity != nullptr)
	//	&&
	//	(((EntityButton*)_text_area->parent_clickable_region->parent_custom_data->parent_entity)->parent_button_group != nullptr)
	//	&&
	//	(((EntityButton*)_text_area->parent_clickable_region->parent_custom_data->parent_entity)->parent_button_group->root_group != nullptr)

	//)
	if ((_text_area != nullptr) && (_text_area->get_root_group() != nullptr))
	{
		EDataContainer_Group_DataEntitiesSearch* data_container = (EDataContainer_Group_DataEntitiesSearch*)_text_area->get_root_group()->data_container;
		
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
			data_container->pointer_to_group_with_data_entities->scroll_y = 0.0f;

			for (EntityButton* but:data_container->pointer_to_group_with_data_entities->button_list)
			if (but != data_container->pointer_to_group_with_data_entities->slider)
			{

				//for (ECustomData* cd:but->custom_data_list)
				//for (EClickableArea* cl_area:cd->clickable_area_list)
				//{
				//	if (EClickableArea::active_clickable_region == cl_area)
				//	{
				//		EClickableArea::active_clickable_region = nullptr;
				//	}
				//}
				//if (rand() % 2 == 0){*but->disable_draw = true;} else { *but->disable_draw = false; }
				bool match = false;



				//EDataContainerEntityDataHolder* data_holder = (EDataContainerEntityDataHolder*)but->custom_data_list[0]->data_container;
				EDataEntity* target_data_entity = but->pointer_to_data_entity;
				std::string value = "";
				std::string search_text = EStringUtils::to_lower(*_text_area->stored_text);

				bool tag_search_mode	= false;
				bool cost_search_mode	= false;



				if ((search_text.length() > 0) && (search_text[0] == '*'))
				{
					tag_search_mode = true;

					search_text = search_text.substr(1);
				}

				if ((search_text.length() > 0) && (search_text[0] == '$'))
				{
					cost_search_mode = true;

					search_text = search_text.substr(1);
				}

				//EInputCore::logger_param("size of tag list", target_data_entity->tag_list.size());

				bool tag_require_match = true;
				for (EDataTag* tag: target_data_entity->tag_list)
				{
					value = EStringUtils::to_lower (*tag->tag_value_list[0]);

					
					//if (data_container->required_tag_list.empty()) { tag_require_match = true; }
					for (DataEntityFilter* filter : data_container->target_rule->required_tag_list)
					{
						if ((tag_require_match) && (filter->target_tag_name == *tag->tag_name) && (!filter->suitable_values_list.empty()))
						{
							//potentially fail match
							tag_require_match = false;

							for (std::string str : filter->suitable_values_list)
							{
								if ((str == "") || (str == value)) { tag_require_match = true; }
							}
						}
					}

					if (tag_search_mode)
					{
						if ((*tag->tag_name == "item tag") && (value.find(search_text) != std::string::npos)) { match = true; }
					}
					else
					if (cost_search_mode)
					{
						if ((*tag->tag_name == "worth") && (value.find(search_text) != std::string::npos)) { match = true; }
					}
					else
					{
						if ((*tag->tag_name == "name EN") && (value.find(search_text) != std::string::npos)) { match = true; }
						if ((*tag->tag_name == "name RU") && (value.find(search_text) != std::string::npos)) { match = true; }
					}

					//{ *but->disable_draw = false; } else { *but->disable_draw = true; }
				}
				//tag_require_match = false;
				if ((match) && (tag_require_match)) { but->disabled = false; }
				else { but->disabled = true; }

			}

			//*data_container->pointer_to_target_group_send_item->is_active = false;

			//data_container->pointer_to_group_with_data_entities->realign_all_buttons();
			EButtonGroup::refresh_button_group(data_container->pointer_to_group_with_data_entities->root_group);
			//data_container->pointer_to_target_group_send_item->button_list.clear();

			//EButtonGroup::refresh_button_group(data_container->pointer_to_target_group_send_item);
		}
		else
		{
			if 
			(data_container == nullptr) {EInputCore::logger_simple_error("data container is NULL!"); }
			else if
			(data_container->pointer_to_group_with_data_entities == nullptr) {EInputCore::logger_simple_error("target button group is NULL!"); }
			else if
			(data_container->target_rule == nullptr) {EInputCore::logger_simple_error("filter rule is NULL!"); }
		}
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
	auto		multisearch_data_container	= static_cast<EDataContainer_Button_MultiGroupButtonSearcher*>(_text_area->parent_clickable_region->parent_custom_data->data_container);
	std::string	target_text					= *_text_area->stored_text;

	bool match = false;

	

	for (EButtonGroup*		bg			:multisearch_data_container->target_group_list)
	for (EntityButton*		but			:bg->button_list)
	if (but != bg->slider)
	{
		match = false;

		for (ECustomData*		c_data		:but->custom_data_list)
		for (EClickableArea*	c_area		:c_data->clickable_area_list)
		if (c_area->text_area != nullptr)
		{
			//stored text
			if
			(
				EStringUtils::to_lower(*c_area->text_area->stored_text).find(EStringUtils::to_lower(target_text))
				!=
				std::string::npos
			)
			{match = true;}

			//search on localisations text
			for (int i = 0; i < NSW_languages_count; i++)
			{
				if
				(
					EStringUtils::to_lower(c_area->text_area->localisation_text.localisations[i]).find(EStringUtils::to_lower(target_text))
					!=
					std::string::npos
				)
				{match = true;}
			}

			//base name
			if
			(
				EStringUtils::to_lower(c_area->text_area->localisation_text.base_name).find(EStringUtils::to_lower(target_text))
				!=
				std::string::npos
			)
			{match = true;}

			if (match)
			{	
				but->disabled		= false;
				but->disable_draw	= false;
			}
			else
			{
				but->disabled		= true;
				but->disable_draw	= true;
			} 
		}

		bg->scroll_y = 0.0f;
		EButtonGroup::change_group(bg);
	}
}


std::vector<EFilterRule*> EFilterRule::registered_filter_rules(RegisteredFilterRules::_RDEF_LAST_ELEMENT_);

void EDataActionCollection::action_open_data_entity_filter_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EInputCore::logger_simple_info("???");
	EDataContainerStoreTargetGroup* button_data_container = ((EDataContainerStoreTargetGroup*)_custom_data->data_container);
	EDataContainer_Group_DataEntitiesSearch* button_group_data_container = (EDataContainer_Group_DataEntitiesSearch*)EButtonGroup::data_entity_filter->data_container;

	EButtonGroup::data_entity_filter->is_active = true;

	button_group_data_container->pointer_to_group_item_receiver = button_data_container->target_group;
	button_group_data_container->target_rule = button_data_container->filter_rule;
	button_group_data_container->action_on_select_for_button = button_data_container->target_action_on_click;

	EDataActionCollection::action_type_text(button_group_data_container->filter_text_area);
	/* OUTDATED */
	//if
	//(
	//	(data_container_with_rule->target_rule != nullptr)
	//	&&
	//	(!data_container_with_rule->target_rule->required_tag_list.empty())
	//	&&
	//	(!data_container_with_rule->target_rule->required_tag_list[0]->suitable_values_list.empty())
	//)
	//{
	//	data_container_with_rule->target_rule->required_tag_list[0]->suitable_values_list[0] = data->search_tag;
	//}
}

void EDataActionCollection::action_open_color_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (_custom_data->data_container != nullptr)
	{
		EButtonGroup::color_editor_group->is_active = true;

		EDataContainer_Button_StoreColor*	button_data		= static_cast<EDataContainer_Button_StoreColor*>(_custom_data->data_container);
		EDataContainer_Group_ColorEditor*	group_data		= static_cast<EDataContainer_Group_ColorEditor*>(EButtonGroup::color_editor_group->data_container);
		//Helper::hsvrgba_color*				master_color	= nullptr;
		EDataContainer_Button_StoreColor*	master_data		= group_data->target_data_container_with_color;


		//set target button to button group
		if (button_data->selected_mode == ColorButtonMode::CBM_OPEN_WINDOW)
		{
			group_data->pointer_to_color_collection_group->selected_button = nullptr;
			group_data->target_data_container_with_color = button_data;

			if (group_data->pointer_to_color_collection_group != nullptr)
				for (EntityButton* but : group_data->pointer_to_color_collection_group->button_list)
				{
					if (static_cast<EDataContainer_Button_StoreColor*>(but->custom_data_list[0]->data_container)->stored_color == button_data->stored_color)
					{
						group_data->pointer_to_color_collection_group->selected_button = but;
						break;
					}
				}
			else
			{
				EInputCore::logger_simple_error("pointer to color group is null!");
			}

			master_data = group_data->target_data_container_with_color;
			group_data->work_color = master_data->stored_color;
		}

		//color data container from target button
		//if (group_data->target_data_container_with_color != nullptr)
		//{
			//master_color = group_data->target_data_container_with_color->stored_color;
		//}



		//set new color to master_button
		if ((button_data->selected_mode == ColorButtonMode::CBM_SELECT_COLOR) && (master_data->stored_color != nullptr))
		{
			if
				(
					(EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
					||
					(EInputCore::key_pressed(GLFW_KEY_RIGHT_SHIFT))
					)
			{
				//if color not from collection, remove personal color
				if (!master_data->stored_color->is_from_collection)
				{
					delete master_data->stored_color;
					
					master_data->stored_color->is_from_collection = true;
				}

				master_data->stored_color = button_data->stored_color;

				group_data->pointer_to_color_collection_group->selected_button = static_cast<EntityButton*>(_entity);
				group_data->work_color = button_data->stored_color;
			}
			else
			{
				//if color from collection, create personal color
				if (master_data != nullptr)
				{
					if (master_data->stored_color->is_from_collection)
					{
						master_data->stored_color = new Helper::HSVRGBAColor();
						master_data->stored_color->is_from_collection = false;
					}

					master_data->stored_color->set_color(button_data->stored_color);
					//button_data->stored_color->set_color(button_data->stored_color);

					group_data->pointer_to_color_collection_group->selected_button = nullptr;

					group_data->work_color = master_data->stored_color;
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

	receiver->button_list.push_back(jc_button);
	//receiver->button_list.clear();
	EButtonGroup::refresh_button_group(receiver->root_group);
}

void EDataActionCollection::action_add_wide_item_to_group_receiver(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup*								parent_group		= ((EntityButton*)_entity)->parent_button_group;
	EButtonGroup*								root_group			= parent_group->root_group;
	EDataContainer_Group_DataEntitiesSearch*	data				= (EDataContainer_Group_DataEntitiesSearch*)root_group->data_container;
	EButtonGroup*								receiver			= data->pointer_to_group_item_receiver;
	EDataContainer_DataEntityHolder*			data_entity_holder	= (EDataContainer_DataEntityHolder*)_custom_data->data_container;

	EInputCore::logger_simple_info("!!!");

	float temp_width = 300.0f;

	//if (data->target_rule. )
	EntityButton* jc_button = EntityButton::create_wide_item_button
	(
		new ERegionGabarite(temp_width, 40.0f),
		receiver,
		data_entity_holder->stored_data_entity,
		EFont::font_list[0]
	);

	if (!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{
		root_group->is_active = false;
	}
	receiver->button_list.push_back(jc_button);
	//receiver->button_list.clear();
	EButtonGroup::change_group(receiver);
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

void EDataActionCollection::action_update_vertical_named_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EDataContainer_VerticalNamedSlider* data = static_cast<EDataContainer_VerticalNamedSlider*>(_custom_data->data_container);

	float original_value = *data->pointer_to_value / data->max_value;

	if (original_value != data->current_value)
	{
		data->current_value = original_value;
		
		if (data->pointer_to_text_area != nullptr)
		{data->pointer_to_text_area->change_text(data->stored_text + ": " + Helper::float_to_string_with_precision(data->current_value * data->max_value, 100.0f));}
	}

	
	if
	(
		(EInputCore::MOUSE_BUTTON_LEFT)
		&&
		(EClickableArea::active_clickable_region == _custom_data->clickable_area_list.at(0))
	)
	{
		if
		(
			(EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
			||
			(EInputCore::key_pressed(GLFW_KEY_RIGHT_SHIFT))
		)
		{data->current_value += (EInputCore::MOUSE_SPEED_X / NS_EGraphicCore::current_zoom * 0.1f) / data->operable_area_size_x;}
		else
		{data->current_value = (EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom - data->pointer_to_bg->world_position_x) / data->operable_area_size_x;}

		data->current_value = max(data->current_value, 0.0f);
		data->current_value = min(data->current_value, 1.0f);


		//change text to [stored_text] + slider value * max_value. Example: "Gloss: 0.75"
		

		if (data->pointer_to_value != nullptr)
		{*data->pointer_to_value = data->current_value * data->max_value;}

		if (data->additional_action_on_slide != nullptr)
		{
			data->additional_action_on_slide(_entity, _custom_data, _d);
		}

		if (data->pointer_to_text_area != nullptr)
		{
			data->pointer_to_text_area->change_text(data->stored_text + ": " + Helper::float_to_string_with_precision(data->current_value * data->max_value, 100.0f));
		}
		//EInputCore::logger_param("Value", data->current_value);
	}



}

void EDataActionCollection::action_draw_vertical_named_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EDataContainer_VerticalNamedSlider* data = static_cast<EDataContainer_VerticalNamedSlider*>(_custom_data->data_container);
	EntityButton* button = static_cast<EntityButton*>(_entity);
	if (data->style != nullptr)
	{

		
		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);

		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_real_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,
			data->pointer_to_bg->world_position_x + data->operable_area_size_x * data->current_value,
			data->pointer_to_bg->world_position_y,
			data->style->round_slider->main_texture
		);
	}
}

void EDataActionCollection::action_convert_HSV_to_RGB(EButtonGroup* _group)
{
	//EInputCore::logger_simple_info("?");
	Helper::hsv2rgb(static_cast<EDataContainer_Group_ColorEditor*>(_group->data_container)->work_color);
}

void EDataActionCollection::action_set_new_color_to_button(EButtonGroup* _group)
{
	EInputCore::logger_simple_info("@");
	static_cast<EDataContainer_Group_ColorEditor*>(_group->root_group->data_container)->target_data_container_with_color->stored_color
	=
	static_cast<EDataContainer_Group_ColorEditor*>(_group->root_group->data_container)->work_color;
}

void EDataActionCollection::action_resize_to_full_window(EButtonGroup* _group)
{
	_group->region_gabarite->size_x = (NS_EGraphicCore::SCREEN_WIDTH	/ NS_EGraphicCore::current_zoom);
	_group->region_gabarite->size_y = (NS_EGraphicCore::SCREEN_HEIGHT	/ NS_EGraphicCore::current_zoom);
																		
	_group->base_width				= (NS_EGraphicCore::SCREEN_WIDTH	/ NS_EGraphicCore::current_zoom);
	_group->base_height				= (NS_EGraphicCore::SCREEN_HEIGHT	/ NS_EGraphicCore::current_zoom);

	//EInputCore::logger_simple_info("group resized");

	EButtonGroup::change_style(_group, _group->selected_style);
	//EButtonGroup::apply_style_to_button_group(_group, _group->selected_style);
	//EButtonGroup::refresh_button_group(_group);
}

void EDataActionCollection::action_draw_boolean_switcher(Entity* _entity, ECustomData* _custom_data, float _d)
{
	auto data_container = static_cast <EDataContainer_Button_BoolSwitcher*> (_custom_data->data_container);

	if (*data_container->target_value)
	{
		NS_EGraphicCore::set_active_color(1.0f, 1.0f, 1.0f, 1.0f);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			((EntityButton*)_entity)->button_gabarite->world_position_x,
			((EntityButton*)_entity)->button_gabarite->world_position_y,

			((EntityButton*)_entity)->button_gabarite->size_x,
			((EntityButton*)_entity)->button_gabarite->size_y,

			data_container->texture_gabarite_on
		);
	}
	else
	{
		NS_EGraphicCore::set_active_color(1.0f, 1.0f, 1.0f, 1.0f);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			((EntityButton*)_entity)->button_gabarite->world_position_x,
			((EntityButton*)_entity)->button_gabarite->world_position_y,

			((EntityButton*)_entity)->button_gabarite->size_x,
			((EntityButton*)_entity)->button_gabarite->size_y,

			data_container->texture_gabarite_off
		);
	}
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
			data->pointer_to_color_box_group->region_gabarite->world_position_x + 0.0f,
			data->pointer_to_color_box_group->region_gabarite->world_position_y + 0.0f,
			data->pointer_to_color_box_group->region_gabarite->size_x - 0.0f,
			data->pointer_to_color_box_group->region_gabarite->size_y - 0.0f,
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
	}
}

void EDataActionCollection::action_draw_stored_color_as_box(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if ((_custom_data != nullptr) && (_custom_data->data_container != nullptr))
	{
		EDataContainer_Button_StoreColor* data = static_cast<EDataContainer_Button_StoreColor*>(_custom_data->data_container);
		EntityButton* button = static_cast<EntityButton*>(_entity);
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

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
				NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,
				button->button_gabarite->world_position_x + button->parent_button_group->border_left,
				button->button_gabarite->world_position_y + button->parent_button_group->border_bottom,
				button->button_gabarite->size_x - button->parent_button_group->border_left - button->parent_button_group->border_right,
				button->button_gabarite->size_y - button->parent_button_group->border_bottom - button->parent_button_group->border_up - 15.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}

	}
}

void EDataActionCollection::action_transfer_pointer_to_color_data_container(Entity* _entity, ECustomData* _custom_data, float _d)
{
	static_cast<EDataContainer_Group_ColorEditor*>(EButtonGroup::color_editor_group->data_container)->target_data_container_with_color
	=
	static_cast<EDataContainer_Button_StoreColor*>(_custom_data->data_container);
}

void EDataActionCollection::action_unbing_color(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup*						parent_group	= static_cast<EntityButton*>(_entity)->parent_button_group;
	EButtonGroup*						root_group		= parent_group->root_group;
	EDataContainer_Group_ColorEditor*	group_data		= static_cast<EDataContainer_Group_ColorEditor*>(root_group->data_container);
	EDataContainer_Button_StoreColor*	target_button_data		= group_data->target_data_container_with_color;

	//get current color
	Helper::HSVRGBAColor* original_color = target_button_data->stored_color;

	//create non-binded color
	Helper::HSVRGBAColor* HRA_color = new Helper::HSVRGBAColor();
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
		group_data->pointer_to_color_collection_group->selected_button = nullptr;
	}

}

void EDataActionCollection::action_create_new_color(Entity* _entity, ECustomData* _custom_data, float _d)
{

	EButtonGroup* parent_group = static_cast<EntityButton*>(_entity)->parent_button_group;
	EButtonGroup* root_group = parent_group->root_group;
	EDataContainer_Group_ColorEditor* group_data = static_cast<EDataContainer_Group_ColorEditor*>(root_group->data_container);
	EDataContainer_Button_StoreColor* button_data = group_data->target_data_container_with_color;

	//get current color
	Helper::HSVRGBAColor* original_color = group_data->work_color;

	//create non-binded color
	Helper::HSVRGBAColor			HRA_color;
	Helper::HRA_color_collection*	HRA_collection = new Helper::HRA_color_collection();

	HRA_color.set_color(original_color);//apply old color to non-binded
	HRA_collection->target_color = HRA_color;

	//button_data->stored_color = &HRA_color;
	
	

	Helper::registered_color_list.push_back(HRA_collection);

	//group_data->crosshair_slider_data_container->target_pointer_x = &HRA_color.h;
	//group_data->crosshair_slider_data_container->target_pointer_y = &HRA_color.s;

	//group_data->slider_data_value_container->pointer_to_value = &HRA_color.v;
	//group_data->slider_data_alpha_container->pointer_to_value = &HRA_color.a;

	//group_data->work_color = &HRA_color;

	EntityButton* jc_button = EntityButton::create_named_color_button
	(
		//*color_collection->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

		new ERegionGabarite(80.0f, 38.0f),
		group_data->pointer_to_color_collection_group,
		EFont::font_list[0],
		EGUIStyle::active_style,
		"Цвет",
		HRA_collection,
		&HRA_collection->target_color,
		ColorButtonMode::CBM_SELECT_COLOR
	);
	//Entity::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_button);
	group_data->pointer_to_color_collection_group->button_list.push_back(jc_button);
	EButtonGroup::refresh_button_group(root_group);	

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
			//EInputCore::logger_simple_info("window list");
			for (EButtonGroup* bg : w->button_group_list)
			{
				//EInputCore::logger_simple_info("button group list");
				for (group_window_resize_action gwra : bg->actions_on_resize_window)
				{
					//EInputCore::logger_simple_info("try call GWRA");
					gwra(bg);
				}
			}
		}
	}
}

void EDataActionCollection::action_invoke_data_entity_group_action(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if
	(
		(static_cast<EntityButton*>(_entity)->parent_button_group != nullptr)
		&&
		(static_cast<EntityButton*>(_entity)->parent_button_group->root_group != nullptr)
	)
	{
		//data container in root group							//cast to button
		static_cast<EDataContainer_Group_DataEntitiesSearch*>(static_cast<EntityButton*>(_entity)->parent_button_group->root_group->data_container)->
		action_on_select_for_button(_entity, _custom_data, _d);
	}
}

void EDataActionCollection::action_set_button_group_as_active(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EDataContainer_Button_OpenButtonGroup* button_data = static_cast<EDataContainer_Button_OpenButtonGroup*>(_custom_data->data_container);
	button_data->target_group->is_active = true;
}

void EDataActionCollection::action_switch_boolean_value(Entity* _entity, ECustomData* _custom_data, float _d)
{
	*(static_cast<EDataContainer_Button_BoolSwitcher*>(_custom_data->data_container)->target_value)
	=
	!*(static_cast<EDataContainer_Button_BoolSwitcher*>(_custom_data->data_container)->target_value);
}




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
	EInputCore::logger_simple_info("deleting clickable area");
	if (region_gabarite != nullptr)
	{
		(region_gabarite->pointers_to_this_object)--;

		EInputCore::logger_param("pointers left", region_gabarite->pointers_to_this_object);

		if (region_gabarite->pointers_to_this_object <= 0)
		{
			delete region_gabarite;
			EInputCore::logger_simple_success("deleting clickable area");
		}
	}

	delete catched_side_left;
	delete catched_side_right;
	delete catched_side_up;
	delete catched_side_down;
	delete catched_side_mid;
	delete catched_body;
	delete have_rama;
	delete any_visual_changes;
	delete[] can_catch_side;


		
		//region = nullptr;
	

	//if (text_area != nullptr)
	//{delete text_area;}

	//if (!sprite_layer_list.empty())
	//{
	//	for (ESpriteLayer* layer : sprite_layer_list)
	//	{
	//		delete layer;
	//	}
	//	sprite_layer_list.clear();
	//	sprite_layer_list.shrink_to_fit();
	//}

	if (internal_sprite_layer != nullptr)
	{delete internal_sprite_layer;}

	//for (data_action_pointer dap:actions_on_click_list)
	//{delete &dap;}
	//actions_on_click_list.clear();

	//for (data_action_pointer dap:actions_on_right_click_list)
	//{delete &dap;}
	//actions_on_right_click_list.clear();




	
	//for (data_action_pointer dap:actions_on_right_click_list)
	//{delete &dap;}
	//actions_on_right_click_list.clear();



	

	//delete &parent_entity;
	//delete &parent_custom_data;



	delete catch_offset_x;
	delete catch_offset_y;

	//delete &batcher_for_default_draw;
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
				*catched_side_left = catched_side_by_mouse
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
				*catched_side_left = false;
			}



			if (can_catch_side[ClickableRegionSides::CRS_SIDE_RIGHT])
			{

				*catched_side_right = catched_side_by_mouse
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
				*catched_side_right = false;
			}



			if (can_catch_side[ClickableRegionSides::CRS_SIDE_DOWN])
			{
				*catched_side_down = catched_side_by_mouse
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
				*catched_side_down = false;
			}


			if (can_catch_side[ClickableRegionSides::CRS_SIDE_UP])
			{
				*catched_side_up = catched_side_by_mouse
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
				*catched_side_up = false;
			}

			if (can_catch_side[ClickableRegionSides::CRS_SIDE_MID])
			{
				*catched_side_mid = catched_side_by_mouse
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
				*catched_side_mid = false;
			}

			if ((can_catch_side[ClickableRegionSides::CRS_SIDE_BODY]) && (!any_catch))
			{
				*catched_body = catched_side_by_mouse
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
				*catched_body = false;
			}

			*catch_offset_x = EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom - region_gabarite->world_position_x;
			*catch_offset_y = EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom - region_gabarite->world_position_y;
		}
		else
		{

			if (*catched_side_left)
			{
				region_gabarite->size_x -= EInputCore::MOUSE_SPEED_X;
				translate_clickable_region(EInputCore::MOUSE_SPEED_X, 0.0f, 0.0f, true);
			}

			if (*catched_side_right)
			{
				region_gabarite->size_x += EInputCore::MOUSE_SPEED_X;
				redraw_text();
			}

			if (*catched_side_down)
			{
				translate_clickable_region(0.0f, EInputCore::MOUSE_SPEED_Y, 0.0f, true);
				region_gabarite->size_y -= EInputCore::MOUSE_SPEED_Y;
			}

			if (*catched_side_up)
			{
				region_gabarite->size_y += EInputCore::MOUSE_SPEED_Y;
				redraw_text();
			}

			if (*catched_side_mid)
			{
				translate_clickable_region(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f, true);
			}

			if ((*catched_side_left) || (*catched_side_right) || (*catched_side_up) || (*catched_side_down) || (*catched_side_mid))
			{


			}
		}



	if
	(
		(
			(*catched_side_left)
			||
			(*catched_side_right)
			||
			(*catched_side_up)
			||
			(*catched_side_down)
			||
			(*catched_side_mid)
			||
			(*catched_body)
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

	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr) {s_layer->translate_sprite_layer(_x, _y, _z, false);}

	if (text_area != nullptr) { text_area->translate(_x, _y, 0.0f, false); }
}

EClickableArea* EClickableArea::create_default_clickable_region(ERegionGabarite* _gabarite, Entity* _parent_entity, ECustomData* _custom_data)
{
	EClickableArea* jc_clickable_area = new EClickableArea();

	ERegionGabarite::set_region_gabarite (&jc_clickable_area->region_gabarite, _gabarite);

	jc_clickable_area->parent_entity = _parent_entity;
	jc_clickable_area->parent_custom_data = _custom_data;

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

	//left click
	for (data_action_pointer dap : actions_on_click_list)
	if
	(
		(dap != nullptr)
		&&
		(parent_entity != nullptr)
		&&
		(EButtonGroup::focused_button_group == ((EntityButton*)parent_entity)->parent_button_group)
		&&
		(overlapped_by_mouse(this, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
		&&
		(EInputCore::mouse_button_pressed_once(GLFW_MOUSE_BUTTON_LEFT))
	)
	{
		dap(parent_entity, parent_custom_data, _d);
	}

	//right click
	for (data_action_pointer dap : actions_on_right_click_list)
	if
	(
		(dap != nullptr)
		&&
		(parent_entity != nullptr)
		&&
		(EButtonGroup::focused_button_group == ((EntityButton*)parent_entity)->parent_button_group)
		&&
		(overlapped_by_mouse(this, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
		&&
		(EInputCore::mouse_button_pressed_once(GLFW_MOUSE_BUTTON_RIGHT))
	)
	{
		dap(parent_entity, parent_custom_data, _d);
	}

	if (text_area != nullptr)
	{
		text_area->update(_d);
	}
}

void EClickableArea::draw()
{
	//if ((parent_custom_data != nullptr)&&(*parent_custom_data->is_second_pass)) { EInputCore::logger_simple_info("idiot?"); }
	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* s_layer : sprite_layer_list)
		{
			s_layer->transfer_vertex_buffer_to_batcher();
		}
	}
	
	if ((batcher_for_default_draw != nullptr) && (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT)))
	{
		if (EClickableArea::overlapped_by_mouse(this, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
		{
			NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.2f);

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
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_left));
		//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_left)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
		//if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
		if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			region_gabarite->world_position_x - 2.0f,
			region_gabarite->world_position_y,

			2.0f,
			region_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_right));
		//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_right)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
		if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			region_gabarite->world_position_x + region_gabarite->size_x,
			region_gabarite->world_position_y,

			2.0f,
			region_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_down));
		//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_down)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
		if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			region_gabarite->world_position_x - 2.0f,
			region_gabarite->world_position_y - 2.0f,

			region_gabarite->size_x + 4.0f,
			2.0f,
			
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_up));
		//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_up)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
		if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 1);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			region_gabarite->world_position_x - 2.0f,
			region_gabarite->world_position_y + region_gabarite->size_y,

			region_gabarite->size_x + 4.0f,
			2.0f,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_mid));
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
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_body));
		//if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_body)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }
		if (active_clickable_region == this) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		if (*catched_body)
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
	region_gabarite->world_position_x = _x + region_gabarite->offset_x;
	region_gabarite->world_position_y = _y + region_gabarite->offset_y;
	region_gabarite->world_position_z = _z + region_gabarite->offset_z;

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
	/*delete offset_x;
	delete offset_y;
	delete offset_z;

	delete size_x;
	delete size_y;

	delete world_position_x;
	delete world_position_y;
	delete world_position_z;*/

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

	if (_source_region->root_owner == nullptr)
	{
		_source_region->root_owner = _source_region;
	}

	if (*_target_region != _source_region)
	{
		
		//EInputCore::logger_simple_success("target != source");
		//old region lose 1 pointer to him
		

		//target region lose 1 owner
		if (*_target_region != nullptr)
		{
			//EInputCore::logger_simple_success("decrease");
			(*_target_region)->pointers_to_this_object--; 
		}
		else
		{
			//EInputCore::logger_simple_error("target is NULL!");
		}

		//this region have 1 more pointers to him
		(_source_region->pointers_to_this_object)++;
		
	}
	else
	{
		//EInputCore::logger_simple_error("target = source");
	}

	*_target_region = _source_region;

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
			delete clickable_area;
			//clickable_area = nullptr;
		}
	}
	clickable_area_list.clear();
	clickable_area_list.shrink_to_fit();

	
	//for (data_action_pointer dap : actions_on_change_style)	{delete &dap;}
	actions_on_change_style.clear();
	actions_on_change_style.shrink_to_fit();

	
	//for (data_action_pointer dap : actions_on_draw)			{delete	&dap;}
	actions_on_draw.clear();
	actions_on_draw.shrink_to_fit();

	//for (data_action_pointer dap : actions_on_update)		{delete &dap;}
	actions_on_update.clear();
	actions_on_update.shrink_to_fit();

	if (data_container != nullptr)
	{delete data_container;}

}

void ECustomData::draw()//(if (but->description_data != nullptr) { but->description_data->draw(); })
{


	if ((!*disable_draw)&&(!*is_second_pass))
	{
		
		//if (_second_pass) { EInputCore::logger_simple_info("???"); }


		for (EClickableArea* clickable_area : clickable_area_list)
		if (clickable_area != nullptr)
		{clickable_area->draw();}

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

	if ((!*disable_draw) && (*is_second_pass))
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
	delete message;
}

EDataContainerScrollBar::~EDataContainerScrollBar()
{
	delete max_value;
	delete &value_pointer;

	delete current_percent;
}

	//static registere section
	std::string		ETextParser::data_array[1000];
	std::string		ETextParser::action_text_buffer;
	std::string		ETextParser::value_text_buffer;

	EDataEntity*	ETextParser::last_created_data_entity;
	EDataTag*		ETextParser::last_created_data_tag;
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
			if (raw_char == '"')
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
	writabro.open("data_entity_for_explicits.txt");

	std::ifstream file;
	std::string str;

	file.open(_file);

	std::string	temp_string	= "";
	char		target_sym	= 0;

	std::string temp_array[256];
	int temp_array_id = 0;

	while (std::getline(file, str))
	{
		temp_array_id = 0;

		for (int i = 0; i < str.length(); i++)
		{
			
			target_sym = str[i];

			if (target_sym != '\t')
			{
				temp_string += target_sym;
			}
			else
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
			writabro << "\t[tag]\"data type\"\t[value]\"Explicit\"" << std::endl;
			writabro << std::endl;
			writabro << "\t[tag]\"base name\"\t[value]\"" << temp_array[1] << "\"" << std::endl;
			writabro << std::endl;
			writabro << "\t[tag]\"name EN\"\t\t[value]\"[" << temp_array[1] << "]" << temp_array[3] << "\"" << std::endl;
			writabro << "\t[tag]\"name RU\"\t\t[value]\"[" << temp_array[6] << "]" << temp_array[8] << "\"" << std::endl;
			writabro << std::endl;
			writabro << "\t[tag]\"icon path\"\t[value]\"Active\"" << std::endl;
		}
	}

	file.close();

	
	
	//for 
	writabro.close();
}

void ETextParser::do_action(std::string _action_text, std::string _value)
{
	//EInputCore::logger_simple_info("do action");
	//EInputCore::simple_logger_with_parameter("action:", _action_text);
	//EInputCore::simple_logger_with_parameter("value:", _value);

	if (_action_text == "ADD_NEW_DATA_ENTITY")
	{
		last_created_data_entity = new EDataEntity();

		EDataEntity::data_entity_list.push_back(last_created_data_entity);
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
		last_created_data_tag->tag_value_list.push_back(new std::string  (_value));
	}
}

EDataContainerRadialButton::~EDataContainerRadialButton()
{
	delete min_value;
	delete max_value;
	delete current_percent;
	delete stored_type;
}

std::string EStringUtils::to_lower(std::string _text)
{
	std::string output_string = "";
	int char_id = 0;

	//EInputCore::logger_param("drunk?", _text.length());
	for (int i = 0; i < _text.length(); i++)
	{
		char_id = (int)_text[i];
		std::string drunker = "" + _text[i];

		//EInputCore::logger_param("char", drunker);
		//EInputCore::logger_param("id", char_id);
		//std::cout << " " << _text[i] << std::endl;

		if
		(
			(
				(char_id >= 65)
				&&
				(char_id <= 90)
			)
			||
			(
				(char_id >= -64)
				&&
				(char_id <= -33)
			)
		)
		{
			output_string += (char)(char_id + 32);
		}
		else
		{
			output_string += _text[i];
		}
	}
	return output_string;
}
