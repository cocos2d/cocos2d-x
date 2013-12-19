/*
 *
 */
#include "PerformanceMathTest.h"

#include <algorithm>

#define GLM_MATH
#define C3D_MATH



#ifdef C3D_MATH
#include "C3DMatrix.h"
#include "C3DVector3.h"
#include "C3DVector2.h"
#include "C3DVector4.h"
#include "CCAction.h"
#endif

#ifdef GLM_MATH
#define GLM_MESSAGES
#define GLM_FORCE_INLINE


#include "glm.hpp"
#endif

#include "kazmath/kazmath.h"
#include "kazmath/vec4.h"


// Enable profiles for this file
#undef CC_PROFILER_DISPLAY_TIMERS
#define CC_PROFILER_DISPLAY_TIMERS() Profiler::getInstance()->displayTimers()
#undef CC_PROFILER_PURGE_ALL
#define CC_PROFILER_PURGE_ALL() Profiler::getInstance()->releaseAllTimers()

#undef CC_PROFILER_START
#define CC_PROFILER_START(__name__) ProfilingBeginTimingBlock(__name__)
#undef CC_PROFILER_STOP
#define CC_PROFILER_STOP(__name__) ProfilingEndTimingBlock(__name__)
#undef CC_PROFILER_RESET
#define CC_PROFILER_RESET(__name__) ProfilingResetTimingBlock(__name__)

#undef CC_PROFILER_START_CATEGORY
#define CC_PROFILER_START_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingBeginTimingBlock(__name__); } while(0)
#undef CC_PROFILER_STOP_CATEGORY
#define CC_PROFILER_STOP_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingEndTimingBlock(__name__); } while(0)
#undef CC_PROFILER_RESET_CATEGORY
#define CC_PROFILER_RESET_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingResetTimingBlock(__name__); } while(0)

#undef CC_PROFILER_START_INSTANCE
#define CC_PROFILER_START_INSTANCE(__id__, __name__) do{ ProfilingBeginTimingBlock( String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_STOP_INSTANCE
#define CC_PROFILER_STOP_INSTANCE(__id__, __name__) do{ ProfilingEndTimingBlock(    String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_RESET_INSTANCE
#define CC_PROFILER_RESET_INSTANCE(__id__, __name__) do{ ProfilingResetTimingBlock( String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)

static std::function<PerformceMathScene*()> createFunctions[] =
{
    CL(MatMultiplyTest),
    CL(MatVec4MultiplyTest),
    CL(Vec3CrossTest),
    CL(Mat4AddTest),
    CL(Vec4AddTest),
};


#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))


enum {
    kInitRunTimes = 10000,
    kIncreaseRunTimes = 5000,
    kMaxRunTimes = 500000,
};

enum {
    kTagInfoLayer = 1,
    
    kTagBase = 20000,
};

static int g_curCase = 0;
static int g_curRunTimes = kInitRunTimes;

////////////////////////////////////////////////////////
//
// MathBasicLayer
//
////////////////////////////////////////////////////////

MathBasicLayer::MathBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{
}

void MathBasicLayer::showCurrentTest()
{

    auto scene = createFunctions[_curCase]();

    g_curCase = _curCase;

    if (scene)
    {
        scene->initPerformanceScene();
        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
}

////////////////////////////////////////////////////////
//
// PerformceMathScene
//
////////////////////////////////////////////////////////
void PerformceMathScene::initPerformanceScene()
{
    
    auto s = Director::getInstance()->getWinSize();

    // Title
    auto label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = LabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(Point(s.width/2, s.height-80));
    }

    lastRenderedCount = 0;
    

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Object *sender) {
		g_curRunTimes -= kIncreaseRunTimes;
		if( g_curRunTimes < kInitRunTimes )
			g_curRunTimes = kInitRunTimes;

		updateTestLabel();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        srand(0);
	});
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [&](Object *sender) {
		g_curRunTimes += kIncreaseRunTimes;
		if( g_curRunTimes > kMaxRunTimes )
			g_curRunTimes = kMaxRunTimes;

		updateTestLabel();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        srand(0);
	});
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = LabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    auto menuLayer = new MathBasicLayer(true, MAX_LAYER, g_curCase);
    addChild(menuLayer);
    menuLayer->release();

    updateTestLabel();
    updateProfilerName();
    srand(0);
}

