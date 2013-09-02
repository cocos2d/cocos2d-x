


#include "CocosGUIExamplesEquipScene.h"
#include "CocosGUIExamplesRegisterScene.h"
#include "CocosGUIExamplesWeaponScene.h"

CocosGUIExamplesEquipScene::CocosGUIExamplesEquipScene()
{
    CCScene::init();
}

CocosGUIExamplesEquipScene::~CocosGUIExamplesEquipScene()
{
    
}

void CocosGUIExamplesEquipScene::onEnter()
{
    CCScene::onEnter();
    
    m_pUILayer = UILayer::create();
    m_pUILayer->scheduleUpdate();
    addChild(m_pUILayer);
    
    // equip initialize
    EquipInit();
    
    // left button
    UIButton* left_button = UIButton::create();
    left_button->setTouchEnable(true);
    left_button->loadTextures("cocosgui/UITest/b1.png", "cocosgui/UITest/b2.png", "");
    float left_button_width = left_button->getContentSize().width;
    left_button->setPosition(ccp(left_button_width - left_button_width / 2, m_pUILayer->getContentSize().height / 2));
    left_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::toCocosGUIExamplesRegisterScene));
    m_pUILayer->addWidget(left_button);
    
    // right button
    UIButton* right_button = UIButton::create();
    right_button->setTouchEnable(true);
    right_button->loadTextures("cocosgui/UITest/f1.png", "cocosgui/UITest/f2.png", "");
    right_button->setPosition(ccp(m_pUILayer->getContentSize().width - right_button->getContentSize().width / 2, m_pUILayer->getContentSize().height / 2));
    right_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::toCocosGUIExamplesWeaponScene));
    m_pUILayer->addWidget(right_button);
}

void CocosGUIExamplesEquipScene::onExit()
{
    m_pUILayer->removeFromParent();
    
    CCSSceneReader::purgeSceneReader();
    UIHelper::purgeUIHelper();
    UIActionManager::purgeUIActionManager();
    
    CCScene::onExit();
}

void CocosGUIExamplesEquipScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUIExamplesEquipScene::toCocosGUIExamplesRegisterScene(CCObject *pSender)
{
    CocosGUIExamplesRegisterScene* pScene = new CocosGUIExamplesRegisterScene();
    pScene->runThisTest();
    pScene->release();
}

void CocosGUIExamplesEquipScene::toCocosGUIExamplesWeaponScene(CCObject *pSender)
{
    CocosGUIExamplesWeaponScene* pScene = new CocosGUIExamplesWeaponScene();
    pScene->runThisTest();
    pScene->release();
}

// equip
void CocosGUIExamplesEquipScene::EquipInit()
{
    m_eEquipType = EQUIP_TYPE_CLOTHES;
    
    m_dicBeUsedSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicBeUsedSlot);
    m_dicClothesSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicClothesSlot);
    m_dicWeaponsSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicWeaponsSlot);
    m_dicPetsSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicPetsSlot);
    
    m_dicClothes = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicClothes);
    m_dicWeapons = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicWeapons);
    m_dicPets = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicPets);
    
    container_1_Zorder = 0;
    container_2_Zorder = 0;
    container_3_Zorder = 0;
    container_1_Position = CCPointZero;
    container_2_Position = CCPointZero;
    container_3_Position = CCPointZero;
    movePoint = CCPointZero;
    lastPoint = CCPointZero;
    
    widgetLastWorldSpace = CCPointZero;
    widgetLastNodeSpace = CCPointZero;
    lastWidgetParent = NULL;
    //        
    
    // equip root from json
    Layout* equipe_root =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/equip_1/equip_1.json"));
    equipe_root->setWidgetTag(EQUIP_LAYOUT_TAG_ROOT);
    m_pUILayer->addWidget(equipe_root);        
    
    // title layout
    Layout* title_layout = dynamic_cast<Layout*>(equipe_root->getChildByName("title_panel"));
    // close button
    UIButton* close_btn = dynamic_cast<UIButton*>(title_layout->getChildByName("close_button"));
    close_btn->setVisible(false);
