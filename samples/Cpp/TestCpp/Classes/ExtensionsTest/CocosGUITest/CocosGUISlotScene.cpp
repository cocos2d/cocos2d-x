
#include "CocosGUISlotScene.h"
#include "CocosGUIScene.h"


CocosGUISlotScene::CocosGUISlotScene(bool bPortrait)
{
	TestScene::init();
    
    CCLayerColor* lc = CCLayerColor::create(ccc4(0, 0, 0, 255));
    addChild(lc);
    
    /*
	CCSprite *bg = CCSprite::create("armature/bg.jpg");
	bg->setPosition(VisibleRect::center());
    
	float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
	float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;
    
	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);
    
	addChild(bg);
     */
}

void CocosGUISlotScene::onExit()
{
    TestScene::onExit();
    
    //CC_SAFE_RELEASE(m_dicBeUsedSlot);
    //CC_SAFE_RELEASE(m_dicEquipClothesSlot);
    //CC_SAFE_RELEASE(m_dicEquipWeaponsSlot);
    //CC_SAFE_RELEASE(m_dicEquipPetsSlot);
    //CC_SAFE_RELEASE(m_dicEquipClothes);
    //CC_SAFE_RELEASE(m_dicEquipWeapons);
    //CC_SAFE_RELEASE(m_dicEquipPets);
}

