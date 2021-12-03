#include "Batcher.h"

#include <glad/glad.h>
#include <iostream>

#include "EColor.h"
#include "EGabarite.h"
#include <NSW_api/EUtils.h>

float Batcher::shadow_FBO_w;
float Batcher::shadow_FBO_h;
float Batcher::zoom;

float Batcher::skew_factor;

void Batcher::setcolor(float _r, float _g, float _b, float _a)
{
	batch_color_r = _r;
	batch_color_g = _g;
	batch_color_b = _b;

	batch_color_a = _a;
}

Batcher::Batcher()
{
	std::cout << "created" << std::endl;
}

void Batcher::init()
{
	std::cout << "initiate" << std::endl;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Batcher::init_shadowmap()
{
	std::cout << "initiate" << std::endl;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// shadowmap coord attribute
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// supermap coord attribute
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(10 * sizeof(float)));
	glEnableVertexAttribArray(4);

	// lightmap coord attribute
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(12 * sizeof(float)));
	glEnableVertexAttribArray(5);

	// full shadow coord attribute
	glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(14 * sizeof(float)));
	glEnableVertexAttribArray(6);
}

void Batcher::init_terrain()
{
	std::cout << "initiate" << std::endl;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Batcher::init_PBR()
{
	std::cout << "initiate PBR" << std::endl;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// global illumination reflection UV
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// normal gloss map UV
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(11 * sizeof(float)));
	glEnableVertexAttribArray(4);
}

void Batcher::draw_rect_position(float _x, float _y, float _x2, float _y2)
{
	//std::cout << "filled rect" << std::endl;
	//std::cout << "filled rect" << std::endl;

	//.#
	//..
	vertices[id + 0] = (_x2);
	vertices[id + 1] = (_y2);
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	vertices[id + 6] = 1.0f;
	vertices[id + 7] = 1.0f;

	//..
	//.#
	vertices[id + 8] = (_x2);
	vertices[id + 9] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = 1.0f;
	vertices[id + 15] = 0.0f;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = 0.0f;
	vertices[id + 23] = 0.0f;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y2);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = 0.0f;
	vertices[id + 31] = 1.0f;

	id += 32;
}

void Batcher::draw_rect(float _x, float _y, float _w, float _h)
{
	//std::cout << "filled rect" << std::endl;
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

	vertices[id + 6] = 1.0f;
	vertices[id + 7] = 1.0f;

	//..
	//.#
	vertices[id + 8] = (_x + _w);
	vertices[id + 9] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = 1.0f;
	vertices[id + 15] = 0.0f;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = 0.0f;
	vertices[id + 23] = 0.0f;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y + _h);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = 0.0f;
	vertices[id + 31] = 1.0f;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_rect_without_color(float _x, float _y, float _w, float _h, int _tx, int _ty)
{
	//std::cout << "filled rect" << std::endl;

	vertices[id + 0] = _x + _w;
	vertices[id + 1] = _y + _h;
	vertices[id + 2] = 0;

	vertices[id + 3] = 0.25f + 0.25f * _tx;
	vertices[id + 4] = 0.20f + 0.20f * _ty;

	vertices[id + 5] = _x + _w;
	vertices[id + 6] = _y - _h;
	vertices[id + 7] = 0;

	vertices[id + 8] = 0.25f + 0.25f * _tx;
	vertices[id + 9] = 0.0f + 0.20f * _ty;

	vertices[id + 10] = _x - _w;
	vertices[id + 11] = _y - _h;
	vertices[id + 12] = 0;

	vertices[id + 13] = 0.0f + 0.25f * _tx;
	vertices[id + 14] = 0.0f + 0.20f * _ty;

	vertices[id + 15] = _x - _w;
	vertices[id + 16] = _y + _h;
	vertices[id + 17] = 0;

	vertices[id + 18] = 0.0f + 0.25f * _tx;
	vertices[id + 19] = 0.20f + 0.20f * _ty;

	id += 20;
}

void Batcher::draw_with_custom_uv(float _x, float _y, float _w, float _h, float _start_x, float _start_y, float _end_x, float _end_y)
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

	vertices[id + 6] = _end_x;
	vertices[id + 7] = _end_y;

	//..
	//.#
	vertices[id + 8] = (_x + _w);
	vertices[id + 9] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = _end_x;
	vertices[id + 15] = _start_y;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = _start_x;
	vertices[id + 23] = _start_y;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y + _h);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = _start_x;
	vertices[id + 31] = _end_y;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_gabarite_screen_space(float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g)
{
	//std::cout << "filled rect" << std::endl;

	//.#
	//..
	vertices[id + 0] = (_start_x + _size_x);
	vertices[id + 1] = (_start_y + _size_y);
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	vertices[id + 6] = *_g->x + (_start_x + _size_x) / 4096.0f;
	vertices[id + 7] = *_g->y + (_start_y + _size_y) / 4096.0f;

	//..
	//.#
	vertices[id + 8] = (_start_x + _size_x);
	vertices[id + 9] = _start_y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = *_g->x + (_start_x + _size_x) / 4096.0f;
	vertices[id + 15] = *_g->y + (_start_y) / 4096.0f;

	//..
	//#.
	vertices[id + 16] = _start_x;
	vertices[id + 17] = _start_y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x + (_start_x) / 4096.0f;
	vertices[id + 23] = *_g->y + (_start_y) / 4096.0f;

	//#.
	//..
	vertices[id + 24] = _start_x;
	vertices[id + 25] = _start_y + _size_y;
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = *_g->x + (_start_x) / 4096.0f;
	vertices[id + 31] = *_g->y + (_start_y + _size_y) / 4096.0f;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_gabarite(float _x, float _y, float _w, float _h, EGabarite* _g)
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

	vertices[id + 6] = *_g->x2;
	vertices[id + 7] = *_g->y2;

	//..
	//.#
	vertices[id + 8] = (_x + _w);
	vertices[id + 9] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = *_g->x2;
	vertices[id + 15] = *_g->y;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x;
	vertices[id + 23] = *_g->y;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y + _h);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = *_g->x;
	vertices[id + 31] = *_g->y2;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

//void Batcher::draw_sprite(float _x, float _y, float _w, float _h, float _left, float _right, float _down, float _up, EGabarite* _g)


//void Batcher::draw_sprite_PBR(float _x, float _y, float _z, float _size_x, float _size_y, float _size_z, float _left, float _right, float _down, float _up, EGabarite* _g, EGabarite* _nmg, float _true_height)


