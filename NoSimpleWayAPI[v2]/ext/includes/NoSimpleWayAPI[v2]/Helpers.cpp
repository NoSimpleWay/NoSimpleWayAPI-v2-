#include "Helpers.h"

ETestObject::ETestObject()
{
}

std::vector<Helper::HRA_color_collection*> Helper::registered_color_list;
std::vector <ETestObject*> ETestObject::test_object_vector;

std::string Helper::float_to_string(float _f)
{
	std::string t = std::to_string(_f);

	for (int i = t.length() - 1; i >= 0; i--)
	{
		if (t.at(i) == '.') { return t.substr(0, i); }
		if (t.at(i) != '0') { return t.substr(0, i + 1); }

	}

	return "?";
}

std::string Helper::float_to_string_with_precision(float _f, float _precision)
{
	return float_to_string(round(_f * _precision) / _precision);
}

void Helper::hsvrgba_color::set_color(hsvrgba_color* _HRA_color)
{
	h = _HRA_color->h;
	s = _HRA_color->s;
	v = _HRA_color->v;

	r = _HRA_color->r;
	g = _HRA_color->g;
	b = _HRA_color->b;

	a = _HRA_color->a;
	
}
