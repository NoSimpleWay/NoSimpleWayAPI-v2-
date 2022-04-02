#pragma once
#ifndef _E_GUI_CORE_ALREADY_LINKED_
#define _E_GUI_CORE_ALREADY_LINKED_
#include "EGUICore.h"
#endif

std::vector<EWindow*> EWindow::window_list;

EButtonGroup* EButtonGroup::focused_button_group = nullptr;

//EButtonGroup* EButtonGroup::focused_button_group;
EButtonGroup* EButtonGroup::focused_button_group_with_slider = nullptr;

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
		EButtonGroup::get_last_focused_group(b_group);
	}

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

EButtonGroup::EButtonGroup(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y)
{
	if (region == nullptr)
	{
		region = new ERegionGabarite(_offset_x, _offset_y, _size_x, _size_y);
	}
	else
	{
		region->set_region_offset_and_size(_offset_x, _offset_y, _offset_z, _size_x, _size_y);
	}
}

EButtonGroup::EButtonGroup(ERegionGabarite* _region)
{
	region = _region;
}

EButtonGroup::~EButtonGroup()
{
}

void EButtonGroup::update(float _d)
{
	//clickable_region->update(_d);

	//subgroup
	//EButtonGroup* prev_group = nullptr;

	//if (but->re*higher_culling_line)


	for (EButtonGroupRow* row : group_row_list)
	if (row != nullptr)
	{
		for (EButtonGroup* _group : row->button_group_list)
		{
			_group->update(_d);
		}

		/*if (row->header_button_group != nullptr)
		{
			row->header_button_group->update(_d);
		}*/
	}

	{
		for (EntityButton* but : button_list)
		if
		(
			(*but->update_when_scissored)
			||
			(
				(*but->button_gabarite->world_position_y <= *higher_culling_line + *border_bottom)
				&&
				(*but->button_gabarite->world_position_y + *but->button_gabarite->size_y >= *lower_culling_line - *border_up)
			)
		)
		{
			but->update(_d);
		}
	}

	//final button groun, not subgroup
	//if (group_row_list.empty())
	
	if (header_button_group != nullptr)
	{
		header_button_group->update(_d);
	}
}

