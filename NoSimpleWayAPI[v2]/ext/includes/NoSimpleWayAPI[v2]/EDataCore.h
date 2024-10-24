#pragma once

#include <fstream>
#include <iostream>

#include <string>
#include <vector>



/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/


#include "Helpers.h"


//#ifndef _E_TEXT_CORE_ALREADY_LINKED_
///**/#define _E_TEXT_CORE_ALREADY_LINKED_
///**/
//#endif

//#include "ETextCore.h"



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
	std::vector<data_action_pointer> actions_on_generate_vertex;
	std::vector<data_action_pointer> actions_on_draw;
	std::vector<data_action_pointer> actions_on_pre_draw;

	//clickable regions list
	std::vector<EClickableArea*> clickable_area_list;



	void custom_data_draw();
	void draw_second_pass();

	void update(float _d);
	void translate_custom_data(float _x, float _y, float _z, bool _move_offset);

	ESprite* get_sprite_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id, unsigned int _frame);
	ESpriteLayer* get_sprite_layer_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id);
	ESpriteFrame* get_sprite_frame_by_id(unsigned int _clickable_region_id, unsigned int _sprite_layer_id, unsigned int _frame_id);
	//std::vector<void (*)(Entity*, ECustomData*)> data_actions_list;

	bool is_second_pass				= false;
	bool disable_custom_data_draw	= false;
};

class ERegionGabarite
{
public:
	ERegionGabarite();
	~ERegionGabarite();

	ERegionGabarite(float _offset_x, float _offset_y, float _size_x, float _size_y);
	ERegionGabarite(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y);
	ERegionGabarite(float _size_x, float _size_y);

	//parent gabarite for autoalign
	std::vector<ERegionGabarite*> child_gabarite_list;
	ERegionGabarite* parent_gabarite = nullptr;
	
	float				offset_by_size_x = 0.0f;
	float				offset_by_size_y = 0.0f;

	float				offset_by_parent_size_x = 0.0f;
	float				offset_by_parent_size_y = 0.0f;

	float				offset_by_pixels_x = 0.0f;
	float				offset_by_pixels_y = 0.0f;
	//

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

	static	ERegionGabarite*			temporary_gabarite;
	void	set_region_offset_and_size	(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y);
	//void	set_region_size			(float _size_x, float _size_y);
	bool	overlapped_by_mouse();

	unsigned int pointers_to_this_object = 0;
	//unsigned int* pointer_id = new unsigned int(0);
	static void set_region_gabarite(ERegionGabarite** _destination, ERegionGabarite* _source);
	//void* parent_region;

	void add_child_to_this_region(ERegionGabarite* _child);
	void align_all_clild_gabarites();

	float phantom_translate_x;
	float phantom_translate_y;
	float phantom_translate_z;

	bool have_phantom_translation;
};

class ERegionGabariteContainer
{
	ERegionGabarite* target_region_gabarite;

	bool is_original;
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

	bool debug_updating = false;
	//bool can_be_focused = true;



	ERegionGabarite*					region_gabarite;
	bool								original_region_gabarite = false;
	ERegionGabarite*					draw_only_is_specific_region_overlapped = nullptr;

	std::vector<ESpriteLayer*>			sprite_layer_list;
	//ESpriteLayer*						internal_sprite_layer;

	std::vector<data_action_pointer>	actions_on_click_list;
	std::vector<data_action_pointer>	actions_on_right_click_list;

	Entity* parent_entity;
	EButtonGroup* parent_group;
	ECustomData* parent_custom_data;

	ETextArea* text_area;
	//std::vector<data_action_pointer> action_on_change_text;

	bool catched_side_left = false;
	bool catched_side_right = false;
	bool catched_side_up = false;
	bool catched_side_down = false;
	bool catched_side_mid = false;

	bool catched_body = false;

	bool have_rama = true;
	bool any_visual_changes = true;

	bool clickable_region_is_active = true;

	//bool* editable_borders	= new bool(false);
	bool can_catch_side[_CRS_SIDE_LAST_ELEMENT]{ false };

	float catch_offset_x = 0.0f;
	float catch_offset_y = 0.0f;

	float hover_time = 0.0f;

	//float* internal_vertex_buffer;

