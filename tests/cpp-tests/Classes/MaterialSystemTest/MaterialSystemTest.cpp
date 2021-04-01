/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "MaterialSystemTest.h"

#include <ctime>
#include <spine/spine-cocos2dx.h>

#include "../testResource.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

static void printProperties(Properties* properties, int indent);


// MARK: Tests

MaterialSystemTest::MaterialSystemTest()
{
    ADD_TEST_CASE(Material_2DEffects);
    ADD_TEST_CASE(Material_AutoBindings);
    ADD_TEST_CASE(Material_setTechnique);
    ADD_TEST_CASE(Material_clone);
    ADD_TEST_CASE(Material_MultipleSprite3D);
    ADD_TEST_CASE(Material_Sprite3DTest);
    ADD_TEST_CASE(Material_parsePerformance);
}

std::string MaterialSystemBaseTest::title() const
{
    return "Material System";
}

// MARK: Tests start here

void Material_Sprite3DTest::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(8.f);
    sprite->setTexture("Sprite3DTest/boss.png");
    this->addChild(sprite);
    sprite->setPositionNormalized(Vec2(0.5f,0.5f));
}

std::string Material_Sprite3DTest::subtitle() const
{
    return "Material System on Sprite3D";
}

void Material_MultipleSprite3D::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    const char* names[] = {
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
    };

    const int totalNames = sizeof(names) / sizeof(names[0]);

    auto size = Director::getInstance()->getWinSize();

    for(int i=0;i<totalNames;i++)
    {
        auto sprite = Sprite3D::create(names[i]);
        this->addChild(sprite);
        sprite->setPosition(Vec2((size.width/(totalNames+1))*(i+1), size.height/4));
        sprite->setScale(3);
    }
}

std::string Material_MultipleSprite3D::subtitle() const
{
    return "Sprites with multiple meshes";
}

//
// MARK: Material_2DEffects
//
void Material_2DEffects::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto properties = Properties::createNonRefCounted("Materials/2d_effects.material#sample");

    // Print the properties of every namespace within this one.
    printProperties(properties, 0);

    Material *mat1 = Material::createWithProperties(properties);

    auto spriteBlur = Sprite::create("Images/grossini.png");
    spriteBlur->setPositionNormalized(Vec2(0.2f, 0.5f));
    this->addChild(spriteBlur);
    spriteBlur->setProgramState(mat1->getTechniqueByName("blur")->getPassByIndex(0)->getProgramState());

    auto spriteOutline = Sprite::create("Images/grossini.png");
    spriteOutline->setPositionNormalized(Vec2(0.4f, 0.5f));
    this->addChild(spriteOutline);
    spriteOutline->setProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getProgramState());

    auto spriteNoise = Sprite::create("Images/grossini.png");
    spriteNoise->setPositionNormalized(Vec2(0.6f, 0.5f));
    this->addChild(spriteNoise);
    spriteNoise->setProgramState(mat1->getTechniqueByName("noise")->getPassByIndex(0)->getProgramState());

    auto spriteEdgeDetect = Sprite::create("Images/grossini.png");
    spriteEdgeDetect->setPositionNormalized(Vec2(0.8f, 0.5f));
    this->addChild(spriteEdgeDetect);
    spriteEdgeDetect->setProgramState(mat1->getTechniqueByName("edge_detect")->getPassByIndex(0)->getProgramState());

    timeUniforms.clear();

#define FETCH_CCTIME_LOCATION(sprite) do {                                  \
        auto programState = sprite->getProgramState();                      \
        auto location     = programState->getUniformLocation("u_Time");    \
        timeUniforms.emplace_back(programState, location);                  \
    }while(0)

    FETCH_CCTIME_LOCATION(spriteBlur);
    FETCH_CCTIME_LOCATION(spriteOutline);
    FETCH_CCTIME_LOCATION(spriteNoise);
    FETCH_CCTIME_LOCATION(spriteEdgeDetect);

    schedule(CC_SCHEDULE_SELECTOR(Material_2DEffects::updateCCTimeUniforms));

    // properties is not a "Ref" object
    CC_SAFE_DELETE(properties);
}

std::string Material_2DEffects::subtitle() const
{
    return "Testing effects on Sprite";
}

void Material_2DEffects::updateCCTimeUniforms(float)
{
    float time = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();
    Vec4 random(time / 10.0f, time, time * 2.0f, time * 4.0f);
    for (auto &loc : timeUniforms)
    {
        loc.programState->setUniform(loc.location, &random, sizeof(random));
    }
}

//
// MARK: Material_AutoBindings
//

/*
 * Custom material auto-binding resolver for terrain.
 */
class EffectAutoBindingResolver : public backend::ProgramState::AutoBindingResolver
{
    virtual bool resolveAutoBinding(backend::ProgramState* programState,/* Node* node,*/ const std::string& uniform, const std::string& autoBinding) override;

    void callbackRadius(backend::ProgramState* programState, backend::UniformLocation uniform);
    void callbackColor(backend::ProgramState* programState, backend::UniformLocation uniform);
};

