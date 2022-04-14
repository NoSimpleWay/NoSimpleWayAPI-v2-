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
		_entity->translate_entity(0.0f, 1000.0f * _d, 0.0f);

	};

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_S))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{
		_entity->translate_entity(0.0f, -1000.0f * _d, 0.0f);

	};

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_Z))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{ 
		
		NS_ERenderCollection::generate_brick_texture(_custom_data->clickable_area_list[0]->region_gabarite, _entity->sprite_layer_list[0], NS_DefaultGabarites::texture_lead_and_gold);
		_entity->set_world_position(*_entity->world_position_x, *_entity->world_position_y, *_entity->world_position_z);
		_entity->generate_vertex_buffer_for_all_sprite_layers();
		
		
	}
}

void EDataActionCollection::action_update_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton* entity_button = ((EntityButton*)_entity);
	EDataContainerScrollBar* data_bar = ((EDataContainerScrollBar*)_custom_data->data_container);

	//EInputCore::logger_simple_success("@");

	*entity_button->button_gabarite->size_y = *entity_button->parent_button_group->region_gabarite->size_y;



	*_entity->offset_x
	=
	*entity_button->parent_button_group->region_gabarite->size_x
	-
	*entity_button->button_gabarite->size_x
	-
	*entity_button->parent_button_group->border_right;



	*_entity->world_position_x
	=
	*_entity->offset_x
	+
	*entity_button->parent_button_group->region_gabarite->world_position_x;

	*data_bar->max_value
	=
	max
	(
		0.0f,
		*entity_button->parent_button_group->highest_point_y
		-
		(
			*entity_button->parent_button_group->region_gabarite->size_y
			-
			//*entity_button->parent_button_group->border_bottom
			//-
			*entity_button->parent_button_group->border_up
		)
	);

	//*data_bar->max_value = 1000.0f;
	
	
	if (*data_bar->max_value > 0.0f)
	{


		*_entity->disable_draw = false;
	}
	else
	{
		*_entity->disable_draw = true;
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
				*_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y += EInputCore::MOUSE_SPEED_Y;
			}

			if (*_custom_data->get_sprite_frame_by_id(0, 0, 0)->active_frame_id != 1)
			{
				*_custom_data->get_sprite_frame_by_id(0, 0, 0)->active_frame_id = 1;

				_entity->set_world_position(*_entity->world_position_x, *_entity->world_position_y, *_entity->world_position_z);
				_entity->generate_vertex_buffer_for_all_sprite_layers();
			}
		}

		if
		(
			(EInputCore::scroll_direction != 0)
			&&
			(EButtonGroup::focused_button_group_with_slider == entity_button->parent_button_group)
			&&
			(*entity_button->parent_button_group->region_gabarite->size_y > 10.0f)
		)
		{
			*_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
			+=
			(EInputCore::scroll_direction * EInputCore::scroll_direction * EInputCore::scroll_direction)
			*
			(*entity_button->parent_button_group->region_gabarite->size_y  / *data_bar->max_value)
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
			*_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
				=
				max(*entity_button->parent_button_group->border_bottom, *_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y);

			*_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
				=
				min
				(
					*entity_button->parent_button_group->region_gabarite->size_y
					-
					*_custom_data->clickable_area_list.at(0)->region_gabarite->size_y
					-
					*entity_button->parent_button_group->border_up,
					*_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
				);

			*data_bar->current_percent
				=
				//head position (990 - 7) = 983
				(
					*_custom_data->clickable_area_list.at(0)->region_gabarite->offset_y
					-
					*entity_button->parent_button_group->border_bottom
					)
				/
				(
					*entity_button->parent_button_group->region_gabarite->size_y//1000
					-
					*_custom_data->clickable_area_list.at(0)->region_gabarite->size_y//39
					-
					*entity_button->parent_button_group->border_up
					-
					*entity_button->parent_button_group->border_bottom//7
					);

			*data_bar->current_percent = min(*data_bar->current_percent, 1.0f);

			*data_bar->value_pointer
				=
				round
				(
					*data_bar->current_percent
					*
					*data_bar->max_value
					*
					-1.0f
				);


			//EInputCore::logger_param("HPy", *entity_button->parent_button_group->highest_point_y);
			EButtonGroup::refresh_button_group(entity_button->parent_button_group);
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

			_entity->set_world_position(*_entity->world_position_x, *_entity->world_position_y, *_entity->world_position_z);
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

void EDataActionCollection::action_change_style(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//cast to button entity
	EntityButton*	target_button = ((EntityButton*)_entity);

	//get "slider" sprite
	ESprite*		target_sprite = target_button->get_sprite_from_entity(0, 0, 0);

	if (target_sprite != nullptr)
	{													
		target_sprite->set_texture_gabarite
		(
			target_button->			//button, which change style
			parent_button_group->	//group, which contain this button
			selected_style->		//style, used by group
			slider_bg->				//"brick style" for sliders
			main_texture			//texture from "brick style"
		);
	}									

}

void EDataActionCollection::action_highlight_button_if_overlap(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (((EntityButton*)_entity)->button_gabarite->overlapped_by_mouse())
	{
		NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.35f);
		ERenderBatcher::check_batcher(NS_EGraphicCore::default_batcher_for_drawing);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			*((EntityButton*)_entity)->button_gabarite->world_position_x,
			*((EntityButton*)_entity)->button_gabarite->world_position_y,

			*((EntityButton*)_entity)->button_gabarite->size_x,
			*((EntityButton*)_entity)->button_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
	
		);
	}
}

