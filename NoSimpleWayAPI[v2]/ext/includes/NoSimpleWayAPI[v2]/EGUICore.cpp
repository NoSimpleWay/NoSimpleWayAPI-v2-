#pragma once
#ifndef _E_GUI_CORE_ALREADY_LINKED_
#define _E_GUI_CORE_ALREADY_LINKED_
#include "EGUICore.h"
#endif

std::vector<EWindow*> EWindow::window_list;

EButtonGroup* EButtonGroup::focused_button_group = nullptr;
EButtonGroup* EButtonGroup::catched_group_for_translation = nullptr;

//EButtonGroup* EButtonGroup::focused_button_group;
EButtonGroup* EButtonGroup::focused_button_group_with_slider = nullptr;

EButtonGroup* EButtonGroup::data_entity_filter					= nullptr;
EButtonGroup* EButtonGroup::color_editor_group					= nullptr;
EButtonGroup* EButtonGroup::add_content_to_filter_block_group	= nullptr;
EButtonGroup* EButtonGroup::header_line							= nullptr;

std::vector<FreshCreatedGroup*> EButtonGroup::fresh_created_block_list;

constexpr float BUTTON_GROUP_Y_DISTANCE = 2.0f;



void EWindow::update_default(float _d)
{
	
}

void EWindow::update_additional(float _d)
{
}

