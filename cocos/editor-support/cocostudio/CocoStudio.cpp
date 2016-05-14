
#include "editor-support/cocostudio/CocoStudio.h"

#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "editor-support/cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "editor-support/cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "editor-support/cocostudio/WidgetReader/ParticleReader/ParticleReader.h"
#include "editor-support/cocostudio/WidgetReader/GameMapReader/GameMapReader.h"
#include "editor-support/cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"
#include "editor-support/cocostudio/WidgetReader/ComAudioReader/ComAudioReader.h"

#include "editor-support/cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "editor-support/cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "editor-support/cocostudio/WidgetReader/ImageViewReader/ImageViewReader.h"
#include "editor-support/cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "editor-support/cocostudio/WidgetReader/TextReader/TextReader.h"
#include "editor-support/cocostudio/WidgetReader/TextFieldReader/TextFieldReader.h"
#include "editor-support/cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "editor-support/cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "editor-support/cocostudio/WidgetReader/SliderReader/SliderReader.h"
#include "editor-support/cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "editor-support/cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "editor-support/cocostudio/WidgetReader/PageViewReader/PageViewReader.h"
#include "editor-support/cocostudio/WidgetReader/ListViewReader/ListViewReader.h"
#include "editor-support/cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.h"
#include "editor-support/cocostudio/WidgetReader/Node3DReader/Node3DReader.h"
#include "editor-support/cocostudio/WidgetReader/Sprite3DReader/Sprite3DReader.h"
#include "editor-support/cocostudio/WidgetReader/UserCameraReader/UserCameraReader.h"
#include "editor-support/cocostudio/WidgetReader/Particle3DReader/Particle3DReader.h"


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