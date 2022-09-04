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

#include <chrono>

//class Entity;
EWindowMain*	EWindowMain::link_to_main_window;
EButtonGroup*	EWindowMain::select_rarity_button_group;
EButtonGroup*	EWindowMain::select_quality_button_group;

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

void EDataActionCollection::action_select_this_text_variant(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton*	clicked_button								= static_cast<EntityButton*>(_entity);
	ETextArea*		clicked_button_text_area					= EntityButton::get_last_clickable_area(clicked_button)->text_area;

	EButtonGroup*	root_group									= clicked_button->parent_button_group->root_group;
	EDataContainer* root_container								= root_group->data_container;
	

	ETextArea*		target_text_area							= EntityButton::get_last_clickable_area(static_cast<EDataContainer_Group_TextSelectorFromVariants*>(root_container)->target_button)->text_area;

					target_text_area->localisation_text			= clicked_button_text_area->localisation_text;
					//*target_text_area->stored_text = *EntityButton::get_last_clickable_area(static_cast<EntityButton*>(_entity))->text_area->stored_text;

					target_text_area->stored_color				= clicked_button_text_area->stored_color;
					target_text_area->color						= clicked_button_text_area->color;

					target_text_area->change_text				(*clicked_button_text_area->stored_text);

					root_group->is_active = false;
}

void EDataActionCollection::action_mark_parent_group_as_removed(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EInputCore::logger_simple_info("try mark parent group is deleted");

	if (static_cast<EntityButton*>(_entity)->parent_button_group != nullptr)
	{
		
		static_cast<EntityButton*>(_entity)->parent_button_group->need_remove = true;

		EInputCore::logger_simple_success("marked as deleted");
	}
	else
	{
		EInputCore::logger_simple_error("parent is NULL");
	}
}


