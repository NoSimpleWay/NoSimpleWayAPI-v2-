#ifndef _E_TEXT_CORE_ALREADY_LINKED_
/**/#define _E_TEXT_CORE_ALREADY_LINKED_
/**/#include "ETextCore.h"
#endif

namespace NS_FONT_UTILS
{
	ETextArea* active_text_area;
}

EFont::EFont(std::string _name, ETextureGabarite* _g, ETextureAtlas* _atlas, bool _not_cyrrilic)
{
	gabarite = _g;
	texture_atlas = _atlas;
	load_font_littera(_name);

	name = _name;

	is_not_cyrrilic = _not_cyrrilic;
}

float EFont::get_float_from_sub_data(std::string _s)
{
	std::string get_data = "";

	bool comma_is_open = false;

	//cout << "parse sub_data:" << _s << endl;

	for (int j = 0; j < _s.length(); j++)
	{
		if (_s.at(j) == '"')
		{
			if (!comma_is_open)
			{
				comma_is_open = true;
			}
			else
			{
				//cout << "try return:" << get_data << endl;
				return std::stof(get_data);
			}
		}
		else
		{
			if (comma_is_open) { get_data += _s.at(j); }
		}
	}
}

int EFont::get_int_from_sub_data(std::string _s)
{
	std::string get_data = "";

	bool comma_is_open = false;

	//cout << "parse sub_data:" << _s << endl;

	for (int j = 0; j < _s.length(); j++)
	{
		if (_s.at(j) == '"')
		{
			if (!comma_is_open)
			{
				comma_is_open = true;
			}
			else
			{
				//cout << "try return:" << get_data << endl;
				return std::stoi(get_data);
			}
		}
		else
		{
			if (comma_is_open) { get_data += _s.at(j); }
		}
	}
}

std::vector<EFont*> EFont::font_list;