std::string PerformceMathScene::title()
{
    return "No title";
}

std::string PerformceMathScene::subtitle()
{
    return "";
}

void PerformceMathScene::updateTestLabel()
{
    if( g_curRunTimes != lastRenderedCount )
    {
        auto infoLabel = static_cast<LabelTTF*>( getChildByTag(kTagInfoLayer) );
        char str[30] = {0};
        sprintf(str, "%u times operation", g_curRunTimes);
        infoLabel->setString(str);

        lastRenderedCount = g_curRunTimes;
    }
}

const char * PerformceMathScene::profilerName()
{
    return _profilerName;
}

void PerformceMathScene::updateProfilerName()
{
    snprintf(_profilerName, sizeof(_profilerName)-1, "%s(%d)", testName(), g_curRunTimes);
}

void PerformceMathScene::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    sched->unscheduleSelector(SEL_SCHEDULE(&PerformceMathScene::dumpProfilerInfo), this);
}

void PerformceMathScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();

    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    CC_PROFILER_PURGE_ALL();
    sched->scheduleSelector(SEL_SCHEDULE(&PerformceMathScene::dumpProfilerInfo), this, 2, false);
}

void PerformceMathScene::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
}

////////////////////////////////////////////////////////
//
// MatMultiplyTest
//
////////////////////////////////////////////////////////

void MatMultiplyTest::initPerformanceScene()
{
    PerformceMathScene::initPerformanceScene();

    scheduleUpdate();
}

void MatMultiplyTest::update(float dt)
{
    float m[16];
    int i;
    for (i = 0; i < 16; i++) {
        m[i] = CCRANDOM_0_1();
    }

#ifdef GLM_MATH
    glm::mat4x4 Mat0(
                     glm::dvec4(m[0], m[1], m[2], m[3]),
                     glm::dvec4(m[4], m[5], m[6], m[7]),
                     glm::dvec4(m[8], m[9], m[10], m[11]),
                     glm::dvec4(m[12], m[13], m[14], m[15]));
    glm::dmat4 re;
    string glm = "glm ";
    glm += profilerName();
    
    CC_PROFILER_START(glm.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        re = Mat0 * Mat0;
    }
    CC_PROFILER_STOP(glm.c_str());

#endif
    
#ifdef C3D_MATH
    cocos3d::C3DMatrix c3dmat(m);
    cocos3d::C3DMatrix c3dre;

    string our = "c3d ";
    our += profilerName();
    CC_PROFILER_START(our.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        c3dre = c3dmat * c3dmat;
    }
    CC_PROFILER_STOP(our.c_str());
#endif
    
    ////kazmath
    kmMat4 kam, rekam;
    kmMat4Fill(&kam, m);
    
    string strkam = "kazmath ";
    strkam += profilerName();
    CC_PROFILER_START(strkam.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        kmMat4Multiply(&rekam, &kam, &kam);
    }
    CC_PROFILER_STOP(strkam.c_str());
    ////kazmath
   
}


std::string MatMultiplyTest::title()
{
    return "math Perf test.";
}

std::string MatMultiplyTest::subtitle()
{
    return "Matrix multiply Perf test. See console";
}

const char*  MatMultiplyTest::testName()
{
    return "Matrix4X4 multiply ";
}

////////////////////////////////////////////////////////
//
// MatVec4MultiplyTest
//
////////////////////////////////////////////////////////

void MatVec4MultiplyTest::initPerformanceScene()
{
    PerformceMathScene::initPerformanceScene();
    
    scheduleUpdate();
}

