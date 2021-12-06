#pragma once
#include "EWindow.h"
//#include "../../../EBA.h"

GLFWwindow* EWindow::main_window = NULL;

std::vector<EWindow*> EWindow::window_list;

ETextureAtlas* EWindow::default_texture_atlas;
ETextureAtlas* EWindow::shadow_FBO;
ETextureAtlas* EWindow::shadow_ground_FBO;
ETextureAtlas* EWindow::lightmap_FBO;
ETextureAtlas* EWindow::lightmap_FBO2;
ETextureAtlas* EWindow::base_lightmap;
ETextureAtlas* EWindow::base_blockmap;

ETextureAtlas* EWindow::supermap_FBO;
ETextureAtlas* EWindow::AO_shadow_FBO;

ETextureAtlas* EWindow::skydome_light_FBO[8];
ETextureAtlas* EWindow::skydome_light_FBO_buffer[8];


ETextureAtlas* EWindow::screen_FBO;

EButton* EButton::dragged_button;

unsigned int EWindow::transformLoc;

double EWindow::mouse_x = 0;
double EWindow::mouse_y = 0;

bool EWindow::key_pressed_array[512];

int EWindow::saved_pos_x = 0;
int EWindow::saved_pos_y = 0;

int EWindow::prev_mouse_x = 0;
int EWindow::prev_mouse_y = 0;

float EWindow::mouse_speed_x = 0.0f;
float EWindow::mouse_speed_y = 0.0f;

float EWindow::real_mouse_x;
float EWindow::real_mouse_y;

bool EWindow::LMB = false;
bool EWindow::RMB = false;

bool EWindow::button_pressed = false;
bool EWindow::button_main_group_pressed = false;

bool EWindow::button_right_pressed = false;
bool EWindow::button_backspace_released = true;

//bool EWindow::is_active = true;

float EWindow::delete_button_hold_time = 0.0f;

char EWindow::last_inputed_char = NULL;

int EWindow::time_process_rota_id = 0;

std::vector<EWindow::time_process_struct*> EWindow::tps_list;

bool EWindow::system_button_release = true;
double EWindow::scroll = 0;

std::chrono::time_point<std::chrono::high_resolution_clock> EWindow::start, EWindow::stop;

EWindowMain* EWindow::window_main;
//std::pair<float, std::string> EWindow::time_process;

int EButton::top_window_id = -1;
//void (*zzz)();

//void (*action_on_left_click)(EButton* _b, float _d);

bool EButton::any_input = false;
bool EButton::any_overlap = false;

std::vector <EWindow::massive_style*>	EWindow::list_of_massive_style;
EButton::button_super_group*			EWindow::top_overlaped_group;
EButton*								EWindow::operable_button;

constexpr auto time_process_rota_size = 60;

EButton::EButton()
{
	update_localisation();
}

void EButton::static_click()
{
	std::cout << "STATIC CLICK!!!" << std::endl;
}

void EButton::static_click2()
{
	std::cout << "STATIC CLICK2!!!" << std::endl;
}

void EButton::set_left_click_action(void(*function)(EButton*, float))
{
	//action_on_left_click = function;
}

EButton::EButton(float _x, float _y, float _sx, float _sy)
{
	//EBA::foo = &EButton::static_click;
	//EBA::foo = NULL;

	/*if (rand() % 100 < 50)
	{
		EBA::set_method(&static_click);
	}
	else
	{
		EBA::set_method(&static_click2);
	}*/

	button_x_offset = _x;
	button_y_offset = _y;

	button_base_x = _x;
	button_base_y = _y;

	button_size_x = _sx;
	button_size_y = _sy;

	button_min_size_x = _sx;
	button_min_size_y = _sy;

	update_localisation();

	//action_on_left_click = &EBA::action_add_new_sprite;
}

EButton::~EButton()
{
}

bool EButton::is_number(char _c)
{
	if
		(
			(_c == '-') ||
			(_c == '.') ||
			(_c == '0') ||
			(_c == '1') ||
			(_c == '2') ||
			(_c == '3') ||
			(_c == '4') ||
			(_c == '5') ||
			(_c == '6') ||
			(_c == '7') ||
			(_c == '8') ||
			(_c == '9')
			)
	{
		return true;
	}

	return false;
}

bool EButton::is_overlap()
{
	//ETexture::texture[0] = 0;
	//std::cout << "" << std::endl;

	//std::cout << Helper::x << " " << Helper::y << " " << std::endl;
	//std::cout << "PIZDOS=" << EMouse::mouse_x<< endl;

	if
	(
		(EWindow::operable_button != NULL)
		&
		(EWindow::operable_button != this)
	)
	{
		return false;
	}

	float total_x = 0.0f;
	float total_y = 0.0f;
	if
	(
		(master_group != NULL)
		&&
		(master_super_group != NULL)
		&&
		(
			(EWindow::mouse_x < *master_super_group->position_x + *master_group->position_x)
			||
			(EWindow::mouse_x > * master_super_group->position_x + *master_group->position_x + *master_group->size_x)
			||
			(EWindow::mouse_y < *master_super_group->position_y + *master_group->position_y)
			||
			(EWindow::mouse_y > * master_super_group->position_y + *master_group->position_y + *master_group->size_y)
			||
			(EWindow::top_overlaped_group != master_super_group)
		)
	)
	{
		return false;
	}

	if
		(
			(EWindow::mouse_x > screen_position_x - bound_size_left)
			&&
			(EWindow::mouse_x < screen_position_x + button_size_x + bound_size_right)
			&&
			(EWindow::mouse_y > screen_position_y - bound_size_down)
			&&
			(EWindow::mouse_y < screen_position_y + button_size_y + bound_size_up)
			&&
			(top_window_id == master_window->id)
			)
	{
		return true;
	}
	else
	{
		return false;
	}
	//return false;
}

bool EButton::is_click()
{
	if ((EWindow::LMB) && (!EWindow::button_pressed) && (is_overlap())) { return true; }

	return false;
}

bool EButton::is_outclick()
{
	if ((EWindow::LMB) && (!is_overlap()) && (!outclick_protection)) { return true; }

	return false;
}

bool EButton::is_right_click()
{
	if ((EWindow::RMB) && (!EWindow::button_right_pressed) && (is_overlap())) { EWindow::button_right_pressed = true; return true; }

	return false;
}

void EButton::simple_float_changer_input(EButton* _b)
{
	for (SimpleFloatChanger* sfcl : _b->simple_float_changer_list)
		if ((sfcl != NULL) && (sfcl->target_float_pointer != NULL) && (*sfcl->selected_activation_type == ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_INPUT))
		{
			if (*sfcl->float_changer_type == SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_BUTTON_VALUE)
			{
				float result_value = EMath::to_float(_b->text) + *sfcl->pre_correction_value;

				if (*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SET_VALUE)
				{
					*sfcl->target_float_pointer = result_value;
				}

				if (*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_ADD_VALUE)
				{
					*sfcl->target_float_pointer += result_value;
				}

				if (*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SUBSTRACT_VALUE)
				{
					*sfcl->target_float_pointer -= result_value;
				}

				if ((*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_DIVIDE_VALUE) & (result_value != 0.0f))
				{
					*sfcl->target_float_pointer /= result_value;
				}

				if ((*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_MULTIPLY_VALUE) & (result_value != 0.0f))
				{
					*sfcl->target_float_pointer *= result_value;
				}
			}

			if (*sfcl->float_changer_type == SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_CONSTANT)
			{
				*sfcl->target_float_pointer = *sfcl->float_value;

				//std::cout << "target value is [" << std::to_string(*sfcl->float_value) << std::endl;
			}
		}
		else
		{
			if (sfcl == NULL) { std::cout << "ERROR: sfcl is NULL" << std::endl; }
			if (sfcl->target_float_pointer == NULL) { std::cout << "ERROR: sfcl target value is NULL" << std::endl; }
		}
}