void EDataActionCollection::action_select_this_style(Entity* _entity, ECustomData* _custom_data, float _d)
{
	for (EWindow* window : EWindow::window_list)
	for (EButtonGroup* group:window->group_list)
	{
		EButtonGroup::change_style
		(
			group,
			((EntityButton*)_entity)->parent_button_group->selected_style
		);
	}
}

void EDataActionCollection::action_close_root_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if
	(
		(	((EntityButton*)_entity)->parent_button_group != nullptr	)
		&&
		(	((EntityButton*)_entity)->parent_button_group->root_group != nullptr	)
	)
	{
		*(((EntityButton*)_entity)->parent_button_group->root_group->is_active) = false;
	}
}

void EDataActionCollection::action_delete_entity(Entity* _entity, ECustomData* _custom_data, float _d)
{
	*_entity->need_remove = true;
	//((EWindowMain*)EWindow::window_list[0])->

	//for (TestObject* to : EWindow::window_list[0]->test_vector)
	//{
	//	delete to;
	//}

	//EInputCore::logger_simple_try("set 'need remove' flag");
}

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
		(*region_gabarite->pointers_to_this_object)--;

		EInputCore::logger_param("pointers left", *region_gabarite->pointers_to_this_object);

		if (*region_gabarite->pointers_to_this_object <= 0)
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
				(EInputCore::MOUSE_POSITION_X >= ((double)*_region->region_gabarite->world_position_x + (double)_offset_x) * _zoom)
				&&
				(EInputCore::MOUSE_POSITION_X <= ((double)*_region->region_gabarite->world_position_x + (double)*_region->region_gabarite->size_x + _offset_x) * _zoom)

				&&

				(EInputCore::MOUSE_POSITION_Y >= ((double)*_region->region_gabarite->world_position_y + _offset_y) * _zoom)
				&&
				(EInputCore::MOUSE_POSITION_Y <= ((double)*_region->region_gabarite->world_position_y + *_region->region_gabarite->size_y + _offset_y) * _zoom)
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
					*region_gabarite->world_position_x,
					*region_gabarite->world_position_y,

					0.0f,
					*region_gabarite->size_y,

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
					*region_gabarite->world_position_x + *region_gabarite->size_x,
					*region_gabarite->world_position_y,

					0.0f,
					*region_gabarite->size_y,

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
					*region_gabarite->world_position_x,
					*region_gabarite->world_position_y,

					*region_gabarite->size_x,
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
					*region_gabarite->world_position_x,
					*region_gabarite->world_position_y + *region_gabarite->size_y,

					*region_gabarite->size_x,
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
					*region_gabarite->world_position_x + *region_gabarite->size_x / 2.0f,
					*region_gabarite->world_position_y + *region_gabarite->size_y / 2.0f,

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
					*region_gabarite->world_position_x,
					*region_gabarite->world_position_y,

					*region_gabarite->size_x,
					*region_gabarite->size_y,

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

			*catch_offset_x = EInputCore::MOUSE_POSITION_X - *region_gabarite->world_position_x;
			*catch_offset_y = EInputCore::MOUSE_POSITION_Y - *region_gabarite->world_position_y;
		}
		else
		{

			if (*catched_side_left)
			{
				*region_gabarite->size_x -= EInputCore::MOUSE_SPEED_X;
				translate_clickable_region(EInputCore::MOUSE_SPEED_X, 0.0f, 0.0f, true);
			}

			if (*catched_side_right)
			{
				*region_gabarite->size_x += EInputCore::MOUSE_SPEED_X;
				redraw_text();
			}

			if (*catched_side_down)
			{
				translate_clickable_region(0.0f, EInputCore::MOUSE_SPEED_Y, 0.0f, true);
				*region_gabarite->size_y -= EInputCore::MOUSE_SPEED_Y;
			}

			if (*catched_side_up)
			{
				*region_gabarite->size_y += EInputCore::MOUSE_SPEED_Y;
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

		if (EClickableArea::active_clickable_region == nullptr) { EClickableArea::active_clickable_region = this; }
	}
	else
	{
		if (EClickableArea::active_clickable_region == this) { EClickableArea::active_clickable_region = nullptr; }
	}
	
}

