#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//glm::mat4 matrix_transform;


#include <vector>
#include "NSW_api/EFont.h"

#include <iostream>
#include <chrono>

#include "NSW_api/ETextureAtlas.h"

#include "NSW_api/EUtils.h"
#include <windows.h>
#include "NSW_api/Batcher.h"
#include "../../../ExternalEnums.h"


//#include <WinUser.h>

//#include "NSW_api/EWindowTest.h"

const int key_array_size = 512;



class EWindowMain;
class EWindow;


static bool is_catched_by_mouse(bool _is_catched, float _x, float _y, float _size_x, float _size_y, float _catch_size, int _mode);

static float get_mouse_speed_x();
static float get_mouse_speed_y();



class EButton
{
public:
	typedef void (*BUTTON_ACTION)(EButton* _b, float _d);

	std::vector<BUTTON_ACTION> action_on_left_click;
	std::vector<BUTTON_ACTION> action_on_drag;
	std::vector<BUTTON_ACTION> action_on_td_gradient_drag;

	bool* drag_is_positive = new bool(false);

	


	//std::vector <EPolygomMassive*> polygon_massive_list;

	Batcher::EPolygonMassive* polygon_massive;

	std::vector <int*> mode_list;



	enum ButtonSimpleChangerActivationType
	{
		CHANGER_ACTIVATION_TYPE_LEFT_CLICK,
		CHANGER_ACTIVATION_TYPE_RIGHT_CLICK,
		CHANGER_ACTIVATION_TYPE_DOUBLE_LEFT_CLICK,
		CHANGER_ACTIVATION_TYPE_DROP_LIST_EXPAND,
		CHANGER_ACTIVATION_TYPE_DROP_LIST_SELECT_ELEMENT,
		CHANGER_ACTIVATION_TYPE_SLIDER_DRAG,
		CHANGER_ACTIVATION_TYPE_INPUT
	};

	enum ButtonSimpleChangerMathematic
	{
		BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SET_VALUE,
		BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_ADD_VALUE,
		BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SUBSTRACT_VALUE,
		BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_DIVIDE_VALUE,
		BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_MULTIPLY_VALUE
	};

	//////////////////////////////
	struct SimpleFloatChanger
	{
		float* target_float_pointer = NULL;
		float* float_value = new float(0.0f);

		enum SimpleFloatChangerType
		{
			SIMPLE_FLOAT_CHANGER_BUTTON_VALUE,
			SIMPLE_FLOAT_CHANGER_CONSTANT
		};

		int* float_changer_type = new int(0);

		int* selected_activation_type = new int(0);
		int* selected_mathematic_type = new int(0);

		float* pre_correction_value = new float(0.0f);
	};
	std::vector <SimpleFloatChanger*> simple_float_changer_list;
	//////////////////////////////
	struct SimpleTextureChanger
	{
		EGabarite** target_texture_pointer = NULL;
		EGabarite* texture_value = NULL;
		enum SimpleTextureChangerType
		{
			SIMPLE_TEXTURE_CHANGER_BUTTON_VALUE,
			SIMPLE_TEXTURE_CHANGER_CONSTANT
		};

		int* texture_changer_type = new int(0);
	};

	std::vector <SimpleTextureChanger*> simple_texture_changer_list;

	//std::vector <float*> simple_float_changer;

	std::vector<BUTTON_ACTION> action_on_left_double_click;
	float* click_timer = new float(0.0f);

	std::vector<BUTTON_ACTION> action_on_right_click;

	std::vector<BUTTON_ACTION> action_on_input;
	BUTTON_ACTION action_on_input_finish;

	std::vector<BUTTON_ACTION> action_on_slider_drag;
	std::vector<BUTTON_ACTION> action_on_drop_list_select_element;

	//std::vector < DefaultButtonActions::SimpleValueChanger* > simple_value_changer_list;

	int* target_address_for_int;
	int* target_value_for_int = new int(0);

	float* target_address_for_float;
	float* target_value_for_float = new float(0.0f);

	bool* target_address_for_bool;
	bool* target_value_for_bool = new bool(false);

	short* target_address_for_short;
	short* target_value_for_short = new short(1);

	EGabarite** target_address_for_gabarite;

