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
#include <windows.h>
#include <Lmcons.h>
#include <shlobj.h>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

//class Entity;
EWindowMain* EWindowMain::link_to_main_window;

EButtonGroup* EWindowMain::select_rarity_button_group;
EButtonGroup* EWindowMain::select_quality_button_group;
EButtonGroup* EWindowMain::loot_filter_editor;



std::string		EWindowMain::username;
std::string		EWindowMain::path_of_exile_folder;

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
	EntityButton* clicked_button = static_cast<EntityButton*>(_entity);
	ETextArea* clicked_button_text_area = EntityButton::get_last_clickable_area(clicked_button)->text_area;

	EButtonGroup* root_group = clicked_button->parent_button_group->root_group;
	EDataContainer* root_container = root_group->data_container;


	ETextArea* target_text_area = EntityButton::get_last_clickable_area(static_cast<EDataContainer_Group_TextSelectorFromVariants*>(root_container)->target_button)->text_area;

	target_text_area->localisation_text = clicked_button_text_area->localisation_text;
	//*target_text_area->stored_text = *EntityButton::get_last_clickable_area(static_cast<EntityButton*>(_entity))->text_area->stored_text;

	//transfer parameters from [select rarity button] to [non-listed button]
	target_text_area->stored_color = clicked_button_text_area->stored_color;
	target_text_area->color = clicked_button_text_area->color;
	target_text_area->localisation_text = clicked_button_text_area->localisation_text;

	target_text_area->change_text(*clicked_button_text_area->stored_text);

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

void EDataActionCollection::action_generate_filter_block_text(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//const char* output = (*_custom_data->clickable_area_list.back()->text_area->stored_text).c_str();
	std::string str = "";

	EButtonGroup* filter_block_massive = static_cast<EDataContainer_Button_StoreParentFilterBlock*>(_custom_data->data_container)->parent_filter_block->root_group;
	for (EButtonGroup* group : filter_block_massive->group_list)
	{
		str += generate_filter_block_text(group);
		str += '\n';
	}

	const char* output = str.c_str();
	const size_t len = strlen(output) + 1;

	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);

	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

void EDataActionCollection::action_select_this_filter_variant(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EDataContainer_Group_DataEntitiesSearch* button_group_data_container = (EDataContainer_Group_DataEntitiesSearch*)EButtonGroup::data_entity_filter->data_container;

	//if (EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{
		EntityButtonFilterRule* filter_button = (EntityButtonFilterRule*)_entity;

		//std::cout << filter_button->target_data_container->target_rule << std::endl;

		//filter_button->target_data_container->target_rule = filter_button->target_filter_rule;
		button_group_data_container->target_rule = filter_button->target_filter_rule;

		filter_button->parent_button_group->selected_button = filter_button;
	}
	//else
	//{
	//	button_group_data_container->target_rule = EFilterRule::registered_filter_rules_for_list[0];
	//}
	//static_cast<EntityButtonFilterRule*> 
	EDataActionCollection::action_type_search_data_entity_text(button_group_data_container->filter_text_area);

}

void EDataActionCollection::action_open_loot_filters_list_window(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//for (EButtonGroup* group : EWindowMain::loot_filter_editor->group_list)
	//{
	//	group->need_remove = true;
	//}





	EButtonGroup::existing_loot_filter_list->is_active = true;
	EButtonGroup::existing_loot_filter_list->move_to_foreground();
	EWindowMain::load_loot_filter_list();
	EButtonGroup::refresh_button_group(EButtonGroup::existing_loot_filter_list);

}

void EDataActionCollection::action_select_this_loot_filter_from_list(Entity* _entity, ECustomData* _custom_data, float _d)
{

	//EWindowMain::loot_filter_editor->need_remove = true;



	for (EButtonGroup* group : EWindowMain::loot_filter_editor->group_list)
	{
		group->need_remove = true;
	}

	EWindowMain::loot_filter_editor->group_list.clear();

	EButtonGroup::existing_loot_filter_list->is_active = false;

	EWindowMain::open_loot_filter(((EntityButtonForLootFilterSelector*)_entity)->full_path);
	EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);

}

void EDataActionCollection::action_add_all_entity_buttons_to_filter_block(Entity* _entity, ECustomData* _custom_data, float _d)
{
	auto data_entity_container = static_cast<EDataContainer_Group_DataEntitiesSearch*>(static_cast<EntityButton*>(_entity)->parent_button_group->root_group->data_container);

	if ((data_entity_container != nullptr) && (data_entity_container->pointer_to_group_with_data_entities != nullptr))
	{
		for (EntityButton* but : data_entity_container->pointer_to_group_with_data_entities->button_list)
			if
				(
					(but != data_entity_container->pointer_to_group_with_data_entities->slider)
					&&
					(!but->disabled)
					&&
					(!but->disable_draw)
					)
			{
				data_entity_container->action_on_select_for_button(but, Entity::get_last_custom_data(but), _d);
			}
	}


}

void EDataActionCollection::action_save_lootfilter(Entity* _entity, ECustomData* _custom_data, float _d)
{
	std::string str = "";

	//EButtonGroup* filter_block_massive = static_cast<EDataContainer_Button_StoreParentFilterBlock*>(_custom_data->data_container)->parent_filter_block->root_group;
	//for (EButtonGroup* group : EWindowMain::loot_filter_editor->group_list)
	//for (int i = EWindowMain::loot_filter_editor->group_list.size() - 1; i >= 0; i--)
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
	{
		str += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[i]);
		str += '\n';
		str += '\n';
	}

	std::ofstream writabro;

	writabro.open(EWindowMain::path_of_exile_folder + "/AwakenedDaDEditor.filter");
	writabro << str;
	writabro.close();
}


