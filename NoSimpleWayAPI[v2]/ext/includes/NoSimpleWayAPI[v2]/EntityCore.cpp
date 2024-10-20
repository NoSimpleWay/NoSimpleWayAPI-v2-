#pragma once
/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/

#ifndef _E_DATA_ENTITY_ALREADY_LINKED_
/**/#define _E_DATA_ENTITY_ALREADY_LINKED_
/**/#include "EDataEntity.h"
#endif

#include <algorithm>
#include <iterator>

void Entity::draw()
{
	if (entity_is_active())
	{
		{transfer_all_vertex_buffers_to_batcher(); }


		//custom data store clickable regions and text
		if (!custom_data_list.empty())
		{
			for (ECustomData* c_data : custom_data_list) if (c_data != nullptr) { c_data->custom_data_draw(); }
		}
	}
}

void Entity::draw_second_pass()
{
	if (entity_is_active())
	{
		//custom data store clickable regions and text
		if (!custom_data_list.empty())
		{
			for (ECustomData* c_data : custom_data_list)
				if (c_data != nullptr) { c_data->draw_second_pass(); }
		}
	}
	else
	{
		//EInputCore::logger_simple_info("scond pass entity disabled draw");
	}



}

void Entity::generate_vertex_buffer_for_all_sprite_layers()
{
	if (be_visible_last_time)
	{
		for (ECustomData* custom_data : custom_data_list)
			for (EClickableArea* clickable_area : custom_data->clickable_area_list)
			{
				if (clickable_area->text_area != nullptr)
				{
					clickable_area->text_area->change_text(clickable_area->text_area->original_text);
				}
			}
		if (!sprite_layer_list.empty())
		{
			for (ESpriteLayer* sl : sprite_layer_list)
				if (sl != nullptr)
				{
					sl->generate_vertex_buffer_for_sprite_layer("Entity sprite layers");
				}
		}
		else
		{
			//EInputCore::logger_simple_error("SpriteList is empty!");
		}

		for (ECustomData* c_data : custom_data_list)
			if (c_data != nullptr)
			{
				for (EClickableArea* c_region : c_data->clickable_area_list)
					if (c_region != nullptr)
					{
						for (ESpriteLayer* s_layer : c_region->sprite_layer_list)
							if (s_layer != nullptr)
							{
								s_layer->generate_vertex_buffer_for_sprite_layer("Clickable region sprite layer");
							}

					}


			}
	}
	else
	{
		have_phantom_draw = true;
	}
}

void Entity::transfer_all_vertex_buffers_to_batcher()
{

	//sprite list for entity
	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* sl : sprite_layer_list)
			if (sl != nullptr) { sl->transfer_vertex_buffer_to_batcher(); }
	}



}

void Entity::set_world_positions(float _x, float _y, float _z)
{
	world_position_x = _x;
	world_position_y = _y;
	world_position_z = _z;

	if (!sprite_layer_list.empty())
		for (ESpriteLayer* s_layer : sprite_layer_list)
			if (s_layer != nullptr)
			{
				s_layer->sprite_layer_set_world_position(world_position_x, world_position_y, world_position_z);
			}

	for (ECustomData* c_data : custom_data_list)
		if (c_data != nullptr)
		{
			for (EClickableArea* clickable_area : c_data->clickable_area_list)
				if (clickable_area != nullptr)
					//
				{
					clickable_area->clickable_region_set_world_positions(world_position_x, world_position_y, world_position_z);
				}
		}
}

void Entity::set_world_position_w(ERegionGabarite* _region_gabarite)
{
	set_world_positions
	(
		_region_gabarite->world_position_x,
		_region_gabarite->world_position_y,
		_region_gabarite->world_position_z
	);
}

void Entity::set_world_position_l(ERegionGabarite* _region_gabarite)
{
	set_world_positions
	(
		_region_gabarite->offset_x,
		_region_gabarite->offset_y,
		_region_gabarite->offset_z
	);
}

void Entity::modify_buffer_translate_for_entity(float _x, float _y, float _z)
{
	for (ESpriteLayer* s_layer : sprite_layer_list)
	{
		s_layer->modify_buffer_position_for_sprite_layer(_x, _y, _z);
	}

	for (ECustomData* c_data : custom_data_list)
	{
		for (EClickableArea* c_region : c_data->clickable_area_list)
		{
			for (ESpriteLayer* s_layer : c_region->sprite_layer_list)
			{
				s_layer->modify_buffer_position_for_sprite_layer(_x, _y, _z);
			}
		}


	}

}

void Entity::destroy_all_vertex_buffer_data()
{
	for (ESpriteLayer* s_layer : sprite_layer_list)
	{
		s_layer->destroy_vertex_buffer();
	}

	for (ECustomData* c_data : custom_data_list)
		for (EClickableArea* c_area : c_data->clickable_area_list)
		{
			if (c_area->text_area != nullptr)
			{
				c_area->text_area->sprite_layer->destroy_vertex_buffer();
			}

			for (ESpriteLayer* s_layer : c_area->sprite_layer_list)
			{
				s_layer->destroy_vertex_buffer();
			}
		}
}

void Entity::translate_entity(float _x, float _y, float _z, bool _move_positions)
{

	world_position_x += _x;
	world_position_y += _y;
	world_position_z += _z;

	//entity position
	if (_move_positions)
	{
		offset_x += _x;
		offset_y += _y;
		offset_z += _z;
	}

	translate_sprite_layer(_x, _y, _z, false);
	translate_custom_data(_x, _y, _z, false);
}

void Entity::translate_sprite_layer(float _x, float _y, float _z, bool _move_locals)
{
	for (ESpriteLayer* s_layer : sprite_layer_list)
		if (s_layer != nullptr) { s_layer->translate_sprite_layer(_x, _y, _z, false); }
}

void Entity::translate_custom_data(float _x, float _y, float _z, bool _move_locals)
{
	for (ECustomData* c_data : custom_data_list)
		if (c_data != nullptr) { c_data->translate_custom_data(_x, _y, _z, false); }
}

bool Entity::entity_is_active()
{
	return (!entity_disabled);
}

void Entity::update(float _d)
{
	//translate_entity(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f);

	if (entity_is_active())
	for (ECustomData* c_data : custom_data_list)
		if (c_data != nullptr)
		{
			c_data->update(_d);
		}
}

Entity::Entity()
{
}

Entity::~Entity()
{
	if (debug_deleting) { EInputCore::logger_simple_info("Called <Entity> destructor"); }
	//EInputCore::logger_simple_try("delete entity");

	//delete offset_x;
	//delete offset_y;
	//delete offset_z;

	//delete world_position_x;
	//delete world_position_y;
	//delete world_position_z;

	//
	if (debug_deleting)EInputCore::logger_simple_info("start deleting base entity");
	if (!custom_data_list.empty())
	{
		if (debug_deleting)EInputCore::logger_simple_info("start deleting custom data");

		//std::vector<ECustomData*>::iterator ib = custom_data_list.begin(), ie = custom_data_list.end();
		for (ECustomData* custom_data : custom_data_list)
		{
			if (debug_deleting)EInputCore::logger_simple_info("try delete custom data");
			if (!disable_deleting)
			{
				delete custom_data;
			}

			if (debug_deleting)EInputCore::logger_simple_success("custom data deleted");

		}

		if (debug_deleting)EInputCore::logger_simple_success("all custom data deleted");

		custom_data_list.clear();
		custom_data_list.shrink_to_fit();

		if (debug_deleting)EInputCore::logger_simple_success("custom data list cleared and shrinked");


	}


	if (!sprite_layer_list.empty())
	{
		if (debug_deleting)EInputCore::logger_simple_info("start deleting sprite layers");

		for (ESpriteLayer* sl : sprite_layer_list)
		{
			if (debug_deleting)EInputCore::logger_simple_info("try delete sprite layer");
			if (!disable_deleting)
			{
				delete sl;
			}
			if (debug_deleting)EInputCore::logger_simple_success("delete sprite layer");

		}
		if (debug_deleting)EInputCore::logger_simple_success("all sprite layers deleted");

		sprite_layer_list.clear();
		sprite_layer_list.shrink_to_fit();

		if (debug_deleting)EInputCore::logger_simple_success("sprite layer list cleared and shrinked");

	}

	//delete disable_draw;
	//delete need_remove;
	//delete& custom_data_list;
	//delete[] custom_data_list;
}

ESprite* Entity::get_sprite_from_data(unsigned int _data_id, unsigned int _layer_id, unsigned int _frame_id, unsigned int _frame)
{
	/*if
	(
		(!custom_data_list.empty())
		&&
		(!custom_data_list.at(_data_id)->clickable_region_list)
	)*/
	return nullptr;
}

ESpriteLayer* Entity::get_sprite_layer_by_id(unsigned int _id)
{
	if
		(
			(!sprite_layer_list.empty())
			&&
			(_id >= 0)
			&&
			(_id < sprite_layer_list.size())
			)
	{
		return sprite_layer_list[_id];
	}
	else
	{
		return nullptr;
	}
}

ESprite* Entity::get_sprite_from_entity(unsigned int _layer_id, unsigned int _frame, unsigned int _frame_id)
{
	//ESpriteLayer* sprite_layer = nullptr;
	//ESpriteFrame* target_sprite_frame = nullptr;

	//if (!sprite_layer_list.empty()) { sprite_layer =}
	if
		(
			(_CHECK_VECTOR_BOUND(sprite_layer_list, _layer_id))
			&&
			(_CHECK_VECTOR_BOUND(sprite_layer_list[_layer_id]->sprite_frame_list, _frame))
			)
	{
		return sprite_layer_list[_layer_id]->sprite_frame_list[_frame]->sprite_list[_frame_id];
	}

	//if (target_sprite_frame != nullptr)
	//{return target_sprite_frame->sprite_list[_frame_id];}

	return nullptr;
}

ESpriteFrame* Entity::get_sprite_frame_from_layer(ESpriteLayer* _layer, unsigned int _frame_id)
{
	if
		(
			(_layer != nullptr)
			&&
			(_CHECK_VECTOR_BOUND(_layer->sprite_frame_list, _frame_id))
			)
	{
		return _layer->sprite_frame_list[_frame_id];
	}
	else
	{
		return nullptr;
	}
}

ESprite* Entity::get_sprite_from_sprite_frame(ESpriteFrame* _frame, unsigned int _id)
{
	if
		(
			(_frame != nullptr)
			&&
			(_CHECK_VECTOR_BOUND(_frame->sprite_list, _id))
			)
	{
		return _frame->sprite_list[_id];
	}

	return nullptr;
}