void EButton::update(float _d)
{
	//text = std::to_string(data_id);

	if (*is_consumable)
	{
		if
			(
				(
					(is_slider)
					||
					(*is_radial_button)
					)
				&
				(target_address_for_float != NULL)
				)
		{
			slider_value = *target_address_for_float;
		}

		if ((*is_checkbox) & (target_address_for_bool != NULL))
		{
			*is_checked = *target_address_for_bool;
		}

		if ((*is_checkbox) & (target_address_for_short != NULL))
		{
			*is_checked = bool(*target_address_for_short);
		}

		if ((is_drop_list) & (target_address_for_int != NULL))
		{
			selected_element = *target_address_for_int;
			text = drop_text.at(selected_element);
		}

		if ((have_input_mode) & (target_address_for_int != NULL))
		{
			text = std::to_string(*target_address_for_int);
		}

		if ((have_text) & (target_address_for_string != NULL))
		{
			text = *target_address_for_string;
		}
	}

	if ((is_overlap()) & (have_input_mode) & (input_only_numbers) & (EWindow::scroll != 0))
	{
		if (text == "") { text = "0"; }
		text = EString::float_to_string(EMath::to_float(text) + EWindow::scroll);
		input_finish_event();

		simple_float_changer_input(this);
		if (!action_on_input.empty())
		{
			for (BUTTON_ACTION b : action_on_input) { b(this, _d); }
		}

		if ((action_on_input_finish != NULL) & (!is_input_mode_active)) { action_on_input_finish(this, _d); }
	}

	if
		(
			(can_receive_paste)
			&&
			(is_overlap())
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_V) == GLFW_PRESS)
			)
	{
		if (!OpenClipboard(nullptr))
		{
		}

		// Get handle of clipboard object for ANSI text
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr)
		{
		}

		// Lock the handle to get the actual text pointer
		char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr)
		{
		}

		// Save text in a string class instance
		std::string clipboard_text(pszText);
		text = clipboard_text;

		// Release the lock
		GlobalUnlock(hData);

		// Release the clipboard
		CloseClipboard();

		if (is_input_mode_active)
		{
			input_event();
			simple_float_changer_input(this);
			if (!action_on_input.empty())
			{
				for (BUTTON_ACTION b : action_on_input) { b(this, _d); }
			}
		}
		else
		{
			input_finish_event();
		}

		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
		//if (master_separator != NULL) { StaticData::window_filter_block->unsave_change = true; }
	}

	if
		(
			(is_overlap())
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS)
			)
	{
		const char* output = text.c_str();
		const size_t len = strlen(output) + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), output, len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}
	//std::cout << "clipboard [" << (text) << "]" << std::endl;

	//cout << main_window << endl;

	icon_size_multiplier = 1.0f;
	if
		(
			(have_icon)
			&&
			(icon_adaptation)
			&&
			(gabarite != NULL)
			)
	{
		mul_method_vertical = button_size_x / *gabarite->size_x;
		mul_method_horizontal = button_size_y / *gabarite->size_y;

		if (mul_method_vertical < mul_method_horizontal)
		{
			icon_size_multiplier = mul_method_vertical;
		}
		else
		{
			icon_size_multiplier = mul_method_horizontal;
		}
	}

	if ((master_position == Enums::PositionMaster::WINDOW) && (master_window != NULL))
	{
		if (position_by_window_mode_x == Enums::PositionMode::LEFT) { screen_position_x = master_window->offset_x + button_x_offset; }
		if (position_by_window_mode_x == Enums::PositionMode::MID) { screen_position_x = master_window->offset_x + (master_window->window_size_x - button_size_x) / 2.0f + button_x_offset; }
		if (position_by_window_mode_x == Enums::PositionMode::RIGHT) { screen_position_x = master_window->offset_x + master_window->window_size_x + button_x_offset - button_size_x; }

		if (position_by_window_mode_y == Enums::PositionMode::DOWN) { screen_position_y = master_window->offset_y + button_y_offset; }
		if (position_by_window_mode_y == Enums::PositionMode::MID) { screen_position_y = master_window->offset_y + (master_window->window_size_y - button_size_y) / 2.0f + button_y_offset; }
		if (position_by_window_mode_y == Enums::PositionMode::UP) { screen_position_y = master_window->offset_y + master_window->window_size_y + button_y_offset - button_size_y; }
	}

	if ((master_position == Enums::PositionMaster::BUTTON) && (master_button != NULL))
	{
		if (position_by_window_mode_x == Enums::PositionMode::SUPER_LEFT) { screen_position_x = master_button->screen_position_x + button_x_offset - master_button->button_size_x; }
		if (position_by_window_mode_x == Enums::PositionMode::LEFT) { screen_position_x = master_button->screen_position_x + button_x_offset; }
		if (position_by_window_mode_x == Enums::PositionMode::MID) { screen_position_x = master_button->screen_position_x + (master_button->button_size_x - button_size_x) / 2.0f + button_x_offset; }
		if (position_by_window_mode_x == Enums::PositionMode::RIGHT) { screen_position_x = master_button->screen_position_x + master_button->button_size_x + button_x_offset - button_size_x; }
		if (position_by_window_mode_x == Enums::PositionMode::SUPER_RIGHT) { screen_position_x = master_button->screen_position_x + master_button->button_size_x + button_x_offset; }

		if (position_by_window_mode_y == Enums::PositionMode::UP) { screen_position_y = master_button->screen_position_y + button_y_offset + master_button->button_size_y; }
		if (position_by_window_mode_y == Enums::PositionMode::MID) { screen_position_y = master_button->screen_position_y + (master_button->button_size_y - button_size_y) / 2.0f + button_y_offset; }
		if (position_by_window_mode_y == Enums::PositionMode::DOWN) { screen_position_y = master_button->screen_position_y + button_y_offset - button_size_y; }
	}

	if (master_position == Enums::PositionMaster::SCREEN)
	{
		if (position_by_window_mode_x == Enums::PositionMode::LEFT) { screen_position_x = button_x_offset; }
		if (position_by_window_mode_y == Enums::PositionMode::DOWN) { screen_position_y = button_y_offset; }
	}

	if (is_input_mode_active)
	{
		//std::cout << last_inputed_char << std::endl;
		if
			(
				(EWindow::last_inputed_char != NULL)
				&&
				(
					(!input_only_numbers)
					||
					(is_number(EWindow::last_inputed_char))
					)
				&&
				(
					(EFont::active_font->get_width(EFont::active_font, text + EWindow::last_inputed_char) < button_size_x)
					||
					(dynamic_input_width)
					)
				)
		{
			text += EWindow::last_inputed_char;
			EWindow::last_inputed_char = NULL;

			//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
			input_event();
			simple_float_changer_input(this);
			if (!action_on_input.empty())
			{
				for (BUTTON_ACTION b : action_on_input) { b(this, _d); }
			}
		}

		//is_button_pressed

		if ((EWindow::delete_button_hold_time > 0.5f) && (is_input_mode_active))
		{
			text = "";

			input_event();
			simple_float_changer_input(this);
			if (!action_on_input.empty())
			{
				for (BUTTON_ACTION b : action_on_input) { b(this, _d); }
			}
		}

		if
			(
				(
					(glfwGetKey(EWindow::main_window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
					||
					(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_PRESS)
					)
				&&
				(EWindow::button_backspace_released)
				)
		{
			EWindow::button_backspace_released = false;

			if (text.length() > 1)
			{
				text = text.substr(0, text.length() - 1.0f);
				input_event();
			}
			else
			{
				text = "";
				input_event();
				//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
			}

			simple_float_changer_input(this);
			if (!action_on_input.empty())
			{
				for (BUTTON_ACTION b : action_on_input) { b(this, _d); }
			}

			//input_event();
		}

		if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_ENTER) == GLFW_PRESS)
				||
				(glfwGetKey(EWindow::main_window, GLFW_KEY_KP_ENTER) == GLFW_PRESS)
				)
		{
			//any_input = false;
			is_input_mode_active = false;

			if (EWindow::operable_button == this) { EWindow::operable_button = NULL; }

			if ((input_only_numbers) && (text == ""))
			{
				text = "0";
			}

			input_finish_event();
			if (action_on_input_finish != NULL) { action_on_input_finish(this, _d); }
		}

		if (dynamic_input_width) { button_size_x = EFont::get_width(EFont::active_font, text) + 10.0f; }
	}

	if (button_size_x < button_min_size_x) { button_size_x = button_min_size_x; }

	//click ouside by button
	if (is_outclick())
	{
		//if (text == "") { text = "0"; }

		if ((input_only_numbers) && (text == ""))
		{
			text = "0";
		}

		if ((is_expanded) && (is_drop_list))
		{
			is_expanded = false;
			
		}

		if (is_input_mode_active)
		{
			is_input_mode_active = false;

			if (EWindow::operable_button == this) { EWindow::operable_button = NULL; }
			input_finish_event();

			if (action_on_input_finish != NULL) { action_on_input_finish(this, _d); }

			

		}
	}

	if (is_overlap())
	{
		any_overlap = true;

		if ((EButton::dragged_button == NULL) & (EWindow::LMB))
		{
			dragged_button = this;
		}

		if ((EButton::dragged_button != NULL) && (!EWindow::LMB) && (dragged_button->master_group == master_group))
		{
			EButton* swap_button = NULL;

			//if (EWindow::mouse_x < master_position + button_size_x / 2.0f)

			EButton* button_swap = NULL;
			if
				(
					(data_id >= 0)
					&
					(*can_be_selected)
					&
					(EWindow::mouse_x < screen_position_x + button_size_x / 2.0f)
					&
					(dragged_button != this)
					&
					(master_group != NULL)
					)
			{
				*dragged_button->drag_is_positive = false;

				if (data_id < dragged_button->data_id)
				{
					for (int i = dragged_button->data_id; i >= data_id; i--)
					{
						button_swap = master_group->button_list.at(i - 1);
						master_group->button_list.at(i - 1) = master_group->button_list.at(i);
						master_group->button_list.at(i) = button_swap;

						for (BUTTON_ACTION ba : action_on_drag)
						{
							ba(dragged_button, _d);
						}

						update_data_id_for_buttons(master_group);
					}
				}
				else
				{
					for (int i = dragged_button->data_id; i < data_id - 1; i++)
					{
						button_swap = master_group->button_list.at(i + 1);
						master_group->button_list.at(i + 1) = master_group->button_list.at(i);
						master_group->button_list.at(i) = button_swap;

						for (BUTTON_ACTION ba : action_on_drag)
						{
							ba(this, _d);
						}

						update_data_id_for_buttons(master_group);
					}
				}

				//master_group->button_list.erase(master_group->button_list.begin() + dragged_button->data_id);
			}

			if
				(
					(master_group != NULL)
					&&
					(data_id < master_group->button_list.size() - 1)
					&&
					(*can_be_selected)
					&&
					(EWindow::mouse_x > screen_position_x + button_size_x / 2.0f)
					&&
					(dragged_button != this)
					&&
					(master_group != NULL)
					)
			{
				*dragged_button->drag_is_positive = true;

				if (data_id < dragged_button->data_id)
				{
					for (int i = dragged_button->data_id; i > data_id; i--)
					{
						button_swap = master_group->button_list.at(i - 1);
						master_group->button_list.at(i - 1) = master_group->button_list.at(i);
						master_group->button_list.at(i) = button_swap;

						//text = "NO";

						for (BUTTON_ACTION ba : action_on_drag)
						{
							ba(dragged_button, _d);
						}

						update_data_id_for_buttons(master_group);
					}
				}
				else
				{
					for (int i = dragged_button->data_id; i < data_id; i++)
					{
						button_swap = master_group->button_list.at(i + 1);
						master_group->button_list.at(i + 1) = master_group->button_list.at(i);
						master_group->button_list.at(i) = button_swap;

						//text = "NO";

						for (BUTTON_ACTION ba : action_on_drag)
						{
							ba(dragged_button, _d);
						}

						update_data_id_for_buttons(master_group);
					}
				}

				//master_group->button_list.erase(master_group->button_list.begin() + dragged_button->data_id);
			}

			/*if (EWindow::LMB)
			{text = "YES";}
			else
			{
				text = "NO";

				dragged_button = NULL;
			}*/
		}

		/*if ((EButton::dragged_button != NULL) & (EWindow::LMB))
		{
			text = "LMB";
		}*/
	}

	if (!EWindow::LMB)
	{
		outclick_protection = false;
		//dragged_button = NULL;
	}

	if (is_right_click())
	{
		right_click_event();

		if (can_be_removed)
		{
			std::cout << "TRY REMOVE" << std::endl;
			*need_remove = true;

			//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
		}

		if (!action_on_right_click.empty())
		{
			for (BUTTON_ACTION ba : action_on_right_click)
			{
				ba(this, _d);
			}
		}
	}

	/*if
	(
		(master_group != NULL)
		&
		(*start_drag)
		&
		(*can_be_selected)
	)
	{
		EButton* swap_button = NULL;
		if
		(
			(data_id > 0)
			&
			(*master_group->button_list.at(data_id - 1)->can_be_selected)
			&
			(EWindow::mouse_x < master_position_x - 5.0f)
		)
		{
			swap_button = master_group->button_list.at(data_id - 1);
			master_group->button_list.at(data_id - 1) = swap_button;
			master_group->button_list.at(data_id) = swap_button;

			*start_drag = false;
		}
	}*/

	if ((is_overlap()) & (is_drop_list) & (is_expanded))
	{
		selected_element = (int)((screen_position_y - EWindow::mouse_y) / 22.0f);

		if (!action_on_drop_list_select_element.empty())
		{
			for (BUTTON_ACTION ba : action_on_drop_list_select_element)
			{
				ba(this, _d);
			}
		}
	}

	if (is_click())
	{
		if (*is_double_click)
		{
			*double_click_started = true;
		}

		//(*action_on_left_click)();
		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }

		if (simple_action_open_window != NULL)
		{
			simple_action_open_window->is_active = true;
		}

		if (!is_holdable) { EWindow::button_pressed = true; }
		std::cout << "Button pressed" << std::endl;

		if (is_drop_list)
		{
			if (is_expanded)
			{
				if (selected_element < 0) { selected_element = 0; }
				if (selected_element > drop_elements) { selected_element = drop_elements; }

				text = drop_text.at(selected_element);
				drop_list_select_event();
			}

			is_expanded = !is_expanded;
		}

		std::cout << "try active input mode" << std::endl;
		if ((have_input_mode) && (!is_input_mode_active))
		{
			//any_input = true;
			if (input_auto_clear_text) { text = ""; }
			is_input_mode_active = true;

			
		}

		if ((is_slider) || (*is_radial_button)) { slider_activate = true; }

		click_event();

		if (*is_checkbox) { *is_checked = !*is_checked; }

		if ((!action_on_left_click.empty()) & (*click_timer <= 0.0f))
		{
			for (BUTTON_ACTION ba : action_on_left_click)
			{
				ba(this, _d);
			}
		}

		if (*click_timer > 0.0f)
		{
			if (!action_on_left_double_click.empty())
			{
				for (BUTTON_ACTION ba : action_on_left_double_click)
				{
					ba(this, _d);
				}
			}

			*click_timer = -1.0f;
		}
		
		

		
	}

	if (!EWindow::LMB)
	{
		slider_activate = false;
	}

	if (((is_slider) || (*is_radial_button)) && (slider_activate) && (slider_is_horizontal))
	{
		//slider_value = (EWindow::mouse_x - master_position_x) / button_size_x;
		//slider_value = EMath::clamp_value_float(slider_value, 0.0f, 1.0f) * slider_value_multiplier;
		//slider_value += , 0.0f, 1.0f;
		float shift_value = 1.0f / button_size_x;
		if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				||
				(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
			)
		{
			shift_value *= 0.1f;
		}

		slider_value = EMath::clamp_value_float(slider_value + EWindow::mouse_speed_x * shift_value * slider_value_multiplier * *maximum_value, 0.0f, *maximum_value);

		slider_drag_event();

		if (!action_on_slider_drag.empty())
		{
			for (BUTTON_ACTION ba : action_on_slider_drag)
			{
				ba(this, _d);
			}
		}
		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
	}

	if (((is_slider) || (*is_radial_button)) && (slider_activate) && (!slider_is_horizontal))
	{
		slider_value = 1.0f - (EWindow::mouse_y - screen_position_y) / button_size_y;
		slider_value = EMath::clamp_value_float(slider_value, 0.0f, *maximum_value);

		slider_drag_event();

		if (!action_on_slider_drag.empty())
		{
			for (BUTTON_ACTION ba : action_on_slider_drag)
			{
				ba(this, _d);
			}
		}

		for (SimpleFloatChanger* sfcl : simple_float_changer_list)
			if ((sfcl != NULL) && (sfcl->target_float_pointer != NULL) && (*sfcl->selected_activation_type == ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_SLIDER_DRAG))
			{
				if (*sfcl->float_changer_type == SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_BUTTON_VALUE)
				{
					float result_value = slider_value + *sfcl->pre_correction_value;

					if (*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SET_VALUE)
					{
						*sfcl->target_float_pointer = result_value;
					}

					if (*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_ADD_VALUE)
					{
						*sfcl->target_float_pointer += result_value;
					}

					if (*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SUBSTRACT_VALUE)
					{
						*sfcl->target_float_pointer -= result_value;
					}

					if ((*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_DIVIDE_VALUE) & (result_value != 0.0f))
					{
						*sfcl->target_float_pointer /= result_value;
					}

					if ((*sfcl->selected_mathematic_type == BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_MULTIPLY_VALUE) & (result_value != 0.0f))
					{
						*sfcl->target_float_pointer *= result_value;
					}
				}

				if (*sfcl->float_changer_type == SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_CONSTANT)
				{
					*sfcl->target_float_pointer = *sfcl->float_value;

					//std::cout << "target value is [" << std::to_string(*sfcl->float_value) << std::endl;
				}
			}
			else
			{
				if (sfcl == NULL) { std::cout << "ERROR: sfcl is NULL" << std::endl; }
				if (sfcl->target_float_pointer == NULL) { std::cout << "ERROR: sfcl target value is NULL" << std::endl; }
			}
		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
	}

	flash_cooldown -= _d;
	if (flash_cooldown < 0)
	{
		flash_cooldown += 0.25f;

		flash_line_active = !flash_line_active;
	}

	if ((*double_click_started) & (!EWindow::LMB))
	{
		*double_click_started = false;
		*click_timer = 0.2f;
	}

	if (*click_timer >= 0.0f)
	{
		*click_timer -= _d;
	}
	update_additional(_d);

	if
		(
			(is_input_mode_active)
			||
			(slider_activate)
			||
			(is_expanded)
		)
	{
		//text = "+";
		EButton::any_input = true;
		EWindow::operable_button = this;
	}

	//else
		if
		(
			(EWindow::operable_button == this)
			&
			(
				(
					(
						(is_slider)
						||
						(*is_radial_button)
					)
					&
					(!slider_activate)
				)
				||
				((have_input_mode)&(!is_input_mode_active))
				||
				((is_drop_list)&(!is_expanded))
				||
				((two_dimension_gradient != NULL)&(!EWindow::LMB))
			)
		)
		{
			EWindow::operable_button = NULL;
			//if (is_slider)
		}
		//text = "-";

	if (!grid_region_list.empty())
		for (EGridRegion* gr : grid_region_list)
		{
			//left
			if
				(
					(EWindow::mouse_x >= screen_position_x + (*gr->position_x + *gr->size_x * 0.0f) * icon_size_multiplier - 5.0f)
					&
					(EWindow::mouse_x <= screen_position_x + (*gr->position_x + *gr->size_x * 0.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_y >= screen_position_y + (*gr->position_y + *gr->size_y * 0.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_y <= screen_position_y + (*gr->position_y + *gr->size_y * 1.0f) * icon_size_multiplier + 0.0f)
					&
					(!*gr->locked_left_side)
					)
			{
				if (!EWindow::LMB) { *gr->cathed_left_side = true; }
			}
			else
			{
				if (!EWindow::LMB) { *gr->cathed_left_side = false; }
			}

			//right
			if
				(
					(EWindow::mouse_x >= screen_position_x + (*gr->position_x + *gr->size_x * 1.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_x <= screen_position_x + (*gr->position_x + *gr->size_x * 1.0f) * icon_size_multiplier + 5.0f)
					&
					(EWindow::mouse_y >= screen_position_y + (*gr->position_y + *gr->size_y * 0.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_y <= screen_position_y + (*gr->position_y + *gr->size_y * 1.0f) * icon_size_multiplier + 0.0f)
					&
					(!*gr->locked_right_side)
					)
			{
				if (!EWindow::LMB) { *gr->cathed_right_side = true; }
			}
			else
			{
				if (!EWindow::LMB) { *gr->cathed_right_side = false; }
			}

			//up
			if
				(
					(EWindow::mouse_x >= screen_position_x + (*gr->position_x + *gr->size_x * 0.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_x <= screen_position_x + (*gr->position_x + *gr->size_x * 1.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_y >= screen_position_y + (*gr->position_y + *gr->size_y * 1.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_y <= screen_position_y + (*gr->position_y + *gr->size_y * 1.0f) * icon_size_multiplier + 5.0f)
					&
					(!*gr->locked_up_side)
					)
			{
				if (!EWindow::LMB) { *gr->cathed_up_side = true; }
			}
			else
			{
				if (!EWindow::LMB) { *gr->cathed_up_side = false; }
			}

			//down
			if
				(
					(EWindow::mouse_x >= screen_position_x + (*gr->position_x + *gr->size_x * 0.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_x <= screen_position_x + (*gr->position_x + *gr->size_x * 1.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_y >= screen_position_y + (*gr->position_y + *gr->size_y * 0.0f) * icon_size_multiplier + 0.0f)
					&
					(EWindow::mouse_y <= screen_position_y + (*gr->position_y + *gr->size_y * 0.0f) * icon_size_multiplier + 5.0f)
					&
					(!*gr->locked_down_side)
					)
			{
				if (!EWindow::LMB) { *gr->cathed_down_side = true; }
			}
			else
			{
				if (!EWindow::LMB) { *gr->cathed_down_side = false; }
			}

			if (EWindow::LMB)
			{
				if (*gr->cathed_left_side)
				{
					*gr->position_x += EWindow::mouse_speed_x * 0.1f;

					*gr->position_x = min(*gr->position_x, button_size_x / icon_size_multiplier - *gr->size_x);
					*gr->position_x = max(*gr->position_x, 0.0f);
				}

				if (*gr->cathed_right_side)
				{
					*gr->size_x += EWindow::mouse_speed_x * 0.1f;

					*gr->size_x = min(*gr->size_x, button_size_x / icon_size_multiplier - *gr->position_x);
					*gr->size_x = max(*gr->size_x, 1.0f);
				}

				if (*gr->cathed_up_side)
				{
					*gr->size_y += EWindow::mouse_speed_y * 0.1f;

					*gr->size_y = min(*gr->size_y, button_size_y / icon_size_multiplier - *gr->position_y);
					*gr->size_y = max(*gr->size_y, 1.0f);
				}
				if (*gr->cathed_down_side)
				{
					*gr->position_y += EWindow::mouse_speed_y * 0.1f;

					*gr->position_y = min(*gr->position_y, button_size_y / icon_size_multiplier - *gr->size_y);
					*gr->position_y = max(*gr->position_y, 0.0f);
				}
			}
		}

	
	if (polygon_massive != NULL)
	{
		for (Batcher::EPolygonShape* p_shape : polygon_massive->shape_list)
		{
			int vertex_id = 0;

			

			//catch vertex
			for (Batcher::EPolygonVertex* p_vertex : p_shape->vertex_list)
			{


				if
					(
						(EWindow::mouse_x >= screen_position_x + button_size_x * *p_vertex->position_x - 5.0f)
						&
						(EWindow::mouse_x <= screen_position_x + button_size_x * *p_vertex->position_x + 5.0f)
						&
						(EWindow::mouse_y >= screen_position_y + button_size_y * *p_vertex->position_y - 5.0f)
						&
						(EWindow::mouse_y <= screen_position_y + button_size_y * *p_vertex->position_y + 5.0f)
						)
				{
					if (!EWindow::LMB)
					{
						*p_vertex->is_catched = true;
					}

				}
				else
				{
					if (!EWindow::LMB)
					{
						*p_vertex->is_catched = false;
					}
				}
			}

			//catch borders
			if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS)
			{
				*p_shape->catched_left_side
					=
					is_catched_by_mouse
					(
						*p_shape->catched_left_side,
						screen_position_x + *p_shape->pos_x * button_size_x - 3.0f,
						screen_position_y + *p_shape->pos_y * button_size_y,
						(*p_shape->size_x - *p_shape->pos_x) * button_size_x,
						(*p_shape->size_y - *p_shape->pos_y) * button_size_y,
						2.0f,
						CatchMethod::CATCH_METHOD_BORDER_LEFT
					);

				*p_shape->vertex_list.at(2)->is_catched |= *p_shape->catched_left_side;
				*p_shape->vertex_list.at(3)->is_catched |= *p_shape->catched_left_side;
				//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*
				*p_shape->catched_right_side
					=
					is_catched_by_mouse
					(
						*p_shape->catched_right_side,
						screen_position_x + *p_shape->pos_x * button_size_x,
						screen_position_y + *p_shape->pos_y * button_size_y,
						(*p_shape->size_x - *p_shape->pos_x) * button_size_x,
						(*p_shape->size_y - *p_shape->pos_y) * button_size_y,
						2.0f,
						CatchMethod::CATCH_METHOD_BORDER_RIGHT
					);

				*p_shape->vertex_list.at(1)->is_catched |= *p_shape->catched_right_side;
				*p_shape->vertex_list.at(0)->is_catched |= *p_shape->catched_right_side;

				//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*
				*p_shape->catched_down_side
					=
					is_catched_by_mouse
					(
						*p_shape->catched_down_side,
						screen_position_x + *p_shape->pos_x * button_size_x,
						screen_position_y + *p_shape->pos_y * button_size_y,
						(*p_shape->size_x - *p_shape->pos_x) * button_size_x,
						(*p_shape->size_y - *p_shape->pos_y) * button_size_y,
						2.0f,
						CatchMethod::CATCH_METHOD_BORDER_DOWN
					);

				*p_shape->vertex_list.at(1)->is_catched |= *p_shape->catched_down_side;
				*p_shape->vertex_list.at(2)->is_catched |= *p_shape->catched_down_side;
				//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*
				*p_shape->catched_up_side
					=
					is_catched_by_mouse
					(
						*p_shape->catched_up_side,
						screen_position_x + *p_shape->pos_x * button_size_x,
						screen_position_y + *p_shape->pos_y * button_size_y,
						(*p_shape->size_x - *p_shape->pos_x) * button_size_x,
						(*p_shape->size_y - *p_shape->pos_y) * button_size_y,
						2.0f,
						CatchMethod::CATCH_METHOD_BORDER_UP
					);

				*p_shape->vertex_list.at(0)->is_catched |= *p_shape->catched_up_side;
				*p_shape->vertex_list.at(3)->is_catched |= *p_shape->catched_up_side;
				//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*
				*p_shape->catched_mid_side
					=
					is_catched_by_mouse
					(
						*p_shape->catched_mid_side,
						screen_position_x + *p_shape->pos_x * button_size_x,
						screen_position_y + *p_shape->pos_y * button_size_y,
						(*p_shape->size_x - *p_shape->pos_x) * button_size_x,
						(*p_shape->size_y - *p_shape->pos_y) * button_size_y,
						2.0f,
						CatchMethod::CATCH_METHOD_MID
					);

				*p_shape->vertex_list.at(0)->is_catched |= *p_shape->catched_mid_side;
				*p_shape->vertex_list.at(1)->is_catched |= *p_shape->catched_mid_side;
				*p_shape->vertex_list.at(2)->is_catched |= *p_shape->catched_mid_side;
				*p_shape->vertex_list.at(3)->is_catched |= *p_shape->catched_mid_side;
			}
			if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS)
			{
				*p_shape->pos_x = 1.0f;
				*p_shape->pos_y = 1.0f;
				*p_shape->size_x = 0.0f;
				*p_shape->size_y = 0.0f;
			}

			//move vertex
			for (Batcher::EPolygonVertex* p_vertex : p_shape->vertex_list)
			{
				if
				(
					(EWindow::LMB)
					&
					(*p_vertex->is_catched)
				)
				{
					for (Batcher::EPolygonShape* p_shape2 : polygon_massive->shape_list)
					{
						p_shape2->selected_vertex = NULL;
					}

					p_shape->selected_vertex = p_vertex;

					if
						(
							(!*p_shape->catched_up_side)
							&
							(!*p_shape->catched_down_side)
						)
					{
						*p_vertex->position_x += EWindow::mouse_speed_x / button_size_x;
					}

					if
						(
							(!*p_shape->catched_left_side)
							&
							(!*p_shape->catched_right_side)
						)
					{
						*p_vertex->position_y += EWindow::mouse_speed_y / button_size_y;
					}

					EMath::clamp_value_float(p_vertex->position_x, 0.0f, 1.0f);
					EMath::clamp_value_float(p_vertex->position_y, 0.0f, 1.0f);

					if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
					{
						EMath::clamp_value_float(p_vertex->position_x, *p_shape->pos_x, *p_shape->size_x);
						EMath::clamp_value_float(p_vertex->position_y, *p_shape->pos_y, *p_shape->size_y);
					}

					if
						(
							(
								*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_UP)->position_x - 0.001f
								<
								*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_UP)->position_x
							)
							&
							(
								vertex_id == PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_UP
							)
						)
					{
						*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_UP)->position_x
						=
						*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_UP)->position_x - 0.001f;
					}

					if
						(
							(
								*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_UP)->position_x
								<
								*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_UP)->position_x + 0.001f
								)
							&
							(
								vertex_id == PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_UP
							)
						)
					{
						*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_UP)->position_x
						=
						*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_UP)->position_x + 0.001f;
					}

					if
						(
							(
								*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_DOWN)->position_x - 0.001f
								<
								*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_DOWN)->position_x
							)
							&
							(
								vertex_id == PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_DOWN
							)
						)
					{
						*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_DOWN)->position_x
						=
						*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_RIGHT_DOWN)->position_x - 0.001f;
					}
				}

				
				if (*p_vertex->position_x < *p_shape->pos_x)
				{
					*p_shape->pos_x = *p_vertex->position_x;
				}

				if (*p_vertex->position_y < *p_shape->pos_y)
				{
					*p_shape->pos_y = *p_vertex->position_y;
				}

				if (*p_vertex->position_x > *p_shape->size_x)
				{
					*p_shape->size_x = *p_vertex->position_x;
				}

				if (*p_vertex->position_y > *p_shape->size_y)
				{
					*p_shape->size_y = *p_vertex->position_y;
				}


				vertex_id++;
			}

			
			

			//*p_shape->vertex_list.at(PolygonVertexName::POLYGON_VERTEX_NAME_LEFT_UP)->position_x = 0.5f;

			
		}
	}

	if (two_dimension_gradient != NULL)
	{
		*two_dimension_gradient->is_catched
			=
			is_catched_by_mouse
			(
				*two_dimension_gradient->is_catched,
				screen_position_x + *two_dimension_gradient->value_x * button_size_x,
				screen_position_y + *two_dimension_gradient->value_y * button_size_y,
				0.0f,
				0.0f,
				5.0f,
				CatchMethod::CATCH_METHOD_FREE
			);


		if
		(
			(EWindow::LMB)			
		)
		{
			
				if
				(
					(!*two_dimension_gradient->is_catched)
					&
					(is_overlap())
				)
				{
					*two_dimension_gradient->value_x = (EWindow::mouse_x - screen_position_x) / button_size_x;
					*two_dimension_gradient->value_y = (EWindow::mouse_y - screen_position_y) / button_size_y;

					if (!action_on_td_gradient_drag.empty())
					{
						for (BUTTON_ACTION ba : action_on_td_gradient_drag)
						{ba(this, _d);}
					}

					if (EWindow::operable_button == NULL) { EWindow::operable_button = this; }
				}

				
				if (*two_dimension_gradient->is_catched)
				{
					*two_dimension_gradient->value_x += get_mouse_speed_x() / button_size_x;
					*two_dimension_gradient->value_y += get_mouse_speed_y() / button_size_y;

					if (!action_on_td_gradient_drag.empty())
					{
						for (BUTTON_ACTION ba : action_on_td_gradient_drag)
						{ba(this, _d);}
					}

					if (EWindow::operable_button == NULL) { EWindow::operable_button = this; }
				}
			

			EMath::clamp_value_float(two_dimension_gradient->value_x, 0.0f, 1.0f);
			EMath::clamp_value_float(two_dimension_gradient->value_y, 0.0f, 1.0f);

			
		}
	}
}

