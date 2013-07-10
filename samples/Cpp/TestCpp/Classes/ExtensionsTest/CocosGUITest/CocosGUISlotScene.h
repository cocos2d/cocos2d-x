

#ifndef __TestCpp__CocosGUISlotScene__
#define __TestCpp__CocosGUISlotScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../testBasic.h"

#define SWITCH_PANEL_BTN_TAG_CLOTHES        1

#define SWITCH_PANEL_BTN_TAG_CLOTHES        1
#define SWITCH_PANEL_BTN_TAG_WEAPONS        2
#define SWITCH_PANEL_BTN_TAG_PETS           3

#define PANEL_TAG_CLOTHES       4
#define PANEL_TAG_WEAPONS       5
#define PANEL_TAG_PETS          6

#define PANEL_TAG_20_2      7
#define PANEL_TAG_UP        8

#define IMAGEVIEW_TAG_WAL       9

#define IMAGEVIEW_TAG_SLOT_ORIGINAL_CLOTHES      10

enum EQUIP_TYPE {
    EQUIP_TYPE_NONE,
    EQUIP_TYPE_CLOTHES,
    EQUIP_TYPE_WEAPONS,
    EQUIP_TYPE_PETS,
};

using namespace cocos2d;
using namespace cocos2d::extension;

class CocosGUISlotScene : public TestScene
{
public:
	CocosGUISlotScene(bool bPortrait = false);
    
    virtual void onExit();
    
	virtual void runThisTest();
    
	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(CCObject* pSender);
    
    void toCocosGUITestScene(CCObject* pSender);
    
    void switchBtnCallBack(CCObject* pSender);
    
    void createEquip();
    void createClothes();
    void createWeapons();
    void createPets();
    
    void touchEquip(CCObject* pSender);
    void moveEquip(CCObject* pSender);
    void dropEquip(CCObject* pSender);
    
    void backOver(CCObject* pObject);
    
protected:
    UILayer* ul;
    
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
    
    CCPoint widgetLastLocal;
    CCPoint widgetLastNodePosition;
    UIWidget* lastWidgetParent;
};

#endif /* defined(__TestCpp__CocosGUISlotScene__) */
