#pragma once
#ifndef _E_MAIN_WINDOW_ALREADY_LINKED_
#define _E_MAIN_WINDOW_ALREADY_LINKED_
#include "EWindowMain.h"
#endif

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

/**/
#ifndef _E_DATA_ENTITY_ALREADY_LINKED_
#define _E_DATA_ENTITY_ALREADY_LINKED_
#include "NoSimpleWayAPI[v2]/EDataEntity.h"
#endif
/**/

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
	//for(int i = 0; i < 1'000'000; i++)
	//{
	//	test_vector.push_back(new TestObject());
	//}
	
	//gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);

	ETextParser::data_entity_parse_file("data/data_entity_list.txt");

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
	EClickableArea*		jc_clickable_area = new EClickableArea();
	ETextArea*			jc_text_area = new ETextArea();
	EButtonGroup*		jc_button_group;
	EButtonGroup*		main_button_group;
	EButtonGroupRow*	jc_button_group_row;
	EntityButton*		jc_button;
	ESpriteFrame*		jc_sprite_frame = new ESpriteFrame();
	


	jc_custom_data->actions_on_update.push_back(&EDataActionCollection::action_player_control);

	*jc_text_area->stored_text = "ABC\\nLOL\\nKEK";
	jc_text_area->font = EFont::font_list.at(0);

	ERegionGabarite::set_region_gabarite (&jc_text_area->region_gabarite, jc_region_gabarite);

	jc_text_area->sprite_layer = jc_sprite_layer_for_text;
	jc_text_area->master_clickable_region = jc_clickable_area;
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

	jc_custom_data->clickable_area_list.push_back(jc_clickable_area);
	jc_custom_data->parent_entity = jc_entity;
	ERegionGabarite::set_region_gabarite (&jc_clickable_area->region_gabarite, jc_region_gabarite);
	//jc_clickable_area->region_gabarite = jc_region_gabarite;

	jc_clickable_area->parent_entity = jc_entity;
	jc_clickable_area->parent_custom_data = jc_custom_data;

	jc_clickable_area->can_catch_side[0] = true;
	jc_clickable_area->can_catch_side[1] = true;
	jc_clickable_area->can_catch_side[2] = true;
	jc_clickable_area->can_catch_side[3] = true;
	jc_clickable_area->can_catch_side[4] = true;

	jc_clickable_area->text_area = jc_text_area;
	jc_clickable_area->batcher_for_default_draw = NS_EGraphicCore::default_batcher_for_drawing;

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
			jc_button_group_row = EButtonGroup::add_default_row_to_group(main_button_group, new ERegionGabarite(0.0f, 0.0f, 1200.0f, 160.0f));
			*jc_button_group_row->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;

			//*jc_button_group_row->

			if (true)
			{//new group
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
					if (j == 0) { jc_region_gabarite = new ERegionGabarite(100.0f, 20.0f); }
					else
					if (j == 1) { jc_region_gabarite = new ERegionGabarite(20.0f, 20.0f); }
					else
					if (j == 2) { jc_region_gabarite = new ERegionGabarite(50.0f, 20.0f); }

					jc_button = EntityButton::create_default_clickable_button
					(
						jc_region_gabarite,
						jc_button_group,
						nullptr
					);
					
					jc_button_group->button_list.push_back(jc_button);

					
					jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "!");
					Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

					if ((jc_text_area != nullptr) && (jc_text_area->stored_text != nullptr))
					{
						if (j == 0) { jc_text_area->change_text (random_item_property[rand() % 5]); }
						else
						if (j == 1) { jc_text_area->change_text("="); }
						else
						if (j == 2) { jc_text_area->change_text(std::to_string(rand() % 100)); }
					}
				}
			}
				
				//ITEM GROUP
				//massive
					EButtonGroup* massive_game_item = EButtonGroup::create_default_button_group(new ERegionGabarite(800.0f, 160.0f), EGUIStyle::active_style);
					jc_button_group_row->add_group(massive_game_item);

					//row
					EButtonGroupRow* row_game_item = EButtonGroup::add_default_row_to_group(massive_game_item, new ERegionGabarite(800.0f, 160.0f));		
				//
				
				////////////////////////
				//small subrow for additional buttons

					//side group for buttons
					EButtonGroup* group_side
					=
					EButtonGroup::create_button_group_without_bg(new ERegionGabarite(125.0f, 150.0f), EGUIStyle::active_style);
					row_game_item->add_group(group_side);

					float vertical_borders = *group_side->border_left + *group_side->border_right;


					EntityButton*

					//add new button
					small_button = EntityButton::create_default_clickable_button
					(new ERegionGabarite(120.0f, 18.0f), group_side, nullptr);

					jc_text_area = ETextArea::create_centered_text_area
					(EntityButton::get_last_clickable_area(small_button), EFont::font_list[0], "Add new button");

					*jc_text_area->can_be_edited = false;
					Entity::add_text_area_to_last_clickable_region(small_button, jc_text_area);

					group_side->button_list.push_back(small_button);

					//remove all buttons
					small_button = EntityButton::create_default_clickable_button
					(new ERegionGabarite(120.0f, 18.0f), group_side, nullptr);

					jc_text_area = ETextArea::create_centered_text_area
					(EntityButton::get_last_clickable_area(small_button), EFont::font_list[0], "");
					jc_text_area->color[0] = 1.0f;
					jc_text_area->color[1] = 0.20f;
					jc_text_area->color[2] = 0.25f;
					jc_text_area->color[3] = 1.0f;
					jc_text_area->change_text("Remove all buttons");

					*jc_text_area->can_be_edited = false;
					Entity::add_text_area_to_last_clickable_region(small_button, jc_text_area);

					group_side->button_list.push_back(small_button);
				////////////////////////



				////////////////////////
				//big subrow for items
					EButtonGroup*
					subgroup_for_items = EButtonGroup::create_button_group_without_bg
					(new ERegionGabarite(600.0f - vertical_borders, 150.0f), EGUIStyle::active_style);

					row_game_item->add_group(subgroup_for_items);
				////////////////////////



				//button item
				int button_count	= rand() % 10 + 1;
				button_count		*= rand() % 10 + 1;

				for (int i = 0; i < button_count; i++)
				{
					//button with clickable region, and brick bg
					jc_button = EntityButton::create_default_clickable_button
					(new ERegionGabarite(44.0f, 44.0f), subgroup_for_items,	nullptr);

					//delete action on right click
					Entity::get_last_clickable_area(jc_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_delete_entity);
					
					subgroup_for_items->button_list.push_back(jc_button);

					//add 2nd layer (icon)
					jc_button->sprite_layer_list.push_back
					(	
						ESpriteLayer::create_default_sprite_layer_with_size_and_offset
						(NS_EGraphicCore::default_texture_load(random_texture_list[rand() % 5]),
							3.0f, 3.0f, 3.0f,
							38.0f, 38.0f, 0.0f
						)
					);
			}
		}
	

	EButtonGroup::refresh_button_group(main_button_group);
	//main_button_group->realign_all_buttons();
	//main_button_group->align_groups();
	//EButtonGroup::calculate_culling_lines(main_button_group);
	

	//STYLE LIST BUTTON GROUP
	main_button_group = EButtonGroup::create_root_button_group
	(new ERegionGabarite(400.0f, 100.0f, 0.0f, 400.0f, 600.0f), EGUIStyle::active_style);
	main_button_group->root_group = main_button_group;
	*main_button_group->button_group_type = ButtonGroupType::BGT_DARKEN;

	//*main_button_group->can_change_style = false;

	for (EGUIStyle* style : EGUIStyle::style_list)
	{
		float horizontal_side = 350.0f - *style->button_group_main->side_offset_left - *style->button_group_main->side_offset_right;

		//main row
		jc_button_group_row = EButtonGroup::add_default_row_to_group (main_button_group, new ERegionGabarite(350.0f, 10.0f));
		*jc_button_group_row->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;

		//group with constant style
		jc_button_group = jc_button_group_row->add_group
		(EButtonGroup::create_default_button_group (new ERegionGabarite(350.0f, 10.0f + *style->button_group_main->side_offset_up), style));
		*jc_button_group->can_change_style = false;
		*jc_button_group->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;

		//subrow big
		jc_button_group_row = EButtonGroup::add_default_row_to_group
		(jc_button_group, new ERegionGabarite(0.0f, 0.0f, horizontal_side, 100.0f));

		//group big
		EButtonGroup* big_subgroup = jc_button_group_row->add_group
		(EButtonGroup::create_default_button_group (new ERegionGabarite (0.0f, 0.0f, horizontal_side, 100.0f) ,style));

			if (big_subgroup != nullptr)
			{
				*big_subgroup->can_change_style = false;

				for (int i = 0; i < 20; i++)
				{

					jc_button = EntityButton::create_default_clickable_button
					(
						new ERegionGabarite(40.0f, 40.0f),
						big_subgroup,
						nullptr
					);
					big_subgroup->button_list.push_back(jc_button);
				}

			}

		//subrow small (for button "select")
		jc_button_group_row = EButtonGroup::add_default_row_to_group
		(
			jc_button_group, new ERegionGabarite
			(horizontal_side, 20.0f + *style->button_group_main->side_offset_bottom + *style->button_group_main->side_offset_up + 8.0f)
		);

		

		//group (for button "select")
		jc_button_group = jc_button_group_row->add_group
		(
			EButtonGroup::create_default_button_group
			(new ERegionGabarite(horizontal_side, 20.0f + *style->button_group_main->side_offset_bottom + *style->button_group_main->side_offset_up + 8.0f), style)
		);		

		//select button
		if (jc_button_group != nullptr)
		{

			*jc_button_group->can_change_style = false;

			jc_button = EntityButton::create_default_clickable_button
			(
				new ERegionGabarite
				(
					horizontal_side
					-
					*style->button_group_main->side_offset_left
					-
					*style->button_group_main->side_offset_right
					-
					3.0f,
					20.0f
				),
				jc_button_group,
				&EDataActionCollection::action_select_this_style
			);

			
			jc_button_group->button_list.push_back(jc_button);

			

			//text area
			jc_text_area = ETextArea::create_centered_text_area	(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Select this style");
			*jc_text_area->can_be_edited = false;
			Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

			
			
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
	/**/jc_button_group_row = EButtonGroup::add_default_row_to_group (button_group_header, new ERegionGabarite(400.0f, 10.0f));
	///**/*button_group_header->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;
			jc_button_group_row->add_group(EButtonGroup::create_invisible_button_group(new ERegionGabarite(355.0f, 28.0f), EGUIStyle::active_style));

			EButtonGroup* close_group = jc_button_group_row->add_group
			(EButtonGroup::create_invisible_button_group (new ERegionGabarite(28.0f, 28.0f),EGUIStyle::active_style));
			//EButtonGroup* close_group = jc_button_group_row->add_group
			//close_group->parent_group = button_group_header;
					jc_button = new EntityButton();
					//jc_button->action_on_change_style_list.push_back(&action_change_style_button);
					close_group->button_list.push_back(jc_button);
					jc_button->parent_button_group = close_group;

					jc_button->sprite_layer_list.push_back (ESpriteLayer::create_default_sprite_layer (NS_EGraphicCore::default_texture_load("button_close")));

					jc_region_gabarite = new ERegionGabarite(20.0f, 20.0f);
					jc_button->button_gabarite = jc_region_gabarite;

					//EntityButton::button_generate_brick_bg(jc_button, EGUIStyle::active_style);

					//ECustomData* close_custom_data

						jc_custom_data = new ECustomData();
						jc_button->custom_data_list.push_back(jc_custom_data);

						jc_clickable_area = EClickableArea::create_default_clickable_region(jc_region_gabarite, jc_button, jc_custom_data);
						jc_clickable_area->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
						//jc_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_style);
						jc_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_close_root_group);

						jc_custom_data->clickable_area_list.push_back(jc_clickable_area);
						jc_custom_data->parent_entity = jc_button;
						jc_custom_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);

					jc_button->set_world_position(*jc_button->offset_x, *jc_button->offset_y, *jc_button->offset_z);
					jc_button->generate_vertex_buffer_for_all_sprite_layers();

	

	button_group_list.push_back(main_button_group);
	EButtonGroup::refresh_button_group(main_button_group);

	//DATA ENTITY
	main_button_group = EButtonGroup::create_root_button_group
	(new ERegionGabarite(900.0f, 100.0f, 0.0f, 900.0f, 600.0f), EGUIStyle::active_style);
	main_button_group->root_group = main_button_group;
	*main_button_group->button_group_type = ButtonGroupType::BGT_DARKEN;
	
	jc_button_group_row = EButtonGroup::add_default_row_to_group
	(main_button_group, new ERegionGabarite(890.0f, 580.0f));
	
	jc_button_group = jc_button_group_row->add_group
	(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 580.0f), EGUIStyle::active_style));
	
	unsigned int counter = 0;
	for (EDataEntity* data_entity: EDataEntity::data_entity_list)
	{
		jc_button = EntityButton::create_default_clickable_button
		(
			new ERegionGabarite(260.0f, 44.0f),
			jc_button_group,
			nullptr
		);

		//NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
		ETextureGabarite* gab = NS_EGraphicCore::default_texture_load("icons/" + DataEntityUtils::get_tag_value_by_name(0, "icon path", data_entity));
		float resize_factor = 38.0f / max(*gab->size_x_in_pixels, *gab->size_y_in_pixels);
		resize_factor = min(resize_factor, 1.0f);

		
		if (DataEntityUtils::get_tag_value_by_name(0, "icon path", data_entity) != "")
		//add 2nd layer (icon)
		{
			jc_button->sprite_layer_list.push_back
			(
				ESpriteLayer::create_default_sprite_layer_with_size_and_offset
				(
					gab,
					3.0f, 3.0f, 3.0f,
					38.0f * resize_factor, 38.0f * resize_factor, 0.0f
				)
			);

			ESpriteLayer::set_size_for_last_sprite
			(
				jc_button->sprite_layer_list.back(),
				*gab->size_x_in_pixels* resize_factor,
				*gab->size_y_in_pixels* resize_factor
			);
		}

		jc_text_area = ETextArea::create_centered_text_area
		(
			EntityButton::get_last_clickable_area(jc_button),
			EFont::font_list[0],
			DataEntityUtils::get_tag_value_by_name(0, "name EN", data_entity)//std::to_string(counter)
		);
			*jc_text_area->can_be_edited = false;

			*jc_text_area->offset_by_gabarite_size_x = 0.2;
			*jc_text_area->offset_by_text_size_x = 0.0;

			jc_text_area->offset_border[BorderSide::LEFT] = 65.0f;
			jc_text_area->change_text(DataEntityUtils::get_tag_value_by_name(0, "name EN", data_entity));

		Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

		jc_button_group->button_list.push_back(jc_button);

		counter++;
	}
	//*******HEADER*******
	button_group_header = EButtonGroup::create_header_button_group
	(new ERegionGabarite(0.0f, 0.0f, 0.0f, 900.0f, 40.0f), EGUIStyle::active_style);
	button_group_header->parent_group = main_button_group;
	//*button_group_header->is_active = false;
	//*main_button_group->is_active = false;
	/**/main_button_group->header_button_group = button_group_header;
	/**/*button_group_header->culling_lines_method = CullingLinesCalcMethod::CLCM_BY_HIMSELF;
	/**/button_group_header->root_group = main_button_group;
	/**/
	/**/jc_button_group_row = EButtonGroup::add_default_row_to_group(button_group_header, new ERegionGabarite(800.0f, 10.0f));
	///**/*button_group_header->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;
	jc_button_group_row->add_group(EButtonGroup::create_invisible_button_group(new ERegionGabarite(855.0f, 28.0f), EGUIStyle::active_style));

	 close_group = jc_button_group_row->add_group
	(EButtonGroup::create_invisible_button_group(new ERegionGabarite(28.0f, 28.0f), EGUIStyle::active_style));
	//EButtonGroup* close_group = jc_button_group_row->add_group
	//close_group->parent_group = button_group_header;
	jc_button = new EntityButton();
	jc_button->action_on_change_style_list.push_back(&action_change_style_button);
	close_group->button_list.push_back(jc_button);
	jc_button->parent_button_group = close_group;

	jc_button->sprite_layer_list.push_back(ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::default_texture_load("button_close")));

	jc_region_gabarite = new ERegionGabarite(20.0f, 20.0f);
	jc_button->button_gabarite = jc_region_gabarite;

	//EntityButton::button_generate_brick_bg(jc_button, EGUIStyle::active_style);

	//ECustomData* close_custom_data

	jc_custom_data = new ECustomData();
	jc_button->custom_data_list.push_back(jc_custom_data);

	jc_clickable_area = EClickableArea::create_default_clickable_region(jc_region_gabarite, jc_button, jc_custom_data);
	jc_clickable_area->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
	//jc_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_style);
	jc_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_close_root_group);

	jc_custom_data->clickable_area_list.push_back(jc_clickable_area);
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
