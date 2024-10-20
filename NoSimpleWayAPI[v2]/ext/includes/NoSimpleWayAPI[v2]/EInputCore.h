#pragma once

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
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
	extern bool NSW_have_unsave_changes;

	extern int		scroll_direction;

	extern	bool		MOUSE_BUTTON_LEFT;
	extern	bool		MOUSE_BUTTON_RIGHT;
	extern	bool		MOUSE_BUTTON_MID;

	extern	double		MOUSE_POSITION_X;
	extern	double		MOUSE_POSITION_Y;

	extern	double		MOUSE_PREV_X;
	extern	double		MOUSE_PREV_Y;

	extern	double		MOUSE_SPEED_X;
	extern	double		MOUSE_SPEED_Y;

	extern	char		LAST_INPUTED_CHAR;

	extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	extern void mouse_position_callback(GLFWwindow* window, double _x, double _y);
	extern void char_input_callback(GLFWwindow* window, unsigned int _char);
	extern void key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	extern void initiate_input_core();

	extern void simple_logger_with_parameter(std::string _text, std::string _parameter);
	extern void simple_logger_with_parameter_and_warning(std::string _text, std::string _parameter);

	extern void logger_param(std::string _text, std::string _parameter);
	extern void logger_param_with_warning(std::string _text, std::string _parameter);

	extern void logger_simple_error(std::string _error);
	extern void logger_simple_success(std::string _message);
	extern void logger_simple_try(std::string _message);
	extern void logger_simple_info(std::string _message);

	template<typename T>
	extern std::string border_this_text(T _data, char _border_symbol)
	{
		static_assert(not std::is_same_v<T, std::string>, "T cannot be string");
		//static_assert(not std::is_same_v<T, std::string_view>, "T cannot be string_view");
		//std::cout << "------[" << _text << ": " << std::to_string(_parameter) << "]-------" << std::endl;
		//simple_logger_with_parameter(_z, std::to_string(_parameter));
		char right_side = _border_symbol;

		if (_border_symbol == '[') { right_side = ']'; }
		if (_border_symbol == '(') { right_side = ')'; }
		if (_border_symbol == '{') { right_side = '}'; }
		if (_border_symbol == '<') { right_side = '>'; }

		return (_border_symbol + std::to_string(_data) + right_side);
	}

	template<typename T>
	extern void logger_param(std::string _text, T _parameter)
	{
		static_assert(not std::is_same_v<T, std::string>, "T cannot be string");
		simple_logger_with_parameter(_text, std::to_string(_parameter));
	}
	template<typename T>
	extern void logger_param_with_warning(std::string _text, T _parameter)
	{
		static_assert(not std::is_same_v<T, std::string>, "T cannot be string");
		simple_logger_with_parameter_and_warning(_text, std::to_string(_parameter));
	}

	const unsigned int		key_count = 512;
	extern int				key_state				[key_count];
	extern float			key_hold_time			[key_count];

	const unsigned int		mouse_key_count = 8;
	extern float			mouse_button_state			[mouse_key_count];
	extern float			mouse_hold_time			[mouse_key_count];
	extern float			mouse_unhold_save_time	[mouse_key_count];

	extern bool				key_pressed_once(int _key);
	extern bool				key_pressed(int _key);
	extern bool				key_holded(int _key, float _time);

	extern bool				mouse_button_pressed_once(int _button);
	//extern float key_is_holded[512];

	extern float			ger_real_mouse_x();
	extern float			ger_real_mouse_y();
}
