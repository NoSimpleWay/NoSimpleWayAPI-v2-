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

/**/
#ifndef _IRR_KLANG_ALREADY_LINKED_
#define _IRR_KLANG_ALREADY_LINKED_
#include <irr/irrKlang.h>
#endif
/**/

#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "NoSimpleWayAPI[v2]/EGraphicCore.h"
#endif

#include <chrono>
#include <windows.h>
#include <Lmcons.h>
#include <shlobj.h>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>




//class Entity;
EWindowMain* EWindowMain::link_to_main_window;

EButtonGroup*												EWindowMain::select_rarity_button_group;
EButtonGroup*												EWindowMain::select_quality_button_group;
EButtonGroupFilterBlockEditor*								EWindowMain::loot_filter_editor;
EButtonGroup*												EWindowMain::world_parameters;
EButtonGroup*												EWindowMain::tab_list_group;
EButtonGroupNewLootFilter*									EWindowMain::create_new_loot_filter_group;
EButtonGroupDataEntity*										EWindowMain::data_entity_filter = nullptr;
EButtonGroupBottomFilterBlockControl*						EWindowMain::bottom_filter_block_control = nullptr;
EButtonGroupLootSimulator*									EWindowMain::loot_simulator_button_group = nullptr;



std::string													EWindowMain::username;
std::string													EWindowMain::path_of_exile_folder;

RouterVariant*												EWindowMain::registered_rarity_router_variants[NSW_registered_rarity_count];
RouterVariant*												EWindowMain::registered_alternate_gem_quality_router_variants[NSW_registered_altered_gem_quality_count];

std::vector < std::string>									EWindowMain::filter_text_lines;
std::vector <EButtonGroupFilterBlockEditor*>				EWindowMain::filter_block_tabs = std::vector<EButtonGroupFilterBlockEditor*>(filter_tabs_count);

std::vector<ENamedSound*>									EWindowMain::default_sound_list;
std::vector<ENamedSound*>									EWindowMain::custom_sound_list;

GameItemAttribute* GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::_GAME_ATTRIBUTE_LAST_ELEMENT];

namespace NS_DefaultGabarites
{
	ETextureGabarite* texture_example_text_for_preview_box;
	ETextureGabarite* texture_example_text_for_preview_box_half;
	ETextureGabarite* texture_example_text_bg_for_preview_box;

	ETextureGabarite* texture_loot_version_full_ignore;
	ETextureGabarite* texture_loot_version_hide;
	ETextureGabarite* texture_loot_version_ignore;
	ETextureGabarite* texture_loot_version_default;
	ETextureGabarite* texture_loot_version_focus;

	ETextureGabarite* texture_show_hide_visual_editor;
	ETextureGabarite* texture_show_hide_visual_editor_deactivate;

	ETextureGabarite* texture_minimap_shape_circle;
	ETextureGabarite* texture_minimap_shape_diamond;
	ETextureGabarite* texture_minimap_shape_hexagon;
	ETextureGabarite* texture_minimap_shape_square;
	ETextureGabarite* texture_minimap_shape_star;
	ETextureGabarite* texture_minimap_shape_triangle;
	ETextureGabarite* texture_minimap_shape_cross;
	ETextureGabarite* texture_minimap_shape_moon;
	ETextureGabarite* texture_minimap_shape_raindrop;
	ETextureGabarite* texture_minimap_shape_kite;
	ETextureGabarite* texture_minimap_shape_pentagon;
	ETextureGabarite* texture_minimap_shape_upside_down_house;

	ETextureGabarite* texture_button_plus;

	ETextureGabarite* texture_button_move_up;
	ETextureGabarite* texture_button_move_down;
	ETextureGabarite* texture_button_move;
	ETextureGabarite* texture_button_cut;

	ETextureGabarite* texture_button_remove_filter_block;

	ETextureGabarite* texture_ray;


}

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


	ETextArea* target_text_area = static_cast<EDataContainer_Group_TextSelectorFromVariants*>(root_container)->target_button->main_text_area;

	//target_text_area->localisation_text = clicked_button_text_area->localisation_text;
	//*target_text_area->stored_text = *EntityButton::get_last_clickable_area(static_cast<EntityButton*>(_entity))->text_area->stored_text;

	//transfer parameters from [select rarity button] to [non-listed button]
	target_text_area->stored_color = clicked_button_text_area->stored_color;
	target_text_area->color = clicked_button_text_area->color;
	target_text_area->localisation_text = clicked_button_text_area->localisation_text;

	target_text_area->change_text(clicked_button_text_area->localisation_text.localisations[ELocalisationText::active_localisation]);

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
		if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(group))//filter block
		{
			str += generate_filter_block_text(group, FilterBlockSaveMode::VERSION_ORIGINAL);
			str += '\n';
		}
		else
			if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(group))//filter block separator
			{
				str += generate_filter_block_separator_text(static_cast<EButtonGroupFilterBlockSeparator*>(group), FilterBlockSaveMode::VERSION_ORIGINAL);
			}
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
	EDataContainer_Group_DataEntitiesSearch* button_group_data_container = (EDataContainer_Group_DataEntitiesSearch*)EWindowMain::data_entity_filter->data_container;

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
		//group->need_remove = true;
		delete group;
	}

	EWindowMain::loot_filter_editor->group_list.clear();

	EButtonGroup::existing_loot_filter_list->is_active = false;

	EWindowMain::tab_list_group->selected_button->main_text_area->change_text(((EntityButtonForLootFilterSelector*)_entity)->filter_name);




	EWindowMain::open_loot_filter(((EntityButtonForLootFilterSelector*)_entity)->loot_filter_full_path, LootFlterOpenMode::LOOT_FILTER_OPEN_MODE_USER_FILTER_FROM_DISC);

	EButtonGroupFilterBlockSeparator*
		separator = EWindowMain::create_filter_block_separator(EWindowMain::loot_filter_editor, -1);
	separator->pointer_to_description_button->main_text_area->change_text("DEFAULT FILTER BLOCKS");
	separator->is_expanded = false;
	separator->autogenerated_do_dot_save = true;

	EWindowMain::open_loot_filter("data/default_loot_filter.filter", LootFlterOpenMode::LOOT_FILTER_OPEN_MODE_DEFAULT_FILTER_FROM_GAME);





	for (EButtonGroup* group : EWindowMain::loot_filter_editor->group_list)
	{
		if (group->suppressed) { group->recursive_set_suppressed(); }
	}

	//EWindowMain::loot_filter_editor->realign_groups();
	EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);

	EWindowMain::loot_simulator_button_group->refresh_loot_simulator();

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

void EDataActionCollection::action_import_filter_text_from_clipboard(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (!OpenClipboard(nullptr))
	{
	}

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr)
	{
	}

	// Lock the handle to get the actual text pointer
	char* pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr)
	{
	}

	// Save text in a string class instance
	std::string clipboard_text(pszText);

	std::string full_text = clipboard_text;

	EWindowMain::filter_text_lines.clear();
	std::string buffer = "";

	for (int i = 0; i < full_text.length(); i++)
	{

		if ((full_text[i] == '\r') || (full_text[i] == '\n') || (i + 1 >= full_text.length()))
		{
			if (i + 1 >= full_text.length())
			{
				buffer += full_text[i];
			}

			EWindowMain::filter_text_lines.push_back(buffer);
			buffer = "";
		}

		if
			(
				(
					(i < full_text.length())
					&&
					(full_text[i] != '\r')
					&&
					(full_text[i] != '\n')
					)

				)
		{
			buffer += full_text[i];
		}
	}

	//text = clipboard_text;

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	EWindowMain::parse_filter_text_lines(static_cast<EntityButtonForFilterBlock*>(_entity)->parent_filter_block, LootFlterOpenMode::LOOT_FILTER_OPEN_MODE_USER_FILTER_FROM_DISC);

	EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);


}

void EDataActionCollection::action_add_text_as_item(Entity* _entity, ECustomData* _custom_data, float _d)
{
	auto data_entity_container = static_cast<EDataContainer_Group_DataEntitiesSearch*>(static_cast<EntityButton*>(_entity)->parent_button_group->root_group->data_container);

	EntityButton* wide_button = EntityButton::create_wide_item_button
	(
		new ERegionGabarite(220.0f, 40.0f),
		data_entity_container->pointer_to_group_item_receiver,
		nullptr,
		EFont::font_list[0]
	);

	data_entity_container->pointer_to_group_item_receiver->button_list.push_back(wide_button);

	ELocalisationText l_text;
	l_text.base_name = data_entity_container->filter_text_area->original_text;
	l_text.localisations[NSW_localisation_EN] = data_entity_container->filter_text_area->original_text;
	l_text.localisations[NSW_localisation_RU] = data_entity_container->filter_text_area->original_text;

	Entity::get_last_text_area(wide_button)->localisation_text = l_text;
	Entity::get_last_text_area(wide_button)->change_text(l_text.localisations[ELocalisationText::active_localisation]);

	EButtonGroup::change_group(data_entity_container->pointer_to_group_item_receiver);
	((EntityButton*)(_entity))->parent_button_group->root_group->is_active = false;
}

void EDataActionCollection::action_add_new_filter_block(Entity* _entity, ECustomData* _custom_data, float _d)
{
	int position = -1;

	EDataContainer* base_container = ((EntityButton*)_entity)->parent_button_group->root_group->data_container;
	EDataContainer_Group_AddContentToFilterBlock* data_container = (EDataContainer_Group_AddContentToFilterBlock*)base_container;
	EButtonGroupFilterBlock* filter_block = data_container->target_filter_block;

	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
	{
		if (EWindowMain::loot_filter_editor->group_list[i] == filter_block)
		{
			position = i;
		}
	}

	EWindowMain::create_filter_block(EWindowMain::loot_filter_editor, position);

	EWindowMain::loot_filter_editor->group_list[position]->highlight_this_group();

	EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);

	if (!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{
		EButtonGroup::add_content_to_filter_block_group->is_active = false;
	}

	EInputCore::NSW_have_unsave_changes = true;

	EWindowMain::loot_simulator_button_group->refresh_loot_simulator();
}

void EDataActionCollection::action_open_custom_sound_list(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup::sound_list_group->is_active = true;
	EButtonGroup::sound_list_group->target_sound_button = static_cast<EntityButtonFilterSound*>(_entity);
	EButtonGroup::sound_list_group->move_to_foreground();

	EButtonGroup::sound_list_group->action_on_select_for_button = &EDataActionCollection::action_select_this_sound_for_target_button;
	//EWindowMain::load_custom_sound_list();

	EButtonGroup::sound_list_group->pointer_to_sound_list = &EWindowMain::custom_sound_list;

	EButtonGroup::sound_list_group->refresh_sound_list();
	EButtonGroup::refresh_button_group(EButtonGroup::sound_list_group);
}

void EDataActionCollection::action_open_ingame_sound_list(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup::sound_list_group->is_active = true;
	EButtonGroup::sound_list_group->target_sound_button = static_cast<EntityButtonFilterSound*>(_entity);
	EButtonGroup::sound_list_group->move_to_foreground();

	EButtonGroup::sound_list_group->action_on_select_for_button = &EDataActionCollection::action_select_this_sound_for_target_button;
	//EWindowMain::load_custom_sound_list();

	EButtonGroup::sound_list_group->pointer_to_sound_list = &EWindowMain::default_sound_list;

	EButtonGroup::sound_list_group->refresh_sound_list();
	EButtonGroup::refresh_button_group(EButtonGroup::sound_list_group);
}

void EDataActionCollection::action_play_attached_sound(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if
		(
			(static_cast<EntityButtonFilterSound*>(_entity)->stored_named_sound != nullptr)
			&&
			(static_cast<EntityButtonFilterSound*>(_entity)->stored_named_sound->sound != nullptr)
			)
	{
		static_cast<EntityButtonFilterSound*>(_entity)->stored_named_sound->sound->setDefaultVolume(0.2f);
		ESound::engine->play2D(((EntityButtonFilterSound*)_entity)->stored_named_sound->sound);
	}
	else
	{
		if (static_cast<EntityButtonFilterSound*>(_entity)->stored_named_sound == nullptr)
		{
			EInputCore::logger_simple_error("target named sound is NULL!");
		}
		else
		{
			if (static_cast<EntityButtonFilterSound*>(_entity)->stored_named_sound->sound == nullptr)
			{
				EInputCore::logger_simple_error("stored sound is NULL!");
			}
		}
	}
}

void EDataActionCollection::action_invoke_button_action_in_sound_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonFilterSound* sound_button = static_cast<EntityButtonFilterSound*>(_entity);

	if (sound_button->target_sound_group != nullptr)
	{
		if (sound_button->target_sound_group->action_on_select_for_button != nullptr)
		{
			sound_button->target_sound_group->action_on_select_for_button(sound_button, _custom_data, _d);
		}

		sound_button->target_sound_group->is_active = false;
	}
}

void EDataActionCollection::action_show_hide_cosmetic_blocks(Entity* _entity, ECustomData* _custom_data, float _d)
{
	auto but = static_cast<EntityButtonVariantRouterForFilterBlock*>(_entity);

	//but->parent_filter_block->pointer_to_cosmetic_segment	->is_active									= but->selected_variant;
	but->parent_filter_block->pointer_to_sound_segment->is_active = but->selected_variant;
	but->parent_filter_block->pointer_to_minimap_segment->is_active = but->selected_variant;
	but->parent_filter_block->pointer_to_ray_segment->is_active = but->selected_variant;



	//but->parent_filter_block->pointer_to_cosmetic_segment->region_gabarite->have_phantom_translation	= false;
	but->parent_filter_block->pointer_to_sound_segment->region_gabarite->have_phantom_translation = false;
	but->parent_filter_block->pointer_to_minimap_segment->region_gabarite->have_phantom_translation = false;
	but->parent_filter_block->pointer_to_ray_segment->region_gabarite->have_phantom_translation = false;



	EButtonGroup::change_group(but->parent_filter_block);
}

void EDataActionCollection::action_select_this_sound_for_target_button(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroupSoundList*
		sound_group = EButtonGroup::sound_list_group;

	if
		(
			(sound_group->target_sound_button != nullptr)
			)
	{
		sound_group->target_sound_button->stored_named_sound = static_cast<EntityButtonFilterSound*>(_entity)->stored_named_sound;
	}

}

void EDataActionCollection::action_select_this_tab(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonFilterBlockTab* tab_button = static_cast<EntityButtonFilterBlockTab*>(_entity);



	int id = -1;

	//search matched EButtonGroup
	for (int i = 0; i < EWindowMain::link_to_main_window->button_group_list.size(); i++)
		if (EWindowMain::link_to_main_window->button_group_list[i] == EWindowMain::loot_filter_editor)
		{
			EWindowMain::link_to_main_window->button_group_list[i] = EWindowMain::filter_block_tabs[tab_button->tab_id];
			break;
		}

	for (int i = 0; i < EWindowMain::link_to_main_window->autosize_group_list.size(); i++)
		if (EWindowMain::link_to_main_window->autosize_group_list[i] == EWindowMain::loot_filter_editor)
		{
			EWindowMain::link_to_main_window->autosize_group_list[i] = EWindowMain::filter_block_tabs[tab_button->tab_id];
			break;
		}



	EWindowMain::loot_filter_editor = EWindowMain::filter_block_tabs[tab_button->tab_id];

	for (EWindow* w : EWindow::window_list)
	{
		NS_EGraphicCore::refresh_autosize_groups(w);
	}

	EButtonGroup::change_group(EWindowMain::loot_filter_editor);

}

void EDataActionCollection::action_create_new_loot_filter_with_name(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton* but = static_cast<EntityButton*>(_entity);

	if
		(
			(but->parent_button_group != nullptr)
			&&
			(but->parent_button_group->root_group != nullptr)
			)
	{
		std::string new_loot_filter_name = static_cast<EButtonGroupNewLootFilter*>(but->parent_button_group->root_group)->input_field_button->main_text_area->original_text;

		EntityButtonFilterBlockTab*
			tab = static_cast<EntityButtonFilterBlockTab*>(EWindowMain::tab_list_group->selected_button);

		EButtonGroup*
			filter_editor = tab->target_filter_editor;

		for (EButtonGroup* button_group : filter_editor->group_list)
		{
			delete button_group;
		};

		filter_editor->group_list.clear();
		filter_editor->group_list.shrink_to_fit();

		tab->main_text_area->change_text(new_loot_filter_name);

		EButtonGroupFilterBlock* created_filter_block = EWindowMain::create_filter_block(filter_editor, -1);

		filter_editor->scroll_y = 0.0f;
		EButtonGroup::refresh_button_group(filter_editor);

		EWindowMain::create_new_loot_filter_group->is_active = false;

		EDataActionCollection::action_save_lootfilter(_entity, _custom_data, _d);
	}
}

void EDataActionCollection::action_open_new_lootfilter_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EWindowMain::create_new_loot_filter_group->is_active = true;
	EWindowMain::create_new_loot_filter_group->move_to_foreground();
	EWindowMain::create_new_loot_filter_group->input_field_button->main_text_area->change_text("");
}

void EDataActionCollection::action_clone_block(Entity* _entity, ECustomData* _custom_data, float _d)
{


	EDataContainer* base_container = ((EntityButton*)_entity)->parent_button_group->root_group->data_container;
	EDataContainer_Group_AddContentToFilterBlock* data_container = (EDataContainer_Group_AddContentToFilterBlock*)base_container;
	EButtonGroupFilterBlock* filter_block = data_container->target_filter_block;

	int position = -1;
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
	{
		if (EWindowMain::loot_filter_editor->group_list[i] == filter_block)
		{
			position = i;


		}
	}

	if (position >= 0)
	{
		std::string full_text = "";
		full_text += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[position], FilterBlockSaveMode::VERSION_ORIGINAL);

		generate_filter_lines_from_text(full_text);
	}

	EWindowMain::parse_filter_text_lines(filter_block, LootFlterOpenMode::LOOT_FILTER_OPEN_MODE_USER_FILTER_FROM_DISC);

	EWindowMain::loot_filter_editor->group_list[position]->highlight_this_group();

	EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);

	if (!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{
		EButtonGroup::add_content_to_filter_block_group->is_active = false;
	}

	EWindowMain::loot_simulator_button_group->refresh_loot_simulator();
}

void EDataActionCollection::action_add_separator_block(Entity* _entity, ECustomData* _custom_data, float _d)
{
	int position = -1;

	EDataContainer* base_container = ((EntityButton*)_entity)->parent_button_group->root_group->data_container;
	EDataContainer_Group_AddContentToFilterBlock* data_container = (EDataContainer_Group_AddContentToFilterBlock*)base_container;
	EButtonGroupFilterBlock* filter_block = data_container->target_filter_block;

	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
	{
		if (EWindowMain::loot_filter_editor->group_list[i] == filter_block)
		{
			position = i;
		}
	}

	EWindowMain::create_filter_block_separator(EWindowMain::loot_filter_editor, position);

	EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);

	if (!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{
		EButtonGroup::add_content_to_filter_block_group->is_active = false;
	}
}

void EDataActionCollection::generate_filter_lines_from_text(std::string& full_text)
{
	EWindowMain::filter_text_lines.clear();
	std::string buffer = "";

	for (int i = 0; i < full_text.length(); i++)
	{

		if ((full_text[i] == '\r') || (full_text[i] == '\n') || (i + 1 >= full_text.length()))
		{
			if (i + 1 >= full_text.length())
			{
				buffer += full_text[i];
			}

			EWindowMain::filter_text_lines.push_back(buffer);
			buffer = "";
		}

		if
			(
				(
					(i < full_text.length())
					&&
					(full_text[i] != '\r')
					&&
					(full_text[i] != '\n')
					)

				)
		{
			buffer += full_text[i];
		}
	}
}

void EDataActionCollection::action_remove_filter_block(Entity* _entity, ECustomData* _custom_data, float _d)
{
	static_cast<EntityButtonForFilterBlock*>(_entity)->parent_filter_block->need_remove = true;
	if (EWindowMain::loot_filter_editor->group_list.size() <= 1)
	{
		EWindowMain::create_filter_block(EWindowMain::loot_filter_editor, -1);
		EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);
	}

	EWindowMain::loot_simulator_button_group->refresh_loot_simulator();

}

void EDataActionCollection::action_move_filter_block_up(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroupFilterBlock*
		parent_filter_block = static_cast<EntityButtonForFilterBlock*>(_entity)->parent_filter_block;

	int vector_position = -1;

	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (EWindowMain::loot_filter_editor->group_list[i] == parent_filter_block)
		{
			vector_position = i;
		}

	if (vector_position > 0)
	{
		EButtonGroupFilterBlock*
			swap = parent_filter_block;
		EWindowMain::loot_filter_editor->group_list[vector_position] = EWindowMain::loot_filter_editor->group_list[vector_position - 1];
		EWindowMain::loot_filter_editor->group_list[vector_position - 1] = swap;

		EButtonGroup::change_group(EWindowMain::loot_filter_editor);
	}
}

void EDataActionCollection::action_move_filter_block_down(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroupFilterBlock*
		parent_filter_block = static_cast<EntityButtonForFilterBlock*>(_entity)->parent_filter_block;

	int vector_position = -1;

	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (EWindowMain::loot_filter_editor->group_list[i] == parent_filter_block)
		{
			vector_position = i;
		}

	if ((vector_position >= 0) && (vector_position < EWindowMain::loot_filter_editor->group_list.size()))
	{
		EButtonGroupFilterBlock*
			swap = parent_filter_block;
		EWindowMain::loot_filter_editor->group_list[vector_position] = EWindowMain::loot_filter_editor->group_list[vector_position + 1];
		EWindowMain::loot_filter_editor->group_list[vector_position + 1] = swap;

		EButtonGroup::change_group(EWindowMain::loot_filter_editor);
	}
}

void EDataActionCollection::action_move_filter_block(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup::vector_moving_group = static_cast<EntityButtonForFilterBlock*>(_entity)->parent_filter_block;
	EButtonGroup::parent_vector_moving_group = static_cast<EntityButtonForFilterBlock*>(_entity)->parent_button_group->root_group;

	EButtonGroup::move_vector_mode = MoveVectorMethod::METHOD_DRAG;
}

void EDataActionCollection::action_move_button_group(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EButtonGroup::vector_moving_group = static_cast<EntityButtonMoveButtonGroup*>(_entity)->target_group_for_moving;
	EButtonGroup::parent_vector_moving_group = static_cast<EntityButtonMoveButtonGroup*>(_entity)->parent_group_for_moving;

	EButtonGroup::move_vector_mode = static_cast<EntityButtonMoveButtonGroup*>(_entity)->move_method;
}

void EDataActionCollection::action_delete_listed_segment(Entity* _entity, ECustomData* _custom_data, float _d)
{
	static_cast<EntityButtonForListedSegment*>(_entity)->listed_group->need_remove = true;
}

void EDataActionCollection::action_open_data_entity_filter_group(Entity* _entity, ECustomData* _custom_data, float _d)
{

	EInputCore::logger_simple_info("???");
	EDataContainer_Group_StoreFilterRuleForDataEntitySearcher* button_data_container = ((EDataContainer_Group_StoreFilterRuleForDataEntitySearcher*)_custom_data->data_container);
	EDataContainer_Group_DataEntitiesSearch* button_group_data_container = (EDataContainer_Group_DataEntitiesSearch*)EWindowMain::data_entity_filter->data_container;

	EWindowMain::data_entity_filter->is_active = true;
	EWindowMain::data_entity_filter->move_to_foreground();

	button_group_data_container->pointer_to_group_item_receiver = button_data_container->target_group;
	button_group_data_container->target_rule = button_data_container->filter_rule;
	button_group_data_container->action_on_select_for_button = button_data_container->target_action_on_click;

	for (EntityButton* but : EWindowMain::data_entity_filter->right_side_for_filters->button_list)
		if (but != EWindowMain::data_entity_filter->right_side_for_filters->slider)
		{
			EntityButtonFilterRule* button_rule = static_cast<EntityButtonFilterRule*>(but);
			if
				(
					(button_rule->target_filter_rule->tag == button_data_container->filter_rule->focused_by_data_type)
					||
					(button_rule->target_filter_rule->tag == "*ALL*")
					)
			{
				button_rule->disabled = false;
			}
			else
			{
				button_rule->disabled = true;
			}
		}

	EDataActionCollection::action_type_search_data_entity_text(button_group_data_container->filter_text_area);
	/* OUTDATED */
	//if
	//(
	//	(data_container_with_rule->target_rule != nullptr)
	//	&&
	//	(!data_container_with_rule->target_rule->required_tag_list.empty())
	//	&&
	//	(!data_container_with_rule->target_rule->required_tag_list[0]->suitable_values_list.empty())
	//)
	//{
	//	data_container_with_rule->target_rule->required_tag_list[0]->suitable_values_list[0] = data->search_tag;
	//}
}

void EDataActionCollection::action_change_separator_shrink_flag(Entity* _entity, ECustomData* _custom_data, float _d)
{
	//static_cast<EntityButton*>(_entity)->parent_button_group->root_group->scroll
	//EButtonGroup::change_group(static_cast<EntityButton*>(_entity)->parent_button_group->root_group);

	static_cast<EntityButton*>(_entity)->parent_button_group->root_group->need_change = true;
	static_cast<EntityButton*>(_entity)->parent_button_group->highlight_this_group();
}

void EDataActionCollection::action_clear_text(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if (EWindowMain::bottom_filter_block_control->search_button != nullptr)
	{
		EWindowMain::bottom_filter_block_control->search_button->main_text_area->change_text("");
		EDataActionCollection::action_type_search_filter_block_text(EWindowMain::bottom_filter_block_control->search_button->main_text_area);
	}
}

void EDataActionCollection::action_draw_loot_button(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton*
		entity_button = static_cast<EntityButton*>(_entity);

	EntityButtonLootItem*
		loot_button = static_cast<EntityButtonLootItem*>(_entity);

	HSVRGBAColor*
		target_temp_color = &EButtonGroupLootSimulator::temp_color;

	int selected_version_router = EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button->selected_variant;

	if
		(
			(!entity_button->disable_draw)
			&&
			(!loot_button->matched_filter_blocks.empty())
			&&
			(loot_button->matched_filter_blocks.back() != nullptr)
			&&
			(
				(
					(loot_button->matched_filter_blocks.back()->button_show_hide->selected_variant == 1)
					&&
					(loot_button->matched_filter_blocks.back()->version_routers[selected_version_router]->selected_variant != 1)
					)
				||
				(EButtonGroupLootSimulator::show_hidden)
				)
			)
	{
		if
			(
				(loot_button->matched_text_color != nullptr)
				&&
				(
					(loot_button->main_text_area->stored_color.r != (*loot_button->matched_text_color)->r)
					||
					(loot_button->main_text_area->stored_color.g != (*loot_button->matched_text_color)->g)
					||
					(loot_button->main_text_area->stored_color.b != (*loot_button->matched_text_color)->b)
					||
					(loot_button->main_text_area->stored_color.a != (*loot_button->matched_text_color)->a)
					)
				)
		{
			loot_button->main_text_area->set_color(*loot_button->matched_text_color);
			loot_button->main_text_area->generate_text();
		}

		if (loot_button->matched_bg_color != nullptr)
		{
			target_temp_color->set_color(*loot_button->matched_bg_color);
			EWindowMain::set_color_version(target_temp_color, loot_button->matched_bg_color_block->version_routers[selected_version_router]->selected_variant);
			NS_EGraphicCore::set_active_color(target_temp_color);

		}
		else
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_WHITE);
		}

		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			entity_button->button_gabarite->world_position_x,

			//y pos
			entity_button->button_gabarite->world_position_y,

			entity_button->button_gabarite->size_x,
			entity_button->button_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);




		//		RAMA
		if (loot_button->matched_rama_color != nullptr)
		{
			target_temp_color->set_color(*loot_button->matched_rama_color);
			EWindowMain::set_color_version(target_temp_color, loot_button->matched_rama_color_block->version_routers[selected_version_router]->selected_variant);
			NS_EGraphicCore::set_active_color(target_temp_color);
		}
		else
		{
			NS_EGraphicCore::set_active_color(NS_EColorUtils::COLOR_RED);
		}

		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 4);
		NS_ERenderCollection::add_data_to_vertex_buffer_rama
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			entity_button->button_gabarite->world_position_x,

			//y pos
			entity_button->button_gabarite->world_position_y,

			entity_button->button_gabarite->size_x,
			entity_button->button_gabarite->size_y,

			3.0f,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);


		//		MINIMAP ICON
		if (loot_button->matched_minimap_icon_color != nullptr)
		{
			float size_multiplier = 1.0f - loot_button->matched_minimap_icon_size->selected_variant * 0.25;
			ETextureGabarite* texture_gabarite = loot_button->matched_minimap_icon_shape->router_variant_list[loot_button->matched_minimap_icon_shape->selected_variant]->texture;

			NS_EGraphicCore::set_active_color(loot_button->matched_minimap_icon_color->router_variant_list[loot_button->matched_minimap_icon_color->selected_variant]->color);
			ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
				NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

				//x pos
				entity_button->button_gabarite->world_position_x - texture_gabarite->size_x_in_pixels * 0.5f,

				//y pos
				entity_button->button_gabarite->world_position_y,

				texture_gabarite->size_x_in_pixels * size_multiplier,
				texture_gabarite->size_y_in_pixels * size_multiplier,

				texture_gabarite
			);
		}
	}
}

void EDataActionCollection::action_refresh_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d)
{


	EWindowMain::loot_simulator_button_group->refresh_loot_simulator();

	//

}

void EDataActionCollection::action_refresh_loot_simulator_sizes(Entity* _entity, ECustomData* _custom_data, float _d)
{
	if
		(
			(EClickableArea::active_clickable_region == static_cast<EntityButton*>(_entity)->main_clickable_area)
			&&
			(EWindowMain::loot_simulator_button_group != nullptr)
			&&
			(EInputCore::MOUSE_BUTTON_LEFT)
			&&
			(EInputCore::MOUSE_SPEED_X != 0.0f)
			)
	{

		EButtonGroupLootSimulator::refresh_button_sizes();


		EButtonGroup::change_group(EButtonGroupLootSimulator::pointer_to_loot_buttons_segment);
	}
}

void EDataActionCollection::action_highlight_matched_blocks(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonLootItem*
		loot_button = static_cast<EntityButtonLootItem*>(_entity);

	if (false)
		for (EGameItemAttributeContainer attribute_container : loot_button->stored_game_item->attribute_container_list)
		{
			EInputCore::logger_param("attribute name", attribute_container.target_attribute->localisation.localisations[ELocalisationText::active_localisation]);

			if (attribute_container.attribute_value_int != 0) { EInputCore::logger_param("INT", attribute_container.attribute_value_int); }
			EInputCore::logger_param("BOOL", attribute_container.attribute_value_bool);
			if (attribute_container.attribute_value_str != "") { EInputCore::logger_param("STR", attribute_container.attribute_value_str); }

			if (!attribute_container.listed_value_list.empty())
			{
				EInputCore::logger_simple_info("Listed");
				for (ELocalisationText listed_value : attribute_container.listed_value_list)
				{
					EInputCore::logger_param("-------", listed_value.localisations[ELocalisationText::active_localisation]);
				}
			}

			std::cout << std::endl;
			std::cout << std::endl;

		}

	for (EButtonGroup* group : loot_button->matched_filter_blocks)
	{
		group->highlight_time = 0.5f;
	}

	float need_translate = 0.0f;

	if ((!loot_button->matched_filter_blocks.empty()))
	{
		if
			(
				(loot_button->matched_filter_blocks.back()->attached_separator != nullptr)
				&&
				!(loot_button->matched_filter_blocks.back()->attached_separator->is_expanded)
				)
		{
			loot_button->matched_filter_blocks.back()->attached_separator->is_expanded = true;

			EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);
		}

		EWindowMain::loot_filter_editor->scroll_y = max(-loot_button->matched_filter_blocks.back()->region_gabarite->offset_y, 0.0f);
		EWindowMain::loot_filter_editor->slider->current_value = EWindowMain::loot_filter_editor->scroll_y;

		EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);
	}

	//need_translate = -loot_button->matched_filter_blocks.back()->region_gabarite->world_position_y;

	//EWindowMain::loot_filter_editor->translate_content(0.0f, need_translate, 0.0f, false);

}

void EDataActionCollection::action_add_items_from_this_loot_pattern(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButtonLootPatternSelector*
		patter_button = static_cast<EntityButtonLootPatternSelector*>(_entity);

	EButtonGroupLootSimulator::pointer_to_patterns_buttons_segment->selected_button = patter_button;

	LootSimulatorPattern::refresh_loot_simulator(patter_button->target_pattern);
}

void EDataActionCollection::action_create_or_delete_description_on_hover(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EntityButton*
		but = static_cast<EntityButton*>(_entity);

	EntityButtonLootItem*
		loot_button = static_cast<EntityButtonLootItem*>(_entity);

	if
		(
			(EButtonGroup::focused_button_group == ((EntityButton*)_entity)->parent_button_group)
			&&
			(but->button_gabarite->overlapped_by_mouse())
			)
	{
		if (but->attached_description == nullptr)
		{
			//		MAIN GROUP
			EButtonGroup*
				main_group = new EButtonGroup
				(
					new ERegionGabarite
					(
						but->button_gabarite->world_position_x,
						but->button_gabarite->world_position_y + but->button_gabarite->size_y + 5.0f,
						0.0f,

						500.0f,
						200.0f
					)
				);
			main_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
			main_group->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_without_slider, bgroup_darken_bg);

			main_group->can_be_focused = false;
			main_group->can_be_moved = false;
			main_group->can_change_position_in_vector = false;
			//


			//		BOTTOM PART FOR ATTRIBUTES
			EButtonGroup*
				bottom_part = main_group->add_group(new EButtonGroup(new ERegionGabarite(100.0f, 100.0f)));

			bottom_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
			bottom_part->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_without_slider, bgroup_darken_bg);
			//



			//		UP PART FOR NAME
			EButtonGroup*
				up_part = main_group->add_group(new EButtonGroup(new ERegionGabarite(500.0f, 30.0f)));

			up_part->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_static_autosize);
			up_part->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_without_slider, bgroup_default_bg);
			//


			/////////////		CLICKABLE AREA FOR BOTTOM PART (ATTRIBUTES)		/////////////
			if (true)

			{
				EClickableArea*
				clickable_area_for_bottom_attributes = EClickableArea::create_default_clickable_region(bottom_part->region_gabarite, main_group);
				bottom_part->clickable_area_list.push_back(clickable_area_for_bottom_attributes);

				std::string item_attributes_generated_text = "";

				for (int i = 0; i < loot_button->stored_game_item->attribute_container_list.size(); i++)
				{
					EGameItemAttributeContainer*
						attribute_container = &loot_button->stored_game_item->attribute_container_list[i];

					if
						(
							(attribute_container->target_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER)
							&&
							(attribute_container->attribute_value_bool)
							)
					{
						item_attributes_generated_text += attribute_container->target_attribute->localisation.localisations[ELocalisationText::active_localisation];

					}
					else
						if
							(
								(attribute_container->target_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER)
								)
						{
							item_attributes_generated_text += "\\n";
							item_attributes_generated_text += attribute_container->target_attribute->localisation.localisations[ELocalisationText::active_localisation];
							item_attributes_generated_text += " ";
							item_attributes_generated_text += std::to_string(attribute_container->attribute_value_int);

						}
						else
							if
								(
									(attribute_container->target_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT)
									)
							{
								item_attributes_generated_text += "\\n";
								item_attributes_generated_text += attribute_container->target_attribute->localisation.localisations[ELocalisationText::active_localisation];
								item_attributes_generated_text += " [";
								item_attributes_generated_text += attribute_container->attribute_value_str;
								item_attributes_generated_text += "]";

							}
							else
								if
									(
										(attribute_container->target_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY)
										&&
										(true)
										)
								{
									item_attributes_generated_text += "\\n";
									item_attributes_generated_text += attribute_container->target_attribute->localisation.localisations[ELocalisationText::active_localisation];
									for (ELocalisationText listed_string : attribute_container->listed_value_list)
									{
										item_attributes_generated_text += " {";
										item_attributes_generated_text += listed_string.localisations[ELocalisationText::active_localisation];
										item_attributes_generated_text += "}";
									}


								}
				}

				ETextArea*
				text_area_for_group = ETextArea::create_centered_text_area(clickable_area_for_bottom_attributes, EFont::font_list[0], item_attributes_generated_text);
				clickable_area_for_bottom_attributes->text_area = text_area_for_group;




			}
			/////////////

			/////////////		CLICKABLE AREA FOR TOP PART (NAME)		/////////////
			if (true)
			{
				EClickableArea*
					clickable_area_for_top_name = EClickableArea::create_default_clickable_region(up_part->region_gabarite, main_group);
				up_part->clickable_area_list.push_back(clickable_area_for_top_name);

				ETextArea*
					text_area_for_group = ETextArea::create_centered_text_area
					(
						clickable_area_for_top_name,
						EFont::font_list[1],
						loot_button->stored_game_item->localised_name.localisations[ELocalisationText::active_localisation]
					);

				switch (loot_button->stored_game_item->rarity)
				{
				case 0:
				{
					text_area_for_group->set_color(1.0f, 0.9f, 0.8f, 1.0f);
					break;
				}
				case 1:
				{
					text_area_for_group->set_color(0.4f, 0.6f, 1.0f, 1.0f);
					break;
				}
				case 2:
				{
					text_area_for_group->set_color(1.0f, 0.9f, 0.35f, 1.0f);
					break;
				}
				case 3:
				{
					text_area_for_group->set_color(1.0f, 0.5f, 0.25f, 1.0f);
					break;
				}

				default:
				{
					text_area_for_group->set_color(1.0f, 0.2f, 0.1f, 1.0f);
					break;
				}
				}
				//text_area_for_group->set_color(1.0f, 0.2f, 0.1f, 1.0f);
				clickable_area_for_top_name->text_area = text_area_for_group;
			}

			but->attached_description = main_group;
			but->parent_button_group->root_group->parent_window->button_group_list.push_back(main_group);
			EButtonGroup::refresh_button_group(main_group);
		}
	}
	else
	{
		if (but->attached_description != nullptr)
		{
			but->destroy_attached_description();
		}
	}
}

void EDataActionCollection::action_open_and_refresh_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d)
{
	EWindowMain::loot_simulator_button_group->is_active = true;
	EWindowMain::loot_simulator_button_group->refresh_loot_simulator();
}

