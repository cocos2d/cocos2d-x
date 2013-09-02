

#include "CocosGUIExamplesWeaponScene.h"
#include "CocosGUIExamplesEquipScene.h"
#include "CocosGUIExamplesMapScene.h"

const char* weapon_introduce_text[31] =
{
	"Booties: 1.99$",
	"Targe: 2.99$",
	"Cane: 3.99$",
	"Bushwacka: 4.99$",
	"Sandvich: 5.99$",
	"Banner: 6.99$",
	"Beast: 7.99$",
	"Bottle: 8.99$",
	"Basher: 9.99$",
	"Bootlegger.: 10.99$",
	"Bonesaw: 11.99$",
	"Blutsauger: 12.99$",
	"Rose: 13.99$",
	"Box: 14.99$",
	"Kill: 15.99$",
	"Earner: 16.99$",
	"Bazooka: 17.99$",
	"Bargain: 18.99$",
	"Backup: 19.99$",
	"Bat: 20.99$",
	"Backburner: 21.99$",
	"Scratcher Lai: 22.99$",
	"Blaster: 23.99$",
	"Axtinguisher: 24.99$",
	"Hand: 25.99$",
	"Atomizer: 26.99$",
	"Armageddon: 27.99$",
	"Fists: 28.99$",
	"Sap: 29.99$",
	"Amputator: 30.99$",
	"Ambassador: 31.99$",
};

const int weapon_colors[31][3] =
{
    { 247, 172, 188 },
    { 222, 171, 138 },
    { 129, 121, 54  },
    { 68,  70,  147 },
    
    { 201, 153, 121 },
    { 95,  93,  70 },
    { 27,  49,  94 },
    { 29,  22,  38 },
    
    { 239, 91,  156 },
    { 254, 220, 190 },
    { 127, 117, 34 },
    { 43,  68,  144 },
    
    { 222, 119, 63 },
    { 82,  95,  66 },
    { 37,  133, 166 },
    { 47,  39,  29 },
    
    { 254, 238, 237 },
    { 244, 121, 32 },
    { 128, 117, 44 },
    { 42,  92, 170 },
    
    { 183, 112, 79 },
    { 89,  96,  50 },
    { 37,  112, 161 },
    { 40,  31,  29 },
    
    { 240, 91,  114 },
    { 144, 90,  61 },
    { 135, 132, 59 },
    { 34,  75,  143 },
    
    { 180, 83,  42 },
    { 110, 107, 65 },
    { 36,  104, 42 },
};

CocosGUIExamplesWeaponScene::CocosGUIExamplesWeaponScene()
{
    CCScene::init();
}

CocosGUIExamplesWeaponScene::~CocosGUIExamplesWeaponScene()
{
    
}

void CocosGUIExamplesWeaponScene::onEnter()
{
    CCScene::onEnter();
    
    m_pUILayer = UILayer::create();
    m_pUILayer->scheduleUpdate();
    addChild(m_pUILayer);
    
    WeaponInit();
    BuyInit();
    
    // left button
    UIButton* left_button = UIButton::create();
    left_button->setTouchEnable(true);
    left_button->loadTextures("cocosgui/UITest/b1.png", "cocosgui/UITest/b2.png", "");
    float left_button_width = left_button->getContentSize().width;
    left_button->setPosition(ccp(left_button_width - left_button_width / 2, m_pUILayer->getContentSize().height / 2));
    left_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesWeaponScene::toCocosGUIExamplesEquipScene));
    m_pUILayer->addWidget(left_button);
    
    // right button
    UIButton* right_button = UIButton::create();
    right_button->setTouchEnable(true);
    right_button->loadTextures("cocosgui/UITest/f1.png", "cocosgui/UITest/f2.png", "");
    right_button->setPosition(ccp(m_pUILayer->getContentSize().width - right_button->getContentSize().width / 2, m_pUILayer->getContentSize().height / 2));
    right_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesWeaponScene::toCocosGUIExamplesMapScene));
    m_pUILayer->addWidget(right_button);
}