ESprite* Entity::get_last_sprite(Entity* _entity)
{
	if
		(
			(_entity != nullptr)
			&&
			(!_entity->sprite_layer_list.empty())
			&&
			(!_entity->sprite_layer_list.back()->sprite_frame_list.empty())
			&&
			(!_entity->sprite_layer_list.back()->sprite_frame_list.back()->sprite_list.empty())
			)
	{
		return _entity->sprite_layer_list.back()->sprite_frame_list.back()->sprite_list.back();
	}
	else
	{
		return nullptr;
	}
}

ECustomData* Entity::get_last_custom_data(Entity* _entity)
{
	if
		(
			(_entity != nullptr)
			&&
			(!_entity->custom_data_list.empty())
			)
	{
		return _entity->custom_data_list.back();
	}
	else
	{
		return nullptr;
	}
}

EClickableArea* Entity::get_last_clickable_area(Entity* _entity)
{
	ECustomData* last_data = Entity::get_last_custom_data(_entity);

	if
		(
			(last_data != nullptr)
			&&
			(!last_data->clickable_area_list.empty())
			)
	{
		return last_data->clickable_area_list.back();
	}
	else
	{
		return nullptr;
	}
}

ETextArea* Entity::get_last_text_area(Entity* _entity)
{
	EClickableArea* last_clickable_area = get_last_clickable_area(_entity);

	if (last_clickable_area != nullptr)
	{
		//TextArea* last_text_area =

		return last_clickable_area->text_area;
	}

	return nullptr;
}

void Entity::add_text_area_to_last_clickable_region(EntityButton* _button, ETextArea* _text_area)
{
	if (_button != nullptr)
	{
		EClickableArea* last_clickable_area = get_last_clickable_area(_button);

		if (last_clickable_area != nullptr)
		{
			last_clickable_area->text_area = _text_area;
			_text_area->parent_entity_for_text_area = _button;

			if ((_button->parent_button_group != nullptr) && (_button->parent_button_group->selected_style != nullptr))
			{
				last_clickable_area->text_area->color = last_clickable_area->text_area->stored_color;
				//apply color correction from style
				//for (int i = 0; i < 4; i++)
				//{
				//	last_clickable_area->text_area->color[i]
				//	=
				//	last_clickable_area->text_area->stored_color[i]
				//	*
				//	_button->parent_button_group->selected_style->text_color_multiplier[i];
				//}
			}
		}
	}
}

bool EntityButton::entity_is_active()
{
	return ((Entity::entity_is_active()) && (!button_hidden_by_search));
}

void EntityButton::destroy_all_vertex_buffer_data()
{
	Entity::destroy_all_vertex_buffer_data();

	have_phantom_draw = false;
}

void EntityButton::set_highlight(float _set_time, float _max_time)
{
	highlight_time = _set_time;
	max_highlight_time = _max_time;

	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	highlight_timestamp = ms;
}

void EntityButton::add_hotkey(int _key_main, int _key_secondary)
{
	EHotKeyManager hmanager;
	hmanager.require_main_button = _key_main;
	hmanager.require_secondare_button = _key_secondary;
	hmanager.parent_button = this;
	hotkey_list.push_back(hmanager);
}

void EntityButton::destroy_attached_description()
{
	if (attached_description != nullptr)
	{
		auto finder = std::find
		(
			parent_button_group->root_group->parent_window->button_group_list.begin(),
			parent_button_group->root_group->parent_window->button_group_list.end(),
			attached_description
		);

		if (finder != std::end(parent_button_group->root_group->parent_window->button_group_list))
		{
			parent_button_group->root_group->parent_window->button_group_list.erase
			(
				finder
			);

			if (!disable_deleting)
			{
				//delete attached_description;
				attached_description->block_need_remove = true;
				
				//attached_description = nullptr;
			}
		}

		attached_description = nullptr;
	}
}

void EntityButton::button_generate_brick_bg(EntityButton* _button, EGUIStyle* _style)
{
	if ((_button != nullptr) && (_style != nullptr) && (!_button->do_not_generate_bg))
	{
		ESpriteLayer* last_layer = nullptr;

		if (_button->sprite_layer_list.empty())
		{
			std::cout << "auto generate sprite layer!" << std::endl;
			_button->sprite_layer_list.push_back
			(ESpriteLayer::create_default_sprite_layer(nullptr));
		}

		last_layer = _button->sprite_layer_list.at(0);

		NS_ERenderCollection::set_brick_borders_and_subdivisions(_style->brick_style[BrickStyleID::BUTTON_BG]);

		NS_ERenderCollection::temporary_sprites = false;

		NS_ERenderCollection::generate_brick_texture
		(
			_button->button_gabarite,
			last_layer,
			_style->brick_style[BrickStyleID::BUTTON_BG].main_texture,
			_style->brick_style[BrickStyleID::BUTTON_BG].normal_map_texture,
			_style->brick_style[BrickStyleID::BUTTON_BG].gloss_map_texture
		);
	}
	//_button->sprite_layer_list.pu
}

//class EButtonGroupButtonDebugger;
EButtonGroupButtonDebugger* EntityButton::open_button_debugger()
{
	EButtonGroupButtonDebugger*
	button_debug_group
	=
	new EButtonGroupButtonDebugger (new ERegionGabarite (200.0f, 500.0f));

	button_debug_group->target_button = this;
	button_debug_group->auto_superfocused = true;

	
	button_debug_group->autodeletable = true;

	button_debug_group->init_as_root_group(parent_button_group->root_group->parent_window);





	EButtonGroup*
	workspace_part = button_debug_group->add_close_group_and_return_workspace_group(new ERegionGabarite(100.0f, 20.0f), EGUIStyle::active_style);

	//WIDTH
	{
		EntityButton*
			button_width_slider = EntityButton::create_horizontal_named_slider
			(
				new ERegionGabarite(200.0f, 38.0f),
				workspace_part,
				EFont::font_list[0],
				EGUIStyle::active_style,
				ELocalisationText::get_localisation_by_key("button_width")
			);

		button_width_slider->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_refresh_parent_group_slider_version);
		button_width_slider->main_text_area->font = EFont::font_list[1];
		button_width_slider->main_text_area->font_scale = 0.75f;
		button_width_slider->can_be_stretched = true;

		set_parameters_for_named_slider(button_width_slider, &(button_gabarite->size_x), 0.0f, 250.0f, 1000.0f);
		set_parameters_for_named_slider(button_width_slider, true, true);

		workspace_part->add_button_to_working_group(button_width_slider);
	}
	
	//HEIGHT
	{
		EntityButton*
			button_width_slider = EntityButton::create_horizontal_named_slider
			(
				new ERegionGabarite(200.0f, 38.0f),
				workspace_part,
				EFont::font_list[0],
				EGUIStyle::active_style,
				ELocalisationText::get_localisation_by_key("button_height")
			);

		button_width_slider->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_refresh_parent_group_slider_version);
		button_width_slider->main_text_area->font = EFont::font_list[1];
		button_width_slider->main_text_area->font_scale = 0.75f;
		button_width_slider->can_be_stretched = true;

		set_parameters_for_named_slider(button_width_slider, &(button_gabarite->size_y), 0.0f, 50.0f, 500.0f);
		set_parameters_for_named_slider(button_width_slider, true, true);

		workspace_part->add_button_to_working_group(button_width_slider);
	}
	
	//FORCE FIELD: BOTTOM
	{
		EntityButton*
			button_width_slider = EntityButton::create_horizontal_named_slider
			(
				new ERegionGabarite(200.0f, 38.0f),
				workspace_part,
				EFont::font_list[0],
				EGUIStyle::active_style,
				ELocalisationText::get_localisation_by_key("button_force_field_bottom")
			);

		button_width_slider->force_field_bottom = 4.0f;
		button_width_slider->main_text_area->set_color(0.9f, 0.7f, 1.0f, 1.0f);
		button_width_slider->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_refresh_parent_group_slider_version);
		button_width_slider->main_text_area->font = EFont::font_list[1];
		button_width_slider->main_text_area->font_scale = 0.75f;
		button_width_slider->can_be_stretched = true;

		set_parameters_for_named_slider(button_width_slider, &(force_field_bottom), 0.0f, 50.0f, 500.0f);
		set_parameters_for_named_slider(button_width_slider, true, true);

		workspace_part->add_button_to_working_group(button_width_slider);
	}
	
	//FORCE FIELD: UP
	{
		EntityButton*
			button_width_slider = EntityButton::create_horizontal_named_slider
			(
				new ERegionGabarite(200.0f, 38.0f),
				workspace_part,
				EFont::font_list[0],
				EGUIStyle::active_style,
				ELocalisationText::get_localisation_by_key("button_force_field_top")
			);

		button_width_slider->force_field_bottom = 4.0f;
		button_width_slider->main_text_area->set_color(0.9f, 0.7f, 1.0f, 1.0f);
		button_width_slider->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_refresh_parent_group_slider_version);
		button_width_slider->main_text_area->font = EFont::font_list[1];
		button_width_slider->main_text_area->font_scale = 0.75f;
		button_width_slider->can_be_stretched = true;

		set_parameters_for_named_slider(button_width_slider, &(force_field_up), 0.0f, 50.0f, 500.0f);
		set_parameters_for_named_slider(button_width_slider, true, true);

		workspace_part->add_button_to_working_group(button_width_slider);
	}
	
	//FORCE FIELD: LEFT
	{
		EntityButton*
			button_width_slider = EntityButton::create_horizontal_named_slider
			(
				new ERegionGabarite(200.0f, 38.0f),
				workspace_part,
				EFont::font_list[0],
				EGUIStyle::active_style,
				ELocalisationText::get_localisation_by_key("button_force_field_left")
			);

		button_width_slider->force_field_bottom = 4.0f;
		button_width_slider->main_text_area->set_color(0.9f, 0.7f, 1.0f, 1.0f);
		button_width_slider->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_refresh_parent_group_slider_version);
		button_width_slider->main_text_area->font = EFont::font_list[1];
		button_width_slider->main_text_area->font_scale = 0.75f;
		button_width_slider->can_be_stretched = true;

		set_parameters_for_named_slider(button_width_slider, &(force_field_left), 0.0f, 50.0f, 500.0f);
		set_parameters_for_named_slider(button_width_slider, true, true);

		workspace_part->add_button_to_working_group(button_width_slider);
	}
	
	//FORCE FIELD: LEFT
	{
		EntityButton*
			button_width_slider = EntityButton::create_horizontal_named_slider
			(
				new ERegionGabarite(200.0f, 38.0f),
				workspace_part,
				EFont::font_list[0],
				EGUIStyle::active_style,
				ELocalisationText::get_localisation_by_key("button_force_field_right")
			);

		button_width_slider->force_field_bottom = 4.0f;
		button_width_slider->main_text_area->set_color(0.9f, 0.7f, 1.0f, 1.0f);
		button_width_slider->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_refresh_parent_group_slider_version);
		button_width_slider->main_text_area->font = EFont::font_list[1];
		button_width_slider->main_text_area->font_scale = 0.75f;
		button_width_slider->can_be_stretched = true;

		set_parameters_for_named_slider(button_width_slider, &(force_field_right), 0.0f, 50.0f, 500.0f);
		set_parameters_for_named_slider(button_width_slider, true, true);

		workspace_part->add_button_to_working_group(button_width_slider);
	}

	//NEW LINE METHOD
	{
		EntityButtonVariantRouter*
		router_button = new EntityButtonVariantRouter();
		workspace_part->add_button_to_working_group(router_button);

		router_button->force_field_bottom = 12.0f;

		
		router_button->make_as_default_router_variant_button(new ERegionGabarite(200.0f, 20.0f));
		router_button->action_on_choose_variant_from_window.push_back(&EDataActionCollection::action_refresh_parent_group_router_variant_version);

		router_button->can_be_stretched = true;
		router_button->rotate_variant_mode = RotateVariantMode::OPEN_CHOOSE_WINDOW;
		router_button->height_division = 1;

		router_button->add_router_variant_with_localization_key_and_color("button_new_line_method_overfill",	0.9f, 0.8f, 0.7f, 1.0f);
		router_button->add_router_variant_with_localization_key_and_color("button_new_line_method_forcibly",	0.5f, 1.0f, 0.7f, 1.0f);
		router_button->add_router_variant_with_localization_key_and_color("button_new_line_method_forbidden",	1.0f, 0.7f, 0.5f, 1.0f);

		router_button->target_int_value = &new_line_method;

		router_button->select_variant(new_line_method);

		
	}






	parent_button_group->root_group->parent_window->button_group_list.push_back(button_debug_group);
	button_debug_group->activate_move_to_foreground_and_center();

	return button_debug_group;
}