	std::string* target_address_for_string;
	std::string* target_value_for_string = new std::string("");

	static void static_click();
	static void static_click2();

	static void set_left_click_action(void(*function)(EButton*, float));

	float button_x_offset = 10;
	float button_y_offset = 200;

	float button_base_x = 200;
	float button_base_y = 200;

	float button_size_x = 100;
	float button_size_y = 25;

	float button_min_size_x = 5;
	float button_min_size_y = 5;

	std::string text = "";

	bool have_input_mode = false;
	bool is_input_mode_active = false;

	bool is_active = true;
	bool icon_adaptation = true;

	float icon_size_multiplier = 1;

	float mul_method_vertical = 0.0f;
	float mul_method_horizontal = 0.0f;

	float bound_size_left = 0;
	float bound_size_right = 0;
	float bound_size_up = 0;
	float bound_size_down = 0;

	bool is_expanded = false;
	bool is_drop_list = false;

	int master_position = Enums::PositionMaster::WINDOW;

	int drop_elements = 0;
	std::vector<string> drop_text;
	std::vector<string> drop_text_base;
	bool have_list_color = false;
	std::vector<EColor*> drop_list_color;

	bool slider_activate = false;

	EGabarite* gabarite = NULL;

	bool have_icon = true;
	EColor* icon_color = new EColor(1.0f, 1.0f, 1.0f, 1.0f);

	int position_by_window_mode_x = Enums::PositionMode::LEFT;
	int position_by_window_mode_y = Enums::PositionMode::DOWN;

	int position_by_group_mode_x = Enums::PositionMode::LEFT;
	int position_by_group_mode_y = Enums::PositionMode::DOWN;

	bool* auto_stretch_button_y_size = new bool(false);

	int text_align_x = Enums::PositionMode::LEFT;

	EWindow* master_window;
	EButton* master_button;

	float screen_position_x = 0;
	float screen_position_y = 0;

	EButton();
	EButton(float _x, float _y, float _sx, float _sy);

	//EButton(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type);

	bool have_description = true;
	string description_text;
	string prev_description_text;

	bool have_text = true;

	string input_hint;

	~EButton();

	bool is_number(char _c);

	bool is_overlap();
	bool is_click();
	bool is_outclick();
	bool is_right_click();

	static void simple_float_changer_input(EButton* _b);

	bool have_bg = true;
	void update(float _d);
	virtual void update_additional(float _d);

	bool is_holdable = false;

	bool is_slider = false;
	float slider_value;
	float slider_value_multiplier = 1.0f;

	virtual void additional_draw(Batcher* _batch, float _d);
	void default_draw(Batcher* _batch, float _d);

	void text_pass(Batcher* _batch);
	//virtual void incoming_data(FilterBlock* _block);

	bool outclick_protection = false;

	bool* can_be_selected = new bool(false);
	virtual void click_event();
	virtual void right_click_event();
	virtual void input_event();
	virtual void input_finish_event();
	virtual void drop_list_select_event();

	virtual void slider_drag_event();

	static int top_window_id;

	bool flash_line_active = false;
	float flash_cooldown = 0.5f;

	bool can_be_removed = false;
	bool* need_remove = new bool(false);

	bool have_rama = false;
	int rama_thikness = 2;
	EColor* rama_color = new EColor(0.0f, 0.0f, 0.0f, 1.0f);
	EColor* bg_color = new EColor(0.8f, 0.85f, 0.9f, 1.0f);
	EColor* text_color = new EColor(0.0f, 0.0f, 0.0f, 1.0f);

	int catched_element = 0;
	int selected_element = 0;

	//Enums::ButtonType button_type;

	bool input_only_numbers = false;

	int data_id;

	EColor* icon_color_default = new EColor(1.0f, 1.0f, 1.0f, 1.0f);
	EColor* icon_color_deactivated = new EColor(0.5f, 0.5f, 0.5f, 0.5f);

	EColor* rama_color_default = new EColor(1.0f, 1.0f, 1.0f, 1.0f);
	EColor* rama_color_deactivated = new EColor(0.5f, 0.5f, 0.5f, 0.5f);

	EColor* bg_color_default = new EColor(0.8f, 0.8f, 0.8f, 0.25f);
	EColor* bg_color_deactivated = new EColor(0.1f, 0.1f, 0.1f, 0.1f);

