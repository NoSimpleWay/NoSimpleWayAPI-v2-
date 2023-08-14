#pragma once
#include <string>

#include <vector>
#include <NoSimpleWayAPI[v2]/ETextCore.h>

class ELocalisationText;
class EBrickStyle;

enum BrickStyleID
{
	//NONE_WITH_BORDER	= -2,

	//no bg
	NONE				= -1,

	//thick borders, moderate brightness of background
	GROUP_DEFAULT,

	//bold borders, dark bg
	GROUP_DARKEN,

	//background for slider
	SLIDER_BG,

	//background for buttons
	BUTTON_BG,

	//inactive slider head
	SLIDER_INACTIVE,

	//active slider head
	SLIDER_ACTIVE,

	//circle slider head
	ROUND_SLIDER,

	LAST_ELEMENT
};


constexpr bool NSW_APRIL_FOOL = false;

class EBrickStyle
{
public:
	ETextureGabarite*	main_texture = nullptr;
	ETextureGabarite*	normal_map_texture = nullptr;
	ETextureGabarite*	gloss_map_texture = nullptr;

	EGUIStyle*			parent_style = nullptr;

	std::string file_name = "Group_bg";

	float offset_for_elements_left		= 0.0f;
	float offset_for_elements_right		= 0.0f;
	float offset_for_elements_bottom	= 0.0f;
	float offset_for_elements_up		= 0.0f;

	float border_texture_size_left		= 0.0f;
	float border_texture_size_right		= 0.0f;
	float border_texture_size_bottom	= 0.0f;
	float border_texture_size_up		= 0.0f;

	int subdivision_x			= 0;
	int subdivision_y			= 0;

	static void set_border_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up);
	static void set_offset_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up);
	static void set_subdivisions(EBrickStyle* _brick, int _x, int _y);

	EBrickStyle();
	EBrickStyle(std::string _file_name);
	~EBrickStyle();

	static void apply_brick_parameters_to_button_group(EButtonGroup* _group, EBrickStyle* _brick);
};

class EGUIStyle
{
public:

	static int number;

	EBrickStyle brick_style[BrickStyleID::LAST_ELEMENT];

	//EBrickStyle* button_group_main = nullptr;
	//EBrickStyle* button_group_darken = nullptr;

	//EBrickStyle* slider_bg = nullptr;
	//EBrickStyle* button_bg = nullptr;

	//EBrickStyle* slider_inactive = nullptr;
	//EBrickStyle* slider_active = nullptr;

	//EBrickStyle* round_slider = nullptr;

	std::string* folder = new std::string("lead_and_gold");
	float		text_color_multiplier[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	bool is_rotator = false;

	//float text_color_array[16][4];

	EGUIStyle();
	EGUIStyle(std::string _folder);
	~EGUIStyle();

	static std::vector<EGUIStyle*> style_list;
	static EGUIStyle* active_style;

	ELocalisationText	localisation_text;

	//void set_color_array(unsigned int _id, float _r, float _g, float _b, float _a);
	void set_color_multiplier(float _r, float _g, float _b, float _a);
};

#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif

/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "EntityCore.h"
#endif
/**/



//#ifndef _E_TEXT_CORE_ALREADY_LINKED_
///**/#define _E_TEXT_CORE_ALREADY_LINKED_
///**/#include "ETextCore.h"
//#endif







enum ENUM_ButtonAutoAlign
{
	BUTTON_AUTO_ALIGN__PUSH,								//push button to axis
	BUTTON_AUTO_ALIGN__RESET_CURRENT_AXIS_AND_PUSH_ANOTHER,	//transfer button to new column/row, and reset current axis
	BUTTON_AUTO_ALIGN__PUSH_WITH_EXTRA_SPACE,				//push and add more space between previvous button
	BUTTON_AUTO_ALIGN__FREE									//set exactly position
};

#define NSW_dynamic_autosize	true
#define NSW_static_autosize		false


//class EButtonContainer;


class EWindow
{
public:
	std::vector<EButtonGroup*> button_group_list;
	std::vector<EButtonGroup*> autosize_group_list;

