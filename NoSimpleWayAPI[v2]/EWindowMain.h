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

#define NSW_LOOT_FILTER_MAX_VERSIONS 9
#define NSW_LOOT_FILTER_VERSIONS_BY_DEFAULT 5





constexpr int CLUSTER_DIM_X = 50;
constexpr int CLUSTER_DIM_Y = 50;

constexpr int CLUSTER_SIZE_X = 300;
constexpr int CLUSTER_SIZE_Y = 300;

constexpr float NSW_default_y_force_field_for_separator = 8.0f;
constexpr float NSW_additional_y_force_field_for_separator = 16.0f;






namespace LootFilterVersionPattern
{

#define NSW_LOOT_DEFAULT_VERSION_PATTERN_MAX 5
	//0

	static bool NSW_LOOT_FILTER_VERSION_ACTIVE[NSW_LOOT_FILTER_MAX_VERSIONS]{ false };
	static std::string NSW_LOOT_VERSION_NAME[NSW_LOOT_FILTER_MAX_VERSIONS];

	enum class LootPatternParameterMode
	{
		DO_NOT_CHANGE,
		FORCIBLY_ENABLE,
		FORCIBLY_DISABLE
	};

	struct PatternStruct
	{
	public:
		ELocalisationText			localised_name;
		std::string					key_for_localisation;

		float						focus_multiplier = 1.0f;

		bool						pattern_is_active = true;
		bool						disable_sound = false;
		bool						disable_minimap_elements = false;
		bool						full_ignore_mode = false;

		bool						is_default = false;

		HSVRGBAColor				default_text_color;
		HSVRGBAColor* color_pointer;

		int	show_hide_mode = (int)LootPatternParameterMode::DO_NOT_CHANGE;
		int	continue_mode = (int)LootPatternParameterMode::DO_NOT_CHANGE;

		ETextureGabarite* icon;


	};


	extern std::vector<PatternStruct*> registered_loot_filter_version_patterns;
}


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
	
	extern ETextureGabarite* texture_help_description_exact_match[2];
	
	extern ETextureGabarite* texture_button_plus;
	
	extern ETextureGabarite* texture_button_move_up;
	extern ETextureGabarite* texture_button_move_down;
	extern ETextureGabarite* texture_button_move;
	extern ETextureGabarite* texture_button_move_small;
	
	extern ETextureGabarite* texture_button_cut;
	
	extern ETextureGabarite* texture_button_remove_filter_block;
	
	extern ETextureGabarite* texture_ray;
	
	extern ETextureGabarite* texture_WARNING;
	
	extern ETextureGabarite* texture_config_gear;
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


struct DataEntityTagFilter;
class EntityButtonFilterRule;
class EntityButtonWideItem : public EntityButton
{
public:
	EClickableArea* pointer_to_close_area;

	ELocalisationText localised_name;

	ESpriteLayer*
		second_sprite_layer = nullptr;

	ETextureGabarite*
		texture_icon = nullptr;


	EFilterRule* attached_filter_rule;

	//std::vector<DataEntityTagFilter>	data_entity_tag_required_tag_list;
	//std::vector<DataEntityTagFilter>	data_entity_tag_banned_tag_list;

	std::vector<EntityButtonWideItem*>	attached_game_item_buttons;
	bool is_pattern_filter	= false;
	bool is_part_of_pattern	= false;


	~EntityButtonWideItem();
	static EntityButtonWideItem* create_wide_item_button
	(
		ERegionGabarite* _region_gabarite,
		EButtonGroup* _parent_group,
		EDataEntity* _data_entity,
		EFont* _font,
		bool _can_be_deleted
		//void (*data_action_pointer)(Entity*, ECustomData*, float)
	);

	void change_texture(ETextureGabarite* _texture);

	void reinit_as_pattern_item_button(EFilterRule* _filter_rule, EButtonGroup* _target_group);

};



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
	~EntityButtonForFilterBlock();
};

class EntityButtonFilterBlockError : public EntityButton
{
public:
	EntityButtonFilterBlockError();
	~EntityButtonFilterBlockError();

	EButtonGroupFilterBlock* target_filter_block;

	static EntityButtonFilterBlockError* add_error_button_to_error_list(ERegionGabarite* _gabarite, EButtonGroupFilterBlock* _filter_block, ELocalisationText _ltext);
};


class EntityButtonForUndefinedAttribute : public EntityButton
{
public:
	EButtonGroupFilterBlock* parent_filter_block;
	EButtonGroup* target_part_with_buttons;
	//~EntityButtonFilterBlock
	//int a;
	//EntityButtonFilterBlock() : a(0) {};
	EntityButtonForUndefinedAttribute();
	~EntityButtonForUndefinedAttribute();
};

class EntityButtonForLootFilterSelector : public EntityButton
{
public:
	std::string	loot_filter_full_path;
	std::string	filter_name;
	bool is_autogenerated_loot_filter = false;

	EntityButtonForLootFilterSelector();
	~EntityButtonForLootFilterSelector();
};

class EntityButtonFilterRule : public EntityButton
{
public:
	EFilterRule*								target_filter_rule;
	EDataContainer_Group_DataEntitiesSearch*	target_data_container;

	bool										is_folder = false;
	bool										is_expanded = false;
	bool										hidden_by_folder = false;

	std::string									folder_named_id = "";
	EntityButtonFilterRule*						parent_folder;
	std::vector<EntityButtonFilterRule*>		child_button_list;

	bool entity_is_active() override;

};

class EntityButtonFilterSound : public EntityButtonForFilterBlock
{
public:
	//ENamedSound*				stored_named_sound;
	std::vector <ENamedSound*>	named_sound_vector;
	//irrklang::ISoundSource* target_sound;
	std::string				full_path;
	EButtonGroupSoundList* target_sound_group;

	EntityButtonFilterSound* master_button_pointer;
	~EntityButtonFilterSound();


};

class EntityButtonVariantRouterForFilterBlock : public EntityButtonVariantRouter
{
public:
	EButtonGroupFilterBlock* parent_filter_block;
	GameItemAttribute* used_filter_block_attribute;
	~EntityButtonVariantRouterForFilterBlock();

};

class EntityButtonVariantRouterForLootSimulatorAddition : public EntityButtonVariantRouter
{
public:
	//std::string target_attribute;
	GameItemAttribute* target_attribute;

	bool is_bool_attribute = false;

	std::vector<ELocalisationText> add_one_of_this_string_values;


	std::vector<std::string> suitable_class_list;


};

class EntityButtonVariantRouterLootFilterVerions : public EntityButtonVariantRouterForFilterBlock
{
public:

};

class LootSimulatorPattern;
class DataEntityTagFilter;