void EButtonGroup::draw()
{
	//clickable_region->draw();

	//EInputCore::logger_simple_success("draw button group");
	batcher_for_default_draw->draw_call();

	glDisable(GL_SCISSOR_TEST);
	//glDisable(GL_SCISSOR_TEST);
	/* */if (root_group == this)
	/* */ {
	/* */	NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLACK, 0.335f);
	/* */	if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
	/* */	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	/* */	(
	/* */		batcher_for_default_draw->vertex_buffer,
	/* */		batcher_for_default_draw->last_vertice_buffer_index,
	/* */		*region->world_position_x - 3.0f,
	/* */		*region->world_position_y - 3.0f,
	/* */		*region->size_x + 6.0f,
	/* */		*region->size_y + 6.0f,
	/* */		NS_DefaultGabarites::texture_gabarite_white_pixel
	/* */	);
	/* */}
	batcher_for_default_draw->draw_call();

	glEnable(GL_SCISSOR_TEST);

	//BG
	if ((background_sprite_layer != nullptr)&&(*have_bg))
	{
		
		glScissor
		(
			*region->world_position_x,
			*lower_culling_line_for_bg,

			*region->size_x,
			max(0.0f, *higher_culling_line_for_bg - *lower_culling_line_for_bg)
		);

		background_sprite_layer->transfer_vertex_buffer_to_batcher();

		if (EButtonGroup::focused_button_group == this)
		{
			NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.073f);
			if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,
				*region->world_position_x + 0.0f,
				*region->world_position_y + 0.0f,
				*region->size_x - 0.0f,
				*region->size_y - 0.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}
		batcher_for_default_draw->draw_call();
	}

	

	
	//ELEMENTS
	if (parent_group_row == nullptr)
	{
		glScissor(*region->world_position_x, *region->world_position_y, *region->size_x, *region->size_y);
	}
	else
	{
		//if (root_group != nullptr)
		{
			glScissor
			(
				*region->world_position_x,
				*lower_culling_line,

				*region->size_x,
				max(0.0f, *higher_culling_line - *lower_culling_line)
			);
		}
	}


	for (EntityButton* but : button_list)
	if
	(
		(*but->world_position_y + *but->button_gabarite->size_y >= *lower_culling_line)
		&&
		(*but->world_position_y <= *higher_culling_line)
	)
	{
		but->draw();
	}

	//recursive draw
	for (EButtonGroupRow* row : group_row_list)
	{

		for (EButtonGroup* group : row->button_group_list)
		{
			group->draw();
		}


	}

	//draw call to prepare for header
	batcher_for_default_draw->draw_call();




	//reset scissor
	batcher_for_default_draw->draw_call();



	glDisable(GL_SCISSOR_TEST);
	
	if (EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL))
	{
		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_GREEN);
		if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
		NS_ERenderCollection::add_data_to_vertex_buffer_rama
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,
			*region->world_position_x + 0.0f,
			*region->world_position_y + 0.0f,
			*region->size_x - 0.0f,
			*region->size_y - 0.0f,
			1.0f,
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
	}

	if (EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{
		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_CYAN);
		if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
		NS_ERenderCollection::add_data_to_vertex_buffer_rama
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,
			*region->world_position_x + 0.0f,
			*lower_culling_line,
			*region->size_x - 0.0f,
			1.0f,
			1.0f,
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);

		NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_YELLOW);
		if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
		NS_ERenderCollection::add_data_to_vertex_buffer_rama
		(
			batcher_for_default_draw->vertex_buffer,
			batcher_for_default_draw->last_vertice_buffer_index,
			*region->world_position_x + 0.0f,
			*higher_culling_line,
			*region->size_x - 0.0f,
			1.0f,
			1.0f,
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
	}

	if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
	{
		for (EButtonGroupRow* row : group_row_list)
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_RED);
			if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			NS_ERenderCollection::add_data_to_vertex_buffer_rama
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,
				*row->gabarite->world_position_x + 0.0f,
				*row->gabarite->world_position_y + 0.0f,
				*row->gabarite->size_x - 0.0f,
				*row->gabarite->size_y - 0.0f,
				1.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
			//batcher_for_default_draw->draw_call();
		}
	}

	batcher_for_default_draw->draw_call();

	if (header_button_group != nullptr)
	{
		header_button_group->draw();
	}

}

void EButtonGroup::align_groups()
{
	*highest_point_y = 0.0f;
	//float minimal_culling_line_top		= 10000.0f;
	//float minimal_culling_line_bottom	= -10000.0f;

	if (parent_group_row == nullptr)
	{
		*region->world_position_x = *region->offset_x;
		*region->world_position_y = *region->offset_y;
	}

	if
	(
		(*culling_lines_method == CullingLinesCalcMethod::CLCM_BY_HIMSELF)
		&&
		(root_group != nullptr)
	)
	{
		*region->world_position_x = *root_group->region->offset_x + 0.0f;
		*region->world_position_y = *root_group->region->offset_y + *root_group->region->size_y - *region->size_y * 0.0f - *root_group->border_up;
	}





	
	EButtonGroup* prev_group = nullptr;
	EButtonGroupRow* prev_row = nullptr;
	

	for (EButtonGroupRow* row:group_row_list)
	{
		

		*row->gabarite->offset_x = *border_left;

		if (prev_row != nullptr)
		{
			*row->gabarite->offset_y = *prev_row->gabarite->offset_y + *prev_row->gabarite->size_y + 3.0f;
		}
		else
		{
			*row->gabarite->offset_y = *border_bottom;
		}


		

		//*row->gabarite->offset_y += *scroll_y;
		prev_row = row;
		//*row->gabarite->offset_x = rand() % 100;
		*row->gabarite->world_position_x = *region->world_position_x + *row->gabarite->offset_x;

		*row->gabarite->world_position_y = *region->world_position_y + *row->gabarite->offset_y;
		*row->gabarite->world_position_y += *row->parent_button_group->scroll_y;

		*row->gabarite->world_position_z = *region->world_position_z + *row->gabarite->offset_z;




		prev_group = nullptr;

		//if (*gabarite_size_mode_y == ButtonGroupGabariteSize::BGGS_EXACT_STRETCH) { *region->size_y = 0.0f; }
		//if (*row->gabarite_size_mode_y == ButtonGroupGabariteSize::BGGS_EXACT_STRETCH) { *row->gabarite->size_y = 0.0f; }
		for (EButtonGroup* group : row->button_group_list)
		{
			*group->region->offset_x = 0.0f;

			if (prev_group != nullptr)
			{
				*group->region->offset_x = *prev_group->region->offset_x + *prev_group->region->size_x + 3.0f;
			}
			else
			{

				 *group->region->offset_y = 0.0f;

				 prev_group = group;
			}

			

			*group->region->world_position_x = *row->gabarite->world_position_x + *group->region->offset_x;
			*group->region->world_position_y = *row->gabarite->world_position_y + *group->region->offset_y;
			*group->region->world_position_z = *row->gabarite->world_position_z + *group->region->offset_z;



			//if
			//(
			//	(*row->gabarite_size_mode_y == ButtonGroupGabariteSize::BGGS_EXACT_STRETCH)
			//	&&
			//	(*group->region->offset_y + *group->region->size_y>= *row->gabarite->size_y)
			//)
			//{
			//	*row->gabarite->size_y = *group->region->offset_y + *group->region->size_y;
			//}

			if
			(
				(group->parent_group_row != nullptr)
				&&
				(*group->region->offset_y + *group->region->size_y >= *row->gabarite->size_y)
				//&&
				//(EInputCore::key_pressed(LEFT_ALT_PRESSED))
			)
			{
				EButtonGroup::stretch_parent_row(group, *group->region->offset_y + *group->region->size_y);
			}

			group->align_groups();
			
		}
		


		if (parent_group_row == nullptr)
		{
			*highest_point_y
			=
			*prev_row->gabarite->offset_y
			+
			*prev_row->gabarite->size_y
			+
			*border_up;
		}
		//prev_row = row;
	}





	
	

}