	float* position_x = new float(0.0f);
	float* position_y = new float(0.0f);

	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);

	//std::vector<EButtonGroup*> button_container_list;


	void			update_default(float _d);
	virtual void	update_additional(float _d);

	void			GUI_update_default(float _d);
	virtual void	GUI_update_additional(float _d);

	void			draw_default(float _d);
	virtual void	draw_additional(float _d);

	void			GUI_draw_default(float _d);
	virtual void	GUI_draw_additional(float _d);
	void			GUI_draw_second_pass(float _d);

	bool			window_need_refresh = false;

	virtual void	action_on_close();

	//////////////		_STATIC SECTION_		////////////////////////

	static std::vector<EWindow*> window_list;

	/////////////////////////////////////////////////////////////////////

	std::vector<TestObject*> test_vector;
};

enum CullingLinesCalcMethod
{
	CLCM_BY_PARENT_GROUP,
	CLCM_BY_HIMSELF
};

//enum ButtonRowType
//{
//	BRT_REGULAR,
//	BRT_HEADER
//};

enum GroupStretchMode
{
	CONSTANT,					//do not resize button group
	STRETCHED_FILL_VOID,		//resife to fill empty space
	STRETCHED_ONLY_BY_PARENT	//resize only to fill vertical/horizontal space
};

//class EButtonGroupRow
//{
//public:
//	ERegionGabarite* gabarite;
//	std::vector<EButtonGroup*> button_group_list;
//	//EButtonGroup* header_button_group;
//
//	EButtonGroup* parent_button_group;
//
//	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
//	EButtonGroupRow(ERegionGabarite* _region);
//	EButtonGroupRow();
//
//	EButtonGroup* add_group(EButtonGroup* _group);
//	static EButtonGroup* get_last_group(EButtonGroupRow* _row);
//
//	float* lowest_culling_line = new float(0.0f);
//	float* highest_culling_line = new float(10000.0f);
//
//	float* highest_culling_line_for_bg	= new float(10000.0f);
//	float* lowest_culling_line_for_bg	= new float(0.0f);
//
//	EButtonGroup* root_group = nullptr;
//
//	unsigned int* gabarite_size_mode_y = new unsigned int(GroupStretchMode::CONSTANT);
//	
//	static void stretch_parent_group(EButtonGroupRow* _row, float _new_y_size);
//	//static EButtonGroupRow* create_default_row(ERegionGabarite* _region);
//};

enum ButtonGroupType
{
	BGT_REGULAR,
	BGT_DARKEN,
	BGT_NO_BG_AND_SLIDER,
	BGT_HEADER
};

enum ChildAlignMode
{
	ALIGN_VERTICAL,
	ALIGN_HORIZONTAL,
	ALIGN_FREE
};

typedef void (*group_draw_action)			(EButtonGroup*);
typedef void (*group_update_action)			(EButtonGroup*);
typedef void (*group_select_action)			(EButtonGroup*);
typedef void (*group_window_resize_action)	(EButtonGroup*);
typedef void (*group_close_action)			(EButtonGroup*);

class FreshCreatedGroup
{
public:
	EButtonGroup* just_created_group;
	EButtonGroup* target_group;
};


enum class ButtonAlignType
{
	BUTTON_ALIGN_LEFT,
	BUTTON_ALIGN_MID,
	BUTTON_ALIGN_RIGHT

};

enum class ChildElementsAlignDirection
{
	BOTTOM_TO_TOP,
	TOP_TO_BOTTOM
};

constexpr float BUTTON_FORCE_FIELD_SIZE = 2.0f;

constexpr auto NSW_RECURSIVE = true;
constexpr auto NSW_ONLY_TARGET = false;

enum class MoveVectorMethod
{
	METHOD_DRAG = 0,
	METHOD_PRESS = 1
};

enum class GroupSearchStatus
{
	SEARCH_STATUS_IGNORE,
	SEARCH_STATUS_MATCHED,
	SEARCH_STATUS_REJECTED
};

struct EButtonGroupLine
{
public:
	float line_size_y = 0.0f;

	float offset_y = 0.0f;

