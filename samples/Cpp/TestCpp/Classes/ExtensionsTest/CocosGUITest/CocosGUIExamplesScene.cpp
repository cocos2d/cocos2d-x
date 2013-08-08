

#include "CocosGUIExamplesScene.h"
#include "CocosGUIScene.h"


const char* weapon_introduce_text[31] =
{
	"Chinese: 1",
	"Japanese: 2",
	"Korean: 3",
	"English: 4",
	"French: 5",
	"Russian: 6",
	"German: 7",
	"Spanish: 8",
	"Portuguese: 9",
	"Italian: 10",
	"Greek: 11",
	"Dutch: 12",
	"Swedish: 13",
	"Arabic: 14",
	"Czech: 15",
	"Danish: 16",
	"Finnish: 17",
	"Norwegian:18",
	"Bulgarian: 19",
	"Persian: 20",
	"Hausa: 21",
	"Schieber Lai: 22",
	"Hindi: 23",
	"Hungarian: 24",
	"Pushtu: 25",
	"Polish: 26",
	"Romanian: 27",
	"Serbian: 28",
	"Thai: 29",
	"Turkish: 30",
	"Urdu: 31",
};


CocosGUIExamplesScene::CocosGUIExamplesScene(bool bPortrait)
{
	TestScene::init();
}

CocosGUIExamplesScene::~CocosGUIExamplesScene()
{
	cocos2d::extension::CCJsonReader::purgeJsonReader();
	cocos2d::extension::UIActionManager::purgeUIActionManager();
	cocos2d::extension::UIHelper::purgeUIHelper();
}

void CocosGUIExamplesScene::onEnter()
{
    TestScene::onEnter();
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
    // ui init
    ExamplesInit();
    
    // exit
    UIButton* exit = UIButton::create();
    exit->setTextures("cocosgui/CloseNormal.png", "cocosgui/CloseSelected.png", "");
    exit->setPosition(ccp(430, 60));
    exit->setTouchEnable(true);
    exit->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::toCocosGUITestScene));
    ul->addWidget(exit);
}

void CocosGUIExamplesScene::onExit()
{
    TestScene::onExit();
}

void CocosGUIExamplesScene::runThisTest()
{    
	CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUIExamplesScene::MainMenuCallback(CCObject* pSender)
{
    ul->removeFromParent();
	TestScene::MainMenuCallback(pSender);
}

void CocosGUIExamplesScene::toCocosGUITestScene(CCObject *pSender)
{
    ul->removeFromParent();
    
    CocosGUITestScene *pScene = new CocosGUITestScene();
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}

// ui
void CocosGUIExamplesScene::ExamplesInit()
{
    // example root
    UIWidget* example_root = CCUIHELPER->createWidgetFromJsonFile("cocosgui/examples/examples_1.json");
    example_root->setWidgetTag(EXAMPLE_PANEL_TAG_ROOT);
    ul->addWidget(example_root);
    
    // example button initialize
    ExamplesButtonPanelInit();
    
    // equip initialize
    EquipInit();
    
    // weapon initialize
    WeaponInit();
}

// ui button
void CocosGUIExamplesScene::ExamplesButtonPanelInit()
{
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // examples initialize
    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel")); 
    
    UIButton* equip_btn = dynamic_cast<UIButton*>(button_panel->getChildByName("equip_button"));
    equip_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::ExamplesShowEquip));
    
    UIButton* weapon_btn = dynamic_cast<UIButton*>(button_panel->getChildByName("weapon_button"));
    weapon_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::ExamplesShowWeapon));
}

void CocosGUIExamplesScene::ExamplesShowEquip(CCObject* pSender)
{    
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // equip
    UIPanel* equip_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
    equip_root->setVisible(true);
    
    // button panel
    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));
    button_panel->disable(true);
}