//    close_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::close));
    
    // up layout
    Layout* up_layout = dynamic_cast<Layout*>(equipe_root->getChildByName("up_panel"));
    up_layout->setWidgetTag(EQUIP_LAYOUT_TAG_UP);
    
    // switch button
    // close button
    UITextButton* clothes_btn = dynamic_cast<UITextButton*>(up_layout->getChildByName("clothes_button"));
    clothes_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::switchBtnCallBack));
    clothes_btn->setWidgetTag(EQUIP_SWITCH_LAYOUT_BUTTON_TAG_CLOTHES);
    clothes_btn->disable();
    
    // weapons button
    UITextButton* weapons_btn = dynamic_cast<UITextButton*>(up_layout->getChildByName("weapons_button"));
    weapons_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::switchBtnCallBack));
    weapons_btn->setWidgetTag(EQUIP_SWITCH_LAYOUT_BUTTON_TAG_WEAPONS);
    
    // pets button
    UITextButton* pets_btn = dynamic_cast<UITextButton*>(up_layout->getChildByName("pets_button"));
    pets_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::switchBtnCallBack));
    pets_btn->setWidgetTag(EQUIP_SWITCH_LAYOUT_BUTTON_TAG_PETS);
    
    // repertories
    // clothes layout
    Layout* clothes_layout = dynamic_cast<Layout*>(equipe_root->getChildByName("clothes_panel"));
    clothes_layout->setWidgetTag(EQUIP_LAYOUT_TAG_CLOTHES);
    
    // weapons layout
    Layout* weapons_layout = dynamic_cast<Layout*>(equipe_root->getChildByName("weapons_panel"));
    weapons_layout->setWidgetTag(EQUIP_LAYOUT_TAG_WEAPONS);
    
    // pets layout
    Layout* pets_layout = dynamic_cast<Layout*>(equipe_root->getChildByName("pets_panel"));
    pets_layout->setWidgetTag(EQUIP_LAYOUT_TAG_PETS);
    
    container_1_Zorder = clothes_layout->getWidgetZOrder();
    container_2_Zorder = weapons_layout->getWidgetZOrder();
    container_3_Zorder = pets_layout->getWidgetZOrder();
    
    container_1_Position = clothes_layout->getPosition();
    container_2_Position = weapons_layout->getPosition();
    container_3_Position = pets_layout->getPosition();
    
    CCObject* obj = NULL;
    // clothes repertory slot
    CCARRAY_FOREACH(clothes_layout->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicClothesSlot->setObject(child, child->getName());
    }
    // weapons repertory slot
    CCARRAY_FOREACH(weapons_layout->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicWeaponsSlot->setObject(child, child->getName());
    }
    // pets repertory slot
    CCARRAY_FOREACH(pets_layout->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicPetsSlot->setObject(child, child->getName());
    }
    
    // actor
    UIImageView* wallBG_iv = dynamic_cast<UIImageView*>(up_layout->getChildByName("wall"));
    UIImageView* wal_iv = UIImageView::create();
    wal_iv->setTexture("cocosgui/gui_examples/equip_1/equip/eg/1.png");
    wal_iv->setAnchorPoint(ccp(0.5, 0.5));
    float wal_x = wallBG_iv->getRect().size.width / 2.04;
    float wal_y = wallBG_iv->getRect().size.height / 2.4;
    wal_iv->setPosition(ccp((-wallBG_iv->getRect().size.width / 2) +  wal_x,
                            (-wallBG_iv->getRect().size.height / 2) + wal_y));
    wallBG_iv->addChild(wal_iv);
    
    // original clothes be used slot
    UIImageView* originalClothesSlot_iv = dynamic_cast<UIImageView*>(up_layout->getChildByName("1"));
    UIImageView* originalClothes_iv = UIImageView::create();
    originalClothes_iv->setTexture("cocosgui/gui_examples/equip_1/equip/eg/6.png");
    originalClothesSlot_iv->addChild(originalClothes_iv);
    m_dicBeUsedSlot->setObject(originalClothesSlot_iv, originalClothesSlot_iv->getName());
    
    // other be used slot
    UIImageView* slot_2_iv = dynamic_cast<UIImageView*>(up_layout->getChildByName("2"));
    m_dicBeUsedSlot->setObject(slot_2_iv, slot_2_iv->getName());
    UIImageView* slot_3_iv = dynamic_cast<UIImageView*>(up_layout->getChildByName("3"));
    m_dicBeUsedSlot->setObject(slot_3_iv, slot_3_iv->getName());
    UIImageView* slot_4_iv = dynamic_cast<UIImageView*>(up_layout->getChildByName("4"));
    m_dicBeUsedSlot->setObject(slot_4_iv, slot_4_iv->getName());
    UIImageView* slot_5_iv = dynamic_cast<UIImageView*>(up_layout->getChildByName("5"));
    m_dicBeUsedSlot->setObject(slot_5_iv, slot_5_iv->getName());
    UIImageView* slot_6_iv = dynamic_cast<UIImageView*>(up_layout->getChildByName("6"));
    m_dicBeUsedSlot->setObject(slot_6_iv, slot_6_iv->getName());
    
    // equip create
    create();
    
    // initialize touch able and influence children
    clothes_layout->setTouchEnable(true, true);
    weapons_layout->setTouchEnable(false, false);
    pets_layout->setTouchEnable(false, false);
}

