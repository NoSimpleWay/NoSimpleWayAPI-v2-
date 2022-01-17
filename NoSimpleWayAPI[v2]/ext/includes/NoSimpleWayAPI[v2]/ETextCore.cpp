#ifndef _E_TEXT_CORE_ALREADY_LINKED_
/**/#define _E_TEXT_CORE_ALREADY_LINKED_
/**/#include "ETextCore.h"
#endif


EFont::EFont(std::string _name, ETextureGabarite* _g,  ETextureAtlas* _atlas, bool _not_cyrrilic)
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

						EInputCore::logger_param("final uv_size_y", UV_start_y[font_array_id]);
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
			if (show_console_info) { std::cout << std::endl; }

			font_array_id++;
		}

		myfilez.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	for (int i = 0; i < 256; i++)
	{
		EInputCore::logger_param(EInputCore::border_this_text(i, '{'), UV_start_x[i]);
	}
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

ETextArea::~ETextArea()
{
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

		if (i + 1 < data_length)//can read next symbol
		{next_sym = (*stored_text)[i + 1];}
		else//end of text
		{
			temp_s += sym;
			row.push_back(new std::string(temp_s));
			temp_s = "";

			sym = 0;
			next_sym = 0;

			stop_writing = true;
		}

		//new line
		if ((sym == '\\') & (next_sym == 'n'))
		{
			stop_writing = true;

			row.push_back(new std::string (temp_s));
			temp_s = "";
			i++;
		}

		if (!stop_writing)
		{
			temp_s += sym;
		}

	}

	*row_count = row.size();

	EInputCore::logger_param("Count of row", *row_count);
	for (std::string* str : row)
	{
		EInputCore::simple_logger_with_parameter("row", *str);
	}
}

void ETextArea::generate_text()
{
	

	std::string temp_s = "";

	int target_symbol = 0;
	int str_lenght = 0;

	float x_adding = 0.0f;
	float y_adding = 0.0f;


	
	//region_gabarite->

	if
	(
		(sprite_layer != nullptr)
		&
		(region_gabarite != nullptr)
		&
		(font != nullptr)
	)
	{
		*sprite_layer->last_buffer_id = 0;

		if (sprite_layer->vertex_buffer != nullptr)
		{
			delete sprite_layer->vertex_buffer;
		}

		sprite_layer->vertex_buffer = new float[1000];


		for (std::string* str : row)
		{
			temp_s = *str;
			str_lenght = temp_s.length();
			x_adding = 0;

			for (int i = 0; i < str_lenght; i++)
			{
				target_symbol = (int)(temp_s.at(i));
				if (target_symbol < 0) { target_symbol += 256; }

				NS_ERenderCollection::fill_vertex_buffer_custom_uv
				(
					sprite_layer->vertex_buffer,
					*sprite_layer->last_buffer_id,

					*region_gabarite->world_position_x + x_adding + font->offset_x[target_symbol],
					*region_gabarite->world_position_y + y_adding + 50.0f,

					font->size_x_in_pixels[target_symbol] * *font_scale,
					font->size_y_in_pixels[target_symbol] * *font_scale,

					font->UV_start_x[target_symbol],
					font->UV_start_y[target_symbol] - font->UV_size_y[target_symbol],

					font->UV_start_x[target_symbol] + font->UV_size_x[target_symbol],
					font->UV_start_y[target_symbol] * *font_scale
				);

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

				EInputCore::logger_param("caller", font->UV_start_y[target_symbol]);

				x_adding += (font->advance[target_symbol]) * *font_scale;
			}

			EInputCore::logger_param("last buffer id", *sprite_layer->last_buffer_id);

			y_adding -= 20.0f;
		}
	}
	else
	{
		if (!*error)
		{
			if (sprite_layer == nullptr) { EInputCore::logger_simple_error("sprite layer is null!"); }
			if (region_gabarite == nullptr) { EInputCore::logger_simple_error("region gabarite is null!"); }
			if (font == nullptr) { EInputCore::logger_simple_error("font is null!"); }

			*error = true;
		}

		
	}
}



void ETextArea::set_font(EFont* _font)
{
	font = _font;
}