void CocosGUIExamplesScene::ExamplesShowWeapon(CCObject* pSender)
{
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // examples button panel
    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));
    button_panel->disable(true);
    
    // weapon root
    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
    weapon_root->setVisible(true);
    
    // weapon reset
    // introduce panel
    UIPanel* weapon_introduce_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("introduce_panel"));
    UITextArea* weapon_introduce_text = dynamic_cast<UITextArea*>(weapon_introduce_panel->getChildByName("introduce_text"));
    weapon_introduce_text->setText("Please touch weapon icon to watch introduce,and scroll panel to check more");
    
    // weapon panel
    UIPanel* weapon_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("weapon_panel"));
    
    // weapon scrollview
    UIScrollView* weapon_scrlv = dynamic_cast<UIScrollView*>(weapon_panel->getChildByName("weapon_scrollview"));    
    CCObject* obj = NULL;
    CCARRAY_FOREACH(weapon_scrlv->getChildren(), obj)
    {
        UIPanel* item = dynamic_cast<UIPanel*>(obj);
        
        UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
        normal->setVisible(true);
        
        UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
        selected->setVisible(false);
    }
}

// equip
void CocosGUIExamplesScene::EquipInit()
{
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
    
    widgetLastWorldSpace = CCPointZero;
    widgetLastNodeSpace = CCPointZero;
    lastWidgetParent = NULL;
    //    
    
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // equip root
    UIPanel* equipe_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
    equipe_root->setWidgetTag(EQUIP_PANEL_TAG_ROOT);
    
    // title panel
    UIPanel* title_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("Title"));
    UIButton* close_btn = dynamic_cast<UIButton*>(title_panel->getChildByName("button"));
    close_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipClose));
    
    // up panel
    UIPanel* up_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("UP"));
    up_panel->setWidgetTag(EQUIP_PANEL_TAG_UP);
    
    // switch button
    UITextButton* clothes_btn = dynamic_cast<UITextButton*>(up_panel->getChildByName("I_Button"));
    clothes_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipSwitchBtnCallBack));
    clothes_btn->setWidgetTag(EQUIP_SWITCH_PANEL_BUTTON_TAG_CLOTHES);
    clothes_btn->disable();
    
    UITextButton* weapons_btn = dynamic_cast<UITextButton*>(up_panel->getChildByName("II_Button"));
    weapons_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipSwitchBtnCallBack));
    weapons_btn->setWidgetTag(EQUIP_SWITCH_PANEL_BUTTON_TAG_WEAPONS);
    
    UITextButton* pets_btn = dynamic_cast<UITextButton*>(up_panel->getChildByName("III_Button"));
    pets_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipSwitchBtnCallBack));
    pets_btn->setWidgetTag(EQUIP_SWITCH_PANEL_BUTTON_TAG_PETS);
    
    // repertories 
    UIPanel* clothes_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("IX"));
    clothes_panel->setWidgetTag(EQUIP_PANEL_TAG_CLOTHES);
    
    UIPanel* weapons_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("IIX"));
    weapons_panel->setWidgetTag(EQUIP_PANEL_TAG_WEAPONS);
    
    UIPanel* pets_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("IIIX"));
    pets_panel->setWidgetTag(EQUIP_PANEL_TAG_PETS);
    
    container_1_Zorder = clothes_panel->getWidgetZOrder();
    container_2_Zorder = weapons_panel->getWidgetZOrder();
    container_3_Zorder = pets_panel->getWidgetZOrder();
    
    container_1_Position = clothes_panel->getPosition();
    container_2_Position = weapons_panel->getPosition();
    container_3_Position = pets_panel->getPosition();
    
    CCObject* obj = NULL;
    // clothes repertory slot
    CCARRAY_FOREACH(clothes_panel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicEquipClothesSlot->setObject(child, child->getName());
    }
    // weapons repertory slot
    CCARRAY_FOREACH(weapons_panel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicEquipWeaponsSlot->setObject(child, child->getName());
    }
    // pets repertory slot
    CCARRAY_FOREACH(pets_panel->getChildren(), obj)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(obj);
        m_dicEquipPetsSlot->setObject(child, child->getName());
    }
    
    // actor
    UIImageView* walBG_iv = dynamic_cast<UIImageView*>(up_panel->getChildByName("WAL"));
    UIImageView* wal_iv = UIImageView::create();
    wal_iv->setTexture("cocosgui/examples/equip/eg/1.png");
    wal_iv->setAnchorPoint(ccp(0.5, 0.5));
    float wal_x = walBG_iv->getRect().size.width / 2.04;
    float wal_y = walBG_iv->getRect().size.height / 2.4;
    wal_iv->setPosition(ccp((-walBG_iv->getRect().size.width / 2) +  wal_x,
                                  (-walBG_iv->getRect().size.height / 2) + wal_y));
    walBG_iv->addChild(wal_iv);
    
    // original clothes be used slot
    UIImageView* originalClothesSlot_iv = dynamic_cast<UIImageView*>(up_panel->getChildByName("1"));
    UIImageView* originalClothes_iv = UIImageView::create();
    originalClothes_iv->setTexture("cocosgui/examples/equip/eg/6.png");
    originalClothesSlot_iv->addChild(originalClothes_iv);
    m_dicBeUsedSlot->setObject(originalClothesSlot_iv, originalClothesSlot_iv->getName());
    
    // other be used slot
    UIImageView* slot_2_iv = dynamic_cast<UIImageView*>(up_panel->getChildByName("2"));
    m_dicBeUsedSlot->setObject(slot_2_iv, slot_2_iv->getName());
    UIImageView* slot_3_iv = dynamic_cast<UIImageView*>(up_panel->getChildByName("3"));
    m_dicBeUsedSlot->setObject(slot_3_iv, slot_3_iv->getName());
    UIImageView* slot_4_iv = dynamic_cast<UIImageView*>(up_panel->getChildByName("4"));
    m_dicBeUsedSlot->setObject(slot_4_iv, slot_4_iv->getName());
    UIImageView* slot_5_iv = dynamic_cast<UIImageView*>(up_panel->getChildByName("5"));
    m_dicBeUsedSlot->setObject(slot_5_iv, slot_5_iv->getName());
    UIImageView* slot_6_iv = dynamic_cast<UIImageView*>(up_panel->getChildByName("6"));
    m_dicBeUsedSlot->setObject(slot_6_iv, slot_6_iv->getName());
    
    // equip create
    EquipCreate();
    
    // initialize touch able and influence children
    clothes_panel->setTouchEnable(true, true);
    weapons_panel->setTouchEnable(false, false);
    pets_panel->setTouchEnable(false, false);
}