void Batcher::draw_AO_shadow(float _x, float _y, float _size_x, float _size_y, float _s, EGabarite* _g)
{
	//#..
	//...
	//...

		//.#
		//..
			vertices[id + 0] = _x;
			vertices[id + 1] = _y + _size_y + _s;
			//vertices[id + 2] = 0;

			//color
			vertices[id + 2] = 1.0f;
			vertices[id + 3] = 1.0f;
			vertices[id + 4] = 1.0f;
			vertices[id + 5] = batch_color_a;

			//uv
			vertices[id + 6] = *_g->x2;
			vertices[id + 7] = *_g->y2;
		
		//..
		//.#
			vertices[id + 8] = _x;
			vertices[id + 9] = _y + _size_y;
			//vertices[id + 2] = 0;

			//color
			vertices[id + 10] = batch_color_r;
			vertices[id + 11] = batch_color_g;
			vertices[id + 12] = batch_color_b;
			vertices[id + 13] = batch_color_a;

			//uv
			vertices[id + 14] = *_g->x2;
			vertices[id + 15] = *_g->y;
			
		//..
		//#.
			vertices[id + 16] = _x - _s;
			vertices[id + 17] = _y + _size_y;
			//vertices[id + 2] = 0;

			//color
			vertices[id + 18] = 1.0f;
			vertices[id + 19] = 1.0f;
			vertices[id + 20] = 1.0f;
			vertices[id + 21] = batch_color_a;

			//uv
			vertices[id + 22] = *_g->x;
			vertices[id + 23] = *_g->y;
			
		//#.
		//..
			vertices[id + 24] = _x - _s * 0.6f;
			vertices[id + 25] = _y + _size_y + _s * 0.6f;
			//vertices[id + 2] = 0;

			//color
			vertices[id + 26] = 1.0f;
			vertices[id + 27] = 1.0f;
			vertices[id + 28] = 1.0f;
			vertices[id + 29] = batch_color_a;

			//uv
			vertices[id + 30] = *_g->x;
			vertices[id + 31] = *_g->y;

			id += 32;

	//.#.
	//...
	//...

		//.#
		//..
		vertices[id + 0] = _x + _size_x;
		vertices[id + 1] = _y + _size_y + _s;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = 1.0f;
		vertices[id + 3] = 1.0f;
		vertices[id + 4] = 1.0f;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id + 8] = _x + _size_x;
		vertices[id + 9] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = batch_color_r;
		vertices[id + 11] = batch_color_g;
		vertices[id + 12] = batch_color_b;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x2;
		vertices[id + 15] = *_g->y;

		//..
		//#.
		vertices[id + 16] = _x;
		vertices[id + 17] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = batch_color_r;
		vertices[id + 19] = batch_color_g;
		vertices[id + 20] = batch_color_b;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = _x;
		vertices[id + 25] = _y + _size_y + _s;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = 1.0f;
		vertices[id + 27] = 1.0f;
		vertices[id + 28] = 1.0f;
		vertices[id + 29] = batch_color_a;

		//uv
		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y;

		id += 32;
	//..#
	//...
	//...

		//#.
		//..
		vertices[id + 0] = _x + _size_x;
		vertices[id + 1] = _y + _size_y + _s;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = 1.0f;
		vertices[id + 3] = 1.0f;
		vertices[id + 4] = 1.0f;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x;
		vertices[id + 7] = *_g->y2;

		//..
		//#.
		vertices[id + 8] = _x + _size_x;
		vertices[id + 9] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = batch_color_r;
		vertices[id + 11] = batch_color_g;
		vertices[id + 12] = batch_color_b;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x;
		vertices[id + 15] = *_g->y;

		//..
		//.#
		vertices[id + 16] = _x + _size_x + _s;
		vertices[id + 17] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = 1.0f;
		vertices[id + 19] = 1.0f;
		vertices[id + 20] = 1.0f;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x2;
		vertices[id + 23] = *_g->y;

		//.#
		//..
		vertices[id + 24] = _x + _size_x + _s * 0.6f;
		vertices[id + 25] = _y + _size_y + _s * 0.6f;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = 1.0f;
		vertices[id + 27] = 1.0f;
		vertices[id + 28] = 1.0f;
		vertices[id + 29] = batch_color_a;

		//uv
		vertices[id + 30] = *_g->x2;
		vertices[id + 31] = *_g->y2;

		id += 32;

	//...
	//#..
	//...

		//.#
		//..
		vertices[id + 0] = _x;
		vertices[id + 1] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = batch_color_r;
		vertices[id + 3] = batch_color_g;
		vertices[id + 4] = batch_color_b;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id + 8] = _x;
		vertices[id + 9] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = batch_color_r;
		vertices[id + 11] = batch_color_g;
		vertices[id + 12] = batch_color_b;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x2;
		vertices[id + 15] = *_g->y;

		//..
		//#.
		vertices[id + 16] = _x - _s;
		vertices[id + 17] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = 1.0f;
		vertices[id + 19] = 1.0f;
		vertices[id + 20] = 1.0f;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = _x - _s;
		vertices[id + 25] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = 1.0f;
		vertices[id + 27] = 1.0f;
		vertices[id + 28] = 1.0f;
		vertices[id + 29] = batch_color_a;

		//uv
		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y;

		id += 32;

	//...
	//.#.
	//...

		//.#
		//..
		vertices[id + 0] = _x + _size_x;
		vertices[id + 1] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = batch_color_r;
		vertices[id + 3] = batch_color_g;
		vertices[id + 4] = batch_color_b;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id + 8] = _x + _size_x;
		vertices[id + 9] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = batch_color_r;
		vertices[id + 11] = batch_color_g;
		vertices[id + 12] = batch_color_b;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x2;
		vertices[id + 15] = *_g->y;

		//..
		//#.
		vertices[id + 16] = _x;
		vertices[id + 17] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = batch_color_r;
		vertices[id + 19] = batch_color_g;
		vertices[id + 20] = batch_color_b;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = _x;
		vertices[id + 25] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = batch_color_r;
		vertices[id + 27] = batch_color_g;
		vertices[id + 28] = batch_color_b;
		vertices[id + 29] = batch_color_a;;

		//uv
		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y;

		id += 32;

	//...
	//..#
	//...

		//.#
		//..
		vertices[id + 0] = _x + _size_x + _s;
		vertices[id + 1] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = 1.0f;
		vertices[id + 3] = 1.0f;
		vertices[id + 4] = 1.0f;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id + 8] = _x + _size_x + _s;
		vertices[id + 9] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = 1.0f;
		vertices[id + 11] = 1.0f;
		vertices[id + 12] = 1.0f;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x2;
		vertices[id + 15] = *_g->y;

		//..
		//#.
		vertices[id + 16] = _x + _size_x;
		vertices[id + 17] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = batch_color_r;
		vertices[id + 19] = batch_color_g;
		vertices[id + 20] = batch_color_b;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = _x + _size_x;
		vertices[id + 25] = _y + _size_y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = batch_color_r;
		vertices[id + 27] = batch_color_g;
		vertices[id + 28] = batch_color_b;
		vertices[id + 29] = batch_color_a;

		//uv
		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y;

		id += 32;

	//...
	//...
	//#..

		//		|0|
		//#.
		//..
		vertices[id + 0] = _x - _s;
		vertices[id + 1] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = 1.0f;
		vertices[id + 3] = 1.0f;
		vertices[id + 4] = 1.0f;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x;
		vertices[id + 7] = *_g->y2;

		//		|1|
		//.#
		//..
		vertices[id + 8] = _x;
		vertices[id + 9] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = batch_color_r;
		vertices[id + 11] = batch_color_g;
		vertices[id + 12] = batch_color_b;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x;
		vertices[id + 15] = *_g->y;

		//		|2|
		//..
		//.#
		vertices[id + 16] = _x;
		vertices[id + 17] = _y - _s;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = 1.0f;
		vertices[id + 19] = 1.0f;
		vertices[id + 20] = 1.0f;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x2;
		vertices[id + 23] = *_g->y;
		
		//		|3|
		//..
		//#.
		vertices[id + 24] = _x - _s * 0.6f;
		vertices[id + 25] = _y - _s * 0.6f;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = 1.0f;
		vertices[id + 27] = 1.0f;
		vertices[id + 28] = 1.0f;
		vertices[id + 29] = batch_color_a;

		//uv
		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y;


			id += 32;
		
	//...
	//...
	//.#.

		//.#
		//..
		vertices[id + 0] = _x + _size_x;
		vertices[id + 1] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = batch_color_r;
		vertices[id + 3] = batch_color_g;
		vertices[id + 4] = batch_color_b;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id + 8] = _x + _size_x;
		vertices[id + 9] = _y - _s;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = 1.0f;
		vertices[id + 11] = 1.0f;
		vertices[id + 12] = 1.0f;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x2;
		vertices[id + 15] = *_g->y;

		//..
		//#.
		vertices[id + 16] = _x;
		vertices[id + 17] = _y - _s;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = 1.0f;
		vertices[id + 19] = 1.0f;
		vertices[id + 20] = 1.0f;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = _x;
		vertices[id + 25] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = batch_color_r;
		vertices[id + 27] = batch_color_g;
		vertices[id + 28] = batch_color_b;
		vertices[id + 29] = batch_color_a;

		//uv
		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y;

		id += 32;
		
	//...
	//...
	//..#

		//.#
		//..
		vertices[id + 0] = _x + _size_x + _s;
		vertices[id + 1] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 2] = 1.0f;
		vertices[id + 3] = 1.0f;
		vertices[id + 4] = 1.0f;
		vertices[id + 5] = batch_color_a;

		//uv
		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id + 8] = _x + _size_x + _s * 0.6f;
		vertices[id + 9] = _y - _s * 0.6f;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 10] = 1.0f;
		vertices[id + 11] = 1.0f;
		vertices[id + 12] = 1.0f;
		vertices[id + 13] = batch_color_a;

		//uv
		vertices[id + 14] = *_g->x2;
		vertices[id + 15] = *_g->y;

		//..
		//#.
		vertices[id + 16] = _x + _size_x;
		vertices[id + 17] = _y - _s;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 18] = 1.0f;
		vertices[id + 19] = 1.0f;
		vertices[id + 20] = 1.0f;
		vertices[id + 21] = batch_color_a;

		//uv
		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = _x + _size_x;
		vertices[id + 25] = _y;
		//vertices[id + 2] = 0;

		//color
		vertices[id + 26] = batch_color_r;
		vertices[id + 27] = batch_color_g;
		vertices[id + 28] = batch_color_b;
		vertices[id + 29] = batch_color_a;

		//uv
		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y;

		id += 32;


	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}

}


