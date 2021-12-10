#ifndef _EGRAPHICCORE_
/**/#define _EGRAPHICCORE_
/**/#include "EGraphicCore.h"
#endif

namespace EGraphicCore
{
	int				SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
	float			correction_x = 1.0f, correction_y = 1.0f;
	Shader*			texture_atlas_putter_shader;

	glm::mat4			matrix_transform;
	Batcher*			default_batcher_for_texture_atlas;

	GLFWwindow*		main_window;

	unsigned int		texture[32];
	ETextureAtlas*		default_texture_atlas;
	unsigned char*		image_data;
	int				texture_loader_width, texture_loader_height, nrChannels, last_texture_width, last_texture_height;


	void processInput(GLFWwindow* window);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void recalculate_correction();

	void switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas);
	void make_transform_from_size(glm::mat4 _transform, float _size_x, float _size_y);

	void initiate_graphic_core();
};


Batcher::Batcher()
{
	//zzz(indices_buffer);
	//indices_buffer = generateData();
}

Batcher::~Batcher()
{
}

namespace zalupa
{
	int zalupa1;
	int zalupa2;
	int zalupa3;
}


void Batcher::draw_call()
{
	if (last_vertice_buffer_index > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * last_vertice_buffer_index, vertex_buffer, GL_DYNAMIC_DRAW);



		glDrawElements(GL_TRIANGLES, 6 * (int)(last_vertice_buffer_index / parameters_count), GL_UNSIGNED_SHORT, 0);
	}
}

void Batcher::set_color(const float(&_color)[4])
{
	std::copy(std::begin(_color), std::end(_color), std::begin(batch_color));
}

void Batcher::reset()
{
	set_last_id(0);
	//indices_id = 0;
	//indices_order = 0;
}

unsigned int Batcher::get_last_id()
{
	return last_vertice_buffer_index;
}

void Batcher::set_last_id(unsigned int _id)
{
	last_vertice_buffer_index = _id;
}

/*
unsigned int Batcher::set_last_id()
{
	
	return 0;
}
*/

bool ETextureAtlas::can_place_here(int _x, int _y, int _w, int _h)
{
	for (int i = _y; i <= _y + _h; i++)
	for (int j = _x; j <= _x + _w; j++)
	{
		if ((j >= *atlas_size_x) || (i >= *atlas_size_x))
		{
			return false;
		}

		if (!free_space[j][i]) { return false; }
	}

	return true;
}

unsigned short ETextureAtlas::get_atlas_size_x()
{
	return *atlas_size_x;
}

unsigned short ETextureAtlas::get_atlas_size_y()
{
	return *atlas_size_y;
}

unsigned short ETextureAtlas::get_framebuffer()
{
	return *framebuffer;
}

ETextureAtlas::ETextureAtlas(float _size_x, float _size_y)
{
	free_space = new bool* [_size_x];

	for (unsigned short i = 0; i++; i++)
	{
		free_space[i] = new bool[_size_y];

		for (int j = 0; j < _size_y; ++j)
		{
			free_space[i][j] = true;
		}
	}
}

ETextureAtlas::~ETextureAtlas()
{
}

void EGraphicCore::switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas)
{
	glViewport(0, 0, _atlas->get_atlas_size_x(), _atlas->get_atlas_size_y());
	glBindFramebuffer(GL_FRAMEBUFFER, _atlas->get_framebuffer());

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	make_transform_from_size(EGraphicCore::matrix_transform, _atlas->get_atlas_size_x() * 2.0f, _atlas->get_atlas_size_y() * 2.0f);
	EGraphicCore::texture_atlas_putter_shader->use();	



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EGraphicCore::texture[0]);
	EGraphicCore::texture_atlas_putter_shader->setInt("texture1", 0);
	default_batcher_for_texture_atlas->set_color(EColorCollection::COLOR_WHITE);
}

