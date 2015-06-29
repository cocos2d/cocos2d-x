/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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
    ADD_TEST_CASE(Material_invalidate);
    ADD_TEST_CASE(Material_renderState);
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
    sprite->setNormalizedPosition(Vec2(0.5,0.5));
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
    spriteBlur->setNormalizedPosition(Vec2(0.2f, 0.5f));
    this->addChild(spriteBlur);
    spriteBlur->setGLProgramState(mat1->getTechniqueByName("blur")->getPassByIndex(0)->getGLProgramState());

    auto spriteOutline = Sprite::create("Images/grossini.png");
    spriteOutline->setNormalizedPosition(Vec2(0.4f, 0.5f));
    this->addChild(spriteOutline);
    spriteOutline->setGLProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getGLProgramState());

    auto spriteNoise = Sprite::create("Images/grossini.png");
    spriteNoise->setNormalizedPosition(Vec2(0.6f, 0.5f));
    this->addChild(spriteNoise);
    spriteNoise->setGLProgramState(mat1->getTechniqueByName("noise")->getPassByIndex(0)->getGLProgramState());

    auto spriteEdgeDetect = Sprite::create("Images/grossini.png");
    spriteEdgeDetect->setNormalizedPosition(Vec2(0.8f, 0.5f));
    this->addChild(spriteEdgeDetect);
    spriteEdgeDetect->setGLProgramState(mat1->getTechniqueByName("edge_detect")->getPassByIndex(0)->getGLProgramState());

    // properties is not a "Ref" object
    CC_SAFE_DELETE(properties);
}

std::string Material_2DEffects::subtitle() const
{
    return "Testing effects on Sprite";
}

//
// MARK: Material_AutoBindings
//

/*
 * Custom material auto-binding resolver for terrain.
 */
class EffectAutoBindingResolver : public GLProgramState::AutoBindingResolver
{
    bool resolveAutoBinding(GLProgramState* glProgramState, Node* node, const std::string& uniform, const std::string& autoBinding);

    void callbackRadius(GLProgram* glProgram, Uniform* uniform);
    void callbackColor(GLProgram* glProgram, Uniform* uniform);
};

bool EffectAutoBindingResolver::resolveAutoBinding(GLProgramState* glProgramState, Node* node, const std::string& uniform, const std::string& autoBinding)
{
    if (autoBinding.compare("DYNAMIC_RADIUS")==0)
    {
        glProgramState->setUniformCallback(uniform, CC_CALLBACK_2(EffectAutoBindingResolver::callbackRadius, this));
        return true;
    }
    else if (autoBinding.compare("OUTLINE_COLOR")==0)
    {
        glProgramState->setUniformCallback(uniform, CC_CALLBACK_2(EffectAutoBindingResolver::callbackColor, this));
        return true;
    }
    return false;
}

void EffectAutoBindingResolver::callbackRadius(GLProgram* glProgram, Uniform* uniform)
{
    float f = CCRANDOM_0_1() * 10;
    glProgram->setUniformLocationWith1f(uniform->location, f);
}

void EffectAutoBindingResolver::callbackColor(GLProgram* glProgram, Uniform* uniform)
{
    float r = CCRANDOM_0_1();
    float g = CCRANDOM_0_1();
    float b = CCRANDOM_0_1();

    glProgram->setUniformLocationWith3f(uniform->location, r, g, b);
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
    spriteBlur->setNormalizedPosition(Vec2(0.2f, 0.5f));
    this->addChild(spriteBlur);
    spriteBlur->setGLProgramState(mat1->getTechniqueByName("blur")->getPassByIndex(0)->getGLProgramState());

    auto spriteOutline = Sprite::create("Images/grossini.png");
    spriteOutline->setNormalizedPosition(Vec2(0.4f, 0.5f));
    this->addChild(spriteOutline);
    spriteOutline->setGLProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getGLProgramState());

    auto spriteNoise = Sprite::create("Images/grossini.png");
    spriteNoise->setNormalizedPosition(Vec2(0.6f, 0.5f));
    this->addChild(spriteNoise);
    spriteNoise->setGLProgramState(mat1->getTechniqueByName("noise")->getPassByIndex(0)->getGLProgramState());

    auto spriteEdgeDetect = Sprite::create("Images/grossini.png");
    spriteEdgeDetect->setNormalizedPosition(Vec2(0.8f, 0.5f));
    this->addChild(spriteEdgeDetect);
    spriteEdgeDetect->setGLProgramState(mat1->getTechniqueByName("edge_detect")->getPassByIndex(0)->getGLProgramState());

    // properties is not a "Ref" object
    CC_SAFE_DELETE(properties);
}

