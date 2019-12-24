/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include "SpineTest.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "spine/spine.h"

using namespace cocos2d;
using namespace std;
using namespace spine;


#define NUM_SKELETONS 50
#define SPINE_NODE_SCALE_FACTOR 0.4

static Cocos2dTextureLoader textureLoader;

PowInterpolation pow2(2);
PowOutInterpolation powOut2(2);
SwirlVertexEffect effect(400, powOut2);



#define SCALE_SKELETON_NODE(node) do { if(node) node->setScale(SPINE_NODE_SCALE_FACTOR); } while(false)

//------------------------------------------------------------------
//
// SpineTestScene
//
//------------------------------------------------------------------


SpineTests::SpineTests()
{
    auto fu = FileUtils::getInstance();
    _searchPaths = fu->getSearchPaths();
    fu->addSearchPath("spine", true);

    ADD_TEST_CASE(BatchingExample);
    ADD_TEST_CASE(CoinExample);
    ADD_TEST_CASE(GoblinsExample);
    ADD_TEST_CASE(IKExample);
    ADD_TEST_CASE(MixAndMatchExample);
    ADD_TEST_CASE(RaptorExample);
    ADD_TEST_CASE(SkeletonRendererSeparatorExample);
    ADD_TEST_CASE(SpineboyExample);
    ADD_TEST_CASE(TankExample);

#ifdef COCOS2D_DEBUG
    debugExtension = new DebugExtension(SpineExtension::getInstance());
#endif
}

SpineTests::~SpineTests()
{
    FileUtils::getInstance()->setSearchPaths(_searchPaths);
    SkeletonBatch::destroyInstance();
    SkeletonTwoColorBatch::destroyInstance();
#ifdef COCOS2D_DEBUG
    debugExtension->reportLeaks();
    delete debugExtension;
#endif
}

SpineTestLayer::SpineTestLayer()
: _title("")
{}

SpineTestLayer::~SpineTestLayer()
{

}

std::string SpineTestLayer::title() const
 {
     return _title;
 }

bool SpineTestLayer::init()
{   
    if (!TestCase::init()) return false;

    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, cocos2d::Event* event) -> bool {
        if (!skeletonNode) return true;
        _touchIndex = (_touchIndex + 1) % 3;
        if (_touchIndex == 0)
        {
            skeletonNode->setDebugBonesEnabled(false);
            skeletonNode->setTimeScale(1.0f);
        }
        else if (_touchIndex == 1)
        {
            skeletonNode->setDebugBonesEnabled(true);
            skeletonNode->setTimeScale(1.0f);
        }
        else if (_touchIndex == 2)
        {
            skeletonNode->setDebugBonesEnabled(true);
            skeletonNode->setTimeScale(0.3f);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    SCALE_SKELETON_NODE(skeletonNode);

    return true;
}

// BatchingExample
bool BatchingExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "Batching";

    _atlas = new (__FILE__, __LINE__) Atlas("spineboy.atlas", &textureLoader, true);
    CCASSERT(_atlas, "Error reading atlas file.");

    // This attachment loader configures attachments with data needed for cocos2d-x rendering.
    // Do not dispose the attachment loader until the skeleton data is disposed!
    _attachmentLoader = new (__FILE__, __LINE__) Cocos2dAtlasAttachmentLoader(_atlas);

    // Load the skeleton data.
    SkeletonJson* json = new (__FILE__, __LINE__) SkeletonJson(_attachmentLoader);
    json->setScale(0.6f); // Resizes skeleton data to 60% of the size it was in Spine.
    _skeletonData = json->readSkeletonDataFile("spineboy-pro.json");
    CCASSERT(_skeletonData, json->getError().isEmpty() ? json->getError().buffer() : "Error reading skeleton data file.");
    delete json;

    // Setup mix times.
    _stateData = new (__FILE__, __LINE__) AnimationStateData(_skeletonData);
    _stateData->setMix("walk", "jump", 0.2f);
    _stateData->setMix("jump", "run", 0.2f);

    int xMin = _contentSize.width * 0.10f, xMax = _contentSize.width * 0.90f;
    int yMin = 0, yMax = _contentSize.height * 0.7f;
    for (int i = 0; i < NUM_SKELETONS; i++) {
        // Each skeleton node shares the same atlas, skeleton data, and mix times.
        SkeletonAnimation* skeletonNode = SkeletonAnimation::createWithData(_skeletonData, false);
        skeletonNode->setAnimationStateData(_stateData);

        skeletonNode->setAnimation(0, "walk", true);
        skeletonNode->addAnimation(0, "jump", true, RandomHelper::random_int(0, 300) / 100.0f);
        skeletonNode->addAnimation(0, "run", true);

        // alternative setting two color tint for groups of 10 skeletons
        // should end up with #skeletons / 10 batches
        // if (j++ < 10)
//			skeletonNode->setTwoColorTint(true);
//		if (j == 20) j = 0;
        // skeletonNode->setTwoColorTint(true);

        skeletonNode->setPosition(Vec2(
            RandomHelper::random_int(xMin, xMax),
            RandomHelper::random_int(yMin, yMax)
        ));
        addChild(skeletonNode);
    }
    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}


