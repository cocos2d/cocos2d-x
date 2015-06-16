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

#ifndef __cocos2d_libs__FlatBuffersSerialize__
#define __cocos2d_libs__FlatBuffersSerialize__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "cocostudio/CocosStudioExport.h"

namespace flatbuffers
{
    class FlatBufferBuilder;
    template<typename T> struct Offset;
    struct String;
    
    struct CSParseBinary;
    struct NodeTree;
    
    struct WidgetOptions;
    
    struct SingleNodeOptions;
    struct SpriteOptions;
    struct ParticleSystemOptions;
    struct TMXTiledMapOptions;
    
    struct ButtonOptions;
    struct CheckBoxOptions;
    struct ImageViewOptions;
    struct TextBMFontOptions;
    struct TextOptions;
    struct TextFieldOptions;
    struct LoadingBarOptions;
    struct SliderOptions;
    struct PanelOptions;
    struct ScrollViewOptions;
    struct PageViewOptions;
    struct ListViewOptions;
    
    struct ProjectNodeOptions;
    
    struct ComponentOptions;
    struct ComAudioOptions;
    
    struct TextAtlasOptions;
    
    struct NodeAction;
    struct AnimationInfo;
    struct TimeLine;
    struct Frame;
    struct PointFrame;
    struct ScaleFrame;
    struct ColorFrame;
    struct TextureFrame;
    struct EventFrame;
    struct IntFrame;
    struct BoolFrame;
    struct InnerActionFrame;
    struct EasingData;
}

namespace tinyxml2
{
    class XMLElement;
}

namespace cocostudio {
    
class CC_STUDIO_DLL FlatBuffersSerialize
{
    
public:
    /**
    * @~english Gets the static instance of FlatBuffersSerialize.
    * @~chinese 获取FlatBuffersSerialize的静态实例.
    */
    static FlatBuffersSerialize* getInstance();
    /**
    * @~english Destroy FlatBuffersSerialize static instance.
    * @~chinese 释放FlatBuffersSerialize的静态实例.
    */
    static void destroyInstance();

    /** 
    * @deprecated @~english Use method destroyInstance() instead @~chinese 已弃用，请使用destroyInstance()
    */
    CC_DEPRECATED_ATTRIBUTE static void purge();

    FlatBuffersSerialize();
    ~FlatBuffersSerialize();

    /**
    * @~english Destroy FlatBufferBuilder instance.
    * @~chinese 释放FlatBufferBuilder的静态实例.
    */
    void deleteFlatBufferBuilder();

    /**
    * @~english Serialize flat buffers with XML.
    * @~chinese 根据xml数据序列化flat buffer.
    *
    * @parame xmlFileName           @~english input xml file name @~chinese xml文件名称
    *
    * @parame flatbuffersFileName   @~english output flatbuffer file name @~chinese 输出的flat buffer文件名
    *
    * @return @~english error message @~chinese 错误信息
    */
    std::string serializeFlatBuffersWithXMLFile(const std::string& xmlFileName,
                                                const std::string& flatbuffersFileName);

    /**
    * @~english Create node tree flatbuffer from xml object
    * @~chinese 根据xml数据创建flat buffer节点树
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @parame classType   @~english root node class type @~chinese 根节点类型
    *
    * @return @~english error message @~chinese 错误信息
    */
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTree(const tinyxml2::XMLElement* objectData,
                                                              std::string classType);
    
