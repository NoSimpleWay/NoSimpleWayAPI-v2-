#pragma once
//#define STB_IMAGE_IMPLEMENTATION

/**/#include "ETextCore.h"
//#include <ios>
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
//#ifndef _E_TEXT_CORE_ALREADY_LINKED_
///**/#define _E_TEXT_CORE_ALREADY_LINKED_
///**/#include "ETextCore.h"
/// 


/////// /////// /////// /////// /////// /////// ///////

#include "Helpers.h"


#include <learnopengl/shader_s.h>
#include <vector>
#include <filesystem>

#define NSW_debug_graphic_to_console false

//VERTEX BUFFER ARRAY
constexpr unsigned int VERTICES_PER_SHAPE = 4;
constexpr unsigned int MAX_SHAPES_COUNT = 10000;
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
	extern void add_data_to_vertex_buffer_sprite_test(float* _array, unsigned int& _start_offset, ESprite* _sprite);
	extern void add_data_to_vertex_buffer_sprite_PBR(float* _array, unsigned int& _start_offset, ESprite* _sprite);
	extern void add_data_to_vertex_buffer_texture_gabarite_PBR(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, ETextureGabarite* _texture, ETextureGabarite* _gloss, ETextureGabarite* _normal);
	
	extern void add_data_to_vertex_buffer_texture_fragment_PBR
	(
		float* _array,
		unsigned int& _start_offset,

		float _x,
		float _y,

		float _w,
		float _h,

		float _uv_x,
		float _uv_y,

		ETextureGabarite* _texture,
		ETextureGabarite* _gloss,
		ETextureGabarite* _normal
	);

	extern void add_data_to_vertex_buffer_textured_rectangle_real_size(float* _array, unsigned int& _start_offset, float _x, float _y, ETextureGabarite* _texture);

	extern void add_data_to_vertex_buffer_rama(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _t, ETextureGabarite* _texture);
	extern void add_data_to_vertex_buffer_custom_uv(float* _array, unsigned int& _start_offset, float _x, float _y, float _size_x, float _size_y, float _uv_start_x, float _uv_start_y, float _uv_end_x, float _uv_end_y);
	//extern void fill_vertex_buffer_text(float* _array, unsigned int& _start_offset, float _x, float _y, ETextArea* _area);

	extern void call_render_textured_rectangle_with_custom_size(ESprite* _sprite);
	extern void call_render_textured_rectangle_real_size(ESprite* _sprite);
	extern void call_render_textured_sprite(ESprite* _sprite);
	extern void call_render_textured_sprite_test(ESprite* _sprite);
	extern void call_render_textured_sprite_PBR(ESprite* _sprite);

	extern float			border_left_size;
	extern float			border_right_size;
	extern float			border_up_size;
	extern float			border_down_size;

	extern unsigned int		subdivision_x;
	extern unsigned int		subdivision_y;

	extern bool				temporary_sprites;

	extern void				set_brick_borders_and_subdivisions(float _left, float _right, float _bottom, float _up, int _subdivision_x, int _subdivision_y);

	extern void				add_data_to_vertex_buffer_shade(float* _array, unsigned int& _start_offset, float _x, float _y, float _w, float _h, float _shade_size, ETextureGabarite* _texture);

	//
	//gabarite
	//sprite layer
	//texture
	extern void generate_brick_texture(ERegionGabarite* _region, ESpriteLayer* _sprite_layer, ETextureGabarite* _texture_gabarite, ETextureGabarite* _normal_map_gabarite = nullptr, ETextureGabarite* _gloss_map_gabarite = nullptr);
}

const int texture_skydome_levels = 6;
//[0] 1024
//[1] 512
//[2] 256
//[3] 128
//[4] 64
//[5] 32

class HSVRGBAColor;
namespace NS_EGraphicCore
{
	extern int				SCREEN_WIDTH, SCREEN_HEIGHT;
	extern float			correction_x, correction_y;
	extern Shader*			shader_texture_atlas_putter;

	extern glm::mat4		matrix_transform_default;

	//batchers
	extern ERenderBatcher* default_batcher_for_texture_atlas;
	extern ERenderBatcher* default_batcher_for_drawing;
	extern ERenderBatcher* pbr_batcher;
	extern ERenderBatcher* test_batcher;
	extern ERenderBatcher* skydome_batcher;

	extern GLFWwindow*		main_window;

	extern unsigned int		texture[32];