void EButton::update_additional(float _d)
{
}

void EButton::default_draw(Batcher* _batch, float _d)
{
	//std::cout << "!" << std::endl;
	EFont::active_font->scale = 1.0f;
	if (is_overlap())
	{
		_batch->setcolor_255(0, 200, 0, 100);
	}
	else
	{
		_batch->setcolor_255(20, 30, 45, 17);
	}

	if (is_input_mode_active)
	{
		_batch->setcolor_255(220, 255, 200, 100);
	}

	//std::cout << "red color is:" << _batch->batch_color_r;

	if ((have_bg) & (EGraphicCore::gabarite_small_wood_button_bg != NULL))
	{
		_batch->setcolor(bg_color);
		_batch->draw_gabarite(screen_position_x, screen_position_y, button_size_x, button_size_y, EGraphicCore::gabarite_small_wood_button_bg);
	}

	float temp_w = 0;

	if ((have_icon) & (gabarite != NULL))
	{
		if (icon_adaptation)
		{
			//float mul_x = 1;
			//float mul_y = 1;

			_batch->setcolor(icon_color);
			_batch->draw_gabarite(screen_position_x + round((button_size_x - *gabarite->size_x * icon_size_multiplier) / 2.0f), screen_position_y, *gabarite->size_x * icon_size_multiplier, *gabarite->size_y * icon_size_multiplier, gabarite);
		}
		else
		{
			_batch->setcolor(icon_color);
			_batch->draw_gabarite(screen_position_x, screen_position_y, button_size_x, button_size_y, gabarite);
		}
	}

	EFont* target_font = EFont::active_font;

	if (have_text)
	{
		if (force_font != NULL) { target_font = force_font; }

		float added_x = 0;

		if (text_align_x == Enums::PositionMode::MID) { added_x = (button_size_x / 2.0f); }
		target_font->align_x = text_align_x;

		if (text != "")
		{
			_batch->setcolor(text_color);
			target_font->draw(_batch, text, screen_position_x + 3.0f + added_x, screen_position_y + ((button_size_y - 20.0f) / 2.0f + 4.0f));
		}

		if ((text == "") && (input_hint != ""))
		{
			_batch->setcolor(0.2f, 0.2f, 0.2f, 0.8f);
			target_font->draw(_batch, input_hint, screen_position_x + 3.0f + added_x, screen_position_y + ((button_size_y - 20.0f) / 2.0f + 4.0f));
		}

		if (is_input_mode_active)
		{
			if (flash_line_active)
			{
				_batch->setcolor(EColor::COLOR_BLACK);
				_batch->draw_gabarite(screen_position_x + 3.0f + EFont::get_width(target_font, text) + added_x, screen_position_y + (button_size_y - 20.0f) / 2.0f + 4.0f, 3.0f, 17, EGraphicCore::gabarite_white_pixel);
			}
		}
	}

	/*if (*side_text != "")
	{
		target_font->draw_with_background(*side_text, _batch, screen_position_x - 8.0f - EFont::get_width(target_font, *side_text), screen_position_y + ((button_size_y - 20.0f) / 2.0f + 0.0f), EColor::COLOR_LIGHT_GRAY, EColor::COLOR_DARK_GRAY);
	}*/

	//20:12:17 08.07.2021
	//Jvnko Still Loves You
	//Sewerslvt
	if (*side_text != "")
	{
		target_font->draw_with_background(*side_text, _batch, screen_position_x, screen_position_y + button_size_y - 20.0f, EColor::COLOR_LIGHT_GRAY, EColor::COLOR_DARK_GRAY);
	}

	

	if (have_rama)
	{
		if (dragged_button == this)
		{
			_batch->setcolor(EColor::COLOR_RED);
		}
		else
		{
			_batch->setcolor(rama_color);
		}

		_batch->draw_rama(screen_position_x, screen_position_y, button_size_x, button_size_y, rama_thikness, EGraphicCore::gabarite_small_wood_button_bg);
	}

	if (is_slider)
	{
		if (slider_is_horizontal)
		{
			_batch->setcolor(EColor::COLOR_WHITE);
			_batch->draw_gabarite(screen_position_x + (button_size_x - 3.0f) * slider_value / *maximum_value - 1, screen_position_y - 1, 5, button_size_y + 2, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_BLACK);
			_batch->draw_gabarite(screen_position_x + (button_size_x - 3.0f) * slider_value / *maximum_value, screen_position_y, 3, button_size_y, EGraphicCore::gabarite_white_pixel);
		}
		else
		{
			_batch->setcolor(EColor::COLOR_WHITE);
			_batch->draw_gabarite(screen_position_x - 1, screen_position_y - 31.0f + button_size_y - (button_size_y - 32.0f) * slider_value / *maximum_value, button_size_x + 2, 32.0f, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_BLACK);
			_batch->draw_gabarite(screen_position_x, screen_position_y - 30.0f + button_size_y - (button_size_y - 32.0f) * slider_value / *maximum_value, button_size_x, 32.0f, EGraphicCore::gabarite_white_pixel);
		}
	}

	additional_draw(_batch, _d);

	if (is_overlap())
	{
		_batch->setcolor_alpha(EColor::COLOR_GREEN, 0.25f);
		_batch->draw_gabarite(screen_position_x - 3.0f, screen_position_y - 3.0f, button_size_x + 6.0f, button_size_y + 6.0f, EGraphicCore::gabarite_white_pixel);

		_batch->setcolor_alpha(EColor::COLOR_GREEN, 1.0f);
		if ((dragged_button != NULL) & (flash_line_active))
		{
			if (EWindow::mouse_x < screen_position_x + button_size_x / 2.0f)
			{
				_batch->draw_gabarite(screen_position_x - 3.0f, screen_position_y, 3.0f, button_size_y, EGraphicCore::gabarite_white_pixel);
			}
			else
			{
				_batch->draw_gabarite(screen_position_x + button_size_x, screen_position_y, 3.0f, button_size_y, EGraphicCore::gabarite_white_pixel);
			}
		}
	}

	if (*is_radial_button)
	{
		float tsx = EFont::get_width(EFont::font_list.at(EFont::FONT_ENUM::FE_DOT), EString::float_to_string(round(slider_value * 100.0f) / 100.0f));
		//float tx
		float tsy = 5.0f;

		float tx = (*EGraphicCore::gabarite_radial_button->size_x - tsx) / 2.0f;
		tx = 35.0f;

		_batch->setcolor(bg_color);
		_batch->draw_gabarite(screen_position_x, screen_position_y, EGraphicCore::gabarite_radial_button);

		_batch->setcolor_lum(EColor::COLOR_WHITE, 0.12f);
		_batch->draw_gabarite(screen_position_x + tx - 2.0f, screen_position_y + tsy - 2.0f, tsx + 5.0f, 25.0f, EGraphicCore::gabarite_white_pixel);

		_batch->setcolor(text_color);
		EFont::font_list.at(EFont::FONT_ENUM::FE_DOT)->draw(_batch, EString::float_to_string(round(slider_value * 100.0f) / 100.0f) + "", screen_position_x + tx, screen_position_y + tsy);

		_batch->setcolor(EColor::COLOR_WHITE);
		_batch->draw_gabarite(screen_position_x + cos(3.14f * (1.0f - slider_value / *maximum_value)) * 13.0f + 13.0f, screen_position_y + sin(3.14f * (1.0f - slider_value / *maximum_value)) * 13.0f + 13.0f, EGraphicCore::gabarite_radial_button_dot);
	}

	if (*is_checkbox)
	{
		if (*is_checked)
		{
			_batch->setcolor(EColor::COLOR_GREEN);
			_batch->draw_rama(screen_position_x + button_size_x + 2.0f - button_size_y, screen_position_y + 2.0f, button_size_y - 4.0f, button_size_y - 4.0f, 2.0f, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_DARK_GREEN);
			_batch->draw_gabarite(screen_position_x + button_size_x + 4.0f - button_size_y, screen_position_y + 4.0f, button_size_y - 8.0f, button_size_y - 8.0f, EGraphicCore::gabarite_white_pixel);

			rama_color->set_color(EColor::COLOR_WHITE);
			bg_color->set_color(EColor::COLOR_LIME);
			text_color->set_color(EColor::COLOR_BLACK);
		}
		else
		{
			_batch->setcolor(EColor::COLOR_RED);
			_batch->draw_rama(screen_position_x + button_size_x + 2.0f - button_size_y, screen_position_y + 2.0f, button_size_y - 4.0f, button_size_y - 4.0f, 2.0f, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_BLACK);
			_batch->draw_gabarite(screen_position_x + button_size_x + 4.0f - button_size_y, screen_position_y + 4.0f, button_size_y - 8.0f, button_size_y - 8.0f, EGraphicCore::gabarite_white_pixel);

			rama_color->set_color(EColor::COLOR_RED);
			bg_color->set_color(EColor::COLOR_RED);
			text_color->set_color(EColor::COLOR_WHITE);
		}
	}

	if (!grid_region_list.empty())
		for (EGridRegion* gr : grid_region_list)
		{
			_batch->setcolor_alpha(EColor::COLOR_BLUE, 0.8f);
			_batch->draw_rama(screen_position_x + *gr->position_x * icon_size_multiplier, screen_position_y + *gr->position_y * icon_size_multiplier, *gr->size_x * icon_size_multiplier, *gr->size_y * icon_size_multiplier, 1.0f, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor_alpha(EColor::COLOR_BLUE, 0.5f);

			float subdivided_line_size = *gr->size_x / (*gr->subdivision_x + 1.0f);

			if (*gr->subdivision_x > 0)
				for (int i = 1; i <= *gr->subdivision_x; i++)
				{
					_batch->draw_gabarite
					(
						screen_position_x + (*gr->position_x + subdivided_line_size * i) * icon_size_multiplier,
						screen_position_y + *gr->position_y * icon_size_multiplier,
						1.0f,
						*gr->size_y * icon_size_multiplier, EGraphicCore::gabarite_white_pixel
					);
				}
			subdivided_line_size = *gr->size_y / (*gr->subdivision_y + 1.0f);
			if (*gr->subdivision_y > 0)
				for (int i = 1; i <= *gr->subdivision_y; i++)
				{
					_batch->draw_gabarite
					(
						screen_position_x + *gr->position_x * icon_size_multiplier,
						screen_position_y + (*gr->position_y + subdivided_line_size * i) * icon_size_multiplier,
						*gr->size_x * icon_size_multiplier,
						1.0f,
						EGraphicCore::gabarite_white_pixel
					);
				}

			_batch->setcolor_alpha(EColor::COLOR_PINK, 0.8f);
			if (*gr->cathed_left_side) { _batch->draw_gabarite(screen_position_x + *gr->position_x * icon_size_multiplier - 5.0f, screen_position_y + *gr->position_y * icon_size_multiplier, 5.0f, *gr->size_y * icon_size_multiplier, EGraphicCore::gabarite_white_pixel); }
			if (*gr->cathed_right_side) { _batch->draw_gabarite(screen_position_x + (*gr->position_x + *gr->size_x) * icon_size_multiplier, screen_position_y + *gr->position_y * icon_size_multiplier, 5.0f, *gr->size_y * icon_size_multiplier, EGraphicCore::gabarite_white_pixel); }
			if (*gr->cathed_up_side) { _batch->draw_gabarite(screen_position_x + *gr->position_x * icon_size_multiplier, screen_position_y + (*gr->position_y + *gr->size_y) * icon_size_multiplier, *gr->size_x * icon_size_multiplier, 5.0f, EGraphicCore::gabarite_white_pixel); }
			if (*gr->cathed_down_side) { _batch->draw_gabarite(screen_position_x + *gr->position_x * icon_size_multiplier, screen_position_y + *gr->position_y * icon_size_multiplier, *gr->size_x * icon_size_multiplier, 5.0f, EGraphicCore::gabarite_white_pixel); }
		}

	if
	(
		(polygon_massive != NULL)
		&
		(!mode_list.empty())
	)
	{
		_batch->setcolor(EColor::COLOR_WHITE);
		if (*mode_list.at(0) == PolygonDrawMode::POLYGON_DRAW_MODE_DEPTH)
		{
			_batch->draw_depthmap_polygon
			(
				polygon_massive,
				screen_position_x,
				screen_position_y,
				button_size_x,
				button_size_y,
				EGraphicCore::gabarite_white_pixel
			);
		}

		if (*mode_list.at(0) == PolygonDrawMode::POLYGON_DRAW_MODE_NORMAL_MAP)
		{
			_batch->draw_normalmap_polygon
			(
				polygon_massive,
				screen_position_x,
				screen_position_y,
				button_size_x,
				button_size_y,
				EGraphicCore::gabarite_white_pixel
			);
		}

		
		for (Batcher::EPolygonShape* p_shape : polygon_massive->shape_list)
		{
			for (Batcher::EPolygonVertex* p_vertex : p_shape->vertex_list)
			{
				if (*p_vertex->is_catched)
				{
					_batch->setcolor(EColor::COLOR_GREEN);
					_batch->draw_gabarite
					(
						screen_position_x + *p_vertex->position_x * button_size_x - 2.0f,
						screen_position_y + *p_vertex->position_y * button_size_y - 2.0f,
						5.0f,
						5.0f,
						EGraphicCore::gabarite_white_pixel
					);
				}

				if
					(
						(p_shape->selected_vertex != NULL)
						&&
						(p_shape->selected_vertex == p_vertex)
						)
				{
					_batch->setcolor(EColor::COLOR_YELLOW);

					_batch->draw_gabarite
					(
						screen_position_x + *p_vertex->position_x * button_size_x - 1.0f,
						screen_position_y + *p_vertex->position_y * button_size_y - 1.0f,
						3.0f,
						3.0f,
						EGraphicCore::gabarite_white_pixel
					);
				}

				
			}

			if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			{
				_batch->setcolor_alpha(EColor::COLOR_RED, 0.75f);
				
			}
			else
			{
				_batch->setcolor_alpha(EColor::COLOR_WHITE, 0.5f);
			}
			
			_batch->draw_rama
			(
				screen_position_x + *p_shape->pos_x * button_size_x,
				screen_position_y + *p_shape->pos_y * button_size_y,
				(*p_shape->size_x - *p_shape->pos_x) * button_size_x,
				(*p_shape->size_y - *p_shape->pos_y) * button_size_y,
				1.0f,
				EGraphicCore::gabarite_white_pixel
			);

			_batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
			if (*p_shape->catched_left_side)
			{
				_batch->draw_gabarite
				(
					screen_position_x + *p_shape->pos_x * button_size_x,
					screen_position_y + *p_shape->pos_y * button_size_y,
					3.0f,
					(*p_shape->size_y - *p_shape->pos_y)* button_size_y,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (*p_shape->catched_right_side)
			{
				_batch->draw_gabarite
				(
					screen_position_x + *p_shape->size_x * button_size_x,
					screen_position_y + *p_shape->pos_y * button_size_x,
					3.0f,
					(*p_shape->size_y - *p_shape->pos_y) * button_size_y,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (*p_shape->catched_down_side)
			{
				_batch->draw_gabarite
				(
					screen_position_x + *p_shape->pos_x * button_size_x,
					screen_position_y + *p_shape->pos_y * button_size_y,
					(*p_shape->size_x - *p_shape->pos_x)* button_size_x,
					3.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (*p_shape->catched_up_side)
			{
				_batch->draw_gabarite
				(
					screen_position_x + *p_shape->pos_x * button_size_x,
					screen_position_y + *p_shape->size_y * button_size_y,
					(*p_shape->size_x - *p_shape->pos_x)* button_size_x,
					3.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (*p_shape->catched_mid_side)
			{
				_batch->draw_gabarite
				(
					screen_position_x + (*p_shape->pos_x + *p_shape->size_x) / 2.0f * button_size_x - 3.0f,
					screen_position_y + (*p_shape->pos_y + *p_shape->size_y) / 2.0f * button_size_y - 3.0f,
					7.0f,
					7.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}
		}
		/*for (Batcher::EPolygonShape* p_massive : polygon_massive->shape_list)
		{
			for (Batcher::EPolygonVertex* p_vertex : p_massive->vertex_list)
			{
				if (*mode_list.at(0) == PolygonDrawMode::POLYGON_DRAW_MODE_DEPTH)
				{
					_batch-> draw_depthmap_polygon()
				}
			}
		}*/
	}

	if
	(
		(two_dimension_gradient != NULL)
	)
	{

		if (*two_dimension_gradient->draw_gradient)
		{
			_batch->draw_two_dimension_gradient
			(
				screen_position_x,
				screen_position_y,
				button_size_x,
				button_size_y,
				EGraphicCore::gabarite_white_pixel,
				two_dimension_gradient->color_x,
				two_dimension_gradient->color_y
			);
		}

		if (*two_dimension_gradient->is_catched)
		{
			_batch->setcolor(EColor::COLOR_GREEN);
		}
		else
		{
			_batch->setcolor(EColor::COLOR_WHITE);
		}

		//
		//------
		//
		_batch->draw_gabarite
		(
			screen_position_x,
			screen_position_y + *two_dimension_gradient->value_y * button_size_y,
			button_size_x,
			1.0f,
			EGraphicCore::gabarite_white_pixel
		);

		//	|
		//	|
		//	|
		_batch->draw_gabarite
		(
			screen_position_x + *two_dimension_gradient->value_x * button_size_x,
			screen_position_y,
			1.0f,
			button_size_y,
			EGraphicCore::gabarite_white_pixel
		);



	}

	if (EWindow::operable_button == this)
	{
		_batch->setcolor(EColor::COLOR_BLUE);
		_batch->draw_rama(screen_position_x, screen_position_y, button_size_x, button_size_y, 5.0f, EGraphicCore::gabarite_small_wood_button_bg);
	}
}

void EButton::additional_draw(Batcher* _batch, float _d)
{
	//std::cout << "Default" << std::endl;
}

void EButton::text_pass(Batcher* _batch)
{
	catched_element = (int)((screen_position_y - EWindow::mouse_y) / 22.0f);
	if (is_expanded)
	{
		bound_size_down = drop_elements * 22;

		for (int i = 0; i < drop_elements; i++)
		{
			if (catched_element == i)
			{
				_batch->setcolor(0.05f, 0.10f, 0.06f, 1.0f);
			}
			else
			{
				if (have_list_color)
				{
					_batch->setcolor(drop_list_color.at(i));
				}
				else
				{
					_batch->setcolor(0.8f, 0.9f, 1.0f, 1.0f);
				}
			}

			_batch->draw_gabarite(screen_position_x, screen_position_y - i * 22 - 20, button_size_x, 20, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(0.0f, 0.1f, 0.2f, 0.9f);
			_batch->draw_rama(screen_position_x, screen_position_y - i * 22 - 20, button_size_x, 20, rama_thikness, EGraphicCore::gabarite_white_pixel);

			if (catched_element == i)
			{
				_batch->setcolor(0.95f, 0.90f, 0.94f, 1.0f);
			}
			else
			{
				_batch->setcolor(EColor::COLOR_BLACK);
			}
			EFont::active_font->set_align_once(Enums::PositionMode::MID);
			EFont::active_font->draw(_batch, drop_text.at(i), screen_position_x + button_size_x / 2.0f, screen_position_y - i * 22 - 20 + 3);
		}
	}
	else
	{
		bound_size_down = 0;
	}

	/*if (prev_description_text != description_text)
	{
		//std::cout << "description changed from <" << prev_description_text << "> to [" << description_text << ">" << std::endl;

		//prev_description_text = description_text;
	}*/

	if ((have_description) && (is_overlap()) && (description_text != ""))
		//if (is_overlap() && (have_description))
	{
		EFont* target_font = EFont::active_font;

		float th = EFont::get_height(target_font, description_text) + 5.0f;

		if (force_font != NULL)
		{
			target_font = force_font;
		}

		float x_description = EWindow::mouse_x + 20.0f;
		if (x_description + EFont::get_width(target_font, description_text) + 5 > EGraphicCore::SCR_WIDTH)
		{
			x_description += EGraphicCore::SCR_WIDTH - (x_description + EFont::get_width(target_font, description_text) + 5.0f);
		}

		target_font->align_x = Enums::PositionMode::LEFT;

		_batch->setcolor(EColor::COLOR_WHITE);
		_batch->draw_gabarite(x_description, EWindow::mouse_y - 20.0f - th, EFont::get_width(target_font, description_text) + 8, th, EGraphicCore::gabarite_white_pixel);

		_batch->setcolor(EColor::COLOR_BLACK);
		target_font->draw(_batch, description_text, x_description + 5.0f, EWindow::mouse_y - 34.0f);

		_batch->draw_rama(x_description, EWindow::mouse_y - 20.0f - th, EFont::get_width(target_font, description_text) + 8, th, 2, EGraphicCore::gabarite_white_pixel);
	}

	if ((is_slider) && (slider_activate))
	{
		EFont* target_font = EFont::active_font;
		float th = EFont::get_height(target_font, std::to_string(slider_value * slider_value_multiplier)) + 5.0f;

		_batch->setcolor(EColor::COLOR_WHITE);
		_batch->draw_gabarite(EWindow::mouse_x + 10.0f, EWindow::mouse_y - 20.0f - th, EFont::get_width(target_font, std::to_string(slider_value * slider_value_multiplier)) + 8, th, EGraphicCore::gabarite_white_pixel);

		_batch->setcolor(EColor::COLOR_BLACK);
		target_font->draw(_batch, std::to_string(slider_value * slider_value_multiplier / *maximum_value), EWindow::mouse_x + 15.0f, EWindow::mouse_y - 34.0f);
	}
}

void EButton::click_event()
{
	if ((master_group != NULL) & (*can_be_selected))
	{
		master_group->selected_button = this;
	}
	//std::cout << "STANDART click event" << std::endl;
}

void EButton::right_click_event()
{
}

void EButton::input_event()
{
	//hide or show button on target button group
	for (SimpleButtonSearchDeactivator* sbsd : simple_button_search_deactivator_list)
	{
		//std::cout << "@" << std::endl;
		if ((sbsd != NULL) && (sbsd->target_button_group != NULL))
		{
			for (EButton* b : sbsd->target_button_group->button_list)
				if ((*b->can_be_hidden_by_search_deactivator))
				{
					bool valid_match = false;
					//std::cout << "!" << std::endl;
					if
						(
							(*sbsd->is_search_by_text)
							&
							(b->text.find(text) != std::string::npos)
							)
					{
						valid_match = true;
					}

					if
						(
							(*sbsd->is_search_by_description)
							)
					{
						if (b->description_text.find(text) != std::string::npos)
						{
							valid_match = true;
						}
						else
						{
							//	std::cout << "string [" << b->description_text << "] not contain [" << text << "]" << std::endl;
						}
					}

					if
						(
							(*sbsd->is_search_by_data_string)
							&
							(b->data_string.find(text) != std::string::npos)
							)
					{
						valid_match = true;
					}

					if (valid_match)
					{
						*sbsd->target_button_group->button_y_scroll = 0.0f;
					}
					b->is_active = valid_match;
					//b->text = "!";
				}
				else
				{
					if (sbsd == NULL) { std::cout << "ERROR: SBSD is NULL!" << std::endl; }
					else
						if (sbsd->target_button_group == NULL)
						{
							std::cout << "ERROR: SBSD target group is NULL!" << std::endl;
						}
				}
		}
	}
}

void EButton::input_finish_event()
{
}

void EButton::drop_list_select_event()
{
}

void EButton::slider_drag_event()
{
}

void EButton::update_localisation()
{
	/* the ampersand is actually optional */

	//std::cout << "DEFAULT LOCAL" << std::endl;
}

EButton* EButton::clone_button(EButton* _b, float _x, float _y, float _sx, float _sy)
{
	EButton* but = new EButton(*_b);

	but->button_base_x = _x;
	but->button_x_offset = _x;

	but->button_base_y = _y;
	but->button_y_offset = _y;

	return but;
}

void EButton::update_data_id_for_buttons(button_group* _bg)
{
	int id = 0;
	EButton* last_button = NULL;
	for (int i = 0; i < _bg->button_list.size(); i++)
	{
		//if (*_bg->button_list.at(i)->can_be_selected) { last_button = _bg->button_list.at(i); }

		if ((i + 1 < _bg->button_list.size()) && (*_bg->button_list.at(i + 1)->can_be_selected) && (!_bg->button_list.at(i)->is_active))
		{
			_bg->button_list.at(i)->gabarite = _bg->button_list.at(i + 1)->gabarite;
			_bg->button_list.at(i)->is_active = _bg->button_list.at(i + 1)->is_active;

			_bg->button_list.at(i)->update(0.1f);

			_bg->button_list.at(i + 1)->is_active = false;
		}
	}

	//last_button->is_active = false;
	//_bg->button_list.at(_bg->button_list.size() - 1)->is_active = 0;

	//std::cout << "size " << std::to_string(_bg->button_list.size()) << std::endl;
	for (int i = 0; i < _bg->button_list.size(); i++)
	{
		//std::cout << "WUT? " << std::to_string(i) << std::endl;
		if ((*_bg->button_list.at(i)->can_be_selected) & (_bg->button_list.at(i)->is_active))
		{
			_bg->button_list.at(i)->data_id = id;

			//_bg->button_list.at(i)->text = std::to_string(id);
			id++;
		}
	}
}

EButton::EButton(float _x, float _y, float _sx, float _sy, EWindow* _w, button_super_group* _bsg, button_group* _bg)
{
	button_x_offset = _x;
	button_y_offset = _y;

	button_base_x = _x;
	button_base_y = _y;

	button_size_x = _sx;
	button_size_y = _sy;

	//button_min_size_x = _sx;
	//button_min_size_y = _sy;

	master_window = _w;
	master_super_group = _bsg;
	master_group = _bg;

	update_localisation();
}

bool EButton::is_not_outside_of_group(EButton* _b, button_super_group* _bsg, button_group* _bg)
{
	if
		(
			(_b->button_y_offset <= *_bg->size_y + *_bg->position_y + *_bsg->position_y + 40.0f)
			&
			(_b->button_y_offset + _b->button_size_y >= *_bg->position_y + *_bsg->position_y - 40.0f)
			)
	{
		//_b->bg_color->set_color(EColor::COLOR_WHITE);
		//_b->have_icon = true;
		return true;
	}
	else
	{
		//_b->bg_color->set_color(EColor::COLOR_RED);
		//_b->have_icon = false;
		return false;
	}
}

bool EButton::is_not_outside_of_super_group(EButton* _b, button_super_group* _bsg)
{
	return false;
}

void EWindow::default_update(float _d)
{
	for (int i = 0; i < button_list.size(); i++)
	{
		if (*button_list.at(i)->need_remove)
		{
			button_list.erase(button_list.begin() + i);
		}
	}

	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->update(_d);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active) { b->update(_d); }
	}

	/*for (EButton::button_array_collection* z : button_array_collection_list)
	{
		z->update_button_position();
	}*/

	float add_offset_x = 0.0f;
	std::vector<float> maximum_button_size_x;
	maximum_button_size_x.clear();
	int array_id = 0;

	float maximum_size_of_horizontal = 0.0f;
	float maximum_size_of_vertical = 0.0f;
	float maximum_size_of_array = 0.0f;

	float h_base_offset_x = 0.0f;

	float button_added_position_x = 0.0f;
	float button_added_position_y = 0.0f;

	float maximum_button_gabarite_x = 0.0f;
	float maximum_button_gabarite_y = 0.0f;

	float maximum_group_size_x = 0.0f;
	float maximum_group_size_y = 0.0f;

	float base_x = 0.0f;
	float base_y = 0.0f;

	float previvous_button_size_x = 0.0f;
	float previvous_button_size_y = 0.0f;

	float previvous_button_position_x = 0.0f;
	float previvous_button_position_y = 0.0f;

	float previvous_group_push_x = 0.0f;
	float previvous_group_push_y = 0.0f;

	float group_total_offset_x = 0.0f;
	float group_total_offset_y = 0.0f;

	float maximum_button_group_size_x = 0.0f;
	float maximum_button_group_size_y = 0.0f;

	float group_baseline_y = 0.0f;

	//update buttons on button group and update button group
	for (EButton::button_super_group* bsg : button_group_list)
		if (*bsg->is_active)
		{
			previvous_group_push_x = 0.0f;
			previvous_group_push_y = 0.0f;

			maximum_button_group_size_x = 0.0f;
			maximum_button_group_size_y = 0.0f;

			if
				(
					(mouse_x >= *bsg->position_x)
					&
					(mouse_x <= *bsg->position_x + *bsg->size_x)
					&
					(mouse_y >= *bsg->position_y + *bsg->size_y)
					&
					(mouse_y <= *bsg->position_y + *bsg->size_y + 20.0f)
					&
					(EWindow::top_overlaped_group == bsg)
				)
			{
				if (!LMB) { *bsg->is_catched = true; }
			}
			else
			{
				if (!LMB) { *bsg->is_catched = false; }
			}

			if ((LMB) & (*bsg->is_catched) & (EWindow::operable_button == NULL))
			{
				*bsg->position_x += mouse_speed_x;
				*bsg->position_y += mouse_speed_y;
			}

			//*bsg->position_x += _d * 20.0f;



			for (EButton::button_group* bg : bsg->button_group_list)
			{
				//*bg->position_y
				if (*bg->can_be_stretched_x) { *bg->size_x *= 0.95f; }
				if (*bg->can_be_stretched_y) { *bg->size_y *= 0.95f; }

				if (*bg->selected_push_method == EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X)
				{
					//*bg->position_x = 0.0f;
					*bg->position_x = round(*bg->position_x);
					if (*bg->position_x < 0.0f) { *bg->position_x = 0.0f; }
				}

				//stretch by mouse right
				if (*bg->can_be_moved_by_user)
				{
					catch_right_side(bg, bsg);
					catch_left_side(bg, bsg);
					catch_up_side(bg, bsg);
					catch_down_side(bg, bsg);
				}

				maximum_button_gabarite_x = 0.0f;
				maximum_button_gabarite_y = 0.0f;

				base_x = 0.0f;
				base_y = 0.0f;

				previvous_button_position_x = *bsg->position_x + *bg->position_x + 5.0f;
				previvous_button_position_y = *bsg->position_y + *bg->position_y + 5.0f;

				previvous_button_size_x = 0.0f;
				previvous_button_size_y = 0.0f;

				group_total_offset_x = *bsg->position_x + *bg->position_x;
				group_total_offset_y = *bsg->position_y + *bg->position_y;

				if (*bg->selected_push_method == EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_Y)
				{
					if (*bg->size_x < maximum_button_group_size_x) { *bg->size_x = previvous_group_push_x; }
					if (*bg->position_y < previvous_group_push_y + 5.0f) { *bg->position_y = previvous_group_push_y + 5.0f; }
				}

				if (*bg->selected_push_method == EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X)
				{
					//if (*bg->size_x < maximum_button_group_size_x) { *bg->size_x = previvous_group_push_x; }
					/*if (*bg->position_x < previvous_group_push_x + 5.0f)*/ { *bg->position_x = previvous_group_push_x + 5.0f; }
				}

				if (*bg->selected_push_method == EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y)
				{
					//if (*bg->size_x < maximum_button_group_size_x) { *bg->size_x = previvous_group_push_x; }
					{ *bg->position_y = maximum_button_group_size_y + 5.0f; }

					maximum_button_group_size_y = *bg->size_y;
				}

				for (EButton* b : bg->button_list)
					if (b->is_active)
					{
						//if (b->description_text == "Entity #0")
						//{
						//	std::cout << "------- size" << std::to_string(bg->button_list.size()) << std::endl;
						//}

						//if (b->text == "Entity")
						//{
						//
						//	std::cout << std::to_string(previvous_button_position_y) << std::endl;
						//}

						//position relative screen
						if (*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE)
						{
							if (b->position_by_group_mode_x == Enums::PositionMode::LEFT)
							{
								b->button_x_offset = b->button_base_x + *bsg->position_x + *bg->position_x;
							}

							if (b->position_by_group_mode_x == Enums::PositionMode::RIGHT)
							{
								b->button_x_offset = b->button_base_x + *bsg->position_x + *bg->position_x + *bg->size_x - b->button_size_x - 5.0f;
							}

							{b->button_y_offset = b->button_base_y + *bsg->position_y + *bg->position_y; }
						}
						else
						{
							b->button_x_offset = *bsg->position_x + *bg->position_x + 5.0f + base_x;
							b->button_y_offset = *bsg->position_y + *bg->position_y + 5.0f + base_y + round(*bg->button_y_scroll * 20.0f);
						}

						if
							(
								(
									(!*bg->can_be_stretched_x)
									&
									(previvous_button_position_x + previvous_button_size_x + b->button_size_x + *bg->additional_right_side_bound_for_autostretch >= *bg->size_x + group_total_offset_x)
									&
									(*b->selected_auto_align_mode != EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE)
									)
								||
								(*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y)
								)
						{
							b->button_y_offset += maximum_button_gabarite_y + 5.0f;

							base_y += maximum_button_gabarite_y + 5.0f;
							maximum_button_gabarite_y = b->button_size_y;
						}

						if
							(
								((*bg->can_be_stretched_x) || (previvous_button_position_x + previvous_button_size_x + b->button_size_x + *bg->additional_right_side_bound_for_autostretch < *bg->size_x + group_total_offset_x))
								&
								(*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X)
								)
						{
							b->button_x_offset = previvous_button_position_x + previvous_button_size_x;

							if (b->button_size_x > maximum_button_gabarite_x) { maximum_button_gabarite_x = b->button_size_x; }
							if (b->button_size_y > maximum_button_gabarite_y) { maximum_button_gabarite_y = b->button_size_y; }
						}

						if (*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y)
						{
							//b->text = EString::float_to_string(previvous_button_position_y);
							b->button_x_offset = (previvous_button_position_x);
							b->button_y_offset = (previvous_button_position_y + previvous_button_size_y);
							//b->description_text = EString::float_to_string(previvous_button_position_y);

							if (b->button_size_x > maximum_button_gabarite_x) { maximum_button_gabarite_x = b->button_size_x; }
						}

						if (*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_Y_AND_ADD_X)
						{
							b->button_x_offset += maximum_button_gabarite_x + 5.0f;
							maximum_button_gabarite_x = b->button_size_x;
						}

						//autostretch group size x
						if
							(
								(*bg->can_be_stretched_x)
								&
								(b->button_x_offset + b->button_size_x - *bg->position_x - *bsg->position_x + 5.0f > * bg->size_x)
								&
								(*b->selected_auto_align_mode != EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE)
								)
						{
							*bg->size_x = b->button_x_offset + b->button_size_x - *bg->position_x - *bsg->position_x + 5.0f;
						}

						if
							(
								(*bg->can_be_stretched_y)
								&
								(b->button_y_offset + b->button_size_y - *bg->position_y - *bsg->position_y + 5.0f > * bg->size_y)
								&
								(*b->selected_auto_align_mode != EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE)
								)
						{
							*bg->size_y = b->button_y_offset + b->button_size_y - *bg->position_y - *bsg->position_y + 5.0f;
						}

						//if (*b->auto_stretch_button_y_size)

						//calculate position to next button
						if (*b->selected_auto_align_mode != EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE)
						{
							previvous_button_position_x = b->button_x_offset;
							previvous_button_position_y = b->button_y_offset;

							previvous_button_size_x = b->button_size_x + 5.0f;
							previvous_button_size_y = b->button_size_y + 5.0f;
						}

						//push next group
						{ previvous_group_push_x = *bg->size_x + *bg->position_x; }
						{ previvous_group_push_y = *bg->size_y + *bg->position_y; }

						//b->text = EString::float_to_string(*b->selected_auto_align_mode);

						if (*b->auto_stretch_button_y_size)
						{
							b->button_size_y = *bg->size_y;
						}

						//if buttons not leave group, update it
						//if(EButton::is_not_outside_of_group(b, bsg, bg))
						if (b == bg->selected_button)
						{
							b->rama_color->set_color(EColor::COLOR_YELLOW);
							b->rama_thikness = 3.0f;
						}
						else
						{
							b->rama_color->set_color_alpha(EColor::COLOR_GRAY, 0.333f);
							b->rama_thikness = 1.0f;
						}

						{
							b->update(_d);
							b->update_additional(_d);
						}
					}

				if (*bg->position_x + *bg->size_x > maximum_button_group_size_x) { maximum_button_group_size_x = *bg->position_x + *bg->size_x; }
				if (*bg->position_y + *bg->size_y > maximum_button_group_size_y) { maximum_button_group_size_y = *bg->position_y + *bg->size_y; }

				*bsg->size_x *= 0.99f;
				*bsg->size_y *= 0.99f;
				//main supergroup autostretch
				if (*bg->position_x + *bg->size_x + 5.0f > * bsg->size_x) { *bsg->size_x = *bg->position_x + *bg->size_x + 5.0f; }
				if (*bg->position_y + *bg->size_y + 5.0f > * bsg->size_y) { *bsg->size_y = *bg->position_y + *bg->size_y + 5.0f; }
			}

			if (bsg->button_close != NULL)
			{
				bsg->button_close->button_x_offset = *bsg->position_x + *bsg->size_x - bsg->button_close->button_size_x;
				bsg->button_close->button_y_offset = *bsg->position_y + *bsg->size_y - bsg->button_close->button_size_y;
			}
			for (EButton* b : bsg->additional_button_list)
			{
				b->update(_d);
				b->update_additional(_d);
			}
		}
}

void EWindow::catch_right_side(EButton::button_group* bg, EButton::button_super_group* bsg)
{
	if
		(
			(!*bg->can_be_stretched_x)
			)
	{
		if
			(
				(mouse_x > * bsg->position_x + *bg->position_x + *bg->size_x - 10.0f)
				&
				(mouse_x <= *bsg->position_x + *bg->position_x + *bg->size_x + 10.0f)
				&
				(mouse_y <= *bsg->position_y + *bg->position_y + *bg->size_y + 10.0f)
				&
				(mouse_y >= *bsg->position_y + *bg->position_y - 10.0f)
				)
		{
			if (!LMB) { *bg->right_side_catched = true; }
		}
		else
		{
			if (!LMB) { *bg->right_side_catched = false; }
		}

		if ((LMB) & (*bg->right_side_catched)) { *bg->size_x += mouse_speed_x * 1.0f; *bg->size_x = max(*bg->size_x, 10.0f); }
	}
}
void EWindow::catch_left_side(EButton::button_group* bg, EButton::button_super_group* bsg)
{
	/*if
		(
			(!*bg->can_be_stretched_x)
		)*/
	{
		if
			(
				(mouse_x > * bsg->position_x + *bg->position_x - 10.0f)
				&
				(mouse_x <= *bsg->position_x + *bg->position_x + 10.0f)
				&
				(mouse_y <= *bsg->position_y + *bg->position_y + *bg->size_y + 10.0f)
				&
				(mouse_y >= *bsg->position_y + *bg->position_y - 10.0f)
				)
		{
			if (!LMB) { *bg->left_side_catched = true; }
		}
		else
		{
			if (!LMB) { *bg->left_side_catched = false; }
		}

		if ((LMB) & (*bg->left_side_catched)) { *bg->position_x += mouse_speed_x * 1.0f; }
	}
}
void EWindow::catch_up_side(EButton::button_group* bg, EButton::button_super_group* bsg)
{
	if
		(
			(!*bg->can_be_stretched_x)
			)
	{
		if
			(
				(mouse_x > * bsg->position_x + *bg->position_x - 10.0f)
				&
				(mouse_x <= *bsg->position_x + *bg->position_x + *bg->size_x + 10.0f)
				&
				(mouse_y <= *bsg->position_y + *bg->position_y + *bg->size_y + 10.0f)
				&
				(mouse_y >= *bsg->position_y + *bg->position_y + *bg->size_y - 10.0f)
				)
		{
			if (!LMB) { *bg->up_side_catched = true; }
		}
		else
		{
			if (!LMB) { *bg->up_side_catched = false; }
		}

		if ((LMB) & (*bg->up_side_catched)) { *bg->size_y += mouse_speed_y * 1.0f; *bg->size_y = max(*bg->size_y, 10.0f); }
	}
}
void EWindow::catch_down_side(EButton::button_group* bg, EButton::button_super_group* bsg)
{
	/*if
		(
			(!*bg->can_be_stretched_y)
		)*/
	{
		if
			(
				(mouse_x > * bsg->position_x + *bg->position_x - 10.0f)
				&
				(mouse_x <= *bsg->position_x + *bg->position_x + *bg->size_x + 10.0f)
				&
				(mouse_y <= *bsg->position_y + *bg->position_y + 10.0f)
				&
				(mouse_y >= *bsg->position_y + *bg->position_y - 10.0f)
				)
		{
			if (!LMB) { *bg->down_side_catched = true; }
		}
		else
		{
			if (!LMB) { *bg->down_side_catched = false; }
		}

		if ((LMB) & (*bg->down_side_catched)) { *bg->position_y += mouse_speed_y * 1.0f; *bg->position_y = max(*bg->position_y, 10.0f); }
	}
}

/*EWindow::button_array_collection_massive()
{
}*/

void EWindow::update(float _d)
{
}

void EWindow::default_draw(float _d)
{
	if (have_bg)
	{
		if (!screen_space)
		{
			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.8f);
			EGraphicCore::batch->draw_gabarite(offset_x, offset_y, window_size_x, window_size_y, EGraphicCore::gabarite_white_pixel);
		}
		else
			if (screen_space_texture != NULL)
			{
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
				EGraphicCore::batch->draw_with_custom_uv
				(
					offset_x,
					offset_y,

					window_size_x,
					window_size_y,

					*screen_space_texture->x + offset_x / EWindow::default_texture_atlas->size_x,
					*screen_space_texture->y + offset_y / EWindow::default_texture_atlas->size_y,

					*screen_space_texture->x + (offset_x + window_size_x) / EWindow::default_texture_atlas->size_x,
					*screen_space_texture->y + (offset_y + window_size_y) / EWindow::default_texture_atlas->size_y
				);
			}
	}
}

void EWindow::draw(float _d)
{
}

void EWindow::default_resize_event()
{
	if (always_fullscreen)
	{
		window_size_x = EGraphicCore::SCR_WIDTH;
		window_size_y = EGraphicCore::SCR_HEIGHT;

		offset_x = 0;
		offset_y = 0;
	}
	else
	{
		if (align_x == Enums::PositionMode::LEFT) { offset_x = position_x; }
		if (align_x == Enums::PositionMode::MID) { offset_x = (EGraphicCore::SCR_WIDTH - window_size_x) / 2.0f + position_x; }
		if (align_x == Enums::PositionMode::RIGHT) { offset_x = (EGraphicCore::SCR_WIDTH - window_size_x) + position_x; }

		if (align_y == Enums::PositionMode::DOWN) { offset_y = position_y; }
		if (align_y == Enums::PositionMode::MID) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) / 2.0f + position_y; }
		if (align_y == Enums::PositionMode::UP) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) + position_y; }
	}
}

void EWindow::default_draw_interface(float _d)
{
	EGraphicCore::ourShader->use();
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	//if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS))
	//if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS))
	{EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f)); }
	//else
	//{EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, -1.0f));}

	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1.0f));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//סבנמס באעקונא
	EGraphicCore::batch->reset();

	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch, _d);
			b->additional_draw(EGraphicCore::batch, _d);
		}
	}

	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->text_pass(EGraphicCore::batch);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch, _d);
			b->additional_draw(EGraphicCore::batch, _d);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->text_pass(EGraphicCore::batch);
		}
	}
	EWindow::add_time_process("button process");
	/*
	for (button_array_collection_massive* massive : button_array_collection_massive_list)
	if (*massive->is_active)
	{
		for (button_array_horizontal_collection* horizontal : massive->button_array_horizontal_collection_list)
		{
			for (button_array_vertical_collection* vertical : horizontal->button_array_vertical_collection_list)
				if (*horizontal->selected_tab == *vertical->tab_id)
					for (button_array* array : vertical->button_array_list)
		}
	}*/

	//float previvous_button_size_x = 0.0f;
	//float previvous_button_size_y = 0.0f;

	//draw buttons on button group and update button group

	if (true)
	for (EButton::button_super_group* bsg : button_group_list)
		if (*bsg->is_active)
		{
			//EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.5f);
			if (EWindow::top_overlaped_group == bsg)
			{
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
			}
			else
			{
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_DARK_GRAY, 0.9f);
			}


			//EGraphicCore::batch->draw_gabarite_screen_space(*bsg->position_x, *bsg->position_y, *bsg->size_x, *bsg->size_y, EWindow::list_of_massive_style.at(0)->background);
			//EGraphicCore::batch->draw_gabarite(*bsg->position_x, *bsg->position_y, *bsg->size_x, *bsg->size_y, EGraphicCore::gabarite_white_pixel);

			float bg_texture_size_x = 0.0f;
			float bg_texture_size_y = 0.0f;

			for (int i = 0; i < ceil(*bsg->size_y / 48.0f); i++)
			for (int j = 0; j < ceil(*bsg->size_x / 48.0f); j++)
			{
				bg_texture_size_x = min(*bsg->size_x - j * 48.0f, 48.0f);
				bg_texture_size_y = min(*bsg->size_y - i * 48.0f, 48.0f);

				EGraphicCore::batch->draw_with_custom_uv
				(
					*bsg->position_x + j * 48.0f,
					*bsg->position_y + i * 48.0f,

					bg_texture_size_x,
					bg_texture_size_y,

					*bsg->background_texture->x + 3.0f / 4096.0f,
					*bsg->background_texture->y + 3.0f / 4096.0f,

					*bsg->background_texture->x + (bg_texture_size_x + 3.0f) / 4096.0f,
					*bsg->background_texture->y + (bg_texture_size_y + 3.0f) / 4096.0f
				);
			}

			for (int i = 0; i < ceil(*bsg->size_y / 48.0f); i++)
			{
				bg_texture_size_x = 3.0f;
				bg_texture_size_y = min(*bsg->size_y - i * 48.0f, 48.0f);

				EGraphicCore::batch->draw_with_custom_uv
				(
					*bsg->position_x - 3.0f,
					*bsg->position_y + i * 48.0f,

					bg_texture_size_x,
					bg_texture_size_y,

					*bsg->background_texture->x + 0.0f / 4096.0f,
					*bsg->background_texture->y + 3.0f / 4096.0f,

					*bsg->background_texture->x + (3.0f) / 4096.0f,
					*bsg->background_texture->y + (bg_texture_size_y + 3.0f) / 4096.0f
				);

				EGraphicCore::batch->draw_with_custom_uv
				(
					*bsg->position_x + *bsg->size_x + 0.0f,
					*bsg->position_y + i * 48.0f,

					bg_texture_size_x,
					bg_texture_size_y,

					* bsg->background_texture->x + 51.0f / 4096.0f,
					* bsg->background_texture->y + 3.0f / 4096.0f,

					* bsg->background_texture->x + (51.0f + 3.0f) / 4096.0f,
					* bsg->background_texture->y + (bg_texture_size_y + 3.0f) / 4096.0f
				);
			}

			if (*bsg->is_catched)
			{
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLUE, 0.8f);
				EGraphicCore::batch->draw_rama(*bsg->position_x - 5.0f, *bsg->position_y - 5.0f, *bsg->size_x + 10.0f, *bsg->size_y + 10.0f, 3.0f, EGraphicCore::gabarite_white_pixel);
			}

			/*
			if (EWindow::top_overlaped_group == bsg)
			{
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GREEN, 0.8f);
				EGraphicCore::batch->draw_rama(*bsg->position_x - 5.0f, *bsg->position_y - 5.0f, *bsg->size_x + 10.0f, *bsg->size_y + 10.0f, 2.0f, EGraphicCore::gabarite_white_pixel);;
			}*/

			EGraphicCore::batch->force_draw_call();

			glEnable(GL_SCISSOR_TEST);
			for (EButton::button_group* bg : bsg->button_group_list)
			{
				float total_x = *bsg->position_x + *bg->position_x;
				float total_y = *bsg->position_y + *bg->position_y;

				glScissor(total_x - 3.0f, total_y - 3.0f, *bg->size_x + 6.0f, *bg->size_y + 6.0f);
				//glScissor(0.0f, total_y - 3.0f, *bg->size_x + 6.0f, *bg->size_y + 6.0f);

				/*
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GRAY, 0.9f);
				EGraphicCore::batch->draw_gabarite(*bsg->position_x + *bg->position_x, *bsg->position_y + *bg->position_y, *bg->size_x, *bg->size_y, EGraphicCore::gabarite_white_pixel);
				*/


				//EGraphicCore::batch->
				//EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
				//EGraphicCore::batch->draw_gabarite_screen_space(total_x, total_y, *bg->size_x, *bg->size_y, EWindow::list_of_massive_style.at(0)->background);

				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLUE, 0.9f);
				if (*bg->right_side_catched)
				{
					EGraphicCore::batch->draw_gabarite(*bsg->position_x + *bg->position_x + *bg->size_x - 10.0f, *bsg->position_y + *bg->position_y, 10.0f, *bg->size_y, EGraphicCore::gabarite_white_pixel);
				}

				if (*bg->left_side_catched)
				{
					EGraphicCore::batch->draw_gabarite(*bsg->position_x + *bg->position_x, *bsg->position_y + *bg->position_y, 10.0f, *bg->size_y, EGraphicCore::gabarite_white_pixel);
				}

				if (*bg->up_side_catched)
				{
					EGraphicCore::batch->draw_gabarite(*bsg->position_x + *bg->position_x, *bsg->position_y + *bg->position_y + *bg->size_y - 10.0f, *bg->size_x, 10.0f, EGraphicCore::gabarite_white_pixel);
				}

				if (*bg->down_side_catched)
				{
					EGraphicCore::batch->draw_gabarite(*bsg->position_x + *bg->position_x, *bsg->position_y + *bg->position_y, *bg->size_x, 10.0f, EGraphicCore::gabarite_white_pixel);
				}

				//draw pass with scissors
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GRAY, 0.1f);
				EGraphicCore::batch->draw_rama(total_x, total_y, *bg->size_x, *bg->size_y, 1.0f, EGraphicCore::gabarite_white_pixel);

				for (EButton* but : bg->button_list)
				if
				(
					(
						(EButton::is_not_outside_of_group(but, bsg, bg))
						//||
						//(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
					)
					&
					(but->is_active)
				)
				{
						but->default_draw(EGraphicCore::batch, _d);
						but->additional_draw(EGraphicCore::batch, _d);
				}



				EGraphicCore::batch->reinit();
				EGraphicCore::batch->draw_call();
				EGraphicCore::batch->reset();
			}

			EGraphicCore::batch->force_draw_call();

			//draw text pass
			glDisable(GL_SCISSOR_TEST);
			for (EButton::button_group* bg : bsg->button_group_list)
			{
				for (EButton* but : bg->button_list)
					if
						(
							(EButton::is_not_outside_of_group(but, bsg, bg))
							&
							(but->is_active)
							)
					{
						but->text_pass(EGraphicCore::batch);
					}
				//text pass without scissors
			}

			
			

			for (EButton* but : bsg->additional_button_list)
				if (but->is_active)
				{
					but->default_draw(EGraphicCore::batch, _d);
					but->additional_draw(EGraphicCore::batch, _d);
				}

			EGraphicCore::batch->force_draw_call();
		}
		EWindow::add_time_process("button group process");
	//draw graphic for button group

	//if (time_process_active)
		if (glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS)
		{
			float time_process_h = 0.0f;
			float time_process_summ = 0.0f;

			float offset_y = 0.0f;

			for (time_process_struct* str : tps_list)
			{
				//time_process_summ += str->time_process_value.at(time_process_rota_id);

				//EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(round(str->time_process_value.at(time_process_rota_id) * 100.0f) / 100.0f), 205.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

				float time_process_average = 0.0f;
				float min_value = 10000.0f;
				float max_value = 0.0f;
				for (int i = 0; i < time_process_rota_size; i++)
				{
					float current = str->time_process_value.at(i);
					time_process_average += current;

					if (current < min_value) { min_value = current; }
					if (current > max_value) { max_value = current; }
				}

				time_process_average /= time_process_rota_size;
				time_process_summ += time_process_average;

				//if (glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS)
				//if (time_process_average > 0.05f)
				{
					if (time_process_average > 0.2f)
					{
						EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.9f);
					}
					else
					if (time_process_average > 0.1f)
					{
						EGraphicCore::batch->setcolor_alpha(EColor::COLOR_DARK_GRAY, 0.8f);
					}
					else
					{
						EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GRAY, 0.8f);
					}

					EGraphicCore::batch->draw_gabarite(0.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y, 400.0f, 20.0f, EGraphicCore::gabarite_white_pixel);

					EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.9f);
					EFont::active_font->draw(EGraphicCore::batch, str->time_process_name, 5.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

					EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.9f);
					EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(round(time_process_average * 100.0f) / 100.0f), 205.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

					EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GREEN, 0.9f);
					EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(min_value), 255.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

					EGraphicCore::batch->setcolor_alpha(EColor::COLOR_RED, 0.9f);
					EFont::active_font->draw(EGraphicCore::batch, EString::float_to_string(max_value), 305.0f, EGraphicCore::SCR_HEIGHT - 52.0f - offset_y + 3.0f);

					offset_y += 25.0f;
				}
				
			}

			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.9f);
			EGraphicCore::batch->draw_gabarite(0.0f, EGraphicCore::SCR_HEIGHT - 32.0f, 400.0f, 20.0f, EGraphicCore::gabarite_white_pixel);

			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_PINK, 0.9f);
			EFont::active_font->draw(EGraphicCore::batch, "summ", 5.0f, EGraphicCore::SCR_HEIGHT - 32.0f + 3.0f);
			EFont::active_font->draw(EGraphicCore::batch, std::to_string(time_process_summ), 205.0f, EGraphicCore::SCR_HEIGHT - 32.0f + 3.0f);

			time_process_rota_id++;

			if (time_process_rota_id >= time_process_rota_size)
			{
				time_process_rota_id = 0;
			}
		}

		EWindow::add_time_process("time process draw");

		EGraphicCore::batch->force_draw_call();
		EWindow::add_time_process("default interface draw call");
}