void CocosGUISlotScene::runThisTest()
{
    
	CCDirector::sharedDirector()->replaceScene(this);
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
    
    CCObject* obj = NULL;
    
    // init properties
    m_eEquipType = EQUIP_TYPE_CLOTHES;
    
    m_dicBeUsedSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicBeUsedSlot);
    m_dicEquipClothesSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicEquipClothesSlot);
    m_dicEquipWeaponsSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicEquipWeaponsSlot);
    m_dicEquipPetsSlot = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicEquipPetsSlot);
    
    m_dicEquipClothes = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicEquipClothes);
    m_dicEquipWeapons = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicEquipWeapons);
    m_dicEquipPets = CCDictionary::create();
    CC_SAFE_RETAIN(m_dicEquipPets);
    
    container_1_Zorder = 0;
    container_2_Zorder = 0;
    container_3_Zorder = 0;
    container_1_Position = CCPointZero;
    container_2_Position = CCPointZero;
    container_3_Position = CCPointZero;
    movePoint = CCPointZero;
    lastPoint = CCPointZero;
    
    widgetLastLocal = CCPointZero;
    widgetLastNodePosition = CCPointZero;
    lastWidgetParent = NULL;
    //
    
    // gui
    
    UIWidget* widget = CCUIHELPER->createWidgetFromJsonFile("slot/20_2.json");
    ul->addWidget(widget);
    
    // root in json
    UIPanel* root = dynamic_cast<UIPanel*>(ul->getWidgetByName("root"));
    root->setWidgetTag(PANEL_TAG_20_2);
    
    // upPanel
    UIPanel* upPanel = dynamic_cast<UIPanel*>(root->getChildByName("UP"));
    upPanel->setWidgetTag(PANEL_TAG_UP);
    
    // switch button
    UITextButton* clothesBtn = dynamic_cast<UITextButton*>(upPanel->getChildByName("I_Button"));
    clothesBtn->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::switchBtnCallBack));
    clothesBtn->setWidgetTag(SWITCH_PANEL_BTN_TAG_CLOTHES);
    clothesBtn->disable();
    
    UITextButton* weaponsBtn = dynamic_cast<UITextButton*>(upPanel->getChildByName("II_Button"));
    weaponsBtn->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::switchBtnCallBack));
    weaponsBtn->setWidgetTag(SWITCH_PANEL_BTN_TAG_WEAPONS);
    
    UITextButton* petsBtn = dynamic_cast<UITextButton*>(upPanel->getChildByName("III_Button"));
    petsBtn->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::switchBtnCallBack));
    petsBtn->setWidgetTag(SWITCH_PANEL_BTN_TAG_PETS);
    
    // equip panel
    UIPanel* clothesPanel = dynamic_cast<UIPanel*>(root->getChildByName("IX"));
    clothesPanel->setWidgetTag(PANEL_TAG_CLOTHES);
    
    UIPanel* weaponsPanel = dynamic_cast<UIPanel*>(root->getChildByName("IIX"));
    weaponsPanel->setWidgetTag(PANEL_TAG_WEAPONS);
    
    UIPanel* petsPanel = dynamic_cast<UIPanel*>(root->getChildByName("IIIX"));
    petsPanel->setWidgetTag(PANEL_TAG_PETS);
    
    container_1_Zorder = clothesPanel->getWidgetZOrder();
    container_2_Zorder = weaponsPanel->getWidgetZOrder();
    container_3_Zorder = petsPanel->getWidgetZOrder();
    
    container_1_Position = clothesPanel->getPosition();
    container_2_Position = weaponsPanel->getPosition();
    container_3_Position = petsPanel->getPosition();
    
    // clothes equip slot
    CCARRAY_FOREACH(clothesPanel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicEquipClothesSlot->setObject(child, child->getName());
    }
    // weapons equip slot
    CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicEquipWeaponsSlot->setObject(child, child->getName());
    }
    // pets equip slot
    CCARRAY_FOREACH(petsPanel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicEquipPetsSlot->setObject(child, child->getName());
    }
    
    // actor
    UIImageView* walBG = dynamic_cast<UIImageView*>(upPanel->getChildByName("WAL"));
    UIImageView* walImageView = UIImageView::create();
    walImageView->setTexture("slot/eg/1.png");
    walImageView->setAnchorPoint(ccp(0.5, 0.5));
    float wal_x = walBG->getRect().size.width / 2.04;
    float wal_y = walBG->getRect().size.height / 2.4;
    walImageView->setPosition(ccp((-walBG->getRect().size.width / 2) +  wal_x,
                                  (-walBG->getRect().size.height / 2) + wal_y));
    walBG->addChild(walImageView);
    
    // original clothes be used slot
    UIImageView* originalClothesSlot = dynamic_cast<UIImageView*>(upPanel->getChildByName("1"));
    originalClothesSlot->setWidgetTag(IMAGEVIEW_TAG_SLOT_ORIGINAL_CLOTHES);
    UIImageView* originalClothes = UIImageView::create();
    originalClothes->setTexture("slot/eg/6.png");    
    originalClothesSlot->addChild(originalClothes);
    m_dicBeUsedSlot->setObject(originalClothesSlot, originalClothesSlot->getName());
    
    // other be used slot
    UIImageView* iv_2 = dynamic_cast<UIImageView*>(upPanel->getChildByName("2"));
    m_dicBeUsedSlot->setObject(iv_2, iv_2->getName());
    UIImageView* iv_3 = dynamic_cast<UIImageView*>(upPanel->getChildByName("3"));
    m_dicBeUsedSlot->setObject(iv_3, iv_3->getName());
    UIImageView* iv_4 = dynamic_cast<UIImageView*>(upPanel->getChildByName("4"));
    m_dicBeUsedSlot->setObject(iv_4, iv_4->getName());
    UIImageView* iv_5 = dynamic_cast<UIImageView*>(upPanel->getChildByName("5"));
    m_dicBeUsedSlot->setObject(iv_5, iv_5->getName());
    UIImageView* iv_6 = dynamic_cast<UIImageView*>(upPanel->getChildByName("6"));
    m_dicBeUsedSlot->setObject(iv_6, iv_6->getName());
    
    // equip
    createEquip();
    
    // initialize touch able
    clothesPanel->setBeTouchEnable(true);
    CCARRAY_FOREACH(clothesPanel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        child->setBeTouchEnable(true);
    }
    weaponsPanel->setBeTouchEnable(false);
    CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        child->setBeTouchEnable(false);
    }
    petsPanel->setBeTouchEnable(true);
    CCARRAY_FOREACH(petsPanel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        child->setBeTouchEnable(false);
    }
    //
    
    // exit
    UIButton* exit = UIButton::create();
    exit->setTextures("cocosgui/CloseNormal.png", "cocosgui/CloseSelected.png", "");
    exit->setPosition(ccp(430, 60));
    exit->setBeTouchEnable(true);
    exit->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::toCocosGUITestScene));
    ul->addWidget(exit);
}

void CocosGUISlotScene::MainMenuCallback(CCObject* pSender)
{
	TestScene::MainMenuCallback(pSender);
}

void CocosGUISlotScene::toCocosGUITestScene(CCObject *pSender)
{
    CocosGUITestScene *pScene = new CocosGUITestScene();
    if (pScene)
    {
        ul->dispose();
        
        pScene->runThisTest();
        pScene->release();
    }
}

