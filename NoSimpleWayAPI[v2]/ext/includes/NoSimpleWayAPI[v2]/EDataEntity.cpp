#pragma once
#ifndef _E_DATA_ENTITY_ALREADY_LINKED_
/**/#define _E_DATA_ENTITY_ALREADY_LINKED_
/**/#include "EDataEntity.h"
#endif
std::string DataEntityUtils::get_tag_value_by_name(int _id, std::string _name, EDataEntity* _data_entity)
{
	for (EDataTag* data_tag : _data_entity->tag_list)
	{
		if (*data_tag->tag_name == _name)
		{
			if (_id < data_tag->tag_value_list.size())
			{return *data_tag->tag_value_list.at(_id);}
			else
			{return "";}
		}
		
	}

	return "";
}