	static bool overlapped_by_mouse(EClickableArea* _region, float _offset_x, float _offset_y, float _zoom);
	static bool catched_side_by_mouse(float _x, float _y, float _size_x, float _size_y, float _offset_x, float _offset_y, float _zoom, float _catch_distance = 5.0f);
	void check_all_catches();
	void translate_clickable_region(float _x, float _y, float _z, bool _move_offset);

	static EClickableArea* active_clickable_region;
	static EClickableArea* create_default_clickable_region(ERegionGabarite* _gabarite, Entity* _parent_entity, ECustomData* _custom_data);
	static EClickableArea* create_default_clickable_region(ERegionGabarite* _gabarite, EButtonGroup* _parent_button_group);

	

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
	float min_value =0.0f;
	float max_value =5.0f;

	void* value_pointer = nullptr;

	float current_percent = 0.0f;
	float step_multiplier = 1.0f;

	std::string text = "";

	StoredPointerType stored_type = StoredPointerType::STORED_TYPE_FLOAT;

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



//struct DataEntityFilter
//{
//public:
//	std::string							target_tag_name = "";
//	std::vector<std::string>			suitable_values_list;
//};


constexpr unsigned int ID_string_array_size = 65536;
constexpr unsigned int ID_string_array_size_for_hash = ID_string_array_size/128;
struct ID_string
{
	bool is_empty						= true;
	unsigned short int	ID				= 0;
	std::string			string_value	= "";
	
	static void			register_new_ID_string(int _id, std::string _string);
	static ID_string	register_new_unique_ID_by_key(std::string _string);

	//static ID_string GLOBAL_registered_ID_strings[ID_string_array_size];
	static ID_string HASHED_registered_ID_strings[256][ID_string_array_size_for_hash];
	static unsigned int last_registered_id;


	void set_ID_by_string(std::string _string);
};

namespace ERegisteredStrings
{
	extern const ID_string data_type;
	extern const ID_string icon_path;
	extern const ID_string name_EN;
	extern const ID_string name_RU;
	extern const ID_string base_name;
	extern const ID_string base_class;
	extern const ID_string short_name;
	extern const ID_string max_stack_size;
	extern const ID_string stack_multiplier;
	extern const ID_string max_sockets;
	extern const ID_string base_ward_min;
	extern const ID_string base_ward_max;
	extern const ID_string base_armour_min;
	extern const ID_string base_armour_max;
	extern const ID_string base_evasion_min;
	extern const ID_string base_evasion_max;
	extern const ID_string base_energy_shield_min;
	extern const ID_string base_energy_shield_max;
	extern const ID_string item_height;
	extern const ID_string item_width;
	extern const ID_string key;
	extern const ID_string worth;
	extern const ID_string base_worth;

	extern const ID_string trash;
	extern const ID_string common;
	extern const ID_string moderate;
	extern const ID_string rare;
	extern const ID_string expensive;
	extern const ID_string very_expensive;

	extern const ID_string item_tag;
	extern const ID_string all_sockets_white;
	extern const ID_string always_six_linked;

	extern const ID_string rarity_override;
	extern const ID_string unique_item;
	extern const ID_string details_ID;

	extern const ID_string divination_cards;
	extern const ID_string stackable_currency;
	extern const ID_string support_gems;
	extern const ID_string map_fragments;
	extern const ID_string embers_of_allflame;
	extern const ID_string expensive_base_for_unique;
	extern const ID_string good_base_for_unique;

	extern const ID_string worth_world_drop;
	extern const ID_string worth_boss_drop;

	extern const ID_string world_drop;
	extern const ID_string boss_drop;
	extern const ID_string heist_drop;
	extern const ID_string uber_lab;
	extern const ID_string replica_item;
	extern const ID_string assembled_from_pieces;
	extern const ID_string atzoatl_sacrifice;
	extern const ID_string non_world_drop;
	extern const ID_string upgraded_by_blessing;
	extern const ID_string vendor_recipe;
	extern const ID_string blight_drop;
	extern const ID_string simulacrum;

	extern const ID_string dust_quantity;


}






struct DETF_SuitableVariant
{
public:
	ID_string			target_value_key;


	ELocalisationText	localised_attribute_name;
	HSVRGBAColor		text_color;


