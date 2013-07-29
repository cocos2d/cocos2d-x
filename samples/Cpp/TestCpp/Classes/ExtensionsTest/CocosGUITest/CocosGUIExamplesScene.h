

#ifndef __TestCpp__CocosGUIExamplesScene__
#define __TestCpp__CocosGUIExamplesScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../testBasic.h"

#define EXAMPLE_PANEL_TAG_ROOT                           1

#define EQUIP_PANEL_TAG_ROOT                            1000
#define EQUIP_PANEL_TAG_UP                              1001
#define EQUIP_PANEL_TAG_CLOTHES                         1002
#define EQUIP_PANEL_TAG_WEAPONS                         1003
#define EQUIP_PANEL_TAG_PETS                            1004

#define EQUIP_SWITCH_PANEL_BUTTON_TAG_CLOTHES           1005
#define EQUIP_SWITCH_PANEL_BUTTON_TAG_WEAPONS           1006
#define EQUIP_SWITCH_PANEL_BUTTON_TAG_PETS              1007

#define WEAPON_PANEL_TAG_ROOT                           2000

#define WEAPON_ITEM_PANEL_TAG                           2100

enum EQUIP_TYPE {
    EQUIP_TYPE_NONE,
    EQUIP_TYPE_CLOTHES,
    EQUIP_TYPE_WEAPONS,
    EQUIP_TYPE_PETS,
};

using namespace cocos2d;
using namespace cocos2d::extension;

class CocosGUIExamplesScene : public TestScene
{
public:
	CocosGUIExamplesScene(bool bPortrait = false);
    
    virtual void onEnter();
    virtual void onExit();
    
	virtual void runThisTest();
    
    void toCocosGUITestScene(Object* pSender);
    
    // example
    void ExamplesInit();
    void ExamplesButtonPanelInit();
    void ExamplesShowEquip(Object* pSender);
    void ExamplesShowWeapon(Object* pSender);
    
    // equip
    void EquipInit();
    void EquipCreate();
    void EquipCreateClothes();
    void EquipCreateWeapons();
    void EquipCreatePets();
    
    void EquipSwitchBtnCallBack(Object* pSender);
    
    void EquipTouch(Object* pSender);
    void EquipMove(Object* pSender);
    void EquipDrop(Object* pSender);
    
    void EquipBackOver(Object* pObject);
    
    void EquipClose(Object* pObject);
    
    // weapon introduce
    void WeaponInit();
    void WeaponCreate();
    
    void WeaponItemTouch(Object* pObject);
    void WeaponItemShowDetail(UIWidget* widget);
    
    void WeaponClose(Object* pObject);
    
protected:
    UILayer* ul;
    
    // equip
    EQUIP_TYPE m_eEquipType;
    
    Dictionary* m_dicBeUsedSlot;
    Dictionary* m_dicEquipClothesSlot;
    Dictionary* m_dicEquipWeaponsSlot;
    Dictionary* m_dicEquipPetsSlot;
    
    Dictionary* m_dicEquipClothes;
    Dictionary* m_dicEquipWeapons;
    Dictionary* m_dicEquipPets;
    
    int container_1_Zorder;
    int container_2_Zorder;
    int container_3_Zorder;
    
    Point container_1_Position;
    Point container_2_Position;
    Point container_3_Position;
    
    Point movePoint;
    Point lastPoint;
    
    Point widgetLastWorldSpace;
    Point widgetLastNodeSpace;
    UIWidget* lastWidgetParent;
    //
};

#endif /* defined(__TestCpp__CocosGUIExamplesScene__) */
