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
	virtual void draw_second_pass();

	void generate_vertex_buffer_for_all_sprite_layers();
	void transfer_all_vertex_buffers_to_batcher();
	void set_world_positions(float _x, float _y, float _z);
	void set_world_position_w(ERegionGabarite* _region_gabarite);
	void set_world_position_l(ERegionGabarite* _region_gabarite);

	void modify_buffer_translate_for_entity(float _x, float _y, float _z);

	virtual void destroy_all_vertex_buffer_data();
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

	bool entity_disabled = false;
	bool entity_need_remove = false;
	bool have_phantom_draw = false;
	bool be_visible_last_time = false;

	static ECustomData* get_last_custom_data(Entity* _entity);
	static EClickableArea* get_last_clickable_area(Entity* _entity);
	static ETextArea* get_last_text_area(Entity* _entity);

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




typedef void (*generate_vertex_buffer)(EntityButton*, EGUIStyle*);

void action_generate_vertex_slider(EntityButton* _but, EGUIStyle* _style);
void action_generate_brick_bg_for_button(EntityButton* _but, EGUIStyle* _style);
void action_generate_vertex_for_horizontal_named_slider(EntityButton* _but, EGUIStyle* _style);
void action_generate_vertex_for_vertical_slider(EntityButton* _but, EGUIStyle* _style);

#include "Helpers.h"
struct HRA_color_collection;
class EntityButtonColorButton;

struct EStringReplacer
{
public:
	EStringReplacer(std::string _what_replaced, std::string _result_string);

	std::string what_replaced = "";
	std::string result_string = "";
};
class EntityButton;
struct DescriptionContainer
{
public:
	DescriptionContainer();
	DescriptionContainer(float _size_x, float _size_y);
	ELocalisationText localisation_text;

	float size_x = 250.0f;
	float size_y = 50.0f;

	virtual void	create_description();
	void			init_description(EButtonGroup* _group);

	EntityButton* parent_button;
	EClickableArea* parent_clickable_area;

	std::vector<EStringReplacer> replacer_list;


};

struct DescriptionContainerDefault : public DescriptionContainer
{
public:
	DescriptionContainerDefault(float _size_x, float _size_y) :DescriptionContainer(_size_x, _size_y) {};
	virtual ~DescriptionContainerDefault();
	void create_description() override;
};







enum class NewLineMethod
{
	WHEN_OUT_OF_GABARITE,
	FORCIBLY,
	FORBIDDEN

};

struct EHotKeyManager
{
	EntityButton* parent_button;

	int require_main_button;
	int require_secondare_button;
};

enum class ButtonSearchMode
{
	DEFAULT,
	ALWAYS_HIDDEN,
	ALWAY_SHOW
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EntityButton : public Entity
{
public:
	EntityButton();
	virtual ~EntityButton();

	ButtonSearchMode				button_search_mode = ButtonSearchMode::DEFAULT;

	NewLineMethod
		new_line_method = NewLineMethod::WHEN_OUT_OF_GABARITE;

	bool button_hidden_by_search = false;
	bool disable_force_field = false;
	bool fixed_position = false;
	bool force_draw = true;
	bool update_when_scissored = false;
	bool align_even_if_hidden = false;
	bool do_not_generate_bg = false;
	bool cannot_be_auto_deleted = false;
	bool can_be_stretched = false;
	bool have_simple_bg = false;
	bool entity_is_active();

	void destroy_all_vertex_buffer_data() override;

	DescriptionContainer*
	description_container = nullptr;

	float hover_time = 0.0f;



	float force_field_left = 0.0f;
	float force_field_right = 0.0f;
	float force_field_bottom = 0.0f;
	float force_field_up = 0.0f;


	float highlight_time = 0.0f;
	float max_highlight_time = 1.0f;
	std::chrono::milliseconds		highlight_timestamp;
	void set_highlight(float _set_time, float _max_time);

	float base_size_x = 10.0f;
	float base_size_y = 10.0f;

	float max_stretch_factor = 0.5f;

	ERegionGabarite* button_gabarite;

	//std::string* autoalign_id = new std::string("");

	//float* autoalight_offset_x_mathed_id = new float(0.0f);
	//float* autoalight_offset_x_not_mathed_id = new float(0.0f);

	EButtonGroup* parent_button_group;

	std::vector<EHotKeyManager> hotkey_list;


	void add_hotkey(int _key_main, int _key_secondary);

	void destroy_attached_description();
	EButtonGroup* attached_description;

	std::vector<generate_vertex_buffer> action_on_generate_vertex_buffer;

	static void				button_generate_brick_bg(EntityButton* _button, EGUIStyle* _style);

	void add_default_description_by_key(std::string _key);

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




	static EntityButton* create_horizontal_named_slider
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		EFont* _font,
		EGUIStyle* _style,
		ELocalisationText _ltext

		//void (*data_action_pointer)(Entity*, ECustomData*, float)
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
		ELocalisationText _ltext
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

	void make_as_default_button_with_icon_and_localisation_by_key
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer	_dap,
		ETextureGabarite* _gabarite,
		std::string _key
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



	void make_default_bool_switcher_button_with_unedible_text
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		data_action_pointer	_dap,
		ETextureGabarite* _gabarite_on,
		ETextureGabarite* _gabarite_off,
		ELocalisationText	_ltext,
		bool* _target_bool = nullptr
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);


