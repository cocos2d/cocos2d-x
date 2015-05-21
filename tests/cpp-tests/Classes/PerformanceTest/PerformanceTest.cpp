#include "PerformanceTest.h"
#include "../testResource.h"
#include "PerformanceNodeChildrenTest.h"
#include "PerformanceParticleTest.h"
#include "PerformanceParticle3DTest.h"
#include "PerformanceSpriteTest.h"
#include "PerformanceTextureTest.h"
#include "PerformanceTouchesTest.h"
#include "PerformanceAllocTest.h"
#include "PerformanceLabelTest.h"
#include "PerformanceContainerTest.h"
#include "PerformanceEventDispatcherTest.h"
#include "PerformanceScenarioTest.h"
#include "PerformanceCallbackTest.h"
#include "PerformanceMathTest.h"

USING_NS_CC;

PerformanceTests::PerformanceTests()
{
    addTest("Alloc Test", [](){ return new (std::nothrow) PerformceAllocTests; });
    addTest("NodeChildren Test", [](){ return new (std::nothrow) PerformceNodeChildrenTests; });
    addTest("Particle Test", [](){ return new (std::nothrow) PerformceParticleTests; });
    addTest("Particle3D Perf Test", [](){ return new (std::nothrow) PerformceParticle3DTests; });
    addTest("Sprite Perf Test", [](){ return new (std::nothrow) PerformceSpriteTests; });
    addTest("Texture Perf Test", [](){ return new (std::nothrow) PerformceTextureTests; });
    addTest("Touches Perf Test", [](){ return new (std::nothrow) PerformceTouchesTests; });
    addTest("Label Perf Test", [](){ return new (std::nothrow) PerformceLabelTests; });
    addTest("Container Perf Test", []() {  return new (std::nothrow) PerformceContainerTests; });
    addTest("EventDispatcher Perf Test", []() {  return new (std::nothrow) PerformceEventDispatcherTests; });
    addTest("Scenario Perf Test", []() { return new (std::nothrow) PerformceScenarioTests; });
    addTest("Callback Perf Test", []() { return new (std::nothrow) PerformceCallbackTests; });
    addTest("Math Perf Test", []() { return new (std::nothrow) PerformceMathTests; });
}