void CocosGUISlotScene::switchBtnCallBack(CCObject *pSender)
{
    // switch button
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    
    UIPanel* root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(PANEL_TAG_20_2));
    
    UIPanel* clothesPanel = dynamic_cast<UIPanel*>(root->getChildByTag(PANEL_TAG_CLOTHES));
    UIPanel* weaponsPanel = dynamic_cast<UIPanel*>(root->getChildByTag(PANEL_TAG_WEAPONS));
    UIPanel* petsPanel = dynamic_cast<UIPanel*>(root->getChildByTag(PANEL_TAG_PETS));
    
    UIPanel* upPanel = dynamic_cast<UIPanel*>(root->getChildByTag(PANEL_TAG_UP));
    UITextButton* clothesBtn = dynamic_cast<UITextButton*>(upPanel->getChildByTag(SWITCH_PANEL_BTN_TAG_CLOTHES));
    UITextButton* weaponsBtn = dynamic_cast<UITextButton*>(upPanel->getChildByTag(SWITCH_PANEL_BTN_TAG_WEAPONS));
    UITextButton* petsBtn = dynamic_cast<UITextButton*>(upPanel->getChildByTag(SWITCH_PANEL_BTN_TAG_PETS));
    
    clothesBtn->active();
    weaponsBtn->active();
    petsBtn->active();
    
    CCObject* obj = NULL;
    CCDictElement* element = NULL;
    
    switch (widget->getWidgetTag())
    {
        case SWITCH_PANEL_BTN_TAG_CLOTHES:
        {
            m_eEquipType = EQUIP_TYPE_CLOTHES;
            
            clothesBtn->disable();
            
            clothesPanel->setWidgetZOrder(container_1_Zorder);
            weaponsPanel->setWidgetZOrder(container_2_Zorder);
            petsPanel->setWidgetZOrder(container_3_Zorder);
            
            clothesPanel->setPosition(container_1_Position);
            weaponsPanel->setPosition(container_2_Position);
            petsPanel->setPosition(container_3_Position);
            
            // equip slot touch able
            clothesPanel->setBeTouchEnable(true);
            CCARRAY_FOREACH(clothesPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(true);
            }
            weaponsPanel->setBeTouchEnable(false);
            CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(false);
            }
            petsPanel->setBeTouchEnable(true);
            CCARRAY_FOREACH(petsPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(false);
            }
            
            // equip touch able
            CCDICT_FOREACH(m_dicEquipClothes, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(true);
            }
            CCDICT_FOREACH(m_dicEquipWeapons, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(false);
            }
            CCDICT_FOREACH(m_dicEquipPets, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(false);
            }
        }
            break;
            
        case SWITCH_PANEL_BTN_TAG_WEAPONS:
        {
            m_eEquipType = EQUIP_TYPE_WEAPONS;
            
            weaponsBtn->disable();
            
            clothesPanel->setWidgetZOrder(container_3_Zorder);
            weaponsPanel->setWidgetZOrder(container_1_Zorder);
            petsPanel->setWidgetZOrder(container_2_Zorder);
            
            weaponsPanel->setPosition(container_1_Position);
            petsPanel->setPosition(container_2_Position);
            clothesPanel->setPosition(container_3_Position);
            
            // equip slot touch able
            weaponsPanel->setBeTouchEnable(true);
            CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(true);
            }
            clothesPanel->setBeTouchEnable(false);
            CCARRAY_FOREACH(clothesPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(false);
            }
            petsPanel->setBeTouchEnable(false);
            CCARRAY_FOREACH(petsPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(false);
            }
            
            // equip touch able
            CCDICT_FOREACH(m_dicEquipClothes, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(false);
            }
                CCDICT_FOREACH(m_dicEquipWeapons, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(true);
            }
                CCDICT_FOREACH(m_dicEquipPets, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(false);
            }
        }
            break;
            
        case SWITCH_PANEL_BTN_TAG_PETS:
        {
            m_eEquipType = EQUIP_TYPE_PETS;
            
            petsBtn->disable();
            
            petsPanel->setWidgetZOrder(container_1_Zorder);
            clothesPanel->setWidgetZOrder(container_2_Zorder);
            weaponsPanel->setWidgetZOrder(container_3_Zorder);
            
            petsPanel->setPosition(container_1_Position);
            clothesPanel->setPosition(container_2_Position);
            weaponsPanel->setPosition(container_3_Position);
            
            // equip slot touch able
            petsPanel->setBeTouchEnable(true);
            CCARRAY_FOREACH(petsPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(true);
            }
            clothesPanel->setBeTouchEnable(false);
            CCARRAY_FOREACH(clothesPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(false);
            }
            weaponsPanel->setBeTouchEnable(false);
            CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(obj);
                child->setBeTouchEnable(false);
            }
            
            // equip touch able
            CCDICT_FOREACH(m_dicEquipClothes, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(false);
            }
            CCDICT_FOREACH(m_dicEquipWeapons, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(false);
            }
            CCDICT_FOREACH(m_dicEquipPets, element)
            {
                UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
                widget->setBeTouchEnable(true);
            }
        }
            break;
            
        default:
            break;
    }
}

