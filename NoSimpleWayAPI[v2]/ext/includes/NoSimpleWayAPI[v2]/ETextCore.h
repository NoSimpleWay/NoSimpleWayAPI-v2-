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


class EFontGlyph;

enum AlignSide
{
	AS_LEFT,
	AS_MID,
	AS_RIGHT,
	AS_DOWN
};


class ERegionGabarite;

class ETextureGabarite;
class ESpriteLayer;
class ETextureAtlas;

class EClickableRegion;

class ETextArea;

/*


*/


enum FONT_ENUM
{
		FE_DEFAULT,
		FE_DOT
};


namespace NS_FONT_UTILS
{
	extern ETextArea* active_text_area;
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
	EFont* font = nullptr;

	float* down_offset = new float(20.0f);

	ERegionGabarite* region_gabarite;

	std::string* stored_text = new std::string("");

	std::vector<std::string*> row;
	int* row_count = new int (0);

	bool* translate_region_gabarite = new bool (false);

	void generate_rows();
	void generate_text();
	void set_font(EFont* _font);
	float get_row_width(std::string* _row);

	void translate(float _x, float _y);

	EClickableRegion* master_clickable_region;

	//int* align_size_x = new int(AlignSide::AS_LEFT);
	//int* align_size_y = new int(AlignSide::AS_DOWN);


	//aligns
	float* offset_by_gabarite_size_x = new float(0.5f);
	float* offset_by_gabarite_size_y = new float(0.0f);

	float* offset_by_text_size_x = new float(0.5f);
	float* offset_by_text_size_y = new float(0.0f);
	//

	void update(float _d);
	void draw();


	ESpriteLayer* sprite_layer;
	///
	std::vector<EFontGlyph*> font_glyph_list;

	int* selected_glyph_position = new int (0);
	bool* flash_line_active = new bool(false);
	float* flash_line_cooldown = new float(0.0f);
	

	//bool* selected_left_side = new bool(false);
	float* jump_cooldown = new float(0.0f);

	bool* text_area_active = new bool(false);

	float* border_offset = new float(5.0f);

	//static 
};

class EFontGlyph
{
public:
	EFontGlyph(char _sym, float _pos_x, float _pos_y, float _size_x, float _size_y);
	~EFontGlyph();

	float* world_position_x = new float (0.0f);
	float* world_position_y = new float (0.0f);

	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);

	char* sym = new char(0);
	int* row_id = new int(0);

	int* storer_text_sym_id = new int(0);

	bool* is_first_symbol = new bool (false);
	bool* is_last_symbol = new bool (false);
	bool* is_empty = new bool(false);

	
};


