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
class EDataContainer_Button_StoreParentFilterBlock : public EDataContainer
{
public:
	EButtonGroup* parent_filter_block;
};
//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//

//BUTTONS
class EntityButtonForFilterBlock : public EntityButton
{
public:
	EButtonGroup* parent_filter_block;
	//~EntityButtonFilterBlock
	//int a;
	//EntityButtonFilterBlock() : a(0) {};
	EntityButtonForFilterBlock();
	~EntityButtonForFilterBlock();
};

class EntityButtonForLootFilterSelector : public EntityButton
{
public:
	std::string	full_path;

	EntityButtonForLootFilterSelector();
	~EntityButtonForLootFilterSelector();
};

class EntityButtonFilterRule : public EntityButton
{
public:
	EFilterRule								*target_filter_rule;
	EDataContainer_Group_DataEntitiesSearch	*target_data_container;

};



//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//
//EButtonGroup
class EButtonGroupLootFilterList : public EButtonGroup
{
public:
	EButtonGroup*	part_with_list;
	ETextArea*		input_field;
};

class EButtonGroupTopControlSection : public EButtonGroup
{
public:
	EDataContainer_Group_WholeFilterBlock*	pointer_to_whole_filter_block_data_container	= nullptr;
	EButtonGroup*							pointer_to_filter_block_group					= nullptr;

	EButtonGroupTopControlSection(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite){};

	float box_size_x = 180.0f;

	ETextureGabarite* example_text_texture[2] =
	{ 
		NS_EGraphicCore::load_from_textures_folder("example_text"),
		NS_EGraphicCore::load_from_textures_folder("example_text_half")
	};

	ETextureGabarite* example_text_bg = NS_EGraphicCore::load_from_textures_folder("example_text_bg");

	void draw();
};



namespace EDataActionCollection
{
	void action_open_add_content_window(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_selected_content_to_filter_block(Entity* _entity, ECustomData* _custom_data, float _d);


	void action_open_rarity_selector(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_quality_selector(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_select_this_text_variant(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_mark_parent_group_as_removed(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_generate_filter_block_text(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_select_this_filter_variant(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_open_loot_filters_list_window(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_mark_button_group_as_removed(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_loot_filter_from_list(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_all_entity_buttons_to_filter_block(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_save_lootfilter(Entity* _entity, ECustomData* _custom_data, float _d);
	//void 
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
	FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY,
	FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST,
	FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER,
	FILTER_ATTRIBUTE_VALUE_TYPE_COLOR
};

class FilterBlockAttribute
{
public:
	FilterAttributeType			filter_attribute_type;
	FilterAttributeValueType	filter_attribute_value_type;
	EFilterRule*				filter_rule;

	bool have_operator = false;

	ELocalisationText			localisation;

	//std::string					data_entity_tag_filtration;

	bool						always_present;
};

static void add_filter_block_buttons_to_filter_block(EButtonGroup* _target_group, FilterBlockAttribute* _filter_block_attribute);
static std::string generate_filter_block_text(EButtonGroup* _button_group);


static std::vector<FilterBlockAttribute*> registered_filter_block_attributes;
static EButtonGroup* create_block_for_listed_segment(EFilterRule* _filter_rule, std::string _attribute_name, EButtonGroup* _parent);

class EWindowMain : public EWindow
{
public:

	virtual void	draw_additional(float _d);
	virtual void	update_additional(float _d);

	//ECluster* cluster_array[CLUSTER_DIM_X][CLUSTER_DIM_Y];

	EWindowMain();
	void register_filter_rules();
	~EWindowMain();

	//ETextureGabarite* gudron;

	static EWindowMain* link_to_main_window;

	static EButtonGroup* select_rarity_button_group;
	static EButtonGroup* select_quality_button_group;
	static EButtonGroup* loot_filter_editor;

	static std::string username;
	static std::string path_of_exile_folder;

	static void				load_loot_filter_list();

	static void				open_loot_filter(std::string _full_path);
	static EButtonGroup*	create_filter_block(EButtonGroup* _target_whole_group);

	//static bool disable_deleting = true;


};


