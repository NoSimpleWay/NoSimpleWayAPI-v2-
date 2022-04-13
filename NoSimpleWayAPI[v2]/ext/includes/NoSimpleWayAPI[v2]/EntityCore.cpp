#pragma once
/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/

#include <algorithm>
#include <iterator>

void Entity::draw()
{
	if (!*disable_draw)
	{
		transfer_all_vertex_buffers_to_batcher();

		//custom data store clickable regions and text
		if (!custom_data_list.empty())
		{
			for (ECustomData* c_data : custom_data_list)
				if (c_data != nullptr) { c_data->draw(); }
		}
	}

	//for (ECustomData* custom_data :custom_data_list)
	//{
	//	custom_data->draw();
	//}
}

void Entity::generate_vertex_buffer_for_all_sprite_layers()
{
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
			for (EClickableArea* c_region:c_data->clickable_area_list)
			if (c_region != nullptr)
			{
				for (ESpriteLayer* s_layer:c_region->sprite_layer_list)
				if (s_layer != nullptr)
				{s_layer->generate_vertex_buffer_for_sprite_layer("Clickable region sprite layer");}

				if (c_region->internal_sprite_layer != nullptr)
				{c_region->internal_sprite_layer->generate_vertex_buffer_for_sprite_layer("internal sprite layer");}

				//for (ETextArea* ta:c_regio)
				if (c_region->text_area != nullptr)
				{
					//c_region->text_area->generate_rows();
					c_region->text_area->generate_text();
				}
			}

			
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
	*world_position_x = _x;
	*world_position_y = _y;
	*world_position_z = _z;

	if (!sprite_layer_list.empty())
	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr)
	{s_layer->sprite_layer_set_world_position(*world_position_x, *world_position_y, *world_position_z);}

	for (ECustomData* c_data : custom_data_list)
	if (c_data != nullptr)
	{
		for (EClickableArea* clickable_area : c_data->clickable_area_list)
		if (clickable_area != nullptr)
		//
		{
			clickable_area->clickable_region_set_world_positions(*world_position_x, *world_position_y, *world_position_z);
		}
	}
}

void Entity::set_world_position_w(ERegionGabarite* _region_gabarite)
{
	set_world_position
	(
		*_region_gabarite->world_position_x,
		*_region_gabarite->world_position_y,
		*_region_gabarite->world_position_z
	);
}

void Entity::set_world_position_l(ERegionGabarite* _region_gabarite)
{
	set_world_position
	(
		*_region_gabarite->offset_x,
		*_region_gabarite->offset_y,
		*_region_gabarite->offset_z
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

			if (c_region->internal_sprite_layer != nullptr)
			{
				c_region->internal_sprite_layer->modify_buffer_position_for_sprite_layer(_x, _y, _z);
			}
		}


	}

}

void Entity::translate_entity(float _x, float _y, float _z)
{
	//entity position
	*offset_x += _x;
	*offset_y += _y;
	*offset_z += _z;

	*world_position_x += _x;
	*world_position_y += _y;
	*world_position_z += _z;


	translate_all_sprite_layers(_x, _y, _z);
}

void Entity::translate_all_sprite_layers(float _x, float _y, float _z)
{
	for (ESpriteLayer* s_layer : sprite_layer_list)
	if (s_layer != nullptr) {s_layer->translate_sprite_layer(_x, _y, _z, false);}
	
	for (ECustomData* c_data : custom_data_list)
	if (c_data != nullptr) {c_data->translate_custom_data(_x, _y, _z, false);}


}

void Entity::update(float _d)
{
	//translate_entity(EInputCore::MOUSE_SPEED_X, EInputCore::MOUSE_SPEED_Y, 0.0f);

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

	//EInputCore::logger_simple_try("delete entity");

	delete offset_x;
	delete offset_y;
	delete offset_z;

	delete world_position_x;
	delete world_position_y;
	delete world_position_z;

	//
	
	if (!custom_data_list.empty())
	{
		//std::vector<ECustomData*>::iterator ib = custom_data_list.begin(), ie = custom_data_list.end();
		for (ECustomData* custom_data:custom_data_list)
		{
			delete custom_data;
		}

		custom_data_list.clear();
		custom_data_list.shrink_to_fit();
	}

	if (!sprite_layer_list.empty())
	{
		for (ESpriteLayer* sl:sprite_layer_list)
		{ delete sl; }

		sprite_layer_list.clear();
		sprite_layer_list.shrink_to_fit();

	}

	delete disable_draw;
	delete need_remove;
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

void Entity::add_text_area_to_last_clickable_region(EntityButton* _button, ETextArea* _text_area)
{
	if (_button != nullptr)
	{
		EClickableArea* last_clickable_area = get_last_clickable_area(_button);

		if (last_clickable_area != nullptr)
		{
			last_clickable_area->text_area = _text_area;
			_text_area->parent_entity = _button;

			if ((_button->parent_button_group != nullptr) && (_button->parent_button_group->selected_style != nullptr))
			{
				//apply color correction from style
				for (int i = 0; i < 4; i++)
				{
					last_clickable_area->text_area->color[i]
					=
					last_clickable_area->text_area->stored_color[i]
					*
					_button->parent_button_group->selected_style->text_color_multiplier[i];
				}
			}
		}
	}
}

void EntityButton::button_generate_brick_bg(EntityButton* _button, EGUIStyle* _style)
{
	if ((_button != nullptr) && (_style != nullptr) && (_style->button_bg != nullptr))
	{
		ESpriteLayer* last_layer = nullptr;

		if (_button->sprite_layer_list.empty())
		{
			_button->sprite_layer_list.push_back
			(ESpriteLayer::create_default_sprite_layer(nullptr));
		}

		last_layer = _button->sprite_layer_list[0];

		NS_ERenderCollection::set_brick_borders_and_subdivisions
		(
			*_style->button_bg->side_size_left,
			*_style->button_bg->side_size_right,
			*_style->button_bg->side_size_bottom,
			*_style->button_bg->side_size_up,

			*_style->button_bg->subdivision_x,
			*_style->button_bg->subdivision_y
		);

		NS_ERenderCollection::generate_brick_texture
		(
			_button->button_gabarite,
			last_layer,
			_style->button_bg->main_texture
		);
	}
	//_button->sprite_layer_list.pu
}

EntityButton* EntityButton::create_base_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_row)
{
	EntityButton* jc_button = new EntityButton();
	jc_button->parent_button_group = _parent_row;
	ERegionGabarite::set_region_gabarite(&jc_button->button_gabarite, _region_gabarite);

	EntityButton::button_generate_brick_bg(jc_button, _parent_row->selected_style);
	jc_button->set_world_position_w(_region_gabarite);

	jc_button->action_on_change_style_list.push_back(&action_change_style_button);

	return jc_button;
}

