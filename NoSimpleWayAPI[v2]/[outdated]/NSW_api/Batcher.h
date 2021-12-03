#pragma once

#include "EColor.h"
#include "EGabarite.h"
#include <vector>

const static int batch_force_draw_call = 30000;

class Batcher
{

public:
	struct EPolygonVertex
	{
		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		EPolygonVertex();
		~EPolygonVertex();

		bool* is_catched = new bool(false);

		std::vector <float*> float_vector;
	};

	struct EPolygonShape
	{
		std::vector<EPolygonVertex*> vertex_list;

		EPolygonVertex* selected_vertex = NULL;

		bool* catched_up_side =		new bool(false);
		bool* catched_down_side =	new bool(false);
		bool* catched_left_side =	new bool(false);
		bool* catched_right_side =	new bool(false);

		bool* catched_mid_side =	new bool(false);

		float* pos_x = new float(0.0f);
		float* pos_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);


		EPolygonShape();
		~EPolygonShape();
	};

	struct EPolygonMassive
	{
		std::vector<EPolygonShape*> shape_list;

		EPolygonMassive();
		~EPolygonMassive();
	};

	Batcher();

	void init();
	void init_shadowmap();
	void init_terrain();
	void init_PBR();

	void draw_rect(float _x, float _y, float _w, float _h);
	void draw_rect_position(float _x, float _y, float _x2, float _y2);
	void draw_rect_without_color(float _x, float _y, float _w, float _h, int _tx, int _ty);
	void draw_with_custom_uv(float _x, float _y, float _w, float _h, float _start_x, float _start_y, float _end_x, float _end_y);

	void draw_gabarite_screen_space(float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g);

	void draw_gabarite(float _x, float _y, float _w, float _h, EGabarite* _g);

	__inline void draw_sprite(float _x, float _y, float _w, float _h, float _left, float _right, float _down, float _up, EGabarite* _g)
	{
		//std::cout << "filled rect" << std::endl;

		//.#
		//..
		vertices[id + 0] = (_x + _w);
		vertices[id + 1] = (_y + _h);
		//vertices[id + 2] = 0;

		vertices[id + 2] = batch_color_r;
		vertices[id + 3] = batch_color_g;
		vertices[id + 4] = batch_color_b;
		vertices[id + 5] = batch_color_a;

		vertices[id + 6] = *_g->x2 - _right;
		vertices[id + 7] = *_g->y2 - _up;

		//..
		//.#
		vertices[id + 8] = (_x + _w);
		vertices[id + 9] = _y;
		//vertices[id + 10] = 0;

		vertices[id + 10] = batch_color_r;
		vertices[id + 11] = batch_color_g;
		vertices[id + 12] = batch_color_b;
		vertices[id + 13] = batch_color_a;

		vertices[id + 14] = *_g->x2 - _right;
		vertices[id + 15] = *_g->y + _down;

		//..
		//#.
		vertices[id + 16] = _x;
		vertices[id + 17] = _y;
		//vertices[id + 18] = 0;

		vertices[id + 18] = batch_color_r;
		vertices[id + 19] = batch_color_g;
		vertices[id + 20] = batch_color_b;
		vertices[id + 21] = batch_color_a;

		vertices[id + 22] = *_g->x + _left;
		vertices[id + 23] = *_g->y + _down;

		//#.
		//..
		vertices[id + 24] = _x;
		vertices[id + 25] = (_y + _h);
		//vertices[id + 26] = 0;

		vertices[id + 26] = batch_color_r;
		vertices[id + 27] = batch_color_g;
		vertices[id + 28] = batch_color_b;
		vertices[id + 29] = batch_color_a;

		vertices[id + 30] = *_g->x + _left;
		vertices[id + 31] = *_g->y2 - _up;

		id += 32;

		if (id > batch_force_draw_call)
		{
			reinit();
			draw_call();
			reset();
		}
	}

	__inline void draw_terrain_PBR(float _x, float _y, float _z, float _size_x, float _size_y, float _size_z, float _tile_offset_x, float _tile_offset_y, EGabarite* _g, EGabarite* _nmg, float _true_height)
	{
		//std::cout << "filled rect" << std::endl;

		//.#
		//..

		//if (_nmg == NULL) { std::cout << "ti ebanutyi?" << std::endl; }
		//std::cout << "zaebal: " << _nmg->name << std::endl;

		//position
		vertices[id + 0] = (_x + _size_x);
		vertices[id + 1] = (_y + _size_y);
		vertices[id + 2] = (_z + _size_z);
		//vertices[id + 2] = 0;

		//color
		vertices[id + 3] = batch_color_r;
		vertices[id + 4] = batch_color_g;
		vertices[id + 5] = batch_color_b;
		vertices[id + 6] = batch_color_a;

		//uv
		vertices[id + 7] = *_g->x + _tile_offset_x + _size_x / 4096.0f;
		vertices[id + 8] = *_g->y + _tile_offset_y + _size_y / 4096.0f;

		//uv reflection
		vertices[id + 9] = 0.0f;
		vertices[id + 10] = (_true_height + _size_y) / 1080.0f;

		//normal gloss
		vertices[id + 11] = *_nmg->x + _tile_offset_x + _size_x / 4096.0f;
		vertices[id + 12] = *_nmg->y + _tile_offset_y + _size_y / 4096.0f;



		//..
		//.#
		vertices[id + 13] = (_x + _size_x);
		vertices[id + 14] = _y;
		vertices[id + 15] = _z;
		//vertices[id + 10] = 0;

		vertices[id + 16] = batch_color_r;
		vertices[id + 17] = batch_color_g;
		vertices[id + 18] = batch_color_b;
		vertices[id + 19] = batch_color_a;

		vertices[id + 20] = *_g->x + _tile_offset_x + _size_x / 4096.0f;
		vertices[id + 21] = *_g->y + _tile_offset_y;

		//uv reflection
		vertices[id + 22] = 0.0f;
		vertices[id + 23] = (_true_height) / 1080.0f;

		//normal gloss
		vertices[id + 24] = *_nmg->x + _tile_offset_x + _size_x / 4096.0f;
		vertices[id + 25] = *_nmg->y + _tile_offset_y;


		//..
		//#.
		vertices[id + 26] = _x;
		vertices[id + 27] = _y;
		vertices[id + 28] = _z;
		//vertices[id + 18] = 0;

		vertices[id + 29] = batch_color_r;
		vertices[id + 30] = batch_color_g;
		vertices[id + 31] = batch_color_b;
		vertices[id + 32] = batch_color_a;

		vertices[id + 33] = *_g->x + _tile_offset_x;
		vertices[id + 34] = *_g->y + _tile_offset_y;

		//uv reflection
		vertices[id + 35] = 0.0f;
		vertices[id + 36] = (_true_height) / 1080.0f;


		//normal gloss
		vertices[id + 37] = *_nmg->x + _tile_offset_x;
		vertices[id + 38] = *_nmg->y + _tile_offset_y;

		//#.
		//..
		vertices[id + 39] = _x;
		vertices[id + 40] = (_y + _size_y);
		vertices[id + 41] = (_z + _size_z);
		//vertices[id + 26] = 0;

		vertices[id + 42] = batch_color_r;
		vertices[id + 43] = batch_color_g;
		vertices[id + 44] = batch_color_b;
		vertices[id + 45] = batch_color_a;

		vertices[id + 46] = *_g->x + _tile_offset_x;
		vertices[id + 47] = *_g->y + _tile_offset_y + _size_y / 4096.0f;

		//uv reflection
		vertices[id + 48] = 0.0f;
		vertices[id + 49] = (_true_height + _size_y) / 1080.0f;

		//normal gloss
		vertices[id + 50] = *_nmg->x + _tile_offset_x;
		vertices[id + 51] = *_nmg->y + _tile_offset_y + _size_y / 4096.0f;

		id += 52;

		if (id > batch_force_draw_call)
		{
			reinit();
			draw_call_PBR();
			reset();
		}
	}

	__inline void draw_sprite_PBR(float _x, float _y, float _z, float _size_x, float _size_y, float _size_z, float _left, float _right, float _down, float _up, EGabarite* _g, EGabarite* _nmg, float _true_height)
	{
		//std::cout << "filled rect" << std::endl;

		//.#
		//..

		//if (_nmg == NULL) { std::cout << "ti ebanutyi?" << std::endl; }
		//std::cout << "zaebal: " << _nmg->name << std::endl;

		//position
		vertices[id + 0] = (_x + _size_x);
		vertices[id + 1] = (_y + _size_y);
		vertices[id + 2] = (_z + _size_z);
		//vertices[id + 2] = 0;

		//color
		vertices[id + 3] = batch_color_r;
		vertices[id + 4] = batch_color_g;
		vertices[id + 5] = batch_color_b;
		vertices[id + 6] = batch_color_a;

		//uv
		vertices[id + 7] = *_g->x2 - _right;
		vertices[id + 8] = *_g->y2 - _up;

		//uv reflection
		vertices[id + 9] = 0.0f;
		vertices[id + 10] = (_true_height + _size_y) / 1080.0f;

		//normal gloss
		vertices[id + 11] = *_nmg->x2 - _right;
		vertices[id + 12] = *_nmg->y2 - _up;



		//..
		//.#
		vertices[id + 13] = (_x + _size_x);
		vertices[id + 14] = _y;
		vertices[id + 15] = _z;
		//vertices[id + 10] = 0;

		vertices[id + 16] = batch_color_r;
		vertices[id + 17] = batch_color_g;
		vertices[id + 18] = batch_color_b;
		vertices[id + 19] = batch_color_a;

		vertices[id + 20] = *_g->x2 - _right;
		vertices[id + 21] = *_g->y + _down;

		//uv reflection
		vertices[id + 22] = 0.0f;
		vertices[id + 23] = (_true_height) / 1080.0f;

		//normal gloss
		vertices[id + 24] = *_nmg->x2 - _right;
		vertices[id + 25] = *_nmg->y + _down;


		//..
		//#.
		vertices[id + 26] = _x;
		vertices[id + 27] = _y;
		vertices[id + 28] = _z;
		//vertices[id + 18] = 0;

		vertices[id + 29] = batch_color_r;
		vertices[id + 30] = batch_color_g;
		vertices[id + 31] = batch_color_b;
		vertices[id + 32] = batch_color_a;

		vertices[id + 33] = *_g->x + _left;
		vertices[id + 34] = *_g->y + _down;

		//uv reflection
		vertices[id + 35] = 0.0f;
		vertices[id + 36] = (_true_height) / 1080.0f;


		//normal gloss
		vertices[id + 37] = *_nmg->x + _left;
		vertices[id + 38] = *_nmg->y + _down;

		//#.
		//..
		vertices[id + 39] = _x;
		vertices[id + 40] = (_y + _size_y);
		vertices[id + 41] = (_z + _size_z);
		//vertices[id + 26] = 0;

		vertices[id + 42] = batch_color_r;
		vertices[id + 43] = batch_color_g;
		vertices[id + 44] = batch_color_b;
		vertices[id + 45] = batch_color_a;

		vertices[id + 46] = *_g->x + _left;
		vertices[id + 47] = *_g->y2 - _up;

		//uv reflection
		vertices[id + 48] = 0.0f;
		vertices[id + 49] = (_true_height + _size_y) / 1080.0f;

		//normal gloss
		vertices[id + 50] = *_nmg->x + _left;
		vertices[id + 51] = *_nmg->y2 - _up;

		id += 52;

		if (id > batch_force_draw_call)
		{
			reinit();
			draw_call_PBR();
			reset();
		}
	}

	void draw_AO_shadow(float _x, float _y, float _size_x, float _size_y, float _size, EGabarite* _g);

	void draw_depthmap_polygon	(EPolygonMassive* _p_massive, float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g);
	void draw_normalmap_polygon	(EPolygonMassive* _p_massive, float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g);

	void draw_two_dimension_gradient	(float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g, EColor* _color_x, EColor* _color_y);



	void draw_gabarite(float _x, float _y, EGabarite* _g);

	void draw_terrain(float _x, float _y, EGabarite* _g);
	void draw_terrain_with_offset(float _x, float _y, float _left, float _right, float _up, float _down, EGabarite* _g);

	void draw_gabarite_skew(float _x, float _y, float _collision_x, float _collision_y, float _tall, EGabarite* _g, float _bottom_skew);
	void draw_gabarite_ark_shadow(float _x, float _y, EGabarite* _g);

	void draw_gabarite_shadowmap(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z);
	void draw_gabarite_shadowmap_fragment(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z, float _fx, float _fy);
	void draw_gabarite_shadowmap_fragment_mirrored(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z, float _fx, float _fy);

	void draw_gabarite_with_offset(float _x, float _y, float _w, float _h, float _offset_x, float _offset_y, float _offset_end_x, float _offset_end_y, EGabarite* _g);

	void fill_indices();

	void setcolor_255(int _r, int _g, int _b, int _a);
	void setcolor(float _r, float _g, float _b, float _a);
	~Batcher();

	float batch_color_r;
	float batch_color_g;
	float batch_color_b;
	float batch_color_a;

	

	void reinit();

	unsigned int id = 0;
	unsigned int VBO, VAO, EBO = 0;

	unsigned int indices_id = 0;
	unsigned int indices_order = 0;

	float vertices[32000];
	unsigned int indices[6000];

	void draw_call();
	void draw_call_terrain();
	void draw_call_shadowmap();
	void draw_call_PBR();

	void reset();

	void setcolor(EColor* _color);
	void setcolor(EColorCollection* _color);

	void setcolor_lum(EColorCollection* _color, float _lum);
	void setcolor_lum_RGB(EColorCollection* _color, float _lum);
	void setcolor_alpha(EColorCollection* _color, float _a);
	void setcolor_lumalpha(EColorCollection* _color, float _lum, float _a);
	void draw_rama(float _x, float _y, float _sx, float _sy, float _t, EGabarite* _g);
	void draw_rama(float _x, float _y, float _sx, float _sy, float _t);
	void draw_rect_gabarite_custom_uv(float _x, float _y, float _w, float _h, EGabarite* _g, float _sx, float _sy, float _ex, float _ey);

	void draw_simple_rect(float _x, float _y, float _size_x, float _size_y);

	void force_draw_call();
	void force_draw_call_terrain();
	void force_draw_call_shadowmap();
	void force_draw_call_PBR();
	static float shadow_FBO_w;
	static float shadow_FBO_h;
	static float zoom;

	static float skew_factor;

	void set_interpolated_color(EColorCollection* _a, EColorCollection* _b, float _value);
};
