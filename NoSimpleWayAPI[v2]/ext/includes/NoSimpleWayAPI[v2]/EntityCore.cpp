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
	if ((!disable_draw) && (!disabled))
	{
		{transfer_all_vertex_buffers_to_batcher();}


		//custom data store clickable regions and text
		if (!custom_data_list.empty())
		{
			for (ECustomData* c_data : custom_data_list) if (c_data != nullptr) { c_data->draw(); }
		}
	}

	//for (ECustomData* custom_data :custom_data_list)
	//{
	//	custom_data->draw();
	//}
}

void Entity::draw_second_pass()
{
	if ((!disable_draw) && (!disabled))
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
		for (EClickableArea* clickable_area:custom_data->clickable_area_list)
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
		if (sl != nullptr) {sl->transfer_vertex_buffer_to_batcher();}
	}


	
}

void Entity::set_world_position(float _x, float _y, float _z)
{
	world_position_x = _x;
	world_position_y = _y;
	world_position_z = _z;

	if (!sprite_layer_list.empty())
	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr)
	{s_layer->sprite_layer_set_world_position(world_position_x, world_position_y, world_position_z);}

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
	set_world_position
	(
		_region_gabarite->world_position_x,
		_region_gabarite->world_position_y,
		_region_gabarite->world_position_z
	);
}

void Entity::set_world_position_l(ERegionGabarite* _region_gabarite)
{
	set_world_position
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
	if (s_layer != nullptr) {s_layer->translate_sprite_layer(_x, _y, _z, false);}
}

void Entity::translate_custom_data(float _x, float _y, float _z, bool _move_locals)
{
	for (ECustomData* c_data : custom_data_list)
	if (c_data != nullptr) {c_data->translate_custom_data(_x, _y, _z, false);}
}

void Entity::update(float _d)
{
	//translate_entity(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f);

	if ((!disabled) && (!disable_draw))
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
		for (ECustomData* custom_data:custom_data_list)
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
		
		for (ESpriteLayer* sl:sprite_layer_list)
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
	{return _layer->sprite_frame_list[_frame_id]; }
	else
	{return nullptr;}
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
	{return _entity->sprite_layer_list.back()->sprite_frame_list.back()->sprite_list.back(); }
	else
	{return nullptr;}
}

ECustomData* Entity::get_last_custom_data(Entity* _entity)
{
	if
	(
		(_entity != nullptr)
		&&
		(!_entity->custom_data_list.empty())
	)
	{return _entity->custom_data_list.back(); }
	else
	{return nullptr;}
}