void Batcher::draw_depthmap_polygon(EPolygonMassive* _p_massive, float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g)
{
	
	for (EPolygonShape* p_shape: _p_massive->shape_list)
	{
		//std::cout << "try draw vertex massive" << std::endl;
		//.#
		//..
		vertices[id + 0] = (_start_x + _size_x * *p_shape->vertex_list.at(0)->position_x);
		vertices[id + 1] = (_start_y + _size_y * *p_shape->vertex_list.at(0)->position_y);
		//vertices[id + 2] = 0;

		vertices[id + 2] = *p_shape->vertex_list.at(0)->float_vector.at(0) / 512.0f;
		vertices[id + 3] = *p_shape->vertex_list.at(0)->float_vector.at(0) / 512.0f;
		vertices[id + 4] = *p_shape->vertex_list.at(0)->float_vector.at(0) / 512.0f;
		vertices[id + 5] = 1.0f;

		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id +	8]	= (_start_x + _size_x * *p_shape->vertex_list.at(1)->position_x);
		vertices[id +	9]	= (_start_y + _size_y * *p_shape->vertex_list.at(1)->position_y);

		vertices[id +	10]	= *p_shape->vertex_list.at(1)->float_vector.at(0) / 512.0f;
		vertices[id +	11]	= *p_shape->vertex_list.at(1)->float_vector.at(0) / 512.0f;
		vertices[id +	12]	= *p_shape->vertex_list.at(1)->float_vector.at(0) / 512.0f;
		vertices[id +	13]	= 1.0f;

		vertices[id +	14]	= *_g->x2;
		vertices[id +	15]	= *_g->y;

		//..
		//#.
		vertices[id + 16] = (_start_x + _size_x * *p_shape->vertex_list.at(2)->position_x);
		vertices[id + 17] = (_start_y + _size_y * *p_shape->vertex_list.at(2)->position_y);

		vertices[id + 18] = *p_shape->vertex_list.at(2)->float_vector.at(0) / 512.0f;
		vertices[id + 19] = *p_shape->vertex_list.at(2)->float_vector.at(0) / 512.0f;
		vertices[id + 20] = *p_shape->vertex_list.at(2)->float_vector.at(0) / 512.0f;
		vertices[id + 21] = 1.0f;

		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = (_start_x + _size_x * *p_shape->vertex_list.at(3)->position_x);
		vertices[id + 25] = (_start_y + _size_y * *p_shape->vertex_list.at(3)->position_y);

		vertices[id + 26] = *p_shape->vertex_list.at(3)->float_vector.at(0) / 512.0f;
		vertices[id + 27] = *p_shape->vertex_list.at(3)->float_vector.at(0) / 512.0f;
		vertices[id + 28] = *p_shape->vertex_list.at(3)->float_vector.at(0) / 512.0f;
		vertices[id + 29] = 1.0f;

		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y2;
	}

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_normalmap_polygon(EPolygonMassive* _p_massive, float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g)
{
	for (EPolygonShape* p_shape : _p_massive->shape_list)
	{
		//std::cout << "try draw vertex massive" << std::endl;
		//.#
		//..
		vertices[id + 0] = (_start_x + _size_x * *p_shape->vertex_list.at(0)->position_x);
		vertices[id + 1] = (_start_y + _size_y * *p_shape->vertex_list.at(0)->position_y);
		//vertices[id + 2] = 0;

		vertices[id + 2] = *p_shape->vertex_list.at(0)->float_vector.at(0);
		vertices[id + 3] = 0.0f;
		vertices[id + 4] = *p_shape->vertex_list.at(0)->float_vector.at(1);
		vertices[id + 5] = 1.0f;

		vertices[id + 6] = *_g->x2;
		vertices[id + 7] = *_g->y2;

		//..
		//.#
		vertices[id + 8] = (_start_x + _size_x * *p_shape->vertex_list.at(1)->position_x);
		vertices[id + 9] = (_start_y + _size_y * *p_shape->vertex_list.at(1)->position_y);

		vertices[id + 10] = *p_shape->vertex_list.at(1)->float_vector.at(0);
		vertices[id + 11] = 0.0f;
		vertices[id + 12] = *p_shape->vertex_list.at(1)->float_vector.at(1);
		vertices[id + 13] = 1.0f;

		vertices[id + 14] = *_g->x2;
		vertices[id + 15] = *_g->y;

		//..
		//#.
		vertices[id + 16] = (_start_x + _size_x * *p_shape->vertex_list.at(2)->position_x);
		vertices[id + 17] = (_start_y + _size_y * *p_shape->vertex_list.at(2)->position_y);

		vertices[id + 18] = *p_shape->vertex_list.at(2)->float_vector.at(0);
		vertices[id + 19] = 0.0f;
		vertices[id + 20] = *p_shape->vertex_list.at(2)->float_vector.at(1);
		vertices[id + 21] = 1.0f;

		vertices[id + 22] = *_g->x;
		vertices[id + 23] = *_g->y;

		//#.
		//..
		vertices[id + 24] = (_start_x + _size_x * *p_shape->vertex_list.at(3)->position_x);
		vertices[id + 25] = (_start_y + _size_y * *p_shape->vertex_list.at(3)->position_y);

		vertices[id + 26] = *p_shape->vertex_list.at(3)->float_vector.at(0);
		vertices[id + 27] = 0.0f;
		vertices[id + 28] = *p_shape->vertex_list.at(3)->float_vector.at(1);
		vertices[id + 29] = 1.0f;

		vertices[id + 30] = *_g->x;
		vertices[id + 31] = *_g->y2;
	}

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_two_dimension_gradient(float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g, EColor* _color_x, EColor* _color_y)
{
	//.#
	//..
	vertices[id + 0]	= (_start_x + _size_x);
	vertices[id + 1]	= (_start_y + _size_y);

	vertices[id + 2]	= _color_x->red		+ _color_y->red;
	vertices[id + 3]	= _color_x->green	+ _color_y->green;
	vertices[id + 4]	= _color_x->blue	+ _color_y->blue;
	vertices[id + 5]	= 1.0f;

	vertices[id + 6]	= *_g->x2;
	vertices[id + 7]	= *_g->y2;

	//..
	//.#
	vertices[id + 8]	= (_start_x + _size_x);
	vertices[id + 9]	= (_start_y);

	vertices[id + 10]	= _color_x->red		+ _color_y->red		* 0.0f;
	vertices[id + 11]	= _color_x->green	+ _color_y->green	* 0.0f;
	vertices[id + 12]	= _color_x->blue	+ _color_y->blue	* 0.0f;
	vertices[id + 13]	= 1.0f;

	vertices[id + 14]	= *_g->x2;
	vertices[id + 15]	= *_g->y2;

	//..
	//#.
	vertices[id + 16] = (_start_x);
	vertices[id + 17] = (_start_y);

	vertices[id + 18] = 0.0f;
	vertices[id + 19] = 0.0f;
	vertices[id + 20] = 0.0f;
	vertices[id + 21] = 1.0f;

	vertices[id + 22] = *_g->x;
	vertices[id + 23] = *_g->y;

	//#.
	//..
	vertices[id + 24] = (_start_x);
	vertices[id + 25] = (_start_y + _size_y);

	vertices[id + 26] = _color_y->red;
	vertices[id + 27] = _color_y->green;
	vertices[id + 28] = _color_y->blue;
	vertices[id + 29] = 1.0f;

	vertices[id + 30] = *_g->x;
	vertices[id + 31] = *_g->y2;


id += 32;

if (id > batch_force_draw_call)
{
	reinit();
	draw_call();
	reset();
}
}



void Batcher::draw_gabarite(float _x, float _y, EGabarite* _g)
{
	//std::cout << "filled rect" << std::endl;

	//.#
	//..
	vertices[id + 0] = (_x + *_g->size_x);
	vertices[id + 1] = (_y + *_g->size_y);
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	vertices[id + 6] = *_g->x2;
	vertices[id + 7] = *_g->y2;

	//..
	//.#
	vertices[id + 8] = (_x + *_g->size_x);
	vertices[id + 9] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = *_g->x2;
	vertices[id + 15] = *_g->y;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x;
	vertices[id + 23] = *_g->y;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y + *_g->size_y);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = *_g->x;
	vertices[id + 31] = *_g->y2;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_terrain(float _x, float _y, EGabarite* _g)
{
	//std::cout << "filled rect" << std::endl;

	//.#
	//..
	vertices[id + 0] = (_x + *_g->size_x);
	vertices[id + 1] = (_y + *_g->size_y);
	//vertices[id + 2] = 0;

	vertices[id + 2] = *_g->x2;
	vertices[id + 3] = *_g->y2;

	//..
	//.#
	vertices[id + 4] = (_x + *_g->size_x);
	vertices[id + 5] = (_y);
	//vertices[id + 10] = 0;

	vertices[id + 6] = *_g->x2;
	vertices[id + 7] = *_g->y;

	//..
	//#.
	vertices[id + 8] = (_x);
	vertices[id + 9] = (_y);
	//vertices[id + 18] = 0;

	vertices[id + 10] = *_g->x;
	vertices[id + 11] = *_g->y;

	//#.
	//..
	vertices[id + 12] = (_x);
	vertices[id + 13] = (_y + *_g->size_y);
	//vertices[id + 26] = 0;

	vertices[id + 14] = *_g->x;
	vertices[id + 15] = *_g->y2;

	id += 16;

	if (id > 16000)
	{
		reinit();
		draw_call_terrain();
		reset();
	}
}

void Batcher::draw_terrain_with_offset(float _x, float _y, float _left, float _right, float _up, float _down, EGabarite* _g)
{
	//std::cout << "filled rect" << std::endl;

	//.#
	//..
	vertices[id + 0] = (_x + *_g->size_x - (_right + _left) * 4096.0f);
	vertices[id + 1] = (_y + *_g->size_y - (_up + _down) * 4096.0f);
	//vertices[id + 2] = 0;

	vertices[id + 2] = *_g->x2 - _right;
	vertices[id + 3] = *_g->y2 - _up;

	//..
	//.#
	vertices[id + 4] = (_x + *_g->size_x - (_right + _left) * 4096.0f);
	vertices[id + 5] = (_y);
	//vertices[id + 10] = 0;

	vertices[id + 6] = *_g->x2 - _right;
	vertices[id + 7] = *_g->y + _down;

	//..
	//#.
	vertices[id + 8] = (_x);
	vertices[id + 9] = (_y);
	//vertices[id + 18] = 0;

	vertices[id + 10] = *_g->x + _left;
	vertices[id + 11] = *_g->y + _down;

	//#.
	//..
	vertices[id + 12] = (_x);
	vertices[id + 13] = (_y + *_g->size_y - (_up + _down) * 4096.0f);
	//vertices[id + 26] = 0;

	vertices[id + 14] = *_g->x + _left;
	vertices[id + 15] = *_g->y2 - _up;

	id += 16;

	if (id > 16000)
	{
		reinit();
		draw_call_terrain();
		reset();
	}
}

void Batcher::draw_gabarite_skew(float _x, float _y, float _collision_x, float _collision_y, float _tall, EGabarite* _g, float _bottom_tall)
{
	//std::cout << "filled rect" << std::endl;

	//.#
	//..
	vertices[id + 0] = (_x + _tall * (1.0f - skew_factor) * 1.35f);
	vertices[id + 1] = (_y + _collision_y + _bottom_tall * skew_factor);
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a / (1.0f + _tall / 100.0f) * 0.0f;

	vertices[id + 6] = *_g->x2;
	vertices[id + 7] = *_g->y2;

	//..
	//.#
	vertices[id + 8] = (_x + _bottom_tall * (1.0f - skew_factor) * 1.35f);
	vertices[id + 9] = _y + _bottom_tall * skew_factor;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a / (1.0f + _bottom_tall / 100.0f) * 0.0f;

	vertices[id + 14] = *_g->x2;
	vertices[id + 15] = *_g->y;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x;
	vertices[id + 23] = *_g->y;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = _y + _collision_y;
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = *_g->x;
	vertices[id + 31] = *_g->y2;

	id += 32;

	///////////////////////////////////////////////////////////////////////////////

	//.#
	//..
	vertices[id + 0] = _x + (_tall) * (1.0f - skew_factor) * 1.35f;
	vertices[id + 1] = _y + _collision_y + _bottom_tall * skew_factor;
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a / (1.0f + _tall / 100.0f) * 0.0f;

	vertices[id + 6] = *_g->x2;
	vertices[id + 7] = *_g->y2;

	//..
	//.#
	vertices[id + 8] = _x;
	vertices[id + 9] = _y + _collision_y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = *_g->x2;
	vertices[id + 15] = *_g->y;

	//..
	//#.
	vertices[id + 16] = _x - _collision_x;
	vertices[id + 17] = _y + _collision_y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x;
	vertices[id + 23] = *_g->y;

	//#.
	//..
	vertices[id + 24] = _x - _collision_x + (_bottom_tall) * (1.0f - skew_factor) * 1.35f;
	vertices[id + 25] = (_y + _collision_y + _bottom_tall * skew_factor);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a / (1.0f + _bottom_tall / 100.0f) * 0.0f;

	vertices[id + 30] = *_g->x;
	vertices[id + 31] = *_g->y2;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_gabarite_ark_shadow(float _x, float _y, EGabarite* _g)
{
	//std::cout << "filled rect" << std::endl;

//.#
//..

//*------------*--*
//*--*------------#
	vertices[id + 0] = (_x + *_g->size_x + (1.0f - skew_factor) * 300.0f);
	vertices[id + 1] = (_y + skew_factor * 300.0f);
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	vertices[id + 6] = *_g->x2;
	vertices[id + 7] = *_g->y;

	//..
	//.#

	//*------------*--*
	//*--#------------*
	vertices[id + 8] = (_x + *_g->size_x);
	vertices[id + 9] = _y + *_g->size_x * skew_factor;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = *_g->x2;
	vertices[id + 15] = *_g->y;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x;
	vertices[id + 23] = *_g->y;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y + *_g->size_y);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = *_g->x;
	vertices[id + 31] = *_g->y2;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_gabarite_shadowmap(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z)
{
	//std::cout << "filled rect" << std::endl;

	//.#
	//..
	vertices[id + 0] = (_x + *_g->size_x);
	vertices[id + 1] = (_y + *_g->size_y);
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	vertices[id + 6] = *_g->x2;
	vertices[id + 7] = *_g->y2;

	vertices[id + 8] = (_x + *_g->size_x) * zoom / shadow_FBO_w;
	vertices[id + 9] = _z;

	vertices[id + 10] = *_supermap->x2;
	vertices[id + 11] = *_supermap->y2;

	vertices[id + 12] = (_x + *_g->size_x) / 12000.0f;
	vertices[id + 13] = (_y - 4.0f) / 12000.0f;

	vertices[id + 14] = (_y - _z + _h) * zoom / shadow_FBO_h;

	//..
	//.#
	vertices[id + 15] = (_x + *_g->size_x);
	vertices[id + 16] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 17] = batch_color_r;
	vertices[id + 18] = batch_color_g;
	vertices[id + 19] = batch_color_b;
	vertices[id + 20] = batch_color_a;

	vertices[id + 21] = *_g->x2;
	vertices[id + 22] = *_g->y;

	vertices[id + 23] = (_x + *_g->size_x) * zoom / shadow_FBO_w;
	vertices[id + 24] = _z;

	vertices[id + 25] = *_supermap->x2;
	vertices[id + 26] = *_supermap->y;

	vertices[id + 27] = (_x + *_g->size_x) / 12000.0f;
	vertices[id + 28] = (_y - 40.0f) / 12000.0f;

	vertices[id + 29] = (_y + 0.0f - _z) * zoom / shadow_FBO_h;

	//..
	//#.
	vertices[id + 30] = _x;
	vertices[id + 31] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 32] = batch_color_r;
	vertices[id + 33] = batch_color_g;
	vertices[id + 34] = batch_color_b;
	vertices[id + 35] = batch_color_a;

	vertices[id + 36] = *_g->x;
	vertices[id + 37] = *_g->y;

	vertices[id + 38] = (_x)*zoom / shadow_FBO_w;
	vertices[id + 39] = _z;

	vertices[id + 40] = *_supermap->x;
	vertices[id + 41] = *_supermap->y;

	vertices[id + 42] = (_x) / 12000.0f;
	vertices[id + 43] = (_y - 40.0f) / 12000.0f;

	vertices[id + 44] = (_y + 0.0f - _z) * zoom / shadow_FBO_h;

	//#.
	//..
	vertices[id + 45] = _x;
	vertices[id + 46] = (_y + *_g->size_y);
	//vertices[id + 26] = 0;

	vertices[id + 47] = batch_color_r;
	vertices[id + 48] = batch_color_g;
	vertices[id + 49] = batch_color_b;
	vertices[id + 50] = batch_color_a;

	vertices[id + 51] = *_g->x;
	vertices[id + 52] = *_g->y2;

	vertices[id + 53] = (_x)*zoom / shadow_FBO_w;
	vertices[id + 54] = _z;

	vertices[id + 55] = *_supermap->x;
	vertices[id + 56] = *_supermap->y2;

	vertices[id + 57] = (_x) / 12000.0f;
	vertices[id + 58] = (_y - 4.0f) / 12000.0f;

	vertices[id + 59] = (_y - _z + _h) * zoom / shadow_FBO_h;

	id += 60;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call_shadowmap();
		reset();
	}
}