void MatVec4MultiplyTest::update(float dt)
{
    float m[16];
    int i;
    for (i = 0; i < 16; i++) {
        m[i] = CCRANDOM_0_1();
    }
    
    float vec31[3], vec32[3];
    for (i = 0; i < 3; i++) {
        vec31[i] = CCRANDOM_0_1();
        vec32[i] = CCRANDOM_0_1();
    }
    
    float vec41[4];
    for (i = 0; i < 4; i++) {
        vec41[i] = CCRANDOM_0_1();
    }

    
#ifdef GLM_MATH
    glm::mat4x4 Mat0(
                     glm::dvec4(m[0], m[1], m[2], m[3]),
                     glm::dvec4(m[4], m[5], m[6], m[7]),
                     glm::dvec4(m[8], m[9], m[10], m[11]),
                     glm::dvec4(m[12], m[13], m[14], m[15]));
    glm::vec4 u(1.0f);
    string glm = "glm ";
    glm += profilerName();
    glm::vec4 v(vec41[0], vec41[1], vec41[2], vec41[3]);
    
    CC_PROFILER_START(glm.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        u = Mat0 * v;
    }
    CC_PROFILER_STOP(glm.c_str());
    
#endif
    
#ifdef C3D_MATH
    cocos3d::C3DMatrix c3dmat(m);
    cocos3d::C3DVector4 c3du;
    cocos3d::C3DVector4 c3dv(vec41[0], vec41[1], vec41[2], vec41[3]);
    
    string our = "c3d ";
    our += profilerName();
    CC_PROFILER_START(our.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        c3dmat.transformVector(c3dv, &c3du);
    }
    CC_PROFILER_STOP(our.c_str());
#endif
    
    kmMat4 kam;
    kmMat4Fill(&kam, m);
    kmVec4 kmv4, rekmv4;
    kmVec4Fill(&kmv4, vec41[0], vec41[1], vec41[2], vec41[3]);
    string strkaz = "kazmath ";
    
    CC_PROFILER_START(strkaz.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        kmVec4Transform(&rekmv4, &kmv4, &kam);
    }
    
    CC_PROFILER_STOP(strkaz.c_str());
}


std::string MatVec4MultiplyTest::title()
{
    return "math Perf test.";
}

std::string MatVec4MultiplyTest::subtitle()
{
    return "Matrix vec4 multiply Perf test. See console";
}

const char*  MatVec4MultiplyTest::testName()
{
    return "Matrix4X4 vec4 multiply ";
}

////////////////////////////////////////////////////////
//
// Vec4CrossTest
//
////////////////////////////////////////////////////////

void Vec3CrossTest::initPerformanceScene()
{
    PerformceMathScene::initPerformanceScene();
    
    scheduleUpdate();
}

void Vec3CrossTest::update(float dt)
{
    int i;
        
    float vec31[3], vec32[3];
    for (i = 0; i < 3; i++) {
        vec31[i] = CCRANDOM_0_1();
        vec32[i] = CCRANDOM_0_1();
    }
    
    
#ifdef GLM_MATH
    glm::vec3 v1(vec31[0],vec31[1],vec31[2]);
    glm::vec3 v2(vec32[0],vec32[1],vec32[2]);
    glm::vec3 v3;

    string glm = "glm ";
    glm += profilerName();
    
    CC_PROFILER_START(glm.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        v3 = glm::cross(v1, v2);
    }
    CC_PROFILER_STOP(glm.c_str());
    
#endif
    
#ifdef C3D_MATH
    cocos3d::C3DVector3 c3dv1(vec31[0],vec31[1],vec31[2]);
    cocos3d::C3DVector3 c3dv2(vec32[0],vec32[1],vec32[2]);
    cocos3d::C3DVector3 c3dv3;
    
    string our = "c3d ";
    our += profilerName();
    CC_PROFILER_START(our.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        cocos3d::C3DVector3::cross(c3dv1, c3dv2, &c3dv3);
    }
    CC_PROFILER_STOP(our.c_str());
#endif
    
    kmVec3 kmv1, kmv2, rekmv;
    kmVec3Fill(&kmv1, vec31[0], vec31[1], vec31[2]);
    kmVec3Fill(&kmv2, vec32[0], vec32[1], vec32[2]);
    string strkaz = "kazmath ";
    strkaz += profilerName();
    CC_PROFILER_START(our.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        kmVec3Cross(&rekmv, &kmv1, &kmv2);
    }
    CC_PROFILER_STOP(our.c_str());
}


std::string Vec3CrossTest::title()
{
    return "math Perf test.";
}

std::string Vec3CrossTest::subtitle()
{
    return "Matrix vec3 cross product Perf test. See console";
}