void CocosGUISlotScene::createEquip()
{
    createClothes();
    createWeapons();
    createPets();
}

void CocosGUISlotScene::createClothes()
{
    UIPanel* clothesPanel = dynamic_cast<UIPanel*>(ul->getWidgetByTag(PANEL_TAG_CLOTHES));
    
    // clothes
    float parent_w = clothesPanel->getRect().size.width;
    float parent_h = clothesPanel->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    CCLOG("offest_x = %f", offest_x);
    CCLOG("offest_y = %f", offest_y);
    
    const short clothes_column = 3;
    // jacket
    const char* jacket_png[clothes_column] =
    {
        "slot/eg/3.png",
        "slot/eg/4.png",
        "slot/eg/5.png",
    };
    const char* jacket_name[clothes_column] =
    {
        "jacket_taenia",
        "jacket_suit",
        "jacket_shoes",
    };
    for (int i = 0; i < clothes_column; ++i)
    {
        UIImageView* jacketIv = UIImageView::create();
        jacketIv->setTexture(jacket_png[i]);
        jacketIv->setAnchorPoint(ccp(0.5, 0.5));
        jacketIv->setPosition(ccp(offest_x + i * offest_x * 4, parent_h - offest_y));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(clothesPanel->getChildren()->lastObject());
        if (lastChild)
        {
            jacketIv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        jacketIv->setName(jacket_name[i]);
        jacketIv->setBeTouchEnable(true);
        jacketIv->addPushDownEvent(this, coco_pushselector(CocosGUISlotScene::touchEquip));
        jacketIv->addMoveEvent(this, coco_moveselector(CocosGUISlotScene::moveEquip));
        jacketIv->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::dropEquip));        
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(clothesPanel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(jacketIv->getPosition()))
            {
                jacketIv->setPosition(CCPointZero);
                slot->addChild(jacketIv);
                break;
            }
        }
        
        jacketIv->setColor(ccc3(255, 255, 255));
        
        m_dicEquipClothes->setObject(jacketIv, jacketIv->getName());
    }
    // kimono
    const char* kimono_png[clothes_column] =
    {
        "slot/eg/8.png",
        "slot/eg/10.png",
        "slot/eg/9.png",
    };
    const char* kimono_name[clothes_column] =
    {
        "kimono_strawhat",
        "kimono_suit",
        "kimono_shoes",
    };
    for (int i = 0; i < clothes_column; ++i)
    {
        UIImageView* kimonoIv = UIImageView::create();
        kimonoIv->setTexture(kimono_png[i]);
        kimonoIv->setPosition(ccp(offest_x + i * offest_x * 4, parent_h - offest_y * 3));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(clothesPanel->getChildren()->lastObject());
        if (lastChild)
        {
            kimonoIv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        kimonoIv->setName(kimono_name[i]);
        kimonoIv->setBeTouchEnable(true);
        kimonoIv->addPushDownEvent(this, coco_pushselector(CocosGUISlotScene::touchEquip));
        kimonoIv->addMoveEvent(this, coco_moveselector(CocosGUISlotScene::moveEquip));
        kimonoIv->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::dropEquip));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(clothesPanel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(kimonoIv->getPosition()))
            {
                kimonoIv->setPosition(CCPointZero);
                slot->addChild(kimonoIv);
                break;
            }
        }
        
        kimonoIv->setColor(ccc3(255, 255, 255));
        
        m_dicEquipClothes->setObject(kimonoIv, kimonoIv->getName());
    }
}