void Batcher::draw_gabarite_shadowmap_fragment(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z, float _fx, float _fy)
{
	//_fx = 0.5f;
	//_fy = 0.5f;
	//std::cout << "filled rect" << std::endl;

	//.#
	//..

	//COORD	[0]
	vertices[id + 0] = (_x + *_g->size_x * _fx);
	vertices[id + 1] = (_y + *_g->size_y * _fy);

	//COLOR	[1]
	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	//MAIN TEXTURE UV COORD	[2]
	vertices[id + 6] = *_g->x + *_g->uv_size_x * _fx;
	vertices[id + 7] = *_g->y + *_g->uv_size_y * _fy;

	//HALT COORD	[3]
	vertices[id + 8] = (_x + *_g->size_x * _fx) * zoom / shadow_FBO_w;
	vertices[id + 9] = *_g->size_y * _fy + _z;

	//SUPERMAP TEXTURE UV COORD	[4]
	vertices[id + 10] = *_supermap->x + *_supermap->uv_size_x * _fx;
	vertices[id + 11] = *_supermap->y + *_supermap->uv_size_y * _fy;

	//LIGHTMAP UV COORD	[5]
	vertices[id + 12] = (_x + *_g->size_x) / 12000.0f;
	vertices[id + 13] = (_y + *_g->size_y * 0.0f - _z) / 12000.0f;

	//SHADOW BASELINE	[6]
	vertices[id + 14] = (_y - _z) * zoom / shadow_FBO_h;

	//..
	//.#

	//COORD
	vertices[id + 15] = (_x + *_g->size_x * _fx);
	vertices[id + 16] = _y;
	//vertices[id + 10] = 0;

	//COLOR
	vertices[id + 17] = batch_color_r;
	vertices[id + 18] = batch_color_g;
	vertices[id + 19] = batch_color_b;
	vertices[id + 20] = batch_color_a;

	//MAIN TEXTURE UV COORD
	vertices[id + 21] = *_g->x + *_g->uv_size_x * _fx;
	vertices[id + 22] = *_g->y;

	//HALT COORD
	vertices[id + 23] = (_x + *_g->size_x * _fx) * zoom / shadow_FBO_w;
	vertices[id + 24] = _z;

	//SUPERMAP TEXTURE UV COORD
	vertices[id + 25] = *_supermap->x + *_supermap->uv_size_x * _fx;
	vertices[id + 26] = *_supermap->y;

	//LIGHTMAP UV COORD
	vertices[id + 27] = (_x + *_g->size_x) / 12000.0f;
	vertices[id + 28] = (_y - 00.0f - _z) / 12000.0f;

	//SHADOW BASELINE
	vertices[id + 29] = (_y - _z) * zoom / shadow_FBO_h;

	//..
	//#.

	//COORD
	vertices[id + 30] = _x;
	vertices[id + 31] = _y;
	//vertices[id + 18] = 0;

	//COLOR
	vertices[id + 32] = batch_color_r;
	vertices[id + 33] = batch_color_g;
	vertices[id + 34] = batch_color_b;
	vertices[id + 35] = batch_color_a;

	//MAIN TEXTURE UV COORD
	vertices[id + 36] = *_g->x;
	vertices[id + 37] = *_g->y;

	//HALT COORD
	vertices[id + 38] = _x * zoom / shadow_FBO_w;
	vertices[id + 39] = _z;

	//SUPERMAP TEXTURE UV COORD
	vertices[id + 40] = *_supermap->x;
	vertices[id + 41] = *_supermap->y;

	//LIGHTMAP UV COORD
	vertices[id + 42] = (_x) / 12000.0f;
	vertices[id + 43] = (_y - 00.0f - _z) / 12000.0f;

	//SHADOW BASELINE
	vertices[id + 44] = (_y - _z) * zoom / shadow_FBO_h;

	//#.
	//..

	//COORD
	vertices[id + 45] = _x;
	vertices[id + 46] = (_y + *_g->size_y * _fy);
	//vertices[id + 26] = 0;

	//COLOR
	vertices[id + 47] = batch_color_r;
	vertices[id + 48] = batch_color_g;
	vertices[id + 49] = batch_color_b;
	vertices[id + 50] = batch_color_a;

	//MAIN TEXTURE UV COORD
	vertices[id + 51] = *_g->x;
	vertices[id + 52] = *_g->y + *_g->uv_size_y * _fy;

	//HALT COORD
	vertices[id + 53] = (_x)*zoom / shadow_FBO_w;
	vertices[id + 54] = *_g->size_y * _fy + _z;

	//SUPERMAP TEXTURE UV COORD
	vertices[id + 55] = *_supermap->x;
	vertices[id + 56] = *_supermap->y + *_supermap->uv_size_y * _fy;

	//LIGHTMAP UV COORD
	vertices[id + 57] = (_x) / 12000.0f;
	vertices[id + 58] = (_y + *_g->size_y * 0.0f - 00.0f - _z) / 12000.0f;

	//SHADOW BASELINE
	vertices[id + 59] = (_y - _z) * zoom / shadow_FBO_h;

	id += 60;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call_shadowmap();
		reset();
	}
}

