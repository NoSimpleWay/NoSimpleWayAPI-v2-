#pragma once

#ifndef _E_INPUT_CORE_LINKER_
#define _E_INPUT_CORE_LINKER_
#include "EInputCore.h"
#endif

namespace EInputCore
{
	int		scroll_direction;

	bool		MOUSE_BUTTON_LEFT;
	bool		MOUSE_BUTTON_RIGHT;
	bool		MOUSE_BUTTON_MID;

	double	MOUSE_POSITION_X;
	double	MOUSE_POSITION_Y;

	char		LAST_INPUTED_CHAR = NULL;
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
	EInputCore::MOUSE_POSITION_X = _x;
	EInputCore::MOUSE_POSITION_Y = NS_EGraphicCore::SCREEN_HEIGHT - _y;
}

void EInputCore::char_input_callback(GLFWwindow* window, unsigned int _char)
{
	int inputed_c = (int)_char;

	if (inputed_c == 1025) { inputed_c = 168; }
	else
		if (inputed_c == 1105) { inputed_c = 184; }
		else
			if (inputed_c > 255) { inputed_c -= 848; }

	//cout << "input character: " << inputed_c << "|" << (int)_char << "[  " << (char)inputed_c << " ]" << " (" << _char << ")" << endl;

	EInputCore::LAST_INPUTED_CHAR = (char)inputed_c;

	//EWindow::last_inputed_char = _char;
}