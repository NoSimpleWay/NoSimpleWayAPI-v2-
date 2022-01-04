#pragma once
/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/

#include <algorithm>
#include <iterator>

void Entity::draw(float _d)
{
	sprite_layer_generate_vertex_buffer();
}

void Entity::sprite_layer_generate_vertex_buffer()
{
	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* sl : sprite_layer_list)
		{
			if
			(
				(sl != nullptr)
				&&
				(
					(!sl->sprite_list.empty())
					&
					(sl->batcher != nullptr)
				)
			)
			{
				for (ESprite* spr : sl->sprite_list)
				{
					if ((spr != nullptr) & (sl->batcher->pointer_to_sprite_render != nullptr))
					{
						sl->batcher->pointer_to_sprite_render(spr);
					}
				}
			}
		}
	}
}

void Entity::transfer_vertex_buffer_to_batcher()
{
	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* sl : sprite_layer_list)
		{
			if
				(
					(sl != nullptr)
					&&
					(
						(!sl->sprite_list.empty())
						&
						(sl->batcher != nullptr)
					)
				)
			{
				//memcpy();
				unsigned int vertices_buffer_capacity = MAX_SHAPES_COUNT * VERTICES_PER_SHAPE * sl->batcher->gl_vertex_attribute_total_count;
				unsigned int passes = ceil (*sl->last_buffer_id / vertices_buffer_capacity);
				
				unsigned int data_size = *sl->last_buffer_id;

				for (unsigned int i = 0; i < passes; i++)
				{
					memcpy
					(
						sl->batcher + sl->batcher->last_vertice_buffer_index,
						sl->vertex_buffer + (size_t)(i * vertices_buffer_capacity),
						min(data_size , vertices_buffer_capacity) * sizeof(*sl->vertex_buffer)
					);

					sl->batcher->last_vertice_buffer_index += *sl->last_buffer_id;


					if (sl->batcher->last_vertice_buffer_index >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE)
					{
						sl->batcher->draw_call();
					}
				}
				//std::copy(0, (int)(sizeof(sl->vertex_buffer)), std::begin(sl->batcher->vertex_buffer));
			}
		}
	}
	
}

void Entity::update(float _d)
{
}


