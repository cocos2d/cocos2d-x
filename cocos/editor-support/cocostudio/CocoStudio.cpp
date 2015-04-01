
#include "CocoStudio.h"

#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "cocostudio/WidgetReader/ParticleReader/ParticleReader.h"
#include "cocostudio/WidgetReader/GameMapReader/GameMapReader.h"
#include "cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"
#include "cocostudio/WidgetReader/ComAudioReader/ComAudioReader.h"

#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "cocostudio/WidgetReader/ImageViewReader/ImageViewReader.h"
#include "cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "cocostudio/WidgetReader/TextReader/TextReader.h"
#include "cocostudio/WidgetReader/TextFieldReader/TextFieldReader.h"
#include "cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "cocostudio/WidgetReader/SliderReader/SliderReader.h"
#include "cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "cocostudio/WidgetReader/PageViewReader/PageViewReader.h"
#include "cocostudio/WidgetReader/ListViewReader/ListViewReader.h"
#include "cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.h"
#include "cocostudio/WidgetReader/Node3DReader/Node3DReader.h"
#include "cocostudio/WidgetReader/Sprite3DReader/Sprite3DReader.h"
#include "cocostudio/WidgetReader/UserCameraReader/UserCameraReader.h"
#include "cocostudio/WidgetReader/Particle3DReader/Particle3DReader.h"


namespace cocostudio
{
    void destroyCocosStudio()
    {        
        NodeReader::destroyInstance();
        SingleNodeReader::destroyInstance();
        SpriteReader::destroyInstance();
        ParticleReader::destroyInstance();
        GameMapReader::destroyInstance();
        ProjectNodeReader::destroyInstance();
        ComAudioReader::destroyInstance();
        
        WidgetReader::destroyInstance();
        ButtonReader::destroyInstance();
        CheckBoxReader::destroyInstance();
        ImageViewReader::destroyInstance();
        TextBMFontReader::destroyInstance();
        TextReader::destroyInstance();
        TextFieldReader::destroyInstance();
        TextAtlasReader::destroyInstance();
        LoadingBarReader::destroyInstance();
        SliderReader::destroyInstance();
        LayoutReader::destroyInstance();
        ScrollViewReader::destroyInstance();
        PageViewReader::destroyInstance();
        ListViewReader::destroyInstance();
        
        ArmatureNodeReader::destroyInstance();
        Node3DReader::destroyInstance();
        Sprite3DReader::destroyInstance();
        UserCameraReader::destroyInstance();
        Particle3DReader::destroyInstance();
        
        cocos2d::CSLoader::destroyInstance();
        
        
        ArmatureDataManager::destroyInstance();
        SceneReader::destroyInstance();
        ActionManagerEx::destroyInstance();
        GUIReader::destroyInstance();
    }
}