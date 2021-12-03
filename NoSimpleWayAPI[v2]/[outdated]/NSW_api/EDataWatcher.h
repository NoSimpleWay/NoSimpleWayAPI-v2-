#pragma once
#include <string>
#include <vector>
#include "NSW_api/EGabarite.h"

#include <iostream>
namespace std
{
	//template<typename T>
	_NODISCARD inline string to_string(string _Val) { // convert any to string
		//std::cout << "you are retard? [" << _Val << "]" << std::endl;
		return _Val;
	}
}

//float* retard = new float(0.0f);

class EDataWatcher
{
public:

	template<typename T>

	struct data_watcher_struct
	{
		std::string name;

		data_watcher_struct();

		std::vector <T> watcher_address;
		data_watcher_struct(std::string _name, T _address);
	};

	template<typename T>
	static void add_new_vector_element(std::vector<T> _vector);

	//template<typename T>
	//static void set_name_and_data(data_watcher_struct<T*>* _struct, std::string _name, T* _address);

	template<typename T, typename T2>
	void vectorizator(std::vector<T> _vector, data_watcher_struct<T2>* _struct);
};

template<typename T>
inline void EDataWatcher::add_new_vector_element(std::vector<T> _vector)
{
	_vector.push_back(new T());
}

/*template<typename T>
inline void EDataWatcher::set_name_and_data(data_watcher_struct<T*>* _struct, std::string _name, T* _address)
{
	_struct->name = _name;
	_struct->watcher_address.push_back(&_address);

	std::cout << "pointer data with name [" << _name << "] have address [" << _address << "] and value <" << std::to_string(*_address) << ">" << std::endl;
}*/

template<typename T, typename T2>
inline void EDataWatcher::vectorizator(std::vector<T> _vector, data_watcher_struct<T2>* _struct)
{
	int id = 0;

	for (T zzz : _vector)
	{
		//std::cout << "vector T test [" << id <<"] value: " << _struct->data* << std::to_string(id) << std::endl;
		id++;
	}
}

template<typename T>
inline EDataWatcher::data_watcher_struct<T>::data_watcher_struct()
{
}

template<typename T>
inline EDataWatcher::data_watcher_struct<T>::data_watcher_struct(std::string _name, T _address)
{
	name = _name;
	watcher_address.push_back(_address);

	//std::cout << "pointer data with name [" << _name << "] have address [" << _address << "] and value <" << std::to_string(*_address) << ">" << std::endl;
}

/*template<typename T>
inline EDataWatcher::data_watcher_struct<T>::data_watcher_struct(std::string _name, T _address)
{
	name = _name;
	watcher_address.push_back(&_address);

	std::cout << "non-pointer data with name [" << _name << "] have address [" << &_address << "] and value <" << _address << ">" << std::endl;
}*/
