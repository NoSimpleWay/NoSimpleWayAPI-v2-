#pragma once
#include <array>

#include <iostream>
#include <string_view>

#include <glad/glad.h>

#ifndef _GLFW_CORE_
/**/#define _GLFW_CORE_
/**/#include <GLFW/glfw3.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_s.h>

#include <vector>

#include <stb_image.h>

class ETextureAtlas;
class Batcher;
class ETextureGabarite;

namespace EGraphicCore
{
	extern int			SCREEN_WIDTH, SCREEN_HEIGHT;
	extern float			correction_x, correction_y;
	extern Shader*			texture_atlas_putter_shader;

	extern glm::mat4		matrix_transform;
	extern Batcher*		default_batcher_for_texture_atlas;

	extern GLFWwindow*		main_window;

	extern unsigned int		texture[32];
	extern ETextureAtlas*	default_texture_atlas;
	extern unsigned char*	image_data;
	extern int			texture_loader_width, texture_loader_height, nrChannels, last_texture_width, last_texture_height;

	extern void processInput(GLFWwindow* window);

	extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	extern void recalculate_correction();

	extern void switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas);
	extern void make_transform_from_size(glm::mat4 _transform, float _size_x, float _size_y);
	//void load_texture(char const* _path, int _id);

	extern void initiate_graphic_core();
	extern std::vector<ETextureGabarite*> texture_gabarites_list;
	extern void load_texture(char const* _path, int _id);
	extern ETextureGabarite* put_texture_to_atlas(std::string _name, ETextureAtlas* _atlas);
	extern void fill_vertex_buffer_default(float _array[], int _start_offset, Batcher* _batch, float _x, float _y, float _w, float _h);
	
};

typedef float EColor_4;

#ifndef _COLOR_COLLECTION_
#define _COLOR_COLLECTION_
namespace EColorCollection
{

	const EColor_4 COLOR_WHITE[4]	{ 1.0f,	1.0f,	1.0f,	1.0f };
	const EColor_4 COLOR_BLACK[4]	{ 0.0f,	0.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_GRAY[4]	{ 0.5f,	0.5f,	0.5f,	1.0f };

	const EColor_4 COLOR_RED[4]	{ 1.0f,	0.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_GREEN[4]	{ 0.0f,	1.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_BLUE[4]	{ 0.0f,	0.0f,	1.0f,	1.0f };
}
#endif

namespace zalupa
{
	extern int zalupa1;
	extern int zalupa2;
	extern int zalupa3;
}




//VERTEX BUFFER ARRAY
constexpr unsigned int VERTICES_PER_SHAPE					= 4;
constexpr unsigned int MAX_SHAPES_COUNT						= 1000;
constexpr unsigned int EXPECTABLE_PARAMETERS_COUNT_FOR_VERTEX	= 10;

constexpr unsigned int TOTAL_MAX_VERTICES_COUNT				= VERTICES_PER_SHAPE * MAX_SHAPES_COUNT * EXPECTABLE_PARAMETERS_COUNT_FOR_VERTEX;

//INDICES ARRAY
constexpr unsigned int INDICES_PER_SHAPE					= (int)(VERTICES_PER_SHAPE * 1.5f);
constexpr unsigned int TOTAL_INDICES_COUNT					= INDICES_PER_SHAPE * MAX_SHAPES_COUNT;


typedef										std::array<unsigned short, TOTAL_INDICES_COUNT> array_type;







class Batcher
{
private:
	
	unsigned int									last_vertice_buffer_index;				//last element of vertex buffer
	unsigned int									VBO, VAO, EBO = 0;
	unsigned short									parameters_count = 1;

	float										vertex_buffer[TOTAL_MAX_VERTICES_COUNT];


	//BATCHER VERTEX DATA SEGMENT
	unsigned int									vertices_data_per_vertex;			//count of parameters for one vertices
	//const std::array<int, 255>						indices_buffer[TOTAL_INDICES_COUNT] = generateData();	//indices array

	
	const array_type								indices_buffer = generateData();

	array_type generateData() {
		array_type a;
		size_t indices_id		= 0;
		size_t indices_order	= 0;

		for (int i = 0; i < MAX_SHAPES_COUNT; i++) {
			a[indices_id + 0] = indices_order + 0;
			a[indices_id + 1] = indices_order + 1;
			a[indices_id + 2] = indices_order + 3;

			a[indices_id + 3] = indices_order + 1;
			a[indices_id + 4] = indices_order + 2;
			a[indices_id + 5] = indices_order + 3;

			//std::

			indices_id += 6;
			indices_order += 4;

			//std::cout << "Generated indices. Id->[" << std::to_string(i) << "]" << " indices count->["<< std::to_string(indices_id) << "]" << std::endl;
		}
		return a;
	}

	
	/*float color_red = 0.0f;
	float color_green	= 0.0f;
	float color_blue	= 0.0f;
	float color_alpha	= 0.0f;*/

public:
	EColor_4 batch_color[4];

	Batcher();
	~Batcher();

	void draw_call();

	
	void set_color(const float(&_color)[4]);
	void reset();
	unsigned int get_last_id();
	void set_last_id(unsigned int _id);

};

class ETextureAtlas
{
private:
	int* atlas_size_x	= new int (0);
	int* atlas_size_y	= new int (0);

	unsigned short* framebuffer	= new unsigned short(0);
	unsigned short* colorbuffer	= new unsigned short(0);
	unsigned short* rbo			= new unsigned short(0);;

	

	

public:
	unsigned short get_atlas_size_x();
	unsigned short get_atlas_size_y();
	unsigned short get_framebuffer();

	ETextureAtlas	(float _size_x, float _size_y);
	~ETextureAtlas	();

	bool** free_space;
	bool can_place_here(int _x, int _y, int _w, int _h);

};

class ETextureGabarite
{
private:
	std::string_view* full_path = new std::string_view("");

	int* pos_x_in_pixels = new int(0);
	int* pos_y_in_pixels = new int(0);

	int* size_x_in_pixels = new int(0);
	int* size_y_in_pixels = new int(0);

	float* uv_start_x	= new float(0.0f);
	float* uv_start_y	= new float(0.0f);
	float* uv_end_x	= new float(0.0f);
	float* uv_end_y	= new float(0.0f);

public:
	std::string_view get_full_path();
};

