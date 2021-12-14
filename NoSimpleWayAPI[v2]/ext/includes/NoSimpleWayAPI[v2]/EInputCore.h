#pragma once

#ifndef _EGRAPHICCORE_
/**/#define _EGRAPHICCORE_
/**/#include "EGraphicCore.h"
#endif

#include <string>
#include "ConsoleColor.h"

namespace std
{
	std::string to_string(std::string _string);
}

namespace EInputCore
{
	extern	 int		scroll_direction;
	
	extern	 bool	MOUSE_BUTTON_LEFT;
	extern	 bool	MOUSE_BUTTON_RIGHT;
	extern	 bool	MOUSE_BUTTON_MID;
	
	extern	 bool	MOUSE_POSITION_X;
	extern	 bool	MOUSE_POSITION_Y;
	
	extern	 char	LAST_INPUTED_CHAR;

	

	extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	extern void mouse_position_callback(GLFWwindow* window, double _x, double _y);
	extern void char_input_callback(GLFWwindow* window, unsigned int _char); 
	extern void initiate_input_core();

	extern void simple_logger_with_parameter(std::string _text, std::string _parameter);

	extern void logger_param(std::string _text, std::string_view _parameter);
	extern void logger_param(std::string _text, std::string _parameter);

	extern void logger_simple_error(std::string _error);
	extern void logger_simple_success(std::string _message);

	template<typename T>
	extern void logger_param(std::string _text, T _parameter)
	{
		static_assert(not std::is_same_v<T, std::string>, "T cannot be string");
		static_assert(not std::is_same_v<T, std::string_view>, "T cannot be string_view");
		//std::cout << "------[" << _text << ": " << std::to_string(_parameter) << "]-------" << std::endl;
		simple_logger_with_parameter(_text, std::to_string(_parameter));
	}


	

}

