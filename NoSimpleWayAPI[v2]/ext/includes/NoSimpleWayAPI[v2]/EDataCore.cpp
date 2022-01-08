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

/*
bool EClickableRegion::overlapped_by_mouse(EClickableRegion* _region)
{
	return false;
}
*/

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
				(EInputCore::MOUSE_POSITION_X >= (*_region->master_entity->offset_x + *_region->region->offset_x + _offset_x) * _zoom)
				&
				(EInputCore::MOUSE_POSITION_X <= (*_region->master_entity->offset_x + *_region->region->offset_x + *_region->region->size_x + _offset_x) * _zoom)

				&

				(EInputCore::MOUSE_POSITION_Y >= (*_region->master_entity->offset_y + *_region->region->offset_y + _offset_y) * _zoom)
				&
				(EInputCore::MOUSE_POSITION_Y <= (*_region->master_entity->offset_y + *_region->region->offset_y + *_region->region->size_y + _offset_y) * _zoom)
			)
		)
	{
		return true;
	}

	return false;
}

bool EClickableRegion::catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance = 3.0f)
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

void EClickableRegion::update(float _d)
{
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

			3.0f
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

			3.0f
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

			3.0f
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

			3.0f
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

			5.0f
		);
	}
}
