#pragma once

#ifndef _ELOCALISATION_ALREADY_LINKED_
#define _ELOCALISATION_ALREADY_LINKED_

#include <string>
#define NSW_localisation_EN 0
#define NSW_localisation_RU 1
#define NSW_localisation_placeholder_2 2
#define NSW_localisation_placeholder_3 3
#define NSW_localisation_placeholder_4 4
#define NSW_localisation_placeholder_5 5
#define NSW_localisation_placeholder_6 6

constexpr unsigned int NSW_languages_count = 2;
class ELocalisationText
{
public:
	ELocalisationText();
	std::string base_name = "";
	std::string stored_key = "";

	std::string localisations[NSW_languages_count] = { "" };

	static int active_localisation;
	static ELocalisationText get_localisation_by_key(std::string _key);
	static ELocalisationText empty_localisation;
	static ELocalisationText generate_localization_with_base_name(std::string _text);
	static ELocalisationText generate_localization_only_languages(std::string _text);

	void add_localisation_text_from_another(std::string _prefix, ELocalisationText* _ltext);

	void add_text_to_all_languages(std::string _text);
};
#endif






#include <vector>

#ifndef _E_TEXT_CORE_ALREADY_LINKED_
#define _E_TEXT_CORE_ALREADY_LINKED_
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

constexpr size_t EFont_array_dim = 65536u;


//0 - EN
//1 - RU



class EFont
{
public:


	float UV_start_x[EFont_array_dim];
	float UV_start_y[EFont_array_dim];

	float UV_size_x[EFont_array_dim];
	float UV_size_y[EFont_array_dim];

	float offset_x[EFont_array_dim];
	float offset_y[EFont_array_dim];

	float advance[EFont_array_dim];

	float size_x_in_pixels[EFont_array_dim];
	float size_y_in_pixels[EFont_array_dim];

	int lineheight = 15;
	int base = 10;

	std::string localised_name;


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



#include "Helpers.h"
class ETextArea
{
public:
	ETextArea();



	ETextArea(EClickableArea* _region, EFont* _font, std::string _text);
	/*------>*/ETextArea(ERegionGabarite* _region, EFont* _font, ELocalisationText _ltext);

	~ETextArea();

	//bool* error = new bool(false);

	HSVRGBAColor color;
	HSVRGBAColor stored_color;

	//unsigned int* selected_color_table = new unsigned int(TextColorArray::FREE);
	float font_scale = 1.0f;
	EFont* font = nullptr;

	float down_offset = 20.0f;

	ERegionGabarite* region_gabarite;

	std::string			original_text = "";
	std::string			stored_text = "";

	ELocalisationText	localisation_text;
	ELocalisationText	gray_text;
	bool				indicate_gray_text = false;
	bool				non_original_region = false;
	bool				autoerase_text = false;
	bool				forbide_new_line = false;
	bool				forbide_outbounding = false;

	std::vector<std::string*> row;
	int row_count = 0;

	bool translate_region_gabarite = false;

	void change_text(std::string _text);
	void update_localisation();

	void generate_rows();
	void generate_text();

	std::string get_stored_text();

	void set_font(EFont* _font);
	float get_row_width(std::string* _row);
	float get_text_width(std::string* _text);

	void translate(float _x, float _y, float _z, bool _translate_local_coordinate);

	float offset_border[BorderSide::_LAST_ELEMENT]{ 0.0f };

	EClickableArea* parent_clickable_region;
	EntityButton* parent_entity_for_text_area;
	EButtonGroup* parent_group;

	//int* align_size_x = new int(AlignSide::AS_LEFT);
	//int* align_size_y = new int(AlignSide::AS_DOWN);


	//aligns
	float offset_by_gabarite_size_x = 0.5f;
	float offset_by_gabarite_size_y = 0.0f;

	float offset_by_text_size_x		= -0.5f;
	float offset_by_text_size_y		= 0.0f;

	float offset_by_constant_x		= 0.0f;
	float offset_by_constant_y		= 0.0f;
	//
	bool outclick_protection = false;

	void deactivate_this_text_area();

	void update(float _d);
	bool is_overlapped_by_mouse();
	void activate_this_text_area();
	void draw();

	void text_area_set_active_and_select_glyph();


	bool can_be_edited = true;
	bool can_change_localisation = true;
	bool forcibly_create_glyph = false;
	bool text_have_background = false;

	ESpriteLayer* sprite_layer;
	///
	std::vector<EFontGlyph*> font_glyph_list;

	int selected_glyph_position = (0);
	bool flash_line_active = false;
	float flash_line_cooldown = 0.0f;


	//bool* selected_left_side = new bool(false);
	float jump_cooldown = 0.0f;

	bool text_area_active = false;

	float _unused_border_offset = 5.0f;

	static void set_region(ETextArea* _text_area, ERegionGabarite* _region_gabarite);
	static ETextArea* create_base_text_area(EClickableArea* _region_gabarite, EFont* _font, ELocalisationText _ltext);

	static ETextArea* create_centered_text_area(EClickableArea* _region_gabarite, EFont* _font, ELocalisationText _ltext);
	static ETextArea* create_centered_to_right_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text);

	static ETextArea* create_centered_to_left_text_area(EClickableArea* _region_gabarite, EFont* _font, ELocalisationText _ltext);

	static ETextArea* create_bottomed_to_left_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text);
	static ETextArea* create_centered_to_up_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text);




	bool can_get_access_to_group_style();

	std::vector<text_actions_pointer> action_on_change_text;
	std::vector<text_actions_pointer> action_on_finalize_text;

	EButtonGroup* get_root_group();
	//static 
	void set_color(const float(&_color)[4]);
	void set_color(HSVRGBAColor* _color);
	void set_color(float _r, float _g, float _b, float _a);

	void set_align_to_left_middle();

	float type_cooldown = 0.0f;
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

	bool is_first_symbol = false;
	bool is_last_symbol = false;
	bool is_empty = false;


};

#endif
