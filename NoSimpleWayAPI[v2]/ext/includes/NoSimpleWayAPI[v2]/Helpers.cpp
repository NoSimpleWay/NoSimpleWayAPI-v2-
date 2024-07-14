#include "Helpers.h"



std::vector<HRA_color_collection*> Helper::registered_color_list;

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

std::string Helper::get_clipboard_text()
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
	
	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();


	//std::string full_text = clipboard_text;

	return clipboard_text;
	//return std::string();
}



void HSVRGBAColor::set_color(HSVRGBAColor* _HRA_color)
{
	h = _HRA_color->h;
	s = _HRA_color->s;
	v = _HRA_color->v;

	r = _HRA_color->r;
	g = _HRA_color->g;
	b = _HRA_color->b;

	a = _HRA_color->a;

}

void HSVRGBAColor::set_color_RGBA(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;

	a = _a;

	Helper::rgb2hsv(this);
}

void HSVRGBAColor::set_color_HSVA(float _h, float _s, float _v, float _a)
{
	h = _h;
	s = _s;
	v = _v;

	a = _a;

	Helper::hsv2rgb(this);
}
