#pragma once

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

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

#include <vector>

enum ENUM_ButtonAutoAlign
{
	BUTTON_AUTO_ALIGN__PUSH,								//push button to axis
	BUTTON_AUTO_ALIGN__RESET_CURRENT_AXIS_AND_PUSH_ANOTHER,	//transfer button to new column/row, and reset current axis
	BUTTON_AUTO_ALIGN__PUSH_WITH_EXTRA_SPACE,				//push and add more space between previvous button
	BUTTON_AUTO_ALIGN__FREE								//set exactly position
};

//class EButtonContainer;


class EWindow
{
public:
	float* position_x = new float(0.0f);
	float* position_y = new float(0.0f);

	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);

	std::vector<EButtonGroup*> button_container_list;
	

	void			update_default(float _d);
	virtual void	update_additional(float _d);

	void			GUI_update_default(float _d);
	virtual void	GUI_update_additional(float _d);

	void			draw_default(float _d);
	virtual void	draw_additional(float _d);

	void			GUI_draw_default(float _d);
	virtual void	GUI_draw_additional(float _d);

	std::vector<EButtonGroup*> group_list;
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

class EButtonGroup
{
public:
	//float* offset_x = new float(0.0f);
	//float* offset_y = new float(0.0f);

	//float* size_x = new float(0.0f);
	//float* size_y = new float(0.0f);


	EButtonGroup(float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y);
	EButtonGroup(ERegionGabarite* _gabarite);
	~EButtonGroup();

	EButtonGroup* header_button_group;

	EButtonGroup* root_group = nullptr;

	EntityButton* slider = nullptr;

	ERenderBatcher* batcher_for_default_draw = nullptr;

	ERegionGabarite* region_gabarite = nullptr;

	std::vector<EntityButton*> button_list;
	//std::vector<EButtonGroupRow*> group_row_list;
	//EButtonGroupRow* parent_group_row = nullptr;
	std::vector<EButtonGroup*> group_list;
	EButtonGroup* parent_group = nullptr;

	int* order_in_vector = new int(0);
	static EButtonGroup* focused_button_group;
	static EButtonGroup* focused_button_group_with_slider;

	float* scroll_x = new float(0.0f);
	float* scroll_y = new float(0.0f);

	float* highest_point_y = new float(0.0f);

	float* higher_culling_line = new float(0.0f);
	float* lower_culling_line = new float(0.0f);

	float* higher_culling_line_for_bg = new float(0.0f);
	float* lower_culling_line_for_bg = new float(0.0f);

	float* base_height		= new float(0.0f);
	float* base_width		= new float(0.0f);

	void update(float _d);
	void draw();
	void draw_second_pass();

		
		void substretch_groups_y();
		void check_slider();

		void group_stretch_x();
		void group_stretch_y();

		void align_groups();
		static void calculate_culling_lines(EButtonGroup* _group);
		void realign_all_buttons();
		static void generate_vertex_buffer_for_group(EButtonGroup* _group);
		

		static void refresh_button_group(EButtonGroup* _group);

	ESpriteLayer* background_sprite_layer = nullptr;
	
	float*	border_bottom		= new float(0.0f);
	float*	border_up			= new float(0.0f);

	float*	border_left			= new float(0.0f);
	float*	border_right		= new float(0.0f);

	bool*	can_change_style	= new bool (true);

	EGUIStyle* selected_style = nullptr;

	static void add_horizontal_scroll_bar(EButtonGroup* _button_group);
	static void set_offset_borders(EButtonGroup* _group, float _left, float _right, float _bottom, float _up);
	static void generate_brick_textured_bg(EButtonGroup* _group);

	static void apply_style_to_button_group(EButtonGroup* _group, EGUIStyle* _style);

	//base
	static EButtonGroup* create_base_button_group		(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg);
	
	//bg, slider, focusable, bright
	static EButtonGroup* create_default_button_group	(ERegionGabarite* _region, EGUIStyle* _style);
	
	//bg, slider, focusable, dark, [no slider]
	static EButtonGroup* create_root_button_group		(ERegionGabarite* _region, EGUIStyle* _style);
	
	//bg, dark, [unfocusable], [no slider]
	static EButtonGroup* create_header_button_group		(ERegionGabarite* _region, EGUIStyle* _style);
	
