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



namespace NS_DefaultGabarites
{
	extern ETextureGabarite* texture_example_text_for_preview_box;
	extern ETextureGabarite* texture_example_text_for_preview_box_half;
	extern ETextureGabarite* texture_example_text_bg_for_preview_box;

	extern ETextureGabarite* texture_loot_version_full_ignore;
	extern ETextureGabarite* texture_loot_version_hide;
	extern ETextureGabarite* texture_loot_version_ignore;
	extern ETextureGabarite* texture_loot_version_default;
	extern ETextureGabarite* texture_loot_version_focus;

	extern ETextureGabarite* texture_show_hide_visual_editor;
	extern ETextureGabarite* texture_show_hide_visual_editor_deactivate;

	extern ETextureGabarite* texture_minimap_shape_circle;
	extern ETextureGabarite* texture_minimap_shape_diamond;
	extern ETextureGabarite* texture_minimap_shape_hexagon;
	extern ETextureGabarite* texture_minimap_shape_square;
	extern ETextureGabarite* texture_minimap_shape_star;
	extern ETextureGabarite* texture_minimap_shape_triangle;
	extern ETextureGabarite* texture_minimap_shape_cross;
	extern ETextureGabarite* texture_minimap_shape_moon;
	extern ETextureGabarite* texture_minimap_shape_raindrop;
	extern ETextureGabarite* texture_minimap_shape_kite;
	extern ETextureGabarite* texture_minimap_shape_pentagon;
	extern ETextureGabarite* texture_minimap_shape_upside_down_house;

	extern ETextureGabarite* texture_button_plus;

	extern ETextureGabarite* texture_button_move_up;
	extern ETextureGabarite* texture_button_move_down;
	extern ETextureGabarite* texture_button_move;
	extern ETextureGabarite* texture_button_cut;

	extern ETextureGabarite* texture_button_remove_filter_block;

	extern ETextureGabarite* texture_ray;
}


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
	EButtonGroupFilterBlock* parent_filter_block;
	GameItemAttribute* used_filter_block_attribute;
	//~EntityButtonFilterBlock
	//int a;
	//EntityButtonFilterBlock() : a(0) {};
	EntityButtonForFilterBlock();
	virtual ~EntityButtonForFilterBlock();
};

class EntityButtonForLootFilterSelector : public EntityButton
{
public:
	std::string	loot_filter_full_path;
	std::string	filter_name;

	EntityButtonForLootFilterSelector();
	~EntityButtonForLootFilterSelector();
};

class EntityButtonFilterRule : public EntityButton
{
public:
	EFilterRule* target_filter_rule;
	EDataContainer_Group_DataEntitiesSearch* target_data_container;

};

class EntityButtonFilterSound : public EntityButtonForFilterBlock
{
public:
	ENamedSound* stored_named_sound;
	//irrklang::ISoundSource* target_sound;
	std::string				full_path;
	EButtonGroupSoundList* target_sound_group;
	~EntityButtonFilterSound();


};

class EntityButtonVariantRouterForFilterBlock : public EntityButtonVariantRouter
{
public:
	EButtonGroupFilterBlock* parent_filter_block;

	~EntityButtonVariantRouterForFilterBlock();

};

class EntityButtonFilterBlockTab : public EntityButton
{
public:
	int tab_id = 0;

	EButtonGroup* target_filter_editor;
};




class EntityButtonForListedSegment : public EntityButtonForFilterBlock
{
public:
	EButtonGroup* listed_group;
	//~EntityButtonFilterBlock
	//int a;
	//EntityButtonFilterBlock() : a(0) {};
	EntityButtonForListedSegment();
	virtual ~EntityButtonForListedSegment();
};

class EntityButtonMoveButtonGroup : public EntityButton
{
public:
	EButtonGroup* target_group_for_moving;
	EButtonGroup* parent_group_for_moving;
	MoveVectorMethod move_method = MoveVectorMethod::METHOD_DRAG;
};




//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//
//EButtonGroup
class EButtonGroupLootFilterList : public EButtonGroup
{
public:
	EButtonGroup* part_with_list;
	ETextArea* input_field;
};

class EButtonGroupTopControlSection : public EButtonGroup
{
public:

	//EDataContainer_Group_WholeFilterBlock*	pointer_to_whole_filter_block_data_container	= nullptr;
	EButtonGroupFilterBlock* pointer_to_filter_block_group = nullptr;