void CocosGUIExamplesWeaponScene::onExit()
{
    m_pUILayer->removeFromParent();
    
    CCSSceneReader::purgeSceneReader();
    UIHelper::purgeUIHelper();
    UIActionManager::purgeUIActionManager();
    
    CCScene::onExit();
}

void CocosGUIExamplesWeaponScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUIExamplesWeaponScene::toCocosGUIExamplesEquipScene(CCObject *pSender)
{
    CocosGUIExamplesEquipScene* pScene = new CocosGUIExamplesEquipScene();
    pScene->runThisTest();
    pScene->release();
}

void CocosGUIExamplesWeaponScene::toCocosGUIExamplesMapScene(CCObject *pSender)
{
    CocosGUIExamplesMapScene* pScene = new CocosGUIExamplesMapScene();
    pScene->runThisTest();
    pScene->release();
}

// weapon
void CocosGUIExamplesWeaponScene::WeaponInit()
{
    // weapon root from json
    Layout* weapon_root = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/weapon_introduce_1/weapon_introduce_1.json"));
    m_pUILayer->addWidget(weapon_root);
    
    // title layout
    Layout* title_layout = dynamic_cast<Layout*>(weapon_root->getChildByName("title_panel"));
    UIButton* close_btn = dynamic_cast<UIButton*>(title_layout->getChildByName("close_button"));
    close_btn->setVisible(false);
//    close_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesWeaponScene::WeaponClose));
    
    // introduce layout
    Layout* introduce_layout = dynamic_cast<Layout*>(weapon_root->getChildByName("introduce_panel"));
    UITextArea* introduce_text = dynamic_cast<UITextArea*>(introduce_layout->getChildByName("introduce_text"));
    introduce_text->setFontSize(16);
    introduce_text->setText("Touch weapon icon to buy weapon introduce, scroll weapon warehouse to check more weapon.");
    
    // weapon layout create
    create();
}

void CocosGUIExamplesWeaponScene::create()
{    
    // weapon root
    Layout* weapon_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("weapon_root"));
    
    // weapon layout
    Layout* weapon_layout = dynamic_cast<Layout*>(weapon_root->getChildByName("weapon_panel"));
    
    // weapon scrollview
    UIScrollView* weapon_scrlv = dynamic_cast<UIScrollView*>(weapon_layout->getChildByName("weapon_scrollview"));
    
    float weapon_scrlv_inner_width = weapon_scrlv->getInnerContainerSize().width;
    float weapon_scrlv_inner_height = weapon_scrlv->getInnerContainerSize().height;
    
    // weapon item add to weapon scrollview
    int dataLength = sizeof(weapon_introduce_text) / sizeof(weapon_introduce_text[0]);
    int columnMax = 4;
    int mod = dataLength % columnMax;
    int rowMax = dataLength / columnMax;
    if (mod != 0)
    {
        rowMax += 1;
    }
    
    for (int i = 0; i < rowMax; ++i)
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
            
            Layout* item = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/weapon_introduce_1/weapon_item_1/weapon_item_1.json"));
            item->setWidgetTag(WEAPON_ITEM_LAYOUT_TAG + i * columnMax + j);
            
            float width = item->getRect().size.width;
            float height = item->getRect().size.height;
            float interval_x = width / 10;
            float interval_y = height / 10;
            float start_x = weapon_scrlv_inner_width / 25;
            float start_y = weapon_scrlv_inner_height - (height + height / 9);
            float x = start_x + j * (width + interval_x);
            float y = start_y - i * (height + interval_y);
            item->setPosition(ccp(x, y));
            
            weapon_scrlv->addChild(item);
            
            // weapon item normal
            UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
            normal->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesWeaponScene::itemTouch));
            // weapon item selected
            UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
            selected->setVisible(false);
            // weapon item weapon
            UIImageView* weapon = dynamic_cast<UIImageView*>(item->getChildByName("weapon"));
            int index = i * columnMax + j;
            weapon->setTexture(CCString::createWithFormat("cocosgui/gui_examples/weapon_introduce_1/weapon_item_1/weapons/weapons_%d.png",
                                                          index + 1)->getCString());
            weapon->setScale(0.3f);
            weapon->setName(CCString::createWithFormat("weapon_%d", index)->getCString());
            weapon->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesWeaponScene::itemTouch));            
        }
        
        if (isBreak_i)
        {
            break;
        }
    }
}