EntityButton* EntityButton::create_default_button_with_custom_data(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_row)
{
	EntityButton*	jc_button						= create_base_button(_region_gabarite, _parent_row);
	ECustomData*	jc_custom_data					= new ECustomData();
					jc_custom_data->parent_entity	= jc_button;

	jc_button->custom_data_list.push_back(jc_custom_data);

	return jc_button;
}


EntityButton* EntityButton::create_default_clickable_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_group, data_action_pointer _dap)
{
	EntityButton* jc_button = create_default_button_with_custom_data(_region_gabarite, _parent_group);

	EClickableArea* jc_clickable_area = EClickableArea::create_default_clickable_region
	(
		_region_gabarite,
		jc_button,
		EntityButton::get_last_custom_data(jc_button)
	);

	jc_clickable_area->can_catch_side[ClickableRegionSides::CRS_SIDE_BODY] = true;
	if (_dap != nullptr) { jc_clickable_area->actions_on_click_list.push_back(_dap); }
	
	ECustomData* last_data = Entity::get_last_custom_data(jc_button);
	last_data->actions_on_draw.push_back(&EDataActionCollection::action_highlight_button_if_overlap);

	last_data->clickable_area_list.push_back(jc_clickable_area);

	return jc_button;
}

bool EntityButton::can_get_access_to_style()
{
	return false;
}

EntityButton::~EntityButton()
{
	EInputCore::logger_simple_info("deleting entity button");
	if (button_gabarite != nullptr)
	{
		(*button_gabarite->pointers_to_this_object)--;

		EInputCore::logger_param("pointers left", *button_gabarite->pointers_to_this_object);

		if (*button_gabarite->pointers_to_this_object <= 0)
		{
			
			delete button_gabarite;
			EInputCore::logger_simple_success("deleting button gabarite");
		}
	}

	delete autoalign_id;
	delete autoalight_offset_x_mathed_id;
	delete autoalight_offset_x_not_mathed_id;

	delete fixed_position;
	delete update_when_scissored;

	action_on_change_style_list.clear();
	action_on_change_style_list.shrink_to_fit();

	//EInputCore::logger_simple_try("delete entity button");

	if (parent_button_group != nullptr)
	{
		EButtonGroup::refresh_button_group(parent_button_group);
	}
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
		*_but->parent_button_group->selected_style->slider_inactive->main_texture->size_x_in_pixels,
		*_but->parent_button_group->region_gabarite->size_y - *_but->parent_button_group->border_bottom - *_but->parent_button_group->border_up
	);

	//offset by button_group
	float total_group_height
	=
	*_but->parent_button_group->region_gabarite->size_y
	-
	*_but->parent_button_group->border_bottom
	-
	*_but->parent_button_group->border_up;

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







	NS_ERenderCollection::generate_brick_texture
	(
		ERegionGabarite::temporary_gabarite,
		_but->sprite_layer_list[0],
		_style->slider_bg->main_texture
	);

	*_but->sprite_layer_list[0]->offset_y = *_but->parent_button_group->border_bottom;
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

	*_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_y
	=
	*_style->slider_inactive->main_texture->size_y_in_pixels;

	*_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->offset_y
	=
	round
	(
		(
			total_group_height
			-
			*_but->custom_data_list[0]->clickable_area_list[0]->region_gabarite->size_y
		)
		*
		*(((EDataContainerScrollBar*)_but->custom_data_list[0]->data_container)->current_percent)
		+
		*_but->parent_button_group->border_bottom
	)
	;

	//change clickable region size y


	//change button gabarites size y
	*_but->button_gabarite->size_y = *_style->slider_inactive->main_texture->size_y_in_pixels;

	_but->custom_data_list[0]->get_sprite_by_id(0, 0, 0, 0)->set_texture_gabarite(_style->slider_inactive->main_texture);
	_but->custom_data_list[0]->get_sprite_by_id(0, 0, 0, 1)->set_texture_gabarite(_style->slider_active->main_texture);

}

void action_change_style_button(EntityButton* _but, EGUIStyle* _style)
{
	EntityButton::button_generate_brick_bg(_but, _style);

	for (ECustomData* custom_data:_but->custom_data_list)
	for (EClickableArea* clickable_area:custom_data->clickable_area_list)
	if (clickable_area->text_area != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			clickable_area->text_area->color[i] = clickable_area->text_area->stored_color[i] * _style->text_color_multiplier[i];
		}
	}
}