void CocosGUIExamplesScene::EquipCreate()
{
    EquipCreateClothes();
    EquipCreateWeapons();
    EquipCreatePets();
}

void CocosGUIExamplesScene::EquipCreateClothes()
{
    UIPanel* clothes_panel = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EQUIP_PANEL_TAG_CLOTHES));
    
    // clothes
    float parent_w = clothes_panel->getRect().size.width;
    float parent_h = clothes_panel->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;        
    
    const short columnMax = 3;
    
    // jacket
    const char* jacket_png[columnMax] =
    {
        "cocosgui/examples/equip/eg/3.png",
        "cocosgui/examples/equip/eg/4.png",
        "cocosgui/examples/equip/eg/5.png",
    };
    const char* jacket_name[columnMax] =
    {
        "jacket_taenia",
        "jacket_suit",
        "jacket_shoes",
    };
    for (int i = 0; i < columnMax; ++i)
    {
        UIImageView* jacket_iv = UIImageView::create();
        jacket_iv->setTexture(jacket_png[i]);
        jacket_iv->setAnchorPoint(ccp(0.5, 0.5));
        jacket_iv->setPosition(ccp(offest_x + i * offest_x * 4, parent_h - offest_y));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(clothes_panel->getChildren()->lastObject());
        if (lastChild)
        {
            jacket_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        jacket_iv->setName(jacket_name[i]);
        jacket_iv->setTouchEnable(true);
        jacket_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesScene::EquipTouch));
        jacket_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesScene::EquipMove));
        jacket_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipDrop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(clothes_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(jacket_iv->getPosition()))
            {
                jacket_iv->setPosition(CCPointZero);
                slot->addChild(jacket_iv);
                break;
            }
        }
        
        m_dicEquipClothes->setObject(jacket_iv, jacket_iv->getName());
    }
    
    // kimono
    const char* kimono_png[columnMax] =
    {
        "cocosgui/examples/equip/eg/8.png",
        "cocosgui/examples/equip/eg/10.png",
        "cocosgui/examples/equip/eg/9.png",
    };
    const char* kimono_name[columnMax] =
    {
        "kimono_strawhat",
        "kimono_suit",
        "kimono_shoes",
    };
    for (int i = 0; i < columnMax; ++i)
    {
        UIImageView* kimono_iv = UIImageView::create();
        kimono_iv->setTexture(kimono_png[i]);
        kimono_iv->setPosition(ccp(offest_x + i * offest_x * 4, parent_h - offest_y * 3));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(clothes_panel->getChildren()->lastObject());
        if (lastChild)
        {
            kimono_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        kimono_iv->setName(kimono_name[i]);
        kimono_iv->setTouchEnable(true);
        kimono_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesScene::EquipTouch));
        kimono_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesScene::EquipMove));
        kimono_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipDrop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(clothes_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(kimono_iv->getPosition()))
            {
                kimono_iv->setPosition(CCPointZero);
                slot->addChild(kimono_iv);
                break;
            }
        }
        
        m_dicEquipClothes->setObject(kimono_iv, kimono_iv->getName());
    }
}

