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
			e->draw(_d);
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
	Entity*			jc_entity = new Entity();
	ESpriteLayer*		jc_sprite_layer = new ESpriteLayer();
	ESpriteLayer*		jc_sprite_layer_for_text = new ESpriteLayer();
	ESprite*			jc_sprite = new ESprite();
	ECustomData*		jc_custom_data = new ECustomData();
	ERegionGabarite*	jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 100.0f, 200.0f);
	EClickableRegion*	jc_clickable_region = new EClickableRegion();
	ETextArea*		jc_text_area = new ETextArea();

	jc_custom_data->data_actions_list.push_back(&EDataActionCollection::action_player_control);

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
	

	jc_sprite_layer->sprite_list.push_back(jc_sprite);
	jc_sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;

	jc_custom_data->clickable_region_list.push_back(jc_clickable_region);
	jc_custom_data->master_entity = jc_entity;

	jc_clickable_region->region = jc_region_gabarite;
	jc_clickable_region->master_entity = jc_entity;
	jc_clickable_region->master_custom_data = jc_custom_data;

	jc_clickable_region->text_area = jc_text_area;
	

	//create sprite
	jc_sprite->main_texture = NS_DefaultGabarites::texture_gabarite_gudron;

	*jc_sprite->size_x = *NS_DefaultGabarites::texture_gabarite_gudron->size_x_in_pixels;
	*jc_sprite->size_y = *NS_DefaultGabarites::texture_gabarite_gudron->size_y_in_pixels;
	jc_sprite->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_rectangle_real_size;
	jc_sprite->master_sprite_layer = jc_sprite_layer;
	//

	//attach batcher to sprite layer
	
	//
	
	jc_clickable_region->init_internal_sprite_layer();
	jc_entity->calculate_all_world_positions();

	jc_text_area->generate_rows();
	jc_text_area->generate_text();

	jc_entity->sprite_layer_generate_vertex_buffer();
	

	

	

	cluster_array[0][0]->entity_list.push_back(jc_entity);
}

EWindowMain::~EWindowMain()
{

}