EClickableArea* Entity::get_last_clickable_area(Entity* _entity)
{
	ECustomData* last_data = Entity::get_last_custom_data(_entity);

	if
	(
		( last_data != nullptr )
		&&
		( !last_data->clickable_area_list.empty() )
	)
	{ return last_data->clickable_area_list.back(); }
	else
	{ return nullptr; }
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

void EntityButton::destroy_attached_description()
{
	if (attached_description != nullptr)
	{
		parent_button_group->root_group->parent_window->button_group_list.erase
		(
			std::find
			(
				parent_button_group->root_group->parent_window->button_group_list.begin(),
				parent_button_group->root_group->parent_window->button_group_list.end(),
				attached_description
			)
		);

		delete attached_description;
		attached_description = nullptr;
	}
}

void EntityButton::button_generate_brick_bg(EntityButton* _button, EGUIStyle* _style)
{
	if ((_button != nullptr) && (_style != nullptr) && (_style->button_bg != nullptr) && (!_button->do_not_generate_bg))
	{
		ESpriteLayer* last_layer = nullptr;

		if (_button->sprite_layer_list.empty())
		{
			std::cout << "auto generate sprite layer!" << std::endl;
			_button->sprite_layer_list.push_back
			(ESpriteLayer::create_default_sprite_layer(nullptr));
		}

		last_layer = _button->sprite_layer_list.at(0);

		NS_ERenderCollection::set_brick_borders_and_subdivisions
		(
			*_style->button_bg->side_size_left,
			*_style->button_bg->side_size_right,
			*_style->button_bg->side_size_bottom,
			*_style->button_bg->side_size_up,

			*_style->button_bg->subdivision_x,
			*_style->button_bg->subdivision_y
		);

		NS_ERenderCollection::temporary_sprites = false;

		NS_ERenderCollection::generate_brick_texture
		(
			_button->button_gabarite,
			last_layer,
			_style->button_bg->main_texture,
			_style->button_bg->normal_map_texture,
			_style->button_bg->gloss_map_texture
		);
	}
	//_button->sprite_layer_list.pu
}


void EntityButton::init(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group)
{
	parent_button_group = _parent_group;
	ERegionGabarite::set_region_gabarite(&button_gabarite, _region_gabarite);

	sprite_layer_list.push_back(ESpriteLayer::create_default_sprite_layer(nullptr));

	EntityButton::button_generate_brick_bg(this, _parent_group->selected_style);
	set_world_position_w(_region_gabarite);

	action_on_generate_vertex_buffer.push_back(&action_change_style_button);
}

void EntityButton::add_default_custom_data(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_row)
{
	init (_region_gabarite, _parent_row);
	ECustomData*	jc_custom_data					= new ECustomData();
					jc_custom_data->parent_entity	= this;

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
	
	ECustomData* last_data = Entity::get_last_custom_data(this);
	last_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);

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
		NS_EGraphicCore::load_from_textures_folder
		("icons/" + DataEntityUtils::get_tag_value_by_name(0, "icon path", _data_entity));

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

EntityButton* EntityButton::create_wide_item_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, EDataEntity* _data_entity, EFont* _font)
{
		EntityButton* jc_button = new EntityButton();

		jc_button->make_as_default_clickable_button
		(
			_region_gabarite,
			_parent_group,
			&EDataActionCollection::action_invoke_data_entity_group_action
		);

		EDataContainer_DataEntityHolder* data_holder = new EDataContainer_DataEntityHolder();
		data_holder->stored_data_entity = _data_entity;
		EntityButton::get_last_custom_data(jc_button)->data_container = data_holder;
		//EntityButton::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_invoke_data_entity_group_action);

		jc_button->pointer_to_data_entity = _data_entity;

		//delete action on right click
		Entity::get_last_clickable_area(jc_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_delete_entity);

		//_parent_group->button_list.push_back(jc_button);


		//create text area
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ETextArea* jc_text_area = ETextArea::create_centered_to_left_text_area(Entity::get_last_clickable_area(jc_button), _font, "");
		jc_text_area->offset_by_gabarite_size_x = 0.0;
		jc_text_area->offset_by_text_size_x = 0.0;

		jc_text_area->offset_border[BorderSide::LEFT] = _region_gabarite->size_y;

		jc_text_area->can_be_edited = false;
		Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

		jc_button->main_text_area = jc_text_area;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (_data_entity != nullptr)
		{

			ETextureGabarite* item_icon = NS_EGraphicCore::load_from_textures_folder("icons/" + DataEntityUtils::get_tag_value_by_name(0, "icon path", _data_entity));

			float resize_factor = 0.0f;
			float offset_x = 0.0f;
			float offset_y = 0.0f;

			if (item_icon != nullptr)
			{
				resize_factor = (_region_gabarite->size_y - _parent_group->border_bottom - _parent_group->border_up - 6.0f) / max(item_icon->size_x_in_pixels, item_icon->size_y_in_pixels);
				resize_factor = min(resize_factor, 1.0f);

				offset_x = ((_region_gabarite->size_y - _parent_group->border_bottom - _parent_group->border_up) - item_icon->size_x_in_pixels * resize_factor) / 2.0f;
				offset_y = ((_region_gabarite->size_y - _parent_group->border_bottom - _parent_group->border_up) - item_icon->size_y_in_pixels * resize_factor) / 2.0f;

				ESpriteLayer* second_button_layer =
					ESpriteLayer::create_default_sprite_layer_with_size_and_offset
					(
						item_icon,

						_parent_group->border_left + offset_x,
						_parent_group->border_bottom + offset_y,
						3.0f,

						item_icon->size_x_in_pixels * resize_factor,
						item_icon->size_y_in_pixels * resize_factor,
						0.0f
					);

				jc_button->sprite_layer_list.push_back(second_button_layer);

				//second_button_layer->make_as_PBR();
			}
		

			

			jc_text_area->localisation_text.localisations[NSW_localisation_EN] = DataEntityUtils::get_tag_value_by_name(0, "name EN", _data_entity);
			jc_text_area->localisation_text.localisations[NSW_localisation_RU] = DataEntityUtils::get_tag_value_by_name(0, "name RU", _data_entity);

			jc_text_area->change_text(jc_text_area->localisation_text.localisations[ELocalisationText::active_localisation]);

			//////localistation//////
			std::string base_name_value = DataEntityUtils::get_tag_value_by_name(0, "base name", _data_entity);

			//if base name exist, set
			if (base_name_value != "")
			{
				jc_text_area->localisation_text.base_name = DataEntityUtils::get_tag_value_by_name(0, "base name", _data_entity);
			}
			else//use english localisation
			{
				jc_text_area->localisation_text.base_name = DataEntityUtils::get_tag_value_by_name(0, "name EN", _data_entity);
			}

			////////////////////////
		}
		else
		{
			ETextureGabarite* item_icon = NS_EGraphicCore::load_from_textures_folder("undefined_item");
			NS_EGraphicCore::complete_texture_gabarite(item_icon);

			float resize_factor = 0.0f;
			float offset_x = 0.0f;
			float offset_y = 0.0f;

			if (item_icon != nullptr)
			{
				resize_factor = (_region_gabarite->size_y - _parent_group->border_bottom - _parent_group->border_up - 6.0f) / max(item_icon->size_x_in_pixels, item_icon->size_y_in_pixels);
				resize_factor = min(resize_factor, 1.0f);

				offset_x = ((_region_gabarite->size_y - _parent_group->border_bottom - _parent_group->border_up) - item_icon->size_x_in_pixels * resize_factor) / 2.0f;
				offset_y = ((_region_gabarite->size_y - _parent_group->border_bottom - _parent_group->border_up) - item_icon->size_y_in_pixels * resize_factor) / 2.0f;

				ESpriteLayer* second_button_layer =
					ESpriteLayer::create_default_sprite_layer_with_size_and_offset
					(
						item_icon,

						_parent_group->border_left + offset_x,
						_parent_group->border_bottom + offset_y,
						3.0f,

						item_icon->size_x_in_pixels * resize_factor,
						item_icon->size_y_in_pixels * resize_factor,
						0.0f
					);

				jc_button->sprite_layer_list.push_back(second_button_layer);

				//second_button_layer->make_as_PBR();
			}
		}

		return jc_button;
}

