#pragma once

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

	std::vector<ECustomData*> custom_data_list;

	//\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\//
	std::vector<ESpriteLayer*> sprite_layer_list;

	void draw(float _d);
	void sprite_layer_generate_vertex_buffer();
	void transfer_vertex_buffer_to_batcher();
	void calculate_all_world_positions();
	void modify_buffer_translate_for_entity(float _x, float _y, float _z);
	//\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\//
	
	void translate_entity(float _x, float _y, float _z);
	
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

	float* autoalight_offset_x_while_mathed_id = new float(0.0f);
	float* autoalight_offset_y_while_mathed_id = new float(0.0f);
	
	float* autoalight_offset_x_while_not_mathed_id = new float(0.0f);
	float* autoalight_offset_y_while_not_mathed_id = new float(0.0f);
};

class ECluster
{
public:
	std::vector<Entity*> entity_list;
};
