#pragma once
#include <string>

/**/
#ifndef _E_CLASS_LINKER_ALREADY_LINKED_
#define _E_CLASS_LINKER_ALREADY_LINKED_
#include "EClassLinker.h"
#endif
/**/

#ifndef _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#define _E_GRAPHIC_CORE_ALREADY_LINKED_
/**/#include "EGraphicCore.h"
#endif
namespace NS_EdataTag
{
	extern std::vector<RegisteredDataTag*> list_of_registered_data_tags;
};

struct RegisteredDataTag
{
	std::string* localised_name = new std::string("");
	ELocalisationText* description;
};

struct EDataTag
{
public:
	std::string* tag_name = new std::string("");

	std::vector<std::string*>  tag_value_list;

};

struct DataEntityNamedStruct
{
public:
	std::vector <std::vector<EDataEntity*>> data_entity_list{16};
	std::string localised_name = "";
};

class EDataEntity
{
public:
	EDataEntity();

	std::vector<EDataTag*> tag_list;

	static std::vector<EDataEntity*> data_entity_global_list;

	static std::vector<DataEntityNamedStruct*> data_entity_named_structs;
};

namespace DataEntityUtils
{
	extern std::string get_tag_value_by_name(int _id, std::string _name, EDataEntity* _data_entity);
	extern bool is_exist_tag_by_name_and_value(int _id, std::string _name, std::string _value, EDataEntity* _data_entity);
}

//struct ELocalisationText
//{
//public:
//	std::string* RU_value = new std::string("");
//	std::string* EN_value = new std::string("");
//};