void CocosGUIExamplesEquipScene::create()
{
    createClothes();
    createWeapons();
    createPets();
}

void CocosGUIExamplesEquipScene::createClothes()
{
    Layout* clothes_layout = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(EQUIP_LAYOUT_TAG_CLOTHES));
    
    // clothes
    float parent_w = clothes_layout->getRect().size.width;
    float parent_h = clothes_layout->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    const short columnMax = 3;
    
    // jacket
    const char* jacket_png[columnMax] =
    {
        "cocosgui/gui_examples/equip_1/equip/eg/3.png",
        "cocosgui/gui_examples/equip_1/equip/eg/4.png",
        "cocosgui/gui_examples/equip_1/equip/eg/5.png",
    };
    const char* jacket_name[columnMax] =
    {
        "jacket_taenia",
        "jacket_suit",
        "jacket_shoes",
    };
    // jacket imageview add to clothes slot
    for (int i = 0; i < columnMax; ++i)
    {
        UIImageView* jacket_iv = UIImageView::create();
        jacket_iv->setTexture(jacket_png[i]);
        jacket_iv->setAnchorPoint(ccp(0.5, 0.5));
        jacket_iv->setPosition(ccp(offest_x + i * offest_x * 4, parent_h - offest_y));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(clothes_layout->getChildren()->lastObject());
        if (lastChild)
        {
            jacket_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        jacket_iv->setName(jacket_name[i]);
        jacket_iv->setTouchEnable(true);
        jacket_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesEquipScene::touch));
        jacket_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesEquipScene::move));
        jacket_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::drop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(clothes_layout->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            if (slot->getContainerNode()->boundingBox().containsPoint(jacket_iv->getPosition()))
            {
                jacket_iv->setPosition(CCPointZero);
                slot->addChild(jacket_iv);
                break;
            }
        }
        
        m_dicClothes->setObject(jacket_iv, jacket_iv->getName());
    }
    
    // kimono
    const char* kimono_png[columnMax] =
    {
        "cocosgui/gui_examples/equip_1/equip/eg/8.png",
        "cocosgui/gui_examples/equip_1/equip/eg/10.png",
        "cocosgui/gui_examples/equip_1/equip/eg/9.png",
    };
    const char* kimono_name[columnMax] =
    {
        "kimono_strawhat",
        "kimono_suit",
        "kimono_shoes",
    };
    // kimono imageview add to clothes slot
    for (int i = 0; i < columnMax; ++i)
    {
        UIImageView* kimono_iv = UIImageView::create();
        kimono_iv->setTexture(kimono_png[i]);
        kimono_iv->setPosition(ccp(offest_x + i * offest_x * 4, parent_h - offest_y * 3));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(clothes_layout->getChildren()->lastObject());
        if (lastChild)
        {
            kimono_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        kimono_iv->setName(kimono_name[i]);
        kimono_iv->setTouchEnable(true);
        kimono_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesEquipScene::touch));
        kimono_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesEquipScene::move));
        kimono_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::drop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(clothes_layout->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            if (slot->getContainerNode()->boundingBox().containsPoint(kimono_iv->getPosition()))
            {
                kimono_iv->setPosition(CCPointZero);
                slot->addChild(kimono_iv);
                break;
            }            
        }
        
        m_dicClothes->setObject(kimono_iv, kimono_iv->getName());
    }
}