void EDataActionCollection::action_change_localisation(Entity* _entity, ECustomData* _custom_data, float _d)
{
	ELocalisationText::active_localisation = static_cast<EntityButtonLocalisationSelector*>(_entity)->stored_localisation;

	for (EWindow* w : EWindow::window_list)
		for (EButtonGroup* g : w->button_group_list)
		{
			g->recursive_change_localisation(ELocalisationText::active_localisation);

			EButtonGroup::change_group(g);
		}
}

void EDataActionCollection::action_type_search_filter_block_text(ETextArea* _text_area)
{


	for (EButtonGroup* group : EWindowMain::loot_filter_editor->group_list)
	{
		EButtonGroupFilterBlock* filter_block = static_cast<EButtonGroupFilterBlock*>(group);

		filter_block->group_search_status = GroupSearchStatus::SEARCH_STATUS_IGNORE;

		if (_text_area->original_text != "")
		{
			if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(group))
			{
				if (EWindowMain::filter_block_contains_this_text(filter_block, &_text_area->original_text))
				{
					filter_block->group_search_status = GroupSearchStatus::SEARCH_STATUS_MATCHED;
				}
				else
				{
					filter_block->group_search_status = GroupSearchStatus::SEARCH_STATUS_REJECTED;
				}
			}
		}
		//group->recursive_phantom_translate_if_need();
		//filter_block->scroll_y = 0.0f;
	}


	EWindowMain::loot_filter_editor->scroll_y = 0.0f;
	EWindowMain::loot_filter_editor->slider->current_value = 0.0f;
	EButtonGroup::change_group(EWindowMain::loot_filter_editor);
	//EButtonGroup::change_group(EWindowMain::loot_filter_editor);
}

void EDataActionCollection::action_refresh_loot_simulator_when_type(ETextArea* _text_area)
{
	if (EStringUtils::if_text_is_number(&_text_area->original_text))
	{
		EWindowMain::loot_simulator_button_group->refresh_loot_simulator();
	}
}

void EDataActionCollection::action_save_lootfilter(Entity* _entity, ECustomData* _custom_data, float _d)
{
	std::string str = "";

	//EButtonGroup* filter_block_massive = static_cast<EDataContainer_Button_StoreParentFilterBlock*>(_custom_data->data_container)->parent_filter_block->root_group;
	//for (EButtonGroup* group : EWindowMain::loot_filter_editor->group_list)
	//for (int i = EWindowMain::loot_filter_editor->group_list.size() - 1; i >= 0; i--)

	//ORIGINAL
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (!EWindowMain::loot_filter_editor->group_list[i]->suppressed)
		{
			if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				str += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[i], FilterBlockSaveMode::VERSION_ORIGINAL);
				str += '\n';
				str += '\n';
			}
			else
				if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
				{
					if (!static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i])->autogenerated_do_dot_save)
					{
						str += generate_filter_block_separator_text(static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]), FilterBlockSaveMode::VERSION_ORIGINAL);
						str += '\n';
						str += '\n';
					}
				}
		}

	EWindowMain::write_loot_filter_to_disc(EWindowMain::path_of_exile_folder + "/" + EWindowMain::tab_list_group->selected_button->main_text_area->original_text + ".filter", &str);

	//VERY SOFT
	str = "";
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (!EWindowMain::loot_filter_editor->group_list[i]->suppressed)
		{
			if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				str += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[i], FilterBlockSaveMode::VERSION_VERY_SOFT);
				str += '\n';
				str += '\n';
			}
			else if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				if (!static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i])->autogenerated_do_dot_save)
				{
					str += generate_filter_block_separator_text(static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]), FilterBlockSaveMode::VERSION_ORIGINAL);
					str += '\n';
					str += '\n';
				}
			}
		}
	EWindowMain::write_loot_filter_to_disc(EWindowMain::path_of_exile_folder + "/" + EWindowMain::tab_list_group->selected_button->main_text_area->original_text + "[#0 very soft].filter", &str);

	//SOFT
	str = "";
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (!EWindowMain::loot_filter_editor->group_list[i]->suppressed)
		{
			if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				str += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[i], FilterBlockSaveMode::VERSION_SOFT);
				str += '\n';
				str += '\n';
			}
			else if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				if (!static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i])->autogenerated_do_dot_save)
				{
					str += generate_filter_block_separator_text(static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]), FilterBlockSaveMode::VERSION_ORIGINAL);
					str += '\n';
					str += '\n';
				}
			}
		}
	EWindowMain::write_loot_filter_to_disc(EWindowMain::path_of_exile_folder + "/" + EWindowMain::tab_list_group->selected_button->main_text_area->original_text + "[#1 soft].filter", &str);

	//DEFAULT
	str = "";
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (!EWindowMain::loot_filter_editor->group_list[i]->suppressed)
		{
			if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				str += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[i], FilterBlockSaveMode::VERSION_DEFAULT);
				str += '\n';
				str += '\n';
			}
			else if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				if (!static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i])->autogenerated_do_dot_save)
				{
					str += generate_filter_block_separator_text(static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]), FilterBlockSaveMode::VERSION_ORIGINAL);
					str += '\n';
					str += '\n';
				}
			}
		}
	EWindowMain::write_loot_filter_to_disc(EWindowMain::path_of_exile_folder + "/" + EWindowMain::tab_list_group->selected_button->main_text_area->original_text + "[#2 default].filter", &str);

	//STRICT
	str = "";
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (!EWindowMain::loot_filter_editor->group_list[i]->suppressed)
		{
			if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				str += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[i], FilterBlockSaveMode::VERSION_STRICT);
				str += '\n';
				str += '\n';
			}
			else if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				if (!static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i])->autogenerated_do_dot_save)
				{
					str += generate_filter_block_separator_text(static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]), FilterBlockSaveMode::VERSION_ORIGINAL);
					str += '\n';
					str += '\n';
				}
			}
		}
	EWindowMain::write_loot_filter_to_disc(EWindowMain::path_of_exile_folder + "/" + EWindowMain::tab_list_group->selected_button->main_text_area->original_text + "[#3 strict].filter", &str);

	//VERY STRICT
	str = "";
	for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
		if (!EWindowMain::loot_filter_editor->group_list[i]->suppressed)
		{
			if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				str += generate_filter_block_text(EWindowMain::loot_filter_editor->group_list[i], FilterBlockSaveMode::VERSION_VERY_STRICT);
				str += '\n';
				str += '\n';
			}
			else if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]))//filter block
			{
				if (!static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i])->autogenerated_do_dot_save)
				{
					str += generate_filter_block_separator_text(static_cast<EButtonGroupFilterBlockSeparator*>(EWindowMain::loot_filter_editor->group_list[i]), FilterBlockSaveMode::VERSION_ORIGINAL);
					str += '\n';
					str += '\n';
				}
			}
		}
	EWindowMain::write_loot_filter_to_disc(EWindowMain::path_of_exile_folder + "/" + EWindowMain::tab_list_group->selected_button->main_text_area->original_text + "[#4 very strict].filter", &str);

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


	preload_textures();


	register_rarities();

	register_alternate_qualities();

	register_game_item_attributes();

	ETextParser::data_entity_parse_file("data/data_entity_list[game_item].txt");
	ETextParser::data_entity_parse_file("data/data_entity_list[influence].txt");
	ETextParser::data_entity_parse_file("data/data_entity_list[base_class].txt");
	ETextParser::data_entity_parse_file("data/data_entity_list[explicit].txt");
	ETextParser::data_entity_parse_file("data/data_entity_list[enchantment].txt");

	ETextParser::split_data_entity_list_to_named_structs();

	register_loot_simulator_patterns();

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

	//HRA COLOR COLLECTION
	{
		//NORMAL RARITY
		HSVRGBAColor HRA_color;
		HRA_color.set_color_RGBA(1.0f, 0.9f, 0.8f, 1.0f);
		Helper::hsv2rgb(&HRA_color);

		HRA_color_collection* HRA_collection = new HRA_color_collection();
		HRA_collection->name.localisations[NSW_localisation_EN] = "Normal rarity";
		HRA_collection->name.localisations[NSW_localisation_RU] = "������� ��������";
		HRA_collection->target_color = HRA_color;

		Helper::registered_color_list.push_back(HRA_collection);

		//MAGIC RARITY
		HRA_color.set_color_RGBA(0.25f, 0.5f, 1.0f, 1.0f);
		Helper::hsv2rgb(&HRA_color);

		HRA_collection = new HRA_color_collection();
		HRA_collection->name.localisations[NSW_localisation_EN] = "Magic rarity";
		HRA_collection->name.localisations[NSW_localisation_RU] = "��������� ��������";
		HRA_collection->target_color = HRA_color;

		Helper::registered_color_list.push_back(HRA_collection);

		//RARE RARITY
		HRA_color.set_color_RGBA(1.0f, 0.8f, 0.4f, 1.0f);
		Helper::hsv2rgb(&HRA_color);

		HRA_collection = new HRA_color_collection();
		HRA_collection->name.localisations[NSW_localisation_EN] = "Rare rarity";
		HRA_collection->name.localisations[NSW_localisation_RU] = "���������� ��������";
		HRA_collection->target_color = HRA_color;

		Helper::registered_color_list.push_back(HRA_collection);
	}

	//		SEARCH BOTTOM LINE
	{
		EButtonGroupBottomFilterBlockControl* main_bottom_filter_block_control = new EButtonGroupBottomFilterBlockControl(new ERegionGabarite(0.0f, 0.0f, 1020.0f, 32.0f));
		//(
		//	EButtonGroup::create_root_button_group
		//);
		main_bottom_filter_block_control->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_without_slider, bgroup_darken_bg);

		main_bottom_filter_block_control->parent_window = this;

		main_bottom_filter_block_control->root_group = main_bottom_filter_block_control;
		main_bottom_filter_block_control->can_be_moved = false;
		main_bottom_filter_block_control->can_resize_to_workspace_size_x = false;
		main_bottom_filter_block_control->can_resize_to_workspace_size_y = true;

		main_bottom_filter_block_control->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		main_bottom_filter_block_control->actions_on_resize_window.push_back(&EDataActionCollection::action_resize_to_full_window_only_x);
		main_bottom_filter_block_control->dynamic_autosize_for_window = false;
		main_bottom_filter_block_control->shadow_size = 8.0f;

		EWindowMain::bottom_filter_block_control = main_bottom_filter_block_control;

		autosize_group_list.push_back(main_bottom_filter_block_control);

		//for (int z = 0; z < 0; z++)
		//{
		//	create_filter_block(main_button_group);
		//}



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		EntityButton*
			search_button = new EntityButton();
		search_button->make_default_button_with_edible_text
		(
			new ERegionGabarite(300.0f, 30.0f),
			main_bottom_filter_block_control,
			nullptr,
			""
		);
		search_button->main_text_area->action_on_change_text.push_back(&EDataActionCollection::action_type_search_filter_block_text);

		search_button->main_text_area->gray_text = ELocalisationText();
		search_button->main_text_area->gray_text.localisations[NSW_localisation_EN] = "Search...";
		search_button->main_text_area->gray_text.localisations[NSW_localisation_RU] = "�����...";

		main_bottom_filter_block_control->search_button = search_button;
		//search_button->main_text_area->change_text("");

		main_bottom_filter_block_control->button_list.push_back(search_button);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		EntityButton*
			button_clear_text = new EntityButtonForFilterBlock();
		button_clear_text->make_as_default_button_with_icon
		(
			new ERegionGabarite(30.0f, 30.0f),
			main_bottom_filter_block_control,
			&EDataActionCollection::action_clear_text,
			NS_EGraphicCore::load_from_textures_folder("button_close")
		);

		main_bottom_filter_block_control->search_button_clear = button_clear_text;
		//search_button->main_text_area->change_text("");

		main_bottom_filter_block_control->button_list.push_back(button_clear_text);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		button_group_list.push_back(main_bottom_filter_block_control);
		EButtonGroup::refresh_button_group(main_bottom_filter_block_control);


	}



	//NEW BUTTON GROUP
	if (true)
	{
		for (int i = 0; i < filter_tabs_count; i++)
		{
			EButtonGroupFilterBlockEditor* main_filter_editor =
				new EButtonGroupFilterBlockEditor(new ERegionGabarite(NS_EGraphicCore::SCREEN_WIDTH, NS_EGraphicCore::SCREEN_HEIGHT));
			main_filter_editor->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_with_slider, bgroup_with_slider);
			main_filter_editor->parent_window = this;

			main_filter_editor->child_align_direction = ChildElementsAlignDirection::TOP_TO_BOTTOM;

			main_filter_editor->actions_on_resize_window.push_back(&EDataActionCollection::action_resize_to_full_window);

			main_filter_editor->root_group = main_filter_editor;
			main_filter_editor->can_be_moved = false;
			main_filter_editor->can_resize_to_workspace_size_x = false;
			main_filter_editor->can_resize_to_workspace_size_y = false;

			main_filter_editor->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
			//*main_button_group->stretch_mode		= GroupStretchMode::CONSTANT;
			main_filter_editor->dynamic_autosize_for_window = true;

			filter_block_tabs[i] = main_filter_editor;
		}

		loot_filter_editor = filter_block_tabs[0];
		autosize_group_list.push_back(filter_block_tabs[0]);

		//for (int z = 0; z < 0; z++)
		//{
		//	create_filter_block(main_button_group);
		//}




		button_group_list.insert(button_group_list.begin(), filter_block_tabs[0]);
		EButtonGroup::refresh_button_group(filter_block_tabs[0]);
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
			data_container_entity_filter->target_group = EWindowMain::data_entity_filter;
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
							float resize_factor = 32.0f / max(item_icon->size_x_in_pixels, item_icon->size_y_in_pixels);
							resize_factor = min(resize_factor, 1.0f);

							jc_button->sprite_layer_list.push_back
							(
								ESpriteLayer::create_default_sprite_layer_with_size_and_offset
								(item_icon,
									(40.0f - item_icon->size_x_in_pixels * resize_factor) / 2.0f,
									(40.0f - item_icon->size_y_in_pixels * resize_factor) / 2.0f,
									3.0f,

									item_icon->size_x_in_pixels * resize_factor,
									item_icon->size_y_in_pixels * resize_factor,
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
				(new ERegionGabarite(horizontal_side, 30.0f), style)
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
						25.0f
					),
					jc_button_group,
					&EDataActionCollection::action_select_this_style
				);


				jc_button_group->button_list.push_back(jc_button);



				//text area
				ELocalisationText l_text;
				l_text.localisations[NSW_localisation_EN] = "Select <" + style->localisation_text.localisations[NSW_localisation_EN] + ">";
				l_text.localisations[NSW_localisation_RU] = "������� <" + style->localisation_text.localisations[NSW_localisation_RU] + ">";

				jc_text_area = ETextArea::create_centered_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], l_text.localisations[ELocalisationText::active_localisation]);
				jc_text_area->localisation_text = l_text;
				jc_text_area->can_be_edited = false;
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

	//Create new loot-filter
	if (true)
	{
		EButtonGroupNewLootFilter*
			main_loot_filter_group = new EButtonGroupNewLootFilter(new ERegionGabarite(100.0f, 100.0f, 300.0f, 80.0f));
		main_loot_filter_group->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_darken_bg);
		main_loot_filter_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
		main_loot_filter_group->root_group = main_loot_filter_group;
		main_loot_filter_group->is_active = false;
		main_loot_filter_group->parent_window = this;

		main_loot_filter_group->can_resize_to_workspace_size_x = true;
		main_loot_filter_group->can_resize_to_workspace_size_y = true;

		EWindowMain::create_new_loot_filter_group = main_loot_filter_group;
		EButtonGroup*
			new_loot_filter_workspace_group = main_loot_filter_group->add_close_group_and_return_workspace_group(new ERegionGabarite(100, 20.0f), EGUIStyle::active_style);
		new_loot_filter_workspace_group->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
		new_loot_filter_workspace_group->can_resize_to_workspace_size_x = true;
		new_loot_filter_workspace_group->can_resize_to_workspace_size_y = true;


		////////////////////////
		EntityButton*
			button_input_field = new EntityButton();
		button_input_field->make_default_button_with_edible_text
		(
			new ERegionGabarite(240.0f, 30.0f),
			new_loot_filter_workspace_group,
			nullptr,
			""
		);

		ELocalisationText ltext;
		ltext.base_name = "Type new loot filter name";
		ltext.localisations[NSW_localisation_EN] = "Type new loot filter name";
		ltext.localisations[NSW_localisation_RU] = "�������� �������� ���-�������";

		button_input_field->main_text_area->gray_text = ltext;

		new_loot_filter_workspace_group->button_list.push_back(button_input_field);
		////////////////////////

		////////////////////////
		EntityButton*
			button_accept = new EntityButton();
		button_accept->make_default_button_with_unedible_text
		(
			new ERegionGabarite(50.0f, 30.0f),
			new_loot_filter_workspace_group,
			&EDataActionCollection::action_create_new_loot_filter_with_name,
			"OK"
		);

		new_loot_filter_workspace_group->button_list.push_back(button_accept);
		////////////////////////

		main_loot_filter_group->input_field_button = button_input_field;

		button_group_list.push_back(main_loot_filter_group);
		EButtonGroup::refresh_button_group(main_loot_filter_group);
	}

	//DATA ENTITY
	if (true)
	{
		EButtonGroupDataEntity*
			data_entity_main_group = new EButtonGroupDataEntity(new ERegionGabarite(900.0f, 100.0f, 0.0f, 1500.0f, 600.0f));
		data_entity_main_group->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_without_slider, bgroup_darken_bg);

		data_entity_main_group->parent_window = this;
		data_entity_main_group->root_group = data_entity_main_group;
		data_entity_main_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;
		EWindowMain::data_entity_filter = data_entity_main_group;


		EDataContainer_Group_DataEntitiesSearch* jc_data_container_for_search_group = new EDataContainer_Group_DataEntitiesSearch();
		data_entity_main_group->data_container = jc_data_container_for_search_group;
		data_entity_main_group->is_active = false;

		DataEntityFilter* data_entity_filter = new DataEntityFilter();
		data_entity_filter->target_tag_name = "data type";
		data_entity_filter->suitable_values_list.push_back("Game item");

		EFilterRule* jc_filter_rule = new EFilterRule();
		jc_filter_rule->required_tag_list.push_back(data_entity_filter);

		jc_data_container_for_search_group->target_rule = new EFilterRule();

		EButtonGroup* workspace_part = data_entity_main_group->add_close_group_and_return_workspace_group(new ERegionGabarite(200.0f, 20.0f), EGUIStyle::active_style);

		// // //	DATA ENTITY LIST	// // //
		jc_button_group = workspace_part->add_group
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
				new ERegionGabarite(250.0f, 480.0f),
				EGUIStyle::active_style
			)
		)->set_parameters
		(
			ChildAlignMode::ALIGN_HORIZONTAL,
			NSW_dynamic_autosize,
			NSW_dynamic_autosize
		);

		left_side_for_data_entity_buttons->button_size_x_override = 350.0f;

		data_entity_main_group->main_left_side = left_side_for_data_entity_buttons;

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

		right_side_for_filter_rule_buttons->button_size_x_override = 200.0f;

		data_entity_main_group->right_side_for_filters = right_side_for_filter_rule_buttons;
		//right_side_for_filter_rule_buttons->can

		jc_data_container_for_search_group->pointer_to_group_with_data_entities = left_side_for_data_entity_buttons;
		jc_data_container_for_search_group->pointer_to_group_with_filter_rules_list = right_side_for_filter_rule_buttons;



		////buttons for data entity
		//unsigned int counter = 0;
		//for (EDataEntity* data_entity : EDataEntity::data_entity_global_list)
		//{

		//	jc_button = EntityButton::create_wide_item_button
		//	(
		//		new ERegionGabarite(300.0f, 50.0f),
		//		left_side_for_data_entity_buttons,
		//		data_entity,
		//		EFont::font_list[0]
		//	);

		//	left_side_for_data_entity_buttons->button_list.push_back(jc_button);

		//	counter++;
		//}

		for (int i = 0; i < EFilterRule::registered_filter_rules_for_list.size(); i++)
		{
			EntityButtonFilterRule* filter_button = new EntityButtonFilterRule();
			filter_button->make_as_default_button_with_icon_and_text
			(
				new ERegionGabarite(200.0f, 40.0f),
				right_side_for_filter_rule_buttons,
				&EDataActionCollection::action_select_this_filter_variant,
				EFilterRule::registered_filter_rules_for_list[i]->icon_texture,
				EFilterRule::registered_filter_rules_for_list[i]->localisation_text->localisations[ELocalisationText::active_localisation]
			);

			//filter_button->

			Entity::get_last_text_area(filter_button)->localisation_text = *EFilterRule::registered_filter_rules_for_list[i]->localisation_text;
			filter_button->main_text_area->offset_by_gabarite_size_x = 0.0f;
			filter_button->main_text_area->offset_by_text_size_x = 0.0f;
			filter_button->target_filter_rule = EFilterRule::registered_filter_rules_for_list[i];
			filter_button->target_data_container = jc_data_container_for_search_group;

			right_side_for_filter_rule_buttons->button_list.push_back(filter_button);
		}

		//search bar group
		jc_button_group = workspace_part->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(800.0f, 50.0f), EGUIStyle::active_style));
		jc_button_group->stretch_x_by_parent_size = true;
		jc_button_group->stretch_y_by_parent_size = false;

		jc_button = new EntityButton();
		jc_button->make_default_button_with_edible_text
		(
			new ERegionGabarite(700.0f, 25.0f),
			jc_button_group,
			nullptr,
			""
		);

		data_entity_main_group->main_input_field = jc_button;

		jc_data_container_for_search_group->filter_text_area = jc_button->main_text_area;

		jc_button->main_text_area->gray_text = ELocalisationText();
		jc_button->main_text_area->gray_text.localisations[NSW_localisation_EN] = "Type search text...";
		jc_button->main_text_area->gray_text.localisations[NSW_localisation_RU] = "�������� ����� ������...";

		jc_button->main_text_area->action_on_change_text.push_back(&EDataActionCollection::action_type_search_data_entity_text);

		jc_data_container_for_search_group->pointer_to_search_bar = jc_button;

		jc_button_group->button_list.push_back(jc_button);











		button_group_list.push_back(data_entity_main_group);

		///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	
		jc_button = new EntityButton();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(256.0f, 25.0f),
			jc_button_group,
			&EDataActionCollection::action_add_text_as_item,
			"Add this text as item"
		);

		jc_button_group->button_list.push_back(jc_button);
		///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	///	

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

		EButtonGroup::refresh_button_group(data_entity_main_group);
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

		main_button_group->is_active = false;
		world_parameters = main_button_group;

		EButtonGroup*
			world_parameters_workspace_part = main_button_group->add_close_group_and_return_workspace_group(new ERegionGabarite(1.0f, 20.0f), EGUIStyle::active_style);

		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		//*----------------------------		SUN SECTION		-------------------------------------------------------*//
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = world_parameters_workspace_part->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 60.0f), EGUIStyle::active_style));
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
		EButtonGroup* button_group_sun_main = world_parameters_workspace_part->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 260.0f), EGUIStyle::active_style));
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
		ELocalisationText l_text;
		l_text.localisations[NSW_localisation_EN] = "Sun color";
		l_text.localisations[NSW_localisation_RU] = "���� ������";
		jc_button = EntityButton::create_named_color_button
		(
			new ERegionGabarite(170.0f, 38.0f),
			jc_button_group,
			EFont::font_list[0],
			EGUIStyle::active_style,
			l_text,
			nullptr,
			&NS_EGraphicCore::sun_color,
			ColorButtonMode::CBM_OPEN_WINDOW
		);

		jc_button_group->button_list.push_back(jc_button);



		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		//*----------------------------		SKYDOME SECTION		-------------------------------------------------------*//
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = world_parameters_workspace_part->add_group
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
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 4.0f;
		//EntityButton::get_last_custom_data(jc_button)->actions_on_update.push_back(&EDataActionCollection::action_force_resize_callback);
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //


		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		//*----------------------------		INTERFACE SECTION		-----------------------------------------------*//
		//**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**////**//**//
		jc_button_group = world_parameters_workspace_part->add_group
		(EButtonGroup::create_default_button_group(new ERegionGabarite(890.0f, 60.0f), EGUIStyle::active_style));
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
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &NS_EGraphicCore::stored_zoom;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 2.0f;
		static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->force_shift = true;
		EntityButton::get_last_custom_data(jc_button)->actions_on_update.push_back(&EDataActionCollection::action_force_resize_callback);
		jc_button_group->button_list.push_back(jc_button);
		// // // // // // //// // // // // // //// // // // // // //



		// // // // // // //// // // // // // //// // // // // // //
		//TEST
		jc_button = new EntityButtonForFilterBlock();
		jc_button->make_default_bool_switcher_button
		(
			new ERegionGabarite(22.0f, 22.0f),
			jc_button_group,
			EDataActionCollection::action_switch_boolean_value,
			NS_DefaultGabarites::texture_bool_switcher_activated_box,
			NS_DefaultGabarites::texture_bool_switcher_deactivated_box
		);

		jc_button_group->button_list.push_back(jc_button);


		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}

	//		LOOT SIMULATOR
	{
		////////////////////////////////
		EButtonGroupLootSimulator*
			main_loot_buttons_group = new EButtonGroupLootSimulator(new ERegionGabarite(100.0f, 100.0f, 1400.0f, 600.0f));

		main_loot_buttons_group->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_darken_bg);
		main_loot_buttons_group->root_group = main_loot_buttons_group;
		main_loot_buttons_group->parent_window = this;

		loot_simulator_button_group = main_loot_buttons_group;
		////////////////////////////////
		EButtonGroup*
			workspace_part = main_loot_buttons_group->add_close_group_and_return_workspace_group(new ERegionGabarite(20.0f, 20.0f), EGUIStyle::active_style);

		////////////////////////////////
		EButtonGroup*
			bottom_loot_part = new EButtonGroup(new ERegionGabarite(90.0f, 90.0f));
		bottom_loot_part->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_with_slider, bgroup_darken_bg);
		bottom_loot_part->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);


		workspace_part->add_group(bottom_loot_part);

		////////////////////////////////
		EButtonGroup*
			top_control_part = new EButtonGroup(new ERegionGabarite(90.0f, 30.0f));
		top_control_part->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_default_bg);
		top_control_part->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_static_autosize);
		workspace_part->add_group(top_control_part);



		////////////////////////////////
		EButtonGroup*
			left_part_for_patterns = new EButtonGroup(new ERegionGabarite(220.0f, 500.0f));
		left_part_for_patterns->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_default_bg);
		left_part_for_patterns->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);

		main_loot_buttons_group->pointer_to_patterns_buttons_segment = left_part_for_patterns;

		bottom_loot_part->add_group(left_part_for_patterns);

		////////////////////////////////
		EButtonGroup*
			middle_loot_buttons = new EButtonGroup(new ERegionGabarite(10.0f, 10.0f));
		middle_loot_buttons->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_with_slider, bgroup_darken_bg);
		middle_loot_buttons->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
		middle_loot_buttons->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;

		bottom_loot_part->add_group(middle_loot_buttons);

		main_loot_buttons_group->pointer_to_loot_buttons_segment = middle_loot_buttons;

		////////////////////////////////
		EButtonGroup*
			right_loot_part = new EButtonGroup(new ERegionGabarite(200.0f, 10.0f));
		right_loot_part->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_default_bg);
		right_loot_part->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);
		bottom_loot_part->add_group(right_loot_part);



		if (false)
		{
			//		BUTTON REFRESH LOOT SIMULATOR
			EntityButton*
				button_refresh = new EntityButton();
			button_refresh->make_as_default_button_with_icon
			(
				new ERegionGabarite(30.0f, 30.0f),
				top_control_part,
				&EDataActionCollection::action_refresh_loot_simulator,
				NS_EGraphicCore::load_from_textures_folder("buttons/button_refresh_loot_simulator")
			);
			top_control_part->button_list.push_back(button_refresh);
		}

		//		BUTTONS FOR PATTERNS
		{
			for (LootSimulatorPattern* loot_pattern : LootSimulatorPattern::registered_loot_simulater_pattern_list)
			{
				EntityButtonLootPatternSelector*
					pattern_button = new EntityButtonLootPatternSelector();
				pattern_button->make_as_default_button_with_icon_and_text
				(
					new ERegionGabarite(200.0f, 40.0f),
					left_part_for_patterns,
					&EDataActionCollection::action_add_items_from_this_loot_pattern,
					loot_pattern->icon,
					loot_pattern->localised_name.localisations[ELocalisationText::active_localisation]
				);
				pattern_button->target_pattern = loot_pattern;
				pattern_button->main_text_area->localisation_text = loot_pattern->localised_name;

				left_part_for_patterns->button_list.push_back(pattern_button);
			}
		}

		//		SELECTED VERSION
		{
			EntityButtonVariantRouter*
				variant_router_button = new EntityButtonVariantRouter();
			main_loot_buttons_group->pointer_to_target_loot_filter_version_button = variant_router_button;

			variant_router_button->make_as_default_button_with_icon
			(
				new ERegionGabarite(256.0f, 25.0f),
				top_control_part,
				&EDataActionCollection::action_rotate_variant,
				nullptr
			);

			variant_router_button->custom_data_list.back()->clickable_area_list.back()->actions_on_click_list.push_back(&EDataActionCollection::action_refresh_loot_simulator);

			variant_router_button->layer_with_icon = variant_router_button->sprite_layer_list.back();
			//
			ETextArea* jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(variant_router_button), EFont::font_list[0], "|?|");
			variant_router_button->pointer_to_text_area = jc_text_area;

			jc_text_area->can_be_edited = false;
			Entity::add_text_area_to_last_clickable_region(variant_router_button, jc_text_area);


			//
			RouterVariant* router_variant;
			ELocalisationText* local_text = nullptr;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//		router variant
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
			router_variant = new RouterVariant();
			local_text = new ELocalisationText();

			local_text->base_name = "Very soft";
			local_text->localisations[NSW_localisation_EN] = "Loot filter version: Very soft";
			local_text->localisations[NSW_localisation_RU] = "������ ��� �������: ���������";
			router_variant->localisation = local_text;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

			variant_router_button->router_variant_list.push_back(router_variant);
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

			//		router variant
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
			router_variant = new RouterVariant();
			local_text = new ELocalisationText();

			local_text->base_name = "Soft";
			local_text->localisations[NSW_localisation_EN] = "Loot filter version: Soft";
			local_text->localisations[NSW_localisation_RU] = "������ ��� �������: ������";
			router_variant->localisation = local_text;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(0.5f, 1.0f, 0.75f, 1.0f);

			variant_router_button->router_variant_list.push_back(router_variant);
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

			//		router variant
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
			router_variant = new RouterVariant();
			local_text = new ELocalisationText();

			local_text->base_name = "Default";
			local_text->localisations[NSW_localisation_EN] = "Loot filter version: Default";
			local_text->localisations[NSW_localisation_RU] = "������ ��� �������: �������";
			router_variant->localisation = local_text;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(0.5f, 0.75f, 1.0f, 1.0f);

			variant_router_button->router_variant_list.push_back(router_variant);
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

			//		router variant
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
			router_variant = new RouterVariant();
			local_text = new ELocalisationText();

			local_text->base_name = "Strict";
			local_text->localisations[NSW_localisation_EN] = "Loot filter version: Strict";
			local_text->localisations[NSW_localisation_RU] = "������ ��� �������: �������";
			router_variant->localisation = local_text;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(1.0f, 0.5f, 1.0f, 1.0f);

			variant_router_button->router_variant_list.push_back(router_variant);
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

			//		router variant
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
			router_variant = new RouterVariant();
			local_text = new ELocalisationText();

			local_text->base_name = "Very strict";
			local_text->localisations[NSW_localisation_EN] = "Loot filter version: Very strict";
			local_text->localisations[NSW_localisation_RU] = "������ ��� �������: ����� �������";
			router_variant->localisation = local_text;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(1.0f, 0.75f, 0.35f, 1.0f);

			variant_router_button->router_variant_list.push_back(router_variant);
			/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

			variant_router_button->select_variant(0);

			top_control_part->button_list.push_back(variant_router_button);
		}

		//		AREA LEVEL TEXT FIELD
		{
			EntityButton*
				button_area_level_text = new EntityButton();

			ELocalisationText l_text;

			l_text.localisations[NSW_localisation_EN] = "Area level";
			l_text.localisations[NSW_localisation_RU] = "������� �������";

			button_area_level_text->make_default_button_with_unedible_text
			(
				new ERegionGabarite(150.0f, 25.0f),
				top_control_part,
				nullptr,
				l_text.localisations[ELocalisationText::active_localisation]
			);

			button_area_level_text->main_text_area->localisation_text = l_text;


			top_control_part->button_list.push_back(button_area_level_text);

		}

		//		AREA LEVEL INPUT FIELD
		{
			EntityButton*
				button_area_level_input = new EntityButton();
			main_loot_buttons_group->pointer_to_input_area_level_button = button_area_level_input;

			button_area_level_input->make_default_button_with_edible_text
			(
				new ERegionGabarite(50.0f, 25.0f),
				top_control_part,
				nullptr,
				"81"
			);

			button_area_level_input->main_text_area->action_on_change_text.push_back(&EDataActionCollection::action_refresh_loot_simulator_when_type);

			button_area_level_input->main_text_area->localisation_text.localisations[NSW_localisation_EN] = "Area level";
			button_area_level_input->main_text_area->localisation_text.localisations[NSW_localisation_RU] = "������� �������";

			top_control_part->button_list.push_back(button_area_level_input);

		}







		button_group_list.push_back(main_loot_buttons_group);
		EButtonGroup::refresh_button_group(main_loot_buttons_group);
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
			add_content_group = EButtonGroup::create_root_button_group(new ERegionGabarite(100.0f, 100.0f, 600.0f, 400.0f), EGUIStyle::active_style);
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

		EntityButtonMultiSearch*
			button_multisearch = new EntityButtonMultiSearch();
		button_multisearch->make_default_button_with_edible_text
		(
			new ERegionGabarite(800.0f, 30.0f),
			search_bar_group,
			nullptr,
			""
		);

		button_multisearch->main_text_area->gray_text = ELocalisationText();
		button_multisearch->main_text_area->gray_text.localisations[NSW_localisation_EN] = "Type attribute name...";
		button_multisearch->main_text_area->gray_text.localisations[NSW_localisation_RU] = "�������� �������� ��������...";

		//add pointer to clickable are in "add content to filter block group"
		content_group_data_container->typing_text_area = EntityButton::get_last_text_area(button_multisearch);

		//auto multi_search_data_container = new EntityButtonMultiSearch();

		Entity::get_last_clickable_area(button_multisearch)->text_area->action_on_change_text.push_back(&EDataActionCollection::action_type_text_multiblock_searcher);

		search_bar_group->button_list.push_back(button_multisearch);
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
		filter_block_operation_segment->button_size_x_override = 200.0f;
		filter_block_operation_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;


		/////////////////////	ADD NEW BLOCK	///////////////////////////////////////////
		ELocalisationText l_text;
		l_text.localisations[NSW_localisation_EN] = "Add new block";
		l_text.localisations[NSW_localisation_RU] = "������� ����� ����";

		jc_button = new EntityButton();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(160.0f, 30.0f),
			filter_block_operation_segment,
			&EDataActionCollection::action_add_new_filter_block,
			l_text.localisations[ELocalisationText::active_localisation]
		);
		jc_button->main_text_area->localisation_text = l_text;

		filter_block_operation_segment->button_list.push_back(jc_button);
		/////////////////////	CLONE	///////////////////////////////////////////
		EntityButtonForFilterBlock* clone_button = new EntityButtonForFilterBlock();

		l_text.localisations[NSW_localisation_EN] = "Clone block";
		l_text.localisations[NSW_localisation_RU] = "����������� ����";

		clone_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(160.0f, 30.0f),
			filter_block_operation_segment,
			&EDataActionCollection::action_clone_block,
			l_text.localisations[ELocalisationText::active_localisation]
		);
		clone_button->main_text_area->localisation_text = l_text;
		//clone_button->parent_filter_block = 

		filter_block_operation_segment->button_list.push_back(clone_button);
		////////////////////////////////////////////////////////////////////////////////////////////////////



		/////////////////////	SEPARATOR	///////////////////////////////////////////
		l_text.localisations[NSW_localisation_EN] = "Add separator";
		l_text.localisations[NSW_localisation_RU] = "�������� �����������";
		EntityButtonForFilterBlock*
			separator_button = new EntityButtonForFilterBlock();
		separator_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(160.0f, 30.0f),
			filter_block_operation_segment,
			&EDataActionCollection::action_add_separator_block,
			l_text.localisations[ELocalisationText::active_localisation]
		);
		separator_button->main_text_area->localisation_text = l_text;
		//clone_button->parent_filter_block = 

		filter_block_operation_segment->button_list.push_back(separator_button);
		////////////////////////////////////////////////////////////////////////////////////////////////////




		////////////////////////////////////////////////////////////////////////////////////////////////////
		//jc_button = EntityButton::create_default_clickable_button_with_unedible_text(new ERegionGabarite(160.0f, 20.0f), filter_block_operation_segment, nullptr, "����������� ���� ����");
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
		non_listed_segment->button_size_x_override = 200.0f;
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
		listed_segment->button_size_x_override = 200.0f;
		listed_segment->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;




		button_multisearch->target_group_list.push_back(content_list_group);
		button_multisearch->target_group_list.push_back(non_listed_segment);
		button_multisearch->target_group_list.push_back(listed_segment);

		EButtonGroup* target_group = nullptr;
		for (GameItemAttribute* fba : registered_game_item_attributes)
			if ((!fba->always_present) && (!fba->commentary_config))
			{
				EDataContainer_Button_AddContentToFilterBlock* add_content_data = new EDataContainer_Button_AddContentToFilterBlock();
				add_content_data->target_attribute = fba;

				if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED) { target_group = non_listed_segment; }
				if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED) { target_group = listed_segment; }
				//if (fba->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC) { target_group = cosmetic_segment; }

				jc_button = new EntityButton();
				jc_button->make_default_button_with_unedible_text
				(
					new ERegionGabarite(160.0f, 38.0f),
					target_group,
					&EDataActionCollection::action_add_selected_content_to_filter_block,
					fba->localisation.localisations[ELocalisationText::active_localisation]
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
	if (false)
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
			"�������"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 1.0f, 1.0f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		ltext.base_name = "Normal";

		ltext.localisations[NSW_localisation_EN] = "Normal";
		ltext.localisations[NSW_localisation_RU] = "����������";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//magic
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_rarity_group,
			&EDataActionCollection::action_select_this_text_variant,
			"����������"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(0.4f, 0.5f, 1.0f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);


		ltext.base_name = "Magic";

		ltext.localisations[NSW_localisation_EN] = "Magic";
		ltext.localisations[NSW_localisation_RU] = "���������";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//rare
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_rarity_group,
			&EDataActionCollection::action_select_this_text_variant,
			"������"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 1.0f, 0.25f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		ltext.base_name = "Rare";

		ltext.localisations[NSW_localisation_EN] = "Rare";
		ltext.localisations[NSW_localisation_RU] = "������";

		EntityButton::get_last_text_area(jc_button)->localisation_text = ltext;

		//unique
		jc_button = new EntityButtonFilterRule();
		jc_button->make_default_button_with_unedible_text
		(
			new ERegionGabarite(100.0f, 20.0f),
			workspace_rarity_group,
			&EDataActionCollection::action_select_this_text_variant,
			"����������"
		);

		EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(1.0f, 0.50f, 0.25f, 1.0f);
		workspace_rarity_group->button_list.push_back(jc_button);

		ltext.base_name = "Unique";

		ltext.localisations[NSW_localisation_EN] = "Unique";
		ltext.localisations[NSW_localisation_RU] = "����������";

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


		for (int i = 0; i < NSW_registered_altered_gem_quality_count; i++)
		{
			jc_button = new EntityButtonFilterRule();
			jc_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(100.0f, 20.0f),
				workspace_quality_group,
				&EDataActionCollection::action_select_this_text_variant,
				""
			);

			jc_button->main_text_area->set_color(registered_alternate_gem_quality_router_variants[i]->color);
			jc_button->main_text_area->change_text(registered_alternate_gem_quality_router_variants[i]->localisation->localisations[ELocalisationText::active_localisation]);
			EntityButton::get_last_text_area(jc_button)->localisation_text = *registered_alternate_gem_quality_router_variants[i]->localisation;

			workspace_quality_group->button_list.push_back(jc_button);
		}

		button_group_list.push_back(whole_quality_list_group);
		EButtonGroup::refresh_button_group(whole_quality_list_group);

		whole_quality_list_group->is_active = false;
	}

	//filter sound list
	{
		EWindowMain::load_ingame_sound_list();
		EWindowMain::load_custom_sound_list();

		EButtonGroupSoundList*
			main_sound_group = new EButtonGroupSoundList(new ERegionGabarite(512.0f, 256.0f, 1020.0f, 512.0f));
		main_sound_group->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_darken_bg);
		main_sound_group->is_active = false;

		EButtonGroup::sound_list_group = main_sound_group;
		EButtonGroup::sound_list_group->action_on_select_for_button = &EDataActionCollection::action_select_this_sound_for_target_button;

		//auto whole_loot_filter_group = static_cast<EButtonGroupLootFilterList*>(main_sound_group);


		main_sound_group->parent_window = this;

		main_sound_group->root_group = main_sound_group;
		main_sound_group->can_be_moved = true;
		main_sound_group->can_resize_to_workspace_size_x = true;
		main_sound_group->can_resize_to_workspace_size_y = true;

		main_sound_group->child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

		EButtonGroup* sound_list_workspace_part = main_sound_group->add_close_group_and_return_workspace_group
		(
			new ERegionGabarite(1.0f, 20.0f),
			EGUIStyle::active_style
		)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

		///////////////		SOUNDS LIST PART		///////////////
		EButtonGroup* sound_list_part = sound_list_workspace_part->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(1.0f, 1.0f),
				EGUIStyle::active_style
			)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize)
		);
		//

		///////////////		SEARCH INPUT PART		///////////////
		EButtonGroup* search_input_part = sound_list_workspace_part->add_group
		(
			EButtonGroup::create_default_button_group
			(
				new ERegionGabarite(1.0f, 32.0f),
				EGUIStyle::active_style
			)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize)
		);
		search_input_part->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;



		EntityButtonMultiSearch*
			button_multisearch = new EntityButtonMultiSearch();
		button_multisearch->make_default_button_with_edible_text
		(
			new ERegionGabarite(800.0f, 28.0f),
			search_input_part,
			nullptr,
			""
		);

		button_multisearch->main_text_area->gray_text = ELocalisationText();
		button_multisearch->main_text_area->gray_text.localisations[NSW_localisation_EN] = "Type sound name...";
		button_multisearch->main_text_area->gray_text.localisations[NSW_localisation_RU] = "�������� �������� �����...";

		button_multisearch->target_group_list.push_back(sound_list_part);
		EntityButton::get_last_text_area(button_multisearch)->action_on_change_text.push_back(&EDataActionCollection::action_type_text_multiblock_searcher);


		search_input_part->button_list.push_back(button_multisearch);



		/// set data parameters
		main_sound_group->part_with_list = sound_list_part;



		button_group_list.push_back(main_sound_group);
		EButtonGroup::refresh_button_group(main_sound_group);
	}	//loot-filter list




	//loot filters list
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
		EButtonGroup*
			search_input_part = loot_filters_list_workspace_part->add_group
			(
				EButtonGroup::create_default_button_group
				(
					new ERegionGabarite(1.0f, 32.0f),
					EGUIStyle::active_style
				)->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize)
			);
		search_input_part->button_align_type = ButtonAlignType::BUTTON_ALIGN_MID;



		EntityButtonMultiSearch*
			button_multisearch = new EntityButtonMultiSearch();
		button_multisearch->make_default_button_with_edible_text
		(
			new ERegionGabarite(800.0f, 28.0f),
			search_input_part,
			nullptr,
			""
		);

		button_multisearch->main_text_area->gray_text = ELocalisationText();
		button_multisearch->main_text_area->gray_text.localisations[NSW_localisation_EN] = "Type loot-filter name...";
		button_multisearch->main_text_area->gray_text.localisations[NSW_localisation_RU] = "�������� �������� ���-�������...";

		button_multisearch->target_group_list.push_back(loot_filter_list_part);
		EntityButton::get_last_text_area(button_multisearch)->action_on_change_text.push_back(&EDataActionCollection::action_type_text_multiblock_searcher);


		search_input_part->button_list.push_back(button_multisearch);


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
		main_button_group->shadow_size = 8.0f;

		autosize_group_list.push_back(main_button_group);
		EButtonGroup* bottom_tab_section = main_button_group->add_group
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
			&EDataActionCollection::action_open_new_lootfilter_group,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_create_new_loot_filter")
		);
		top_section->button_list.push_back(jc_button);

		//////////////////////////////////////////////////////

		jc_button = new EntityButtonForFilterBlock();
		jc_button->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_open_loot_filters_list_window,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_open")
		);
		top_section->button_list.push_back(jc_button);

		//////////////////////////////////////////////////////
		jc_button = new EntityButtonForFilterBlock();

		jc_button->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_save_lootfilter,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_save")
		);

		top_section->button_list.push_back(jc_button);
		//////////////////////////////////////////////////////



		//////////////////////////////////////////////////////
		EntityButtonButtonGroupActivator* button_activator = new EntityButtonButtonGroupActivator();

		button_activator->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_set_button_group_as_active,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_world_parameters")
		);
		button_activator->target_group = EWindowMain::world_parameters;
		top_section->button_list.push_back(button_activator);
		//////////////////////////////////////////////////////



		//////////////////////////////////////////////////////
		button_activator = new EntityButtonButtonGroupActivator();

		button_activator->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_open_custom_sound_list,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_custom_sound")
		);
		//button_activator->target_group = EWindowMain::world_parameters;
		top_section->button_list.push_back(button_activator);
		//////////////////////////////////////////////////////



		//////////////////////////////////////////////////////
		button_activator = new EntityButtonButtonGroupActivator();

		button_activator->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_open_and_refresh_loot_simulator,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_open_loot_simulator")
		);
		//button_activator->target_group = EWindowMain::loot_simulator_button_group;
		top_section->button_list.push_back(button_activator);
		//////////////////////////////////////////////////////


		//LOCALISATION RU
		//////////////////////////////////////////////////////
		EntityButtonLocalisationSelector*
			button_RU = new EntityButtonLocalisationSelector();

		button_RU->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_change_localisation,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_localisation_RU")
		);
		button_RU->stored_localisation = NSW_localisation_RU;
		top_section->button_list.push_back(button_RU);
		//////////////////////////////////////////////////////


		//LOCALISATION EN
		//////////////////////////////////////////////////////
		EntityButtonLocalisationSelector*
			button_EN = new EntityButtonLocalisationSelector();

		button_EN->make_as_default_button_with_icon
		(
			new ERegionGabarite(45.0f, 45.0f),
			top_section,
			&EDataActionCollection::action_change_localisation,
			NS_EGraphicCore::load_from_textures_folder("buttons/button_localisation_EN")
		);
		button_EN->stored_localisation = NSW_localisation_EN;
		top_section->button_list.push_back(button_EN);
		//////////////////////////////////////////////////////

		ELocalisationText l_text;
		for (int i = 0; i < 5; i++)
		{
			EntityButtonFilterBlockTab* tab_button = new EntityButtonFilterBlockTab();

			l_text.localisations[NSW_localisation_EN] = "Filter tab #" + std::to_string(i);
			l_text.localisations[NSW_localisation_RU] = "�������� #" + std::to_string(i);

			tab_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(200.0f, 26.0f),
				bottom_tab_section,
				&EDataActionCollection::action_select_this_tab,
				l_text.localisations[ELocalisationText::active_localisation]
			);

			tab_button->main_text_area->localisation_text = l_text;

			tab_list_group = bottom_tab_section;
			tab_button->main_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_select_this_button);

			tab_button->tab_id = i;
			tab_button->target_filter_editor = filter_block_tabs[i];

			bottom_tab_section->button_list.push_back(tab_button);

			if (i == 0) { bottom_tab_section->selected_button = tab_button; }
		}

		//////////////////////////////////////////////////////


		button_group_list.push_back(main_button_group);
		EButtonGroup::refresh_button_group(main_button_group);
	}


	NS_EGraphicCore::refresh_autosize_groups(this);
}