void EWindow::draw_interface(float _d)
{
}

void EWindow::add_time_process(std::string _name)
{
	//std::vector <float> tvec = new std::vector<float>(60, 0.0f);
	if (glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		int id = -1;
		int tid = 0;
		for (time_process_struct* tps : tps_list)
		{
			if (tps->time_process_name == _name) { id = tid; break; }

			tid++;
		}

		stop = std::chrono::high_resolution_clock::now();

		if (id != -1)
		{
			tps_list.at(id)->time_process_name = _name;
			tps_list.at(id)->time_process_value.at(time_process_rota_id) = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f;
		}
		else
		{
			time_process_struct* new_tps = new time_process_struct;

			std::cout << "Create new time process (" << _name << ")" << std::endl;

			tps_list.push_back(new_tps);

			for (int i = 0; i < time_process_rota_size; i++)
			{
				new_tps->time_process_value.push_back(0.0f);
			}

			new_tps->time_process_name = _name;
		}

		start = std::chrono::high_resolution_clock::now();
	}
}

void EWindow::push_cursor(float _x, float _y)
{
	SetCursorPos(real_mouse_x + _x, real_mouse_y + _y);

	mouse_x += _x;
	mouse_y += _y;

	real_mouse_x += _x;
	real_mouse_y += _y;
}

