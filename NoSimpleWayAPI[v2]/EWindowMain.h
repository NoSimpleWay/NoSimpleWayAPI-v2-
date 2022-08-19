#pragma once



#ifndef _E_GUI_CORE_ALREADY_LINKED_
#define _E_GUI_CORE_ALREADY_LINKED_
#include "NoSimpleWayAPI[v2]/EGUICore.h"
#endif

/**/
#ifndef	_ENTITY_CORE_ALREADY_LINKED_
#define	_ENTITY_CORE_ALREADY_LINKED_
#include "NoSimpleWayAPI[v2]/EntityCore.h"
#endif
/**/


//#ifndef _E_TEXT_CORE_ALREADY_LINKED_
///**/#define _E_TEXT_CORE_ALREADY_LINKED_
///**/#include "NoSimpleWayAPI[v2]/ETextCore.h"
//#endif



constexpr int CLUSTER_DIM_X = 50;
constexpr int CLUSTER_DIM_Y = 50;

constexpr int CLUSTER_SIZE_X = 300;
constexpr int CLUSTER_SIZE_Y = 300;

//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//
class EDataContainer_Group_TextSelectorFromVariants : public EDataContainer
{
public:
	EntityButton* target_button;
};
//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//


namespace EDataActionCollection
{
	void action_open_add_content_window(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_content_to_filter_block(Entity* _entity, ECustomData* _custom_data, float _d);


	void action_open_rarity_selector(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_text_variant(Entity* _entity, ECustomData* _custom_data, float _d);
}

enum FilterAttributeType
{
	FILTER_ATTRIBUTE_TYPE_NON_LISTED,
	FILTER_ATTRIBUTE_TYPE_LISTED,
	FILTER_ATTRIBUTE_TYPE_COSMETIC
};

enum FilterAttributeValueType
{
	FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER,
	FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST,
	FILTER_ATTRIBUTE_VALUE_TYPE_TEXT,
	FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY
};

class FilterBlockAttribute
{
public:
	FilterAttributeType			filter_attribute_type;
	FilterAttributeValueType	filter_attribute_value_type;

	bool have_operator = false;

	ELocalisationText			localisation;
};



static std::vector<FilterBlockAttribute*> registered_filter_block_attributes;

class EWindowMain : public EWindow
{
public:

	virtual void	draw_additional(float _d);
	virtual void	update_additional(float _d);

	//ECluster* cluster_array[CLUSTER_DIM_X][CLUSTER_DIM_Y];

	EWindowMain();
	~EWindowMain();

	//ETextureGabarite* gudron;

	static EWindowMain* link_to_main_window;

	static EButtonGroup* select_rarity_button_group;

};


