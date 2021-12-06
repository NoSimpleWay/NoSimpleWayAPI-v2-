#include "NSW_api/EUtils.h"
#include <iostream>

float EMath::clamp_value_float(float _v, float _min, float _max)
{
	if (_v < _min) { return _min; }
	if (_v > _max) { return _max; }
	return _v;
}

void EMath::clamp_value_float(float* _v, float _min, float _max)
{
	if (*_v < _min) { *_v = _min; }
	if (*_v > _max) { *_v = _max; }
}

int EMath::clamp_value_int(int _v, int _min, int _max)
{
	if (_v < _min) { return _min; }
	if (_v > _max) { return _max; }
	return _v;
}

float EMath::to_float(std::string _text)
{
	if (_text == "") { return 0.0f; }
	int dot_count = 0;
	//bool too_many_dots = false;
	//bool no_number_after_dot = true;

	bool number_error = false;

	for (int i = 0; i < _text.length(); i++)
	{
		if (_text[i] == '.')
		{
			dot_count++;

			//too many dots
			if (dot_count > 1) { number_error = true; std::cout << "too many dots" << std::endl; break; }
		}

		////have no numbers after dot
		//if ((dot_count >= 1) & (i + 1 >= _text.length())) { number_error = true; std::cout << "no number after dot" << std::endl; break; }

		//wrong position of minus
		if ((_text[i] == '-') && (i != 0)) { number_error = true; std::cout << "wrong position of '-'" << std::endl; return 0.0f; }
	}

	if (number_error) { return 0.0f; }

	if (dot_count > 0)
	{
		return std::stof(_text + "0");
	}
	else
	{
		if (_text == "-")
		{
			return 0.0f;
		}
		else
		{
			return std::stof(_text);
		}
	}
}

std::string* EFile::data_array = new std::string[1];
int EFile::array_size = 0;

void EFile::data_parser(std::string _s)
{
	array_size = 1;
	std::string subdata = "";
	int dim = 0;

	for (int i = 0; i < _s.size(); i++)
	{
		if (_s[i] == '\t') { array_size++; }
	}

	if (array_size > 0)
	{
		data_array = new std::string[array_size];

		for (int i = 0; i < _s.length(); i++)
		{
			if ((_s.at(i) == '\t') || (i + 1 == _s.length()))
			{
				if (i + 1 == _s.length()) { subdata += _s.at(i); }

				data_array[dim] = subdata;

				//std::cout << "_______subdata [" << data_array[dim] << "] added to index " <<  std::endl << std::endl;

				subdata = "";
				dim++;
			}
			else
			{
				subdata += _s.at(i);

				//std::cout << "SUBATA:" << subdata << std::endl;
			}
		}
	}
}

int EFile::find_data_array_id(std::string _s)
{
	return 0;
}

bool EString::is_contain(std::string _text_source, std::string _text_value)
{
	if (_text_source.find(_text_value) != std::string::npos) { return true; }

	return false;
}

void EString::out_debug(std::string _s)
{
	std::cout << _s << std::endl;
}

std::string EString::float_to_string(float _f)
{
	std::string t = std::to_string(_f);

	bool dot_is_found = false;
	bool minus_is_found = false;

	int numbers_before_dot = 0;
	int numbers_after_dot = 0;

	std::string subdata = "";

	/*for (int i = 0; i < t.length(); i++)
	{
		subdata += t.at(i);

		//non-zero numbers before dot
		if ((!dot_is_found) & (t.at(i) != '.'))
		{
			numbers_before_dot++;
		}

		//non-zero numbers after dot
		if ((t.at(i) != '.') & (dot_is_found))
		{
			numbers_after_dot++;

			if (numbers_after_dot >= 2)
			{
				return subdata;
			}
		}

		if ((t.at(i) == '0') & (dot_is_found))
		{
			if (numbers_after_dot == 0)
			{
				if (numbers_before_dot <= 0)
				{
					return "0";
				}

				return subdata.substr(0, subdata.length() - 2);
			}
			else
			{
				return subdata.substr(0, subdata.length() - 1);
			}
		}

		if (t.at(i) == '.')
		{
			dot_is_found = true;
		}
	}*/

	int end_digit_id = 0;

	//return t;
	for (int i = t.length() - 1; i >= 0; i--)
	{
		if (t.at(i) == '.') { return t.substr(0, i); }
		if (t.at(i) != '0') { return t.substr(0, i + 1); }
		
	}

	return subdata;
}