BatchingExample::~BatchingExample() {
    // SkeletonAnimation instances are cocos2d-x nodes and are disposed of automatically as normal, but the data created
    // manually to be shared across multiple SkeletonAnimations needs to be disposed of manually.

    delete _skeletonData;
    delete _stateData;
    delete _attachmentLoader;
    delete _atlas;
}


bool CoinExample::init() {
    
    if (!SpineTestLayer::init()) return false;

    _title = "Coin";


    skeletonNode = SkeletonAnimation::createWithBinaryFile("coin-pro.skel", "coin.atlas", 1);
    skeletonNode->setAnimation(0, "animation", true);

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, _contentSize.height / 2));
    addChild(skeletonNode);

    scheduleUpdate();
    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}



bool GoblinsExample::init() {
    if (!SpineTestLayer::init()) return false;

    _title = "Goblins";
    skeletonNode = SkeletonAnimation::createWithJsonFile("goblins-pro.json", "goblins.atlas", 1.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->setSkin("goblin");

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    addChild(skeletonNode);
    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}


bool IKExample::init() {
    if (!SpineTestLayer::init()) return false;

    _title = "IKExample";

    // Load the Spineboy skeleton and create a SkeletonAnimation node from it
    // centered on the screen.
    skeletonNode = SkeletonAnimation::createWithJsonFile("spineboy-pro.json", "spineboy.atlas", 0.6f);
    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    addChild(skeletonNode);

    // Queue the "walk" animation on the first track.
    skeletonNode->setAnimation(0, "walk", true);

    // Queue the "aim" animation on a higher track.
    // It consists of a single frame that positions
    // the back arm and gun such that they point at
    // the "crosshair" bone. By setting this
    // animation on a higher track, it overrides
    // any changes to the back arm and gun made
    // by the walk animation, allowing us to
    // mix the two. The mouse position following
    // is performed in the lambda below.
    skeletonNode->setAnimation(1, "aim", true);

    // Next we setup a listener that receives and stores
    // the current mouse location. The location is converted
    // to the skeleton's coordinate system.
    EventListenerMouse* mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [this](cocos2d::Event* event) -> void {
        // convert the mosue location to the skeleton's coordinate space
        // and store it.
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        position = skeletonNode->convertToNodeSpace(mouseEvent->getLocationInView());
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Position the "crosshair" bone at the mouse
    // location.
    //
    // When setting the crosshair bone position
    // to the mouse position, we need to translate
    // from "skeleton space" to "local bone space".
    // Note that the local bone space is calculated
    // using the bone's parent worldToLocal() function!
    //
    // After updating the bone position based on the
    // converted mouse location, we call updateWorldTransforms()
    // again so the change of the IK target position is
    // applied to the rest of the skeleton.
    skeletonNode->setPostUpdateWorldTransformsListener([this](SkeletonAnimation* node) -> void {
        Bone* crosshair = node->findBone("crosshair"); // The bone should be cached
        float localX = 0, localY = 0;
        crosshair->getParent()->worldToLocal(position.x, position.y, localX, localY);
        crosshair->setX(localX);
        crosshair->setY(localY);
        crosshair->setAppliedValid(false);

        node->getSkeleton()->updateWorldTransform();
        });

    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}



MixAndMatchExample::~MixAndMatchExample() {
    delete skin;
}

bool MixAndMatchExample::init() {
    if (!SpineTestLayer::init()) return false;
    
    _title = "Mix and Match";

    skeletonNode = SkeletonAnimation::createWithBinaryFile("mix-and-match-pro.skel", "mix-and-match.atlas", 0.5);
    skeletonNode->setAnimation(0, "dance", true);

    // Create a new skin, by mixing and matching other skins
    // that fit together. Items making up the girl are individual
    // skins. Using the skin API, a new skin is created which is
    // a combination of all these individual item skins.
    SkeletonData* skeletonData = skeletonNode->getSkeleton()->getData();
    skin = new (__FILE__, __LINE__) Skin("mix-and-match");
    skin->addSkin(skeletonData->findSkin("skin-base"));
    skin->addSkin(skeletonData->findSkin("nose/short"));
    skin->addSkin(skeletonData->findSkin("eyelids/girly"));
    skin->addSkin(skeletonData->findSkin("eyes/violet"));
    skin->addSkin(skeletonData->findSkin("hair/brown"));
    skin->addSkin(skeletonData->findSkin("clothes/hoodie-orange"));
    skin->addSkin(skeletonData->findSkin("legs/pants-jeans"));
    skin->addSkin(skeletonData->findSkin("accessories/bag"));
    skin->addSkin(skeletonData->findSkin("accessories/hat-red-yellow"));
    skeletonNode->getSkeleton()->setSkin(skin);

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, _contentSize.height / 2 - 100 ));
    addChild(skeletonNode);

    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}