void CocosGUIExamplesScene::EquipCreateWeapons()
{
    UIPanel* weapons_panel = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EQUIP_PANEL_TAG_WEAPONS));
    
    // weapons
    float parent_w = weapons_panel->getRect().size.width;
    float parent_h = weapons_panel->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    // sword
    const short swordAmount = 3;
    const char* sword_png[swordAmount] =
    {
        "cocosgui/examples/equip/eg/train.png",
        "cocosgui/examples/equip/eg/research.png",
        "cocosgui/examples/equip/eg/upgrade.png",
    };
    const char* sword_name[swordAmount] =
    {
        "sword_sword",
        "sword_plus",
        "sword_hammer",
    };
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
        sword_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesScene::EquipTouch));
        sword_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesScene::EquipMove));
        sword_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipDrop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weapons_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(sword_iv->getPosition()))
            {
                sword_iv->setPosition(CCPointZero);
                slot->addChild(sword_iv);
                break;
            }
        }
        
        m_dicEquipWeapons->setObject(sword_iv, sword_iv->getName());
    }
    
    // arrow
    const short arrowAmount = 3;
    const char* arrow_png[arrowAmount] =
    {
        "cocosgui/examples/equip/eg/shop_shield_1.png",
        "cocosgui/examples/equip/eg/shop_shield_2.png",
        "cocosgui/examples/equip/eg/shop_shield_3.png",
    };
    const char* arrow_name[arrowAmount] =
    {
        "arraw_normal",
        "arraw_hard",
        "arraw_devil",
    };
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
        arrow_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesScene::EquipTouch));
        arrow_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesScene::EquipMove));
        arrow_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipDrop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weapons_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(arrow_iv->getPosition()))
            {
                arrow_iv->setPosition(CCPointZero);
                slot->addChild(arrow_iv);
                break;
            }
        }
        
        m_dicEquipWeapons->setObject(arrow_iv, arrow_iv->getName());
    }
    
    // bomb
    const short bombAmount = 1;
    const char* bomb_png[bombAmount] =
    {
        "cocosgui/examples/equip/eg/sell.png",
    };
    const char* bomb_name[bombAmount] =
    {
        "bomb_normal",
    };
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
        bomb_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesScene::EquipTouch));
        bomb_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesScene::EquipMove));
        bomb_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipDrop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(weapons_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(bomb_iv->getPosition()))
            {
                bomb_iv->setPosition(CCPointZero);
                slot->addChild(bomb_iv);
                break;
            }
        }
        
        m_dicEquipWeapons->setObject(bomb_iv, bomb_iv->getName());
    }
}

