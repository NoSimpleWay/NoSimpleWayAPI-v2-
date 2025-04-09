#pragma once

/**/
#ifndef _E_INPUT_CORE_ALREADY_LINKED_
#define _E_INPUT_CORE_ALREADY_LINKED_
#include "EInputCore.h"
#endif
/**/


namespace EInputCore
{
	int			scroll_direction;

	bool		NSW_have_unsave_changes = false;

	std::ofstream				logger_writer;
	std::string					logger_buffer = "";
	//std::string					logger_prefix = "";
	unsigned long long			last_timestamp;

	std::string					logger_prefixes[128];
	unsigned long long			prefix_timestamp[128];
	int							active_prefix_id = -1;
	
	bool		MOUSE_BUTTON_LEFT;
	bool		MOUSE_BUTTON_RIGHT;
	bool		MOUSE_BUTTON_MID;

	double		MOUSE_POSITION_X;
	double		MOUSE_POSITION_Y;
	
	double		MOUSE_PREV_X = -1.0;
	double		MOUSE_PREV_Y = -1.0;

	double		MOUSE_SPEED_X;
	double		MOUSE_SPEED_Y;

	int			key_state				[key_count]{ false };
	float		key_hold_time			[key_count];

	float		mouse_button_state			[mouse_key_count]{};
	float		mouse_hold_time			[mouse_key_count]{};
	float		mouse_unhold_save_time	[mouse_key_count]{};

	char		LAST_INPUTED_CHAR = 0;



	bool key_pressed_once(int _key)
	{
		if ((key_state[_key] != GLFW_RELEASE) && (key_hold_time[_key] <= 0.0f)) { return true; }
		return false;
	}

	bool key_pressed(int _key)
	{
		if ((key_state[_key] != GLFW_RELEASE)) { return true; }
		return false;
	}

	bool key_holded(int _key, float _time)
	{
		if ((key_state[_key] != GLFW_RELEASE) && (key_hold_time[_key] > _time)) { return true; }
		return false;
	}



	bool mouse_button_pressed_once(int _button)
	{
		if ((mouse_button_state[_button] != GLFW_RELEASE) && (mouse_hold_time[_button] <= 0.0f)){ return true; }
		return false;
	}

	float ger_real_mouse_x()
	{
		return float(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom);
	}
	float ger_real_mouse_y()
	{
		return float(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom);
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

void EInputCore::simple_logger_with_parameter_and_warning(std::string _text, std::string _parameter)
{
	std::cout << white << "------[" << yellow << _text << ":\t" << blue << _parameter << white << "]-------" << std::endl;
}

void EInputCore::logger_param(std::string _text, std::string _parameter)
{
	simple_logger_with_parameter(_text, _parameter);
}
void EInputCore::logger_param_with_warning(std::string _text, std::string _parameter)
{
	simple_logger_with_parameter_and_warning(_text, _parameter);
}

void EInputCore::logger_simple_error(std::string _error)
{
	std::cout << red << "^^^^^^^ ERROR: " << _error << std::endl;
}

void EInputCore::logger_simple_success(std::string _message)
{
	std::cout << green << "| Success: " << _message << " |" << std::endl;
}

void EInputCore::logger_simple_try(std::string _message)
{
	std::cout << blue << "| Try: " << _message << " |" << std::endl;
}

void EInputCore::logger_simple_info(std::string _message)
{
	std::cout << white << "[info]: " << _message  << std::endl;
}


void EInputCore::add_log_info_with_timestamp(std::string _text)
{
	unsigned long long
	current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	unsigned long long
	passed_time = current_time - last_timestamp;

	if (active_prefix_id >= 0)
	{
		//add tabs
		for (int i = 0; i <= active_prefix_id; i++)
		{
			logger_writer << "\t";
		}

		//add prefixes
		//for (int i = 0; i <= active_prefix_id; i++)
		{
			logger_writer << ("(" + logger_prefixes[active_prefix_id] + ") ");
		}
	}

	logger_writer << _text << "[" << (std::chrono::milliseconds)(passed_time) << "]";
	logger_writer << " ";
	logger_writer << "Delay status: ";

	if (passed_time >= 1000) { logger_writer << "UNACCEPTABLE!"; }
	else
	if (passed_time >= 500)
	{
		logger_writer << "Very high";
	}
	else
	if (passed_time >= 250) { logger_writer << "High"; }
	else
	if (passed_time >= 100) { logger_writer << "Medium"; }
	else
	if (passed_time >= 50) { logger_writer << "Low"; }
	else
	if (passed_time >= 10) { logger_writer << "Very low"; }
	else
	{ logger_writer << "Minimal"; }




	logger_writer << std::endl;
	last_timestamp = current_time;
}

void EInputCore::add_logger_prefix(std::string _text)
{
	active_prefix_id++;

	active_prefix_id = std::clamp(active_prefix_id, -1, 127);

	unsigned long long
	current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	prefix_timestamp[active_prefix_id]	= current_time;
	logger_prefixes[active_prefix_id]	= _text;
	
	//logger_prefix = _text;
}

void EInputCore::reset_timestamp()
{
	last_timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void EInputCore::remove_last_logger_prefix()
{

	if (active_prefix_id >= 0)
	{
		unsigned long long
			current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		unsigned long long
			passed_time = current_time - prefix_timestamp[active_prefix_id];

		logger_writer << "TOTAL TIME OF (" << logger_prefixes[active_prefix_id] << ") is [" << (std::chrono::milliseconds)(passed_time) << "]" << std::endl;
	

		active_prefix_id--;
		active_prefix_id = std::clamp(active_prefix_id, -1, 127);
	}
	//logger_prefix = "";
}

void EInputCore::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll: " << std::to_string(yoffset) << std::endl;
	scroll_direction = yoffset;
}

void EInputCore::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	mouse_button_state[button] = action;

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
	unsigned int inputed_c = _char;

	if (inputed_c == 1025) { inputed_c = 168; }
	else
		if (inputed_c == 1105) { inputed_c = 184; }
		else
			if (inputed_c > 255) { inputed_c -= 848; }

	//std::cout << "input character: " << inputed_c << "|" << (int)_char << "[  " << (char)inputed_c << " ]" << " (" << _char << ")" << std::endl;
	//EInputCore::logger_simple_info(std::to_string((int)'É'));
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