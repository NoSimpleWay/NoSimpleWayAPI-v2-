#pragma once

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/

#ifndef _E_TEXT_CORE_ALREADY_LINKED_
/**/#define _E_TEXT_CORE_ALREADY_LINKED_
/**/#include "ETextCore.h"
#endif

#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif

#include <vector>
#include <string>
//class ETextArea;

//link to method, who manipulate with data
//Entity*		= master entity, which store data object
//ECustomData*	= data object, which call data action
//float		= delta time
typedef void (*data_action_pointer)(Entity*, ECustomData*, float);

class ECustomData
{
public:
	ECustomData();
	~ECustomData();

	Entity* parent_entity;

	//data
	EDataContainer* data_container;
	std::vector<EClickableRegion*> clickable_region_list;

	//WHAT do with data
	std::vector<data_action_pointer> actions_on_update;

	void draw();
	void update(float _d);
	void translate_custom_data(float _x, float _y, float _z, bool _move_offset);

	ESprite*		get_sprite_by_id		(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id, unsigned int _frame);
	ESpriteLayer*	get_sprite_layer_by_id	(unsigned int _clickable_region_id, unsigned int _sprite_layer_id);
	ESpriteFrame*	get_sprite_frame_by_id	(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id);
	//std::vector<void (*)(Entity*, ECustomData*)> data_actions_list;
};

class ERegionGabarite
{
public:
	ERegionGabarite();
	~ERegionGabarite();

	ERegionGabarite(float _offset_x, float _offset_y, float _size_x, float _size_y);

	float* offset_x = new float(0.0f);
	float* offset_y = new float(0.0f);
	float* offset_z = new float(0.0f);

	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);

	float* border_left_offset = new float(0.0f);
	float* border_right_offset = new float(0.0f);
	float* border_up_offset = new float(0.0f);
	float* border_down_offset = new float(0.0f);

	float* world_position_x = new float(0.0f);
	float* world_position_y = new float(0.0f);
	float* world_position_z = new float(0.0f);

	void translate(float _x, float _y);
};

enum ClickableRegionSides
{
	CRS_SIDE_LEFT,
	CRS_SIDE_RIGHT,
	CRS_SIDE_DOWN,
	CRS_SIDE_UP,
	CRS_SIDE_MID,
	CRS_SIDE_BODY,
	_CRS_SIDE_LAST_ELEMENT
};
class EClickableRegion
{
public:
	EClickableRegion();
	~EClickableRegion();

	ERegionGabarite* region;

	std::vector<ESpriteLayer*> sprite_layer_list;
	ESpriteLayer* internal_sprite_layer;

	std::vector<data_action_pointer> actions_on_click_list;
	Entity* parent_entity;
	ECustomData* parent_custom_data;

	ETextArea* text_area;

	bool* catched_side_left		= new bool (false);
	bool* catched_side_right	= new bool (false);
	bool* catched_side_up		= new bool (false);	
	bool* catched_side_down		= new bool (false);
	bool* catched_side_mid		= new bool (false);

	bool* catched_body			= new bool (false);

	bool* have_rama				= new bool (true);
	bool* any_visual_changes	= new bool (true);

	//bool* editable_borders		= new bool(false);
	bool* can_catch_side		= new bool[_CRS_SIDE_LAST_ELEMENT]{false};

	float* catch_offset_x		= new float (0.0f);
	float* catch_offset_y		= new float (0.0f);

	//float* internal_vertex_buffer;

	static bool overlapped_by_mouse(EClickableRegion* _region, float _offset_x, float _offset_y, float _zoom);
	static bool catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance = 5.0f);
	void check_all_catches();
	void translate_clickable_region(float _x, float _y, float _z, bool _move_offset);

	static EClickableRegion* active_clickable_region;
	static EClickableRegion* create_default_clickable_region(ERegionGabarite* _gabarite, Entity* _parent_entity, ECustomData* _custom_data);
	
	void update(float _d);
	void draw();

	void redraw_text();
	void clickable_region_set_world_positions(float _x, float _y, float _z);
	ERenderBatcher* batcher_for_default_draw;
};

//////////////////////////////////////////////////////////////////////
// data container section
//////////////////////////////////////////////////////////////////////
class EDataContainer
{
};

class EDataContainerMessage : public EDataContainer
{
public:
	std::string* message = new std::string("");
};

class EDataContainerScrollBar : public EDataContainer
{
public:
	float*	max_value	= new float(0.0f);
	float*	value_pointer;

	//EButtonGroup* parent_button_group;
};
//////////////////////////////////////////////////////////////////////
// actions section
//////////////////////////////////////////////////////////////////////

namespace EDataActionCollection
{
	void action_log_text					(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_player_control				(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_update_slider				(Entity* _entity, ECustomData* _custom_data, float _d);
}