std::string Material_AutoBindings::subtitle() const
{
    return "Testing auto-bindings uniforms";
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
    sprite->setNormalizedPosition(Vec2(0.5,0.5));
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

    auto rot = RotateBy::create(5, Vec3(30,60,270));
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

    _techniqueState++;
    if (_techniqueState>2)
        _techniqueState = 0;
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
    sprite->setNormalizedPosition(Vec2(0.25, 0.5));

    Material *mat = Material::createWithFilename("Materials/3d_effects.material");
    sprite->setMaterial(mat);

    auto rot = RotateBy::create(5, Vec3(360,240,120));
    auto repeat = RepeatForever::create(rot);
    sprite->runAction(repeat);

    // sprite 2... using same material
    auto sprite2 = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite2->setScale(3);
    this->addChild(sprite2);
    sprite2->setNormalizedPosition(Vec2(0.5, 0.5));
    sprite2->setMaterial(mat);
    sprite2->runAction(repeat->clone());

    // sprite 3... using cloned material
    auto sprite3 = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite3->setScale(3);
    this->addChild(sprite3);
    sprite3->setNormalizedPosition(Vec2(0.75, 0.5));
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
void Material_parsePerformance::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    std::clock_t begin = std::clock();

    for(int i=0;i<5000;i++)
    {
        Material::createWithFilename("Materials/2d_effects.material");
        Material::createWithFilename("Materials/3d_effects.material");
    }

    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    log("Parsing took: %f", elapsed_secs);
}

std::string Material_parsePerformance::subtitle() const
{
    return "Testing parsing performance";
}

//
//
//
void Material_invalidate::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    // ORC
    auto sprite = Sprite3D::create("Sprite3DTest/orc.c3b");
    sprite->setScale(5);
    sprite->setRotation3D(Vec3(0,180,0));
    addChild(sprite);
    sprite->setNormalizedPosition(Vec2(0.3f,0.3f));

    auto rotate = RotateBy::create(5, Vec3(0,360,0));
    auto repeat = RepeatForever::create(rotate);
    sprite->runAction(repeat);

    // SPINE
    auto skeletonNode = spine::SkeletonAnimation::createWithFile("spine/goblins-ffd.json", "spine/goblins-ffd.atlas", 1.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->setSkin("goblin");

    skeletonNode->setScale(0.25);
    skeletonNode->setNormalizedPosition(Vec2(0.6f,0.3f));
    this->addChild(skeletonNode);
}

std::string Material_invalidate::subtitle() const
{
    return "Testing RenderState::StateBlock::invalidate()";
}

void Material_invalidate::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = []() {
        glDisable(GL_DEPTH_TEST);
        CHECK_GL_ERROR_DEBUG();

        glDepthMask(false);
        CHECK_GL_ERROR_DEBUG();

        glEnable(GL_CULL_FACE);
        CHECK_GL_ERROR_DEBUG();

        glCullFace((GLenum)GL_FRONT);
        CHECK_GL_ERROR_DEBUG();

        glFrontFace((GLenum)GL_CW);
        CHECK_GL_ERROR_DEBUG();

        glDisable(GL_BLEND);
        CHECK_GL_ERROR_DEBUG();

        // a non-optimal way is to pass all bits, but that would be very inefficient
//        RenderState::StateBlock::invalidate(RenderState::StateBlock::RS_ALL_ONES);

        RenderState::StateBlock::invalidate(RenderState::StateBlock::RS_DEPTH_TEST |
                                            RenderState::StateBlock::RS_DEPTH_WRITE |
                                            RenderState::StateBlock::RS_CULL_FACE |
                                            RenderState::StateBlock::RS_CULL_FACE_SIDE |
                                            RenderState::StateBlock::RS_FRONT_FACE |
                                            RenderState::StateBlock::RS_BLEND);
    };

    renderer->addCommand(&_customCommand);
}

//
//
//
void Material_renderState::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    // ORC
    auto sprite = Sprite3D::create("Sprite3DTest/orc.c3b");
    sprite->setScale(5);
    sprite->setRotation3D(Vec3(0,180,0));
    addChild(sprite);
    sprite->setNormalizedPosition(Vec2(0.3f,0.3f));

    auto rotate = RotateBy::create(5, Vec3(0,360,0));
    auto repeat = RepeatForever::create(rotate);
    sprite->runAction(repeat);

    // SPINE
    auto skeletonNode = spine::SkeletonAnimation::createWithFile("spine/goblins-ffd.json", "spine/goblins-ffd.atlas", 1.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->setSkin("goblin");

    skeletonNode->setScale(0.25);
    skeletonNode->setNormalizedPosition(Vec2(0.6f,0.3f));
    this->addChild(skeletonNode);

    _stateBlock.setDepthTest(false);
    _stateBlock.setDepthWrite(false);
    _stateBlock.setCullFace(true);
    _stateBlock.setCullFaceSide(RenderState::CULL_FACE_SIDE_FRONT);
    _stateBlock.setFrontFace(RenderState::FRONT_FACE_CW);
    _stateBlock.setBlend(false);
}

std::string Material_renderState::subtitle() const
{
    return "You should see a Spine animation on the right";
}

void Material_renderState::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = [this]() {

        this->_stateBlock.bind();

        // should do something...
        // and after that, restore

        this->_stateBlock.restore(0);
    };
    
    renderer->addCommand(&_customCommand);
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
