/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include <string>
#include <vector>

#include "ExtensionMacros.h"
#include "editor-support/cocostudio/CocosStudioExport.h"
#include "platform/CCPlatformMacros.h"
#include "ui/UIWidget.h"

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
    struct BlendFrame;
}

namespace tinyxml2
{
    class XMLElement;
}

namespace cocostudio {
    
class CC_STUDIO_DLL FlatBuffersSerialize
{
    
public:
    static FlatBuffersSerialize* getInstance();
    /** @deprecated Use method destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purge();
    static void destroyInstance();
    
    FlatBuffersSerialize();
    ~FlatBuffersSerialize();
    
    void deleteFlatBufferBuilder();
    
    std::string test(const std::string& xmlFileName,
                     const std::string& flatbuffersFileName);
    
    /* serialize flat buffers with XML */
    std::string serializeFlatBuffersWithXMLFile(const std::string& xmlFileName,
                                                const std::string& flatbuffersFileName);

    // NodeTree
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTree(const tinyxml2::XMLElement* objectData,
                                                              std::string classType);
    
    // NodeAction
    flatbuffers::Offset<flatbuffers::NodeAction> createNodeAction(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLine> createTimeLine(const tinyxml2::XMLElement* objectData);    
    flatbuffers::Offset<flatbuffers::PointFrame> createPointFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::ScaleFrame> createScaleFrame(const tinyxml2::XMLElement* objectData);    
    flatbuffers::Offset<flatbuffers::ColorFrame> createColorFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TextureFrame> createTextureFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::EventFrame> createEventFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::IntFrame> createIntFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::BoolFrame> createBoolFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::InnerActionFrame> createInnerActionFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::BlendFrame> createBlendFrame(const tinyxml2::XMLElement* objectData);
    
    flatbuffers::Offset<flatbuffers::EasingData> createEasingData(const tinyxml2::XMLElement* objectData);

    //Animation Info
    flatbuffers::Offset<flatbuffers::AnimationInfo> createAnimationInfo(const tinyxml2::XMLElement* objectData);
    /**/
    
    int getResourceType(std::string key);
    std::string getGUIClassName(const std::string &name);
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    /* create flat buffers with XML */
    flatbuffers::FlatBufferBuilder* createFlatBuffersWithXMLFileForSimulator(const std::string& xmlFileName);
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTreeForSimulator(const tinyxml2::XMLElement* objectData,
                                                                          std::string classType);
    flatbuffers::Offset<flatbuffers::ProjectNodeOptions> createProjectNodeOptionsForSimulator(const tinyxml2::XMLElement* objectData);
	/**/
    std::string getCsdVersion() { return _csdVersion; }

    /* Serialize language XML file to Flat Buffers file. */
    std::string serializeFlatBuffersWithXMLFileForLanguageData(const std::string& xmlFilePath,
                                                               const std::string& flatBuffersFilePath,
                                                               const std::string& languageName);
    
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
