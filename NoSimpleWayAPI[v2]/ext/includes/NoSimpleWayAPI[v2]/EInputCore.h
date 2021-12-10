#pragma once

#ifndef _EGRAPHICCORE_
/**/#define _EGRAPHICCORE_
/**/#include "EGraphicCore.h"
#endif

namespace EInputCore
{
	static	 int		scroll_direction;

	static	 bool	MOUSE_BUTTON_LEFT;
	static	 bool	MOUSE_BUTTON_RIGHT;
	static	 bool	MOUSE_BUTTON_MID;

	static	 bool	MOUSE_POSITION_X;
	static	 bool	MOUSE_POSITION_Y;

	static	 char	LAST_INPUTED_CHAR = NULL;

	

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_position_callback(GLFWwindow* window, double _x, double _y);
	void char_input_callback(GLFWwindow* window, unsigned int _char);

	void initiate_input_core();

	
}