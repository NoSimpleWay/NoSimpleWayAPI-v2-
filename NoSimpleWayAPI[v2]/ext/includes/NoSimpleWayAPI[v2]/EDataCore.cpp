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

void EDataActionCollection::action_log_text(Entity* _entity, ECustomData* _custom_data)
{
	EInputCore::logger_param("Message", ((EDataContainerMessage*)_custom_data->data_container)->message);
}

void EDataActionCollection::action_player_control(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if
	(
		(EInputCore::key_pressed(GLFW_KEY_W))
		&
		(NS_FONT_UTILS::active_text_area == nullptr)
	)
	{
		_entity->translate_entity(0.0f, 100.0f * _d, 0.0f);
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
			&
			(
				(EInputCore::MOUSE_POSITION_X >= ((double)*_region->region->world_position_x + (double)_offset_x) * _zoom)
				&
				(EInputCore::MOUSE_POSITION_X <= ((double)*_region->region->world_position_x + (double)*_region->region->size_x + _offset_x) * _zoom)

				&

				(EInputCore::MOUSE_POSITION_Y >= ((double)*_region->region->world_position_y + _offset_y) * _zoom)
				&
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
		&
		(EInputCore::MOUSE_POSITION_X <= (_x + _size_x + _offset_x + 2.0f) * _zoom + _catch_distance)

		&

		(EInputCore::MOUSE_POSITION_Y >= (_y + _offset_y) * _zoom - _catch_distance)
		&
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

			if (*catched_side_left)
			{ change_buffer_color(ClickableRegionSides::CRS_SIDE_LEFT, NS_EColorCollection::COLOR_GREEN); }
			else
			{ change_buffer_color(ClickableRegionSides::CRS_SIDE_LEFT, NS_EColorCollection::COLOR_BLACK); }
		
		
		
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

			if (*catched_side_right)
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_RIGHT, NS_EColorCollection::COLOR_GREEN);
			}
			else
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_RIGHT, NS_EColorCollection::COLOR_BLACK);
			}
		

		
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
			if (*catched_side_down)
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_DOWN, NS_EColorCollection::COLOR_GREEN);
			}
			else
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_DOWN, NS_EColorCollection::COLOR_BLACK);
			}

		
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

			if (*catched_side_up)
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_UP, NS_EColorCollection::COLOR_GREEN);
			}
			else
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_UP, NS_EColorCollection::COLOR_BLACK);
			}
		
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
			if (*catched_side_mid)
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_MID, NS_EColorCollection::COLOR_GREEN);
			}
			else
			{
				change_buffer_color(ClickableRegionSides::CRS_SIDE_MID, NS_EColorCollection::COLOR_BLACK);
			}
		
	}
	else
	{

		if (*catched_side_left)
		{
			//*region->offset_x			+= EInputCore::MOUSE_SPEED_X;
			*region->size_x			-= EInputCore::MOUSE_SPEED_X;
			//*region->world_position_x	+= EInputCore::MOUSE_SPEED_X;

			translate(EInputCore::MOUSE_SPEED_X, 0.0f, 0.0f);

			//region->
		}

		if (*catched_side_right)
		{
			*region->size_x += EInputCore::MOUSE_SPEED_X;
		}

		if (*catched_side_down)
		{
			translate(0.0f, EInputCore::MOUSE_SPEED_Y, 0.0f);
			//*region->offset_y += EInputCore::MOUSE_SPEED_Y;
			*region->size_y -= EInputCore::MOUSE_SPEED_Y;
			//*region->world_position_y += EInputCore::MOUSE_SPEED_Y;
		}

		if (*catched_side_up)
		{
			*region->size_y += EInputCore::MOUSE_SPEED_Y;
		}

		if (*catched_side_mid)
		{
			translate(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f);
			/**region->offset_x += EInputCore::MOUSE_SPEED_X;
			*region->world_position_x += EInputCore::MOUSE_SPEED_X;

			*region->offset_y += EInputCore::MOUSE_SPEED_Y;
			*region->world_position_y += EInputCore::MOUSE_SPEED_Y;*/

			//*region->sprite
			
			//region->tr
		}

		if ((*catched_side_left) || (*catched_side_right) || (*catched_side_up) || (*catched_side_down) || (*catched_side_mid))
		{
			
			refresh_border_sprites();
			master_entity->calculate_all_world_positions();
			internal_sprite_layer->generate_vertex_buffer_for_sprite_layer("refresh sides sprites");
		}
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

	if (internal_sprite_layer != nullptr) {internal_sprite_layer->translate_sprite_layer(_x, _y, _z);}

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
		{s_layer->transfer_vertex_buffer_to_batcher();}
	}

	if (internal_sprite_layer != nullptr)
	{
		internal_sprite_layer->transfer_vertex_buffer_to_batcher();
	}

	if (text_area != nullptr)
	{
		text_area->draw();
	}
}

