#pragma once

/**/
#ifndef	_DATA_CORE_ALREADY_LINKED_
#define	_DATA_CORE_ALREADY_LINKED_
#include "EDataCore.h"
#endif
/**/

class Entity
{
private:


public:
	float* position_x = new float(0.0f);
	float* position_y = new float(0.0f);


	Entity();
	~Entity();



};

class EntityPhysicalObject : public Entity
{
	float* mass = new float(1.0f);

	float* inpulse_x = new float(0.0f);
	float* inpulse_y = new float(0.0f);
	float* inpulse_z = new float(0.0f);
};

