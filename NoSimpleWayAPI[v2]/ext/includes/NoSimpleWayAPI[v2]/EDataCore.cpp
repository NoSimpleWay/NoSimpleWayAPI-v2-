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