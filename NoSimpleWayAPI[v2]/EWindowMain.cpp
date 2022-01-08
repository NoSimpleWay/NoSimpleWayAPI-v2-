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

	Entity* jc_entity = new Entity();
	ESpriteLayer* jc_sprite_layer = new ESpriteLayer();
	ESprite* jc_sprite = new ESprite();

	jc_sprite->main_texture = NS_DefaultGabarites::texture_gabarite_gudron;

	*jc_sprite->size_x = *NS_DefaultGabarites::texture_gabarite_gudron->size_x_in_pixels;
	*jc_sprite->size_y = *NS_DefaultGabarites::texture_gabarite_gudron->size_y_in_pixels;
	jc_sprite->master_sprite_layer = jc_sprite_layer;

	jc_sprite_layer->batcher = NS_EGraphicCore::default_batcher_for_drawing;
	jc_sprite_layer->batcher->pointer_to_sprite_render = &NS_ERenderCollection::call_render_textured_rectangle_real_size;
	

	jc_sprite_layer->sprite_list.push_back(jc_sprite);
	jc_entity->sprite_layer_list.push_back(jc_sprite_layer);
	jc_entity->sprite_layer_generate_vertex_buffer();

	cluster_array[0][0]->entity_list.push_back(jc_entity);
}

EWindowMain::~EWindowMain()
{

}