void EButtonGroup::calculate_culling_lines(EButtonGroup* _group)
{
	if (_group->parent_group_row == nullptr)
	{


		*_group->higher_culling_line		= *_group->region->world_position_y + *_group->region->size_y;
		*_group->lower_culling_line			= *_group->region->world_position_y;

		*_group->higher_culling_line_for_bg	= *_group->region->world_position_y + *_group->region->size_y;
		*_group->lower_culling_line_for_bg	= *_group->region->world_position_y;

		//minimal_culling_line_top	= *higher_culling_line;
		//minimal_culling_line_bottom	= *lower_culling_line;
	}

	if
	(
		(*_group->culling_lines_method == CullingLinesCalcMethod::CLCM_BY_HIMSELF)
		&&
		(_group->root_group != nullptr)
	)
	{


		*_group->higher_culling_line		= *_group->region->world_position_y + *_group->region->size_y;
		*_group->lower_culling_line			= *_group->region->world_position_y;

		*_group->higher_culling_line_for_bg	= *_group->region->world_position_y + *_group->region->size_y;
		*_group->lower_culling_line_for_bg	= *_group->region->world_position_y;
	}

	

	for (EButtonGroupRow*	row:	_group->group_row_list)
	for (EButtonGroup*		group:	row->button_group_list)
	{
		*group->higher_culling_line_for_bg = min
		(
			*group->region->world_position_y + *group->region->size_y,
			*_group->region->world_position_y + *_group->region->size_y - *_group->border_up
		);

		*group->higher_culling_line_for_bg = min
		(
			*group->higher_culling_line_for_bg,
			*_group->higher_culling_line_for_bg
		);



		*group->lower_culling_line_for_bg = max
		(
			*group->region->world_position_y,
			*_group->region->world_position_y + *_group->border_bottom
		);

		*group->lower_culling_line_for_bg = max
		(
			*group->lower_culling_line_for_bg,
			*_group->lower_culling_line_for_bg
		);



		*group->higher_culling_line = min
		(
			*group->region->world_position_y + *group->region->size_y - *group->border_up,
			*_group->region->world_position_y + *_group->region->size_y - *_group->border_up
		);

		*group->higher_culling_line = min
		(
			*group->higher_culling_line,
			*_group->higher_culling_line
		);


		*group->lower_culling_line = max(*group->region->world_position_y + *group->border_bottom, *_group->region->world_position_y + *_group->border_bottom);
		*group->lower_culling_line = max(*group->lower_culling_line, *_group->lower_culling_line);

		EButtonGroup::calculate_culling_lines(group);
	}


}

