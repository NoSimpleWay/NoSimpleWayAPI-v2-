#pragma once

/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/

#include <vector>
#include <string>

class EDataContainer;
class EClickableRegion;
class ECustomData;
class Entity;
class ESpriteLayer;

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

	Entity* master_entity;

	//data
	EDataContainer* data_container;
	std::vector<EClickableRegion*> clickable_region_list;

	//WHAT do with data
	std::vector<data_action_pointer> data_actions_list;

	//std::vector<void (*)(Entity*, ECustomData*)> data_actions_list;
};

class ERegionGabarite
{
public:
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
};

class EClickableRegion
{
public:
	ERegionGabarite* region;

	std::vector<ESpriteLayer*> sprite_layer_list;

	std::vector<data_action_pointer> data_actions_list;
	Entity* master_entity;

	bool* catched_side_left	= new bool (false);
	bool* catched_side_right	= new bool (false);
	bool* catched_side_up	= new bool (false);	
	bool* catched_side_down	= new bool (false);
	bool* catched_side_mid	= new bool (false);

	static bool overlapped_by_mouse(EClickableRegion* _region, float _offset_x, float _offset_y, float _zoom);
	static bool catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance = 5.0f);
	static void check_all_catches();

	void update(float _d);
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
	void action_log_text(Entity* _entity, ECustomData* _custom_data);
}