EWindowMain::EWindowMain()
{

	register_filter_rules();

	FilterBlockAttribute*	jc_filter_block_attribute;
	ELocalisationText		jc_localisation;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "ItemLevel";
	jc_localisation.localisations[NSW_localisation_EN]		= "Item level";
	jc_localisation.localisations[NSW_localisation_RU]		= "������� ��������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "DropLevel";
	jc_localisation.localisations[NSW_localisation_EN]		= "Required level";
	jc_localisation.localisations[NSW_localisation_RU]		= "��������� �������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "Quality";
	jc_localisation.localisations[NSW_localisation_EN]		= "Quality";
	jc_localisation.localisations[NSW_localisation_RU]		= "��������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "GemLevel";
	jc_localisation.localisations[NSW_localisation_EN]		= "Gem level";
	jc_localisation.localisations[NSW_localisation_RU]		= "������� �����";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "SocketGroup";
	jc_localisation.localisations[NSW_localisation_EN]		= "Links colours";
	jc_localisation.localisations[NSW_localisation_RU]		= "����� ������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "Sockets";
	jc_localisation.localisations[NSW_localisation_EN]		= "Sockets colours";
	jc_localisation.localisations[NSW_localisation_RU]		= "����� �����";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "LinkedSockets";
	jc_localisation.localisations[NSW_localisation_EN]		= "Linked sockets";
	jc_localisation.localisations[NSW_localisation_RU]		= "��������� ������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "StackSize";
	jc_localisation.localisations[NSW_localisation_EN]		= "Stack size";
	jc_localisation.localisations[NSW_localisation_RU]		= "������ ������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "AreaLevel";
	jc_localisation.localisations[NSW_localisation_EN]		= "Area level";
	jc_localisation.localisations[NSW_localisation_RU]		= "������� �������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "CorruptedMods";
	jc_localisation.localisations[NSW_localisation_EN]		= "Corrupted mods";
	jc_localisation.localisations[NSW_localisation_RU]		= "������������ ��������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "Width";
	jc_localisation.localisations[NSW_localisation_EN]		= "Width";
	jc_localisation.localisations[NSW_localisation_RU]		= "������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "Height";
	jc_localisation.localisations[NSW_localisation_EN]		= "Height";
	jc_localisation.localisations[NSW_localisation_RU]		= "������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "EnchantmentPassiveNum";
	jc_localisation.localisations[NSW_localisation_EN]		= "Passives count";
	jc_localisation.localisations[NSW_localisation_RU]		= "�������� ���������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "GemQualityType";
	jc_localisation.localisations[NSW_localisation_EN]		= "Alternative quality";
	jc_localisation.localisations[NSW_localisation_RU]		= "�������������� ��������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST;
		jc_filter_block_attribute->have_operator				= false;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "BaseDefencePercentile";
	jc_localisation.localisations[NSW_localisation_EN]		= "Defence procentile";
	jc_localisation.localisations[NSW_localisation_RU]		= "���������� ������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "HasSearingExarchImplicit";
	jc_localisation.localisations[NSW_localisation_EN]		= "Searing Exarch implicits";
	jc_localisation.localisations[NSW_localisation_RU]		= "�������� ���������� �������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "HasEaterOfWorldsImplicit";
	jc_localisation.localisations[NSW_localisation_EN]		= "Eater of Worlds implicits";
	jc_localisation.localisations[NSW_localisation_RU]		= "�������� ���������� �����";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "MapTier";
	jc_localisation.localisations[NSW_localisation_EN]		= "Map tier";
	jc_localisation.localisations[NSW_localisation_RU]		= "��� �����";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name								= "ItemRarity";
	jc_localisation.localisations[NSW_localisation_EN]		= "Item rarity";
	jc_localisation.localisations[NSW_localisation_RU]		= "�������� ��������";
		
	jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation					= jc_localisation;
		jc_filter_block_attribute->filter_attribute_type		= FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type	= FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST;
		jc_filter_block_attribute->have_operator				= true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);



	




	/*____________________________________LISTED SECTION___________________________________________________*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		jc_localisation.base_name = "BaseType";
		jc_localisation.localisations[NSW_localisation_EN] = "Game item";
		jc_localisation.localisations[NSW_localisation_RU] = "�������";

		jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation = jc_localisation;
		jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
		jc_filter_block_attribute->have_operator = false;

		jc_filter_block_attribute->filter_rule = EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM];

		registered_filter_block_attributes.push_back(jc_filter_block_attribute);


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		jc_localisation.base_name = "HasExplicitMod ";
		jc_localisation.localisations[NSW_localisation_EN] = "Explicit mode";
		jc_localisation.localisations[NSW_localisation_RU] = "�������/�������";

		jc_filter_block_attribute = new FilterBlockAttribute();
		jc_filter_block_attribute->localisation = jc_localisation;
		jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
		jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
		jc_filter_block_attribute->have_operator = false;

		jc_filter_block_attribute->filter_rule = EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS];

		registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	/*_____________________________________________________________________________________________________*/




	

	//EInputCore::logger_param("registered data entity filter size", EFilterRule::registered_filter_rules.size());

	

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




		//test blocks
		if (false)
		{
			for (int i = 0; i < 500 * 1; i++)
			{
				EButtonGroup* test_group = main_button_group->add_group
				(EButtonGroup::create_default_button_group(new ERegionGabarite(100.0f, 200.0f), EGUIStyle::active_style));
				test_group->can_be_stretched_by_child = true;

				test_group->stretch_x_by_parent_size = true;
				test_group->stretch_y_by_parent_size = false;

				for (int k = 0; k < 20; k++)
				{
					EntityButton* test_button = EntityButton::create_default_clickable_button(new ERegionGabarite(64.0f, 64.0f), test_group, nullptr);
					test_group->button_list.push_back(test_button);
				}
			}
			button_group_list.push_back(main_button_group);
			EButtonGroup::refresh_button_group(main_button_group);
		}
	////////////////////////////////////////////////

		std::string color_names_list[] = {"Never", "Gonna", "Give","You","Up","Never","Gonna","Ley","You","Down","Never","Gonna","Run","Arround","And", "Desert", "You"};

	/*	REGISTER COLORS	*/
		for (int i = 0; i < 17; i++)
		{
			Helper::HSVRGBAColor HRA_color;

			HRA_color.h = rand() % 360;
			HRA_color.s = 1.0f - pow((rand() % 100) / 100.0f, 1.0);
			HRA_color.v = 1.0f - pow((rand() % 100) / 100.0f, 3.0);
			HRA_color.a = 1.0f - pow((rand() % 100) / 100.0f, 4.0);

			Helper::hsv2rgb(&HRA_color);

			Helper::HRA_color_collection* HRA_collection = new Helper::HRA_color_collection();
			HRA_collection->name = color_names_list[i];
			HRA_collection->target_color = HRA_color;

			Helper::registered_color_list.push_back(HRA_collection);
		}
	/*------------------*/

	//filters block
	if (true)
	{
		main_button_group = EButtonGroup::create_button_group_without_bg
		(
			new ERegionGabarite(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT),
			EGUIStyle::active_style
		);
		main_button_group->actions_on_resize_window.push_back(&EDataActionCollection::action_resize_to_full_window);

		main_button_group->root_group = main_button_group;
		main_button_group->can_be_moved = false;
		main_button_group->can_resize_to_workspace_size = false;

		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		//*main_button_group->stretch_mode		= GroupStretchMode::CONSTANT;

		//std::string[3]
		for (int z = 0; z < 100; z++)
		{
			//whole filter block
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			EButtonGroup* whole_filter_block_group = EButtonGroup::create_root_button_group(new ERegionGabarite(0.0f, 0.0f, 1200.0f, 200.0f), EGUIStyle::active_style);
			whole_filter_block_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;

			whole_filter_block_group->stretch_x_by_parent_size = true;
			whole_filter_block_group->stretch_y_by_parent_size = false;

			
			main_button_group->add_group(whole_filter_block_group);

			EDataContainer_Group_WholeFilterBlock* whole_block_data = new EDataContainer_Group_WholeFilterBlock();
			whole_filter_block_group->data_container = whole_block_data;

			////main bottom section
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//EButtonGroup* bottom_section_for_conditions = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(0.0f, 0.0f, 1200.0f, 180.0f), EGUIStyle::active_style);
			//	*bottom_section_for_conditions->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
			//	*bottom_section_for_conditions->stretch_x_by_parent_size = true;
			//	*bottom_section_for_conditions->stretch_y_by_parent_size = true;
			//	whole_filter_block_group->add_group(bottom_section_for_conditions);

			//left additional section
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			EButtonGroup* left_control_section = EButtonGroup::create_default_button_group(new ERegionGabarite(50.0f, 20.0f), EGUIStyle::active_style);
				left_control_section->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
				left_control_section->stretch_x_by_parent_size = false;
				left_control_section->stretch_y_by_parent_size = true;
				whole_filter_block_group->add_group(left_control_section);

				EntityButton* jc_button = EntityButton::create_default_clickable_button
				(
					new ERegionGabarite(50.0f, 50.0f),
					left_control_section,
					&EDataActionCollection::action_open_add_content_window
				);

				EDataContainer_Button_OpenButtonGroup* data_open_group = new EDataContainer_Button_OpenButtonGroup();
				data_open_group->master_group = whole_filter_block_group;
				data_open_group->target_group = EButtonGroup::data_entity_filter;

				ESpriteLayer* jc_sprite_layer = ESpriteLayer::create_default_sprite_layer_with_size_and_offset
				(
					NS_EGraphicCore::load_from_textures_folder("button_plus"),

					5.0f,
					5.0f,
					0.0f,

					40.0f,
					40.0f,
					0.0f
				);

				jc_button->sprite_layer_list.push_back(jc_sprite_layer);

				EntityButton::get_last_custom_data(jc_button)->data_container = data_open_group;

				//jc_text_area = ETextArea::create_centered_text_area
				//(EntityButton::get_last_clickable_area(jc_button), EFont::font_list[0], "");
				//jc_text_area->change_text("+");

				//*jc_text_area->can_be_edited = false;
				//Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

				left_control_section->button_list.push_back(jc_button);

			//left side for equational parameters
			if (true)
			{//new group
				EButtonGroup* non_list_condition_group = EButtonGroup::create_default_button_group
				(
					new ERegionGabarite(340.0f, 160.0f),
					EGUIStyle::active_style
				);
				

				whole_block_data->pointer_to_non_listed_segment = non_list_condition_group;

				non_list_condition_group->stretch_x_by_parent_size = false;
				non_list_condition_group->stretch_y_by_parent_size = true;

				non_list_condition_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

				whole_filter_block_group->add_group(non_list_condition_group);

				//"ZZZ" buttons
				int parameters_count = (rand() % 4) * (rand() % 4);
				int rnd = 0;
				for (int i = 0; i < parameters_count; i++)
				{
					rnd = rand() % registered_filter_block_attributes.size();
					if ((registered_filter_block_attributes.size() > 0) && (registered_filter_block_attributes[rnd]->filter_attribute_type == FILTER_ATTRIBUTE_TYPE_NON_LISTED))
					{add_non_listed_buttons_to_filter_block(whole_filter_block_group, registered_filter_block_attributes[rnd]);}
				}
			}

			//####### ITEM GROUP //#######
			//massive
			EButtonGroup* listed_condition_segment = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(800.0f, 160.0f), EGUIStyle::active_style);

				
				listed_condition_segment->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
				//*massive_game_item->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				listed_condition_segment->stretch_x_by_parent_size = true;
				listed_condition_segment->stretch_y_by_parent_size = true;

				whole_block_data->pointer_to_listed_segment = listed_condition_segment;

				std::string select_window_tags[3] = { "game item", "base class", "influence" };

				whole_filter_block_group->add_group(listed_condition_segment);

			RegisteredFilterRules rule_id[3] =
			{
				RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM,
				RegisteredFilterRules::FILTER_RULE_BASE_CLASS,
				RegisteredFilterRules::FILTER_RULE_INFLUENCE
			};

			for (int r = 0; r < 3; r++)
			if (rand() % 3 == 0)
			{


				EButtonGroup* list_condition_group_container = EButtonGroup::create_default_button_group(new ERegionGabarite(800.0f, 100.0f), EGUIStyle::active_style);
				
				listed_condition_segment->add_group(list_condition_group_container);
				list_condition_group_container->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*massive_game_item->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				list_condition_group_container->stretch_x_by_parent_size = true;
				list_condition_group_container->stretch_y_by_parent_size = true;

				////////////////////////
				//small subrow for additional buttons

				//side group for buttons
				EButtonGroup* list_left_part_group = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(134.0f, 80.0f), EGUIStyle::active_style);
				list_condition_group_container->add_group(list_left_part_group);
				//row_game_item->add_group(group_side);
				list_left_part_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*group_side->stretch_mode		= GroupStretchMode::STRETCHED_ONLY_BY_PARENT;

				list_left_part_group->stretch_x_by_parent_size = false;
				list_left_part_group->stretch_y_by_parent_size = true;

				float vertical_borders = list_left_part_group->border_left + list_left_part_group->border_right;

				//add new button
				EntityButton*
					small_button = EntityButton::create_default_clickable_button
					(
						new ERegionGabarite(130.0f, 18.0f),
						list_left_part_group,
						&EDataActionCollection::action_open_data_entity_filter_group
					);

				EDataContainerStoreTargetGroup*
				data_store_target_group = new EDataContainerStoreTargetGroup();
				data_store_target_group->filter_rule = EFilterRule::registered_filter_rules[rule_id[r]];
				
				//game item
				if (r == 0) { data_store_target_group->target_action_on_click = &EDataActionCollection::action_add_wide_item_to_group_receiver; }

				//class
				if (r == 1) { data_store_target_group->target_action_on_click = &EDataActionCollection::action_add_wide_item_to_group_receiver; }
				
				//influence
				if (r == 2) { data_store_target_group->target_action_on_click = &EDataActionCollection::action_add_wide_item_to_group_receiver; }

				EntityButton::get_last_custom_data(small_button)->data_container = data_store_target_group;
				

				jc_text_area = ETextArea::create_centered_text_area
				(EntityButton::get_last_clickable_area(small_button), EFont::font_list[0], "Add new item");

				*jc_text_area->can_be_edited = false;
				Entity::add_text_area_to_last_clickable_region(small_button, jc_text_area);

				list_left_part_group->button_list.push_back(small_button);

				//remove all buttons
				small_button = EntityButton::create_default_clickable_button
				(new ERegionGabarite(130.0f, 18.0f), list_left_part_group, nullptr);

				jc_text_area = ETextArea::create_centered_text_area
				(EntityButton::get_last_clickable_area(small_button), EFont::font_list[0], "");
				jc_text_area->change_text("������� ����");

				*jc_text_area->can_be_edited = false;
				Entity::add_text_area_to_last_clickable_region(small_button, jc_text_area);

				list_left_part_group->button_list.push_back(small_button);
				////////////////////////



				////////////////////////
				//big subrow for items
				EButtonGroup* list_main_part_group = EButtonGroup::create_button_group_without_bg (new ERegionGabarite(600.0f, 80.0f), EGUIStyle::active_style);

				list_main_part_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*group_for_items->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				list_main_part_group->stretch_x_by_parent_size = true;
				list_main_part_group->stretch_y_by_parent_size = true;

				list_condition_group_container->add_group(list_main_part_group);

				data_store_target_group->target_group = list_main_part_group;
				////////////////////////


				std::vector <EDataEntity*> suitable_data_entity;
				//regular items
				//button item
				list_condition_group_container->min_size_y = 20.0f;
				if (r == 0)
				{
					list_condition_group_container->min_size_y = 120.0f;

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
						jc_button = EntityButton::create_wide_item_button
						(
							new ERegionGabarite(200.0f, 40.0f),
							list_main_part_group,
							suitable_data_entity[selected_data_entity],
							EFont::font_list[0]
						);
						Entity::get_last_text_area(jc_button)->stored_color.set_color_RGBA(1.0f, 0.9f, 0.5f, 1.0f);

						list_main_part_group->button_list.push_back(jc_button);


					}
				}

				//base class
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
							new ERegionGabarite(200.0f, 40.0f),
							list_main_part_group,
							suitable_data_entity[selected_data_entity],
							EFont::font_list[0]
						);
						Entity::get_last_text_area(jc_button)->stored_color.set_color_RGBA(0.5f, 1.0f, 0.5f, 1.0f);

						list_main_part_group->button_list.push_back(jc_button);


					}
				}

				//influences
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
									new ERegionGabarite(200.0f, 40.0f),
									list_main_part_group,
									suitable_data_entity[k],
									EFont::font_list[0]
								);
								Entity::get_last_text_area(jc_button)->stored_color.set_color_RGBA(1.0f, 0.6f, 0.5f, 1.0f);

								list_main_part_group->button_list.push_back(jc_button);
							}
						}
				}
			}
			





			std::string decorative_element_name[3] = { "���� ����","���� ������","���� �����" };
			//####### COSMETIC SEGMENT #######
			//block
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
				EButtonGroup* cosmetic_segment = EButtonGroup::create_default_button_group(new ERegionGabarite(256.0f, 160.0f), EGUIStyle::active_style);
				

				cosmetic_segment->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
				//*massive_game_item->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

				cosmetic_segment->stretch_x_by_parent_size = false;
				cosmetic_segment->stretch_y_by_parent_size = true;

				whole_block_data->pointer_to_cosmetic_segment = cosmetic_segment;
				whole_filter_block_group->add_group(cosmetic_segment);

				for (int clr = 0; clr < 3; clr++)
				if (rand() % 3 == 0)
				{
				// // // // // // //// // // // // // //// // // // // // //
				Helper::HRA_color_collection*	HRA_collection = Helper::registered_color_list[rand() % Helper::registered_color_list.size()];
				Helper::HSVRGBAColor*			HRA_color = &HRA_collection->target_color;
				//HRA_color->h = rand() % 360;
				//HRA_color->s = 1.0f - pow((rand() % 100) / 100.0f, 1.0);
				//HRA_color->v = 1.0f - pow((rand() % 100) / 100.0f, 3.0);
				//HRA_color->a = 1.0f - pow((rand() % 100) / 100.0f, 4.0);

				jc_button = EntityButton::create_named_color_button
				(
					new ERegionGabarite(242.0f, 38.0f),
					cosmetic_segment,
					EFont::font_list[0],
					EGUIStyle::active_style,
					decorative_element_name[clr],
					HRA_collection,
					HRA_color,
					ColorButtonMode::CBM_OPEN_WINDOW
				);
				//EntityButton::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_transfer_pointer_to_color_data_container);
				//EntityButton::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_button);

				cosmetic_segment->button_list.push_back(jc_button);
			}
				// // // // // // //// // // // // // //// // // // // // //
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}



		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}

	//skill gems
	if (false)
	{
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(10.0f, 10.0f, 0.0f, 512.0f, 800.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		jc_button_group = main_button_group->add_group(EButtonGroup::create_default_button_group(new ERegionGabarite(256.0f, 150.0f), EGUIStyle::active_style));
		jc_button_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = true;

		std::vector <EDataEntity*> suitable_data_entity_list;
		for (EDataEntity* de : EDataEntity::data_entity_list)
		{
			if
				(
					EStringUtils::to_lower(DataEntityUtils::get_tag_value_by_name(0, "data type", de))
					==
					"gem"
				)
			{
				suitable_data_entity_list.push_back(de);
			}
		}

		for (int i = 0; i < 6; i++)
		{
			jc_button = EntityButton::create_wide_item_button
			(
				new ERegionGabarite(480.0f, 64.0f),
				jc_button_group,
				suitable_data_entity_list[rand() % suitable_data_entity_list.size()],
				EFont::font_list[1]
			);
			jc_button_group->button_list.push_back(jc_button);
			//Entity::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_open_data_entity_filter_group);


			EDataContainerStoreTargetGroup* data_container_entity_filter = new EDataContainerStoreTargetGroup();
			data_container_entity_filter->target_group = EButtonGroup::data_entity_filter;
			data_container_entity_filter->filter_rule = EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_SKILL_GEMS];

			ECustomData* custom_data_for_gem_button = new ECustomData();
			custom_data_for_gem_button->data_container = data_container_entity_filter;

			EClickableArea* clickable_area_for_gem_button = EClickableArea::create_default_clickable_region(jc_button->button_gabarite, jc_button, custom_data_for_gem_button);
			clickable_area_for_gem_button->actions_on_click_list.push_back(&EDataActionCollection::action_open_data_entity_filter_group);
			custom_data_for_gem_button->clickable_area_list.push_back(clickable_area_for_gem_button);


			jc_button->custom_data_list.push_back(custom_data_for_gem_button);
		}

		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);



	}

	//STYLE LIST BUTTON GROUP
	if (true)
	{
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(400.0f, 300.0f, 0.0f, 410.0f, 600.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		main_button_group->can_be_stretched_by_child = false;

		//main_button_group->add_close_group_and_return_workspace_group(new ERegionGabarite(100.0f, 40.0f), EGUIStyle::active_style);
		//*main_button_group->can_change_style = false;

		EButtonGroup* worspace_group = main_button_group->add_close_group_and_return_workspace_group(new ERegionGabarite(100.0f, 20.0f), EGUIStyle::active_style);;
		worspace_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		worspace_group->stretch_x_by_parent_size = true;
		worspace_group->stretch_y_by_parent_size = true;


		float horizontal_side = 350.0f;
		float max_size_x = 0.0f;

		for (EGUIStyle* style : EGUIStyle::style_list)
		{
			max_size_x = max(max_size_x, horizontal_side + 20.0f);
		}
		for (EGUIStyle* style : EGUIStyle::style_list)
			//EGUIStyle* style = EGUIStyle::style_list[0];
		{
			


			//group with constant style
			EButtonGroup*
			style_group = worspace_group->add_group
			(EButtonGroup::create_root_button_group(new ERegionGabarite(max_size_x, 20.0f), style));
			style_group->can_resize_to_workspace_size = false;
			style_group->can_be_stretched_by_child = true;

			style_group->stretch_x_by_parent_size = false;
			style_group->stretch_y_by_parent_size = false;

			*style_group->can_change_style = false;




			//group for prewiev button
			EButtonGroup* buttons_simulator = style_group->add_group
			(EButtonGroup::create_default_button_group(new ERegionGabarite(horizontal_side, 100.0f), style));
			buttons_simulator->stretch_x_by_parent_size = false;
			buttons_simulator->stretch_y_by_parent_size = false;

			if (buttons_simulator != nullptr)
			{
				*buttons_simulator->can_change_style = false;

				for (int i = 0; i < 17; i++)
				{

					jc_button = EntityButton::create_default_clickable_button
					(
						new ERegionGabarite(40.0f, 40.0f),
						buttons_simulator,
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

					buttons_simulator->button_list.push_back(jc_button);
				}

			}

			//subrow small (for button "select")
			/*jc_button_group_row = EButtonGroup::add_default_row_to_group
			(
				jc_button_group, new ERegionGabarite
				(horizontal_side, 30.0f)
			);*/



			//group (for button "select")
			jc_button_group = style_group->add_group
			(
				EButtonGroup::create_default_button_group
				(new ERegionGabarite(horizontal_side, 24.0f), style)
			);

			jc_button_group->stretch_x_by_parent_size = false;
			jc_button_group->stretch_y_by_parent_size = false;

			//select button
			if (jc_button_group != nullptr)
			{

				*jc_button_group->can_change_style = false;

				jc_button = EntityButton::create_default_clickable_button
				(
					new ERegionGabarite
					(
						horizontal_side,
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

		



		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}

	//DATA ENTITY
	if (true)
	{
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(900.0f, 100.0f, 0.0f, 900.0f, 600.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		EButtonGroup::data_entity_filter = main_button_group;
		

		EDataContainer_Group_DataEntitiesSearch* jc_data_container_for_search_group = new EDataContainer_Group_DataEntitiesSearch();
		main_button_group->data_container = jc_data_container_for_search_group;
		main_button_group->is_active = false;

		DataEntityFilter* data_entity_filter = new DataEntityFilter();
			data_entity_filter->target_tag_name		= "data type";
			data_entity_filter->suitable_values_list.push_back("game item");

		EFilterRule* jc_filter_rule = new EFilterRule();
		jc_filter_rule->required_tag_list.push_back(data_entity_filter);

		jc_data_container_for_search_group->target_rule = new EFilterRule();

		// // //	DATA ENTITY LIST	// // //
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 480.0f), EGUIStyle::active_style));
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = true;
		jc_data_container_for_search_group->pointer_to_group_with_data_entities = jc_button_group;
		jc_button_group->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		unsigned int counter = 0;
		for (EDataEntity* data_entity : EDataEntity::data_entity_list)
		{
			
			jc_button = EntityButton::create_wide_item_button
			(
				new ERegionGabarite(270.0f, 64.0f),
				jc_button_group,
				data_entity,
				EFont::font_list[0]
			);

			jc_button->pointer_to_data_entity = data_entity;

			
			jc_button_group->button_list.push_back(jc_button);

			counter++;
		}

		//search bar group
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 50.0f), EGUIStyle::active_style));
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = false;

		jc_button = EntityButton::create_default_clickable_button
		(
			new ERegionGabarite(800.0f, 25.0f),
			jc_button_group,
			nullptr
		);
		jc_data_container_for_search_group->pointer_to_search_bar = jc_button;

		jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "Chaos orb");
		jc_data_container_for_search_group->filter_text_area = jc_text_area;
		jc_text_area->action_on_change_text.push_back(&EDataActionCollection::action_type_text);
		Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
		jc_button_group->button_list.push_back(jc_button);

		



		EDataActionCollection::action_type_text(jc_text_area);

		


		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}

	//world parameters
	if (true)
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////		world parameter		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(400.0f, 100.0f, 0.0f, 400, 600.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		//*----------------------------		SUN SECTION		-------------------------------------------------------*//
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 100.0f), EGUIStyle::active_style));
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = false;

		// // // // // // //// // // // // // //// // // // // // //
		jc_button = EntityButton::create_vertical_named_slider
		(

			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			EFont::font_list[0],
			EGUIStyle::active_style,
			"������"
		);
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::global_gloss_multiplier;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 4.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //

		// // // // // // //// // // // // // //// // // // // // //
		jc_button = EntityButton::create_vertical_named_slider
		(

			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			EFont::font_list[0],
			EGUIStyle::active_style,
			"�������"
		);
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::global_normal_multiplier;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 2.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //






		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		//*----------------------------		SUN SECTION		-------------------------------------------------------*//
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		EButtonGroup* button_group_sun_main = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 250.0f), EGUIStyle::active_style));
		button_group_sun_main->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		button_group_sun_main->stretch_x_by_parent_size = true;
		button_group_sun_main->stretch_y_by_parent_size = false;
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//

		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = button_group_sun_main->add_group(EButtonGroup::create_default_button_group(new ERegionGabarite(160.0f, 160.0f), EGUIStyle::active_style));
		jc_button_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		jc_button_group->stretch_x_by_parent_size = false;
		jc_button_group->stretch_y_by_parent_size = true;
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//

		// // // // // // //
		jc_button = EntityButton::create_default_crosshair_slider
		(
			new ERegionGabarite(148.0f, 148.0f),
			jc_button_group,
			&NS_EGraphicCore::sun_x,
			&NS_EGraphicCore::sun_y,
			"skydome"
		);

		EDataContainer_CrosshairSlider* crosshair_data = (EDataContainer_CrosshairSlider*)EntityButton::get_last_custom_data(jc_button)->data_container;
		crosshair_data->min_x = 0.0f;
		crosshair_data->max_x = 1.0f;

		crosshair_data->min_y = 0.0f;
		crosshair_data->max_y = 1.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //

		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = button_group_sun_main->add_group(EButtonGroup::create_default_button_group(new ERegionGabarite(160.0f, 160.0f), EGUIStyle::active_style));
		jc_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = true;
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//

		// // // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			"������:"
		);
		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::sun_size;
		*((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // // //

		// // // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			"���������:"
		);
		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::sun_blur;
		*((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // // //
		// 
		// // // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			"�������:"
		);
		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::sun_bright;
		*((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 100.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // // //
		
		// // // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			"�������:"
		);
		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::sun_exp;
		*((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 10.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // // //
		
		// // // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			"������� ���������:"
		);
		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::sun_flat_decay;
		*((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // // //
		
		// // // // // // // //
		jc_button = EntityButton::create_named_color_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			EFont::font_list[0],
			EGUIStyle::active_style,
			"���� ������",
			nullptr,
			&NS_EGraphicCore::sun_color,
			ColorButtonMode::CBM_OPEN_WINDOW
		);

		jc_button_group->button_list.push_back(jc_button);



		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		//*----------------------------		SKYDOME SECTION		-------------------------------------------------------*//
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 100.0f), EGUIStyle::active_style));
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = false;
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//

		// // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			"������� ������:"
		);
		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::ground_level;
		*((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //

		// // // // // // //
		jc_button = EntityButton::create_default_radial_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			"�������� ��������:"
		);
		((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->value_pointer = &NS_EGraphicCore::move_multiplier;
		*((EDataContainerRadialButton*)EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 10.0f;
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //

		// // // // // // //// // // // // // //// // // // // // //
		jc_button = EntityButton::create_vertical_named_slider
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			EFont::font_list[0],
			EGUIStyle::active_style,
			"������� ���� ����"
		);
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::global_free_sky_light_multiplier;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 2.0f;
		//EntityButton::get_last_custom_data(jc_button)->actions_on_update.push_back(&EDataActionCollection::action_force_resize_callback);
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //

		// // // // // // //// // // // // // //// // // // // // //
		jc_button = EntityButton::create_vertical_named_slider
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			EFont::font_list[0],
			EGUIStyle::active_style,
			"������� ���������"
		);
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::global_reflection_multiplier;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 2.0f;
		//EntityButton::get_last_custom_data(jc_button)->actions_on_update.push_back(&EDataActionCollection::action_force_resize_callback);
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //
		

		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		//*----------------------------		INTERFACE SECTION		-----------------------------------------------*//
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 100.0f), EGUIStyle::active_style));
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = false;
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		// // // // // // //// // // // // // //// // // // // // //
		jc_button = EntityButton::create_vertical_named_slider
		(

			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			EFont::font_list[0],
			EGUIStyle::active_style,
			"���"
		);
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::current_zoom;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 2.0f;
		EntityButton::get_last_custom_data(jc_button)->actions_on_update.push_back(&EDataActionCollection::action_force_resize_callback);
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //

		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}


	//color editor
	if (true)
	{
		main_button_group = EButtonGroup::create_color_editor_group(new ERegionGabarite(200.0f, 200.0f, 980.0f, 380.0f), EGUIStyle::active_style);
		main_button_group->root_group = main_button_group;
		main_button_group->is_active = false;
		EButtonGroup::color_editor_group = main_button_group;
		//main_button_group->can_be_moved = true;

		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
		
		
	}

	//add content to filter block group
	if (true)
	{
		EButtonGroup*
		add_content_group = EButtonGroup::create_root_button_group(new ERegionGabarite(100.0f, 100.0f, 900.0f, 400.0f), EGUIStyle::active_style);
		add_content_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		add_content_group->stretch_x_by_parent_size = false;
		add_content_group->stretch_y_by_parent_size = false;

		EButtonGroup::add_content_to_filter_block_group = add_content_group;
		add_content_group->is_active = false;

		EDataContainer_Group_AddContentToFilterBlock* content_group_data_container = new EDataContainer_Group_AddContentToFilterBlock();
		add_content_group->data_container = content_group_data_container;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		EButtonGroup* workspace_group
		=
		add_content_group->add_close_group_and_return_workspace_group(new ERegionGabarite(10.0f, 20.0f), EGUIStyle::active_style);
		workspace_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		EButtonGroup* content_list_group
		=
		workspace_group->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(10.0f, 10.0f),
				EGUIStyle::active_style
			)
		);
		content_list_group->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		EButtonGroup* search_bar_group
		=
		workspace_group->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(10.0f, 30.0f),
				EGUIStyle::active_style
			)
		);
		search_bar_group->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		jc_button = EntityButton::create_default_clickable_button_with_text
		(
			new ERegionGabarite(800.0f, 30.0f),
			search_bar_group,
			nullptr,
			""
		);

		//add pointer to clickable are in "add content to filter block group"
		content_group_data_container->typing_text_area	= EntityButton::get_last_text_area(jc_button);

		auto multi_search_data_container				= new EDataContainer_Button_MultiGroupButtonSearcher();

		Entity::get_last_custom_data(jc_button)->data_container = multi_search_data_container;
		Entity::get_last_clickable_area(jc_button)->text_area->action_on_change_text.push_back(&EDataActionCollection::action_type_text_multiblock_searcher);

		search_bar_group->button_list.push_back(jc_button);
		search_bar_group->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_static_autosize);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		EButtonGroup*
		filter_block_operation_segment
		=
		content_list_group->add_group
		(
			EButtonGroup::create_default_button_group (new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
			->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
		);
		filter_block_operation_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(160.0f, 20.0f), filter_block_operation_segment, nullptr, "�������� ����� ����");
		filter_block_operation_segment->button_list.push_back(jc_button);

		//jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(160.0f, 20.0f), filter_block_operation_segment, nullptr, "����������� ���� ����");
		//filter_block_operation_segment->button_list.push_back(jc_button);

		///
		EButtonGroup*
		non_listed_segment
		=
		content_list_group->add_group
		(
			EButtonGroup::create_default_button_group (new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
			->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
		);
		non_listed_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;


		///
		EButtonGroup*
		listed_segment
		=
		content_list_group->add_group
		(
			EButtonGroup::create_default_button_group (new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
			->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
		);
		listed_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		///
		EButtonGroup*
		cosmetic_segment
		=
		content_list_group->add_group
		(
			EButtonGroup::create_default_button_group (new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
			->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
		);
		cosmetic_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		multi_search_data_container->target_group_list.push_back(content_list_group);
		multi_search_data_container->target_group_list.push_back(non_listed_segment);
		multi_search_data_container->target_group_list.push_back(listed_segment);
		multi_search_data_container->target_group_list.push_back(cosmetic_segment);

		EButtonGroup* target_group = nullptr;
		for (FilterBlockAttribute* fba : registered_filter_block_attributes)
		{
			EDataContainer_Button_AddContentToFilterBlock* add_content_data = new EDataContainer_Button_AddContentToFilterBlock();
			add_content_data->target_attribute = fba;

			if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED)	{ target_group = non_listed_segment; }
			if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED)		{ target_group = listed_segment; }
			if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)		{ target_group = cosmetic_segment; }

			jc_button = EntityButton::create_default_clickable_button_with_unedible_text
			(
				new ERegionGabarite(160.0f, 30.0f),
				target_group,
				&EDataActionCollection::action_add_selected_content_to_filter_block,
				fba->localisation.localisations[NSW_localisation_EN]
			);

			EntityButton::get_last_custom_data(jc_button)->data_container = add_content_data;
			
			//set localisations to text area
			EntityButton::get_last_clickable_area(jc_button)->text_area->localisation_text = fba->localisation;

			target_group->button_list.push_back(jc_button); 

		}



		button_group_list.push_back(add_content_group);
		EButtonGroup::refresh_button_group(add_content_group);
	}

	//rarity selector
	if (true)
	{
		EButtonGroup* whole_rarity_list_group = EButtonGroup::create_root_button_group(new ERegionGabarite(100.0f, 120.0f), EGUIStyle::active_style);
		EButtonGroup* workspace_rarity_group = whole_rarity_list_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), EGUIStyle::active_style);
		workspace_rarity_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		select_rarity_button_group = whole_rarity_list_group;

		auto data_text_selector = new EDataContainer_Group_TextSelectorFromVariants();
		whole_rarity_list_group->data_container = data_text_selector;

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(100.0f, 20.0f), workspace_rarity_group, &EDataActionCollection::action_select_this_text_variant, "�������");
		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 1.0f, 1.0f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(100.0f, 20.0f), workspace_rarity_group, &EDataActionCollection::action_select_this_text_variant, "����������");
		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(0.4f, 0.5f, 1.0f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(100.0f, 20.0f), workspace_rarity_group, &EDataActionCollection::action_select_this_text_variant, "������");
		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 1.0f, 0.25f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(100.0f, 20.0f), workspace_rarity_group, &EDataActionCollection::action_select_this_text_variant, "����������");
		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 0.50f, 0.25f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		button_group_list.push_back(whole_rarity_list_group);
		EButtonGroup::refresh_button_group(whole_rarity_list_group);

		whole_rarity_list_group->is_active = false;
	}
	
	//quality selector
	if (true)
	{
		EButtonGroup* whole_quality_list_group = EButtonGroup::create_root_button_group(new ERegionGabarite(100.0f, 120.0f), EGUIStyle::active_style);
		EButtonGroup* workspace_quality_group = whole_quality_list_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), EGUIStyle::active_style);
		workspace_quality_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		select_quality_button_group = whole_quality_list_group;

		auto data_text_selector = new EDataContainer_Group_TextSelectorFromVariants();
		whole_quality_list_group->data_container = data_text_selector;

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(100.0f, 20.0f), workspace_quality_group, &EDataActionCollection::action_select_this_text_variant, "����������");
		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 0.8f, 0.8f, 1.0f);
		workspace_quality_group->button_list.push_back(jc_button);

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(100.0f, 20.0f), workspace_quality_group, &EDataActionCollection::action_select_this_text_variant, "�����������");
		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(0.8f, 1.0f, 0.8f, 1.0f);
		workspace_quality_group->button_list.push_back(jc_button);

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(100.0f, 20.0f), workspace_quality_group, &EDataActionCollection::action_select_this_text_variant, "���������");
		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(0.8f, 0.8f, 1.0f, 1.0f);
		workspace_quality_group->button_list.push_back(jc_button);

		button_group_list.push_back(whole_quality_list_group);
		EButtonGroup::refresh_button_group(whole_quality_list_group);

		whole_quality_list_group->is_active = false;
	}


}