void EButtonGroup::generate_vertex_buffer_for_group(EButtonGroup* _group)
{
	if
	(
		(_group->background_sprite_layer != nullptr)

	)
	{
		_group->background_sprite_layer->sprite_layer_set_world_position
		(
			*_group->region->world_position_x,
			*_group->region->world_position_y,
			*_group->region->world_position_z
		);

		_group->background_sprite_layer->generate_vertex_buffer_for_sprite_layer("Button group background");
	}

	if (_group->slider != nullptr)
	{
		_group->slider->set_world_position(*_group->slider->world_position_x, *_group->slider->world_position_y, *_group->slider->world_position_z);
		_group->slider->generate_vertex_buffer_for_all_sprite_layers();
	}

	//if (group_row_list.empty())
	{
		for (EntityButton* but : _group->button_list)
		{
			but->set_world_position(*but->world_position_x, *but->world_position_y, *but->world_position_z);


			if
			(
				(*but->world_position_y + *but->button_gabarite->size_y >= *_group->lower_culling_line)
				&&
				(*but->world_position_y <= *_group->higher_culling_line)
			)
			{
				but->generate_vertex_buffer_for_all_sprite_layers();
			}
		}
	}


}

void EButtonGroup::refresh_button_group(EButtonGroup* _group)
{
	
	_group->align_groups();
	EButtonGroup::calculate_culling_lines(_group);
	_group->realign_all_buttons();
	EButtonGroup::generate_vertex_buffer_for_group(_group);

	for (EButtonGroupRow*	row:	_group->group_row_list)
	for (EButtonGroup*		group:	row->button_group_list)
	{
		EButtonGroup::refresh_button_group(group);
	}

	if (_group->header_button_group != nullptr)
	{
		EButtonGroup::refresh_button_group(_group->header_button_group);
	}
}

void EButtonGroup::realign_all_buttons()
{
	EntityButton* prev_button = nullptr;





	for (EntityButton* but : button_list)
	if ((!*but->fixed_position) || (false))
	{
		if (prev_button != nullptr)
		{
			*but->offset_x = *prev_button->offset_x + *prev_button->button_gabarite->offset_x + *prev_button->button_gabarite->size_x + 5.0f;
			*but->offset_y = *prev_button->offset_y;

			if (*but->offset_x + *but->button_gabarite->size_x + 25.0f >= *region->size_x)
			{
				*but->offset_x = *but->parent_button_group->border_left;
				*but->offset_y += *but->button_gabarite->size_y + 5.0f;
			}

			
		}
		else
		{
			*but->offset_x = *but->parent_button_group->border_left + 2.0f;
			*but->offset_y = *but->parent_button_group->border_bottom + 2.0f;
		}

		if ((*but->fixed_position) && (true))
		{
			*but->world_position_x = *but->parent_button_group->region->world_position_x + *but->offset_x;
			*but->world_position_y = *but->parent_button_group->region->world_position_y + *but->offset_y;
		}
		else
		{
			*but->world_position_x = *but->parent_button_group->region->world_position_x + *but->offset_x + *but->parent_button_group->scroll_x;
			*but->world_position_y = *but->parent_button_group->region->world_position_y + *but->offset_y + *but->parent_button_group->scroll_y;

			//*but->world_position_x = *but->parent_button_group->region->world_position_x + *but->parent_button_group->scroll_y;
			//*but->world_position_y = *but->parent_button_group->region->world_position_y;
		}

		*highest_point_y = max(*highest_point_y, *but->offset_y + *but->button_gabarite->size_y + 3.0f);
		//EInputCore::logger_param("highest point y", *highest_point_y);
		prev_button = but;
	}
	else
	{
		//but->update(0.1f);
	}

	if (!group_row_list.empty())
	{
		for (EButtonGroupRow* row : group_row_list)
		{
			for (EButtonGroup* group : row->button_group_list)
			{
				group->realign_all_buttons();
			}
		}
	}

	if (slider != nullptr)
	{
		*slider->offset_x
			=
			*region->size_x
			-
			*slider->button_gabarite->size_x
			-
			*border_right;



		*slider->world_position_x
			=
			*slider->offset_x
			+
			*region->world_position_x;

		*slider->offset_y = 0.0f;
		*slider->world_position_y = *region->world_position_y;
	}
}

