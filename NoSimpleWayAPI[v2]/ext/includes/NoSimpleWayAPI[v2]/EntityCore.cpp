#pragma once
/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/

#include <algorithm>
#include <iterator>

void Entity::draw()
{
	transfer_all_vertex_buffers_to_batcher();
}

void Entity::sprite_layer_generate_vertex_buffer()
{
	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* sl : sprite_layer_list)
		if (sl != nullptr)
		{
			sl->generate_vertex_buffer_for_sprite_layer("Entity sprite layers");
		}

		for (ECustomData* c_data : custom_data_list)
		if (c_data != nullptr)
		{
			for (EClickableRegion* c_region:c_data->clickable_region_list)
			if (c_region != nullptr)
			{
				for (ESpriteLayer* s_layer:c_region->sprite_layer_list)
				if (s_layer != nullptr)
				{s_layer->generate_vertex_buffer_for_sprite_layer("Clickable region sprite layer");}

				if (c_region->internal_sprite_layer != nullptr)
				{c_region->internal_sprite_layer->generate_vertex_buffer_for_sprite_layer("internal sprite layer");}
			}

			
		}

		
	}
	else
	{
		//EInputCore::logger_simple_error("SpriteList is empty!");
	}
}

void Entity::transfer_all_vertex_buffers_to_batcher()
{

	//sprite list for entity
	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* sl : sprite_layer_list)
		if (sl != nullptr) {sl->transfer_vertex_buffer_to_batcher();}
	}

	//custom data store clickable regions and text
	if (!custom_data_list.empty())
	{
		for (ECustomData* c_data : custom_data_list)
		if (c_data != nullptr) {c_data->draw();}
	}
	
}

void Entity::set_world_position(float _x, float _y, float _z)
{
	*world_position_x = _x;
	*world_position_y = _y;
	*world_position_z = _z;

	if (!sprite_layer_list.empty())
	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr)
	{s_layer->sprite_layer_set_world_position(*world_position_x, *world_position_y, *world_position_z);}

	for (ECustomData* c_data : custom_data_list)
	if (c_data != nullptr)
	{
		for (EClickableRegion* clickable_region : c_data->clickable_region_list)
		if (clickable_region != nullptr)
		{clickable_region->clickable_region_set_world_positions(*world_position_x, *world_position_y, *world_position_z);}
	}
}

void Entity::modify_buffer_translate_for_entity(float _x, float _y, float _z)
{
	for (ESpriteLayer* s_layer : sprite_layer_list)
	{
		s_layer->modify_buffer_position_for_sprite_layer(_x, _y, _z);
	}

	for (ECustomData* c_data : custom_data_list)
	{
		for (EClickableRegion* c_region : c_data->clickable_region_list)
		{
			for (ESpriteLayer* s_layer : c_region->sprite_layer_list)
			{
				s_layer->modify_buffer_position_for_sprite_layer(_x, _y, _z);
			}

			if (c_region->internal_sprite_layer != nullptr)
			{
				c_region->internal_sprite_layer->modify_buffer_position_for_sprite_layer(_x, _y, _z);
			}
		}


	}

}

void Entity::translate_entity(float _x, float _y, float _z)
{
	//entity position
	*offset_x += _x;
	*offset_y += _y;
	*offset_z += _z;

	*world_position_x += _x;
	*world_position_y += _y;
	*world_position_z += _z;

	translate_all_sprite_layers(_x, _y, _z);
}

void Entity::translate_all_sprite_layers(float _x, float _y, float _z)
{
	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr) {s_layer->translate_sprite_layer(_x, _y, _z);}
	
	for (ECustomData* c_data : custom_data_list)
	if (c_data != nullptr) {c_data->translate(_x, _y, _z);}


}

void Entity::update(float _d)
{
	//translate_entity(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f);

	for (ECustomData* c_data : custom_data_list)
	if (c_data != nullptr)
	{
		c_data->update(_d);
	}
}

Entity::Entity()
{
}

Entity::~Entity()
{
}

ESprite* Entity::get_sprite_from_data(unsigned int _data_id, unsigned int _layer_id, unsigned int _frame_id, unsigned int _frame)
{
	/*if
	(
		(!custom_data_list.empty())
		&&
		(!custom_data_list.at(_data_id)->clickable_region_list)
	)*/
	return nullptr;
}

ESpriteLayer* Entity::get_sprite_layer_by_id(unsigned int id)
{
	return nullptr;
}