void EFont::load_font_littera(std::string _path)
{
	EInputCore::logger_simple_success("try load font: " + _path);
	//using namespace std;

	std::string line;
	std::string sub_data;
	int data_order;

	bool comma_is_open = false;
	int font_array_id = 31;
	bool show_console_info = false;

	std::ifstream myfilez("data/font/" + _path + ".fnt");

	for (int i = 0; i < 300; i++)
	{
		UV_start_x[i] = 0;
		UV_start_y[i] = 0;
		UV_size_x[i] = 0;
		UV_size_y[i] = 0;
		offset_x[i] = 0;
		offset_y[i] = 0;
	}

	if (myfilez.is_open())
	{
		//cout << "symbol a=" << (int)'a' << endl;

		while ((getline(myfilez, line)))
		{
			//EInputCore::logger_simple_success(line);
			comma_is_open = true;
			data_order = 0;
			//cout << line << '\n';

			//cout << "line #" << font_array_id;
			for (int i = 0; i < line.length(); i++)
			{
				if ((line.at(i) == ' ') || (i + 1 >= line.length()))
				{
					//if (show_console_info) std::cout << "subdata | " << sub_data << " |" << std::endl;

					if (compare_with_key(sub_data, "id="))
					{
						font_array_id = get_int_from_sub_data(sub_data);

						if (font_array_id == 1025) { font_array_id = 168; }
						else
							if (font_array_id == 1105) { font_array_id = 184; }
							else
								if (font_array_id > 255) { font_array_id -= 848; }

						//if (show_console_info) std::cout << white << "subdata:" << sub_data << " id:" << font_array_id << " sym:" << (char)(font_array_id) << std::endl;
					}

					if (compare_with_key(sub_data, "x="))
					{
						if (show_console_info) std::cout << "x pos | " << get_float_from_sub_data(sub_data) << " |" << std::endl;
						UV_start_x[font_array_id] = get_float_from_sub_data(sub_data);
					}

					if (compare_with_key(sub_data, "y="))
					{
						if (show_console_info) std::cout << "y pos | " << get_float_from_sub_data(sub_data) << " |" << std::endl;
						UV_start_y[font_array_id] = get_float_from_sub_data(sub_data);
					}

					if (compare_with_key(sub_data, "width="))
					{
						if (show_console_info) std::cout << "x size | " << get_float_from_sub_data(sub_data) << " |" << std::endl;
						size_x_in_pixels[font_array_id] = UV_size_x[font_array_id] = get_float_from_sub_data(sub_data);
					}

					if (compare_with_key(sub_data, "height="))
					{
						size_y_in_pixels[font_array_id] = UV_size_y[font_array_id] = get_float_from_sub_data(sub_data);
						if (show_console_info) std::cout << "y size | " << UV_size_y[font_array_id] << " |" << std::endl;
					}

					if (compare_with_key(sub_data, "xoffset="))
					{
						if (show_console_info) std::cout << "x offset | " << get_float_from_sub_data(sub_data) << " |" << std::endl;
						offset_x[font_array_id] = get_float_from_sub_data(sub_data);
					}

					if (compare_with_key(sub_data, "yoffset="))
					{
						offset_y[font_array_id] = get_float_from_sub_data(sub_data);
						if (show_console_info) std::cout << "y offset | size_y=" << UV_size_y[font_array_id] << " offset=" << get_float_from_sub_data(sub_data) << " result=" << offset_y[font_array_id] << " |" << std::endl;
					}

					if (compare_with_key(sub_data, "xadvance="))
					{
						if (show_console_info) std::cout << "advance | " << get_float_from_sub_data(sub_data) << " |" << std::endl;

						if (show_console_info) { std::cout << "font_array_id=" << font_array_id << std::endl; }
						advance[font_array_id] = get_float_from_sub_data(sub_data);

						UV_size_x[font_array_id] = UV_size_x[font_array_id] / (float)texture_atlas->get_atlas_size_x();
						UV_size_y[font_array_id] = UV_size_y[font_array_id] / (float)texture_atlas->get_atlas_size_y();

						UV_start_x[font_array_id] = *gabarite->uv_start_x + UV_start_x[font_array_id] / (float)texture_atlas->get_atlas_size_x();
						UV_start_y[font_array_id] = *gabarite->uv_start_y + (*gabarite->size_y_in_pixels / (float)texture_atlas->get_atlas_size_y()) - UV_start_y[font_array_id] / (float)texture_atlas->get_atlas_size_y();

						//EInputCore::logger_param("final uv_size_y", UV_start_y[font_array_id]);
					}

					//

					//if (data_order == 6) { cout << "advance | " << sub_data << " |" << endl; }
					sub_data = "";

					data_order++;
				}
				else
				{
					sub_data += line.at(i);
				}
			}
			//if (show_console_info) { std::cout << std::endl; }

			font_array_id++;
		}

		myfilez.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	//for (int i = 0; i < 256; i++)
	//{
	//	EInputCore::logger_param(EInputCore::border_this_text(i, '{'), UV_start_x[i]);
	//}
}

inline bool EFont::compare_with_key(std::string _data, std::string _key)
{
	if (_data.substr(0, _key.length()) == _key)
	{
		return true;
	}
	else
	{
		return false;
	}
	//return false;
}

ETextArea::ETextArea()
{
}

ETextArea::ETextArea(EClickableArea* _region, EFont* _font, std::string _text)
{
	ERegionGabarite::set_region_gabarite
	(&region_gabarite, _region->region_gabarite);
	font = _font;
	//*stored_text = _text;

	parent_clickable_region = _region;

	sprite_layer = ESpriteLayer::create_default_sprite_layer(nullptr);

	ETextArea::change_text(_text);
	//generate_rows();
	//generate_text();
}

ETextArea::~ETextArea()
{
	delete		error;
	delete[]	color;
	delete[]	offset_border;
	delete		font_scale;
	//delete		&font;
	delete		down_offset;

	EInputCore::logger_simple_info("deleting text area");
	if (region_gabarite != nullptr)
	{
		(*region_gabarite->pointers_to_this_object)--;

		if (*region_gabarite->pointers_to_this_object <= 0)
		{
			delete region_gabarite;
			EInputCore::logger_simple_success("deleting text area gabarite");
		}
	}

	delete		stored_text;

	for (std::string* _row : row) {delete _row;}
	row.clear();
	row.shrink_to_fit();

	delete row_count;
	delete translate_region_gabarite;
	//delete& master_clickable_region;
	delete offset_by_gabarite_size_x;
	delete offset_by_gabarite_size_y;
	delete offset_by_text_size_x;
	delete offset_by_text_size_y;

	delete can_be_edited;
	delete sprite_layer;

	for (EFontGlyph* glyph : font_glyph_list)
	{delete glyph;}
	font_glyph_list.clear();
	font_glyph_list.shrink_to_fit();

	delete selected_glyph_position;
	delete flash_line_active;
	delete flash_line_cooldown;

	delete jump_cooldown;
	delete text_area_active;
	delete _unused_border_offset;

}

void ETextArea::generate_rows()
{
	/// /// /// /// /// /// ///
	std::string temp_s = "";
	int data_length = (*stored_text).length();
	char sym = ' ';
	char next_sym = ' ';
	bool stop_writing = false;
	/// /// /// /// /// /// ///

	if (!row.empty())
	{
		for (int i = 0; i < row.size(); i++)
			if (row.at(i) != nullptr)
			{
				delete row.at(i);
			}

		row.clear();

		*row_count = 0;
	}

	for (int i = 0; i < data_length; i++)
	{
		stop_writing = false;

		sym = (*stored_text)[i];

		std::string z;
		if (i + 1 < data_length)//can read next symbol
		{
			next_sym = (*stored_text)[i + 1];

			

			//EInputCore::logger_simple_success("-=-=-=-=-=-=-");
			z = sym;
			//EInputCore::logger_param("current sym", z);

			z = next_sym;
			//EInputCore::logger_param("next sym", z);

			//new line
			if ((sym == '\\') && (next_sym == 'n'))
			{
				stop_writing = true;

				row.push_back(new std::string(temp_s));
				temp_s = "";

				i++;
			}
		}
		else//end of text
		{
		}



		if (!stop_writing)
		{
			temp_s += sym;
		}
	}

	row.push_back(new std::string(temp_s));

	*row_count = row.size();

	//EInputCore::logger_param("Stored text", *stored_text);
	//EInputCore::logger_param("Count of row", *row_count);

	for (std::string* str : row)
	{
		//EInputCore::simple_logger_with_parameter("row", *str);
	}
}

void ETextArea::generate_text()
{
	std::string temp_s = "";

	int target_symbol = 0;
	int str_lenght = 0;

	float x_adding = 0.0f;
	float y_adding = 0.0f;
	float full_text_height = 0.0f;


	EFontGlyph* temp_glyph = nullptr;

	if (!font_glyph_list.empty())
	{
		for (int i = 0; i < font_glyph_list.size(); i++)
		{
			delete font_glyph_list.at(i);
		}

		font_glyph_list.clear();
	}



	if
		(
			(sprite_layer != nullptr)
			&&
			(region_gabarite != nullptr)
			&&
			(font != nullptr)
		)
	{
		//if (*selected_color_table == TextColorArray::FREE)
		{NS_EGraphicCore::set_active_color(color);}

		*sprite_layer->last_buffer_id = 0;

		if (sprite_layer->vertex_buffer != nullptr)
		{
			delete sprite_layer->vertex_buffer;
		}
		

		sprite_layer->vertex_buffer = new float[sprite_layer->batcher->gl_vertex_attribute_total_count * stored_text->length() * 4];

		int row_id = 0;
		int id_for_stored_text_sym = 0;

		full_text_height = 14.0f * (row.size());
		y_adding = full_text_height - 14.0f;
		
		float border_offset_bottom	= 0.0f;
		float border_offset_top		= 0.0f;

		if (can_get_access_to_group_style())
		{
			border_offset_bottom	= *parent_entity->parent_button_group->selected_style->button_bg->side_offset_bottom;
			border_offset_top		= *parent_entity->parent_button_group->selected_style->button_bg->side_offset_up;
		}

		y_adding += (region_gabarite->size_y - border_offset_bottom - border_offset_top) * *offset_by_gabarite_size_y;

		//vertical align
		y_adding += (full_text_height - 2.0f) * *offset_by_text_size_y;
		y_adding += border_offset_bottom;


		for (std::string* str : row)
		{
			temp_s = *str;
			str_lenght = temp_s.length();

			x_adding
			=
			(
				(
					region_gabarite->size_x
					-
					offset_border[BorderSide::RIGHT]
				)
				*
				*offset_by_gabarite_size_x
			)
			+
			(get_row_width(str) * *offset_by_text_size_x);

			x_adding += offset_border[BorderSide::LEFT];
			//_adding = *region_gabarite->size_y * *offset_by_gabarite_size_y + get_row_width(str) * *offset_by_text_size_y;


			for (int i = 0; i < str_lenght; i++)
			{
				target_symbol = (int)(temp_s.at(i));
				if (target_symbol < 0) { target_symbol += 256; }

				NS_ERenderCollection::add_data_to_vertex_buffer_custom_uv
				(
					sprite_layer->vertex_buffer,
					*sprite_layer->last_buffer_id,

					round(region_gabarite->world_position_x + x_adding + font->offset_x[target_symbol]),
					round(region_gabarite->world_position_y - (font->size_y_in_pixels[target_symbol] - 15.0f + font->offset_y[target_symbol] * *font_scale - y_adding)),

					font->size_x_in_pixels[target_symbol] * *font_scale,
					font->size_y_in_pixels[target_symbol] * *font_scale,

					font->UV_start_x[target_symbol],
					font->UV_start_y[target_symbol] - font->UV_size_y[target_symbol],

					font->UV_start_x[target_symbol] + font->UV_size_x[target_symbol],
					font->UV_start_y[target_symbol] * *font_scale
				);

				//no sence generate glyphs to text, which can be edited
				if (*can_be_edited)
				{
					temp_glyph = new EFontGlyph
					(
						target_symbol,

						region_gabarite->world_position_x + x_adding + font->offset_x[target_symbol],
						region_gabarite->world_position_y + y_adding,

						font->size_x_in_pixels[target_symbol] * *font_scale,
						font->size_y_in_pixels[target_symbol] * *font_scale
					);

					if (i == 0) { temp_glyph->is_first_symbol = true; }
					if (i == str_lenght - 1) { temp_glyph->is_last_symbol = true; }

					temp_glyph->row_id = row_id;
					temp_glyph->storer_text_sym_id = id_for_stored_text_sym;
					id_for_stored_text_sym++;

					font_glyph_list.push_back(temp_glyph);
				}

				/*NS_ERenderCollection::fill_vertex_buffer_custom_uv
				(
					sprite_layer->vertex_buffer,
					*sprite_layer->last_buffer_id,

					*region_gabarite->world_position_x + x_adding,
					*region_gabarite->world_position_y + y_adding,

					100.0f,
					100.0f,

					0.0f,
					0.0f,

					0.1f,
					0.1f
				);*/

				//EInputCore::logger_param("caller", font->UV_start_y[target_symbol]);

				x_adding += (font->advance[target_symbol]) * *font_scale;
			}


			//empty glyph
			temp_glyph = new EFontGlyph
			(
				0,

				region_gabarite->world_position_x + x_adding + font->offset_x[target_symbol],
				region_gabarite->world_position_y + y_adding,

				5.0f,
				5.0f
			);

			temp_glyph->row_id = row_id;
			temp_glyph->storer_text_sym_id = id_for_stored_text_sym;
			font_glyph_list.push_back(temp_glyph);
			temp_glyph->is_empty = true;
			//*temp_glyph->is_first_symbol = true;

			row_id++;
			id_for_stored_text_sym += 2;

			//EInputCore::logger_param("last buffer id", *sprite_layer->last_buffer_id);

			y_adding -= 14.0f;
		}
	}
	else
	{
		if (!*error)
		{
			if (sprite_layer == nullptr) { EInputCore::logger_simple_error("sprite layer in [text area] is null!"); }
			if (region_gabarite == nullptr) { EInputCore::logger_simple_error("region gabarite in [text area] is null!"); }
			if (font == nullptr) { EInputCore::logger_simple_error("font in [text area] is null!"); }

			*error = true;
		}
	}
}

void ETextArea::set_font(EFont* _font)
{
	font = _font;
}

float ETextArea::get_row_width(std::string* _row)
{
	float total_width = 0.0f;

	for (int i = 0; i < _row->length(); i++)
	{
		int sym_id = (int)(_row->at(i));
		if (sym_id <= 0) { sym_id += 256; }

		total_width += font->advance[sym_id];
	}

	return total_width;
}

void ETextArea::translate(float _x, float _y, float _z, bool _translate_local_coordinate)
{
	if
	(
		(parent_entity == nullptr)
		||
		(region_gabarite != ((EntityButton*)parent_entity)->button_gabarite)
	)
	{
		region_gabarite->world_position_x += _x;
		region_gabarite->world_position_y += _y;

		if (_translate_local_coordinate)
		{
			region_gabarite->offset_x += _x;
			region_gabarite->offset_y += _y;
		}
	}
	

	sprite_layer->modify_buffer_position_for_sprite_layer(_x, _y, 0.0f);

	for (EFontGlyph* f_glyph : font_glyph_list)
	if (f_glyph != nullptr)
	{
		f_glyph->world_position_x += _x;
		f_glyph->world_position_y += _y;
	}
}

void ETextArea::update(float _d)
{
	int glyph_id = 0;

	if (*flash_line_cooldown > 0)
	{
		*flash_line_cooldown -= _d;
	}
	else
	{
		*flash_line_cooldown += 0.25f;
		*flash_line_active = !*flash_line_active;
	}

	//if
	//(
	//	(EClickableRegion::active_clickable_region == nullptr)
	//	||
	//	(EClickableRegion::active_clickable_region == master_clickable_region)
	//)
	//{
	//	if (EClickableRegion::active_clickable_region == nullptr) {*stored_text = "null";}
	//	if (EClickableRegion::active_clickable_region == master_clickable_region) {*stored_text = "master";}
	//}
	//else
	//{
	//	*stored_text = "NO";
	//}
	//generate_rows();
	//generate_text();
	
	//click to glyph
	if (!font_glyph_list.empty())
	{
		if
			(
				(*can_be_edited)
				&&
				(EInputCore::MOUSE_BUTTON_LEFT)
				&&
				(
					(EClickableArea::active_clickable_region == nullptr)
					||
					(EClickableArea::active_clickable_region == parent_clickable_region)
				)
				&&
				(NS_FONT_UTILS::active_text_area == nullptr)
			)
			for (EFontGlyph* glyph : font_glyph_list)
			{



				if
					(
						(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom >= glyph->world_position_x)
						&&
						(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom <= glyph->world_position_x + glyph->size_x)
						&&
						(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom >= glyph->world_position_y)
						&&
						(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom <= glyph->world_position_y + glyph->size_y)
						)
				{
					//*selected_glyph_position = glyph_id;
					//*selected_glyph_position = -1;
					//NS_FONT_UTILS::active_text_area = this;

					if (EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom <= glyph->world_position_x + glyph->size_x / 2.0f)
					{
						*selected_glyph_position = glyph_id;
						//*selected_left_side = true;
						//*selected_glyph_position = glyph_id;
					}
					else
					{
						*selected_glyph_position = glyph_id + 1;
						//*selected_left_side = false;
						//*selected_glyph_position = min(glyph_id, font_glyph_list.size() - 1);
					}

					*text_area_active = true;
					*selected_glyph_position = min(*selected_glyph_position, font_glyph_list.size() - 1);
					NS_FONT_UTILS::active_text_area = this;
					break;
				}

				glyph_id++;
			}
	}

	if
	(
		(EInputCore::MOUSE_BUTTON_LEFT)
	)
	{
		//click into gabarite
		if
		(
			(*can_be_edited)
			&&
			(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom >= region_gabarite->world_position_x)
			&&
			(EInputCore::MOUSE_POSITION_X / NS_EGraphicCore::current_zoom <= region_gabarite->world_position_x + region_gabarite->size_x)
			&&
			(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom >= region_gabarite->world_position_y)
			&&
			(EInputCore::MOUSE_POSITION_Y / NS_EGraphicCore::current_zoom <= region_gabarite->world_position_y + region_gabarite->size_y)
			&&
			(
				(EClickableArea::active_clickable_region == nullptr)
				||
				(EClickableArea::active_clickable_region == parent_clickable_region)
			)
		)
		{ 
			if ((!row.empty()) && (!*text_area_active) && (NS_FONT_UTILS::active_text_area == nullptr))
			{
				*text_area_active = true;
				*selected_glyph_position = font_glyph_list.size() - 1;

				NS_FONT_UTILS::active_text_area = this;
			}
		}
		else//declick,
		{
			*text_area_active = false;

			*selected_glyph_position = -1;
			NS_FONT_UTILS::active_text_area = nullptr; 
		}
	}

	

	//insert new char to text
	if ((*text_area_active) && (EInputCore::LAST_INPUTED_CHAR != 0))
	{
		int target_id = font_glyph_list.at(min(*selected_glyph_position, font_glyph_list.size() - 1))->storer_text_sym_id + 0;
		//if (!*selected_left_side) { target_id++;}

		std::string temp_s(1, EInputCore::LAST_INPUTED_CHAR);
		//EInputCore::logger_param("last inputed char", temp_s);

		//std::cout << EInputCore::LAST_INPUTED_CHAR << std::endl;
		if (*selected_glyph_position >= 0)
		{
			stored_text->insert(target_id, temp_s);
			//*stored_text = "1234567";
			(*selected_glyph_position)++;
		}
		else
		{
			*stored_text = temp_s;
			//*selected_left_side = false;
			*selected_glyph_position = 0;
		}

		generate_rows();
		generate_text();

		if
		(
			(target_id > 0)
			&&
			(
				(EInputCore::LAST_INPUTED_CHAR == 'n')
				&&
				(stored_text->at(target_id - 1) == '\\')
			)
		)
		{
			(*selected_glyph_position) -= 2;
		}

		for (text_actions_pointer dap : action_on_change_text) if (dap != nullptr) { dap(this); }
	}

	//BACKSPACE key - erase left sided symbol
	if
	(
		(EInputCore::key_pressed_once(GLFW_KEY_ENTER))
		&&
		(*text_area_active)
	)
	{
		//*selected_glyph_position = -1;
		*text_area_active = false;

		NS_FONT_UTILS::active_text_area = nullptr;
	}

	if
	(
		(
			(EInputCore::key_pressed_once(GLFW_KEY_BACKSPACE))
			||
			(
				(EInputCore::key_holded(GLFW_KEY_BACKSPACE, 0.25f))
				&&
				(*jump_cooldown <= 0)
			)
		)
		&&
		(*text_area_active)
	)
	{
		*jump_cooldown = 0.1f;

		int target_glyph_id = min(*selected_glyph_position, font_glyph_list.size() -1);
		EFontGlyph* target_glyph = font_glyph_list.at(target_glyph_id);

		int target_row_id = target_glyph->row_id;
		int target_sym_id = target_glyph->storer_text_sym_id - 1;

		//if (*selected_left_side) { target_sym_id--; }

		if (target_sym_id >= 0)
		{

			stored_text->erase(target_sym_id , 1);

			//std::string ss(target_glyph->sym, 1);
			//EInputCore::logger_param("IS EMPTY", *font_glyph_list.at(target_glyph_id - 1)->is_empty);

			if ((target_glyph_id - 1 >= 0) && (font_glyph_list.at(target_glyph_id - 1)->is_empty)) { (*selected_glyph_position) += 1; }
			(*selected_glyph_position) -= 1;

			change_text(*stored_text);
			
			//if ((parent_clickable_region != nullptr) && (parent_clickable_region->parent_custom_data != nullptr))
			//{
				for (text_actions_pointer dap : action_on_change_text) if (dap != nullptr) {dap(this);}
			//}
			

			//if (row.at(*target_glyph->row_id)->length() <= 1) { (*selected_glyph_position) -= 1; }
			

			//if delete all text

		}
		
	}

	if
	(
		(
			(EInputCore::key_pressed_once(GLFW_KEY_LEFT))
			||
			(
				(EInputCore::key_holded(GLFW_KEY_LEFT, 0.25f))
				&&
				(*jump_cooldown <= 0)
			)
		)
		&&
		(*text_area_active)
		&&
		(*selected_glyph_position >= 0)
	)
	{
		*jump_cooldown = 0.1f;

		*flash_line_cooldown = 0.5f;
		*flash_line_active = true;

		if (font_glyph_list.at(*selected_glyph_position)->is_first_symbol)
		{
			//if (!(*selected_left_side)) { *selected_left_side = true; }
			//else
			{
				if (*selected_glyph_position > 0)
				{
					//*selected_left_side = false;
					*selected_glyph_position = max(*selected_glyph_position - 1, 0);
				}
			}
		}
		else
		{
			*selected_glyph_position = max(*selected_glyph_position - 1, 0);
		}
	}

	if
	(
		(
			(EInputCore::key_pressed_once(GLFW_KEY_RIGHT))
			||
			(
				(EInputCore::key_holded(GLFW_KEY_RIGHT, 0.25f))
				&&
				(*jump_cooldown <= 0)
			)
		)
		&&
		(*text_area_active)
		&&
		(*selected_glyph_position >= 0)
	)
	{
		*jump_cooldown = 0.1f;

		*flash_line_cooldown = 0.5f;
		*flash_line_active = true;

		if (font_glyph_list.at(*selected_glyph_position)->is_last_symbol)
		{
			//if (*selected_left_side) { *selected_left_side = false; }
			//else
			{
				if (*selected_glyph_position < font_glyph_list.size() - 1)
				{
					//*selected_left_side = true;
					*selected_glyph_position = min(*selected_glyph_position + 1, font_glyph_list.size() - 1);
				}
			}
			
		}
		else
		{
			*selected_glyph_position = min(*selected_glyph_position + 1, font_glyph_list.size() - 1);
		}
	}

	*jump_cooldown -= _d;
}

void ETextArea::draw()
{
	EFontGlyph* active_glyph = nullptr;

	sprite_layer->transfer_vertex_buffer_to_batcher();

	if ((*selected_glyph_position >= 0) && (*flash_line_active) && (*text_area_active))
	{
		//EInputCore::logger_param("selected glyph position", *selected_glyph_position);
		//EInputCore::logger_param("font_glyph_list.size()", font_glyph_list.size());

		active_glyph = font_glyph_list.at(min(*selected_glyph_position, font_glyph_list.size() - 1));

		//EInputCore::logger_simple_success("LOL");
		ERenderBatcher::if_have_space_for_data(sprite_layer->batcher, 1);

		NS_EGraphicCore::set_active_color(color);

		//if (*selected_left_side)
		{
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				sprite_layer->batcher->vertex_buffer,
				sprite_layer->batcher->last_vertice_buffer_index,
				active_glyph->world_position_x,
				active_glyph->world_position_y,
				2.0f,
				15.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}
		/*else
		{
			NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
			(
				sprite_layer->batcher->vertex_buffer,
				sprite_layer->batcher->last_vertice_buffer_index,
				*active_glyph->world_position_x + *active_glyph->size_x - 1.0f,
				*active_glyph->world_position_y,
				2.0f,
				15.0f,
				NS_DefaultGabarites::texture_gabarite_white_pixel
			);
		}*/
	}

	/*if ((*selected_glyph_position < 0) & (*flash_line_active) & (*text_area_active))
	{
		NS_EGraphicCore::set_active_color(NS_EColorCollection::COLOR_GREEN);
		
		NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
		(
			sprite_layer->batcher->vertex_buffer,
			sprite_layer->batcher->last_vertice_buffer_index,
			*region_gabarite->world_position_x,
			*region_gabarite->world_position_y,
			2.0f,
			15.0f,
			NS_DefaultGabarites::texture_gabarite_white_pixel
		);
	}
	*/

	/*NS_ERenderCollection::add_data_to_vertex_buffer_textured_rectangle_with_custom_size
	(
		sprite_layer->batcher->vertex_buffer,
		sprite_layer->batcher->last_vertice_buffer_index,
		10.0f,
		10.0f,
		100.0f,
		100.0f,
		NS_DefaultGabarites::texture_gabarite_white_pixel
	);*/
}

void ETextArea::set_region(ETextArea* _text_area, ERegionGabarite* _region_gabarite)
{
	//if ()
	if (_text_area->region_gabarite != _region_gabarite)
	{
		//old region lose 1 pointer to him
		if (_text_area->region_gabarite != nullptr)
		{_text_area->region_gabarite->pointers_to_this_object--;}

		//this region have 1 more pointers to him
		(*_region_gabarite->pointers_to_this_object)++;
		_text_area->region_gabarite = _region_gabarite;
	}
}

ETextArea* ETextArea::create_base_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text)
{
	ETextArea* jc_text_area = new ETextArea(_region_gabarite, _font, _text);

	return jc_text_area;
}

