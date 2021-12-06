#pragma once
#include <string>

#define logger(_a_) std::cout << _a_ << std::endl
#define logger_param(_a_, _b_) std::cout << "[" << _a_ << "]: " << std::to_string(_b_) << std::endl

class EMath
{
public:
	static float clamp_value_float(float _v, float _min, float _max);
	static void clamp_value_float(float* _v, float _min, float _max);
	static int clamp_value_int(int _v, int _min, int _max);
	static float to_float(std::string _text);
};

class EFile
{
public:
	static std::string* data_array;
	static int array_size;

	static void data_parser(std::string _s);
	static int find_data_array_id(std::string _s);
};

class EString
{
public:
	static bool is_contain(std::string _text_source, std::string _text_value);
	static void out_debug(std::string _s);
	static std::string float_to_string(float _f);
};