EWindowMain::EWindowMain()
{

	//REGISTER USERNAME
	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;

	if (GetUserName(name, &size))
	{
		//std::string zalupa = *(new std::string(name));

		username = EStringUtils::UTF8_to_ANSI(name);
		std::cout << "Hello, " << username << "!\n";
	}
	else
	{
		std::cout << "Hello, unnamed person!\n";
	}

	//DEFINE PATH TO FOLDER WITH LOOT-FILTERS
	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK)
	{
		std::cout << "Error: " << result << "\n";
	}
	else
	{
		/*
		for (int i = 0; i < MAX_PATH; i++)
		{
			cout << "symbol at " << i << "is= " << my_documents[i] << endl;
		}
		*/

		path_of_exile_folder = (std::string)my_documents + "\\My Games\\Path of Exile\\";
		std::cout << "Path to loot-filters folder: " << path_of_exile_folder << "\n";

	}

	register_filter_rules();


	FilterBlockAttribute* jc_filter_block_attribute;
	ELocalisationText		jc_localisation;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ItemLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Item level";
	jc_localisation.localisations[NSW_localisation_RU] = "Уровень предмета";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "DropLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Required level";
	jc_localisation.localisations[NSW_localisation_RU] = "Требуемый уровень";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Quality";
	jc_localisation.localisations[NSW_localisation_EN] = "Quality";
	jc_localisation.localisations[NSW_localisation_RU] = "Качество";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "GemLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Gem level";
	jc_localisation.localisations[NSW_localisation_RU] = "Уровень камня";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SocketGroup";
	jc_localisation.localisations[NSW_localisation_EN] = "Links colours";
	jc_localisation.localisations[NSW_localisation_RU] = "Цвета связей";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Sockets";
	jc_localisation.localisations[NSW_localisation_EN] = "Sockets colours";
	jc_localisation.localisations[NSW_localisation_RU] = "Цвета гнёзд";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "LinkedSockets";
	jc_localisation.localisations[NSW_localisation_EN] = "Linked sockets";
	jc_localisation.localisations[NSW_localisation_RU] = "Связанные гнёзда";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "StackSize";
	jc_localisation.localisations[NSW_localisation_EN] = "Stack size";
	jc_localisation.localisations[NSW_localisation_RU] = "Размер стопки";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "AreaLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Area level";
	jc_localisation.localisations[NSW_localisation_RU] = "Уровень области";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "CorruptedMods";
	jc_localisation.localisations[NSW_localisation_EN] = "Corrupted mods";
	jc_localisation.localisations[NSW_localisation_RU] = "Осквернённые свойства";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Width";
	jc_localisation.localisations[NSW_localisation_EN] = "Width";
	jc_localisation.localisations[NSW_localisation_RU] = "Ширина";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Height";
	jc_localisation.localisations[NSW_localisation_EN] = "Height";
	jc_localisation.localisations[NSW_localisation_RU] = "Высота";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "EnchantmentPassiveNum";
	jc_localisation.localisations[NSW_localisation_EN] = "Passives count";
	jc_localisation.localisations[NSW_localisation_RU] = "Пассивки самоцвета";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "GemQualityType";
	jc_localisation.localisations[NSW_localisation_EN] = "Alternative quality";
	jc_localisation.localisations[NSW_localisation_RU] = "Альтернативное качество";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST;
	jc_filter_block_attribute->have_operator = false;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "BaseDefencePercentile";
	jc_localisation.localisations[NSW_localisation_EN] = "Defence procentile";
	jc_localisation.localisations[NSW_localisation_RU] = "Проценталь защиты";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasSearingExarchImplicit";
	jc_localisation.localisations[NSW_localisation_EN] = "Searing Exarch implicits";
	jc_localisation.localisations[NSW_localisation_RU] = "Свойства Пламенного Экзарха";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasEaterOfWorldsImplicit";
	jc_localisation.localisations[NSW_localisation_EN] = "Eater of Worlds implicits";
	jc_localisation.localisations[NSW_localisation_RU] = "Свойства Пожирателя Миров";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "MapTier";
	jc_localisation.localisations[NSW_localisation_EN] = "Map tier";
	jc_localisation.localisations[NSW_localisation_RU] = "Тир карты";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ItemRarity";
	jc_localisation.localisations[NSW_localisation_EN] = "Item rarity";
	jc_localisation.localisations[NSW_localisation_RU] = "Редкость предмета";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST;
	jc_filter_block_attribute->have_operator = true;
	registered_filter_block_attributes.push_back(jc_filter_block_attribute);








	/*____________________________________LISTED SECTION___________________________________________________*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "BaseType";
	jc_localisation.localisations[NSW_localisation_EN] = "Game item";
	jc_localisation.localisations[NSW_localisation_RU] = "Предмет";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM];

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Class";
	jc_localisation.localisations[NSW_localisation_EN] = "Item class";
	jc_localisation.localisations[NSW_localisation_RU] = "Класс предмета";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_BASE_CLASS];

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasExplicitMod";
	jc_localisation.localisations[NSW_localisation_EN] = "Explicit mode";
	jc_localisation.localisations[NSW_localisation_RU] = "Префикс/суффикс";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS];

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "EnchantmentPassiveNode";
	jc_localisation.localisations[NSW_localisation_EN] = "Cluster passive";
	jc_localisation.localisations[NSW_localisation_RU] = "Пассивки кластера";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_CLUSTER_PASSIVE];

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasInfluence";
	jc_localisation.localisations[NSW_localisation_EN] = "Influence";
	jc_localisation.localisations[NSW_localisation_RU] = "Влияние";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_INFLUENCE];

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasEnchantment";
	jc_localisation.localisations[NSW_localisation_EN] = "Enchantment";
	jc_localisation.localisations[NSW_localisation_RU] = "Зачарование";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_ENCHANTMENT];

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	/*_____________________________________________________________________________________________________*/





	/*____________________________________BOOLEAN SECTION___________________________________________________*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "AnyEnchantment";
	jc_localisation.localisations[NSW_localisation_EN] = "Any enchantment";
	jc_localisation.localisations[NSW_localisation_RU] = "Есть зачарование";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	//jc_filter_block_attribute->filter_rule = EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS];

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "AlternateQuality";
	jc_localisation.localisations[NSW_localisation_EN] = "Alternate quality";
	jc_localisation.localisations[NSW_localisation_RU] = "Альтернативное качество";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Replica";
	jc_localisation.localisations[NSW_localisation_EN] = "Replica";
	jc_localisation.localisations[NSW_localisation_RU] = "Реплика";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Identified";
	jc_localisation.localisations[NSW_localisation_EN] = "Identified";
	jc_localisation.localisations[NSW_localisation_RU] = "Опознан";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Corrupted";
	jc_localisation.localisations[NSW_localisation_EN] = "Corrupted";
	jc_localisation.localisations[NSW_localisation_RU] = "Осквернён";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Mirrored";
	jc_localisation.localisations[NSW_localisation_EN] = "Mirrored";
	jc_localisation.localisations[NSW_localisation_RU] = "Отражён";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ElderItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Elder item";
	jc_localisation.localisations[NSW_localisation_RU] = "Предмет Древнего";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ShaperItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Shaper item";
	jc_localisation.localisations[NSW_localisation_RU] = "Предмет Создателя";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "FracturedItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Fractured item";
	jc_localisation.localisations[NSW_localisation_RU] = "Расколотый предмет";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SynthesisedItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Synthesised item";
	jc_localisation.localisations[NSW_localisation_RU] = "Синтезированный предмет";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ElderMap";
	jc_localisation.localisations[NSW_localisation_EN] = "Elder map";
	jc_localisation.localisations[NSW_localisation_RU] = "Карта Древнего";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ShapedMap";
	jc_localisation.localisations[NSW_localisation_EN] = "Shaped map";
	jc_localisation.localisations[NSW_localisation_RU] = "Карта Создателя";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "BlightedMap";
	jc_localisation.localisations[NSW_localisation_EN] = "Blighted map";
	jc_localisation.localisations[NSW_localisation_RU] = "Карта скверны";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/*____________________________________COSMETIC SECTION___________________________________________________*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetBackgroundColor";
	jc_localisation.localisations[NSW_localisation_EN] = "Background color";
	jc_localisation.localisations[NSW_localisation_RU] = "Цвет фона";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetBorderColor";
	jc_localisation.localisations[NSW_localisation_EN] = "Border color";
	jc_localisation.localisations[NSW_localisation_RU] = "Цвет рамки";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetTextColor";
	jc_localisation.localisations[NSW_localisation_EN] = "Text color";
	jc_localisation.localisations[NSW_localisation_RU] = "Цвет текста";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetFontSize";
	jc_localisation.localisations[NSW_localisation_EN] = "Font size";
	jc_localisation.localisations[NSW_localisation_RU] = "Размер текста";

	jc_filter_block_attribute = new FilterBlockAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_filter_block_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	ETextParser::data_entity_parse_file("data/data_entity_list.txt");
	ETextParser::split_data_entity_list_to_named_structs();




	//ETextParser::data_read_explicit_file_and_generate_data_entity("data/Enchantmets list.txt");

	//for (int j = 0; j < CLUSTER_DIM_X; j++)
	//for (int i = 0; i < CLUSTER_DIM_Y; i++)
	//{
	//	cluster_array[j][i] = new ECluster();
	//}

	//jc = Just Created
	Entity* jc_entity = new Entity();
	ESpriteLayer* jc_sprite_layer = new ESpriteLayer();
	ESpriteLayer* jc_sprite_layer_for_text = new ESpriteLayer();
	ESprite* jc_sprite = new ESprite();
	ECustomData* jc_custom_data = new ECustomData();
	ERegionGabarite* jc_region_gabarite = new ERegionGabarite(0.0f, 0.0f, 500.0f, 200.0f);
	EClickableArea* jc_clickable_area = new EClickableArea();
	ETextArea* jc_text_area = new ETextArea();
	EButtonGroup* jc_button_group;
	EButtonGroup* main_button_group;
	//EButtonGroupRow*	jc_button_group_row;
	EntityButton* jc_button;
	ESpriteFrame* jc_sprite_frame = new ESpriteFrame();

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
				EntityButton* test_button = new EntityButton();
				test_button->make_as_default_clickable_button(new ERegionGabarite(64.0f, 64.0f), test_group, nullptr);

				test_group->button_list.push_back(test_button);
			}
		}
		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}
	////////////////////////////////////////////////

	std::string color_names_list[] = { "Never", "Gonna", "Give","You","Up","Never","Gonna","Ley","You","Down","Never","Gonna","Run","Arround","And", "Desert", "You" };

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
		main_button_group->parent_window = this;

		main_button_group->child_align_direction = ChildElementsAlignDirection::TOP_TO_BOTTOM;

		main_button_group->actions_on_resize_window.push_back(&EDataActionCollection::action_resize_to_full_window);

		main_button_group->root_group = main_button_group;
		main_button_group->can_be_moved = false;
		main_button_group->can_resize_to_workspace_size_x = false;
		main_button_group->can_resize_to_workspace_size_y = false;

		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		//*main_button_group->stretch_mode		= GroupStretchMode::CONSTANT;
		main_button_group->dynamic_autosize_for_window = true;

		loot_filter_editor = main_button_group;
		autosize_group_list.push_back(main_button_group);

		for (int z = 0; z < 0; z++)
		{
			create_filter_block(main_button_group);
		}




		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}

	//skill gems
	if (false)
	{
		main_button_group = EButtonGroup::create_root_button_group
		(new ERegionGabarite(10.0f, 10.0f, 0.0f, 512.0f, 800.0f), EGUIStyle::active_style);
		main_button_group->parent_window = this;
		main_button_group->root_group = main_button_group;
		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		jc_button_group = main_button_group->add_group(EButtonGroup::create_default_button_group(new ERegionGabarite(256.0f, 150.0f), EGUIStyle::active_style));
		jc_button_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = true;

		std::vector <EDataEntity*> suitable_data_entity_list;
		for (EDataEntity* de : EDataEntity::data_entity_global_list)
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


			EDataContainer_Group_StoreFilterRuleForDataEntitySearcher* data_container_entity_filter = new EDataContainer_Group_StoreFilterRuleForDataEntitySearcher();
			data_container_entity_filter->target_group = EButtonGroup::data_entity_filter;
			data_container_entity_filter->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_SKILL_GEMS];

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
		main_button_group->parent_window = this;
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
			style_group->can_resize_to_workspace_size_x = false;
			style_group->can_resize_to_workspace_size_y = false;

			style_group->can_be_stretched_by_child = true;

			style_group->stretch_x_by_parent_size = true;
			style_group->stretch_y_by_parent_size = false;

			*style_group->can_change_style = false;




			//group for prewiev button
			EButtonGroup* buttons_simulator = style_group->add_group
			(EButtonGroup::create_default_button_group(new ERegionGabarite(horizontal_side, 100.0f), style));
			buttons_simulator->stretch_x_by_parent_size = true;
			buttons_simulator->stretch_y_by_parent_size = false;

			if (buttons_simulator != nullptr)
			{
				*buttons_simulator->can_change_style = false;

				if (!EDataEntity::data_entity_global_list.empty())
					for (int i = 0; i < 17; i++)
					{

						jc_button = new EntityButton();
						jc_button->make_as_default_clickable_button
						(
							new ERegionGabarite(40.0f, 40.0f),
							buttons_simulator,
							nullptr
						);

						ETextureGabarite* item_icon
							=
							NS_EGraphicCore::load_from_textures_folder
							("icons/" + DataEntityUtils::get_tag_value_by_name(0, "icon path", EDataEntity::data_entity_global_list[rand() % EDataEntity::data_entity_global_list.size()]));

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

			jc_button_group->stretch_x_by_parent_size = true;
			jc_button_group->stretch_y_by_parent_size = false;

			//select button
			if (jc_button_group != nullptr)
			{

				*jc_button_group->can_change_style = false;

				jc_button = new EntityButton();
				jc_button->make_as_default_clickable_button
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
		(new ERegionGabarite(900.0f, 100.0f, 0.0f, 1250.0f, 600.0f), EGUIStyle::active_style);
		main_button_group->parent_window = this;
		main_button_group->root_group = main_button_group;
		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		EButtonGroup::data_entity_filter = main_button_group;


		EDataContainer_Group_DataEntitiesSearch* jc_data_container_for_search_group = new EDataContainer_Group_DataEntitiesSearch();
		main_button_group->data_container = jc_data_container_for_search_group;
		main_button_group->is_active = false;

		DataEntityFilter* data_entity_filter = new DataEntityFilter();
		data_entity_filter->target_tag_name = "data type";
		data_entity_filter->suitable_values_list.push_back("Game item");

		EFilterRule* jc_filter_rule = new EFilterRule();
		jc_filter_rule->required_tag_list.push_back(data_entity_filter);

		jc_data_container_for_search_group->target_rule = new EFilterRule();

		// // //	DATA ENTITY LIST	// // //
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 480.0f), EGUIStyle::active_style));
		jc_button_group->child_align_mode = ChildAlignMode::ALIGN_HORIZONTAL;
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = true;
		jc_button_group->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;








		/// LEFT SIDE FOR BUTTONS
		EButtonGroup* left_side_for_data_entity_buttons = jc_button_group->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(890.0f, 480.0f),
				EGUIStyle::active_style
			)
		)->set_parameters
		(
			ChildAlignMode::ALIGN_HORIZONTAL,
			NSW_dynamic_autosize,
			NSW_dynamic_autosize
		);

		/// RIGHT SIDE FOR FILTERS
		EButtonGroup* right_side_for_filter_rule_buttons = jc_button_group->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(250.0f, 480.0f),
				EGUIStyle::active_style
			)
		)->set_parameters
		(
			ChildAlignMode::ALIGN_VERTICAL,
			NSW_static_autosize,
			NSW_dynamic_autosize
		);
		//right_side_for_filter_rule_buttons->can

		jc_data_container_for_search_group->pointer_to_group_with_data_entities = left_side_for_data_entity_buttons;
		jc_data_container_for_search_group->pointer_to_group_with_filter_rules_list = right_side_for_filter_rule_buttons;



		//buttons for data entity
		unsigned int counter = 0;
		for (EDataEntity* data_entity : EDataEntity::data_entity_global_list)
		{

			jc_button = EntityButton::create_wide_item_button
			(
				new ERegionGabarite(220.0f, 40.0f),
				left_side_for_data_entity_buttons,
				data_entity,
				EFont::font_list[0]
			);

			left_side_for_data_entity_buttons->button_list.push_back(jc_button);

			counter++;
		}

		for (int i = 0; i < EFilterRule::registered_filter_rules_for_list.size(); i++)
		{
			EntityButtonFilterRule* filter_button = new EntityButtonFilterRule();
			filter_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(200.0f, 28.0f),
				right_side_for_filter_rule_buttons,
				&EDataActionCollection::action_select_this_filter_variant,
				EFilterRule::registered_filter_rules_for_list[i]->localisation_text->localisations[NSW_localisation_EN]
			);

			//filter_button->

			Entity::get_last_text_area(filter_button)->localisation_text = *EFilterRule::registered_filter_rules_for_list[i]->localisation_text;

			filter_button->target_filter_rule = EFilterRule::registered_filter_rules_for_list[i];
			filter_button->target_data_container = jc_data_container_for_search_group;

			right_side_for_filter_rule_buttons->button_list.push_back(filter_button);
		}

		//search bar group
		jc_button_group = main_button_group->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 50.0f), EGUIStyle::active_style));
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = false;

		jc_button = new EntityButton();
		jc_button->make_as_default_clickable_button
		(
			new ERegionGabarite(800.0f, 25.0f),
			jc_button_group,
			nullptr
		);
		jc_data_container_for_search_group->pointer_to_search_bar = jc_button;

		jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "");
		jc_data_container_for_search_group->filter_text_area = jc_text_area;
		jc_text_area->action_on_change_text.push_back(&EDataActionCollection::action_type_search_data_entity_text);
		Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
		jc_button_group->button_list.push_back(jc_button);





		EDataActionCollection::action_type_search_data_entity_text(jc_text_area);




		button_group_list.push_back(main_button_group);



		///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	
		jc_button = new EntityButton();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(256.0f, 25.0f),
			jc_button_group,
			&EDataActionCollection::action_add_all_entity_buttons_to_filter_block,
			"Add all these items"
		);

		jc_button_group->button_list.push_back(jc_button);
		///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	

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
		main_button_group->parent_window = this;
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
			"Глянец"
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
			"Нормаль"
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
			"Размер:"
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
			"Затухание:"
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
			"Яркость:"
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
			"Степень:"
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
			"Матовое затухание:"
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
			"Цвет солнца",
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
			"Уровень грунта:"
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
			"Скорость смещения:"
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
			"Матовый свет фона"
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
			"Яркость отражения"
		);
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::global_reflection_multiplier;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 4.0f;
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
			"Зум"
		);
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::current_zoom;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 2.0f;
		EntityButton::get_last_custom_data(jc_button)->actions_on_update.push_back(&EDataActionCollection::action_force_resize_callback);
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //



		// // // // // // //// // // // // // //// // // // // // //
		jc_button = new EntityButtonForFilterBlock();
		jc_button->make_default_bool_switcher_button
		(
			new ERegionGabarite(22.0f, 22.0f),
			jc_button_group,
			EDataActionCollection::action_switch_boolean_value,
			NS_EGraphicCore::load_from_textures_folder("box_switcher_on"),
			NS_EGraphicCore::load_from_textures_folder("box_switcher_off")
		);

		jc_button_group->button_list.push_back(jc_button);


		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}


	//color editor
	if (true)
	{
		main_button_group = EButtonGroup::create_color_editor_group(new ERegionGabarite(200.0f, 200.0f, 980.0f, 420.0f), EGUIStyle::active_style);
		main_button_group->parent_window = this;
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
		add_content_group->parent_window = this;
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

		jc_button = new EntityButton();
		jc_button->make_default_button_with_edible_text
		(
			new ERegionGabarite(800.0f, 30.0f),
			search_bar_group,
			nullptr,
			""
		);

		//add pointer to clickable are in "add content to filter block group"
		content_group_data_container->typing_text_area = EntityButton::get_last_text_area(jc_button);

		auto multi_search_data_container = new EDataContainer_Button_MultiGroupButtonSearcher();

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
				EButtonGroup::create_default_button_group(new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
				->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
			);
		filter_block_operation_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(160.0f, 20.0f),
			filter_block_operation_segment,
			nullptr,
			"Добавить новый блок"
		);

		filter_block_operation_segment->button_list.push_back(jc_button);

		//jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(160.0f, 20.0f), filter_block_operation_segment, nullptr, "Клонировать этот блок");
		//filter_block_operation_segment->button_list.push_back(jc_button);

		///
		EButtonGroup*
			non_listed_segment
			=
			content_list_group->add_group
			(
				EButtonGroup::create_default_button_group(new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
				->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
			);
		non_listed_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;


		///
		EButtonGroup*
			listed_segment
			=
			content_list_group->add_group
			(
				EButtonGroup::create_default_button_group(new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
				->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
			);
		listed_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		///
		EButtonGroup*
			cosmetic_segment
			=
			content_list_group->add_group
			(
				EButtonGroup::create_default_button_group(new ERegionGabarite(100.0f, 100.0f), EGUIStyle::active_style)
				->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
			);
		cosmetic_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		multi_search_data_container->target_group_list.push_back(content_list_group);
		multi_search_data_container->target_group_list.push_back(non_listed_segment);
		multi_search_data_container->target_group_list.push_back(listed_segment);
		multi_search_data_container->target_group_list.push_back(cosmetic_segment);

		EButtonGroup* target_group = nullptr;
		for (FilterBlockAttribute* fba : registered_filter_block_attributes)
			if (!fba->always_present)
			{
				EDataContainer_Button_AddContentToFilterBlock* add_content_data = new EDataContainer_Button_AddContentToFilterBlock();
				add_content_data->target_attribute = fba;

				if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED) { target_group = non_listed_segment; }
				if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED) { target_group = listed_segment; }
				if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC) { target_group = cosmetic_segment; }

				jc_button = new EntityButtonFilterRule();
				jc_button->make_default_button_with_unedible_text
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
		ELocalisationText ltext;

		EButtonGroup* whole_rarity_list_group = EButtonGroup::create_root_button_group(new ERegionGabarite(100.0f, 120.0f), EGUIStyle::active_style);
		whole_rarity_list_group->parent_window = this;
		EButtonGroup* workspace_rarity_group = whole_rarity_list_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), EGUIStyle::active_style);
		workspace_rarity_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		select_rarity_button_group = whole_rarity_list_group;

		auto data_text_selector = new EDataContainer_Group_TextSelectorFromVariants();
		whole_rarity_list_group->data_container = data_text_selector;





		//normal
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_rarity_group,
			&EDataActionCollection::action_select_this_text_variant,
			"Обычный"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 1.0f, 1.0f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		ltext.base_name = "Normal";

		ltext.localisations[NSW_localisation_EN] = "Normal";
		ltext.localisations[NSW_localisation_RU] = "Нормальный";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//magic
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_rarity_group,
			&EDataActionCollection::action_select_this_text_variant,
			"Магический"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(0.4f, 0.5f, 1.0f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);


		ltext.base_name = "Magic";

		ltext.localisations[NSW_localisation_EN] = "Magic";
		ltext.localisations[NSW_localisation_RU] = "Волшебный";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//rare
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_rarity_group,
			&EDataActionCollection::action_select_this_text_variant,
			"Редкий"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 1.0f, 0.25f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		ltext.base_name = "Rare";

		ltext.localisations[NSW_localisation_EN] = "Rare";
		ltext.localisations[NSW_localisation_RU] = "Редкий";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//unique
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_rarity_group,
			&EDataActionCollection::action_select_this_text_variant,
			"Уникальный"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 0.50f, 0.25f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		ltext.base_name = "Unique";

		ltext.localisations[NSW_localisation_EN] = "Unique";
		ltext.localisations[NSW_localisation_RU] = "Уникальный";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;


		button_group_list.push_back(whole_rarity_list_group);
		EButtonGroup::refresh_button_group(whole_rarity_list_group);

		whole_rarity_list_group->is_active = false;
	}

	//quality selector
	if (true)
	{
		ELocalisationText ltext;

		EButtonGroup* whole_quality_list_group = EButtonGroup::create_root_button_group(new ERegionGabarite(100.0f, 120.0f), EGUIStyle::active_style);
		whole_quality_list_group->parent_window = this;
		EButtonGroup* workspace_quality_group = whole_quality_list_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), EGUIStyle::active_style);
		workspace_quality_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		select_quality_button_group = whole_quality_list_group;

		auto data_text_selector = new EDataContainer_Group_TextSelectorFromVariants();
		whole_quality_list_group->data_container = data_text_selector;

		//anomalous
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_quality_group,
			&EDataActionCollection::action_select_this_text_variant,
			"Аномальный"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 0.8f, 0.8f, 1.0f);
		workspace_quality_group->button_list.push_back(jc_button);

		ltext.base_name = "Anomalous";

		ltext.localisations[NSW_localisation_EN] = "Anomalous";
		ltext.localisations[NSW_localisation_RU] = "Аномальный";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//divergent
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_quality_group,
			&EDataActionCollection::action_select_this_text_variant,
			"Искривлённый"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(0.8f, 1.0f, 0.8f, 1.0f);
		workspace_quality_group->button_list.push_back(jc_button);

		ltext.base_name = "Divergent";

		ltext.localisations[NSW_localisation_EN] = "Divergent";
		ltext.localisations[NSW_localisation_RU] = "Искривлённый";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//phantasmal
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_quality_group,
			&EDataActionCollection::action_select_this_text_variant,
			"Фантомный"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(0.8f, 0.8f, 1.0f, 1.0f);
		workspace_quality_group->button_list.push_back(jc_button);

		ltext.base_name = "Phantasmal";

		ltext.localisations[NSW_localisation_EN] = "Phantasmal";
		ltext.localisations[NSW_localisation_RU] = "Фантомный";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		button_group_list.push_back(whole_quality_list_group);
		EButtonGroup::refresh_button_group(whole_quality_list_group);

		whole_quality_list_group->is_active = false;
	}

	//loot-filter list
	{
		main_button_group = EButtonGroup::create_root_button_group
		(
			new ERegionGabarite(512.0f, 256.0f, 1020.0f, 512.0f),
			EGUIStyle::active_style
		);
		EButtonGroup::existing_loot_filter_list = main_button_group;

		auto whole_loot_filter_group = static_cast<EButtonGroupLootFilterList*>(main_button_group);


		main_button_group->parent_window = this;

		main_button_group->root_group = main_button_group;
		main_button_group->can_be_moved = true;
		main_button_group->can_resize_to_workspace_size_x = true;
		main_button_group->can_resize_to_workspace_size_y = true;

		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		EButtonGroup* loot_filters_list_workspace_part = main_button_group->add_close_group_and_return_workspace_group
		(
			new ERegionGabarite(1.0f, 20.0f),
			EGUIStyle::active_style
		)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

		///////////////		LOOT-FILTERS LIST PART		///////////////
		EButtonGroup* loot_filter_list_part = loot_filters_list_workspace_part->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(1.0f, 1.0f),
				EGUIStyle::active_style
			)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
		);

		///////////////		SEARCH INPUT PART		///////////////
		EButtonGroup* search_input_part = loot_filters_list_workspace_part->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(1.0f, 32.0f),
				EGUIStyle::active_style
			)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize)
		);


		/// set data parameters
		whole_loot_filter_group->part_with_list = loot_filter_list_part;



		load_loot_filter_list();

		/*for (int i = 0; i < 2; i++)
		{
			EntityButton* but = EntityButton::make_default_button_with_unedible_text
			(
				new ERegionGabarite(128.0f, 32.0f),
				loot_filter_list_part,
				nullptr,
				"ZZZ"
			);
			loot_filter_list_part->button_list.push_back(but);
		}*/

		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}


	////////////////////////////////////////////////////////////////
	// 
	//		#LOCKED VECTOR ORDER
	// 
	//////////////////////////////////////////////////////////////// 
	//head button group
	{
		main_button_group = EButtonGroup::create_root_button_group
		(
			new ERegionGabarite(NS_EGraphicCore::SCREEN_WIDTH, 76.0f),
			EGUIStyle::active_style
		);
		EButtonGroup::header_line = main_button_group;
		main_button_group->region_gabarite->offset_y = NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom - main_button_group->region_gabarite->size_y;

		main_button_group->parent_window = this;

		main_button_group->root_group = main_button_group;
		main_button_group->can_be_moved = false;
		main_button_group->can_resize_to_workspace_size_x = false;
		main_button_group->can_resize_to_workspace_size_y = true;

		main_button_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		main_button_group->actions_on_resize_window.push_back(&EDataActionCollection::action_resize_to_full_window_only_x);
		main_button_group->dynamic_autosize_for_window = false;
		autosize_group_list.push_back(main_button_group);
		EButtonGroup* bottom_section = main_button_group->add_group
		(
			EButtonGroup::create_button_group_without_bg
			(
				new ERegionGabarite(1.0f, 1.0f),
				EGUIStyle::active_style
			)
		)->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

		EButtonGroup* top_section = main_button_group->add_group
		(
			EButtonGroup::create_button_group_without_bg
			(
				new ERegionGabarite(1.0f, 46.0f),
				EGUIStyle::active_style
			)
		)->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_static_autosize);

		//////////////////////////////////////////////////////

		jc_button = new EntityButtonForFilterBlock();
		jc_button->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_open_loot_filters_list_window,
			NS_EGraphicCore::load_from_textures_folder("button_open")
		);
		top_section->button_list.push_back(jc_button);

		//////////////////////////////////////////////////////

		jc_button = new EntityButtonForFilterBlock();

		jc_button->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_save_lootfilter,
			NS_EGraphicCore::load_from_textures_folder("button_save")
		);
		//auto data_container = new EDataContainer_Button_StoreParentFilterBlock();
		//data_container->parent_filter_block = top_section;

		//EntityButton::get_last_custom_data(jc_button)->
		top_section->button_list.push_back(jc_button);

		//////////////////////////////////////////////////////

		for (int i = 0; i < 5; i++)
		{
			jc_button = new EntityButtonFilterRule();
			jc_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(120.0f, 26.0f),
				bottom_section,
				&EDataActionCollection::action_select_this_button,
				"Filter tab #" + std::to_string(i)
			);

			bottom_section->button_list.push_back(jc_button);
		}

		//////////////////////////////////////////////////////


		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}



}