enum class DETFConfigurerMode
{
	LOOT_GENERATOR_PATTERN,
	DATA_ENTITY_FILTER
};
class EntityButtonVariantRouterPatternConfigurer : public EntityButtonVariantRouterForFilterBlock
{
public:
	DataEntityTagFilter* target_tag_filter;
	EButtonGroup* target_group_with_configurer_buttons;
	std::vector<EntityButtonVariantRouterPatternConfigurer*>* router_button_vector_pointer;

	DETFConfigurerMode DETF_mode = DETFConfigurerMode::LOOT_GENERATOR_PATTERN;
};

class EntityButtonFilterBlockTab : public EntityButton
{
public:
	int tab_id = 0;

	EButtonGroup* target_filter_editor = nullptr;

	bool is_empty = true;
	bool unsave_changes = false;
};

class EButtonGroupListedBlock;
class EntityButtonForListedSegment : public EntityButtonForFilterBlock
{
public:
	EButtonGroupListedBlock* listed_group;
	EButtonGroup* group_with_items;

	EButtonGroup* target_block_for_highlight;
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

class EntityButtonClearAttachedTextArea : public EntityButton
{
public:
	ETextArea* attached_text_area;
};

class EButtonGroupListedBlock;
class EntityButtonAttributeTab : public EntityButton
{
public:
	bool			is_undefined = false;
	std::string		undefined_value = "";

	EButtonGroup* target_listed_block;
	EButtonGroupListedBlock* target_whole_listed_block;
	EButtonGroupFilterBlock* parent_filter_block;
};

class EntityButtonColorButtonForFilterBlock;
class EntityButtonCosmeticElement : public EntityButton
{
public:
	HSVRGBAColor*							target_color;
	EntityButtonColorButtonForFilterBlock*	assigned_color_button_from_filter_block;
};




//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//
//EButtonGroup
class EButtonGroupLootFilterList : public EButtonGroup
{
public:
	EButtonGroupLootFilterList(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EButtonGroup* part_with_list;
	ETextArea* input_field;
	EntityButtonVariantRouter* pointer_to_filtration_router;
};



class EButtonGroupTopControlSection : public EButtonGroup
{
public:

	//EDataContainer_Group_WholeFilterBlock*	pointer_to_whole_filter_block_data_container	= nullptr;
	//EButtonGroupFilterBlock* pointer_to_filter_block_group = nullptr;

	EButtonGroupTopControlSection(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};