	std::vector<EntityButton*> button_list;
};

enum class HighlightID
{
	GREEN_INFO,
	RED_WARNING
};

struct HighlightStruct
{
	HighlightStruct();

	void set_color(float _r, float _g, float _b, float _a);

	float highlight_color[4]{ 1.0f };

	float max_time			= 1.0f;
	float time_remaining	= 1.0f;

	HighlightID highlight_id = HighlightID::GREEN_INFO;

	static HighlightStruct	create_new_highlihght(float _r, float _g, float _b, float _a, HighlightID _id, float _time);
};


enum class ButtonGroupChangeAfterRemove
{
	CHANGE_ONLY_DELETED_ELEMENT,
	CHANGE_PARENT_GROUP,
	CHANGE_ROOT_GROUP
};

class EButtonGroupFastMessage;	
class EButtonGroup
{
public:

	bool silicon_idiot = false;

	bool is_viped = false;
	std::string debug_name = "";
	//float* offset_x = new float(0.0f);
	//float* offset_y = new float(0.0f);

	//float* size_x = new float(0.0f);
	//float* size_y = new float(0.0f);

	ButtonAlignType button_align_type = ButtonAlignType::BUTTON_ALIGN_LEFT;

	std::vector<EButtonGroupLine> button_line_list;

	void recursive_set_suppressed();
	bool is_blocked_by_superfocus();

	bool group_is_suppressed = false;

	bool debug_translation = false;
	bool can_be_moved = true;
	bool have_shadow = true;
	bool is_selected = false;
	bool focusable_for_select = false;
	bool have_rama = false;
	bool can_be_resized_to_highest_point_y = false;
	bool ignore_buttons_force_field = false;
	bool ignore_vertical_buttons_force_field = false;

	EntityButton* close_button = nullptr;

	int fake_borders_id = -1;

	float min_size_for_resize = 120.0f;
	//bool need_recalcualte_culling_lines = false;
	//bool hidden_by_search = false;
	GroupSearchStatus group_search_status = GroupSearchStatus::SEARCH_STATUS_IGNORE;

	virtual bool is_this_group_active();

	float shadow_size = 32.0f;

	EButtonGroup(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y);
	EButtonGroup(ERegionGabarite* _gabarite);
	EButtonGroup();
	virtual ~EButtonGroup();

	//EButtonGroup* header_button_group;

	EButtonGroup* root_group = nullptr;

	EntityButtonVerticalSlider* slider = nullptr;

	ERenderBatcher* batcher_for_default_draw = nullptr;

	ERegionGabarite* region_gabarite = nullptr;


	std::vector<EntityButton*> all_button_list;
	std::vector<EntityButton*> workspace_button_list;
	void delete_exact_button(EntityButton* _button);
	void remove_all_workspace_buttons();

	float vipe_timer = 1.0f;
	void try_vipe_data(float _d);

	void close_this_group();
	void recursive_close_process();

	void destroy_all_vertex_buffer_data();

	//std::vector<EButtonGroupRow*> group_row_list;
	//EButtonGroupRow* parent_group_row = nullptr;
	std::vector<EButtonGroup*> group_list;
	EButtonGroup* parent_group = nullptr;
	EButtonGroup* close_section = nullptr;
	EButtonGroup* close_section_left_part = nullptr;

	//int* order_in_vector = new int(0);
	static EButtonGroup* focused_button_group;
	static EButtonGroup* focused_button_group_for_select;
	static EButtonGroup* focused_button_group_mouse_unpressed;
	static EButtonGroup* focused_button_group_with_slider;
	static EButtonGroup* catched_group_for_translation;
	static EButtonGroup* super_focus_on_this_group;


	static EButtonGroupFastMessage* pointer_to_fast_message_group;

	//MOVE GROUPS ORDER IN VECTOR
	static EButtonGroup* vector_moving_group;
	static EButtonGroup* parent_vector_moving_group;

	//SELECTED GROUPS
	static EButtonGroup* parent_for_selected_groups;
	static EButtonGroup* first_selected_element;
	static EButtonGroup* last_selected_element;
	static std::vector<EButtonGroup*> selected_groups;