void EWindowMain::preload_textures()
{
	NS_DefaultGabarites::texture_example_text_bg_for_preview_box = NS_EGraphicCore::put_texture_to_atlas("data/textures/example_text_bg.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_example_text_for_preview_box = NS_EGraphicCore::put_texture_to_atlas("data/textures/example_text.png", NS_EGraphicCore::default_texture_atlas);
	NS_DefaultGabarites::texture_example_text_for_preview_box_half = NS_EGraphicCore::put_texture_to_atlas("data/textures/example_text_half.png", NS_EGraphicCore::default_texture_atlas);


	NS_DefaultGabarites::texture_loot_version_full_ignore = NS_EGraphicCore::load_from_textures_folder("loot_versions/loot_version_full_ignore");
	NS_DefaultGabarites::texture_loot_version_hide = NS_EGraphicCore::load_from_textures_folder("loot_versions/loot_version_hide");
	NS_DefaultGabarites::texture_loot_version_ignore = NS_EGraphicCore::load_from_textures_folder("loot_versions/loot_version_strong_ignore");
	NS_DefaultGabarites::texture_loot_version_default = NS_EGraphicCore::load_from_textures_folder("loot_versions/loot_version_default");
	NS_DefaultGabarites::texture_loot_version_focus = NS_EGraphicCore::load_from_textures_folder("loot_versions/loot_version_strong_focus");


	NS_DefaultGabarites::texture_show_hide_visual_editor = NS_EGraphicCore::load_from_textures_folder("buttons/button_show_hide_visual_editor");
	NS_DefaultGabarites::texture_show_hide_visual_editor_deactivate = NS_EGraphicCore::load_from_textures_folder("buttons/button_show_hide_visual_editor_deactivate");

	NS_DefaultGabarites::texture_button_plus = NS_EGraphicCore::load_from_textures_folder("buttons/button_plus");

	NS_DefaultGabarites::texture_button_move_up = NS_EGraphicCore::load_from_textures_folder("buttons/button_move_up");
	NS_DefaultGabarites::texture_button_move_down = NS_EGraphicCore::load_from_textures_folder("buttons/button_move_down");
	NS_DefaultGabarites::texture_button_move = NS_EGraphicCore::load_from_textures_folder("buttons/button_move");
	NS_DefaultGabarites::texture_button_cut = NS_EGraphicCore::load_from_textures_folder("buttons/button_cut");

	NS_DefaultGabarites::texture_button_remove_filter_block = NS_EGraphicCore::load_from_textures_folder("buttons/button_remove_filter_block");

	NS_DefaultGabarites::texture_ray = NS_EGraphicCore::load_from_textures_folder("ray");

	NS_DefaultGabarites::texture_minimap_shape_circle = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[circle]");
	NS_DefaultGabarites::texture_minimap_shape_diamond = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[diamond]");
	NS_DefaultGabarites::texture_minimap_shape_hexagon = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[hexagon]");
	NS_DefaultGabarites::texture_minimap_shape_square = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[square]");
	NS_DefaultGabarites::texture_minimap_shape_star = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[star]");
	NS_DefaultGabarites::texture_minimap_shape_triangle = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[triangle]");
	NS_DefaultGabarites::texture_minimap_shape_cross = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[cross]");
	NS_DefaultGabarites::texture_minimap_shape_moon = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[moon]");
	NS_DefaultGabarites::texture_minimap_shape_raindrop = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[raindrop]");
	NS_DefaultGabarites::texture_minimap_shape_kite = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[kite]");
	NS_DefaultGabarites::texture_minimap_shape_pentagon = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[pentagon]");
	NS_DefaultGabarites::texture_minimap_shape_upside_down_house = NS_EGraphicCore::load_from_textures_folder("minimap_shapes/minimap_icon_shape[upside_down_house]");
}

void EWindowMain::register_rarities()
{
	ELocalisationText* localisation_text = nullptr;

	localisation_text = new ELocalisationText();
	registered_rarity_router_variants[0] = new RouterVariant();
	registered_rarity_router_variants[0]->localisation = localisation_text;
	registered_rarity_router_variants[0]->color = new HSVRGBAColor();
	registered_rarity_router_variants[0]->color->set_color_RGBA(0.9f, 0.95f, 1.0f, 1.0f);
	localisation_text->base_name = "Normal";
	localisation_text->localisations[NSW_localisation_EN] = "Normal";
	localisation_text->localisations[NSW_localisation_RU] = "�������";

	//Magic
	localisation_text = new ELocalisationText();
	registered_rarity_router_variants[1] = new RouterVariant();
	registered_rarity_router_variants[1]->localisation = localisation_text;
	registered_rarity_router_variants[1]->color = new HSVRGBAColor();
	registered_rarity_router_variants[1]->color->set_color_RGBA(0.5f, 0.7f, 1.0f, 1.0f);
	localisation_text->base_name = "Magic";
	localisation_text->localisations[NSW_localisation_EN] = "Magic";
	localisation_text->localisations[NSW_localisation_RU] = "����������";

	//Rare
	localisation_text = new ELocalisationText();
	registered_rarity_router_variants[2] = new RouterVariant();
	registered_rarity_router_variants[2]->localisation = localisation_text;
	registered_rarity_router_variants[2]->color = new HSVRGBAColor();
	registered_rarity_router_variants[2]->color->set_color_RGBA(1.0f, 0.9f, 0.35f, 1.0f);
	localisation_text->base_name = "Rare";
	localisation_text->localisations[NSW_localisation_EN] = "Rare";
	localisation_text->localisations[NSW_localisation_RU] = "������";

	//Unique
	localisation_text = new ELocalisationText();
	registered_rarity_router_variants[3] = new RouterVariant();
	registered_rarity_router_variants[3]->localisation = localisation_text;
	registered_rarity_router_variants[3]->color = new HSVRGBAColor();
	registered_rarity_router_variants[3]->color->set_color_RGBA(1.0f, 0.5f, 0.25f, 1.0f);
	localisation_text->base_name = "Unique";
	localisation_text->localisations[NSW_localisation_EN] = "Unique";
	localisation_text->localisations[NSW_localisation_RU] = "����������";
}

void EWindowMain::register_alternate_qualities()
{
	ELocalisationText* localisation_text = nullptr;
	/*		REGISTER ALTERNATE QUALITIES		*/
	//Superior
	localisation_text = new ELocalisationText();

	localisation_text->base_name = "Superior";
	localisation_text->localisations[NSW_localisation_EN] = "Superior";
	localisation_text->localisations[NSW_localisation_RU] = "�������";

	registered_alternate_gem_quality_router_variants[0] = new RouterVariant();
	registered_alternate_gem_quality_router_variants[0]->localisation = localisation_text;
	registered_alternate_gem_quality_router_variants[0]->color = new HSVRGBAColor();
	registered_alternate_gem_quality_router_variants[0]->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

	//Anomalous
	localisation_text = new ELocalisationText();

	localisation_text->base_name = "Anomalous";
	localisation_text->localisations[NSW_localisation_EN] = "Anomalous";
	localisation_text->localisations[NSW_localisation_RU] = "����������";

	registered_alternate_gem_quality_router_variants[1] = new RouterVariant();
	registered_alternate_gem_quality_router_variants[1]->localisation = localisation_text;
	registered_alternate_gem_quality_router_variants[1]->color = new HSVRGBAColor();
	registered_alternate_gem_quality_router_variants[1]->color->set_color_RGBA(1.0f, 0.4f, 0.4f, 1.0f);


	//Divergent
	localisation_text = new ELocalisationText();

	localisation_text->base_name = "Divergent";
	localisation_text->localisations[NSW_localisation_EN] = "Divergent";
	localisation_text->localisations[NSW_localisation_RU] = "�����������";

	registered_alternate_gem_quality_router_variants[2] = new RouterVariant();
	registered_alternate_gem_quality_router_variants[2]->localisation = localisation_text;
	registered_alternate_gem_quality_router_variants[2]->color = new HSVRGBAColor();
	registered_alternate_gem_quality_router_variants[2]->color->set_color_RGBA(0.4f, 1.0f, 0.4f, 1.0f);


	//Phantasmal
	localisation_text = new ELocalisationText();

	localisation_text->base_name = "Phantasmal";
	localisation_text->localisations[NSW_localisation_EN] = "Phantasmal";
	localisation_text->localisations[NSW_localisation_RU] = "���������";

	registered_alternate_gem_quality_router_variants[3] = new RouterVariant();
	registered_alternate_gem_quality_router_variants[3]->localisation = localisation_text;
	registered_alternate_gem_quality_router_variants[3]->color = new HSVRGBAColor();
	registered_alternate_gem_quality_router_variants[3]->color->set_color_RGBA(0.4f, 0.4f, 1.0f, 1.0f);
}

void EWindowMain::register_game_item_attributes()
{
	/*		REGISTER FILTER BLOCK ATTRIBUTES		*/
	GameItemAttribute* jc_filter_block_attribute;
	ELocalisationText		jc_localisation;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ItemLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Item level";
	jc_localisation.localisations[NSW_localisation_RU] = "������� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "DropLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Required level";
	jc_localisation.localisations[NSW_localisation_RU] = "��������� �������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Quality";
	jc_localisation.localisations[NSW_localisation_EN] = "Quality";
	jc_localisation.localisations[NSW_localisation_RU] = "��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "GemLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Gem level";
	jc_localisation.localisations[NSW_localisation_RU] = "������� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SocketGroup";
	jc_localisation.localisations[NSW_localisation_EN] = "Links colours";
	jc_localisation.localisations[NSW_localisation_RU] = "����� ������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Sockets";
	jc_localisation.localisations[NSW_localisation_EN] = "Sockets colours";
	jc_localisation.localisations[NSW_localisation_RU] = "����� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_TEXT;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "LinkedSockets";
	jc_localisation.localisations[NSW_localisation_EN] = "Linked sockets";
	jc_localisation.localisations[NSW_localisation_RU] = "��������� ������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "StackSize";
	jc_localisation.localisations[NSW_localisation_EN] = "Stack size";
	jc_localisation.localisations[NSW_localisation_RU] = "������ ������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "AreaLevel";
	jc_localisation.localisations[NSW_localisation_EN] = "Area level";
	jc_localisation.localisations[NSW_localisation_RU] = "������� �������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	jc_filter_block_attribute->global_attribute_value = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "CorruptedMods";
	jc_localisation.localisations[NSW_localisation_EN] = "Corrupted mods";
	jc_localisation.localisations[NSW_localisation_RU] = "������������ ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Width";
	jc_localisation.localisations[NSW_localisation_EN] = "Width";
	jc_localisation.localisations[NSW_localisation_RU] = "������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_WIDTH] = jc_filter_block_attribute;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Height";
	jc_localisation.localisations[NSW_localisation_EN] = "Height";
	jc_localisation.localisations[NSW_localisation_RU] = "������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_HEIGHT] = jc_filter_block_attribute;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "EnchantmentPassiveNum";
	jc_localisation.localisations[NSW_localisation_EN] = "Passives count";
	jc_localisation.localisations[NSW_localisation_RU] = "�������� ���������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "GemQualityType";
	jc_localisation.localisations[NSW_localisation_EN] = "Alternative quality";
	jc_localisation.localisations[NSW_localisation_RU] = "�������������� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST;
	jc_filter_block_attribute->have_operator = false;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "BaseDefencePercentile";
	jc_localisation.localisations[NSW_localisation_EN] = "Defence procentile";
	jc_localisation.localisations[NSW_localisation_RU] = "���������� ������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasSearingExarchImplicit";
	jc_localisation.localisations[NSW_localisation_EN] = "Searing Exarch implicits";
	jc_localisation.localisations[NSW_localisation_RU] = "�������� ���������� �������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasEaterOfWorldsImplicit";
	jc_localisation.localisations[NSW_localisation_EN] = "Eater of Worlds implicits";
	jc_localisation.localisations[NSW_localisation_RU] = "�������� ���������� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "MapTier";
	jc_localisation.localisations[NSW_localisation_EN] = "Map tier";
	jc_localisation.localisations[NSW_localisation_RU] = "��� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Rarity";
	jc_localisation.localisations[NSW_localisation_EN] = "Item rarity";
	jc_localisation.localisations[NSW_localisation_RU] = "�������� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST;
	jc_filter_block_attribute->have_operator = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);








	/*____________________________________LISTED SECTION___________________________________________________*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "BaseType";
	jc_localisation.localisations[NSW_localisation_EN] = "Game item";
	jc_localisation.localisations[NSW_localisation_RU] = "�������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->button_x_size_override = 200.0f;
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->have_exact_match = true;
	jc_filter_block_attribute->have_input_field_for_listed = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM];
	GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_BASE_TYPE] = jc_filter_block_attribute;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Class";
	jc_localisation.localisations[NSW_localisation_EN] = "Item class";
	jc_localisation.localisations[NSW_localisation_RU] = "����� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->button_x_size_override = 150.0f;
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->have_exact_match = true;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_BASE_CLASS];

	GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_BASE_CLASS] = jc_filter_block_attribute;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasExplicitMod";

	jc_localisation.localisations[NSW_localisation_EN] = "Explicit mode";
	jc_localisation.localisations[NSW_localisation_RU] = "�������/�������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->button_x_size_override = 280.0f;

	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->have_input_field_for_listed = true;
	jc_filter_block_attribute->have_exact_match = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS];

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "EnchantmentPassiveNode";

	jc_localisation.localisations[NSW_localisation_EN] = "Cluster passive";
	jc_localisation.localisations[NSW_localisation_RU] = "�������� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->button_x_size_override = 200.0f;

	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->have_exact_match = true;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_CLUSTER_PASSIVE];

	registered_game_item_attributes.push_back(jc_filter_block_attribute);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasInfluence";
	jc_localisation.localisations[NSW_localisation_EN] = "Influence";
	jc_localisation.localisations[NSW_localisation_RU] = "�������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->button_x_size_override = 150.0f;

	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->have_exact_match = true;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_INFLUENCE];

	registered_game_item_attributes.push_back(jc_filter_block_attribute);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "HasEnchantment";
	jc_localisation.localisations[NSW_localisation_EN] = "Enchantment";
	jc_localisation.localisations[NSW_localisation_RU] = "�����������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->button_x_size_override = 200.0f;

	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->have_input_field_for_listed = true;
	jc_filter_block_attribute->have_exact_match = false;

	jc_filter_block_attribute->filter_rule = EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_ENCHANTMENT];

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	/*_____________________________________________________________________________________________________*/





	/*____________________________________BOOLEAN SECTION___________________________________________________*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "AnyEnchantment";
	jc_localisation.localisations[NSW_localisation_EN] = "Any enchantment";
	jc_localisation.localisations[NSW_localisation_RU] = "���� �����������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	//jc_filter_block_attribute->filter_rule = EFilterRule::registered_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS];

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "AlternateQuality";
	jc_localisation.localisations[NSW_localisation_EN] = "Alternate quality";
	jc_localisation.localisations[NSW_localisation_RU] = "�������������� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Replica";
	jc_localisation.localisations[NSW_localisation_EN] = "Replica";
	jc_localisation.localisations[NSW_localisation_RU] = "�������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Identified";
	jc_localisation.localisations[NSW_localisation_EN] = "Identified";
	jc_localisation.localisations[NSW_localisation_RU] = "�������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Corrupted";
	jc_localisation.localisations[NSW_localisation_EN] = "Corrupted";
	jc_localisation.localisations[NSW_localisation_RU] = "���������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Mirrored";
	jc_localisation.localisations[NSW_localisation_EN] = "Mirrored";
	jc_localisation.localisations[NSW_localisation_RU] = "������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ElderItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Elder item";
	jc_localisation.localisations[NSW_localisation_RU] = "������� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ShaperItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Shaper item";
	jc_localisation.localisations[NSW_localisation_RU] = "������� ���������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "FracturedItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Fractured item";
	jc_localisation.localisations[NSW_localisation_RU] = "���������� �������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SynthesisedItem";
	jc_localisation.localisations[NSW_localisation_EN] = "Synthesised item";
	jc_localisation.localisations[NSW_localisation_RU] = "��������������� �������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ElderMap";
	jc_localisation.localisations[NSW_localisation_EN] = "Elder map";
	jc_localisation.localisations[NSW_localisation_RU] = "����� ��������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "ShapedMap";
	jc_localisation.localisations[NSW_localisation_EN] = "Shaped map";
	jc_localisation.localisations[NSW_localisation_RU] = "����� ���������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "BlightedMap";
	jc_localisation.localisations[NSW_localisation_EN] = "Blighted map";
	jc_localisation.localisations[NSW_localisation_RU] = "����� �������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "UberBlightedMap";
	jc_localisation.localisations[NSW_localisation_EN] = "Uber Blighted map";
	jc_localisation.localisations[NSW_localisation_RU] = "����� �����������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER;
	jc_filter_block_attribute->have_operator = false;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	/*____________________________________COSMETIC SECTION___________________________________________________*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetBackgroundColor";
	jc_localisation.localisations[NSW_localisation_EN] = "Background color";
	jc_localisation.localisations[NSW_localisation_RU] = "���� ����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetBorderColor";
	jc_localisation.localisations[NSW_localisation_EN] = "Border color";
	jc_localisation.localisations[NSW_localisation_RU] = "���� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetTextColor";
	jc_localisation.localisations[NSW_localisation_EN] = "Text color";
	jc_localisation.localisations[NSW_localisation_RU] = "���� ������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "SetFontSize";
	jc_localisation.localisations[NSW_localisation_EN] = "Text size";
	jc_localisation.localisations[NSW_localisation_RU] = "������ ������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_SLIDER;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "MinimapIcon";
	jc_localisation.localisations[NSW_localisation_EN] = "Minimap icon";
	jc_localisation.localisations[NSW_localisation_RU] = "������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_MINIMAP_ICON;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "CustomAlertSound";
	jc_localisation.localisations[NSW_localisation_EN] = "User sound";
	jc_localisation.localisations[NSW_localisation_RU] = "���� ����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_USER_SOUND;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "CustomAlertSoundOptional";
	jc_localisation.localisations[NSW_localisation_EN] = "User sound";
	jc_localisation.localisations[NSW_localisation_RU] = "���� ����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_USER_SOUND;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "PlayAlertSound";
	jc_localisation.localisations[NSW_localisation_EN] = "Game sound";
	jc_localisation.localisations[NSW_localisation_RU] = "����������� ����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_INGAME_SOUND;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "PlayAlertSoundPositional";
	jc_localisation.localisations[NSW_localisation_EN] = "Game sound (positional)";
	jc_localisation.localisations[NSW_localisation_RU] = "����������� ���� (����������)";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_INGAME_SOUND;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "DisableDropSound";
	jc_localisation.localisations[NSW_localisation_EN] = "Disable drop sound";
	jc_localisation.localisations[NSW_localisation_RU] = "��������� ���� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DISABLE_DROP_SOUND;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "EnableDropSound";
	jc_localisation.localisations[NSW_localisation_EN] = "Enable drop sound";
	jc_localisation.localisations[NSW_localisation_RU] = "�������� ���� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_ENABLE_DROP_SOUND;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "DisableDropSoundIfAlertSound";
	jc_localisation.localisations[NSW_localisation_EN] = "Disable drop sound if alert sound";
	jc_localisation.localisations[NSW_localisation_RU] = "��������� ���� �����, ���� ���� ����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_DISABLE_DROP_SOUND_IF_ALERT;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "EnableDropSoundIfAlertSound";
	jc_localisation.localisations[NSW_localisation_EN] = "Enable drop sound if alert sound";
	jc_localisation.localisations[NSW_localisation_RU] = "�������� ���� �����, ���� ���� ����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_ENABLE_DROP_SOUND_IF_ALERT;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "PlayEffect";
	jc_localisation.localisations[NSW_localisation_EN] = "Loot ray";
	jc_localisation.localisations[NSW_localisation_RU] = "��� �����";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RAY;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "Continue";
	jc_localisation.localisations[NSW_localisation_EN] = "Continue";
	jc_localisation.localisations[NSW_localisation_RU] = "����������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_CONTINUE;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->always_present = true;

	registered_game_item_attributes.push_back(jc_filter_block_attribute);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "config_VersionControl";
	jc_localisation.localisations[NSW_localisation_EN] = "Configue versions";
	jc_localisation.localisations[NSW_localisation_RU] = "��������� ������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_CONFIG;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_CONFIG_VERSIONS;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->commentary_config = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//	OLD DADEditor Parameters
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "autogen";
	jc_localisation.localisations[NSW_localisation_EN] = "Autogeneration (old version support)";
	jc_localisation.localisations[NSW_localisation_RU] = "������������� (��������� ������ ������)";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_CONFIG;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_OLD_VERSION_AUTOGEN;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->commentary_config = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_localisation.base_name = "BlockSeparator";
	jc_localisation.localisations[NSW_localisation_EN] = "Block separator";
	jc_localisation.localisations[NSW_localisation_RU] = "�����������";

	jc_filter_block_attribute = new GameItemAttribute();
	jc_filter_block_attribute->localisation = jc_localisation;
	jc_filter_block_attribute->filter_attribute_type = FilterAttributeType::FILTER_ATTRIBUTE_TYPE_CONFIG;
	jc_filter_block_attribute->filter_attribute_value_type = FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_CONFIG_SEPARATOR;
	jc_filter_block_attribute->have_operator = false;
	jc_filter_block_attribute->commentary_config = true;
	registered_game_item_attributes.push_back(jc_filter_block_attribute);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void EWindowMain::register_filter_rules()
{
	EFilterRule* jc_filter_rule = nullptr;
	DataEntityFilter* jc_filter = nullptr;

	// // // GLOBAL // // //
	////////////////////////////////////////////////////////////////////////////////////////////
	//game items
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->min_y_size = 90.0f;
	jc_filter_rule->focused_by_data_type = "Game item";
	jc_filter_rule->stored_action_for_data_entity_group = &EDataActionCollection::action_add_wide_item_to_group_receiver;

	//filter by game item
	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);

	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//base class
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->min_y_size = 80.0f;
	jc_filter_rule->focused_by_data_type = "Base Class";
	jc_filter_rule->stored_action_for_data_entity_group = &EDataActionCollection::action_add_wide_item_to_group_receiver;

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Base Class");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_BASE_CLASS] = jc_filter_rule;


	////////////////////////////////////////////////////////////////////////////////////////////
	//influence
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->min_y_size = 80.0f;
	jc_filter_rule->focused_by_data_type = "Influence";
	jc_filter_rule->stored_action_for_data_entity_group = &EDataActionCollection::action_add_wide_item_to_group_receiver;

	jc_filter = new DataEntityFilter();


	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Influence");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_INFLUENCE] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//gem
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->focused_by_data_type = "Gem";
	jc_filter_rule->stored_action_for_data_entity_group = &EDataActionCollection::action_add_wide_item_to_group_receiver;

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Gem");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_SKILL_GEMS] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//explicit
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->min_y_size = 110.0f;
	jc_filter_rule->focused_by_data_type = "Explicit";
	jc_filter_rule->stored_action_for_data_entity_group = &EDataActionCollection::action_add_wide_item_to_group_receiver;

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Explicit");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_EXPLICITS] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//cluster passives
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->min_y_size = 80.0f;
	jc_filter_rule->focused_by_data_type = "Cluster passive";
	jc_filter_rule->stored_action_for_data_entity_group = &EDataActionCollection::action_add_wide_item_to_group_receiver;

	jc_filter = new DataEntityFilter();

	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Cluster passive");

	jc_filter_rule->required_tag_list.push_back(jc_filter);
	EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_CLUSTER_PASSIVE] = jc_filter_rule;

	////////////////////////////////////////////////////////////////////////////////////////////
	//enchantments from lab
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->min_y_size = 100.0f;
	jc_filter_rule->focused_by_data_type = "Enchantment";
	jc_filter_rule->stored_action_for_data_entity_group = &EDataActionCollection::action_add_wide_item_to_group_receiver;

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
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/all_items");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "All items";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "��� ��������";
	jc_filter_rule->tag = "Game item";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Game item");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);
	////////////////////////////////////////////////////////////////////////////////////////////
	//ALL CLASSES
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/all_items");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "All classes";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "��� ������";
	jc_filter_rule->tag = "Base Class";

	//filter by game item
	jc_filter = new DataEntityFilter();
	jc_filter->target_tag_name = "data type";
	jc_filter->suitable_values_list.push_back("Base Class");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//


	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//TRASH DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/card");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Trash divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "�������� ��������� �����";
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
	//COMMON DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/card");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Common divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "������� ��������� �����";
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
	//MODERATE DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/card");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Moderate divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "������� ��������� �����";
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
	//RARE DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/card");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Rare divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "������ ��������� �����";
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
	//EXPENSIVE DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/card");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Expensive divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "������� ��������� �����";
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
	jc_filter->suitable_values_list.push_back("Very expensive");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//VERY EXPENSIVE DIVINATIONS
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/card");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Very expensive divinations";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "����� ������� ��������� �����";
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
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/SuperRing");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Heist bases";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "���� �����";
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
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("buttons/button_remove_filter_block");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Deleted items";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "�������� ��������";
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
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/Steel_Ring_inventory_icon");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Atlas bases";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "���� ������";
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
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/Ornate_Spiked_Shield_inventory_icon");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Top tier base";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "������ ���� ���������";
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
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/RitualRune");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "League: Ritual";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "����: ������";
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
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/RoguesMarker");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Heist league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "���� '�����'";
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
	//Forbidden sanctum league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/Sanctum_league");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Forbidden Sanctum league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "���� '��������� ���������'";
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
	jc_filter->suitable_values_list.push_back("Introduced: Forbidden Sanctum league");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);
	////////////////////////////////////////////////////////////////////////////////////////////
	//Kalandra league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/LakeStampingDevice");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Kalandra league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "���� '��������'";
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
	//Archnemesis league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/Archnemesis_league");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Archnemesis league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "���� '���������'";
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
	jc_filter->suitable_values_list.push_back("Introduced: Archnemesis league");
	jc_filter_rule->required_tag_list.push_back(jc_filter);
	//

	//
	//EFilterRule::registered_global_filter_rules.push_back(jc_filter_rule);
	EFilterRule::registered_filter_rules_for_list.push_back(jc_filter_rule);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Scourge league
	jc_filter_rule = new EFilterRule();
	jc_filter_rule->icon_texture = NS_EGraphicCore::load_from_textures_folder("icons/HellscapePaleBoss");

	jc_filter_rule->localisation_text = new ELocalisationText();
	jc_filter_rule->localisation_text->localisations[NSW_localisation_EN] = "Scourge league";
	jc_filter_rule->localisation_text->localisations[NSW_localisation_RU] = "���� '���������'";
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
	jc_filter->suitable_values_list.push_back("Introduced: Scourge league");
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

		std::string loot_filter_full_name = p.path().filename().u8string();
		std::string loot_filter_name = loot_filter_full_name.substr(0, loot_filter_full_name.length() - 7);

		//EInputCore::logger_param("detect file:", filter_path);
		//writer << custom_sound << endl;;




		if
			(
				(loot_filter_full_name.length() >= 8)
				&&
				(EStringUtils::to_lower(loot_filter_full_name.substr(loot_filter_full_name.length() - 7, 7)) == ".filter")
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
				loot_filter_button->loot_filter_full_path = filter_path;
				loot_filter_button->filter_name = loot_filter_name;

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

void EWindowMain::load_custom_sound_list()
{
	for (int i = 0; i < EWindowMain::custom_sound_list.size(); i++)
	{
		delete EWindowMain::custom_sound_list[i];
	}

	EWindowMain::custom_sound_list.clear();
	EWindowMain::custom_sound_list.shrink_to_fit();

	for (auto& p : std::experimental::filesystem::directory_iterator(path_of_exile_folder))
	{
		std::string sound_path = EStringUtils::UTF8_to_ANSI(p.path().u8string());

		std::string sound_name = EStringUtils::UTF8_to_ANSI(p.path().filename().u8string());

		if
			(
				(sound_name.length() >= 8)
				&&
				(
					(EStringUtils::to_lower(sound_name.substr(sound_name.length() - 4, 4)) == ".mp3")
					||
					(EStringUtils::to_lower(sound_name.substr(sound_name.length() - 4, 4)) == ".wav")
					)
				)
		{
			ENamedSound* named_sound = new ENamedSound(path_of_exile_folder + p.path().filename().u8string());
			ELocalisationText l_text;
			l_text.base_name = sound_name;
			l_text.localisations[NSW_localisation_EN] = sound_name;
			l_text.localisations[NSW_localisation_RU] = sound_name;
			named_sound->localisation_text = l_text;

			EWindowMain::custom_sound_list.push_back(named_sound);
		}
	}
}

void EWindowMain::load_ingame_sound_list()
{






	ENamedSound* named_sound = nullptr;
	ELocalisationText l_text;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert06.wav");
	l_text.base_name = "6";
	l_text.localisations[NSW_localisation_EN] = "Something worth!";
	l_text.localisations[NSW_localisation_RU] = "���-�� ������!";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert01.wav");
	l_text.base_name = "1";
	l_text.localisations[NSW_localisation_EN] = "Iron drum 1";
	l_text.localisations[NSW_localisation_RU] = "�������� ������� 1";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);



	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert10.wav");
	l_text.base_name = "10";
	l_text.localisations[NSW_localisation_EN] = "Iron drum 2";
	l_text.localisations[NSW_localisation_RU] = "�������� ������� 2";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);






	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert13.wav");
	l_text.base_name = "13";
	l_text.localisations[NSW_localisation_EN] = "Iron drum 3";
	l_text.localisations[NSW_localisation_RU] = "�������� ������� 3";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert03.wav");
	l_text.base_name = "3";
	l_text.localisations[NSW_localisation_EN] = "Drum 1";
	l_text.localisations[NSW_localisation_RU] = "������� 1";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);



	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert11.wav");
	l_text.base_name = "11";
	l_text.localisations[NSW_localisation_EN] = "Drum 2";
	l_text.localisations[NSW_localisation_RU] = "������� 2";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);



	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert16.wav");
	l_text.base_name = "16";
	l_text.localisations[NSW_localisation_EN] = "Drum 3";
	l_text.localisations[NSW_localisation_RU] = "������� 3";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);




	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert02.wav");
	l_text.base_name = "2";
	l_text.localisations[NSW_localisation_EN] = "Drum 4";
	l_text.localisations[NSW_localisation_RU] = "������� 4";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert04.wav");
	l_text.base_name = "4";
	l_text.localisations[NSW_localisation_EN] = "Echo 1";
	l_text.localisations[NSW_localisation_RU] = "��� 1";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);





	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert05.wav");
	l_text.base_name = "5";
	l_text.localisations[NSW_localisation_EN] = "Echo 2";
	l_text.localisations[NSW_localisation_RU] = "��� 2";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);





	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert07.wav");
	l_text.base_name = "7";
	l_text.localisations[NSW_localisation_EN] = "Echo 3";
	l_text.localisations[NSW_localisation_RU] = "��� 3";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);








	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert08.wav");
	l_text.base_name = "8";
	l_text.localisations[NSW_localisation_EN] = "Echo 4";
	l_text.localisations[NSW_localisation_RU] = "��� 4";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);








	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert09.wav");
	l_text.base_name = "9";
	l_text.localisations[NSW_localisation_EN] = "Echo 5";
	l_text.localisations[NSW_localisation_RU] = "��� 5";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);





	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert14.wav");
	l_text.base_name = "14";
	l_text.localisations[NSW_localisation_EN] = "Echo 6";
	l_text.localisations[NSW_localisation_RU] = "��� 6";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);






	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert15.wav");
	l_text.base_name = "15";
	l_text.localisations[NSW_localisation_EN] = "Echo 7";
	l_text.localisations[NSW_localisation_RU] = "��� 7";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	named_sound = new ENamedSound("data/sounds/default_drop_sound/ItemFilterAlert12.wav");
	l_text.base_name = "12";
	l_text.localisations[NSW_localisation_EN] = "Glass";
	l_text.localisations[NSW_localisation_RU] = "������";
	named_sound->localisation_text = l_text;
	EWindowMain::default_sound_list.push_back(named_sound);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		//||
		//(buffer_text == "<>")
		||
		(buffer_text == "!");
}

void EWindowMain::open_loot_filter(std::string _full_path, LootFlterOpenMode _loot_filter_mode)
{
	EInputCore::logger_param("open loot filter", _full_path);

	//loot_filter_editor->scroll_y = 1.0f;

	std::ifstream file;
	std::string full_line;

	file.open(_full_path);

	filter_text_lines.clear();

	while (std::getline(file, full_line))
	{
		filter_text_lines.push_back(full_line);
	}


	parse_filter_text_lines(nullptr, _loot_filter_mode);

	//for (EButtonGroup* group : EWindowMain::loot_filter_editor->group_list)
	//{
	//	if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(group))
	//	{
	//		EInputCore::logger_simple_info("It FilterBlock!");
	//	}
	//	else
	//	{
	//		EInputCore::logger_simple_info("It NOT FilterBlock!");
	//	}
	//}

	file.close();

	//EButtonGroup::refresh_button_group(EWindowMain::loot_filter_editor);

}

EButtonGroupFilterBlock* EWindowMain::create_filter_block(EButtonGroup* _target_editor, int _specific_position = -1)
{

	//EInputCore::logger_simple_info("create new block!");
	//whole filter block
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroupFilterBlock*
		whole_filter_block_group = new EButtonGroupFilterBlock(new ERegionGabarite(1200.0f, 300.0f));
	whole_filter_block_group->init_button_group(EGUIStyle::active_style, true, true, false);
	whole_filter_block_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);
	whole_filter_block_group->debug_name = "Whole filter block";
	whole_filter_block_group->focusable_for_select = true;
	whole_filter_block_group->additional_y_distance = 16.0f;

	if (_specific_position < 0)
	{
		_target_editor->add_group(whole_filter_block_group);
	}
	else
	{
		_target_editor->add_group_scecific_position(whole_filter_block_group, _specific_position);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//workspace bottom part
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup* workspace_part = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(1200.0f, 150.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);

	whole_filter_block_group->add_group(workspace_part);
	workspace_part->debug_name = "Filter block workspace part";
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/*			TOP CONTROL PART			*/
	// whole line
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroupTopControlSection* control_part = new EButtonGroupTopControlSection(new ERegionGabarite(1200.0f, 30.0f));
	control_part->init_button_group(EGUIStyle::active_style, false, false, true);
	control_part->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_static_autosize);

	control_part->pointer_to_filter_block_group = whole_filter_block_group;
	control_part->debug_name = "Control part";

	whole_filter_block_group->pointer_to_top_control_block = control_part;
	whole_filter_block_group->add_group(control_part);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//left section for preview
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		control_part_left_show_hide_section = new EButtonGroup(new ERegionGabarite(480.0f, 30.0f));
	control_part_left_show_hide_section->init_button_group(EGUIStyle::active_style, false, false, true);
	control_part_left_show_hide_section->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);
	control_part_left_show_hide_section->debug_name = "Left show/hide";

	whole_filter_block_group->pointer_to_control_group_left_show_hide = control_part_left_show_hide_section;
	control_part->add_group(control_part_left_show_hide_section);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	//mid section for button import
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//EButtonGroup*
	//	control_part_mid_import = new EButtonGroup(new ERegionGabarite(215.0f, 30.0f));
	//control_part_mid_import->init_button_group(EGUIStyle::active_style, false, false, true);
	//control_part_mid_import->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);
	//control_part_mid_import->debug_name = "Mid part import";

	//whole_filter_block_group->pointer_to_control_group_mid_import = control_part_mid_import;
	//control_part->add_group(control_part_mid_import);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//mid section for version control
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		control_part_mid_versions = new EButtonGroup(new ERegionGabarite(200.0f, 30.0f));
	control_part_mid_versions->init_button_group(EGUIStyle::active_style, false, false, true);
	control_part_mid_versions->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
	control_part_mid_versions->debug_name = "Versions";

	whole_filter_block_group->pointer_to_control_group_mid_versions = control_part_mid_versions;
	control_part->add_group(control_part_mid_versions);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	//mid section show hide cosmetic
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		control_part_mid_show_hide_cosmetic = new EButtonGroup(new ERegionGabarite(110.0f, 30.0f));
	control_part_mid_show_hide_cosmetic->init_button_group(EGUIStyle::active_style, false, false, true);
	control_part_mid_show_hide_cosmetic->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);
	control_part_mid_show_hide_cosmetic->debug_name = "Show/hide cosmetic";

	whole_filter_block_group->pointer_to_control_group_mid_versions = control_part_mid_show_hide_cosmetic;
	control_part->add_group(control_part_mid_show_hide_cosmetic);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//right section for preview box
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		control_part_right_preview_box = new EButtonGroup(new ERegionGabarite(182.0f, 30.0f));
	control_part_right_preview_box->init_button_group(EGUIStyle::active_style, false, false, true);
	control_part_right_preview_box->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);

	whole_filter_block_group->pointer_to_preview_box_segment = control_part_right_preview_box;
	control_part->add_group(control_part_right_preview_box);

	whole_filter_block_group->pointer_to_top_control_block_right_section = control_part_right_preview_box;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*			===============================			*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//left additional section
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		left_control_section = EButtonGroup::create_default_button_group(new ERegionGabarite(40.0f, 20.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);

	workspace_part->add_group(left_control_section);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//		SHOW/HIDE LOOT BUTTON ROUTER
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	EntityButtonVariantRouterForFilterBlock* button_variant_router = new EntityButtonVariantRouterForFilterBlock();
	button_variant_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(120.0f, 29.0f),
		control_part_left_show_hide_section,
		&EDataActionCollection::action_rotate_variant,
		nullptr
	);

	button_variant_router->layer_with_icon = button_variant_router->sprite_layer_list.back();
	//
	ETextArea* jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_router), EFont::font_list[0], "|?|");
	button_variant_router->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_router, jc_text_area);


	//
	RouterVariant* router_variant;
	ELocalisationText* local_text = nullptr;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//		router variant
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Hide";
	local_text->localisations[NSW_localisation_EN] = "Loot: hidden";
	local_text->localisations[NSW_localisation_RU] = "���: �����";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.5f, 0.45f, 1.0f);

	button_variant_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	//		router variant
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Show";
	local_text->localisations[NSW_localisation_EN] = "Loot: Visible";
	local_text->localisations[NSW_localisation_RU] = "���: �����";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.8f, 1.0f, 0.8f, 1.0f);

	button_variant_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	button_variant_router->select_variant(1);

	control_part->button_list.push_back(button_variant_router);
	whole_filter_block_group->button_show_hide = button_variant_router;


	//		CONTINUE PARAMETER
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	EntityButtonVariantRouterForFilterBlock* button_continue = new EntityButtonVariantRouterForFilterBlock();
	button_continue->make_as_default_button_with_icon
	(
		new ERegionGabarite(120.0f, 29.0f),
		control_part_left_show_hide_section,
		&EDataActionCollection::action_rotate_variant,
		nullptr
	);

	button_continue->layer_with_icon = button_continue->sprite_layer_list.back();
	//
	jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_continue), EFont::font_list[0], "|?|");
	button_continue->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_continue, jc_text_area);


	//
	router_variant;
	local_text = nullptr;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//		router variant
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Continue";
	local_text->localisations[NSW_localisation_EN] = "Continue";
	local_text->localisations[NSW_localisation_RU] = "����������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.25f, 0.9f, 1.0f, 1.0f);

	button_continue->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	//		router variant
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Not continue";
	local_text->localisations[NSW_localisation_EN] = "Not continue";
	local_text->localisations[NSW_localisation_RU] = "�� ����������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.3f, 0.4f, 0.5f, 1.0f);

	button_continue->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	button_continue->select_variant(1);

	control_part->button_list.push_back(button_continue);
	whole_filter_block_group->button_continue = button_continue;


	//		IMPORT BUTTON
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//EntityButtonForFilterBlock*
	//	top_import_button = new EntityButtonForFilterBlock();
	//top_import_button->parent_filter_block = whole_filter_block_group;

	//top_import_button->make_default_button_with_unedible_text
	//(
	//	new ERegionGabarite(200.0f, 29.0f),
	//	control_part_mid_import,
	//	&EDataActionCollection::action_import_filter_text_from_clipboard,
	//	"Import filter block"
	//);

	//control_part_mid_import->button_list.push_back(top_import_button);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string base_names[5] =
	{
		"full_ignore",
		"hide",
		"ignore",
		"standart",
		"focus",
	};

	std::string EN_names[5] =
	{
		"Very soft",
		"Soft",
		"Regular",
		"Strict",
		"Very strict"
	};

	std::string RU_names[5] =
	{
		"���������",
		"������",
		"����������",
		"�������",
		"�������+",
	};


	std::string base_names_for_select_window[5] =
	{
		"very_soft",
		"soft",
		"regular",
		"strict",
		"very_strict"
	};

	std::string EN_names_for_select_window[5] =
	{
		"Full ignore",
		"Hide",
		"Ignore",
		"Default",
		"Focus"
	};

	std::string RU_names_for_select_window[5] =
	{
		"������ �����",
		"������",
		"�����",
		"��������",
		"�����"
	};


	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	for (int i = 0; i < 5; i++)
	{
		button_variant_router = new EntityButtonVariantRouterForFilterBlock();
		button_variant_router->make_as_default_button_with_icon
		(
			new ERegionGabarite(120.0f, 29.0f),
			control_part_mid_versions,
			EDataActionCollection::action_rotate_variant,
			nullptr
		);
		button_variant_router->height_division = 1;

		whole_filter_block_group->version_routers[i] = button_variant_router;

		button_variant_router->rotate_variant_mode = RotateVariantMode::OPEN_CHOOSE_WINDOW;

		button_variant_router->layer_with_icon = button_variant_router->sprite_layer_list.back();

		ETextArea* jc_text_area = ETextArea::create_centered_to_left_text_area(EntityButton::get_last_clickable_area(button_variant_router), EFont::font_list[0], "|?|");
		button_variant_router->pointer_to_text_area = jc_text_area;

		jc_text_area->can_be_edited = false;
		Entity::add_text_area_to_last_clickable_region(button_variant_router, jc_text_area);


		RouterVariant* router_variant = new RouterVariant();
		//	0
		/*************************************************************************************/


		router_variant = new RouterVariant();
		local_text = new ELocalisationText();


		//----------------------------------------------------------------------
		local_text->base_name = base_names[0];
		local_text->localisations[NSW_localisation_EN] = EN_names[i];
		local_text->localisations[NSW_localisation_RU] = RU_names[i];
		router_variant->localisation = local_text;
		//----------------------------------------------------------------------
		local_text = new ELocalisationText();

		local_text->base_name = base_names_for_select_window[0];
		local_text->localisations[NSW_localisation_EN] = EN_names_for_select_window[0];
		local_text->localisations[NSW_localisation_RU] = RU_names_for_select_window[0];
		router_variant->localisation_for_select_window = local_text;
		//----------------------------------------------------------------------

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.0f, 0.0f, 1.0f);

		router_variant->texture = NS_DefaultGabarites::texture_loot_version_full_ignore;

		button_variant_router->router_variant_list.push_back(router_variant);

		/*************************************************************************************/

		//	1
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		//----------------------------------------------------------------------
		local_text->base_name = base_names[1];
		local_text->localisations[NSW_localisation_EN] = EN_names[i];
		local_text->localisations[NSW_localisation_RU] = RU_names[i];
		router_variant->localisation = local_text;
		//----------------------------------------------------------------------
		local_text = new ELocalisationText();

		local_text->base_name = base_names_for_select_window[1];
		local_text->localisations[NSW_localisation_EN] = EN_names_for_select_window[1];
		local_text->localisations[NSW_localisation_RU] = RU_names_for_select_window[1];
		router_variant->localisation_for_select_window = local_text;
		//----------------------------------------------------------------------

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.5f, 0.45f, 1.0f);

		router_variant->texture = NS_DefaultGabarites::texture_loot_version_hide;

		button_variant_router->router_variant_list.push_back(router_variant);

		/*************************************************************************************/

		//	2
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		//----------------------------------------------------------------------
		local_text->base_name = base_names[2];
		local_text->localisations[NSW_localisation_EN] = EN_names[i];
		local_text->localisations[NSW_localisation_RU] = RU_names[i];
		router_variant->localisation = local_text;
		//----------------------------------------------------------------------
		local_text = new ELocalisationText();

		local_text->base_name = base_names_for_select_window[2];
		local_text->localisations[NSW_localisation_EN] = EN_names_for_select_window[2];
		local_text->localisations[NSW_localisation_RU] = RU_names_for_select_window[2];
		router_variant->localisation_for_select_window = local_text;
		//----------------------------------------------------------------------

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.7f, 0.7f, 0.7f, 1.0f);

		router_variant->texture = NS_DefaultGabarites::texture_loot_version_ignore;

		button_variant_router->router_variant_list.push_back(router_variant);

		/*************************************************************************************/

		////	3
		///*************************************************************************************/
		//
		//local_text = new ELocalisationText();

		//local_text->base_name = base_names[i] + "\n" + "Soft ignore";
		//local_text->localisations[NSW_localisation_EN] = EN_names[i] + "\n" + "Soft ignore";
		//local_text->localisations[NSW_localisation_RU] = RU_names[i] + "\n" + "������ �����";
		//router_variant->localisation = local_text;

		//router_variant->color = new HSVRGBAColor();
		//router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

		//router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_soft_ignore");

		//button_variant_router->router_variant_list.push_back(router_variant);
		///*************************************************************************************/

		//	3
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		//----------------------------------------------------------------------
		local_text->base_name = base_names[3];
		local_text->localisations[NSW_localisation_EN] = EN_names[i];
		local_text->localisations[NSW_localisation_RU] = RU_names[i];
		router_variant->localisation = local_text;
		//----------------------------------------------------------------------
		local_text = new ELocalisationText();

		local_text->base_name = base_names_for_select_window[3];
		local_text->localisations[NSW_localisation_EN] = EN_names_for_select_window[3];
		local_text->localisations[NSW_localisation_RU] = RU_names_for_select_window[3];
		router_variant->localisation_for_select_window = local_text;
		//----------------------------------------------------------------------

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.9f, 0.95f, 1.0f, 1.0f);

		router_variant->texture = NS_DefaultGabarites::texture_loot_version_default;

		button_variant_router->router_variant_list.push_back(router_variant);

		/*************************************************************************************/

		////	5
		///*************************************************************************************/
		//
		//local_text = new ELocalisationText();

		//local_text->base_name = base_names[i] + "\n" + "Soft focus";
		//local_text->localisations[NSW_localisation_EN] = EN_names[i];
		//local_text->localisations[NSW_localisation_RU] = RU_names[i];
		//router_variant->localisation = local_text;

		//router_variant->color = new HSVRGBAColor();
		//router_variant->color->set_color_RGBA(0.8f, 1.0f, 0.9f, 1.0f);

		//router_variant->texture = NS_EGraphicCore::load_from_textures_folder("loot_version_soft_focus");

		//button_variant_router->router_variant_list.push_back(router_variant);
		///*************************************************************************************/

		//	4
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		//----------------------------------------------------------------------
		local_text->base_name = base_names[4];
		local_text->localisations[NSW_localisation_EN] = EN_names[i];
		local_text->localisations[NSW_localisation_RU] = RU_names[i];
		router_variant->localisation = local_text;
		//----------------------------------------------------------------------
		local_text = new ELocalisationText();

		local_text->base_name = base_names_for_select_window[4];
		local_text->localisations[NSW_localisation_EN] = EN_names_for_select_window[4];
		local_text->localisations[NSW_localisation_RU] = RU_names_for_select_window[4];
		router_variant->localisation_for_select_window = local_text;
		//----------------------------------------------------------------------

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.6f, 1.0f, 0.8f, 1.0f);

		router_variant->texture = NS_DefaultGabarites::texture_loot_version_focus;

		button_variant_router->router_variant_list.push_back(router_variant);

		/*************************************************************************************/





		button_variant_router->select_variant(3);



		control_part_mid_versions->button_list.push_back(button_variant_router);

		//whole_block_data->button_show_hide = button_variant_router;

	}
	// // // // // // //// // // // // // //// // // // // // //





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EntityButtonVariantRouterForFilterBlock* button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
	button_variant_FB_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(100.0f, 29.0f),
		control_part_mid_show_hide_cosmetic,
		EDataActionCollection::action_rotate_variant,
		nullptr
	);
	Entity::get_last_clickable_area(button_variant_FB_router)->actions_on_click_list.push_back(&EDataActionCollection::action_show_hide_cosmetic_blocks);

	button_variant_FB_router->parent_filter_block = whole_filter_block_group;

	button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

	jc_text_area = ETextArea::create_centered_to_left_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
	button_variant_FB_router->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

	//control_part_mid_show_hide_cosmetic->button_list.push_back(button_variant_FB_router);



	//	0
	/*************************************************************************************/
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Show cosmetic";
	local_text->localisations[NSW_localisation_EN] = "Edit visual";
	local_text->localisations[NSW_localisation_RU] = "�������� ������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.6f, 1.0f, 0.8f, 1.0f);

	router_variant->texture = NS_DefaultGabarites::texture_show_hide_visual_editor;

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/*************************************************************************************/

	//	1
	/*************************************************************************************/
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Hide cosmetic";
	local_text->localisations[NSW_localisation_EN] = "Hide";
	local_text->localisations[NSW_localisation_RU] = "������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.6f, 1.0f, 0.8f, 1.0f);

	router_variant->texture = NS_DefaultGabarites::texture_show_hide_visual_editor_deactivate;

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/*************************************************************************************/

	button_variant_FB_router->select_variant(0);
	control_part_mid_show_hide_cosmetic->button_list.push_back(button_variant_FB_router);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//	BOTTOM SECTION FOR ADD NEW CONTENT, AND MOVE BLOCK
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup* bottom_section_for_block_control = EButtonGroup::create_button_group_without_bg
	(
		new ERegionGabarite(40.0f, 90.0f),
		EGUIStyle::active_style
	);
	bottom_section_for_block_control->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
	left_control_section->add_group(bottom_section_for_block_control);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//	TOP SECTION FOR REMOVE BLOCK
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup* top_section_for_remove = EButtonGroup::create_button_group_without_bg
	(
		new ERegionGabarite(40.0f, 30.0f),
		EGUIStyle::active_style
	);
	top_section_for_remove->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);
	left_control_section->add_group(top_section_for_remove);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	///////////		BUTTON PLUS		///////////
	EntityButton*
		jc_button = new EntityButton();
	jc_button->make_as_default_button_with_icon
	(
		new ERegionGabarite(40.0f, 40.0f),
		bottom_section_for_block_control,
		&EDataActionCollection::action_open_add_content_window,
		NS_DefaultGabarites::texture_button_plus
	);

	EDataContainer_Button_OpenButtonGroup*
		data_open_group = new EDataContainer_Button_OpenButtonGroup();
	data_open_group->master_group = whole_filter_block_group;
	data_open_group->target_group = EWindowMain::data_entity_filter;

	EntityButton::get_last_custom_data(jc_button)->data_container = data_open_group;

	bottom_section_for_block_control->button_list.push_back(jc_button);
	////////////////

	if (false)
	{
		///////////		BUTTON MOVE DOWN		///////////
		EntityButtonForFilterBlock*
			move_down_button = new EntityButtonForFilterBlock();
		move_down_button->make_as_default_button_with_full_icon
		(
			new ERegionGabarite(40.0f, 15.0f),
			bottom_section_for_block_control,
			&EDataActionCollection::action_move_filter_block_down,
			NS_DefaultGabarites::texture_button_move_down
		);
		move_down_button->parent_filter_block = whole_filter_block_group;

		bottom_section_for_block_control->button_list.push_back(move_down_button);
		////////////////

		///////////		BUTTON MOVE UP		///////////
		EntityButtonForFilterBlock*
			move_up_button = new EntityButtonForFilterBlock();
		move_up_button->make_as_default_button_with_full_icon
		(
			new ERegionGabarite(40.0f, 15.0f),
			bottom_section_for_block_control,
			&EDataActionCollection::action_move_filter_block_up,
			NS_DefaultGabarites::texture_button_move_up
		);
		move_up_button->parent_filter_block = whole_filter_block_group;

		bottom_section_for_block_control->button_list.push_back(move_up_button);
		////////////////
	}

	///////////		BUTTON MOVE		///////////
	EntityButtonMoveButtonGroup*
		move_button = new EntityButtonMoveButtonGroup();
	move_button->make_as_default_button_with_full_icon
	(
		new ERegionGabarite(40.0f, 15.0f),
		bottom_section_for_block_control,
		&EDataActionCollection::action_move_button_group,
		NS_DefaultGabarites::texture_button_move
	);
	move_button->target_group_for_moving = whole_filter_block_group;
	move_button->parent_group_for_moving = _target_editor;
	move_button->move_method = MoveVectorMethod::METHOD_DRAG;

	bottom_section_for_block_control->button_list.push_back(move_button);
	////////////////





	///////////		BUTTON CUT		///////////
	EntityButtonMoveButtonGroup*
		cut_button = new EntityButtonMoveButtonGroup();
	cut_button->make_as_default_button_with_full_icon
	(
		new ERegionGabarite(40.0f, 15.0f),
		bottom_section_for_block_control,
		&EDataActionCollection::action_move_button_group,
		NS_DefaultGabarites::texture_button_cut
	);
	cut_button->target_group_for_moving = whole_filter_block_group;
	cut_button->parent_group_for_moving = _target_editor;
	cut_button->move_method = MoveVectorMethod::METHOD_PRESS;

	bottom_section_for_block_control->button_list.push_back(cut_button);
	////////////////






