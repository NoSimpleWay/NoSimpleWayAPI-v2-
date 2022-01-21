#pragma once

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

#include <vector>
#include <string>

class EDataContainer;
class EClickableRegion;
class ECustomData;
class Entity;
class ESpriteLayer;
//class ETextArea;

//link to method, who manipulate with data
//Entity*		= master entity, which store data object
//ECustomData*	= data object, which call data action
//float		= delta time
typedef void (*data_action_pointer)(Entity*, ECustomData*, float);

class ETextArea;
class ECustomData
{
public:
	ECustomData();
	~ECustomData();

	Entity* master_entity;

	//data
	EDataContainer* data_container;
	std::vector<EClickableRegion*> clickable_region_list;

	//WHAT do with data
	std::vector<data_action_pointer> data_actions_list;

	void draw();
	void translate(float _x, float _y, float _z);

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

	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);

	float* border_left_offset = new float(0.0f);
	float* border_right_offset = new float(0.0f);
	float* border_up_offset = new float(0.0f);
	float* border_down_offset = new float(0.0f);

	float* world_position_x = new float(0.0f);
	float* world_position_y = new float(0.0f);

	void translate(float _x, float _y);
};

enum ClickableRegionSides
{
	CRS_SIDE_LEFT,
	CRS_SIDE_RIGHT,
	CRS_SIDE_DOWN,
	CRS_SIDE_UP,
	CRS_SIDE_MID
};
class EClickableRegion
{
public:
	EClickableRegion();
	~EClickableRegion();

	ERegionGabarite* region;

	std::vector<ESpriteLayer*> sprite_layer_list;
	ESpriteLayer* internal_sprite_layer;

	std::vector<data_action_pointer> data_actions_list;
	Entity* master_entity;
	ECustomData* master_custom_data;

	ETextArea* text_area;

	bool* catched_side_left	= new bool (false);
	bool* catched_side_right	= new bool (false);
	bool* catched_side_up	= new bool (false);	
	bool* catched_side_down	= new bool (false);
	bool* catched_side_mid	= new bool (false);

	bool* have_rama		= new bool (true);
	bool* any_visual_changes	= new bool (true);



	//float* internal_vertex_buffer;

	static bool overlapped_by_mouse(EClickableRegion* _region, float _offset_x, float _offset_y, float _zoom);
	static bool catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance = 5.0f);
	void check_all_catches();
	void translate(float _x, float _y, float _z);

	static EClickableRegion* active_clickable_region;
	
	void update(float _d);
	void draw();

	void redraw_text();

	void update_sides_visual(int _side, float _offset_x, float _offset_y, bool _catched);
	void init_internal_sprite_layer();
	bool set_catch_side(bool _catch_side, bool _set);

	void change_buffer_color(int _side, const float(&_color)[4]);
	void set_sides_position_and_sizes(int _side, float _x, float _y, float _z, float _w, float _h);
	void refresh_border_sprites();
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
	std::string message;
};
//////////////////////////////////////////////////////////////////////
// actions section
//////////////////////////////////////////////////////////////////////

namespace EDataActionCollection
{
	void action_log_text			(Entity* _entity, ECustomData* _custom_data);
	void action_player_control		(Entity* _entity, ECustomData* _custom_data, float _d);
}