bool RaptorExample::init() {
    if (!SpineTestLayer::init()) return false;

    _title = "Raptor";
    skeletonNode = SkeletonAnimation::createWithJsonFile("raptor-pro.json", "raptor.atlas", 0.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->addAnimation(1, "gun-grab", false, 2);
    skeletonNode->setTwoColorTint(true);

    effect.setCenterY(200);
    swirlTime = 0;

    skeletonNode->setVertexEffect(&effect);

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    addChild(skeletonNode);

    scheduleUpdate();

    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}

void RaptorExample::update(float fDelta) {
    swirlTime += fDelta;
    float percent = spine::MathUtil::fmod(swirlTime, 2);
    if (percent > 1) percent = 1 - (percent - 1);
    effect.setAngle(pow2.interpolate(-60.0f, 60.0f, percent));
}



bool SkeletonRendererSeparatorExample::init() {
    if (!SpineTestLayer::init()) return false;
    
    _title = "Seperator";

    // Spineboy's back, which will manage the animation and GPU resources
    // will render only the front slots of Spineboy
    skeletonNode = SkeletonAnimation::createWithJsonFile("spineboy-pro.json", "spineboy.atlas", 0.6f);
    skeletonNode->setMix("walk", "jump", 0.4);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->setSlotsRange(skeletonNode->findSlot("rear-upper-arm")->getData().getIndex(), skeletonNode->findSlot("rear-shin")->getData().getIndex());
    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));

    // A simple rectangle to go between the front and back slots of Spineboy
    betweenNode = DrawNode::create();
    Vec2 rect[4];
    rect[0] = Vec2(0, 0);
    rect[1] = Vec2(40, 0);
    rect[2] = Vec2(40, 200);
    rect[3] = Vec2(0, 200);
    betweenNode->drawPolygon(rect, 4, Color4F(1, 0, 0, 1), 1, Color4F(1, 0, 0, 1));
    betweenNode->setPosition(Vec2(_contentSize.width / 2 + 30, 20));
    // Spineboy's front, doesn't manage any skeleton, animation or GPU resources, but simply
    // renders the back slots of Spineboy. The skeleton, animatio state and GPU resources
    // are shared with the front node!
    frontNode = SkeletonRenderer::createWithSkeleton(skeletonNode->getSkeleton());
    frontNode->setSlotsRange(frontNode->findSlot("neck")->getData().getIndex(), -1);
    frontNode->setPosition(Vec2(_contentSize.width / 2, 20));

    // Add the front, between and back node in the correct order to this scene
    addChild(skeletonNode);
    addChild(betweenNode);
    addChild(frontNode);

    scheduleUpdate();

    SCALE_SKELETON_NODE(skeletonNode);
    SCALE_SKELETON_NODE(frontNode);
    return true;
}