void CocosGUIExamplesEquipScene::createWeapons()
{
    Layout* weapons_panel = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(EQUIP_LAYOUT_TAG_WEAPONS));
    
    // weapons
    float parent_w = weapons_panel->getRect().size.width;
    float parent_h = weapons_panel->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    // sword
    const short swordAmount = 3;
    const char* sword_png[swordAmount] =
    {
        "cocosgui/gui_examples/equip_1/equip/eg/train.png",
        "cocosgui/gui_examples/equip_1/equip/eg/research.png",
        "cocosgui/gui_examples/equip_1/equip/eg/upgrade.png",
    };
    const char* sword_name[swordAmount] =
    {
        "sword_sword",
        "sword_plus",
        "sword_hammer",
    };
    // sword imageview add to weapons slot
    for (int i = 0; i < swordAmount; ++i)
    {
        UIImageView* sword_iv = UIImageView::create();
        sword_iv->setTexture(sword_png[i]);
        sword_iv->setPosition(ccp(offest_x, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(weapons_panel->getChildren()->lastObject());
        if (lastChild)
        {
            sword_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        sword_iv->setName(sword_name[i]);
        sword_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesEquipScene::touch));
        sword_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesEquipScene::move));
        sword_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::drop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weapons_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            if (slot->getContainerNode()->boundingBox().containsPoint(sword_iv->getPosition()))
            {
                sword_iv->setPosition(CCPointZero);
                slot->addChild(sword_iv);
                break;
            }
        }
        
        m_dicWeapons->setObject(sword_iv, sword_iv->getName());
    }
    
    // arrow
    const short arrowAmount = 3;
    const char* arrow_png[arrowAmount] =
    {
        "cocosgui/gui_examples/equip_1/equip/eg/shop_shield_1.png",
        "cocosgui/gui_examples/equip_1/equip/eg/shop_shield_2.png",
        "cocosgui/gui_examples/equip_1/equip/eg/shop_shield_3.png",
    };
    const char* arrow_name[arrowAmount] =
    {
        "arraw_normal",
        "arraw_hard",
        "arraw_devil",
    };
    // arrow imageview add to weapons slot
    for (int i = 0; i < arrowAmount; ++i)
    {
        UIImageView* arrow_iv = UIImageView::create();
        arrow_iv->setTexture(arrow_png[i]);
        arrow_iv->setPosition(ccp(offest_x * 5, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(weapons_panel->getChildren()->lastObject());
        if (lastChild)
        {
            arrow_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        arrow_iv->setName(arrow_name[i]);
        arrow_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesEquipScene::touch));
        arrow_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesEquipScene::move));
        arrow_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::drop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weapons_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            if (slot->getContainerNode()->boundingBox().containsPoint(arrow_iv->getPosition()))
            {
                arrow_iv->setPosition(CCPointZero);
                slot->addChild(arrow_iv);
                break;
            }
        }
        
        m_dicWeapons->setObject(arrow_iv, arrow_iv->getName());
    }
    
    // bomb
    const short bombAmount = 1;
    const char* bomb_png[bombAmount] =
    {
        "cocosgui/gui_examples/equip_1/equip/eg/sell.png",
    };
    const char* bomb_name[bombAmount] =
    {
        "bomb_normal",
    };
    // bomo imageview add to weapons slot
    for (int i = 0; i < bombAmount; ++i)
    {
        UIImageView* bomb_iv = UIImageView::create();
        bomb_iv->setTexture(bomb_png[i]);
        bomb_iv->setPosition(ccp(offest_x * 9, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(weapons_panel->getChildren()->lastObject());
        if (lastChild)
        {
            bomb_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        bomb_iv->setName(bomb_name[i]);
        bomb_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesEquipScene::touch));
        bomb_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesEquipScene::move));
        bomb_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::drop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weapons_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            if (slot->getContainerNode()->boundingBox().containsPoint(bomb_iv->getPosition()))
            {
                bomb_iv->setPosition(CCPointZero);
                slot->addChild(bomb_iv);
                break;
            }
        }
        
        m_dicWeapons->setObject(bomb_iv, bomb_iv->getName());
    }
}

