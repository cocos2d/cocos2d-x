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
#include "tinyxml2/tinyxml2.h"

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
    struct TimeLine;
    struct Frame;
    struct TimeLineBoolFrame;
    struct TimeLineIntFrame;
    struct TimeLineStringFrame;
    struct TimeLinePointFrame;
    struct TimeLineColorFrame;
    struct TimeLineTextureFrame;
}

namespace cocostudio {

class CC_STUDIO_DLL FlatBuffersSerialize
{
    
public:
    
    FlatBuffersSerialize();
    ~FlatBuffersSerialize();
    
    static FlatBuffersSerialize* getInstance();
    static void purge();
    
    /* serialize flat buffers with XML */
    std::string serializeFlatBuffersWithXMLFile(const std::string& xmlFileName,
                                                const std::string& flatbuffersFileName);
    
    // NodeTree
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTree(const tinyxml2::XMLElement* objectData,
                                                              std::string classType);    
    
    // NodeAction
    flatbuffers::Offset<flatbuffers::NodeAction> createNodeAction(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLine> createTimeLine(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLineBoolFrame> createTimeLineBoolFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLineIntFrame> createTimeLineIntFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLineStringFrame> createTimeLineStringFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLinePointFrame> createTimeLinePointFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLineColorFrame> createTimeLineColorFrame(const tinyxml2::XMLElement* objectData);
    flatbuffers::Offset<flatbuffers::TimeLineTextureFrame> createTimeLineTextureFrame(const tinyxml2::XMLElement* objectData);
    /**/
    
    int getResourceType(std::string key);
    std::string getGUIClassName(const std::string &name);
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
public:
    std::vector<flatbuffers::Offset<flatbuffers::String>> _textures;
    std::vector<flatbuffers::Offset<flatbuffers::String>> _texturePngs;
    bool _isSimulator;
    
private:
    flatbuffers::FlatBufferBuilder* _builder;
    flatbuffers::Offset<flatbuffers::CSParseBinary>* _csparsebinary;
    
};
    
}

#endif /* defined(__cocos2d_libs__FlatBuffersSerialize__) */