ETextArea* ETextArea::create_centered_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text)
{
	if (_region_gabarite != nullptr)
	{
		ETextArea* jc_text_area = create_base_text_area(_region_gabarite, _font, _text);

		*jc_text_area->offset_by_gabarite_size_x = 0.5f;
		*jc_text_area->offset_by_gabarite_size_y = 0.5f;

		*jc_text_area->offset_by_text_size_x = -0.5f;
		*jc_text_area->offset_by_text_size_y = -0.5f;

		//*jc_text_area->can_be_edited = false;


		return jc_text_area;
	}
	else
	{
		return nullptr;
	}
}

ETextArea* ETextArea::create_centered_to_right_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text)
{
	if (_region_gabarite != nullptr)
	{
		ETextArea* jc_text_area = create_base_text_area(_region_gabarite, _font, _text);

		*jc_text_area->offset_by_gabarite_size_x = 1.0f;
		*jc_text_area->offset_by_gabarite_size_y = 0.5f;

		*jc_text_area->offset_by_text_size_x = -1.0f;
		*jc_text_area->offset_by_text_size_y = -0.5f;

		//*jc_text_area->can_be_edited = false;


		return jc_text_area;
	}
	else
	{
		return nullptr;
	}

}

ETextArea* ETextArea::create_centered_to_left_text_area(EClickableArea* _region_gabarite, EFont* _font, std::string _text)
{
	if (_region_gabarite != nullptr)
	{
		ETextArea* jc_text_area = create_base_text_area(_region_gabarite, _font, _text);

		*jc_text_area->offset_by_gabarite_size_x = 0.0f;
		*jc_text_area->offset_by_gabarite_size_y = 0.5f;

		*jc_text_area->offset_by_text_size_x = 0.0f;
		*jc_text_area->offset_by_text_size_y = -0.5f;

		//*jc_text_area->can_be_edited = false;


		return jc_text_area;
	}
	else
	{
		return nullptr;
	}
}