void CocosGUIExamplesEquipScene::createPets()
{
    Layout* pets_layout = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(EQUIP_LAYOUT_TAG_PETS));
    
    // pets
    float parent_w = pets_layout->getRect().size.width;
    float parent_h = pets_layout->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    // dragon
    const short dragonAmount = 1;
    const char* dragon_png[dragonAmount] =
    {
        "cocosgui/gui_examples/equip_1/equip/eg/7.png",
    };
    const char* dragon_name[dragonAmount] =
    {
        "pet_dragon",
    };
    // dragon imageview add to pets slot
    for (int i = 0; i < dragonAmount; ++i)
    {
        UIImageView* dragon_iv = UIImageView::create();
        dragon_iv->setTexture(dragon_png[i]);
        dragon_iv->setPosition(ccp(offest_x, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(pets_layout->getChildren()->lastObject());
        if (lastChild)
        {
            dragon_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        dragon_iv->setName(dragon_name[i]);
        dragon_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesEquipScene::touch));
        dragon_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesEquipScene::move));
        dragon_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::drop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(pets_layout->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);            
            if (slot->getContainerNode()->boundingBox().containsPoint(dragon_iv->getPosition()))
            {
                dragon_iv->setPosition(CCPointZero);
                slot->addChild(dragon_iv);
                break;
            }
        }
        
        m_dicPets->setObject(dragon_iv, dragon_iv->getName());
    }
    
    // crab
    const short crabAmount = 1;
    const char* crab_png[crabAmount] =
    {
        "cocosgui/gui_examples/equip_1/equip/eg/crab.png",
    };
    const char* crab_name[crabAmount] =
    {
        "pet_crab",
    };
    // crab imageview add to pets slot
    for (int i = 0; i < crabAmount; ++i)
    {
        UIImageView* crab_iv = UIImageView::create();
        crab_iv->setTexture(crab_png[i]);
        crab_iv->setPosition(ccp(offest_x * 5, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(pets_layout->getChildren()->lastObject());
        if (lastChild)
        {
            crab_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        crab_iv->setName(crab_name[i]);
        crab_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesEquipScene::touch));
        crab_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesEquipScene::move));
        crab_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesEquipScene::drop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(pets_layout->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            if (slot->getContainerNode()->boundingBox().containsPoint(crab_iv->getPosition()))
            {
                crab_iv->setPosition(CCPointZero);
                slot->addChild(crab_iv);
                break;
            }                        
        }
        
        m_dicPets->setObject(crab_iv, crab_iv->getName());
    }
    
}