const char*  Vec3CrossTest::testName()
{
    return "vec3 cross product ";
}

////////////////////////////////////////////////////////
//
// Mat4AddTest
//
////////////////////////////////////////////////////////

void Mat4AddTest::initPerformanceScene()
{
    PerformceMathScene::initPerformanceScene();
    
    scheduleUpdate();
}

void Mat4AddTest::update(float dt)
{
    float m[16];
    int i;
    for (i = 0; i < 16; i++) {
        m[i] = CCRANDOM_0_1();
    }
    
#ifdef GLM_MATH
    glm::mat4x4 Mat0(
                     glm::dvec4(m[0], m[1], m[2], m[3]),
                     glm::dvec4(m[4], m[5], m[6], m[7]),
                     glm::dvec4(m[8], m[9], m[10], m[11]),
                     glm::dvec4(m[12], m[13], m[14], m[15]));
    glm::dmat4 re;
    string glm = "glm ";
    glm += profilerName();
    
    CC_PROFILER_START(glm.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        re = Mat0 + Mat0;
    }
    CC_PROFILER_STOP(glm.c_str());
    
#endif
    
#ifdef C3D_MATH
    cocos3d::C3DMatrix c3dmat(m);
    cocos3d::C3DMatrix c3dre;
    
    string our = "c3d ";
    our += profilerName();
    CC_PROFILER_START(our.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        c3dre = c3dmat + c3dmat;
    }
    CC_PROFILER_STOP(our.c_str());
#endif
    
}


std::string Mat4AddTest::title()
{
    return "math Perf test.";
}

std::string Mat4AddTest::subtitle()
{
    return "Matrix add Perf test. See console";
}

const char*  Mat4AddTest::testName()
{
    return "Matrix4X4 add ";
}


////////////////////////////////////////////////////////
//
// Vec4AddTest
//
////////////////////////////////////////////////////////

void Vec4AddTest::initPerformanceScene()
{
    PerformceMathScene::initPerformanceScene();
    
    scheduleUpdate();
}

void Vec4AddTest::update(float dt)
{
    int i;
    
    float vec41[4];
    for (i = 0; i < 4; i++) {
        vec41[i] = CCRANDOM_0_1();
    }
    
    
#ifdef GLM_MATH
    glm::vec4 v1(vec41[0], vec41[1], vec41[2], vec41[3]);
    glm::vec4 v2(vec41[0], vec41[1], vec41[2], vec41[3]);
    glm::vec4 v3;
    
    string glm = "glm ";
    glm += profilerName();
    
    CC_PROFILER_START(glm.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        v3 = v1 + v2;
    }
    CC_PROFILER_STOP(glm.c_str());
    
#endif
    
#ifdef C3D_MATH
    cocos3d::C3DVector4 c3dv1(vec41);
    cocos3d::C3DVector4 c3dv2(vec41);
    cocos3d::C3DVector4 c3dv3;
    
    string our = "c3d ";
    our += profilerName();
    CC_PROFILER_START(our.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        c3dv3 = c3dv1 + c3dv2;
    }
    CC_PROFILER_STOP(our.c_str());
#endif
    
    kmVec4 kmv1, kmv2, rekmv;
    kmVec4Fill(&kmv1, vec41[0], vec41[1], vec41[2], vec41[3]);
    kmVec4Fill(&kmv2, vec41[0], vec41[1], vec41[2], vec41[3]);
    string strkm = "kazmath ";
    strkm += profilerName();
    CC_PROFILER_START(strkm.c_str());
    for (i = 0; i < g_curRunTimes; i++) {
        kmVec4Add(&rekmv, &kmv1, &kmv2);
    }
    CC_PROFILER_STOP(strkm.c_str());
}

std::string Vec4AddTest::title()
{
    return "math Perf test.";
}

std::string Vec4AddTest::subtitle()
{
    return "Vec4 add Perf test. See console";
}

const char*  Vec4AddTest::testName()
{
    return "Vec4 add ";
}



///----------------------------------------
void runMathPerformanceTest()
{
    g_curCase = 2;
    auto scene = createFunctions[g_curCase]();
    scene->initPerformanceScene();
    
    Director::getInstance()->replaceScene(scene);
    scene->release();
}