void EWindowMain::register_filter_rules()
{
	EFilterRule* jc_filter_rule = nullptr;
	DataEntityFilter* jc_filter = nullptr;

	// // // GLOBAL // // //
	////////////////////////////////////////////////////////////////////////////////////////////
	//game items
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);

	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//base class
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Base Class";

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Base Class");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_BASE_CLASS] = jc_filter_rule;


	////////////////////////////////////////////////////////////////////////////////////////////
	//influence
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Influence";

	jc_filter = new DataEntityFilter();


	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Influence");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_INFLUENCE] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//gem
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Gem";

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Gem");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_SKILL_GEMS] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//explicit
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Explicit";

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Explicit");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//cluster passives
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Cluster passive";

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Cluster passive");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_CLUSTER_PASSIVE] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//enchantments from lab
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Enchantment";

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Enchantment");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_ENCHANTMENT] = jc_filter_rule;


	// <cost list>
	// trash
	// common
	// moderate
	// rare
	// expensive
	// very expensive

	// // // BUTTON LIST // // //

	////////////////////////////////////////////////////////////////////////////////////////////
	//ALL ITEMS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "All items";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Все предметы";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//


	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//TRASH DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Trash divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Мусорные гадальные карты";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "base class";
	jc_filter->suitable_values_list.push_back("Divination card");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "worth";
	jc_filter->suitable_values_list.push_back("Trash");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//TRASH DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Common divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Дешёвые гадальные карты";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "base class";
	jc_filter->suitable_values_list.push_back("Divination card");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "worth";
	jc_filter->suitable_values_list.push_back("Common");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//TRASH DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Moderate divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Хорошие гадальные карты";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "base class";
	jc_filter->suitable_values_list.push_back("Divination card");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "worth";
	jc_filter->suitable_values_list.push_back("Moderate");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//TRASH DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Rare divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Ценные гадальные карты";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "base class";
	jc_filter->suitable_values_list.push_back("Divination card");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "worth";
	jc_filter->suitable_values_list.push_back("Rare");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//TRASH DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Expensive divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Дорогие гадальные карты";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "base class";
	jc_filter->suitable_values_list.push_back("Divination card");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "worth";
	jc_filter->suitable_values_list.push_back("Expensive");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//TRASH DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Very expensive divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Очень дорогие гадальные карты";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "base class";
	jc_filter->suitable_values_list.push_back("Divination card");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter by class "divination"
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "worth";
	jc_filter->suitable_values_list.push_back("Very expensive");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);


	////////////////////////////////////////////////////////////////////////////////////////////
		//Heist league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Heist bases";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Базы кражи";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("Heist base");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//D
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Deleted items";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Удалённые предметы";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("Deleted");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Atlas bases
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Atlas bases";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Базы атласа";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("Rare base");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Top tier bases
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Top tier base";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Лучшие базы предметов";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("Top tier base");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Ritual league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "League: Ritual";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Лига: Ритуал";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("League: Ritual");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Heist league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Heist league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Лига 'Кража'";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("League: Heist");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Kalandra league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "kalandra league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Лига 'Каландра'";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("Introduced: Kalandra league");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Heist league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Game item";

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Heist league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "Лига 'Кража'";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//filter "item tag" by 
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "item tag";
	jc_filter->suitable_values_list.push_back("League: Heist");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

}