void CocosGUIExamplesEquipScene::switchBtnCallBack(CCObject *pSender)
{
    // switch button
    UIButton* button = dynamic_cast<UIButton*>(pSender);
    
    // equip root
    Layout* root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(EQUIP_LAYOUT_TAG_ROOT));
    
    // equip repertory
    Layout* clothes_layout = dynamic_cast<Layout*>(root->getChildByTag(EQUIP_LAYOUT_TAG_CLOTHES));
    Layout* weapons_layout = dynamic_cast<Layout*>(root->getChildByTag(EQUIP_LAYOUT_TAG_WEAPONS));
    Layout* pets_layout = dynamic_cast<Layout*>(root->getChildByTag(EQUIP_LAYOUT_TAG_PETS));
    
    Layout* up_layout = dynamic_cast<Layout*>(root->getChildByTag(EQUIP_LAYOUT_TAG_UP));
    UITextButton* clothes_btn = dynamic_cast<UITextButton*>(up_layout->getChildByTag(EQUIP_SWITCH_LAYOUT_BUTTON_TAG_CLOTHES));
    UITextButton* weapons_btn = dynamic_cast<UITextButton*>(up_layout->getChildByTag(EQUIP_SWITCH_LAYOUT_BUTTON_TAG_WEAPONS));
    UITextButton* pets_btn = dynamic_cast<UITextButton*>(up_layout->getChildByTag(EQUIP_SWITCH_LAYOUT_BUTTON_TAG_PETS));
    
    clothes_btn->active();
    weapons_btn->active();
    pets_btn->active();
    
    // switch slot
    switch (button->getWidgetTag())
    {
        case EQUIP_SWITCH_LAYOUT_BUTTON_TAG_CLOTHES:
        {
            m_eEquipType = EQUIP_TYPE_CLOTHES;
            
            clothes_btn->disable();
            
            clothes_layout->setWidgetZOrder(container_1_Zorder);
            weapons_layout->setWidgetZOrder(container_2_Zorder);
            pets_layout->setWidgetZOrder(container_3_Zorder);
            
            clothes_layout->setPosition(container_1_Position);
            weapons_layout->setPosition(container_2_Position);
            pets_layout->setPosition(container_3_Position);
            
            // equip slot touch able
            clothes_layout->setTouchEnable(true, true);
            weapons_layout->setTouchEnable(false, true);
            pets_layout->setTouchEnable(false, true);
        }
            break;
            
        case EQUIP_SWITCH_LAYOUT_BUTTON_TAG_WEAPONS:
        {
            m_eEquipType = EQUIP_TYPE_WEAPONS;
            
            weapons_btn->disable();
            
            clothes_layout->setWidgetZOrder(container_3_Zorder);
            weapons_layout->setWidgetZOrder(container_1_Zorder);
            pets_layout->setWidgetZOrder(container_2_Zorder);
            
            weapons_layout->setPosition(container_1_Position);
            pets_layout->setPosition(container_2_Position);
            clothes_layout->setPosition(container_3_Position);
            
            // equip slot touch able
            weapons_layout->setTouchEnable(true, true);
            clothes_layout->setTouchEnable(false, true);
            pets_layout->setTouchEnable(false, true);
        }
            break;
            
        case EQUIP_SWITCH_LAYOUT_BUTTON_TAG_PETS:
        {
            m_eEquipType = EQUIP_TYPE_PETS;
            
            pets_btn->disable();
            
            pets_layout->setWidgetZOrder(container_1_Zorder);
            clothes_layout->setWidgetZOrder(container_2_Zorder);
            weapons_layout->setWidgetZOrder(container_3_Zorder);
            
            pets_layout->setPosition(container_1_Position);
            clothes_layout->setPosition(container_2_Position);
            weapons_layout->setPosition(container_3_Position);
            
            // equip slot touch able
            pets_layout->setTouchEnable(true, true);
            clothes_layout->setTouchEnable(false, true);
            weapons_layout->setTouchEnable(false, true);
        }
            break;
            
        default:
            break;
    }
}

void CocosGUIExamplesEquipScene::touch(CCObject *pSender)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    CCPoint worldSpace = widget->getContainerNode()->convertToWorldSpace(CCPointZero);
    
    widgetLastWorldSpace = worldSpace;
    widgetLastNodeSpace = widget->getPosition();
    
    lastWidgetParent = widget->getWidgetParent();
    widget->removeFromParentAndCleanup(false);
    
    m_pUILayer->addWidget(widget);
    
    widget->setPosition(widget->getTouchStartPos());
    movePoint = widget->getTouchStartPos();
}

void CocosGUIExamplesEquipScene::move(CCObject* pSender)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    
    lastPoint = movePoint;
    movePoint = widget->getTouchMovePos();
    CCPoint offset = ccpSub(movePoint, lastPoint);
    CCPoint toPoint = ccpAdd(widget->getPosition(), offset);
    widget->setPosition(toPoint);
}