	bool				DETF_is_active	= true;
	bool				always_suitable = false;
	bool				force_field		= false;
};



struct DataEntityTagFilter
{
public:
	ID_string				target_tag;
	bool					can_be_configured	= true;
	bool					merge_with_prev		= false;


	//std::vector<std::string>	suitable_values;
	//std::vector<std::string>	banned_tags;

	std::vector<DETF_SuitableVariant>	suitable_values;
	std::vector<DETF_SuitableVariant>	banned_tags;

	void add_new_suitable_value				(std::string _value, ELocalisationText _ltext = ELocalisationText());
	void add_new_suitable_value_with_color	(std::string _value, ELocalisationText _ltext, float _r, float _g, float _b, float _a);
	void add_new_banned_value(std::string _value, ELocalisationText _ltext = ELocalisationText());

	void set_text_color(float _r, float _g, float _b, float _a);
	void add_force_field();

	



	
};


class EFilterRule
{
public:
	ELocalisationText localisation_text;

	std::string focused_by_data_type = "";

	//std::vector<DataEntityFilter*>		required_tag_list;
	//std::vector<DataEntityFilter*>		banned_tag_list;

	std::vector<DataEntityTagFilter>		required_tag_list;
	std::vector<DataEntityTagFilter>		banned_tag_list;


	


	std::string							tag									= "";
	float								min_y_size							= 100.0f;

	data_action_pointer					stored_action_for_data_entity_group = nullptr;
	//unsigned int						category_id							= 0;

	ETextureGabarite*					icon_texture;

	bool								is_folder	= false;
	std::string							named_id	= "";

	bool								always_show = false;

	//void								add_default_banned_tag();
	
	
	void	reset_filter_rule();
	
	
	static	std::vector<EFilterRule*>	registered_global_filter_rules;
	static	std::vector<EFilterRule*>	registered_filter_rules_for_list;

	static bool matched_by_filter_rule(EDataEntity* _data_entity, EFilterRule* _filter_rule, std::string _search_text);
};

class EDataContainer_Group_DataEntitiesSearch : public EDataContainer
{
public:
	//std::vector<DataEntityFilter*>	required_tag_list;
	//std::vector<DataEntityFilter*>	banned_tag_list;
	EFilterRule* target_rule;

	EntityButton* pointer_to_search_bar;
	EntityButton* pointer_to_add_as_item_button;
	EButtonGroup* pointer_to_group_with_data_entities;
	EButtonGroup* pointer_to_group_with_filter_rules_list;
	EButtonGroup* pointer_to_group_with_configurers;
	EButtonGroup* pointer_to_group_item_receiver;

	ETextArea* filter_text_area;

	data_action_pointer				action_on_select_for_button;

};

class EDataContainer_VerticalNamedSlider : public EDataContainer
{
public:
	//ESpriteLayer*			pointer_to_head;
	ESpriteLayer*			pointer_to_brick_line_sprite_layer;
	ESpriteLayer*			pointer_to_digit_section_sprite_layer;

	EGUIStyle*				slider_style;

	ELocalisationText		stored_text;
	ETextArea*				pointer_to_text_area;
	ETextArea*				pointer_to_digit_text_area;

	float					operable_area_size_x;
	float					current_slide_value;



	float					min_value = 0.0f;
	float					mid_value = 0.5f;
	float					max_value = 1.0f;
	

	void*					pointer_to_value;

	bool					force_shift = false;
	bool					rounded_numbers = false;

	bool					is_float = true;
	bool					need_init = true;

	float					slider_stored_value;

	data_action_pointer		additional_action_on_slide;

	float					get_slider_value_by_pointer_value(float _pointer_value);
	//EDataContainer*			additional_data_container;
};


//class EDataContainer_Button_StoreColor : public EDataContainer
//{
//public:
//	HSVRGBAColor* stored_color;
//	ColorButtonMode selected_mode = ColorButtonMode::CBM_OPEN_WINDOW;
//};
class EntityButtonColorButton;

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

	HSVRGBAColor* work_color;

	EButtonGroup* pointer_to_color_box_sector;
	EButtonGroup* pointer_to_color_collection_sector;

	//data containers of color ajust buttons
	EDataContainer_VerticalNamedSlider* slider_data_value_container;
	EDataContainer_VerticalNamedSlider* slider_data_alpha_container;

	EDataContainer_CrosshairSlider* crosshair_slider_data_container;