EWindowMain::~EWindowMain()
{

}

void EWindowMain::load_loot_filter_list()
{
	//EString::loot_filter_path_list.clear();
	//EString::loot_filter_name_list.clear();

	auto			loot_filter_group = static_cast<EButtonGroupLootFilterList*>(EButtonGroup::existing_loot_filter_list);
	EButtonGroup* part_with_list = loot_filter_group->part_with_list;

	std::vector<EntityButton*> deleted_buttons;

	//EInputCore::logger_param("size of elements - part_with_list->button_list", part_with_list->button_list.size());

	for (int i = 0; i < part_with_list->button_list.size(); i++)
	{
		EntityButton* but = part_with_list->button_list[i];

		if (but != part_with_list->slider)
		{
			/*		but->need_remove	= true;
					but->disabled		= true;
					but->disable_draw	= true;*/

			delete but;

			part_with_list->button_list.erase(part_with_list->button_list.begin() + i);

			i--;


		}
	}

	//for (int z = 0; z < (deleted_buttons.size()) - 1; z++ )
	//{
	//	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	//	EInputCore::logger_param("try delete " , std::to_string(z) + "/" + std::to_string(deleted_buttons.size()));
	//	//delete deleted_buttons[i];
	//	EInputCore::logger_simple_success("deleted");
	//}




	//part_with_list->button_list.clear();

	//part_with_list->button_list.shrink_to_fit();

	for (auto& p : std::experimental::filesystem::directory_iterator(path_of_exile_folder))
	{
		std::string filter_path = p.path().u8string();

		std::string loot_filter_name = p.path().filename().u8string();

		//EInputCore::logger_param("detect file:", filter_path);
		//writer << custom_sound << endl;;




		if
			(
				(loot_filter_name.length() >= 8)
				&&
				(EStringUtils::to_lower(loot_filter_name.substr(loot_filter_name.length() - 7, 7)) == ".filter")
				)
		{


			//cout <<"It sound!" << '\n'<<'\n';

			//for (int i = 0; i < 10; i ++)
			{
				EntityButtonForLootFilterSelector* loot_filter_button = new EntityButtonForLootFilterSelector();
				loot_filter_button->make_default_button_with_unedible_text
				(
					new ERegionGabarite(325.0f, 32.0f),
					part_with_list,
					&EDataActionCollection::action_select_this_loot_filter_from_list,
					loot_filter_name
				);
				loot_filter_button->full_path = filter_path;

				part_with_list->button_list.push_back(loot_filter_button);
			}
			//EInputCore::logger_simple_success("push back");

			//EInputCore::logger_simple_success("It filter!");
			//EStringUtils::loot_filter_path_list.push_back(UTF8_to_ANSI(loot_filter_name));
			//EStringUtils::loot_filter_name_list.push_back(UTF8_to_ANSI(p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 7)));

			//std::cout << "It filter! " << p.path().filename().u8string() << '\n' << '\n';

			//ESound::custom_drop_sound.push_back(ESound::engine->addSoundSourceFromFile(custom_sound.c_str()));
		}
	}
}

//enum class ReadLootFilterState
//{
//	BEGIN,
//	ATTRIBUTE_NAME,
//	WTF
//};

bool EWindowMain::text_is_condition(std::string& buffer_text)
{
	return
		(buffer_text == "<=")
		||
		(buffer_text == "<")
		||
		(buffer_text == "=")
		||
		(buffer_text == "==")
		||
		(buffer_text == ">")
		||
		(buffer_text == ">=")
		||
		(buffer_text == "<>");
}