void EntityButton::add_default_description_by_key(std::string _key)
{

	description_container = new DescriptionContainerDefault(800.0f, 120.0f);
	description_container->localisation_text = ELocalisationText::get_localisation_by_key(_key);
	description_container->parent_button = this;
}


void EntityButton::init(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group)
{
	parent_button_group = _parent_group;
	ERegionGabarite::set_region_gabarite(&button_gabarite, _region_gabarite);

	base_size_x = _region_gabarite->size_x;
	base_size_y = _region_gabarite->size_y;

	sprite_layer_list.push_back(ESpriteLayer::create_default_sprite_layer(nullptr));

	//EntityButton::button_generate_brick_bg(this, _parent_group->selected_style);
	//set_world_position_w(_region_gabarite);

	action_on_generate_vertex_buffer.push_back(&action_generate_brick_bg_for_button);
}

void EntityButton::add_default_custom_data(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_row)
{
	init(_region_gabarite, _parent_row);
	ECustomData* jc_custom_data = new ECustomData();
	jc_custom_data->parent_entity = this;

	//*jc_custom_data->is_second_pass = true;
	main_custom_data = jc_custom_data;
	custom_data_list.push_back(jc_custom_data);
}


void EntityButton::make_as_default_clickable_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap)
{
	add_default_custom_data(_region_gabarite, _parent_group);

	EClickableArea* jc_clickable_area = EClickableArea::create_default_clickable_region
	(
		_region_gabarite,
		this,
		EntityButton::get_last_custom_data(this)
	);

	main_clickable_area = jc_clickable_area;

	jc_clickable_area->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
	if (_dap != nullptr) { jc_clickable_area->actions_on_click_list.push_back(_dap); }

	ECustomData*
	last_data = Entity::get_last_custom_data(this);

	last_data->clickable_area_list.push_back(jc_clickable_area);
}

EntityButton* EntityButton::create_item_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, EDataEntity* _data_entity)
{
	EntityButton* jc_button = new EntityButton();

	jc_button->make_as_default_clickable_button
	(
		new ERegionGabarite(44.0f, 44.0f),
		_parent_group,
		nullptr
	);

	EDataContainer_DataEntityHolder* data = new EDataContainer_DataEntityHolder();
	data->stored_data_entity = _data_entity;

	EntityButton::get_last_custom_data(jc_button)->data_container = data;

	//delete action on right click
	Entity::get_last_clickable_area(jc_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_delete_entity);

	//_parent_group->button_list.push_back(jc_button);

	//int selected_data_entity = _data_entity;

	ETextureGabarite* item_icon
		=
		NS_EGraphicCore::load_from_textures_folder("icons/" + DataEntityUtils::get_tag_value_by_name_ID(0, &ERegisteredStrings::icon_path, _data_entity));

	if (item_icon != nullptr)
	{
		float resize_factor = 38.0f / max(item_icon->size_x_in_pixels, item_icon->size_y_in_pixels);
		resize_factor = min(resize_factor, 1.0f);

		ESpriteLayer* second_button_layer =
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(item_icon,
				(44.0f - item_icon->size_x_in_pixels * resize_factor) / 2.0f,
				(44.0f - item_icon->size_y_in_pixels * resize_factor) / 2.0f,
				3.0f,

				item_icon->size_x_in_pixels * resize_factor,
				item_icon->size_y_in_pixels * resize_factor,
				0.0f
			);

		jc_button->sprite_layer_list.push_back(second_button_layer);

		//second_button_layer->make_as_PBR();
	}

	//jc_button->add_description("123");
	//jc_button->add_description(DataEntityUtils::get_tag_value_by_name(0, "name EN", _data_entity));

	return jc_button;
}






EntityButton* EntityButton::create_horizontal_named_slider(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, EFont* _font, EGUIStyle* _style, ELocalisationText _ltext)
{
	EntityButton* jc_button = new EntityButton();

	jc_button->make_as_default_clickable_button
	(
		_region_gabarite,
		_parent_group,
		nullptr
	);

	EDataContainer_VerticalNamedSlider*
	data = new EDataContainer_VerticalNamedSlider();

	//jc_button->main_custom_data = EntityButton::get_last_custom_data(jc_button);

	jc_button->main_custom_data->data_container = data;
	//data->slider_style = _style;
	data->operable_area_size_x = _region_gabarite->size_x - _style->brick_style[BrickStyleID::ROUND_SLIDER].main_texture->size_x_in_pixels;

	jc_button->main_custom_data->actions_on_update.push_back(&EDataActionCollection::action_update_horizontal_named_slider);
	jc_button->main_custom_data->actions_on_draw.push_back(&EDataActionCollection::action_draw_horizontal_named_slider);

	//jc_button->action_on_generate_vertex_buffer.push_back(&action_generate_brick_bg_for_button);
	jc_button->action_on_generate_vertex_buffer.push_back(&action_generate_vertex_for_horizontal_named_slider);

	//SLIDER LINE
	{
		ESpriteLayer*
			brick_line_layer = ESpriteLayer::create_default_sprite_layer(nullptr);

		data->pointer_to_brick_line_sprite_layer = brick_line_layer;
		jc_button->sprite_layer_list.push_back(brick_line_layer);
	}

	//DIGIT SECTION
	{
		ESpriteLayer*
		digit_section = ESpriteLayer::create_default_sprite_layer(nullptr);
		digit_section->offset_x = 0.0f;
		data->pointer_to_digit_section_sprite_layer = digit_section;
		jc_button->sprite_layer_list.push_back(digit_section);
	}


	/*ESpriteLayer* head_layer = ESpriteLayer::create_default_sprite_layer(_style->round_slider->main_texture);
	data->pointer_to_head = head_layer;
	jc_button->sprite_layer_list.push_back(head_layer);*/
	//delete action on right click
	//Entity::get_last_clickable_area(jc_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_delete_entity);

	//_parent_group->button_list.push_back(jc_button);

	//int selected_data_entity = _data_entity;

	//TEXT HEAD
	ETextArea* jc_text_area = ETextArea::create_centered_to_left_text_area(Entity::get_last_clickable_area(jc_button), _font, _ltext);
	jc_button->main_text_area = jc_text_area;

	jc_text_area->offset_by_gabarite_size_x = 0.0;
	jc_text_area->offset_by_text_size_x = 0.0;

	jc_text_area->offset_by_gabarite_size_y = 1.0;
	jc_text_area->offset_by_text_size_y = -1.0;

	jc_text_area->forbide_new_line		= true;
	jc_text_area->forbide_outbounding	= true;

	jc_text_area->offset_border[BorderSide::LEFT] = _style->brick_style[BrickStyleID::BUTTON_BG].offset_for_elements_left * 0.0f;
	//jc_text_area->offset_border[BorderSide::LEFT] = 8.0f;

	jc_text_area->change_text(_ltext.localisations[ELocalisationText::active_localisation]);
	data->pointer_to_text_area = jc_text_area;
	data->stored_text = _ltext;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);



	//DIGIT TEXT
	EClickableArea* clickable_area_for_digit_section = EClickableArea::create_default_clickable_region
	(
		new ERegionGabarite(_style->brick_style[BrickStyleID::BUTTON_BG].offset_for_elements_left - 0.0f, 0.0f, 35.0f, 18.0f),
		jc_button,
		nullptr
	);

	clickable_area_for_digit_section->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;

	jc_button->main_custom_data->clickable_area_list.push_back(clickable_area_for_digit_section);

	ETextArea*
		text_area_digit_segment = ETextArea::create_centered_to_left_text_area(clickable_area_for_digit_section, _font, ELocalisationText::empty_localisation);
	//text_area_digit_segment->offset_border[BorderSide::LEFT] = _style->brick_style[BrickStyleID::BUTTON_BG].offset_for_elements_left * 0.0f;


	text_area_digit_segment->forbide_new_line			= true;
	text_area_digit_segment->forbide_outbounding		= true;

	text_area_digit_segment->can_be_edited				= true;
	text_area_digit_segment->can_change_localisation	= true;

	//text_area_digit_segment->autoerase_text = true;

	data->pointer_to_digit_text_area = text_area_digit_segment;


	Entity::add_text_area_to_last_clickable_region(jc_button, text_area_digit_segment);





	return jc_button;
}

void EntityButton::set_parameters_for_named_slider(EntityButton* _button, void* _pointer, float _min_value, float _mid_value, float _max_value)
{
	EDataContainer_VerticalNamedSlider*
	slider_data = static_cast<EDataContainer_VerticalNamedSlider*>(_button->main_custom_data->data_container);
	
	slider_data->pointer_to_value	= _pointer;
	slider_data->min_value			= _min_value;
	slider_data->mid_value			= _mid_value;
	slider_data->max_value			= _max_value;
}

void EntityButton::set_parameters_for_named_slider(EntityButton* _button, bool _is_rounded, bool _is_float)
{
	EDataContainer_VerticalNamedSlider*
	slider_data = static_cast<EDataContainer_VerticalNamedSlider*>(_button->main_custom_data->data_container);

	slider_data->rounded_numbers	= _is_rounded;
	slider_data->is_float			= _is_float;
}