	void activate();
	void deactivate();

	bool dynamic_input_width = true;

	std::string data_string;

	bool slider_is_horizontal = true;

	virtual void update_localisation();

	bool input_auto_clear_text = false;

	EFont* force_font;

	//FilterBlockSeparator* master_separator;

	bool can_receive_paste = false;

	EWindow* simple_action_open_window;

	std::string* side_text = new string("");

	/*
	EButtonAction* button_action_press;
	EButtonAction* button_action_right_press;
	EButtonAction* button_action_input_finish;
	EButtonAction* button_action_outclick;*/

	//bool& link_to_boolean;

	static EButton* clone_button(EButton* _b, float _x, float _y, float _sx, float _sy);

	bool* double_click_started = new bool(false);
	bool* is_double_click = new bool(false);

	static bool any_input;
	static bool any_overlap;

	bool* is_consumable = new bool(false);
	bool* is_radial_button = new bool(false);
	float* maximum_value = new float(1.0f);

	bool* is_checkbox = new bool(false);
	bool* is_checked = new bool(false);

	bool* can_be_hidden_by_search_deactivator = new bool(true);

	enum GroupPushMethod
	{
		GROUP_PUSH_METHOD_ADD_Y,
		GROUP_PUSH_METHOD_ADD_X,

		GROUP_PUSH_METHOD_RESET_Y_ADD_X,
		GROUP_PUSH_METHOD_RESET_X_ADD_Y
	};

	struct button_group
	{
		std::vector<EButton*> button_list;

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		std::string* name = new std::string("");

		bool* can_be_stretched_x = new bool(true);
		bool* can_be_stretched_y = new bool(true);

		float* button_y_scroll = new float(0.0f);

		bool* right_side_catched = new bool(false);
		bool* left_side_catched = new bool(false);
		bool* up_side_catched = new bool(false);
		bool* down_side_catched = new bool(false);

		float* additional_right_side_bound_for_autostretch = new float(20.0f);

		bool* can_be_moved_by_user = new bool(true);

		int* selected_push_method = new int(0);

		EButton* selected_button = NULL;

		

		button_group();
		~button_group();

	};

	static void update_data_id_for_buttons(button_group* _bg);

	struct SimpleButtonSearchDeactivator
	{
		button_group* target_button_group = NULL;

		bool* is_search_by_name			= new bool(false);
		bool* is_search_by_text			= new bool(false);
		bool* is_search_by_description	= new bool(false);
		bool* is_search_by_data_string	= new bool(false);
	};

	std::vector < SimpleButtonSearchDeactivator* > simple_button_search_deactivator_list;

	struct button_super_group
	{
		button_super_group(EWindow* _w);
		~button_super_group();

		std::vector <button_group*> button_group_list;

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		bool* is_active = new bool(true);

		std::string* name = new std::string("");

		bool* is_catched = new bool(false);

		std::vector<EButton*> additional_button_list;

		EButton* button_close = nullptr;

		bool* inmovable_on_list = new bool(false);

		EGabarite* background_texture;
	};

	EButton(float _x, float _y, float _sx, float _sy, EWindow* _w, button_super_group* _bsg, button_group* _bg);

	enum ButtonAutoAlign
	{
		BUTTON_AUTO_ALIGN_ADD_Y,
		BUTTON_AUTO_ALIGN_ADD_X,
		BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y,
		BUTTON_AUTO_ALIGN_RESET_Y_AND_ADD_X,
		BUTTON_AUTO_ALIGN_FREE,
		BUTTON_AUTO_ALIGN_NONE
	};

	int* selected_auto_align_mode = new int(0);

	static bool is_not_outside_of_group(EButton* _b, button_super_group* _bsg, button_group* _bg);
	static bool is_not_outside_of_super_group(EButton* _b, button_super_group* _bsg);

	button_group* master_group;
	button_super_group* master_super_group;

	struct EGridRegion
	{
		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		int* subdivision_x = new int(0);
		int* subdivision_y = new int(0);

		bool* cathed_right_side = new bool(false);
		bool* cathed_left_side = new bool(false);