///////////		REMOVE FILTER BLOCK		///////////
	EntityButtonForFilterBlock*
		remove_filter_block_button = new EntityButtonForFilterBlock();
	remove_filter_block_button->make_as_default_button_with_full_icon
	(
		new ERegionGabarite(40.0f, 30.0f),
		top_section_for_remove,
		&EDataActionCollection::action_remove_filter_block,
		NS_DefaultGabarites::texture_button_remove_filter_block
	);
	remove_filter_block_button->parent_filter_block = whole_filter_block_group;

	top_section_for_remove->button_list.push_back(remove_filter_block_button);
	////////////////




	/////////////		BUTTON GEN		///////////
	////generate filter block text
	//jc_button = new EntityButton();
	//jc_button->make_default_button_with_unedible_text
	//(
	//	new ERegionGabarite(50.0f, 22.0f),
	//	left_control_section,
	//	&EDataActionCollection::action_generate_filter_block_text,
	//	"Gen"
	//);

	//auto gen_data = new EDataContainer_Button_StoreParentFilterBlock();
	//gen_data->parent_filter_block = whole_filter_block_group;
	//jc_button->custom_data_list.back()->data_container = gen_data;

	//left_control_section->button_list.push_back(jc_button);
	//////////////////




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

	//listed_condition_segment->button_size_x_override = 200.0f;
	//root group data ontaner
	whole_filter_block_group->pointer_to_listed_segment = listed_condition_segment;
	listed_condition_segment->child_align_direction = ChildElementsAlignDirection::TOP_TO_BOTTOM;

	workspace_part->add_group(listed_condition_segment);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	/*			SECONDARY COSMETIC SEGMENT GROUP		*/

	//		RAY
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	EButtonGroup* ray_cosmetic_segment = EButtonGroup::create_default_button_group(new ERegionGabarite(156.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);

	ray_cosmetic_segment->is_active = false;
	//ray_cosmetic_segment->disable_gabarite = true;

	workspace_part->add_group(ray_cosmetic_segment);
	whole_filter_block_group->pointer_to_ray_segment = ray_cosmetic_segment;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	//		SOUND
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	EButtonGroup*
		sound_cosmetic_segment
		= EButtonGroup::create_default_button_group(new ERegionGabarite(178.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);

	sound_cosmetic_segment->is_active = false;
	//sound_cosmetic_segment->disable_gabarite = true;

	workspace_part->add_group(sound_cosmetic_segment);
	whole_filter_block_group->pointer_to_sound_segment = sound_cosmetic_segment;





	EButtonGroup* bottom_user_sound_section
		= EButtonGroup::create_button_group_without_bg(new ERegionGabarite(178.0f, 65.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_static_autosize);
	sound_cosmetic_segment->add_group(bottom_user_sound_section);

	EButtonGroup* mid_ingame_sound_section
		= EButtonGroup::create_button_group_without_bg(new ERegionGabarite(178.0f, 50.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);
	sound_cosmetic_segment->add_group(mid_ingame_sound_section);

	EButtonGroup* top_drop_sound_section
		= EButtonGroup::create_button_group_without_bg(new ERegionGabarite(178.0f, 40.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_static_autosize);
	sound_cosmetic_segment->add_group(top_drop_sound_section);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//		MINIMAP ICON
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		minimap_cosmetic_segment
		= EButtonGroup::create_default_button_group(new ERegionGabarite(156.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_static_autosize, NSW_dynamic_autosize);

	minimap_cosmetic_segment->is_active = false;
	//	minimap_cosmetic_segment->disable_gabarite = true;

	workspace_part->add_group(minimap_cosmetic_segment);
	whole_filter_block_group->pointer_to_minimap_segment = minimap_cosmetic_segment;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/*			===============================			*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*			SECONDARY COSMETIC SEGMENT BUTTONS [sounds, ray, minimap icon]			*/

	//USER SOUND
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ELocalisationText l_text;
	l_text.localisations[NSW_localisation_EN] = "User sound";
	l_text.localisations[NSW_localisation_RU] = "���� ����";

	EntityButtonFilterSound*
		sound_button = new EntityButtonFilterSound();
	sound_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(145.0f, 22.0f),
		bottom_user_sound_section,
		&EDataActionCollection::action_open_custom_sound_list,
		l_text.localisations[ELocalisationText::active_localisation]
	);
	sound_button->main_text_area->localisation_text = l_text;

	Entity::get_last_clickable_area(sound_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_play_attached_sound);

	sound_button->suppressor = &whole_filter_block_group->custom_sound_suppressor_bool;
	whole_filter_block_group->pointer_to_custom_sound_button = sound_button;
	bottom_user_sound_section->button_list.push_back(sound_button);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//	switcher CUSTOM SOUND
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_button = new EntityButton();
	jc_button->make_default_bool_switcher_button
	(
		new ERegionGabarite(22.0f, 22.0f),
		bottom_user_sound_section,
		EDataActionCollection::action_switch_boolean_value,
		NS_DefaultGabarites::texture_bool_switcher_activated_box,
		NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
		&whole_filter_block_group->custom_sound_suppressor_bool
	);
	bottom_user_sound_section->button_list.push_back(jc_button);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//		OPTIONAL/NOT OPTIONAL USER SOUND VARIANT ROUTER
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
	button_variant_FB_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(170.0f, 22.0f),
		bottom_user_sound_section,
		&EDataActionCollection::action_rotate_variant,
		nullptr
	);
	button_variant_FB_router->parent_filter_block = whole_filter_block_group;


	button_variant_FB_router->rotate_variant_mode = RotateVariantMode::SELECT_NEXT;

	button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

	jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
	button_variant_FB_router->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

	button_variant_FB_router->suppressor = &whole_filter_block_group->custom_sound_suppressor_bool;
	whole_filter_block_group->pointer_to_optional_user_sound = button_variant_FB_router;


	//routers
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Optional";
	local_text->localisations[NSW_localisation_EN] = "Optional";
	local_text->localisations[NSW_localisation_RU] = "������������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.65f, 0.5f, 0.4f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///



	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Mandatory";
	local_text->localisations[NSW_localisation_EN] = "Mandatory";
	local_text->localisations[NSW_localisation_RU] = "������������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.6f, 1.0f, 0.8f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	button_variant_FB_router->select_variant(1);

	bottom_user_sound_section->button_list.push_back(button_variant_FB_router);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////













	//INGAME SOUND
	//	text
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	l_text.localisations[NSW_localisation_EN] = "Ingame sound";
	l_text.localisations[NSW_localisation_RU] = "����� �� ����";
	sound_button = new EntityButtonFilterSound();
	sound_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(145.0f, 22.0f),
		mid_ingame_sound_section,
		&EDataActionCollection::action_open_ingame_sound_list,
		l_text.localisations[ELocalisationText::active_localisation]
	);
	sound_button->main_text_area->localisation_text = l_text;

	Entity::get_last_clickable_area(sound_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_play_attached_sound);
	sound_button->suppressor = &whole_filter_block_group->game_sound_suppressor_bool;
	whole_filter_block_group->pointer_to_game_sound_button = sound_button;
	mid_ingame_sound_section->button_list.push_back(sound_button);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//	switcher GAME_SOUND
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_button = new EntityButton();
	jc_button->make_default_bool_switcher_button
	(
		new ERegionGabarite(22.0f, 22.0f),
		mid_ingame_sound_section,
		EDataActionCollection::action_switch_boolean_value,
		NS_DefaultGabarites::texture_bool_switcher_activated_box,
		NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
		&whole_filter_block_group->game_sound_suppressor_bool
	);
	mid_ingame_sound_section->button_list.push_back(jc_button);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//	volume
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	jc_button = EntityButton::create_vertical_named_slider
	(

		new ERegionGabarite(170.0f, 30.0f),
		mid_ingame_sound_section,
		EFont::font_list[0],
		EGUIStyle::active_style,
		"Volume"
	);
	jc_button->suppressor = &whole_filter_block_group->game_sound_suppressor_bool;

	ETextArea*
		last_text_area = Entity::get_last_text_area(jc_button);

	last_text_area->localisation_text.base_name = "Volume";
	last_text_area->localisation_text.localisations[NSW_localisation_EN] = "Volume";
	last_text_area->localisation_text.localisations[NSW_localisation_RU] = "���������";

	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &whole_filter_block_group->sound_volume_value;
	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;

	whole_filter_block_group->sound_volume = jc_button;
	mid_ingame_sound_section->button_list.push_back(jc_button);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//		POSITIONAL/NOT POSITIONAL SOUND ROUTER
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
	button_variant_FB_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(170.0f, 22.0f),
		mid_ingame_sound_section,
		&EDataActionCollection::action_rotate_variant,
		nullptr
	);
	button_variant_FB_router->parent_filter_block = whole_filter_block_group;


	button_variant_FB_router->rotate_variant_mode = RotateVariantMode::SELECT_NEXT;

	button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

	jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
	button_variant_FB_router->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

	button_variant_FB_router->suppressor = &whole_filter_block_group->game_sound_suppressor_bool;
	whole_filter_block_group->pointer_to_positional_variant_button = button_variant_FB_router;


	//routers
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Not positional";
	local_text->localisations[NSW_localisation_EN] = "Not positional";
	local_text->localisations[NSW_localisation_RU] = "�� �����������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.65f, 0.5f, 0.4f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	/// 
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Positional";
	local_text->localisations[NSW_localisation_EN] = "Positional";
	local_text->localisations[NSW_localisation_RU] = "�����������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.8f, 0.9f, 0.6f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	button_variant_FB_router->select_variant(0);

	mid_ingame_sound_section->button_list.push_back(button_variant_FB_router);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	// 
	// //		ENABLE/DISABLE DROP SOUND
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
	button_variant_FB_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(170.0f, 40.0f),
		top_drop_sound_section,
		&EDataActionCollection::action_rotate_variant,
		nullptr
	);
	button_variant_FB_router->rotate_variant_mode = RotateVariantMode::OPEN_CHOOSE_WINDOW;
	button_variant_FB_router->parent_filter_block = whole_filter_block_group;


	button_variant_FB_router->rotate_variant_mode = RotateVariantMode::SELECT_NEXT;

	button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

	jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
	button_variant_FB_router->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

	//button_variant_FB_router->suppressor = &whole_filter_block_group->game_sound_suppressor_bool;
	whole_filter_block_group->pointer_to_disable_enable_drop_sound = button_variant_FB_router;


	//routers
	//0
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Drop sound: default";
	local_text->localisations[NSW_localisation_EN] = "Drop sound: default";
	local_text->localisations[NSW_localisation_RU] = "���� �����: �������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///


	//1
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "DisableDropSound";
	local_text->localisations[NSW_localisation_EN] = "Drop sound: disable";
	local_text->localisations[NSW_localisation_RU] = "���� �����: ��������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.8f, 0.5f, 0.25f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///


	//2
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "EnableDropSound";
	local_text->localisations[NSW_localisation_EN] = "Drop sound: enable";
	local_text->localisations[NSW_localisation_RU] = "���� �����: �������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.25f, 0.8f, 0.5f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///


	//3
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "DisableDropSoundIfAlertSound";
	local_text->localisations[NSW_localisation_EN] = "Drop sound:\nDisable if alert sound";
	local_text->localisations[NSW_localisation_RU] = "���� �����:\n�������� ��� ��������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.8f, 0.5f, 0.25f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///


	//4
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "EnableDropSoundIfAlertSound";
	local_text->localisations[NSW_localisation_EN] = "Drop sound:\nEnable if alert sound";
	local_text->localisations[NSW_localisation_RU] = "���� �����:\n������� ��� ��������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.25f, 0.8f, 0.5f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///


	button_variant_FB_router->select_variant(0);

	top_drop_sound_section->button_list.push_back(button_variant_FB_router);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//		MINIMAP ICONS SEGMENT
	//		COLOR NAMES ROUTER
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//jc_button = new EntityButtonFilterSound();
		button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
		button_variant_FB_router->make_as_default_button_with_icon
		(
			new ERegionGabarite(124.0f, 22.0f),
			minimap_cosmetic_segment,
			&EDataActionCollection::action_rotate_variant,
			nullptr
		);
		button_variant_FB_router->parent_filter_block = whole_filter_block_group;


		button_variant_FB_router->rotate_variant_mode = RotateVariantMode::OPEN_CHOOSE_WINDOW;

		button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

		jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
		button_variant_FB_router->pointer_to_text_area = jc_text_area;

		jc_text_area->can_be_edited = false;
		Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

		button_variant_FB_router->suppressor = &whole_filter_block_group->minimap_icon_color_suppressor_bool;
		whole_filter_block_group->pointer_to_minimap_icon_color_router = button_variant_FB_router;


		//routers
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Red";
		local_text->localisations[NSW_localisation_EN] = "Red";
		local_text->localisations[NSW_localisation_RU] = "�������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.2f, 0.1f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Green";
		local_text->localisations[NSW_localisation_EN] = "Green";
		local_text->localisations[NSW_localisation_RU] = "������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.25f, 1.0f, 0.4f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Blue";
		local_text->localisations[NSW_localisation_EN] = "Blue";
		local_text->localisations[NSW_localisation_RU] = "�����";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.25f, 0.4f, 1.0f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Brown";
		local_text->localisations[NSW_localisation_EN] = "Brown";
		local_text->localisations[NSW_localisation_RU] = "����������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.5f, 0.25f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "White";
		local_text->localisations[NSW_localisation_EN] = "White";
		local_text->localisations[NSW_localisation_RU] = "�����";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 1.0f, 1.0f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Yellow";
		local_text->localisations[NSW_localisation_EN] = "Yellow";
		local_text->localisations[NSW_localisation_RU] = "Ƹ����";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 1.0f, 0.25f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Cyan";
		local_text->localisations[NSW_localisation_EN] = "Cyan";
		local_text->localisations[NSW_localisation_RU] = "�������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.25f, 0.8f, 1.0f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Grey";
		local_text->localisations[NSW_localisation_EN] = "Grey";
		local_text->localisations[NSW_localisation_RU] = "�����";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.55f, 0.55f, 0.55f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Orange";
		local_text->localisations[NSW_localisation_EN] = "Orange";
		local_text->localisations[NSW_localisation_RU] = "���������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.65f, 0.1f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Pink";
		local_text->localisations[NSW_localisation_EN] = "Pink";
		local_text->localisations[NSW_localisation_RU] = "�������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.5f, 1.0f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Purple";
		local_text->localisations[NSW_localisation_EN] = "Purple";
		local_text->localisations[NSW_localisation_RU] = "����������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.8f, 0.1f, 0.9f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		button_variant_FB_router->select_variant(0);


		minimap_cosmetic_segment->button_list.push_back(button_variant_FB_router);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//	switcher MINIMAP ICON
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		jc_button = new EntityButton();
		jc_button->make_default_bool_switcher_button
		(
			new ERegionGabarite(22.0f, 22.0f),
			minimap_cosmetic_segment,
			EDataActionCollection::action_switch_boolean_value,
			NS_DefaultGabarites::texture_bool_switcher_activated_box,
			NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
			&whole_filter_block_group->minimap_icon_color_suppressor_bool
		);
		minimap_cosmetic_segment->button_list.push_back(jc_button);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	//		SIZE NAMES ROUTER
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//jc_button = new EntityButtonFilterSound();
		button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
		button_variant_FB_router->make_as_default_button_with_icon
		(
			new ERegionGabarite(150.0f, 22.0f),
			minimap_cosmetic_segment,
			&EDataActionCollection::action_rotate_variant,
			nullptr
		);
		button_variant_FB_router->parent_filter_block = whole_filter_block_group;


		button_variant_FB_router->rotate_variant_mode = RotateVariantMode::SELECT_NEXT;

		button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

		jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
		button_variant_FB_router->pointer_to_text_area = jc_text_area;

		jc_text_area->can_be_edited = false;
		Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

		button_variant_FB_router->suppressor = &whole_filter_block_group->minimap_icon_color_suppressor_bool;
		whole_filter_block_group->pointer_to_minimap_icon_size_router = button_variant_FB_router;


		//routers
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "0";
		local_text->localisations[NSW_localisation_EN] = "Large";
		local_text->localisations[NSW_localisation_RU] = "�������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "1";
		local_text->localisations[NSW_localisation_EN] = "Medium";
		local_text->localisations[NSW_localisation_RU] = "�������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.8f, 0.7f, 0.6f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "2";
		local_text->localisations[NSW_localisation_EN] = "Small";
		local_text->localisations[NSW_localisation_RU] = "���������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(0.6f, 0.55f, 0.5f, 1.0f);

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

		button_variant_FB_router->select_variant(0);


		minimap_cosmetic_segment->button_list.push_back(button_variant_FB_router);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}

	//		ICONS ROUTER
	{

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//jc_button = new EntityButtonFilterSound();
		button_variant_router = new EntityButtonVariantRouterForFilterBlock();
		button_variant_router->make_as_default_button_with_icon
		(
			new ERegionGabarite(150.0f, 41.0f),
			minimap_cosmetic_segment,
			&EDataActionCollection::action_rotate_variant,
			nullptr
		);
		button_variant_router->layer_with_icon = button_variant_router->sprite_layer_list.back();
		button_variant_router->rotate_variant_mode = RotateVariantMode::OPEN_CHOOSE_WINDOW;

		jc_text_area = ETextArea::create_centered_to_left_text_area(EntityButton::get_last_clickable_area(button_variant_router), EFont::font_list[0], "|?|");
		button_variant_router->pointer_to_text_area = jc_text_area;

		jc_text_area->can_be_edited = false;
		Entity::add_text_area_to_last_clickable_region(button_variant_router, jc_text_area);

		button_variant_router->suppressor = &whole_filter_block_group->minimap_icon_color_suppressor_bool;
		whole_filter_block_group->pointer_to_minimap_icon_shape_router = button_variant_router;


		//routers
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Circle";
		local_text->localisations[NSW_localisation_EN] = "Circle";
		local_text->localisations[NSW_localisation_RU] = "����";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_circle;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///



		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Diamond";
		local_text->localisations[NSW_localisation_EN] = "Diamond";
		local_text->localisations[NSW_localisation_RU] = "�����";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_diamond;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///



		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Hexagon";
		local_text->localisations[NSW_localisation_EN] = "Hexagon";
		local_text->localisations[NSW_localisation_RU] = "�������������";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_hexagon;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Square";
		local_text->localisations[NSW_localisation_EN] = "Square";
		local_text->localisations[NSW_localisation_RU] = "�������";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_square;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Star";
		local_text->localisations[NSW_localisation_EN] = "Star";
		local_text->localisations[NSW_localisation_RU] = "������";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_star;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Triangle";
		local_text->localisations[NSW_localisation_EN] = "Triangle";
		local_text->localisations[NSW_localisation_RU] = "�����������";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_triangle;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Cross";
		local_text->localisations[NSW_localisation_EN] = "Cross";
		local_text->localisations[NSW_localisation_RU] = "�����";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_cross;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Moon";
		local_text->localisations[NSW_localisation_EN] = "Moon";
		local_text->localisations[NSW_localisation_RU] = "���������";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_moon;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Raindrop";
		local_text->localisations[NSW_localisation_EN] = "Raindrop";
		local_text->localisations[NSW_localisation_RU] = "�����";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_raindrop;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Kite";
		local_text->localisations[NSW_localisation_EN] = "Kite";
		local_text->localisations[NSW_localisation_RU] = "����";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_kite;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Pentagon";
		local_text->localisations[NSW_localisation_EN] = "Pentagon";
		local_text->localisations[NSW_localisation_RU] = "������������";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_pentagon;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///



		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "UpsideDownHouse";
		local_text->localisations[NSW_localisation_EN] = "Marker";
		local_text->localisations[NSW_localisation_RU] = "������";
		router_variant->localisation = local_text;

		router_variant->texture = NS_DefaultGabarites::texture_minimap_shape_upside_down_house;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.60f, 1.0f);

		button_variant_router->router_variant_list.push_back(router_variant);
		/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
		button_variant_router->select_variant(0);


		minimap_cosmetic_segment->button_list.push_back(button_variant_router);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	/*=========================================================================*/


	//		RAY PREVIEW
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		ray_preview = EButtonGroup::create_invisible_button_group(new ERegionGabarite(32.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);

	ray_preview->is_active = true;
	//ray_preview->disable_gabarite = false;

	whole_filter_block_group->pointer_to_ray_preview_segment = ray_preview;
	workspace_part->add_group(ray_preview);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//		MAIN COLORS EDIT
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButtonGroup*
		cosmetic_segment = EButtonGroup::create_default_button_group(new ERegionGabarite(150.0f, 160.0f), EGUIStyle::active_style)
		->set_parameters(ChildAlignMode::ALIGN_HORIZONTAL, NSW_static_autosize, NSW_dynamic_autosize);

	cosmetic_segment->is_active = true;
	//cosmetic_segment->disable_gabarite = false;

	ELocalisationText ltext[3];

	ltext[0].base_name = "SetBackgroundColor";
	ltext[0].localisations[NSW_localisation_EN] = "Background";
	ltext[0].localisations[NSW_localisation_RU] = "���";

	ltext[1].base_name = "SetTextColor";
	ltext[1].localisations[NSW_localisation_EN] = "Text";
	ltext[1].localisations[NSW_localisation_RU] = "�����";

	ltext[2].base_name = "SetBorderColor";
	ltext[2].localisations[NSW_localisation_EN] = "Border";
	ltext[2].localisations[NSW_localisation_RU] = "�����";

	//root group data container
	whole_filter_block_group->pointer_to_cosmetic_segment = cosmetic_segment;
	workspace_part->add_group(cosmetic_segment);

	//color buttons
	for (int clr = 0; clr < 3; clr++)
	{
		// // // // // // //// // // // // // //// // // // // // //
		//HRA_color_collection* HRA_collection = Helper::registered_color_list[rand() % Helper::registered_color_list.size()];
		HSVRGBAColor* HRA_color = new HSVRGBAColor();
		HRA_color->h = rand() % 360;
		HRA_color->s = 1.0f - pow((rand() % 100) / 100.0f, 1.0);
		HRA_color->v = 1.0f - pow((rand() % 100) / 100.0f, 3.0);
		HRA_color->a = 1.0f - pow((rand() % 100) / 100.0f, 4.0);

		Helper::hsv2rgb(HRA_color);



		EntityButtonColorButton* color_button = EntityButton::create_named_color_button
		(
			new ERegionGabarite(120.0f, 22.0f),
			cosmetic_segment,
			EFont::font_list[0],
			EGUIStyle::active_style,
			ltext[clr],
			nullptr,
			HRA_color,
			ColorButtonMode::CBM_OPEN_WINDOW
		);
		Entity::get_last_text_area(color_button)->localisation_text = ltext[clr];
		color_button->suppressor = &whole_filter_block_group->color_check[clr];

		whole_filter_block_group->pointer_to_HRA_color[clr] = &color_button->stored_color;

		cosmetic_segment->button_list.push_back(color_button);

		bool*
			target_bool = &whole_filter_block_group->color_check[clr];
		whole_filter_block_group->pointer_to_color_button[clr] = color_button;



		//COLOR CHECKER
		jc_button = new EntityButton();
		jc_button->make_default_bool_switcher_button
		(
			new ERegionGabarite(22.0f, 22.0f),
			cosmetic_segment,
			EDataActionCollection::action_switch_boolean_value,
			NS_DefaultGabarites::texture_bool_switcher_activated_box,
			NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
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
		"������"
	);
	jc_button->suppressor = &whole_filter_block_group->text_size_bool;

	last_text_area = Entity::get_last_text_area(jc_button);

	last_text_area->localisation_text.base_name = "SetFontSize";
	last_text_area->localisation_text.localisations[NSW_localisation_EN] = "Size";
	last_text_area->localisation_text.localisations[NSW_localisation_RU] = "������";

	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->pointer_to_value = &whole_filter_block_group->text_size;
	static_cast<EDataContainer_VerticalNamedSlider*>(EntityButton::get_last_custom_data(jc_button)->data_container)->max_value = 1.0f;

	whole_filter_block_group->text_size_button = jc_button;

	jc_button->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_refresh_loot_simulator_sizes);

	cosmetic_segment->button_list.push_back(jc_button);
	// // // // // // //// // // // // // //// // // // // // //


	//font size switcher
	// // // // // // //// // // // // // //// // // // // // //
	bool* target_bool = &whole_filter_block_group->text_size_bool;

	//TEXT SIZE
	jc_button = new EntityButton();
	jc_button->make_default_bool_switcher_button
	(
		new ERegionGabarite(22.0f, 22.0f),
		cosmetic_segment,
		EDataActionCollection::action_switch_boolean_value,
		NS_DefaultGabarites::texture_bool_switcher_activated_box,
		NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
		target_bool
	);
	whole_filter_block_group->text_size_switch_button = jc_button;

	cosmetic_segment->button_list.push_back(jc_button);
	// // // // // // //// // // // // // //// // // // // // //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//		MINIMAP RAY
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
	button_variant_FB_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(125.0f, 22.0f),
		ray_cosmetic_segment,
		&EDataActionCollection::action_rotate_variant,
		nullptr
	);
	button_variant_FB_router->parent_filter_block = whole_filter_block_group;


	button_variant_FB_router->rotate_variant_mode = RotateVariantMode::OPEN_CHOOSE_WINDOW;

	button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

	jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
	button_variant_FB_router->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

	button_variant_FB_router->suppressor = &whole_filter_block_group->ray_suppressor;
	whole_filter_block_group->pointer_to_ray_color_router = button_variant_FB_router;


	//routers
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Red";
	local_text->localisations[NSW_localisation_EN] = "Red";
	local_text->localisations[NSW_localisation_RU] = "�������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.2f, 0.1f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Green";
	local_text->localisations[NSW_localisation_EN] = "Green";
	local_text->localisations[NSW_localisation_RU] = "������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.25f, 1.0f, 0.4f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Blue";
	local_text->localisations[NSW_localisation_EN] = "Blue";
	local_text->localisations[NSW_localisation_RU] = "�����";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.25f, 0.4f, 1.0f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Brown";
	local_text->localisations[NSW_localisation_EN] = "Brown";
	local_text->localisations[NSW_localisation_RU] = "����������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.5f, 0.25f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "White";
	local_text->localisations[NSW_localisation_EN] = "White";
	local_text->localisations[NSW_localisation_RU] = "�����";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 1.0f, 1.0f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Yellow";
	local_text->localisations[NSW_localisation_EN] = "Yellow";
	local_text->localisations[NSW_localisation_RU] = "Ƹ����";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 1.0f, 0.25f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Cyan";
	local_text->localisations[NSW_localisation_EN] = "Cyan";
	local_text->localisations[NSW_localisation_RU] = "�������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.25f, 0.8f, 1.0f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Grey";
	local_text->localisations[NSW_localisation_EN] = "Grey";
	local_text->localisations[NSW_localisation_RU] = "�����";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.55f, 0.55f, 0.55f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Orange";
	local_text->localisations[NSW_localisation_EN] = "Orange";
	local_text->localisations[NSW_localisation_RU] = "���������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.65f, 0.1f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Pink";
	local_text->localisations[NSW_localisation_EN] = "Pink";
	local_text->localisations[NSW_localisation_RU] = "�������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.5f, 1.0f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Purple";
	local_text->localisations[NSW_localisation_EN] = "Purple";
	local_text->localisations[NSW_localisation_RU] = "����������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.8f, 0.1f, 0.9f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	button_variant_FB_router->select_variant(0);


	ray_cosmetic_segment->button_list.push_back(button_variant_FB_router);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//font size switcher
	// // // // // // //// // // // // // //// // // // // // //
	target_bool = &whole_filter_block_group->ray_suppressor;

	//RAY SUPPRESSOR
	jc_button = new EntityButton();
	jc_button->make_default_bool_switcher_button
	(
		new ERegionGabarite(25.0f, 25.0f),
		ray_cosmetic_segment,
		EDataActionCollection::action_switch_boolean_value,
		NS_DefaultGabarites::texture_bool_switcher_activated_box,
		NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
		target_bool
	);
	whole_filter_block_group->text_size_switch_button = jc_button;

	ray_cosmetic_segment->button_list.push_back(jc_button);
	// // // // // // //// // // // // // //// // // // // // //





	//		MINIMAP RAY [temp?]
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();
	button_variant_FB_router->make_as_default_button_with_icon
	(
		new ERegionGabarite(150.0f, 22.0f),
		ray_cosmetic_segment,
		&EDataActionCollection::action_rotate_variant,
		nullptr
	);
	button_variant_FB_router->parent_filter_block = whole_filter_block_group;


	button_variant_FB_router->rotate_variant_mode = RotateVariantMode::SELECT_NEXT;

	button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

	jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
	button_variant_FB_router->pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);

	button_variant_FB_router->suppressor = &whole_filter_block_group->ray_suppressor;
	whole_filter_block_group->pointer_to_temporary_option_router = button_variant_FB_router;


	//routers
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Constant";
	local_text->localisations[NSW_localisation_EN] = "Constant";
	local_text->localisations[NSW_localisation_RU] = "����������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	router_variant = new RouterVariant();
	local_text = new ELocalisationText();

	local_text->base_name = "Temp";
	local_text->localisations[NSW_localisation_EN] = "Temporary";
	local_text->localisations[NSW_localisation_RU] = "���������";
	router_variant->localisation = local_text;

	router_variant->color = new HSVRGBAColor();
	router_variant->color->set_color_RGBA(0.6f, 0.6f, 0.6f, 1.0f);

	button_variant_FB_router->router_variant_list.push_back(router_variant);
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

	button_variant_FB_router->select_variant(0);


	ray_cosmetic_segment->button_list.push_back(button_variant_FB_router);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//EInputCore::logger_param("size of subgroups", workspace_part->group_list.size());
	return whole_filter_block_group;
}