	//[no bg], [not focusable], [no slider]
	static EButtonGroup* create_invisible_button_group	(ERegionGabarite* _region, EGUIStyle* _style);
	
	//[no bg], focusable, slider
	static EButtonGroup* create_button_group_without_bg	(ERegionGabarite* _region, EGUIStyle* _style);
	

	//static EButtonGroupRow* add_default_row_to_group(EButtonGroup* _group, ERegionGabarite* _region);
	//static EButtonGroupRow* get_last_created_row(EButtonGroup* _group);

	static void change_style(EButtonGroup* _group, EGUIStyle* _style);

	unsigned int* culling_lines_method		= new unsigned int(CullingLinesCalcMethod::CLCM_BY_PARENT_GROUP);
	unsigned int* button_group_type			= new unsigned int(ButtonGroupType::BGT_REGULAR);

	//unsigned int* gabarite_size_mode_x		= new unsigned int(GroupStretchMode::CONSTANT);
	//unsigned int* gabarite_size_mode_y		= new unsigned int(GroupStretchMode::CONSTANT);

	unsigned int* stretch_mode				= new unsigned int(GroupStretchMode::CONSTANT);
	unsigned int* child_align_mode			= new unsigned int(ChildAlignMode::ALIGN_VERTICAL);

	//static EButtonGroup* focused_button_group;

	//static void get_focused_group(EButtonGroup* _group);
	static void get_last_focused_group(EButtonGroup* _group);
	
	static bool catched_by_mouse(EButtonGroup* _group);

	static void stretch_parent_group(EButtonGroup* _group, float _new_y_size);

	bool* have_bg = new bool(true);
	bool* can_be_focused = new bool(true);
	bool* is_active = new bool(true);

	bool* force_new_line					= new bool(false);
	bool* parent_have_slider				= new bool(false);
	bool* need_redraw						= new bool(false);
	bool* can_be_stretched_by_child			= new bool(false);

	bool* stretch_x_by_parent_size			= new bool(false);
	bool* stretch_y_by_parent_size			= new bool(false);

	bool* have_slider						= new bool(false);

	EButtonGroup* add_group(EButtonGroup* _new_group);



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
	ETextureGabarite*									main_texture			= nullptr;
	ETextureGabarite*									normal_map_texture		= nullptr;
	ETextureGabarite*									gloss_map_texture		= nullptr;

	std::string*										file_name			= new std::string("Group_bg");

	float*												side_size_left		= new float (0.0f);
	float*												side_size_right		= new float (0.0f);
	float*												side_size_bottom	= new float (0.0f);
	float*												side_size_up		= new float (0.0f);

	float*												side_offset_left	= new float (0.0f);
	float*												side_offset_right	= new float (0.0f);
	float*												side_offset_bottom	= new float (0.0f);
	float*												side_offset_up		= new float (0.0f);

	int*												subdivision_x		= new int (0);
	int*												subdivision_y		= new int (0);

	static void set_border_size							(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up);
	static void set_offset_size							(EBrickStyle* _brick, float _left, float _right, float _bottom, float _up);
	static void set_subdivisions						(EBrickStyle* _brick, int _x, int _y);

	EBrickStyle();
	EBrickStyle(std::string _file_name);
	~EBrickStyle();

	static void apply_brick_parameters_to_button_group	(EButtonGroup* _group, EBrickStyle* _brick);
};



class EGUIStyle
{
public:

	static int number;

	EBrickStyle*	button_group_main				= nullptr;
	EBrickStyle*	button_group_darken				= nullptr;

	EBrickStyle*	slider_bg						= nullptr;
	EBrickStyle*	button_bg						= nullptr;

	EBrickStyle*	slider_inactive					= nullptr;
	EBrickStyle*	slider_active					= nullptr;

	std::string*	folder							= new std::string("lead_and_gold");
	float			text_color_multiplier[4]		= { 1.0f, 1.0f, 1.0f, 1.0f };
	
	//float text_color_array[16][4];

	EGUIStyle();
	EGUIStyle(std::string _folder);
	~EGUIStyle();

	static std::vector<EGUIStyle*> style_list;
	static EGUIStyle* active_style;

	//void set_color_array(unsigned int _id, float _r, float _g, float _b, float _a);
	void set_color_multiplier(float _r, float _g, float _b, float _a);
};