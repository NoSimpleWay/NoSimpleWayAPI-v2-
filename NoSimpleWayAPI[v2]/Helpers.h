#pragma once
#include <vector>

class ETestObject
{
public:
	int a;
	int *b = new int(0);

	ETestObject();

	static std::vector <ETestObject*> test_object_vector;
};