EntityButton* EntityButton::create_vertical_named_slider(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, EFont* _font, EGUIStyle* _style, std::string _text)
{
	EntityButton* jc_button = new EntityButton();

	jc_button->make_as_default_clickable_button
	(
		_region_gabarite,
		_parent_group,
		nullptr
	);

	EDataContainer_VerticalNamedSlider* data = new EDataContainer_VerticalNamedSlider();
	EntityButton::get_last_custom_data(jc_button)->data_container = data;
	data->style = _style;
	data->operable_area_size_x = _region_gabarite->size_x - _style->round_slider->main_texture->size_x_in_pixels;
	

	EntityButton::get_last_custom_data(jc_button)->actions_on_update.push_back(&EDataActionCollection::action_update_horizontal_named_slider);
	EntityButton::get_last_custom_data(jc_button)->actions_on_draw.push_back(&EDataActionCollection::action_draw_horizontal_named_slider);

	ESpriteLayer* bg_layer = ESpriteLayer::create_default_sprite_layer(nullptr);
	data->pointer_to_bg = bg_layer;

	NS_ERenderCollection::set_brick_borders_and_subdivisions
	(
		*_style->slider_bg->side_size_left,
		*_style->slider_bg->side_size_right,
		*_style->slider_bg->side_size_bottom,
		*_style->slider_bg->side_size_up,
				 
		*_style->slider_bg->subdivision_x,
		*_style->slider_bg->subdivision_y
	);

	NS_ERenderCollection::temporary_sprites = false;

	ERegionGabarite::temporary_gabarite->set_region_offset_and_size
	(
		0.0f,
		0.0f,
		0.0f,
		jc_button->button_gabarite->size_x,
		15.0f
	);

	NS_ERenderCollection::generate_brick_texture
	(
		ERegionGabarite::temporary_gabarite,
		bg_layer,
		_style->slider_bg->main_texture,
		_style->slider_bg->normal_map_texture,
		_style->slider_bg->gloss_map_texture
	);

	jc_button->sprite_layer_list.push_back(bg_layer);


	/*ESpriteLayer* head_layer = ESpriteLayer::create_default_sprite_layer(_style->round_slider->main_texture);
	data->pointer_to_head = head_layer;
	jc_button->sprite_layer_list.push_back(head_layer);*/
	//delete action on right click
	//Entity::get_last_clickable_area(jc_button)->actions_on_right_click_list.push_back(&EDataActionCollection::action_delete_entity);

	//_parent_group->button_list.push_back(jc_button);

	//int selected_data_entity = _data_entity;

	ETextArea* jc_text_area = ETextArea::create_centered_to_left_text_area(Entity::get_last_clickable_area(jc_button), _font, _text);
	jc_text_area->offset_by_gabarite_size_x = 0.0;
	jc_text_area->offset_by_text_size_x = 0.0;

	jc_text_area->offset_by_gabarite_size_y = 1.0;
	jc_text_area->offset_by_text_size_y = -1.0;

	jc_text_area->offset_border[BorderSide::LEFT] = _parent_group->border_left + 3.0f;

	jc_text_area->change_text(_text);
	data->pointer_to_text_area = jc_text_area;
	data->stored_text = _text;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);



	return jc_button;
}