void CocosGUISlotScene::createWeapons()
{
    UIPanel* weaponsPanel = dynamic_cast<UIPanel*>(ul->getWidgetByTag(PANEL_TAG_WEAPONS));
    
    // weapons
    float parent_w = weaponsPanel->getRect().size.width;
    float parent_h = weaponsPanel->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    // sword
    const short sword_amount = 3;
    const char* sword_png[sword_amount] =
    {
        "slot/eg/train.png",
        "slot/eg/research.png",
        "slot/eg/upgrade.png",
    };
    const char* sword_name[sword_amount] =
    {
        "sword_sword",
        "sword_plus",
        "sword_hammer",
    };
    for (int i = 0; i < sword_amount; ++i)
    {
        UIImageView* swordIv = UIImageView::create();
        swordIv->setTexture(sword_png[i]);
        swordIv->setPosition(ccp(offest_x, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(weaponsPanel->getChildren()->lastObject());
        if (lastChild)
        {
            swordIv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        swordIv->setName(sword_name[i]);        
        swordIv->addPushDownEvent(this, coco_pushselector(CocosGUISlotScene::touchEquip));
        swordIv->addMoveEvent(this, coco_moveselector(CocosGUISlotScene::moveEquip));
        swordIv->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::dropEquip));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(swordIv->getPosition()))
            {
                swordIv->setPosition(CCPointZero);
                slot->addChild(swordIv);
                break;
            }
        }
        
        swordIv->setColor(ccc3(255, 255, 255));
        
        m_dicEquipWeapons->setObject(swordIv, swordIv->getName());
    }
    
    // arrow
    const short arrow_amount = 3;
    const char* arrow_png[arrow_amount] =
    {
        "slot/eg/shop_shield_1.png",
        "slot/eg/shop_shield_2.png",
        "slot/eg/shop_shield_3.png",
    };
    const char* arrow_name[arrow_amount] =
    {
        "arraw_normal",
        "arraw_hard",
        "arraw_devil",
    };
    for (int i = 0; i < arrow_amount; ++i)
    {
        UIImageView* arrowIv = UIImageView::create();
        arrowIv->setTexture(arrow_png[i]);
        arrowIv->setPosition(ccp(offest_x * 5, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(weaponsPanel->getChildren()->lastObject());
        if (lastChild)
        {
            arrowIv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        arrowIv->setName(arrow_name[i]);
        arrowIv->addPushDownEvent(this, coco_pushselector(CocosGUISlotScene::touchEquip));
        arrowIv->addMoveEvent(this, coco_moveselector(CocosGUISlotScene::moveEquip));
        arrowIv->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::dropEquip));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(arrowIv->getPosition()))
            {
                arrowIv->setPosition(CCPointZero);
                slot->addChild(arrowIv);
                break;
            }
        }
        
        arrowIv->setColor(ccc3(255, 255, 255));
        
        m_dicEquipWeapons->setObject(arrowIv, arrowIv->getName());
    }
    
    // bomb
    const short bomb_amount = 1;
    const char* bomb_png[bomb_amount] =
    {
        "slot/eg/sell.png",
    };
    const char* bomb_name[bomb_amount] =
    {
        "bomb_normal",
    };
    for (int i = 0; i < bomb_amount; ++i)
    {
        UIImageView* bombIv = UIImageView::create();
        bombIv->setTexture(bomb_png[i]);
        bombIv->setPosition(ccp(offest_x * 9, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(weaponsPanel->getChildren()->lastObject());
        if (lastChild)
        {
            bombIv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        bombIv->setName(bomb_name[i]);
        bombIv->addPushDownEvent(this, coco_pushselector(CocosGUISlotScene::touchEquip));
        bombIv->addMoveEvent(this, coco_moveselector(CocosGUISlotScene::moveEquip));
        bombIv->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::dropEquip));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weaponsPanel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(bombIv->getPosition()))
            {
                bombIv->setPosition(CCPointZero);
                slot->addChild(bombIv);
                break;
            }
        }
        
        bombIv->setColor(ccc3(255, 255, 255));
        
        m_dicEquipWeapons->setObject(bombIv, bombIv->getName());
    }
}