void CocosGUIExamplesScene::EquipCreatePets()
{
    UIPanel* pets_panel = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EQUIP_PANEL_TAG_PETS));
    
    // pets
    float parent_w = pets_panel->getRect().size.width;
    float parent_h = pets_panel->getRect().size.height;
    float offest_x = parent_w / 10;
    float offest_y = parent_h / 6;
    
    // dragon
    const short dragonAmount = 1;
    const char* dragon_png[dragonAmount] =
    {
        "cocosgui/examples/equip/eg/7.png",
    };
    const char* dragon_name[dragonAmount] =
    {
        "pet_dragon",
    };
    for (int i = 0; i < dragonAmount; ++i)
    {
        UIImageView* dragon_iv = UIImageView::create();
        dragon_iv->setTexture(dragon_png[i]);
        dragon_iv->setPosition(ccp(offest_x, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(pets_panel->getChildren()->lastObject());
        if (lastChild)
        {
            dragon_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        dragon_iv->setName(dragon_name[i]);
        dragon_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesScene::EquipTouch));
        dragon_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesScene::EquipMove));
        dragon_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipDrop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(pets_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(dragon_iv->getPosition()))
            {
                dragon_iv->setPosition(CCPointZero);
                slot->addChild(dragon_iv);
                break;
            }
        }
        
        m_dicEquipPets->setObject(dragon_iv, dragon_iv->getName());
    }
    
    // crab
    const short crabAmount = 1;
    const char* crab_png[crabAmount] =
    {
        "cocosgui/examples/equip/eg/crab.png",
    };
    const char* crab_name[crabAmount] =
    {
        "pet_crab",
    };
    for (int i = 0; i < crabAmount; ++i)
    {
        UIImageView* crab_iv = UIImageView::create();
        crab_iv->setTexture(crab_png[i]);
        crab_iv->setPosition(ccp(offest_x * 5, parent_h - offest_y - i * (offest_y * 2)));
        UIWidget* lastChild = dynamic_cast<UIWidget*>(pets_panel->getChildren()->lastObject());
        if (lastChild)
        {
            crab_iv->setWidgetZOrder(lastChild->getWidgetZOrder() + 1);
        }
        crab_iv->setName(crab_name[i]);
        crab_iv->addPushDownEvent(this, coco_pushselector(CocosGUIExamplesScene::EquipTouch));
        crab_iv->addMoveEvent(this, coco_moveselector(CocosGUIExamplesScene::EquipMove));
        crab_iv->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::EquipDrop));
        
        CCObject* obj = NULL;
        CCARRAY_FOREACH(pets_panel->getChildren(), obj)
        {
            UIWidget* slot = dynamic_cast<UIWidget*>(obj);
            slot->setCascadeColorEnabled(false);
            CCRect slot_rect = slot->getRelativeRect();
            if (slot_rect.containsPoint(crab_iv->getPosition()))
            {
                crab_iv->setPosition(CCPointZero);
                slot->addChild(crab_iv);
                break;
            }
        }
        
        m_dicEquipPets->setObject(crab_iv, crab_iv->getName());
    }
    
}

