

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
    ~CocosGUIExamplesScene();

    virtual void onEnter();
    virtual void onExit();
    
	virtual void runThisTest();
    
	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(CCObject* pSender);
    
    void toCocosGUITestScene(CCObject* pSender);
    
    // example
    void ExamplesInit();
    void ExamplesButtonPanelInit();
    void ExamplesShowEquip(CCObject* pSender);
    void ExamplesShowWeapon(CCObject* pSender);
    
    // equip
    void EquipInit();
    void EquipCreate();
    void EquipCreateClothes();
    void EquipCreateWeapons();
    void EquipCreatePets();
    
    void EquipSwitchBtnCallBack(CCObject* pSender);
    
    void EquipTouch(CCObject* pSender);
    void EquipMove(CCObject* pSender);
    void EquipDrop(CCObject* pSender);
    
    void EquipBackOver(CCObject* pObject);
    
    void EquipClose(CCObject* pObject);
    
    // weapon introduce
    void WeaponInit();
    void WeaponCreate();
    
    void WeaponItemTouch(CCObject* pObject);
    void WeaponItemShowDetail(UIWidget* widget);
    
    void WeaponClose(CCObject* pObject);
    
protected:
    UILayer* ul;
    
    // equip
    EQUIP_TYPE m_eEquipType;
    
    CCDictionary* m_dicBeUsedSlot;
    CCDictionary* m_dicEquipClothesSlot;
    CCDictionary* m_dicEquipWeaponsSlot;
    CCDictionary* m_dicEquipPetsSlot;
    
    CCDictionary* m_dicEquipClothes;
    CCDictionary* m_dicEquipWeapons;
    CCDictionary* m_dicEquipPets;
    
    int container_1_Zorder;
    int container_2_Zorder;
    int container_3_Zorder;
    
    CCPoint container_1_Position;
    CCPoint container_2_Position;
    CCPoint container_3_Position;
    
    CCPoint movePoint;
    CCPoint lastPoint;
    
    CCPoint widgetLastWorldSpace;
    CCPoint widgetLastNodeSpace;
    UIWidget* lastWidgetParent;
    //
};

#endif /* defined(__TestCpp__CocosGUIExamplesScene__) */