EButtonGroupFilterBlockSeparator* EWindowMain::create_filter_block_separator(EButtonGroup* _target_editor, int _specific_position)
{
	EButtonGroupFilterBlockSeparator* whole_separator_block = new EButtonGroupFilterBlockSeparator(new ERegionGabarite(1200.0f, 20.0f));
	whole_separator_block->init_button_group(EGUIStyle::active_style, false, false, false);
	whole_separator_block->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_static_autosize);
	whole_separator_block->debug_name = "Whole separator";
	whole_separator_block->focusable_for_select = true;
	whole_separator_block->additional_y_distance = 8.0f;

	//		SHRINKER
	/////////////////////////////////////////////////////////////////////////////////////////////
	EntityButton* shrinker_button = new EntityButton();
	shrinker_button->make_default_bool_switcher_button
	(
		new ERegionGabarite(20.0f, 20.0f),
		whole_separator_block,
		EDataActionCollection::action_switch_boolean_value,
		NS_DefaultGabarites::texture_bool_switcher_activated_box,
		NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
		&whole_separator_block->is_expanded
	);
	whole_separator_block->is_expanded = true;
	shrinker_button->main_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_change_separator_shrink_flag);

	whole_separator_block->button_list.push_back(shrinker_button);
	/////////////////////////////////////////////////////////////////////////////////////////////

	//		MOVE
	/////////////////////////////////////////////////////////////////////////////////////////////
	EntityButtonMoveButtonGroup*
		move_button = new EntityButtonMoveButtonGroup();
	move_button->make_as_default_button_with_full_icon
	(
		new ERegionGabarite(40.0f, 15.0f),
		whole_separator_block,
		&EDataActionCollection::action_move_button_group,
		NS_DefaultGabarites::texture_button_move
	);
	move_button->target_group_for_moving = whole_separator_block;
	move_button->parent_group_for_moving = _target_editor;
	move_button->move_method = MoveVectorMethod::METHOD_DRAG;

	whole_separator_block->button_list.push_back(move_button);
	/////////////////////////////////////////////////////////////////////////////////////////////

	//		DESCRIPTION
	/////////////////////////////////////////////////////////////////////////////////////////////
	EntityButton*
		description_button = new EntityButton();
	description_button->make_default_button_with_edible_text
	(
		new ERegionGabarite(256.0f, 20.0f),
		whole_separator_block,
		nullptr,
		""
	);
	ELocalisationText ltext;
	ltext.localisations[NSW_localisation_EN] = "Type commentary";
	ltext.localisations[NSW_localisation_RU] = "�������� �����������";

	description_button->main_text_area->gray_text = ltext;
	//move_button->parent_group_for_moving = _target_whole_group;

	whole_separator_block->button_list.push_back(description_button);

	whole_separator_block->pointer_to_description_button = description_button;
	/////////////////////////////////////////////////////////////////////////////////////////////


	if (_specific_position < 0)
	{
		_target_editor->add_group(whole_separator_block);
	}
	else
	{
		_target_editor->add_group_scecific_position(whole_separator_block, _specific_position);
	}

	return whole_separator_block;
}

void EWindowMain::parse_filter_text_lines(EButtonGroupFilterBlock* _target_filter_block, LootFlterOpenMode _parse_mode)
{
	std::string buffer_text = "";

	bool space_is_not_separator = false;
	bool comment_mode = false;

	int data_part = 0;
	int value_array_id = 0;
	int matched_id_for_color_button = -1;

	//bool comment_mode = false;

	EntityButton* matched_button = nullptr;

	EButtonGroupFilterBlock* jc_filter_block = nullptr;
	EButtonGroupFilterBlockSeparator* jc_filter_block_separator = nullptr;

	std::string attribute_text = "";
	std::string condition_text = "";
	//std::string value_array[512] = {};

	HSVRGBAColor* target_HRA_color;
	bool* target_color_bool;

	GameItemAttribute* matched_filter_block_attribute = nullptr;

	EButtonGroupNonListedLine* last_non_listed_line = nullptr;
	EntityButtonFilterSound* last_custom_sound_button = nullptr;

	for (std::string str_line : filter_text_lines)
	{
		//comment_mode = false;
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

		last_non_listed_line = nullptr;

		EButtonGroupFilterBlock* whole_block_container = nullptr;
		EDataContainer_Group_FilterBlockListedSegment* listed_container = nullptr;

		target_color_bool = nullptr;

		for (int i = 0; i < str_line.length(); i++)
		{
			char current_sym = str_line.at(i);

			if (current_sym == '"') { space_is_not_separator = !space_is_not_separator; }
			if (current_sym == '#') { comment_mode = true; }

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
					(current_sym != '#')
					&&
					(i + 1 < str_line.length())
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
						(current_sym != '#')
						&&
						(i + 1 >= str_line.length())
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
					if (data_part == DataOrderNames::ATTRIBUTE)
					{
						//EInputCore::logger_param("buffer text", buffer_text);

						if
							(
								(
									(EStringUtils::compare_ignoring_case(buffer_text, "show"))
									||
									(EStringUtils::compare_ignoring_case(buffer_text, "hide"))
									)
								&&
								(!comment_mode)
								)
						{
							int specific_position = -1;

							if (_target_filter_block != nullptr)
							{
								for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
								{
									if (EWindowMain::loot_filter_editor->group_list[i] == _target_filter_block)
									{
										specific_position = i;
									}
								}
							}
							//if (_target_filter_block == nullptr)
							{
								jc_filter_block = create_filter_block(loot_filter_editor, specific_position);

								if (_parse_mode == LootFlterOpenMode::LOOT_FILTER_OPEN_MODE_DEFAULT_FILTER_FROM_GAME) { jc_filter_block->suppressed = true; }
							}
							//else
							//{
							//	jc_filter_block = _target_filter_block;
							//	_target_filter_block = nullptr;
							//}

							whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

							if (EStringUtils::compare_ignoring_case(buffer_text, "show"))
							{
								((EntityButtonVariantRouter*)(whole_block_container->button_show_hide))->select_variant(1);
							}
							else
							{
								((EntityButtonVariantRouter*)(whole_block_container->button_show_hide))->select_variant(0);
							}


							if (_target_filter_block != nullptr)
							{

								//*_target_filter_block = *jc_filter_block;

								//delete jc_filter_block;

								//jc_filter_block = _target_filter_block;
							}


						}
						else
						{
							matched_filter_block_attribute = nullptr;

							for (int b = 0; b < registered_game_item_attributes.size(); b++)
							{
								GameItemAttribute* attribute = registered_game_item_attributes[b];

								if (EStringUtils::compare_ignoring_case(buffer_text, attribute->localisation.base_name))
								{
									matched_filter_block_attribute = attribute;
								}
							}

							if
								(
									(matched_filter_block_attribute != nullptr)
									&&
									(
										(!comment_mode)
										||
										(matched_filter_block_attribute->always_present)
										||
										(matched_filter_block_attribute->commentary_config)
										)
									)
							{
								//add new sections to filter block
								if
									(
										(!matched_filter_block_attribute->always_present)
										&&
										(!matched_filter_block_attribute->commentary_config)
										)
								{
									add_filter_block_content_to_filter_block(jc_filter_block, matched_filter_block_attribute);
								}

								whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

								//EInputCore::logger_param("found registered attribure", buffer_text);

								////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED)
								{
									if (!jc_filter_block->pointer_to_non_listed_segment->group_list.empty())
									{
										last_non_listed_line = static_cast<EButtonGroupNonListedLine*>(jc_filter_block->pointer_to_non_listed_segment->group_list.back());
									}
								}
								////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)
								{
									for (int b = 0; b < 3; b++)
									{
										if (Entity::get_last_text_area(whole_block_container->pointer_to_color_button[b])->localisation_text.base_name == matched_filter_block_attribute->localisation.base_name)
										{
											//matched_button = whole_block_container->pointer_to_color_button[b];
											target_HRA_color = whole_block_container->pointer_to_color_button[b]->stored_color;
											target_color_bool = &whole_block_container->color_check[b];
										}
									}

									if ((matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_MINIMAP_ICON) && (!comment_mode))
									{
										whole_block_container->minimap_icon_color_suppressor_bool = true;
									}

									if ((matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_USER_SOUND) && (!comment_mode))
									{
										last_custom_sound_button = jc_filter_block->pointer_to_custom_sound_button;
										//EInputCore::logger_simple_info("user_sound");
									}


									//		ATTRIBUTES WITHOUT PARAMETERS
									if (!comment_mode)
									{
										//disable/enable varian router button
										int disable_sound_router_id = -1;
										disable_sound_router_id = whole_block_container->pointer_to_disable_enable_drop_sound->seach_id_by_base_name(matched_filter_block_attribute->localisation.base_name);
										if (disable_sound_router_id >= 0) { whole_block_container->pointer_to_disable_enable_drop_sound->select_variant(disable_sound_router_id); }

										if (matched_filter_block_attribute->localisation.base_name == "PlayAlertSoundPositional")
										{
											whole_block_container->pointer_to_positional_variant_button->select_variant(1);
										}
										else
											if (matched_filter_block_attribute->localisation.base_name == "PlayAlertSound")
											{
												whole_block_container->pointer_to_positional_variant_button->select_variant(0);
											}
											else
												if (matched_filter_block_attribute->localisation.base_name == "CustomAlertSoundOptional")
												{
													whole_block_container->pointer_to_optional_user_sound->select_variant(1);
												}
									}

									if ((matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_RAY) && (!comment_mode))
									{
										whole_block_container->ray_suppressor = true;
									}

									if ((matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_CONTINUE) && (!comment_mode))
									{
										whole_block_container->button_continue->select_variant(0);
									}
									//target_HRA_color = ((EDataContainer_Button_StoreColor*)(Entity::get_last_custom_data(whole_block_container->pointer_to_color_button[0])->data_container))->stored_color;
									//target_color_bool = &whole_block_container->color_check[0];
								}
								////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_CONFIG)
								{
									if (matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_CONFIG_SEPARATOR)
									{
										int specific_position = -1;

										if (_target_filter_block != nullptr)
										{
											for (int i = 0; i < EWindowMain::loot_filter_editor->group_list.size(); i++)
											{
												if (EWindowMain::loot_filter_editor->group_list[i] == _target_filter_block)
												{
													specific_position = i;
												}
											}
										}

										jc_filter_block_separator = create_filter_block_separator(loot_filter_editor, specific_position);
									}
								}
								////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								//if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)
								//{

								//}
							}
							else
							{
								if (!comment_mode) { EInputCore::logger_param_with_warning("UNREGISTERED attribure!", buffer_text); }
							}
						}
					}

					//condition operator
					if (data_part == DataOrderNames::CONDITION_OPERATOR)
					{
						if (!comment_mode)
						{
							if ((matched_filter_block_attribute != nullptr) && (matched_filter_block_attribute->filter_attribute_type == FILTER_ATTRIBUTE_TYPE_LISTED))
							{
								whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

								listed_container = (EDataContainer_Group_FilterBlockListedSegment*)(whole_block_container->pointer_to_listed_segment->group_list.back()->data_container);

								//EXACT MATCH
								if (buffer_text == "==")
								{
									listed_container->match_mode_router_button->select_variant(1);
								}



							}



							if (text_is_condition(buffer_text))
							{
								condition_text = buffer_text;

								if ((last_non_listed_line != nullptr) && (last_non_listed_line->target_button_with_condition != nullptr))
								{
									last_non_listed_line->target_button_with_condition->main_text_area->change_text(condition_text);
								}
							}
							else
							{
								condition_text = "";
								data_part = DataOrderNames::VALUE;

								if
									(
										(last_non_listed_line != nullptr)
										&&
										(last_non_listed_line->target_button_with_condition != nullptr)
										&&
										(matched_filter_block_attribute != nullptr)
										&&
										(matched_filter_block_attribute->have_operator)
										)
								{
									Entity::get_last_text_area(last_non_listed_line->target_button_with_condition)->change_text("=");
								}
							}

							//CONDITION OPERATOR FOR EXPLICIT
							std::string f_sym = std::string(buffer_text.substr(0, 1));
							//EInputCore::logger_param("buffer_text", buffer_text);
							//EInputCore::logger_param("f_sym", f_sym);


							if ((matched_filter_block_attribute != nullptr) && (matched_filter_block_attribute->have_input_field_for_listed) && (text_is_condition(f_sym)))
							{
								listed_container->input_field->main_text_area->change_text(buffer_text);
								data_part = DataOrderNames::CONDITION_OPERATOR;
							}

						}
						else
						{
							data_part = DataOrderNames::VALUE;
						}
					}

					//values
					if (data_part >= DataOrderNames::VALUE)
					{
						//EInputCore::logger_param("value", buffer_text);
						//value_array[value_array_id] = buffer_text;

						//value_array_id++;

						if (matched_filter_block_attribute != nullptr)
						{


							if ((matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED) && (!comment_mode))
							{
								if
									(
										(last_non_listed_line != nullptr)
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
											(Entity::get_last_text_area(last_non_listed_line->target_button_with_value) != nullptr)
											)
									{
										Entity::get_last_text_area(last_non_listed_line->target_button_with_value)->change_text(buffer_text);
									}

									if
										(matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER)
									{
										if (EStringUtils::to_lower(buffer_text) == "true")
										{
											*static_cast <EDataContainer_Button_BoolSwitcher*>(last_non_listed_line->target_button_with_value->custom_data_list.back()->data_container)->target_value = true;
										}
										else
										{
											*static_cast <EDataContainer_Button_BoolSwitcher*>(last_non_listed_line->target_button_with_value->custom_data_list.back()->data_container)->target_value = false;
										}

									}

									if
										(matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST)
									{
										/*for (RouterVariant* rv : registered_rarity_router_variants)
										{
											if (EStringUtils::compare_ignoring_case(rv->localisation->base_name, buffer_text))
											{
												EntityButton::get_last_text_area(last_non_listed_container->target_button_with_value)->localisation_text = *rv->localisation;

												EntityButton::get_last_text_area(last_non_listed_container->target_button_with_value)->stored_color = *rv->color;
												EntityButton::get_last_text_area(last_non_listed_container->target_button_with_value)->color = *rv->color;

												EntityButton::get_last_text_area(last_non_listed_container->target_button_with_value)->change_text(rv->localisation->localisations[NSW_localisation_EN]);


											}
										}*/

										last_non_listed_line->rarity_router_button->select_variant_by_base_name(buffer_text);
									}

									if
										(matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST)
									{
										for (RouterVariant* qv : registered_alternate_gem_quality_router_variants)
										{
											if (EStringUtils::compare_ignoring_case(qv->localisation->base_name, buffer_text))
											{
												EntityButton::get_last_text_area(last_non_listed_line->target_button_with_value)->localisation_text = *qv->localisation;

												EntityButton::get_last_text_area(last_non_listed_line->target_button_with_value)->stored_color = *qv->color;
												EntityButton::get_last_text_area(last_non_listed_line->target_button_with_value)->color = *qv->color;

												EntityButton::get_last_text_area(last_non_listed_line->target_button_with_value)->change_text(qv->localisation->localisations[ELocalisationText::active_localisation]);
											}
										}
									}
								}
							}

							if ((matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED) && (!comment_mode))
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
									index = min(index, 15);
									index = max(index, 0);

									//arr[index]++;
									if (named_struct->name == data_type_text) { target_data_entity_list = &named_struct->data_entity_list[index]; break; }
								}

								int xxx = 0;
								EDataEntity* matched_data_entity = nullptr;

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
										matched_data_entity = de;


										//EButtonGroup::change_group(((EDataContainer_Group_FilterBlockListedSegment*)d_container)->group_with_listed_buttons);
									}

									xxx++;
								}

								if (matched_data_entity != nullptr)
								{
									EntityButton* wide_button = EntityButton::create_wide_item_button
									(
										new ERegionGabarite(220.0f, 40.0f),
										((EDataContainer_Group_FilterBlockListedSegment*)listed_container)->group_with_listed_buttons,
										matched_data_entity,
										EFont::font_list[0]
									);

									((EDataContainer_Group_FilterBlockListedSegment*)listed_container)->group_with_listed_buttons->button_list.push_back(wide_button);

								}
								else
								{
									EntityButton* wide_button = EntityButton::create_wide_item_button
									(
										new ERegionGabarite(220.0f, 40.0f),
										((EDataContainer_Group_FilterBlockListedSegment*)listed_container)->group_with_listed_buttons,
										nullptr,
										EFont::font_list[0]
									);

									((EDataContainer_Group_FilterBlockListedSegment*)listed_container)->group_with_listed_buttons->button_list.push_back(wide_button);

									ELocalisationText l_text;
									l_text.base_name = buffer_text;
									l_text.localisations[NSW_localisation_EN] = buffer_text;
									l_text.localisations[NSW_localisation_RU] = buffer_text;

									Entity::get_last_text_area(wide_button)->localisation_text = l_text;
									Entity::get_last_text_area(wide_button)->change_text(l_text.localisations[ELocalisationText::active_localisation]);

								}
							}

							if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)
							{
								whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

								//EInputCore::logger_simple_info("Cosmetic");

								//		FONT SIZE
								//EInputCore::logger_param("buffer text is", buffer_text);
								if (matched_filter_block_attribute->localisation.base_name == "SetFontSize")
								{

									whole_block_container->text_size = (std::stoi(buffer_text) - 18) / 27.0f;

									whole_block_container->text_size = max(whole_block_container->text_size, 0.0f);
									whole_block_container->text_size = min(whole_block_container->text_size, 1.0f);

									whole_block_container->text_size_bool = true;
									//d_container->
								}

								//		BOX COLOR
								if (target_HRA_color != nullptr)
								{
									if (data_part == 2) { target_HRA_color->r = std::stoi(buffer_text) / 255.0f; }
									if (data_part == 3) { target_HRA_color->g = std::stoi(buffer_text) / 255.0f; }
									if (data_part == 4)
									{
										target_HRA_color->b = std::stoi(buffer_text) / 255.0f;

										Helper::rgb2hsv(target_HRA_color);
										if (!comment_mode) { *target_color_bool = true; }
									}
									if (data_part == 5)
									{
										target_HRA_color->a = std::stoi(buffer_text) / 255.0f;


									}
								}

								//		MINIMAP ICON
								if (matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_MINIMAP_ICON)
								{
									EntityButtonVariantRouter* router_button_size = whole_block_container->pointer_to_minimap_icon_size_router;
									EntityButtonVariantRouter* router_button_color = whole_block_container->pointer_to_minimap_icon_color_router;
									EntityButtonVariantRouter* router_button_shape = whole_block_container->pointer_to_minimap_icon_shape_router;

									//SIZE
									if (data_part == 2)
									{
										router_button_size->select_variant(router_button_size->seach_id_by_base_name(buffer_text));
									}

									//COLOR
									if (data_part == 3)
									{
										router_button_color->select_variant(router_button_color->seach_id_by_base_name(buffer_text));
									}

									//SHAPE
									if (data_part == 4)
									{
										router_button_shape->select_variant(router_button_shape->seach_id_by_base_name(buffer_text));
									}
								}

								//		USER SOUND
								if (matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_USER_SOUND)
								{
									//parameter order - name
									if (data_part == 2)
									{
										ENamedSound* matched_named_sound = nullptr;

										for (ENamedSound* named_sound : EWindowMain::custom_sound_list)
											if (named_sound->localisation_text.base_name == buffer_text)
											{
												//EInputCore::logger_param("matched sound", named_sound->localisation_text.base_name);

												matched_named_sound = named_sound;
											}

										if (matched_named_sound == nullptr)
										{
											//EInputCore::logger_param_with_warning("undefined sound", buffer_text);
										}

										whole_block_container->pointer_to_custom_sound_button->stored_named_sound = matched_named_sound;
										if (!comment_mode) { whole_block_container->custom_sound_suppressor_bool = true; }
									}
								}


								//		INGAME SOUND
								if (matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_INGAME_SOUND)
								{
									if (data_part == 2)
									{
										ENamedSound* matched_named_sound = nullptr;

										for (ENamedSound* named_sound : EWindowMain::default_sound_list)
											if (named_sound->localisation_text.base_name == buffer_text)
											{
												//EInputCore::logger_param("matched sound", named_sound->localisation_text.base_name);

												matched_named_sound = named_sound;
											}

										if (matched_named_sound == nullptr)
										{
											//EInputCore::logger_param_with_warning("undefined sound", buffer_text);
										}


										whole_block_container->pointer_to_game_sound_button->stored_named_sound = matched_named_sound;
										if (!comment_mode) { whole_block_container->game_sound_suppressor_bool = true; }

									}
									else
										if (data_part == 3)
										{
											float
												value = std::stoi(buffer_text) / 300.0f;
											value = max(value, 0.0f);
											value = min(value, 1.0f);

											whole_block_container->sound_volume_value = value;
										}


								}

								//		RAY
								if ((matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_RAY) && (!comment_mode))
								{
									EntityButtonVariantRouter* ray_router = whole_block_container->pointer_to_ray_color_router;

									if (data_part == 2)
									{
										ray_router->select_variant(ray_router->seach_id_by_base_name(buffer_text));
									}

									if ((data_part == 3) && (buffer_text == "Temp"))
									{
										whole_block_container->pointer_to_temporary_option_router->select_variant(1);
									}
								}







							}

							if (matched_filter_block_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_CONFIG)
							{
								whole_block_container = (EButtonGroupFilterBlock*)(jc_filter_block);

								if (matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_CONFIG_VERSIONS)
								{
									int
										router_id = data_part - 2;

									EntityButtonVariantRouterForFilterBlock*
										target_router = whole_block_container->version_routers[router_id];

									//EInputCore::logger_param("buffer text", buffer_text);
									//EInputCore::logger_param("router ID", router_id);
									//EInputCore::logger_param("searched id", target_router->seach_id_by_base_name(buffer_text));
									target_router->select_variant(target_router->seach_id_by_base_name(buffer_text));
								}
								else
									if (matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_OLD_VERSION_AUTOGEN)
									{
										int
											router_id = data_part - 2;

										EntityButtonVariantRouterForFilterBlock*
											target_router = whole_block_container->version_routers[router_id];

										if (buffer_text == "true") { target_router->select_variant(3); }
										else
											if (buffer_text == "false") { target_router->select_variant(1); }
									}
									else
										if ((matched_filter_block_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_CONFIG_SEPARATOR) && (jc_filter_block_separator != nullptr))
										{
											if (data_part == 2)
											{
												if (buffer_text == "*EMPTY*")
												{
													jc_filter_block_separator->pointer_to_description_button->main_text_area->change_text("");
												}
												else
												{
													jc_filter_block_separator->pointer_to_description_button->main_text_area->change_text(buffer_text);
												}


											}
											if ((data_part == 3) && (buffer_text == "shrinked"))
											{
												jc_filter_block_separator->is_expanded = false;
												//jc_filter_block->is_expanded = false;
											}
										}


							}
							//FILTER_ATTRIBUTE_VALUE_CONFIG_VERSIONS
						}
					}

					//value_array[data_part] = buffer_text;

					buffer_text = "";
					data_part++;
				}
			}

		}
	}
}

