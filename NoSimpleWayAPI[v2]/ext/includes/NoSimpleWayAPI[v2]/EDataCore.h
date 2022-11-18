#pragma once

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

//#ifndef _E_TEXT_CORE_ALREADY_LINKED_
///**/#define _E_TEXT_CORE_ALREADY_LINKED_
///**/
//#endif

#include "ETextCore.h"

/**/
#ifndef	_HELPERS_ALREADY_LINKED_
#define	_HELPERS_ALREADY_LINKED_
#include "Helpers.h"
#endif
/**/

/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/



#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif





#include <iostream>
#include <fstream>

#include <vector>
#include <string>
//class ETextArea;

//link to method, who manipulate with data
//Entity*		= master entity, which store data object
//ECustomData*	= data object, which call data action
//float		= delta time


class ECustomData
{
public:
	ECustomData();
	~ECustomData();

	Entity* parent_entity = nullptr;

	//data
	EDataContainer* data_container = nullptr;

	//WHAT do with data
	std::vector<data_action_pointer> actions_on_update;
	std::vector<data_action_pointer> actions_on_change_style;
	std::vector<data_action_pointer> actions_on_draw;
	std::vector<data_action_pointer> actions_on_pre_draw;

	//clickable regions list
	std::vector<EClickableArea*> clickable_area_list;



	void draw();
	void draw_second_pass();

	void update(float _d);
	void translate_custom_data(float _x, float _y, float _z, bool _move_offset);

	ESprite*		get_sprite_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id, unsigned int _frame);
	ESpriteLayer*	get_sprite_layer_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id);
	ESpriteFrame*	get_sprite_frame_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id);
	//std::vector<void (*)(Entity*, ECustomData*)> data_actions_list;

	bool* is_second_pass = new bool(false);
	bool* disable_draw = new bool(false);
};

class ERegionGabarite
{
public:
	ERegionGabarite();
	~ERegionGabarite();

	ERegionGabarite(float _offset_x, float _offset_y, float _size_x, float _size_y);
	ERegionGabarite(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y);
	ERegionGabarite(float _size_x, float _size_y);

	float offset_x = 0.0f;
	float offset_y = 0.0f;
	float offset_z = 0.0f;

	float size_x = 0.0f;
	float size_y = 0.0f;

	/*float* border_left_offset = new float(0.0f);
	float* border_right_offset = new float(0.0f);
	float* border_up_offset = new float(0.0f);
	float* border_down_offset = new float(0.0f);*/

	float world_position_x = 0.0f;
	float world_position_y = 0.0f;
	float world_position_z = 0.0f;

	void translate(float _x, float _y);

	static ERegionGabarite* temporary_gabarite;
	void set_region_offset_and_size(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y);
	bool overlapped_by_mouse();

	unsigned int pointers_to_this_object = 0;
	unsigned int* pointer_id = new unsigned int(0);
	static void set_region_gabarite(ERegionGabarite** _destination, ERegionGabarite* _source);
	void* root_owner;

	float phantom_translate_x;
	float phantom_translate_y;
	float phantom_translate_z;

	bool have_phantom_translation;
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
class EClickableArea
{
public:
	EClickableArea();
	~EClickableArea();

	ERegionGabarite* region_gabarite;

	std::vector<ESpriteLayer*> sprite_layer_list;
	ESpriteLayer* internal_sprite_layer;

	std::vector<data_action_pointer> actions_on_click_list;
	std::vector<data_action_pointer> actions_on_right_click_list;
	Entity* parent_entity;
	ECustomData* parent_custom_data;

	ETextArea* text_area;
	//std::vector<data_action_pointer> action_on_change_text;

	bool* catched_side_left = new bool(false);
	bool* catched_side_right = new bool(false);
	bool* catched_side_up = new bool(false);
	bool* catched_side_down = new bool(false);
	bool* catched_side_mid = new bool(false);

	bool* catched_body = new bool(false);

	bool* have_rama = new bool(true);
	bool* any_visual_changes = new bool(true);

	//bool* editable_borders	= new bool(false);
	bool* can_catch_side = new bool[_CRS_SIDE_LAST_ELEMENT] {false};

	float* catch_offset_x = new float(0.0f);
	float* catch_offset_y = new float(0.0f);

	//float* internal_vertex_buffer;

	static bool overlapped_by_mouse(EClickableArea* _region, float _offset_x, float _offset_y, float _zoom);
	static bool catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance = 5.0f);
	void check_all_catches();
	void translate_clickable_region(float _x, float _y, float _z, bool _move_offset);

	static EClickableArea* active_clickable_region;
	static EClickableArea* create_default_clickable_region(ERegionGabarite* _gabarite, Entity* _parent_entity, ECustomData* _custom_data);

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

	~EDataContainerMessage();
};

class EDataContainerScrollBar : public EDataContainer
{
public:
	float* max_value = new float(0.0f);
	float* value_pointer;

	float* current_percent = new float(0.0f);

	~EDataContainerScrollBar();
	//EButtonGroup* parent_button_group;
};

