#pragma once
#include <string>

#include <vector>
#include <NoSimpleWayAPI[v2]/ETextCore.h>
class ELocalisationText;
class EBrickStyle;
class EGUIStyle
{
public:

	static int number;

	EBrickStyle* button_group_main = nullptr;
	EBrickStyle* button_group_darken = nullptr;

	EBrickStyle* slider_bg = nullptr;
	EBrickStyle* button_bg = nullptr;

	EBrickStyle* slider_inactive = nullptr;
	EBrickStyle* slider_active = nullptr;

	EBrickStyle* round_slider = nullptr;

	std::string* folder = new std::string("lead_and_gold");
	float		text_color_multiplier[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

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

constexpr auto NSW_RECURSIVE			= true;
constexpr auto NSW_ONLY_TARGET			= false;

class EButtonGroup
{
public:

	std::string debug_name = "";
	//float* offset_x = new float(0.0f);
	//float* offset_y = new float(0.0f);

	//float* size_x = new float(0.0f);
	//float* size_y = new float(0.0f);

	ButtonAlignType button_align_type = ButtonAlignType::BUTTON_ALIGN_LEFT;

	bool debug_translation = false;
	bool can_be_moved = true;
	bool have_shadow = true;

	float shadow_size = 32.0f;

	EButtonGroup(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y);
	EButtonGroup(ERegionGabarite* _gabarite);
	EButtonGroup();
	virtual ~EButtonGroup();

	//EButtonGroup* header_button_group;

	EButtonGroup* root_group = nullptr;

	EntityButton* slider = nullptr;

	ERenderBatcher* batcher_for_default_draw = nullptr;

	ERegionGabarite* region_gabarite = nullptr;

	std::vector<EntityButton*> button_list;
	//std::vector<EButtonGroupRow*> group_row_list;
	//EButtonGroupRow* parent_group_row = nullptr;
	std::vector<EButtonGroup*> group_list;
	EButtonGroup* parent_group = nullptr;

	//int* order_in_vector = new int(0);
	static EButtonGroup* focused_button_group;
	static EButtonGroup* focused_button_group_with_slider;
	static EButtonGroup* catched_group_for_translation;

	bool need_remove = false;

	float scroll_x = (0.0f);
	float scroll_y = (0.0f);

	float highest_point_y = (0.0f);
	float highest_point_y_for_buttons = (0.0f);

	float higher_culling_line			= 0.0f;
	float lower_culling_line			= 0.0f;

	float higher_culling_line_for_bg	= 0.0f;
	float lower_culling_line_for_bg		= 0.0f;

	float base_height;
	float base_width;

	virtual void update(float _d);
	//virtual void post_update(float _d);
	virtual void draw();
	virtual void post_draw();
	void draw_second_pass();

	float min_size_y = 10.0f;


	void substretch_groups_y();
	void check_slider();

	void group_stretch_x();
	void group_stretch_y();

	void align_groups();
	static void calculate_culling_lines(EButtonGroup* _group);

	void realign_all_buttons();

	void align_button_in_gabarite(std::vector<EntityButton*>& button_vector, float slider_additional);
	static void generate_vertex_buffer_for_group(EButtonGroup* _group, bool _recursive = NSW_RECURSIVE);

	void expand_to_workspace_size();

	static void refresh_button_group(EButtonGroup* _group);



	static void change_group(EButtonGroup* _group);
	void refresh_buttons_in_group();


	ESpriteLayer* background_sprite_layer = nullptr;

	bool can_resize_to_workspace_size_x = true;
	bool can_resize_to_workspace_size_y = true;

	float border_bottom	=  (0.0f);
	float border_up		=  (0.0f);

	float border_left	=  (0.0f);
	float border_right	=  (0.0f);

	bool* can_change_style = new bool(true);

	EGUIStyle* selected_style = nullptr;

	static void add_horizontal_scroll_bar(EButtonGroup* _button_group);
	static void set_offset_borders(EButtonGroup* _group, float _left, float _right, float _bottom, float _up);
	static void generate_brick_textured_bg(EButtonGroup* _group);

	static void apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style);

	//base
	static EButtonGroup* create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg);
	void init_button_group(EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg);

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




	//static EButtonGroupRow* add_default_row_to_group(EButtonGroup* _group, ERegionGabarite* _region);
	//static EButtonGroupRow* get_last_created_row(EButtonGroup* _group);

	static void change_style(EButtonGroup* _group, EGUIStyle* _style);

