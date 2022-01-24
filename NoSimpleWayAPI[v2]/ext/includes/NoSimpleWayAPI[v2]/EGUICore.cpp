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

void EButtonGroup::calculate_all_world_positions()
{
	*region->world_position_x = *region->offset_x;
	*region->world_position_y = *region->offset_y;

	if (group_row_list.empty())
	{
		for (EntityButton* but : button_list)
		{
			*but->world_position_x = *region->world_position_x + *but->offset_x;
			*but->world_position_y = *region->world_position_y + *but->offset_y;

			but->calculate_all_world_positions();
		}
	}
}

void EButtonGroup::realign_all_buttons()
{
	EntityButton* prev_button = nullptr;

	for (EntityButton* but : button_list)
	{
		if (prev_button != nullptr)
		{
			
			*but->offset_x = *prev_button->offset_x + *prev_button->button_gabarite->offset_x + *prev_button->button_gabarite->size_x + 5.0f;
			*but->offset_y = *prev_button->offset_y;
			if (*but->offset_x + *but->button_gabarite->size_x + 5.0f >= *region->size_x)
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

		prev_button = but;
	}
}