	//void draw_button_group() override;
};

class EButtonGroupPreviewBox : public EButtonGroup
{
public:
	EButtonGroupPreviewBox(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EButtonGroupFilterBlock* pointer_to_filter_block_group = nullptr;
	float box_size_x = 160.0f;

	ETextureGabarite* example_text_texture[2] =
	{
		NS_DefaultGabarites::texture_example_text_for_preview_box,
		NS_DefaultGabarites::texture_example_text_for_preview_box_half
	};

	ETextureGabarite* example_text_bg = NS_DefaultGabarites::texture_example_text_bg_for_preview_box;

	void draw_button_group() override;
};

class EButtonGroupFilterBlockSeparator;
class EButtonGroupFilterBlock : public EButtonGroup
{
public:
	EButtonGroupFilterBlock(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	~EButtonGroupFilterBlock();



	EButtonGroupFilterBlockSeparator* attached_separator = nullptr;

	void clear_non_listed_segment();
	void clear_listed_segment();
	static GameItemAttribute* get_suitable_game_item_attribute(std::string _name);

	EButtonGroup* pointer_to_whole_non_listed_segment;
	EButtonGroup* pointer_to_workspace_non_listed_segment;

	EButtonGroup* pointer_to_listed_segment_in_filter_block;
	EButtonGroup* pointer_to_listed_attributes;
	EButtonGroup* pointer_to_attribute_tab;

	EButtonGroup* pointer_to_fake_listed_segment_in_filter_block;
	EButtonGroup* pointer_to_preview_box_segment;



	EButtonGroup* pointer_to_cosmetic_segment;
	EButtonGroup* pointer_to_sound_segment;
	EButtonGroup* pointer_to_minimap_and_ray_segment;
	//EButtonGroup* pointer_to_ray_segment;
	EButtonGroup* pointer_to_ray_preview_segment;

	EButtonGroup* pointer_to_top_control_block;
	EButtonGroup* pointer_preview_box_group;

	EButtonGroup* pointer_to_ID_block;
	EntityButton* id_button;
	EButtonGroup* pointer_to_block_show_hide_continue;
	EButtonGroup* pointer_to_control_group_mid_import;
	EButtonGroup* pointer_to_control_group_mid_versions;
	EButtonGroup* pointer_to_control_group_mid_show_hide_cosmetic;



	//color section
	EntityButtonColorButtonForFilterBlock* pointer_to_color_button[3];
	EntityButton* pointer_to_color_check_button[3];

	bool	color_check[3]{ true, true, true };
	HSVRGBAColor** pointer_to_HRA_color[3];

	//font size
	EntityButton* text_size_button;
	EntityButtonVariantRouter* text_size_router_button;
	bool	text_size_bool = true;
	float	text_size = 30.0f;

	EntityButtonVariantRouterForFilterBlock* button_show_hide;
	EntityButtonVariantRouterForFilterBlock* button_continue;


	//sounds
	EntityButtonFilterSound* pointer_to_custom_sound_button;
	bool	custom_sound_suppressor_bool;

	EntityButtonFilterSound* pointer_to_game_sound_button;
	bool	game_sound_suppressor_bool;
	EntityButton* user_sound_volume_button;
	EntityButton* ingame_sound_volume_button;

	float	user_sound_volume_value = 1.0f;
	float	ingame_sound_volume_value = 1.0f;


	EntityButtonVariantRouterForFilterBlock* pointer_to_positional_variant_button;

	EntityButtonVariantRouterForFilterBlock* pointer_to_forcibly_disable_ingame_sound_variant_button;
	EntityButtonVariantRouterForFilterBlock* pointer_to_forcibly_disable_user_sound_variant_button;

	EntityButtonVariantRouterForFilterBlock* pointer_to_disable_enable_drop_sound;
	EntityButtonVariantRouterForFilterBlock* pointer_to_optional_user_sound;



	//		MINIMAP ICONS SECTION
	EntityButtonVariantRouterForFilterBlock* pointer_to_minimap_icon_color_router;
	EntityButtonVariantRouterForFilterBlock* pointer_to_minimap_icon_size_router;
	EntityButtonVariantRouterForFilterBlock* pointer_to_minimap_icon_shape_router;
	EntityButtonVariantRouterForFilterBlock* pointer_to_forcibly_disable_minimap_icon_variant_button;

	//		RAY SECTION
	EntityButtonVariantRouterForFilterBlock* pointer_to_ray_color_router;
	EntityButtonVariantRouterForFilterBlock* pointer_to_temporary_option_router;
	bool										ray_suppressor;

	//[0]"Full ignore",
	//[1]"Hide",
	//[2]"Ignore",
	//[3]"Default",
	//[4]"Focus"
	EntityButtonVariantRouterForFilterBlock* version_routers[NSW_LOOT_FILTER_MAX_VERSIONS] = { nullptr };





	bool	minimap_icon_color_suppressor_bool;

	//EButtonGroupFilterBlockAsText*	target_filter_block_as_text_group;
	void post_draw() override;
	void button_group_update(float _d) override;
	void button_group_prechange();

	bool is_this_group_active() override;
	bool is_expanded = false;
	void button_group_postchange() override;


	bool is_default_filter_block = false;
	bool is_base_filter_block = false;

	void refresh_version_router_button();
	void reselect_specific_variant_on_version_routers(int _target_variant);
};


class EButtonGroupFilterBlockSeparator : public EButtonGroup
{
public:
	EButtonGroupFilterBlockSeparator(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	~EButtonGroupFilterBlockSeparator();
	EntityButton* pointer_to_description_button;
	bool			autogenerated_do_dot_save = false;
	bool			is_expanded = false;
	bool			additional_force_field = false;
	bool			for_default_filter_block = false;
};

class EButtonGroupFilterBlockEditor : public EButtonGroup
{
public:
	EButtonGroupFilterBlockEditor(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	void button_group_prechange() override;


	void reinit_all_filter_rule_pattern_buttons();
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

enum class NSW_StoredSoundsType
{
	INGAME_SOUNDS,
	CUSTOM_USER_SOUND
};

class EButtonGroupSoundList : public EButtonGroup
{
public:
	EButtonGroup* part_with_registered_sound;
	EButtonGroup* part_with_selected_sound;
	ETextArea* input_field;

	EButtonGroupSoundList(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	std::vector<ENamedSound*>* pointer_to_sound_list;

	data_action_pointer			action_on_select_for_button;
	EntityButtonFilterSound*	target_sound_button;

	NSW_StoredSoundsType
	stored_sound_type_enum = NSW_StoredSoundsType::INGAME_SOUNDS;


	//EntityButton
	void refresh_sound_list();
	void add_selected_button_to_right_side(ENamedSound* _named_sound);
	void set_colors_to_registered_buttons();
};

class EButtonGroupDataEntity : public EButtonGroup
{
public:

	int data_entity_id = 0;

	EntityButton* main_input_field;
	EntityButton* add_as_item_button;

	EButtonGroup* main_left_side							= nullptr;
	EButtonGroup* right_side_for_filters					= nullptr;
	EButtonGroup* right_side_for_configure					= nullptr;
	EButtonGroup* top_side_for_add_pattern_button			= nullptr;

	EntityButtonWideItem* target_filter_rule_pattern_button	= nullptr;

	EButtonGroupDataEntity(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	void button_group_update(float _d) override;
	void background_update(float _d);

	void show_only_suitable_buttons();

	void prepare_for_filter_pattern(EntityButtonWideItem* _wide_button);
	void prepare_for_default_use();

	EButtonGroup* focused_part = nullptr;
};

class EButtonGroupBottomFilterBlockControl : public EButtonGroup
{
public:
	EButtonGroupBottomFilterBlockControl(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButton* search_button;
	EntityButton* search_button_clear;
};
















//		FOR LOOT SIMULATOR
//		ATTRIBUTE GROUPS
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
class GameAttributeGenerator;
struct GameItemGenerator;
class EButtonGroupAttributeGeneratorGroup : public EButtonGroup
{
public:
	EButtonGroupAttributeGeneratorGroup(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	ID_string	name;
	bool		attribute_generator_is_active = false;

	//GameAttributeGenerator*
	//attribute_generator = nullptr;

	virtual void init();
	virtual void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator);
};







class GameItemGenerator;
class EButtonGroupAttributeGeneratorGroup_Rarity : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_Rarity(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};


class EButtonGroupAttributeGeneratorGroup_ItemLevel : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_ItemLevel(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};

class EButtonGroupAttributeGeneratorGroup_SocketsAndLinks : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_SocketsAndLinks(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};

class EButtonGroupAttributeGeneratorGroup_Quantity : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_Quantity(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};

class EButtonGroupAttributeGeneratorGroup_FlagAttributes : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_FlagAttributes(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};



class EButtonGroupAttributeGeneratorGroup_Quality : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_Quality(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};

class EButtonGroupAttributeGeneratorGroup_GemAttributes : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_GemAttributes(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};

class EButtonGroupAttributeGeneratorGroup_MapAttributes : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_MapAttributes(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};

class EButtonGroupAttributeGeneratorGroup_DefenceProcentile : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_DefenceProcentile(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};


class EButtonGroupAttributeGeneratorGroup_Influense : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_Influense(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};

constexpr int NSW_loot_simulator_explicit_button_count = 3;
class EButtonGroupAttributeGeneratorGroup_Explicit : public EButtonGroupAttributeGeneratorGroup
{
public:
	EButtonGroupAttributeGeneratorGroup_Explicit(ERegionGabarite* _gabarite) :EButtonGroupAttributeGeneratorGroup(_gabarite) {};

	EntityButtonWideItem*
	explicit_item_buttons[NSW_loot_simulator_explicit_button_count];

	void init()																			override;
	void execute_attribute_group(EGameItem* _game_item, GameItemGenerator* _generator)	override;
};


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


class EntityButtonLootItem;
class EButtonGroupLootSimulator : public EButtonGroup
{
public:
	EButtonGroupLootSimulator(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	unsigned int seed = 0;

	float MF_factor = 1.0f;

	bool	delayed_execution = false;
	bool	warning_sign_show_flag = false;
	float	warning_cooldown = 1.0f;
	//void button_group_update(float _d) override;

	static EButtonGroup* pointer_to_loot_buttons_segment;
	static EButtonGroup* pointer_to_patterns_buttons_segment;
	static EButtonGroup* pointer_to_right_side_info_buttons;
	static EButtonGroup* pointer_to_warning_group;
	static EButtonGroup* pointer_to_flag_configurator_group;

	static EntityButtonVariantRouter* pointer_to_target_loot_filter_version_button;
	static EntityButton* pointer_to_input_area_level_button;

	std::vector<EntityButtonVariantRouterForLootSimulatorAddition*> pointer_to_addition_button;

	static bool		show_hidden;
	//static float	show_hidden_cooldown;

	static bool	this_group_is_matched(EntityButtonLootItem* _loot_button, EGameItem* _game_item, EButtonGroupFilterBlock* _filter_block);
	static bool	is_condition_satisfied(int _left, std::string _operator, int _right);
	static bool	is_sockets_matched(std::string _block, std::string _operator, std::string _item);

	void		clear_loot_simulator();
	void		refresh_loot_simulator();
	static void	refresh_button_sizes();

	static HSVRGBAColor temp_color;
	static bool is_condition_sactified_for_listed_expression(std::string _expression, int _matches_count);

	void button_group_update(float _d) override;
	void generate_info_buttons_for_right_side(EntityButtonLootItem* _loot_button);

	void create_info_button(EButtonGroupFilterBlock* _filter_block, std::string _key);



	//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_//_

	EButtonGroupAttributeGeneratorGroup_Rarity* attribute_group_rarity = nullptr;
	int		selected_rarity					= -1;
	int		rarity_override					= -1;

	int	selected_item_level				= 80.0f;
	int	selected_quality				= 0.0f;

	int	selected_gem_level				= 1.0f;
	int	selected_gem_quality			= 0.0f;

	int	selected_maptier				= 1.0f;

	int	selected_procentile				= 0.0f;

	int	selected_sockets				= 3.0f;
	int	selected_links					= 3.0f;

	int	selected_red_weight				= 100.0f;
	int	selected_green_weight			= 100.0f;
	int	selected_blue_weight			= 100.0f;
	int	selected_white_weight			= 0.0f;

	int	selected_quantity				= 1;
	int	selected_corrupted_implicits	= -1;
	int	selected_exarch_level			= 0;
	int	selected_eater_level			= 0;
	int	selected_area_level				= 1;

	bool	is_synthesised					= false;
	bool	is_fractured					= false;
	bool	is_corrupted					= false;
	bool	gem_is_corrupted				= false;
	bool	is_identified					= false;
	bool	is_mirrored						= false;
	bool	is_enchanted					= false;
	bool	is_replica						= false;
	bool	is_transfigured					= false;
	bool	is_blighted						= false;
	bool	is_uberblighted					= false;

	bool	influence_crusader				= false;
	bool	influence_hunter				= false;
	bool	influence_redeemer				= false;
	bool	influence_warlord				= false;
	bool	influence_shaper				= false;
	bool	influence_elder					= false;

	//float	selected_corrupted_imlicits	= 0.0f;


	std::vector<EButtonGroupAttributeGeneratorGroup*> attribute_group_list;
};

class EButtonGroupNonListedLine : public EButtonGroup
{
public:
	EButtonGroupNonListedLine(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButton* target_button_with_attribute_name;
	EntityButtonVariantRouterForFilterBlock* target_button_with_condition;
	EntityButton* target_button_with_value;

	EntityButtonVariantRouterForFilterBlock* rarity_router_button;

	GameItemAttribute* target_game_attribute;
};

class EButtonGroupFilterEditorTopHeader : public EButtonGroup
{
public:
	EButtonGroupFilterEditorTopHeader(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	EButtonGroup* pointer_to_bottom_tabs_section;
	EntityButtonButtonGroupActivator* pointer_to_debug_button;
};

class EButtonGroupConfirmActionOpenAutogeneratedLootFilter : public EButtonGroupConfirmAction
{
public:
	EButtonGroupConfirmActionOpenAutogeneratedLootFilter(ERegionGabarite* _gabarite) :EButtonGroupConfirmAction(_gabarite) {};

	EntityButtonForLootFilterSelector* target_filter_button;
};


class EButtonGroupConfirmActionDelete : public EButtonGroupConfirmAction
{
public:
	EButtonGroupConfirmActionDelete(ERegionGabarite* _gabarite) :EButtonGroupConfirmAction(_gabarite) {};

	EntityButton* target_button_for_deletion;
	EButtonGroup* target_group_for_deletion;
};

struct LootFilterError
{
public:
	ELocalisationText error_localisation;
};
class EButtonGroupLootFilterErrors : public EButtonGroup
{
public:
	EButtonGroupLootFilterErrors(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};
	~EButtonGroupLootFilterErrors();

	EButtonGroup*	part_with_buttons = nullptr;
	ETextArea*		status_text_area;

	std::vector< LootFilterError*> error_struct_list;

	static void check_errors();

	void set_status_error();
	void set_status_fine();

};

//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//^//


struct DescriptionContainerSeparatorExample : public DescriptionContainer
{
public:
	DescriptionContainerSeparatorExample(float _size_x, float _size_y) :DescriptionContainer(_size_x, _size_y) {};
	virtual ~DescriptionContainerSeparatorExample();

	void create_description() override;
};

class EButtonGroupSeparatorExample : public EButtonGroup
{
public:
	EButtonGroupSeparatorExample(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	float cooldown_time = 1.0f;
	void button_group_update(float _d) override;

	bool separators_status = true;
	std::vector<EButtonGroupFilterBlockSeparator*> separators_list;
	std::vector<EButtonGroup*> blocks_for_hide_list;
};

class EButtonGroupSocketPreview : public EButtonGroup
{
public:
	EButtonGroupSocketPreview(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	ETextureGabarite* icon_texture{};
	EGameItem* stored_game_item{};

	void draw_button_group() override;
};

class EButtonGroupListedBlock : public EButtonGroup
{
public:
	EButtonGroupListedBlock(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButtonForFilterBlock* pointer_to_undefined_attribute_field;

	EButtonGroup* section_for_wide_item_buttons;
	//EButtonGroup* pointer_to_attribute_tab;

	EntityButtonVariantRouterForFilterBlock* matching_mode_router_button;

	std::string				filter_attribute_name;
	GameItemAttribute* associated_item_attribute;

	//EntityButton*			button_with;
	EDataContainer_Group_StoreFilterRuleForDataEntitySearcher* data_container_with_filter_rule;
	EntityButtonForFilterBlock* input_field;
	EButtonGroupFilterBlock* parent_filter_block;

	void reinit_all_pattern_wide_item_buttons();
};



static std::string loot_version_localization_key[NSW_LOOT_FILTER_VERSIONS_BY_DEFAULT]
{
	"version_name_very_soft",
	"version_name_soft",
	"version_name_default",
	"version_name_strict",
	"version_name_very_strict"
};

class EButtonGroupVersionControlConfigure : public EButtonGroup
{
public:
	EButtonGroupVersionControlConfigure(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButton* pointer_to_version_name_button[NSW_LOOT_FILTER_MAX_VERSIONS];
	EntityButton* pointer_to_version_name_button_switcher[NSW_LOOT_FILTER_MAX_VERSIONS];


	EButtonGroup* part_with_pattern_list;
	EButtonGroup* part_with_pattern_configure;

	EntityButton* button_disable_minimap_elements;
	EntityButton* button_disable_sound;
	EntityButton* button_full_ignore;
	EntityButton* button_focus_slider;

	EntityButton* button_new_pattern;

	EntityButton* button_remove;
	EntityButtonColorButton* button_text_color;


	EntityButtonVariantRouter* button_router_icon;
	EntityButtonVariantRouter* button_router_continue;
	EntityButtonVariantRouter* button_router_show_hide;



};

class EntityButtonColorButtonForFilterBlock;



class EButtonGroupFilterBlockColors : public EButtonGroupSimpleColorEditor
{
public:
	EButtonGroupFilterBlockColors(ERegionGabarite* _gabarite) :EButtonGroupSimpleColorEditor(_gabarite) {};

	EButtonGroup*					pointer_to_cosmetic_element_group;

	EntityButtonCosmeticElement*	cosmetic_element_button_rama;
	EntityButtonCosmeticElement*	cosmetic_element_button_text;
	EntityButtonCosmeticElement*	cosmetic_element_button_bg;

	void draw_button_group() override;
	//void assign_colors(HSVRGBAColor* _color);
	//void generate_color_pattern_buttons();
};

//
//class EButtonGroupErrorList : public EButtonGroup
//{
//
//};

//
//class EDataContainer_Group_FilterBlockListedSegment : public EDataContainer
//{
//public:
//	EButtonGroup* group_with_listed_buttons;
//
//	EntityButtonVariantRouterForFilterBlock* match_mode_router_button;
//
//	std::string				filter_attribute_name;
//	GameItemAttribute* associated_item_attribute;
//
//	//EntityButton*			button_with;
//	EDataContainer_Group_StoreFilterRuleForDataEntitySearcher* data_container_with_filter_rule;
//	EntityButtonForFilterBlock* input_field;
//};

class EButtonGroupAddExplicitToLootSimulatorItem : public EButtonGroup
{
public:
	EButtonGroupAddExplicitToLootSimulatorItem(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButtonWideItem*
	target_wide_button = nullptr;
};

class EButtonGroupPoeNijaPriceChecker : public EButtonGroup
{
public:
	EButtonGroupPoeNijaPriceChecker(ERegionGabarite* _gabarite) :EButtonGroup(_gabarite) {};

	EntityButton*
	league_name_button = nullptr;

	EButtonGroup*
	pointer_to_status_group = nullptr;

	EntityButton* add_status_button(ELocalisationText _ltext, int _code, int _data_length);
};




namespace NSWRegisteredButtonGroups
{
	static EButtonGroupFilterBlockColors*				filter_block_colors;
	static EButtonGroupAddExplicitToLootSimulatorItem*	add_explicit_to_simulator;
	static EButtonGroupPoeNijaPriceChecker*				poe_ninja_price_checker_group;

	static void register_filter_block_colors_group_for_filter_block();
	static void register_explicit_for_loot_simulator_group();
	static void register_poe_ninja_price_checker();

}

namespace EDataActionCollection
{
	void action_highlight_block_with_error(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_add_content_window(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_selected_content_to_filter_block(Entity* _entity, ECustomData* _custom_data, float _d);


	void action_open_rarity_selector(Entity* _entity, ECustomData* _custom_data, float _d);
	//void action_open_quality_selector(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_select_this_text_variant(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_mark_parent_group_as_removed(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_open_mark_filter_blocks_as_removed_confirmation(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_confirmed_mark_filter_blocks_as_removed_confirmation(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_highlight_removed_block(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_generate_filter_block_text(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_select_this_filter_variant(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_switch_folder_for_data_entity_filter(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_open_loot_filters_list_window(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_confirm_creating_new_loot_filter(Entity* _entity, ECustomData* _custom_data, float _d);
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

	void action_open_delete_listed_segment_confirmation(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_confirmed_deleting_listed_segment(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_open_delete_listed_buttons_confirmation(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_accept_deleting_listed_buttons(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_draw_deleted_group(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_open_data_entity_filter_group(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_change_separator_shrink_flag(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_change_force_field(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_clear_bottom_section_for_search_text(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_clear_main_text_area(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_clear_attached_text_area(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_expand_all_separators(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_shrink_all_separators(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_draw_loot_button(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_refresh_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d);



	void action_refresh_loot_simulator_when_release(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_refresh_loot_simulator_when_press(Entity* _entity, ECustomData* _custom_data, float _d);



	void action_refresh_loot_simulator_sizes(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_loot_item_button(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_highlight_stored_block(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_generate_items_from_this_loot_pattern(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_switch_pattern_folder_state(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_create_or_delete_description_on_hover(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_open_and_refresh_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_and_refresh_error_list(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_change_localisation(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_remove_wide_button(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_make_unsave_filter_block_changes(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_make_unsave_filter_block_changes_and_refresh_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_add_wide_item_to_group_receiver(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_show_hide_autogenerated_loot_filters(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_confirm_decline_window_for_autogenerated_loot_filter(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_confirm_open_autogenerated_loot_filter(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_add_new_undefined_attribute(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_select_this_attribute_tag(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_switch_loot_version_flag(Entity* _entity, ECustomData* _custom_data, float _d);


	void action_select_loot_filter_version_pattern(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_delete_selected_filter_version_pattern(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_create_new_loot_version_pattern(Entity* _entity, ECustomData* _custom_data, float _d);

	//void action_select_loot_filter_pattern			(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_change_selection_of_tag_configurer(Entity* _entity, ECustomData* _custom_data, float _d);



	void action_remove_this_random_user_sound(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_filter_block_color_editor(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_cosmetic_element(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_create_color_pattern_for_filter_block_color_editor(Entity* _entity, ECustomData* _custom_data, float _d);

	void action_configure_pattern_filter_rule(Entity* _entity, ECustomData* _custom_data, float _d);




	//LOOT SIMULATOR ATTRIBUTES AFFIXES
	void action_open_add_explicit_for_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_select_this_affix_for_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_reset_affix_for_loot_simulator(Entity* _entity, ECustomData* _custom_data, float _d);


	void action_get_poe_ninja_prices(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_open_price_check_window(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_add_pattern_as_game_item(Entity* _entity, ECustomData* _custom_data, float _d);















	//type text
	void action_type_search_filter_block_text(ETextArea* _text_area);
	void action_refresh_loot_simulator_when_type(ETextArea* _text_area);
	void action_set_unsave_changes_flag(ETextArea* _text_area);
	void action_change_version_names(ETextArea* _text_area);
	void action_change_version_pattern_name(ETextArea* _text_area);




	void action_multisave_lootfilter(Entity* _entity, ECustomData* _custom_data, float _d);
	void action_save_lootfilter(Entity* _entity, ECustomData* _custom_data, float _d);


	//void 





	//close button grup
	void action_on_closing_loot_versions_window(EButtonGroup* _group);
	void action_on_closing_data_entity_group(EButtonGroup* _group);

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
	FILTER_ATTRIBUTE_VALUE_TYPE_COLOURS_TEXT,
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
	FILTER_ATTRIBUTE_VALUE_CONFIG_COLOR_COLLECTION,
	FILTER_ATTRIBUTE_VALUE_CONFIG_SEPARATOR,

	FILTER_ATTRIBUTE_VALUE_UNDEFINED_ATTRIBUTE,



	FILTER_ATTRIBUTE_VALUE_OLD_VERSION_AUTOGEN,

	FILTER_ATTRIBUTE_VALUE_CONFIG_FAKE_BUTTONS_COUNT,
	
	FILTER_ATTRIBUTE_VALUE_CONFIG_CREATE_PATTERN_BUTTON,
	FILTER_ATTRIBUTE_VALUE_CONFIG_REQUIRED_TAGS,
	FILTER_ATTRIBUTE_VALUE_CONFIG_FORBIDDEN_TAGS,
	FILTER_ATTRIBUTE_VALUE_CONFIG_FINALIZE_FILTER_RULE
	



};

enum DefaultGameAttributeEnum
{
	GAME_ATTRIBUTE_HEIGHT,
	GAME_ATTRIBUTE_WIDTH,
	GAME_ATTRIBUTE_BASE_CLASS,
	GAME_ATTRIBUTE_BASE_TYPE,
	GAME_ATTRIBUTE_HAVE_IMPLICIT,

	GAME_ATTRIBUTE_BASE_WARD,

	GAME_ATTRIBUTE_BASE_ARMOUR,
	GAME_ATTRIBUTE_BASE_ENERGY_SHIELD,
	GAME_ATTRIBUTE_BASE_EVASION,

	_GAME_ATTRIBUTE_LAST_ELEMENT

};
class EGameItemAttributeContainer;
class GameItemAttribute
{
public:
	ELocalisationText			localisation;
	FilterAttributeType			filter_attribute_type;
	FilterAttributeValueType	filter_attribute_value_type;
	EFilterRule* filter_rule;

	ETextureGabarite* icon;

	bool have_operator = false;
	bool have_input_field_for_listed = false;
	bool have_exact_match = false;

	int									attribute_tab_priority = 0;

	std::string							data_entity_tag_filtration;
	std::string							header_localistaion_key = "";
	std::string							description_localisation_key = "";

	bool								always_present;
	float								button_x_size_override = 0.0f;

	bool								commentary_config = false;
	bool								global_attribute_value = false;
	bool								show_in_loot_item_description = true;

	static GameItemAttribute*			get_attribute_by_name(std::vector<GameItemAttribute*>* _vector, std::string _name);
	static EGameItemAttributeContainer* add_new_game_attribute_by_name(EGameItem* _game_item, std::string _name);

	static void							add_new_listed_value_to_game_attribute	(EGameItem* _game_item, std::string _name, ELocalisationText _value);

	static void							game_attribute_set_int_value		(EGameItem* _game_item, std::string _name, int _value);
	static void							game_attribute_set_string_value		(EGameItem* _game_item, std::string _name, std::string _value);

	static GameItemAttribute* default_game_attribute[DefaultGameAttributeEnum::_GAME_ATTRIBUTE_LAST_ELEMENT];
};

static void add_game_item_attribute_to_filter_block(EButtonGroupFilterBlock* _target_group, GameItemAttribute* _filter_block_attribute, std::string _undefined_attribute_text);

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

static std::string generate_filter_block_text(EButtonGroup* _button_group, int _save_mode);
static std::string generate_color_palette_text();
static std::string generate_filter_block_separator_text(EButtonGroupFilterBlockSeparator* _separator, FilterBlockSaveMode _save_mode);


static std::vector<GameItemAttribute*> registered_game_item_attributes;
static EButtonGroupListedBlock* create_block_for_listed_segment(EFilterRule* _filter_rule, GameItemAttribute* _attribute, std::string _attribute_name, EButtonGroup* _parent, EButtonGroupFilterBlock* _parent_filter_block);

#define NSW_registered_rarity_count					4//	1|normal		2|magic			3|rare				4|unique
#define NSW_registered_altered_gem_quality_count	4//	1|superior		2|anomalous		3|divergent			4|phantasmal

enum class LootFilterOpenMode
{
	LOOT_FILTER_OPEN_MODE_USER_FILTER_FROM_DISC,
	LOOT_FILTER_OPEN_MODE_DEFAULT_FILTER_FROM_GAME,
	LOOT_FILTER_OPEN_MODE_BASIC_FILTER_COLORS_FROM_GAME

};


struct RawExplicitDataEntity
{
public:
	bool duplicate = false;


	std::vector					<std::string>	class_list;
	std::string					tier;
	
	std::string					required_level;
	std::string					icon_text;


	std::vector<std::string>	tag_type_list;

	ELocalisationText			mod_description;
	ELocalisationText			mod_name;


	static std::vector<RawExplicitDataEntity> raw_data_entity_list;
};

enum class PoeNinjaAPIMode
{
	CURRENCY,
	UNIQUES,
	DIVINATIONS,
	GEMS,
	FRAGMENTS,
	EMBERS,
	TATTOO,
	OMEN
};
constexpr int filter_tabs_count = 5;
class EWindowMain : public EWindow
{
public:

	virtual void	draw_additional(float _d)		override;
	virtual void	update_additional(float _d)		override;

	//ECluster* cluster_array[CLUSTER_DIM_X][CLUSTER_DIM_Y];

	void register_loot_version_names();

	
	static void get_poe_ninja_api_prices();
	static void parse_json_from_poe_ninja(std::string* _url_content, PoeNinjaAPIMode _mode, bool _console_debug = false);

	void export_loot_patterns_to_file();
	void import_loot_patterns_from_file();

	void add_all_loot_patter_to_loot_simulator(EButtonGroup* left_part_for_patterns);

	void register_loot_simulator_group();

	void register_add_content_to_filter_block_group();

	void register_sound_group();

	void register_about_group();

	void register_world_parameters_group();

	void register_add_data_entity_group();

	void register_create_new_loot_filter_group();

	void register_loot_version_configurator();

	void register_loot_filter_error_list_group();

	void register_2013_april_fool_group();

	void register_styles_group();

	void register_filter_tabs();

	void register_bottom_search_line();

	void register_color_editor();

	void register_default_color_patterns();

	

	EWindowMain();

	void register_loot_filter_list_group();

	void parse_raw_explicit_table();

	void load_config_from_disc();
	void load_config_from_disc_for_filter_version();
	void load_config_from_disc_for_filter_version_patterns();

	void preload_textures();
	void register_rarities();
	void register_alternate_qualities();
	void register_game_item_attributes();
	void register_filter_rules();
	~EWindowMain();

	//ETextureGabarite* gudron;

	static EWindowMain* link_to_main_window;

	//registered button groups
	static EButtonGroup* select_rarity_button_group;
	//static EButtonGroup* select_quality_button_group;
	static EButtonGroupFilterBlockEditor* active_loot_filter_editor;
	static EButtonGroup* world_parameters;
	static EButtonGroup* tab_list_group;
	static EButtonGroupNewLootFilter* create_new_loot_filter_group;
	static EButtonGroupDataEntity* data_entity_filter;
	static EButtonGroupBottomFilterBlockControl* bottom_filter_block_control;
	static EButtonGroupLootSimulator* loot_simulator_button_group;
	static EButtonGroupFilterEditorTopHeader* header_line;
	static EButtonGroupLootFilterList* existing_loot_filter_list;

	static EButtonGroupConfirmActionOpenAutogeneratedLootFilter* confirm_load_autogenerated_block;
	static EButtonGroupConfirmActionDelete* confirm_deletion_group;

	static EButtonGroup* info_button_group;
	static EButtonGroup* style_list_group;
	static EButtonGroup* pointer_to_joke_AD;
	static EButtonGroup* pointer_to_battlepass;
	static EButtonGroupFastMessage* background_loading_info;
	static EButtonGroupLootFilterErrors* registered_group_filter_error_list;

	static EButtonGroupVersionControlConfigure* registered_group_loot_version_configure;


	static std::string username;
	static std::string path_of_exile_folder;

	static void										load_loot_filter_list();

	static void										load_custom_sound_list();
	static void										load_ingame_sound_list();

	static bool										text_is_condition(std::string& buffer_text);

	static bool										first_time_open;
	static bool										have_no_loot_version_config;
	static bool										have_no_loot_version_pattern_config;

	static void										open_loot_filter(std::string _full_path, LootFilterOpenMode _loot_filter_mode);





	static EntityButtonVariantRouterForFilterBlock* create_show_hide_button();




	static EButtonGroupFilterBlock* create_filter_block(EButtonGroup* _target_editor, int _specific_position);
	static EButtonGroupFilterBlockSeparator* create_filter_block_separator(EButtonGroup* _target_whole_group, int _specific_position);

	static void									parse_filter_text_lines(EButtonGroupFilterBlock* _target_filter_block, LootFilterOpenMode _parse_mode);

	static RouterVariant* registered_rarity_router_variants[NSW_registered_rarity_count];
	static RouterVariant* registered_alternate_gem_quality_router_variants[NSW_registered_altered_gem_quality_count];

	static std::vector < std::string>	filter_text_lines;

	static								std::vector<ENamedSound*> default_sound_list;
	static								std::vector<ENamedSound*> custom_sound_list;
	static bool							filter_block_contains_this_text(EButtonGroupFilterBlock* _target_filter_block, std::string* _text);
	//static bool disable_deleting = true;

	static std::vector<EDataEntity*>			registered_data_entity_game_item_list;
	static std::vector<EDataEntity*>			registered_data_entity_class_list;
	static std::vector<EDataEntity*>			registered_data_entity_explicit_list;

	static void									add_game_item_data_entity_to_list();
	

	static std::vector <EButtonGroupFilterBlockEditor*> filter_block_tabs;
	static int selected_filter_tab_id;
	static void write_loot_filter_to_disc(std::string _full_path, std::string* _data);


	static void register_filter_rule_folder(std::string _named_id, std::string _tag, std::string _localisation_key, std::string _icon_path);

	static void register_loot_filter_version_patterns();



	//UNUSUAL CURRENCY FOLDER
	


	static void set_color_version	(HSVRGBAColor* _target_color, int _selected_mode);
	static void set_color_focus		(HSVRGBAColor* _target_color, float _focus);

	static void make_unsaved_loot_filter_changes();
	static void remove_unsave_changes_flag_from_tab();

	static void save_config_file();
	static void save_config_file_for_loot_versions();
	static void save_config_file_for_loot_version_patterns();

	void action_on_close() override;
};




//		LOOT SIMULATOR ELEMENTS
class EGameItemAttributeContainer
{
public:
	GameItemAttribute* target_attribute;

	std::string						attribute_value_str;
	int								attribute_value_int;
	float							attribute_value_float;
	bool							attribute_value_bool;

	std::vector<ELocalisationText>	listed_value_list;
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

	int max_available_sockets = 0;

	int max_stack_size = 1;
	float stack_multiplier = 1.0f;

	bool can_be_synthesised		= false;
	bool can_be_fractured		= false;
	bool can_be_corrupted		= false;
	bool can_be_mirrored		= false;
	bool can_be_enchanted		= false;
	bool can_be_replica			= false;
	bool can_be_quality			= false;
	bool can_be_gem_level		= false;
	bool can_be_maptier			= false;
	bool can_be_blighted		= false;
	bool can_be_uberblighted	= false;
	bool can_be_transfigured	= false;
	bool can_be_procentile		= false;
	bool can_be_influenced		= false;

	bool warn_when_hidden = false;


	std::string short_class_name = "";




};

struct ESuitableFilterBlock
{
public:
	ELocalisationText			localisation_text;
	EButtonGroupFilterBlock* suitable_filter_block;
};

class EntityButtonLootItem : public EntityButton
{
public:
	EGameItem* stored_game_item;

	std::vector<EButtonGroupFilterBlock*> matched_filter_blocks;

	EButtonGroupFilterBlock* matched_show_hide_block;

	//BG COLOR
	HSVRGBAColor** matched_bg_color;
	EButtonGroupFilterBlock* matched_bg_color_block;

	//TEXT COLOR
	HSVRGBAColor** matched_text_color;
	EButtonGroupFilterBlock* matched_text_color_block;

	//RAMA COLOR
	HSVRGBAColor** matched_rama_color;
	EButtonGroupFilterBlock* matched_rama_color_block;


	//MINIMAP ICONS
	EntityButtonVariantRouter* matched_minimap_icon_shape;
	//EButtonGroupFilterBlock* matched_minimap_icon_shape_block;

	//
	EntityButtonVariantRouter* matched_minimap_icon_color;
	//EButtonGroupFilterBlock* matched_minimap_icon_color_block;

	//
	EntityButtonVariantRouter* matched_minimap_icon_size;
	//EButtonGroupFilterBlock* matched_minimap_icon_size_block;

	EButtonGroupFilterBlock* matched_minimap_icon_block;

	//SIZE
	float* matched_size;
	EButtonGroupFilterBlock* matched_size_block;
	bool	have_implicit;

	EntityButtonLootItem();
	~EntityButtonLootItem();

	std::vector<EntityButton*> suitable_buttons_list;



	void get_matched_filter_blocks();
	void get_matched_filter_blocks_list(EButtonGroupFilterBlockEditor* _filter_block_editor);
};

class EntityButtonLootItemSuitableBlocks : public EntityButton
{
public:
	EntityButtonLootItemSuitableBlocks();
	~EntityButtonLootItemSuitableBlocks();

	EButtonGroupFilterBlock* target_filter_block;

};

enum LootPatternFolderEnum
{
	NEW_LEAGUE,
	BASIC_CURRENCY,
	SPECIAL_CURRENCY,
	ITEM_BASES,
	HEIST_ITEMS,
	DELVE_ITEM,
	BREACH_ITEM,
	MAPS_ITEM,
	FLASKS,
	DIVINATIONS,
	BOSS_LOOT,
	SKILL_GEMS,
	SPECIAL_ITEMS
};

class EntityButtonLootPatternSelector : public EntityButton
{
public:
	LootSimulatorPattern*				target_pattern;

	bool								is_folder;
	bool								hidden_by_folder;
	bool								folder_is_expanded = false;

	LootPatternFolderEnum				folder_enum;
	EntityButtonLootPatternSelector*	parent_folder_button;

	EButtonGroup* target_loot_pattern_button_group;

	bool entity_is_active() override;
};


class EntityButtonLootfilterVersionPattern : public EntityButton
{
public:
	LootFilterVersionPattern::PatternStruct* attached_pattern;
};


class EntityButtonColorButtonForFilterBlock : public EntityButtonColorButton
{
public:
	EntityButtonCosmeticElement*		assigned_cosmetic_element_button;
	EButtonGroupFilterBlock*			master_block;

	~EntityButtonColorButtonForFilterBlock();
};






class GameItemAttribute;




#define ROUTER_BUTTON_VECTOR_SIZE 200
namespace DataEntityFilterConfigurer
{
	extern void create_configurer_buttons(DataEntityTagFilter* _tag_filter, DETFConfigurerMode _mode, EButtonGroup* _target_group);

	////////////////////////////////
	extern std::vector <EntityButtonVariantRouterPatternConfigurer*> router_button_vector_for_loot_simulator[ROUTER_BUTTON_VECTOR_SIZE];
	extern std::vector <EntityButtonVariantRouterPatternConfigurer*> router_button_vector_for_data_entity_filter[ROUTER_BUTTON_VECTOR_SIZE];

	extern int router_button_vector_id_for_loot_simulator;
	extern int router_button_vector_id_for_data_entity_filter;

	extern void clear_router_vector(DETFConfigurerMode _mode);
	////////////////////////////////
}


struct GameAttributeGenerator
{
public:
	EGameItemAttributeContainer* target_attribute_container;

	~GameAttributeGenerator();

	float chance_to_generate = 1.0f;

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


struct GameAttributeGeneratorMinMaxFloat : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorMinMaxFloat(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	float min_value;
	float max_value;

	float generator_pow = 1.0f;

	void execute_generation(EGameItem* _game_item);
};



struct GameAttributeGeneratorQuantity : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorQuantity(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};
	//float base_pow = 1.0f;
	void execute_generation(EGameItem* _game_item);
};

struct GameAttributeGeneratorItemLevel : public GameAttributeGenerator
{
public:
	//pointer_to_input_area_level_button
	GameAttributeGeneratorItemLevel(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	void execute_generation(EGameItem* _game_item);
};

struct GameAttributeGeneratorRarity : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorRarity(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	float base_pow = 1.0f;

	void execute_generation(EGameItem* _game_item);
};

struct GameAttributeGeneratorQuality : public GameAttributeGeneratorMinMaxInt
{
public:
	GameAttributeGeneratorQuality(std::string _attribute_name) : GameAttributeGeneratorMinMaxInt(_attribute_name) {};

	float base_pow = 1.0f;

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
	SOCKET_COLOR_ENUM_DELVE,

	_SOCKET_COLOR_ENUM_LAST_ELEMENT
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
	float base_chance_to_add = 1.0f;
	void execute_generation(EGameItem* _game_item);
	//float influence_chance = 0.5f;
};


struct GameAttributeGeneratorExactListedValue : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorExactListedValue(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	void execute_generation(EGameItem* _game_item);
	std::vector<ELocalisationText> exact_values_list;
};

struct GameAttributeGeneratorBoolFlag : public GameAttributeGenerator
{
public:
	GameAttributeGeneratorBoolFlag(std::string _attribute_name) : GameAttributeGenerator(_attribute_name) {};

	float chance_to_activate = 1.0f;
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
	~GameItemGenerator();

	GameItemGenerator(std::string _key);
	int										generations_count = 1;
	std::vector<GameAttributeGenerator*>	attribute_generators_list;

	ELocalisationText						generator_name;

	GameItemGeneratorMode					generator_mode = GameItemGeneratorMode::GAME_ITEM_GENERATOR_MODE_ALL;
	int										random_selection_count = 1;

	bool									forceful_warn_when_hided	= false;
	bool									can_be_configured			= true;
	bool									indicate					= true;

	bool									always_unique	= false;
	bool									always_6_linked	= false;

	ELocalisationText						filtered_by_exact_name;
	std::vector<DataEntityTagFilter*>		filtered_by_tags;

	//ELocalisationText						localisation;
	ETextureGabarite* icon;

	void										generate_game_item_list(std::vector<EGameItem*>* _target_list);
	void										init_game_item(EGameItem* _game_item, GameItemGenerator* _generator);

	//void											add_rarity(int _rarity_min, int _rarity_max, float _pow);
	//void											add_item_level(int _level_min, int _level_max, float _pow);
	//void											add_random_influence(float _chance);
	//GameAttributeGeneratorSocketsLinksColours*	add_sockets_and_links(int _min_sockets, int _max_sockets, int _min_links, int _max_links);
	//void											add_quantity(float _min, float _max, float _pow);
	//void											add_quality(int _min, int _max, float _pow);
	void										add_gem_level(int _level_min, int _level_max, float _pow);

	//void										add_flag_attrubite_by_name(std::string _attribute_name, float _chance_to_add);
	void										add_class(ELocalisationText _attribute_localisation);

	void										add_default_worth_tags(int _min, int _max);
	void										add_default_worth_tags();

};

class LootSimulatorPattern
{
public:
	ELocalisationText									localised_name;
	ETextureGabarite*									icon;
	LootPatternFolderEnum								folder_enum;

	LootSimulatorPattern();
	~LootSimulatorPattern();

	std::vector<GameItemGenerator*>						game_item_generator_list;

	static std::vector<LootSimulatorPattern*>			registered_loot_simulater_pattern_list;
	static void											execute_loot_pattern(LootSimulatorPattern* _pattern);

	bool												additional_force_field_for_buttons = false;
	//static void										refresh_loot_simulator();
	bool												always_show = false;
	bool												is_folder = false;
	bool												have_force_field = false;
	bool												can_be_configured = true;

	std::vector<ID_string>								activate_attribute_group_by_ID_string_list;

	void												activate_attribute_group_by_name(std::string _name);

	int													rarity_override = -1;


};