void CocosGUIExamplesScene::EquipSwitchBtnCallBack(CCObject *pSender)
{
    // switch button
    UIButton* button = dynamic_cast<UIButton*>(pSender);
    
    // equip root
    UIPanel* root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EQUIP_PANEL_TAG_ROOT));
    
    // equip repertory
    UIPanel* clothes_panel = dynamic_cast<UIPanel*>(root->getChildByTag(EQUIP_PANEL_TAG_CLOTHES));
    UIPanel* weapons_panel = dynamic_cast<UIPanel*>(root->getChildByTag(EQUIP_PANEL_TAG_WEAPONS));
    UIPanel* pets_panel = dynamic_cast<UIPanel*>(root->getChildByTag(EQUIP_PANEL_TAG_PETS));
    
    UIPanel* up_panel = dynamic_cast<UIPanel*>(root->getChildByTag(EQUIP_PANEL_TAG_UP));
    UITextButton* clothes_btn = dynamic_cast<UITextButton*>(up_panel->getChildByTag(EQUIP_SWITCH_PANEL_BUTTON_TAG_CLOTHES));
    UITextButton* weapons_btn = dynamic_cast<UITextButton*>(up_panel->getChildByTag(EQUIP_SWITCH_PANEL_BUTTON_TAG_WEAPONS));
    UITextButton* pets_btn = dynamic_cast<UITextButton*>(up_panel->getChildByTag(EQUIP_SWITCH_PANEL_BUTTON_TAG_PETS));
    
    clothes_btn->active();
    weapons_btn->active();
    pets_btn->active();    
    
    switch (button->getWidgetTag())
    {
        case EQUIP_SWITCH_PANEL_BUTTON_TAG_CLOTHES:
        {
            m_eEquipType = EQUIP_TYPE_CLOTHES;
            
            clothes_btn->disable();
            
            clothes_panel->setWidgetZOrder(container_1_Zorder);
            weapons_panel->setWidgetZOrder(container_2_Zorder);
            pets_panel->setWidgetZOrder(container_3_Zorder);
            
            clothes_panel->setPosition(container_1_Position);
            weapons_panel->setPosition(container_2_Position);
            pets_panel->setPosition(container_3_Position);
            
            // equip slot touch able
            clothes_panel->setTouchEnable(true, true);
            weapons_panel->setTouchEnable(false, true);
            pets_panel->setTouchEnable(false, true);
        }
            break;
            
        case EQUIP_SWITCH_PANEL_BUTTON_TAG_WEAPONS:
        {
            m_eEquipType = EQUIP_TYPE_WEAPONS;
            
            weapons_btn->disable();
            
            clothes_panel->setWidgetZOrder(container_3_Zorder);
            weapons_panel->setWidgetZOrder(container_1_Zorder);
            pets_panel->setWidgetZOrder(container_2_Zorder);
            
            weapons_panel->setPosition(container_1_Position);
            pets_panel->setPosition(container_2_Position);
            clothes_panel->setPosition(container_3_Position);
            
            // equip slot touch able
            weapons_panel->setTouchEnable(true, true);
            clothes_panel->setTouchEnable(false, true);
            pets_panel->setTouchEnable(false, true);
        }
            break;
            
        case EQUIP_SWITCH_PANEL_BUTTON_TAG_PETS:
        {
            m_eEquipType = EQUIP_TYPE_PETS;
            
            pets_btn->disable();
            
            pets_panel->setWidgetZOrder(container_1_Zorder);
            clothes_panel->setWidgetZOrder(container_2_Zorder);
            weapons_panel->setWidgetZOrder(container_3_Zorder);
            
            pets_panel->setPosition(container_1_Position);
            clothes_panel->setPosition(container_2_Position);
            weapons_panel->setPosition(container_3_Position);
            
            // equip slot touch able
            pets_panel->setTouchEnable(true, true);
            clothes_panel->setTouchEnable(false, true);
            weapons_panel->setTouchEnable(false, true);
        }
            break;
            
        default:
            break;
    }
}

void CocosGUIExamplesScene::EquipTouch(CCObject *pSender)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    CCPoint worldSpace = widget->getContainerNode()->convertToWorldSpace(CCPointZero);
    
    widgetLastWorldSpace = worldSpace;
    widgetLastNodeSpace = widget->getPosition();
    
    lastWidgetParent = widget->getWidgetParent();
    widget->removeFromParentAndCleanup(false);
    
    ul->addWidget(widget);
    
    widget->setPosition(widget->getTouchStartPos());
    movePoint = widget->getTouchStartPos();
}

void CocosGUIExamplesScene::EquipMove(CCObject* pSender)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    
    lastPoint = movePoint;
    movePoint = widget->getTouchMovePos();
    CCPoint offset = ccpSub(movePoint, lastPoint);
    CCPoint toPoint = ccpAdd(widget->getPosition(), offset);    
    widget->setPosition(toPoint);
}

