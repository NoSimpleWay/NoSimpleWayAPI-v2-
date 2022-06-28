#pragma once

#define _CHECK_VECTOR_BOUND(v, id) (id < v.size()) && (id >= 0)

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
	float offset_x = 0.0f;
	float offset_y = 0.0f;
	float offset_z = 0.0f;

	float world_position_x = 0.0f;
	float world_position_y = 0.0f;
	float world_position_z = 0.0f;

	std::vector<ECustomData*> custom_data_list;

	//\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\//
	std::vector<ESpriteLayer*> sprite_layer_list;

	void draw();
	void draw_second_pass();

	void generate_vertex_buffer_for_all_sprite_layers();
	void transfer_all_vertex_buffers_to_batcher();
	void set_world_position(float _x, float _y, float _z);
	void set_world_position_w(ERegionGabarite* _region_gabarite);
	void set_world_position_l(ERegionGabarite* _region_gabarite);

	void modify_buffer_translate_for_entity(float _x, float _y, float _z);
	//\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\//
	
	void translate_entity(float _x, float _y, float _z, bool _move_positions);

	void translate_sprite_layer(float _x, float _y, float _z, bool _move_locals);
	void translate_custom_data(float _x, float _y, float _z, bool _move_locals);

	void update(float _d);
	Entity();
	~Entity();

	ESprite* get_sprite_from_data(unsigned int _data_id, unsigned int _layer_id, unsigned int _frame_id, unsigned int _frame);
	ESpriteLayer* get_sprite_layer_by_id(unsigned int id);

	ESprite*			get_sprite_from_entity(unsigned int _layer, unsigned int _frame, unsigned int _frame_id);
	ESpriteFrame*		get_sprite_frame_from_layer(ESpriteLayer* _layer, unsigned int _frame_id);
	ESprite*			get_sprite_from_sprite_frame(ESpriteFrame* _frame, unsigned int _id);
	
	static ESprite*		get_last_sprite(Entity* _en);
	bool disable_draw	= false;
	bool need_remove	= false;
	bool disabled		= false;

	static ECustomData*		get_last_custom_data(Entity* _entity);
	static EClickableArea*	get_last_clickable_area(Entity* _entity);

	static void add_text_area_to_last_clickable_region(EntityButton* _button, ETextArea* _text_area);
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


typedef void (*change_style_action)(EntityButton*, EGUIStyle*);

void action_change_style_slider		(EntityButton* _but, EGUIStyle* _style);
void action_change_style_button		(EntityButton* _but, EGUIStyle* _style);



class EntityButton : public Entity
{
public:
	~EntityButton();

	ERegionGabarite* button_gabarite;

	//std::string* autoalign_id = new std::string("");

	//float* autoalight_offset_x_mathed_id = new float(0.0f);
	//float* autoalight_offset_x_not_mathed_id = new float(0.0f);

	EButtonGroup* parent_button_group;

	bool* fixed_position = new bool(false);
	bool* update_when_scissored = new bool(false);


	std::vector<change_style_action> action_on_change_style_list;

	static void button_generate_brick_bg(EntityButton* _button, EGUIStyle* _style);
	static EntityButton* create_base_button(ERegionGabarite* _region_gabarite, EButtonGroup* _parent_row);
	
	static EntityButton* create_default_button_with_custom_data
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_row
	);
	
	static EntityButton* create_default_clickable_button
	(
		ERegionGabarite*	_region_gabarite,
		EButtonGroup*		_parent_group,
		data_action_pointer _dap
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	
	static EntityButton* create_item_button
	(
		ERegionGabarite*	_region_gabarite,
		EButtonGroup*		_parent_group,
		EDataEntity*		_data_entity
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	
	static EntityButton* create_wide_item_button
	(
		ERegionGabarite*	_region_gabarite,
		EButtonGroup*		_parent_group,
		EDataEntity*		_data_entity,
		EFont*				_font
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);
	
	static EntityButton* create_default_radial_button
	(
		ERegionGabarite*	_region_gabarite,
		EButtonGroup*		_parent_group,
		std::string _text
	);

	bool can_get_access_to_style();

	//ECustomData* description_data;
	void add_description(std::string _text);
	EDataEntity* pointer_to_data_entity;


};

class ECluster
{
public:
	std::vector<Entity*> entity_list;
};

class TestObject
{
	//std::vector<EntityButton*> test_vector;
	long long* test_field;
};