	extern ETextureAtlas*	default_texture_atlas;
	extern ETextureAtlas*	skydome_texture_atlas[texture_skydome_levels];

	extern unsigned char*	image_data;
	extern unsigned char*	zalupa;
	extern int				nrChannels;
	extern int				texture_loader_width, texture_loader_height,  last_texture_width, last_texture_height;
	//extern ETextureAtlas*	default_texture_atlas;
	extern float			delta_time;
	extern float			saved_time_for_delta;

	extern					std::vector<std::vector<ETextureGabarite*>> texture_gabarites_list;

	extern void processInput(GLFWwindow* window);

	extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	extern void recalculate_correction();

	extern void switch_to_texture_atlas_draw_mode(ETextureAtlas* _atlas);
	extern void make_transform_from_size(ERenderBatcher* _batcher, float _size_x, float _size_y);
	extern void switch_to_this_FBO(ETextureAtlas* _atlas);
	//void load_texture(char const* _path, int _id);

	extern void initiate_graphic_core();

	extern void load_texture(char const* _path, int _id);
	extern void get_png_image_dimensions(std::string& file_path, unsigned int& width, unsigned int& height);
	extern bool getPngSize(const char* fileName, int& _x, int& _y);


	extern ETextureGabarite*	put_texture_to_atlas(std::string _name, ETextureAtlas* _atlas);
	extern ETextureGabarite*	load_from_textures_folder(std::string _name);
	extern ETextureGabarite*	load_texture_to_default_atlas(std::string _name);
	extern void					load_style_texture(EGUIStyle* _style, EBrickStyle* _brick);
	extern void					complete_texture_gabarite(ETextureGabarite* _texture_gabarite);

	void gl_set_texture_filtering(GLint _wrap_mode, GLint _filter);
	void gl_set_blend_mode_default();

	extern float current_offset_x;
	extern float current_offset_y;

	extern float stored_zoom;
	extern float current_zoom;

	extern void set_active_color(const EColor_4(&_color)[4]);
	extern void set_active_color_custom_alpha(const EColor_4(&_color)[4], float _alpha);
	extern void set_active_color(EColor_4* _color);
	extern void set_active_color(float _r, float _g, float _b, float _a);
	extern void set_active_color(HSVRGBAColor* _color);

	extern void make_skydome_textures(ETextureGabarite* _texture);

	extern EColor_4 active_color[4];

	extern void set_source_FBO(int _GL_texture_id, unsigned int _colorbuffer_id);
	extern void set_target_FBO(unsigned int _framebuffer_id);

	extern ETextureGabarite* get_gabarite_from_full_path_and_suffix(ETextureGabarite* _gabarite, std::string _suffix);
	extern float global_normal_multiplier;
	extern float global_gloss_multiplier;
	extern float plastic_or_metal_multiplier;

	extern float global_free_sky_light_multiplier;
	extern float global_free_sun_light_multiplier;
	extern float global_reflection_multiplier;

	extern float sun_x;
	extern float sun_y;

	extern float sun_size;
	extern float sun_blur;
	extern float sun_bright;
	extern float sun_exp;

	extern float time_total;
	extern float move_multiplier;

	extern float sun_flat_decay;

	extern HSVRGBAColor sun_color;

	extern float ground_level;

	typedef struct RgbColor
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	} RgbColor;

	typedef struct HsvColor
	{
		unsigned char h;
		unsigned char s;
		unsigned char v;
	} HsvColor;

	extern RgbColor HsvToRgb(HsvColor hsv);


	extern HsvColor RgbToHsv(RgbColor rgb);

	extern void refresh_autosize_groups(EWindow* _window);
};

namespace NS_DefaultGabarites
{
	extern ETextureGabarite* texture_gabarite_gudron;
	extern ETextureGabarite* texture_rusted_bronze;
	extern ETextureGabarite* texture_lead_and_gold;
	extern ETextureGabarite* texture_lapis_wood;
	extern ETextureGabarite* texture_black_marble;
	extern ETextureGabarite* texture_dark_spruce;
	extern ETextureGabarite* texture_slider_bg_lead_and_gold;

	extern ETextureGabarite* texture_gabarite_white_pixel;
	extern ETextureGabarite* texture_gabarite_normal_map_placeholder;
	extern ETextureGabarite* texture_gabarite_gloss_map_placeholder;
	extern ETextureGabarite* texture_gabarite_skydome;

	extern ETextureGabarite* texture_bool_switcher_activated_box;
	extern ETextureGabarite* texture_bool_switcher_deactivated_box;

