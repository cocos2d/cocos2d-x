/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TestCpp__CocosGUIExamplesEquipScene__
#define __TestCpp__CocosGUIExamplesEquipScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../testBasic.h"


#define EQUIP_LAYOUT_TAG_ROOT                            1000
#define EQUIP_LAYOUT_TAG_UP                              1001
#define EQUIP_LAYOUT_TAG_CLOTHES                         1002
#define EQUIP_LAYOUT_TAG_WEAPONS                         1003
#define EQUIP_LAYOUT_TAG_PETS                            1004

#define EQUIP_SWITCH_LAYOUT_BUTTON_TAG_CLOTHES           1005
#define EQUIP_SWITCH_LAYOUT_BUTTON_TAG_WEAPONS           1006
#define EQUIP_SWITCH_LAYOUT_BUTTON_TAG_PETS              1007

USING_NS_CC;
USING_NS_CC_EXT;

class CocosGUIExamplesEquipScene : public CCScene
{
public:
    CocosGUIExamplesEquipScene();
    ~CocosGUIExamplesEquipScene();
    
    virtual void onEnter();
    virtual void onExit();
    
	virtual void runThisTest();
    
protected:
    void toCocosGUIExamplesRegisterScene(CCObject* pSender);
    void toCocosGUIExamplesWeaponScene(CCObject* pSender);
    
    // equip                                            original function name
    void EquipInit();                                   // EquipInit
    void create();                                      // EquipCreate
    void createClothes();                               // EquipCreateClothes
    void createWeapons();                               // EquipCreateWeapons
    void createPets();                                  // EquipCreatePets
    
    void switchBtnCallBack(CCObject* pSender);          // EquipSwitchBtnCallBack
    
    void touch(CCObject* pSender);                      // EquipTouch
    void move(CCObject* pSender);                       // EquipMove
    void drop(CCObject* pSender);                       // EquipDrop
    
    void backOver(CCObject* pObject);                   // EquipBackOver
    
    void close(CCObject* pObject);                      // EquipClose
    
protected:
    enum EQUIP_TYPE
    {
        EQUIP_TYPE_NONE,
        EQUIP_TYPE_CLOTHES,
        EQUIP_TYPE_WEAPONS,
        EQUIP_TYPE_PETS,
    };
    
protected:
    UILayer* m_pUILayer;
    
    // equip
    EQUIP_TYPE m_eEquipType;
    
    CCDictionary* m_dicBeUsedSlot;
    CCDictionary* m_dicClothesSlot;
    CCDictionary* m_dicWeaponsSlot;
    CCDictionary* m_dicPetsSlot;
    
    CCDictionary* m_dicClothes;
    CCDictionary* m_dicWeapons;
    CCDictionary* m_dicPets;
    
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
};

#endif /* defined(__TestCpp__CocosGUIExamplesEquipScene__) */
