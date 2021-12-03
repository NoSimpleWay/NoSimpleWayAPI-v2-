#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "NoSimpleWayAPI[v2]/EGraphicCore.h"
#include "NoSimpleWayAPI[v2]/EInputCore.h"


extern GLFWwindow* main_window{ nullptr };

void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void recalculate_correction();
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_position_callback(GLFWwindow* window, double _x, double _y);
void char_input_callback(GLFWwindow* window, unsigned int _char);
//void load_texture(char const* _path, int _id);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 2);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

// glfw window creation
// --------------------


	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, NULL);

	main_window = glfwCreateWindow(EGraphicCore::SCREEN_WIDTH, EGraphicCore::SCREEN_HEIGHT, "Window name", NULL, NULL);

	if (main_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(main_window);

	glfwSetFramebufferSizeCallback(main_window, framebuffer_size_callback);
	glfwSetScrollCallback(main_window, scroll_callback);
	glfwSetMouseButtonCallback(main_window, mouse_button_callback);
	glfwSetCursorPosCallback(main_window, mouse_position_callback);
	glfwSetCharCallback(main_window, char_input_callback);

	glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glfwSetMousePos(0, 0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);

	//logger_param("max_texture_size:", max_tex_size);

	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(main_window))
	{
		glfwPollEvents();

		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(main_window);
		processInput(main_window);

		EInputCore::LAST_INPUTED_CHAR	=	NULL;
		EInputCore::scroll_direction	=	0;
	}

	return 0;

}

void processInput(GLFWwindow* window)
{
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//
	//width = round(width / 2.0f) * 2;
	//height = round(height / 2.0f) * 2;
	//glScissor(0, 0, 500, 500);
	glfwSetWindowSize(main_window, width, height);
	 
	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &EGraphicCore::SCREEN_WIDTH, &EGraphicCore::SCREEN_WIDTH);

	std::cout << "Resize event width:" << EGraphicCore::SCREEN_WIDTH << " height: " << EGraphicCore::SCREEN_WIDTH << std::endl;

	recalculate_correction();
}

void recalculate_correction()
{
	if ((EGraphicCore::SCREEN_WIDTH > 100) && (EGraphicCore::SCREEN_HEIGHT > 100))
	{
		EGraphicCore::correction_x = 1.0f / EGraphicCore::SCREEN_WIDTH * 2.0f;
		EGraphicCore::correction_y = 1.0f / EGraphicCore::SCREEN_HEIGHT * 2.0f;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << "scroll: " << std::to_string(yoffset) << std::endl;
	EInputCore::scroll_direction = (int)yoffset;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
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

void mouse_position_callback(GLFWwindow* window, double _x, double _y)
{
	EInputCore::MOUSE_POSITION_X = _x;
	EInputCore::MOUSE_POSITION_Y = EGraphicCore::SCREEN_HEIGHT - _y;
}

void char_input_callback(GLFWwindow* window, unsigned int _char)
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