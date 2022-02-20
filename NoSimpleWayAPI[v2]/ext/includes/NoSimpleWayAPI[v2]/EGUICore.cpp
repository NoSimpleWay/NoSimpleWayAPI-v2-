#pragma once
#ifndef _E_GUI_CORE_ALREADY_LINKED_
#define _E_GUI_CORE_ALREADY_LINKED_
#include "EGUICore.h"
#endif

std::vector<EWindow*> EWindow::window_list;

EButtonGroup* EButtonGroup::focused_button_group = nullptr;

void EWindow::update_default(float _d)
{
	
}

void EWindow::update_additional(float _d)
{
}

void EWindow::GUI_update_default(float _d)
{
	for (EButtonGroup* b_group : button_group_list)
	if (b_group != nullptr)
	{
		b_group->update(_d);
	}
}

void EWindow::GUI_update_additional(float _d)
{
}

void EWindow::draw_default(float _d)
{
}

void EWindow::draw_additional(float _d)
{
}

void EWindow::GUI_draw_default(float _d)
{
	for (EButtonGroup* b_group : button_group_list)
	if (b_group != nullptr)
	{
		b_group->draw();
	}
}

void EWindow::GUI_draw_additional(float _d)
{
}

void EButtonGroup::update(float _d)
{
	//clickable_region->update(_d);

	//subgroup
	for (EButtonGroupRow* row : group_row_list)
	if (row != nullptr)
	{
		for (EButtonGroup* _group : row->button_group_list)
		{
			_group->update(_d);
		}
	}

	//final button groun, nt subgroup
	if (group_row_list.empty())
	{
		for (EntityButton* but : button_list)
		{
			but->update(_d);
		}
	}
}

void EButtonGroup::draw()
{
	//clickable_region->draw();

	//EInputCore::logger_simple_success("draw button group");

	NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_GREEN);
	if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
	NS_ERenderCollection::add_data_to_vertex_buffer_rama
	(
		batcher_for_default_draw->vertex_buffer,
		batcher_for_default_draw->last_vertice_buffer_index,
		*region->world_position_x,
		*region->world_position_y,
		*region->size_x,
		*region->size_y,
		2.0f,
		NS_DefaultGabarites::texture_gabarite_white_pixel
	);
	batcher_for_default_draw->draw_call();

	glEnable(GL_SCISSOR_TEST);
	glScissor(*region->world_position_x, *region->world_position_y, *region->size_x, *region->size_y);

	if (group_row_list.empty())
	{
		for (EntityButton* but : button_list)
		{but->draw();}
	}

	batcher_for_default_draw->draw_call();

	glDisable(GL_SCISSOR_TEST);
}

void EButtonGroup::set_world_position()
{
	*region->world_position_x = *region->offset_x;
	*region->world_position_y = *region->offset_y;

	if (group_row_list.empty())
	{
		for (EntityButton* but : button_list)
		{
			if (*but->fixed_position)
			{
				*but->world_position_x = *region->world_position_x + *but->offset_x;
				*but->world_position_y = *region->world_position_y + *but->offset_y;
			}
			else
			{
				*but->world_position_x = *region->world_position_x + *but->offset_x + *scroll_x;
				*but->world_position_y = *region->world_position_y + *but->offset_y + *scroll_y;
			}

			but->set_world_position(*but->world_position_x, *but->world_position_y, *but->world_position_z);
		}
	}
}

void EButtonGroup::realign_all_buttons()
{
	EntityButton* prev_button = nullptr;

	*highest_point_y = 0.0f;

	for (EntityButton* but : button_list)
	if (!*but->fixed_position)
	{
		if (prev_button != nullptr)
		{
			
			*but->offset_x = *prev_button->offset_x + *prev_button->button_gabarite->offset_x + *prev_button->button_gabarite->size_x + 5.0f;
			*but->offset_y = *prev_button->offset_y;
			if (*but->offset_x + *but->button_gabarite->size_x + 25.0f >= *region->size_x)
			{
				*but->offset_x = 10.0f;
				*but->offset_y += *but->button_gabarite->size_y + 5.0f;
			}

			
		}
		else
		{
			*but->offset_x = 10.0f;
			*but->offset_y = 10.0f;
		}

		*highest_point_y = max(*highest_point_y, *but->offset_y + *but->button_gabarite->size_y + 10.0f);
		//EInputCore::logger_param("highest point y", *highest_point_y);
		prev_button = but;
	}
}

void EButtonGroup::add_horizontal_scroll_bar(EButtonGroup* _button_group)
{
	EntityButton* but = new EntityButton();
	ECustomData* custom_data = new ECustomData();
	EDataContainerScrollBar* data_container = new EDataContainerScrollBar();
	custom_data->actions_on_update.push_back(EDataActionCollection::action_update_slider);

	//sprite and sprite layer
		ESpriteLayer* sprite_layer = new ESpriteLayer();
		sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;

		ESpriteFrame* sprite_frame = new ESpriteFrame();
		ESprite* sprite = new ESprite();

		sprite_layer->sprite_frame_list.push_back(sprite_frame);

		sprite->set_texture_gabarite(NS_EGraphicCore::put_texture_to_atlas("data/textures/slider_head.png", NS_EGraphicCore::default_texture_atlas));
		sprite->master_sprite_layer = sprite_layer;
		sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
		sprite_frame->sprite_list.push_back(sprite);

		sprite = new ESprite();
		sprite->set_texture_gabarite(NS_EGraphicCore::put_texture_to_atlas("data/textures/slider_head_active.png", NS_EGraphicCore::default_texture_atlas));
		sprite->master_sprite_layer = sprite_layer;
		sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
		sprite_frame->sprite_list.push_back(sprite);


		
	//

	ERegionGabarite* button_gabarite = new ERegionGabarite(0.0f, 0.0f, 14.0f, 14.0f);

	EClickableRegion* cl_region = new EClickableRegion();
	ERegionGabarite* clickable_gabarite = new ERegionGabarite(0.0f, 0.0f, 14.0f, 14.0f);
	cl_region->region = clickable_gabarite;
	cl_region->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
	cl_region->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
	cl_region->sprite_layer_list.push_back(sprite_layer);
	//r_gabarite->
	but->custom_data_list.push_back(custom_data);
	but->button_gabarite = button_gabarite;
	but->parent_button_group = _button_group;
	*but->fixed_position = true;

	custom_data->data_container = data_container;
	custom_data->clickable_region_list.push_back(cl_region);
	custom_data->parent_entity = but;

	data_container->value_pointer = _button_group->scroll_y;

	_button_group->button_list.push_back(but);

	*but->world_position_x = *_button_group->region->offset_x + *_button_group->region->size_x - *but->button_gabarite->size_x;
	*but->world_position_y = *_button_group->region->offset_y;

	but->set_world_position(*but->offset_x, *but->offset_y, *but->offset_z);
	but->sprite_layer_generate_vertex_buffer();
	sprite_layer->generate_vertex_buffer_for_sprite_layer("scroll bar sprite layer");

	EInputCore::logger_param("world x", *sprite->world_position_x);

}