void EButtonGroup::add_horizontal_scroll_bar(EButtonGroup* _button_group)
{
	EntityButton* but = new EntityButton();

	_button_group->slider = but;

	ECustomData* custom_data = new ECustomData();
	EDataContainerScrollBar* data_container = new EDataContainerScrollBar();
	custom_data->actions_on_update.push_back(EDataActionCollection::action_update_slider);
	but->action_on_change_style_list.push_back(action_change_style_slider);

	EClickableRegion* cl_region = new EClickableRegion();

	//bar
		ESpriteLayer* sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
		*sprite_layer->offset_y = *_button_group->border_bottom;

		but->sprite_layer_list.push_back(sprite_layer);
		ERegionGabarite::temporary_gabarite->set_region_offset_and_size
		(
			0.0f,
			0.0f,
			0.0f,
			*_button_group->selected_style->slider_head_inactive->size_x_in_pixels,
			*_button_group->region->size_y - *_button_group->border_bottom - *_button_group->border_up
		);

		NS_ERenderCollection::set_brick_borders_and_subdivisions
		(
			*_button_group->selected_style->slider_border_left,
			*_button_group->selected_style->slider_border_right,
			*_button_group->selected_style->slider_border_bottom,
			*_button_group->selected_style->slider_border_up,

			*_button_group->selected_style->slider_subdivision_x,
			*_button_group->selected_style->slider_subdivision_y
		);

		NS_ERenderCollection::generate_brick_texture(ERegionGabarite::temporary_gabarite, sprite_layer, _button_group->selected_style->background_for_slider);
		sprite_layer->sprite_layer_set_world_position(0.0f, 0.0f, 0.0f);
		sprite_layer->generate_vertex_buffer_for_sprite_layer("init bg");

	//head inactive
	sprite_layer
	=
	ESpriteLayer::create_default_sprite_layer
	(
		_button_group->selected_style->slider_head_inactive
	);
	cl_region->sprite_layer_list.push_back(sprite_layer);


	//head_active
	ESpriteLayer::get_last_sprite_frame(sprite_layer)
	->
	sprite_list.push_back (ESprite::create_default_sprite (_button_group->selected_style->slider_head_active, sprite_layer));

	
	ERegionGabarite* clickable_gabarite
		=
		new ERegionGabarite
		(
			0.0f,
			*_button_group->border_bottom,
			*ESpriteLayer::get_last_created_sprite(sprite_layer)->size_x,
			*ESpriteLayer::get_last_created_sprite(sprite_layer)->size_y
		);

	cl_region->region = clickable_gabarite;
	cl_region->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
	cl_region->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
	


		
	//

	ERegionGabarite* button_gabarite
	=
	new ERegionGabarite
	(
		0.0f,
		0.0f,
		*ESpriteLayer::get_last_created_sprite(sprite_layer)->size_x,
		*ESpriteLayer::get_last_created_sprite(sprite_layer)->size_y
	);

	
	//r_gabarite->
	but->custom_data_list.push_back(custom_data);
	but->button_gabarite = button_gabarite;
	but->parent_button_group = _button_group;
	*but->fixed_position = true;
	*but->update_when_scissored = true;

	custom_data->data_container = data_container;
	custom_data->clickable_region_list.push_back(cl_region);
	custom_data->parent_entity = but;

	data_container->value_pointer = _button_group->scroll_y;

	_button_group->button_list.push_back(but);

	*but->world_position_x = *_button_group->region->offset_x + *_button_group->region->size_x - *but->button_gabarite->size_x;
	*but->world_position_y = *_button_group->region->offset_y;

	but->set_world_position(*but->offset_x, *but->offset_y, *but->offset_z);
	but->generate_vertex_buffer_for_all_sprite_layers();
	sprite_layer->generate_vertex_buffer_for_sprite_layer("scroll bar sprite layer");

	//EInputCore::logger_param("world x", *sprite->world_position_x);

}

