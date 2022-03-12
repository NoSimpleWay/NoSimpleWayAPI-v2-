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


EClickableRegion* EClickableRegion::active_clickable_region = nullptr;

ERegionGabarite* ERegionGabarite::temporary_gabarite;

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
	

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_W))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{
		_entity->translate_entity(0.0f, 100.0f * _d, 0.0f);

	};

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_S))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{
		_entity->translate_entity(0.0f, -100.0f * _d, 0.0f);

	};

	if
	(
		(EInputCore::key_pressed(GLFW_KEY_Z))
		&&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{ 
		
		NS_ERenderCollection::generate_brick_texture(_custom_data->clickable_region_list[0]->region, _entity->sprite_layer_list[0], NS_DefaultGabarites::texture_lead_and_gold);
		_entity->set_world_position(*_entity->world_position_x, *_entity->world_position_y, *_entity->world_position_z);
		_entity->generate_vertex_buffer_for_all_sprite_layers();
		
		
	}
}

void EDataActionCollection::action_update_slider(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton* entity_button = ((EntityButton*)_entity);
	EDataContainerScrollBar* data_bar = ((EDataContainerScrollBar*)_custom_data->data_container);

	//EInputCore::logger_simple_success("@");

	*entity_button->button_gabarite->size_y = *entity_button->parent_button_group->region->size_y;



	*_entity->offset_x = *entity_button->parent_button_group->region->size_x - *entity_button->button_gabarite->size_x - 2.0f;



	*_entity->world_position_x
	=
	*_entity->offset_x
	+
	*entity_button->parent_button_group->region->world_position_x;

	*data_bar->max_value
	=
	max(0.0f, *entity_button->parent_button_group->highest_point_y - *entity_button->parent_button_group->region->size_y);

	if (*_entity->custom_data_list.at(0)->clickable_region_list.at(0)->catched_body)
	{
		*_custom_data->get_sprite_frame_by_id(0, 0, 0)->active_frame_id = 1;

		if (EInputCore::mouse_button_state[GLFW_MOUSE_BUTTON_LEFT] != GLFW_RELEASE)
		{
			*_entity->custom_data_list.at(0)->clickable_region_list.at(0)->region->offset_y += EInputCore::MOUSE_SPEED_Y;

			*_entity->custom_data_list.at(0)->clickable_region_list.at(0)->region->offset_y
				=
				max(*entity_button->parent_button_group->border_bottom, *_entity->custom_data_list.at(0)->clickable_region_list.at(0)->region->offset_y);

			*_entity->custom_data_list.at(0)->clickable_region_list.at(0)->region->offset_y
				=
				min
				(
					*entity_button->parent_button_group->region->size_y
					-
					*_entity->custom_data_list.at(0)->clickable_region_list.at(0)->region->size_y
					-
					*entity_button->parent_button_group->border_up,
					*_entity->custom_data_list.at(0)->clickable_region_list.at(0)->region->offset_y
				);


			*data_bar->value_pointer
				=
				round
				(
					(*_entity->custom_data_list.at(0)->clickable_region_list.at(0)->region->offset_y - *entity_button->parent_button_group->border_bottom)
					/
					(
						*entity_button->parent_button_group->region->size_y
						-
						*_custom_data->clickable_region_list.at(0)->region->size_y
						+
						*entity_button->parent_button_group->border_up
					)
					*
					*data_bar->max_value * -1.0f
				);

			//EInputCore::logger_param("max value", *data_bar->max_value);
			//EInputCore::logger_param("scroll value", *data_bar->value_pointer);


			//*entity_button->parent_button_group->scroll_y += 100.0f * _d;

			entity_button->parent_button_group->realign_all_buttons();
			entity_button->parent_button_group->set_world_position_and_redraw();

			//_entity->calculate_all_world_positions();
		}
	}
	else
	{
		*_custom_data->clickable_region_list.at(0)->sprite_layer_list.at(0)->sprite_frame_list.at(0)->active_frame_id = 0;

		_entity->set_world_position(*_entity->world_position_x, *_entity->world_position_y, *_entity->world_position_z);
		_entity->generate_vertex_buffer_for_all_sprite_layers();
	}

	//*_entity->world_position_x = *entity_button->parent_button_group->region->world_position_x + *entity_button->parent_button_group->region->size_x - *entity_button->button_gabarite->size_x;
	//*_entity->world_position_y = *entity_button->parent_button_group->region->world_position_y;

	//_entity->custom_data_list.at(0)->get_sprite_by_id(0, 0, 0, 0)->generate_vertex_buffer_for_sprite_layer("");
	
	//_custom_data->clickable_region_list.at(0)->sprite_layer_list.at(0)->generate_vertex_buffer_for_sprite_layer("");



	//_custom_data->get_sprite_layer_by_id(0, 0)->generate_vertex_buffer_for_sprite_layer("");
	
	

	//_entity->


}

