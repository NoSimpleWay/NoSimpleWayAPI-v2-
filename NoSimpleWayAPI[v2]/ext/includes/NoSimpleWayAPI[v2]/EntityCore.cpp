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
	transfer_vertex_buffer_to_batcher();

	NS_EGraphicCore::default_batcher_for_drawing->draw_call();
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
				{
					s_layer->generate_vertex_buffer_for_sprite_layer("Clickable region sprite layer");
				}

				if (c_region->internal_sprite_layer != nullptr)
				{
					//EInputCore::logger_simple_success("try generate vertex buffer for sprite layer[]");
					c_region->internal_sprite_layer->generate_vertex_buffer_for_sprite_layer("internal sprite layer");

					for (int i = 0; i < *c_region->internal_sprite_layer->last_buffer_id * 0; i++)
					{
						
						EInputCore::logger_param(EInputCore::border_this_text(i, '['), c_region->internal_sprite_layer->vertex_buffer[i]);

						if ((i > 0))
						{
							if ((i + 1) % 8 == 0)
							{
								std::cout << white << "===" << std::endl;
							}

							if
								(
									((i + 7) % 8 == 0)
									||
									((i + 3) % 8 == 0)
									)
							{
								std::cout << white << "-" << std::endl;
							}
						}

						//EInputCore::logger_param("c_region->last_buffer_id", *c_region->internal_sprite_layer->last_buffer_id);
					}
				}
			}

			
		}

		
	}
	else
	{
		//EInputCore::logger_simple_error("SpriteList is empty!");
	}
}

