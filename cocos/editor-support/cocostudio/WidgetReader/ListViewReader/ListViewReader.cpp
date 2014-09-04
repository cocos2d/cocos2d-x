

#include "ListViewReader.h"
#include "ui/UIListView.h"
#include "cocostudio/CocoLoader.h"
#include "../../CSParseBinary.pb.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_Direction = "direction";
    static const char* P_ItemMargin = "itemMargin";
    
    static ListViewReader* instanceListViewReader = nullptr;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(ListViewReader)
    
    ListViewReader::ListViewReader()
    {
        
    }
    
    ListViewReader::~ListViewReader()
    {
        
    }
    
    ListViewReader* ListViewReader::getInstance()
    {
        if (!instanceListViewReader)
        {
            instanceListViewReader = new ListViewReader();
        }
        return instanceListViewReader;
    }
    
    void ListViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode* cocoNode)
    {
        ScrollViewReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        ListView* listView = static_cast<ListView*>(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            if (key == P_Direction) {
                listView->setDirection((ScrollView::Direction)valueToInt(value));
            }
            else if(key == P_Gravity){
                listView->setGravity((ListView::Gravity)valueToInt(value));
            }else if(key == P_ItemMargin){
                listView->setItemsMargin(valueToFloat(value));
            }
            
        } //end of for loop
    }
    
    void ListViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        ScrollViewReader::setPropsFromJsonDictionary(widget, options);
        
        
        ListView* listView = static_cast<ListView*>(widget);
                
        int direction = DICTOOL->getFloatValue_json(options, P_Direction,2);
        listView->setDirection((ScrollView::Direction)direction);
        
        ListView::Gravity gravity = (ListView::Gravity)DICTOOL->getIntValue_json(options, P_Gravity,3);
        listView->setGravity(gravity);
        
        float itemMargin = DICTOOL->getFloatValue_json(options, P_ItemMargin);
        listView->setItemsMargin(itemMargin);
    }
    
    void ListViewReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        
        
        ListView* listView = static_cast<ListView*>(widget);
        const protocolbuffers::ListViewOptions& options = nodeTree.listviewoptions();

		/* peterson */
		std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
		/**/
        
        listView->setClippingEnabled(options.clipable());
        
        bool backGroundScale9Enable = options.backgroundscale9enable();
        listView->setBackGroundImageScale9Enabled(backGroundScale9Enable);
        
        
        int cr;
        int cg;
        int cb;
        int scr;
        int scg;
        int scb;
        int ecr;
        int ecg;
        int ecb;
        
        
        
        cr = options.has_bgcolorr() ? options.bgcolorr() : 150;
        cg = options.has_bgcolorg() ? options.bgcolorg() : 150;
        cb = options.has_bgcolorb() ? options.bgcolorb() : 255;
        
        scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
        scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
        scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
        
        ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 150;
        ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 150;
        ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 255;
        
        float bgcv1 = options.vectorx();
        float bgcv2 = options.has_vectory() ? options.vectory() : -0.5f;
        listView->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        int co = options.has_bgcoloropacity() ? options.bgcoloropacity() : 100;
        
        int colorType = options.has_colortype() ? options.colortype() : 1;
        listView->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        
        listView->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        listView->setBackGroundColor(Color3B(cr, cg, cb));
        listView->setBackGroundColorOpacity(co);
        
        
		const protocolbuffers::ResourceData& imageFileNameDic = options.backgroundimagedata();
        int imageFileNameType = imageFileNameDic.resourcetype();
		/* peterson */
		if (imageFileNameType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + imageFileNameDic.plistfile());			
		}
		/**/
        std::string imageFileName = this->getResourcePath(imageFileNameDic.path(), (Widget::TextureResType)imageFileNameType);
        listView->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        if (backGroundScale9Enable)
        {
            float cx = options.capinsetsx();
            float cy = options.capinsetsy();
            float cw = options.has_capinsetswidth() ? options.capinsetswidth() : 1;
            float ch = options.has_capinsetsheight() ? options.capinsetsheight() : 1;
            listView->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
        }
        
        const protocolbuffers::WidgetOptions& widgetOptions = nodeTree.widgetoptions();
        int bgimgcr = widgetOptions.has_colorr() ? widgetOptions.colorr() : 255;
        int bgimgcg = widgetOptions.has_colorg() ? widgetOptions.colorg() : 255;
        int bgimgcb = widgetOptions.has_colorb() ? widgetOptions.colorb() : 255;
        listView->setBackGroundImageColor(Color3B(bgimgcr, bgimgcg, bgimgcb));
        
        int bgimgopacity = widgetOptions.has_opacity() ? widgetOptions.opacity() : 255;
        listView->setBackGroundImageOpacity(bgimgopacity);
        
        
        
        
        
        float innerWidth = options.has_innerwidth() ? options.innerwidth() : 200;
        float innerHeight = options.has_innerheight() ? options.innerheight() : 200;
        listView->setInnerContainerSize(Size(innerWidth, innerHeight));
        listView->setBounceEnabled(options.bounceenable());
        
        int direction = options.has_direction() ? options.direction() : 2;
        listView->setDirection((ScrollView::Direction)direction);
        
        int gravityValue = options.has_gravity() ? options.gravity() : 3;
        ListView::Gravity gravity = (ListView::Gravity)gravityValue;
        listView->setGravity(gravity);
        
        float itemMargin = options.itemmargin();
        listView->setItemsMargin(itemMargin);
        
        
        // other commonly protperties
        setAnchorPointForWidget(widget, nodeTree);
        
        bool flipX = widgetOptions.flipx();
        bool flipY = widgetOptions.flipy();
        widget->setFlippedX(flipX);
        widget->setFlippedY(flipY);
    }
}

