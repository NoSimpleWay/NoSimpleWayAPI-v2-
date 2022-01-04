#pragma once
#ifndef _E_MAIN_WINDOW_ALREADY_LINKED_
#define _E_MAIN_WINDOW_ALREADY_LINKED_
#include "EWindowMain.h"
#endif

EWindowMain* EWindowMain::link_to_main_window;

void EWindowMain::draw_additional(float _d)
{

	NS_EGraphicCore::default_batcher_for_drawing->set_transform_position(0.0f, 0.0f);
	NS_EGraphicCore::default_batcher_for_drawing->set_transform_screen_size(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT);
	NS_EGraphicCore::default_batcher_for_drawing->set_transform_zoom(1.0f);

	for (int j = 0; j < CLUSTER_DIM_X; j++)
	for (int i = 0; i < CLUSTER_DIM_Y; i++)
	{
		for (Entity* e : cluster_array[j][i]->entity_list)
		{
			e->draw(_d);
		}

	}

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			NS_ERenderCollection::fill_vertex_buffer_textured_rectangle_real_size
			(
				NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
				NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

				j * 160.0f + 5.0f,
				i * 105.0f + 5.0f,

				gudron
			);

			ERenderBatcher::is_batcher_have_free_space(NS_EGraphicCore::default_batcher_for_drawing);
		}

	NS_EGraphicCore::default_batcher_for_drawing->draw_call();
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
	gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);

	for (int j = 0; j < CLUSTER_DIM_X; j++)
	for (int i = 0; i < CLUSTER_DIM_Y; i++)
	{
		cluster_array[j][i] = new ECluster();
	}
}

EWindowMain::~EWindowMain()
{

}