EntityButtonColorButton* EntityButton::create_named_color_button
(
	ERegionGabarite*				_region_gabarite,
	EButtonGroup*					_parent_group,
	EFont*							_font,
	EGUIStyle*						_style,
	ELocalisationText				_text,
	HRA_color_collection*	_color_collection,
	HSVRGBAColor*			_color,
	ColorButtonMode					_mode
)
{


	EntityButtonColorButton* jc_button = new EntityButtonColorButton();
	jc_button->parent_color_collection = _color_collection;

	jc_button->make_as_default_clickable_button
	(
		_region_gabarite,
		_parent_group,
		nullptr
	);

	//EDataContainer_Button_StoreColor* data = new EDataContainer_Button_StoreColor();
	//if (!data->stored_color->is_from_collection)
	//EntityButton::get_last_custom_data(jc_button)->data_container = data;
	jc_button->stored_color = _color;
	jc_button->selected_mode = _mode;

	//std::cout << data->stored_color << std::endl;

	EntityButton::get_last_custom_data(jc_button)->actions_on_draw.push_back(&EDataActionCollection::action_draw_stored_color_as_box);
	EntityButton::get_last_clickable_area(jc_button)->actions_on_click_list.push_back(&EDataActionCollection::action_open_color_group);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ETextArea* jc_text_area = ETextArea::create_centered_to_left_text_area(Entity::get_last_clickable_area(jc_button), _font, _text.localisations[ELocalisationText::active_localisation]);
	jc_text_area->offset_by_gabarite_size_x = 0.0;
	jc_text_area->offset_by_text_size_x = 0.0;

	jc_text_area->offset_by_gabarite_size_y = 1.0;
	jc_text_area->offset_by_text_size_y = -1.0;

	jc_text_area->offset_border[BorderSide::LEFT] = _parent_group->border_left;

	jc_text_area->change_text(_text.localisations[ELocalisationText::active_localisation]);

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(jc_button, jc_text_area);

	jc_button->main_text_area = jc_text_area;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	return jc_button;
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
	last_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);

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



void EntityButton::make_default_button_with_unedible_text(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, std::string _text)
{
	

	make_as_default_clickable_button
	(
		_region_gabarite,
		_parent_group,
		_dap
	);


	ETextArea*
	jc_text_area = ETextArea::create_centered_text_area
	(EntityButton::get_last_clickable_area(this), EFont::font_list[0], _text);

	jc_text_area->change_text(_text);

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
		(EntityButton::get_last_clickable_area(this), EFont::font_list[0], _text);

	jc_text_area->change_text(_text);

	jc_text_area->can_be_edited = true;
	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);

	main_text_area = jc_text_area;
}