void EntityButtonColorButton::make_as_named_color_button
(
	ERegionGabarite*		_region_gabarite,
	EButtonGroup*			_parent_group,
	EFont*					_font,
	EGUIStyle*				_style,
	ELocalisationText		_text,
	HRA_color_collection*	_color_collection,
	HSVRGBAColor*			_color,
	ColorButtonMode			_mode
)
{


	//EntityButtonColorButton
	//jc_button;

	parent_color_collection = _color_collection;

	make_as_default_clickable_button
	(
		_region_gabarite,
		_parent_group,
		nullptr
	);



	//EDataContainer_Button_StoreColor* data = new EDataContainer_Button_StoreColor();
	//if (!data->stored_color->is_from_collection)
	//EntityButton::get_last_custom_data(jc_button)->data_container = data;
	stored_color = _color;
	selected_mode = _mode;

	//std::cout << data->stored_color << std::endl;

	EntityButton::get_last_custom_data(this)->actions_on_draw.push_back(&EDataActionCollection::action_draw_stored_color_as_box);
	
	if (_mode == ColorButtonMode::CBM_OPEN_WINDOW)
	{
		EntityButton::get_last_clickable_area(this)->actions_on_click_list.push_back(&EDataActionCollection::action_open_color_group);
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ETextArea*
	jc_text_area = ETextArea::create_centered_to_left_text_area(Entity::get_last_clickable_area(this), _font, _text);
	jc_text_area->forbide_new_line = true;
	jc_text_area->forbide_outbounding = true;

	if (_mode == ColorButtonMode::CBM_SELECT_COLOR)
	{
		jc_text_area->forcibly_create_glyph = true;
	}

	jc_text_area->offset_by_gabarite_size_x = 0.0;
	jc_text_area->offset_by_text_size_x = 0.0;

	jc_text_area->offset_by_gabarite_size_y = 1.0;
	jc_text_area->offset_by_text_size_y = -1.0;

	jc_text_area->offset_border[BorderSide::LEFT] = _parent_group->group_offset_for_content_left;

	jc_text_area->change_text(_text.localisations[ELocalisationText::active_localisation]);
	jc_text_area->localisation_text = _text;
	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);



	main_text_area = jc_text_area;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (_mode == ColorButtonMode::CBM_SELECT_COLOR)
	{
		main_clickable_area->actions_on_right_click_list.push_back(&EDataActionCollection::action_active_text_area);
		main_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_transfer_pointer_to_color_data_container);

		jc_text_area->action_on_change_text.push_back(&EDataActionCollection::action_change_localisation_for_color_button);
		jc_text_area->action_on_finalize_text.push_back(&EDataActionCollection::action_deactive_text_area);

		add_default_description_by_key("description_color_selector");








		//add new clickable area (close X)
		EClickableArea*
			close_clickable_area = EClickableArea::create_default_clickable_region
			(
				new ERegionGabarite(16.0f, 16.0f),
				this,
				EntityButton::get_last_custom_data(this)
			);

		//jc_button->pointer_to_close_area = close_clickable_area;
		close_clickable_area->actions_on_click_list.push_back(&EDataActionCollection::action_delete_entity);

		close_clickable_area->region_gabarite->offset_by_parent_size_x = 1.0f;
		close_clickable_area->region_gabarite->offset_by_parent_size_y = 1.0f;

		close_clickable_area->region_gabarite->offset_by_size_x = -1.0f;
		close_clickable_area->region_gabarite->offset_by_size_y = -1.0f;

		close_clickable_area->region_gabarite->offset_by_pixels_x = -3.0f;
		close_clickable_area->region_gabarite->offset_by_pixels_y = -3.0f;

		close_clickable_area->draw_only_is_specific_region_overlapped = main_clickable_area->region_gabarite;

		main_custom_data->clickable_area_list.push_back(close_clickable_area);
		main_clickable_area->region_gabarite->add_child_to_this_region(close_clickable_area->region_gabarite);

		ESpriteLayer* third_sprite_layer =
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				NS_DefaultGabarites::texture_close_circle,

				0.0f,
				0.0f,
				0.0f,

				16.0f,
				16.0f,
				0.0f
			);

		close_clickable_area->sprite_layer_list.push_back(third_sprite_layer);
	}







	//return jc_button;
}

EntityButton* EntityButton::create_default_radial_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, std::string _text)
{
	EntityButton* jc_button = new EntityButton();

	jc_button->add_default_custom_data(_region_gabarite, _parent_group);

	unsigned int square_size = min(_region_gabarite->size_x, _region_gabarite->size_y);

	EClickableArea* jc_clickable_area = EClickableArea::create_default_clickable_region
	(
		_region_gabarite,
		jc_button,
		EntityButton::get_last_custom_data(jc_button)
	);

	jc_button->main_clickable_area = jc_clickable_area;



	jc_clickable_area->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;

	ECustomData* last_data = Entity::get_last_custom_data(jc_button);
	//last_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);

	last_data->clickable_area_list.push_back(jc_clickable_area);
	last_data->actions_on_update.push_back(&EDataActionCollection::action_update_radial_button);


	//create data container
	EDataContainerRadialButton* jc_data_container = new EDataContainerRadialButton();
	last_data->data_container = jc_data_container;

	jc_data_container->text = _text;

	ESpriteLayer* jc_sprite_layer = ESpriteLayer::create_default_sprite_layer_with_size_and_offset
	(
		NS_EGraphicCore::load_from_textures_folder("buttons/radiance_button"),

		0.0f,
		0.0f,
		0.0f,

		square_size,
		square_size,
		0.0f
	);

	ESpriteLayer::add_new_default_frame_with_sprite
	(
		NS_EGraphicCore::load_from_textures_folder("buttons/radiance_button_dot"),
		jc_sprite_layer
	);

	jc_clickable_area->sprite_layer_list.push_back(jc_sprite_layer);

	ETextArea* jc_text_area = ETextArea::create_centered_to_right_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "1.0");
	jc_text_area->offset_border[BorderSide::RIGHT] = 6.0f;
	jc_text_area->can_be_edited = false;

	//jc_text_area->change_text("123\\n456");
	//jc_text_area->stored_text = "123\\n456";
	//jc_text_area->generate_rows();
	//jc_text_area->generate_text();

	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

	jc_button->main_text_area = jc_text_area;

	return jc_button;
}

EntityButton* EntityButton::create_default_crosshair_slider(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, float* _pointer_x, float* _pointer_y, std::string _texture)
{
	EntityButton* jc_button = new EntityButton();

	jc_button->add_default_custom_data(_region_gabarite, _parent_group);

	EClickableArea* jc_clickable_area = EClickableArea::create_default_clickable_region
	(
		_region_gabarite,
		jc_button,
		EntityButton::get_last_custom_data(jc_button)
	);

	jc_button->main_clickable_area = jc_clickable_area;


	jc_clickable_area->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;

	ECustomData* last_data = Entity::get_last_custom_data(jc_button);
	//update
	last_data->actions_on_update.push_back(&EDataActionCollection::action_update_crosshair_slider);


	//draw
	last_data->actions_on_draw.push_back(&EDataActionCollection::action_draw_crosshair_slider);
	//last_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);


	last_data->clickable_area_list.push_back(jc_clickable_area);



	//create data container
	EDataContainer_CrosshairSlider* jc_data_container = new EDataContainer_CrosshairSlider();
	jc_data_container->target_pointer_x = _pointer_x;
	jc_data_container->target_pointer_y = _pointer_y;
	last_data->data_container = jc_data_container;

	if (_texture != "")
	{
		ESpriteLayer* jc_sprite_layer = ESpriteLayer::create_default_sprite_layer_with_size_and_offset
		(
			NS_EGraphicCore::load_from_textures_folder(_texture),

			0.0f,
			0.0f,
			0.0f,

			_region_gabarite->size_x,
			_region_gabarite->size_y,
			0.0f
		);

		jc_clickable_area->sprite_layer_list.push_back(jc_sprite_layer);
	}



	//ETextArea* jc_text_area = ETextArea::create_centered_to_right_text_area(Entity::get_last_clickable_area(jc_button), EFont::font_list[0], "1.0");
	//jc_text_area->offset_border[BorderSide::RIGHT] = 6.0f;
	//jc_text_area->can_be_edited = false;

	//jc_text_area->change_text("123\\n456");
	//jc_text_area->stored_text = "123\\n456";
	//jc_text_area->generate_rows();
	//jc_text_area->generate_text();

	//Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);
	return jc_button;
}



void EntityButton::make_default_button_with_unedible_text(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ELocalisationText _ltext)
{


	make_as_default_clickable_button
	(
		_region_gabarite,
		_parent_group,
		_dap
	);


	ETextArea*
		jc_text_area = ETextArea::create_centered_text_area
		(EntityButton::get_last_clickable_area(this), EFont::font_list[0], _ltext);

	jc_text_area->change_text(_ltext.localisations[ELocalisationText::active_localisation]);

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);

	main_text_area = jc_text_area;
}

void EntityButton::make_default_button_with_edible_text(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, std::string _text)
{

	make_as_default_clickable_button
	(
		_region_gabarite,
		_parent_group,
		_dap
	);


	ETextArea*
		jc_text_area = ETextArea::create_centered_text_area
		(EntityButton::get_last_clickable_area(this), EFont::font_list[0], ELocalisationText());

	jc_text_area->change_text(_text);

	jc_text_area->can_be_edited = true;
	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);

	main_text_area = jc_text_area;
}

void EntityButton::make_as_default_button_with_icon(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _texture_gabarite)
{


	make_as_default_clickable_button(_region_gabarite, _parent_group, _dap);

	float region_size = min(_region_gabarite->size_x, _region_gabarite->size_y);

	if (_texture_gabarite != nullptr)
	{

		EBrickStyle*
			brick_style = &parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG];

		float
			resize_factor = 1.0f;

		float
			icon_size = max(_texture_gabarite->size_x_in_pixels, _texture_gabarite->size_y_in_pixels);


		//region_size -=  brick_style->offset_for_elements_bottom + brick_style->offset_for_elements_up;

		resize_factor = region_size / icon_size;
		resize_factor = min(resize_factor, 1.0f);

		float offset_x = (region_size - (float)(_texture_gabarite->size_x_in_pixels * resize_factor)) / 2.0f;
		float offset_y = (region_size - (float)(_texture_gabarite->size_y_in_pixels * resize_factor)) / 2.0f;


		sprite_layer_list.push_back
		(
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				_texture_gabarite,

				round(offset_x),
				round(offset_y),
				0.0f,

				round(_texture_gabarite->size_x_in_pixels * resize_factor),
				round(_texture_gabarite->size_y_in_pixels * resize_factor),
				0.0f
			)
		);
	}
	else
	{
		sprite_layer_list.push_back
		(
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				_texture_gabarite,

				round(offset_x),
				round(offset_y),
				0.0f,

				region_size,
				region_size,
				0.0f
			)
		);
	}
}

