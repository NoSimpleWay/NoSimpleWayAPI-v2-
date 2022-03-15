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
	cluster_array[0][0]->entity_list.push_back(jc_entity);

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
	main_button_group = new EButtonGroup(0.0f, 0.0f, 0.0f, 1920.0f, 1000.0f);
		main_button_group->background_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_DefaultGabarites::texture_gabarite_gudron);
		
		EButtonGroup::set_borders(main_button_group, 7.0f, 7.0f, 7.0f, 7.0f);

		button_group_list.push_back(main_button_group);
		main_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
		//jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 1200.0f, 1000.0f);
		//main_button_group->region = jc_region_gabarite;
		EButtonGroup::add_horizontal_scroll_bar(main_button_group);
		
			NS_ERenderCollection::set_borders_and_subdivisions(7.0f, 7.0f, 7.0f, 7.0f, 2, 2);
			NS_ERenderCollection::generate_brick_texture(main_button_group->region, main_button_group->background_sprite_layer, NS_DefaultGabarites::texture_lead_and_gold);
			main_button_group->background_sprite_layer->sprite_layer_set_world_position(0.0f, 0.0f, 0.0f);
			main_button_group->background_sprite_layer->generate_vertex_buffer_for_sprite_layer("init bg");

		for (int z = 0; z < 10; z++)
		{
			//new row
			jc_button_group_row = new EButtonGroupRow();
			jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 1200.0f, 150.0f); jc_button_group_row->gabarite = jc_region_gabarite;
			jc_button_group_row->parent_button_group = main_button_group;
			main_button_group->group_row_list.push_back(jc_button_group_row);

			//new group
			jc_button_group = new EButtonGroup(0.0f, 0.0f, 0.0f, 230.0f, 150.0f); jc_button_group_row->button_group_list.push_back(jc_button_group);
				EButtonGroup::set_borders(jc_button_group, 7.0f, 7.0f, 7.0f, 7.0f);
				//*jc_button_group->border_left = 7.0f;
				//*jc_button_group->border_bottom = 7.0f;
				//*jc_button_group->border_up = 7.0f;

			jc_button_group->parent_group_row = jc_button_group_row;
			jc_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
			//jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 100.0f, 150.0f); jc_button_group->region = jc_region_gabarite;
				jc_button_group->background_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_DefaultGabarites::texture_gabarite_gudron);
				
				NS_ERenderCollection::set_borders_and_subdivisions(7.0f, 7.0f, 7.0f, 7.0f, 2, 2);
				NS_ERenderCollection::generate_brick_texture(jc_button_group->region, jc_button_group->background_sprite_layer, NS_DefaultGabarites::texture_lead_and_gold);
				jc_button_group->background_sprite_layer->sprite_layer_set_world_position(0.0f, 0.0f, 0.0f);
				jc_button_group->background_sprite_layer->generate_vertex_buffer_for_sprite_layer("init bg");
			EButtonGroup::add_horizontal_scroll_bar(jc_button_group);

			//EInputCore::logger_param("row count", main_button_group->group_row_list.size());



			//"ZZZ" buttons
			for (int i = 0; i < 10; i++)
			for (int j = 0; j < 3; j++)
			{
				jc_button = new EntityButton();
				jc_custom_data = new ECustomData();
				EDataContainerMessage* jc_data_container_message = new EDataContainerMessage();
				 *jc_data_container_message->message = "ItemLevel";
				
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

				jc_clickable_region = EClickableRegion::create_default_clickable_region(jc_region_gabarite, jc_button, jc_custom_data);
				jc_clickable_region->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
				jc_clickable_region->actions_on_click_list.push_back(&EDataActionCollection::action_log_text);

				jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
				jc_custom_data->parent_entity = jc_button;

				jc_button_group->button_list.push_back(jc_button);

				jc_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::put_texture_to_atlas("data/textures/button_bg.png", NS_EGraphicCore::default_texture_atlas));
				ESpriteLayer::set_size_for_last_sprite(jc_sprite_layer, *jc_region_gabarite->size_x, 20.0f);

				jc_button->sprite_layer_list.push_back(jc_sprite_layer);


				jc_text_area = new ETextArea();
				jc_clickable_region->text_area = jc_text_area;

				if (j == 0) { *jc_text_area->stored_text = random_item_property[rand() % 5]; } else
				if (j == 1) { *jc_text_area->stored_text = "="; } else
				if (j == 2) { *jc_text_area->stored_text = std::to_string(rand() % 100); }

				*jc_text_area->offset_by_gabarite_size_y = 0.0f;
				*jc_text_area->offset_by_text_size_y = -0.0f;

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


				jc_button_group = new EButtonGroup(0.0f, 0.0f, 0.0f, 600.0f, 150.0f); jc_button_group_row->button_group_list.push_back(jc_button_group);
				EButtonGroup::set_borders(jc_button_group, 7.0f, 7.0f, 7.0f, 7.0f);
				//*jc_button_group->border_bottom = 7.0f;
				//*jc_button_group->border_up = 7.0f;
				//jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 600.0f, 150.0f); jc_button_group->region = jc_region_gabarite;
				jc_button_group->parent_group_row = jc_button_group_row;

				jc_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
					jc_button_group->background_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_DefaultGabarites::texture_gabarite_gudron);
					
					NS_ERenderCollection::set_borders_and_subdivisions(7.0f, 7.0f, 7.0f, 7.0f, 2, 2);
					NS_ERenderCollection::generate_brick_texture(jc_button_group->region, jc_button_group->background_sprite_layer, NS_DefaultGabarites::texture_lead_and_gold);
					jc_button_group->background_sprite_layer->sprite_layer_set_world_position
					(
						0.0f,
						0.0f,
						0.0f
					);
					jc_button_group->background_sprite_layer->generate_vertex_buffer_for_sprite_layer("init bg");

				EButtonGroup::add_horizontal_scroll_bar(jc_button_group);
				//button item
				for (int i = 0; i < 120; i++)
				{
					jc_button = new EntityButton();
					jc_custom_data = new ECustomData();
					EDataContainerMessage* jc_data_container_message = new EDataContainerMessage();
					*jc_data_container_message->message = "123";
					//jc_custom_data->action

					jc_custom_data->data_container = jc_data_container_message;
					jc_button->custom_data_list.push_back(jc_custom_data);
					*jc_button->offset_x = 10.0f;
					*jc_button->offset_y = 10.0f;

					*jc_button->fixed_position = false;


					jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 40.0f, 40.0f);
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

					jc_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::put_texture_to_atlas("data/textures/button_bg.png", NS_EGraphicCore::default_texture_atlas));
					jc_button->sprite_layer_list.push_back(jc_sprite_layer);

					jc_sprite_layer = ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::put_texture_to_atlas("data/textures/" + random_texture_list[rand() % 5] + ".png", NS_EGraphicCore::default_texture_atlas));
					*jc_sprite_layer->sprite_frame_list[0]->sprite_list[0]->size_x = 40.0f;
					*jc_sprite_layer->sprite_frame_list[0]->sprite_list[0]->size_y = 40.0f;
					jc_sprite_layer->sprite_frame_list[0]->sprite_list[0]->sprite_calculate_uv();

					jc_button->sprite_layer_list.push_back(jc_sprite_layer);

					jc_button->set_world_position(*jc_button->offset_x, *jc_button->offset_y, *jc_button->offset_z);
					jc_button->generate_vertex_buffer_for_all_sprite_layers();
				}
			}
		}
	

	button_group_list[0]->realign_all_buttons();
	button_group_list[0]->set_world_position_and_redraw();
	
	
	
	
	
	

	//push back button


	

	

	




}

EWindowMain::~EWindowMain()
{

}