void EWindowMain::open_loot_filter(std::string _full_path)
{
	EInputCore::logger_param("open loot filter", _full_path);

	std::ifstream file;
	std::string full_line;

	file.open(_full_path);

	std::string buffer_text = "";

	bool space_is_not_separator = false;
	bool comment_mode = false;

	int data_part = 0;
	int value_array_id = 0;
	int matched_id_for_color_button = -1;

	EntityButton* matched_button = nullptr;

	EButtonGroupFilterBlock* jc_filter_block = nullptr;

	std::string attribute_text = "";
	std::string condition_text = "";
	std::string value_array[512] = {};

	Helper::HSVRGBAColor* target_HRA_color;
	bool* target_color_bool;

	FilterBlockAttribute* matched_filter_block_attribute = nullptr;

	EDataContainer_Group_FilterBlockNonListedSegment* last_non_listed_container = nullptr;
	EButtonGroup* last_non_listed_group = nullptr;



	while (std::getline(file, full_line))
	{
		data_part = 0;
		value_array_id = 0;
		matched_id_for_color_button = -1;
		matched_button = nullptr;

		buffer_text = "";

		space_is_not_separator = false;
		comment_mode = false;

		condition_text = "";

		matched_filter_block_attribute = nullptr;
		target_HRA_color = nullptr;

		EButtonGroupFilterBlock* whole_block_container = nullptr;
		EDataContainer_Group_FilterBlockListedSegment* listed_container = nullptr;

		target_color_bool = nullptr;

		for (int i = 0; i < full_line.length(); i++)
		{
			char current_sym = full_line.at(i);

			if (current_sym == '"') { space_is_not_separator = !space_is_not_separator; }

			if
				(
					(
						(current_sym != ' ')
						||
						(space_is_not_separator)
						)
					&&
					(current_sym != '\t')
					&&
					(current_sym != '\r')
					&&
					(current_sym != '\n')
					&&
					(i + 1 < full_line.length())
					)
			{
				if (current_sym != '"')
				{
					buffer_text += current_sym;
				}
			}
			else
			{
				//force add symbol
				if
					(
						(
							(current_sym != ' ')
							||
							(space_is_not_separator)
							)
						&&
						(current_sym != '\t')
						&&
						(current_sym != '\r')
						&&
						(current_sym != '\n')
						&&
						(i + 1 >= full_line.length())
						)
				{
					if (current_sym != '"')
					{
						buffer_text += current_sym;
					}
				}

				if (buffer_text != "")
				{
					//attribute name
					if (data_part == 0)
					{
						//EInputCore::logger_param("buffer text", buffer_text);

						if
							(
								(EStringUtils::compare_ignoring_case(buffer_text, "show"))
								||
								(EStringUtils::compare_ignoring_case(buffer_text, "hide"))
								)
						{
							jc_filter_block = create_filter_block(loot_filter_editor);

							whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

							if (EStringUtils::compare_ignoring_case(buffer_text, "show"))
							{
								((EntityButtonVariantRouter*)(whole_block_container->button_show_hide))->select_variant(1);
							}
							else
							{
								((EntityButtonVariantRouter*)(whole_block_container->button_show_hide))->select_variant(0);
							}



						}
						else
						{
							matched_filter_block_attribute = nullptr;

							for (int b = 0; b < registered_filter_block_attributes.size(); b++)
							{
								FilterBlockAttribute* attribute = registered_filter_block_attributes[b];

								if (EStringUtils::compare_ignoring_case(buffer_text, attribute->localisation.base_name))
								{
									matched_filter_block_attribute = attribute;
								}
							}

							if (matched_filter_block_attribute != nullptr)
							{
								add_filter_block_buttons_to_filter_block(jc_filter_block, matched_filter_block_attribute);

								whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

								if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED)
								{
									if (!jc_filter_block->pointer_to_non_listed_segment->group_list.empty())
									{
										last_non_listed_group = jc_filter_block->pointer_to_non_listed_segment->group_list.back();
										last_non_listed_container = (EDataContainer_Group_FilterBlockNonListedSegment*)(last_non_listed_group->data_container);
									}
								}

								if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)
								{
									for (int b = 0; b < 3; b++)
									{
										if (Entity::get_last_text_area(whole_block_container->pointer_to_color_button[b])->localisation_text.base_name == matched_filter_block_attribute->localisation.base_name)
										{
											//matched_button = whole_block_container->pointer_to_color_button[b];
											target_HRA_color = ((EDataContainer_Button_StoreColor*)(Entity::get_last_custom_data(whole_block_container->pointer_to_color_button[b])->data_container))->stored_color;
											target_color_bool = &whole_block_container->color_check[b];
										}
									}

									//target_HRA_color = ((EDataContainer_Button_StoreColor*)(Entity::get_last_custom_data(whole_block_container->pointer_to_color_button[0])->data_container))->stored_color;
									//target_color_bool = &whole_block_container->color_check[0];
								}
							}
						}
					}

					//condition operator
					if (data_part == 1)
					{
						if(text_is_condition(buffer_text))
						{
							condition_text = buffer_text;

							if ((last_non_listed_container != nullptr) && (last_non_listed_container->target_button_with_condition != nullptr))
							{
								Entity::get_last_text_area(last_non_listed_container->target_button_with_condition)->change_text(condition_text);
							}
						}
						else
						{
							condition_text = "";
							data_part = 2;

							if
								(
									(last_non_listed_container != nullptr)
									&&
									(last_non_listed_container->target_button_with_condition != nullptr)
									&&
									(matched_filter_block_attribute != nullptr)
									&&
									(matched_filter_block_attribute->have_operator)
									)
							{
								Entity::get_last_text_area(last_non_listed_container->target_button_with_condition)->change_text("=");
							}
						}
					}

					//values
					if (data_part >= 2)
					{
						//EInputCore::logger_param("value", buffer_text);
						//value_array[value_array_id] = buffer_text;

						//value_array_id++;

						if (matched_filter_block_attribute != nullptr)
						{


							if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED)
							{
								if
									(
										(last_non_listed_container != nullptr)
										&&
										(matched_filter_block_attribute != nullptr)
										
										)
								{
									if
									(
										(
											(matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER)
											||
											(matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_TEXT)
										)
										&&
										(Entity::get_last_text_area(last_non_listed_container->target_button_with_value) != nullptr)
									)
									{
										Entity::get_last_text_area(last_non_listed_container->target_button_with_value)->change_text(buffer_text);
									}

									if
									(matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER)
									{
										if (EStringUtils::to_lower(buffer_text) == "true")
										{
											*static_cast <EDataContainer_Button_BoolSwitcher*>(last_non_listed_container->target_button_with_value->custom_data_list.back()->data_container)->target_value = true;
										}
										else
										{
											*static_cast <EDataContainer_Button_BoolSwitcher*>(last_non_listed_container->target_button_with_value->custom_data_list.back()->data_container)->target_value = false;
										}

									}
								}


							}

							if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED)
							{
								whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);
								listed_container = (EDataContainer_Group_FilterBlockListedSegment*)(whole_block_container->pointer_to_listed_segment->group_list.back()->data_container);

								EFilterRule* filter_rule = listed_container->data_container_with_filter_rule->filter_rule;
								std::string data_type_text = filter_rule->focused_by_data_type;

								std::vector<EDataEntity*>* target_data_entity_list = &EDataEntity::data_entity_global_list;

								for (DataEntityNamedStruct* named_struct : EDataEntity::data_entity_named_structs)
								{
									int
										index = EStringUtils::hashFunction(buffer_text) & 0x000000000000000F;
									index = min(index, 16);
									index = max(index, 0);

									//arr[index]++;
									if (named_struct->name == data_type_text) { target_data_entity_list = &named_struct->data_entity_list[index]; break; }
								}

								int xxx = 0;
								for (EDataEntity* de : *target_data_entity_list)
								{
									if
										(
											(
												(DataEntityUtils::get_tag_value_by_name(0, "name EN", de) == buffer_text)
												||
												(DataEntityUtils::get_tag_value_by_name(0, "base name", de) == buffer_text)
												)
											&&
											(EFilterRule::matched_by_filter_rule(de, filter_rule, ""))
											)
									{
										EntityButton* wide_button = EntityButton::create_wide_item_button
										(
											new ERegionGabarite(220.0f, 40.0f),
											((EDataContainer_Group_FilterBlockListedSegment*)listed_container)->group_with_listed_buttons,
											de,
											EFont::font_list[0]
										);

										((EDataContainer_Group_FilterBlockListedSegment*)listed_container)->group_with_listed_buttons->button_list.push_back(wide_button);
										//EButtonGroup::change_group(((EDataContainer_Group_FilterBlockListedSegment*)d_container)->group_with_listed_buttons);
									}

									xxx++;
								}
							}

							if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)
							{
								whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

								if (matched_filter_block_attribute->localisation.base_name == "SetFontSize")
								{

									whole_block_container->text_size = (std::stoi(buffer_text) - 18) / 27.0f;

									whole_block_container->text_size = max(whole_block_container->text_size, 0.0f);
									whole_block_container->text_size = min(whole_block_container->text_size, 1.0f);

									whole_block_container->text_size_bool = true;
									//d_container->
								}

								if (target_HRA_color != nullptr)
								{
									if (data_part == 2) { target_HRA_color->r = std::stoi(buffer_text) / 255.0f; }
									if (data_part == 3) { target_HRA_color->g = std::stoi(buffer_text) / 255.0f; }
									if (data_part == 4) { target_HRA_color->b = std::stoi(buffer_text) / 255.0f; }
									if (data_part == 5) { target_HRA_color->a = std::stoi(buffer_text) / 255.0f; Helper::rgb2hsv(target_HRA_color); *target_color_bool = true; }
								}





							}
						}
					}

					//value_array[data_part] = buffer_text;

					buffer_text = "";
					data_part++;
				}
			}

		}
	}

	file.close();

}