void EntityButton::make_as_default_button_with_full_icon(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _gabarite)
{
	make_as_default_clickable_button(_region_gabarite, _parent_group, _dap);


	sprite_layer_list.push_back
	(
		ESpriteLayer::create_default_sprite_layer_with_size_and_offset
		(
			_gabarite,

			0.0f,
			0.0f,
			0.0f,

			_region_gabarite->size_x,
			_region_gabarite->size_y,
			0.0f
		)
	);
}

void EntityButton::make_as_default_button_with_icon_and_text(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _gabarite, std::string _text)
{
	make_as_default_clickable_button(_region_gabarite, _parent_group, _dap);

	float
		region_size = min(_region_gabarite->size_x, _region_gabarite->size_y);

	region_size -= parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG].border_texture_size_bottom;
	region_size -= parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG].border_texture_size_up;

	if (_gabarite != nullptr)
	{
		int
			icon_size = max(_gabarite->size_x_in_pixels, _gabarite->size_y_in_pixels);
		icon_size = max(icon_size, 4.0f);



		float
			resize_factor = region_size / icon_size;
		resize_factor = min(resize_factor, 1.0f);

		float icon_size_x = round(_gabarite->size_x_in_pixels * resize_factor);
		float icon_size_y = round(_gabarite->size_y_in_pixels * resize_factor);

		float icon_offset_x = (region_size - icon_size_x) / 2.0f + parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG].border_texture_size_left;
		float icon_offset_y = (region_size - icon_size_y) / 2.0f + parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG].border_texture_size_bottom;

		sprite_layer_list.push_back
		(
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				_gabarite,

				icon_offset_x,
				icon_offset_y,
				0.0f,

				icon_size_x,
				icon_size_y,
				0.0f
			)
		);
	}
	else
	{
		sprite_layer_list.push_back
		(
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				_gabarite,

				parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG].offset_for_elements_left,
				parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG].offset_for_elements_bottom,
				0.0f,

				_region_gabarite->size_y,
				_region_gabarite->size_y,
				0.0f
			)
		);
	}

	ETextArea* jc_text_area;

	if (_gabarite != nullptr)
	{
		jc_text_area = ETextArea::create_centered_to_left_text_area
		(EntityButton::get_last_clickable_area(this), EFont::font_list[0], ELocalisationText::get_localisation_by_key(_text));

		jc_text_area->offset_border[BorderSide::LEFT] = _region_gabarite->size_y;
	}
	else
	{
		jc_text_area = ETextArea::create_centered_text_area
		(EntityButton::get_last_clickable_area(this), EFont::font_list[0], ELocalisationText::get_localisation_by_key(_text));

		jc_text_area->offset_border[BorderSide::LEFT] = 0.0f;
	}

	main_text_area = jc_text_area;




	jc_text_area->change_text(_text);

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);
}

void EntityButton::make_as_default_button_with_icon_and_localisation_by_key(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _gabarite, std::string _key)
{
	ELocalisationText
		l_text = ELocalisationText(ELocalisationText::get_localisation_by_key(_key));



	make_as_default_button_with_icon_and_text
	(
		_region_gabarite,
		_parent_group,
		_dap,
		_gabarite,
		l_text.localisations[ELocalisationText::active_localisation]
	);



	main_text_area->localisation_text = l_text;

}

void EntityButton::make_default_bool_switcher_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _gabarite_on, ETextureGabarite* _gabarite_off, bool* _target_bool)
{


	make_as_default_clickable_button(_region_gabarite, _parent_group, _dap);

	auto data_container = new EDataContainer_Button_BoolSwitcher();


	data_container->texture_gabarite_on = _gabarite_on;
	data_container->texture_gabarite_off = _gabarite_off;

	if (_target_bool != nullptr)
	{
		data_container->target_value = _target_bool;
	}
	else
	{
		//EInputCore::logger_simple_error("Target bool is NULL, generate new bool!");
		data_container->target_value = new bool(true);
	}




	EntityButton::get_last_custom_data(this)->data_container = data_container;
	EntityButton::get_last_custom_data(this)->actions_on_draw.insert
	(
		EntityButton::get_last_custom_data(this)->actions_on_draw.begin(),
		&EDataActionCollection::action_draw_boolean_switcher
	);
}









//void EntityButtonVariantRouter::make_default_router_variant_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap)
//{
//	make_as_default_button_with_icon
//	(
//		_region_gabarite,
//		_parent_group,
//		_dap,
//		nullptr
//	);
//
//	//parent_filter_block = static_cast<EButtonGroupFilterBlock*>(_parent_group);
//
//	layer_with_icon = sprite_layer_list.back();
//
//	ETextArea* jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(this), EFont::font_list[0], ELocalisationText());
//	pointer_to_text_area = jc_text_area;
//
//	jc_text_area->can_be_edited = false;
//	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);
//}

void EntityButton::make_default_bool_switcher_button_with_unedible_text(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _gabarite_on, ETextureGabarite* _gabarite_off, ELocalisationText _ltext, bool* _target_bool)
{
	make_default_button_with_unedible_text(_region_gabarite, _parent_group, _dap, _ltext);
	main_text_area->offset_border[BorderSide::LEFT] = _region_gabarite->size_y;
	main_text_area->set_align_to_left_middle();

	auto data_container = new EDataContainer_Button_BoolSwitcher();


	data_container->texture_gabarite_on = _gabarite_on;
	data_container->texture_gabarite_off = _gabarite_off;

	if (_target_bool != nullptr)
	{
		data_container->target_value = _target_bool;
	}
	else
	{
		//EInputCore::logger_simple_error("Target bool is NULL, generate new bool!");
		data_container->target_value = new bool(true);
	}

	if ((data_container->target_value != nullptr) && (*data_container->target_value))
	{
		main_text_area->set_color(1.0f, 0.8f, 0.6f, 1.0f);
	}
	else
	{
		main_text_area->set_color(0.5f, 0.45f, 0.40f, 1.0f);
	}




	EntityButton::get_last_custom_data(this)->data_container = data_container;
	EntityButton::get_last_custom_data(this)->actions_on_draw.insert
	(
		EntityButton::get_last_custom_data(this)->actions_on_draw.begin(),
		&EDataActionCollection::action_draw_boolean_switcher
	);
}

void EntityButton::make_as_default_router_variant_button(ERegionGabarite* _region_gabarite)
{
	make_as_default_button_with_icon_and_text(_region_gabarite, parent_button_group, &EDataActionCollection::action_rotate_variant, nullptr, "");

	static_cast<EntityButtonVariantRouter*>(this)->layer_with_icon = sprite_layer_list.back();
	static_cast<EntityButtonVariantRouter*>(this)->pointer_to_text_area = main_text_area;

	main_text_area->can_be_edited = false;
}

bool Entity::is_suppressed()
{
	if
	(
		(suppressor != nullptr)
		&&
		(!(*suppressor ^ invert_suppression))//T^F F^T
	)
	{return true;}

	return false;
}

EClickableArea* EntityButton::create_clickable_region_witch_sprtite_layer_and_icon(ERegionGabarite* _region_gabarite, ETextureGabarite* _icon, data_action_pointer _action)
{
	EClickableArea*
		new_clickable_region = EClickableArea::create_default_clickable_region
		(
			_region_gabarite,
			this,
			EntityButton::get_last_custom_data(this)
		);

	if (_action != nullptr)
	{
		new_clickable_region->actions_on_click_list.push_back(_action);
	}

	new_clickable_region->region_gabarite->offset_by_parent_size_x = 0.0f;
	new_clickable_region->region_gabarite->offset_by_parent_size_y = 0.0f;

	new_clickable_region->region_gabarite->offset_by_size_x = 0.0f;
	new_clickable_region->region_gabarite->offset_by_size_y = 0.0f;

	new_clickable_region->region_gabarite->offset_by_pixels_x = 0.0f;
	new_clickable_region->region_gabarite->offset_by_pixels_y = 0.0f;

	main_custom_data->clickable_area_list.push_back(new_clickable_region);
	main_clickable_area->region_gabarite->add_child_to_this_region(new_clickable_region->region_gabarite);


	//////////////////////////////////

	float resize_factor = 0.0f;
	float offset_x = 0.0f;
	float offset_y = 0.0f;
	{
		resize_factor = (new_clickable_region->region_gabarite->size_y) / max(_icon->size_x_in_pixels, _icon->size_y_in_pixels);
		resize_factor = min(resize_factor, 1.0f);

		offset_x = ((new_clickable_region->region_gabarite->size_y) - _icon->size_x_in_pixels * resize_factor) / 2.0f;
		offset_y = ((new_clickable_region->region_gabarite->size_y) - _icon->size_y_in_pixels * resize_factor) / 2.0f;

		ESpriteLayer* new_sprite_layer =
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				_icon,

				0.0f,
				0.0f,
				0.0f,

				_icon->size_x_in_pixels * resize_factor,
				_icon->size_y_in_pixels * resize_factor,
				0.0f
			);

		new_clickable_region->sprite_layer_list.push_back(new_sprite_layer);

		//second_button_layer->make_as_PBR();
	}
	//////////////////////////////////

	return new_clickable_region;
}

EClickableArea* EntityButton::add_close_circle(data_action_pointer _dap)
{

	//add new clickable area (close X)
	EClickableArea*
		close_clickable_area = EClickableArea::create_default_clickable_region
		(
			new ERegionGabarite(20.0f, 20.0f),
			this,
			EntityButton::get_last_custom_data(this)
		);

	if (_dap != nullptr)
	{
		close_clickable_area->actions_on_click_list.push_back(_dap);
	}

	close_clickable_area->region_gabarite->offset_by_parent_size_x = 1.0f;
	close_clickable_area->region_gabarite->offset_by_parent_size_y = 1.0f;

	close_clickable_area->region_gabarite->offset_by_size_x = -1.0f;
	close_clickable_area->region_gabarite->offset_by_size_y = -1.0f;

	close_clickable_area->region_gabarite->offset_by_pixels_x = -3.0f;
	close_clickable_area->region_gabarite->offset_by_pixels_y = -3.0f;

	close_clickable_area->draw_only_is_specific_region_overlapped = this->main_clickable_area->region_gabarite;

	this->main_custom_data->clickable_area_list.push_back(close_clickable_area);
	this->main_clickable_area->region_gabarite->add_child_to_this_region(close_clickable_area->region_gabarite);


	//////////////////////////////////
	ETextureGabarite*
		close_icon = NS_DefaultGabarites::texture_close_circle;

	float resize_factor = 0.0f;
	float offset_x = 0.0f;
	float offset_y = 0.0f;
	{
		resize_factor = (close_clickable_area->region_gabarite->size_y) / max(close_icon->size_x_in_pixels, close_icon->size_y_in_pixels);
		resize_factor = min(resize_factor, 1.0f);

		offset_x = ((close_clickable_area->region_gabarite->size_y) - close_icon->size_x_in_pixels * resize_factor) / 2.0f;
		offset_y = ((close_clickable_area->region_gabarite->size_y) - close_icon->size_y_in_pixels * resize_factor) / 2.0f;

		ESpriteLayer* third_sprite_layer =
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				close_icon,

				0.0f,
				0.0f,
				0.0f,

				close_icon->size_x_in_pixels * resize_factor,
				close_icon->size_y_in_pixels * resize_factor,
				0.0f
			);

		close_clickable_area->sprite_layer_list.push_back(third_sprite_layer);

		//second_button_layer->make_as_PBR();
	}
	//////////////////////////////////

	return close_clickable_area;
}