void EClickableRegion::update_sides_visual(int _side, float _offset_x, float _offset_y, bool _catched)
{	
	//left
	*internal_sprite_layer->sprite_list.at(_side)->offset_x = _offset_x;
	*internal_sprite_layer->sprite_list.at(_side)->offset_y = _offset_y;

	//*internal_sprite_layer->sprite_list.at(_side)->world_position_x = _offset_x;
	//*internal_sprite_layer->sprite_list.at(_side)->world_position_y = _offset_y;

	if (_catched)
	{
		if (!EInputCore::MOUSE_BUTTON_LEFT)
		{
			internal_sprite_layer->sprite_list.at(_side)->set_color(NS_EColorCollection::COLOR_GREEN);
		}
		else
		{
			internal_sprite_layer->sprite_list.at(_side)->set_color(NS_EColorCollection::COLOR_BLUE);
		}
	}
	else
	{
		internal_sprite_layer->sprite_list.at(_side)->set_color(NS_EColorCollection::COLOR_BLACK);
	}
}

void EClickableRegion::init_internal_sprite_layer()
{
	internal_sprite_layer = new ESpriteLayer();
	internal_sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;

	ESprite* jc_sprite = nullptr;


		//delete internal_sprite_layer->vertex_buffer;
		internal_sprite_layer->vertex_buffer = new float[1000];


	for (int i = 0; i < 5; i++)
	{
		jc_sprite = new ESprite();
		jc_sprite->main_texture = NS_DefaultGabarites::texture_gabarite_white_pixel;

		jc_sprite->master_sprite_layer = internal_sprite_layer;
		jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_rectangle_with_custom_size;

		internal_sprite_layer->sprite_list.push_back(jc_sprite);
	}

		refresh_border_sprites();
}

bool EClickableRegion::set_catch_side(bool _catch_side, bool _set)
{
	if (_catch_side != _set)
	{
		*any_visual_changes = true;
	}

	return _set;
}

void EClickableRegion::change_buffer_color(int _side, const float(&_color)[4])
{
	for (int i = 0; i < 4; i++)
	{ 
		internal_sprite_layer->vertex_buffer
		[_side * 32 + 2 + 0 + 8 * i] = _color[0];

		internal_sprite_layer->vertex_buffer
		[_side * 32 + 2 + 1 + 8 * i] = _color[1];

		internal_sprite_layer->vertex_buffer
		[_side * 32 + 2 + 2 + 8 * i] = _color[2];

		internal_sprite_layer->vertex_buffer
		[_side * 32 + 2 + 3 + 8 * i] = _color[3];
	}
}

void EClickableRegion::set_sides_position_and_sizes(int _side, float _x, float _y, float _z, float _w, float _h)
{
	*internal_sprite_layer->sprite_list.at(_side)->offset_x = _x;
	*internal_sprite_layer->sprite_list.at(_side)->offset_y = _y;
	*internal_sprite_layer->sprite_list.at(_side)->offset_z = _z;

	*internal_sprite_layer->sprite_list.at(_side)->size_x = _w;
	*internal_sprite_layer->sprite_list.at(_side)->size_y = _h;
}

void EClickableRegion::refresh_border_sprites()
{
	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_LEFT)->size_x = 2.0f;
	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_LEFT)->size_y = *region->size_y + 4.0f;

	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_RIGHT)->size_x = 2.0f;
	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_RIGHT)->size_y = *region->size_y + 4.0f;

	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_DOWN)->size_x = *region->size_x + 0.0f;
	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_DOWN)->size_y = 2.0f;

	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_UP)->size_x = *region->size_x + 0.0f;
	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_UP)->size_y = 2.0f;

	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_MID)->size_x = 6.0f;
	*internal_sprite_layer->sprite_list.at(ClickableRegionSides::CRS_SIDE_MID)->size_y = 6.0f;

	update_sides_visual
	(
		ClickableRegionSides::CRS_SIDE_LEFT,
		*region->offset_x - 2.0f,
		*region->offset_y - 2.0f,
		*catched_side_left
	);

	update_sides_visual
	(
		ClickableRegionSides::CRS_SIDE_RIGHT,
		*region->offset_x + *region->size_x + 0.0f,
		*region->offset_y - 2.0f,
		*catched_side_right
	);

	update_sides_visual
	(
		ClickableRegionSides::CRS_SIDE_DOWN,
		*region->offset_x - 0.0f,
		*region->offset_y - 2.0f,
		*catched_side_down
	);

	update_sides_visual
	(
		ClickableRegionSides::CRS_SIDE_UP,
		*region->offset_x - 0.0f,
		*region->offset_y + *region->size_y + 0.0f,
		*catched_side_up
	);

	update_sides_visual
	(
		ClickableRegionSides::CRS_SIDE_MID,
		*region->offset_x + *region->size_x / 2.0f - 3.0f,
		*region->offset_y + *region->size_y / 2.0f - 3.0f,
		*catched_side_mid
	);
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
