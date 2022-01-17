#pragma once
#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif

/**/
#ifndef	_DATA_CORE_ALREADY_LINKED_
#define	_DATA_CORE_ALREADY_LINKED_
#include "EDataCore.h"
#endif
/**/

#include <vector>



enum AlignSide
{
	AS_LEFT,
	AS_MID,
	AS_RIGHT
};


class ERegionGabarite;
class ETextureGabarite;
class ESpriteLayer;
class ETextureAtlas;

/*


*/


enum FONT_ENUM
{
		FE_DEFAULT,
		FE_DOT
};



class EFont
{
public:


	float UV_start_x[512];
	float UV_start_y[512];

	float UV_size_x[512];
	float UV_size_y[512];

	float offset_x[512];
	float offset_y[512];

	float advance[512];

	float size_x_in_pixels[512];
	float size_y_in_pixels[512];

	std::string name;

	EFont(std::string _name, ETextureGabarite* _g, ETextureAtlas* _atlas, bool _not_cyrrilic);

	float get_float_from_sub_data(std::string _s);
	int get_int_from_sub_data(std::string _s);

	void load_font_littera(std::string _path);

	static std::vector<EFont*> font_list;

	bool is_not_cyrrilic;

	bool align_only_once = false;
	int align_prev = AlignSide::AS_LEFT;

	ETextureGabarite* gabarite = NULL;

	bool compare_with_key(std::string _data, std::string _key);

	ESpriteLayer* sprite_layer;

	ETextureAtlas* texture_atlas;
};



class ETextArea
{
public:
	ETextArea();
	~ETextArea();

	bool* error = new bool(false);

	float* color = new float[4]{1.0f, 1.0f, 1.0f, 1.0f};
	float* font_scale = new float(1.0f);
	EFont* font;

	float* down_offset = new float(20.0f);

	ERegionGabarite* region_gabarite;

	std::string* stored_text = new std::string("");

	std::vector<std::string*> row;
	int* row_count = new int (0);

	void generate_rows();
	void generate_text();
	void set_font(EFont* _font);


	ESpriteLayer* sprite_layer;
};