bool EntityButton::can_get_access_to_style()
{
	return false;
}

bool EntityButton::button_in_culling_gabarites()
{
	//return true;
	if (parent_button_group == nullptr) { return false; }

	return
		(
			(world_position_y + button_gabarite->phantom_translate_y <= parent_button_group->higher_culling_line_for_group)
			&&
			(world_position_y + button_gabarite->phantom_translate_y + button_gabarite->size_y >= parent_button_group->lower_culling_line_for_group)
			);
}


void EntityButton::draw()
{
	//		SIMPLE BACKROUND (transparent black rectangle)
	if (have_simple_bg)
	{
		NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_BLACK, 0.75f);
		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			button_gabarite->world_position_x,

			//y pos
			button_gabarite->world_position_y,

			button_gabarite->size_x,
			button_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
	}

	Entity::draw();



	if
	(
		(suppressor != nullptr)
		&&
		(!(*suppressor ^ invert_suppression))//T^F F^T
	)
	{
		NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_DARK_GREY, 0.85f);
		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			button_gabarite->world_position_x,

			//y pos
			button_gabarite->world_position_y,

			button_gabarite->size_x,
			button_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
	}

	if ((max_highlight_time > 0.0f) && (highlight_time > 0.0f))
	{
		NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, highlight_time / max_highlight_time);
		ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
			NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

			//x pos
			button_gabarite->world_position_x,

			//y pos
			button_gabarite->world_position_y,

			button_gabarite->size_x,
			button_gabarite->size_y,

			NS_DefaultGabarites::texture_gabarite_white_pixel
		);


	}
}

void EntityButton::draw_second_pass()
{
	Entity::draw_second_pass();

	if
		(
			(button_suppressor != nullptr)
			&&
			(EClickableArea::active_clickable_region == main_clickable_area)
			&&
			(!(*suppressor ^ invert_suppression))
			)
	{
		unsigned long long timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		//EInputCore::logger_param("timer", timer % 100);

		if (timer % 700 <= 350)
		{
			button_suppressor->set_highlight(0.2f, 0.2f);

			NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_GREEN, 0.5f);
			ERenderBatcher::if_have_space_for_data(NS_EGraphicCore::default_batcher_for_drawing, 1);
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				NS_EGraphicCore::default_batcher_for_drawing->vertex_buffer,
				NS_EGraphicCore::default_batcher_for_drawing->last_vertice_buffer_index,

				//x pos
				button_suppressor->button_gabarite->world_position_x,

				//y pos
				button_suppressor->button_gabarite->world_position_y,

				button_suppressor->button_gabarite->size_x,
				button_suppressor->button_gabarite->size_y,

				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}
	}
}

void EntityButton::update(float _d)
{
	//if ((suppressor == nullptr) || (*suppressor))
	//{

	Entity::update(_d);


	if (highlight_time > 0.0f)
	{
		using namespace std::chrono;
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		if (ms - highlight_timestamp > (milliseconds)(1000)) { highlight_time = 0.0f; }
		highlight_time -= _d;
	}

	if ((main_clickable_area != nullptr) && (main_clickable_area->hover_time >= 0.50f) && (description_container != nullptr))
	{
		if (attached_description == nullptr)
		{
			description_container->create_description();
		}

		attached_description->autodelete_time = 0.1f;
	}

	if
	(
			(attached_description != nullptr)
			&&
			(!button_gabarite->overlapped_by_mouse())
	)
	{
		destroy_attached_description();
	}

	//HOTKEY
	if (!is_suppressed())
	{
		for (EHotKeyManager hotkey : hotkey_list)
		{
			if
				(
					(hotkey.parent_button != nullptr)
					&&
					(
						(
							(hotkey.require_main_button > 0)
							&&
							(EInputCore::key_pressed(hotkey.require_main_button))
							)
						&&
						(
							(hotkey.require_main_button <= 0)
							||
							(EInputCore::key_pressed_once(hotkey.require_secondare_button))
							)
						)
					)
			{
				for (ECustomData* cd : custom_data_list)
					for (EClickableArea* ca : cd->clickable_area_list)
						for (data_action_pointer dap : ca->actions_on_click_list)
							if
							(
								(dap != nullptr)
							)
							{
								EInputCore::logger_simple_info("call [actions on click list]");
								dap(this, cd, _d);
							}
			}
		}
	}

	if
	(
		(EInputCore::key_pressed_once(GLFW_KEY_F10))
		&&
		(EClickableArea::active_clickable_region == main_clickable_area)
	)
	{
		EButtonGroupButtonDebugger* button_bebugger = open_button_debugger();
	}
	
	//}
}

EntityButton::EntityButton()
{
	if (debug_deleting) EInputCore::logger_simple_info("<Entity Button created>");
}

EntityButton::~EntityButton()
{
	if (debug_deleting) EInputCore::logger_simple_info("try deleting entity button");

	if (debug_deleting) EInputCore::logger_simple_info("Called <EntityButton> destructor");

	if (button_gabarite != nullptr)
	{
		(button_gabarite->pointers_to_this_object)--;

		if (debug_deleting) EInputCore::logger_param("pointers to button gabarite left", button_gabarite->pointers_to_this_object);

		if (button_gabarite->pointers_to_this_object <= 0)
		{
			if (debug_deleting) EInputCore::logger_simple_info("try delete button gabarite");

			if (!disable_deleting)
			{
				delete button_gabarite;
			}

			if (debug_deleting) EInputCore::logger_simple_success("delete button gabarite");
		}
	}


	if (debug_deleting) EInputCore::logger_simple_info("try clear and shrink action on change style");
	action_on_generate_vertex_buffer.clear();
	action_on_generate_vertex_buffer.shrink_to_fit();
	if (debug_deleting) EInputCore::logger_simple_success("clear and shrink action on change style");

	if (description_container != nullptr)
	{
		delete description_container;
	}

	//this;

	if (attached_description != nullptr)
	{
		//delete attached_description;
		attached_description->block_need_remove = true;
	}
	//EInputCore::logger_simple_try("delete entity button");

	//if ((parent_button_group != nullptr) && (!parent_button_group->need_remove))
	//{
	//	//EButtonGroup::change_group(parent_button_group->root_group);
	//	EButtonGroup::change_group(parent_button_group->parent_group);
	//	parent_button_group->refresh_buttons_in_group();
	//}
}

void action_generate_vertex_slider(EntityButton* _but, EGUIStyle* _style)
{
	NS_ERenderCollection::set_brick_borders_and_subdivisions(_style->brick_style[BrickStyleID::SLIDER_BG]);

	ERegionGabarite::temporary_gabarite->set_region_offset_and_size
	(
		0.0f,
		0.0f,
		0.0f,
		_but->parent_button_group->selected_style->brick_style[0].main_texture->size_x_in_pixels,
		_but->parent_button_group->region_gabarite->size_y - _but->parent_button_group->group_offset_for_content_bottom - _but->parent_button_group->group_offset_for_content_up
	);

	//offset by button_group
	float total_group_height
		=
		_but->parent_button_group->region_gabarite->size_y
		-
		_but->parent_button_group->group_offset_for_content_bottom
		-
		_but->parent_button_group->group_offset_for_content_up;

	//float current_height_percent
	//=
	//(
	//	*_but->custom_data_list[0]->clickable_region_list[0]->region->offset_y
	//	-
	//	*_but->parent_button_group->border_bottom
	//)
	///
	//(
	//	total_group_height
	//	-
	//	*_but->custom_data_list[0]->clickable_region_list[0]->region->size_y
	//);






	NS_ERenderCollection::temporary_sprites = false;
	NS_ERenderCollection::generate_brick_texture
	(
		ERegionGabarite::temporary_gabarite,
		_but->sprite_layer_list[0],
		_style->brick_style[BrickStyleID::SLIDER_BG].main_texture,
		_style->brick_style[BrickStyleID::SLIDER_BG].normal_map_texture,
		_style->brick_style[BrickStyleID::SLIDER_BG].gloss_map_texture
	);

	_but->sprite_layer_list[0]->offset_y = _but->parent_button_group->group_offset_for_content_bottom;
	_but->sprite_layer_list[0]->sprite_layer_set_world_position(0.0f, 0.0f, 0.0f);
	_but->sprite_layer_list[0]->generate_vertex_buffer_for_sprite_layer("init bg");

	//*_but->custom_data_list[0]->clickable_region_list[0]->region->offset_y
	//=
	//*_style->offset_border_bottom
	//+
	//(
	//	(total_group_height - *_style->slider_head_inactive->size_y_in_pixels)
	//	*
	//	current_height_percent
	//);

	_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_x = _style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture->size_x_in_pixels;

	_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_y = _style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture->size_y_in_pixels;

	_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->offset_y
		=
		round
		(
			(
				total_group_height
				-
				_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_y
				)
			*
			*(((EDataContainerScrollBar*)_but->custom_data_list[0]->data_container)->current_percent)
			+
			_but->parent_button_group->group_offset_for_content_bottom
		)
		;

	//change clickable region size y


	//change button gabarites size y
	//_but->button_gabarite->size_x = _style->slider_inactive->main_texture->size_x_in_pixels;
	//_but->button_gabarite->size_y = _style->slider_inactive->main_texture->size_y_in_pixels;

	_but->custom_data_list[0]->get_sprite_by_id(0, 0, 0, 0)->set_texture_gabarite
	(
		_style->brick_style[BrickStyleID::SLIDER_INACTIVE].main_texture,
		_style->brick_style[BrickStyleID::SLIDER_INACTIVE].normal_map_texture,
		_style->brick_style[BrickStyleID::SLIDER_INACTIVE].gloss_map_texture
	);

	_but->custom_data_list[0]->get_sprite_by_id(0, 0, 0, 1)->set_texture_gabarite
	(
		_style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture,
		_style->brick_style[BrickStyleID::SLIDER_ACTIVE].normal_map_texture,
		_style->brick_style[BrickStyleID::SLIDER_ACTIVE].gloss_map_texture
	);



}

void action_generate_brick_bg_for_button(EntityButton* _but, EGUIStyle* _style)
{
	EntityButton::button_generate_brick_bg(_but, _style);
}