void CocosGUISlotScene::createPets()
{
    UIPanel* petsPanel = dynamic_cast<UIPanel*>(ul->getWidgetByTag(PANEL_TAG_PETS));
    
    // pets
    float parent_w = petsPanel->getRect().size.width;
    float parent_h = petsPanel->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    // dragon
    const short dragon_amount = 1;
    const char* dragon_png[dragon_amount] =
    {
        "slot/eg/7.png",
    };
    const char* dragon_name[dragon_amount] =
    {
        "pet_dragon",
    };
    for (int i = 0; i < dragon_amount; ++i)
    {
        UIImageView* dragonIv = UIImageView::create();
        dragonIv->setTexture(dragon_png[i]);
        dragonIv->setPosition(ccp(offest_x, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(petsPanel->getChildren()->lastObject());
        if (lastChild)
        {
            dragonIv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        dragonIv->setName(dragon_name[i]);
        dragonIv->addPushDownEvent(this, coco_pushselector(CocosGUISlotScene::touchEquip));
        dragonIv->addMoveEvent(this, coco_moveselector(CocosGUISlotScene::moveEquip));
        dragonIv->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::dropEquip));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(petsPanel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(dragonIv->getPosition()))
            {
                dragonIv->setPosition(CCPointZero);
                slot->addChild(dragonIv);
                break;
            }
        }
        
        dragonIv->setColor(ccc3(255, 255, 255));
        
        m_dicEquipPets->setObject(dragonIv, dragonIv->getName());
    }
    
    // crab
    const short crab_amount = 1;
    const char* crab_png[crab_amount] =
    {
        "slot/eg/crab.png",
    };
    const char* crab_name[crab_amount] =
    {
        "pet_crab",
    };
    for (int i = 0; i < crab_amount; ++i)
    {
        UIImageView* crabIv = UIImageView::create();
        crabIv->setTexture(crab_png[i]);
        crabIv->setPosition(ccp(offest_x * 5, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(petsPanel->getChildren()->lastObject());
        if (lastChild)
        {
            crabIv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        crabIv->setName(crab_name[i]);
        crabIv->addPushDownEvent(this, coco_pushselector(CocosGUISlotScene::touchEquip));
        crabIv->addMoveEvent(this, coco_moveselector(CocosGUISlotScene::moveEquip));
        crabIv->addReleaseEvent(this, coco_releaseselector(CocosGUISlotScene::dropEquip));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(petsPanel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(crabIv->getPosition()))
            {
                crabIv->setPosition(CCPointZero);
                slot->addChild(crabIv);
                break;
            }
        }
        
        crabIv->setColor(ccc3(255, 255, 255));
        
        m_dicEquipPets->setObject(crabIv, crabIv->getName());
    }
    
}

void CocosGUISlotScene::touchEquip(CCObject *pSender)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    CCPoint local = widget->getContainerNode()->convertToWorldSpace(CCPointZero);

    widgetLastLocal = local;
    widgetLastNodePosition = widget->getPosition();
    lastWidgetParent = widget->getWidgetParent();
    
    widget->removeFromParentAndCleanup(false);
    ul->addWidget(widget);
    widget->setPosition(widget->getTouchStartPos());
    
    movePoint = widget->getTouchStartPos();
}

void CocosGUISlotScene::moveEquip(CCObject* pSender)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    
    lastPoint = movePoint;
    movePoint = widget->getTouchMovePos();
    CCPoint offset = ccpSub(movePoint, lastPoint);
    CCPoint toPoint = ccpAdd(widget->getPosition(), offset);
    
    widget->setPosition(toPoint);
}