EWindow::EWindow()
{
	default_resize_event();

	EButton* but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
	but->master_window = this;
	but->position_by_window_mode_x = Enums::PositionMode::RIGHT;
	but->position_by_window_mode_y = Enums::PositionMode::UP;
	but->text = "X";
	//but->action_on_left_click = &EBA::action_close_window;

	default_button_list.push_back(but);
}

EWindow::~EWindow()
{
}

bool EWindow::is_overlap(EWindow* _w)
{
	if
		(
			(mouse_x >= _w->offset_x)
			&&
			(mouse_x <= _w->offset_x + _w->window_size_x)
			&&
			(mouse_y >= _w->offset_y)
			&&
			(mouse_y <= _w->offset_y + _w->window_size_y)
			)
	{
		return true;
	}

	return false;
}

bool EWindow::is_group_overlapped_by_mouse(EButton::button_super_group* _group)
{
	if
		(
			(EWindow::mouse_x >= *_group->position_x)
			&
			(EWindow::mouse_x <= *_group->position_x + *_group->size_x)
			&
			(EWindow::mouse_y >= *_group->position_y)
			&
			(EWindow::mouse_y <= *_group->position_y + *_group->size_y + 20.0f)
		)
	{
		return true;
	}
	return false;
}

EButton::button_group* EWindow::get_button_group_by_name(EWindow* _w, std::string _super_group_name, std::string _group_name)
{
	return nullptr;
}

