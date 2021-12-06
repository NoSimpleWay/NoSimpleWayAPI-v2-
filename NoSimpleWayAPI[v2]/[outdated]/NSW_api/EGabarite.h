#pragma once
#include <string>
class EGabarite
{
public:
	float* x = new float(0.0f);
	float* y = new float(0.0f);

	float* x2 = new float(0.0f);
	float* y2 = new float(0.0f);

	float* size_x = new float(0.0f);
	float* size_y = new float(0.0f);

	float* uv_size_x = new float(0.0f);
	float* uv_size_y = new float(0.0f);

	std::string name;

	EGabarite(std::string _name, float _x, float _y, float _size_x, float _size_y);
	EGabarite(std::string _name);
	~EGabarite();
};