	extern ETextureGabarite* texture_button_radiance;
	extern ETextureGabarite* texture_button_radiance_dot;
	//extern 
}



#ifndef _COLOR_COLLECTION_
#define _COLOR_COLLECTION_
namespace NS_EColorUtils
{
	const EColor_4 COLOR_WHITE[4]		{ 1.0f,		1.0f,	1.0f,	1.0f };
	const EColor_4 COLOR_BLACK[4]		{ 0.0f,		0.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_GRAY[4]		{ 0.5f,		0.5f,	0.5f,	1.0f };
	const EColor_4 COLOR_DARK_GRAY[4]	{ 0.25f,	0.25f,	0.25f,	1.0f };

	const EColor_4 COLOR_RED[4]			{ 1.0f,		0.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_GREEN[4]		{ 0.0f,		1.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_BLUE[4]		{ 0.0f,		0.0f,	1.0f,	1.0f };

	const EColor_4 COLOR_YELLOW[4]		{ 1.0f,		1.0f,	0.0f,	1.0f };
	const EColor_4 COLOR_PINK[4]		{ 1.0f,		0.0f,	1.0f,	1.0f };
	const EColor_4 COLOR_CYAN[4]		{ 0.0f,		1.0f,	1.0f,	1.0f };
	

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

	GLuint											gl_vertex_attribute_id = 0;
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
	void direct_draw_call();

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

	static bool check_batcher(ERenderBatcher* _batcher,unsigned int _add = 0);
	static bool if_have_space_for_data(ERenderBatcher* _batcher, unsigned int _add = 0);

	GLsizei										gl_vertex_attribute_total_count = 0;

	int array_offset_for_x = 0;
	int array_offset_for_y = 1;
	int array_offset_for_z = -1;
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

	ETextureAtlas(int _size_x, int _size_y, int _color_depth = GL_RGBA, int _byte_mode = GL_UNSIGNED_BYTE);
	~ETextureAtlas();

	bool** free_space;
	bool can_place_here(int _x, int _y, int _w, int _h);
};

class ETextureGabarite
{
private:
	std::string* full_path = new std::string("");
	std::string* name = new std::string("");

	int pos_x_in_pixels = (0);
	int pos_y_in_pixels = (0);

public:
	ETextureAtlas* target_atlas = nullptr;

	std::string get_full_path();
	void set_full_path(std::string _full_path);

	std::string get_name();
	void set_name_based_on_full_path(std::string _name);

	void set_uv_parameters(float _uv_start_x, float _uv_start_y, float _uv_end_x, float _uv_end_y);
	void set_real_texture_size(int _size_x, int _size_y);

	float uv_start_x = (0.0f);
	float uv_start_y = (0.0f);
	float uv_end_x = (0.0f);
	float uv_end_y = (0.0f);

	float uv_size_x = 0.0f;
	float uv_size_y = 0.0f;

	int position_on_texture_atlas_x = (-1);
	int position_on_texture_atlas_y = (-1);

	int size_x_in_pixels = (0);
	int size_y_in_pixels = (0);

	void calculate_final_sizes();

	//bool incomplete = false;

	static std::vector<ETextureGabarite*> incomplete_gabarites_list;

	//int x_position_on_atlas = -1;
	//int y_position_on_atlas = -1;
};

class ESprite
{
public:
	ESprite();
	~ESprite();

	void(*pointer_to_sprite_render)(ESprite* _sprite);

	ETextureGabarite* main_texture		= nullptr;
	ETextureGabarite* normal_texture	= nullptr;
	ETextureGabarite* gloss_texture		= nullptr;

	ESpriteLayer* master_sprite_layer	= nullptr;

	EColor_4* sprite_color = new float[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	void set_color(float _r, float _g, float _b, float _a);
	void set_color(const float(&_color)[4]);

	//minus size from diffirent side
	float fragment_offset_x = 0.0f;
	float fragment_offset_y = 0.0f;

	float fragment_size_x = 0.0f;
	float fragment_size_y = 0.0f;
	//


	// 
	//final calculated fise with fragments
	float uv_start_x = 0.0f;
	float uv_start_y = 0.0f;

	float uv_end_x = 0.0f;
	float uv_end_y = 0.0f;
	//


	// 
	//final calculated fise with fragments
	float normal_uv_start_x = 0.0f;
	float normal_uv_start_y = 0.0f;
		  
	float normal_uv_end_x = 0.0f;
	float normal_uv_end_y = 0.0f;
	//


	// 
	//final calculated fise with fragments
	float gloss_uv_start_x = 0.0f;
	float gloss_uv_start_y = 0.0f;
		  
	float gloss_uv_end_x = 0.0f;
	float gloss_uv_end_y = 0.0f;
	//

	//position and size
	float offset_x =0.0f;
	float offset_y =0.0f;
	float offset_z =0.0f;

	float world_position_x = 0.0f;
	float world_position_y = 0.0f;
	float world_position_z = 0.0f;


	float size_x = 0.0f;
	float size_y = 0.0f;
	float size_z = 0.0f;
	//what wrong

	void translate_sprite(float _x, float _y, float _z);
	void generate_vertex_buffer_for_master_sprite_layer();

	void set_texture_gabarite						(ETextureGabarite* _gabarite, ETextureGabarite* _normal_map_gabarite, ETextureGabarite* _gloss_map_gabarite);
	void set_texture_gabarite_with_size_and_offset	(ETextureGabarite* _gabarite, ETextureGabarite* _normal_map_gabarite, ETextureGabarite* _gloss_map_gabarite, float _offset_x, float _offset_y, float _offset_z, float _size_x, float _size_y, float _size_z);
	void sprite_calculate_uv();

	void reset_sprite();

	void sprite_set_world_positions(float _x, float _y, float _z);

	static ESprite* create_default_sprite(ETextureGabarite* _gabarite, ESpriteLayer* _sprite_layer);
	static void set_size(ESprite* _sprite, float _size_x, float _size_y, float _size_z);

	bool marked_as_deleted;
	
};

class ESpriteFrame
{
public:
	~ESpriteFrame();

	std::vector<ESprite*> sprite_list;
	int* active_frame_id = new int(0);

	bool marked_as_temporary = false;

	static ESpriteFrame* create_default_sprite_frame();
	static ESpriteFrame* create_default_sprite_frame_with_sprite(ETextureGabarite* _texture_gabarite, ESpriteLayer* _parent_sprite_layer);
};

class ESpriteLayer
{
public:
	~ESpriteLayer();

	std::vector<ESpriteFrame*> sprite_frame_list;

	float offset_x = (0.0f);
	float offset_y = (0.0f);
	float offset_z = (0.0f);

	float world_position_x = (0.0f);
	float world_position_y = (0.0f);
	float world_position_z = (0.0f);

	unsigned int last_buffer_id = (0);
	unsigned int total_capacity = (0);

	bool autodeletable = true;
	ERenderBatcher* batcher = nullptr;
	float* vertex_buffer = nullptr;

	bool disable_draw = false;

	void translate_sprite_layer	(float _x, float _y, float _z, bool _move_offset);
	void translate_sprites		(float _x, float _y, float _z, bool _move_offset);

	void modify_buffer_position_for_sprite_layer(float _x, float _y, float _z);
	void generate_vertex_buffer_for_sprite_layer(std::string _text);

	void transfer_vertex_buffer_to_batcher();

	void sprite_layer_set_world_position(float _x, float _y, float _z);

	static ESpriteLayer* create_default_sprite_layer(ETextureGabarite* _texture);
	void make_as_PBR();

	static ESpriteLayer* create_default_sprite_layer_with_size_and_offset
	(
		ETextureGabarite* _texture,
		float _offset_x,
		float _offset_y,
		float _offset_z,
		float _size_x,
		float _size_y,
		float _size_z
	);


	static ESprite* get_last_created_sprite(ESpriteLayer* _layer);
	static ESpriteFrame* get_last_sprite_frame(ESpriteLayer* _layer);
	static void set_size_for_last_sprite(ESpriteLayer* _layer, float _size_x, float _size_y);
	static void set_offset_for_last_sprite(ESpriteLayer* _layer, float _offset_x, float _offset_y, float _offset_z );
	static void add_new_default_frame_with_sprite(ETextureGabarite* _texture_gabarite, ESpriteLayer* _sprite_layer);

	static int data_copies_count;
	static int data_copy_calls;

	std::vector <EBrickPlane*> brick_plane_list;

};

class EBrickPlane
{
public:
	ERegionGabarite*	region_gabarite;

	ETextureGabarite*	main_texture;
	ETextureGabarite*	normal_map_texture;
	ETextureGabarite*	gloss_texture;

	ESpriteLayer*		parent_sprite_layer;
};


