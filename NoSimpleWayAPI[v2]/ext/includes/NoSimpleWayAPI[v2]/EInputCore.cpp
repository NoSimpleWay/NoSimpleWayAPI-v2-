#pragma once

/**/
#ifndef _E_INPUT_CORE_ALREADY_LINKED_
#define _E_INPUT_CORE_ALREADY_LINKED_
#include "EInputCore.h"
#endif
/**/
namespace EInputCore
{
	int		scroll_direction;

	bool		MOUSE_BUTTON_LEFT;
	bool		MOUSE_BUTTON_RIGHT;
	bool		MOUSE_BUTTON_MID;

	double	MOUSE_POSITION_X;
	double	MOUSE_POSITION_Y;
	
	double	MOUSE_PREV_X = -1.0;
	double	MOUSE_PREV_Y = -1.0;

	double	MOUSE_SPEED_X;
	double	MOUSE_SPEED_Y;

	char		LAST_INPUTED_CHAR = 0;

	int		key_state[512]{ false };
	float	key_hold_time[512];

	bool key_pressed_once(int _key)
	{
		if ((key_state[_key] != GLFW_RELEASE) & (key_hold_time[_key] <= 0.0f)) { return true; }
		return false;
	}

	bool key_pressed(int _key)
	{
		if ((key_state[_key] != GLFW_RELEASE)) { return true; }
		return false;
	}

	bool key_holded(int _key, float _time)
	{
		if ((key_state[_key] != GLFW_RELEASE) & (key_hold_time[_key] > _time)) { return true; }
		return false;
	}
};

std::string std::to_string(std::string _string)
{
	return _string;
}

void EInputCore::initiate_input_core()
{
	if (NS_EGraphicCore::main_window != nullptr)
	{
		glfwSetScrollCallback(NS_EGraphicCore::main_window, EInputCore::scroll_callback);
		glfwSetMouseButtonCallback(NS_EGraphicCore::main_window, EInputCore::mouse_button_callback);
		glfwSetCursorPosCallback(NS_EGraphicCore::main_window, EInputCore::mouse_position_callback);
		glfwSetCharCallback(NS_EGraphicCore::main_window, EInputCore::char_input_callback);
		glfwSetKeyCallback(NS_EGraphicCore::main_window, EInputCore::key_input_callback);
	}
	else
	{
		std::cout << "Window is NULL" << std::endl;
	}
}

extern void EInputCore::simple_logger_with_parameter(std::string _text, std::string _parameter)
{
	std::cout << white << "------[" << green << _text << ":\t" << blue << _parameter << white << "]-------" << std::endl;
}

void EInputCore::logger_param(std::string _text, std::string_view _parameter)
{
	simple_logger_with_parameter(_text, { _parameter.data(), _parameter.size() });
}

void EInputCore::logger_param(std::string _text, std::string _parameter)
{
	simple_logger_with_parameter(_text, _parameter);
}

void EInputCore::logger_simple_error(std::string _error)
{
	std::cout << red << "^^^^^^^ ERROR: " << _error << std::endl;
}

void EInputCore::logger_simple_success(std::string _message)
{
	std::cout << green << "| Success: " << _message << " |" << std::endl;
}


void EInputCore::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll: " << std::to_string(yoffset) << std::endl;
	scroll_direction = yoffset;
}

void EInputCore::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//if () 00:13:53 27.11.2019
	if ((button == GLFW_MOUSE_BUTTON_LEFT) && (action == GLFW_PRESS))
	{
		EInputCore::MOUSE_BUTTON_LEFT = true;
	}

	if ((button == GLFW_MOUSE_BUTTON_LEFT) && (action == GLFW_RELEASE))
	{
		EInputCore::MOUSE_BUTTON_LEFT = false;
	}

	if ((button == GLFW_MOUSE_BUTTON_RIGHT) && (action == GLFW_PRESS))
	{
		EInputCore::MOUSE_BUTTON_RIGHT = true;
	}

	if ((button == GLFW_MOUSE_BUTTON_RIGHT) && (action == GLFW_RELEASE))
	{
		EInputCore::MOUSE_BUTTON_RIGHT = false;
	}

	if ((button == GLFW_MOUSE_BUTTON_MIDDLE) && (action == GLFW_PRESS))
	{
		EInputCore::MOUSE_BUTTON_MID = true;
	}

	if ((button == GLFW_MOUSE_BUTTON_MIDDLE) && (action == GLFW_RELEASE))
	{
		EInputCore::MOUSE_BUTTON_MID = false;
	}
}

void EInputCore::mouse_position_callback(GLFWwindow* window, double _x, double _y)
{
	if ((EInputCore::MOUSE_PREV_X >= 0) & (EInputCore::MOUSE_PREV_Y >= 0))
	{
		EInputCore::MOUSE_SPEED_X = _x - EInputCore::MOUSE_PREV_X;
		EInputCore::MOUSE_SPEED_Y = (NS_EGraphicCore::SCREEN_HEIGHT - _y) - EInputCore::MOUSE_PREV_Y;
	}

	EInputCore::MOUSE_POSITION_X = _x;
	EInputCore::MOUSE_POSITION_Y = NS_EGraphicCore::SCREEN_HEIGHT - _y;

	EInputCore::MOUSE_PREV_X = EInputCore::MOUSE_POSITION_X;
	EInputCore::MOUSE_PREV_Y = EInputCore::MOUSE_POSITION_Y;


	//EInputCore::logger_param("x", EInputCore::MOUSE_SPEED_X);
	//EInputCore::logger_param("y", EInputCore::MOUSE_SPEED_Y);
	//EInputCore::logger_param("x", EInputCore::MOUSE_POSITION_X);
	//EInputCore::logger_param("y", EInputCore::MOUSE_POSITION_Y);
}

void EInputCore::char_input_callback(GLFWwindow* window, unsigned int _char)
{
	int inputed_c = (int)_char;

	if (inputed_c == 1025) { inputed_c = 168; }
	else
		if (inputed_c == 1105) { inputed_c = 184; }
		else
			if (inputed_c > 255) { inputed_c -= 848; }

	//std::cout << "input character: " << inputed_c << "|" << (int)_char << "[  " << (char)inputed_c << " ]" << " (" << _char << ")" << std::endl;

	EInputCore::LAST_INPUTED_CHAR = (char)inputed_c;

	//EWindow::last_inputed_char = _char;
}

void EInputCore::key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	key_state[key] = action;

	//if (key_state)
	
	//if ((action == GLFW_PRESS) & (key == GLFW_KEY_W)) { logger_simple_success("WwWwW"); }
	/*logger_simple_success("---");
	logger_param("key", key);
	logger_param("scancode", scancode);
	logger_param("action", action);
	logger_param("mods", mods);*/
}