enum class StoredPointerType
{
	STORED_TYPE_FLOAT,
	STORED_TYPE_INT
};

class EDataContainerRadialButton : public EDataContainer
{
public:
	float* min_value = new float(0.0f);
	float* max_value = new float(5.0f);

	void* value_pointer = nullptr;

	float* current_percent = new float(0.0f);
	float* step_multiplier = new float(1.0f);

	std::string text = "";

	StoredPointerType* stored_type = new StoredPointerType(StoredPointerType::STORED_TYPE_FLOAT);

	~EDataContainerRadialButton();
	//EButtonGroup* parent_button_group;
};

class EDataContainer_CrosshairSlider : public EDataContainer
{
public:
	float min_x = 0.0f;
	float max_x = 1.0f;

	float min_y = 0.0f;
	float max_y = 1.0f;

	float current_value_x = 0.5f;
	float current_value_y = 0.5f;

	float* target_pointer_x = nullptr;
	float* target_pointer_y = nullptr;
};

enum RegisteredFilterRules
{
	FILTER_RULE_OBTAINABLE_GAME_ITEM,
	FILTER_RULE_BASE_CLASS,
	FILTER_RULE_SKILL_GEMS,
	FILTER_RULE_INFLUENCE,
	FILTER_RULE_ENCHANTMENT,
	FILTER_RULE_EXPLICITS,
	FILTER_RULE_CLUSTER_PASSIVE,
	_RDEF_LAST_ELEMENT_
};



struct DataEntityFilter
{
public:
	std::string							target_tag_name = "";
	std::vector<std::string>			suitable_values_list;
};

class EFilterRule
{
public:
	ELocalisationText* localisation_text = nullptr;

	std::string focused_by_data_type = "";

	std::vector<DataEntityFilter*>		required_tag_list;
	std::vector<DataEntityFilter*>		banned_tag_list;

	static	std::vector<EFilterRule*>	registered_global_filter_rules;
	static	std::vector<EFilterRule*>	registered_filter_rules_for_list;

	static bool matched_by_filter_rule(EDataEntity* _data_entity, EFilterRule* _filter_rule, std::string _search_text);


	std::string							tag = "";
	float								min_y_size = 100.0f;
};

class EDataContainer_Group_DataEntitiesSearch : public EDataContainer
{
public:
	//std::vector<DataEntityFilter*>	required_tag_list;
	//std::vector<DataEntityFilter*>	banned_tag_list;
	EFilterRule* target_rule;

	EntityButton* pointer_to_search_bar;
	EButtonGroup* pointer_to_group_with_data_entities;
	EButtonGroup* pointer_to_group_with_filter_rules_list;
	EButtonGroup* pointer_to_group_item_receiver;

	ETextArea* filter_text_area;

	data_action_pointer				action_on_select_for_button;

};

class EDataContainer_VerticalNamedSlider : public EDataContainer
{
public:
	//ESpriteLayer*			pointer_to_head;
	ESpriteLayer* pointer_to_bg;

	EGUIStyle* style;

	std::string				stored_text;
	ETextArea* pointer_to_text_area;

	float					operable_area_size_x;
	float					current_value;
	float					max_value;

	float* pointer_to_value;

	data_action_pointer		additional_action_on_slide;
	//EDataContainer*			additional_data_container;
};


class EDataContainer_Button_StoreColor : public EDataContainer
{
public:
	Helper::HSVRGBAColor* stored_color;
	ColorButtonMode selected_mode = ColorButtonMode::CBM_OPEN_WINDOW;
};

class EDataContainer_Group_ColorEditor : public EDataContainer
{
public:

	//Helper::
	//float*							pointer_to_H;
	//float*							pointer_to_S;
	//float*							pointer_to_V;

	//float*							pointer_to_red;
	//float*							pointer_to_green;
	//float*							pointer_to_blue;

	//float*							pointer_to_alpha;

	Helper::HSVRGBAColor* work_color;

	EButtonGroup* pointer_to_color_box_group;
	EButtonGroup* pointer_to_color_collection_group;

	//data containers of color ajust buttons
	EDataContainer_VerticalNamedSlider* slider_data_value_container;
	EDataContainer_VerticalNamedSlider* slider_data_alpha_container;

	EDataContainer_CrosshairSlider* crosshair_slider_data_container;




	EDataContainer_Button_StoreColor* target_data_container_with_color;

};


class EDataContainer_DataEntityHolder : public EDataContainer
{
public:
	EDataEntity* stored_data_entity;
};



class EDataContainer_Group_StoreFilterRuleForDataEntitySearcher : public EDataContainer
{
public:
	EButtonGroup* target_group;
	std::string search_tag = "";
	EFilterRule* filter_rule;

	data_action_pointer	target_action_on_click;
};

class EDataContainer_Group_FilterBlock : public EDataContainer
{
public:

};

class EDataContainer_Button_OpenButtonGroup : public EDataContainer
{
public:
	EButtonGroup* master_group;
	EButtonGroup* target_group;
};

