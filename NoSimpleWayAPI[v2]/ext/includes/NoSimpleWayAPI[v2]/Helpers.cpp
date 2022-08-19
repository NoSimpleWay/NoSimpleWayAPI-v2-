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

void Helper::HSVRGBAColor::set_color(HSVRGBAColor* _HRA_color)
{
	h = _HRA_color->h;
	s = _HRA_color->s;
	v = _HRA_color->v;

	r = _HRA_color->r;
	g = _HRA_color->g;
	b = _HRA_color->b;

	a = _HRA_color->a;

}

void Helper::HSVRGBAColor::set_color_RGBA(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;

	a = _a;

	Helper::rgb2hsv(this);
}

void Helper::HSVRGBAColor::set_color_HSVA(float _h, float _s, float _v, float _a)
{
	h = _h;
	s = _s;
	v = _v;

	a = _a;

	Helper::hsv2rgb(this);
}