void SkeletonRendererSeparatorExample::update(float deltaTime) {
    // Test releasing memory.
    // Director::getInstance()->replaceScene(SpineboyExample::scene());
}


bool SpineboyExample::init() {
    if (!SpineTestLayer::init()) return false;

    _title = "Spineboy";

    skeletonNode = SkeletonAnimation::createWithJsonFile("spineboy-pro.json", "spineboy.atlas", 0.6f);

    skeletonNode->setStartListener([](TrackEntry* entry) {
        log("%d start: %s", entry->getTrackIndex(), entry->getAnimation()->getName().buffer());
        });
    skeletonNode->setInterruptListener([](TrackEntry* entry) {
        log("%d interrupt", entry->getTrackIndex());
        });
    skeletonNode->setEndListener([](TrackEntry* entry) {
        log("%d end", entry->getTrackIndex());
        });
    skeletonNode->setCompleteListener([](TrackEntry* entry) {
        log("%d complete", entry->getTrackIndex());
        });
    skeletonNode->setDisposeListener([](TrackEntry* entry) {
        log("%d dispose", entry->getTrackIndex());
        });
    skeletonNode->setEventListener([](TrackEntry* entry, spine::Event* event) {
        log("%d event: %s, %d, %f, %s", entry->getTrackIndex(), event->getData().getName().buffer(), event->getIntValue(), event->getFloatValue(), event->getStringValue().buffer());
        });

    skeletonNode->setMix("walk", "jump", 0.4);
    skeletonNode->setMix("jump", "run", 0.4);
    skeletonNode->setAnimation(0, "walk", true);
    TrackEntry* jumpEntry = skeletonNode->addAnimation(0, "jump", false, 1);
    skeletonNode->addAnimation(0, "run", true);

    skeletonNode->setTrackStartListener(jumpEntry, [](TrackEntry* entry) {
        log("jumped!");
        });

    // skeletonNode->addAnimation(1, "test", true);
    // skeletonNode->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), DelayTime::create(5), NULL)));

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    addChild(skeletonNode);

    scheduleUpdate();

    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}

void SpineboyExample::update(float deltaTime) {
    // Test releasing memory.
    // Director::getInstance()->replaceScene(SpineboyExample::scene());
}


bool TankExample::init() {
    if (!SpineTestLayer::init()) return false;

    _title = "Tank";
    skeletonNode = SkeletonAnimation::createWithBinaryFile("tank-pro.skel", "tank.atlas", 0.5f);
    skeletonNode->setAnimation(0, "shoot", true);

    skeletonNode->setPosition(Vec2(_contentSize.width / 2 + 400, 20));
    addChild(skeletonNode);

    SCALE_SKELETON_NODE(skeletonNode);
    return true;
}
