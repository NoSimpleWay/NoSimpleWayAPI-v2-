#pragma once

#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif

#include <vector>

enum ENUM_ButtonAutoAlign
{
	BUTTON_AUTO_ALIGN__PUSH,								//push button to axis
	BUTTON_AUTO_ALIGN__RESET_CURRENT_AXIS_AND_PUSH_ANOTHER,	//transfer button to new column/row, and reset current axis
	BUTTON_AUTO_ALIGN__PUSH_WITH_EXTRA_SPACE,				//push and add more space between previvous button
	BUTTON_AUTO_ALIGN__FREE								//set exactly position
};

class EButtonContainer;

class EWindow
{
public:
	float* position_x = new float(0.0f);
	float* position_y = new float(0.0f);

	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);

	std::vector<EButtonContainer*> button_container_list;
	

	void			update_default(float _d);
	virtual void	update_additional(float _d);

	void			GUI_update_default(float _d);
	virtual void	GUI_update_additional(float _d);

	void			draw_default(float _d);
	virtual void	draw_additional(float _d);

	void			GUI_draw_default(float _d);
	virtual void	GUI_draw_additional(float _d);



	//////////////		_STATIC SECTION_		////////////////////////

	static std::vector<EWindow*> window_list;

	/////////////////////////////////////////////////////////////////////
};

class EButtonGroup
{
	//std::vector
};

class EButtonContainer
{

};