bool EffectAutoBindingResolver::resolveAutoBinding(backend::ProgramState* programState, /*Node* node,*/ const std::string& uniform, const std::string& autoBinding)
{
    if (autoBinding.compare("DYNAMIC_RADIUS")==0)
    {
        auto loc = programState->getUniformLocation(uniform);
        programState->setCallbackUniform(loc, CC_CALLBACK_2(EffectAutoBindingResolver::callbackRadius, this));
        return true;
    }
    else if (autoBinding.compare("OUTLINE_COLOR")==0)
    {
        auto loc = programState->getUniformLocation(uniform);
        programState->setCallbackUniform(loc, CC_CALLBACK_2(EffectAutoBindingResolver::callbackColor, this));
        return true;
    }
    return false;
}

void EffectAutoBindingResolver::callbackRadius(backend::ProgramState *programState, backend::UniformLocation uniform)
{
    float f = CCRANDOM_0_1() * 10;
    programState->setUniform(uniform, &f, sizeof(f));
}

void EffectAutoBindingResolver::callbackColor(backend::ProgramState *programState, backend::UniformLocation uniform)
{
    float r = CCRANDOM_0_1();
    float g = CCRANDOM_0_1();
    float b = CCRANDOM_0_1();
    Vec3 color(r, g, b);

    programState->setUniform(uniform, &color, sizeof(color));
}

Material_AutoBindings::Material_AutoBindings()
{
    _resolver = new EffectAutoBindingResolver;
}

Material_AutoBindings::~Material_AutoBindings()
{
    delete _resolver;
}


void Material_AutoBindings::onEnter()
{
    MaterialSystemBaseTest::onEnter();

//    auto properties = Properties::createNonRefCounted("Materials/2d_effects.material#sample");
    auto properties = Properties::createNonRefCounted("Materials/auto_binding_test.material#sample");

    // Print the properties of every namespace within this one.
    printProperties(properties, 0);

    Material *mat1 = Material::createWithProperties(properties);

    auto spriteBlur = Sprite::create("Images/grossini.png");
    spriteBlur->setPositionNormalized(Vec2(0.2f, 0.5f));
    this->addChild(spriteBlur);
    spriteBlur->setProgramState(mat1->getTechniqueByName("blur")->getPassByIndex(0)->getProgramState());

    auto spriteOutline = Sprite::create("Images/grossini.png");
    spriteOutline->setPositionNormalized(Vec2(0.4f, 0.5f));
    this->addChild(spriteOutline);
    spriteOutline->setProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getProgramState());

    auto spriteNoise = Sprite::create("Images/grossini.png");
    spriteNoise->setPositionNormalized(Vec2(0.6f, 0.5f));
    this->addChild(spriteNoise);
    spriteNoise->setProgramState(mat1->getTechniqueByName("noise")->getPassByIndex(0)->getProgramState());

    auto spriteEdgeDetect = Sprite::create("Images/grossini.png");
    spriteEdgeDetect->setPositionNormalized(Vec2(0.8f, 0.5f));
    this->addChild(spriteEdgeDetect);
    spriteEdgeDetect->setProgramState(mat1->getTechniqueByName("edge_detect")->getPassByIndex(0)->getProgramState());

    _noiseProgramState = spriteNoise->getProgramState();
    _locationTime = _noiseProgramState->getUniformLocation("u_Time");
    
    schedule(CC_SCHEDULE_SELECTOR(Material_AutoBindings::updateUniformTime));
    // properties is not a "Ref" object
    CC_SAFE_DELETE(properties);
}

std::string Material_AutoBindings::subtitle() const
{
    return "Testing auto-bindings uniforms";
}

void Material_AutoBindings::updateUniformTime(float dt)
{
    float time = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();
    Vec4 random(time / 10.0f, time, time * 2.0f, time * 4.0f);
    _noiseProgramState->setUniform(_locationTime, &random, sizeof(random));
}

//
//
//
void Material_setTechnique::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(6);
    this->addChild(sprite);
    sprite->setPositionNormalized(Vec2(0.5f,0.5f));
    _sprite = sprite;


    Material *mat = Material::createWithFilename("Materials/3d_effects.material");
    sprite->setMaterial(mat);

    // lights
    auto light1 = AmbientLight::create(Color3B::RED);
    addChild(light1);

    auto light2 = DirectionLight::create(Vec3(-1,1,0), Color3B::GREEN);
    addChild(light2);

    this->schedule(CC_CALLBACK_1(Material_setTechnique::changeMaterial, this),  1, "cookie");
    _techniqueState = 0;

    auto rot = RotateBy::create(5, Vec3(30.0f,60.0f,270.0f));
    auto repeat = RepeatForever::create(rot);
    sprite->runAction(repeat);
}

std::string Material_setTechnique::subtitle() const
{
    return "Testing setTechnique()";
}

