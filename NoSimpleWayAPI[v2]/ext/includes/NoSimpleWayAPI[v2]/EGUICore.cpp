#pragma once
#ifndef _E_GUI_CORE_ALREADY_LINKED_
#define _E_GUI_CORE_ALREADY_LINKED_
#include "EGUICore.h"
#endif

std::vector<EWindow*> EWindow::window_list;

EButtonGroup* EButtonGroup::focused_button_group = nullptr;

//EButtonGroup* EButtonGroup::focused_button_group;
EButtonGroup* EButtonGroup::focused_button_group_with_slider = nullptr;
EButtonGroup* EButtonGroup::data_entity_filter = nullptr;

void EWindow::update_default(float _d)
{
	
}

void EWindow::update_additional(float _d)
{
}

void EWindow::GUI_update_default(float _d)
{

	for (EButtonGroup* b_group : group_list)
	if
	(
		(b_group != nullptr)
		&&
		(*b_group->is_active)
		&&
		(b_group->region_gabarite->world_position_y <= *b_group->higher_culling_line_for_bg)
		&&
		(b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y >= *b_group->lower_culling_line_for_bg)
	)
	{
		EButtonGroup::get_last_focused_group(b_group);
	}

	if ((EButtonGroup::focused_button_group != nullptr))
	{
		for (EntityButton* but : EButtonGroup::focused_button_group->button_list)
		for (ECustomData* data:but->custom_data_list)
		for (EClickableArea* c_area:data->clickable_area_list)
		if ((!EInputCore::MOUSE_BUTTON_LEFT)&&(*c_area->catched_body))
		{
			EClickableArea::active_clickable_region = c_area;
		}
	}

	for (EButtonGroup* b_group : group_list)
	if
	(
		(b_group != nullptr)
		&&
		(*b_group->is_active)
		//&&
		//(*b_group->region_gabarite->world_position_y										<= *b_group->higher_culling_line_for_bg)
		//&&
		//(*b_group->region_gabarite->world_position_y + *b_group->region_gabarite->size_y	>= *b_group->lower_culling_line_for_bg)
	)
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


	for (EButtonGroup* b_group : group_list)
	if
	(
		(b_group != nullptr)
		&&
		(*b_group->is_active)
		&&
		(b_group->region_gabarite->world_position_y <= 1920.0f)
		&&
		(b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y >= 0.0f)

	)
	{
		b_group->draw();
	}
}

void EWindow::GUI_draw_additional(float _d)
{
}

void EWindow::GUI_draw_second_pass(float _d)
{	
	//glDisable(GL_SCISSOR_TEST);

	//for (EButtonGroup* b_group : group_list)
	//{
	//	b_group->draw_second_pass();

	//	if (b_group->header_button_group != nullptr)
	//	{b_group->header_button_group->draw_second_pass();}
	//}
	int counter = 0;
	for (EButtonGroup* b_group : group_list)
	if ((b_group != nullptr) && (*b_group->is_active) && (counter <= 10))
	{
		b_group->draw_second_pass();
		counter++;
	}

}

EButtonGroup::EButtonGroup(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y)
{
	if (region_gabarite == nullptr)
	{
		ERegionGabarite::set_region_gabarite
		(&region_gabarite, new ERegionGabarite(_offset_x, _offset_y, _size_x, _size_y));
	}
	else
	{
		region_gabarite->set_region_offset_and_size(_offset_x, _offset_y, _offset_z, _size_x, _size_y);
	}
}

EButtonGroup::EButtonGroup(ERegionGabarite* _region)
{
	ERegionGabarite::set_region_gabarite(&region_gabarite, _region);
	//region_gabarite = _region;
}

EButtonGroup::~EButtonGroup()
{
}

void EButtonGroup::update(float _d)
{
	//clickable_area->update(_d);

	//subgroup
	//EButtonGroup* prev_group = nullptr;

	//if (but->re*higher_culling_line)

	//invisible elements become visible



		/*if (row->header_button_group != nullptr)
		{
			row->header_button_group->update(_d);
		}*/
	if (can_see_this_group())
	{
		if (!button_list.empty())
		for (unsigned int i = 0; i < button_list.size(); i++)
		if (button_list[i]->need_remove)
		{
			EntityButton* but = button_list[i];
			button_list.erase(button_list.begin() + i);
			delete but;
			i--;
		}

		{
			for (EntityButton* but : button_list)
			if
			(
				(*but->update_when_scissored)
				||
				(
					(but->button_gabarite->world_position_y <= *higher_culling_line + *border_bottom)
					&&
					(but->button_gabarite->world_position_y + but->button_gabarite->size_y >= *lower_culling_line - *border_up)
				)
			)
			{
				but->update(_d);
			}
		}

		//final button groun, not subgroup
		//if (group_row_list.empty())
	
		if (header_button_group != nullptr)
		{header_button_group->update(_d);}

	
		phantom_translate_if_need();
		calculate_culling_lines(this);

		for (EButtonGroup* _group : group_list)
		{
			_group->update(_d);
		}
	}



}