	EButtonGroupTopControlSection(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	float box_size_x = 160.0f;

	ETextureGabarite* example_text_texture[2] =
	{
		NS_DefaultGabarites::texture_example_text_for_preview_box,
		NS_DefaultGabarites::texture_example_text_for_preview_box_half
	};

	ETextureGabarite* example_text_bg = NS_DefaultGabarites::texture_example_text_bg_for_preview_box;

	void draw();
};

class EButtonGroupFilterBlockSeparator;
class EButtonGroupFilterBlock : public EButtonGroup
{
public:
	EButtonGroupFilterBlock(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	~EButtonGroupFilterBlock();



	EButtonGroupFilterBlockSeparator* attached_separator = nullptr;

	EButtonGroup* pointer_to_non_listed_segment;
	EButtonGroup* pointer_to_listed_segment;
	EButtonGroup* pointer_to_preview_box_segment;



	EButtonGroup* pointer_to_cosmetic_segment;
	EButtonGroup* pointer_to_sound_segment;
	EButtonGroup* pointer_to_minimap_segment;
	EButtonGroup* pointer_to_ray_segment;
	EButtonGroup* pointer_to_ray_preview_segment;

	EButtonGroup* pointer_to_top_control_block;
	EButtonGroup* pointer_to_top_control_block_right_section;

	EButtonGroup* pointer_to_control_group_left_show_hide;
	EButtonGroup* pointer_to_control_group_mid_import;
	EButtonGroup* pointer_to_control_group_mid_versions;
	EButtonGroup* pointer_to_control_group_mid_show_hide_cosmetic;


	//color section
	EntityButton* pointer_to_color_button[3];
	EntityButton* pointer_to_color_check_button[3];

	bool	color_check[3];
	Helper::HSVRGBAColor** pointer_to_HRA_color[3];

	//font size
	EntityButton* text_size_button;
	EntityButton* text_size_switch_button;
	bool	text_size_bool;
	float	text_size = 0.5f;

	EntityButtonVariantRouterForFilterBlock* button_show_hide;
	EntityButtonVariantRouterForFilterBlock* button_continue;


	//sounds
	EntityButtonFilterSound* pointer_to_custom_sound_button;
	bool	custom_sound_suppressor_bool;

	EntityButtonFilterSound* pointer_to_game_sound_button;
	bool	game_sound_suppressor_bool;
	EntityButton* sound_volume;
	float	sound_volume_value = 1.0f;


	EntityButtonVariantRouterForFilterBlock* pointer_to_positional_variant_button;
	EntityButtonVariantRouterForFilterBlock* pointer_to_disable_enable_drop_sound;
	EntityButtonVariantRouterForFilterBlock* pointer_to_optional_user_sound;



	//		MINIMAP ICONS SECTION
	EntityButtonVariantRouterForFilterBlock* pointer_to_minimap_icon_color_router;
	EntityButtonVariantRouterForFilterBlock* pointer_to_minimap_icon_size_router;
	EntityButtonVariantRouterForFilterBlock* pointer_to_minimap_icon_shape_router;

	//		RAY SECTION
	EntityButtonVariantRouterForFilterBlock* pointer_to_ray_color_router;
	EntityButtonVariantRouterForFilterBlock* pointer_to_temporary_option_router;
	bool										ray_suppressor;

	//[0]"Full ignore",
	//[1]"Hide",
	//[2]"Ignore",
	//[3]"Default",
	//[4]"Focus"
	EntityButtonVariantRouterForFilterBlock* version_routers[5] = { nullptr };





	bool	minimap_icon_color_suppressor_bool;

	//EButtonGroupFilterBlockAsText*	target_filter_block_as_text_group;
	void post_draw();
	void update(float _d);
	void button_group_prechange();

	bool is_visible();
	bool is_expanded = false;
};

class EButtonGroupFilterBlockSeparator : public EButtonGroup
{
public:
	EButtonGroupFilterBlockSeparator(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	~EButtonGroupFilterBlockSeparator();
	EntityButton* pointer_to_description_button;
	bool autogenerated_do_dot_save = false;
	bool			is_expanded = false;
};

class EButtonGroupFilterBlockEditor : public EButtonGroup
{
public:
	EButtonGroupFilterBlockEditor(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	void button_group_prechange();
};

class EButtonGroupNewLootFilter : public EButtonGroup
{
public:
	EButtonGroupNewLootFilter(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButton* input_field_button;
};

enum DataOrderNames
{
	ATTRIBUTE,
	CONDITION_OPERATOR,
	VALUE
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
	EButtonGroup* part_with_list;
	ETextArea* input_field;