	unsigned int* culling_lines_method = new unsigned int(CullingLinesCalcMethod::CLCM_BY_PARENT_GROUP);
	unsigned int* button_group_type = new unsigned int(ButtonGroupType::BGT_REGULAR);

	//unsigned int* gabarite_size_mode_x		= new unsigned int(GroupStretchMode::CONSTANT);
	//unsigned int* gabarite_size_mode_y		= new unsigned int(GroupStretchMode::CONSTANT);

	unsigned int child_align_mode = ChildAlignMode::ALIGN_VERTICAL;

	//static EButtonGroup* focused_button_group;

	//static void get_focused_group(EButtonGroup* _group);
	static void get_last_focused_group(EButtonGroup* _group);

	static bool catched_by_mouse(EButtonGroup* _group);

	static void stretch_parent_group(EButtonGroup* _group, float _new_y_size);

	bool have_bg						= (true);
	bool can_be_focused					= (true);
	bool is_active						= (true);
	bool disable_gabarite				= (false);

	bool force_new_line					= (false);
	bool parent_have_slider				= (false);
	bool need_redraw					= (false);
	bool can_be_stretched_by_child		= (false);

	bool stretch_x_by_parent_size		= (false);
	bool stretch_y_by_parent_size		= (false);

	bool have_slider					= (false);

	bool can_change_position_in_vector	= true;

	bool dynamic_autosize_for_window	= false;

	EButtonGroup* add_group(EButtonGroup* _new_group);
	EButtonGroup* add_group_scecific_position(EButtonGroup* _new_group, int _specific_position);

	EDataContainer* data_container = nullptr;

	std::vector<group_update_action>			actions_on_update;
	std::vector<group_draw_action>				actions_on_draw;
	std::vector<group_select_action>			actions_on_select_button;
	std::vector<group_window_resize_action>		actions_on_resize_window;
	std::vector<group_close_action>				actions_on_close;


	//static fuck_you_leatherman
	static EButtonGroup* data_entity_filter;
	static EButtonGroup* color_editor_group;
	static EButtonGroup* add_content_to_filter_block_group;
	static EButtonGroup* header_line;
	static EButtonGroup* existing_loot_filter_list;

	static EButtonGroupSoundList* sound_list_group;

	void translate(float _x, float _y, float _z, bool _affect_child);
	void translate_content(float _x, float _y, float _z, bool _move_slider);
	bool can_see_this_group();
	void phantom_translate_if_need();
	void recursive_phantom_translate_if_need();

	EntityButton* selected_button;

	void select_this_button(EntityButton* _but);

	bool group_phantom_redraw = false;

	int seed = 0;

	EButtonGroup* set_parameters(ChildAlignMode _child_align_mode, bool _autosize_x, bool _autosize_y);

	static std::vector<FreshCreatedGroup*> fresh_created_block_list;

	EWindow* parent_window;

	void move_to_foreground();

	ChildElementsAlignDirection child_align_direction = ChildElementsAlignDirection::BOTTOM_TO_TOP;

	float button_size_x_override = 0.0f;
};



class EButtonGroupRouterVariant: public EButtonGroup
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
enum StyleList
{
	STYLE_LIST_LEAD_AND_GOLD,
	STYLE_LIST_DARK_SPRUCE,
	STYLE_LIST_GRAY_MINIMALISM
};


class EBrickStyle
{
public:
	ETextureGabarite* main_texture = nullptr;
	ETextureGabarite* normal_map_texture = nullptr;
	ETextureGabarite* gloss_map_texture = nullptr;

	std::string* file_name = new std::string("Group_bg");

	float* side_size_left = new float(0.0f);
	float* side_size_right = new float(0.0f);
	float* side_size_bottom = new float(0.0f);
	float* side_size_up = new float(0.0f);

	float* side_offset_left = new float(0.0f);
	float* side_offset_right = new float(0.0f);
	float* side_offset_bottom = new float(0.0f);
	float* side_offset_up = new float(0.0f);

	int* subdivision_x = new int(0);
	int* subdivision_y = new int(0);

	static void set_border_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up);
	static void set_offset_size(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up);
	static void set_subdivisions(EBrickStyle* _brick, int _x, int _y);

	EBrickStyle();
	EBrickStyle(std::string _file_name);
	~EBrickStyle();

	static void apply_brick_parameters_to_button_group(EButtonGroup* _group, EBrickStyle* _brick);
};