void action_generate_vertex_for_horizontal_named_slider(EntityButton* _but, EGUIStyle* _style)
{
	EDataContainer_VerticalNamedSlider* data = static_cast<EDataContainer_VerticalNamedSlider*>(_but->main_custom_data->data_container);

	data->slider_style = _style;

	//data->pointer_to_digit_text_area->offset_border[BorderSide::LEFT]		= 0.0f;
	//data->pointer_to_text_area->offset_border[BorderSide::LEFT]			= 0.0f;
	//data->pointer_to_digit_section_sprite_layer

	//DIGIN SECTION
	NS_ERenderCollection::set_brick_borders_and_subdivisions(_style->brick_style[BrickStyleID::BUTTON_BG]);
	ERegionGabarite::temporary_gabarite->set_region_offset_and_size
	(
		_but->world_position_x + 3.0f,
		_but->world_position_y + 3.0f,
		0.0f,

		30.0f,
		16.0f
	);

	NS_ERenderCollection::generate_brick_texture
	(
		ERegionGabarite::temporary_gabarite,
		data->pointer_to_digit_section_sprite_layer,
		_style->brick_style[BrickStyleID::BUTTON_BG].main_texture,
		_style->brick_style[BrickStyleID::BUTTON_BG].normal_map_texture,
		_style->brick_style[BrickStyleID::BUTTON_BG].gloss_map_texture
	);

	data->operable_area_size_x = _but->button_gabarite->size_x - _style->brick_style[BrickStyleID::ROUND_SLIDER].main_texture->size_x_in_pixels - 33.0f;
	//SLIDER LINE
	//data->pointer_to_brick_line_sprite_layer->offset_x = 30.0f;
	NS_ERenderCollection::set_brick_borders_and_subdivisions(_style->brick_style[BrickStyleID::SLIDER_BG]);
	ERegionGabarite::temporary_gabarite->set_region_offset_and_size
	(
		_but->world_position_x + 33.0f,
		_but->world_position_y + 3.0f,
		0.0f,

		_but->button_gabarite->size_x - 36.0f,
		15.0f
	);

	NS_ERenderCollection::generate_brick_texture
	(
		ERegionGabarite::temporary_gabarite,
		data->pointer_to_brick_line_sprite_layer,
		_style->brick_style[BrickStyleID::SLIDER_BG].main_texture,
		_style->brick_style[BrickStyleID::SLIDER_BG].normal_map_texture,
		_style->brick_style[BrickStyleID::SLIDER_BG].gloss_map_texture
	);


}

void action_generate_vertex_for_vertical_slider(EntityButton* _but, EGUIStyle* _style)
{
	NS_ERenderCollection::set_brick_borders_and_subdivisions(_style->brick_style[BrickStyleID::SLIDER_BG]);



	//offset by button_group
	float total_group_height
		=
		_but->parent_button_group->region_gabarite->size_y
		-
		_but->parent_button_group->group_offset_for_content_bottom
		-
		_but->parent_button_group->group_offset_for_content_up;


	ERegionGabarite::temporary_gabarite->set_region_offset_and_size
	(
		_but->world_position_x,
		_but->world_position_y,
		0.0f,
		_but->parent_button_group->selected_style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture->size_x_in_pixels,
		total_group_height
	);



	if (!_but->sprite_layer_list.empty())
	{
		NS_ERenderCollection::temporary_sprites = false;
		NS_ERenderCollection::generate_brick_texture
		(
			ERegionGabarite::temporary_gabarite,
			_but->sprite_layer_list[0],
			_style->brick_style[BrickStyleID::SLIDER_BG].main_texture,
			_style->brick_style[BrickStyleID::SLIDER_BG].normal_map_texture,
			_style->brick_style[BrickStyleID::SLIDER_BG].gloss_map_texture
		);
	}

	if (!_but->custom_data_list.empty())
	{
		_but->offset_y = 10.0f;
		_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_x = _style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture->size_x_in_pixels;
		_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_y = total_group_height;
	}



	//change clickable region size y


	//change button gabarites size y
	_but->button_gabarite->size_x = _style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture->size_x_in_pixels;
	_but->button_gabarite->size_y = total_group_height;

	EntityButtonVerticalSlider*
		slider = static_cast<EntityButtonVerticalSlider*>(_but);
	slider->workspace_height = total_group_height - _style->brick_style[BrickStyleID::SLIDER_ACTIVE].main_texture->size_y_in_pixels;
	slider->brick_style_active_slider = &_style->brick_style[BrickStyleID::SLIDER_ACTIVE];
	slider->slider_inactive = &_style->brick_style[BrickStyleID::SLIDER_INACTIVE];

	if (_but->parent_button_group->child_align_direction == ChildElementsAlignDirection::BOTTOM_TO_TOP)
	{
		slider->min_value = 0.0f;

		slider->max_value = -(_but->parent_button_group->final_highest_point_y - _but->parent_button_group->region_gabarite->size_y + _but->parent_button_group->group_offset_for_content_up);
		slider->max_value = min(slider->max_value, 0.0f);
	}
	else
		if (_but->parent_button_group->child_align_direction == ChildElementsAlignDirection::TOP_TO_BOTTOM)
		{
			slider->min_value = (_but->parent_button_group->final_highest_point_y - _but->parent_button_group->region_gabarite->size_y + _but->parent_button_group->group_offset_for_content_up);
			slider->min_value = max(slider->min_value, 0.0f);

			slider->max_value = 0.0f;

		}
}


EntityButtonVariantRouter::~EntityButtonVariantRouter()
{
	if (debug_deleting) {
		EInputCore::logger_simple_info("pre deleting EntityButtonVariantRouter");
	}

	if (opened_router_group != nullptr)
	{
		opened_router_group->block_need_remove = true;

		opened_router_group = nullptr;
	}

	if (!disable_deleting)
		for (RouterVariant* rv : router_variant_list)
			if (rv != nullptr)
			{
				delete rv;
			}
	router_variant_list.clear();
	router_variant_list.shrink_to_fit();

	if (debug_deleting) { EInputCore::logger_simple_info("deleting EntityButtonVariantRouter"); }

}

void EntityButtonVariantRouter::select_variant(int _variant_id)
{
	if (!router_variant_list.empty())
	{
		//_variant_id = std::clamp(_variant_id, 0, (int)(router_variant_list.size() - 1));

		selected_variant = std::clamp(_variant_id, 0, (int)(router_variant_list.size() - 1));

		if (layer_with_icon != nullptr)
		{
			//6999999999999999999999999999999, 10 november 2022, cat, stop, pls



			if (router_variant_list[selected_variant]->texture != nullptr)
				{

					EBrickStyle*
						brick_style = &parent_button_group->selected_style->brick_style[BrickStyleID::BUTTON_BG];

					float
						texture_size
						=
						max
						(
							router_variant_list[selected_variant]->texture->size_x_in_pixels,
							router_variant_list[selected_variant]->texture->size_y_in_pixels
						);

					float
						available_region_size = min(button_gabarite->size_x, button_gabarite->size_y);

					available_region_size -= brick_style->border_texture_size_bottom;
					available_region_size -= brick_style->border_texture_size_up;
					//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->main_texture = router_variant_list[selected_variant].texture;

					float
						resize_factor = available_region_size / texture_size;

					float
						final_icon_size_x = router_variant_list[selected_variant]->texture->size_x_in_pixels * resize_factor;

					float
						final_icon_size_y = router_variant_list[selected_variant]->texture->size_y_in_pixels * resize_factor;

					float offset_x = brick_style->border_texture_size_left + (available_region_size - final_icon_size_x) / 2.0f;
					float offset_y = brick_style->border_texture_size_bottom + (available_region_size - final_icon_size_y) / 2.0f;

					//float resize_factor =
					//	min
					//	(
					//		(button_gabarite->size_x - brick_style->border_texture_size_bottom - brick_style->border_texture_size_up) / (float)(router_variant_list[selected_variant]->texture->size_x_in_pixels)
					//		,
					//		(button_gabarite->size_y - brick_style->border_texture_size_left - brick_style->border_texture_size_right) / (float)(router_variant_list[selected_variant]->texture->size_y_in_pixels)
					//	);

					//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->offset_x = *brick_style->side_offset_left;
					//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->offset_y = *brick_style->side_offset_bottom;
					//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->offset_z = 0.0f;


					layer_with_icon->sprite_frame_list[0]->sprite_list[0]->size_texture_gabarite_to_this_size_and_offset
					(
						router_variant_list[selected_variant]->texture,
						nullptr,
						nullptr,

						round(offset_x),
						round(offset_y),
						0.0f,

						round(final_icon_size_x),
						round(final_icon_size_y),
						0.0f
					);

					pointer_to_text_area->offset_border[BorderSide::LEFT] = button_gabarite->size_y;
				}
			else
			{
				pointer_to_text_area->offset_border[BorderSide::LEFT] = 0.0f;
			}
			
			pointer_to_text_area->offset_border[BorderSide::RIGHT] = 0.0f;


			
			have_phantom_draw = true;
			//redraw
			//set_world_positions(world_position_x, world_position_y, world_position_z);
			//generate_vertex_buffer_for_all_sprite_layers();

		}
		


		pointer_to_text_area->localisation_text = router_variant_list[selected_variant]->router_localisation;

		if (router_variant_list[selected_variant]->text_color != nullptr)
		{
			pointer_to_text_area->stored_color = *(router_variant_list[selected_variant]->text_color);
			pointer_to_text_area->color = *(router_variant_list[selected_variant]->text_color);
		}

		pointer_to_text_area->change_text(pointer_to_text_area->localisation_text.localisations[ELocalisationText::active_localisation]);

		if (target_bool_value != nullptr)	{*target_bool_value = (bool)(selected_variant);}

		if (target_int_value != nullptr)	{*target_int_value = selected_variant;}
	}
	else
	{

		pointer_to_text_area->localisation_text = ELocalisationText::generate_localization_with_base_name("<?>");

		have_phantom_draw = true;
	}
}

void EntityButtonVariantRouter::select_variant_by_icon(ETextureGabarite* _icon)
{
	for (int i = 0; i < router_variant_list.size(); i++)
	{
		if (router_variant_list[i]->texture == _icon)
		{
			select_variant(i);

			break;
		}
	}
}

void EntityButtonVariantRouter::select_variant_by_base_name(std::string& _base_name)
{
	select_variant(search_id_by_base_name(_base_name));
}

void EntityButtonVariantRouter::select_variant_by_base_name_from_window_buttons(std::string& _base_name)
{
	select_variant(search_id_by_base_name_window_variant(_base_name));
}

void EntityButtonVariantRouter::reselect_variant()
{
	select_variant(selected_variant);
}

