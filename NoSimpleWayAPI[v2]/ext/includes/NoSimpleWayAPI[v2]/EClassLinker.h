#pragma once

#define bgroup_with_bg true
#define bgroup_without_bg false

#define bgroup_with_slider true
#define bgroup_without_slider false

#define bgroup_default_bg true
#define bgroup_darken_bg false

#define disable_deleting	false
#define debug_deleting		false


enum DebugStructID
{
	GROUP_GABARITES,
	CULLING_LINES,
	HIGHEST_POINT_Y,
	ENTITY_GABARITES,
	DISABLE_GL_SCISSOR,
	PHANTOM_HIGHLIGHT_FOR_GROUPS,
	PHANTOM_HIGHLIGHT_FOR_BUTTONS,

	DEBUG_STRUCT_ID_LAST_ELEMENT
};


class ECustomData;
class ERegionGabarite;
class EClickableArea;
class EDataContainer;




class Entity;
class EntityPhysicalObject;
class EntityButton;
class ECluster;

class ERenderBatcher;
class ETextureAtlas;
class ETextureGabarite;
class ESprite;
class ESpriteLayer;
class ESpriteFrame;

class EWindow;
//class EButtonGroupRow;
class EButtonGroup;

class EFont;
class ETextArea;
class EFontGlyph;

struct EDataTag;
struct RegisteredDataTag;
class EDataEntity;

class EGUIStyle;
class EBrickStyle;

class EWindowMain;

class TestObject;

class ETextParser;
class EDataContainer;
class EBrickPlane;

class ELocalisationText;
class GameItemAttribute;

typedef void (*data_action_pointer)(Entity*, ECustomData*, float);

struct hsvrgba_color;

typedef void (*text_actions_pointer)(ETextArea*);

class EntityButtonVariantRouter;
class EButtonGroupFilterBlock;

class EButtonGroupSoundList;
class EButtonGroupRouterVariant;
class EntityButtonVariantRouterForFilterBlock;
class EntityButtonForFilterBlock;

class EntityButtonVerticalSlider;
class EGameItem;