void Batcher::draw_gabarite_shadowmap_fragment_mirrored(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z, float _fx, float _fy)
{
	//_fx = 0.5f;
	//_fy = 0.5f;
	//std::cout << "filled rect" << std::endl;

	//.#
	//..

	//COORD	[0]
	vertices[id + 0] = _x;
	vertices[id + 1] = (_y + *_g->size_y * _fy);

	//COLOR	[1]
	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	//MAIN TEXTURE UV COORD	[2]
	vertices[id + 6] = *_g->x + *_g->uv_size_x * _fx;
	vertices[id + 7] = *_g->y + *_g->uv_size_y * _fy;

	//HALT COORD	[3]
	vertices[id + 8] = (_x)*zoom / shadow_FBO_w;
	vertices[id + 9] = *_g->size_y * _fy + _z;

	//SUPERMAP TEXTURE UV COORD	[4]
	vertices[id + 10] = *_supermap->x + *_supermap->uv_size_x * _fx;
	vertices[id + 11] = *_supermap->y + *_supermap->uv_size_y * _fy;

	//LIGHTMAP UV COORD	[5]
	vertices[id + 12] = (_x) / 12000.0f;
	vertices[id + 13] = (_y + *_g->size_y * 0.0f - _z) / 12000.0f;

	//SHADOW BASELINE	[6]
	vertices[id + 14] = (_y - _z) * zoom / shadow_FBO_h;

	//..
	//.#

	//COORD
	vertices[id + 15] = _x;
	vertices[id + 16] = _y;
	//vertices[id + 10] = 0;

	//COLOR
	vertices[id + 17] = batch_color_r;
	vertices[id + 18] = batch_color_g;
	vertices[id + 19] = batch_color_b;
	vertices[id + 20] = batch_color_a;

	//MAIN TEXTURE UV COORD
	vertices[id + 21] = *_g->x + *_g->uv_size_x * _fx;
	vertices[id + 22] = *_g->y;

	//HALT COORD
	vertices[id + 23] = _x * zoom / shadow_FBO_w;
	vertices[id + 24] = _z;

	//SUPERMAP TEXTURE UV COORD
	vertices[id + 25] = *_supermap->x + *_supermap->uv_size_x * _fx;
	vertices[id + 26] = *_supermap->y;

	//LIGHTMAP UV COORD
	vertices[id + 27] = (_x) / 12000.0f;
	vertices[id + 28] = (_y - 00.0f - _z) / 12000.0f;

	//SHADOW BASELINE
	vertices[id + 29] = (_y - _z) * zoom / shadow_FBO_h;

	//..
	//#.

	//COORD
	vertices[id + 30] = (_x + *_g->size_x * _fx);
	vertices[id + 31] = _y;
	//vertices[id + 18] = 0;

	//COLOR
	vertices[id + 32] = batch_color_r;
	vertices[id + 33] = batch_color_g;
	vertices[id + 34] = batch_color_b;
	vertices[id + 35] = batch_color_a;

	//MAIN TEXTURE UV COORD
	vertices[id + 36] = *_g->x;
	vertices[id + 37] = *_g->y;

	//HALT COORD
	vertices[id + 38] = (_x + *_g->size_x * _fx) * zoom / shadow_FBO_w;
	vertices[id + 39] = _z;

	//SUPERMAP TEXTURE UV COORD
	vertices[id + 40] = *_supermap->x;
	vertices[id + 41] = *_supermap->y;

	//LIGHTMAP UV COORD
	vertices[id + 42] = (_x + *_g->size_x) / 12000.0f;
	vertices[id + 43] = (_y - 00.0f - _z) / 12000.0f;

	//SHADOW BASELINE
	vertices[id + 44] = (_y - _z) * zoom / shadow_FBO_h;

	//#.
	//..

	//COORD
	vertices[id + 45] = (_x + *_g->size_x * _fx);
	vertices[id + 46] = (_y + *_g->size_y * _fy);
	//vertices[id + 26] = 0;

	//COLOR
	vertices[id + 47] = batch_color_r;
	vertices[id + 48] = batch_color_g;
	vertices[id + 49] = batch_color_b;
	vertices[id + 50] = batch_color_a;

	//MAIN TEXTURE UV COORD
	vertices[id + 51] = *_g->x;
	vertices[id + 52] = *_g->y + *_g->uv_size_y * _fy;

	//HALT COORD
	vertices[id + 53] = (_x + *_g->size_x * _fx) * zoom / shadow_FBO_w;
	vertices[id + 54] = *_g->size_y * _fy + _z;

	//SUPERMAP TEXTURE UV COORD
	vertices[id + 55] = *_supermap->x;
	vertices[id + 56] = *_supermap->y + *_supermap->uv_size_y * _fy;

	//LIGHTMAP UV COORD
	vertices[id + 57] = (_x + *_g->size_x) / 12000.0f;
	vertices[id + 58] = (_y + *_g->size_y * 0.0f - 00.0f - _z) / 12000.0f;

	//SHADOW BASELINE
	vertices[id + 59] = (_y - _z) * zoom / shadow_FBO_h;

	id += 60;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call_shadowmap();
		reset();
	}
}