int EntityButtonVariantRouter::search_id_by_base_name(std::string& _base_name)
{
	//int id = 0;

	for (int i = 0; i < router_variant_list.size(); i++)
	{
		if (router_variant_list[i]->router_localisation.base_name == _base_name)
		{
			return i;
		}

		//id++;
	}
	return -1;
}

int EntityButtonVariantRouter::search_id_by_base_name_window_variant(std::string& _base_name)
{
	//int id = 0;

	for (int i = 0; i < router_variant_list.size(); i++)
	{
		if (router_variant_list[i]->localisation_for_select_window.base_name == _base_name)
		{
			return i;
		}

		//id++;
	}

	return -1;
}

std::string EntityButtonVariantRouter::return_base_text_from_selected_router()
{
	return router_variant_list[selected_variant]->router_localisation.base_name;
}

RouterVariant* EntityButtonVariantRouter::add_router_variant_by_text_and_color(std::string _text, float _r, float _g, float _b, float _a)
{
	RouterVariant*
	router_variant = new RouterVariant();

	router_variant->router_localisation = ELocalisationText::generate_localization_with_base_name(_text);

	router_variant->text_color = new HSVRGBAColor();
	router_variant->text_color->set_color_RGBA(_r, _g, _b, _a);

	router_variant_list.push_back(router_variant);

	return router_variant;
}

RouterVariant* EntityButtonVariantRouter::add_router_variant_with_localization_key_and_color(std::string _key, float _r, float _g, float _b, float _a)
{
	RouterVariant*
		router_variant = new RouterVariant();

	router_variant->router_localisation = ELocalisationText::get_localisation_by_key(_key);

	router_variant->text_color = new HSVRGBAColor();
	router_variant->text_color->set_color_RGBA(_r, _g, _b, _a);

	router_variant_list.push_back(router_variant);

	return router_variant;
}

RouterVariant* EntityButtonVariantRouter::add_router_variant_with_localization_key_color_and_icon(std::string _key, std::string _key_for_window, float _r, float _g, float _b, float _a, ETextureGabarite* _icon)
{
	RouterVariant*
		router_variant = new RouterVariant();

	router_variant->router_localisation = ELocalisationText::get_localisation_by_key(_key);

	if (_key_for_window != "")
	{
		router_variant->localisation_for_select_window = ELocalisationText::get_localisation_by_key(_key_for_window);
	}

	router_variant->text_color = new HSVRGBAColor();
	router_variant->text_color->set_color_RGBA(_r, _g, _b, _a);

	router_variant_list.push_back(router_variant);

	router_variant->texture = _icon;

	return router_variant;
}

RouterVariant* EntityButtonVariantRouter::add_router_variant_with_localization_color_and_icon(ELocalisationText* _ltext, std::string _key_for_window, float _r, float _g, float _b, float _a, ETextureGabarite* _icon)
{
	RouterVariant*
	router_variant = new RouterVariant();

	router_variant->router_localisation = *_ltext;

	if (_key_for_window != "")
	{
		router_variant->localisation_for_select_window = ELocalisationText::get_localisation_by_key(_key_for_window);
	}

	router_variant->text_color = new HSVRGBAColor();
	router_variant->text_color->set_color_RGBA(_r, _g, _b, _a);

	router_variant_list.push_back(router_variant);

	router_variant->texture = _icon;

	return router_variant;
}

RouterVariant::~RouterVariant()
{
	if (!do_not_delete_me)
	{
		//EInputCore::logger_simple_info("~RouterVariant");
		//if ((localisation_for_select_window != nullptr) && (router_localisation != localisation_for_select_window)){ delete localisation_for_select_window; }
		//if (router_localisation != nullptr)					{ delete router_localisation; router_localisation = nullptr;}
		//if (color != nullptr)							{ delete color; }


		//EInputCore::logger_simple_success("~RouterVariant deleted");
	}
}

EntityButtonVerticalSlider::~EntityButtonVerticalSlider()
{
	if (debug_deleting) { EInputCore::logger_simple_info("deleting EntityButtonVerticalSlider"); }
}

EntityButtonLocalisationSelector::~EntityButtonLocalisationSelector()
{
}

EntityButtonConfirmAction::EntityButtonConfirmAction()
{
}

EntityButtonConfirmAction::~EntityButtonConfirmAction()
{
}

EntityButtonColorButton::~EntityButtonColorButton()
{
	if (selected_mode == ColorButtonMode::CBM_SELECT_COLOR)
	{
		Helper::registered_color_list.erase
		(
			std::find
			(
				Helper::registered_color_list.begin(),
				Helper::registered_color_list.end(),
				parent_color_collection
			)
		);

		delete parent_color_collection;
	}

	if (debug_deleting) { EInputCore::logger_simple_info("deleting EntityButtonColorButton"); }
}

EntityButtonVariantRouterSelector::~EntityButtonVariantRouterSelector()
{
}

EntityButtonMultiSearch::~EntityButtonMultiSearch()
{
}

EntityButtonOpenURL::EntityButtonOpenURL()
{
}

EntityButtonOpenURL::~EntityButtonOpenURL()
{
}

DescriptionContainer::DescriptionContainer()
{
}

DescriptionContainer::DescriptionContainer(float _size_x, float _size_y)
{
	size_x = _size_x;
	size_y = _size_y;
}

void DescriptionContainer::create_description()
{

}

void DescriptionContainer::init_description(EButtonGroup* _group)
{
	float borders_size_x = _group->group_offset_for_content_left + _group->group_offset_for_content_right;
	float borders_size_y = _group->group_offset_for_content_bottom + _group->group_offset_for_content_up;

	_group->region_gabarite->offset_x = max(parent_button->button_gabarite->world_position_x, borders_size_x + 3.0f);
	_group->region_gabarite->offset_x = min(_group->region_gabarite->offset_x, NS_EGraphicCore::SCREEN_WIDTH / NS_EGraphicCore::current_zoom - _group->region_gabarite->size_x - borders_size_x - 3.0f);

	if (parent_button->button_gabarite->world_position_y + parent_button->button_gabarite->size_y + size_y + borders_size_y + 6.0f <= NS_EGraphicCore::SCREEN_HEIGHT / NS_EGraphicCore::current_zoom)
	{
		_group->region_gabarite->offset_y
			=
			parent_button->button_gabarite->world_position_y
			+
			parent_button->button_gabarite->size_y
			+
			borders_size_y
			+
			3.0f;
	}
	else
	{
		_group->region_gabarite->offset_y = max(parent_button->button_gabarite->world_position_y - size_y - borders_size_y - 3.0f, 3.0f);
	}


}

DescriptionContainerDefault::~DescriptionContainerDefault()
{
}

void DescriptionContainerDefault::create_description()
{
	//EInputCore::logger_simple_info("@");
	DescriptionContainer::create_description();

	if (parent_button != nullptr)
	{

		EButtonGroup*
			description_group = new EButtonGroup
			(
				new ERegionGabarite
				(
					size_x,
					size_y
				)
			);

		description_group->init_as_root_group(parent_button->parent_button_group->root_group->parent_window);
		description_group->need_refresh = true;

		if
		(
			(parent_button->suppressor == nullptr)
			||
			(*(parent_button->suppressor) ^ (parent_button->invert_suppression))//T^F F^T
		)
		{
			if (!replacer_list.empty())
			{
				ELocalisationText
					temp_ltext = localisation_text;

				for (int i = 0; i < NSW_languages_count; i++)
				{
					for (EStringReplacer replacer : replacer_list)
					{
						size_t start_pos = 0;
						while ((start_pos = temp_ltext.localisations[i].find(replacer.what_replaced, start_pos)) != std::string::npos)
						{
							temp_ltext.localisations[i].replace(start_pos, replacer.what_replaced.length(), replacer.result_string);
							start_pos += replacer.result_string.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
						}
					}
				}

				description_group->add_default_clickable_region_with_text_area(temp_ltext);
			}
			else
			{
				description_group->add_default_clickable_region_with_text_area(localisation_text);
			}
		}
		else
		{
			description_group->add_default_clickable_region_with_text_area(ELocalisationText::get_localisation_by_key("description_this_button_is_supressed"));
		}

		float additional_left_offset = 8.0f;

		description_group->main_clickable_area->text_area->offset_by_gabarite_size_x = 0.0f;
		description_group->main_clickable_area->text_area->offset_by_text_size_x = 0.0f;

		description_group->main_clickable_area->text_area->text_have_background = false;
		description_group->main_clickable_area->text_area->offset_border[BorderSide::LEFT] = additional_left_offset;

		float max_row_w = 0.0f;

		for (std::string* row_element : description_group->clickable_area_list[0]->text_area->row)
		{
			max_row_w = max(max_row_w, description_group->clickable_area_list[0]->text_area->get_row_width(row_element) + additional_left_offset);
		}

		size_x = max_row_w;
		size_x = std::clamp(size_x, 200.0f, 600.0f);
		description_group->region_gabarite->size_x = size_x;
		description_group->base_width = size_x;

		size_y = description_group->clickable_area_list[0]->text_area->row.size() * EFont::font_list[0]->lineheight;
		size_y = std::clamp(size_y, 50.0f, 600.0f);
		description_group->region_gabarite->size_y = size_y;
		description_group->base_height = size_y;

		parent_button->parent_button_group->root_group->parent_window->button_group_list.push_back(description_group);
		parent_button->attached_description = description_group;

		init_description(description_group);
	}
}

DescriptionContainerHelpDescriptionImage::~DescriptionContainerHelpDescriptionImage()
{
}

void DescriptionContainerHelpDescriptionImage::create_description()
{
	if (parent_button != nullptr)
	{

		size_x = stored_image[ELocalisationText::active_localisation]->size_x_in_pixels;
		size_y = stored_image[ELocalisationText::active_localisation]->size_y_in_pixels;

		EButtonGroup*
			description_group = new EButtonGroup
			(
				new ERegionGabarite
				(
					size_x,
					size_y
				)
			);

		description_group->init_as_root_group(parent_button->parent_button_group->root_group->parent_window);
		description_group->need_refresh = true;

		EntityButton*
			texture_button = new EntityButton();
		description_group->add_button_to_working_group(texture_button);

		texture_button->make_as_default_button_with_full_icon
		(
			new ERegionGabarite(size_x, size_y),
			description_group,
			nullptr,
			stored_image[ELocalisationText::active_localisation]
		);


		parent_button->parent_button_group->root_group->parent_window->button_group_list.push_back(description_group);
		parent_button->attached_description = description_group;

		init_description(description_group);
	}
}



EntityButtonDebugStructButton::~EntityButtonDebugStructButton()
{
}

EStringReplacer::EStringReplacer(std::string _what_replaced, std::string _result_string)
{
	what_replaced = _what_replaced;
	result_string = _result_string;
}

EntityButtonNewColorPattern::EntityButtonNewColorPattern()
{
}

EntityButtonNewColorPattern::~EntityButtonNewColorPattern()
{
}