EWindow::button_array_collection_massive::button_array_collection_massive(EWindow* _w)
{
	button_close = new EButton(0.0f, 0.0f, 20.0f, 20.0f);

	button_close->text_color->set_color(EColor::COLOR_WHITE);
	button_close->bg_color->set_color(EColor::COLOR_RED);

	button_close->text = "X";

	button_close->master_window = _w;

	//button_close->action_on_left_click = &EBA::action_set_constant_bool_to_address;
	button_close->target_address_for_bool = is_active;
	*button_close->target_value_for_bool = false;

	service_button.push_back(button_close);
}

EButton::ETwoDimensionGradient::ETwoDimensionGradient()
{
}

EButton::ETwoDimensionGradient::~ETwoDimensionGradient()
{
}

bool is_catched_by_mouse(bool _is_catched, float _x, float _y, float _size_x, float _size_y, float _catch_size, int _mode)
{
	float border_right	= _x + _size_x + _catch_size;
	float border_left	= _x - _catch_size;
	float border_up		= _y + _size_y + _catch_size;
	float border_down	= _y - _catch_size;

	switch (_mode)
	{
		case	CatchMethod::CATCH_METHOD_BORDER_DOWN:
				border_up		= _y + _catch_size;
				break;
		
		case	CatchMethod::CATCH_METHOD_BORDER_LEFT:
				border_right	= _x + _catch_size;
				break;
		
		case	CatchMethod::CATCH_METHOD_BORDER_RIGHT:
				border_left		= _x + _size_x - _catch_size;
				break;
		
		case	CatchMethod::CATCH_METHOD_BORDER_UP:
				border_down		= _y + _size_y - _catch_size;
				break;
		
		case	CatchMethod::CATCH_METHOD_BOTTOM:
				border_down		= _y  - _catch_size * 2.0f;
				border_up		= _y  - _catch_size;
				break;
		
		case	CatchMethod::CATCH_METHOD_CORNER_LEFT_DOWN:
				border_right	= _x + _catch_size;
				border_up		= _y + _catch_size;
				break;
				break;
		
		case	CatchMethod::CATCH_METHOD_CORNER_LEFT_UP:
				border_right	= _x + _catch_size;
				border_down		= _y + _size_y - _catch_size;
				break;
		
		case	CatchMethod::CATCH_METHOD_CORNER_RIGHT_DOWN:
				border_left		= _x +	_size_x - _catch_size;
				border_up		= _y +	_catch_size;
				break;

		case	CatchMethod::CATCH_METHOD_CORNER_RIGHT_UP:
				border_left		= _x + _size_x - _catch_size;
				border_down		= _y + _size_y - _catch_size;
				break;

		case	CatchMethod::CATCH_METHOD_MID:
				border_left		= _x + _size_x / 2.0f - _catch_size;
				border_down		= _y + _size_y / 2.0f - _catch_size;
				border_up		= _y + _size_y / 2.0f + _catch_size;
				border_right	= _x + _size_x / 2.0f + _catch_size;
				break;

		case	CatchMethod::CATCH_METHOD_MID_UP:
				border_left		= _x + _size_x / 2.0f - _catch_size / 2.0f;
				border_down		= _y + _size_y / 2.0f + _catch_size;
				border_up		= _y + _size_y / 2.0f + _catch_size * 2.0f;
				border_right	= _x + _size_x / 2.0f + _catch_size / 2.0f;
				break;

		default:break;
	}


	if
	(
		(EWindow::mouse_x >= border_left)
		&
		(EWindow::mouse_x <= border_right)
		&
		(EWindow::mouse_y >= border_down)
		&
		(EWindow::mouse_y <= border_up)
	)
	{
		//std::cout << "inside!" << std::endl;
		if (!EWindow::LMB)
		{
			return true;
		}
	}
	else
	{
		//std::cout << "outside!" << std::endl;
		if (!EWindow::LMB)
		{
			return false;
		}
	}

	return _is_catched;
}