	static MoveVectorMethod move_vector_mode;

	

	ButtonGroupChangeAfterRemove change_after_remove = ButtonGroupChangeAfterRemove::CHANGE_ONLY_DELETED_ELEMENT;

	bool filter_block_need_remove = false;
	bool need_refresh = false;
	bool need_change = false;
	bool need_recalculate_culling_lines = false;

	float scroll_x = (0.0f);
	float scroll_y = (0.0f);

	float final_highest_point_y = (0.0f);
	float highest_point_y_for_buttons = (0.0f);
	float highest_point_y_for_groups = (0.0f);

	float higher_culling_line_for_group		= 0.0f;
	float lower_culling_line_for_group		= 0.0f;

	float higher_culling_line_for_elements	= 0.0f;
	float lower_culling_line_for_elements	= 0.0f;

	float autodelete_time					= -1.0f;

	//float higher_culling_line_for_bg = 0.0f;
	//float lower_culling_line_for_bg = 0.0f;

	float base_height;
	float base_width;

	virtual void button_group_update(float _d);
	virtual void background_update(float _d);

	void recursive_get_info();

	//virtual void post_update(float _d);
	virtual void draw_button_group();
	virtual void draw_button_group_debug_overlay();
	virtual void post_draw();
	void draw_second_pass();

	float min_size_y = 10.0f;
	float max_size_y = 350.0f;


	bool check_slider();
	void check_slider_and_call_recursive_pass_if_need();

	void recursive_group_stretch_childs_x();
	void recursive_group_stretch_childs_y();

	void align_groups();
	static void calculate_culling_lines(EButtonGroup* _group, bool _recursive);

	void realign_all_buttons();

	void align_button_in_gabarite(std::vector<EntityButton*>& button_vector, float slider_additional);
	static void generate_vertex_buffer_for_group(EButtonGroup* _group, bool _recursive = NSW_ONLY_TARGET);

	void recursive_expand_to_workspace_size();

	void recursive_set_recalculate_culling_lines();

	virtual void button_group_prechange();

	/*-----------------------------------*/
	static void refresh_button_group(EButtonGroup* _group);
	static void refresh_button_group_forceful(EButtonGroup* _group);
	static void change_group(EButtonGroup* _group);
	static void recursive_change_group_first_pass(EButtonGroup* _group);
	static void change_group_second_pass(EButtonGroup* _group);


	static void soft_recursion_first_pass(EButtonGroup* _group);
	/*-----------------------------------*/

	virtual void button_group_postchange();


	void recalculate_culling_lines();
	void recursive_recalculate_culling_lines();
	void recursive_reset_phantom_translate();
	void reset_buttons_phantom_translate();
	void reset_slider();
	void set_base_size_x();
	void put_buttons_to_lines();
	void set_buttons_offset();
	//void align_buttons_to_lines();
	void calculate_group_lines();
	void activate_slider_if_need();
	void stretch_all_buttons();
	void align_buttons_in_lines();
	void calculate_world_coordinates_for_buttons();
	
	void resize_group_to_highest_point_y();
	float get_child_total_y_size();
	float get_highest_point_y_for_groups();

	void slide_to_this_group(EButtonGroup* _group);

	void scroll_down(float _value);
	void scroll_up	(float _value);

	


	void add_button_to_working_group(EntityButton* _button);
	void add_button_to_additional_group(EntityButton* _button);
	ESpriteLayer* background_sprite_layer = nullptr;

	bool can_resize_to_workspace_size_x = true;
	bool can_resize_to_workspace_size_y = true;

	float group_offset_for_content_bottom	= (0.0f);
	float group_offset_for_content_up		= (0.0f);

	float group_offset_for_content_left		= (0.0f);
	float group_offset_for_content_right	= (0.0f);
	

	float group_border_texture_bottom		= (0.0f);
	float group_border_texture_up			= (0.0f);
				
	float group_border_texture_left			= (0.0f);
	float group_border_texture_right		= (0.0f);

	std::vector<HighlightStruct> highlight_list;

	float additional_y_distance = 0.0f;