		bool* cathed_up_side = new bool(false);
		bool* cathed_down_side = new bool(false);

		bool* locked_left_side = new bool(false);
		bool* locked_right_side = new bool(false);

		bool* locked_up_side = new bool(false);
		bool* locked_down_side = new bool(false);
	};

	std::vector<EGridRegion*> grid_region_list;

	bool* can_edit_grid_region = new bool(false);

	bool* start_drag = new bool(false);
	static EButton* dragged_button;

	struct ETwoDimensionGradient
	{
		float* value_x = new float(0.5f);
		float* value_y = new float(0.5f);

		EColor* color_x = new EColor(1.0f, 0.0f, 0.0f, 1.0f);
		EColor* color_y = new EColor(0.0f, 0.0f, 1.0f, 1.0f);

		EColor* lines_color = new EColor(1.0f, 1.0f, 1.0f, 1.0f);

		ETwoDimensionGradient();
		~ETwoDimensionGradient();

		bool* is_catched = new bool(false);

		bool* draw_gradient = new bool(true);

	};

	ETwoDimensionGradient* two_dimension_gradient;
};

static void external_button_action_close_master_button_super_group(EButton* _b, float _f);
void send_this_button_group_to_top (EWindow* _w, EButton::button_super_group* _group);

class EWindow
{
public:
	static bool key_pressed_array[512];
	void default_update(float _d);

	static void catch_right_side(EButton::button_group* bg, EButton::button_super_group* bsg);
	static void catch_left_side(EButton::button_group* bg, EButton::button_super_group* bsg);
	static void catch_up_side(EButton::button_group* bg, EButton::button_super_group* bsg);
	static void catch_down_side(EButton::button_group* bg, EButton::button_super_group* bsg);

	virtual void update(float _d);

	void default_draw(float _d);
	virtual void draw(float _d);

	void default_resize_event();

	virtual void draw_interface(float _d);
	void default_draw_interface(float _d);

	void static add_time_process(std::string _name);

	static GLFWwindow* main_window;

	static unsigned int transformLoc;

	float offset_x = 0;
	float offset_y = 0;

	float position_x = 0;
	float position_y = 0;

	float window_size_x = 100.0f;
	float window_size_y = 100.0f;

	static double mouse_x;
	static double mouse_y;

	static int prev_mouse_x;
	static int prev_mouse_y;

	static int saved_pos_x;
	static int saved_pos_y;

	static float mouse_speed_x;
	static float mouse_speed_y;

	static float real_mouse_x;
	static float real_mouse_y;

	static bool LMB;
	static bool RMB;

	static bool system_button_release;

	static double scroll;

	//static std::pair<float, std::string> time_process;

	struct time_process_struct
	{
		std::vector<float> time_process_value;
		std::string time_process_name;
	};

	static std::vector<time_process_struct*> tps_list;

	static int time_process_rota_id;
	static std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;

	static void push_cursor(float _x, float _y);

	EWindow();
	~EWindow();

	static Batcher* batch;
	static std::vector<EWindow*> window_list;
	static float delete_button_hold_time;

	static EWindowMain* window_main;

	static ETextureAtlas* default_texture_atlas;
	static ETextureAtlas* shadow_FBO;
	static ETextureAtlas* shadow_ground_FBO;
	static ETextureAtlas* lightmap_FBO;
	static ETextureAtlas* lightmap_FBO2;
	static ETextureAtlas* base_lightmap;
	static ETextureAtlas* base_blockmap;

	static ETextureAtlas* supermap_FBO;
	static ETextureAtlas* AO_shadow_FBO;

	static ETextureAtlas* skydome_light_FBO[8];
	static ETextureAtlas* skydome_light_FBO_buffer[8];

	static ETextureAtlas* screen_FBO;

	static bool button_pressed;

	static bool button_main_group_pressed;

	static bool button_right_pressed;
	static bool button_backspace_released;
	bool is_active = true;
	int id = 0;

	static bool is_overlap(EWindow* _w);

	static char last_inputed_char;

	std::vector <EButton*> button_list;
	std::vector <EButton*> default_button_list;

	bool always_fullscreen;
	bool have_bg = false;

	bool screen_space = false;

	EGabarite* screen_space_texture = NULL;

	int align_x;
	int align_y;