float get_mouse_speed_x()
{
	if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		)
	{
		return EWindow::mouse_speed_x * 0.1f;
	}
	else
	{
		return EWindow::mouse_speed_x;
	}

	return 0.0f;
}

float get_mouse_speed_y()
{
	if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
			)
	{
		return EWindow::mouse_speed_y * 0.1f;
	}
	else
	{
		return EWindow::mouse_speed_y;
	}

	return 0.0f;
}

void send_this_button_group_to_top (EWindow* _w, EButton::button_super_group* _group)
{
	for (int i = 0; i < _w->button_group_list.size() - 1; i++)
	{
		if ((_w->button_group_list.at(i) == _group) & (!*_w->button_group_list.at(i + 1)->inmovable_on_list))
		{
			swap(_w->button_group_list.at(i), _w->button_group_list.at(i + 1));
		}
	}
}

void external_button_action_close_master_button_super_group(EButton* _b, float _f)
{
	if (_b->master_super_group != NULL)
	{
		*_b->master_super_group->is_active = false;
	}
}

EButton::button_super_group::button_super_group(EWindow* _w)
{
	EButton* but = new EButton(0.0f, 0.0f, 20.0f, 20.0f, _w, this, nullptr);
	but->text = "X";
	but->bg_color->set_color(EColor::COLOR_DARK_RED);
	but->text_color->set_color(EColor::COLOR_LAMP);
	but->action_on_left_click.push_back(&external_button_action_close_master_button_super_group);

	button_close = but;
	additional_button_list.push_back(but);

	background_texture = ETextureAtlas::put_texture_to_atlas("data/textures/gui_bg.png", EWindow::default_texture_atlas);
}

EButton::button_super_group::~button_super_group()
{
}

EButton::button_group::button_group()
{
	
}

EButton::button_group::~button_group()
{
}
