#pragma once
//#include
#include "EGraphicCore.h"
#include <iostream>

class ETextureAtlas
{
public:
	unsigned int framebuffer;
	unsigned int colorbuffer;
	unsigned int rbo;

	float size_x;
	float size_y;

	bool free_space[1024][1024];

	bool can_place_here(int _x, int _y, int _w, int _h);

	static EGabarite* put_texture_to_atlas(std::string _name, ETextureAtlas* _ta);
	static void draw_to_this_FBO(ETextureAtlas* _ta, ETextureAtlas* _ta2);
	static void active_this_texture_atlas(ETextureAtlas* _ta, ETextureAtlas* _ta2, ETextureAtlas* _ta3);
	static void set_this_FBO_as_active(ETextureAtlas* _ta);

	ETextureAtlas(int _x, int _y, int _color_depth = GL_RGBA, int _byte_mode = GL_UNSIGNED_BYTE);
	~ETextureAtlas();

	static EGabarite* get_supermap_from_regular_texture_path(std::string _s, ETextureAtlas* _a);
	static EGabarite* get_normal_gloss_map_from_regular_texture_path(std::string _s, ETextureAtlas* _a);
};