    /**
    * @~english Create node action flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式节点动作描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::NodeAction> createNodeAction(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create time line flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式时间轴描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::TimeLine> createTimeLine(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create point frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式point帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::PointFrame> createPointFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create scale frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式缩放帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::ScaleFrame> createScaleFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create color frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式颜色帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::ColorFrame> createColorFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create texture frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式材质帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::TextureFrame> createTextureFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create event frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式事件帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::EventFrame> createEventFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create int frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式整型帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::IntFrame> createIntFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create bool frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式布尔型帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::BoolFrame> createBoolFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create inner action frame flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式嵌套帧描述
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::InnerActionFrame> createInnerActionFrame(const tinyxml2::XMLElement* objectData);
    
    /**
    * @~english Create easing data flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式缓动数据
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::EasingData> createEasingData(const tinyxml2::XMLElement* objectData);

    /**
    * @~english Create animation info flatbuffer from xml object
    * @~chinese 根据xml节点创建flat buffer格式动画数据
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml格式描述数据
    *
    * @return @~english flatbuffer object @~chinese flat buffer对象
    */
    flatbuffers::Offset<flatbuffers::AnimationInfo> createAnimationInfo(const tinyxml2::XMLElement* objectData);
    /**/

    /**
    * @~english Get resource type embed default or user added
    * @~chinese 获取资源类型：编辑器自带默认资源/用户添加资源
    *
    * @parame key  @~english resource type key @~chinese 资源类型键值
    *
    * @return @~english resource type @~chinese 资源类型
    */
    int getResourceType(std::string key);
    /**
    * @~english Get GUI widget class type of a special component
    * @~chinese 获取指定组件的UI组件类型
    *
    * @parame name  @~english component class name @~chinese 组件类名称
    *
    * @return @~english widget class name @~chinese UI组件类名
    */
    std::string getGUIClassName(const std::string &name);
    /**
    * @~english Get GUI widget reader class name or a special widget
    * @~chinese 获取指定UI组件的reader类名
    *
    * @parame widget  @~english UI widget component @~chinese UI组件
    *
    * @return @~english widget reader class name @~chinese UI组件reader类名
    */
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    /**
    * @~english Choose flat buffer builder that can convert current xml project file to flat buffer data for simulator use
    * @~chinese 选择可以将当前xml项目文件转换成供模拟器使用数据的flat buffer构造器
    *
    * @parame xmlFileName  @~english xml project file @~chinese xml项目文件
    *
    * @return @~english flat buffer builder @~chinese flat buffer构造器
    */
    flatbuffers::FlatBufferBuilder* createFlatBuffersWithXMLFileForSimulator(const std::string& xmlFileName);
    /**
    * @~english Convert xml project object to flat buffer data for simulator use
    * @~chinese 将xml项目对象转换为flat buffer数据供模拟器使用
    *
    * @parame objectData  @~english xml project object @~chinese xml项目对象
    *
    * @parame classType   @~english root node class type @~chinese 根节点类型
    *
    * @return @~english flat buffer data @~chinese flat buffer数据
    */
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTreeForSimulator(const tinyxml2::XMLElement* objectData,
                                                                          std::string classType);
    /**
    * @~english Convert xml project object to flat buffer data for simulator use
    * @~chinese 将xml项目对象转换为flat buffer数据供模拟器使用
    *
    * @parame objectData  @~english xml project object @~chinese xml项目对象
    *
    * @return @~english flat buffer data @~chinese flat buffer数据
    */
    flatbuffers::Offset<flatbuffers::ProjectNodeOptions> createProjectNodeOptionsForSimulator(const tinyxml2::XMLElement* objectData);
	/** 
    * @~english Get csd format version
    * @~chinese 获取csd格式版本
    *
    * ·return @~english csd version @~chinese csd 版本
    */
    std::string getCsdVersion() { return _csdVersion; }
    
public:
    std::vector<flatbuffers::Offset<flatbuffers::String>> _textures;
    std::vector<flatbuffers::Offset<flatbuffers::String>> _texturePngs;
    bool _isSimulator;
    
private:
    flatbuffers::FlatBufferBuilder* _builder;
    flatbuffers::Offset<flatbuffers::CSParseBinary>* _csparsebinary;
    std::string _csdVersion;
};
}

#endif /* defined(__cocos2d_libs__FlatBuffersSerialize__) */
