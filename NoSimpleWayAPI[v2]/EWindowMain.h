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

/**/
#ifndef _ESOUND_ALREADY_LINKED_
#define _ESOUND_ALREADY_LINKED_
#include "NoSimpleWayAPI[v2]/ESound.h"
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
	EButtonGroupFilterBlock*			parent_filter_block;
	FilterBlockAttribute*				used_filter_block_attribute;
	//~EntityButtonFilterBlock
	//int a;
	//EntityButtonFilterBlock() : a(0) {};
	EntityButtonForFilterBlock();
	virtual ~EntityButtonForFilterBlock();
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

class EntityButtonFilterSound : public EntityButtonForFilterBlock
{
public:
	ENamedSound*			 target_sound;
	//irrklang::ISoundSource* target_sound;
	std::string				full_path;
	EButtonGroupSoundList*	target_sound_group;


};

class EntityButtonVariantRouterForFilterBlock : public EntityButtonVariantRouter
{
public:
	EButtonGroupFilterBlock* parent_filter_block;

	~EntityButtonVariantRouterForFilterBlock();

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

	//EDataContainer_Group_WholeFilterBlock*	pointer_to_whole_filter_block_data_container	= nullptr;
	EButtonGroupFilterBlock*				pointer_to_filter_block_group					= nullptr;

	EButtonGroupTopControlSection(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite){};

	float box_size_x = 160.0f;

	ETextureGabarite* example_text_texture[2] =
	{ 
		NS_EGraphicCore::load_from_textures_folder("example_text"),
		NS_EGraphicCore::load_from_textures_folder("example_text_half")
	};

	ETextureGabarite* example_text_bg = NS_EGraphicCore::load_from_textures_folder("example_text_bg");

	void draw();
};

class EButtonGroupFilterBlock : public EButtonGroup
{
public:
	EButtonGroupFilterBlock(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EButtonGroup*					pointer_to_non_listed_segment;
	EButtonGroup*					pointer_to_listed_segment;
	EButtonGroup*					pointer_to_preview_box_segment;



	EButtonGroup*					pointer_to_cosmetic_segment;
	EButtonGroup*					pointer_to_sound_segment;
	EButtonGroup*					pointer_to_minimap_segment;

	EButtonGroup*					pointer_to_top_control_block;
	EButtonGroup*					pointer_to_control_group_left_show_hide;
	EButtonGroup*					pointer_to_control_group_mid_import;
	EButtonGroup*					pointer_to_control_group_mid_versions;
	EButtonGroup*					pointer_to_control_group_mid_show_hide_cosmetic;


	//color section
	EntityButton*					pointer_to_color_button[3];
	EntityButton*					pointer_to_color_check_button[3];

	bool							color_check[3];
	Helper::HSVRGBAColor**			pointer_to_HRA_color[3];

	//font size
	EntityButton*					text_size_button;
	EntityButton*					text_size_switch_button;
	bool							text_size_bool;
	float							text_size;

	EntityButtonVariantRouter*		button_show_hide;


	EntityButtonFilterSound*		pointer_to_custom_sound_button;
	bool							custom_sound_suppressor_bool;

	EntityButtonFilterSound*		pointer_to_game_sound_button;
	bool							game_sound_suppressor_bool;

	EntityButtonVariantRouter*		pointer_to_minimap_icon_color_router;
	EntityButtonVariantRouter*		pointer_to_minimap_icon_size_router;
	EntityButtonVariantRouter*		pointer_to_minimap_icon_shape_router;
	bool							minimap_icon_color_suppressor_bool;

	//EButtonGroupFilterBlockAsText*	target_filter_block_as_text_group;

	void update(float _d);
};

class EButtonGroupFilterBlockAsText : public EButtonGroup
{
	EButtonGroupFilterBlockAsText(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EButtonGroupFilterBlock* target_filter_block;

	static EButtonGroupFilterBlockAsText* create_filter_block_as_text_group(EButtonGroupFilterBlock* _target_filter_block);
};

class EButtonGroupSoundList : public EButtonGroup
{
public:
	EButtonGroup*				part_with_list;
	ETextArea*					input_field;

	EButtonGroupSoundList(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	std::vector<ENamedSound*>*	pointer_to_sound_list;

	data_action_pointer			action_on_select_for_button;
	//EntityButton
	void refresh_sound_list();
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
	void action_import_filter_text_from_clipboard(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_text_as_item(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_new_filter_block(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_custom_sound_list(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_play_attached_sound(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_invoke_button_action_in_sound_group(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_show_hide_cosmetic_blocks(Entity* _entity, ECustomData* _custom_data, float _d);






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

static void add_filter_block_buttons_to_filter_block(EButtonGroupFilterBlock* _target_group, FilterBlockAttribute* _filter_block_attribute);
static std::string generate_filter_block_text(EButtonGroup* _button_group);


static std::vector<FilterBlockAttribute*> registered_filter_block_attributes;
static EButtonGroup* create_block_for_listed_segment(EFilterRule* _filter_rule, std::string _attribute_name, EButtonGroup* _parent);

#define NSW_registered_rarity_count					4//	1|normal		2|magic			3|rare				4|unique
#define NSW_registered_altered_gem_quality_count	3//	1|anomalous		2|divergent		3|phantasmal		4|unique


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
	static EButtonGroup* world_parameters;

	static std::string username;
	static std::string path_of_exile_folder;

	static void							load_loot_filter_list();
	static void							load_custom_sound_list();

	static bool							text_is_condition(std::string& buffer_text);

	static void							open_loot_filter(std::string _full_path);
	static EButtonGroupFilterBlock*		create_filter_block(EButtonGroup* _target_whole_group, int _specific_position);

	static void							parse_filter_text_lines(EButtonGroupFilterBlock* _target_filter_block);

	static RouterVariant*				registered_rarity_router_variants					[NSW_registered_rarity_count];
	static RouterVariant*				registered_alternate_gem_quality_router_variants	[NSW_registered_altered_gem_quality_count];

	static std::vector < std::string>	filter_text_lines;

	static								std::vector<ENamedSound*> default_sound_list;
	static								std::vector<ENamedSound*> custom_sound_list;
	//static bool disable_deleting = true;


};