void EButtonGroup::draw()
{
	//clickable_area->draw();

	//EInputCore::logger_simple_success("draw button group");
	if
	(
		can_see_this_group()
		//(*region_gabarite->world_position_y <= *higher_culling_line_for_bg)
		//&&
		//(*region_gabarite->world_position_y + *region_gabarite->size_y >= *lower_culling_line_for_bg)
	)
	{
		batcher_for_default_draw->draw_call();

		glDisable(GL_SCISSOR_TEST);
		//glDisable(GL_SCISSOR_TEST);
		//		SHADOW		//
		/* */if ((root_group == this) && (true))
			/* */ {
			/* */	NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLACK, 0.335f * 2.0f);
			/* */	if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			/* */	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			/* */(
				/* */		batcher_for_default_draw->vertex_buffer,
				/* */		batcher_for_default_draw->last_vertice_buffer_index,
				/* */		region_gabarite->world_position_x - 3.0f,
				/* */		region_gabarite->world_position_y - 3.0f,
				/* */		region_gabarite->size_x + 6.0f,
				/* */		region_gabarite->size_y + 6.0f,
				/* */		NS_DefaultGabarites::texture_gabarite_white_pixel
			/* */);
			/* */
		}
		batcher_for_default_draw->draw_call();

		glEnable(GL_SCISSOR_TEST);

		glScissor
		(
			region_gabarite->world_position_x,
			*lower_culling_line_for_bg,

			region_gabarite->size_x,
			max(0.0f, *higher_culling_line_for_bg - *lower_culling_line_for_bg)
		);
		//BG
		if ((background_sprite_layer != nullptr) && (*have_bg))
		{
			background_sprite_layer->transfer_vertex_buffer_to_batcher();
		}

		if ((EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL)) && (EButtonGroup::focused_button_group == this))
		{
			NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.13f);
			if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,
				region_gabarite->world_position_x + 0.0f,
				region_gabarite->world_position_y + 0.0f,
				region_gabarite->size_x - 0.0f,
				region_gabarite->size_y - 0.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}

		if ((EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL)) && (EButtonGroup::focused_button_group_with_slider == this))
		{
			NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLUE, 0.13f);
			if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,
				region_gabarite->world_position_x + 0.0f,
				region_gabarite->world_position_y + 0.0f,
				region_gabarite->size_x - 0.0f,
				region_gabarite->size_y - 0.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}

		NS_EGraphicCore::pbr_batcher->draw_call();
		batcher_for_default_draw->draw_call();

		NS_EGraphicCore::test_batcher->draw_call();


		//ELEMENTS
		if (parent_group == nullptr)
		{
			glScissor(region_gabarite->world_position_x, region_gabarite->world_position_y, region_gabarite->size_x, region_gabarite->size_y);
		}
		else
		{
			//if (root_group != nullptr)
			{
				glScissor
				(
					region_gabarite->world_position_x,
					*lower_culling_line,

					region_gabarite->size_x,
					max(0.0f, *higher_culling_line - *lower_culling_line)
				);
			}
		}


		for (EntityButton* but : button_list)
			if
				(
					(but->world_position_y + but->button_gabarite->size_y >= *lower_culling_line)
					&&
					(but->world_position_y <= *higher_culling_line)
					)
			{
				but->draw();
			}
		NS_EGraphicCore::pbr_batcher->draw_call();//draw pbg bg
		batcher_for_default_draw->draw_call();//draw text to default batcher



		//recursive draw


		for (EButtonGroup* group : group_list) { group->draw(); }



		//draw call to prepare for header
		NS_EGraphicCore::test_batcher->draw_call();
		NS_EGraphicCore::pbr_batcher->draw_call();




		glDisable(GL_SCISSOR_TEST);

		if (EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL))
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_GREEN);
			if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			NS_ERenderCollection::add_data_to_vertex_buffer_rama
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,
				region_gabarite->world_position_x + 0.0f,
				region_gabarite->world_position_y + 0.0f,
				region_gabarite->size_x - 0.0f,
				region_gabarite->size_y - 0.0f,
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
				region_gabarite->world_position_x + 0.0f,
				*lower_culling_line,
				region_gabarite->size_x - 0.0f,
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
				region_gabarite->world_position_x + 0.0f,
				*higher_culling_line,
				region_gabarite->size_x - 0.0f,
				1.0f,
				1.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}

		if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
		{
			for (EButtonGroup* group : group_list)
			{
				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_RED);
				if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				NS_ERenderCollection::add_data_to_vertex_buffer_rama
				(
					batcher_for_default_draw->vertex_buffer,
					batcher_for_default_draw->last_vertice_buffer_index,
					group->region_gabarite->world_position_x + 0.0f,
					group->region_gabarite->world_position_y + 0.0f,
					group->region_gabarite->size_x - 0.0f,
					group->region_gabarite->size_y - 0.0f,
					1.0f,
					NS_DefaultGabarites::texture_gabarite_white_pixel
				);
				//batcher_for_default_draw->draw_call();
			}
		}

		NS_EGraphicCore::pbr_batcher->draw_call();
		batcher_for_default_draw->draw_call();

		NS_EGraphicCore::test_batcher->draw_call();

		if (header_button_group != nullptr)
		{
			header_button_group->draw();
		}

		draw_second_pass();
	}
}

void EButtonGroup::draw_second_pass()
{
	

	for (EntityButton* but : button_list)
	if
	(
		(but->world_position_y + but->button_gabarite->size_y >= *lower_culling_line)
		&&
		(but->world_position_y <= *higher_culling_line)
	)
	{
		but->draw_second_pass();
	}

	for (EButtonGroup* group : group_list) { group->draw_second_pass(); }
}