void Material_setTechnique::changeMaterial(float dt)
{
    // get it from Mesh 0
    switch (_techniqueState)
    {
        case 0:
            _sprite->getMaterial(0)->setTechnique("lit");
            break;
        case 1:
            _sprite->getMaterial(0)->setTechnique("normal");
            break;
        case 2:
            _sprite->getMaterial(0)->setTechnique("outline");
            break;
        default:
            break;
    }

    _techniqueState = (_techniqueState + 1) % 3;
}

//
//
//
void Material_clone::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(3);
    this->addChild(sprite);
    sprite->setPositionNormalized(Vec2(0.25f, 0.5f));

    Material *mat = Material::createWithFilename("Materials/3d_effects.material");
    sprite->setMaterial(mat);

    auto rot = RotateBy::create(5, Vec3(360.0f,240.0f,120.0f));
    auto repeat = RepeatForever::create(rot);
    sprite->runAction(repeat);

    // sprite 2... using same material
    auto sprite2 = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite2->setScale(3);
    this->addChild(sprite2);
    sprite2->setPositionNormalized(Vec2(0.5f, 0.5f));
    sprite2->setMaterial(mat);
    sprite2->runAction(repeat->clone());

    // sprite 3... using cloned material
    auto sprite3 = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite3->setScale(3);
    this->addChild(sprite3);
    sprite3->setPositionNormalized(Vec2(0.75f, 0.5f));
    auto mat2 = mat->clone();
    sprite3->setMaterial(mat2);
    sprite3->runAction(repeat->clone());

    // testing clone
    // should affect both sprite 1 and sprite 2
    mat->setTechnique("outline");

    // should affect only sprite 3
//    mat2->setTechnique("normal");

}

std::string Material_clone::subtitle() const
{
    return "Testing material->clone()";
}

//
//
//
const int SHOW_LEBAL_TAG = 114;

void Material_parsePerformance::onEnter()
{
    MaterialSystemBaseTest::onEnter();
    
    _maxParsingCoumt = 5e3;
    
    auto screenSize = Director::getInstance()->getWinSize();
    
    ui::Slider* slider = ui::Slider::create();
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPercent(50);
    
    slider->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 3.0f));
    slider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
        
        if (type == ui::Slider::EventType::ON_SLIDEBALL_UP)
        {
            ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
            float p = slider->getPercent() / 100.0f;
            slider->setTouchEnabled(false);
            CCLOG("Will parsing material %d times", (int)(p * _maxParsingCoumt));
            Label* label = dynamic_cast<Label*>(this->getChildByTag(SHOW_LEBAL_TAG));
            if(label)
            {
                label->setString("Testing start!");
            }
            this->scheduleOnce(
                               [this, p, slider](float)
                               {
                                   this->parsingTesting(p * _maxParsingCoumt);
                                   slider->setTouchEnabled(true);
                               },
                               1.0, "schedule test parsing");
            
        }
    });
    
    addChild(slider);
    
    auto label = Label::createWithSystemFont("Max parsing count is 10000, which may crash because of high memory consumption.", "Helvetica", 10);
    label->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f - 20));
    addChild(label);
    label = Label::createWithSystemFont("Slide to test parsing performance", "Helvetica", 10);
    label->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
    addChild(label);
    
    label = Label::createWithSystemFont("", "Helvetica", 10);
    label->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + 20));
    label->setTag(SHOW_LEBAL_TAG);
    addChild(label);

}

void Material_parsePerformance::parsingTesting(unsigned int count)
{
    std::clock_t begin = std::clock();
    
    for (unsigned int i = 0; i < count; i++)
    {
        Material::createWithFilename("Materials/2d_effects.material");
        Material::createWithFilename("Materials/3d_effects.material");
    }
    
    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    Label* label = dynamic_cast<Label*>(this->getChildByTag(SHOW_LEBAL_TAG));
    if(label)
    {
        std::string str = StringUtils::format("Testing completed! Took: %.3f seconds for parsing material %d times.", elapsed_secs, count);
        label->setString(str);
        
        CCLOG("Took: %.3f seconds for parsing material %d times.", elapsed_secs, count);
    }
}

std::string Material_parsePerformance::subtitle() const
{
    return "Testing parsing performance";
}

// MARK: Helper functions

static void printProperties(Properties* properties, int indent)
{
    // Print the name and ID of the current namespace.
    const char* spacename = properties->getNamespace();
    const char* id = properties->getId();
    char chindent[64];
    int i=0;
    for(i=0; i<indent*2;i++)
        chindent[i] = ' ';
    chindent[i] = '\0';

    log("%sNamespace: %s  ID: %s\n%s{", chindent, spacename, id, chindent);

    // Print all properties in this namespace.
    const char* name = properties->getNextProperty();
    const char* value = NULL;
    while (name != NULL)
    {
        value = properties->getString(name);
        log("%s%s = %s", chindent, name, value);
        name = properties->getNextProperty();
    }

    Properties* space = properties->getNextNamespace();
    while (space != NULL)
    {
        printProperties(space, indent+1);
        space = properties->getNextNamespace();
    }

    log("%s}\n",chindent);
}
