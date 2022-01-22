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


void EDataActionCollection::action_log_text(Entity* _entity, ECustomData* _custom_data)
{
	EInputCore::logger_param("Message", ((EDataContainerMessage*)_custom_data->data_container)->message);
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
				(_region->master_entity != nullptr)
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

	if (!EInputCore::MOUSE_BUTTON_LEFT)
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

		if (*catched_side_left)
		{
			*region->size_x			-= EInputCore::MOUSE_SPEED_X;
			translate(EInputCore::MOUSE_SPEED_X, 0.0f, 0.0f);
		}

		if (*catched_side_right)
		{
			*region->size_x += EInputCore::MOUSE_SPEED_X;
			redraw_text();
		}

		if (*catched_side_down)
		{
			translate(0.0f, EInputCore::MOUSE_SPEED_Y, 0.0f);
			*region->size_y -= EInputCore::MOUSE_SPEED_Y;
		}

		if (*catched_side_up)
		{
			*region->size_y += EInputCore::MOUSE_SPEED_Y;
			redraw_text();
		}

		if (*catched_side_mid)
		{
			translate(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f);
		}

		if ((*catched_side_left) || (*catched_side_right) || (*catched_side_up) || (*catched_side_down) || (*catched_side_mid))
		{

			//refresh_border_sprites();
			//master_entity->calculate_all_world_positions();
			//internal_sprite_layer->generate_vertex_buffer_for_sprite_layer("refresh sides sprites");
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

void EClickableRegion::translate(float _x, float _y, float _z)
{
	if (region != nullptr)
	{
		*region->offset_x += _x;
		*region->offset_y += _y;

		*region->world_position_x += _x;
		*region->world_position_y += _y;
	}

	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr) {s_layer->translate_sprite_layer(_x, _y, _z);}

	//if (internal_sprite_layer != nullptr) {internal_sprite_layer->translate_sprite_layer(_x, _y, _z);}

	if (text_area != nullptr) { text_area->translate(_x, _y); }
}

void EClickableRegion::update(float _d)
{
	check_all_catches();

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

	if (batcher_for_default_draw != nullptr)
	{
		//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--
		NS_EGraphicCore::set_active_color(NS_EColorUtils::choose_from_two(NS_EColorUtils::COLOR_GREEN, NS_EColorUtils::COLOR_BLACK, *catched_side_left));
		if ((EInputCore::MOUSE_BUTTON_LEFT) && (*catched_side_left)) { NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_BLUE); }

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

void ECustomData::translate(float _x, float _y, float _z)
{
	for (EClickableRegion* cl_region : clickable_region_list)
	if (cl_region != nullptr)
	{
		cl_region->translate(_x, _y, _z);
	}
}