void EButtonGroup::set_offset_borders(EButtonGroup* _group, float _left, float _right, float _bottom, float _up)
{
	*_group->border_left	= _left;
	*_group->border_right	= _right;

	*_group->border_bottom	= _bottom;
	*_group->border_up		= _up;
}

void EButtonGroup::apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style)
{

	if (*_group->can_change_style) {_group->selected_style = _style;}

	if ((EGUIStyle::active_style != nullptr) && (*_group->can_change_style))
	{
		//_group->selected_style = EGUIStyle::active_style;

		//for (EButtonGroupRow* row : _group->group_row_list)
		//if(row != nullptr)
		//for (EButtonGroup* group:row->button_group_list)
		//if (group != nullptr)
		//{
		//	EButtonGroup::apply_style_to_button_group(group, EGUIStyle::active_style);
		//}

		

		if (*_group->have_bg)
		{
			

			EButtonGroup::set_offset_borders
			(
				_group,
				*_style->offset_border_left,
				*_style->offset_border_right,
				*_style->offset_border_bottom,
				*_style->offset_border_up
			);


			EButtonGroup::generate_brick_textured_bg(_group);


			for (EntityButton* but : _group->button_list)
			{
				for (change_style_action csa : but->action_on_change_style_list)
				{
					csa(but, _style);

					but->generate_vertex_buffer_for_all_sprite_layers();
				}
			}
		}
		else
		{
			EButtonGroup::set_offset_borders
			(
				_group,
				0.0f,
				0.0f,
				0.0f,
				0.0f
			);
		}


}

	

	


}

void EButtonGroup::generate_brick_textured_bg(EButtonGroup* _group)
{
	if ((_group != nullptr) && (_group->selected_style != nullptr))
	{
		NS_ERenderCollection::set_brick_borders_and_subdivisions
		(
			*_group->selected_style->brick_border_left,
			*_group->selected_style->brick_border_right,
			*_group->selected_style->brick_border_bottom,
			*_group->selected_style->brick_border_up,

			*_group->selected_style->subdivision_x,
			*_group->selected_style->subdivision_y
		);

		if
		(
			(*_group->button_group_type == ButtonGroupType::BGT_DARKEN)
		)
		{
			NS_ERenderCollection::generate_brick_texture
			(
				_group->region,
				_group->background_sprite_layer,
				_group->selected_style->background_for_root_button_group
			);
		}
		else //if (*_group->button_group_type == ButtonGroupType::BGT_REGULAR)
		{
			NS_ERenderCollection::generate_brick_texture
			(
				_group->region,
				_group->background_sprite_layer,
				_group->selected_style->background_for_button_group
			);
		}

		if (_group->background_sprite_layer != nullptr)
		{
			_group->background_sprite_layer->sprite_layer_set_world_position(0.0f, 0.0f, 0.0f);
			_group->background_sprite_layer->generate_vertex_buffer_for_sprite_layer("Generate brick texture");
		}
	}
}

EButtonGroupRow* EButtonGroup::add_default_row(EButtonGroup* _group, ERegionGabarite* _region)
{
	EButtonGroupRow* jc_row = new EButtonGroupRow(_region);
	jc_row->parent_button_group = _group;

	jc_row->root_group = _group->root_group;
	//_group->parent_group_row = jc_row;

	_group->group_row_list.push_back(jc_row);

	return jc_row;
}

EButtonGroupRow* EButtonGroup::get_last_created_row(EButtonGroup* _group)
{
	if
	(
		(_group != nullptr)
		&&
		(!_group->group_row_list.empty())
	)
	{return _group->group_row_list[_group->group_row_list.size() - 1]; }
	else
	{return nullptr;}
}

void EButtonGroup::change_style(EButtonGroup* _group, EGUIStyle* _style)
{
	EButtonGroup::apply_style_to_button_group(_group, _style);

	//down to child elements
	for (EButtonGroupRow* row: _group->group_row_list)
	if (row != nullptr)
	for (EButtonGroup* group:row->button_group_list)
	if (group != nullptr)
	{
		EButtonGroup::change_style(group, _style);
	}

	EButtonGroup::refresh_button_group(_group);
	//_group->realign_all_buttons();
	//_group->align_groups();
	//EButtonGroup::calculate_culling_lines(_group);
	if (_group->header_button_group != nullptr)
	{
		EButtonGroup::change_style(_group->header_button_group, _style);
	}
}