void Batcher::draw_gabarite_with_offset(float _x, float _y, float _w, float _h, float _offset_x, float _offset_y, float _offset_end_x, float _offset_end_y, EGabarite* _g)
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

	vertices[id + 6] = *_g->x + _offset_end_x;
	vertices[id + 7] = *_g->y + _offset_end_y;

	//..
	//.#
	vertices[id + 8] = (_x + _w);
	vertices[id + 9] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = *_g->x + _offset_end_x;
	vertices[id + 15] = *_g->y + _offset_y;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x + _offset_x;
	vertices[id + 23] = *_g->y + _offset_y;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y + _h);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = *_g->x + _offset_x;
	vertices[id + 31] = *_g->y + _offset_end_y;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::fill_indices()
{
	indices[indices_id + 0] = indices_order + 0;
	indices[indices_id + 1] = indices_order + 1;
	indices[indices_id + 2] = indices_order + 3;

	indices[indices_id + 3] = indices_order + 1;
	indices[indices_id + 4] = indices_order + 2;
	indices[indices_id + 5] = indices_order + 3;

	//std::

	indices_id += 6;
	indices_order += 4;
}

void Batcher::setcolor_255(int _r, int _g, int _b, int _a)
{
	setcolor(_r / 255.0f, _g / 255.0f, _b / 255.0f, _a / 100.0f);
}