void EWindow::GUI_update_default(float _d)
{

	for (int i = 0; i < button_group_list.size(); i++)
	if ((button_group_list[i] != nullptr) && (button_group_list[i]->need_remove))
	{
		delete button_group_list[i];
		EInputCore::logger_simple_success("Need remove [" + std::to_string(i) + "] element of button group list");

		button_group_list.erase(button_group_list.begin() + i);
	}

	for (EButtonGroup* b_group : button_group_list)
	if
	(
		(b_group != nullptr)
		&&
		(b_group->is_active)
		&&
		(b_group->region_gabarite->world_position_y <= b_group->higher_culling_line_for_bg)
		&&
		(b_group->region_gabarite->world_position_y + b_group->region_gabarite->size_y >= b_group->lower_culling_line_for_bg)
	)
	{
		EButtonGroup::get_last_focused_group(b_group);
	}

	if ((EButtonGroup::focused_button_group != nullptr))
	{
		for (EntityButton* but : EButtonGroup::focused_button_group->button_list)
		for (ECustomData* data:but->custom_data_list)
		for (EClickableArea* c_area:data->clickable_area_list)
		if
		(
			(!EInputCore::MOUSE_BUTTON_LEFT)
			&&
			(*c_area->catched_body)
			&&
			(
				(c_area->parent_entity == nullptr)
				||
				(
					(c_area->parent_entity != nullptr)
					&&
					(!c_area->parent_entity->disable_draw)
					&&
					(!c_area->parent_entity->disabled)
				)
			)
		)
		{
			EClickableArea::active_clickable_region = c_area;
		}
	}

	for (EButtonGroup* b_group : button_group_list)
	if
	(
		(b_group != nullptr)
		&&
		(b_group->is_active)
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


	for (EButtonGroup* b_group : button_group_list)
	if
	(
		(b_group != nullptr)
		&&
		(b_group->is_active)
		&&
		(b_group->can_see_this_group())

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
	for (EButtonGroup* b_group : button_group_list)
	if ((b_group != nullptr) && (b_group->is_active) && (counter <= 10))
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
	EInputCore::logger_simple_success("Destructor [for button group] called");

	if ((region_gabarite != nullptr))
	{
		region_gabarite->pointers_to_this_object--;

		if (region_gabarite->pointers_to_this_object <= 0) { delete region_gabarite; }
	}

	for (int i = 0; i < button_list.size(); i++)
	{delete button_list[i];}
	button_list.clear();
	button_list.shrink_to_fit();

	for (int i = 0; i < group_list.size(); i++)
	{
		delete group_list[i];
	};
	group_list.clear();
	group_list.shrink_to_fit();

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

	for (int i = 0; i < group_list.size(); i++)
	if ((group_list[i] != nullptr) && (group_list[i]->need_remove))
	{
		delete group_list[i];
		EInputCore::logger_simple_success("Need remove [" + std::to_string(i) + "] child element of button group list");

		group_list.erase(group_list.begin() + i);

		i--;

		if (parent_group != nullptr)
		{
			change_group(parent_group);
		}
	}

	if (can_see_this_group())
	{

		//need remove button
		if (!button_list.empty())
		for (unsigned int i = 0; i < button_list.size(); i++)
		if (button_list[i]->need_remove)
		{
			EntityButton* but = button_list[i];
			button_list.erase(button_list.begin() + i);
			delete but;
			i--;

			//change_group(this);

			//refresh_buttons_in_group();
		}

		{
			for (EntityButton* but : button_list)
			{

				//can see this button
				if
					(
						(but->update_when_scissored)
						||
						(
							(but->button_gabarite->world_position_y + but->button_gabarite->phantom_translate_y <= higher_culling_line + 0.0f)
							&&
							(but->button_gabarite->world_position_y + but->button_gabarite->phantom_translate_y + but->button_gabarite->size_y >= lower_culling_line - 0.0f)
						)
					)
				{
					//phantom translation
					if (but->button_gabarite->have_phantom_translation)
					{
						but->button_gabarite->have_phantom_translation = false;

						but->translate_entity
						(
							but->button_gabarite->phantom_translate_x,
							but->button_gabarite->phantom_translate_y,
							but->button_gabarite->phantom_translate_z,
							true
						);

						but->button_gabarite->phantom_translate_x = 0.0f;
						but->button_gabarite->phantom_translate_y = 0.0f;
						but->button_gabarite->phantom_translate_z = 0.0f;
					}

					but->update(_d);
				}
			}
		}

		//final button groun, not subgroup
		//if (group_row_list.empty())


	
		phantom_translate_if_need();
		calculate_culling_lines(this);

		for (group_update_action gua : actions_on_update)
		{
			gua(this);
		}

		for (EButtonGroup* _group : group_list)
		{
			_group->update(_d);
		}
	}

	//move group by mouse
	if
	(
		(EInputCore::MOUSE_BUTTON_LEFT)
		&&
		(root_group != nullptr)
		&&
		(root_group->can_be_moved)
		&&
		(
			(EButtonGroup::focused_button_group == this)
			//||
			//(EButtonGroup::focused_button_group == root_group)
		)
		&&
		(EClickableArea::active_clickable_region == nullptr)
		&&
		(
			(EButtonGroup::catched_group_for_translation == root_group)
			||
			(EButtonGroup::catched_group_for_translation == nullptr)
		)
	)
	{
		if (EButtonGroup::catched_group_for_translation == nullptr)
		{
			EButtonGroup::catched_group_for_translation = root_group;
			root_group->move_to_foreground();
		}

		
		root_group->translate(EInputCore::MOUSE_SPEED_X / NS_EGraphicCore::current_zoom, EInputCore::MOUSE_SPEED_Y / NS_EGraphicCore::current_zoom, 0.0f, true);
	}
	else
	{
		if (debug_translation)
		{
			if (root_group == nullptr) { EInputCore::logger_simple_error("root group is null!"); }
			else
			if (!root_group->can_be_moved) { EInputCore::logger_simple_error("group cannot be moved!"); }
			else
			if (EButtonGroup::focused_button_group != this) { EInputCore::logger_simple_error("this group not focused"); }
			else
			if
			(EClickableArea::active_clickable_region != nullptr)
			{
				EInputCore::logger_simple_error("focused some clickable region");

				EInputCore::logger_param("x", EClickableArea::active_clickable_region->region_gabarite->world_position_x);
				EInputCore::logger_param("y", EClickableArea::active_clickable_region->region_gabarite->world_position_y);
			}
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
		if (phantom_redraw)
		{
			EButtonGroup::generate_vertex_buffer_for_group(this);
			phantom_redraw = false;
		}

		//batcher_for_default_draw->draw_call();

		glDisable(GL_SCISSOR_TEST);
		//glDisable(GL_SCISSOR_TEST);
		//		SHADOW		//
		/* */if ((root_group == this) && (false))
			/* */ {
			/* */	NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLACK, 0.335f * 2.0f);
			/* */	if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			/* */	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			/* */(
				/* */		batcher_for_default_draw->vertex_buffer,
				/* */		batcher_for_default_draw->last_vertice_buffer_index,
				/* */		region_gabarite->world_position_x - 6.0f,
				/* */		region_gabarite->world_position_y - 6.0f,
				/* */		region_gabarite->size_x + 12.0f,
				/* */		region_gabarite->size_y + 12.0f,
				/* */		NS_DefaultGabarites::texture_gabarite_white_pixel
			/* */);
			/* */
		}
		//batcher_for_default_draw->draw_call();

		glEnable(GL_SCISSOR_TEST);

		glScissor
		(
			region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
			lower_culling_line_for_bg * NS_EGraphicCore::current_zoom,

			region_gabarite->size_x * NS_EGraphicCore::current_zoom,
			max(0.0f, higher_culling_line_for_bg - lower_culling_line_for_bg) * NS_EGraphicCore::current_zoom
		);

		//BG
		if ((background_sprite_layer != nullptr) && (have_bg))
		{background_sprite_layer->transfer_vertex_buffer_to_batcher();}


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

		//NS_EGraphicCore::test_batcher->draw_call();


		//ELEMENTS
		if (parent_group == nullptr)
		{
			glScissor
			(
				region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
				region_gabarite->world_position_y * NS_EGraphicCore::current_zoom,
				region_gabarite->size_x * NS_EGraphicCore::current_zoom,
				region_gabarite->size_y * NS_EGraphicCore::current_zoom
			);
		}
		else
		{
			//if (root_group != nullptr)
			{
				glScissor
				(
					region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
					lower_culling_line * NS_EGraphicCore::current_zoom,

					region_gabarite->size_x* NS_EGraphicCore::current_zoom,
					max(0.0f, higher_culling_line - lower_culling_line) * NS_EGraphicCore::current_zoom
				);
			}
		}


		for (EntityButton* but : button_list)
			if
				(
					(but->world_position_y + but->button_gabarite->phantom_translate_y + but->button_gabarite->size_y >= lower_culling_line)
					&&
					(but->world_position_y + but->button_gabarite->phantom_translate_y <= higher_culling_line)
				)
			{
				but->draw();

				if (selected_button == but)
				{
					NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_YELLOW, 1.0f);
					ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);

					NS_ERenderCollection::add_data_to_vertex_buffer_rama
					(
						NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
						NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

						but->button_gabarite->world_position_x - 3.0f,
						but->button_gabarite->world_position_y - 3.0f,

						but->button_gabarite->size_x + 6.0f,
						but->button_gabarite->size_y + 6.0f,

						5.0f,

						NS_DefaultGabarites::texture_gabarite_white_pixel

					);
				}
			}



		NS_EGraphicCore::pbr_batcher->draw_call();//draw pbg bg
		batcher_for_default_draw->draw_call();//draw text to default batcher



		//recursive draw


		for (EButtonGroup* group : group_list) { group->draw(); }



		//draw call to prepare for header
		//NS_EGraphicCore::test_batcher->draw_call();
		NS_EGraphicCore::pbr_batcher->draw_call();




		glDisable(GL_SCISSOR_TEST);

		if (EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL))
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_GREEN);
			//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
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

		if ((EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT)) && (false))
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_CYAN);
			//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
			NS_ERenderCollection::add_data_to_vertex_buffer_rama
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,
				region_gabarite->world_position_x + 0.0f,
				lower_culling_line,
				region_gabarite->size_x - 0.0f,
				1.0f,
				1.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);

			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_YELLOW);
			//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
			ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
			NS_ERenderCollection::add_data_to_vertex_buffer_rama
			(
				batcher_for_default_draw->vertex_buffer,
				batcher_for_default_draw->last_vertice_buffer_index,
				region_gabarite->world_position_x + 0.0f,
				higher_culling_line,
				region_gabarite->size_x - 0.0f,
				1.0f,
				1.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}

		if (EInputCore::key_pressed(GLFW_KEY_LEFT_ALT))
		{
			for (EButtonGroup* group : group_list)
			if
			(
				(EButtonGroup::focused_button_group == group)
				||
				(EInputCore::key_pressed(GLFW_KEY_LEFT_CONTROL))
			)
			{
				NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_RED);
				//if (batcher_for_default_draw->last_vertice_buffer_index + batcher_for_default_draw->gl_vertex_attribute_total_count * 4 * 4 >= TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE) { batcher_for_default_draw->draw_call(); }
				ERenderBatcher::if_have_space_for_data(batcher_for_default_draw, 4);
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

				//EInputCore::logger_param("size y", group->region_gabarite->size_y);
				//batcher_for_default_draw->draw_call();
			}
		}

		
		

		NS_EGraphicCore::pbr_batcher->draw_call();
		batcher_for_default_draw->draw_call();
		//NS_EGraphicCore::test_batcher->draw_call();

			glEnable(GL_SCISSOR_TEST);
			glScissor
			(
				region_gabarite->world_position_x * NS_EGraphicCore::current_zoom,
				region_gabarite->world_position_y * NS_EGraphicCore::current_zoom,
				region_gabarite->size_x * NS_EGraphicCore::current_zoom,
				region_gabarite->size_y * NS_EGraphicCore::current_zoom
			);
			for (group_draw_action gda : actions_on_draw)
			{gda(this);}

		NS_EGraphicCore::pbr_batcher->draw_call();
		batcher_for_default_draw->draw_call();
		//NS_EGraphicCore::test_batcher->draw_call();
		glDisable(GL_SCISSOR_TEST);



		//draw_second_pass();
	}
}