EButtonGroupFilterBlock* EWindowMain::create_filter_block(EButtonGroup* _target_whole_group)
{

	//EInputCore::logger_simple_info("create new block!");
	//whole filter block
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroupFilterBlock*
		whole_filter_block_group = new EButtonGroupFilterBlock(new ERegionGabarite(1200.0f, 200.0f));
	whole_filter_block_group->init_button_group(EGUIStyle::active_style, true, true, false);
	whole_filter_block_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);

	_target_whole_group->add_group(whole_filter_block_group);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//workspace bottom part
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup* workspace_part = EButtonGroup::create_default_button_group(new ERegionGabarite(1200.0f, 150.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

	whole_filter_block_group->add_group(workspace_part);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//control top part
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroupTopControlSection* control_part = new EButtonGroupTopControlSection(new ERegionGabarite(1200.0f, 30.0f));
	control_part->init_button_group(EGUIStyle::active_style, false, false, true);
	control_part->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_static_autosize);

	control_part->pointer_to_filter_block_group = whole_filter_block_group;

	whole_filter_block_group->pointer_to_top_control_block = control_part;
	whole_filter_block_group->add_group(control_part);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//left additional section
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		left_control_section = EButtonGroup::create_default_button_group(new ERegionGabarite(50.0f, 20.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);

	workspace_part->add_group(left_control_section);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//button router
	// // // // // // //// // // // // // //// // // // // // //
	EntityButtonVariantRouter* button_variant_router = new EntityButtonVariantRouter();
	button_variant_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(120.0f, 30.0f),
		control_part,
		EDataActionCollection::action_rotate_variant,
		nullptr
	);

	button_variant_router->layer_with_icon = button_variant_router->sprite_layer_list.back();
	//
	ETextArea* jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_router), EFont::font_list[0], "|?|");
	button_variant_router->pointer_to_text_area = jc_text_area;

	*jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_router, jc_text_area);


	//
	RouterVariant* router_variant = nullptr;
	ELocalisationText* local_text = nullptr;

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Hide";
	local_text->localisations[NSW_localisation_EN] = "Loot: hidden";
	local_text->localisations[NSW_localisation_RU] = "Лут: скрыт";
	router_variant->localisation = local_text;

	router_variant->color = new Helper::HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.5f, 0.45f, 1.0f);

	button_variant_router->router_variant_list.push_back(*router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Show";
	local_text->localisations[NSW_localisation_EN] = "Loot: Visible";
	local_text->localisations[NSW_localisation_RU] = "Лут: Виден";
	router_variant->localisation = local_text;

	router_variant->color = new Helper::HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.8f, 1.0f, 0.8f, 1.0f);

	button_variant_router->router_variant_list.push_back(*router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	control_part->button_list.push_back(button_variant_router);
	whole_filter_block_group->button_show_hide = button_variant_router;




	std::string base_names[5] =
	{
		"Start",
		"Low",
		"Default",
		"Rich",
		"Very rich",
	};

	std::string EN_names[5] =
	{
		"Start",
		"Low",
		"Default",
		"Rich",
		"Very rich",
	};

	std::string RU_names[5] =
	{
		"Стартовый",
		"Ранний",
		"Нормальный",
		"Поздный",
		"Максимальный",
	};
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	for (int i = 0; i < 5; i++)
	{
		button_variant_router = new EntityButtonVariantRouter();
		button_variant_router->make_as_default_button_with_icon
		(
			new ERegionGabarite(120.0f, 29.0f),
			control_part,
			EDataActionCollection::action_rotate_variant,
			nullptr
		);

		button_variant_router->layer_with_icon = button_variant_router->sprite_layer_list.back();

		ETextArea* jc_text_area = ETextArea::create_centered_to_left_text_area(EntityButton::get_last_clickable_area(button_variant_router), EFont::font_list[0], "|?|");
		button_variant_router->pointer_to_text_area = jc_text_area;

		*jc_text_area->can_be_edited = false;
		Entity::add_text_area_to_last_clickable_region(button_variant_router, jc_text_area);



		//	0
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = base_names[i] + '\n' + "Full ignore";
		local_text->localisations[NSW_localisation_EN] = EN_names[i] + '\n' + "Full ignore";
		local_text->localisations[NSW_localisation_RU] = RU_names[i] + '\n' + "Игнорирование";
		router_variant->localisation = local_text;

		router_variant->color = new Helper::HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.0f, 0.0f, 1.0f);

		router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_full_ignore");

		button_variant_router->router_variant_list.push_back(*router_variant);
		/*************************************************************************************/

		//	1
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = base_names[i] + '\n' + "Hide";
		local_text->localisations[NSW_localisation_EN] = EN_names[i] + '\n' + "Hide";
		local_text->localisations[NSW_localisation_RU] = RU_names[i] + '\n' + "Скрыт";
		router_variant->localisation = local_text;

		router_variant->color = new Helper::HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.7f, 0.7f, 0.7f, 1.0f);

		router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_hide");

		button_variant_router->router_variant_list.push_back(*router_variant);
		/*************************************************************************************/

		//	2
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = base_names[i] + '\n' + "Strong ignore";
		local_text->localisations[NSW_localisation_EN] = EN_names[i] + '\n' + "Strong ignore";
		local_text->localisations[NSW_localisation_RU] = RU_names[i] + '\n' + "Сильный игнор";
		router_variant->localisation = local_text;

		router_variant->color = new Helper::HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.5f, 0.45f, 1.0f);

		router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_strong_ignore");

		button_variant_router->router_variant_list.push_back(*router_variant);
		/*************************************************************************************/

		//	3
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = base_names[i] + "\n" + "Soft ignore";
		local_text->localisations[NSW_localisation_EN] = EN_names[i] + "\n" + "Soft ignore";
		local_text->localisations[NSW_localisation_RU] = RU_names[i] + "\n" + "Слабый игнор";
		router_variant->localisation = local_text;

		router_variant->color = new Helper::HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

		router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_soft_ignore");

		button_variant_router->router_variant_list.push_back(*router_variant);
		/*************************************************************************************/

		//	4
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = base_names[i] + "\n" + "Default";
		local_text->localisations[NSW_localisation_EN] = EN_names[i] + "\n" + "Default";
		local_text->localisations[NSW_localisation_RU] = RU_names[i] + "\n" + "Обычный";
		router_variant->localisation = local_text;

		router_variant->color = new Helper::HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.9f, 0.95f, 1.0f, 1.0f);

		router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_default");

		button_variant_router->router_variant_list.push_back(*router_variant);
		/*************************************************************************************/

		//	5
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = base_names[i] + "\n" + "Soft focus";
		local_text->localisations[NSW_localisation_EN] = EN_names[i] + "\\n" + "Soft focus";
		local_text->localisations[NSW_localisation_RU] = RU_names[i] + "\n" + "Слабый фокус";
		router_variant->localisation = local_text;

		router_variant->color = new Helper::HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.8f, 1.0f, 0.9f, 1.0f);

		router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_soft_focus");

		button_variant_router->router_variant_list.push_back(*router_variant);
		/*************************************************************************************/

		//	6
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = base_names[i] + "\n" + "Strong focus";
		local_text->localisations[NSW_localisation_EN] = EN_names[i] + "\n" + "Strong focus";
		local_text->localisations[NSW_localisation_RU] = RU_names[i] + "\n" + "Сильный фокус";
		router_variant->localisation = local_text;

		router_variant->color = new Helper::HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.6f, 1.0f, 0.8f, 1.0f);

		router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_strong_focus");

		button_variant_router->router_variant_list.push_back(*router_variant);
		/*************************************************************************************/





		button_variant_router->select_variant(4);



		control_part->button_list.push_back(button_variant_router);

		//whole_block_data->button_show_hide = button_variant_router;

	}
	// // // // // // //// // // // // // //// // // // // // //


	///////////		BUTTON PLUS		///////////
	EntityButton*
		jc_button = new EntityButton();
	jc_button->make_as_default_button_with_icon
	(
		new ERegionGabarite(50.0f, 50.0f),
		left_control_section,
		&EDataActionCollection::action_open_add_content_window,
		NS_EGraphicCore::load_from_textures_folder("button_plus")
	);

	EDataContainer_Button_OpenButtonGroup*
		data_open_group = new EDataContainer_Button_OpenButtonGroup();
	data_open_group->master_group = whole_filter_block_group;
	data_open_group->target_group = EButtonGroup::data_entity_filter;

	EntityButton::get_last_custom_data(jc_button)->data_container = data_open_group;

	left_control_section->button_list.push_back(jc_button);
	////////////////

	///////////		BUTTON GEN		///////////
	//generate filter block text
	jc_button = new EntityButton();
	jc_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(50.0f, 22.0f),
		left_control_section,
		&EDataActionCollection::action_generate_filter_block_text,
		"Gen"
	);

	auto gen_data = new EDataContainer_Button_StoreParentFilterBlock();
	gen_data->parent_filter_block = whole_filter_block_group;
	jc_button->custom_data_list.back()->data_container = gen_data;

	left_control_section->button_list.push_back(jc_button);
	////////////////


	//left side for equational parameters
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		EButtonGroup*
			non_list_condition_group = EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(420.0f, 160.0f),
				EGUIStyle::active_style
			)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);


		whole_filter_block_group->pointer_to_non_listed_segment = non_list_condition_group;

		workspace_part->add_group(non_list_condition_group);

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//####### ITEM GROUP //#######
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		listed_condition_segment = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(800.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);


	//root group data ontaner
	whole_filter_block_group->pointer_to_listed_segment = listed_condition_segment;


	workspace_part->add_group(listed_condition_segment);

	//cosmetic segment
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		filter_preview_box_segment = EButtonGroup::create_default_button_group(new ERegionGabarite(100.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);

	workspace_part->add_group(filter_preview_box_segment);
	//whole_block_data->pointer_to_preview_box_segment = filter_preview_box_segment;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//cosmetic segment
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		cosmetic_segment = EButtonGroup::create_default_button_group(new ERegionGabarite(165.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);

	ELocalisationText ltext[3];

	ltext[0].base_name = "SetBackgroundColor";
	ltext[0].localisations[NSW_localisation_EN] = "Background";
	ltext[0].localisations[NSW_localisation_RU] = "Фон";

	ltext[1].base_name = "SetTextColor";
	ltext[1].localisations[NSW_localisation_EN] = "Text";
	ltext[1].localisations[NSW_localisation_RU] = "Текст";

	ltext[2].base_name = "SetBorderColor";
	ltext[2].localisations[NSW_localisation_EN] = "Border";
	ltext[2].localisations[NSW_localisation_RU] = "Рамка";

	//root group data container
	whole_filter_block_group->pointer_to_cosmetic_segment = cosmetic_segment;
	workspace_part->add_group(cosmetic_segment);

	//color buttons
	for (int clr = 0; clr < 3; clr++)
	{
		// // // // // // //// // // // // // //// // // // // // //
		//Helper::HRA_color_collection* HRA_collection = Helper::registered_color_list[rand() % Helper::registered_color_list.size()];
		Helper::HSVRGBAColor* HRA_color = new Helper::HSVRGBAColor();
		HRA_color->h = rand() % 360;
		HRA_color->s = 1.0f - pow((rand() % 100) / 100.0f, 1.0);
		HRA_color->v = 1.0f - pow((rand() % 100) / 100.0f, 3.0);
		HRA_color->a = 1.0f - pow((rand() % 100) / 100.0f, 4.0);

		Helper::hsv2rgb(HRA_color);



		jc_button = EntityButton::create_named_color_button
		(
			new ERegionGabarite(120.0f, 25.0f),
			cosmetic_segment,
			EFont::font_list[0],
			EGUIStyle::active_style,
			ltext[clr].localisations[NSW_localisation_EN],
			nullptr,
			HRA_color,
			ColorButtonMode::CBM_OPEN_WINDOW
		);
		Entity::get_last_text_area(jc_button)->localisation_text = ltext[clr];


		whole_filter_block_group->pointer_to_HRA_color[clr] = &((EDataContainer_Button_StoreColor*)(EntityButton::get_last_custom_data(jc_button)->data_container))->stored_color;

		cosmetic_segment->button_list.push_back(jc_button);

		bool*
			target_bool = &whole_filter_block_group->color_check[clr];
		whole_filter_block_group->pointer_to_color_button[clr] = jc_button;




		jc_button = new EntityButton();
		jc_button->make_default_bool_switcher_button
		(
			new ERegionGabarite(25.0f, 25.0f),
			cosmetic_segment,
			EDataActionCollection::action_switch_boolean_value,
			NS_EGraphicCore::load_from_textures_folder("box_switcher_on"),
			NS_EGraphicCore::load_from_textures_folder("box_switcher_off"),
			target_bool
		);

		whole_filter_block_group->pointer_to_color_check_button[clr] = jc_button;

		cosmetic_segment->button_list.push_back(jc_button);
	}


	//font size slider
	// // // // // // //// // // // // // //// // // // // // //
	jc_button = EntityButton::create_vertical_named_slider
	(

		new ERegionGabarite(120.0f, 30.0f),
		cosmetic_segment,
		EFont::font_list[0],
		EGUIStyle::active_style,
		"Font size"
	);

	ETextArea*
		last_text_area = Entity::get_last_text_area(jc_button);

	last_text_area->localisation_text.base_name = "SetFontSize";
	last_text_area->localisation_text.localisations[NSW_localisation_EN] = "Font size";
	last_text_area->localisation_text.localisations[NSW_localisation_RU] = "Размер текста";

	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &whole_filter_block_group->text_size;
	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;

	whole_filter_block_group->text_size_button = jc_button;

	cosmetic_segment->button_list.push_back(jc_button);
	// // // // // // //// // // // // // //// // // // // // //


	//font size switcher
	// // // // // // //// // // // // // //// // // // // // //
	bool* target_bool = &whole_filter_block_group->text_size_bool;

	jc_button = new EntityButton();
	jc_button->make_default_bool_switcher_button
	(
		new ERegionGabarite(25.0f, 30.0f),
		cosmetic_segment,
		EDataActionCollection::action_switch_boolean_value,
		NS_EGraphicCore::load_from_textures_folder("box_switcher_on"),
		NS_EGraphicCore::load_from_textures_folder("box_switcher_off"),
		target_bool
	);
	whole_filter_block_group->text_size_switch_button = jc_button;

	cosmetic_segment->button_list.push_back(jc_button);
	// // // // // // //// // // // // // //// // // // // // //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return whole_filter_block_group;
}

void EDataActionCollection::action_open_add_content_window(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup::add_content_to_filter_block_group->is_active = true;
	EButtonGroup::add_content_to_filter_block_group->move_to_foreground();

	//_custom_data
	EDataContainer_Button_OpenButtonGroup* button_plus_data = static_cast<EDataContainer_Button_OpenButtonGroup*>			(_custom_data->data_container);
	EButtonGroupFilterBlock* whole_filter_block_data = static_cast<EButtonGroupFilterBlock*>			(button_plus_data->master_group);
	EDataContainer_Group_AddContentToFilterBlock* add_content_block_data = static_cast<EDataContainer_Group_AddContentToFilterBlock*>	(EButtonGroup::add_content_to_filter_block_group->data_container);
	ETextArea* typing_text_area = add_content_block_data->typing_text_area;

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


	EDataContainer_Group_AddContentToFilterBlock* add_content_group_data = static_cast<EDataContainer_Group_AddContentToFilterBlock*>	(EButtonGroup::add_content_to_filter_block_group->data_container);
	EButtonGroup* whole_button_group = add_content_group_data->target_filter_block;

	EButtonGroupFilterBlock* whole_filter_block_data = static_cast<EButtonGroupFilterBlock*>			(whole_button_group);
	EDataContainer_Button_AddContentToFilterBlock* add_content_button_data = static_cast<EDataContainer_Button_AddContentToFilterBlock*>	(_custom_data->data_container);

	EButtonGroup* target_group_for_content = nullptr;

	EntityButton* jc_button = nullptr;

	add_filter_block_buttons_to_filter_block(whole_button_group, add_content_button_data->target_attribute);

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
	EWindowMain::select_rarity_button_group->move_to_foreground();

	static_cast<EDataContainer_Group_TextSelectorFromVariants*>(EWindowMain::select_rarity_button_group->data_container)->target_button = static_cast<EntityButton*>(_entity);
	//reg
	EWindowMain::select_rarity_button_group->region_gabarite->offset_x = static_cast<EntityButton*>(_entity)->button_gabarite->world_position_x;
	EWindowMain::select_rarity_button_group->region_gabarite->offset_y = static_cast<EntityButton*>(_entity)->button_gabarite->world_position_y + static_cast<EntityButton*>(_entity)->button_gabarite->size_y + 3.0f;

	EButtonGroup::refresh_button_group(EWindowMain::select_rarity_button_group);
}

void EDataActionCollection::action_open_quality_selector(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EWindowMain::select_quality_button_group->is_active = true;
	EWindowMain::select_quality_button_group->move_to_foreground();

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
void add_filter_block_buttons_to_filter_block(EButtonGroup* _target_filter_block, FilterBlockAttribute* _filter_block_attribute)
{
	float button_height = 22.0f;
	//filter block have 4 sectors
	//1) control
	//2) non_listed
	//3) listed
	//4) cosmetic
	//
	//EDataContainer_Group_WholeFilterBlock store pointers to each segemnt
	auto whole_filter_block_data = static_cast<EButtonGroupFilterBlock*>(_target_filter_block);

	EntityButtonForFilterBlock* jc_button;

	std::string temp_rarity[] = { "Нормальный", "Магический", "Редкий", "Уникальный" };
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

	//unique
	temp_color.set_color_RGBA(1.0f, 0.5f, 0.250f, 1.0f);
	rarity_color[3] = temp_color;

	//if selected content is non-listed
	if (_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED)
	{
		EInputCore::logger_simple_info("add new non listed button");
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
		non_listed_line->button_align_type = ButtonAlignType::BUTTON_ALIGN_LEFT;

		//EInputCore::logger_simple_info("create fresh block");

		//FreshCreatedGroup* fresh_created_group = new FreshCreatedGroup();
		//fresh_created_group->target_group = whole_filter_block_data->pointer_to_non_listed_segment;
		//fresh_created_group->just_created_group = non_listed_line;
		//EButtonGroup::fresh_created_block_list.push_back(fresh_created_group);

		whole_filter_block_data->pointer_to_non_listed_segment->add_group(non_listed_line);

		//EInputCore::logger_param("size", EButtonGroup::fresh_created_block_list.size());

		auto non_listed_line_data = new EDataContainer_Group_FilterBlockNonListedSegment();
		non_listed_line_data->target_filter_block_attribute = _filter_block_attribute;
		non_listed_line->data_container = non_listed_line_data;

		/*CLOSE BUTTON*/
		///////////////////////////////////////////////////////////////////////////////////////////////
		jc_button = new EntityButtonForFilterBlock();
		jc_button->make_as_default_button_with_icon
		(
			new ERegionGabarite(button_height, button_height),
			non_listed_line,
			&EDataActionCollection::action_mark_parent_group_as_removed,
			NS_EGraphicCore::load_from_textures_folder("button_close")
		);
		non_listed_line->button_list.push_back(jc_button);
		jc_button->parent_filter_block = _target_filter_block;
		///////////////////////////////////////////////////////////////////////////////////////////////







		/*ATTRIBUTE NAME BUTTON*/
		///////////////////////////////////////////////////////////////////////////////////////////////
		jc_button = new EntityButtonForFilterBlock();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(200.0f, button_height),
			non_listed_line,
			nullptr,
			_filter_block_attribute->localisation.localisations[0]
		);

		jc_button->parent_filter_block = _target_filter_block;

		ETextArea* last_text_area = Entity::get_last_text_area(jc_button);
		if (last_text_area != nullptr) { last_text_area->localisation_text = _filter_block_attribute->localisation; }
		non_listed_line_data->target_button_with_attribute_name = jc_button;

		non_listed_line->button_list.push_back(jc_button);
		///////////////////////////////////////////////////////////////////////////////////////////////







		/*CONDITION OPERATOR BUTTON*/
		///////////////////////////////////////////////////////////////////////////////////////////////
		float input_field_additional_width = 0.0f;
		//condition operator
		if (_filter_block_attribute->have_operator)
		{
			jc_button = new EntityButtonForFilterBlock();
			jc_button->make_default_button_with_edible_text
			(
				new ERegionGabarite(button_height * 2.0f, button_height),
				non_listed_line,
				nullptr,
				"="
			);

			jc_button->parent_filter_block = _target_filter_block;

			non_listed_line->button_list.push_back(jc_button);

			non_listed_line_data->target_button_with_condition = jc_button;
		}
		else
		{
			input_field_additional_width = button_height * 2.0f + DISTANCE_BETWEEN_BUTTONS;

			non_listed_line_data->target_button_with_condition = nullptr;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////

		srand(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

		//EInputCore::logger_param("current time", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		int rarity_id = rand() % 4;

		std::string text = std::to_string(rand() % 100 + 1);

		switch (_filter_block_attribute->filter_attribute_value_type)
		{
		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST:
		{
			text = temp_rarity[rarity_id];

			jc_button = new EntityButtonForFilterBlock();
			jc_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				&EDataActionCollection::action_open_rarity_selector,
				text
			);

			jc_button->parent_filter_block = _target_filter_block;

			EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(&rarity_color[rarity_id]);
			Entity::get_last_text_area(jc_button)->localisation_text = _filter_block_attribute->localisation;

			non_listed_line_data->target_button_with_value = jc_button;

			break;
		}

		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST:
		{
			text = "Аномальный";
			jc_button = new EntityButtonForFilterBlock();
			jc_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				&EDataActionCollection::action_open_quality_selector,
				text
			);

			jc_button->parent_filter_block = _target_filter_block;

			Entity::get_last_text_area(jc_button)->localisation_text = _filter_block_attribute->localisation;

			non_listed_line_data->target_button_with_value = jc_button;

			break;
		}

		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER:
		{
			jc_button = new EntityButtonForFilterBlock();
			jc_button->make_default_bool_switcher_button
			(
				new ERegionGabarite(22.0f, 22.0f),
				non_listed_line,
				EDataActionCollection::action_switch_boolean_value,
				NS_EGraphicCore::load_from_textures_folder("box_switcher_on"),
				NS_EGraphicCore::load_from_textures_folder("box_switcher_off")

			);

			jc_button->parent_filter_block = _target_filter_block;

			non_listed_line_data->target_button_with_value = jc_button;

			break;
		}

		default:
		{
			jc_button = new EntityButtonForFilterBlock();
			jc_button->make_default_button_with_edible_text
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				nullptr,
				text
			);
			jc_button->parent_filter_block = _target_filter_block;

			Entity::get_last_text_area(jc_button)->localisation_text = _filter_block_attribute->localisation;
		}

		non_listed_line_data->target_button_with_value = jc_button;
		}


		non_listed_line->button_list.push_back(jc_button);


		//EButtonGroup::change_group(target_group_for_content);

		/*if (j == 0) { jc_region_gabarite = new ERegionGabarite(100.0f, 20.0f); }
		else
			if (j == 1) { jc_region_gabarite = new ERegionGabarite(20.0f, 20.0f); }
			else
				if (j == 2) { jc_region_gabarite = new ERegionGabarite(50.0f, 20.0f); }*/

		EInputCore::logger_param("vector size", whole_filter_block_data->pointer_to_non_listed_segment->group_list.size());
	}


	if (_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED)
	{
		target_group_for_content = whole_filter_block_data->pointer_to_listed_segment;

		EButtonGroup* listed_condition_group_container = create_block_for_listed_segment
		(
			_filter_block_attribute->filter_rule,
			_filter_block_attribute->localisation.base_name,
			target_group_for_content
		);


		EButtonGroup::change_group(target_group_for_content);
	}


	if
		(
			(_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)
			&&
			(false)
			)
	{
		target_group_for_content = whole_filter_block_data->pointer_to_cosmetic_segment;

		switch (_filter_block_attribute->filter_attribute_value_type)
		{
		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR:
		{
			Helper::HRA_color_collection* HRA_collection = Helper::registered_color_list[rand() % Helper::registered_color_list.size()];
			Helper::HSVRGBAColor* HRA_color = &HRA_collection->target_color;


			EntityButton* jc_button = EntityButton::create_named_color_button
			(
				new ERegionGabarite(242.0f, 38.0f),
				target_group_for_content,
				EFont::font_list[0],
				EGUIStyle::active_style,
				_filter_block_attribute->localisation.localisations[NSW_localisation_RU],
				HRA_collection,
				HRA_color,
				ColorButtonMode::CBM_OPEN_WINDOW
			);
			Entity::get_last_text_area(jc_button)->localisation_text = _filter_block_attribute->localisation;

			target_group_for_content->button_list.push_back(jc_button);

			EButtonGroup::change_group(target_group_for_content);
			break;
		}

		default:
		{

		}
		}
	}


}

