#pragma once

#define _CHECK_VECTOR_BOUND(v, id) (id < v.size()) && (id >= 0)


#include "ETextCore.h"

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

	virtual void draw();
	void draw_second_pass();

	void generate_vertex_buffer_for_all_sprite_layers();
	void transfer_all_vertex_buffers_to_batcher();
	void set_world_positions(float _x, float _y, float _z);
	void set_world_position_w(ERegionGabarite* _region_gabarite);
	void set_world_position_l(ERegionGabarite* _region_gabarite);

	void modify_buffer_translate_for_entity(float _x, float _y, float _z);
	//\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\////\\//\\//\\//

	void translate_entity(float _x, float _y, float _z, bool _move_positions);

	void translate_sprite_layer(float _x, float _y, float _z, bool _move_locals);
	void translate_custom_data(float _x, float _y, float _z, bool _move_locals);

	virtual bool entity_is_active();
	virtual void update(float _d);
	Entity();
	virtual ~Entity();

	ESprite* get_sprite_from_data(unsigned int _data_id, unsigned int _layer_id, unsigned int _frame_id, unsigned int _frame);
	ESpriteLayer* get_sprite_layer_by_id(unsigned int id);

	ESprite* get_sprite_from_entity(unsigned int _layer, unsigned int _frame, unsigned int _frame_id);
	ESpriteFrame* get_sprite_frame_from_layer(ESpriteLayer* _layer, unsigned int _frame_id);
	ESprite* get_sprite_from_sprite_frame(ESpriteFrame* _frame, unsigned int _id);

	static ESprite* get_last_sprite(Entity* _en);

	bool entity_disabled			= false;
	bool need_remove				= false;
	bool have_phantom_draw			= false;
	bool be_visible_last_time		= false;

	static ECustomData*		get_last_custom_data(Entity* _entity);
	static EClickableArea*	get_last_clickable_area(Entity* _entity);
	static ETextArea*		get_last_text_area(Entity* _entity);

	static void				add_text_area_to_last_clickable_region(EntityButton* _button, ETextArea* _text_area);


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

void action_generate_vertex_slider(EntityButton* _but, EGUIStyle* _style);
void action_change_style_button(EntityButton* _but, EGUIStyle* _style);
void action_change_style_vertical_slider(EntityButton* _but, EGUIStyle* _style);

#include "Helpers.h"
struct HRA_color_collection;
class EntityButtonColorButton;



class EntityButton : public Entity
{
public:
	EntityButton();
	virtual ~EntityButton();

	bool button_hidden_by_search	= false;
	bool disable_force_field		= false;
	bool fixed_position				= false;
	bool force_draw					= true;
	bool update_when_scissored		= false;
	bool align_even_if_hidden		= false;
	bool do_not_generate_bg			= false;
	bool cannot_be_auto_deleted		= false;

	bool entity_is_active();

	float hover_time				= 0.0f;

	float force_field_left			= 0.0f;
	float force_field_right			= 0.0f;
	float force_field_bottom		= 0.0f;
	float force_field_up			= 0.0f;

	ERegionGabarite* button_gabarite;

	//std::string* autoalign_id = new std::string("");

	//float* autoalight_offset_x_mathed_id = new float(0.0f);
	//float* autoalight_offset_x_not_mathed_id = new float(0.0f);

	EButtonGroup* parent_button_group;


	


	void destroy_attached_description();
	EButtonGroup* attached_description;

	std::vector<change_style_action> action_on_generate_vertex_buffer;

	static void				button_generate_brick_bg(EntityButton* _button, EGUIStyle* _style);


