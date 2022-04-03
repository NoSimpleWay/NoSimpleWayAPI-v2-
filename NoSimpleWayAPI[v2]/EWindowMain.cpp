#pragma once
#ifndef _E_MAIN_WINDOW_ALREADY_LINKED_
#define _E_MAIN_WINDOW_ALREADY_LINKED_
#include "EWindowMain.h"
#endif



//class Entity;
EWindowMain* EWindowMain::link_to_main_window;

void EWindowMain::draw_additional(float _d)
{
	

	NS_EGraphicCore::default_batcher_for_drawing->set_transform_position(0.0f, 0.0f);
	NS_EGraphicCore::default_batcher_for_drawing->set_transform_screen_size(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	NS_EGraphicCore::default_batcher_for_drawing->set_transform_zoom(1.0f);

	for (int j = 0; j < CLUSTER_DIM_X; j++)
	for (int i = 0; i < CLUSTER_DIM_Y; i++)
	{
		if (!cluster_array[j][i]->entity_list.empty())
		for (Entity* e : cluster_array[j][i]->entity_list)
		{
			e->draw();
		}

	}

	NS_EGraphicCore::default_batcher_for_drawing->draw_call();
	
	
	//if (EInputCore::key_pressed_once(GLFW_KEY_W))	{ EInputCore::logger_simple_success("WwWwW"); }
	//if (EInputCore::key_holded(GLFW_KEY_W))			{ EInputCore::logger_simple_success("holded WwWwW"); }
}

void EWindowMain::update_additional(float _d)
{
	for (int j = 0; j < CLUSTER_DIM_X; j++)
	for (int i = 0; i < CLUSTER_DIM_Y; i++)
	{
		
		for (Entity* el : cluster_array[j][i]->entity_list)
		{
			el->update(_d);
		}
	}

}

EWindowMain::EWindowMain()
{
	//gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);

	for (int j = 0; j < CLUSTER_DIM_X; j++)
	for (int i = 0; i < CLUSTER_DIM_Y; i++)
	{
		cluster_array[j][i] = new ECluster();
	}

	//jc = Just Created
	Entity*				jc_entity = new Entity();
	ESpriteLayer*		jc_sprite_layer = new ESpriteLayer();
	ESpriteLayer*		jc_sprite_layer_for_text = new ESpriteLayer();
	ESprite*			jc_sprite = new ESprite();
	ECustomData*		jc_custom_data = new ECustomData();
	ERegionGabarite*	jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 500.0f, 200.0f);
	EClickableRegion*	jc_clickable_region = new EClickableRegion();
	ETextArea*			jc_text_area = new ETextArea();
	EButtonGroup*		jc_button_group;
	EButtonGroup*		main_button_group;
	EButtonGroupRow*	jc_button_group_row;
	EntityButton*		jc_button;
	ESpriteFrame*		jc_sprite_frame = new ESpriteFrame();
	


	jc_custom_data->actions_on_update.push_back(&EDataActionCollection::action_player_control);

	*jc_text_area->stored_text = "ABC\\nLOL\\nKEK";
	jc_text_area->font = EFont::font_list.at(0);

	jc_text_area->region_gabarite = jc_region_gabarite;
	jc_text_area->sprite_layer = jc_sprite_layer_for_text;
	jc_text_area->master_clickable_region = jc_clickable_region;
	jc_sprite_layer_for_text->batcher = NS_EGraphicCore::default_batcher_for_drawing;

	
	

	//push back objects
	jc_entity->sprite_layer_list.push_back(jc_sprite_layer);
	jc_entity->custom_data_list.push_back(jc_custom_data);
	*jc_entity->offset_x = 30.0f;
	*jc_entity->offset_y = 40.0f;
	*jc_entity->world_position_x = 30.0f;
	*jc_entity->world_position_y = 40.0f;
	//cluster_array[0][0]->entity_list.push_back(jc_entity);

	//jc_sprite_frame->sprite_list.push_back(jc_sprite);

	//jc_sprite_layer->sprite_frame_list.push_back(jc_sprite_frame);
	jc_sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;

	jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
	jc_custom_data->parent_entity = jc_entity;

	jc_clickable_region->region = jc_region_gabarite;
	jc_clickable_region->parent_entity = jc_entity;
	jc_clickable_region->parent_custom_data = jc_custom_data;

	jc_clickable_region->can_catch_side[0] = true;
	jc_clickable_region->can_catch_side[1] = true;
	jc_clickable_region->can_catch_side[2] = true;
	jc_clickable_region->can_catch_side[3] = true;
	jc_clickable_region->can_catch_side[4] = true;

	jc_clickable_region->text_area = jc_text_area;
	jc_clickable_region->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
	//*jc_clickable_region->editable_borders = true;

	//create sprite
	//jc_sprite->set_texture_gabarite(NS_DefaultGabarites::texture_gabarite_gudron);
	//jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
	//jc_sprite->master_sprite_layer = jc_sprite_layer;

	/*NS_ERenderCollection::border_up_size = 7.0f;
	NS_ERenderCollection::border_down_size = 7.0f;

	NS_ERenderCollection::border_left_size = 7.0f;
	NS_ERenderCollection::border_right_size = 7.0f;

	NS_ERenderCollection::subdivision_x = 2.0f;
	NS_ERenderCollection::subdivision_y = 2.0f;
	
	NS_ERenderCollection::generate_brick_texture(jc_region_gabarite, jc_sprite_layer, NS_DefaultGabarites::texture_gabarite_gudron);*/
	//

	//attach batcher to sprite layer
	
	//
	
	//jc_clickable_region->init_internal_sprite_layer();
	jc_entity->set_world_position(*jc_entity->offset_x, *jc_entity->offset_y, *jc_entity->offset_z);

	jc_text_area->generate_rows();
	jc_text_area->generate_text();

	jc_entity->generate_vertex_buffer_for_all_sprite_layers();
	
	std::string random_texture_list[5] =
	{
		"Chaos_Orb_inventory_icon",
		"Orb_of_Horizons_inventory_icon",
		"Orb_of_Regret_inventory_icon",
		"Orb_of_Scouring_inventory_icon",
		"Orb_of_Transmutation_inventory_icon"
	};

	std::string random_item_property[5] =
	{
		"Item level",
		"Map tier",
		"Links",
		"Sockets",
		"Require level"
	};

	////////////////////////////////////////////////
	//main button group
	main_button_group = EButtonGroup::create_root_button_group
	(
		new ERegionGabarite(0.0f, 0.0f, 0.0f, 1920.0f, 1000.0f),
		EGUIStyle::active_style
	);
		main_button_group->root_group = main_button_group;
		*main_button_group->button_group_type	= ButtonGroupType::BGT_DARKEN;
		
	button_group_list.push_back(main_button_group);

		


		for (int z = 0; z < 10; z++)
		{
			jc_button_group_row = EButtonGroup::add_default_row(main_button_group, new ERegionGabarite(0.0f, 0.0f, 1200.0f, 160.0f));
			*jc_button_group_row->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;

			//*jc_button_group_row->

			//new group
			jc_button_group = EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(230.0f, 160.0f),
				EGUIStyle::active_style
			);

			jc_button_group_row->add_group(jc_button_group);

			//"ZZZ" buttons
			for (int i = 0; i < 10; i++)
			for (int j = 0; j < 3; j++)
			{
				jc_button = new EntityButton();
				jc_button->action_on_change_style_list.push_back(&action_change_style_button);

				jc_custom_data = new ECustomData();
				EDataContainerMessage* jc_data_container_message = new EDataContainerMessage();
				*jc_data_container_message->message = "ItemLevel";
				jc_button->parent_button_group = jc_button_group;
				//jc_custom_data->action

				jc_custom_data->data_container = jc_data_container_message;
				jc_button->custom_data_list.push_back(jc_custom_data);
				*jc_button->offset_x = 10.0f;
				*jc_button->offset_y = 10.0f;

				*jc_button->fixed_position = false;

				if (j == 0) { jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 100.0f, 20.0f); } else
				if (j == 1) { jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 20.0f, 20.0f); } else
				if (j == 2) { jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 50.0f, 20.0f); }

				//jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 70.0f, 20.0f);
				jc_button->button_gabarite = jc_region_gabarite;
				EntityButton::button_generate_brick_bg(jc_button, jc_button_group->selected_style);

				jc_clickable_region = EClickableRegion::create_default_clickable_region(jc_region_gabarite, jc_button, jc_custom_data);
				jc_clickable_region->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
				jc_clickable_region->actions_on_click_list.push_back(&EDataActionCollection::action_log_text);

				jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
				jc_custom_data->parent_entity = jc_button;

				jc_button_group->button_list.push_back(jc_button);

				

				/*jc_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::put_texture_to_atlas("data/textures/button_bg.png", NS_EGraphicCore::default_texture_atlas));
				_button->jc_button->sprite_layer_list.push_back(jc_sprite_layer);
				NS_ERenderCollection::set_brick_borders_and_subdivisions(2.0f, 2.0f, 2.0f, 2.0f, 0, 0);
				NS_ERenderCollection::generate_brick_texture
				(
					jc_region_gabarite,
					jc_sprite_layer,
					jc_button_group->selected_style->backround_for_buttons
				);*/

				


				jc_text_area = new ETextArea();
				jc_clickable_region->text_area = jc_text_area;

				if (j == 0) { *jc_text_area->stored_text = random_item_property[rand() % 5]; } else
				if (j == 1) { *jc_text_area->stored_text = "="; } else
				if (j == 2) { *jc_text_area->stored_text = std::to_string(rand() % 100); }

				*jc_text_area->offset_by_gabarite_size_y = 0.5f;
				*jc_text_area->offset_by_text_size_y = -0.5f;

				jc_text_area->font = EFont::font_list.at(0);

				jc_sprite_layer_for_text = new ESpriteLayer();
				jc_text_area->region_gabarite = jc_region_gabarite;
				jc_text_area->sprite_layer = jc_sprite_layer_for_text;
				jc_text_area->master_clickable_region = jc_clickable_region;
				jc_sprite_layer_for_text->batcher = NS_EGraphicCore::default_batcher_for_drawing;

				jc_button->set_world_position(*jc_button->offset_x, *jc_button->offset_y, *jc_button->offset_z);

				jc_text_area->generate_rows();
				jc_text_area->generate_text();

				//jc_button->sprite_layer_list.push_back(jc_sprite_layer);

				jc_button->generate_vertex_buffer_for_all_sprite_layers();
			}

			//items group
			for (int k = 0; k < 1; k++)
			{
				//sub button group [level 1]


				jc_button_group = EButtonGroup::create_default_button_group
				(new ERegionGabarite(0.0f, 0.0f, 0.0f, 1000.0f, 160.0f), EGUIStyle::active_style);
				
				jc_button_group_row->button_group_list.push_back(jc_button_group);
				jc_button_group->parent_group_row = jc_button_group_row;

				//button item
				int button_count = rand() % 10 + 1;
				button_count *= rand() % 10 + 1;

				for (int i = 0; i < button_count; i++)

				{
					jc_button = new EntityButton();
					jc_button->action_on_change_style_list.push_back(&action_change_style_button);
					jc_button->parent_button_group = jc_button_group;
					jc_custom_data = new ECustomData();
					EDataContainerMessage* jc_data_container_message = new EDataContainerMessage();
					*jc_data_container_message->message = "123";
					//jc_custom_data->action

					jc_custom_data->data_container = jc_data_container_message;
					jc_button->custom_data_list.push_back(jc_custom_data);
					*jc_button->offset_x = 0.0f;
					*jc_button->offset_y = 0.0f;

					*jc_button->fixed_position = false;


					jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 44.0f, 44.0f);
					jc_button->button_gabarite = jc_region_gabarite;
					jc_clickable_region = new EClickableRegion();

					jc_clickable_region->region = jc_region_gabarite;
					jc_clickable_region->parent_entity = jc_button;
					jc_clickable_region->parent_custom_data = jc_custom_data;
					jc_clickable_region->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
					jc_clickable_region->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;

					jc_clickable_region->actions_on_click_list.push_back(&EDataActionCollection::action_log_text);

					jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
					jc_custom_data->parent_entity = jc_button;

					jc_button_group->button_list.push_back(jc_button);



					jc_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::put_texture_to_atlas("data/textures/" + random_texture_list[rand() % 5] + ".png", NS_EGraphicCore::default_texture_atlas));
					jc_button->sprite_layer_list.push_back(jc_sprite_layer);

					NS_ERenderCollection::set_brick_borders_and_subdivisions(2.0f, 2.0f, 2.0f, 2.0f, 0, 0);
					ERegionGabarite::temporary_gabarite->set_region_offset_and_size
					(
						0.0f,
						0.0f,
						0.0f,
						44.0f,
						44.0f
					);


					if (jc_button_group->selected_style != nullptr)
					NS_ERenderCollection::generate_brick_texture
					(
						ERegionGabarite::temporary_gabarite,
						jc_sprite_layer,
						jc_button_group->selected_style->button_bg->main_texture
					);

					jc_sprite_layer = ESpriteLayer::create_default_sprite_layer
					(
						NS_EGraphicCore::put_texture_to_atlas
						("data/textures/" + random_texture_list[rand() % 5] + ".png", NS_EGraphicCore::default_texture_atlas)
					);
					ESpriteLayer::set_size_for_last_sprite(jc_sprite_layer, 40.0f, 40.0f);
					ESpriteLayer::set_offset_for_last_sprite(jc_sprite_layer, 2.0f, 2.0f, 0.0f);

					jc_button->sprite_layer_list.push_back(jc_sprite_layer);

					//jc_button->set_world_position(*jc_button->offset_x, *jc_button->offset_y, *jc_button->offset_z);
					//jc_button->generate_vertex_buffer_for_all_sprite_layers();
				}
			}
		}
	

	EButtonGroup::refresh_button_group(main_button_group);
	//main_button_group->realign_all_buttons();
	//main_button_group->align_groups();
	//EButtonGroup::calculate_culling_lines(main_button_group);
	

	//STYLE LIST BUTTON GROUP
	main_button_group = EButtonGroup::create_root_button_group
	(new ERegionGabarite(800.0f, 100.0f, 0.0f, 400.0f, 600.0f), EGUIStyle::active_style);
	main_button_group->root_group = main_button_group;
	*main_button_group->button_group_type = ButtonGroupType::BGT_DARKEN;

	//*main_button_group->can_change_style = false;

	for (EGUIStyle* style : EGUIStyle::style_list)
	{
		//main row
		jc_button_group_row = EButtonGroup::add_default_row (main_button_group, new ERegionGabarite(0.0f, 0.0f, 350.0f, 10.0f));
		*jc_button_group_row->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;

		//group with constant style
		jc_button_group = jc_button_group_row->add_group
		(EButtonGroup::create_default_button_group (new ERegionGabarite(350.0f, 10.0f + *style->button_group_main->side_offset_up), style));
		*jc_button_group->can_change_style = false;
		*jc_button_group->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;

		//subrow big
		jc_button_group_row = EButtonGroup::add_default_row (jc_button_group, new ERegionGabarite(0.0f, 0.0f, 330.0f, 130.0f));

		//group big
		EButtonGroup* big_subgroup = jc_button_group_row->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(0.0f, 0.0f, 0.0f, 330.0f, 130.0f),style));

			if (big_subgroup != nullptr)
			{
				*big_subgroup->can_change_style = false;

				for (int i = 0; i < 20; i++)
				{
					jc_button = new EntityButton();
					jc_button->action_on_change_style_list.push_back(&action_change_style_button);
					big_subgroup->button_list.push_back(jc_button);
					jc_region_gabarite = new ERegionGabarite(40.0f, 40.0f);
					jc_button->button_gabarite = jc_region_gabarite;
					jc_button->parent_button_group = big_subgroup;

					jc_button->sprite_layer_list.push_back
					(
						ESpriteLayer::create_default_sprite_layer
						(NS_EGraphicCore::put_texture_to_atlas("data/textures/button_bg_bright.png", NS_EGraphicCore::default_texture_atlas))
					);

					EntityButton::button_generate_brick_bg(jc_button, style);

					jc_button->set_world_position(*jc_button->offset_x, *jc_button->offset_y, *jc_button->offset_z);
					jc_button->generate_vertex_buffer_for_all_sprite_layers();
				}

			}

		//subrow small (for button "select")
		jc_button_group_row = EButtonGroup::add_default_row
		(jc_button_group, new ERegionGabarite
		(330.0f, 20.0f + *style->button_group_main->side_offset_bottom + *style->button_group_main->side_offset_up + 8.0f));

		

		//group (for button "select")
		jc_button_group_row->add_group
		(
			EButtonGroup::create_default_button_group
			(new ERegionGabarite(330.0f, 20.0f + *style->button_group_main->side_offset_bottom + *style->button_group_main->side_offset_up + 8.0f), style)
		);

		jc_button_group = EButtonGroupRow::get_last_group(jc_button_group_row);
		

		if (jc_button_group != nullptr)
		{
			*jc_button_group->can_change_style = false;
			jc_button = new EntityButton();
			jc_button->action_on_change_style_list.push_back(&action_change_style_button);
			jc_button_group->button_list.push_back(jc_button);
			jc_button->parent_button_group = jc_button_group;

			jc_button->sprite_layer_list.push_back
			(
				ESpriteLayer::create_default_sprite_layer
				(NS_EGraphicCore::put_texture_to_atlas("data/textures/button_bg_bright.png", NS_EGraphicCore::default_texture_atlas))
			);
			jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 310.0f, 20.0f);
			jc_button->button_gabarite = jc_region_gabarite;

			ESprite::set_size
			(
				Entity::get_last_sprite(jc_button),
				300.0f,
				20.0f,
				0.0f
			);

			EntityButton::button_generate_brick_bg(jc_button, style);

			jc_button->set_world_position(*jc_button->offset_x, *jc_button->offset_y, *jc_button->offset_z);
			jc_button->generate_vertex_buffer_for_all_sprite_layers();
			
			

			jc_custom_data = new ECustomData();
			jc_button->custom_data_list.push_back(jc_custom_data);

			jc_clickable_region = EClickableRegion::create_default_clickable_region (jc_region_gabarite, jc_button, jc_custom_data);
			jc_clickable_region->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_style);

			jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
			jc_custom_data->parent_entity = jc_button;
			jc_custom_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);

			jc_text_area = new ETextArea(jc_clickable_region, EFont::font_list[0], "Select this style");

			*jc_text_area->offset_by_gabarite_size_x = 0.5f;
			*jc_text_area->offset_by_gabarite_size_y = 0.5f;

			*jc_text_area->offset_by_text_size_x = -0.5f;
			*jc_text_area->offset_by_text_size_y = -0.5f;

			*jc_text_area->can_be_edited = false;

			jc_text_area->generate_rows();
			jc_text_area->generate_text();

			jc_clickable_region->text_area = jc_text_area;

			
		}
		else
		{
			EInputCore::logger_simple_error("jc_button group is NULL!");
		}





		
	}

	//*******HEADER*******
	EButtonGroup* button_group_header = EButtonGroup::create_header_button_group
	(new ERegionGabarite(0.0f, 0.0f, 0.0f, 400.0f, 40.0f), EGUIStyle::active_style);
	button_group_header->parent_group = main_button_group;
	//*button_group_header->is_active = false;
	//*main_button_group->is_active = false;
	/**/main_button_group->header_button_group = button_group_header;
	/**/*button_group_header->culling_lines_method = CullingLinesCalcMethod::CLCM_BY_HIMSELF;
	/**/button_group_header->root_group = main_button_group;
	/**/
	/**/jc_button_group_row = EButtonGroup::add_default_row (button_group_header, new ERegionGabarite(400.0f, 10.0f));
	///**/*button_group_header->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;
			jc_button_group_row->add_group(EButtonGroup::create_invisible_button_group(new ERegionGabarite(355.0f, 28.0f), EGUIStyle::active_style));

			EButtonGroup* close_group = jc_button_group_row->add_group
			(EButtonGroup::create_invisible_button_group (new ERegionGabarite(28.0f, 28.0f),EGUIStyle::active_style));
			//EButtonGroup* close_group = jc_button_group_row->add_group
			//close_group->parent_group = button_group_header;
					jc_button = new EntityButton();
					jc_button->action_on_change_style_list.push_back(&action_change_style_button);
					close_group->button_list.push_back(jc_button);
					jc_button->parent_button_group = close_group;

					jc_button->sprite_layer_list.push_back (ESpriteLayer::create_default_sprite_layer (NS_EGraphicCore::default_texture_load("button_close")));

					jc_region_gabarite = new ERegionGabarite(20.0f, 20.0f);
					jc_button->button_gabarite = jc_region_gabarite;

					//EntityButton::button_generate_brick_bg(jc_button, EGUIStyle::active_style);

					//ECustomData* close_custom_data

						jc_custom_data = new ECustomData();
						jc_button->custom_data_list.push_back(jc_custom_data);

						jc_clickable_region = EClickableRegion::create_default_clickable_region(jc_region_gabarite, jc_button, jc_custom_data);
						jc_clickable_region->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
						//jc_clickable_region->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_style);
						jc_clickable_region->actions_on_click_list.push_back(&EDataActionCollection::action_close_root_group);

						jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
						jc_custom_data->parent_entity = jc_button;
						jc_custom_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);

					jc_button->set_world_position(*jc_button->offset_x, *jc_button->offset_y, *jc_button->offset_z);
					jc_button->generate_vertex_buffer_for_all_sprite_layers();

	

	button_group_list.push_back(main_button_group);

	EButtonGroup::refresh_button_group(main_button_group);


	

	

	




}

EWindowMain::~EWindowMain()
{

}