std::string generate_filter_block_text(EButtonGroup* _button_group)
{
	std::string result_string = "";

	result_string += "Show";
	result_string += '\r';
	result_string += '\n';

	auto whole_block_data = static_cast<EButtonGroupFilterBlock*>(_button_group);

	EButtonGroup* non_listed_section = whole_block_data->pointer_to_non_listed_segment;
	EButtonGroup* listed_section = whole_block_data->pointer_to_listed_segment;
	EButtonGroup* cosmetic_section = whole_block_data->pointer_to_cosmetic_segment;

	//NON-LISTED
	for (EButtonGroup* n_listed : non_listed_section->group_list)
	{
		auto container = static_cast<EDataContainer_Group_FilterBlockNonListedSegment*>(n_listed->data_container);

		result_string
			+=
			'\t'
			+
			container->
			target_button_with_attribute_name->
			custom_data_list.back()->
			clickable_area_list.back()->
			text_area->
			localisation_text.base_name;

		if (container->target_button_with_condition != nullptr)
		{
			result_string += " ";
			result_string += *(Entity::get_last_text_area(container->target_button_with_condition)->stored_text);
		}

		//bool attribute
		if (container->target_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER)
		{
			result_string += " ";
			if (*static_cast <EDataContainer_Button_BoolSwitcher*>(container->target_button_with_value->custom_data_list.back()->data_container)->target_value)
			{
				result_string += "True";
			}
			else
			{
				result_string += "False";
			}
		}

		//bool attribute
		if
			(
				(container->target_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER)
				||
				(container->target_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT)
				)
		{
			result_string += " ";
			result_string += *(Entity::get_last_text_area(container->target_button_with_value)->stored_text);
		}

		if (container->target_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST)
		{
			result_string += " ";
			result_string += Entity::get_last_text_area(container->target_button_with_value)->localisation_text.base_name;
		}


		if (container->target_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST)
		{
			result_string += " ";
			result_string += Entity::get_last_text_area(container->target_button_with_value)->localisation_text.base_name;
		}

		result_string += '\r';
		result_string += '\n';
	}

	//LISTED

	for (EButtonGroup* listed : listed_section->group_list)
	{
		auto container = static_cast<EDataContainer_Group_FilterBlockListedSegment*>(listed->data_container);


		if ((container != nullptr) && (container->group_with_listed_buttons->button_list.size() > 1))
		{
			result_string += '\t' + container->filter_attribute_name;

			int id = 0;

			for (EntityButton* listed_button : container->group_with_listed_buttons->button_list)\
				if (listed_button != container->group_with_listed_buttons->slider)
				{

					if (Entity::get_last_text_area(listed_button) != nullptr)
					{
						result_string += " ";
						result_string += '"' + Entity::get_last_text_area(listed_button)->localisation_text.base_name + '"';
					}
					else
					{
						EInputCore::logger_simple_error("TextArea is NULL! [" + std::to_string(id) + "]");
					}

					id++;
				}

			result_string += '\r';
			result_string += '\n';
		}
		else
		{
			EInputCore::logger_simple_error("listed button group have no data container!");
		}

	}

	//COSMETIC

		//auto container = static_cast<EDataContainer*>(listed->data_container);
		//for (EntityButton* cbut : cosmetic_section->button_list)
		//if (cbut != cosmetic_section->slider)
		//{
		//	//if
		//	//(
		//	//	cbut->custom_data_list[0]->data_container == 
		//	//)
		//}

	auto cosmetic_data = static_cast<EButtonGroupFilterBlock*>(whole_block_data);
	ETextArea* tarea = nullptr;

	for (int i = 0; i < 3; i++)
	{
		result_string += '\t';
		if (!cosmetic_data->color_check[i])
		{
			result_string += "#";
		}
		tarea = Entity::get_last_text_area(cosmetic_data->pointer_to_color_button[i]);

		if (tarea != nullptr)
		{
			result_string += tarea->localisation_text.base_name;
		}
		auto store_color_data = static_cast<EDataContainer_Button_StoreColor*>(Entity::get_last_custom_data(cosmetic_data->pointer_to_color_button[i])->data_container);

		result_string += " " + std::to_string((int)round(store_color_data->stored_color->r * 255.0f));
		result_string += " " + std::to_string((int)round(store_color_data->stored_color->g * 255.0f));
		result_string += " " + std::to_string((int)round(store_color_data->stored_color->b * 255.0f));
		result_string += " " + std::to_string((int)round(store_color_data->stored_color->a * 255.0f));

		result_string += '\r';
		result_string += '\n';
	}


	//font size
	if (!cosmetic_data->text_size_bool)
	{
		result_string += "#";
	}
	tarea = Entity::get_last_text_area(cosmetic_data->text_size_button);

	result_string += tarea->localisation_text.base_name;

	result_string += " " + std::to_string((int)(round(18.0f + cosmetic_data->text_size * 27.0f)));


	return result_string;
}

