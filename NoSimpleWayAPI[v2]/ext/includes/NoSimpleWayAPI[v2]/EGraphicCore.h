#pragma once
#include <array>


namespace EGraphicCore
{
	static int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;
	static float correction_x = 1.0f, correction_y = 1.0f;
}

//VERTEX BUFFER ARRAY
constexpr unsigned int VERTICES_PER_SHAPE					= 4;
constexpr unsigned int MAX_SHAPES_COUNT						= 1000;
constexpr unsigned int EXPECTABLE_PARAMETERS_COUNT_FOR_VERTEX	= 10;

constexpr unsigned int TOTAL_MAX_VERTICES_COUNT				= VERTICES_PER_SHAPE * MAX_SHAPES_COUNT * EXPECTABLE_PARAMETERS_COUNT_FOR_VERTEX;

//INDICES ARRAY
constexpr unsigned int INDICES_PER_SHAPE					= (int)(VERTICES_PER_SHAPE * 1.5f);
constexpr unsigned int TOTAL_INDICES_COUNT					= INDICES_PER_SHAPE * MAX_SHAPES_COUNT;



class Batcher
{
private:
	float										vertices_buffer[TOTAL_MAX_VERTICES_COUNT];	//vertex buffer for batcher
	
	unsigned int									last_vertice_buffer_index;				//last element of vertex buffer

	
	unsigned int VBO, VAO, EBO = 0;

	//BATCHER VERTEX DATA SEGMENT
	unsigned int									vertices_data_per_vertex;			//count of parameters for one vertices
	//const std::array<int, 255>						indices_buffer[TOTAL_INDICES_COUNT] = generateData();	//indices array

	typedef										std::array<unsigned int, TOTAL_INDICES_COUNT> array_type;
	const array_type								indices_buffer = generateData();

	array_type generateData() {
		array_type a;
		size_t indices_id		= 0;
		size_t indices_order	= 0;

		for (int i = 0; i < MAX_SHAPES_COUNT; i++) {
			a[indices_id + 0] = indices_order + 0;
			a[indices_id + 1] = indices_order + 1;
			a[indices_id + 2] = indices_order + 3;

			a[indices_id + 3] = indices_order + 1;
			a[indices_id + 4] = indices_order + 2;
			a[indices_id + 5] = indices_order + 3;

			//std::

			indices_id += 6;
			indices_order += 4;
		}
		return a;
	}


public:
	Batcher();
	~Batcher();

};

/*
constexpr unsigned int &fill_indices(unsigned int (&_buffer)[])
{
	for (int i = 0; i < MAX_SHAPES_COUNT; i++)
	{
		_buffer[i] = 1;
	}

	return _buffer;
}*/

static constexpr void zzz( unsigned int _array[TOTAL_INDICES_COUNT])
{
	_array[0] = 0;
}

static constexpr int(&fillarr())[TOTAL_INDICES_COUNT]
{ // no decay; argument must be size 5

	int indices_id		= 0;
	int indices_order	= 0;

	int arr[TOTAL_INDICES_COUNT] = {0};

	for (int i = 0; i < MAX_SHAPES_COUNT; i++)
	{
		arr[indices_id + 0] = indices_order + 0;
		arr[indices_id + 1] = indices_order + 1;
		arr[indices_id + 2] = indices_order + 3;

		arr[indices_id + 3] = indices_order + 1;
		arr[indices_id + 4] = indices_order + 2;
		arr[indices_id + 5] = indices_order + 3;

		indices_id += 6;
		indices_order += 4;
	}

	return arr;
}