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



	//for (int j = 0; j < CLUSTER_DIM_X; j++)
	//for (int i = 0; i < CLUSTER_DIM_Y; i++)
	//{
	//	if (!cluster_array[j][i]->entity_list.empty())
	//	for (Entity* e : cluster_array[j][i]->entity_list)
	//	{
	//		e->draw();
	//	}

	//}

	NS_EGraphicCore::default_batcher_for_drawing->draw_call();
	
	
	//if (EInputCore::key_pressed_once(GLFW_KEY_W))	{ EInputCore::logger_simple_success("WwWwW"); }
	//if (EInputCore::key_holded(GLFW_KEY_W))			{ EInputCore::logger_simple_success("holded WwWwW"); }
}

void EWindowMain::update_additional(float _d)
{
	//for (int j = 0; j < CLUSTER_DIM_X; j++)
	//for (int i = 0; i < CLUSTER_DIM_Y; i++)
	//{
	//	
	//	for (Entity* el : cluster_array[j][i]->entity_list)
	//	{
	//		el->update(_d);
	//	}
	//}

}

EWindowMain::EWindowMain()
{
	//for(int i = 0; i < 1'000'000; i++)
	//{
	//	test_vector.push_back(new TestObject());
	//}
	
	//gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);

	ETextParser::data_entity_parse_file("data/data_entity_list.txt");

	//for (int j = 0; j < CLUSTER_DIM_X; j++)
	//for (int i = 0; i < CLUSTER_DIM_Y; i++)
	//{
	//	cluster_array[j][i] = new ECluster();
	//}

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
	//EButtonGroupRow*	jc_button_group_row;
	EntityButton*		jc_button;
	ESpriteFrame*		jc_sprite_frame = new ESpriteFrame();
	
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


	main_button_group = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(1920.0f, 1000.0f),	EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		*main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		//test blocks
		if (false)
		{
			for (int i = 0; i < 500 * 1; i++)
			{
				EButtonGroup* test_group = main_button_group->add_group
				(EButtonGroup::create_default_button_group(new ERegionGabarite(100.0f, 200.0f), EGUIStyle::active_style));
				*test_group->can_be_stretched_by_child = true;

				*test_group->stretch_x_by_parent_size = true;
				*test_group->stretch_y_by_parent_size = false;

				for (int k = 0; k < 20; k++)
				{
					EntityButton* test_button = EntityButton::create_default_clickable_button(new ERegionGabarite(64.0f, 64.0f), test_group, nullptr);
					test_group->button_list.push_back(test_button);
				}
			}
			group_list.push_back(main_button_group);
			EButtonGroup::refresh_button_group(main_button_group);
		}
	////////////////////////////////////////////////

	//filters block
	if (true)
	{
		main_button_group = EButtonGroup::create_root_button_group
		(
			new ERegionGabarite(1920.0f, 1000.0f),
			EGUIStyle::active_style
		);
		main_button_group->root_group = main_button_group;

		*main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		//*main_button_group->stretch_mode		= GroupStretchMode::CONSTANT;

		//std::string[3]
		for (int z = 0; z < 100; z++)
		{
			//whole filter block
			EButtonGroup* filter_block_group = EButtonGroup::create_root_button_group(new ERegionGabarite(0.0f, 0.0f, 1200.0f, 200.0f), EGUIStyle::active_style);

			*filter_block_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

			*filter_block_group->stretch_x_by_parent_size = true;
			*filter_block_group->stretch_y_by_parent_size = false;

			main_button_group->add_group(filter_block_group);

			//left side for equational parameters
			if (true)
			{//new group
				EButtonGroup* left_group = EButtonGroup::create_default_button_group
				(
					new ERegionGabarite(210.0f, 160.0f),
					EGUIStyle::active_style
				);

				*left_group->stretch_x_by_parent_size = false;
				*left_group->stretch_y_by_parent_size = true;

				*left_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

				filter_block_group->add_group(left_group);

				//"ZZZ" buttons
				int parameters_count = (rand() % 4) * (rand() % 4) * (rand() % 4);
				for (int i = 0; i < parameters_count; i++)
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
							left_group,
							nullptr
						);

						left_group->button_list.push_back(jc_button);


						jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "!");
						Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

						if ((jc_text_area != nullptr) && (jc_text_area->stored_text != nullptr))
						{
							if (j == 0) { *jc_text_area->can_be_edited = false; jc_text_area->change_text(random_item_property[rand() % 5]); }
							else
								if (j == 1) { *jc_text_area->can_be_edited = false; jc_text_area->change_text("="); }
								else
									if (j == 2) { *jc_text_area->can_be_edited = true; jc_text_area->change_text(std::to_string(rand() % 100)); }
						}
					}
			}

			//####### ITEM GROUP //#######
			//massive
			EButtonGroup* verical_item_element = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(800.0f, 160.0f), EGUIStyle::active_style);
				filter_block_group->add_group(verical_item_element);
				*verical_item_element->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
				//*massive_game_item->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				*verical_item_element->stretch_x_by_parent_size = true;
				*verical_item_element->stretch_y_by_parent_size = true;
			for (int r = 0; r < 3; r++)
			if (rand() % 3 == 0)
			{


				EButtonGroup* massive_game_item = EButtonGroup::create_default_button_group(new ERegionGabarite(800.0f, 100.0f), EGUIStyle::active_style);
				
				verical_item_element->add_group(massive_game_item);
				*massive_game_item->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*massive_game_item->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				*massive_game_item->stretch_x_by_parent_size = true;
				*massive_game_item->stretch_y_by_parent_size = false;

				////////////////////////
				//small subrow for additional buttons

					//side group for buttons
				EButtonGroup* group_side = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(134.0f, 160.0f - 14.0f), EGUIStyle::active_style);
				massive_game_item->add_group(group_side);
				//row_game_item->add_group(group_side);
				*group_side->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*group_side->stretch_mode		= GroupStretchMode::STRETCHED_ONLY_BY_PARENT;

				*group_side->stretch_x_by_parent_size = false;
				*group_side->stretch_y_by_parent_size = true;

				float vertical_borders = *group_side->border_left + *group_side->border_right;

				//add new button
				EntityButton*
					small_button = EntityButton::create_default_clickable_button
					(
						new ERegionGabarite(130.0f, 18.0f),
						group_side,
						&EDataActionCollection::action_open_data_entity_filter_group
					);

				EDataContainerStoreTargetGroup* data_store_target_group = new EDataContainerStoreTargetGroup();
				EntityButton::get_last_custom_data(small_button)->data_container = data_store_target_group;

				jc_text_area = ETextArea::create_centered_text_area
				(EntityButton::get_last_clickable_area(small_button), EFont::font_list[0], "Add new item");

				*jc_text_area->can_be_edited = false;
				Entity::add_text_area_to_last_clickable_region(small_button, jc_text_area);

				group_side->button_list.push_back(small_button);

				//remove all buttons
				small_button = EntityButton::create_default_clickable_button
				(new ERegionGabarite(130.0f, 18.0f), group_side, nullptr);

				jc_text_area = ETextArea::create_centered_text_area
				(EntityButton::get_last_clickable_area(small_button), EFont::font_list[0], "");
				jc_text_area->change_text("Remove all buttons");

				*jc_text_area->can_be_edited = false;
				Entity::add_text_area_to_last_clickable_region(small_button, jc_text_area);

				group_side->button_list.push_back(small_button);
				////////////////////////



				////////////////////////
				//big subrow for items
				EButtonGroup*
					group_for_items = EButtonGroup::create_button_group_without_bg
					(new ERegionGabarite(600.0f, 130.0f), EGUIStyle::active_style);

				*group_for_items->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*group_for_items->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				*group_for_items->stretch_x_by_parent_size = true;
				*group_for_items->stretch_y_by_parent_size = true;

				massive_game_item->add_group(group_for_items);

				data_store_target_group->target_group = group_for_items;
				////////////////////////


				std::vector <EDataEntity*> suitable_data_entity;
				//regular items
				//button item
				if (r == 0)
				{
					int button_count = rand() % 3 + 1;
					button_count *= rand() % 3 + 1;
					button_count *= rand() % 3 + 1;
					button_count *= rand() % 3 + 1;
					button_count *= rand() % 3 + 1;

						suitable_data_entity.clear();
						for (EDataEntity* de : EDataEntity::data_entity_list)
						{
							if (DataEntityUtils::get_tag_value_by_name(0, "data type", de) == "Game item")
							{
								suitable_data_entity.push_back(de);
							}
						}

					for (int i = 0; i < button_count; i++)
					{
						

						int selected_data_entity = rand() % suitable_data_entity.size();

						//button with clickable region, and brick bg
						jc_button = EntityButton::create_item_button
						(
							nullptr,
							group_for_items,
							suitable_data_entity[selected_data_entity]
						);

						group_for_items->button_list.push_back(jc_button);


					}
				}

				if (r == 1)
				{
					int button_count = rand() % 3 + 1;
					button_count *= rand() % 3 + 1;

						suitable_data_entity.clear();
						for (EDataEntity* de : EDataEntity::data_entity_list)
						{
							if (DataEntityUtils::get_tag_value_by_name(0, "data type", de) == "Base Class")
							{
								suitable_data_entity.push_back(de);
							}
						}

					for (int i = 0; i < button_count; i++)
					{
						

						int selected_data_entity = rand() % suitable_data_entity.size();

						//button with clickable region, and brick bg
						jc_button = EntityButton::create_wide_item_button
						(
							nullptr,
							group_for_items,
							suitable_data_entity[selected_data_entity]
						);

						group_for_items->button_list.push_back(jc_button);


					}
				}

				if (r == 2)
				{
	
						suitable_data_entity.clear();
						for (EDataEntity* de : EDataEntity::data_entity_list)
						{
							if (DataEntityUtils::get_tag_value_by_name(0, "data type", de) == "Influence")
							{
								suitable_data_entity.push_back(de);
							}
						}


						for (int k = 0; k < suitable_data_entity.size(); k++)
						{
							if (rand() % 3 == 0)
							{
								jc_button = EntityButton::create_wide_item_button
								(
									nullptr,
									group_for_items,
									suitable_data_entity[k]
								);

								group_for_items->button_list.push_back(jc_button);
							}
						}
				}
			}
			






			//####### COSMETIC SEGMENT #######
			//block
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				EButtonGroup* cosmetic_segment = EButtonGroup::create_default_button_group(new ERegionGabarite(256.0f, 160.0f), EGUIStyle::active_style);
				filter_block_group->add_group(cosmetic_segment);

				*cosmetic_segment->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*massive_game_item->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				*cosmetic_segment->stretch_x_by_parent_size = false;
				*cosmetic_segment->stretch_y_by_parent_size = true;
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}



		group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}

	//TODO: change pointer to non-pointer in font glyph

	

	//STYLE LIST BUTTON GROUP
	if (true)
	{
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(400.0f, 100.0f, 0.0f, 400.0f, 600.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		*main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		*main_button_group->can_be_stretched_by_child = false;
		//*main_button_group->can_change_style = false;

		for (EGUIStyle* style : EGUIStyle::style_list)
			//EGUIStyle* style = EGUIStyle::style_list[0];
		{
			float horizontal_side = 350.0f - *style->button_group_main->side_offset_left - *style->button_group_main->side_offset_right;


			//group with constant style
			jc_button_group = main_button_group->add_group
			(EButtonGroup::create_default_button_group(new ERegionGabarite(horizontal_side, 20.0f), style));
			*jc_button_group->can_be_stretched_by_child = true;

			*jc_button_group->stretch_x_by_parent_size = true;
			*jc_button_group->stretch_y_by_parent_size = false;

			*jc_button_group->can_change_style = false;




			//group for prewiev button
			EButtonGroup* big_subgroup = jc_button_group->add_group
			(EButtonGroup::create_default_button_group(new ERegionGabarite(10.0f, 100.0f), style));
			*big_subgroup->stretch_x_by_parent_size = true;
			*big_subgroup->stretch_y_by_parent_size = false;

			if (big_subgroup != nullptr)
			{
				*big_subgroup->can_change_style = false;

				for (int i = 0; i < 17; i++)
				{

					jc_button = EntityButton::create_default_clickable_button
					(
						new ERegionGabarite(40.0f, 40.0f),
						big_subgroup,
						nullptr
					);

					ETextureGabarite* item_icon
						=
						NS_EGraphicCore::load_from_textures_folder
						("icons/" + DataEntityUtils::get_tag_value_by_name(0, "icon path", EDataEntity::data_entity_list[rand() % EDataEntity::data_entity_list.size()]));

					if (item_icon != nullptr)
					{
						float resize_factor = 32.0f / max(*item_icon->size_x_in_pixels, *item_icon->size_y_in_pixels);
						resize_factor = min(resize_factor, 1.0f);

						jc_button->sprite_layer_list.push_back
						(
							ESpriteLayer::create_default_sprite_layer_with_size_and_offset
							(item_icon,
								(40.0f - *item_icon->size_x_in_pixels * resize_factor) / 2.0f,
								(40.0f - *item_icon->size_y_in_pixels * resize_factor) / 2.0f,
								3.0f,

								*item_icon->size_x_in_pixels * resize_factor,
								*item_icon->size_y_in_pixels * resize_factor,
								0.0f
							)
						);
					}

					big_subgroup->button_list.push_back(jc_button);
				}

			}

			//subrow small (for button "select")
			/*jc_button_group_row = EButtonGroup::add_default_row_to_group
			(
				jc_button_group, new ERegionGabarite
				(horizontal_side, 30.0f)
			);*/



			//group (for button "select")
			jc_button_group = jc_button_group->add_group
			(
				EButtonGroup::create_default_button_group
				(new ERegionGabarite(horizontal_side, 26.0f + *style->button_group_main->side_offset_bottom + *style->button_group_main->side_offset_up), style)
			);

			*jc_button_group->stretch_x_by_parent_size = true;
			*jc_button_group->stretch_y_by_parent_size = false;

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
				jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Select this style");
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
		(new ERegionGabarite(0.0f, 0.0f, 0.0f, 400.0f, 50.0f), EGUIStyle::active_style);
		button_group_header->parent_group = main_button_group;
		*button_group_header->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		//*button_group_header->stretch_mode = GroupStretchMode::STRETCHED_ONLY_BY_PARENT;
		//*button_group_header->is_active = false;
		//*main_button_group->is_active = false;
		/**/main_button_group->header_button_group = button_group_header;
		/**/*button_group_header->culling_lines_method = CullingLinesCalcMethod::CLCM_BY_HIMSELF;
		/**/button_group_header->root_group = main_button_group;
		/**/
		/**///jc_button_group_row = EButtonGroup::add_default_row_to_group (button_group_header, new ERegionGabarite(400.0f, 10.0f));
		///**/*button_group_header->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;
		EButtonGroup* left_sided_close_group = button_group_header->add_group(EButtonGroup::create_invisible_button_group(new ERegionGabarite(355.0f, 28.0f), EGUIStyle::active_style));

		EButtonGroup* close_group = button_group_header->add_group
		(EButtonGroup::create_invisible_button_group(new ERegionGabarite(28.0f, 28.0f), EGUIStyle::active_style));
		//*close_group->stretch_mode = GroupStretchMode::STRETCHED_ONLY_BY_PARENT;
		//EButtonGroup* close_group = jc_button_group_row->add_group
		//close_group->parent_group = button_group_header;
		jc_button = new EntityButton();
		//jc_button->action_on_change_style_list.push_back(&action_change_style_button);
		close_group->button_list.push_back(jc_button);
		jc_button->parent_button_group = close_group;

		jc_button->sprite_layer_list.push_back(ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::load_from_textures_folder("button_close")));

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

		jc_button->set_world_position(jc_button->offset_x, jc_button->offset_y, jc_button->offset_z);
		jc_button->generate_vertex_buffer_for_all_sprite_layers();



		group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}
	//DATA ENTITY
	if (true)
	{
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(900.0f, 100.0f, 0.0f, 900.0f, 600.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		*main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		EButtonGroup::data_entity_filter = main_button_group;

		EDataContainerDataEntitySearchGroup* jc_data_container_for_search_group = new EDataContainerDataEntitySearchGroup();
		main_button_group->data_container = jc_data_container_for_search_group;
		*main_button_group->is_active = false;

		DataEntityFilter* data_filter_rule = new DataEntityFilter();
			*data_filter_rule->target_tag_name		= "data type";
			data_filter_rule->suitable_values_list.push_back(new std::string("game item"));

		jc_data_container_for_search_group->required_tag_list.push_back(data_filter_rule);

		// // //	DATA ENTITY LIST	// // //
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 480.0f), EGUIStyle::active_style));
		*jc_button_group->stretch_x_by_parent_size = true;
		*jc_button_group->stretch_y_by_parent_size = true;
		jc_data_container_for_search_group->pointer_to_group_with_data_entities = jc_button_group;

		unsigned int counter = 0;
		for (EDataEntity* data_entity : EDataEntity::data_entity_list)
		{
			jc_button = EntityButton::create_default_clickable_button
			(
				new ERegionGabarite(260.0f, 44.0f),
				jc_button_group,
				&EDataActionCollection::action_add_item_to_group_receiver
			);


			EDataContainerEntityDataHolder* data_holder = new EDataContainerEntityDataHolder();
			data_holder->stored_data_entity = data_entity;
			EntityButton::get_last_custom_data(jc_button)->data_container = data_holder;

			//EInputCore::logger_param("size of tag list", data_holder->stored_data_entity->tag_list.size());

			jc_button->pointer_to_data_entity = data_entity;

			//NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
			ETextureGabarite* gab = NS_EGraphicCore::load_from_textures_folder("icons/" + DataEntityUtils::get_tag_value_by_name(0, "icon path", data_entity));
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
					*gab->size_x_in_pixels * resize_factor,
					*gab->size_y_in_pixels * resize_factor
				);
			}

			jc_text_area = ETextArea::create_centered_text_area
			(
				EntityButton::get_last_clickable_area(jc_button),
				EFont::font_list[0],
				DataEntityUtils::get_tag_value_by_name(0, "name EN", data_entity)//std::to_string(counter)
			);
			*jc_text_area->can_be_edited = false;

			*jc_text_area->offset_by_gabarite_size_x = 0.0;
			*jc_text_area->offset_by_text_size_x = 0.0;

			jc_text_area->offset_border[BorderSide::LEFT] = 60.0f;
			jc_text_area->change_text(DataEntityUtils::get_tag_value_by_name(0, "name EN", data_entity));

			Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

			jc_button_group->button_list.push_back(jc_button);

			counter++;
		}

		//search bar group
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 50.0f), EGUIStyle::active_style));
		*jc_button_group->stretch_x_by_parent_size = true;
		*jc_button_group->stretch_y_by_parent_size = false;

		jc_button = EntityButton::create_default_clickable_button
		(
			new ERegionGabarite(800.0f, 25.0f),
			jc_button_group,
			nullptr
		);
		jc_data_container_for_search_group->pointer_to_search_bar = jc_button;

		jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Chaos orb");
		jc_text_area->action_on_change_text.push_back(&EDataActionCollection::action_type_text);
		Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
		jc_button_group->button_list.push_back(jc_button);

		EDataActionCollection::action_type_text(jc_text_area);

		//*******HEADER*******
		EButtonGroup* button_group_header = EButtonGroup::create_header_button_group
		(new ERegionGabarite(900.0f, 43.0f), EGUIStyle::active_style);

		button_group_header->parent_group = main_button_group;
		*button_group_header->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		//*button_group_header->is_active = false;
		//*main_button_group->is_active = false;
		/**/main_button_group->header_button_group = button_group_header;
		/**/*button_group_header->culling_lines_method = CullingLinesCalcMethod::CLCM_BY_HIMSELF;
		/**/button_group_header->root_group = main_button_group;
		/**/
		/**///jc_button_group_row = EButtonGroup::add_default_row_to_group(button_group_header, new ERegionGabarite(800.0f, 10.0f));
		///**/*button_group_header->gabarite_size_mode_y = ButtonGroupGabariteSize::BGGS_EXACT_STRETCH;
		EButtonGroup* left_sided_close_group = button_group_header->add_group(EButtonGroup::create_invisible_button_group(new ERegionGabarite(855.0f, 28.0f), EGUIStyle::active_style));
		*left_sided_close_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

		EButtonGroup* close_group = button_group_header->add_group
		(EButtonGroup::create_invisible_button_group(new ERegionGabarite(28.0f, 28.0f), EGUIStyle::active_style));

		//EButtonGroup* close_group = jc_button_group_row->add_group
		//close_group->parent_group = button_group_header;
		jc_button = new EntityButton();
		jc_button->action_on_change_style_list.push_back(&action_change_style_button);
		close_group->button_list.push_back(jc_button);
		jc_button->parent_button_group = close_group;

		jc_button->sprite_layer_list.push_back(ESpriteLayer::create_default_sprite_layer(NS_EGraphicCore::load_from_textures_folder("button_close")));

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

		jc_button->set_world_position(jc_button->offset_x, jc_button->offset_y, jc_button->offset_z);
		jc_button->generate_vertex_buffer_for_all_sprite_layers();


		group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////		world parameter		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(400.0f, 20.0f, 0.0f, 200, 160.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		*main_button_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 580.0f), EGUIStyle::active_style));
		*jc_button_group->stretch_x_by_parent_size = true;
		*jc_button_group->stretch_y_by_parent_size = true;

		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(100.0f, 38.0f),
			jc_button_group
		);

		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::global_normal_multiplier;

		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(100.0f, 38.0f),
			jc_button_group
		);

		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::global_gloss_multiplier;

		jc_button_group->button_list.push_back(jc_button);


		group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}
}

EWindowMain::~EWindowMain()
{

}
