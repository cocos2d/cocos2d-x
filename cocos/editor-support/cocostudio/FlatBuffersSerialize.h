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
    * Gets the static instance of FlatBuffersSerialize.
    */
    static FlatBuffersSerialize* getInstance();
    /**
    * Destroy FlatBuffersSerialize instance.
    */
    static void destroyInstance();

    /** @deprecated Use method destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purge();

    FlatBuffersSerialize();
    ~FlatBuffersSerialize();

    /**
    * Destroy FlatBufferBuilder instance.
    */
    void deleteFlatBufferBuilder();

    //std::string test(const std::string& xmlFileName,
    //                 const std::string& flatbuffersFileName);

    /**
    * Serialize flat buffers with XML.
    *
    * @parame xmlFileName           input xml file name
    *
    * @parame flatbuffersFileName   output flatbuffer file name
    *
    * @return error message
    */
    std::string serializeFlatBuffersWithXMLFile(const std::string& xmlFileName,
                                                const std::string& flatbuffersFileName);
    
    // NodeTree
    /**
    * Create node tree flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @parame classType   root node class type
    *
    * @return error message
    */
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTree(const tinyxml2::XMLElement* objectData,
                                                              std::string classType);
    
    // NodeAction
    /**
    * Create node action flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::NodeAction> createNodeAction(const tinyxml2::XMLElement* objectData);
    /**
    * Create time line flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::TimeLine> createTimeLine(const tinyxml2::XMLElement* objectData);
    /**
    * Create point frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::PointFrame> createPointFrame(const tinyxml2::XMLElement* objectData);
    /**
    * Create scale frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::ScaleFrame> createScaleFrame(const tinyxml2::XMLElement* objectData);
    /**
    * Create color frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::ColorFrame> createColorFrame(const tinyxml2::XMLElement* objectData);
    /**
    * Create texture frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::TextureFrame> createTextureFrame(const tinyxml2::XMLElement* objectData);
    /**
    * Create event frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::EventFrame> createEventFrame(const tinyxml2::XMLElement* objectData);
    /**
    * Create int frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::IntFrame> createIntFrame(const tinyxml2::XMLElement* objectData);
    /**
    * Create bool frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::BoolFrame> createBoolFrame(const tinyxml2::XMLElement* objectData);
    /**
    * Create inner action frame flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::InnerActionFrame> createInnerActionFrame(const tinyxml2::XMLElement* objectData);
    
    /**
    * Create easing data flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::EasingData> createEasingData(const tinyxml2::XMLElement* objectData);

    //Animation Info
    /**
    * Create animation info flatbuffer from xml object
    *
    * @parame objectData  xml descriptoin object
    *
    * @return flatbuffer object
    */
    flatbuffers::Offset<flatbuffers::AnimationInfo> createAnimationInfo(const tinyxml2::XMLElement* objectData);
    /**/

    /**
    * Get resource type embed default or user added
    *
    * @parame key  resource type key
    *
    * @return resource type
    */
    int getResourceType(std::string key);
    /**
    * Get GUI widget class type of a special component
    *
    * @parame name  component class name
    *
    * @return widget class name
    */
    std::string getGUIClassName(const std::string &name);
    /**
    * Get GUI widget reader class name or a special widget
    *
    * @parame widget  UI widget component
    *
    * @return widget reader class name
    */
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    /* create flat buffers with XML */
    /**
    * Choose flat buffer builder that can convert current xml project file to flat buffer data for simulator use
    *
    * @parame xmlFileName  xml project file
    *
    * @return flat buffer builder
    */
    flatbuffers::FlatBufferBuilder* createFlatBuffersWithXMLFileForSimulator(const std::string& xmlFileName);
    /**
    * Convert xml project object to flat buffer data for simulator use
    *
    * @parame objectData  xml project object
    *
    * @parame classType   root node class type
    *
    * @return flat buffer data
    */
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTreeForSimulator(const tinyxml2::XMLElement* objectData,
                                                                          std::string classType);
    /**
    * Convert xml project object to flat buffer data for simulator use
    *
    * @parame objectData  xml project object
    *
    * @return flat buffer data
    */
    flatbuffers::Offset<flatbuffers::ProjectNodeOptions> createProjectNodeOptionsForSimulator(const tinyxml2::XMLElement* objectData);
	/* Get csd format version */
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
