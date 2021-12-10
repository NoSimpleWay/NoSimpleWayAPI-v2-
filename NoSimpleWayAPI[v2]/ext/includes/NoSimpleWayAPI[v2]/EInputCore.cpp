#pragma once
#include "EInputCore.h"


void EInputCore::initiate_input_core()
{
	if (EGraphicCore::main_window != nullptr)
	{
		glfwSetScrollCallback(EGraphicCore::main_window, EInputCore::scroll_callback);
		glfwSetMouseButtonCallback(EGraphicCore::main_window, EInputCore::mouse_button_callback);
		glfwSetCursorPosCallback(EGraphicCore::main_window, EInputCore::mouse_position_callback);
		glfwSetCharCallback(EGraphicCore::main_window, EInputCore::char_input_callback);
	}
	else
	{
		std::cout << "Window is NULL" << std::endl;
	}
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
	EInputCore::MOUSE_POSITION_Y = EGraphicCore::SCREEN_HEIGHT - _y;
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