Batcher::~Batcher()
{
}

void Batcher::reinit()
{
	if (id > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * id, vertices, GL_DYNAMIC_DRAW);
	}
}

void Batcher::draw_call()
{
	//logger_param("Vertices data count:", id);
	//reinit();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6 * (id / 32), GL_UNSIGNED_INT, 0);
	//std::cout << blue << "vertices: " << red << id << std::endl<<white;
}

void Batcher::draw_call_terrain()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6 * (id / 16), GL_UNSIGNED_INT, 0);
}

void Batcher::draw_call_shadowmap()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6 * (id / 60), GL_UNSIGNED_INT, 0);
}

void Batcher::draw_call_PBR()
{
	if (id > 0)
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6 * id / 52, GL_UNSIGNED_INT, 0);
	}
}

void Batcher::reset()
{
	id = 0;
	indices_id = 0;
	indices_order = 0;
}

void Batcher::setcolor(EColor* _color)
{
	batch_color_r = _color->red;
	batch_color_g = _color->green;
	batch_color_b = _color->blue;
	batch_color_a = _color->alpha;
}

void Batcher::setcolor(EColorCollection* _color)
{
	batch_color_r = _color->color_red;
	batch_color_g = _color->color_green;
	batch_color_b = _color->color_blue;
	batch_color_a = _color->color_alpha;
}

