#pragma once
/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/

void Entity::draw(float _d)
{
	fill_vertex_buffer();
}

void Entity::fill_vertex_buffer()
{
	for (ESpriteLayer* sl : sprite_layer_list)
	{
		sl->generate_vertex_buffer_for_sprite_layer();
	}
}