bool EButtonGroup::catched_by_mouse(EButtonGroup* _group)
{
	if
	(
		(*_group->higher_culling_line_for_bg > *_group->lower_culling_line_for_bg)
		&&
		(EInputCore::MOUSE_POSITION_X >= *_group->region->world_position_x)
		&&
		(EInputCore::MOUSE_POSITION_X <= *_group->region->world_position_x + *_group->region->size_x)
		&&
		(EInputCore::MOUSE_POSITION_Y >= *_group->lower_culling_line_for_bg)
		&&
		(EInputCore::MOUSE_POSITION_Y <= *_group->higher_culling_line_for_bg)
	)
	{
		return true;
	}

	return false;
}

void EButtonGroup::stretch_parent_row(EButtonGroup* _group, float _new_y_size)
{
	*_group->parent_group_row->gabarite->size_y = _new_y_size;

	if
	(
		(_group->parent_group_row->parent_button_group != nullptr)
		&&
		(
			*_group->parent_group_row->gabarite->offset_y
			+
			*_group->parent_group_row->gabarite->size_y

			>

			*_group->parent_group_row->parent_button_group->region->size_y - *_group->parent_group_row->parent_button_group->border_up
		)
	)
	{
		EButtonGroupRow::stretch_parent_group
		(
			_group->parent_group_row,
			*_group->parent_group_row->gabarite->offset_y + *_group->parent_group_row->gabarite->size_y + *_group->parent_group_row->parent_button_group->border_up
		);
	}
}

void EButtonGroup::get_last_focused_group(EButtonGroup* _group)
{
	if
	(

		(EButtonGroup::catched_by_mouse(_group))
	)
	{
		focused_button_group = _group;

		if
		(
			(_group->slider != NULL)
			&&
			(!*_group->slider->disable_draw)
		)
		{focused_button_group_with_slider = _group;}
	}

	for (EButtonGroupRow* row : _group->group_row_list)
	for (EButtonGroup* group : row->button_group_list)
	{
		get_last_focused_group(group);
	}
	//return nullptr;
}

//void EButtonGroup::get_focused_group(EButtonGroup* _group)
//{
//	if
//	(
//		(EButtonGroup::catched_by_mouse(_group))
//	)
//	{
//		focused_button_group = _group;
//	}
//
//	for (EButtonGroupRow* row : _group->group_row_list)
//	for (EButtonGroup* group : row->button_group_list)
//	{
//		get_focused_group(group);
//	}
//	//return nullptr;
//}

EButtonGroup* EButtonGroup::create_default_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_with_bg,
		bgroup_with_slider,
		bgroup_default_bg
	);

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_root_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_with_bg,
		bgroup_with_slider,
		bgroup_darken_bg
	);

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_header_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_with_bg,
		bgroup_without_slider,
		bgroup_darken_bg
	);

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_invisible_button_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_without_bg,
		bgroup_without_slider,
		bgroup_darken_bg
	);

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg)
{
	EButtonGroup* just_created_button_group = new EButtonGroup(_region);
	just_created_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	if (_default_bg)
	{
		*just_created_button_group->button_group_type = ButtonGroupType::BGT_REGULAR;
	}
	else
	{
		*just_created_button_group->button_group_type = ButtonGroupType::BGT_DARKEN;
	}

	*just_created_button_group->have_bg = _have_bg;

	if (_have_bg)
	{ 
		just_created_button_group->background_sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);
	}
	else
	{
		*just_created_button_group->border_bottom	= 0.0f;
		*just_created_button_group->border_left		= 0.0f;
		*just_created_button_group->border_right	= 0.0f;
		*just_created_button_group->border_up		= 0.0f;
	}

	if (_have_slider)
	{
		EButtonGroup::add_horizontal_scroll_bar(just_created_button_group);
	}


	return just_created_button_group;
}


EGUIStyle* EGUIStyle::active_style = nullptr;
int EGUIStyle::number = 0;