void EButtonGroup::align_groups()
{
	*highest_point_y = 0.0f;
	//float minimal_culling_line_top		= 10000.0f;
	//float minimal_culling_line_bottom	= -10000.0f;

	if (parent_group == nullptr)
	{
		region_gabarite->world_position_x = region_gabarite->offset_x;
		region_gabarite->world_position_y = region_gabarite->offset_y;
	}

	if
	(
		(*culling_lines_method == CullingLinesCalcMethod::CLCM_BY_HIMSELF)
		&&
		(root_group != nullptr)
	)
	{
		region_gabarite->world_position_x = root_group->region_gabarite->offset_x + 0.0f;
		region_gabarite->world_position_y = root_group->region_gabarite->offset_y + root_group->region_gabarite->size_y - region_gabarite->size_y * 0.0f - *root_group->border_up;
	}





	
	EButtonGroup* prev_group = nullptr;

		prev_group = nullptr;

		//stretch row
		for (EButtonGroup* group : group_list)
		{	
			//bool need_redraw = false;


			//if ((*group->gabarite_size_mode_x == GroupStretchMode::PARENT_SIZE) || (*group->gabarite_size_mode_y == GroupStretchMode::PARENT_SIZE))



			//if (*group->have_bg)
			//{group->region_gabarite->offset_y = *border_bottom + 3.0f;}
			//else
			{group->region_gabarite->offset_y = *border_bottom + 0.0f;}

			if (prev_group != nullptr)
			{
				if (*child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
				{
					group->region_gabarite->offset_x = *border_left + 0.0f;
					group->region_gabarite->offset_y = prev_group->region_gabarite->offset_y + prev_group->region_gabarite->size_y + 10.0f; 
				}
				else
				if (*child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
				{
					group->region_gabarite->offset_x = prev_group->region_gabarite->offset_x + prev_group->region_gabarite->size_x + 1.0f;
					group->region_gabarite->offset_y = prev_group->region_gabarite->offset_y;
				}
			}
			else
			{
				//if (*group->have_bg)
				//{group->region_gabarite->offset_x = *border_left + 3.0f;}
				//else
				{group->region_gabarite->offset_x = *border_left;}
			}

			
			

			group->region_gabarite->world_position_x = region_gabarite->world_position_x + group->region_gabarite->offset_x;
			group->region_gabarite->world_position_y = region_gabarite->world_position_y + group->region_gabarite->offset_y + *scroll_y;
			group->region_gabarite->world_position_z = region_gabarite->world_position_z + group->region_gabarite->offset_z;

			
			


			
	
			prev_group = group;

			group->align_groups();
			
		}

		
	

	if (prev_group != nullptr)
	{
		*highest_point_y
		=
		max
		(
			prev_group->region_gabarite->offset_y
			+
			prev_group->region_gabarite->size_y
			-
			0.0f
			,
			*highest_point_y
		);
	}

	


	for (EButtonGroup* group : group_list) { group->align_groups(); }


	
	

}

void EButtonGroup::calculate_culling_lines(EButtonGroup* _group)
{
	if (_group->parent_group == nullptr)
	{


		*_group->higher_culling_line		= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		*_group->lower_culling_line			= _group->region_gabarite->world_position_y;

		*_group->higher_culling_line_for_bg	= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		*_group->lower_culling_line_for_bg	= _group->region_gabarite->world_position_y;

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


		*_group->higher_culling_line		= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		*_group->lower_culling_line			= _group->region_gabarite->world_position_y;

		*_group->higher_culling_line_for_bg	= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		*_group->lower_culling_line_for_bg	= _group->region_gabarite->world_position_y;
	}

	

	//for (EButtonGroupRow*	row:	_group->group_row_list)
	for (EButtonGroup*		group: _group->group_list)
	{
		*group->higher_culling_line_for_bg = min
		(
			group->region_gabarite->world_position_y + group->region_gabarite->size_y,
			_group->region_gabarite->world_position_y + _group->region_gabarite->size_y - *_group->border_up
		);

		*group->higher_culling_line_for_bg = min
		(
			*group->higher_culling_line_for_bg,
			*_group->higher_culling_line_for_bg
		);



		*group->lower_culling_line_for_bg = max
		(
			group->region_gabarite->world_position_y,
			_group->region_gabarite->world_position_y + *_group->border_bottom
		);

		*group->lower_culling_line_for_bg = max
		(
			*group->lower_culling_line_for_bg,
			*_group->lower_culling_line_for_bg
		);



		*group->higher_culling_line = min
		(
			group->region_gabarite->world_position_y + group->region_gabarite->size_y - *group->border_up,
			_group->region_gabarite->world_position_y + _group->region_gabarite->size_y - *_group->border_up
		);

		*group->higher_culling_line = min
		(
			*group->higher_culling_line,
			*_group->higher_culling_line
		);


		*group->lower_culling_line = max(group->region_gabarite->world_position_y + *group->border_bottom, _group->region_gabarite->world_position_y + *_group->border_bottom);
		*group->lower_culling_line = max(*group->lower_culling_line, *_group->lower_culling_line);

		//EButtonGroup::calculate_culling_lines(group);
	}

	for (EButtonGroup* group : _group->group_list) { EButtonGroup::calculate_culling_lines(group); }
}

void EButtonGroup::generate_vertex_buffer_for_group(EButtonGroup* _group)
{
	//for (EButtonGroup* group : _group->group_list)
	//if ((*group->need_redraw) && (true))
	//{
	//		EButtonGroup::generate_brick_textured_bg(group);

	//		*group->need_redraw = false;
	//}

	if ((*_group->need_redraw))
	{
		EButtonGroup::generate_brick_textured_bg(_group);
		*_group->need_redraw = false;
	}

	if (_group->background_sprite_layer != nullptr)
	{
		_group->background_sprite_layer->sprite_layer_set_world_position
		(
			_group->region_gabarite->world_position_x,
			_group->region_gabarite->world_position_y,
			_group->region_gabarite->world_position_z
		);

		_group->background_sprite_layer->generate_vertex_buffer_for_sprite_layer("Button group background");
	}

	if (_group->slider != nullptr)
	{
		for (change_style_action csa : _group->slider->action_on_change_style_list)
		{
			csa(_group->slider, _group->selected_style);

			_group->slider->generate_vertex_buffer_for_all_sprite_layers();
		}
		_group->slider->set_world_position(_group->slider->world_position_x, _group->slider->world_position_y, _group->slider->world_position_z);
		_group->slider->generate_vertex_buffer_for_all_sprite_layers();
	}

	//if (group_row_list.empty())
	{
		for (EntityButton* but : _group->button_list)
		{
			but->set_world_position(but->world_position_x, but->world_position_y, but->world_position_z);


			//if
			//(
			//	(*but->world_position_y + *but->button_gabarite->size_y >= *_group->lower_culling_line)
			//	&&
			//	(*but->world_position_y <= *_group->higher_culling_line)
			//)
			{
				but->generate_vertex_buffer_for_all_sprite_layers();
			}
		}
	}

	for (EButtonGroup* group : _group->group_list) { EButtonGroup::generate_vertex_buffer_for_group(group); }

}

void EButtonGroup::substretch_groups_y()
{
	//EInputCore::logger_simple_info("substretch");
	//stretch every child, if child size y more than parent size y, also stretch parent
	float total_y = *border_bottom + *border_up;
	float max_y = 0.0f;

	EButtonGroup* prev_group = nullptr;
	if (*child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{
		total_y += ((float)(group_list.size()) - 1.0f) * 3.0f;

		for (EButtonGroup* group : group_list)
		if (!*group->stretch_y_by_parent_size)
		{
			total_y += group->region_gabarite->size_y;
		}
	}

	if (*child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{
		for (EButtonGroup* group : group_list)
		if (!*group->stretch_y_by_parent_size)
		{
			max_y = max(max_y, group->region_gabarite->size_y);
		}

		total_y += max_y;
	}

	for (EButtonGroup* group : group_list)
	{
		//EInputCore::logger_param("child size y", *group->region_gabarite->offset_y + *group->region_gabarite->size_y + 6.0f);
		//EInputCore::logger_param("parent size y", *region_gabarite->size_y);

		if
		(

			//(group->parent_group != nullptr)
			//&&
			//(*stretch_mode == GroupStretchMode::STRETCHED_FILL_VOID)
			(*can_be_stretched_by_child)
			&&
			(*child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
			&&
			(total_y + 6.0f > region_gabarite->size_y)
		)
		{
			EButtonGroup::stretch_parent_group(this, total_y + 6.0f);
		}
	}

	for (EButtonGroup* group : group_list) {group->substretch_groups_y();}
	
}

void EButtonGroup::group_stretch_x()
{
	float			constant_element_sizes_x	= 0.0f;
	float			summ_size					= 0.0f;
	float			target_size					= 0.0f;
	float			final_size					= 0.0f;

	float			slider_effect				= 0.0f;



	unsigned int	dynamic_elements_count		= 0;

	if ((slider != nullptr) && (!slider->disable_draw))
	{
		slider_effect = slider->button_gabarite->size_x + 3.0f;
	}

	float shrink_size = 0.0f;
	//if (!*have_bg) { shrink_size = 0.0f; }

	if (*child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{


		target_size = region_gabarite->size_x - *border_left - *border_right - (group_list.size() - 1) * 1.0f - shrink_size;
		target_size -= slider_effect;

		for (EButtonGroup* group : group_list)
		{
			if (*group->stretch_x_by_parent_size)
			{
				dynamic_elements_count++;
			}
			else
			{
				target_size -= group->region_gabarite->size_x;
				constant_element_sizes_x += group->region_gabarite->size_x;
			}
		}
	}

	if (*child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{
		target_size = region_gabarite->size_x - *border_left - *border_right - shrink_size;
		target_size -= slider_effect;

		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0) { final_size = target_size / float(dynamic_elements_count); }



	//final_size = 100.0f;
	for (EButtonGroup* group : group_list)
	{
		if ((*group->stretch_x_by_parent_size) && (group->region_gabarite->size_x != final_size))
		{
			group->region_gabarite->size_x = round(final_size);
			*group->need_redraw = true;
		}
	}

	for (EButtonGroup* group : group_list) { group->group_stretch_x(); }
}

void EButtonGroup::group_stretch_y()
{
	float			constant_element_sizes_y	= 0.0f;
	float			summ_size					= 0.0f;
	float			target_size					= 0.0f;
	float			final_size					= 0.0f;
	
	

	unsigned int	dynamic_elements_count		= 0;

	float shrink_size = 0.0f;
	if (!*have_bg) { shrink_size = 0.0f; }

	if (*child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{

		target_size = region_gabarite->size_y - *border_bottom - *border_up - (group_list.size() - 1) * 10.0f - shrink_size;

		for (EButtonGroup* group : group_list)
		{
			if (*group->stretch_y_by_parent_size)
			{
				dynamic_elements_count++;
			}
			else
			{
				target_size					-= group->region_gabarite->size_y;
				constant_element_sizes_y	+= group->region_gabarite->size_y;
			}
		}
	}

	if (*child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{
		target_size = region_gabarite->size_y - *border_bottom - *border_up - shrink_size;
		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0) { final_size = target_size / float(dynamic_elements_count); }

	//final_size = 100.0f;
	for (EButtonGroup* group : group_list)
	{
		if ((*group->stretch_y_by_parent_size) && (group->region_gabarite->size_y != final_size))
		{
			group->region_gabarite->size_y = round(final_size);
			*group->need_redraw = true;
		}
	}

	for (EButtonGroup* group : group_list) { group->group_stretch_y(); }
}

void EButtonGroup::check_slider()
{
	*have_slider = true;//have no slider by default

	if (slider != nullptr)
	{slider->disable_draw = true;}

	float child_elements_height_summ = 0.0f;
	float max_y = 0.0f;
	//stretchable group cannot have slider
	if (*can_be_stretched_by_child)
	{
		for (EButtonGroup* group : group_list)
		{*group->parent_have_slider = false;}//parent have no slider
	}
	else//potentially, can have slider
	{
		if (*child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
		{
			child_elements_height_summ = ((float)group_list.size() - 1.0f) * 3.0f;

			for (EButtonGroup* group : group_list)
			if (!*group->stretch_y_by_parent_size)//constant size
			{
				child_elements_height_summ += group->region_gabarite->size_y;//*szOID_ROOT_PROGRAM_AUTO_UPDATE_CA_REVOCATION
			}
		}

		if (*child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
		{

			for (EButtonGroup* group : group_list)
			if (!*group->stretch_y_by_parent_size)//constant size
			{
				max_y = max(max_y, group->region_gabarite->size_y);//*szOID_ROOT_PROGRAM_AUTO_UPDATE_CA_REVOCATION
			}

			child_elements_height_summ += max_y;
		}

		

		if (child_elements_height_summ > region_gabarite->size_y - 3.0f - *border_bottom - *border_up)
		{
			if (slider != nullptr)
			{
				slider->disable_draw = false;
				*have_slider = true;
				//EInputCore::logger_param("summ", child_elements_height_summ);
				//EInputCore::logger_param("size y", *region_gabarite->size_y - 6.0f - *border_bottom - *border_up);
				//std::cout << std::endl;

				for (EButtonGroup* group : group_list)
				{
					//EInputCore::logger_param("group size y", *group->region_gabarite->size_y);
					*group->parent_have_slider = true;
				}//parent have no slider
			}
		}
		else
		{
			if (slider != nullptr)
			{
				slider->disable_draw = true;
				*have_slider = false;
				for (EButtonGroup* group : group_list)
				{*group->parent_have_slider = false;}//parent have no slider
			}
		}
	}

	for (EButtonGroup* group : group_list) { group->check_slider(); }
}

void EButtonGroup::refresh_button_group(EButtonGroup* _group)
{
	
	_group->substretch_groups_y();
	_group->check_slider();

	_group->group_stretch_y();
	_group->group_stretch_x();

	_group->align_groups();
	EButtonGroup::calculate_culling_lines(_group);
	_group->realign_all_buttons();

	EButtonGroup::generate_vertex_buffer_for_group(_group);

	//for (EButtonGroup* group: _group->group_list)
	//{EButtonGroup::refresh_button_group(group);}

	if (_group->header_button_group != nullptr)
	{EButtonGroup::refresh_button_group(_group->header_button_group);}
}

void EButtonGroup::realign_all_buttons()
{
	EntityButton* prev_button = nullptr;

	float slider_additional = 0.0f;



	for (EntityButton* but : button_list)
	if
	(
		(
			(!*but->fixed_position)
			||
			(false)
		)
		&&
		(!but->disable_draw)
		&&
		(!but->disabled)
	)
	{
		if (prev_button != nullptr)
		{
			but->offset_x = prev_button->offset_x + prev_button->button_gabarite->offset_x + prev_button->button_gabarite->size_x + 3.0f;
			but->offset_y = prev_button->offset_y;

			if (slider != nullptr) { slider_additional = slider->button_gabarite->size_x + 3.0f; }

			if (but->offset_x + but->button_gabarite->size_x + slider_additional >= region_gabarite->size_x)
			{
				but->offset_x = *but->parent_button_group->border_left + 2.0f;
				but->offset_y += but->button_gabarite->size_y + 3.0f;
			}

			
		}
		else
		{
			but->offset_x = *but->parent_button_group->border_left + 2.0f;
			but->offset_y = *but->parent_button_group->border_bottom + 2.0f;
		}

		if ((*but->fixed_position) && (true))
		{
			but->world_position_x = but->parent_button_group->region_gabarite->world_position_x + but->offset_x;
			but->world_position_y = but->parent_button_group->region_gabarite->world_position_y + but->offset_y;
		}
		else
		{
			but->world_position_x = but->parent_button_group->region_gabarite->world_position_x + but->offset_x + *but->parent_button_group->scroll_x;
			but->world_position_y = but->parent_button_group->region_gabarite->world_position_y + but->offset_y + *but->parent_button_group->scroll_y;


			//*but->world_position_x = *but->parent_button_group->region->world_position_x + *but->parent_button_group->scroll_y;
			//*but->world_position_y = *but->parent_button_group->region->world_position_y;
		}

		*highest_point_y = max(*highest_point_y, but->offset_y + but->button_gabarite->size_y + 3.0f);

		if ((slider != nullptr) && (*highest_point_y > region_gabarite->size_y - 0.0f - *border_up))
		{
			slider->disable_draw = false;

			for (EButtonGroup* group : group_list) {*group->have_slider = true;}
		}
		//EInputCore::logger_param("highest point y", *highest_point_y);
		prev_button = but;
	}
	else
	{
		//but->update(0.1f);
	}



	if (slider != nullptr)
	{
		slider->offset_x
			=
			region_gabarite->size_x
			-
			slider->button_gabarite->size_x
			-
			*border_right;



		slider->world_position_x
			=
			slider->offset_x
			+
			region_gabarite->world_position_x;

		slider->offset_y = 0.0f;
		slider->world_position_y = region_gabarite->world_position_y;
	}

	for (EButtonGroup* group : group_list) { group->realign_all_buttons(); }
}

void EButtonGroup::add_horizontal_scroll_bar(EButtonGroup* _button_group)
{
	EntityButton* but = new EntityButton();

	_button_group->slider = but;

	//*but->disable_draw = true;

	ECustomData* custom_data = new ECustomData();
	EDataContainerScrollBar* data_container = new EDataContainerScrollBar();
	custom_data->actions_on_update.push_back(EDataActionCollection::action_update_slider);
	but->action_on_change_style_list.push_back(action_change_style_slider);

	EClickableArea* cl_region = new EClickableArea();

	//bar
		ESpriteLayer* sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
		*sprite_layer->offset_y = *_button_group->border_bottom;

		if
	(
			(_button_group->selected_style != nullptr)
			&&
			(_button_group->selected_style->slider_inactive != nullptr)
		)
		{
			but->sprite_layer_list.push_back(sprite_layer);
			ERegionGabarite::temporary_gabarite->set_region_offset_and_size
			(
				0.0f,
				0.0f,
				0.0f,
				*_button_group->selected_style->slider_inactive->main_texture->size_x_in_pixels,
				_button_group->region_gabarite->size_y - *_button_group->border_bottom - *_button_group->border_up
			);
		

		//NS_ERenderCollection::set_brick_borders_and_subdivisions
		//(
		//	*_button_group->selected_style->slider_bg->side_size_left,
		//	*_button_group->selected_style->slider_bg->side_size_right,
		//	*_button_group->selected_style->slider_bg->side_size_bottom,
		//	*_button_group->selected_style->slider_bg->side_size_up,

		//	*_button_group->selected_style->slider_bg->subdivision_x,
		//	*_button_group->selected_style->slider_bg->subdivision_y
		//);

		//NS_ERenderCollection::generate_brick_texture
		//(
		//	ERegionGabarite::temporary_gabarite,
		//	sprite_layer,
		//	_button_group->selected_style->slider_bg->main_texture,
		//	_button_group->selected_style->slider_bg->normal_map_texture,
		//	_button_group->selected_style->slider_bg->gloss_map_texture
		//);

		//sprite_layer->sprite_layer_set_world_position(0.0f, 0.0f, 0.0f);
		//sprite_layer->generate_vertex_buffer_for_sprite_layer("init bg");

		//head inactive
		sprite_layer
		=
		ESpriteLayer::create_default_sprite_layer(_button_group->selected_style->slider_inactive->main_texture);
			ESpriteLayer::get_last_created_sprite(sprite_layer)->set_texture_gabarite
			(
				_button_group->selected_style->slider_inactive->main_texture,
				_button_group->selected_style->slider_inactive->normal_map_texture,
				_button_group->selected_style->slider_inactive->gloss_map_texture
			);

		cl_region->sprite_layer_list.push_back(sprite_layer);


		//head_active
		ESpriteLayer::get_last_sprite_frame(sprite_layer)
		->
		sprite_list.push_back (ESprite::create_default_sprite (_button_group->selected_style->slider_active->main_texture, sprite_layer));
		ESpriteLayer::get_last_created_sprite(sprite_layer)->set_texture_gabarite
		(
			_button_group->selected_style->slider_active->main_texture,
			_button_group->selected_style->slider_active->normal_map_texture,
			_button_group->selected_style->slider_active->gloss_map_texture
		);
		sprite_layer->make_as_PBR();	
	}
	else
	{
			EInputCore::logger_simple_error("[creating slider] Selected style in parent group is empty!");
	}
	
	ERegionGabarite* clickable_gabarite
		=
		new ERegionGabarite
		(
			0.0f,
			*_button_group->border_bottom,
			ESpriteLayer::get_last_created_sprite(sprite_layer)->size_x,
			ESpriteLayer::get_last_created_sprite(sprite_layer)->size_y
		);


	ERegionGabarite::set_region_gabarite
	(&cl_region->region_gabarite, clickable_gabarite);

	cl_region->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
	cl_region->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
	


		
	//

	ERegionGabarite* button_gabarite
	=
	new ERegionGabarite
	(
		0.0f,
		0.0f,
		ESpriteLayer::get_last_created_sprite(sprite_layer)->size_x,
		ESpriteLayer::get_last_created_sprite(sprite_layer)->size_y
	);

	
	//r_gabarite->
	but->custom_data_list.push_back(custom_data);
	but->button_gabarite = button_gabarite;
	but->parent_button_group = _button_group;
	*but->fixed_position = true;
	*but->update_when_scissored = true;

	custom_data->data_container = data_container;
	custom_data->clickable_area_list.push_back(cl_region);
	custom_data->parent_entity = but;

	data_container->value_pointer = _button_group->scroll_y;

	_button_group->button_list.push_back(but);

	but->world_position_x = _button_group->region_gabarite->offset_x + _button_group->region_gabarite->size_x - but->button_gabarite->size_x;
	but->world_position_y = _button_group->region_gabarite->offset_y;

	but->set_world_position(but->offset_x, but->offset_y, but->offset_z);
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
	//_group->translate_child_elements
	//(
	//	_group->region_gabarite->phantom_translate_x,
	//	_group->region_gabarite->phantom_translate_y,
	//	_group->region_gabarite->phantom_translate_z
	//);

	//_group->region_gabarite->have_phantom_translation = false;

	//_group->region_gabarite->phantom_translate_x = 0.0f;
	//_group->region_gabarite->phantom_translate_y = 0.0f;
	//_group->region_gabarite->phantom_translate_z = 0.0f;

	_group->phantom_translate_if_need();

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

		
		//*_group->region->size_x = *_group->base_width	+ *_group->border_left		+ *_group->border_right;
		//*_group->region->size_y = *_group->base_height	+ *_group->border_bottom	+ *_group->border_up;

		if (*_group->have_bg)
		{
			if ((*_group->button_group_type == ButtonGroupType::BGT_REGULAR) && (_style->button_group_main != nullptr))
			{ EBrickStyle::apply_brick_parameters_to_button_group(_group, _style->button_group_main); }

			if ((*_group->button_group_type == ButtonGroupType::BGT_DARKEN) && (_style->button_group_darken != nullptr))
			{ EBrickStyle::apply_brick_parameters_to_button_group(_group, _style->button_group_darken); }

			EButtonGroup::generate_brick_textured_bg(_group);
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

		for (EntityButton* but : _group->button_list)
		{
			for (change_style_action csa : but->action_on_change_style_list)
			{
				csa(but, _style);

				but->generate_vertex_buffer_for_all_sprite_layers();
			}
		}

		//_group->refresh_button_group(_group);
}

	

	


}

void EButtonGroup::generate_brick_textured_bg(EButtonGroup* _group)
{
	if ((_group != nullptr) && (_group->selected_style != nullptr) && (_group->background_sprite_layer != nullptr))
	{

		NS_ERenderCollection::temporary_sprites = true;

		if
		(
			(*_group->button_group_type == ButtonGroupType::BGT_DARKEN)
		)
		{
			

			NS_ERenderCollection::set_brick_borders_and_subdivisions
			(
				*_group->selected_style->button_group_darken->side_size_left,
				*_group->selected_style->button_group_darken->side_size_right,
				*_group->selected_style->button_group_darken->side_size_bottom,
				*_group->selected_style->button_group_darken->side_size_up,

				*_group->selected_style->button_group_darken->subdivision_x,
				*_group->selected_style->button_group_darken->subdivision_y
			);

			NS_ERenderCollection::generate_brick_texture
			(
				_group->region_gabarite,
				_group->background_sprite_layer,
				_group->selected_style->button_group_darken->main_texture,
				_group->selected_style->button_group_darken->normal_map_texture,
				_group->selected_style->button_group_darken->gloss_map_texture
			);
		}
		else //if (*_group->button_group_type == ButtonGroupType::BGT_REGULAR)
		{
			NS_ERenderCollection::set_brick_borders_and_subdivisions
			(
				*_group->selected_style->button_group_main->side_size_left,
				*_group->selected_style->button_group_main->side_size_right,
				*_group->selected_style->button_group_main->side_size_bottom,
				*_group->selected_style->button_group_main->side_size_up,
													  
				*_group->selected_style->button_group_main->subdivision_x,
				*_group->selected_style->button_group_main->subdivision_y
			);

			NS_ERenderCollection::generate_brick_texture
			(
				_group->region_gabarite,
				_group->background_sprite_layer,
				_group->selected_style->button_group_main->main_texture,
				_group->selected_style->button_group_main->normal_map_texture,
				_group->selected_style->button_group_main->gloss_map_texture
			);
		}


	}
}

//EButtonGroupRow* EButtonGroup::add_default_row_to_group(EButtonGroup* _group, ERegionGabarite* _region)
//{
//	EButtonGroupRow* jc_row = new EButtonGroupRow(_region);
//	jc_row->parent_button_group = _group;
//
//	jc_row->root_group = _group->root_group;
//	//_group->parent_group_row = jc_row;
//
//	_group->group_row_list.push_back(jc_row);
//
//	return jc_row;
//}

//EButtonGroupRow* EButtonGroup::get_last_created_row(EButtonGroup* _group)
//{
//	if
//	(
//		(_group != nullptr)
//		&&
//		(!_group->group_row_list.empty())
//	)
//	{return _group->group_row_list[_group->group_row_list.size() - 1]; }
//	else
//	{return nullptr;}
//}

void EButtonGroup::change_style(EButtonGroup* _group, EGUIStyle* _style)
{
	EButtonGroup::apply_style_to_button_group(_group, _style);

	//down to child elements
	for (EButtonGroup* group:_group->group_list)
	if (group != nullptr)
	{
		EButtonGroup::change_style(group, _style);
	}

	
	//_group->realign_all_buttons();
	//_group->align_groups();
	//EButtonGroup::calculate_culling_lines(_group);
	if (_group->header_button_group != nullptr)
	{
		EButtonGroup::change_style(_group->header_button_group, _style);
	}

	EButtonGroup::refresh_button_group(_group);
}

bool EButtonGroup::catched_by_mouse(EButtonGroup* _group)
{
	if
	(
		(*_group->higher_culling_line_for_bg > *_group->lower_culling_line_for_bg)
		&&
		(EInputCore::MOUSE_POSITION_X >= _group->region_gabarite->world_position_x)
		&&
		(EInputCore::MOUSE_POSITION_X <= _group->region_gabarite->world_position_x + _group->region_gabarite->size_x)
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

void EButtonGroup::stretch_parent_group(EButtonGroup* _group, float _new_y_size)
{
	_group->region_gabarite->size_y = _new_y_size;
	*_group->need_redraw = true;

	EButtonGroup::generate_brick_textured_bg(_group);
	EButtonGroup* _parent = _group->parent_group;
	if
	(
		(_parent != nullptr)
		&&
		(*_parent->can_be_stretched_by_child)
		&&
		(*_parent->child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
		&&
		(
			_parent->region_gabarite->offset_y
			+
			_parent->region_gabarite->size_y

			>

			_parent->region_gabarite->size_y - *_parent->border_up
		)
	)
	{
		EButtonGroup::stretch_parent_group
		(
			_parent,
			_parent->region_gabarite->offset_y + _parent->region_gabarite->size_y + *_parent->border_up
		);
	}
}

EButtonGroup* EButtonGroup::add_group(EButtonGroup* _new_group)
{
	_new_group->parent_group = this;
	group_list.push_back(_new_group);
	_new_group->root_group = root_group;

	return _new_group;
}

void EButtonGroup::translate(float _x, float _y, float _z, bool _move_positions)
{

	region_gabarite->world_position_x += _x;
	region_gabarite->world_position_y += _y;
	region_gabarite->world_position_z += _z;

	*higher_culling_line += _y;
	*higher_culling_line_for_bg += _y;

	*lower_culling_line += _y;
	*lower_culling_line_for_bg += _y;

	if (_move_positions)
	{
		region_gabarite->offset_x += _x;
		region_gabarite->offset_y += _y;
		region_gabarite->offset_z += _z;
	}

	if (can_see_this_group())
	{
		translate_content(_x, _y, _z, true);
	}
	else
	{
		region_gabarite->have_phantom_translation = true;

		region_gabarite->phantom_translate_x += _x;
		region_gabarite->phantom_translate_y += _y;
		region_gabarite->phantom_translate_z += _z;
	}


	
}

void EButtonGroup::translate_content(float _x, float _y, float _z, bool _move_slider)
{
		if ((background_sprite_layer != nullptr) && (_move_slider))
		{
			background_sprite_layer->translate_sprite_layer(_x, _y, _z, false);
		}

		for (EntityButton* button : button_list)
		if ((_move_slider) || (button != slider))
		{button->translate_entity(_x, _y, _z, true);}

		for (EButtonGroup* group : group_list)
		{group->translate(_x, _y, _z, false);}
}

bool EButtonGroup::can_see_this_group()
{
	if (EInputCore::key_pressed(GLFW_KEY_TAB))
	{
		return true;
	}

	if
	(
		(*is_active)
		&&
		(region_gabarite->world_position_x <= NS_EGraphicCore::SCREEN_WIDTH)
		&&
		(region_gabarite->world_position_x + region_gabarite->size_x > 0.0f)

		&&

		(region_gabarite->world_position_y <= NS_EGraphicCore::SCREEN_HEIGHT)
		&&
		(region_gabarite->world_position_y + region_gabarite->size_y > 0.0f)
	)
	{return true;}
	else
	{return false;}
}

void EButtonGroup::phantom_translate_if_need()
{
	if (region_gabarite->have_phantom_translation)
	{
		translate_content
		(
			region_gabarite->phantom_translate_x,
			region_gabarite->phantom_translate_y,
			region_gabarite->phantom_translate_z,
			true
		);

		region_gabarite->have_phantom_translation = false;

		region_gabarite->phantom_translate_x = 0.0f;
		region_gabarite->phantom_translate_y = 0.0f;
		region_gabarite->phantom_translate_z = 0.0f;


	}
}

void EButtonGroup::get_last_focused_group(EButtonGroup* _group)
{
	if
	(
		(*_group->can_be_focused)
		&&
		(EButtonGroup::catched_by_mouse(_group))
	)
	{
		focused_button_group = _group;

		if
		(
			(_group->slider != NULL)
			&&
			(!_group->slider->disable_draw)
			&&
			(EInputCore::MOUSE_SPEED_X * EInputCore::MOUSE_SPEED_X + EInputCore::MOUSE_SPEED_Y * EInputCore::MOUSE_SPEED_Y > 0)
		)
		{focused_button_group_with_slider = _group;}
	}

	if (_group->header_button_group != nullptr)
	{get_last_focused_group(_group->header_button_group);}

	for (EButtonGroup* group : _group->group_list)
	{get_last_focused_group(group);}


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

	//*just_created_button_group->can_be_focused = false;

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_button_group_without_bg(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* just_created_button_group = EButtonGroup::create_base_button_group
	(
		_region,
		_style,
		bgroup_without_bg,
		bgroup_with_slider,
		bgroup_default_bg
	);

	*just_created_button_group->can_be_focused = true;

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg)
{
	
	EButtonGroup* just_created_button_group = new EButtonGroup(_region);
	just_created_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	*just_created_button_group->base_width	= _region->size_x;
	*just_created_button_group->base_height	= _region->size_y;

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
		just_created_button_group->background_sprite_layer->make_as_PBR();

		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);
	}
	else
	{
		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);

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


std::vector<EGUIStyle*> EGUIStyle::style_list;
//EButtonGroupRow* EButtonGroupRow::create_default_row(ERegionGabarite* _region, EGUIStyle* _style)
//{
//	return nullptr;
//}

//EButtonGroupRow::EButtonGroupRow(ERegionGabarite* _region)
//{
//	ERegionGabarite::set_region_gabarite(&gabarite, _region);
//}

//EButtonGroupRow::EButtonGroupRow()
//{
//}

//EButtonGroup* EButtonGroupRow::add_group(EButtonGroup* _group)
//{
//	/*EButtonGroup* jc_group = EButtonGroup::create_default_button_group
//	(
//		new ERegionGabarite()
//	)*/
//
//	//correct region size
//
//	if ((_group != nullptr) && (*_group->region_gabarite->size_y > *gabarite->size_y))
//	{
//		*gabarite->size_y = *_group->region_gabarite->size_y;
//	}
//
//	_group->root_group = root_group;
//	group_list.push_back(_group);
//	_group->parent_group_row = this;
//
//	return _group;
//}

//EButtonGroup* EButtonGroupRow::get_last_group(EButtonGroupRow* _row)
//{
//	if((_row != nullptr) && (!_row->group_list.empty()))
//	{
//		return _row->group_list[_row->group_list.size() - 1];
//	}
//	else
//	{return nullptr;}
//}

//void EButtonGroupRow::stretch_parent_group(EButtonGroupRow* _row, float _new_y_size)
//{
//	EButtonGroup* p_group = _row->parent_button_group;
//
//	if (*p_group->gabarite_size_mode_y == GroupStretchMode::EXACT_STRETCH)
//	{
//		*p_group->region_gabarite->size_y = _new_y_size;
//		EButtonGroup::generate_brick_textured_bg(p_group);
//	}
//
//	//*_group->parent_group_row
//	if 
//	(
//		(p_group != nullptr)
//		&&
//		(p_group->parent_group_row != nullptr)
//		&&
//		(*p_group->region_gabarite->offset_y + *p_group->region_gabarite->size_y > *p_group->parent_group_row->gabarite->size_y)
//	)
//	{
//		EButtonGroup::stretch_parent_group
//		(
//			p_group,
//			*p_group->region_gabarite->offset_y + *p_group->region_gabarite->size_y
//		);
//	}
//}

void EBrickStyle::set_border_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up)
{
	*_brick->side_size_left			= _left;
	*_brick->side_size_right		= _right;
	*_brick->side_size_bottom		= _bottom;
	*_brick->side_size_up			= _up;
}

void EBrickStyle::set_offset_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up)
{
	*_brick->side_offset_left = _left;
	*_brick->side_offset_right = _right;
	*_brick->side_offset_bottom = _bottom;
	*_brick->side_offset_up = _up;
}

void EBrickStyle::set_subdivisions(EBrickStyle* _brick, int _x, int _y)
{
	*_brick->subdivision_x = _x;
	*_brick->subdivision_y = _y;
}

EBrickStyle::EBrickStyle()
{
}

EBrickStyle::EBrickStyle(std::string _file_name)
{
	*file_name = _file_name;
}

EBrickStyle::~EBrickStyle()
{
}

void EBrickStyle::apply_brick_parameters_to_button_group(EButtonGroup* _group, EBrickStyle* _brick)
{
	_group->border_left		= _brick->side_offset_left;
	_group->border_right	= _brick->side_offset_right;
	_group->border_bottom	= _brick->side_offset_bottom;
	_group->border_up		= _brick->side_offset_up;
}

EGUIStyle::EGUIStyle()
{
}

EGUIStyle::EGUIStyle(std::string _folder)
{
	*folder = _folder;
}

EGUIStyle::~EGUIStyle()
{
}

void EGUIStyle::set_color_multiplier(float _r, float _g, float _b, float _a)
{
	text_color_multiplier[0] = _r;
	text_color_multiplier[1] = _g;
	text_color_multiplier[2] = _b;
	text_color_multiplier[3] = _a;
}

//void EGUIStyle::set_color_array(unsigned int _id, float _r, float _g, float _b, float _a)
//{
	/*text_color_array[_id][0] = _r;
	text_color_array[_id][0] = _g;
	text_color_array[_id][1] = _b;
	text_color_array[_id][2] = _a;*/
//}
