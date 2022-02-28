#pragma once
//#define STB_IMAGE_IMPLEMENTATION

//#define STB_IMAGE_IMPLEMENTATION
/**/#include <stb_image.h>

#include <array>

#include <iostream>
#include <string>

#include <glad/glad.h>

#ifndef _GLFW_CORE_
/**/#define _GLFW_CORE_
/**/#include <GLFW/glfw3.h>
#endif

/////// /////// /////// /////// /////// /////// ///////
#ifndef _GLM_LINKER_
/**/#define _GLM_LINKER_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif
/////// /////// /////// /////// /////// /////// ///////

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

/////// /////// /////// /////// /////// /////// ///////
#ifndef _E_INPUT_CORE_ALREADY_LINKED_
#define _E_INPUT_CORE_ALREADY_LINKED_
#include "EInputCore.h"
#endif
/////// /////// /////// /////// /////// /////// ///////



/////// /////// /////// /////// /////// /////// ///////
#ifndef _E_TEXT_CORE_ALREADY_LINKED_
/**/#define _E_TEXT_CORE_ALREADY_LINKED_
/**/#include "ETextCore.h"
#endif
/////// /////// /////// /////// /////// /////// ///////

#include <learnopengl/shader_s.h>

#include <vector>

//VERTEX BUFFER ARRAY
constexpr unsigned int VERTICES_PER_SHAPE = 4;
constexpr unsigned int MAX_SHAPES_COUNT = 1000;
constexpr unsigned int EXPECTABLE_PARAMETERS_COUNT_FOR_VERTEX = 10;

constexpr unsigned int TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE = VERTICES_PER_SHAPE * MAX_SHAPES_COUNT * EXPECTABLE_PARAMETERS_COUNT_FOR_VERTEX;

//INDICES ARRAY
constexpr unsigned int INDICES_PER_SHAPE = (int)(VERTICES_PER_SHAPE * 1.5f);
constexpr unsigned int TOTAL_INDICES_COUNT = INDICES_PER_SHAPE * MAX_SHAPES_COUNT;

class ETextureAtlas;
class ERenderBatcher;
class ETextureGabarite;

class ESprite;
class ESpriteLayer;

class ERegionGabarite;

typedef float EColor_4;


namespace NS_ERenderCollection
{
	extern void add_data_to_vertex_buffer_default(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h);
	extern void add_data_to_vertex_buffer_textured_rectangle_with_custom_size(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, ETextureGabarite* _texture);

	extern void add_data_to_vertex_buffer_sprite(float* _array, unsigned int& _start_offset, ESprite* _sprite);

	extern void add_data_to_vertex_buffer_textured_rectangle_real_size(float* _array, unsigned int& _start_offset, float _x, float _y, ETextureGabarite* _texture);

	extern void add_data_to_vertex_buffer_rama(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _t, ETextureGabarite* _texture);
	extern void add_data_to_vertex_buffer_custom_uv(float* _array, unsigned int& _start_offset, float _x, float _y, float _size_x, float _size_y, float _uv_start_x, float _uv_start_y, float _uv_end_x, float _uv_end_y);
	//extern void fill_vertex_buffer_text(float* _array, unsigned int& _start_offset, float _x, float _y, ETextArea* _area);

	extern void call_render_textured_rectangle_with_custom_size(ESprite* _sprite);
	extern void call_render_textured_rectangle_real_size(ESprite* _sprite);
	extern void call_render_textured_sprite(ESprite* _sprite);

	extern float			border_left_size;
	extern float			border_right_size;
	extern float			border_up_size;
	extern float			border_up_size;

	extern unsigned int		subdivision_x;
	extern unsigned int		subdivision_y;

	//
	//gabarite
	//sprite layer
	//texture
	extern void generate_brick_texture(ERegionGabarite* _region, ESpriteLayer* _sprite_layer, ETextureGabarite* _texture_gabarite);
}

namespace NS_EGraphicCore
{
	extern int			SCREEN_WIDTH, SCREEN_HEIGHT;
	extern float			correction_x, correction_y;
	extern Shader* shader_texture_atlas_putter;

	extern glm::mat4		matrix_transform_default;
	extern ERenderBatcher* default_batcher_for_texture_atlas;
	extern ERenderBatcher* default_batcher_for_drawing;

	extern GLFWwindow* main_window;

	extern unsigned int		texture[32];
	extern ETextureAtlas* default_texture_atlas;
	extern unsigned char* image_data;
	extern unsigned char* zalupa;
	extern int			texture_loader_width, texture_loader_height, nrChannels, last_texture_width, last_texture_height;
	extern ETextureAtlas* default_texture_atlas;
	extern float			delta_time;
	extern float			saved_time_for_delta;