	bool can_change_style = new bool(true);

	EGUIStyle* selected_style = nullptr;

	static void add_vertical_scroll_bar(EButtonGroup* _button_group);
	static void set_offset_borders(EButtonGroup* _group, float _left, float _right, float _bottom, float _up);
	static void generate_brick_textured_bg(EButtonGroup* _group);

	static void apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style);
	static void apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style, BrickStyleID _brick_style_id);

	//base
	static EButtonGroup* create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg);
	void init_button_group(EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg);
	void init_button_group(EGUIStyle* _style, BrickStyleID _brick_style_id, bool _have_slider);

	//bg, slider, focusable, bright
	static EButtonGroup* create_default_button_group(ERegionGabarite* _region, EGUIStyle* _style);

	//bg, slider, focusable, dark, [no slider]
	static EButtonGroup* create_root_button_group(ERegionGabarite* _region, EGUIStyle* _style);

	//bg, dark, [unfocusable], [no slider]
	static EButtonGroup* create_header_button_group(ERegionGabarite* _region, EGUIStyle* _style);

	//[no bg], [not focusable], [no slider]
	static EButtonGroup* create_invisible_button_group(ERegionGabarite* _region, EGUIStyle* _style);

	//[no bg], focusable, slider
	static EButtonGroup* create_button_group_without_bg(ERegionGabarite* _region, EGUIStyle* _style);

	static EButtonGroup* create_color_editor_group(ERegionGabarite* _region, EGUIStyle* _style);

	EButtonGroup* add_close_group_and_return_workspace_group(ERegionGabarite* _region, EGUIStyle* _style);
	void add_caption_by_localistation_key(std::string _key);
	void add_help_button(ETextureGabarite* _texture_gabarite, std::string _key);

	void scroll_to_this_button(EntityButton* _button);




	//static EButtonGroupRow* add_default_row_to_group(EButtonGroup* _group, ERegionGabarite* _region);
	//static EButtonGroupRow* get_last_created_row(EButtonGroup* _group);

	static void recursive_change_style(EButtonGroup* _group, EGUIStyle* _style);

	unsigned int* culling_lines_method = new unsigned int(CullingLinesCalcMethod::CLCM_BY_PARENT_GROUP);
	unsigned int* button_group_type = new unsigned int(ButtonGroupType::BGT_REGULAR);

	BrickStyleID brick_style_id;

	//unsigned int* gabarite_size_mode_x		= new unsigned int(GroupStretchMode::CONSTANT);
	//unsigned int* gabarite_size_mode_y		= new unsigned int(GroupStretchMode::CONSTANT);

	unsigned int child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

	//static EButtonGroup* focused_button_group;

	//static void get_focused_group(EButtonGroup* _group);
	static void get_last_focused_group(EButtonGroup* _group);

	static bool catched_by_mouse(EButtonGroup* _group);

	bool group_have_background			= true;
	bool group_have_button_lines		= false;
	bool can_be_focused					= true;
	bool button_group_is_active			= true;
	bool disable_gabarite				= false;

	bool force_new_line					= false;
	bool parent_have_slider				= false;
	bool need_redraw					= false;
	bool can_be_stretched_by_child		= false;

	bool stretch_x_by_parent_size		= false;
	bool dynamic_size_y					= false;

	bool have_slider					= false;

	bool can_change_position_in_vector	= true;

	bool dynamic_autosize_for_window	= false;

	//ETextArea* text_area;
	std::vector<EClickableArea*> clickable_area_list;

	EButtonGroup* add_group(EButtonGroup* _new_group);
	EButtonGroup* add_group_scecific_position(EButtonGroup* _new_group, int _specific_position);

	EDataContainer* data_container = nullptr;

	std::vector<group_update_action>			actions_on_update;
	std::vector<group_draw_action>				actions_on_draw;
	std::vector<group_select_action>			actions_on_select_button;
	std::vector<group_window_resize_action>		actions_on_resize_window;
	std::vector<group_close_action>				actions_on_close;


	//static fuck_you_leatherman

	static EButtonGroup* color_editor_group;
	static EButtonGroup* add_content_to_filter_block_group;



	static EButtonGroupSoundList* sound_list_group;

	void translate_group(float _x, float _y, float _z, bool _affect_child);
	void translate_group_content(float _x, float _y, float _z, bool _move_slider);
	bool is_in_visible_diapason();
	void phantom_translate_if_need();
	void recursive_phantom_translate_if_need();

	EntityButton* selected_button;

	void select_this_button(EntityButton* _but);

	bool group_phantom_redraw = false;

	int seed = 0;

	EButtonGroup* set_parameters(ChildAlignMode _child_align_mode, bool _autosize_x, bool _autosize_y);

	static std::vector<FreshCreatedGroup*> fresh_created_block_list;

	EWindow* parent_window;
	EClickableArea* main_clickable_area;

	void activate_move_to_foreground_and_center();
	void move_to_foreground();
	void move_to_foreground_and_center();

	ChildElementsAlignDirection child_align_direction = ChildElementsAlignDirection::BOTTOM_TO_TOP;

	float button_size_x_override = 0.0f;

	//float max_highlight_time = 0.35f;
	//float highlight_time = 0.0f;

	void highlight_this_group(float _r, float _g, float _b, float _a, HighlightID _id, float _time);

	void highlight_this_group_green_info();
	void highlight_this_group_red_warning();

	void recursive_change_localisation(int _localisaton_id);

	void add_default_clickable_region_with_text_area(ELocalisationText _text);

	void init_as_root_group(EWindow* _window);
	void init_as_fast_message(EWindow* _window, ELocalisationText _text);

	void clear_group_selection();
};