void EButtonGroup::draw_second_pass()
{
	

	for (EntityButton* but : button_list)
	if
	(
		(but->world_position_y + but->button_gabarite->phantom_translate_y + but->button_gabarite->size_y >= lower_culling_line)
		&&
		(but->world_position_y + but->button_gabarite->phantom_translate_y <= higher_culling_line)
	)
	{
		but->draw_second_pass();
	}

	for (EButtonGroup* group : group_list) { group->draw_second_pass(); }
}

void EButtonGroup::align_groups()
{
	highest_point_y = 0.0f;
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
		region_gabarite->world_position_y = root_group->region_gabarite->offset_y + root_group->region_gabarite->size_y - region_gabarite->size_y * 0.0f - root_group->border_up;
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
			{group->region_gabarite->offset_y = border_bottom + 0.0f;}

			if (prev_group != nullptr)
			{
				if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
				{
					group->region_gabarite->offset_x = border_left + 0.0f;
					group->region_gabarite->offset_y = prev_group->region_gabarite->offset_y + prev_group->region_gabarite->size_y + BUTTON_GROUP_Y_DISTANCE;
				}
				else
				if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
				{
					group->region_gabarite->offset_x = prev_group->region_gabarite->offset_x + prev_group->region_gabarite->size_x + 0.0f;
					group->region_gabarite->offset_y = prev_group->region_gabarite->offset_y;
				}
			}
			else
			{
				//if (*group->have_bg)
				//{group->region_gabarite->offset_x = *border_left + 3.0f;}
				//else
				group->region_gabarite->offset_x = border_left;
				group->region_gabarite->offset_y = border_bottom;
			}

			
			

			group->region_gabarite->world_position_x = region_gabarite->world_position_x + group->region_gabarite->offset_x;
			group->region_gabarite->world_position_y = region_gabarite->world_position_y + group->region_gabarite->offset_y + scroll_y;
			group->region_gabarite->world_position_z = region_gabarite->world_position_z + group->region_gabarite->offset_z;

			
			


			
	
			prev_group = group;

			group->align_groups();
			
		}

		
	

	if (prev_group != nullptr)
	{
		highest_point_y
		=
		max
		(
			prev_group->region_gabarite->offset_y
			+
			prev_group->region_gabarite->size_y
			-
			0.0f
			,
			highest_point_y
		);
	}

	


	for (EButtonGroup* group : group_list) { group->align_groups(); }


	
	

}

void EButtonGroup::calculate_culling_lines(EButtonGroup* _group)
{
	if (_group->parent_group == nullptr)
	{


		_group->higher_culling_line			= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		_group->lower_culling_line			= _group->region_gabarite->world_position_y;

		_group->higher_culling_line_for_bg	= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		_group->lower_culling_line_for_bg	= _group->region_gabarite->world_position_y;

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


		_group->higher_culling_line			= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		_group->lower_culling_line			= _group->region_gabarite->world_position_y;

		_group->higher_culling_line_for_bg	= _group->region_gabarite->world_position_y + _group->region_gabarite->size_y;
		_group->lower_culling_line_for_bg	= _group->region_gabarite->world_position_y;
	}

	

	//for (EButtonGroupRow*	row:	_group->group_row_list)
	for (EButtonGroup*		group: _group->group_list)
	{
		group->higher_culling_line_for_bg = min
		(
			group->region_gabarite->world_position_y + group->region_gabarite->size_y,
			_group->region_gabarite->world_position_y + _group->region_gabarite->size_y - _group->border_up
		);

		group->higher_culling_line_for_bg = min
		(
			group->higher_culling_line_for_bg,
			_group->higher_culling_line_for_bg
		);



		group->lower_culling_line_for_bg = max
		(
			group->region_gabarite->world_position_y,
			_group->region_gabarite->world_position_y + _group->border_bottom
		);

		group->lower_culling_line_for_bg = max
		(
			group->lower_culling_line_for_bg,
			_group->lower_culling_line_for_bg
		);



		group->higher_culling_line = min
		(
			group->region_gabarite->world_position_y + group->region_gabarite->size_y - group->border_up,
			_group->region_gabarite->world_position_y + _group->region_gabarite->size_y - _group->border_up
		);

		group->higher_culling_line = min
		(
			group->higher_culling_line,
			_group->higher_culling_line
		);


		group->lower_culling_line = max(group->region_gabarite->world_position_y + group->border_bottom, _group->region_gabarite->world_position_y + _group->border_bottom);
		group->lower_culling_line = max(group->lower_culling_line, _group->lower_culling_line);

		//EButtonGroup::calculate_culling_lines(group);
	}

	for (EButtonGroup* group : _group->group_list) { EButtonGroup::calculate_culling_lines(group); }
}

void EButtonGroup::generate_vertex_buffer_for_group(EButtonGroup* _group)
{

	if (_group->can_see_this_group())
	{
		EButtonGroup::generate_brick_textured_bg(_group);
		_group->need_redraw = false;

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


		
		for (EntityButton* but : _group->button_list)
		{
			for (change_style_action csa : but->action_on_change_style_list)
			{
				csa(but, _group->selected_style);

				//_group->slider->generate_vertex_buffer_for_all_sprite_layers();
			}
			but->set_world_position(but->world_position_x, but->world_position_y, but->world_position_z);
			but->generate_vertex_buffer_for_all_sprite_layers();
		}

		for (EButtonGroup* group : _group->group_list) { EButtonGroup::generate_vertex_buffer_for_group(group); }
	}
	else
	{
		_group->phantom_redraw = true;
	}
}

