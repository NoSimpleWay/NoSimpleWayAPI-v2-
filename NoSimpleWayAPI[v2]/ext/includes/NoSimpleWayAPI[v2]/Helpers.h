#pragma once
#include <vector>
#include <string>

class ETestObject
{
public:
	int a;
	int *b = new int(0);

	ETestObject();

	static std::vector <ETestObject*> test_object_vector;
};

class Helper
{
public:
	static std::string float_to_string(float _f);
	static std::string float_to_string_with_precision(float _f, float _precision);

	struct hsvrgba_color
	{
		float r = 1.0f;			// a fraction between 0 and 1
		float g;			// a fraction between 0 and 1
		float b;			// a fraction between 0 and 1
		float h = 360.0f;		// angle in degrees
		float s = 1.0f;		// a fraction between 0 and 360
		float v = 1.0f;		// a fraction between 0 and 1
		float a = 1.0f;			// a fraction between 0 and 1
	};

	static std::vector<hsvrgba_color*> registered_color_list;

	struct rgba_color {
		double r;       // a fraction between 0 and 1
		double g;       // a fraction between 0 and 1
		double b;       // a fraction between 0 and 1
		double a;       // a fraction between 0 and 1
	};

	struct hsva_color {
		double h;       // angle in degrees
		double s;       // a fraction between 0 and 1
		double v;       // a fraction between 0 and 1
		double a;       // a fraction between 0 and 1
	};



	static void rgb2hsv(hsvrgba_color* col)
	{
		hsva_color         out;
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


	static void hsv2rgb(hsvrgba_color* col)
	{
		double      hh, p, q, t, ff;
		long        i;
		rgba_color         in;

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