void EntityButton::make_as_default_button_with_icon(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _gabarite)
{


	make_as_default_clickable_button(_region_gabarite, _parent_group, _dap);
	
	float min_size = min(_region_gabarite->size_x, _region_gabarite->size_y);

	float offset_x = (_region_gabarite->size_x - min_size - 4.0f) / 2.0f + 2.0f;
	float offset_y = (_region_gabarite->size_y - min_size - 4.0f) / 2.0f + 2.0f;

	sprite_layer_list.push_back
	(
		ESpriteLayer::create_default_sprite_layer_with_size_and_offset
		(
			_gabarite,

			offset_x,
			offset_y,
			0.0f,

			min_size,
			min_size,
			00.0f
		)
	);
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

void EntityButton::make_as_default_button_with_icon_and_text(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap, ETextureGabarite* _gabarite, std::string& _text)
{
	make_as_default_clickable_button(_region_gabarite, _parent_group, _dap);
	
	float min_size = min(_region_gabarite->size_x, _region_gabarite->size_y);

	if (_gabarite != nullptr)
	{
		int
		max_size = max(_gabarite->size_x_in_pixels, _gabarite->size_y_in_pixels);
		max_size = max(max_size, 4.0f);

		float
		resize_factor = (_region_gabarite->size_y - 4.0f) / max_size;
		resize_factor = min(resize_factor, 1.0f);

		float icon_size_x = round(_gabarite->size_x_in_pixels * resize_factor);
		float icon_size_y = round(_gabarite->size_y_in_pixels * resize_factor);

		float offset_x = (_region_gabarite->size_y - icon_size_x) / 2.0f;
		float offset_y = (_region_gabarite->size_y - icon_size_y) / 2.0f;

		sprite_layer_list.push_back
		(
			ESpriteLayer::create_default_sprite_layer_with_size_and_offset
			(
				_gabarite,

				offset_x,
				offset_y,
				0.0f,

				icon_size_x,
				icon_size_y,
				0.0f
			)
		);
	}
	ETextArea* jc_text_area;
	if (_gabarite != nullptr)
	{
		jc_text_area = ETextArea::create_centered_to_left_text_area
		(EntityButton::get_last_clickable_area(this), EFont::font_list[0], _text);

		jc_text_area->offset_border[BorderSide::LEFT] = _region_gabarite->size_y + 3.0f;
	}
	else
	{
		jc_text_area = ETextArea::create_centered_text_area
		(EntityButton::get_last_clickable_area(this), EFont::font_list[0], _text);

		jc_text_area->offset_border[BorderSide::LEFT] = 4.0f;
	}

	main_text_area = jc_text_area;
	

	

	jc_text_area->change_text(_text);

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);
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
		data_container->target_value = new bool(false);
	}




	EntityButton::get_last_custom_data(this)->data_container = data_container;
	EntityButton::get_last_custom_data(this)->actions_on_draw.insert
	(
		EntityButton::get_last_custom_data(this)->actions_on_draw.begin(),
		&EDataActionCollection::action_draw_boolean_switcher
	);
}








void EntityButtonVariantRouter::make_default_router_variant_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap)
{
	make_as_default_button_with_icon
	(
		_region_gabarite,
		_parent_group,
		_dap,
		nullptr
	);

	//parent_filter_block = static_cast<EButtonGroupFilterBlock*>(_parent_group);

	layer_with_icon = sprite_layer_list.back();

	ETextArea* jc_text_area = ETextArea::create_centered_text_area(EntityButton::get_last_clickable_area(this), EFont::font_list[0], "|?|");
	pointer_to_text_area = jc_text_area;

	jc_text_area->can_be_edited = false;
	Entity::add_text_area_to_last_clickable_region(this, jc_text_area);
}

bool EntityButton::can_get_access_to_style()
{
	return false;
}