void CocosGUIExamplesEquipScene::drop(CCObject *pSender)
{
    bool isInUsedSlot = false;
    bool isInEquipSlot = false;
    
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    
    CCDictElement* element = NULL;
    
    // drop into used slot
    CCDICT_FOREACH(m_dicBeUsedSlot, element)
    {
        UIWidget* usedSlot_wigt = dynamic_cast<UIWidget*>(element->getObject());
        if (usedSlot_wigt->getChildren()->count() > 0)
        {
            continue;
        }
        
        if (usedSlot_wigt->getRect().containsPoint(widget->getPosition()))
        {
            widget->removeFromParentAndCleanup(false);
            widget->setPosition(CCPointZero);
            usedSlot_wigt->addChild(widget);
            
            isInUsedSlot = true;
            break;
        }
    }
    
    // drop into equip slot
    CCDictionary* equipSlot_dic = NULL;
    CCDictionary* equip_dic = NULL;
    switch (m_eEquipType)
    {
        case EQUIP_TYPE_CLOTHES:
            equipSlot_dic = m_dicClothesSlot;
            equip_dic = m_dicClothes;
            break;
            
        case EQUIP_TYPE_WEAPONS:
            equipSlot_dic = m_dicWeaponsSlot;
            equip_dic = m_dicWeapons;
            break;
            
        case EQUIP_TYPE_PETS:
            equipSlot_dic = m_dicPetsSlot;
            equip_dic = m_dicPets;
            break;
            
        default:
            break;
    }
    
    CCDICT_FOREACH(equipSlot_dic, element)
    {
        UIWidget* equipSlot = dynamic_cast<UIWidget*>(element->getObject());
        if (equipSlot->getChildren()->count() > 0)
        {
            continue;
        }
        
        CCRect slot_rect = equipSlot->getRect();
        if (slot_rect.containsPoint(widget->getPosition()))
        {
            CCObject* obj = equip_dic->objectForKey(widget->getName());
            if (obj)
            {
                widget->removeFromParentAndCleanup(false);
                widget->setPosition(CCPointZero);
                equipSlot->addChild(widget);
                
                isInEquipSlot = true;
            }
            break;
        }
    }
    
    // back to last position if cannot drop other slot
    if (!isInUsedSlot && !isInEquipSlot)
    {
        CCPoint point = widgetLastWorldSpace;
        CCMoveTo* moveTo = CCMoveTo::create(1.0f, point);
        CCEaseExponentialOut* ease = CCEaseExponentialOut::create(moveTo);
        CCCallFuncO* calllFunc0 = CCCallFuncO::create(this, callfuncO_selector(CocosGUIExamplesEquipScene::backOver), widget);
        CCSequence* seq = CCSequence::create(ease, calllFunc0, NULL);
        widget->runAction(seq);
        
        // widget in equip slot
        CCDICT_FOREACH(equip_dic, element)
        {
            UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
            widget->setTouchEnable(false, true);
        }
        
        // equip up layout
        Layout* equipe_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(EQUIP_LAYOUT_TAG_ROOT));
        Layout* up_layout = dynamic_cast<Layout*>(equipe_root->getChildByName("up_panel"));
        up_layout->setTouchEnable(false, true);
    }
}

void CocosGUIExamplesEquipScene::backOver(CCObject *pObject)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pObject);
    
    widget->removeFromParentAndCleanup(false);
    lastWidgetParent->addChild(widget);
    widget->setPosition(widgetLastNodeSpace);
    
    CCDictElement* element = NULL;
    
    // equip
    CCDictionary* equip_dic = NULL;
    switch (m_eEquipType)
    {
        case EQUIP_TYPE_CLOTHES:
            equip_dic = m_dicClothes;
            break;
            
        case EQUIP_TYPE_WEAPONS:
            equip_dic = m_dicWeapons;
            break;
            
        case EQUIP_TYPE_PETS:
            equip_dic = m_dicPets;
            break;
            
        default:
            break;
    }
    CCDICT_FOREACH(equip_dic, element)
    {
        UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
        widget->setTouchEnable(true, true);
    }
    
    // equip up layout
    Layout* equip_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(EQUIP_LAYOUT_TAG_ROOT));
    Layout* up_layout = dynamic_cast<Layout*>(equip_root->getChildByName("up_panel"));
    up_layout->setTouchEnable(true, true);
}

void CocosGUIExamplesEquipScene::close(CCObject* pObject)
{
    
    // equip
    Layout* equip_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(EQUIP_LAYOUT_TAG_ROOT));
    equip_root->setVisible(false);
}