	EntityButtonColorButton* target_color_button;

};


class EDataContainer_DataEntityHolder : public EDataContainer
{
public:
	EDataEntity* stored_data_entity;
};



class EDataContainer_Group_StoreFilterRuleForDataEntitySearcher : public EDataContainer
{
public:
	EButtonGroup* target_group_receiver;
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
	GameItemAttribute* target_attribute;
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
//	HSVRGBAColor**		pointer_to_HRA_color[3];
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

//class EDataContainer_Group_FilterBlockNonListedSegment : public EDataContainer
//{
//public:
//	EntityButton* target_button_with_attribute_name;
//	EntityButton* target_button_with_condition;
//	EntityButton* target_button_with_value;
//
//	EntityButtonVariantRouterForFilterBlock* rarity_router_button;
//
//	GameItemAttribute* target_filter_block_attribute;
//};




class EDataContainer_Group_AddContentToFilterBlock : public EDataContainer
{
public:
	EButtonGroupFilterBlock* target_filter_block;

	ETextArea* typing_text_area;
};

//class EDataContainer_Button_MultiGroupButtonSearcher : public EDataContainer
//{
//public:
//	std::vector <EButtonGroup*> target_group_list;
//};

class EDataContainer_Button_BoolSwitcher : public EDataContainer
{
public:
	ETextureGabarite* texture_gabarite_on;
	ETextureGabarite* texture_gabarite_off;

	bool* target_value;
	bool reverse_mode = false;
};


//////////////////////////////////////////////////////////////////////
// actions section
//////////////////////////////////////////////////////////////////////

namespace EDataActionCollection
{
	

	void action_log_text(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_player_control(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_update_slider(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_update_vertical_slider(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_change_style						(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_highlight_button_if_overlap(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_style(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_close_root_group(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_delete_entity(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_switch_description(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_update_radial_button(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_type_text							(Entity* _entity, ECustomData* _custom_data, float _d);



	/*	open groups	*/

	void action_open_color_group(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_add_item_to_group_receiver(Entity* _entity, ECustomData* _custom_data, float _d);
	

	void action_update_crosshair_slider(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_draw_crosshair_slider(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_update_horizontal_named_slider(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_update_horizontal_named_slider			(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_draw_horizontal_named_slider(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_draw_vertical_named_slider(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_convert_HSV_to_RGB(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_button(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_force_resize_callback(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_invoke_data_entity_group_action(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_set_button_group_as_active(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_switch_boolean_value(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_transfer_pointer_to_color_data_container(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_unbing_color(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_create_new_color(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_rotate_variant(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_rotate_variant_from_list(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_invoke_stored_confirm_action(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_close_program(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_cancel_closing_program(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_set_unsaved_changes(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_url(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_active_filter_block						(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_active_text_area(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_out_main_text_area(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_refresh_parent_group_slider_version(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_refresh_parent_group_router_variant_version(Entity* _entity, ECustomData* _custom_data, float _d);



	//type text
	void action_type_search_data_entity_text(ETextArea* _text_area);
	void action_type_text_multiblock_searcher(ETextArea* _text_area);
	void action_deactive_text_area(ETextArea* _text_area);
	void action_change_localisation_for_color_button(ETextArea* _text_area);

	//group section
		//draw
	void action_draw_color_rectangle_for_group(EButtonGroup* _group);

	//update
	void action_convert_HSV_to_RGB(EButtonGroup* _group);
	void action_forcibly_redraw_specific_buttons(EButtonGroup* _group);

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
	static std::string		to_lower(std::string _text);
	static bool				compare_ignoring_case(std::string _text1, std::string _text2);
	static bool				A_contains_B_ignore_case(std::string _text_A, std::string _text_B);
	static std::string		UTF8_to_ANSI(std::string _text);

	static bool				if_text_is_number(std::string _text);
	static bool				if_text_is_float(std::string _text);

	static int				safe_convert_string_to_number	(std::string _text, int _min,	int _max);
	static float			safe_convert_string_to_float	(std::string _text, float _min, float _max);

	static std::string		string_array[512];

	static void				split_line_to_array(std::string _line, bool _ignore_spaces = false);


	static int				hashFunction(std::string _input);
	static int				get_id_by_hash(std::string _input);
};