void EntityButton::add_description(std::string _text)
{
	ECustomData*		jc_data				= new ECustomData();
	*jc_data->is_second_pass				= true;

	jc_data->actions_on_update.push_back(&EDataActionCollection::action_switch_description);
	jc_data->parent_entity					= this;
	*jc_data->disable_draw					= true;

	EClickableArea*		jc_clickable_area	=
	EClickableArea::create_default_clickable_region
	(
		new ERegionGabarite
		(
			3.0f,
			-10.0f,
			0.0f,

			120.0f,
			40.0f
		),
		this,
		jc_data
	);

	ETextArea* jc_text = ETextArea::create_centered_text_area
	(
		jc_clickable_area
		,
		EFont::font_list[0],
		_text//"Description"
	);

	jc_text->offset_border[BorderSide::LEFT] = 5.0f;
	jc_text->offset_border[BorderSide::RIGHT] = 5.0f;
	jc_text->offset_by_gabarite_size_x = 0.00f;
	jc_text->offset_by_text_size_x = 0.00f;
	jc_text->change_text(_text);

	jc_data->clickable_area_list.push_back(jc_clickable_area);
	jc_clickable_area->text_area = jc_text;
	jc_clickable_area->sprite_layer_list.push_back(ESpriteLayer::create_default_sprite_layer(nullptr));


	NS_ERenderCollection::set_brick_borders_and_subdivisions
	(
		*parent_button_group->selected_style->button_bg->side_size_left,
		*parent_button_group->selected_style->button_bg->side_size_right,
		*parent_button_group->selected_style->button_bg->side_size_bottom,
		*parent_button_group->selected_style->button_bg->side_size_up,

		*parent_button_group->selected_style->button_bg->subdivision_x,
		*parent_button_group->selected_style->button_bg->subdivision_y
	);

	NS_ERenderCollection::temporary_sprites = true;
	NS_ERenderCollection::generate_brick_texture
	(
		jc_clickable_area->region_gabarite,
		jc_clickable_area->sprite_layer_list[0],
		parent_button_group->selected_style->button_bg->main_texture,
		parent_button_group->selected_style->button_bg->normal_map_texture,
		parent_button_group->selected_style->button_bg->gloss_map_texture
	);


	custom_data_list.push_back(jc_data);
}

void EntityButton::draw()
{
	Entity::draw();

	if ((suppressor != nullptr) && (!*suppressor))
	{
		NS_EGraphicCore::set_active_color_custom_alpha(NS_EColorUtils::COLOR_DARK_GRAY, 0.85f);
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

void EntityButton::update(float _d)
{
	//if ((suppressor == nullptr) || (*suppressor))
	//{
		Entity::update(_d);
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

	//delete autoalign_id;
	//delete autoalight_offset_x_mathed_id;
	//delete autoalight_offset_x_not_mathed_id;

	//delete fixed_position;
	//delete update_when_scissored;

	if (debug_deleting) EInputCore::logger_simple_info("try clear and shrink action on change style");
	action_on_generate_vertex_buffer.clear();
	action_on_generate_vertex_buffer.shrink_to_fit();
	if (debug_deleting) EInputCore::logger_simple_success("clear and shrink action on change style");
	//EInputCore::logger_simple_try("delete entity button");

	//if ((parent_button_group != nullptr) && (!parent_button_group->need_remove))
	//{
	//	//EButtonGroup::change_group(parent_button_group->root_group);
	//	EButtonGroup::change_group(parent_button_group->parent_group);
	//	parent_button_group->refresh_buttons_in_group();
	//}
}

void action_change_style_slider(EntityButton* _but, EGUIStyle* _style)
{
	NS_ERenderCollection::set_brick_borders_and_subdivisions
	(
		*_style->slider_bg->side_size_left,
		*_style->slider_bg->side_size_right,
		*_style->slider_bg->side_size_bottom,
		*_style->slider_bg->side_size_up,
		
		*_style->slider_bg->subdivision_x,
		*_style->slider_bg->subdivision_y
	);

	ERegionGabarite::temporary_gabarite->set_region_offset_and_size
	(
		0.0f,
		0.0f,
		0.0f,
		_but->parent_button_group->selected_style->slider_inactive->main_texture->size_x_in_pixels,
		_but->parent_button_group->region_gabarite->size_y - _but->parent_button_group->border_bottom - _but->parent_button_group->border_up
	);

	//offset by button_group
	float total_group_height
	=
	_but->parent_button_group->region_gabarite->size_y
	-
	_but->parent_button_group->border_bottom
	-
	_but->parent_button_group->border_up;

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
		_style->slider_bg->main_texture,
		_style->slider_bg->normal_map_texture,
		_style->slider_bg->gloss_map_texture
	);

	_but->sprite_layer_list[0]->offset_y = _but->parent_button_group->border_bottom;
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

	_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_x = _style->slider_inactive->main_texture->size_x_in_pixels;

	_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_y = _style->slider_inactive->main_texture->size_y_in_pixels;

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
		_but->parent_button_group->border_bottom
	)
	;

	//change clickable region size y


	//change button gabarites size y
	//_but->button_gabarite->size_x = _style->slider_inactive->main_texture->size_x_in_pixels;
	//_but->button_gabarite->size_y = _style->slider_inactive->main_texture->size_y_in_pixels;

	_but->custom_data_list[0]->get_sprite_by_id(0, 0, 0, 0)->set_texture_gabarite
	(
		_style->slider_inactive->main_texture,
		_style->slider_inactive->normal_map_texture,
		_style->slider_inactive->gloss_map_texture
	);

	_but->custom_data_list[0]->get_sprite_by_id(0, 0, 0, 1)->set_texture_gabarite
	(
		_style->slider_active->main_texture,
		_style->slider_active->normal_map_texture,
		_style->slider_active->gloss_map_texture
	);



}