void CocosGUIExamplesScene::EquipDrop(CCObject *pSender)
{
    bool isInUsedSlot = false;
    bool isInEquipSlot = false;
    
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
//    CCRect widget_rect = widget->getRect();
    
    CCDictElement* element = NULL;
    
    // usedSlot
    CCDICT_FOREACH(m_dicBeUsedSlot, element)
    {
        UIWidget* usedSlot_wigt = dynamic_cast<UIWidget*>(element->getObject());
        if (usedSlot_wigt->getChildren()->count() > 0)
        {
            continue;
        }
        CCRect slot_rect = usedSlot_wigt->getRect();
        if (slot_rect.containsPoint(widget->getPosition()))
        {
            widget->removeFromParentAndCleanup(false);
            widget->setPosition(CCPointZero);
            usedSlot_wigt->addChild(widget);
            
            isInUsedSlot = true;
            break;
        }
    }
    
    // equipSlot
    CCDictionary* equipSlot_dic = NULL;
    CCDictionary* equip_dic = NULL;
    switch (m_eEquipType)
    {
        case EQUIP_TYPE_CLOTHES:
            equipSlot_dic = m_dicEquipClothesSlot;
            equip_dic = m_dicEquipClothes;
            break;
            
        case EQUIP_TYPE_WEAPONS:
            equipSlot_dic = m_dicEquipWeaponsSlot;
            equip_dic = m_dicEquipWeapons;
            break;
            
        case EQUIP_TYPE_PETS:
            equipSlot_dic = m_dicEquipPetsSlot;
            equip_dic = m_dicEquipPets;
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
    
    // back to last position
    if (!isInUsedSlot && !isInEquipSlot)
    {
        CCPoint point = widgetLastWorldSpace;
        CCMoveTo* moveTo = CCMoveTo::create(1.0f, point);
        CCEaseExponentialOut* ease = CCEaseExponentialOut::create(moveTo);
        CCCallFuncO* calllFunc0 = CCCallFuncO::create(this, callfuncO_selector(CocosGUIExamplesScene::EquipBackOver), widget);
        CCSequence* seq = CCSequence::create(ease, calllFunc0, NULL);
        widget->runAction(seq);
        
        // widget in equip slot
        CCDICT_FOREACH(equip_dic, element)
        {
            UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
            widget->setTouchEnable(false, true);
        }
        
        // equip up panel
        UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
        UIPanel* equipe_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
        UIPanel* up_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("UP"));
        up_panel->setTouchEnable(false, true);        
    }
}

void CocosGUIExamplesScene::EquipBackOver(CCObject *pObject)
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
            equip_dic = m_dicEquipClothes;
            break;
            
        case EQUIP_TYPE_WEAPONS:
            equip_dic = m_dicEquipWeapons;
            break;
            
        case EQUIP_TYPE_PETS:
            equip_dic = m_dicEquipPets;
            break;
            
        default:
            break;
    }
    CCDICT_FOREACH(equip_dic, element)
    {
        UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
        widget->setTouchEnable(true, true);
    }
    
    // equip up panel
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    UIPanel* equipe_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
    UIPanel* up_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("UP"));
    up_panel->setTouchEnable(true, true);
}

void CocosGUIExamplesScene::EquipClose(CCObject* pObject)
{
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // equip
    UIPanel* equip_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
    equip_root->setVisible(false);
    
    // button panel
    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));    
    button_panel->active(true);
}

// weapon
void CocosGUIExamplesScene::WeaponInit()
{
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // weapon
    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
    weapon_root->setWidgetTag(WEAPON_PANEL_TAG_ROOT);
    
    // title panel
    UIPanel* title_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("Title"));
    UIButton* close_btn = dynamic_cast<UIButton*>(title_panel->getChildByName("Button"));
    close_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::WeaponClose));
    
    // introduce panel
    UIPanel* introduce_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("introduce_panel"));
    UITextArea* introduce_text = dynamic_cast<UITextArea*>(introduce_panel->getChildByName("introduce_text"));
    introduce_text->setText("点击武器图标查看武器介绍，滑动武器库查看更多武器");        
    
    // weapon panel create
    WeaponCreate();
}

