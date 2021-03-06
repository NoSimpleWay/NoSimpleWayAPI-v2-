#pragma once

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

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

class EClickableArea;

class ETextArea;

/*


*/


enum FONT_ENUM
{
		FE_DEFAULT,
		FE_BAHN
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


enum BorderSide
{
	LEFT,
	RIGHT,
	BOTTOM,
	UP,
	_LAST_ELEMENT
};

enum TextColorArray
{
	FREE,
	WHITE,
	GRAY,
	BLACK,
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	CYAN,
	BLUE,
	MAGENTA
};

class ETextArea
{
public:
	ETextArea();
	ETextArea(EClickableArea* _region, EFont* _font, std::string _text);
	~ETextArea();

	bool* error = new bool(false);

	float* color = new float[4]{0.9f, 0.5f, 0.25f, 1.0f};
	float* stored_color = new float[4]{1.0f, 1.0f, 1.0f, 1.0f};
	unsigned int* selected_color_table = new unsigned int(TextColorArray::FREE);
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

	void translate(float _x, float _y, float _z, bool _translate_local_coordinate);

	float* offset_border = new float[BorderSide::_LAST_ELEMENT] {0.0f};

	EClickableArea* parent_clickable_region;
	EntityButton* parent_entity;

	//int* align_size_x = new int(AlignSide::AS_LEFT);
	//int* align_size_y = new int(AlignSide::AS_DOWN);


	//aligns
	float* offset_by_gabarite_size_x = new float(0.5f);
	float* offset_by_gabarite_size_y = new float(0.0f);

	float* offset_by_text_size_x = new float(-0.5f);
	float* offset_by_text_size_y = new float(0.0f);
	//

	void update(float _d);
	void draw();


	bool* can_be_edited = new bool(true);

	ESpriteLayer* sprite_layer;
	///
	std::vector<EFontGlyph*> font_glyph_list;

	int* selected_glyph_position = new int (0);
	bool* flash_line_active = new bool(false);
	float* flash_line_cooldown = new float(0.0f);
	

	//bool* selected_left_side = new bool(false);
	float* jump_cooldown = new float(0.0f);

	bool* text_area_active = new bool(false);

	float* _unused_border_offset = new float(5.0f);

	static void set_region(ETextArea* _text_area, ERegionGabarite* _region_gabarite);
	static ETextArea* create_base_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text);
	static ETextArea* create_centered_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text);
	static ETextArea* create_centered_to_right_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text);
	static ETextArea* create_centered_to_left_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text);

	void change_text(std::string _text);

	bool can_get_access_to_group_style();

	std::vector<text_actions_pointer> action_on_change_text;

	EButtonGroup* get_root_group();
	//static 
};

class EFontGlyph
{
public:
	EFontGlyph(char _sym, float _pos_x, float _pos_y, float _size_x, float _size_y);
	~EFontGlyph();

	float world_position_x = 0.0f;
	float world_position_y = 0.0f;

	float size_x = 0.0f;
	float size_y = 0.0f;

	char sym = 0;
	int row_id = 0;

	int storer_text_sym_id = 0;

	bool is_first_symbol	= false;
	bool is_last_symbol		= false;
	bool is_empty			= false;

	
};


