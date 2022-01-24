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

struct EDataTag
{
public:
	std::string* tag_name = new std::string("");

	std::vector<std::string*>  tag_value_list;
};

class EDataEntity
{
public:
	std::vector<EDataTag*> tag_list;

};

namespace DataEntityUtils
{
	extern std::string get_tag_value_by_name(int _id, std::string _name, EDataEntity* _data_entity);
}