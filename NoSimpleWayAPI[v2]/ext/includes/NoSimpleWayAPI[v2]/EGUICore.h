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



class EButtonGroupRow
{
public:
	ERegionGabarite* gabarite;
	std::vector<EButtonGroup*> button_group_list;

	EButtonGroup* parent_button_group;
};

class EButtonGroup
{
public:
	//float* offset_x = new float(0.0f);
	//float* offset_y = new float(0.0f);

	//float* size_x = new float(0.0f);
	//float* size_y = new float(0.0f);
	ERenderBatcher* batcher_for_default_draw;

	ERegionGabarite* region;

	std::vector<EntityButton*> button_list;
	std::vector<EButtonGroupRow*> group_row_list;
	EButtonGroupRow* parent_group_row;

	int* order_in_vector = new int(0);
	static EButtonGroup* focused_button_group;

	float* scroll_x = new float(0.0f);
	float* scroll_y = new float(0.0f);

	float* highest_point_y = new float(0.0f);

	void update(float _d);
	void draw();
	void set_world_position();
	void realign_all_buttons();

	static void add_horizontal_scroll_bar(EButtonGroup* _button_group);
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