	EButtonGroupSoundList(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	std::vector<ENamedSound*>* pointer_to_sound_list;

	data_action_pointer			action_on_select_for_button;
	EntityButtonFilterSound* target_sound_button;
	//EntityButton
	void refresh_sound_list();
};

class EButtonGroupDataEntity : public EButtonGroup
{
public:

	int data_entity_id = 0;

	EntityButton* main_input_field;

	EButtonGroup* main_left_side = nullptr;
	EButtonGroup* right_side_for_filters = nullptr;

	EButtonGroupDataEntity(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	void update(float _d);
	void background_update(float _d);

	EButtonGroup* focused_part = nullptr;
};

class EButtonGroupBottomFilterBlockControl : public EButtonGroup
{
public:
	EButtonGroupBottomFilterBlockControl(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButton* search_button;
	EntityButton* search_button_clear;
};

class EButtonGroupLootSimulator : public EButtonGroup
{
public:
	EButtonGroupLootSimulator(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	static EButtonGroup* pointer_to_loot_buttons_segment;
	static EButtonGroup* pointer_to_patterns_buttons_segment;

	static EntityButtonVariantRouter* pointer_to_target_loot_filter_version_button;
	static EntityButton* pointer_to_input_area_level_button;

	static bool		show_hidden;
	//static float	show_hidden_cooldown;

	static bool	this_group_is_matched(EGameItem* _game_item, EButtonGroupFilterBlock* _filter_block);
	static bool	is_condition_satisfied(int _left, std::string _operator, int _right);
	static bool	is_sockets_matched(std::string _block, std::string _operator, std::string _item);
	void		refresh_loot_simulator();
	static void	refresh_button_sizes();

	static Helper::HSVRGBAColor temp_color;
	static bool is_condition_sactified_for_listed_expression(std::string _expression, int _matches_count);

	void update(float _d);
};

class EButtonGroupNonListedLine : public EButtonGroup
{
public:
	EButtonGroupNonListedLine(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButton* target_button_with_attribute_name;
	EntityButton* target_button_with_condition;
	EntityButton* target_button_with_value;

	EntityButtonVariantRouterForFilterBlock* rarity_router_button;

	GameItemAttribute* target_filter_block_attribute;
};



//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//





class EDataContainer_Group_FilterBlockListedSegment : public EDataContainer
{
public:
	EButtonGroup* group_with_listed_buttons;

	EntityButtonVariantRouterForFilterBlock* match_mode_router_button;

	std::string				filter_attribute_name;
	GameItemAttribute* associated_item_attribute;