void Batcher::setcolor_lum(EColorCollection* _color, float _lum)
{
	batch_color_r = _color->color_red * _lum;
	batch_color_g = _color->color_green * _lum;
	batch_color_b = _color->color_blue * _lum;
	batch_color_a = _color->color_alpha;
}

void Batcher::setcolor_alpha(EColorCollection* _color, float _a)
{
	batch_color_r = _color->color_red;
	batch_color_g = _color->color_green;
	batch_color_b = _color->color_blue;
	batch_color_a = _a;
}

void Batcher::setcolor_lumalpha(EColorCollection* _color, float _lum, float _a)
{
	batch_color_r = _color->color_red * _lum;
	batch_color_g = _color->color_green * _lum;
	batch_color_b = _color->color_blue * _lum;
	batch_color_a = _a;
}

void Batcher::draw_rama(float _x, float _y, float _sx, float _sy, float _t, EGabarite* _g)
{
	draw_gabarite(_x - _t, _y - _t, _t, _sy + _t * 2.0f, _g);//left
	draw_gabarite(_x + _sx, _y - _t, _t, _sy + _t * 2.0f, _g);//right

	draw_gabarite(_x - _t, _y + _sy, _sx + _t * 2.0f, _t, _g);//up
	draw_gabarite(_x - _t, _y - _t, _sx + _t * 2.0f, _t, _g);//up
}

void Batcher::draw_rama(float _x, float _y, float _sx, float _sy, float _t)
{
	draw_rect(_x - _t, _y - _t, _t, _sy + _t * 2.0f);//left
	draw_rect(_x + _sx, _y - _t, _t, _sy + _t * 2.0f);//right

	draw_rect(_x - _t, _y + _sy, _sx + _t * 2.0f, _t);//up
	draw_rect(_x - _t, _y - _t, _sx + _t * 2.0f, _t);//up
}

void Batcher::draw_rect_gabarite_custom_uv(float _x, float _y, float _w, float _h, EGabarite* _g, float _sx, float _sy, float _ex, float _ey)
{
	//.#
	//..
	vertices[id + 0] = (_x + _w);
	vertices[id + 1] = (_y + _h);
	//vertices[id + 2] = 0;

	vertices[id + 2] = batch_color_r;
	vertices[id + 3] = batch_color_g;
	vertices[id + 4] = batch_color_b;
	vertices[id + 5] = batch_color_a;

	vertices[id + 6] = *_g->x + _ex / 4096.0f;
	vertices[id + 7] = *_g->y + _ey / 4096.0f;

	//..
	//.#
	vertices[id + 8] = (_x + _w);
	vertices[id + 9] = _y;
	//vertices[id + 10] = 0;

	vertices[id + 10] = batch_color_r;
	vertices[id + 11] = batch_color_g;
	vertices[id + 12] = batch_color_b;
	vertices[id + 13] = batch_color_a;

	vertices[id + 14] = *_g->x + _ex / 4096.0f;
	vertices[id + 15] = *_g->y + _sy / 4096.0f;

	//..
	//#.
	vertices[id + 16] = _x;
	vertices[id + 17] = _y;
	//vertices[id + 18] = 0;

	vertices[id + 18] = batch_color_r;
	vertices[id + 19] = batch_color_g;
	vertices[id + 20] = batch_color_b;
	vertices[id + 21] = batch_color_a;

	vertices[id + 22] = *_g->x + _sx / 4096.0f;
	vertices[id + 23] = *_g->y + _sy / 4096.0f;

	//#.
	//..
	vertices[id + 24] = _x;
	vertices[id + 25] = (_y + _h);
	//vertices[id + 26] = 0;

	vertices[id + 26] = batch_color_r;
	vertices[id + 27] = batch_color_g;
	vertices[id + 28] = batch_color_b;
	vertices[id + 29] = batch_color_a;

	vertices[id + 30] = *_g->x + _sx / 4096.0f;
	vertices[id + 31] = *_g->y + _ey / 4096.0f;

	id += 32;

	if (id > batch_force_draw_call)
	{
		reinit();
		draw_call();
		reset();
	}
}

void Batcher::draw_simple_rect(float _x, float _y, float _size_x, float _size_y)
{
	//draw_rect_with_uv(_x, _y, _size_x, _size_y, DefaultGabarite::gabarite_white);
}

void Batcher::force_draw_call()
{
	
	reinit();
	draw_call();
	reset();
}

void Batcher::force_draw_call_terrain()
{
	reinit();
	draw_call_terrain();
	reset();
}

void Batcher::force_draw_call_shadowmap()
{
	reinit();
	draw_call_shadowmap();
	reset();
}

void Batcher::force_draw_call_PBR()
{
	//std::cout << "PBR batched id: " << std::to_string(id) << std::endl;
	if (id > 0)
	{
		reinit();
		draw_call_PBR();
		reset();
	}

}

void Batcher::set_interpolated_color(EColorCollection* _a, EColorCollection* _b, float _value)
{
	batch_color_r = _a->color_red * _value + _b->color_red * (1.0f - _value);
	batch_color_g = _a->color_green * _value + _b->color_green * (1.0f - _value);
	batch_color_b = _a->color_blue * _value + _b->color_blue * (1.0f - _value);

	batch_color_a = _a->color_alpha * _value + _b->color_alpha * (1.0f - _value);
}

Batcher::EPolygonMassive::EPolygonMassive()
{
}

Batcher::EPolygonMassive::~EPolygonMassive()
{
}

Batcher::EPolygonShape::EPolygonShape()
{
}

Batcher::EPolygonShape::~EPolygonShape()
{
}

Batcher::EPolygonVertex::EPolygonVertex()
{
}

Batcher::EPolygonVertex::~EPolygonVertex()
{
}