	void make_as_default_router_variant_button
	(
		ERegionGabarite* _region_gabarite
	);

	EClickableArea* create_clickable_region_witch_sprtite_layer_and_icon(ERegionGabarite* _region_gabarite, ETextureGabarite* _icon, data_action_pointer _action);

	EClickableArea* add_close_circle(data_action_pointer _dap);

	bool can_get_access_to_style();
	bool button_in_culling_gabarites();
	//ECustomData* description_data;
	void add_description(std::string _text);
	EDataEntity* pointer_to_data_entity;

	void draw() override;
	void draw_second_pass() override;

	void update(float _d) override;

	bool* suppressor = nullptr;
	bool invert_suppression = false;

	EntityButton* button_suppressor;

	ETextArea* main_text_area;
	EClickableArea* main_clickable_area;
	ECustomData* main_custom_data;

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




struct DescriptionContainerHelpDescriptionImage : public DescriptionContainer
{
public:
	DescriptionContainerHelpDescriptionImage() :DescriptionContainer(0.0f, 0.0f)
	{
	};

	ETextureGabarite* stored_image[NSW_languages_count] = { nullptr };

	virtual ~DescriptionContainerHelpDescriptionImage();

	void create_description() override;
};




//		ROUTER VARIANT BUTTON
struct RouterVariant
{
public:
	ELocalisationText	router_localisation;
	ELocalisationText	localisation_for_select_window;
	HSVRGBAColor* text_color;


	ETextureGabarite* texture = nullptr;
	HSVRGBAColor* icon_color;



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



	void	select_variant(int _variant_id);
	
	void	select_variant_by_icon(ETextureGabarite* _icon);

	void	select_variant_by_base_name(std::string& _base_name);
	int		search_id_by_base_name(std::string& _base_name);

	void	select_variant_by_base_name_from_window_buttons(std::string& _base_name);
	int		search_id_by_base_name_window_variant(std::string& _base_name);


	void reselect_variant();

	
	

	std::string	return_base_text_from_selected_router();

	RotateVariantMode			rotate_variant_mode = RotateVariantMode::SELECT_NEXT;

	EButtonGroupRouterVariant* opened_router_group;

	std::vector<data_action_pointer>	action_on_choose_variant_from_window;

	int* target_int_value = nullptr;
	bool* target_bool_value = nullptr;
	//void make_default_router_variant_button
	//(
	//	ERegionGabarite* _region_gabarite,
	//	EButtonGroup* _parent_group,
	//	data_action_pointer _dap
	//	//void (*data_action_pointer)(Entity*, ECustomData*, float)
	//);

	RouterVariant* add_router_variant_by_text_and_color(std::string _text, float _r, float _g, float _b, float _a);
	RouterVariant* add_router_variant_with_localization_key_and_color(std::string _key, float _r, float _g, float _b, float _a);
	RouterVariant* add_router_variant_with_localization_key_color_and_icon(std::string _key, std::string _key_for_window, float _r, float _g, float _b, float _a, ETextureGabarite* _icon);
	RouterVariant* add_router_variant_with_localization_color_and_icon(ELocalisationText* _ltext, std::string _key_for_window, float _r, float _g, float _b, float _a, ETextureGabarite* _icon);
	//RouterVariant* add_router_variant_with_localization_color_and_icon(std::string _text, std::string _key_for_window, float _r, float _g, float _b, float _a, ETextureGabarite* _icon);

	int height_division = 2;
};


struct EDebugStruct;
class EntityButtonDebugStructButton : public EntityButtonVariantRouter
{
public:
	~EntityButtonDebugStructButton();

	EDebugStruct* stored_debug_struct;
};







class EntityButtonButtonGroupActivator : public EntityButton
{
public:
	EButtonGroup* target_group;
};

class EntityButtonWideItem : public EntityButton
{
public:
	EClickableArea* pointer_to_close_area;

	ELocalisationText localised_name;

	static EntityButtonWideItem* create_wide_item_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		EDataEntity* _data_entity,
		EFont* _font,
		bool _can_be_deleted
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);
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
	HSVRGBAColor*				stored_color;
	HSVRGBAColor**				target_color_pointer;

	ColorButtonMode				selected_mode = ColorButtonMode::CBM_OPEN_WINDOW;

	HRA_color_collection*		parent_color_collection;

	std::vector<EntityButton*>	list_of_forcibly_redrawing_buttons;

	void make_as_named_color_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		EFont* _font,
		EGUIStyle* _style,
		ELocalisationText				_text,
		HRA_color_collection* _collection,
		HSVRGBAColor* _color,
		ColorButtonMode					_mode
	);

	virtual ~EntityButtonColorButton();
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

	EBrickStyle* brick_style_active_slider;
	EBrickStyle* slider_inactive;

	float scroll_speed = 0.0f;

	float degree = 0.0f;

	bool is_rotator = false;

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

	EntityButton* target_entity_button = nullptr;
	ECustomData* target_custom_data = nullptr;

	int stored_localisation;

};

class EntityButtonOpenURL : public EntityButton
{
public:
	EntityButtonOpenURL();
	~EntityButtonOpenURL();

	std::string stored_url;

};

class EntityButtonNewColorPattern : public EntityButton
{
public:
	EntityButtonNewColorPattern();
	~EntityButtonNewColorPattern();

	HSVRGBAColor** pointer_to_color;

	EButtonGroup* target_button_group = nullptr;

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

