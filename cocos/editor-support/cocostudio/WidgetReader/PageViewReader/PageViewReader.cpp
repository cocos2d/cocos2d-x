

#include "PageViewReader.h"
#include "ui/UIPageView.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoLoader.h"
#include "../../CSParseBinary.pb.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static PageViewReader* instancePageViewReader = nullptr;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(PageViewReader)
    
    PageViewReader::PageViewReader()
    {
        
    }
    
    PageViewReader::~PageViewReader()
    {
        
    }
    
    PageViewReader* PageViewReader::getInstance()
    {
        if (!instancePageViewReader)
        {
            instancePageViewReader = new PageViewReader();
        }
        return instancePageViewReader;
    }
    
    void PageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
	{
		LayoutReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
    }
    
    void PageViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
    }
    
    void PageViewReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        
        PageView* pageView = static_cast<PageView*>(widget);
        const protocolbuffers::PageViewOptions& options = nodeTree.pageviewoptions();

		/* peterson */
		std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
		/**/
        
        CCLOG("options.clipable() = %d", options.clipable());
        pageView->setClippingEnabled(options.clipable());
        
        bool backGroundScale9Enable = options.backgroundscale9enable();
        pageView->setBackGroundImageScale9Enabled(backGroundScale9Enable);
        
        
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
        cb = options.has_bgcolorb() ? options.bgcolorb() : 150;
        
        scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
        scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
        scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
        
        ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 255;
        ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 150;
        ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 100;
        
        float bgcv1 = options.vectorx();
        float bgcv2 = options.has_vectory() ? options.vectory() : -0.5f;
        pageView->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        int co = options.has_bgcoloropacity() ? options.bgcoloropacity() : 100;
        
        int colorType = options.has_colortype() ? options.colortype() : 1;
        pageView->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        
        pageView->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        pageView->setBackGroundColor(Color3B(cr, cg, cb));
        pageView->setBackGroundColorOpacity(co);
        
        
		const protocolbuffers::ResourceData& imageFileNameDic = options.backgroundimagedata();
        int imageFileNameType = imageFileNameDic.resourcetype();
		/* peterson */
		if (imageFileNameType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + imageFileNameDic.plistfile());			
		}
		/**/
        std::string imageFileName = this->getResourcePath(imageFileNameDic.path(), (Widget::TextureResType)imageFileNameType);
        pageView->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        if (backGroundScale9Enable)
        {
            float cx = options.capinsetsx();
            float cy = options.capinsetsy();
            float cw = options.has_capinsetswidth() ? options.capinsetswidth() : 1;
            float ch = options.has_capinsetsheight() ? options.capinsetsheight() : 1;
            pageView->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
            bool sw = options.has_scale9width();
            bool sh = options.has_scale9height();
            if (sw && sh)
            {
                float swf = options.scale9width();
                float shf = options.scale9height();
                pageView->setContentSize(Size(swf, shf));
            }
        }
        
        const protocolbuffers::WidgetOptions& widgetOptions = nodeTree.widgetoptions();
        int bgimgcr = widgetOptions.has_colorr() ? widgetOptions.colorr() : 255;
        int bgimgcg = widgetOptions.has_colorg() ? widgetOptions.colorg() : 255;
        int bgimgcb = widgetOptions.has_colorb() ? widgetOptions.colorb() : 255;
        pageView->setBackGroundImageColor(Color3B(bgimgcr, bgimgcg, bgimgcb));
        
        int bgimgopacity = widgetOptions.has_opacity() ? widgetOptions.opacity() : 255;
        pageView->setBackGroundImageOpacity(bgimgopacity);
        
        
        // other commonly protperties
        setAnchorPointForWidget(widget, nodeTree);
        
        bool flipX = widgetOptions.flipx();
        bool flipY = widgetOptions.flipy();
        widget->setFlippedX(flipX);
        widget->setFlippedY(flipY);
    }
}