	void init
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_row
	);

	void add_default_custom_data
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_row
	);

	void make_as_default_clickable_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer _dap
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);


	static EntityButton* create_item_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		EDataEntity* _data_entity
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);


	static EntityButton* create_wide_item_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		EDataEntity* _data_entity,
		EFont* _font,
		bool _can_be_deleted
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	static EntityButton* create_vertical_named_slider
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		EFont* _font,
		EGUIStyle* _style,
		std::string			_text
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	static EntityButtonColorButton* create_named_color_button
	(
		ERegionGabarite*				_region_gabarite,
		EButtonGroup*					_parent_group,
		EFont*							_font,
		EGUIStyle*						_style,
		ELocalisationText				_text,
		HRA_color_collection*	_collection,
		HSVRGBAColor*			_color,
		ColorButtonMode					_mode
	);

	static EntityButton* create_default_radial_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		std::string _text
	);

	static EntityButton* create_default_crosshair_slider
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		float* pointer_x,
		float* pointer_y,
		std::string			_texture
	);

	void make_default_button_with_unedible_text
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer _dap,
		std::string			_text
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	void make_default_button_with_edible_text
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer _dap,
		std::string			_text
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	void make_as_default_button_with_icon
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer _dap,
		ETextureGabarite* _gabarite
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	void make_as_default_button_with_full_icon
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer _dap,
		ETextureGabarite* _gabarite
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	void make_as_default_button_with_icon_and_text
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer	_dap,
		ETextureGabarite* _gabarite,
		std::string _text
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	void make_default_bool_switcher_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer _dap,
		ETextureGabarite* _gabarite_on,
		ETextureGabarite* _gabarite_off,
		bool* _target_bool = nullptr
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);


	void make_as_default_router_variant_button
	(
		ERegionGabarite* _region_gabarite
	);

	bool can_get_access_to_style();
	bool button_in_culling_gabarites();
	//ECustomData* description_data;
	void add_description(std::string _text);
	EDataEntity* pointer_to_data_entity;

	void draw();
	void update(float _d);
	bool* suppressor = nullptr;

	ETextArea* main_text_area;
	EClickableArea* main_clickable_area;
	ECustomData* main_custom_data;

};





//		ROUTER VARIANT BUTTON
struct RouterVariant
{
public:
	ELocalisationText*	localisation = nullptr;
	HSVRGBAColor*		color;
	ETextureGabarite*	texture = nullptr;
	ELocalisationText*	localisation_for_select_window;

	bool				do_not_delete_me = false;

	~RouterVariant();

};

enum class RotateVariantMode
{
	SELECT_NEXT,
	OPEN_CHOOSE_WINDOW
};


class EntityButtonVariantRouter : public EntityButton
{
public:
	virtual ~EntityButtonVariantRouter();

	int							selected_variant;
	std::vector<RouterVariant*>	router_variant_list;

	ESpriteLayer* layer_with_icon;
	ETextArea* pointer_to_text_area;



	void select_variant(int _variant_id);
	void select_variant_by_base_name(std::string& _base_name);
	int seach_id_by_base_name(std::string& _base_name);

	std::string	return_base_text_from_selected_router();

	RotateVariantMode			rotate_variant_mode = RotateVariantMode::SELECT_NEXT;

	EButtonGroupRouterVariant* opened_router_group;

	std::vector<data_action_pointer>	action_on_choose_variant_from_window;

	void make_default_router_variant_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer _dap
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);


	int height_division = 2;
};







class EntityButtonButtonGroupActivator : public EntityButton
{
public:
	EButtonGroup* target_group;
};




class EntityButtonVariantRouterSelector : public EntityButton
{
public:
	int							id = 0;
	EButtonGroupRouterVariant* parent_router_group;
	~EntityButtonVariantRouterSelector();
};


class EntityButtonMultiSearch : public EntityButton
{
public:
	std::vector <EButtonGroup*> target_group_list;
	~EntityButtonMultiSearch();
};


class EntityButtonColorButton : public EntityButton
{
public:
	HSVRGBAColor*			stored_color;
	ColorButtonMode			selected_mode = ColorButtonMode::CBM_OPEN_WINDOW;
	~EntityButtonColorButton();
	HRA_color_collection*	parent_color_collection;
};


class EntityButtonVerticalSlider : public EntityButton
{
public:
	~EntityButtonVerticalSlider();


	float workspace_height = 0.0f;

	float min_value = 0.0f;
	float max_value = 0.0f;

	float current_value_percent = 0.0f;
	float current_value = 0.0f;

	void* pointer_to_target_value;

	EBrickStyle* slider_active;
	EBrickStyle* slider_inactive;

	float scroll_speed = 0.0f;



};

class EntityButtonLocalisationSelector : public EntityButton
{
public:
	~EntityButtonLocalisationSelector();

	int stored_localisation;

};

class EntityButtonConfirmAction : public EntityButton
{
public:
	EntityButtonConfirmAction();
	~EntityButtonConfirmAction();

	data_action_pointer stored_action;

	EntityButton* target_entity_button	= nullptr;
	ECustomData* target_custom_data		= nullptr;

	int stored_localisation;

};

class EntityButtonOpenURL : public EntityButton
{
public:
	EntityButtonOpenURL();
	~EntityButtonOpenURL();

	std::string stored_url;

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