bool EWindowMain::filter_block_contains_this_text(EButtonGroupFilterBlock* _target_filter_block, std::string* _text)
{
	bool any_match = false;
	bool listed_match = false;

	if (*_text != "")
	{

		//if (_target_filter_block->pointer_to_listed_segment->group_list.empty()) { any_match = true; }
		for (EButtonGroup* listed_block : _target_filter_block->pointer_to_listed_segment->group_list)
		{
			//listed_match = false;

			auto listed_container = (EDataContainer_Group_FilterBlockListedSegment*)(listed_block->data_container);

			//if
			//(
			//	(listed_container->group_with_listed_buttons->button_list.empty())
			//	||
			//	(listed_container->group_with_listed_buttons->button_list.back() == listed_container->group_with_listed_buttons->slider)

			//)
			//{
			//	any_match = true;
			//}

			for (EntityButton* wide_button : listed_container->group_with_listed_buttons->button_list)
				if
					(
						(wide_button != _target_filter_block->slider)
						&&
						(wide_button->main_text_area != nullptr)
						)
				{
					if
						(
							(EStringUtils::A_contains_B_ignore_case(wide_button->main_text_area->localisation_text.base_name, *_text))
							||
							(EStringUtils::A_contains_B_ignore_case(wide_button->main_text_area->localisation_text.localisations[NSW_localisation_EN], *_text))
							||
							(EStringUtils::A_contains_B_ignore_case(wide_button->main_text_area->localisation_text.localisations[NSW_localisation_RU], *_text))
							)
					{
						any_match = true;
						break;
					}
				}

		}
	}
	else
	{
		any_match = true;
	}

	return any_match;
}

void EWindowMain::write_loot_filter_to_disc(std::string _full_path, std::string* _data)
{
	if
		(
			(EWindowMain::tab_list_group != nullptr)
			&&
			(EWindowMain::tab_list_group->selected_button != nullptr)
			&&
			(EWindowMain::tab_list_group->selected_button->main_text_area != nullptr)
			)
	{
		std::ofstream writabro;

		writabro.open(_full_path);
		writabro << *_data;
		writabro.close();
	}
	else
	{
		EInputCore::logger_simple_error("something wrong, cannot get loot-filter name!");
	}
}

void EWindowMain::register_loot_simulator_patterns()
{




	register_pattern_all_currencies();
	register_pattern_basic_currencies();
	register_pattern_trash_currencies();
	register_pattern_good_currencies();
	register_pattern_rare_currencies();
	register_pattern_tainted_currencies();
	register_pattern_currencies_shard();
	register_pattern_oils_and_catalysts();

	register_pattern_top_tier_bases();
	register_pattern_all_equip_low_level();
	register_pattern_all_equip_high_level();

	register_pattern_delve_items();
	register_pattern_breach_items();

	register_pattern_maps();
	register_pattern_all_map_fragments();
	register_pattern_scarabs();
	register_pattern_set_fragment();

	register_pattern_flasks();

	register_pattern_divinations_trash();
	register_pattern_divinations_cheap();
	register_pattern_divinations_useful();
	register_pattern_divinations_expensive();

	register_pattern_boss_loot();

}