	extern				std::vector<ETextureGabarite*> texture_gabarites_list;

	extern void processInput(GLFWwindow* window);

	extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	extern void recalculate_correction();

	extern void switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas);
	extern void make_transform_from_size(ERenderBatcher* _batcher, float _size_x, float _size_y);
	//void load_texture(char const* _path, int _id);

	extern void initiate_graphic_core();

	extern void load_texture(char const* _path, int _id);
	extern ETextureGabarite* put_texture_to_atlas(std::string _name, ETextureAtlas* _atlas);

	void gl_set_texture_filtering(GLint _wrap_mode, GLint _filter);
	void gl_set_blend_mode_default();

	extern float current_offset_x;
	extern float current_offset_y;
	extern float current_zoom;

	extern void set_active_color(const EColor_4(&_color)[4]);
	extern void set_active_color_custom_alpha(const EColor_4(&_color)[4], float _alpha);
	extern void set_active_color(EColor_4* _color);

	extern EColor_4 active_color[4];

};

namespace NS_DefaultGabarites
{
	extern ETextureGabarite* texture_gabarite_gudron;
	extern ETextureGabarite* texture_gabarite_white_pixel;
	//extern 
}



#ifndef _COLOR_COLLECTION_
#define _COLOR_COLLECTION_
namespace NS_EColorUtils
{
	const EColor_4 COLOR_WHITE[4]{ 1.0f,	1.0f,	1.0f,	1.0f };
	const EColor_4 COLOR_BLACK[4]{ 0.0f,	0.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_GRAY[4]{ 0.5f,	0.5f,	0.5f,	1.0f };

	const EColor_4 COLOR_RED[4]{ 1.0f,	0.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_GREEN[4]{ 0.0f,	1.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_BLUE[4]{ 0.0f,	0.0f,	1.0f,	1.0f };

	extern const EColor_4(&choose_from_two(const EColor_4(&_color1)[4], const EColor_4(&_color2)[4], bool _condition))[4];
}
#endif

namespace zalupa
{
	extern int zalupa1;
	extern int zalupa2;
	extern int zalupa3;
}

typedef										unsigned int  indice_type;

class ERenderBatcher
{
private:

	unsigned int									VBO, VAO, EBO = 0;
	unsigned short									parameters_count = 1;

	GLuint										gl_vertex_attribute_id = 0;
	unsigned short									gl_vertex_attribute_offset = 0;

	glm::mat4										matrix_transform;
	Shader* batcher_shader;

	float										transform_position_x, transform_position_y;
	float										transform_screen_size_x = 800.0f, transform_screen_size_y = 600.0f;
	float										transform_zoom = 1.0f;

	//BATCHER VERTEX DATA SEGMENT
	unsigned int									vertices_data_per_vertex = 0;			//count of parameters for one vertices
	//const std::array<int, 255>						indices_buffer[TOTAL_INDICES_COUNT] = generateData();	//indices array

	indice_type									indices_buffer[TOTAL_INDICES_COUNT]{};


	/*float color_red = 0.0f;
	float color_green	= 0.0f;
	float color_blue	= 0.0f;
	float color_alpha	= 0.0f;*/

public:
	float										vertex_buffer[TOTAL_MAX_VERTEX_BUFFER_ARRAY_SIZE]{};
	unsigned int									last_vertice_buffer_index = 0;				//last element of vertex buffer
	EColor_4 batch_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };


	ERenderBatcher();
	~ERenderBatcher();

	//void(*pointer_to_sprite_render)(ESprite* _sprite);
	//void render_sprite_call(ESprite* _sprite);
	void draw_call();

	void set_total_attribute_count(GLsizei _attribute_count);
	void register_new_vertex_attribute(GLint _subpameters_count);

	void set_active_color(const float(&_color)[4]);
	void reset();

	unsigned int get_last_id();
	void set_last_id(unsigned int _id);

	void apply_transform();

	void set_shader(Shader* _shader);
	Shader* get_shader();

	void set_transform_position(float _x, float _y);
	void set_transform_screen_size(float _size_x, float _size_y);
	void set_transform_zoom(float _zoom);

	static bool check_batcher(ERenderBatcher* _batcher);

	GLsizei										gl_vertex_attribute_total_count = 0;
};

class ETextureAtlas
{
private:
	int* atlas_size_x = new int(0);
	int* atlas_size_y = new int(0);

	GLuint* framebuffer = new GLuint(0);
	GLuint* colorbuffer = new GLuint(0);
	GLuint* rbo = new GLuint(0);

public:
	unsigned short get_atlas_size_x();
	unsigned short get_atlas_size_y();

	unsigned short get_framebuffer();
	unsigned short get_colorbuffer();

	ETextureAtlas(float _size_x, float _size_y, int _color_depth = GL_RGBA, int _byte_mode = GL_UNSIGNED_BYTE);
	~ETextureAtlas();

	bool** free_space;
	bool can_place_here(int _x, int _y, int _w, int _h);
};

class ETextureGabarite
{
private:
	std::string* full_path = new std::string("");
	std::string* name = new std::string("");

	int* pos_x_in_pixels = new int(0);
	int* pos_y_in_pixels = new int(0);

public:
	ETextureAtlas* target_atlas = nullptr;

	std::string get_full_path();
	void set_full_path(std::string _full_path);

	std::string get_name();
	void set_name_based_on_full_path(std::string _name);

	void set_uv_parameters(float _uv_start_x, float _uv_start_y, float _uv_end_x, float _uv_end_y);
	void set_real_texture_size(int _size_x, int _size_y);

	float* uv_start_x = new float(0.0f);
	float* uv_start_y = new float(0.0f);
	float* uv_end_x = new float(0.0f);
	float* uv_end_y = new float(0.0f);

	int* position_on_texture_atlas_x = new int(0);
	int* position_on_texture_atlas_y = new int(0);

	int* size_x_in_pixels = new int(0);
	int* size_y_in_pixels = new int(0);

	void calculate_final_sizes();
};

class ESprite
{
public:
	ESprite();
	~ESprite();

	void(*pointer_to_sprite_render)(ESprite* _sprite);

	ETextureGabarite* main_texture;
	ESpriteLayer* master_sprite_layer;

	EColor_4* sprite_color = new float[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	void set_color(float _r, float _g, float _b, float _a);
	void set_color(const float(&_color)[4]);

	//minus size from diffirent side
	float* fragment_offset_x = new float(0.0f);
	float* fragment_offset_y = new float(0.0f);

	float* fragment_size_x = new float(0.0f);
	float* fragment_size_y = new float(0.0f);
	//


	// 
	//final calculated fise with fragments
	float* uv_start_x = new float(0.0f);
	float* uv_start_y = new float(0.0f);

	float* uv_end_x = new float(0.0f);
	float* uv_end_y = new float(0.0f);
	//

	//position and size
	float* offset_x = new float(0.0f);
	float* offset_y = new float(0.0f);
	float* offset_z = new float(0.0f);

	float* world_position_x = new float(0.0f);
	float* world_position_y = new float(0.0f);
	float* world_position_z = new float(0.0f);


	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);
	//what wrong

	void translate_sprite(float _x, float _y, float _z);
	void generate_vertex_buffer_for_master_sprite_layer();

	void set_texture_gabarite(ETextureGabarite* _gabarite);
	void sprite_calculate_uv();

	void reset_sprite();

	void sprite_set_world_positions(float _x, float _y, float _z);

	static ESprite* create_default_sprite(ETextureGabarite* _gabarite, ESpriteLayer* _sprite_layer);
	

	
};

class ESpriteFrame
{
public:
	std::vector<ESprite*> sprite_list;
	int* active_frame_id = new int(0);

	static ESpriteFrame* create_default_sprite_frame();
};
class ESpriteLayer
{
public:
	std::vector<ESpriteFrame*> sprite_frame_list;

	float* offset_x = new float(0.0f);
	float* offset_y = new float(0.0f);
	float* offset_z = new float(0.0f);

	float* world_position_x = new float(0.0f);
	float* world_position_y = new float(0.0f);
	float* world_position_z = new float(0.0f);

	unsigned int* last_buffer_id = new unsigned int(0);

	ERenderBatcher* batcher;
	float* vertex_buffer;

	void translate_sprite_layer(float _x, float _y, float _z);
	void translate_sprites(float _x, float _y, float _z);

	void modify_buffer_position_for_sprite_layer(float _x, float _y, float _z);
	void generate_vertex_buffer_for_sprite_layer(std::string _text);

	void transfer_vertex_buffer_to_batcher();

	void sprite_layer_set_world_position(float _x, float _y, float _z);

	static ESpriteLayer* create_default_sprite_layer(ETextureGabarite* _texture);

	static ESprite* get_last_created_sprite(ESpriteLayer* _layer);
	static void set_size_for_last_sprite(ESpriteLayer* _layer, float _size_x, float _size_y);
};