void EClickableArea::translate_clickable_region(float _x, float _y, float _z, bool _move_offset)
{
	if (region_gabarite != nullptr)
	{
		*region_gabarite->world_position_x += _x;
		*region_gabarite->world_position_y += _y;

		if (_move_offset)
		{
			*region_gabarite->offset_x += _x;
			*region_gabarite->offset_y += _y;
		}
	}

	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr) {s_layer->translate_sprite_layer(_x, _y, _z, false);}



	if (text_area != nullptr) { text_area->translate(_x, _y); }
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

			ERenderBatcher::check_batcher(batcher_for_default_draw);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				*region_gabarite->world_position_x,
				*region_gabarite->world_position_y,

				*region_gabarite->size_x,
				*region_gabarite->size_y,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_left));
		if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_left)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::check_batcher(batcher_for_default_draw);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			*region_gabarite->world_position_x - 2.0f,
			*region_gabarite->world_position_y,

			2.0f,
			*region_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_right));
		if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_right)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::check_batcher(batcher_for_default_draw);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			*region_gabarite->world_position_x + *region_gabarite->size_x,
			*region_gabarite->world_position_y,

			2.0f,
			*region_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_down));
		if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_down)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::check_batcher(batcher_for_default_draw);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			*region_gabarite->world_position_x - 2.0f,
			*region_gabarite->world_position_y - 2.0f,

			*region_gabarite->size_x + 4.0f,
			2.0f,
			
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_up));
		if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_up)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::check_batcher(batcher_for_default_draw);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			*region_gabarite->world_position_x - 2.0f,
			*region_gabarite->world_position_y + *region_gabarite->size_y,

			*region_gabarite->size_x + 4.0f,
			2.0f,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_mid));
		if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_mid)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		ERenderBatcher::check_batcher(batcher_for_default_draw);

		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,

			*region_gabarite->world_position_x + *region_gabarite->size_x / 2.0f - 3.0f,
			*region_gabarite->world_position_y + *region_gabarite->size_y / 2.0f - 3.0f,

			6.0f,
			6.0f,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);

		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_body));
		if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_body)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

		if (*catched_body)
		{
			ERenderBatcher::check_batcher(batcher_for_default_draw);
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				*region_gabarite->world_position_x,
				*region_gabarite->world_position_y,

				*region_gabarite->size_x,
				*region_gabarite->size_y,

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
	*region_gabarite->world_position_x = _x + *region_gabarite->offset_x;
	*region_gabarite->world_position_y = _y + *region_gabarite->offset_y;
	*region_gabarite->world_position_z = _z + *region_gabarite->offset_z;

	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr)
	{
		s_layer->sprite_layer_set_world_position(*region_gabarite->world_position_x, *region_gabarite->world_position_y, *region_gabarite->world_position_z);
	}
}

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
	*offset_x = _offset_x;
	*offset_y = _offset_y;

	*size_x = _size_x;
	*size_y = _size_y;
}

ERegionGabarite::ERegionGabarite(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y)
{
	*offset_x = _offset_x;
	*offset_y = _offset_y;
	*offset_z = _offset_z;
	
	*world_position_x = _offset_x;
	*world_position_y = _offset_y;
	*world_position_z = _offset_z;

	*size_x = _size_x;
	*size_y = _size_y;
}

ERegionGabarite::ERegionGabarite(float _size_x, float _size_y)
{
	*size_x = _size_x;
	*size_y = _size_y;
}

void ERegionGabarite::translate(float _x, float _y)
{
	*offset_x += _x;
	*offset_y += _y;

	*world_position_x += _x;
	*world_position_y += _y;
}

void ERegionGabarite::set_region_offset_and_size(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y)
{
	*offset_x = _offset_x;
	*offset_y = _offset_y;
	*offset_z = _offset_z;

	*size_x = _size_x;
	*size_y = _size_y;

}

bool ERegionGabarite::overlapped_by_mouse()
{
	if
	(
		(EInputCore::MOUSE_POSITION_X >= *world_position_x)
		&&
		(EInputCore::MOUSE_POSITION_X <= *world_position_x + *size_x)
		&&
		(EInputCore::MOUSE_POSITION_Y >= *world_position_y)
		&&
		(EInputCore::MOUSE_POSITION_Y <= *world_position_y + *size_y)
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
		
		//EInputCore::logger_simple_success("target != source");
		//old region lose 1 pointer to him
		

		if (*_target_region != nullptr)
		{
			//EInputCore::logger_simple_success("decrease");
			((*_target_region)->pointers_to_this_object)--; 
		}
		else
		{
			//EInputCore::logger_simple_error("target is NULL!");
		}

		//this region have 1 more pointers to him
		(*_source_region->pointers_to_this_object)++;
		
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

void ECustomData::draw()
{
	for (data_action_pointer dap : actions_on_draw)
	if (dap != nullptr)
	{
		dap(parent_entity, this, 0.1f);
	}

	if (!clickable_area_list.empty())
	for (EClickableArea* clickable_area : clickable_area_list)
	if (clickable_area != nullptr)
	{
		clickable_area->draw();
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
				if ((raw_char == ']')) { EInputCore::logger_simple_error("** ] **"); }
				if ((raw_char == '[')) { EInputCore::logger_simple_error("** [ **"); }


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
