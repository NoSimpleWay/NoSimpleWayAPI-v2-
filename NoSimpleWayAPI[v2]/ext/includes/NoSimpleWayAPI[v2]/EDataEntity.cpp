#pragma once
#ifndef _E_DATA_ENTITY_ALREADY_LINKED_
/**/#define _E_DATA_ENTITY_ALREADY_LINKED_
/**/#include "EDataEntity.h"
#endif

std::vector<EDataEntity*>			EDataEntity::data_entity_global_list;
DataEntityNamedStruct				EDataEntity::data_entity_hash_struct;
//std::vector<DataEntityNamedStruct*>	EDataEntity::data_entity_named_structs;

std::string DataEntityUtils::get_tag_value_by_name(int _id, std::string _name, EDataEntity* _data_entity)
{
	for (EDataTag* data_tag : _data_entity->tag_list)
	{
		if (data_tag->tag_name.string_value == _name)
		{
			if (_id < data_tag->tag_value_list.size())
			{return data_tag->tag_value_list.at(_id).string_value;}
			else
			{return "";}
		}
		
	}

	return "";
}

bool DataEntityUtils::is_exist_tag_by_name_and_value(int _id, std::string _name, std::string _value, EDataEntity* _data_entity)
{
	for (EDataTag* data_tag : _data_entity->tag_list)
	{
		if ((data_tag->tag_name.string_value == _name) && (data_tag->tag_value_list[_id].string_value == _value))
		{
			return true;
		}
	}
	return false;
}

std::string DataEntityUtils::get_tag_value_by_name_ID(int _id, ID_string* _name, EDataEntity* _data_entity)
{
	for (EDataTag* data_tag : _data_entity->tag_list)
	{
		if (data_tag->tag_name.ID == _name->ID)
		{
			if (_id < data_tag->tag_value_list.size())
			{
				return data_tag->tag_value_list.at(_id).string_value;
			}
			else
			{
				return "";
			}
		}

	}

	return "";
}

bool DataEntityUtils::is_exist_tag_by_name_and_value_ID(int _id, ID_string* _name, ID_string* _value, EDataEntity* _data_entity)
{
	for (EDataTag* data_tag : _data_entity->tag_list)
	{
		if ((data_tag->tag_name.ID == _name->ID) && (data_tag->tag_value_list[_id].ID == _value->ID))
		{
			//std::cout << "tag [" << data_tag->tag_name.string_value << "]<" << data_tag->tag_name.ID << ">" << " with value [" << data_tag->tag_value_list[_id].string_value << "]<" << data_tag->tag_value_list[_id].ID << "> is exist" << std::endl;;
			return true;
		}
	}
	return false;
}

EDataEntity::EDataEntity()
{
}