void action_change_style_button(EntityButton* _but, EGUIStyle* _style)
{
	EntityButton::button_generate_brick_bg(_but, _style);

	for (ECustomData* custom_data:_but->custom_data_list)
	for (EClickableArea* clickable_area:custom_data->clickable_area_list)
	if (clickable_area->text_area != nullptr)
	{
		clickable_area->text_area->color = clickable_area->text_area->stored_color;

		//for (int i = 0; i < 4; i++)
		//{
		//	clickable_area->text_area->color[i] = clickable_area->text_area->stored_color[i] * _style->text_color_multiplier[i];
		//}
	}
}

void action_change_style_vertical_slider(EntityButton* _but, EGUIStyle* _style)
{
	NS_ERenderCollection::set_brick_borders_and_subdivisions
	(
		*_style->slider_bg->side_size_left,
		*_style->slider_bg->side_size_right,
		*_style->slider_bg->side_size_bottom,
		*_style->slider_bg->side_size_up,

		*_style->slider_bg->subdivision_x,
		*_style->slider_bg->subdivision_y
	);



	//offset by button_group
	float total_group_height
		=
		_but->parent_button_group->region_gabarite->size_y
		-
		_but->parent_button_group->border_bottom
		-
		_but->parent_button_group->border_up;


	ERegionGabarite::temporary_gabarite->set_region_offset_and_size
	(
		0.0f,
		0.0f,
		0.0f,
		_but->parent_button_group->selected_style->slider_inactive->main_texture->size_x_in_pixels,
		total_group_height
	);




	NS_ERenderCollection::temporary_sprites = false;
	NS_ERenderCollection::generate_brick_texture
	(
		ERegionGabarite::temporary_gabarite,
		_but->sprite_layer_list[0],
		_style->slider_bg->main_texture,
		_style->slider_bg->normal_map_texture,
		_style->slider_bg->gloss_map_texture
	);

	_but->offset_y = 10.0f;
	_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_x = _style->slider_inactive->main_texture->size_x_in_pixels;
	_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_y = total_group_height;



	//change clickable region size y


	//change button gabarites size y
	_but->button_gabarite->size_x = _style->slider_inactive->main_texture->size_x_in_pixels;
	_but->button_gabarite->size_y = total_group_height;

	EntityButtonVerticalSlider* slider = static_cast<EntityButtonVerticalSlider*>(_but);
	slider->workspace_height = total_group_height - _style->slider_inactive->main_texture->size_y_in_pixels;

	if (_but->parent_button_group->child_align_direction == ChildElementsAlignDirection::BOTTOM_TO_TOP)
	{
		slider->min_value = 0.0f;

		slider->max_value = -(_but->parent_button_group->highest_point_y - _but->parent_button_group->region_gabarite->size_y + _but->parent_button_group->border_up);
		slider->max_value = min(slider->max_value, 0.0f);
	}
	else
	if (_but->parent_button_group->child_align_direction == ChildElementsAlignDirection::TOP_TO_BOTTOM)
	{
		slider->min_value = (_but->parent_button_group->highest_point_y - _but->parent_button_group->region_gabarite->size_y + _but->parent_button_group->border_up);
		slider->min_value = max(slider->min_value, 0.0f);

		slider->max_value = 0.0f;

	}
}