void CocosGUIExamplesScene::WeaponCreate()
{
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // weapon root
    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
    weapon_root->setWidgetTag(WEAPON_PANEL_TAG_ROOT);    
    
    // weapon panel
    UIPanel* weapon_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("weapon_panel"));
    
    // weapon scrollview
    UIScrollView* weapon_scrlv = dynamic_cast<UIScrollView*>(weapon_panel->getChildByName("weapon_scrollview"));
    float weapon_scrlv_width = weapon_scrlv->getRect().size.width;
    float weapon_scrlv_height = weapon_scrlv->getRect().size.height;
    
    // weapon item create
    int dataLength = sizeof(weapon_introduce_text) / sizeof(weapon_introduce_text[0]);
    int columnMax = 4;
    int mod = dataLength % columnMax;
    int rowMax = dataLength / columnMax;
    if (mod != 0)
    {
        rowMax += 1;
    }
    
    for (int i = 0; i  < rowMax; ++i)
    {
        bool isBreak_i = false;
        
        for (int j = 0; j < columnMax; ++j)
        {
            bool isBreak_j = false;
            
            if (i * columnMax + j == dataLength)
            {
                isBreak_i = true;
                isBreak_j = true;
            }
            
            if (isBreak_j)
            {
                break;
            }
            
            
            UIPanel* item = dynamic_cast<UIPanel*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/examples/weapon_introduce/weapon_item/weapon_item_1.json"));
            item->setWidgetTag(WEAPON_ITEM_PANEL_TAG + i * columnMax + j);
            
            float width = item->getRect().size.width;
            float height = item->getRect().size.height;
            float interval_x = width / 10;
            float interval_y = height / 10;
            float start_x = weapon_scrlv_width / 25;
            float start_y = weapon_scrlv_height - height;
            float x = start_x + j * (width + interval_x);
            float y = start_y - i * (height + interval_y);
            item->setPosition(ccp(x, y));
            
            weapon_scrlv->addChild(item);
            
            // weapon item normal
            UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
            normal->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::WeaponItemTouch));
            // weapon item selected
            UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
            selected->setVisible(false);
            // weapon item weapon
            UIImageView* weapon = dynamic_cast<UIImageView*>(item->getChildByName("weapon"));
            weapon->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::WeaponItemTouch));
        }
        
        if (isBreak_i)
        {
            break;
        }
    }        
}

void CocosGUIExamplesScene::WeaponItemTouch(CCObject* pObject)
{
    // weapon item child
    UIImageView* widget = dynamic_cast<UIImageView*>(pObject);
    
    // weapon item
    UIPanel* item = dynamic_cast<UIPanel*>(widget->getWidgetParent());
    
    // weapon scrollview
    UIScrollView* scrollview = dynamic_cast<UIScrollView*>(item->getWidgetParent());
    CCObject* obj = NULL;
    CCARRAY_FOREACH(scrollview->getChildren(), obj)
    {
        UIPanel* item = dynamic_cast<UIPanel*>(obj);
        
        UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
        normal->setVisible(true);
        
        UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
        selected->setVisible(false);
    }
    
    // weapon item normal
    UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
    normal->setVisible(false);
    
    // weapon item selected
    UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
    selected->setVisible(true);
    
    WeaponItemShowDetail(item);
}

void CocosGUIExamplesScene::WeaponItemShowDetail(UIWidget* widget)
{
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // weapon
    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
    // introduce panel
    UIPanel* introduce_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("introduce_panel"));
    UITextArea* introduce_text = dynamic_cast<UITextArea*>(introduce_panel->getChildByName("introduce_text"));
        
    introduce_text->setText(weapon_introduce_text[widget->getWidgetTag() - WEAPON_ITEM_PANEL_TAG]);
}

void CocosGUIExamplesScene::WeaponClose(CCObject* pObject)
{
    // examples root
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    
    // weapon
    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
    weapon_root->setVisible(false);
    
    // button panel
    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));
    button_panel->active(true);
}