void EWindowMain::register_filter_rules()
{
	EFilterRule* jc_filter_rule = nullptr;
	DataEntityFilter* jc_filter = nullptr;


	//game items
	jc_filter_rule = new EFilterRule();
	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM] = jc_filter_rule;

	//base class
	jc_filter_rule = new EFilterRule();
	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("base class");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_BASE_CLASS] = jc_filter_rule;

	//influence
	jc_filter_rule = new EFilterRule();
	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("influence");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_INFLUENCE] = jc_filter_rule;

	//gem
	jc_filter_rule = new EFilterRule();
	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("gem");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_SKILL_GEMS] = jc_filter_rule;

	//explicit
	jc_filter_rule = new EFilterRule();
	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("explicit");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS] = jc_filter_rule;
}

EWindowMain::~EWindowMain()
{

}

void EDataActionCollection::action_open_add_content_window(Entity* _entity, ECustomData* _custom_data, float _d)
{
		EButtonGroup::add_content_to_filter_block_group->is_active = true;

		//_custom_data
		EDataContainer_Button_OpenButtonGroup*			button_plus_data			= static_cast<EDataContainer_Button_OpenButtonGroup*>			(_custom_data->data_container);
		EDataContainer_Group_WholeFilterBlock*			whole_filter_block_data		= static_cast<EDataContainer_Group_WholeFilterBlock*>			(button_plus_data->master_group->data_container);
		EDataContainer_Group_AddContentToFilterBlock*	add_content_block_data		= static_cast<EDataContainer_Group_AddContentToFilterBlock*>	(EButtonGroup::add_content_to_filter_block_group->data_container);
		ETextArea*										typing_text_area			= add_content_block_data->typing_text_area;
		
		typing_text_area->change_text("");
		typing_text_area->outclick_protection = true;
		//for ()

		for (text_actions_pointer dap : typing_text_area->action_on_change_text) if (dap != nullptr) { dap(typing_text_area); }
		//typing_text_area->activate_this_text_area();

		{ add_content_block_data->target_filter_block = button_plus_data->master_group; }

		//if (taget_group_for_content != nullptr) { taget_group_for_content->button_list.clear(); }
}