void Entity::transfer_vertex_buffer_to_batcher()
{
	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* sl : sprite_layer_list)
		if (sl != nullptr)
		{
			sl->transfer_vertex_buffer_to_batcher();
		}
	}

	if (!custom_data_list.empty())
	{
		for (ECustomData* c_data : custom_data_list)
		if (c_data != nullptr)
		{
			if (!c_data->clickable_region_list.empty())
			for (EClickableRegion* cl_region:c_data->clickable_region_list)
			if (cl_region != nullptr)
			{
				if (cl_region->region != nullptr)
				{
					if(!cl_region->sprite_layer_list.empty())
					for (ESpriteLayer* s_layer:cl_region->sprite_layer_list)
					if (s_layer != nullptr)
					{
						//s_layer->transfer_vertex_buffer_to_batcher();
					}

					if
					(
						(cl_region->internal_sprite_layer != nullptr)
					)
					{
						//EInputCore::logger_simple_success("try transfer VB to batcher [sprite layer elements:" + std::to_string(*cl_region->internal_sprite_layer->last_buffer_id) + "]");
						//EInputCore::logger_param("internal sprite list vertex array count", *cl_region->internal_sprite_layer->last_buffer_id);

						cl_region->internal_sprite_layer->transfer_vertex_buffer_to_batcher();
					}

					if
					(
						(cl_region->text_area != nullptr)
						&&
						(cl_region->text_area->sprite_layer != nullptr)
					)
					{
						
						cl_region->text_area->sprite_layer->transfer_vertex_buffer_to_batcher();

						for (int i = 0; i < *cl_region->text_area->sprite_layer->last_buffer_id * 0; i++)
						{

							EInputCore::logger_param(EInputCore::border_this_text(i, '['), cl_region->text_area->sprite_layer->vertex_buffer[i]);

							if ((i > 0))
							{
								if ((i + 1) % 8 == 0)
								{
									std::cout << white << "===" << std::endl;
								}

								if
									(
										((i + 7) % 8 == 0)
										||
										((i + 3) % 8 == 0)
										)
								{
									std::cout << white << "-" << std::endl;
								}
							}

							//EInputCore::logger_param("c_region->last_buffer_id", *cl_region->text_area->sprite_layer->last_buffer_id);
						}
					}
					else
					{
						EInputCore::logger_simple_error("text area or text area sprite layer is null");
					}
				}
			}

			//if (c_data->inter)
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
			//EInputCore::logger_simple_success("^^^");
			*spr->world_position_x = *offset_x + *s_layer->offset_x + *spr->offset_x;
			*spr->world_position_y = *offset_y + *s_layer->offset_y + *spr->offset_y;
			*spr->world_position_z = *offset_z + *s_layer->offset_z + *spr->offset_z;

			//EInputCore::logger_simple_success("^^^");
			//EInputCore::logger_param("sprite x", *spr->world_position_x);
			//EInputCore::logger_param("sprite y", *spr->world_position_y);
		}
	}

	for (ECustomData* c_data : custom_data_list)
		if (c_data != nullptr)
		{
			for (EClickableRegion* c_region : c_data->clickable_region_list)
				if (c_region != nullptr)
				{
					*c_region->region->world_position_x = *offset_x + *offset_z + *c_region->region->offset_x;
					*c_region->region->world_position_y = *offset_x + *offset_z + *c_region->region->offset_y;

					for (ESpriteLayer* s_layer : c_region->sprite_layer_list)
						if (s_layer != nullptr)
						{
							*s_layer->world_position_x = *offset_x + *s_layer->offset_x;
							*s_layer->world_position_y = *offset_y + *s_layer->offset_y;
							*s_layer->world_position_z = *offset_z + *s_layer->offset_z;

							for (ESprite* spr : s_layer->sprite_list)
								if (spr != nullptr)
								{
									//EInputCore::logger_simple_success("^^^");
									*spr->world_position_x = *offset_x + *s_layer->offset_x + *spr->offset_x;
									*spr->world_position_y = *offset_y + *s_layer->offset_y + *spr->offset_y;
									*spr->world_position_z = *offset_z + *s_layer->offset_z + *spr->offset_z;
								}
						}

					if (c_region->internal_sprite_layer != nullptr)
					{
						*c_region->internal_sprite_layer->world_position_x = *offset_x + *c_region->internal_sprite_layer->offset_x;
						*c_region->internal_sprite_layer->world_position_y = *offset_y + *c_region->internal_sprite_layer->offset_y;
						*c_region->internal_sprite_layer->world_position_z = *offset_z + *c_region->internal_sprite_layer->offset_z;

						for (ESprite* spr : c_region->internal_sprite_layer->sprite_list)
							if (spr != nullptr)
							{
								//EInputCore::logger_simple_success("^^^");
								*spr->world_position_x = *offset_x + *c_region->internal_sprite_layer->offset_x + *spr->offset_x;
								*spr->world_position_y = *offset_y + *c_region->internal_sprite_layer->offset_y + *spr->offset_y;
								*spr->world_position_z = *offset_z + *c_region->internal_sprite_layer->offset_z + *spr->offset_z;
							}
					}

					*c_region->region->world_position_x = *offset_x + *c_region->region->offset_x;
					*c_region->region->world_position_y = *offset_y + *c_region->region->offset_y;

				}
		}
}

void Entity::modify_buffer_translate_for_entity(float _x, float _y, float _z)
{
	for (ESpriteLayer* s_layer : sprite_layer_list)
	{
		s_layer->modify_buffer_translate_for_sprite_layer(_x, _y, _z);
	}

	for (ECustomData* c_data : custom_data_list)
	{
		for (EClickableRegion* c_region : c_data->clickable_region_list)
		{
			for (ESpriteLayer* s_layer : c_region->sprite_layer_list)
			{
				s_layer->modify_buffer_translate_for_sprite_layer(_x, _y, _z);
			}

			if (c_region->internal_sprite_layer != nullptr)
			{
				c_region->internal_sprite_layer->modify_buffer_translate_for_sprite_layer(_x, _y, _z);
			}
		}


	}

}

void Entity::translate_entity(float _x, float _y, float _z)
{
	*offset_x += _x;
	*offset_y += _y;
	*offset_z += _z;

	modify_buffer_translate_for_entity(_x, _y, _z);

	calculate_all_world_positions();
}

void Entity::update(float _d)
{
	//translate_entity(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f);

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