class EDataContainer_Button_AddContentToFilterBlock : public EDataContainer
{
public:
	FilterBlockAttribute* target_attribute;
};
//
//class EDataContainer_Group_WholeFilterBlock : public EDataContainer
//{
//public:
//	EButtonGroup*				pointer_to_non_listed_segment;
//	EButtonGroup*				pointer_to_listed_segment;
//	EButtonGroup*				pointer_to_preview_box_segment;
//	EButtonGroup*				pointer_to_top_control_block;
//	EButtonGroup*				pointer_to_cosmetic_segment;
//
//
//	//color section
//	EntityButton*				pointer_to_color_button[3];
//	EntityButton*				pointer_to_color_check_button[3];
//
//	bool						color_check[3];
//	Helper::HSVRGBAColor**		pointer_to_HRA_color[3];
//	
//	//font size
//	EntityButton*				text_size_button;
//	EntityButton*				text_size_switch_button;
//	bool						text_size_bool;
//	float						text_size;
//
//	EntityButtonVariantRouter*	button_show_hide;
//
//};

class EDataContainer_Group_FilterBlockNonListedSegment : public EDataContainer
{
public:
	EntityButton* target_button_with_attribute_name;
	EntityButton* target_button_with_condition;
	EntityButton* target_button_with_value;

	FilterBlockAttribute* target_filter_block_attribute;
};

class EDataContainer_Group_FilterBlockListedSegment : public EDataContainer
{
public:
	EButtonGroup* group_with_listed_buttons;

	std::string				filter_attribute_name;

	//EntityButton*			button_with;
	EDataContainer_Group_StoreFilterRuleForDataEntitySearcher* data_container_with_filter_rule;
};


class EDataContainer_Group_AddContentToFilterBlock : public EDataContainer
{
public:
	EButtonGroupFilterBlock* target_filter_block;

	ETextArea* typing_text_area;
};

class EDataContainer_Button_MultiGroupButtonSearcher : public EDataContainer
{
public:
	std::vector <EButtonGroup*> target_group_list;
};

class EDataContainer_Button_BoolSwitcher : public EDataContainer
{
public:
	ETextureGabarite* texture_gabarite_on;
	ETextureGabarite* texture_gabarite_off;

	bool* target_value;
};


//////////////////////////////////////////////////////////////////////
// actions section
//////////////////////////////////////////////////////////////////////

namespace EDataActionCollection
{
	void action_log_text(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_player_control(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_update_slider(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_change_style						(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_highlight_button_if_overlap(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_style(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_close_root_group(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_delete_entity(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_switch_description(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_update_radial_button(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_type_text							(Entity* _entity, ECustomData* _custom_data, float _d);



	/*	open groups	*/
	void action_open_data_entity_filter_group			(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_color_group						(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_add_item_to_group_receiver				(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_wide_item_to_group_receiver			(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_update_crosshair_slider					(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_draw_crosshair_slider					(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_update_vertical_named_slider			(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_draw_vertical_named_slider				(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_convert_HSV_to_RGB						(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_button						(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_force_resize_callback					(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_invoke_data_entity_group_action			(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_set_button_group_as_active				(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_switch_boolean_value					(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_transfer_pointer_to_color_data_container(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_unbing_color							(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_create_new_color						(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_rotate_variant							(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_rotate_variant_from_list			(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_active_filter_block						(Entity* _entity, ECustomData* _custom_data, float _d);

	//type text
	void action_type_search_data_entity_text(ETextArea* _text_area);
	void action_type_text_multiblock_searcher(ETextArea* _text_area);

	//group section
		//draw
	void action_draw_color_rectangle_for_group(EButtonGroup* _group);

	//update
	void action_convert_HSV_to_RGB(EButtonGroup* _group);

	//select
	void action_set_new_color_to_button(EButtonGroup* _group);

	//window resize
	void action_resize_to_full_window(EButtonGroup* _group);
	void action_resize_to_full_window_only_x(EButtonGroup* _group);

	//draw actions
	void action_draw_boolean_switcher(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_draw_stored_color_as_box(Entity* _entity, ECustomData* _custom_data, float _d);

	//close
	void action_delete_vertical_router_variants_group(EButtonGroup* _group);


}

enum ActiveParserMode
{
	READ_CAPS_ACTION,
	READ_ACTION,
	READ_VALUE
};



class ETextParser
{
public:
	static std::string		data_array[1000];
	static void				data_entity_parse_file(std::string _file);
	static void				data_read_explicit_file_and_generate_data_entity(std::string _file);
	static void				split_data_entity_list_to_named_structs();

	static EDataEntity* last_created_data_entity;
	static EDataTag* last_created_data_tag;

	static std::string		action_text_buffer;
	static std::string		value_text_buffer;

	static void				do_action(std::string _action_text, std::string _value);
};

class EStringUtils
{
public:
	static std::string	to_lower(std::string _text);
	static bool			compare_ignoring_case(std::string _text1, std::string _text2);
	static bool			A_contains_B_ignore_case(std::string _text_A, std::string _text_B);
	static std::string	UTF8_to_ANSI(std::string _text);

	static int hashFunction(std::string _input);
};