class EButtonGroupFastMessage : public EButtonGroup
{
public:
	EButtonGroupFastMessage(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	float exist_time = 2.0f;
	bool delete_when_expire = false;
	void button_group_update(float _d) override;
};

class EButtonGroupRouterVariant : public EButtonGroup
{

public:
	EntityButtonVariantRouter* target_router_button = nullptr;

	static EButtonGroupRouterVariant* create_router_variant_button_group(EWindow* _target_window, EntityButtonVariantRouter* _router_button);

	EButtonGroupRouterVariant(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	~EButtonGroupRouterVariant();
};
//class EButtonContainer
//{
//	ERegionGabarite* gabarite;
//
//	void update(float _d);
//	void draw();
//
//	std::vector<EButtonGroup*> button_group_list;
//};

class EntityButtonConfirmAction;
class EButtonGroupConfirmAction : public EButtonGroup
{
public:
	EButtonGroupConfirmAction(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButtonConfirmAction* pointer_to_confirm_button;
	EntityButtonConfirmAction* pointer_to_decline_button;

	EButtonGroup* pointer_to_workspace_part;
	ETextArea* pointer_to_description_text_area;

	//data_action_pointer				action_on_accept;
	//data_action_pointer				action_on_decline;

	void								init_as_confirm_decline_group();
	
	//EButtonGroupConfirmAction::confirm_decline_group->pointer_to_confirm_button->stored_action = &EDataActionCollection::action_open_loot_filters_list_window;


	static EButtonGroupConfirmAction* confirm_decline_group;
};

enum StyleList
{
	STYLE_LIST_LEAD_AND_GOLD,
	STYLE_LIST_DARK_SPRUCE,
	STYLE_LIST_GRAY_MINIMALISM
};

#ifndef _DEBUG_STRUCTS_ALREADY_DEFINED_
#define _DEBUG_STRUCTS_ALREADY_DEFINED_


	class EntityButtonDebugStructButton;


	struct EDebugStruct
	{
	public:
		ELocalisationText	localisation_text;
		int					selected_variant = 0;
		ETextureGabarite*	icon;

		EntityButtonDebugStructButton* associated_button_router;
	};

	namespace DebugNamespace
	{
		extern EDebugStruct NSW_registered_debug_struct[DebugStructID::DEBUG_STRUCT_ID_LAST_ELEMENT];
		extern EButtonGroup* NSW_pointer_to_debug_window;
		extern bool is_debug_element_active(DebugStructID _id);
	}
#endif