	static EButton* operable_button;

	struct button_array
	{
		std::vector <EButton*> button_list;

		float* maximum_size_x = new float(0.0f);

		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);
	};

	struct button_array_vertical_collection
	{
		button_array_vertical_collection(float _x, float _y, float _sx, float _sy)
		{
			*position_x = _x;
			*position_y = _y;

			*size_x = _sx;
			*size_y = _sy;
		}

		int* tab_id = new int(0);
		int* maximum_button_on_array = new int(0);

		enum BUTTON_DISTANCE_ALIGN_RULE
		{
			FREE,
			BUTTON_SIZE,
			MAXIMUM_BUTTON_SIZE
		};

		int* selected_distance_between_button_mode = new int(BUTTON_DISTANCE_ALIGN_RULE::FREE);

		float* additional_horisontal_distance_between_buttons = new float(0.0f);
		float* additional_vertical_distance_between_buttons = new float(0.0f);

		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		std::vector <button_array*> button_array_list;

		//std::vector<EButton*> a;

		static void update_button_position()
		{
		}
	};

	struct button_array_horizontal_collection
	{
		button_array_horizontal_collection(float _x, float _y, float _sx, float _sy)
		{
			*position_x = _x;
			*position_y = _y;

			*size_x = _sx;
			*size_y = _sy;
		}

		int* selected_tab = new int(0);

		struct test
		{
		};

		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		std::vector < button_array_vertical_collection*> button_array_vertical_collection_list;

		std::vector <EButton*> tab_button_list;

		int* push_method = new int(ARRAY_PUSH_METHOD::APM_PUSH_Y);
	};

	enum ARRAY_PUSH_METHOD
	{
		APM_NONE,
		APM_PUSH_X,
		APM_PUSH_Y
	};

	struct button_array_collection_massive
	{
		bool* head_catched = new bool(false);
		bool* catch_highlight = new bool(false);
		button_array_collection_massive(EWindow* _w);

		bool* is_active = new bool(true);

		std::vector < button_array_horizontal_collection* > button_array_horizontal_collection_list;

		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);
		//-
		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		std::vector<EButton*> service_button;

		EButton* button_close = NULL;

		int* selected_style = new int(0);
	};

	enum GabariteBackgroundMode
	{
		//
		//non screen space
		//
		GBM_SIMPLE,

		//
		//screen space
		//
		GBM_SCREEN_SPACE
	};
	struct massive_style
	{
		EGabarite* left_corner = NULL;
		EGabarite* right_corner = NULL;
		EGabarite* up_corner = NULL;
		EGabarite* down_corner = NULL;

		EGabarite* LU_corner = NULL;
		EGabarite* RU_corner = NULL;
		EGabarite* LD_corner = NULL;
		EGabarite* LR_corner = NULL;

		EGabarite* background = NULL;

		int background_mode = GabariteBackgroundMode::GBM_SCREEN_SPACE;
	};

	static std::vector <massive_style*> list_of_massive_style;

	std::vector<button_array_collection_massive*> button_array_collection_massive_list;

	//void draw_lightmap();
	std::vector< EButton::button_super_group* > button_group_list;

	static EButton::button_super_group* top_overlaped_group;

	static bool is_group_overlapped_by_mouse(EButton::button_super_group* _group);

	static EButton::button_group* get_button_group_by_name(EWindow* _w, std::string _super_group_name, std::string _group_name);
};

class DefaultButtonActions
{
public:
	//static void ButtonActionSetTexture(EButton* _b, float _d);

	//static void button_action_close_master_window

	/*struct SimpleValueChanger
	{
		enum StringValueChangerType
		{
			StringValueChangerType_CONTANT,
			StringValueChangerType_BUTON_VALUE
		};

		std::string		string_value_pointer		= NULL;
		std::string*	string_value				= new string("");
		int*			string_value_changer_type	= new int(StringValueChangerType::StringValueChangerType_CONTANT);
	};*/
};

class EButtonGroup
{
public:
};

/*
class EDataWatcher
{
public:

	struct data_watch_float
	{
		float* data_value = new float(0.0f);
		std::string name;
	};

	struct data_watch_int
	{
		int* data_value = new int(0);
		std::string name;
	};
};*/