void EGraphicCore::make_transform_from_size(glm::mat4 _transform, float _size_x, float _size_y)
{
	_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1, -1, 0.0f));
	_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(1.0f / _size_x, 1.0f / _size_y, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(EGraphicCore::texture_atlas_putter_shader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
}

//void EGraphicCore::make_transform_from_size(glm::mat4 _transform)
//{
//}


void EGraphicCore::initiate_graphic_core()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 2);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, NULL);

	EGraphicCore::main_window = glfwCreateWindow(EGraphicCore::SCREEN_WIDTH, EGraphicCore::SCREEN_HEIGHT, "Window name", NULL, NULL);
	std::cout << "[0]window is:" << (EGraphicCore::main_window) << std::endl;

	if (EGraphicCore::main_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	else
	{
		std::cout << "Hi, idiot, window is NOT null!" << std::endl;
	}

	glfwMakeContextCurrent(EGraphicCore::main_window);

	glfwSetFramebufferSizeCallback(EGraphicCore::main_window, framebuffer_size_callback);
	

	glfwSetInputMode(EGraphicCore::main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glfwSetMousePos(0, 0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	EGraphicCore::default_batcher_for_texture_atlas = new Batcher();
}

void EGraphicCore::load_texture(char const* _path, int _id)
{
	glGenTextures(_id, &texture[_id]);
	glBindTexture(GL_TEXTURE_2D, texture[_id]);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	//ifstream (_path)

	image_data = stbi_load(_path, &texture_loader_width, &texture_loader_height, &nrChannels, STBI_rgb_alpha);
	if (image_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_loader_width, texture_loader_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//cout << "loaded texture W:" << width << " H:" << height << endl;

		last_texture_height = texture_loader_height;
		last_texture_width = texture_loader_width;

		//texture_error = false;
		/*texture_w[_id] = width;
		texture_h[_id] = height;*/
	}
	else
	{
		image_data = stbi_load("data/textures/ERROR.png", &texture_loader_width, &texture_loader_height, &nrChannels, STBI_rgb_alpha);
		if (image_data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_loader_width, texture_loader_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			last_texture_height = texture_loader_height;
			last_texture_width = texture_loader_width;
		}
		//cout << red << "Failed to load texture " << yellow << "(" << _path << ")" << green << endl;
		std::cout << "Failed to load texture " << "(" << _path << ")" << std::endl;
		//last_texture_h = 21;
		//last_texture_w = 21;

		//texture_error = true;

		//just_created_gabarite = DefaultGabarite::gabarite_error;
	}

	stbi_image_free(image_data);
}

ETextureGabarite* EGraphicCore::put_texture_to_atlas(std::string _name, ETextureAtlas* _atlas)
{
	for (int i = 0; i < _name.length(); i++)
	{
		if (_name[i] == '\\') { _name[i] = '/'; }
	}

	ETextureGabarite* duplicate_gabarite = NULL;

	//search already loaded texture gabarite
	for (ETextureGabarite* g : EGraphicCore::texture_gabarites_list)
	{
		if (g->get_full_path() == _name)
		{
			duplicate_gabarite = g;
		}
	}

	ETextureGabarite* new_gabarite = nullptr;

	if (duplicate_gabarite == nullptr)
	{
		EGraphicCore::switch_to_texture_atlas_draw_mode(_atlas);

		EGraphicCore::load_texture(_name.c_str(), 0);

		int place_x = 0;
		int place_y = 0;
		for (int x = 0; x < 1024; x++)
			for (int y = 0; y < 1024; y++)
			{
				if (_atlas->can_place_here(x, y, ceil(EGraphicCore::last_texture_width / 4.0f), ceil(EGraphicCore::last_texture_height / 4.0f)))
				{
					place_x = x * 4;
					place_y = y * 4;

					x = 99999;
					y = 99999;
				}
			}

		for (int x = (ceil)(place_x / 4.0f) - 2; x < (ceil)((place_x + EGraphicCore::last_texture_width) / 4.0f) + 2; x++)
			for (int y = (ceil)(place_y / 4.0f) - 2; y < (ceil)((place_y + EGraphicCore::last_texture_height) / 4.0f) + 2; y++)
				if ((x < 1024) & (y < 1024) & (x >= 0) & (y >= 0))
				{
					_atlas->free_space[x][y] = false;
				}
	}

	EGraphicCore::default_batcher_for_texture_atlas->reset();
	EGraphicCore::default_batcher_for_texture_atlas->set_color(EColorCollection::COLOR_WHITE);

	glBlendEquation(GL_MAX);
	return new_gabarite;
}

void EGraphicCore::fill_vertex_buffer_default(float _array[], int _start_offset, Batcher* _batch, float _x, float _y, float _w, float _h)
{
	_array[_start_offset + 0] = (_x + _w);
	_array[_start_offset + 1] = (_y + _h);

	_array[_start_offset + 2] = _batch->batch_color[0];
	_array[_start_offset + 3] = _batch->batch_color[1];
	_array[_start_offset + 4] = _batch->batch_color[2];
	_array[_start_offset + 5] = _batch->batch_color[3];

	_array[_start_offset + 6] = 1.0f;
	_array[_start_offset + 7] = 1.0f;

	//..
	//.#
	_array[_start_offset + 8] = (_x + _w);
	_array[_start_offset + 9] = _y;

	_array[_start_offset + 10] = _batch->batch_color[0];
	_array[_start_offset + 11] = _batch->batch_color[1];
	_array[_start_offset + 12] = _batch->batch_color[2];
	_array[_start_offset + 13] = _batch->batch_color[3];

	_array[_start_offset + 14] = 1.0f;
	_array[_start_offset + 15] = 0.0f;

	//..
	//#.
	_array[_start_offset + 16] = _x;
	_array[_start_offset + 17] = _y;

	_array[_start_offset + 18] = _batch->batch_color[0];
	_array[_start_offset + 19] = _batch->batch_color[1];
	_array[_start_offset + 20] = _batch->batch_color[2];
	_array[_start_offset + 21] = _batch->batch_color[3];

	_array[_start_offset + 22] = 0.0f;
	_array[_start_offset + 23] = 0.0f;

	//#.
	//..
	_array[_start_offset + 24] = _x;
	_array[_start_offset + 25] = (_y + _h);

	_array[_start_offset + 26] = _batch->batch_color[0];
	_array[_start_offset + 27] = _batch->batch_color[1];
	_array[_start_offset + 28] = _batch->batch_color[2];
	_array[_start_offset + 29] = _batch->batch_color[3];

	_array[_start_offset + 30] = 0.0f;
	_array[_start_offset + 31] = 1.0f;

	_start_offset += 32;
}


void EGraphicCore::processInput(GLFWwindow* window)
{
}

void EGraphicCore::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//
	//width = round(width / 2.0f) * 2;
	//height = round(height / 2.0f) * 2;
	//glScissor(0, 0, 500, 500);
	glfwSetWindowSize(EGraphicCore::main_window, width, height);

	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &EGraphicCore::SCREEN_WIDTH, &EGraphicCore::SCREEN_WIDTH);

	std::cout << "Resize event width:" << EGraphicCore::SCREEN_WIDTH << " height: " << EGraphicCore::SCREEN_WIDTH << std::endl;

	recalculate_correction();
}

void EGraphicCore::recalculate_correction()
{
	if ((EGraphicCore::SCREEN_WIDTH > 100) && (EGraphicCore::SCREEN_HEIGHT > 100))
	{
		EGraphicCore::correction_x = 1.0f / EGraphicCore::SCREEN_WIDTH * 2.0f;
		EGraphicCore::correction_y = 1.0f / EGraphicCore::SCREEN_HEIGHT * 2.0f;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}
}

std::string_view ETextureGabarite::get_full_path()
{

	return *full_path;
}