void EWindowMain::register_pattern_boss_loot()
{
	//		BOSS ITEMS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Boss loot";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��� � ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_pinnacle_boss_loot");


		/////////////////////////////			ITEM GENERATOR(UNIQUE BOSS LOOT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Pinnacle boss loot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Piece of set");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 80;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");

				//		parameters
				value_generator->min_value = 3;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR(MAP FRAGMENTS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Pinnacle boss loot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Piece of set");
			tag_filter->suitable_values.push_back("Atlas Region Upgrade Item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

		}



		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_divinations_expensive()
{
	//		DIVINATIONS: Expensive
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Divinations: expensive";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��������� �����: �������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/card");

		/////////////////////////////			ITEM GENERATOR (MAP WITHOUT INFLUENCE)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Divination Card");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Expensive");
			tag_filter->suitable_values.push_back("Very expensive");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}








		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_divinations_useful()
{
	//		DIVINATIONS: Useful
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Divinations: moderate";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��������� �����: ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/card");

		/////////////////////////////			ITEM GENERATOR (MAP WITHOUT INFLUENCE)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Divination Card");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Moderate");
			tag_filter->suitable_values.push_back("Rare");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}








		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_divinations_cheap()
{
	//		DIVINATIONS: CHEAP
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Divinations: common";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��������� �����: �������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/card");

		/////////////////////////////			ITEM GENERATOR (MAP WITHOUT INFLUENCE)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Divination Card");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Common");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}








		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_divinations_trash()
{
	//		DIVINATIONS: TRASH
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Divinations: trash";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��������� �����: �����";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/card");

		/////////////////////////////			ITEM GENERATOR (MAP WITHOUT INFLUENCE)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Divination Card");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Trash");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);


		}








		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_flasks()
{
	//		FLASKS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Flasks";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "�������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/Hybrid_flask");


		/////////////////////////////			ITEM GENERATOR(NON UNIQUE FLASKS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 4;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Utility Flasks");
			tag_filter->suitable_values.push_back("Life Flasks");
			tag_filter->suitable_values.push_back("Hybrid Flasks");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");

				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 1;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARQUALITYITY			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Quality");

				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 30;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR(UNIQUE FLASKS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Utility Flasks");
			tag_filter->suitable_values.push_back("Life Flasks");
			tag_filter->suitable_values.push_back("Hybrid Flasks");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");

				//		parameters
				value_generator->min_value = 3;
				value_generator->max_value = 3;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			QUALITY			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Quality");

				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 30;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_set_fragment()
{
	//		SET FRAGMENTS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Set fragment";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "�������� ��������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/UberElderSet");


		/////////////////////////////			ITEM GENERATOR			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Piece of set");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_scarabs()
{
	//		SCARABS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Scarabs";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/Scarab");


		/////////////////////////////			ITEM GENERATOR			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Scarab item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_all_map_fragments()
{
	//		ALL MAP FRAGMENTS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "All map fragments";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��� ��������� ����";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/Fragment_of_Knowledge");


		/////////////////////////////			ITEM GENERATOR			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Map Fragments");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_maps()
{
	//		MAPS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Maps";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "�����";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_maps");

		/////////////////////////////			ITEM GENERATOR (MAP WITHOUT INFLUENCE)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 16;

			ELocalisationText l_text;
			l_text.base_name = "Random Map";
			l_text.localisations[NSW_localisation_EN] = "Random Map";
			l_text.localisations[NSW_localisation_RU] = "��������� �����";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Maps";
				l_text.localisations[NSW_localisation_EN] = "Maps";
				l_text.localisations[NSW_localisation_RU] = "�����";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 0.8f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			MAP TIER			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("MapTier");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 16;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}


			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (MAP WITH INFLUENCE)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 16;
			ELocalisationText l_text;
			l_text.base_name = "Guard map";
			l_text.localisations[NSW_localisation_EN] = "Guard map";
			l_text.localisations[NSW_localisation_RU] = "����� ���������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Maps";
				l_text.localisations[NSW_localisation_EN] = "Maps";
				l_text.localisations[NSW_localisation_RU] = "�����";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 1.5f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			MAP TIER			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("MapTier");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 16;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorMapInfluence*
					value_generator = new GameAttributeGeneratorMapInfluence("HasInfluence");

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (FRACTURED MAPS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 8;
			ELocalisationText l_text;
			l_text.base_name = "Fractured Map";
			l_text.localisations[NSW_localisation_EN] = "Fractured Map";
			l_text.localisations[NSW_localisation_RU] = "���������� �����";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Maps";
				l_text.localisations[NSW_localisation_EN] = "Maps";
				l_text.localisations[NSW_localisation_RU] = "�����";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 1.5f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			MAP TIER			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("MapTier");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 16;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			FRACTURED			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorBoolFlag*
					value_generator = new GameAttributeGeneratorBoolFlag("FracturedItem");

				//		parameters
				value_generator->chance_to_activate = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (CORRUPTED MAPS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 8;

			ELocalisationText l_text;
			l_text.base_name = "Corrupted Map";
			l_text.localisations[NSW_localisation_EN] = "Corrupted Map";
			l_text.localisations[NSW_localisation_RU] = "������������ �����";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Maps";
				l_text.localisations[NSW_localisation_EN] = "Maps";
				l_text.localisations[NSW_localisation_RU] = "�����";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 1.5f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			MAP TIER			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("MapTier");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 16;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			FRACTURED			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorBoolFlag*
					value_generator = new GameAttributeGeneratorBoolFlag("Corrupted");

				//		parameters
				value_generator->chance_to_activate = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (ENCHANTED MAPS)			/////////////////////////////////////////////

		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 8;

			ELocalisationText l_text;
			l_text.base_name = "Enchanted Map";
			l_text.localisations[NSW_localisation_EN] = "Enchanted Map";
			l_text.localisations[NSW_localisation_RU] = "������������ �����";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Maps";
				l_text.localisations[NSW_localisation_EN] = "Maps";
				l_text.localisations[NSW_localisation_RU] = "�����";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 1.5f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			MAP TIER			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("MapTier");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 16;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			FRACTURED			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorBoolFlag*
					value_generator = new GameAttributeGeneratorBoolFlag("AnyEnchantment");

				//		parameters
				value_generator->chance_to_activate = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (SYNTHESISED MAPS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 3;

			ELocalisationText l_text;
			l_text.base_name = "Synthesised Map";
			l_text.localisations[NSW_localisation_EN] = "Synthesised Map";
			l_text.localisations[NSW_localisation_RU] = "��������������� �����";
			game_item_generator->filtered_by_exact_name = l_text;


			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 3;
				value_generator->max_value = 3;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			MAP TIER			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("MapTier");


				//		parameters
				value_generator->min_value = 14;
				value_generator->max_value = 16;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			CORRUPTED			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorBoolFlag*
					value_generator = new GameAttributeGeneratorBoolFlag("Corrupted");

				//		parameters
				value_generator->chance_to_activate = 0.4f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_delve_items()
{
	//		DELVE ITEMS
	{
		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Delve items";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "�������� �����";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_delve_items");

		/////////////////////////////			ITEM GENERATOR (DELVE ITEM)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Delve item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);
		}


		/////////////////////////////			ITEM GENERATOR (BODY ARMOUR WITH SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;
			ELocalisationText l_text;
			l_text.base_name = "Delve body armour";
			l_text.localisations[NSW_localisation_EN] = "Delve body armour";
			l_text.localisations[NSW_localisation_RU] = "��������� ������ ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Body armour";
				l_text.localisations[NSW_localisation_EN] = "Body armour";
				l_text.localisations[NSW_localisation_RU] = "��������� ������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (GLOVE WITH SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;
			ELocalisationText l_text;
			l_text.base_name = "Delve gloves";
			l_text.localisations[NSW_localisation_EN] = "Delve gloves";
			l_text.localisations[NSW_localisation_RU] = "�������� ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Gloves";
				l_text.localisations[NSW_localisation_EN] = "Gloves";
				l_text.localisations[NSW_localisation_RU] = "��������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (HELMET WITH SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			ELocalisationText l_text;
			l_text.base_name = "Delve helmet";
			l_text.localisations[NSW_localisation_EN] = "Delve helmet";
			l_text.localisations[NSW_localisation_RU] = "���� ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Helmets";
				l_text.localisations[NSW_localisation_EN] = "Helmets";
				l_text.localisations[NSW_localisation_RU] = "�����";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (BOOTS WITH SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			ELocalisationText l_text;
			l_text.base_name = "Delve boots";
			l_text.localisations[NSW_localisation_EN] = "Delve boots";
			l_text.localisations[NSW_localisation_RU] = "������ ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Boots";
				l_text.localisations[NSW_localisation_EN] = "Boots";
				l_text.localisations[NSW_localisation_RU] = "������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}


		/////////////////////////////			ITEM GENERATOR (RING WITH SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			ELocalisationText l_text;
			l_text.base_name = "Delve ring";
			l_text.localisations[NSW_localisation_EN] = "Delve ring";
			l_text.localisations[NSW_localisation_RU] = "������ ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Rings";
				l_text.localisations[NSW_localisation_EN] = "Rings";
				l_text.localisations[NSW_localisation_RU] = "������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (BELTS WITH SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			ELocalisationText l_text;
			l_text.base_name = "Delve belt";
			l_text.localisations[NSW_localisation_EN] = "Delve belt";
			l_text.localisations[NSW_localisation_RU] = "���� ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Belts";
				l_text.localisations[NSW_localisation_EN] = "Belts";
				l_text.localisations[NSW_localisation_RU] = "�����";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (AMULETS WITH SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;
			ELocalisationText l_text;
			l_text.base_name = "Delve amulet";
			l_text.localisations[NSW_localisation_EN] = "Delve amulet";
			l_text.localisations[NSW_localisation_RU] = "������ ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			CLASS			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("Class");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Amulets";
				l_text.localisations[NSW_localisation_EN] = "Amulets";
				l_text.localisations[NSW_localisation_RU] = "�������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}

		/////////////////////////////			ITEM GENERATOR (SPECIAL EXPLICIT)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();

			game_item_generator->generations_count = 1;

			ELocalisationText l_text;
			l_text.base_name = "Delve item";
			l_text.localisations[NSW_localisation_EN] = "Delve item";
			l_text.localisations[NSW_localisation_RU] = "������� ������";
			game_item_generator->filtered_by_exact_name = l_text;

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 2;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			EXPLICIT			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorExactListedValue*
					value_generator = new GameAttributeGeneratorExactListedValue("HasExplicitMod");


				//		parameters
				ELocalisationText l_text;
				l_text.base_name = "Subterranean";
				l_text.localisations[NSW_localisation_EN] = "Subterranean";
				l_text.localisations[NSW_localisation_RU] = "����������";
				value_generator->exact_values_list.push_back(l_text);

				l_text.base_name = "of the Underground";
				l_text.localisations[NSW_localisation_EN] = "of the Underground";
				l_text.localisations[NSW_localisation_RU] = "���������";
				value_generator->exact_values_list.push_back(l_text);

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}



			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);
		}





		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_breach_items()
{
	//		BOSS ITEMS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Breach loot";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��� � ��������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_breach_items");


		/////////////////////////////			ITEM GENERATOR(Breach item)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Breach item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Piece of set");
			tag_filter->banned_tags.push_back("Splinter item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);
		}


		/////////////////////////////			ITEM GENERATOR(Splinters low)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Breach item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Splinter item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			/////////////////////////////			STACK SIZE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 10;
				value_generator->generator_pow = 3.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR(Splinters high)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Breach item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Splinter item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			/////////////////////////////			STACK SIZE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 10;
				value_generator->max_value = 100;
				value_generator->generator_pow = 3.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR(Uniques)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 1;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Breach unique item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			//GENERATORS
			game_item_generator->add_item_level(70, 86, 1.0f);
			game_item_generator->add_rarity(3, 3, 1.0f);
		}



		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_all_equip_high_level()
{
	//		ALL EQUIP (high level)
	{
		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "All equipable\\n(high level)";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��� ����������\\n(������� �������)";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_all_equip");

		/////////////////////////////			ITEM GENERATOR (ALL GLOVES)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Gloves");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 75;
				value_generator->max_value = 83;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 4;

				value_generator->links_min = 1;
				value_generator->links_max = 4;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (ALL BOOTS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Boots");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 75;
				value_generator->max_value = 83;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 4;

				value_generator->links_min = 1;
				value_generator->links_max = 4;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (ALL HELMETS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("HELMETS");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 75;
				value_generator->max_value = 83;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 4;

				value_generator->links_min = 1;
				value_generator->links_max = 4;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}



		/////////////////////////////			ITEM GENERATOR (ALL BODY AROURS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Body Armours");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 75;
				value_generator->max_value = 83;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 5;
				value_generator->sockets_max_value = 6;

				value_generator->links_min = 4;
				value_generator->links_max = 6;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (JEWELRY)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_ALL;
			game_item_generator->generations_count = 3;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Rings");
			tag_filter->suitable_values.push_back("Amulets");
			tag_filter->suitable_values.push_back("Belts");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			tag_filter->banned_tags.push_back("Expensive base for unique");
			tag_filter->banned_tags.push_back("Rare base");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 75;
				value_generator->max_value = 83;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_all_equip_low_level()
{
	//		ALL EQUIP (low level)
	{
		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "All equipable\\n(low level)";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��� ����������\\n(������ �������)";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_all_equip");

		/////////////////////////////			ITEM GENERATOR (ALL GLOVES)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Gloves");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 68;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 4;

				value_generator->links_min = 1;
				value_generator->links_max = 4;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (ALL BOOTS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Boots");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 75;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 4;

				value_generator->links_min = 1;
				value_generator->links_max = 4;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (ALL HELMETS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("HELMETS");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 75;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 4;

				value_generator->links_min = 1;
				value_generator->links_max = 4;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}



		/////////////////////////////			ITEM GENERATOR (ALL BODY AROURS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE;
			game_item_generator->random_selection_count = 8;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Item slot");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Body Armours");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 75;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 4;
				value_generator->sockets_max_value = 6;

				value_generator->links_min = 4;
				value_generator->links_max = 6;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (JEWELRY)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);

			game_item_generator->generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_ALL;
			game_item_generator->generations_count = 3;


			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Rings");
			tag_filter->suitable_values.push_back("Amulets");
			tag_filter->suitable_values.push_back("Belts");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			tag_filter->banned_tags.push_back("Heist base");
			tag_filter->banned_tags.push_back("Top tier base");
			tag_filter->banned_tags.push_back("Ritual base top");
			tag_filter->banned_tags.push_back("Ritual base medium");
			tag_filter->banned_tags.push_back("Ritual base low");
			tag_filter->banned_tags.push_back("Expensive base for unique");
			tag_filter->banned_tags.push_back("Rare base");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 75;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.1f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_top_tier_bases()
{
	//		TOP TIER BASES
	{
		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Top tier bases";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "������� ����";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_good_bases");

		/////////////////////////////			ITEM GENERATOR (GLOVES HELMETS BOOTS)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Top tier base");
			tag_filter->suitable_values.push_back("Rare base");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Gloves");
			tag_filter->suitable_values.push_back("Helmets");
			tag_filter->suitable_values.push_back("Boots");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.35f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 4;

				value_generator->links_min = 1;
				value_generator->links_max = 4;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (BODY ARMOUR)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Top tier base");
			tag_filter->suitable_values.push_back("Rare base");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Rings");
			tag_filter->suitable_values.push_back("Amulets");
			tag_filter->suitable_values.push_back("Belts");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.5f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (BODY ARMOUR)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Top tier base");
			tag_filter->suitable_values.push_back("Rare base");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Body Armours");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);



			/////////////////////////////			RARITY			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorRarity*
					value_generator = new GameAttributeGeneratorRarity("Rarity");


				//		parameters
				value_generator->min_value = 0;
				value_generator->max_value = 3;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			ITEM LEVEL			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorMinMaxInt*
					value_generator = new GameAttributeGeneratorMinMaxInt("ItemLevel");

				//		parameters
				value_generator->min_value = 68;
				value_generator->max_value = 86;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			INFLUENCE			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorItemInfluence*
					value_generator = new GameAttributeGeneratorItemInfluence("HasInfluence");

				//		parameters
				value_generator->chance_to_generate = 0.5f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}

			/////////////////////////////			SOCKETS			/////////////////////////////////////////////
			{

				//		value
				GameAttributeGeneratorSocketsLinksColours*
					value_generator = new GameAttributeGeneratorSocketsLinksColours("SocketGroup");

				//		parameters
				value_generator->sockets_min_value = 1;
				value_generator->sockets_max_value = 6;

				value_generator->links_min = 1;
				value_generator->links_max = 6;

				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_RED] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_GREEN] = 100;
				value_generator->color_weight[SocketColorEnum::SOCKET_COLOR_ENUM_BLUE] = 100;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_oils_and_catalysts()
{
	//		OILS AND CATALYSTS
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Oils and catlysts";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "����� � ������������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_oils_and_catalysts");


		/////////////////////////////			ITEM GENERATOR (CHEAP CURRENCY SMALL STACK)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 3;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Stackable Currency");
			tag_filter->suitable_values.push_back("Currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Oil item");
			tag_filter->suitable_values.push_back("Catalyst item");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 20;
				value_generator->generator_pow = 3.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_currencies_shard()
{
	//		CURRENCY SHARD
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Currency shard";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "������� �����";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/Annulment_Shard_inventory_icon");


		/////////////////////////////			ITEM GENERATOR (CHEAP CURRENCY SMALL STACK)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 3;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Stackable Currency");
			tag_filter->suitable_values.push_back("Currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			//tag_filter = new LootSimulatorTagFilter;
			//tag_filter->target_tag = "worth";
			//tag_filter->suitable_values.push_back("Rare");
			//tag_filter->suitable_values.push_back("Expensive");
			//tag_filter->suitable_values.push_back("Very expensive");
			//game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Currency shard");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 20;
				value_generator->generator_pow = 3.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_tainted_currencies()
{
	//		TAINTED CURRENCY
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Tainted currency";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "�������� ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("icons/TaintedOrbofFusing");


		/////////////////////////////			ITEM GENERATOR (CHEAP CURRENCY SMALL STACK)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 3;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Stackable Currency");
			tag_filter->suitable_values.push_back("Currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			//tag_filter = new LootSimulatorTagFilter;
			//tag_filter->target_tag = "worth";
			//tag_filter->suitable_values.push_back("Rare");
			//tag_filter->suitable_values.push_back("Expensive");
			//tag_filter->suitable_values.push_back("Very expensive");
			//game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Tainted currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 20;
				value_generator->generator_pow = 3.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_rare_currencies()
{
	//		RARE CURRENCY
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Rare currency";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "������ ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_rare_currency");


		/////////////////////////////			ITEM GENERATOR (CHEAP CURRENCY SMALL STACK)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 3;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Stackable Currency");
			tag_filter->suitable_values.push_back("Currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Rare");
			tag_filter->suitable_values.push_back("Expensive");
			tag_filter->suitable_values.push_back("Very expensive");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			//tag_filter = new LootSimulatorTagFilter;
			//tag_filter->target_tag = "item tag";
			//tag_filter->suitable_values.push_back("Basic currency");
			//game_item_generator->filtered_by_tags.push_back(tag_filter);


			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 20;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_good_currencies()
{
	//			GOOD CURRENCY
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Good currency";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "������ ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_good_currency");


		/////////////////////////////			ITEM GENERATOR (CHEAP CURRENCY SMALL STACK)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 4;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Stackable Currency");
			tag_filter->suitable_values.push_back("Currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Common");
			tag_filter->suitable_values.push_back("Moderate");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Basic currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 20;
				value_generator->generator_pow = 1.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern
	}
}

void EWindowMain::register_pattern_trash_currencies()
{
	//		TRASH CURRENCY
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Cheap currency";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "������� ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_trash_currencies");


		/////////////////////////////			ITEM GENERATOR (CHEAP CURRENCY SMALL STACK)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 4;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Stackable Currency");
			tag_filter->suitable_values.push_back("Currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Trash");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Basic currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 1;
				value_generator->max_value = 4;
				value_generator->generator_pow = 2.0f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		/////////////////////////////			ITEM GENERATOR (CHEAP CURRENCY BIG STACK)			/////////////////////////////////////////////
		{
			GameItemGenerator*
				game_item_generator = new GameItemGenerator();
			game_item_generator->generations_count = 4;
			loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




			LootSimulatorTagFilter*
				tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "base class";
			tag_filter->suitable_values.push_back("Stackable Currency");
			tag_filter->suitable_values.push_back("Currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "worth";
			tag_filter->suitable_values.push_back("Trash");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->suitable_values.push_back("Basic currency");
			game_item_generator->filtered_by_tags.push_back(tag_filter);

			tag_filter = new LootSimulatorTagFilter;
			tag_filter->target_tag = "item tag";
			tag_filter->banned_tags.push_back("Deleted");
			game_item_generator->filtered_by_tags.push_back(tag_filter);


			/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
			{
				//		value
				GameAttributeGeneratorQuantity*
					value_generator = new GameAttributeGeneratorQuantity("StackSize");

				//		parameters
				value_generator->min_value = 5;
				value_generator->max_value = 20;
				value_generator->generator_pow = 0.5f;

				game_item_generator->attribute_generators_list.push_back(value_generator);
			}
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_basic_currencies()
{
	//		BASIC CURRENCY
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "Basic currency";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "������� ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_all_basic_currencies");

		/////////////////////////////			ITEM GENERATOR (ALL BASIC CURRENCY)			/////////////////////////////////////////////
		GameItemGenerator*
			game_item_generator = new GameItemGenerator();
		loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




		LootSimulatorTagFilter*
			tag_filter = new LootSimulatorTagFilter;
		tag_filter->target_tag = "item tag";
		tag_filter->suitable_values.push_back("Basic currency");
		game_item_generator->filtered_by_tags.push_back(tag_filter);

		tag_filter = new LootSimulatorTagFilter;
		tag_filter->target_tag = "item tag";
		tag_filter->suitable_values.push_back("World drop");
		game_item_generator->filtered_by_tags.push_back(tag_filter);

		tag_filter = new LootSimulatorTagFilter;
		tag_filter->target_tag = "item tag";
		tag_filter->banned_tags.push_back("Deleted");
		game_item_generator->filtered_by_tags.push_back(tag_filter);



		/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
		{
			//		value
			GameAttributeGeneratorQuantity*
				value_generator = new GameAttributeGeneratorQuantity("StackSize");

			//		parameters
			value_generator->min_value = 1;
			value_generator->max_value = 20;
			value_generator->generator_pow = 3.0f;

			game_item_generator->attribute_generators_list.push_back(value_generator);
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::register_pattern_all_currencies()
{
	//		ALL CURRENCIES
	{

		LootSimulatorPattern*
			loot_simulator_pattern = new LootSimulatorPattern;

		loot_simulator_pattern->localised_name.localisations[NSW_localisation_EN] = "All currencies";
		loot_simulator_pattern->localised_name.localisations[NSW_localisation_RU] = "��� ������";
		loot_simulator_pattern->icon = NS_EGraphicCore::load_from_textures_folder("buttons/button_all_basic_currencies");

		/////////////////////////////			ITEM GENERATOR (ALL CURRENCY)			/////////////////////////////////////////////
		GameItemGenerator*
			game_item_generator = new GameItemGenerator();
		loot_simulator_pattern->game_item_generator_list.push_back(game_item_generator);




		LootSimulatorTagFilter*
			tag_filter = new LootSimulatorTagFilter;
		tag_filter->target_tag = "base class";
		tag_filter->suitable_values.push_back("Stackable Currency");
		tag_filter->suitable_values.push_back("Currency");
		game_item_generator->filtered_by_tags.push_back(tag_filter);

		tag_filter = new LootSimulatorTagFilter;
		tag_filter->target_tag = "item tag";
		tag_filter->banned_tags.push_back("Deleted");
		game_item_generator->filtered_by_tags.push_back(tag_filter);



		/////////////////////////////			CREATE ATTRIBUTE AND GENERATE VALUE			/////////////////////////////////////////////
		{
			//		value
			GameAttributeGeneratorQuantity*
				value_generator = new GameAttributeGeneratorQuantity("StackSize");

			//		parameters
			value_generator->min_value = 1;
			value_generator->max_value = 20;
			value_generator->generator_pow = 3.0f;

			game_item_generator->attribute_generators_list.push_back(value_generator);
		}

		LootSimulatorPattern::registered_loot_simulater_pattern_list.push_back(loot_simulator_pattern);//register new pattern

	}
}

void EWindowMain::set_color_version(HSVRGBAColor* _target_color, int _selected_mode)
{
	// hide or ignore
	if ((_selected_mode == 1) || (_selected_mode == 2))
	{
		_target_color->s *= 0.75f;
		_target_color->v *= 0.75f;

		Helper::hsv2rgb(_target_color);
	}
	else//focus
		if (_selected_mode == 4)
		{
			_target_color->s *= 1.5f;
			_target_color->v *= 1.5f;

			Helper::hsv2rgb(_target_color);
		}


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

	{ add_content_block_data->target_filter_block = (EButtonGroupFilterBlock*)(button_plus_data->master_group); }

	//if (taget_group_for_content != nullptr) { taget_group_for_content->button_list.clear(); }
}

void EDataActionCollection::action_add_selected_content_to_filter_block(Entity* _entity, ECustomData* _custom_data, float _d)
{

	EDataContainer_Button_AddContentToFilterBlock* button_content_data = static_cast<EDataContainer_Button_AddContentToFilterBlock*>	(_custom_data->data_container);


	EDataContainer_Group_AddContentToFilterBlock* add_content_group_data = static_cast<EDataContainer_Group_AddContentToFilterBlock*>	(EButtonGroup::add_content_to_filter_block_group->data_container);
	EButtonGroupFilterBlock* whole_button_group = add_content_group_data->target_filter_block;

	EButtonGroupFilterBlock* whole_filter_block_data = static_cast<EButtonGroupFilterBlock*>			(whole_button_group);
	EDataContainer_Button_AddContentToFilterBlock* add_content_button_data = static_cast<EDataContainer_Button_AddContentToFilterBlock*>	(_custom_data->data_container);

	EButtonGroup* target_group_for_content = nullptr;

	EntityButton* jc_button = nullptr;

	add_filter_block_content_to_filter_block(whole_button_group, add_content_button_data->target_attribute);

	//if (taget_group_for_content != nullptr)
	//{ 
	//	*taget_group_for_content->is_active = false; 
	//}

	if (!EInputCore::key_pressed(GLFW_KEY_LEFT_SHIFT))
	{
		EButtonGroup::add_content_to_filter_block_group->is_active = false;
	}

	EButtonGroup::change_group(EWindowMain::loot_filter_editor);
	EWindowMain::loot_simulator_button_group->refresh_loot_simulator();

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
void add_filter_block_content_to_filter_block(EButtonGroupFilterBlock* _target_filter_block, GameItemAttribute* _game_item_attribute)
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

	std::string temp_rarity[] = { "����������", "����������", "������", "����������" };
	EButtonGroup* target_group_for_content;

	HSVRGBAColor rarity_color[4];

	HSVRGBAColor temp_color;

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
	if (_game_item_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_NON_LISTED)
	{
		//EInputCore::logger_simple_info("add new non listed button");
		target_group_for_content = whole_filter_block_data->pointer_to_non_listed_segment;

		EButtonGroupNonListedLine*
			non_listed_line = new EButtonGroupNonListedLine(new ERegionGabarite(20.0f, button_height));
		non_listed_line->init_button_group(EGUIStyle::active_style, bgroup_without_bg, bgroup_without_slider, bgroup_default_bg);



		non_listed_line->set_parameters
		(
			ChildAlignMode::ALIGN_VERTICAL,
			NSW_dynamic_autosize,
			NSW_static_autosize
		);
		non_listed_line->button_align_type = ButtonAlignType::BUTTON_ALIGN_LEFT;

		whole_filter_block_data->pointer_to_non_listed_segment->add_group(non_listed_line);


		non_listed_line->target_filter_block_attribute = _game_item_attribute;

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

		jc_button->parent_filter_block = _target_filter_block;
		jc_button->used_filter_block_attribute = _game_item_attribute;

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
			_game_item_attribute->localisation.localisations[ELocalisationText::active_localisation]
		);

		jc_button->parent_filter_block = _target_filter_block;
		jc_button->used_filter_block_attribute = _game_item_attribute;

		ETextArea* last_text_area = Entity::get_last_text_area(jc_button);
		if (last_text_area != nullptr) { last_text_area->localisation_text = _game_item_attribute->localisation; }
		non_listed_line->target_button_with_attribute_name = jc_button;

		non_listed_line->button_list.push_back(jc_button);
		///////////////////////////////////////////////////////////////////////////////////////////////







		/*CONDITION OPERATOR BUTTON*/
		///////////////////////////////////////////////////////////////////////////////////////////////
		float input_field_additional_width = 0.0f;
		//condition operator
		if (_game_item_attribute->have_operator)
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
			jc_button->used_filter_block_attribute = _game_item_attribute;

			non_listed_line->button_list.push_back(jc_button);

			non_listed_line->target_button_with_condition = jc_button;
		}
		else
		{
			input_field_additional_width = button_height * 2.0f + BUTTON_FORCE_FIELD_SIZE;

			non_listed_line->target_button_with_condition = nullptr;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////

		srand(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

		//EInputCore::logger_param("current time", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		int rarity_id = rand() % 4;

		std::string text = std::to_string(rand() % 100 + 1);

		switch (_game_item_attribute->filter_attribute_value_type)
		{
		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST:
		{
			//text = temp_rarity[rarity_id];

			//jc_button = new EntityButtonForFilterBlock();
			//jc_button->make_default_button_with_unedible_text
			//(
			//	new ERegionGabarite(100.0f + input_field_additional_width, button_height),
			//	non_listed_line,
			//	&EDataActionCollection::action_open_rarity_selector,
			//	text
			//);

			//jc_button->parent_filter_block = _target_filter_block;
			//jc_button->used_filter_block_attribute = _filter_block_attribute;

			//EntityButton::get_last_clickable_area(jc_button)->text_area->set_color(&rarity_color[rarity_id]);
			//Entity::get_last_text_area(jc_button)->localisation_text = _filter_block_attribute->localisation;

			//non_listed_line->target_button_with_value = jc_button;

			EntityButtonVariantRouterForFilterBlock*
				rarity_button = new EntityButtonVariantRouterForFilterBlock();
			rarity_button->make_default_router_variant_button
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				&EDataActionCollection::action_rotate_variant
			);
			rarity_button->parent_filter_block = _target_filter_block;
			rarity_button->rotate_variant_mode = RotateVariantMode::OPEN_CHOOSE_WINDOW;

			non_listed_line->rarity_router_button = rarity_button;
			non_listed_line->button_list.push_back(rarity_button);

			RouterVariant* router_variant = nullptr;
			ELocalisationText* ltext = nullptr;

			///		NORMAL		///////////////////////////////////////////////////////////////////////////
			router_variant = new RouterVariant();
			ltext = new ELocalisationText();

			ltext->base_name = "Normal";
			ltext->localisations[NSW_localisation_EN] = "Normal";
			ltext->localisations[NSW_localisation_RU] = "�������";

			router_variant->localisation = ltext;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

			rarity_button->router_variant_list.push_back(router_variant);
			///		MAGIC		///////////////////////////////////////////////////////////////////////////
			router_variant = new RouterVariant();
			ltext = new ELocalisationText();

			ltext->base_name = "Magic";
			ltext->localisations[NSW_localisation_EN] = "Magic";
			ltext->localisations[NSW_localisation_RU] = "���������";

			router_variant->localisation = ltext;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(0.2f, 0.6f, 1.6f, 1.0f);

			rarity_button->router_variant_list.push_back(router_variant);
			///		RARE		///////////////////////////////////////////////////////////////////////////
			router_variant = new RouterVariant();
			ltext = new ELocalisationText();

			ltext->base_name = "Rare";
			ltext->localisations[NSW_localisation_EN] = "Rare";
			ltext->localisations[NSW_localisation_RU] = "������";

			router_variant->localisation = ltext;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.2f, 1.0f);

			rarity_button->router_variant_list.push_back(router_variant);
			///		UNIQUE		///////////////////////////////////////////////////////////////////////////
			router_variant = new RouterVariant();
			ltext = new ELocalisationText();

			ltext->base_name = "Unique";
			ltext->localisations[NSW_localisation_EN] = "Unique";
			ltext->localisations[NSW_localisation_RU] = "����������";

			router_variant->localisation = ltext;

			router_variant->color = new HSVRGBAColor();
			router_variant->color->set_color_RGBA(1.0f, 0.5f, 0.25f, 1.0f);

			rarity_button->router_variant_list.push_back(router_variant);
			///////////////////////////////////////////////////////////////////////////////////////////////

			rarity_button->select_variant(0);


			//non_listed_line->button_list.push_back(rarity_button);
			break;
		}

		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST:
		{
			text = EWindowMain::registered_alternate_gem_quality_router_variants[0]->localisation->base_name;

			jc_button = new EntityButtonForFilterBlock();
			jc_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(100.0f + input_field_additional_width, button_height),
				non_listed_line,
				&EDataActionCollection::action_open_quality_selector,
				text
			);
			jc_button->main_text_area->set_color(EWindowMain::registered_alternate_gem_quality_router_variants[0]->color);
			jc_button->main_text_area->change_text(text);
			jc_button->main_text_area->localisation_text = *EWindowMain::registered_alternate_gem_quality_router_variants[0]->localisation;

			jc_button->parent_filter_block = _target_filter_block;
			jc_button->used_filter_block_attribute = _game_item_attribute;

			//Entity::get_last_text_area(jc_button)->localisation_text = _game_item_attribute->localisation;

			non_listed_line->target_button_with_value = jc_button;
			non_listed_line->button_list.push_back(jc_button);

			break;
		}

		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER:
		{
			//NON-LISTED GAME TTRIBUTE BOOL CHECKER
			jc_button = new EntityButtonForFilterBlock();
			jc_button->make_default_bool_switcher_button
			(
				new ERegionGabarite(22.0f, 22.0f),
				non_listed_line,
				EDataActionCollection::action_switch_boolean_value,
				NS_DefaultGabarites::texture_bool_switcher_activated_box,
				NS_DefaultGabarites::texture_bool_switcher_deactivated_box,
				nullptr
			);

			jc_button->parent_filter_block = _target_filter_block;
			jc_button->used_filter_block_attribute = _game_item_attribute;

			non_listed_line->target_button_with_value = jc_button;
			non_listed_line->button_list.push_back(jc_button);

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

			jc_button->main_text_area->gray_text = ELocalisationText();
			jc_button->main_text_area->gray_text.localisations[NSW_localisation_EN] = "value";
			jc_button->main_text_area->gray_text.localisations[NSW_localisation_RU] = "��������";

			jc_button->parent_filter_block = _target_filter_block;
			jc_button->used_filter_block_attribute = _game_item_attribute;

			Entity::get_last_text_area(jc_button)->localisation_text = _game_item_attribute->localisation;

			non_listed_line->target_button_with_value = jc_button;
			non_listed_line->button_list.push_back(jc_button);
		}


		}





		//EButtonGroup::change_group(target_group_for_content);

		/*if (j == 0) { jc_region_gabarite = new ERegionGabarite(100.0f, 20.0f); }
		else
			if (j == 1) { jc_region_gabarite = new ERegionGabarite(20.0f, 20.0f); }
			else
				if (j == 2) { jc_region_gabarite = new ERegionGabarite(50.0f, 20.0f); }*/

				//EInputCore::logger_param("vector size", whole_filter_block_data->pointer_to_non_listed_segment->group_list.size());
	}


	if (_game_item_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_LISTED)
	{
		target_group_for_content = whole_filter_block_data->pointer_to_listed_segment;

		EButtonGroup* listed_condition_group_container = create_block_for_listed_segment
		(
			_game_item_attribute->filter_rule,
			_game_item_attribute,
			_game_item_attribute->localisation.base_name,
			target_group_for_content
		);


		EButtonGroup::change_group(target_group_for_content);
	}


	if
		(
			(_game_item_attribute->filter_attribute_type == FilterAttributeType::FILTER_ATTRIBUTE_TYPE_COSMETIC)
			&&
			(false)
			)
	{
		target_group_for_content = whole_filter_block_data->pointer_to_cosmetic_segment;

		switch (_game_item_attribute->filter_attribute_value_type)
		{
		case FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_COLOR:
		{
			HRA_color_collection* HRA_collection = Helper::registered_color_list[rand() % Helper::registered_color_list.size()];
			HSVRGBAColor* HRA_color = &HRA_collection->target_color;


			EntityButton* jc_button = EntityButton::create_named_color_button
			(
				new ERegionGabarite(242.0f, 38.0f),
				target_group_for_content,
				EFont::font_list[0],
				EGUIStyle::active_style,
				_game_item_attribute->localisation,
				nullptr,
				HRA_color,
				ColorButtonMode::CBM_OPEN_WINDOW
			);
			Entity::get_last_text_area(jc_button)->localisation_text = _game_item_attribute->localisation;

			target_group_for_content->button_list.push_back(jc_button);

			EButtonGroup::change_group(target_group_for_content);
			break;
		}

		default:
		{

		}
		}
	}

	//EWindowMain::loot_simulator_button_group->refresh_loot_simulator();
}


std::string generate_filter_block_text(EButtonGroup* _button_group, FilterBlockSaveMode _save_mode = FilterBlockSaveMode::VERSION_ORIGINAL)
{

	auto whole_block_data = static_cast<EButtonGroupFilterBlock*>(_button_group);

	float	temp_size = whole_block_data->text_size;
	int		selected_version = -1;

	bool	lower_focus = false;
	bool	raised_focus = false;

	bool	ignore_sound = false;
	bool	ignore_minimap_elements = false;

	int		version_id = (int)(_save_mode);

	EntityButtonVariantRouterForFilterBlock* version_router = nullptr;


	//not original version can modify colors, fonts, sounds and etc...
	if (_save_mode != FilterBlockSaveMode::VERSION_ORIGINAL)
	{
		//matched router button
		version_router = whole_block_data->version_routers[version_id];

		//version of loot colors
		selected_version = version_router->selected_variant;

		if
			(
				(selected_version == LootFilterVersionDescription::LOOT_VERSION_HIDE)
				||
				(selected_version == LootFilterVersionDescription::LOOT_VERSION_IGNORE)
				)
		{
			lower_focus = true;
			ignore_sound = true;
			ignore_minimap_elements = true;
		}

		if (selected_version == LootFilterVersionDescription::LOOT_VERSION_FOCUS)
		{
			raised_focus = true;
		}
	}


	//if version is not FULL_IGNORE, or if VERSION_ORIGINAL
	if ((selected_version != LootFilterVersionDescription::LOOT_VERSION_FULL_IGNORE) || (_save_mode == FilterBlockSaveMode::VERSION_ORIGINAL))
	{
		std::string result_string = "";



		if ((whole_block_data->button_show_hide->selected_variant == 0) || (selected_version == LootFilterVersionDescription::LOOT_VERSION_HIDE))
		{
			result_string += "Hide";
		}
		else
		{
			result_string += "Show";
		}
		result_string += '\n';


		if (_save_mode == FilterBlockSaveMode::VERSION_ORIGINAL)
		{
			result_string += "\t#config_VersionControl";

			for (int i = 0; i < 5; i++)
			{
				result_string += " " + whole_block_data->version_routers[i]->router_variant_list[whole_block_data->version_routers[i]->selected_variant]->localisation->base_name;
			}

			result_string += '\n';
		}







		//auto bg_color_data = static_cast<EDataContainer_Button_StoreColor*>(Entity::get_last_custom_data(whole_block_data->pointer_to_color_button[0])->data_container);
		//auto bg_color = bg_color_data->stored_color;
		HSVRGBAColor temp_colors[3];

		for (int i = 0; i < 3; i++)
		{
			temp_colors[i].set_color(whole_block_data->pointer_to_color_button[i]->stored_color);
		}
		//EInputCore::logger_param("version id", version_id);

		//	Full ignore	0
		//	Hide		1
		//	Ignore		2
		//	Default		3
		//	Focus		4

		//font size


		//if hide or ignore, reduce saturation, brightness, and size
		if (lower_focus)
		{
			for (int i = 0; i < 3; i++)
			{
				temp_colors[i].s *= 0.75f;
				temp_colors[i].v *= 0.75f;

				Helper::hsv2rgb(&temp_colors[i]);
			}

			temp_size *= 0.6f;
		}

		//if focus, increase saturation, brightness, and size
		if (raised_focus)
		{
			for (int i = 0; i < 3; i++)
			{
				temp_colors[i].s *= 1.5f;
				temp_colors[i].v *= 1.5f;

				Helper::hsv2rgb(&temp_colors[i]);
			}

			temp_size *= 1.5f;
		}



		EButtonGroup* non_listed_section = whole_block_data->pointer_to_non_listed_segment;
		EButtonGroup* listed_section = whole_block_data->pointer_to_listed_segment;
		EButtonGroup* cosmetic_section = whole_block_data->pointer_to_cosmetic_segment;

		//NON-LISTED
		for (EButtonGroup* n_listed : non_listed_section->group_list)
		{
			EButtonGroupNonListedLine* container = static_cast<EButtonGroupNonListedLine*>(n_listed);

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

			if ((container->target_button_with_condition != nullptr) && (container->target_button_with_condition->main_text_area->original_text != ""))
			{
				result_string += " ";
				result_string += (Entity::get_last_text_area(container->target_button_with_condition)->original_text);
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
				result_string += (Entity::get_last_text_area(container->target_button_with_value)->original_text);
			}

			if (container->target_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST)
			{
				result_string += " ";
				result_string += container->rarity_router_button->router_variant_list[container->rarity_router_button->selected_variant]->localisation->base_name;
			}


			if (container->target_filter_block_attribute->filter_attribute_value_type == FilterAttributeValueType::FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST)
			{
				result_string += " ";
				result_string += Entity::get_last_text_area(container->target_button_with_value)->localisation_text.base_name;
			}

			result_string += '\n';
		}

		//LISTED
		for (EButtonGroup* listed : listed_section->group_list)
		{
			auto container = static_cast<EDataContainer_Group_FilterBlockListedSegment*>(listed->data_container);


			if ((container != nullptr) && (container->group_with_listed_buttons->button_list.size() > 1))
			{
				result_string += '\t' + container->filter_attribute_name;

				if ((container->match_mode_router_button != nullptr) && (container->match_mode_router_button->selected_variant == 1))
				{
					result_string += " ==";
				}

				if ((container->input_field != nullptr))
				{
					if (container->input_field->main_text_area->original_text != "")
					{
						result_string += " " + container->input_field->main_text_area->original_text;
					}
					else
					{
						result_string += " >=1 ";
					}
				}


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

		auto cosmetic_data = whole_block_data;
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
			//auto store_color_data = static_cast<EDataContainer_Button_StoreColor*>(Entity::get_last_custom_data(cosmetic_data->pointer_to_color_button[i])->data_container);

			result_string += " " + std::to_string((int)round(temp_colors[i].r * 255.0f));
			result_string += " " + std::to_string((int)round(temp_colors[i].g * 255.0f));
			result_string += " " + std::to_string((int)round(temp_colors[i].b * 255.0f));
			result_string += " " + std::to_string((int)round(temp_colors[i].a * 255.0f));

			result_string += '\n';
		}


		//font size
		result_string += '\t';
		if (!cosmetic_data->text_size_bool)
		{
			result_string += "#";
		}
		tarea = Entity::get_last_text_area(cosmetic_data->text_size_button);

		//result_string += tarea->localisation_text.base_name;
		result_string += "SetFontSize";

		result_string += " " + std::to_string((int)(round(18.0f + temp_size * 27.0f)));
		result_string += '\n';




		//		MINIMAP ICONS
		//////////////////////////////////////////////////////////////////

		//		MINIMAP ICON
		if (!ignore_minimap_elements)
		{
			result_string += '\t';
			if (!whole_block_data->minimap_icon_color_suppressor_bool)
			{
				result_string += "#";
			}
			result_string += "MinimapIcon";
			EntityButtonVariantRouter* button_router_size = whole_block_data->pointer_to_minimap_icon_size_router;
			EntityButtonVariantRouter* button_router_color = whole_block_data->pointer_to_minimap_icon_color_router;
			EntityButtonVariantRouter* button_router_shape = whole_block_data->pointer_to_minimap_icon_shape_router;

			//		add size name to line
			result_string += ' ' + button_router_size->router_variant_list[button_router_size->selected_variant]->localisation->base_name;

			//		add color name to line
			result_string += ' ' + button_router_color->router_variant_list[button_router_color->selected_variant]->localisation->base_name;

			//		add shape name to line
			result_string += ' ' + button_router_shape->router_variant_list[button_router_shape->selected_variant]->localisation->base_name;

			result_string += '\n';



			//RAY
			result_string += '\t';
			if (!whole_block_data->ray_suppressor)
			{
				result_string += "#";
			}
			result_string += "PlayEffect";

			result_string += ' ';
			result_string += whole_block_data->pointer_to_ray_color_router->router_variant_list[whole_block_data->pointer_to_ray_color_router->selected_variant]->localisation->base_name;

			if (whole_block_data->pointer_to_temporary_option_router->selected_variant == 1)
			{
				result_string += ' ';
				result_string += whole_block_data->pointer_to_temporary_option_router->router_variant_list[1]->localisation->base_name;
			}

			result_string += '\n';
		}
		//////////////////////////////////////////////////////////////////

		if (!ignore_sound)
		{
			//		USER SOUND
			if (whole_block_data->pointer_to_custom_sound_button->stored_named_sound != nullptr)
			{
				result_string += '\t';
				if (!whole_block_data->custom_sound_suppressor_bool)
				{
					result_string += "#";
				}
				result_string += "CustomAlertSound";
				//if (whole_block_data->pointer_to_positional_variant_button->selected_variant == 1) { result_string }
				if (whole_block_data->pointer_to_optional_user_sound->selected_variant == 1) { result_string += "Optional"; }

				result_string += " \"" + whole_block_data->pointer_to_custom_sound_button->stored_named_sound->localisation_text.base_name + '"';

				result_string += '\n';
			}





			//		INGAME SOUNDS
			if (whole_block_data->pointer_to_game_sound_button->stored_named_sound != nullptr)
			{
				result_string += '\t';
				if (!whole_block_data->game_sound_suppressor_bool)
				{
					result_string += "#";
				}
				result_string += "PlayAlertSound";
				if (whole_block_data->pointer_to_positional_variant_button->selected_variant == 1) { result_string += "Positional"; }


				result_string += ' ' + whole_block_data->pointer_to_game_sound_button->stored_named_sound->localisation_text.base_name;
				result_string += ' ' + std::to_string(int(whole_block_data->sound_volume_value * 300.0f));
				result_string += '\n';
			}

			//ENABLE/DISABLE DROP SOUND
			EntityButtonVariantRouterForFilterBlock* drop_sound_router_button = whole_block_data->pointer_to_disable_enable_drop_sound;

			if (drop_sound_router_button->selected_variant > 0)
			{
				result_string += '\t';
				result_string += drop_sound_router_button->router_variant_list[drop_sound_router_button->selected_variant]->localisation->base_name;
				result_string += '\n';
			}
		}



		//if (whole_block_data->pointer_to_disable_enable_drop_sound->selected_variant == 1)
		//{
		//	result_string += "\tDisableDropSound\n";
		//}

		//if (whole_block_data->pointer_to_disable_enable_drop_sound->selected_variant == 2)
		//{
		//	result_string += "\tEnableDropSound\n";
		//}


		if (whole_block_data->button_continue->selected_variant == 0)
		{
			result_string += "\tContinue";
			result_string += '\n';
		}

		return result_string;
	}
	else
	{
		return "";
	}
}

std::string generate_filter_block_separator_text(EButtonGroupFilterBlockSeparator* _separator, FilterBlockSaveMode _save_mode)
{
	std::string text_buffer = "";

	text_buffer += "#BlockSeparator";

	if (_separator->pointer_to_description_button->main_text_area->original_text == "")
	{
		text_buffer += " \"*EMPTY*\"";
	}
	else
	{
		text_buffer += " \"" + _separator->pointer_to_description_button->main_text_area->original_text + "\"";
	}

	if (_separator->is_expanded)
	{
		text_buffer += " expanded";
	}
	else
	{
		text_buffer += " shrinked";
	}

	return text_buffer;
}

EButtonGroup* create_block_for_listed_segment(EFilterRule* _filter_rule, GameItemAttribute* _attribute, std::string _attribute_name, EButtonGroup* _parent)
{
	EButtonGroup*
		main_listed_group = new EButtonGroup(new ERegionGabarite(800.0f, _filter_rule->min_y_size));
	main_listed_group->init_button_group(EGUIStyle::active_style, bgroup_with_bg, bgroup_with_slider, bgroup_default_bg);

	main_listed_group->
		set_parameters
		(
			ChildAlignMode::ALIGN_HORIZONTAL,
			NSW_dynamic_autosize,
			NSW_dynamic_autosize
		);

	main_listed_group->min_size_y = _filter_rule->min_y_size;

	//data container, store pointer to group with listed buttons
	auto d_container = new EDataContainer_Group_FilterBlockListedSegment();

	//if ((_attribute != nullptr) && (_override_attribute_name == ""))
	//{
	//	d_container->filter_attribute_name = _attribute->localisation.base_name;
	//}
	//else
	//{
	//	d_container->filter_attribute_name = _override_attribute_name;
	//}

	d_container->filter_attribute_name = _attribute_name;
	d_container->associated_item_attribute = _attribute;

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

	ELocalisationText l_text;
	l_text.localisations[NSW_localisation_EN] = "Add new item";
	l_text.localisations[NSW_localisation_RU] = "�������� �������";

	small_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(130.0f, 24.0f),
		listed_group_left_side,
		&EDataActionCollection::action_open_data_entity_filter_group,
		l_text.localisations[ELocalisationText::active_localisation]
	);

	small_button->main_text_area->localisation_text = l_text;


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
	l_text.localisations[NSW_localisation_EN] = "Remove block";
	l_text.localisations[NSW_localisation_RU] = "������� ����";

	EntityButtonForListedSegment* delete_segment_button = new EntityButtonForListedSegment();
	delete_segment_button->make_default_button_with_unedible_text
	(
		new ERegionGabarite(130.0f, 24.0f),
		listed_group_left_side,
		&EDataActionCollection::action_delete_listed_segment,
		l_text.localisations[ELocalisationText::active_localisation]
	);
	delete_segment_button->main_text_area->localisation_text = l_text;
	delete_segment_button->main_text_area->set_color(NS_EColorUtils::COLOR_RED);

	delete_segment_button->listed_group = main_listed_group;
	listed_group_left_side->button_list.push_back(delete_segment_button);
	////////////////////////

	////////////////////////////////////////////////
	////////////////////////////////////////////////
	////////////////////////////////////////////////
	if (_attribute->have_exact_match)
	{
		EntityButtonVariantRouterForFilterBlock* button_variant_FB_router = new EntityButtonVariantRouterForFilterBlock();

		button_variant_FB_router->make_default_router_variant_button
		(
			new ERegionGabarite(130.0f, 32.0f),
			listed_group_left_side,
			EDataActionCollection::action_rotate_variant
		);
		button_variant_FB_router->parent_filter_block = static_cast<EButtonGroupFilterBlock*>(_parent);


		/*button_variant_FB_router->make_as_default_button_with_icon
		(
			new ERegionGabarite(130.0f, 29.0f),
			listed_group_left_side,
			EDataActionCollection::action_rotate_variant,
			nullptr
		);

		button_variant_FB_router->parent_filter_block = static_cast<EButtonGroupFilterBlock*>(_parent);

		button_variant_FB_router->layer_with_icon = button_variant_FB_router->sprite_layer_list.back();

		ETextArea* jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(button_variant_FB_router), EFont::font_list[0], "|?|");
		button_variant_FB_router->pointer_to_text_area = jc_text_area;

		jc_text_area->can_be_edited = false;
		Entity::add_text_area_to_last_clickable_region(button_variant_FB_router, jc_text_area);*/

		//control_part_mid_show_hide_cosmetic->button_list.push_back(button_variant_FB_router);

		d_container->match_mode_router_button = button_variant_FB_router;

		//	0
		/*************************************************************************************/
		RouterVariant* router_variant = new RouterVariant();
		ELocalisationText* local_text = new ELocalisationText();

		local_text->base_name = "Partially match";
		local_text->localisations[NSW_localisation_EN] = "Partially match";
		local_text->localisations[NSW_localisation_RU] = "��������� ����������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.8f, 0.6f, 1.0f);

		//router_variant->texture = NS_DefaultGabarites::texture_show_hide_visual_editor;

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/*************************************************************************************/

		//	1
		/*************************************************************************************/
		router_variant = new RouterVariant();
		local_text = new ELocalisationText();

		local_text->base_name = "Exact match";
		local_text->localisations[NSW_localisation_EN] = "Exact match";
		local_text->localisations[NSW_localisation_RU] = "������ ����������";
		router_variant->localisation = local_text;

		router_variant->color = new HSVRGBAColor();
		router_variant->color->set_color_RGBA(1.0f, 0.5f, 1.0f, 1.0f);

		//router_variant->texture = NS_DefaultGabarites::texture_show_hide_visual_editor_deactivate;

		button_variant_FB_router->router_variant_list.push_back(router_variant);
		/*************************************************************************************/

		button_variant_FB_router->select_variant(0);
		listed_group_left_side->button_list.push_back(button_variant_FB_router);
	}
	////////////////////////////////////////////////
	////////////////////////////////////////////////
	////////////////////////////////////////////////

	///////////////////////////////////////////////
	if (_attribute->have_input_field_for_listed)
	{
		EntityButtonForFilterBlock*
			input_field = new EntityButtonForFilterBlock();
		input_field->make_default_button_with_edible_text
		(
			new ERegionGabarite(130.0f, 29.0f),
			listed_group_left_side,
			nullptr,
			""
		);
		d_container->input_field = input_field;

		ELocalisationText ltext = ELocalisationText();
		ltext.localisations[NSW_localisation_EN] = "condition";
		ltext.localisations[NSW_localisation_RU] = "�������";

		input_field->main_text_area->gray_text = ltext;

		listed_group_left_side->button_list.push_back(input_field);
	}
	////////////////////////////////////////////////


	////////////////////////
	//MAIN SECTION
	EButtonGroup*
		listed_group_main_section = EButtonGroup::create_button_group_without_bg(new ERegionGabarite(600.0f, 80.0f), EGUIStyle::active_style)
		->
		set_parameters
		(
			ChildAlignMode::ALIGN_HORIZONTAL,
			NSW_dynamic_autosize,
			NSW_dynamic_autosize
		);

	if (_attribute != nullptr)
	{
		listed_group_main_section->button_size_x_override = _attribute->button_x_size_override;
	}
	else
	{
		listed_group_main_section->button_size_x_override = 200.0f;
	}

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

	float rescale_factor = min((box_size_x * font_size_rescale) / (float)(example_text_texture[0]->size_x_in_pixels + 6.0f), (region_gabarite->size_y * font_size_rescale) / (float)(example_text_texture[0]->size_y_in_pixels + 6.0f));
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
	if (pointer_to_filter_block_group->color_check[0])
	{
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
	}

	float box_x = pos_x;
	float box_y = pos_y;


	//		PREVIEW BACKGROUND
	if (pointer_to_filter_block_group->color_check[0])
	{
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
	}

	//		PREVIEW TEXT
	if (pointer_to_filter_block_group->color_check[1])
	{
		NS_EGraphicCore::set_active_color(*d_con->pointer_to_HRA_color[1]);
		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			pos_x + (box_size_x * font_size_rescale - example_text_texture[0]->size_x_in_pixels * rescale_factor) / 2.0f,

			//y pos
			pos_y + (region_gabarite->size_y * font_size_rescale - example_text_texture[0]->size_y_in_pixels * rescale_factor) / 2.0f - 1.0f * font_size_rescale,

			example_text_texture[0]->size_x_in_pixels * rescale_factor,
			example_text_texture[0]->size_y_in_pixels * rescale_factor,

			example_text_texture[array_id]
		);
	}

	//		PREVIEW RAMA
	if (pointer_to_filter_block_group->color_check[2])
	{
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
	}




	//		MINIMAP ICON PREVIEW
	if (pointer_to_filter_block_group->minimap_icon_color_suppressor_bool)
	{
		EntityButtonVariantRouter* shape_router_button = pointer_to_filter_block_group->pointer_to_minimap_icon_shape_router;
		RouterVariant* shape_router = (shape_router_button->router_variant_list[shape_router_button->selected_variant]);


		EntityButtonVariantRouter* color_router_button = pointer_to_filter_block_group->pointer_to_minimap_icon_color_router;
		RouterVariant* color_router = (color_router_button->router_variant_list[color_router_button->selected_variant]);


		EntityButtonVariantRouter* size_router_button = pointer_to_filter_block_group->pointer_to_minimap_icon_size_router;



		rescale_factor = pointer_to_filter_block_group->pointer_to_top_control_block->region_gabarite->size_y / (float)(shape_router->texture->size_y_in_pixels);

		rescale_factor *= 1.0f - 0.25f * size_router_button->selected_variant;

		rescale_factor = max(rescale_factor, 0.25f);
		rescale_factor = min(rescale_factor, 1.0f);

		float shape_x_size = shape_router->texture->size_x_in_pixels * rescale_factor;

		NS_EGraphicCore::set_active_color(color_router->color);
		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			box_x - shape_x_size - 1.0f,

			//y pos
			box_y,

			shape_x_size,
			shape_router->texture->size_y_in_pixels * rescale_factor,

			shape_router->texture
		);
	}

	pos_x = pointer_to_filter_block_group->pointer_to_ray_preview_segment->region_gabarite->world_position_x;
	pos_x += (pointer_to_filter_block_group->pointer_to_ray_preview_segment->region_gabarite->size_x - NS_DefaultGabarites::texture_ray->size_x_in_pixels) / 2.0f;

	pos_y = pointer_to_filter_block_group->pointer_to_ray_preview_segment->region_gabarite->world_position_y;

	if (pointer_to_filter_block_group->ray_suppressor)
	{
		EntityButtonVariantRouter* ray_color_router = pointer_to_filter_block_group->pointer_to_ray_color_router;

		NS_EGraphicCore::set_active_color(ray_color_router->router_variant_list[ray_color_router->selected_variant]->color);

		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			pos_x,

			//y pos
			pos_y,

			NS_DefaultGabarites::texture_ray->size_x_in_pixels,
			NS_DefaultGabarites::texture_ray->size_y_in_pixels,


			NS_DefaultGabarites::texture_ray
		);
	}
	//std::cout << "!";
}

EButtonGroupFilterBlock::~EButtonGroupFilterBlock()
{
}

void EButtonGroupFilterBlock::post_draw()
{
	if
		(
			(is_visible())
			&&
			(can_see_this_group())
			)
	{
		EButtonGroup::post_draw();


		if (button_show_hide->selected_variant == 0)
		{
			if (!EButtonGroup::catched_by_mouse(this))
			{
				NS_EGraphicCore::set_active_color(0.3f, 0.25f, 0.2f, 0.6f);
			}
			else
			{
				NS_EGraphicCore::set_active_color(0.3f, 0.3f, 0.3f, 0.3f);
			}
			ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
				NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

				//x pos
				region_gabarite->world_position_x,

				//y pos
				region_gabarite->world_position_y,

				region_gabarite->size_x,
				region_gabarite->size_y,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}
	}

}

void EButtonGroupFilterBlock::update(float _d)
{
	EButtonGroup::update(_d);

	//if (EButtonGroup::catched_by_mouse(this))
	//{
	//	if (!pointer_to_top_control_block->is_active)
	//	{
	//		pointer_to_top_control_block->is_active = true;
	//		pointer_to_top_control_block->group_phantom_redraw = true;

	//		//change_group(pointer_to_top_control_block);
	//	}
	//}
	//else
	//{
	//	if (pointer_to_top_control_block->is_active)
	//	{
	//		pointer_to_top_control_block->is_active = false;
	//		pointer_to_top_control_block->group_phantom_redraw = true;
	//		//change_group(pointer_to_top_control_block);
	//	}
	//};
}

void EButtonGroupFilterBlock::button_group_prechange()
{
}

bool EButtonGroupFilterBlock::is_visible()
{
	//if (EButtonGroup::is_visible() && is_expanded && false)
	//{
	//	EInputCore::logger_simple_info("You are ebanutyi? YES");
	//}
	//else
	//{
	//	EInputCore::logger_simple_info("You are ebanutyi? NO");
	//}

	return EButtonGroup::is_visible() && (is_expanded || group_search_status == GroupSearchStatus::SEARCH_STATUS_MATCHED);
}

EButtonGroupFilterBlockAsText* EButtonGroupFilterBlockAsText::create_filter_block_as_text_group(EButtonGroupFilterBlock* _target_filter_block)
{
	//EButtonGroupFilterBlockAsText*
	//jc_FBaT_group = new EButtonGroupFilterBlockAsText(new ERegionGabarite(800.0f, 500.0f));
	//jc_FBaT_group->init_button_group(EGUIStyle::active_style, true, true, false);
	//jc_FBaT_group->set_parameters(ChildAlignMode::ALIGN_VERTICAL, NSW_dynamic_autosize, NSW_dynamic_autosize);
	//jc_FBaT_group->root_group = jc_FBaT_group;


	//EButtonGroupjc_FBaT_group->add_close_group_and_return_workspace_group(new ERegionGabarite(800.0f, 20.0f), EGUIStyle::active_style);

	//_target_filter_block

	return nullptr;
}

void EButtonGroupSoundList::refresh_sound_list()
{

	for (int i = 0; i < part_with_list->button_list.size(); i++)
	{
		EntityButton* but = part_with_list->button_list[i];

		if (but != part_with_list->slider)
		{

			delete but;

			part_with_list->button_list.erase(part_with_list->button_list.begin() + i);

			i--;
		}
	}

	if (pointer_to_sound_list != nullptr)
	{
		for (ENamedSound* n_sound : *pointer_to_sound_list)
		{
			EntityButtonFilterSound* sound_button = new EntityButtonFilterSound();
			sound_button->make_default_button_with_unedible_text
			(
				new ERegionGabarite(325.0f, 32.0f),
				part_with_list,
				&EDataActionCollection::action_invoke_button_action_in_sound_group,
				n_sound->localisation_text.localisations[ELocalisationText::active_localisation]
			);

			sound_button->main_text_area->localisation_text = n_sound->localisation_text;
			sound_button->full_path = n_sound->full_path;
			sound_button->stored_named_sound = n_sound;
			sound_button->target_sound_group = EButtonGroup::sound_list_group;

			Entity::get_last_clickable_area(sound_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_play_attached_sound);

			part_with_list->button_list.push_back(sound_button);
		}
	}
	else
	{
		EInputCore::logger_simple_error("pointer to sound list is NULL!");
	}
}

EntityButtonVariantRouterForFilterBlock::~EntityButtonVariantRouterForFilterBlock()
{
}

EntityButtonFilterSound::~EntityButtonFilterSound()
{
	//ESound::engine->removeSoundSource(stored_named_sound->sound);
}

EntityButtonForListedSegment::EntityButtonForListedSegment()
{
}

EntityButtonForListedSegment::~EntityButtonForListedSegment()
{
}

void EButtonGroupDataEntity::update(float _d)
{
	EButtonGroup::update(_d);

	//if
	//(
	//	(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom >= right_side_for_filters->region_gabarite->world_position_x)
	//	&&
	//	(focused_part != right_side_for_filters)
	//)
	//{
	//	focused_part = right_side_for_filters;
	//	right_side_for_filters->base_width		= 500.0f;

	//	main_left_side->scroll_y = 0.0f;
	//	EButtonGroup::refresh_button_group(this);

	//	//EInputCore::logger_simple_info("1");
	//}
	//else
	//if
	//	(
	//		(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom < right_side_for_filters->region_gabarite->world_position_x)
	//		&&
	//		(focused_part != main_left_side)
	//	)
	//{
	//	focused_part = main_left_side;
	//	right_side_for_filters->base_width = 250.0f;
	//	
	//	main_left_side->scroll_y = 0.0f;
	//	//scroll_y = 0.0f;
	//	EButtonGroup::refresh_button_group(this);
	//	//EInputCore::logger_simple_info("2");
	//}

}

void EButtonGroupDataEntity::background_update(float _d)
{
	EButtonGroup::background_update(_d);

	//buttons for data entity
	unsigned int counter = 0;
	for (int i = 0; i < 50; i++)
		if (data_entity_id < EDataEntity::data_entity_global_list.size())
		{
			EntityButton* jc_button = EntityButton::create_wide_item_button
			(
				new ERegionGabarite(300.0f, 60.0f),
				main_left_side,
				EDataEntity::data_entity_global_list[data_entity_id],
				EFont::font_list[0]
			);

			main_left_side->button_list.push_back(jc_button);

			//counter++;


			data_entity_id++;

			if (data_entity_id >= EDataEntity::data_entity_global_list.size())
			{

				//EButtonGroup::refresh_button_group(EWindowMain::data_entity_filter);
				EDataActionCollection::action_type_search_data_entity_text(main_input_field->main_text_area);
				EButtonGroup::refresh_button_group(this);


				EInputCore::logger_simple_info("autorefresh!");
			}
		}



}

void EButtonGroupFilterBlockEditor::button_group_prechange()
{
	bool								last_separator_state = true;
	EButtonGroupFilterBlockSeparator* last_separator = nullptr;

	for (int i = 0; i < group_list.size(); i++)
	{
		EButtonGroupFilterBlock* filter_block = static_cast<EButtonGroupFilterBlock*>(group_list[i]);

		//		IF SEPARATOR
		if (EButtonGroupFilterBlockSeparator* block = dynamic_cast<EButtonGroupFilterBlockSeparator*>(group_list[i]))
		{
			last_separator = dynamic_cast<EButtonGroupFilterBlockSeparator*>(group_list[i]);
			last_separator_state = last_separator->is_expanded;
		}
		else if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(group_list[i]))
		{

			filter_block->is_expanded = last_separator_state;
			filter_block->attached_separator = last_separator;
			//filter_block->disable_gabarite = filter_block->disable_gabarite || !filter_block->is_expanded;
			//filter_block->disable_gabarite = !is_visible();
		}
	}
}

EButtonGroupFilterBlockSeparator::~EButtonGroupFilterBlockSeparator()
{
}

EntityButtonLootItem::EntityButtonLootItem()
{
}

EntityButtonLootItem::~EntityButtonLootItem()
{
}

void EntityButtonLootItem::get_matched_filter_blocks()
{
}

GameAttributeGenerator::GameAttributeGenerator(std::string _attribute_name)
{
	target_attribute = GameItemAttribute::get_attribute_by_name(&registered_game_item_attributes, _attribute_name);
}

void GameAttributeGenerator::execute_generation(EGameItem* _game_item)
{
	_game_item->attribute_container_list.push_back(*target_attribute_container);
}




void GameAttributeGeneratorMinMaxInt::execute_generation(EGameItem* _game_item)
{
	int generated_value = min_value + round((max_value - min_value) * pow((rand() % 101) / 100.0f, generator_pow));

	target_attribute_container->attribute_value_int = generated_value;

	//GameAttributeGenerator::execute_generation(_game_item);

}

GameItemGenerator::GameItemGenerator()
{
}

void GameItemGenerator::generate_game_item_list(std::vector<EGameItem*>* _target_list)
{
	if (_target_list != nullptr)
	{



		std::vector<EDataEntity*>*
			target_data_entity_list_for_game_item = &EDataEntity::data_entity_global_list;







		EGameItem*
			game_item = nullptr;

		if (filtered_by_exact_name.base_name != "")
		{

			//try search data entity by exact match
			for (DataEntityNamedStruct* named_struct : EDataEntity::data_entity_named_structs)
			{
				int
					index = EStringUtils::hashFunction(filtered_by_exact_name.base_name) & 0x000000000000000F;
				index = min(index, 15);
				index = max(index, 0);

				//arr[index]++;
				if (named_struct->name == "Game item") { target_data_entity_list_for_game_item = &named_struct->data_entity_list[index]; break; }
			}

			for (EDataEntity* de : *target_data_entity_list_for_game_item)
			{
				if
					(
						(
							(DataEntityUtils::get_tag_value_by_name(0, "name EN", de) == filtered_by_exact_name.localisations[NSW_localisation_EN])
							||
							(DataEntityUtils::get_tag_value_by_name(0, "base name", de) == filtered_by_exact_name.base_name)
							)
						&&
						(EFilterRule::matched_by_filter_rule(de, EFilterRule::registered_global_filter_rules[RegisteredFilterRules::FILTER_RULE_OBTAINABLE_GAME_ITEM], ""))
						)
				{
					for (int i = 0; i < generations_count; i++)
					{
						game_item = new EGameItem();
						game_item->stored_data_entity = de;
						_target_list->push_back(game_item);
					}

					break;
				}


			}



			for (int i = 0; i < generations_count; i++)
			{
				game_item = new EGameItem();

				_target_list->push_back(game_item);
			}
		}
		else
		{
			DataEntityNamedStruct* target_named_struct = nullptr;
			std::vector<EDataEntity*> generated_suitable_data_entity_item_vector;

			for (DataEntityNamedStruct* named_struct : EDataEntity::data_entity_named_structs)
			{
				if (named_struct->name == "Game item") { target_named_struct = named_struct; break; }
			}

			if (!filtered_by_tags.empty())
			{

				for (int i = 0; i < 16; i++)
				{
					target_data_entity_list_for_game_item = &target_named_struct->data_entity_list[i];

					for (EDataEntity* data_entity : *target_data_entity_list_for_game_item)
					{
						bool all_tag_filter_satisfied = true;
						bool any_banned_tag_match = false;

						for (LootSimulatorTagFilter* tag_filter : filtered_by_tags)
							if (all_tag_filter_satisfied)
							{
								if (!tag_filter->suitable_values.empty())
								{
									all_tag_filter_satisfied = false;
									for (std::string required_tag_value : tag_filter->suitable_values)
									{
										if (DataEntityUtils::is_exist_tag_by_name_and_value(0, tag_filter->target_tag, required_tag_value, data_entity))
										{
											all_tag_filter_satisfied = true;
											break;
										}

										//if (!all_tag_filter_satisfied) { break; }
									}
								}

								//if (!all_tag_filter_satisfied) { break; }
								for (std::string banned_tag_value : tag_filter->banned_tags)
									if (DataEntityUtils::is_exist_tag_by_name_and_value(0, tag_filter->target_tag, banned_tag_value, data_entity))
									{
										any_banned_tag_match = true;
										break;
									}
							}

						if ((all_tag_filter_satisfied) && (!any_banned_tag_match))
						{
							generated_suitable_data_entity_item_vector.push_back(data_entity);
						}
					}
				}
			}

			//transfer FROM generated items vector TO global items vector

			if (generator_mode == GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_ALL)
			{
				for (EDataEntity* de : generated_suitable_data_entity_item_vector)
				{
					for (int i = 0; i < generations_count; i++)
					{
						game_item = new EGameItem();
						game_item->stored_data_entity = de;
						_target_list->push_back(game_item);
					}
					//_target_list->insert(_target_list->end(), temp_game_item_vector.begin(), temp_game_item_vector.end());
				}
			}
			else
				if ((generator_mode == GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT) || (generator_mode == GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE))
				{
					for (int i = 0; i < random_selection_count; i++)
						if (!generated_suitable_data_entity_item_vector.empty())
						{
							int random_element = rand() % generated_suitable_data_entity_item_vector.size();
							for (int i = 0; i < generations_count; i++)
							{
								game_item = new EGameItem();
								game_item->stored_data_entity = generated_suitable_data_entity_item_vector[random_element];
								_target_list->push_back(game_item);
							}

							if (generator_mode == GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE)
							{
								generated_suitable_data_entity_item_vector.erase(generated_suitable_data_entity_item_vector.begin() + random_element);
							}
						}
				}


		}





		//game_item->localised_name.base_name = 







		//return game_item;
	}
}

void GameItemGenerator::init_game_item(EGameItem* _game_item)
{
	//automatic generate basic attributes
	if (_game_item->stored_data_entity != nullptr)
	{


		if (_game_item != nullptr)
		{
			_game_item->localised_name.base_name = DataEntityUtils::get_tag_value_by_name(0, "base name", _game_item->stored_data_entity);

			if (_game_item->localised_name.base_name == "")
			{
				_game_item->localised_name.base_name = DataEntityUtils::get_tag_value_by_name(0, "name EN", _game_item->stored_data_entity);
			}

			_game_item->localised_name.localisations[NSW_localisation_EN] = DataEntityUtils::get_tag_value_by_name(0, "name EN", _game_item->stored_data_entity);
			_game_item->localised_name.localisations[NSW_localisation_RU] = DataEntityUtils::get_tag_value_by_name(0, "name RU", _game_item->stored_data_entity);
		}
		else
		{
			//game_item = new EGameItem();
		}



		//default attributes [BASE CLASS]
		if (DataEntityUtils::get_tag_value_by_name(0, "base class", _game_item->stored_data_entity) != "")
		{
			std::string
				raw_class_name_in_item = DataEntityUtils::get_tag_value_by_name(0, "base class", _game_item->stored_data_entity);

			//try search data entity by exact match
			std::vector<EDataEntity*>*
				target_data_entity_list_for_class = &EDataEntity::data_entity_global_list;

			for (DataEntityNamedStruct* named_struct : EDataEntity::data_entity_named_structs)
			{
				if (named_struct->name == "Base Class")
				{
					int
						index = EStringUtils::hashFunction(raw_class_name_in_item) & 0x000000000000000F;
					index = min(index, 15);
					index = max(index, 0);

					target_data_entity_list_for_class = &named_struct->data_entity_list[index];

					break;
				}
			}
			ELocalisationText l_text;

			bool suitable_data_entity_searched = false;
			for (EDataEntity* d_entity : *target_data_entity_list_for_class)
			{
				//try get base name
				std::string
					class_base_name = DataEntityUtils::get_tag_value_by_name(0, "base name", d_entity);

				std::string
					class_EN_name = DataEntityUtils::get_tag_value_by_name(0, "name EN", d_entity);

				std::string
					class_RU_name = DataEntityUtils::get_tag_value_by_name(0, "name RU", d_entity);

				//use EN name instead
				if (class_base_name == "") { class_base_name = class_EN_name; }

				if (class_base_name == raw_class_name_in_item)
				{
					l_text.base_name = class_base_name;
					l_text.localisations[NSW_localisation_EN] = class_EN_name;
					l_text.localisations[NSW_localisation_RU] = class_RU_name;

					suitable_data_entity_searched = true;
					break;
				}
			}

			if (!suitable_data_entity_searched)
			{
				l_text.base_name = raw_class_name_in_item;
				l_text.localisations[NSW_localisation_EN] = raw_class_name_in_item;
				l_text.localisations[NSW_localisation_RU] = raw_class_name_in_item;
			}

			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_BASE_CLASS];
			//attribute_container.attribute_value_str = DataEntityUtils::get_tag_value_by_name(0, "base class", _game_item->stored_data_entity);

			attribute_container.listed_value_list.push_back(l_text);

			_game_item->attribute_container_list.push_back(attribute_container);

			//EInputCore::logger_param("width", attribute_container.attribute_value);
		}

		//default attributes [BASE TYPE]
		if (_game_item->localised_name.base_name != "")
		{
			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_BASE_TYPE];
			//attribute_container.attribute_value_str = game_item->localised_name.base_name;
			attribute_container.listed_value_list.push_back(_game_item->localised_name);

			_game_item->attribute_container_list.push_back(attribute_container);
		}

		//default attributes [HEIGHT]
		if (DataEntityUtils::get_tag_value_by_name(0, "item height", _game_item->stored_data_entity) != "")
		{
			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_HEIGHT];
			attribute_container.attribute_value_int = std::stoi(DataEntityUtils::get_tag_value_by_name(0, "item height", _game_item->stored_data_entity));

			_game_item->attribute_container_list.push_back(attribute_container);

			//EInputCore::logger_param("height", attribute_container.attribute_value);
		}

		//default attributes [WIDTH]
		if (DataEntityUtils::get_tag_value_by_name(0, "item width", _game_item->stored_data_entity) != "")
		{
			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_WIDTH];
			attribute_container.attribute_value_int = std::stoi(DataEntityUtils::get_tag_value_by_name(0, "item width", _game_item->stored_data_entity));

			_game_item->attribute_container_list.push_back(attribute_container);

			//EInputCore::logger_param("width", attribute_container.attribute_value);
		}

	}
	else//undefined item
	{

		{
			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_BASE_TYPE];
			//attribute_container.attribute_value_str = game_item->localised_name.base_name;
			ELocalisationText l_text;

			l_text.base_name = filtered_by_exact_name.base_name;

			l_text.localisations[NSW_localisation_EN] = filtered_by_exact_name.localisations[NSW_localisation_EN];
			if (l_text.localisations[NSW_localisation_EN] == "") { l_text.localisations[NSW_localisation_EN] = filtered_by_exact_name.base_name; }

			l_text.localisations[NSW_localisation_RU] = filtered_by_exact_name.localisations[NSW_localisation_RU];
			if (l_text.localisations[NSW_localisation_RU] == "") { l_text.localisations[NSW_localisation_RU] = filtered_by_exact_name.base_name; }



			attribute_container.listed_value_list.push_back(l_text);

			_game_item->attribute_container_list.push_back(attribute_container);


			_game_item->localised_name = l_text;
		}

		{
			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::get_attribute_by_name(&registered_game_item_attributes, "DropLevel");
			attribute_container.attribute_value_int = 1;

			_game_item->attribute_container_list.push_back(attribute_container);
		}

		{
			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_HEIGHT];
			attribute_container.attribute_value_int = 1;

			_game_item->attribute_container_list.push_back(attribute_container);
		}



		{
			EGameItemAttributeContainer
				attribute_container;

			attribute_container.target_attribute = GameItemAttribute::default_game_attribute[DefaultGameAttributeEnum::GAME_ATTRIBUTE_WIDTH];
			attribute_container.attribute_value_int = 1;

			_game_item->attribute_container_list.push_back(attribute_container);
		}
	}

	for (GameAttributeGenerator* a_generator : attribute_generators_list)
		if
			(
				(a_generator->target_attribute != nullptr)
				&&
				(rand() % 100 < (int)(a_generator->chance_to_generate * 100.0f))
				)
		{
			EGameItemAttributeContainer
				attribute_container;

			a_generator->target_attribute_container = &attribute_container;
			a_generator->execute_generation(_game_item);

			attribute_container.target_attribute = a_generator->target_attribute;
			_game_item->attribute_container_list.push_back(attribute_container);
		}
		else
		{
			EInputCore::logger_simple_error("Cannot work with attribute container with NULL atrribute!");
		}
}

void GameItemGenerator::add_rarity(int _rarity_min, int _rarity_max, float _pow)
{
	//		value
	GameAttributeGeneratorRarity*
		value_generator = new GameAttributeGeneratorRarity("Rarity");

	//		parameters
	value_generator->min_value = _rarity_min;
	value_generator->max_value = _rarity_max;
	value_generator->generator_pow = _pow;

	attribute_generators_list.push_back(value_generator);
}

void GameItemGenerator::add_item_level(int _level_min, int _level_max, float _pow)
{
}

void GameAttributeGeneratorSocketsLinksColours::execute_generation(EGameItem* _game_item)
{
	std::string temp_socket_color_names = "RGBWAD";

	int exactly_color_count[6]{ 0 };
	//int color_id_array[6]		{ 0 };

	int total_weight = 0;

	int sockets_count = sockets_min_value + round((float)(sockets_max_value - sockets_min_value) * pow((rand() % 101) / 100.0f, sockets_pow));
	int links_count = links_min + round((float)(links_max - links_min) * pow((rand() % 101) / 100.0f, links_pow));

	std::string sockets_result_string = "";
	std::string links_result_string = "";

	links_count = min(links_count, sockets_count);
	if (links_count == 1) { links_count = 0; }

	for (int i = 0; i < 6; i++)
	{
		total_weight += color_weight[i];
	}

	int random_selected = 0;

	int weight_sum = 0;

	int result_color_id = -1;

	for (int sc = 0; sc < sockets_count; sc++)
	{
		random_selected = rand() % total_weight + 1;
		weight_sum = 0;
		result_color_id = 0;

		for (int i = 0; i < 6; i++)
		{
			if
				(
					(color_weight[i] > 0)
					&&
					(weight_sum <= random_selected)
					&&
					(color_weight[i] + weight_sum > random_selected)
					)
			{
				result_color_id = i;
				break;
			}

			weight_sum += color_weight[i];
		}

		//color_id_array[sc] = result_color_id;

		_game_item->socket_color_id_array[sc] = result_color_id;
	}

	_game_item->sockets_count = sockets_count;
	_game_item->links_count = links_count;

	sockets_result_string = std::to_string(sockets_count);
	links_result_string = std::to_string(links_count);

	//		GENERATE COLOR SOCKETS STRING LIKE "RRRGGB"
	for (int i = 0; i < 6; i++) { exactly_color_count[i] = 0; }

	for (int i = 0; i < sockets_count; i++)
	{
		exactly_color_count[_game_item->socket_color_id_array[i]]++;
	};

	for (int i = 0; i < 6; i++)
		if (exactly_color_count[i] > 0)
			for (int j = 0; j < exactly_color_count[i]; j++)
			{
				sockets_result_string.append(1, temp_socket_color_names[i]);
			}

	//		GENERATE COLOR LINKS STRING LIKE "RRRGGB"
	for (int i = 0; i < 6; i++) { exactly_color_count[i] = 0; }

	for (int i = 0; i < links_count; i++)
	{
		exactly_color_count[_game_item->socket_color_id_array[i]]++;
	};

	for (int i = 0; i < 6; i++)
		if (exactly_color_count[i] > 0)
			for (int j = 0; j < exactly_color_count[i]; j++)
			{
				links_result_string.append(1, temp_socket_color_names[i]);
			}


	//		GENERATE NEW ATTRIBUTE FOR SOCKETS OR LINKS
	{
		EGameItemAttributeContainer
			new_attribute_container;

		if (target_attribute->localisation.base_name == "Sockets")
		{
			target_attribute_container->attribute_value_str = sockets_result_string;

			new_attribute_container.target_attribute = GameItemAttribute::get_attribute_by_name(&registered_game_item_attributes, "SocketGroup");
			new_attribute_container.attribute_value_str = links_result_string;
		}
		else
			if (target_attribute->localisation.base_name == "SocketGroup")
			{
				target_attribute_container->attribute_value_str = links_result_string;

				new_attribute_container.target_attribute = GameItemAttribute::get_attribute_by_name(&registered_game_item_attributes, "Sockets");
				new_attribute_container.attribute_value_str = sockets_result_string;
			}
		_game_item->attribute_container_list.push_back(new_attribute_container);
	}

	EGameItemAttributeContainer
		new_attribute_container;

	new_attribute_container.target_attribute = GameItemAttribute::get_attribute_by_name(&registered_game_item_attributes, "LinkedSockets");
	new_attribute_container.attribute_value_int = links_count;
	_game_item->attribute_container_list.push_back(new_attribute_container);
}

void EGameItem::import_base_attributes_from_data_entity()
{
	if (stored_data_entity != nullptr)
	{

	}
}

void EntityButtonLootItem::get_matched_filter_blocks_list(EButtonGroupFilterBlockEditor* _filter_block_editor)
{
	bool break_detect = false;

	for (EButtonGroup* group : _filter_block_editor->group_list)
	{

		if (EButtonGroupFilterBlock* block = dynamic_cast<EButtonGroupFilterBlock*>(group))//filter block
		{
			EButtonGroupFilterBlock*
				filter_block = static_cast<EButtonGroupFilterBlock*>(group);

			if (EButtonGroupLootSimulator::this_group_is_matched(stored_game_item, filter_block))
			{


				matched_filter_blocks.push_back(filter_block);

				if (filter_block->color_check[0])
				{
					matched_bg_color = &filter_block->pointer_to_color_button[0]->stored_color;
					matched_bg_color_block = filter_block;
				}

				if (filter_block->color_check[1])
				{

					matched_text_color = &filter_block->pointer_to_color_button[1]->stored_color;

					main_text_area->set_color(filter_block->pointer_to_color_button[1]->stored_color);
					matched_text_color_block = filter_block;
				}

				if (filter_block->color_check[2])
				{
					matched_rama_color = &filter_block->pointer_to_color_button[2]->stored_color;
					matched_rama_color_block = filter_block;
				}

				if (filter_block->text_size_bool)
				{
					matched_size = &filter_block->text_size;
					matched_size_block = filter_block;
				}

				//if not continue
				if (filter_block->button_continue->selected_variant != 0)
				{
					break_detect = true;
				}

				if (filter_block->minimap_icon_color_suppressor_bool)
				{
					matched_minimap_icon_color = filter_block->pointer_to_minimap_icon_color_router;
					matched_minimap_icon_shape = filter_block->pointer_to_minimap_icon_shape_router;
					matched_minimap_icon_size = filter_block->pointer_to_minimap_icon_size_router;

					matched_minimap_icon_color_block = filter_block;
					matched_minimap_icon_shape_block = filter_block;
					matched_minimap_icon_size_block = filter_block;
				}
			}
		}

		if (break_detect) { break; }
	}
}



LootSimulatorPattern::LootSimulatorPattern()
{
}

void LootSimulatorPattern::refresh_loot_simulator(LootSimulatorPattern* _pattern)
{
	//srand(time(NULL));
	srand(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

	for (int i = 0; i < EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->button_list.size(); i++)
		if (EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->button_list[i] != EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->slider)
		{
			delete EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->button_list[i];
			EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->button_list.erase(EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->button_list.begin() + i);
			i--;
		}

	for (int i = 0; i < _pattern->game_item_generator_list.size(); i++)
	{
		std::vector<EGameItem*> game_item_vector;

		_pattern->game_item_generator_list[i]->generate_game_item_list(&game_item_vector);


		//EInputCore::logger_param("WTF", game_item->attribute_container_list[0].target_attribute->localisation.base_name);

		for (EGameItem* game_item : game_item_vector)
		{
			_pattern->game_item_generator_list[i]->init_game_item(game_item);

			EntityButtonLootItem*
				loot_item = new EntityButtonLootItem();
			loot_item->align_even_if_hidden = true;
			loot_item->do_not_generate_bg = true;



			loot_item->stored_game_item = game_item;





			std::string item_name = game_item->localised_name.localisations[ELocalisationText::active_localisation];
			if (game_item->quantity > 1) { item_name += " x" + std::to_string(game_item->quantity); }

			loot_item->make_default_button_with_unedible_text
			(
				new ERegionGabarite(512.0f, 40.0f),
				EButtonGroupLootSimulator::pointer_to_loot_buttons_segment,
				&EDataActionCollection::action_highlight_matched_blocks,
				item_name
			);

			loot_item->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_create_or_delete_description_on_hover);


			loot_item->get_matched_filter_blocks_list(EWindowMain::loot_filter_editor);

			//float size_multiplier = *loot_item->matched_size;



			loot_item->main_custom_data->actions_on_pre_draw.push_back(EDataActionCollection::action_draw_loot_button);
			EButtonGroupLootSimulator::show_hidden = true;

			//loot_item->disable_draw =
			//(
			//	(loot_item->matched_filter_blocks.empty())
			//	&&
			//	(
			//		(loot_item->matched_filter_blocks.back()->button_show_hide->selected_variant == 1)
			//		&&
			//		(loot_item->matched_filter_blocks.back()->version_routers[EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button->selected_variant]->selected_variant != 1)
			//	)
			//	||
			//	(EButtonGroupLootSimulator::show_hidden)
			//);



			EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->button_list.push_back(loot_item);
		}
	}

	std::vector<EButtonGroupFilterBlock*> filter_block_vector;



	EButtonGroupLootSimulator::refresh_button_sizes();
	EButtonGroup::refresh_button_group(EWindowMain::loot_simulator_button_group);
}


void EButtonGroupLootSimulator::refresh_button_sizes()
{
	for (EntityButton* but : EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->button_list)
		if (but != EButtonGroupLootSimulator::pointer_to_loot_buttons_segment->slider)
		{
			EntityButtonLootItem* loot_item = static_cast<EntityButtonLootItem*>(but);

			float size_multiplier = 0.5f;

			if (loot_item->matched_size != nullptr) { size_multiplier = *loot_item->matched_size; }

			if (loot_item->matched_size_block != nullptr)
			{
				if
					(
						(loot_item->matched_size_block->version_routers[EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button->selected_variant]->selected_variant == 1)
						||
						(loot_item->matched_size_block->version_routers[EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button->selected_variant]->selected_variant == 2)
						)
				{
					size_multiplier *= 0.6f;
				}
				else
					if (loot_item->matched_size_block->version_routers[EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button->selected_variant]->selected_variant == 4)
					{
						size_multiplier *= 1.5f;
					}
			}

			size_multiplier = min(size_multiplier, 1.0f);

			loot_item->main_text_area->font = EFont::font_list[1];
			loot_item->main_text_area->font_scale = (0.35f + size_multiplier * 0.65f);

			loot_item->button_gabarite->size_x = loot_item->main_text_area->get_text_width(&loot_item->main_text_area->original_text) * (0.35f + size_multiplier * 0.65f) * 1.35f;
			loot_item->button_gabarite->size_y = 30.0f * (0.35f + size_multiplier * 0.65f);

			loot_item->button_gabarite->size_x = max(loot_item->button_gabarite->size_x, 100.0f);
			loot_item->button_gabarite->size_y = max(loot_item->button_gabarite->size_y, 15.0f);

			loot_item->main_text_area->change_text(loot_item->main_text_area->original_text);
		}
}

std::vector<LootSimulatorPattern*>	LootSimulatorPattern::registered_loot_simulater_pattern_list;

GameItemAttribute* GameItemAttribute::get_attribute_by_name(std::vector<GameItemAttribute*>* _vector, std::string _name)
{
	for (GameItemAttribute* game_attribute : *_vector)
	{
		if (EStringUtils::compare_ignoring_case(game_attribute->localisation.base_name, _name))
		{
			//EInputCore::logger_param("matched attribute", game_attribute->localisation.base_name);
			//EInputCore::logger_param("required attribute", _name);
			return game_attribute;
		}
	}

	EInputCore::logger_simple_error("Attribute with name [" + _name + "] not exist!");
	return nullptr;
}

void GameAttributeGeneratorQuantity::execute_generation(EGameItem* _game_item)
{
	GameAttributeGeneratorMinMaxInt::execute_generation(_game_item);

	_game_item->quantity = target_attribute_container->attribute_value_int;



}

//STATIC FIELDS FOR EButtonGroupLootSimulator
bool						EButtonGroupLootSimulator::show_hidden = false;
//float						EButtonGroupLootSimulator::show_hidden_cooldown = 0.5f;
HSVRGBAColor		EButtonGroupLootSimulator::temp_color;

EButtonGroup* EButtonGroupLootSimulator::pointer_to_loot_buttons_segment;
EButtonGroup* EButtonGroupLootSimulator::pointer_to_patterns_buttons_segment;

EntityButtonVariantRouter* EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button;
EntityButton* EButtonGroupLootSimulator::pointer_to_input_area_level_button;





bool EButtonGroupLootSimulator::this_group_is_matched(EGameItem* _game_item, EButtonGroupFilterBlock* _filter_block)
{
	bool is_matched = true;

	//for (EGameItemAttributeContainer attribute_container : _game_item->attribute_container_list)
	if (_filter_block->version_routers[EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button->selected_variant]->selected_variant == 0) { return false; }


	{

		//		NON-LISTED lines attributes
		//for each non-listed attribute
		for (EButtonGroup* group : _filter_block->pointer_to_non_listed_segment->group_list)
		{
			EButtonGroupNonListedLine*
				line_group = static_cast<EButtonGroupNonListedLine*>(group);

			GameItemAttribute*
				non_listed_attribute = line_group->target_filter_block_attribute;

			EGameItemAttributeContainer*
				matched_item_attribute_container = nullptr;

			//non-global attribute like AreaLevel
			if (!non_listed_attribute->global_attribute_value)
			{
				// try search matched attribute (between block attribute and item attribute)
				for (int i = 0; i < _game_item->attribute_container_list.size(); i++)
				{
					EGameItemAttributeContainer*
						attr_container = &_game_item->attribute_container_list[i];

					//for (EGameItemAttributeContainer item_attribute : _game_item->attribute_container_list)
					if (attr_container->target_attribute == non_listed_attribute)
					{
						matched_item_attribute_container = attr_container;
						break;
					}
				}


				//if matched atribute exist
				if (matched_item_attribute_container != nullptr)
				{
					//number attrubite
					if
						(
							(matched_item_attribute_container->target_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER)
							&&
							(non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER)
							)
					{
						//have_non_listed_attribute_match = true;


						if
							(
								!is_condition_satisfied
								(
									matched_item_attribute_container->attribute_value_int,								//item
									line_group->target_button_with_condition->main_text_area->original_text,			//operator
									std::stoi(line_group->target_button_with_value->main_text_area->original_text)		//block
								)
								)
						{
							return false;
						}
					}

					//bool attribute
					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER)
					{
						bool bool_match = false;

						//if item have matched attribute, and boll flags not same, return false (block not matched)
						if
							(
								(matched_item_attribute_container->target_attribute == line_group->target_filter_block_attribute)//matched attribute
								&&
								(matched_item_attribute_container->attribute_value_bool != *static_cast<EDataContainer_Button_BoolSwitcher*>(line_group->target_button_with_value->main_custom_data->data_container)->target_value)//bool flags not same
								)
						{
							return false;
						}//suitable attribute exist but condition not satified
					}

					//Rarity
					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST)
					{
						if
							(
								!is_condition_satisfied
								(
									matched_item_attribute_container->attribute_value_int,															//item
									line_group->target_button_with_condition->main_text_area->original_text,										//operator
									line_group->rarity_router_button->selected_variant		//block
								)
								)
						{
							return false;
						}
					}

					//alternate quality
					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST)
					{
						if (!EStringUtils::compare_ignoring_case(matched_item_attribute_container->attribute_value_str, line_group->target_button_with_value->main_text_area->localisation_text.base_name)) { return false; }
					}

					//sockets group
					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_TEXT)
					{

						if
							(
								!is_sockets_matched
								(
									line_group->target_button_with_value->main_text_area->original_text,		//block
									line_group->target_button_with_condition->main_text_area->original_text,	//operator
									matched_item_attribute_container->attribute_value_str						//item
								)
								)
						{
							return false;
						}
					}
				}
				else//"phantom" parameter (non existed parameters have value "0"/"false" (for example, chaos orb dont have attribute "MapTier", but have value "0" for this attribute, and "false" for non existed bool-attributes
				{
					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER)
					{
						if
							(
								!is_condition_satisfied
								(
									0,																				//item
									line_group->target_button_with_condition->main_text_area->original_text,		//operator
									std::stoi(line_group->target_button_with_value->main_text_area->original_text)	//block
								)
								)
						{
							return false;
						}
					}

					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST)
					{
						if
							(
								!is_condition_satisfied
								(
									0,																												//item
									line_group->target_button_with_condition->main_text_area->original_text,										//operator
									line_group->rarity_router_button->selected_variant																//block
								)
								)
						{
							return false;
						}
					}

					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER)
					{
						if (*static_cast<EDataContainer_Button_BoolSwitcher*>(line_group->target_button_with_value->main_custom_data->data_container)->target_value)
						{
							return false;//block require bool-flag for attribute, which item dont have
						}
					}

					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST)
					{
						return false;//if item have no alternative quality, always return false
					}

					if (non_listed_attribute->filter_attribute_value_type == FILTER_ATTRIBUTE_VALUE_TYPE_TEXT)
					{
						if
							(
								!is_sockets_matched
								(
									line_group->target_button_with_value->main_text_area->original_text,		//block
									line_group->target_button_with_condition->main_text_area->original_text,	//operator
									"0"																			//item
								)
								)
						{
							return false;
						}
					}


				}
			}
			else
			{
				if
					(
						(non_listed_attribute->localisation.base_name == "AreaLevel")
						&&
						(
							!is_condition_satisfied
							(
								std::stoi(EButtonGroupLootSimulator::pointer_to_input_area_level_button->main_text_area->original_text),	//blobal parameter "AreaLevel"
								line_group->target_button_with_condition->main_text_area->original_text,									//condition operator
								std::stoi(line_group->target_button_with_value->main_text_area->original_text)								//block value
							)
							)
						)
				{
					return false;
				}
			}

		}

		//		LISTED
		for (EButtonGroup* listed_lines : _filter_block->pointer_to_listed_segment->group_list)
		{
			auto data_container = static_cast<EDataContainer_Group_FilterBlockListedSegment*>(listed_lines->data_container);

			bool this_listed_match = false;

			int listed_match_count = 0;

			//search suitable attribute in item
			for (EGameItemAttributeContainer item_attribute : _game_item->attribute_container_list)
				if
					(
						(
							EStringUtils::compare_ignoring_case
							(
								item_attribute.target_attribute->localisation.base_name,	//item
								data_container->filter_attribute_name						//block
							)
							||
							(false)
							)
						)
				{
					//any_listed_match = true;

					//		FOR EVERY BLOCK ITEM
					for (EntityButton* but : data_container->group_with_listed_buttons->button_list)
						if (but != data_container->group_with_listed_buttons->slider)
							for (ELocalisationText item_listed_value : item_attribute.listed_value_list)
							{
								std::string base_item_name = "";

								EDataContainer_DataEntityHolder*
									data_container_entity = static_cast<EDataContainer_DataEntityHolder*>(but->main_custom_data->data_container);


								//		GET ITEM NAME (FROM FILTER BLOCK)
								if (data_container_entity->stored_data_entity != nullptr)
								{
									base_item_name = DataEntityUtils::get_tag_value_by_name(0, "base name", data_container_entity->stored_data_entity);

									if (base_item_name == "")
									{
										base_item_name = DataEntityUtils::get_tag_value_by_name(0, "name EN", data_container_entity->stored_data_entity);
									}
								}
								else
								{
									base_item_name = but->main_text_area->original_text;
								}




								if
									(
										//		PATRIALLY MATCH
										(
											(data_container->match_mode_router_button != nullptr)
											&&
											(data_container->match_mode_router_button->selected_variant == 0)
											&&
											EStringUtils::A_contains_B_ignore_case
											(
												item_listed_value.base_name,	//item
												base_item_name		//block
											)
											)
										||
										//		EXACT MATCH
										(
											(
												(data_container->match_mode_router_button == nullptr)
												||
												(data_container->match_mode_router_button->selected_variant == 1)
												)
											&&
											(
												item_listed_value.base_name	//item
												==
												base_item_name		//block
												)
											)
										)
								{


									listed_match_count++;

									if (!data_container->associated_item_attribute->have_input_field_for_listed)
									{
										this_listed_match = true;
										break;
									}
								}



							}

					if ((data_container->associated_item_attribute->have_input_field_for_listed) && (data_container->input_field != nullptr))
					{
						std::string input_field_value = ">=1";

						if (data_container->input_field->main_text_area->original_text != "") { input_field_value = data_container->input_field->main_text_area->original_text; }

						if (!is_condition_sactified_for_listed_expression(input_field_value, listed_match_count))
						{
							return false;
						}
						else
						{
							this_listed_match = true;
						}
					}
				}

			if (!this_listed_match) { return false; }
		}
	}

	return true;
	//return is_matched;
}