void EButtonGroup::substretch_groups_y()
{
	//EInputCore::logger_simple_info("substretch");
	//stretch every child, if child size y more than parent size y, also stretch parent
	float total_y = border_bottom + border_up;
	float max_y = 0.0f;

	EButtonGroup* prev_group = nullptr;
	if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{
		total_y += ((float)(group_list.size()) - 1.0f) * BUTTON_GROUP_Y_DISTANCE;

		for (EButtonGroup* group : group_list)
		if (!group->stretch_y_by_parent_size)
		{
			total_y += group->region_gabarite->size_y;
		}
	}

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{
		for (EButtonGroup* group : group_list)
		if (!group->stretch_y_by_parent_size)
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
			(can_be_stretched_by_child)
			&&
			(child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
			&&
			(total_y > region_gabarite->size_y)
		)
		{
			EButtonGroup::stretch_parent_group(this, total_y);
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

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{


		target_size = region_gabarite->size_x - border_left - border_right - (group_list.size() - 1) * 1.0f - shrink_size;
		target_size -= slider_effect;

		for (EButtonGroup* group : group_list)
		{
			if (group->stretch_x_by_parent_size)
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

	if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{
		target_size = region_gabarite->size_x - border_left - border_right - shrink_size;
		target_size -= slider_effect;

		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0) { final_size = target_size / float(dynamic_elements_count); }



	//final_size = 100.0f;
	for (EButtonGroup* group : group_list)
	{
		if ((group->stretch_x_by_parent_size) && (group->region_gabarite->size_x != final_size))
		{
			group->region_gabarite->size_x = (final_size);
			group->need_redraw = true;
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
	if (!have_bg) { shrink_size = 0.0f; }

	if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
	{

		target_size = max(region_gabarite->size_y, min_size_y) - border_bottom - border_up - (group_list.size() - 1) * BUTTON_GROUP_Y_DISTANCE - shrink_size - 1.0;

		for (EButtonGroup* group : group_list)
		{
			group->region_gabarite->size_y = max(group->region_gabarite->size_y, group->min_size_y);

			if (group->stretch_y_by_parent_size)
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

	if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
	{

		target_size = region_gabarite->size_y - border_bottom - border_up - shrink_size - 0.0f;
		dynamic_elements_count = 1;
	}

	if (dynamic_elements_count > 0) { final_size = target_size / float(dynamic_elements_count); }

	//final_size = 100.0f;
	for (EButtonGroup* group : group_list)
	{
		if (group->stretch_y_by_parent_size)
		{
			group->region_gabarite->size_y = (max(final_size, group->min_size_y));
			//group->region_gabarite->size_y = round(max(final_size, 0.0f));
			//group->region_gabarite->size_y = round(final_size);
		}

		//group->region_gabarite->size_y = round(max(group->region_gabarite->size_y, min_size_y));

		group->need_redraw = true;
	}

	for (EButtonGroup* group : group_list) { group->group_stretch_y(); }
}

void EButtonGroup::check_slider()
{
	have_slider = true;//have no slider by default

	if (slider != nullptr)
	{
		slider->disable_draw	= true;
		slider->disabled		= true;
	}

	float child_elements_height_summ = 0.0f;
	float max_y = 0.0f;
	//stretchable group cannot have slider
	//if (*can_be_stretched_by_child)
	//{
	//	for (EButtonGroup* group : group_list)
	//	{*group->parent_have_slider = false;}//parent have no slider
	//}
	//else//potentially, can have slider
	{
		if (child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
		{
			child_elements_height_summ = ((float)group_list.size() - 1.0f) * BUTTON_GROUP_Y_DISTANCE;

			for (EButtonGroup* group : group_list)
			//if (!*group->stretch_y_by_parent_size)//constant size
			{
				child_elements_height_summ += group->region_gabarite->size_y;//*szOID_ROOT_PROGRAM_AUTO_UPDATE_CA_REVOCATION
			}
		}

		if (child_align_mode == ChildAlignMode::ALIGN_HORIZONTAL)
		{

			for (EButtonGroup* group : group_list)
			//if (!*group->stretch_y_by_parent_size)//constant size
			{
				max_y = max(max_y, group->region_gabarite->size_y);//*szOID_ROOT_PROGRAM_AUTO_UPDATE_CA_REVOCATION
			}

			child_elements_height_summ += max_y;
		}

		

		if (child_elements_height_summ - 1.0f > region_gabarite->size_y - border_bottom - border_up)
		{
			if (slider != nullptr)
			{
				slider->disable_draw	= false;
				slider->disabled		= false;
				have_slider				= true;
				//EInputCore::logger_param("summ", child_elements_height_summ);
				//EInputCore::logger_param("size y", *region_gabarite->size_y - 6.0f - *border_bottom - *border_up);
				//std::cout << std::endl;

				for (EButtonGroup* group : group_list)
				{
					//EInputCore::logger_param("group size y", *group->region_gabarite->size_y);
					group->parent_have_slider = true;
				}//parent have no slider
			}
		}
		else
		{
			if (slider != nullptr)
			{
				slider->disable_draw	= true;
				slider->disabled		= true;
				have_slider				= false;
				for (EButtonGroup* group : group_list)
				{group->parent_have_slider = false;}//parent have no slider
			}
		}
	}

	for (EButtonGroup* group : group_list) { group->check_slider(); }
}

void EButtonGroup::expand_to_workspace_size()
{
	if (can_resize_to_workspace_size_x)
	{
		region_gabarite->size_x = base_width + border_left + border_right;
		
	}

	if (can_resize_to_workspace_size_y)
	{
		region_gabarite->size_y = base_height + border_bottom + border_up;
	}

	for (EButtonGroup* group : group_list)
	{
		group->expand_to_workspace_size();
	}
}

void EButtonGroup::refresh_button_group(EButtonGroup* _group)
{
	


	_group->expand_to_workspace_size();


	_group->substretch_groups_y();
	//_group->check_slider();

	_group->group_stretch_y();
	_group->check_slider();
	_group->group_stretch_x();


	_group->align_groups();
	EButtonGroup::calculate_culling_lines(_group);

	_group->realign_all_buttons();

	EButtonGroup::generate_vertex_buffer_for_group(_group);
}

void EButtonGroup::change_group(EButtonGroup* _group)
{
	_group->substretch_groups_y();
	//_group->check_slider();

	_group->group_stretch_y();
	_group->check_slider();
	_group->group_stretch_x();


	_group->align_groups();
	EButtonGroup::calculate_culling_lines(_group);
	_group->realign_all_buttons();

	//prevert empty space
	//if (_group->scroll_y < -(_group->highest_point_y_for_buttons - _group->region_gabarite->size_y))
	//{
	//	_group->scroll_y = 0.0f;
	//	//_group->realign_all_buttons();
	//}

	EButtonGroup::generate_vertex_buffer_for_group(_group);
}

void EButtonGroup::refresh_buttons_in_group()
{
	

	//prevert empty space
	if (scroll_y < -(highest_point_y_for_buttons - region_gabarite->size_y))
	{
		scroll_y = -(highest_point_y_for_buttons - region_gabarite->size_y);
		realign_all_buttons();
	}

	

	EButtonGroup::generate_vertex_buffer_for_group(this);
}

void EButtonGroup::realign_all_buttons()
{
	highest_point_y_for_buttons = 0.0f;

	EntityButton* prev_button = nullptr;

	float slider_additional = 0.0f;

	std::vector<EntityButton*> button_vector;

	for (EntityButton* but : button_list)
	{
		but->button_gabarite->have_phantom_translation = false;
		but->button_gabarite->phantom_translate_x = 0.0f;
		but->button_gabarite->phantom_translate_y = 0.0f;
		but->button_gabarite->phantom_translate_z = 0.0f;

		for (ECustomData* cd : but->custom_data_list)
			for (EClickableArea* c_area : cd->clickable_area_list)
			{
				*c_area->catched_body = false;
				*c_area->catched_side_down = false;
				*c_area->catched_side_up = false;
				*c_area->catched_side_left = false;
				*c_area->catched_side_right = false;
				*c_area->catched_side_mid = false;
			}
	}

	for (EntityButton* but : button_list)
	if
	(
		(
			(!but->fixed_position)
			||
			(false)
		)
		&&
		(!but->disable_draw)
		&&
		(!but->disabled)
	)
	{
		
		bool new_lined = false;
		if (prev_button != nullptr)
		{
			if (!but->fixed_position)
			{
				button_vector.push_back(prev_button);
			}


			but->offset_x = prev_button->offset_x + prev_button->button_gabarite->offset_x + prev_button->button_gabarite->size_x + DISTANCE_BETWEEN_BUTTONS;
			but->offset_y = prev_button->offset_y;
			
			

			if ((slider != nullptr) && (!slider->disabled) && (!slider->disable_draw) && (have_slider)) { slider_additional = slider->button_gabarite->size_x + 1.0f; } else { slider_additional = 0.0f; }


			//new line
			if (but->offset_x + but->button_gabarite->size_x + slider_additional >= region_gabarite->size_x)
			{
				but->offset_x = but->parent_button_group->border_left;
				but->offset_y += prev_button->button_gabarite->size_y + DISTANCE_BETWEEN_BUTTONS;

				new_lined = true;
				
				
				
				//button_vector.clear();
			}
			else
			{
				//button_vector.push_back(but);
			}

			
		}
		else
		{
			but->offset_x = but->parent_button_group->border_left;
			but->offset_y = but->parent_button_group->border_bottom;

			//button_vector.push_back(but);
		}





		if ((new_lined))
		{
			
			if ((new_lined) && (but->custom_data_list[0]->clickable_area_list[0]->text_area != nullptr))
			{
				//EInputCore::logger_param("new lined", *but->custom_data_list[0]->clickable_area_list[0]->text_area->stored_text);
			}
			align_button_in_gabarite(button_vector, slider_additional);
			//EInputCore::logger_simple_info("invoke);

			new_lined = false;
		}

		if (!but->fixed_position)
		{
			highest_point_y_for_buttons = max(highest_point_y_for_buttons, but->offset_y + but->button_gabarite->size_y + 0.0f);
		}
		
		//scroll_y		= min(scroll_y, highest_point_y);



		prev_button = but;
	}
	else
	{
		//but->update(0.1f);
	}

	if (prev_button != nullptr)
	{
		if (!prev_button->fixed_position)
		{
			button_vector.push_back(prev_button);
			align_button_in_gabarite(button_vector, slider_additional);
		}
	}

	highest_point_y = max(highest_point_y, highest_point_y_for_buttons);

	//if (!button_vector.empty())
	//{
	//	align_button_in_gabarite(button_vector, slider_additional);
	//}



		//EInputCore::logger_param("highest point y", *highest_point_y);

	if (slider != nullptr)
	{
		slider->offset_x
			=
			region_gabarite->size_x
			-
			slider->button_gabarite->size_x
			-
			border_right;



		slider->world_position_x
			=
			slider->offset_x
			+
			region_gabarite->world_position_x;

		slider->offset_y = 0.0f;
		slider->world_position_y = region_gabarite->world_position_y;
	}

	if ((slider != nullptr) && (highest_point_y > region_gabarite->size_y - 0.0f - border_up))
	{
		slider->disable_draw	= false;
		slider->disabled		= false;

		if (!have_slider)
		{
			have_slider = true;
			this->realign_all_buttons();
		}

		

		for (EButtonGroup* group : group_list) { group->parent_have_slider = true; }
	}

	//float current_scroll = region_gabarite->size_y - scroll_y;

	for (EButtonGroup* group : group_list) { group->realign_all_buttons(); }
}

void EButtonGroup::align_button_in_gabarite(std::vector<EntityButton*>& button_vector, float slider_additional)
{
	float total_width = (button_vector.size() - 1) * DISTANCE_BETWEEN_BUTTONS + slider_additional;

	//EInputCore::logger_param("slider_additional", slider_additional);

	int id = 0;
	for (EntityButton* but_temp : button_vector)
	if (!but_temp->fixed_position)
	{
		total_width += but_temp->button_gabarite->size_x;

		//EInputCore::logger_param("button[" + std::to_string(id) + "]", but_temp->button_gabarite->size_x);
		id++;
	}

	float free_space = 0.0f;
	if (button_align_type == ButtonAlignType::BUTTON_ALIGN_MID) { free_space = (region_gabarite->size_x - total_width) / 2.0f; }
	if (button_align_type == ButtonAlignType::BUTTON_ALIGN_RIGHT) { free_space = (region_gabarite->size_x - total_width); }


	for (EntityButton* but_temp : button_vector)
	{
		if ((but_temp->fixed_position) && (true))
		{
			but_temp->world_position_x = but_temp->parent_button_group->region_gabarite->world_position_x + but_temp->offset_x;
			but_temp->world_position_y = but_temp->parent_button_group->region_gabarite->world_position_y + but_temp->offset_y;
		}
		else
		{
			but_temp->world_position_x = but_temp->parent_button_group->region_gabarite->world_position_x + but_temp->offset_x + but_temp->parent_button_group->scroll_x + free_space;
			but_temp->world_position_y = but_temp->parent_button_group->region_gabarite->world_position_y + but_temp->offset_y + but_temp->parent_button_group->scroll_y;


			//*but->world_position_x = *but->parent_button_group->region->world_position_x + *but->parent_button_group->scroll_y;
			//*but->world_position_y = *but->parent_button_group->region->world_position_y;
		}
	}

	button_vector.clear();
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
		sprite_layer->offset_y = _button_group->border_bottom;

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
				_button_group->region_gabarite->size_y - _button_group->border_bottom - _button_group->border_up
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
			_button_group->border_bottom,
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
	but->fixed_position = true;
	but->update_when_scissored = true;

	custom_data->data_container = data_container;
	custom_data->clickable_area_list.push_back(cl_region);
	custom_data->parent_entity = but;

	data_container->value_pointer = &_button_group->scroll_y;

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
	_group->border_left	= _left;
	_group->border_right	= _right;

	_group->border_bottom	= _bottom;
	_group->border_up		= _up;
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



	_group->need_redraw = true;
	_group->phantom_translate_if_need();

	if (*_group->can_change_style) {_group->selected_style = _style;}

	if ((EGUIStyle::active_style != nullptr) && (*_group->can_change_style))
	{

		if (_group->have_bg)
		{
			if ((*_group->button_group_type == ButtonGroupType::BGT_REGULAR) && (_style->button_group_main != nullptr))
			{ EBrickStyle::apply_brick_parameters_to_button_group(_group, _style->button_group_main); }

			if ((*_group->button_group_type == ButtonGroupType::BGT_DARKEN) && (_style->button_group_darken != nullptr))
			{ EBrickStyle::apply_brick_parameters_to_button_group(_group, _style->button_group_darken); }

			//EButtonGroup::generate_brick_textured_bg(_group);
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
				//csa(but, _style);

				//but->generate_vertex_buffer_for_all_sprite_layers();
			}
		}

		//_group->refresh_button_group(_group);
	}

	

	


}

void EButtonGroup::generate_brick_textured_bg(EButtonGroup* _group)
{
	if ((_group != nullptr) && (_group->selected_style != nullptr) && (_group->background_sprite_layer != nullptr))
	{
		if (_group->seed == 0) { _group->seed = rand() % 70000; }

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

			srand(_group->seed);
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

	//recursive down to child elements
	for (EButtonGroup* group:_group->group_list)
	if (group != nullptr)
	{EButtonGroup::change_style(group, _style);}

	//if (_group->parent_group == nullptr) { EButtonGroup::refresh_button_group(_group); }
}

bool EButtonGroup::catched_by_mouse(EButtonGroup* _group)
{
	if
	(
		(_group->higher_culling_line_for_bg * NS_EGraphicCore::current_zoom > _group->lower_culling_line_for_bg * NS_EGraphicCore::current_zoom)
		&&
		(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom >= _group->region_gabarite->world_position_x)
		&&
		(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom <= _group->region_gabarite->world_position_x + _group->region_gabarite->size_x)
		&&
		(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom >= _group->lower_culling_line_for_bg)
		&&
		(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom <= _group->higher_culling_line_for_bg)
	)
	{
		return true;
	}

	return false;
}

void EButtonGroup::stretch_parent_group(EButtonGroup* _group, float _new_y_size)
{
	_group->region_gabarite->size_y = _new_y_size;
	_group->need_redraw = true;

	EButtonGroup::generate_brick_textured_bg(_group);
	EButtonGroup* _parent = _group->parent_group;
	if
	(
		(_parent != nullptr)
		&&
		(_parent->can_be_stretched_by_child)
		&&
		(_parent->child_align_mode == ChildAlignMode::ALIGN_VERTICAL)
		&&
		(
			_parent->region_gabarite->offset_y
			+
			_parent->region_gabarite->size_y

			>

			_parent->region_gabarite->size_y - _parent->border_up
		)
	)
	{
		EButtonGroup::stretch_parent_group
		(
			_parent,
			_parent->region_gabarite->offset_y + _parent->region_gabarite->size_y + _parent->border_up
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

	region_gabarite->world_position_x += (_x);
	region_gabarite->world_position_y += (_y);
	region_gabarite->world_position_z += (_z);

	

	if (_move_positions)
	{
		region_gabarite->offset_x += (_x);
		region_gabarite->offset_y += (_y);
		region_gabarite->offset_z += (_z);
	}

	if (can_see_this_group())
	{
		translate_content((_x), (_y), (_z), true);
	}
	else
	{
		region_gabarite->have_phantom_translation = true;

		region_gabarite->phantom_translate_x += (_x);
		region_gabarite->phantom_translate_y += (_y);
		region_gabarite->phantom_translate_z += (_z);
	}

	higher_culling_line += _y;
	higher_culling_line_for_bg += _y;

	lower_culling_line += _y;
	lower_culling_line_for_bg += _y;
	
}

void EButtonGroup::translate_content(float _x, float _y, float _z, bool _move_slider)
{
		if ((background_sprite_layer != nullptr) && (_move_slider))
		{
			background_sprite_layer->translate_sprite_layer(_x, _y, _z, false);
		}

		for (EntityButton* button : button_list)
		if ((_move_slider) || (button != slider))
		{
			if
			(
				(
					(button->button_gabarite->world_position_y <= higher_culling_line)
					&&
					(button->button_gabarite->world_position_y + button->button_gabarite->size_y >= lower_culling_line)
					&&
					(!button->disabled)
					&&
					(!button->disable_draw)
				)
				//||
				//(button == slider)
			)
			{
				button->translate_entity(_x, _y, _z, true);
			}
			else
			{
				button->button_gabarite->have_phantom_translation = true;

				button->button_gabarite->phantom_translate_x += _x;
				button->button_gabarite->phantom_translate_y += _y;
				button->button_gabarite->phantom_translate_z += _z;
			}
		}

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
		(is_active)
		&&
		(region_gabarite->world_position_x <= NS_EGraphicCore::SCREEN_WIDTH / NS_EGraphicCore::current_zoom)
		&&
		(region_gabarite->world_position_x + region_gabarite->size_x > 0.0f)

		&&

		(region_gabarite->world_position_y <= NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)
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

void EButtonGroup::recursive_phantom_translate_if_need()
{
	phantom_translate_if_need();

	for (EButtonGroup* group : group_list)
	{
		group->recursive_phantom_translate_if_need();
	}
}

void EButtonGroup::select_this_button(EntityButton* _but)
{
	selected_button = _but;

	EInputCore::logger_simple_info("invoke all select action in group");
	for (group_select_action gsa : actions_on_select_button)
	{
		EInputCore::logger_simple_info("invoke select action");
		gsa(this);
	}
}

EButtonGroup* EButtonGroup::set_parameters(ChildAlignMode _child_align_mode, bool _autosize_x, bool _autosize_y)
{
	child_align_mode = _child_align_mode;

	stretch_x_by_parent_size = _autosize_x;
	stretch_y_by_parent_size = _autosize_y;

	return this;
}

void EButtonGroup::move_to_foreground()
{
	if ((can_change_position_in_vector) && (parent_window != nullptr))
	{
		//EButtonGroup* target_group = nullptr;

		int target_id	= -1;
		int last_id		= -1;

		for (int i = 0; i < parent_window->button_group_list.size(); i++)
		if (parent_window->button_group_list[i] == this)
		{
			target_id = i;
			 
			break;
		}

		for (int i = target_id + 1; i < parent_window->button_group_list.size() - 1; i++)
		if (parent_window->button_group_list[i]->can_change_position_in_vector)
		{
			last_id = i;
		}

		if ((target_id >= 0) && (last_id >= 0))
		{
			EButtonGroup* swap_group = this;

			for (int i = target_id; i < last_id; i++)
			{
				parent_window->button_group_list[i] = parent_window->button_group_list[i + 1];
			}

			parent_window->button_group_list[last_id] = swap_group;
		}

		//parent_window->button_group_list.
	}
}

void EButtonGroup::get_last_focused_group(EButtonGroup* _group)
{
	if
	(
		(_group->can_be_focused)
		&&
		(EButtonGroup::catched_by_mouse(_group))
		&&
		(!EInputCore::MOUSE_BUTTON_LEFT)
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

	just_created_button_group->root_group = just_created_button_group;

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

	just_created_button_group->can_be_focused = true;

	return just_created_button_group;
}

EButtonGroup* EButtonGroup::create_color_editor_group(ERegionGabarite* _region, EGUIStyle* _style)
{
	EButtonGroup* main_group = create_root_button_group(_region, _style);
	main_group->root_group = main_group;
	Helper::HSVRGBAColor* HRA_color = &Helper::registered_color_list[rand() % Helper::registered_color_list.size()]->target_color;


	main_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	main_group->actions_on_draw.push_back(&EDataActionCollection::action_draw_color_rectangle_for_group);
	main_group->actions_on_update.push_back(&EDataActionCollection::action_convert_HSV_to_RGB);

	
	EButtonGroup* workspace_group = main_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), _style);
	workspace_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

	EDataContainer_Group_ColorEditor* data = new EDataContainer_Group_ColorEditor();
	data->work_color = HRA_color;
		//
		//data->pointer_to_H		= new float(1.0f);
		//data->pointer_to_S		= new float(1.0f);
		//data->pointer_to_V		= new float(1.0f);
		//data->pointer_to_alpha	= new float(1.0f);

	main_group->data_container = data;

	//**********************************************************************************************************************************************
	//**********************************************************************************************************************************************
	EButtonGroup* left_part = workspace_group->add_group(create_default_button_group(new ERegionGabarite(265.0f, 285.0f), _style));
	left_part->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	left_part->stretch_x_by_parent_size = false;
	left_part->stretch_y_by_parent_size = true;


	//**********************************************************************************************************************************************
	EButtonGroup* value_and_alpha_part = left_part->add_group(create_default_button_group(new ERegionGabarite(265.0f, 100.0f), _style));
	value_and_alpha_part->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	value_and_alpha_part->stretch_x_by_parent_size = true;
	value_and_alpha_part->stretch_y_by_parent_size = true;

		// // // // // // //
		EntityButton* 
		jc_button = EntityButton::create_vertical_named_slider(new ERegionGabarite(240.0f, 40.0f), value_and_alpha_part, EFont::font_list[0], EGUIStyle::active_style, "Прозрачность");
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &HRA_color->a;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
		value_and_alpha_part->button_list.push_back(jc_button);

		data->slider_data_alpha_container = static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container);
		// // // // // // //

		// // // // // // //
		
		jc_button = EntityButton::create_vertical_named_slider(new ERegionGabarite(240.0f, 40.0f), value_and_alpha_part, EFont::font_list[0], EGUIStyle::active_style, "Яркость");
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &HRA_color->v;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
		value_and_alpha_part->button_list.push_back(jc_button);

		data->slider_data_value_container = static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container);
		// // // // // // //


	//**********************************************************************************************************************************************
	EButtonGroup* hue_part = left_part->add_group(create_default_button_group(new ERegionGabarite(265.0f, 260.0f), _style));
	hue_part->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	hue_part->stretch_x_by_parent_size = true;
	hue_part->stretch_y_by_parent_size = false;

	// // // // // // //
	jc_button = EntityButton::create_default_crosshair_slider
	(
		new ERegionGabarite(256.0f, 256.0f),
		hue_part,
		&HRA_color->h,
		&HRA_color->s,
		"hue_saturation"
	);

	EDataContainer_CrosshairSlider* crosshair_data = (EDataContainer_CrosshairSlider*)EntityButton::get_last_custom_data(jc_button)->data_container;
	crosshair_data->min_x = 0.0f;
	crosshair_data->max_x = 360.0f;

	crosshair_data->min_y = 0.0f;
	crosshair_data->max_y = 1.0f;

	data->crosshair_slider_data_container = crosshair_data;

	hue_part->button_list.push_back(jc_button);
	// // // // // // //


	//**********************************************************************************************************************************************
	//**********************************************************************************************************************************************
	EButtonGroup* color_box = workspace_group->add_group(create_default_button_group(new ERegionGabarite(35.0f, 10.0f), _style));
	//right_part->debug_translation = true;
	color_box->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	color_box->stretch_x_by_parent_size = false;
	color_box->stretch_y_by_parent_size = true;
	data->pointer_to_color_box_group = color_box;

	//**********************************************************************************************************************************************
	//**********************************************************************************************************************************************
	EButtonGroup* color_collection_frame = workspace_group->add_group(create_default_button_group(new ERegionGabarite(256.0f, 100.0f), _style));
	//right_part->debug_translation = true;
	color_collection_frame->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	color_collection_frame->stretch_x_by_parent_size = true;
	color_collection_frame->stretch_y_by_parent_size = true;
	
	
	EButtonGroup* control_button_segment = color_collection_frame->add_group(create_default_button_group(new ERegionGabarite(256.0f, 50.0f), _style));
	control_button_segment->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	control_button_segment->stretch_x_by_parent_size = true;
	control_button_segment->stretch_y_by_parent_size = false;
	
	//button "unbind color"
	jc_button = EntityButton::create_default_clickable_button(new ERegionGabarite(180.0f, 30.0f), control_button_segment, &EDataActionCollection::action_unbing_color);
	ETextArea* jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Отвязать от шаблона");
	*jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
	control_button_segment->button_list.push_back(jc_button);
	
	//button "register new color"
	jc_button = EntityButton::create_default_clickable_button(new ERegionGabarite(180.0f, 30.0f), control_button_segment, &EDataActionCollection::action_create_new_color);
	jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Создать шаблон цвета");
	*jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
	control_button_segment->button_list.push_back(jc_button);

	

	EButtonGroup* color_segment = color_collection_frame->add_group(create_default_button_group(new ERegionGabarite(256.0f, 40.0f), _style));
	color_segment->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	color_segment->stretch_x_by_parent_size = true;
	color_segment->stretch_y_by_parent_size = true;
	data->pointer_to_color_collection_group = color_segment;
	color_segment->actions_on_select_button.push_back(&EDataActionCollection::action_set_new_color_to_button);

	for (int i = 0; i < Helper::registered_color_list.size(); i++)
	{
		// // // // // // //// // // // // // //// // // // // // //
		Helper::HRA_color_collection*	HRA_collection	= Helper::registered_color_list[i];
		Helper::HSVRGBAColor*			HRA_color		= &HRA_collection->target_color;
		//HRA_color->h = rand() % 360;
		//HRA_color->s = 1.0f - pow((rand() % 100) / 100.0f, 1.0);
		//HRA_color->v = 1.0f - pow((rand() % 100) / 100.0f, 3.0);
		//HRA_color->a = 1.0f - pow((rand() % 100) / 100.0f, 4.0);

		
		//std::cout << Helper::registered_color_list[0] << std::endl;
		jc_button = EntityButton::create_named_color_button
		(
			//*color_collection->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

			new ERegionGabarite(120.0f, 38.0f),
			color_segment,
			EFont::font_list[0],
			EGUIStyle::active_style,
			HRA_collection->name,
			HRA_collection,
			HRA_color,
			ColorButtonMode::CBM_SELECT_COLOR
		);

		//std::cout << HRA_color << std::endl;
		//Entity::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_button);

		color_segment->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //
	}

	return main_group;
}

EButtonGroup* EButtonGroup::add_close_group_and_return_workspace_group(ERegionGabarite* _region, EGUIStyle* _style)
{

	child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

	EButtonGroup* workspace_group =
	EButtonGroup::create_button_group_without_bg
	(
		new ERegionGabarite(100.0f, 100.0f),
		_style
	);

	workspace_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	workspace_group->stretch_x_by_parent_size = true;
	workspace_group->stretch_y_by_parent_size = true;

	add_group(workspace_group);

	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
	EButtonGroup* close_group =
	EButtonGroup::create_default_button_group
	(
		new ERegionGabarite(30.0f, _region->size_y),
		_style
	);

	close_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
	close_group->stretch_x_by_parent_size = true;
	close_group->stretch_y_by_parent_size = false;

	add_group(close_group);
	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
	EButtonGroup* close_group_left =
		close_group->add_group
		(
			EButtonGroup::create_button_group_without_bg
			(
				new ERegionGabarite(30.0f, _region->size_y),
				_style
			)
		);

	close_group_left->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	close_group_left->stretch_x_by_parent_size = true;
	close_group_left->stretch_y_by_parent_size = true;

	
	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
	EButtonGroup* close_group_right =
	close_group->add_group
	(
		EButtonGroup::create_button_group_without_bg
		(
			new ERegionGabarite(20.0f, _region->size_y),
			_style
		)
	);

	close_group_right->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
	close_group_right->stretch_x_by_parent_size = false;
	close_group_right->stretch_y_by_parent_size = true;

		EntityButton* jc_button = EntityButton::create_default_clickable_button
		(
			new ERegionGabarite(20.0f, 20.0f),
			close_group_right,
			&EDataActionCollection::action_close_root_group
		);

		jc_button->sprite_layer_list.push_back
		(
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				NS_EGraphicCore::load_from_textures_folder("button_close"),

				0.0f,
				0.0f,
				0.0f,

				20.0f,
				20.0f,
				00.0f
			)
		);
		close_group_right->button_list.push_back(jc_button);

	

	return workspace_group;
}

EButtonGroup* EButtonGroup::create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg)
{
	
	EButtonGroup* just_created_button_group = new EButtonGroup(_region);
	just_created_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

	just_created_button_group->base_width	= _region->size_x;
	just_created_button_group->base_height	= _region->size_y;

	if (_default_bg)
	{
		*just_created_button_group->button_group_type = ButtonGroupType::BGT_REGULAR;
	}
	else
	{
		*just_created_button_group->button_group_type = ButtonGroupType::BGT_DARKEN;
	}

	just_created_button_group->have_bg = _have_bg;

	if (_have_bg)
	{ 
		just_created_button_group->background_sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
		just_created_button_group->background_sprite_layer->make_as_PBR();

		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);
	}
	else
	{
		EButtonGroup::apply_style_to_button_group(just_created_button_group, _style);

		just_created_button_group->border_bottom	= 0.0f;
		just_created_button_group->border_left		= 0.0f;
		just_created_button_group->border_right	= 0.0f;
		just_created_button_group->border_up		= 0.0f;
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
	_group->border_left		= *_brick->side_offset_left;
	_group->border_right	= *_brick->side_offset_right;
	_group->border_bottom	= *_brick->side_offset_bottom;
	_group->border_up		= *_brick->side_offset_up;
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