EButtonGroup* create_block_for_listed_segment(EFilterRule* _filter_rule, std::string _attribute_name, EButtonGroup* _parent)
{
	EButtonGroup* main_listed_group = EButtonGroup::create_default_button_group(new ERegionGabarite(800.0f, 100.0f), EGUIStyle::active_style)
		->
		set_parameters
		(
			ChildAlignMode::ALIGN_HORIZONTAL,
			NSW_dynamic_autosize,
			NSW_dynamic_autosize
		);

	main_listed_group->min_size_y = 120.0f;

	//data container, store pointer to group with listed buttons
	auto d_container = new EDataContainer_Group_FilterBlockListedSegment();
	d_container->filter_attribute_name = _attribute_name;


	main_listed_group->data_container = d_container;

	_parent->add_group(main_listed_group);

	////////////////////////
	//small subrow for additional buttons




	//side group for buttons
	EButtonGroup* listed_group_left_side = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(134.0f, 80.0f), EGUIStyle::active_style)
		->
		set_parameters
		(
			ChildAlignMode::ALIGN_HORIZONTAL,
			NSW_static_autosize,
			NSW_dynamic_autosize
		);
	main_listed_group->add_group(listed_group_left_side);

	float vertical_borders = listed_group_left_side->border_left + listed_group_left_side->border_right;

	////////////////////////
	//ADD NEW ITEM BUTTON
	EntityButton* small_button = new EntityButtonForFilterBlock();
	small_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(130.0f, 18.0f),
		listed_group_left_side,
		&EDataActionCollection::action_open_data_entity_filter_group,
		"Add new item"
	);


	//data conatainer with filter rule (for data entity list)
	EDataContainer_Group_StoreFilterRuleForDataEntitySearcher*
		data_store_filter_rule = new EDataContainer_Group_StoreFilterRuleForDataEntitySearcher();
	data_store_filter_rule->filter_rule = _filter_rule;
	data_store_filter_rule->target_action_on_click = &EDataActionCollection::action_add_wide_item_to_group_receiver;
	EntityButton::get_last_custom_data(small_button)->data_container = data_store_filter_rule;

	d_container->data_container_with_filter_rule = data_store_filter_rule;

	listed_group_left_side->button_list.push_back(small_button);
	////////////////////////

	////////////////////////
	//REMOVE ALL BUTTONS
	small_button = new EntityButtonForFilterBlock();
	small_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(130.0f, 18.0f),
		listed_group_left_side,
		nullptr,
		"Удалить блок"
	);
	listed_group_left_side->button_list.push_back(small_button);
	////////////////////////



	////////////////////////
	//MAIN SECTION
	EButtonGroup* listed_group_main_section = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(600.0f, 80.0f), EGUIStyle::active_style)
		->
		set_parameters
		(
			ChildAlignMode::ALIGN_HORIZONTAL,
			NSW_dynamic_autosize,
			NSW_dynamic_autosize
		);

	main_listed_group->add_group(listed_group_main_section);
	data_store_filter_rule->target_group = listed_group_main_section;

	d_container->group_with_listed_buttons = listed_group_main_section;
	////////////////////////

	return main_listed_group;
}

EntityButtonForFilterBlock::EntityButtonForFilterBlock()
{
	if (debug_deleting) EInputCore::logger_simple_info("<EntityButtonFilterBlock> created");
}

EntityButtonForFilterBlock::~EntityButtonForFilterBlock()
{
	if (debug_deleting) EInputCore::logger_simple_info("Called <EntityButtonFilterBlock> destructor");
}

EntityButtonForLootFilterSelector::EntityButtonForLootFilterSelector()
{
}

EntityButtonForLootFilterSelector::~EntityButtonForLootFilterSelector()
{
}

void EButtonGroupTopControlSection::draw()
{
	EButtonGroup::draw();

	EButtonGroupFilterBlock* d_con = pointer_to_filter_block_group;

	float font_size_rescale = 0.4f + d_con->text_size * 0.6f;

	float rescale_factor = min((box_size_x * font_size_rescale) / (float)(*example_text_texture[0]->size_x_in_pixels + 6.0f), (region_gabarite->size_y * font_size_rescale) / (float)(*example_text_texture[0]->size_y_in_pixels + 6.0f));
	rescale_factor = min(rescale_factor, 1.0f);

	int array_id = round(1.0f - rescale_factor);

	//rescale_factor *= font_size_rescale;

	float
		pos_x =
		pointer_to_filter_block_group->pointer_to_top_control_block->region_gabarite->world_position_x
		+
		pointer_to_filter_block_group->pointer_to_top_control_block->region_gabarite->size_x;



	float
		pos_y = pointer_to_filter_block_group->pointer_to_top_control_block->region_gabarite->world_position_y;

	pos_x -= box_size_x * (font_size_rescale * 0.5f + 0.5f);
	//pos_x += box_size_x * (1.0f - font_size_rescale) * 0.5f;

	pos_y += region_gabarite->size_y * (1.0f - font_size_rescale) * 0.5f;

	//static background
	NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		//x pos
		pos_x,

		//y pos
		pos_y,

		box_size_x * font_size_rescale,
		region_gabarite->size_y * font_size_rescale,

		example_text_bg

	);





	NS_EGraphicCore::set_active_color(*d_con->pointer_to_HRA_color[0]);
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		//x pos
		pos_x,

		//y pos
		pos_y,

		box_size_x * font_size_rescale,
		region_gabarite->size_y * font_size_rescale,

		NS_DefaultGabarites::texture_gabarite_white_pixel

	);

	NS_EGraphicCore::set_active_color(*d_con->pointer_to_HRA_color[1]);
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		//x pos
		pos_x + (box_size_x * font_size_rescale - *example_text_texture[0]->size_x_in_pixels * rescale_factor) / 2.0f,

		//y pos
		pos_y + (region_gabarite->size_y * font_size_rescale - *example_text_texture[0]->size_y_in_pixels * rescale_factor) / 2.0f - 1.0f * font_size_rescale,

		*example_text_texture[0]->size_x_in_pixels * rescale_factor,
		*example_text_texture[0]->size_y_in_pixels * rescale_factor,

		example_text_texture[array_id]
	);

	NS_EGraphicCore::set_active_color(*d_con->pointer_to_HRA_color[2]);
	ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
	NS_ERenderCollection::add_data_to_vertex_buffer_rama
	(
		NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
		NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

		//x pos
		pos_x,

		//y pos
		pos_y,

		box_size_x * font_size_rescale,
		region_gabarite->size_y * font_size_rescale,

		2.0f * (font_size_rescale * 0.5f + 0.5f),

		NS_DefaultGabarites::texture_gabarite_white_pixel

	);
	//std::cout << "!";
}

void EButtonGroupFilterBlock::update(float _d)
{
	EButtonGroup::update(_d);

	if (EButtonGroup::catched_by_mouse(this))
	{
		if (!pointer_to_top_control_block->is_active)
		{
			pointer_to_top_control_block->is_active = true;
			pointer_to_top_control_block->group_phantom_redraw = true;

			//change_group(pointer_to_top_control_block);
		}
	}
	else
	{
		if (pointer_to_top_control_block->is_active)
		{
			pointer_to_top_control_block->is_active = false;
			pointer_to_top_control_block->group_phantom_redraw = true;
			//change_group(pointer_to_top_control_block);
		}
	};
}