EntityButtonVariantRouter::~EntityButtonVariantRouter()
{
	if (opened_router_group != nullptr)
	{
		opened_router_group->need_remove = true;

		opened_router_group = nullptr;
	}

	for (RouterVariant* rv : router_variant_list)
	if (rv != nullptr)
	{
		delete rv;
	}

	router_variant_list.clear();
	router_variant_list.shrink_to_fit();



}

void EntityButtonVariantRouter::select_variant(int _variant_id)
{
	if (_variant_id >= 0)
	{
		selected_variant = _variant_id;

		if (layer_with_icon != nullptr)
		{
			//6999999999999999999999999999999, 10 november 2022, cat, stop, pls

			if (router_variant_list[selected_variant]->texture != nullptr)
			{
				//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->main_texture = router_variant_list[selected_variant].texture;

				EBrickStyle* brick_style = parent_button_group->selected_style->button_bg;
				float resize_factor =
					min
					(
						(button_gabarite->size_x - *brick_style->side_offset_bottom - *brick_style->side_offset_up) / (float)(router_variant_list[selected_variant]->texture->size_x_in_pixels)
						,
						(button_gabarite->size_y - *brick_style->side_offset_left - *brick_style->side_offset_right) / (float)(router_variant_list[selected_variant]->texture->size_y_in_pixels)
					);

				//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->offset_x = *brick_style->side_offset_left;
				//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->offset_y = *brick_style->side_offset_bottom;
				//layer_with_icon->sprite_frame_list[0]->sprite_list[0]->offset_z = 0.0f;


				layer_with_icon->sprite_frame_list[0]->sprite_list[0]->set_texture_gabarite_with_size_and_offset
				(
					router_variant_list[selected_variant]->texture,
					nullptr,
					nullptr,

					(button_gabarite->size_y - router_variant_list[selected_variant]->texture->size_x_in_pixels) / 2.0f,
					(button_gabarite->size_y - router_variant_list[selected_variant]->texture->size_y_in_pixels) / 2.0f,
					0.0f,

					router_variant_list[selected_variant]->texture->size_x_in_pixels * resize_factor,
					router_variant_list[selected_variant]->texture->size_y_in_pixels * resize_factor,
					0.0f
				);

				pointer_to_text_area->offset_border[BorderSide::LEFT] = button_gabarite->size_y;
			}
			else
			{
				pointer_to_text_area->offset_border[BorderSide::LEFT] = 0.0f;
			}
			pointer_to_text_area->offset_border[BorderSide::RIGHT] = 0.0f;


			pointer_to_text_area->localisation_text = *router_variant_list[selected_variant]->localisation;
			pointer_to_text_area->stored_color = *(router_variant_list[selected_variant]->color);
			pointer_to_text_area->color = *(router_variant_list[selected_variant]->color);

			pointer_to_text_area->change_text(pointer_to_text_area->localisation_text.localisations[ELocalisationText::active_localisation]);

			//redraw
			set_world_position(world_position_x, world_position_y, world_position_z);
			generate_vertex_buffer_for_all_sprite_layers();

		}
	}
}

void EntityButtonVariantRouter::select_variant_by_base_name(std::string& _base_name)
{
	select_variant(seach_id_by_base_name(_base_name));
}

int EntityButtonVariantRouter::seach_id_by_base_name(std::string& _base_name)
{
	//int id = 0;

	for (int i = 0; i < router_variant_list.size(); i++)
	{
		if (router_variant_list[i]->localisation->base_name == _base_name)
		{
			return i;
		}

		//id++;
	}
		return -1;
}

RouterVariant::~RouterVariant()
{
	if (!do_not_delete_me)
	{
		//EInputCore::logger_simple_info("~RouterVariant");

		if (localisation != nullptr) { delete localisation; }
		if (color != nullptr) { delete color; }
		if (localisation_for_select_window != nullptr) { delete localisation_for_select_window; }

		//EInputCore::logger_simple_success("~RouterVariant deleted");
	}
}

EntityButtonVerticalSlider::~EntityButtonVerticalSlider()
{
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