void EGUIStyle::set_style_borders_and_subdivisions(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y)
{
	*_style->brick_border_left		= _border_left;
	*_style->brick_border_right		= _border_right;

	*_style->brick_border_up		= _border_up;
	*_style->brick_border_bottom	= _border_bottom;

	*_style->subdivision_x	= _subdivision_x;
	*_style->subdivision_y	= _subdivision_y;
}

void EGUIStyle::set_style_dark_borders_and_subdivisions(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y)
{
	*_style->dark_brick_border_left		= _border_left;
	*_style->dark_brick_border_right		= _border_right;
			 
	*_style->dark_brick_border_up		= _border_up;
	*_style->dark_brick_border_bottom	= _border_bottom;

	*_style->dark_subdivision_x	= _subdivision_x;
	*_style->dark_subdivision_y	= _subdivision_y;
}

void EGUIStyle::set_style_offset_borders(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up)
{
	*_style->offset_border_left		= _border_left;
	*_style->offset_border_right	= _border_right;

	*_style->offset_border_bottom	= _border_bottom;
	*_style->offset_border_up		= _border_up;
}

void EGUIStyle::set_style_dark_offset_borders(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up)
{
	*_style->dark_offset_border_left	= _border_left;
	*_style->dark_offset_border_right	= _border_right;
			 
	*_style->dark_offset_border_bottom	= _border_bottom;
	*_style->dark_offset_border_up		= _border_up;
}

void EGUIStyle::set_style_borders_and_subdivision_for_buttons(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y)
{
	*_style->button_border_left		= _border_left;
	*_style->button_border_right	= _border_right;

	*_style->button_border_bottom	= _border_up;
	*_style->button_border_up		= _border_bottom;

	*_style->button_subdivision_x	= _subdivision_x;
	*_style->button_subdivision_y	= _subdivision_y;
}

void EGUIStyle::set_style_borders_and_subdivision_for_slider_bg(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y)
{
	*_style->slider_border_left		= _border_left;
	*_style->slider_border_right	= _border_right;
	*_style->slider_border_up		= _border_up;
	*_style->slider_border_bottom	= _border_bottom;

	*_style->slider_subdivision_x	=	_subdivision_x;
	*_style->slider_subdivision_y	=	_subdivision_y;
}

std::vector<EGUIStyle*> EGUIStyle::style_list;
//EButtonGroupRow* EButtonGroupRow::create_default_row(ERegionGabarite* _region, EGUIStyle* _style)
//{
//	return nullptr;
//}

EButtonGroupRow::EButtonGroupRow(ERegionGabarite* _region)
{
	gabarite = _region;
}

EButtonGroupRow::EButtonGroupRow()
{
}

EButtonGroup* EButtonGroupRow::add_group(EButtonGroup* _group)
{
	/*EButtonGroup* jc_group = EButtonGroup::create_default_button_group
	(
		new ERegionGabarite()
	)*/

	_group->root_group = root_group;
	button_group_list.push_back(_group);
	_group->parent_group_row = this;

	return _group;
}

EButtonGroup* EButtonGroupRow::get_last_group(EButtonGroupRow* _row)
{
	if((_row != nullptr) && (!_row->button_group_list.empty()))
	{
		return _row->button_group_list[_row->button_group_list.size() - 1];
	}
	else
	{return nullptr;}
}

void EButtonGroupRow::stretch_parent_group(EButtonGroupRow* _row, float _new_y_size)
{
	EButtonGroup* p_group = _row->parent_button_group;

	if (*p_group->gabarite_size_mode_y == ButtonGroupGabariteSize::BGGS_EXACT_STRETCH)
	{
		*p_group->region->size_y = _new_y_size;
		EButtonGroup::generate_brick_textured_bg(p_group);
	}

	//*_group->parent_group_row
	if 
	(
		(p_group != nullptr)
		&&
		(p_group->parent_group_row != nullptr)
		&&
		(*p_group->region->offset_y + *p_group->region->size_y > *p_group->parent_group_row->gabarite->size_y)
	)
	{
		EButtonGroup::stretch_parent_row
		(
			p_group,
			*p_group->region->offset_y + *p_group->region->size_y
		);
	}
}
