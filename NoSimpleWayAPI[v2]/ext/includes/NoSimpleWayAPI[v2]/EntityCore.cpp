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
	//sprite_layer_generate_vertex_buffer();
	transfer_vertex_buffer_to_batcher();

	
	/*NS_ERenderCollection::fill_vertex_buffer_textured_rectangle_real_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		0 * 160.0f + 5.0f,
		0 * 105.0f + 5.0f,

		NS_DefaultGabarites::texture_gabarite_gudron
	);*/
	

	NS_EGraphicCore::default_batcher_for_drawing->draw_call();
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
					(
						(sl->batcher != nullptr)
						&&
						(sl->batcher->pointer_to_sprite_render != nullptr)
					)
				)
			)
			{
				for (ESprite* spr : sl->sprite_list)
				{
					if ((spr != nullptr) & (sl->batcher->pointer_to_sprite_render != nullptr))
					{
						//EInputCore::logger_simple_success("try call render by ponter");
						sl->batcher->pointer_to_sprite_render(spr);
					}
					else
					{
						EInputCore::logger_simple_error("Sprite is null!");
					}
				}
			}
			else
			{
				if (sl == nullptr) { EInputCore::logger_simple_error("SpriteList is null!"); }

				if ((sl != nullptr) && (sl->batcher->pointer_to_sprite_render == nullptr))
				{ EInputCore::logger_simple_error("bather pointer to render is null"); }


			}
		}
	}
	else
	{
		EInputCore::logger_simple_error("SpriteList is empty!");
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
					(sl->last_buffer_id > 0)
					&&
					(
						(!sl->sprite_list.empty())
						&
						(sl->batcher != nullptr)
					)
				)
			{
				//memcpy();
				//std::cout << "-------" << std::endl;

				unsigned int vertices_buffer_capacity = MAX_SHAPES_COUNT * VERTICES_PER_SHAPE * sl->batcher->gl_vertex_attribute_total_count;
				//EInputCore::logger_param("vertices_buffer_capacity", vertices_buffer_capacity);

				unsigned int passes = ceil (*sl->last_buffer_id / (float)vertices_buffer_capacity);
				//EInputCore::logger_param("passes", passes);

				unsigned int data_size = *sl->last_buffer_id;
				//EInputCore::logger_param("data_size", data_size);


				for (unsigned int i = 0; i < passes; i++)
				{

					memcpy
					(
						sl->batcher->vertex_buffer + sl->batcher->last_vertice_buffer_index,
						sl->vertex_buffer + (size_t)(i * vertices_buffer_capacity),
						min(data_size , vertices_buffer_capacity) * sizeof(*sl->vertex_buffer)
					);

					sl->batcher->last_vertice_buffer_index += min(data_size, vertices_buffer_capacity);

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

void Entity::calculate_all_world_positions()
{
	if (!sprite_layer_list.empty())
	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr)
	{
		*s_layer->world_position_x = *offset_x + *s_layer->offset_x;
		*s_layer->world_position_y = *offset_y + *s_layer->offset_y;
		*s_layer->world_position_z = *offset_z + *s_layer->offset_z;

		for (ESprite* spr : s_layer->sprite_list)
		if (spr != nullptr)
		{
			*spr->world_position_x = *offset_x + *s_layer->offset_x + *spr->offset_x;
			*spr->world_position_y = *offset_y + *s_layer->offset_y + *spr->offset_y;
			*spr->world_position_z = *offset_z + *s_layer->offset_z + *spr->offset_z;
		}
	}
}

void Entity::translate_entity(float _x, float _y, float _z)
{
	*offset_x += _x;
	*offset_y += _y;
	*offset_z += _z;

	calculate_all_world_positions();
}

void Entity::update(float _d)
{
	for (ECustomData* c_data : custom_data_list)
	if (c_data != nullptr)
	{
		for (EClickableRegion* cl_region:c_data->clickable_region_list)
		if (cl_region != nullptr)
		{
			cl_region->update(_d);
		}

		for (data_action_pointer action_on_update_pointer:c_data->data_actions_list)
		if ((action_on_update_pointer != nullptr) & (c_data->master_entity != nullptr))
		{
			action_on_update_pointer(c_data->master_entity, c_data, _d);
		}
	}
}

Entity::Entity()
{
}

Entity::~Entity()
{
}


