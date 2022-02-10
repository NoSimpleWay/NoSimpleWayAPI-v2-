#pragma once

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

/**/
#ifndef	_DATA_CORE_ALREADY_LINKED_
#define	_DATA_CORE_ALREADY_LINKED_
#include "EDataCore.h"
#endif
/**/

/**/
#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
#define _E_GRAPHIC_CORE_ALREADY_LINKED_
#include "EGraphicCore.h"
#endif
/**/

/**/
#ifndef _E_GUI_CORE_ALREADY_LINKED_
#define _E_GUI_CORE_ALREADY_LINKED_
#include "EGUICore.h"
#endif
/**/

#include <vector>

/*********/
class ERegionGabarite;
class ECustomData;
class ESpriteLayer;


class Entity
{
private:

public:
	float* offset_x = new float(0.0f);
	float* offset_y = new float(0.0f);
	float* offset_z = new float(0.0f);

	float* world_position_x = new float(0.0f);
	float* world_position_y = new float(0.0f);
	float* world_position_z = new float(0.0f);

	std::vector<ECustomData*> custom_data_list;

	//\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\//
	std::vector<ESpriteLayer*> sprite_layer_list;

	void draw();
	void sprite_layer_generate_vertex_buffer();
	void transfer_all_vertex_buffers_to_batcher();
	void set_world_position(float _x, float _y, float _z);
	void modify_buffer_translate_for_entity(float _x, float _y, float _z);
	//\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\//
	
	void translate_entity(float _x, float _y, float _z);
	void translate_all_sprite_layers(float _x, float _y, float _z);
	void update(float _d);
	Entity();
	~Entity();
};
/*********/

class EntityPhysicalObject : public Entity
{
public:
	float* mass = new float(1.0f);

	float* inpulse_x = new float(0.0f);
	float* inpulse_y = new float(0.0f);
	float* inpulse_z = new float(0.0f);
};



class EntityButton : public Entity
{
public:
	ERegionGabarite* button_gabarite;

	std::string* autoalign_id = new std::string("");

	float* autoalight_offset_x_mathed_id = new float(0.0f);
	float* autoalight_offset_x_not_mathed_id = new float(0.0f);

	EButtonGroup* parent_button_group;

	bool* fixed_position = new bool(false);
};

class ECluster
{
public:
	std::vector<Entity*> entity_list;
};
