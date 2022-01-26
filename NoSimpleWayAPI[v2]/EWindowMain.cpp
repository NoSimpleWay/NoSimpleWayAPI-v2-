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
	ERegionGabarite*	jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 100.0f, 200.0f);
	EClickableRegion*	jc_clickable_region = new EClickableRegion();
	ETextArea*			jc_text_area = new ETextArea();
	EButtonGroup*		jc_button_group = new EButtonGroup();
	EButtonGroupRow*	jc_button_group_row = new EButtonGroupRow();
	EntityButton*		jc_button = new EntityButton();
	


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
	cluster_array[0][0]->entity_list.push_back(jc_entity);

	jc_sprite_layer->sprite_list.push_back(jc_sprite);
	jc_sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;

	jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
	jc_custom_data->parent_entity = jc_entity;

	jc_clickable_region->region = jc_region_gabarite;
	jc_clickable_region->parent_entity = jc_entity;
	jc_clickable_region->parent_custom_data = jc_custom_data;

	jc_clickable_region->text_area = jc_text_area;
	jc_clickable_region->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
	//*jc_clickable_region->editable_borders = true;

	//create sprite
	jc_sprite->set_texture_gabarite(NS_DefaultGabarites::texture_gabarite_gudron);
	///jc_sprite->main_texture = NS_DefaultGabarites::texture_gabarite_gudron;
	//jc_sprite->sprite_calculate_uv();

	*jc_sprite->size_x = *NS_DefaultGabarites::texture_gabarite_gudron->size_x_in_pixels;
	*jc_sprite->size_y = *NS_DefaultGabarites::texture_gabarite_gudron->size_y_in_pixels;
	jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_sprite;
	jc_sprite->master_sprite_layer = jc_sprite_layer;
	//

	//attach batcher to sprite layer
	
	//
	
	//jc_clickable_region->init_internal_sprite_layer();
	jc_entity->calculate_all_world_positions();

	jc_text_area->generate_rows();
	jc_text_area->generate_text();

	jc_entity->sprite_layer_generate_vertex_buffer();
	
	////////////////////////////////////////////////
	jc_region_gabarite = new ERegionGabarite(100.0f, 100.0f, 500.0f, 100.0f);
	jc_button_group->region = jc_region_gabarite;
	jc_button_group->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;
	button_group_list.push_back(jc_button_group);

	EButtonGroup::add_horizontal_scroll_bar(jc_button_group);
	//button section
	for (int i = 0; i < 50; i++)
	{
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

		jc_button = new EntityButton();
	}

	jc_button_group->realign_all_buttons();
	jc_button_group->calculate_all_world_positions();
	
	
	
	
	
	

	//push back button


	

	

	




}

EWindowMain::~EWindowMain()
{

}
