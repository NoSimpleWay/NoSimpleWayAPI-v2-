#pragma once

#define bgroup_with_bg true
#define bgroup_without_bg false

#define bgroup_with_slider true
#define bgroup_without_slider false

#define bgroup_default_bg true
#define bgroup_darken_bg false

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
struct ELocalisationText;
class EDataEntity;

class EGUIStyle;
class EBrickStyle;

class EWindowMain;

class TestObject;

class ETextParser;
class EDataContainer;


typedef void (*data_action_pointer)(Entity*, ECustomData*, float);
typedef void (*text_actions_pointer)(ETextArea*);