void ETextArea::change_text(std::string _text)
{
	std::string		buffer		= "";
	std::string		temp_text	= "";
	float			x_size		= 0.0f;
	bool split = false;

	for (int i = 0; i < _text.size(); i++)
	{
		if
		(
			(i + 1 < _text.size())
			&&
			(_text[i] == '\\')
			&&
			(_text[i + 1] == 'n')
		)
		{
			x_size = 0.0f;

			buffer += "\\n";
			i++;

			//if (buffer[0] == 'M')
			//{
			//	EInputCore::logger_simple_info("reset x_size");
			//}
		}
		else
		//if
		//(
		//	(_text[i] != 'n')
		//	&&
		//	(
		//		(_text[max (i - 1, 0)] != '\\')
		//		||
		//		(i == 0)
		//	)
		//)
		{
			

			//if (i + 1 <= _text.size())
			{
				int sym_id = (int)(_text[i]);
				if (sym_id <= 0) { sym_id += 256; }

				x_size += font->advance[sym_id];

				if
				(
					(x_size + offset_border[BorderSide::LEFT] + 5.0f >= region_gabarite->size_x - offset_border[BorderSide::RIGHT])
				)
				{
					/*if (buffer[0] == 'M')
					{
						EInputCore::logger_param("unfinished buffer", buffer);
						EInputCore::logger_param("x_size", x_size);
						std::cout << std::endl;
					}*/
					//EInputCore::logger_param("text splitted", buffer);
					//EInputCore::logger_param("size", x_size + offset_border[BorderSide::LEFT]);
					//EInputCore::logger_param("border", *region_gabarite->size_x - offset_border[BorderSide::RIGHT]);
					//std::cout << std::endl;
					//if (_text[i] != ' '){ buffer += _text[i]; }
					if (_text[min(i , _text.size() - 1)] != ' ')
					{
						buffer += "-\\n";
					}
					else
					{
						buffer += "\\n";
					}

					

					x_size = 0.0f;
				}
				else
				{

				}
			}

			//ignore space symbol after split
			if
			(
				(i == 0)
				||
				(
					(_text[i] != ' ')
					||
					(x_size > 0.01f)
				)
			)
			{ buffer += _text[i]; }


		}
	}



	if (stored_text != nullptr)
	{
		*stored_text = buffer;
		//if (buffer[0] == '?') { EInputCore::logger_param("buffer", buffer); }
		generate_rows();
		generate_text();
	}
}

bool ETextArea::can_get_access_to_group_style()
{
	if
	(
		(parent_entity != nullptr)
		&&
		(parent_entity->parent_button_group != nullptr)
		&&
		(parent_entity->parent_button_group->selected_style != nullptr)
	)
	{return true;}
	else
	{return false;}
}

EButtonGroup* ETextArea::get_root_group()
{
	if
	(
		(parent_entity != nullptr)
		&&
		(((EntityButton*)parent_entity)->parent_button_group != nullptr)
	)
	{
		return ((EntityButton*)parent_entity)->parent_button_group->root_group;
	}
	else
	{return nullptr;}
}

EFontGlyph::EFontGlyph(char _sym, float _pos_x, float _pos_y, float _size_x, float _size_y)
{
	world_position_x = _pos_x;
	world_position_y = _pos_y;

	size_x = _size_x;
	size_y = _size_y;

	sym = _sym;
}

EFontGlyph::~EFontGlyph()
{
	//delete world_position_x;
	//delete world_position_y;

	//delete size_x;
	//delete size_y;

	//delete sym;
	//delete row_id;

	//delete storer_text_sym_id;

	//delete is_first_symbol;
	//delete is_last_symbol;
	//delete is_empty;
}