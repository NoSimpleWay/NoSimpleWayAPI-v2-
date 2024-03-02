#pragma once
#include <vector>
#include <string>
#include <algorithm>

enum class ColorButtonMode
{
	CBM_OPEN_WINDOW,
	CBM_SELECT_COLOR,
	CBM_CUSTOM//,
	//CBM_NONE

};

#ifndef _HELPER_ALREADY_LINKED_
#define _HELPER_ALREADY_LINKED_
struct HSVRGBAColor
{
	float r = 1.0f;			//	red
	float g = 0.9f;				//	green
	float b = 0.8f;				//	blue

	float h = 360.0f;		//	HUE
	float s = 1.0f;			//	saturation
	float v = 1.0f;			//	value

	float a = 1.0f;			//	alpha

	void set_color(HSVRGBAColor* _HRA_color);

	void set_color_RGBA(float _r, float _g, float _b, float _a);
	void set_color_HSVA(float _h, float _s, float _v, float _a);

	bool is_from_collection = true;

	//unsigned int pointers_to_color = 0;
};

#include "ETextCore.h"
struct HRA_color_collection
{
	HSVRGBAColor		target_color;
	ELocalisationText	localised_name;

	std::vector<HSVRGBAColor*> pointers_to_this_collection;
};



class Helper
{
public:
	static std::string float_to_string(float _f);
	static std::string float_to_string_with_precision(float _f, float _precision);
	






	

	static std::vector<HRA_color_collection*> registered_color_list;





	static void rgb2hsv(HSVRGBAColor* col)
	{
		double      min, max, delta;

		min = col->r < col->g ? col->r : col->g;
		min = min < col->b ? min : col->b;

		max = col->r > col->g ? col->r : col->g;
		max = max > col->b ? max : col->b;

		col->v = max;                                // v
		delta = max - min;
		if (delta < 0.00001f)
		{
			col->s = 0;
			col->h = 0; // undefined, maybe nan?
		}

		{
			if (max > 0.0f) { // NOTE: if Max is == 0, this divide would cause a crash
				col->s = (delta / max);                  // s
			}
			else {
				// if max is 0, then r = g = b = 0              
				// s = 0, h is undefined
				col->s = 0.0f;
				col->h = NAN;                            // its now undefined
			}

			if (col->r >= max)                           // > is bogus, just keeps compilor happy
				col->h = (col->g - col->b) / delta;        // between yellow & magenta
			else
				if (col->g >= max)
					col->h = 2.0f + (col->b - col->r) / delta;  // between cyan & yellow
				else
					col->h = 4.0f + (col->r - col->g) / delta;  // between magenta & cyan

			col->h *= 60.0;                              // degrees

			if (col->h < 0.0)
				col->h += 360.0f;
		}
	}


	static void hsv2rgb(HSVRGBAColor* col)
	{
		double      hh, p, q, t, ff;
		long        i;

		col->s = std::clamp(col->s, 0.0f, 1.0f);
		col->v = std::clamp(col->v, 0.0f, 1.0f);


		if (col->s <= 0.0f) {       // < is bogus, just shuts up warnings
			col->r = col->v;
			col->g = col->v;
			col->b = col->v;
		}
		else
		{
			hh = col->h;
			if (hh >= 360.0f) hh = 0.0;
			hh /= 60.0f;
			i = (long)hh;
			ff = hh - i;
			p = col->v * (1.0f - col->s);
			q = col->v * (1.0f - (col->s * ff));
			t = col->v * (1.0f - (col->s * (1.0f - ff)));

			switch (i) {
			case 0:
				col->r = col->v;
				col->g = t;
				col->b = p;
				break;
			case 1:
				col->r = q;
				col->g = col->v;
				col->b = p;
				break;
			case 2:
				col->r = p;
				col->g = col->v;
				col->b = t;
				break;

			case 3:
				col->r = p;
				col->g = q;
				col->b = col->v;
				break;
			case 4:
				col->r = t;
				col->g = p;
				col->b = col->v;
				break;
			case 5:
			default:
				col->r = col->v;
				col->g = p;
				col->b = q;
				break;
			}
		}

		//col->r = 1.0f;
		//return out;
	}
};


#endif