void CocosGUISlotScene::dropEquip(CCObject *pSender)
{
    bool isInUseSlot = false;
    bool isInEquipSlot = false;
    
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    CCRect widget_rect = widget->getRect();
    
    // usedSlot
    CCDictElement* usedSlotElement = NULL;
    CCDICT_FOREACH(m_dicBeUsedSlot, usedSlotElement)
    {
        UIWidget* usedSlot = dynamic_cast<UIWidget*>(usedSlotElement->getObject());
        if (usedSlot->getChildren()->count() > 0)
        {
            continue;
        }
        CCRect slot_rect = usedSlot->getRect();
        if (slot_rect.containsPoint(widget_rect.origin))
        {
            widget->removeFromParentAndCleanup(false);
            widget->setPosition(CCPointZero);
            usedSlot->addChild(widget);
            
            isInUseSlot = true;
            break;
        }
    }
    
    // equipSlot
    CCDictionary* dictionary = NULL;
    switch (m_eEquipType)
    {
        case EQUIP_TYPE_CLOTHES:
            dictionary = m_dicEquipClothesSlot;
            break;
            
        case EQUIP_TYPE_WEAPONS:
            dictionary = m_dicEquipWeaponsSlot;
            break;
            
        case EQUIP_TYPE_PETS:
            dictionary = m_dicEquipPetsSlot;
            break;
            
        default:
            break;
    }
    
    CCDictElement* equipSlotElement = NULL;
    CCDICT_FOREACH(dictionary, equipSlotElement)
    {
        UIWidget* equipSlot = dynamic_cast<UIWidget*>(equipSlotElement->getObject());
        if (equipSlot->getChildren()->count() > 0)
        {
            continue;
        }
        
        CCRect slot_rect = equipSlot->getRect();
        if (slot_rect.containsPoint(widget_rect.origin))
        {
            // check equip types
            switch (m_eEquipType)
            {
                case EQUIP_TYPE_CLOTHES:
                {
                    bool canDropInClothesSlot = false;
                    
                    CCDictElement* equipClothes = NULL;
                    CCDICT_FOREACH(m_dicEquipClothes, equipClothes)
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(equipClothes->getObject());
                        
                        if (strcmp(child->getName(), widget->getName()) == 0)
                        {
                            canDropInClothesSlot = true;
                            break;
                        }
                    }
                    
                    if (!canDropInClothesSlot)
                    {
                        break;
                    }
                    
                    widget->removeFromParentAndCleanup(false);
                    widget->setPosition(CCPointZero);
                    equipSlot->addChild(widget);
                    
                    isInEquipSlot = true;
                }
                    break;
                    
                case EQUIP_TYPE_WEAPONS:
                {
                    bool canDropInWeaponsSlot = false;
                    
                    CCDictElement* equipWeapons = NULL;
                    CCDICT_FOREACH(m_dicEquipWeapons, equipWeapons)
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(equipWeapons->getObject());
                        if (strcmp(child->getName(), widget->getName()) == 0)
                        {
                            canDropInWeaponsSlot = true;
                            break;
                        }
                    }
                    
                    if (!canDropInWeaponsSlot)
                    {
                        break;
                    }
                    
                    widget->removeFromParentAndCleanup(false);
                    widget->setPosition(CCPointZero);
                    equipSlot->addChild(widget);
                    
                    isInEquipSlot = true;
                }
                    break;
                    
                case EQUIP_TYPE_PETS:
                {
                    bool canDropInPetsSlot = false;
                    
                    CCDictElement* equipPets = NULL;
                    CCDICT_FOREACH(m_dicEquipPets, equipPets)
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(equipPets->getObject());
                        
                        if (strcmp(child->getName(), widget->getName()) == 0)
                        {
                            canDropInPetsSlot = true;
                            break;
                        }
                    }
                    
                    if (!canDropInPetsSlot)
                    {
                        break;
                    }
                    
                    widget->removeFromParentAndCleanup(false);
                    widget->setPosition(CCPointZero);
                    equipSlot->addChild(widget);
                    
                    isInEquipSlot = true;
                }
                    break;
                    
                default:
                    break;
            }
            //
            
            /*
             widget->removeFromParentAndCleanup(false);
             widget->setPosition(CCPointZero);
             equipSlot->addChild(widget);
             
             isInEquipSlot = true;
             */
            break;
        }
    }
    
    // back to last position
    if (!isInUseSlot && !isInEquipSlot)
    {
        CCPoint point = widgetLastLocal;
        CCMoveTo* moveTo = CCMoveTo::create(1.0f, point);
        CCEaseExponentialOut* ease = CCEaseExponentialOut::create(moveTo);
        CCCallFuncO* calllFunc0 = CCCallFuncO::create(this, callfuncO_selector(CocosGUISlotScene::backOver), widget);
        CCSequence* seq = CCSequence::create(ease, calllFunc0, NULL);
        widget->runAction(seq);
        widget->setBeTouchEnable(false);
    }
    
    widget->setColor(ccc3(255, 255, 255));
}

void CocosGUISlotScene::backOver(CCObject *pObject)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pObject);
    
    widget->setBeTouchEnable(true);
    widget->removeFromParentAndCleanup(false);
    lastWidgetParent->addChild(widget);
    widget->setPosition(widgetLastNodePosition);
    
    widget->setColor(ccc3(255, 255, 255));
}
