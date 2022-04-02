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

	std::vector<EButtonGroup*> button_group_list;


	//////////////		_STATIC SECTION_		////////////////////////

	static std::vector<EWindow*> window_list;

	/////////////////////////////////////////////////////////////////////
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

enum ButtonGroupGabariteSize
{
	BGGS_CONSTANT,
	BGGS_EXACT_STRETCH
};

class EButtonGroupRow
{
public:
	ERegionGabarite* gabarite;
	std::vector<EButtonGroup*> button_group_list;
	//EButtonGroup* header_button_group;

	EButtonGroup* parent_button_group;

	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	EButtonGroupRow(ERegionGabarite* _region);
	EButtonGroupRow();

	EButtonGroup* add_group(EButtonGroup* _group);
	static EButtonGroup* get_last_group(EButtonGroupRow* _row);

	float* lowest_culling_line = new float(0.0f);
	float* highest_culling_line = new float(10000.0f);

	float* highest_culling_line_for_bg	= new float(10000.0f);
	float* lowest_culling_line_for_bg	= new float(0.0f);

	EButtonGroup* root_group = nullptr;

	unsigned int* gabarite_size_mode_y = new unsigned int(ButtonGroupGabariteSize::BGGS_CONSTANT);
	
	static void stretch_parent_group(EButtonGroupRow* _row, float _new_y_size);
	//static EButtonGroupRow* create_default_row(ERegionGabarite* _region);
};

enum ButtonGroupType
{
	BGT_REGULAR,
	BGT_DARKEN,
	BGT_NO_BG_AND_SLIDER,
	BGT_HEADER
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

	ERegionGabarite* region = nullptr;

	std::vector<EntityButton*> button_list;
	std::vector<EButtonGroupRow*> group_row_list;
	EButtonGroupRow* parent_group_row = nullptr;

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

	void update(float _d);
	void draw();

		void realign_all_buttons();
		void align_groups();
		static void calculate_culling_lines(EButtonGroup* _group);
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

	static EButtonGroup* create_base_button_group(ERegionGabarite* _region, EGUIStyle* _style, bool _have_bg, bool _have_slider, bool _default_bg);
	static EButtonGroup* create_default_button_group(ERegionGabarite* _region, EGUIStyle* _style);
	static EButtonGroup* create_root_button_group(ERegionGabarite* _region, EGUIStyle* _style);
	static EButtonGroup* create_header_button_group(ERegionGabarite* _region, EGUIStyle* _style);
	static EButtonGroup* create_invisible_button_group(ERegionGabarite* _region, EGUIStyle* _style);
	

	static EButtonGroupRow* add_default_row(EButtonGroup* _group, ERegionGabarite* _region);
	static EButtonGroupRow* get_last_created_row(EButtonGroup* _group);

	static void change_style(EButtonGroup* _group, EGUIStyle* _style);

	unsigned int* culling_lines_method		= new unsigned int(CullingLinesCalcMethod::CLCM_BY_PARENT_GROUP);
	unsigned int* button_group_type		= new unsigned int(ButtonGroupType::BGT_REGULAR);
	unsigned int* gabarite_size_mode_y		= new unsigned int(ButtonGroupGabariteSize::BGGS_CONSTANT);

	//static EButtonGroup* focused_button_group;

	//static void get_focused_group(EButtonGroup* _group);
	static void get_last_focused_group(EButtonGroup* _group);
	
	static bool catched_by_mouse(EButtonGroup* _group);

	static void stretch_parent_row(EButtonGroup* _group, float _new_y_size);

	bool* have_bg = new bool(true);

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



class EGUIStyle
{
public:

	static int number;
	//button group
	ETextureGabarite* background_for_button_group	= nullptr;
	float*	offset_border_left						= new float(0.0f);
	float*	offset_border_right						= new float(0.0f);
			
	float*	offset_border_up						= new float(0.0f);
	float*	offset_border_bottom					= new float(0.0f);
	///
	float*	brick_border_left						= new float(0.0f);
	float*	brick_border_right						= new float(0.0f);
			
	float*	brick_border_up							= new float(0.0f);
	float*	brick_border_bottom						= new float(0.0f);
	///
	int*	subdivision_x							= new int (0);
	int*	subdivision_y							= new int (0);

	//dark button group
	ETextureGabarite* background_for_root_button_group	= nullptr;
	float*	dark_offset_border_left						= new float(0.0f);
	float*	dark_offset_border_right					= new float(0.0f);
			
	float*	dark_offset_border_up						= new float(0.0f);
	float*	dark_offset_border_bottom					= new float(0.0f);
	///
	float*	dark_brick_border_left						= new float(0.0f);
	float*	dark_brick_border_right						= new float(0.0f);
			
	float*	dark_brick_border_up						= new float(0.0f);
	float*	dark_brick_border_bottom					= new float(0.0f);
	///
	int*	dark_subdivision_x							= new int(0);
	int*	dark_subdivision_y							= new int(0);

	//button
	ETextureGabarite* backround_for_buttons			= nullptr;
	float*	button_border_left						= new float (0.0f);
	float*	button_border_right						= new float (0.0f);
	float*	button_border_bottom					= new float (0.0f);
	float*	button_border_up						= new float (0.0f);
	///
	int*	button_subdivision_x					= new int (0.0f);
	int*	button_subdivision_y					= new int (0.0f);


	//slider
	ETextureGabarite*	background_for_slider		= nullptr;
	ETextureGabarite*	slider_head_inactive		= nullptr;
	ETextureGabarite*	slider_head_active			= nullptr;
	float* slider_border_left						= new float(0.0f);
	float* slider_border_right						= new float(0.0f);
	float* slider_border_bottom						= new float(0.0f);
	float* slider_border_up							= new float(0.0f);
	///
	int* slider_subdivision_x						= new int(0.0f);
	int* slider_subdivision_y						= new int(0.0f);

	static EGUIStyle*	active_style;
	static void set_style_borders_and_subdivisions(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y);
	static void set_style_dark_borders_and_subdivisions(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y);
	
	static void set_style_offset_borders(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up);
	static void set_style_dark_offset_borders(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up);
	
	static void set_style_borders_and_subdivision_for_buttons(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y);
	static void set_style_borders_and_subdivision_for_slider_bg(EGUIStyle* _style, float _border_left, float _border_right, float _border_bottom, float _border_up, int _subdivision_x, int _subdivision_y);
	
	static std::vector<EGUIStyle*> style_list;
};