void CocosGUIExamplesWeaponScene::itemTouch(CCObject* pObject)
{
    // weapon item child
    UIImageView* widget = dynamic_cast<UIImageView*>(pObject);
    
    // weapon item
    Layout* item = dynamic_cast<Layout*>(widget->getWidgetParent());
    
    // weapon scrollview
    UIContainerWidget* innerContainer = dynamic_cast<UIContainerWidget*>(item->getWidgetParent());
    CCObject* obj = NULL;
    CCARRAY_FOREACH(innerContainer->getChildren(), obj)
    {
        Layout* item = dynamic_cast<Layout*>(obj);
        
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
    
    // show weapon item info
    itemShowDetail(item);
    
    BuyLogic(item);
}

void CocosGUIExamplesWeaponScene::itemShowDetail(UIWidget* widget)
{
    // weapon
    Layout* weapon_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("weapon_root"));
    // introduce layout
    Layout* introduce_layout = dynamic_cast<Layout*>(weapon_root->getChildByName("introduce_panel"));
    UITextArea* introduce_text = dynamic_cast<UITextArea*>(introduce_layout->getChildByName("introduce_text"));
    
    introduce_text->setText(weapon_introduce_text[widget->getWidgetTag() - WEAPON_ITEM_LAYOUT_TAG]);
}

void CocosGUIExamplesWeaponScene::close(CCObject* pObject)
{
    // weapon
    Layout* weapon_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("weapon_root"));
    weapon_root->setVisible(false);
    
    // button layout
    Layout* button_layout = dynamic_cast<Layout*>(weapon_root->getChildByName("button_panel"));
    button_layout->active(true);
}

// buy
void CocosGUIExamplesWeaponScene::BuyInit()
{
    // buy root from json
    Layout* buy_root = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/buy_1/buy_1.json"));
    buy_root->setVisible(false);
    buy_root->setPosition(ccp((m_pUILayer->getContentSize().width - buy_root->getSize().width) / 2,
                              (m_pUILayer->getContentSize().height - buy_root->getSize().height) / 2 - buy_root->getSize().height / 2));
    m_pUILayer->addWidget(buy_root);
    
    UITextButton* cancel_textbutton = dynamic_cast<UITextButton*>(buy_root->getChildByName("cancel_textbutton"));
    cancel_textbutton->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesWeaponScene::BuyCanel));
    
    UITextButton* ok_textbutton = dynamic_cast<UITextButton*>(buy_root->getChildByName("ok_textbutton"));
    ok_textbutton->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesWeaponScene::BuyOk));
}

void CocosGUIExamplesWeaponScene::BuyLogic(CCObject *pSender)
{
    Layout* weapon_item = dynamic_cast<Layout*>(pSender);
    
    Layout* buy_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("buy_root"));
    buy_root->setVisible(true);
    
    UIImageView* weapon_imageview = dynamic_cast<UIImageView*>(buy_root->getChildByName("alert_imageview"));
    weapon_imageview->setTexture(CCString::createWithFormat("cocosgui/gui_examples/weapon_introduce_1/weapon_item_1/weapons/weapons_%d.png",
                                                            weapon_item->getWidgetTag() - WEAPON_ITEM_LAYOUT_TAG + 1)->getCString());
    weapon_imageview->setScale(0.6f);
    
    UITextArea* text_textarea = dynamic_cast<UITextArea*>(buy_root->getChildByName("text_textarea"));
    text_textarea->setColor(ccBLACK);
    text_textarea->setText(CCString::createWithFormat("Buy %s ?",
                                                      weapon_introduce_text[weapon_item->getWidgetTag() - WEAPON_ITEM_LAYOUT_TAG])->getCString());
}

void CocosGUIExamplesWeaponScene::BuyCanel(CCObject *pSender)
{
    Layout* buy_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("buy_root"));
    buy_root->setVisible(false);
}

void CocosGUIExamplesWeaponScene::BuyOk(CCObject *pSender)
{
    Layout* buy_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("buy_root"));
    buy_root->setVisible(false);
}