bool EButtonGroupLootSimulator::is_condition_satisfied(int _left, std::string _operator, int _right)
{
	if ((_operator == "=") && (_left == _right)) { return true; }
	if ((_operator == "==") && (_left == _right)) { return true; }
	if ((_operator == "!") && (_left != _right)) { return true; }

	if ((_operator == ">=") && (_left >= _right)) { return true; }
	if ((_operator == "<=") && (_left <= _right)) { return true; }

	if ((_operator == "<") && (_left < _right)) { return true; }
	if ((_operator == ">") && (_left > _right)) { return true; }

	return false;
}

bool EButtonGroupLootSimulator::is_sockets_matched(std::string _block, std::string _operator, std::string _item)
{
	int sockets_count_block = 0;
	int red_count_block = 0;
	int green_count_block = 0;
	int blue_count_block = 0;
	int white_count_block = 0;
	int abyss_count_block = 0;
	int delve_count_block = 0;

	int sockets_count_item = 0;
	int red_count_item = 0;
	int green_count_item = 0;
	int blue_count_item = 0;
	int white_count_item = 0;
	int abyss_count_item = 0;
	int delve_count_item = 0;

	for (int i = 0; i < _block.length(); i++)
	{

		if
			(
				(_block[i] == '0')
				||
				(_block[i] == '1')
				||
				(_block[i] == '2')
				||
				(_block[i] == '3')
				||
				(_block[i] == '4')
				||
				(_block[i] == '5')
				||
				(_block[i] == '6')
				)
		{
			sockets_count_block = std::stoi(&_block[i]);
		}

		if (_block[i] == 'R') { red_count_block++; }
		if (_block[i] == 'G') { green_count_block++; }
		if (_block[i] == 'B') { blue_count_block++; }
		if (_block[i] == 'W') { white_count_block++; }

		if (_block[i] == 'A') { abyss_count_block++; }
		if (_block[i] == 'D') { delve_count_block++; }
	}

	for (int i = 0; i < _item.length(); i++)
	{

		if
			(
				(_item[i] == '0')
				||
				(_item[i] == '1')
				||
				(_item[i] == '2')
				||
				(_item[i] == '3')
				||
				(_item[i] == '4')
				||
				(_item[i] == '5')
				||
				(_item[i] == '6')
				)
		{
			sockets_count_item = std::stoi(&_item[i]);
		}

		if (_item[i] == 'R') { red_count_item++; }
		if (_item[i] == 'G') { green_count_item++; }
		if (_item[i] == 'B') { blue_count_item++; }
		if (_item[i] == 'W') { white_count_item++; }
		if (_item[i] == 'A') { abyss_count_item++; }
		if (_item[i] == 'D') { delve_count_item++; }
	}

	if (!is_condition_satisfied(sockets_count_item, _operator, sockets_count_block)) { return false; }
	if (!is_condition_satisfied(red_count_item, _operator, red_count_block)) { return false; }
	if (!is_condition_satisfied(green_count_item, _operator, green_count_block)) { return false; }
	if (!is_condition_satisfied(blue_count_item, _operator, blue_count_block)) { return false; }
	if (!is_condition_satisfied(white_count_item, _operator, white_count_block)) { return false; }
	if (!is_condition_satisfied(abyss_count_item, _operator, abyss_count_block)) { return false; }
	if (!is_condition_satisfied(delve_count_item, _operator, delve_count_block)) { return false; }


	return true;
}

void EButtonGroupLootSimulator::refresh_loot_simulator()
{
	if (EWindowMain::loot_simulator_button_group->is_active)
	{
		EInputCore::logger_simple_info("refresh loot simulator");

		EButtonGroupLootSimulator::show_hidden = true;
		//EButtonGroupLootSimulator::show_hidden_cooldown = 0.0f;

		for (EntityButton* button : pointer_to_loot_buttons_segment->button_list)
			if (button != pointer_to_loot_buttons_segment->slider)
			{


				button->disable_draw = false;

				EntityButtonLootItem*
					loot_button = static_cast<EntityButtonLootItem*>(button);

				loot_button->matched_bg_color = nullptr;
				loot_button->matched_bg_color_block = nullptr;

				loot_button->matched_text_color = nullptr;
				loot_button->matched_text_color_block = nullptr;

				loot_button->matched_rama_color = nullptr;
				loot_button->matched_rama_color_block = nullptr;



				loot_button->matched_minimap_icon_color = nullptr;
				loot_button->matched_minimap_icon_color_block = nullptr;

				loot_button->matched_minimap_icon_shape = nullptr;
				loot_button->matched_minimap_icon_shape_block = nullptr;

				loot_button->matched_minimap_icon_size = nullptr;
				loot_button->matched_minimap_icon_size_block = nullptr;

				loot_button->matched_size_block = nullptr;




				loot_button->matched_filter_blocks.clear();

				loot_button->get_matched_filter_blocks_list(EWindowMain::loot_filter_editor);
			}

		refresh_button_sizes();

		EButtonGroup::change_group(pointer_to_loot_buttons_segment);
	}

}

bool EButtonGroupLootSimulator::is_condition_sactified_for_listed_expression(std::string _expression, int _matches_count)
{
	//expression length cannot  be lesser that 2 (minimum expression for examle "=1", if expression less, then expression have no number or operator
	if (_expression.length() < 2) { EInputCore::logger_simple_error("expression [" + _expression + "] have wrong length. Length cannot be lesser than 2");  return false; }

	std::string condition_operator = "";
	int value = 0;
	if
		(
			(_expression.substr(0, 2) == ">=")
			||
			(_expression.substr(0, 2) == "<=")

			)
	{
		condition_operator = _expression.substr(0, 2);
		value = std::stoi(_expression.substr(2, _expression.length() - 2));
	}
	else
		if
			(
				(_expression[0] == '=')
				||
				(_expression[0] == '<')
				||
				(_expression[0] == '>')
				||
				(_expression[0] == '!')
				)
		{
			condition_operator = _expression[0];
			value = std::stoi(_expression.substr(1, _expression.length() - 1));
		}
		else
		{
			EInputCore::logger_simple_error("expression [" + _expression + "] contains wrong condition operator"); return false;
		}






	//if (_expression.substr(0, 2) == "<=") { condition_operator = "<="; }

	//EInputCore::logger_param("_matches_count", _matches_count);
	//EInputCore::logger_param("condition_operator", condition_operator);
	//EInputCore::logger_param("value", value);
	//std::cout << std::endl;

	return is_condition_satisfied(_matches_count, condition_operator, value);
}

void EButtonGroupLootSimulator::update(float _d)
{
	EButtonGroup::update(_d);
	//show_hidden_cooldown -= _d;

	//if (show_hidden_cooldown <= 0.0f)
	if
		(
			(EInputCore::key_pressed(GLFW_KEY_LEFT_ALT) && (!show_hidden))
			||
			(!EInputCore::key_pressed(GLFW_KEY_LEFT_ALT) && (show_hidden))
			)
	{
		show_hidden = EInputCore::key_pressed(GLFW_KEY_LEFT_ALT);

		//if (show_hidden) { show_hidden_cooldown += 0.75f; }
		//else { show_hidden_cooldown += 0.25f; }

		for (EntityButton* button : pointer_to_loot_buttons_segment->button_list)
			if (button != pointer_to_loot_buttons_segment->slider)
			{
				EntityButtonLootItem*
					loot_button = static_cast<EntityButtonLootItem*>(button);

				button->disable_draw
					=
					!
					(
						(!loot_button->matched_filter_blocks.empty())
						&&
						(
							(loot_button->matched_filter_blocks.back()->button_show_hide->selected_variant == 1)
							&&
							(loot_button->matched_filter_blocks.back()->version_routers[EButtonGroupLootSimulator::pointer_to_target_loot_filter_version_button->selected_variant]->selected_variant != 1)
							)
						||
						(show_hidden)
						);

				if (button->disable_draw) { button->destroy_attached_description(); }
			}
	}
}

void GameAttributeGeneratorMapInfluence::execute_generation(EGameItem* _game_item)
{
	switch (rand() % 6)
	{
		//elder
	case 0:
	{
		ELocalisationText l_text;
		l_text.base_name = "Elder";
		l_text.localisations[NSW_localisation_EN] = "Elder";
		l_text.localisations[NSW_localisation_RU] = "��������";

		target_attribute_container->listed_value_list.push_back(l_text);

		EGameItemAttributeContainer new_container;

		new_container.target_attribute = GameItemAttribute::get_attribute_by_name(&registered_game_item_attributes, "ElderItem");
		new_container.attribute_value_bool = true;
		_game_item->attribute_container_list.push_back(new_container);

		break;
	}

	//shaper
	case 1:
	{
		ELocalisationText l_text;
		l_text.base_name = "Shaper";
		l_text.localisations[NSW_localisation_EN] = "Shaper";
		l_text.localisations[NSW_localisation_RU] = "���������";

		target_attribute_container->listed_value_list.push_back(l_text);

		EGameItemAttributeContainer new_container;

		new_container.target_attribute = GameItemAttribute::get_attribute_by_name(&registered_game_item_attributes, "ShaperItem");
		new_container.attribute_value_bool = true;
		_game_item->attribute_container_list.push_back(new_container);

		break;
	}

	//Redeemer
	case 2:
	{
		ELocalisationText l_text;
		l_text.base_name = "Redeemer";
		l_text.localisations[NSW_localisation_EN] = "Redeemer";
		l_text.localisations[NSW_localisation_RU] = "��������������";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	//Warlord
	case 3:
	{
		ELocalisationText l_text;
		l_text.base_name = "Warlord";
		l_text.localisations[NSW_localisation_EN] = "Warlord";
		l_text.localisations[NSW_localisation_RU] = "�����";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	//Hunter
	case 4:
	{
		ELocalisationText l_text;
		l_text.base_name = "Hunter";
		l_text.localisations[NSW_localisation_EN] = "Hunter";
		l_text.localisations[NSW_localisation_RU] = "��������";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	//Crusader
	case 5:
	{
		ELocalisationText l_text;
		l_text.base_name = "Crusader";
		l_text.localisations[NSW_localisation_EN] = "Crusader";
		l_text.localisations[NSW_localisation_RU] = "�����������";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	default: {}


	}
}

void GameAttributeGeneratorItemInfluence::execute_generation(EGameItem* _game_item)
{
	//if (rand() % 100 < (int)(influence_chance * 100.0f))
	switch (rand() % 6)
	{
		//elder
	case 0:
	{
		ELocalisationText l_text;
		l_text.base_name = "Elder";
		l_text.localisations[NSW_localisation_EN] = "Elder";
		l_text.localisations[NSW_localisation_RU] = "�������";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	//shaper
	case 1:
	{
		ELocalisationText l_text;
		l_text.base_name = "Shaper";
		l_text.localisations[NSW_localisation_EN] = "Shaper";
		l_text.localisations[NSW_localisation_RU] = "���������";

		target_attribute_container->listed_value_list.push_back(l_text);

		//������
		break;
	}

	//Redeemer
	case 2:
	{
		ELocalisationText l_text;
		l_text.base_name = "Redeemer";
		l_text.localisations[NSW_localisation_EN] = "Redeemer";
		l_text.localisations[NSW_localisation_RU] = "��������������";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	//Warlord
	case 3:
	{
		ELocalisationText l_text;
		l_text.base_name = "Warlord";
		l_text.localisations[NSW_localisation_EN] = "Warlord";
		l_text.localisations[NSW_localisation_RU] = "�����";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	//Hunter
	case 4:
	{
		ELocalisationText l_text;
		l_text.base_name = "Hunter";
		l_text.localisations[NSW_localisation_EN] = "Hunter";
		l_text.localisations[NSW_localisation_RU] = "��������";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	//Crusader
	case 5:
	{
		ELocalisationText l_text;
		l_text.base_name = "Crusader";
		l_text.localisations[NSW_localisation_EN] = "Crusader";
		l_text.localisations[NSW_localisation_RU] = "�����������";

		target_attribute_container->listed_value_list.push_back(l_text);

		break;
	}

	default: {}


	}
}

void GameAttributeGeneratorExactListedValue::execute_generation(EGameItem* _game_item)
{
	target_attribute_container->listed_value_list = exact_values_list;
}

void GameAttributeGeneratorBoolFlag::execute_generation(EGameItem* _game_item)
{
	if (rand() % 100 < (int)(chance_to_activate * 100.0f))
	{
		target_attribute_container->attribute_value_bool = true;
	}
	else
	{
		target_attribute_container->attribute_value_bool = false;
	}
}

void GameAttributeGeneratorRarity::execute_generation(EGameItem* _game_item)
{
	GameAttributeGeneratorMinMaxInt::execute_generation(_game_item);

	_game_item->rarity = target_attribute_container->attribute_value_int;
}