void EDataActionCollection::action_add_selected_content_to_filter_block(Entity* _entity, ECustomData* _custom_data, float _d)
{

		EDataContainer_Button_AddContentToFilterBlock* button_content_data = static_cast<EDataContainer_Button_AddContentToFilterBlock*>	(_custom_data->data_container);


		EDataContainer_Group_AddContentToFilterBlock*	add_content_group_data			= static_cast<EDataContainer_Group_AddContentToFilterBlock*>	(EButtonGroup::add_content_to_filter_block_group->data_container);
		EButtonGroup*									whole_button_group				= add_content_group_data->target_filter_block;

		EDataContainer_Group_WholeFilterBlock*			whole_filter_block_data			= static_cast<EDataContainer_Group_WholeFilterBlock*>			(whole_button_group->data_container);
		EDataContainer_Button_AddContentToFilterBlock*	add_content_button_data			= static_cast<EDataContainer_Button_AddContentToFilterBlock*>	(_custom_data->data_container);

		EButtonGroup* target_group_for_content = nullptr;

		EntityButton* jc_button = nullptr;

		add_non_listed_buttons_to_filter_block(whole_button_group, add_content_button_data->target_attribute);

		//if (taget_group_for_content != nullptr)
		//{ 
		//	*taget_group_for_content->is_active = false; 
		//}

		if (!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
		{
			EButtonGroup::add_content_to_filter_block_group->is_active = false;
		}

}

void EDataActionCollection::action_open_rarity_selector(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EWindowMain::select_rarity_button_group->is_active = true;

	static_cast<EDataContainer_Group_TextSelectorFromVariants*>(EWindowMain::select_rarity_button_group->data_container)->target_button = static_cast<EntityButton*>(_entity);
	//reg
	EWindowMain::select_rarity_button_group->region_gabarite->offset_x = static_cast<EntityButton*>(_entity)->button_gabarite->world_position_x;
	EWindowMain::select_rarity_button_group->region_gabarite->offset_y = static_cast<EntityButton*>(_entity)->button_gabarite->world_position_y + static_cast<EntityButton*>(_entity)->button_gabarite->size_y + 3.0f;

	EButtonGroup::refresh_button_group(EWindowMain::select_rarity_button_group);
}

void EDataActionCollection::action_open_quality_selector(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EWindowMain::select_quality_button_group->is_active = true;

	static_cast<EDataContainer_Group_TextSelectorFromVariants*>(EWindowMain::select_quality_button_group->data_container)->target_button = static_cast<EntityButton*>(_entity);
	//reg
	EWindowMain::select_quality_button_group->region_gabarite->offset_x = static_cast<EntityButton*>(_entity)->button_gabarite->world_position_x;
	EWindowMain::select_quality_button_group->region_gabarite->offset_y = static_cast<EntityButton*>(_entity)->button_gabarite->world_position_y + static_cast<EntityButton*>(_entity)->button_gabarite->size_y + 3.0f;

	EButtonGroup::refresh_button_group(EWindowMain::select_quality_button_group);
}

//create group of buttons to filter block.
//usually, group include next buttons:
//1) attribute name ("rarity", "ItemLevel", "BaseClass", ...)
//2) comparison operator, if need ("<=", "=", ">=")
//3) value
//4) remove button
void add_non_listed_buttons_to_filter_block(EButtonGroup* _target_filter_block, FilterBlockAttribute* _filter_block_attribute)
{
	float button_height = 22.0f;
	//filter block have 4 sectors
	//1) control
	//2) non_listed
	//3) listed
	//4) cosmetic
	//
	//EDataContainer_Group_WholeFilterBlock store pointers to each segemnt
	auto whole_filter_block_data = static_cast<EDataContainer_Group_WholeFilterBlock*>(_target_filter_block->data_container);

	EntityButton* jc_button;

	std::string temp_rarity[] = { "����������", "����������", "������", "����������" };
	EButtonGroup* target_group_for_content;

	Helper::HSVRGBAColor rarity_color[4];

	Helper::HSVRGBAColor temp_color;

	//normal
	temp_color.set_color_RGBA(1.0f, 1.0f, 1.0f, 1.0f);
	rarity_color[0] = temp_color;

	//magic
	temp_color.set_color_RGBA(0.5f, 0.6f, 1.0f, 1.0f);
	rarity_color[1] = temp_color;

	//rare
	temp_color.set_color_RGBA(1.0f, 1.0f, 0.25f, 1.0f);
	rarity_color[2] = temp_color;

	//rauniquere
	//unique
	temp_color.set_color_RGBA(1.0f, 0.5f, 0.250f, 1.0f);
	rarity_color[3] = temp_color;

	//if selected content is non-listed
	if (_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED)
	{
		target_group_for_content = whole_filter_block_data->pointer_to_non_listed_segment;

		EButtonGroup* non_listed_line =
			EButtonGroup::create_invisible_button_group
			(
				new ERegionGabarite(20.0f, button_height),
				EGUIStyle::active_style
			)
			->
			set_parameters
			(
				ChildAlignMode::ALIGN_VERTICAL,
				NSW_dynamic_autosize,
				NSW_static_autosize
			);
		non_listed_line->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		//EInputCore::logger_simple_info("create fresh block");
		FreshCreatedGroup* fresh_created_group = new FreshCreatedGroup();
		fresh_created_group->target_group = whole_filter_block_data->pointer_to_non_listed_segment;
		fresh_created_group->just_created_group = non_listed_line;
		EButtonGroup::fresh_created_block_list.push_back(fresh_created_group);
		//EInputCore::logger_param("size", EButtonGroup::fresh_created_block_list.size());

		auto non_listed_line_data = new EDataContainer_Group_FilterBlockNonListedSegment();
		non_listed_line->data_container = non_listed_line_data;

		//target_group_for_content->add_group(non_listed_line);
		//non_listed_line->parent_group = target_group_for_content;

		jc_button = EntityButton::create_default_clickable_button_with_unedible_text
		(
			new ERegionGabarite(160.0f, button_height),
			non_listed_line,
			nullptr,
			_filter_block_attribute->localisation.localisations[0]
		);
		non_listed_line->button_list.push_back(jc_button);

		float input_field_additional_width = 0.0f;
		//condition operator
		if (_filter_block_attribute->have_operator)
		{
			jc_button = EntityButton::create_default_clickable_button_with_text
			(
				new ERegionGabarite(20.0f, button_height),
				non_listed_line,
				nullptr,
				"="
			);
			non_listed_line->button_list.push_back(jc_button);

			
		}
		else
		{
			input_field_additional_width = 20.0f + DISTANCE_BETWEEN_BUTTONS;
		}

		srand(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

		//EInputCore::logger_param("current time", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		int rarity_id = rand() % 4;

		std::string text = std::to_string(rand() % 100 + 1);
		if (_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST)
		{

			text = temp_rarity[rarity_id];

			jc_button = EntityButton::create_default_clickable_button_with_unedible_text
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				&EDataActionCollection::action_open_rarity_selector,
				text
			);

			EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(&rarity_color[rarity_id]);
		}
		else
		if (_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST)
		{
			text = "����������";

			jc_button = EntityButton::create_default_clickable_button_with_unedible_text
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				&EDataActionCollection::action_open_quality_selector,
				text
			);
		}
		else
		{
			jc_button = EntityButton::create_default_clickable_button_with_text
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				nullptr,
				text
			);
		}



		non_listed_line->button_list.push_back(jc_button);

		jc_button = EntityButton::create_default_clickable_button_with_icon
		(
			new ERegionGabarite(button_height, button_height),
			non_listed_line,
			&EDataActionCollection::action_mark_parent_group_as_removed,
			NS_EGraphicCore::load_from_textures_folder("button_close")
		);

		non_listed_line->button_list.push_back(jc_button);
		//EButtonGroup::change_group(target_group_for_content);

		/*if (j == 0) { jc_region_gabarite = new ERegionGabarite(100.0f, 20.0f); }
		else
			if (j == 1) { jc_region_gabarite = new ERegionGabarite(20.0f, 20.0f); }
			else
				if (j == 2) { jc_region_gabarite = new ERegionGabarite(50.0f, 20.0f); }*/
	}


	if (_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED)
	{
		target_group_for_content = whole_filter_block_data->pointer_to_listed_segment;

		EButtonGroup*	listed_condition_group_container = EButtonGroup::create_default_button_group(new ERegionGabarite(800.0f, 100.0f), EGUIStyle::active_style);
						listed_condition_group_container->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		//*massive_game_item->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

						listed_condition_group_container->stretch_x_by_parent_size = true;
						listed_condition_group_container->stretch_y_by_parent_size = true;

		target_group_for_content->add_group(listed_condition_group_container);
		

		////////////////////////
		//small subrow for additional buttons

		//side group for buttons
		EButtonGroup* list_left_part_group = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(134.0f, 80.0f), EGUIStyle::active_style);
		listed_condition_group_container->add_group(list_left_part_group);
		//row_game_item->add_group(group_side);
		list_left_part_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		//*group_side->stretch_mode		= GroupStretchMode::STRETCHED_ONLY_BY_PARENT;

		list_left_part_group->stretch_x_by_parent_size = false;
		list_left_part_group->stretch_y_by_parent_size = true;

		float vertical_borders = list_left_part_group->border_left + list_left_part_group->border_right;

		//add new button
		EntityButton*
			small_button = EntityButton::create_default_clickable_button_with_unedible_text
			(
				new ERegionGabarite(130.0f, 18.0f),
				list_left_part_group,
				&EDataActionCollection::action_open_data_entity_filter_group,
				"Add new item"
			);

		EDataContainerStoreTargetGroup*	data_store_target_group = new EDataContainerStoreTargetGroup();
										data_store_target_group->filter_rule = _filter_block_attribute->filter_rule;

		//game item
		{ data_store_target_group->target_action_on_click = &EDataActionCollection::action_add_wide_item_to_group_receiver; }
		EntityButton::get_last_custom_data(small_button)->data_container = data_store_target_group;
		list_left_part_group->button_list.push_back(small_button);

		//remove all buttons
		small_button = EntityButton::create_default_clickable_button_with_unedible_text
		(new ERegionGabarite(130.0f, 18.0f), list_left_part_group, nullptr, "remove block");
		list_left_part_group->button_list.push_back(small_button);
		////////////////////////



		////////////////////////
		//big subrow for items
		EButtonGroup* list_main_part_group = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(600.0f, 80.0f), EGUIStyle::active_style);

		list_main_part_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		//*group_for_items->stretch_mode		= GroupStretchMode::STRETCHED_FILL_VOID;

		list_main_part_group->stretch_x_by_parent_size = true;
		list_main_part_group->stretch_y_by_parent_size = true;

		listed_condition_group_container->add_group(list_main_part_group);

		data_store_target_group->target_group = list_main_part_group;

		EButtonGroup::change_group(target_group_for_content);
	}


	if (_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)	{ target_group_for_content = whole_filter_block_data->pointer_to_cosmetic_segment; }


}
