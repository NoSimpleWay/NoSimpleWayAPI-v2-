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
	std::string* name = new std::string("");
	ELocalisationText* description;
};

struct EDataTag
{
public:
	std::string* tag_name = new std::string("");

	std::vector<std::string*>  tag_value_list;

};

class EDataEntity
{
public:
	EDataEntity();

	std::vector<EDataTag*> tag_list;

	static std::vector<EDataEntity*> data_entity_list;

};

namespace DataEntityUtils
{
	extern std::string get_tag_value_by_name(int _id, std::string _name, EDataEntity* _data_entity);
}

struct ELocalisationText
{
public:
	std::string* RU_value = new std::string("");
	std::string* EN_value = new std::string("");
};