	//EntityButton*			button_with;
	EDataContainer_Group_StoreFilterRuleForDataEntitySearcher* data_container_with_filter_rule;
	EntityButtonForFilterBlock* input_field;
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
	void action_open_ingame_sound_list(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_play_attached_sound(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_invoke_button_action_in_sound_group(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_show_hide_cosmetic_blocks(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_sound_for_target_button(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_tab(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_create_new_loot_filter_with_name(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_new_lootfilter_group(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_clone_block(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_separator_block(Entity* _entity, ECustomData* _custom_data, float _d);

	void generate_filter_lines_from_text(std::string& full_text);

	void action_remove_filter_block(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_move_filter_block_up(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_move_filter_block_down(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_move_filter_block(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_move_button_group(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_delete_listed_segment(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_open_data_entity_filter_group(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_change_separator_shrink_flag(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_clear_text(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_draw_loot_button(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_refresh_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_refresh_loot_simulator_sizes(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_highlight_matched_blocks(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_add_items_from_this_loot_pattern(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_create_or_delete_description_on_hover(Entity* _entity, ECustomData* _custom_data, float _d);

	//type text
	void action_type_search_filter_block_text(ETextArea* _text_area);
	void action_refresh_loot_simulator_when_type(ETextArea* _text_area);




	void action_save_lootfilter(Entity* _entity, ECustomData* _custom_data, float _d);
	//void 
}


enum FilterAttributeType
{
	FILTER_ATTRIBUTE_TYPE_NON_LISTED,
	FILTER_ATTRIBUTE_TYPE_LISTED,
	FILTER_ATTRIBUTE_TYPE_COSMETIC,
	FILTER_ATTRIBUTE_TYPE_CONFIG

};

enum FilterAttributeValueType
{
	FILTER_ATTRIBUTE_VALUE_TYPE_NUMBER,
	FILTER_ATTRIBUTE_VALUE_TYPE_RARITY_LIST,
	FILTER_ATTRIBUTE_VALUE_TYPE_TEXT,
	FILTER_ATTRIBUTE_VALUE_TYPE_DATA_ENTITY,
	FILTER_ATTRIBUTE_VALUE_TYPE_QUALITY_LIST,
	FILTER_ATTRIBUTE_VALUE_TYPE_BOOL_SWITCHER,
	FILTER_ATTRIBUTE_VALUE_TYPE_COLOR,
	FILTER_ATTRIBUTE_VALUE_TYPE_MINIMAP_ICON,
	FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_SLIDER,
	FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_INGAME_SOUND,
	FILTER_ATTRIBUTE_VALUE_TYPE_VALUE_USER_SOUND,
	FILTER_ATTRIBUTE_VALUE_TYPE_DISABLE_DROP_SOUND,
	FILTER_ATTRIBUTE_VALUE_TYPE_ENABLE_DROP_SOUND,
	FILTER_ATTRIBUTE_VALUE_TYPE_DISABLE_DROP_SOUND_IF_ALERT,
	FILTER_ATTRIBUTE_VALUE_TYPE_ENABLE_DROP_SOUND_IF_ALERT,
	FILTER_ATTRIBUTE_VALUE_TYPE_RAY,
	FILTER_ATTRIBUTE_VALUE_TYPE_CONTINUE,


	FILTER_ATTRIBUTE_VALUE_CONFIG_VERSIONS,
	FILTER_ATTRIBUTE_VALUE_CONFIG_SEPARATOR,



	FILTER_ATTRIBUTE_VALUE_OLD_VERSION_AUTOGEN,



};

enum DefaultGameAttributeEnum
{
	GAME_ATTRIBUTE_HEIGHT,
	GAME_ATTRIBUTE_WIDTH,
	GAME_ATTRIBUTE_BASE_CLASS,
	GAME_ATTRIBUTE_BASE_TYPE,

	_GAME_ATTRIBUTE_LAST_ELEMENT

};

class GameItemAttribute
{
public:
	ELocalisationText			localisation;
	FilterAttributeType			filter_attribute_type;
	FilterAttributeValueType	filter_attribute_value_type;
	EFilterRule* filter_rule;

	bool have_operator = false;
	bool have_input_field_for_listed = false;
	bool have_exact_match = false;



	std::string					data_entity_tag_filtration;

	bool						always_present;
	float						button_x_size_override = 0.0f;

	bool						commentary_config = false;
	bool						global_attribute_value = false;

	static GameItemAttribute* get_attribute_by_name(std::vector<GameItemAttribute*>* _vector, std::string _name);

	static GameItemAttribute* default_game_attribute[DefaultGameAttributeEnum::_GAME_ATTRIBUTE_LAST_ELEMENT];
};

static void add_filter_block_content_to_filter_block(EButtonGroupFilterBlock* _target_group, GameItemAttribute* _filter_block_attribute);

enum class FilterBlockSaveMode
{
	VERSION_ORIGINAL = -1,
	VERSION_VERY_SOFT = 0,
	VERSION_SOFT = 1,
	VERSION_DEFAULT = 2,
	VERSION_STRICT = 3,
	VERSION_VERY_STRICT = 4
};

enum LootFilterVersionDescription
{
	LOOT_VERSION_FULL_IGNORE,
	LOOT_VERSION_HIDE,
	LOOT_VERSION_IGNORE,
	LOOT_VERSION_DEFAULT,
	LOOT_VERSION_FOCUS

};

static std::string generate_filter_block_text(EButtonGroup* _button_group, FilterBlockSaveMode _save_mode);
static std::string generate_filter_block_separator_text(EButtonGroupFilterBlockSeparator* _separator, FilterBlockSaveMode _save_mode);


static std::vector<GameItemAttribute*> registered_game_item_attributes;
static EButtonGroup* create_block_for_listed_segment(EFilterRule* _filter_rule, GameItemAttribute* _attribute, std::string _attribute_name, EButtonGroup* _parent);

#define NSW_registered_rarity_count					4//	1|normal		2|magic			3|rare				4|unique
#define NSW_registered_altered_gem_quality_count	4//	1|superior		2|anomalous		3|divergent			4|phantasmal

enum class LootFlterOpenMode
{
	LOOT_FILTER_OPEN_MODE_USER_FILTER_FROM_DISC,
	LOOT_FILTER_OPEN_MODE_DEFAULT_FILTER_FROM_GAME

};
constexpr int filter_tabs_count = 5;
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
	static EButtonGroupFilterBlockEditor* loot_filter_editor;
	static EButtonGroup* world_parameters;
	static EButtonGroup* tab_list_group;
	static EButtonGroupNewLootFilter* create_new_loot_filter_group;
	static EButtonGroupDataEntity* data_entity_filter;
	static EButtonGroupBottomFilterBlockControl* bottom_filter_block_control;
	static EButtonGroupLootSimulator* loot_simulator_button_group;

	static std::string username;
	static std::string path_of_exile_folder;

	static void									load_loot_filter_list();

	static void									load_custom_sound_list();
	static void									load_ingame_sound_list();

	static bool									text_is_condition(std::string& buffer_text);

	static void									open_loot_filter(std::string _full_path, LootFlterOpenMode _loot_filter_mode);
	static EButtonGroupFilterBlock* create_filter_block(EButtonGroup* _target_editor, int _specific_position);
	static EButtonGroupFilterBlockSeparator* create_filter_block_separator(EButtonGroup* _target_whole_group, int _specific_position);

	static void									parse_filter_text_lines(EButtonGroupFilterBlock* _target_filter_block, LootFlterOpenMode _parse_mode);

	static RouterVariant* registered_rarity_router_variants[NSW_registered_rarity_count];
	static RouterVariant* registered_alternate_gem_quality_router_variants[NSW_registered_altered_gem_quality_count];

	static std::vector < std::string>	filter_text_lines;

	static								std::vector<ENamedSound*> default_sound_list;
	static								std::vector<ENamedSound*> custom_sound_list;
	static bool							filter_block_contains_this_text(EButtonGroupFilterBlock* _target_filter_block, std::string* _text);
	//static bool disable_deleting = true;

	static std::vector <EButtonGroupFilterBlockEditor*> filter_block_tabs;
	static void write_loot_filter_to_disc(std::string _full_path, std::string* _data);

	static void register_loot_simulator_patterns();

	static void set_color_version(Helper::HSVRGBAColor* _target_color, int _selected_mode);


};




//		LOOT SIMULATOR ELEMENTS
class EGameItemAttributeContainer
{
public:
	GameItemAttribute* target_attribute;

	std::string					attribute_value_str;
	int							attribute_value_int;
	bool						attribute_value_bool;

	std::vector<std::string>	listed_value_list;
};

class EGameItem
{
public:
	EDataEntity* stored_data_entity;

	std::vector<EGameItemAttributeContainer>	attribute_container_list;
	ETextureGabarite* icon;
	ELocalisationText							localised_name;
	int											quantity;
	int											rarity;

	void import_base_attributes_from_data_entity();

	int socket_color_id_array[6];

	int sockets_count = 0;
	int links_count = 0;





};

class EntityButtonLootItem : public EntityButton
{
public:
	EGameItem* stored_game_item;

	std::vector<EButtonGroupFilterBlock*>		matched_filter_blocks;

	Helper::HSVRGBAColor** matched_bg_color;
	EButtonGroupFilterBlock* matched_bg_color_block;

	Helper::HSVRGBAColor** matched_text_color;
	EButtonGroupFilterBlock* matched_text_color_block;

	Helper::HSVRGBAColor** matched_rama_color;
	EButtonGroupFilterBlock* matched_rama_color_block;



	EntityButtonVariantRouter* matched_minimap_icon_shape;
	EButtonGroupFilterBlock* matched_minimap_icon_shape_block;

	EntityButtonVariantRouter* matched_minimap_icon_color;
	EButtonGroupFilterBlock* matched_minimap_icon_color_block;

	EntityButtonVariantRouter* matched_minimap_icon_size;
	EButtonGroupFilterBlock* matched_minimap_icon_size_block;


	float* matched_size;
	EButtonGroupFilterBlock* matched_size_block;

	EntityButtonLootItem();
	~EntityButtonLootItem();



	void get_matched_filter_blocks();
	void get_matched_filter_blocks_list(EButtonGroupFilterBlockEditor* _filter_block_editor);
};

class LootSimulatorPattern;
class EntityButtonLootPatternSelector : public EntityButton
{
public:
	LootSimulatorPattern* target_pattern;
};



class GameItemAttribute;
struct LootSimulatorTagFilter
{
public:
	std::string					target_tag;
	std::vector<std::string>	suitable_values;
	std::vector<std::string>	banned_tags;
};


struct GameAttributeGenerator
{
public:
	EGameItemAttributeContainer* target_attribute_container;

	GameAttributeGenerator(std::string _attribute_name);

	GameItemAttribute* target_attribute;
	void virtual execute_generation(EGameItem* _game_item);
};

//	Random int between MIN and MAX, powered by "generator pow"  min + (pow(rand, generator_pow)  * (max - min))
struct GameAttributeGeneratorMinMaxInt : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorMinMaxInt(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	int min_value;
	int max_value;

	float generator_pow = 1.0f;

	void execute_generation(EGameItem* _game_item);
};

struct GameAttributeGeneratorQuantity : public GameAttributeGeneratorMinMaxInt
{
public:
	GameAttributeGeneratorQuantity(std::string _attribute_name) : GameAttributeGeneratorMinMaxInt(_attribute_name) {};

	void execute_generation(EGameItem* _game_item);
};
struct GameAttributeGeneratorRarity : public GameAttributeGeneratorMinMaxInt
{
public:
	GameAttributeGeneratorRarity(std::string _attribute_name) : GameAttributeGeneratorMinMaxInt(_attribute_name) {};

	void execute_generation(EGameItem* _game_item);
};

//	Generate sockets and colors
enum SocketColorEnum
{
	SOCKET_COLOR_ENUM_RED,
	SOCKET_COLOR_ENUM_GREEN,
	SOCKET_COLOR_ENUM_BLUE,
	SOCKET_COLOR_ENUM_WHITE,
	SOCKET_COLOR_ENUM_ABYSS,
	SOCKET_COLOR_ENUM_DELVE
};
struct GameAttributeGeneratorSocketsLinksColours : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorSocketsLinksColours(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	int		sockets_min_value = 1;
	int		sockets_max_value = 6;
	float	sockets_pow = 1.0f;

	int		links_min = 1;
	int		links_max = 6;
	float	links_pow = 1.0f;

	int		color_weight[6];

	void execute_generation(EGameItem* _game_item);
};

struct GameAttributeGeneratorMapInfluence : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorMapInfluence(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	void execute_generation(EGameItem* _game_item);
};

struct GameAttributeGeneratorItemInfluence : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorItemInfluence(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	void execute_generation(EGameItem* _game_item);
	float influence_chance = 0.5f;
};


struct GameAttributeGeneratorExactListedValue : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorExactListedValue(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	void execute_generation(EGameItem* _game_item);
	std::vector<std::string> exact_values_list;
};

struct GameAttributeGeneratorBoolFlag : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorBoolFlag(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	float chance_to_activate = 0.5f;
	void execute_generation(EGameItem* _game_item);
};

enum class GameItemGeneratorMode
{
	GAME_ITEM_GENERATOR_MODE_ALL,
	GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT,
	GAME_ITEM_GENERATOR_MODE_RANDOM_COUNT_ERASE

};

struct GameItemGenerator
{
public:
	GameItemGenerator();
	int										generations_count = 1;
	std::vector<GameAttributeGenerator*>	attribute_generators_list;

	GameItemGeneratorMode					generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_ALL;
	int										random_selection_count = 1;

	std::string								filtered_by_exact_name;
	std::vector<LootSimulatorTagFilter*>	filtered_by_tags;

	ELocalisationText						localisation;
	ETextureGabarite* icon;

	void									generate_game_item_list(std::vector<EGameItem*>* _target_list);
	void									init_game_item(EGameItem* _game_item);

};

class LootSimulatorPattern
{
public:
	ELocalisationText							localised_name;
	ETextureGabarite* icon;

	LootSimulatorPattern();

	std::vector<GameItemGenerator*>				game_item_generator_list;

	static std::vector<LootSimulatorPattern*>	registered_loot_simulater_pattern_list;
	static void									refresh_loot_simulator(LootSimulatorPattern* _pattern);
	//static void								refresh_loot_simulator();

};