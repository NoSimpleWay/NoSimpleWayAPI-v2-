#pragma once

#ifndef _EGRAPHICCORE_
/**/#define _EGRAPHICCORE_
/**/#include "EGraphicCore.h"
#endif

namespace EInputCore
{
	extern	 int		scroll_direction;
	
	extern	 bool	MOUSE_BUTTON_LEFT;
	extern	 bool	MOUSE_BUTTON_RIGHT;
	extern	 bool	MOUSE_BUTTON_MID;
	
	extern	 bool	MOUSE_POSITION_X;
	extern	 bool	MOUSE_POSITION_Y;
	
	extern	 char	LAST_INPUTED_CHAR;

	

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_position_callback(GLFWwindow* window, double _x, double _y);
	void char_input_callback(GLFWwindow* window, unsigned int _char);

	void initiate_input_core();

	
}