/*
bool EClickableRegion::overlapped_by_mouse(EClickableRegion* _region)
{
	return false;
}
*/

EClickableRegion::EClickableRegion()
{
	
	
}

EClickableRegion::~EClickableRegion()
{
}

bool EClickableRegion::overlapped_by_mouse(EClickableRegion* _region, float _offset_x, float _offset_y, float _zoom)
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
				(EInputCore::MOUSE_POSITION_X >= ((double)*_region->region->world_position_x + (double)_offset_x) * _zoom)
				&&
				(EInputCore::MOUSE_POSITION_X <= ((double)*_region->region->world_position_x + (double)*_region->region->size_x + _offset_x) * _zoom)

				&&

				(EInputCore::MOUSE_POSITION_Y >= ((double)*_region->region->world_position_y + _offset_y) * _zoom)
				&&
				(EInputCore::MOUSE_POSITION_Y <= ((double)*_region->region->world_position_y + *_region->region->size_y + _offset_y) * _zoom)
			)
		)
	{
		return true;
	}

	return false;
}

bool EClickableRegion::catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance)
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

void EClickableRegion::check_all_catches()
{
	//bool previvous_state = false;
	bool any_catch = false;
	if (!EInputCore::MOUSE_BUTTON_LEFT)
	{
			if (can_catch_side[ClickableRegionSides::CRS_SIDE_LEFT])
			{
				*catched_side_left = catched_side_by_mouse
				(
					*region->world_position_x,
					*region->world_position_y,

					0.0f,
					*region->size_y,

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
					*region->world_position_x + *region->size_x,
					*region->world_position_y,

					0.0f,
					*region->size_y,

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
					*region->world_position_x,
					*region->world_position_y,

					*region->size_x,
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
					*region->world_position_x,
					*region->world_position_y + *region->size_y,

					*region->size_x,
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
					*region->world_position_x + *region->size_x / 2.0f,
					*region->world_position_y + *region->size_y / 2.0f,

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
					*region->world_position_x,
					*region->world_position_y,

					*region->size_x,
					*region->size_y,

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
			
			*catch_offset_x = EInputCore::MOUSE_POSITION_X - *region->world_position_x;
			*catch_offset_y = EInputCore::MOUSE_POSITION_Y - *region->world_position_y;
	}
	else
	{

		if (*catched_side_left)
		{
			*region->size_x			-= EInputCore::MOUSE_SPEED_X;
			translate_clickable_region(EInputCore::MOUSE_SPEED_X, 0.0f, 0.0f, true);
		}

		if (*catched_side_right)
		{
			*region->size_x += EInputCore::MOUSE_SPEED_X;
			redraw_text();
		}

		if (*catched_side_down)
		{
			translate_clickable_region(0.0f, EInputCore::MOUSE_SPEED_Y, 0.0f, true);
			*region->size_y -= EInputCore::MOUSE_SPEED_Y;
		}

		if (*catched_side_up)
		{
			*region->size_y += EInputCore::MOUSE_SPEED_Y;
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
		)
	)
	{

		if (EClickableRegion::active_clickable_region == nullptr) { EClickableRegion::active_clickable_region = this; }
	}
	else
	{
		if (EClickableRegion::active_clickable_region == this) { EClickableRegion::active_clickable_region = nullptr; }
	}
	
}

void EClickableRegion::translate_clickable_region(float _x, float _y, float _z, bool _move_offset)
{
	if (region != nullptr)
	{
		*region->world_position_x += _x;
		*region->world_position_y += _y;

		if (_move_offset)
		{
			*region->offset_x += _x;
			*region->offset_y += _y;
		}
	}

	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr) {s_layer->translate_sprite_layer(_x, _y, _z, false);}



	if (text_area != nullptr) { text_area->translate(_x, _y); }
}

EClickableRegion* EClickableRegion::create_default_clickable_region(ERegionGabarite* _gabarite, Entity* _parent_entity, ECustomData* _custom_data)
{
	EClickableRegion* jc_clickable_region = new EClickableRegion();

	jc_clickable_region->region = _gabarite;
	jc_clickable_region->parent_entity = _parent_entity;
	jc_clickable_region->parent_custom_data = _custom_data;

	jc_clickable_region->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	return jc_clickable_region;
}

void EClickableRegion::update(float _d)
{
	//if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
	{
		check_all_catches();
	}

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

	if (text_area != nullptr)
	{
		text_area->update(_d);
	}
}

void EClickableRegion::draw()
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
		if (EClickableRegion::overlapped_by_mouse(this, NS_EGraphicCore::current_offset_x, NS_EGraphicCore::current_offset_y, NS_EGraphicCore::current_zoom))
		{
			NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.2f);

			ERenderBatcher::check_batcher(batcher_for_default_draw);

			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,

				*region->world_position_x,
				*region->world_position_y,

				*region->size_x,
				*region->size_y,

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

			*region->world_position_x - 2.0f,
			*region->world_position_y,

			2.0f,
			*region->size_y,

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

			*region->world_position_x + *region->size_x,
			*region->world_position_y,

			2.0f,
			*region->size_y,

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

			*region->world_position_x - 2.0f,
			*region->world_position_y - 2.0f,

			*region->size_x + 4.0f,
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

			*region->world_position_x - 2.0f,
			*region->world_position_y + *region->size_y,

			*region->size_x + 4.0f,
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

			*region->world_position_x + *region->size_x / 2.0f - 3.0f,
			*region->world_position_y + *region->size_y / 2.0f - 3.0f,

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

				*region->world_position_x,
				*region->world_position_y,

				*region->size_x,
				*region->size_y,

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

void EClickableRegion::redraw_text()
{
	//for (ETextArea* t_area:text_area)
	if (text_area != nullptr)
	{
		text_area->generate_rows();
		text_area->generate_text();
	}
}

void EClickableRegion::clickable_region_set_world_positions(float _x, float _y, float _z)
{
	*region->world_position_x = _x + *region->offset_x;
	*region->world_position_y = _y + *region->offset_y;
	*region->world_position_z = _z + *region->offset_z;

	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr)
	{
		s_layer->sprite_layer_set_world_position(*region->world_position_x, *region->world_position_y, *region->world_position_z);
	}
}

ERegionGabarite::ERegionGabarite()
{
}

ERegionGabarite::~ERegionGabarite()
{
}

ERegionGabarite::ERegionGabarite(float _offset_x, float _offset_y, float _size_x, float _size_y)
{
	*offset_x = _offset_x;
	*offset_y = _offset_y;

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

ECustomData::ECustomData()
{
}

ECustomData::~ECustomData()
{
}

void ECustomData::draw()
{
	if (!clickable_region_list.empty())
	for (EClickableRegion* clickable_region : clickable_region_list)
	if (clickable_region != nullptr)
	{
		clickable_region->draw();
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

	for (EClickableRegion* cl_region : clickable_region_list)
	{
		if (cl_region != nullptr)
		{
			cl_region->update(_d);
		}
	}


}

void ECustomData::translate_custom_data(float _x, float _y, float _z, bool _move_offset)
{
	for (EClickableRegion* cl_region : clickable_region_list)
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
		(!clickable_region_list.empty())
		&&
		(!clickable_region_list.at(_clickable_region_id)->sprite_layer_list.empty())
	)
	{
		return clickable_region_list.at(_clickable_region_id)->sprite_layer_list.at(_sprite_layer_id);
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
