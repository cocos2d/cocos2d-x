#ifndef _TestEntries_H_
#define _TestEntries_H_

#include "Test.h"
//#include "GLES-Render.h"

#include "Tests/ContinuousTest.h"
#include "Tests/Cantilever.h"
#include "Tests/BodyTypes.h"
#include "Tests/ApplyForce.h"
#include "Tests/CharacterCollision.h"
#include "Tests/EdgeShapes.h"
#include "Tests/Breakable.h"
#include "Tests/Bridge.h"
//#include "Tests/CCDTest.h"
#include "Tests/Chain.h"
#include "Tests/CollisionFiltering.h"
#include "Tests/CollisionProcessing.h"
#include "Tests/CompoundShapes.h"
#include "Tests/Confined.h"
#include "Tests/DistanceTest.h"
#include "Tests/Dominos.h"
#include "Tests/DynamicTreeTest.h"
#include "Tests/Gears.h"
#include "Tests/LineJoint.h"
#include "Tests/OneSidedPlatform.h"
#include "Tests/PolyCollision.h"
#include "Tests/PolyShapes.h"
#include "Tests/Prismatic.h"
#include "Tests/Pulleys.h"
#include "Tests/Pyramid.h"
#include "Tests/RayCast.h"
#include "Tests/Revolute.h"
#include "Tests/SensorTest.h"
#include "Tests/ShapeEditing.h"
#include "Tests/SliderCrank.h"
#include "Tests/SphereStack.h"
#include "Tests/TheoJansen.h"
#include "Tests/TimeOfImpact.h"
#include "Tests/VaryingFriction.h"
#include "Tests/VaryingRestitution.h"
#include "Tests/VerticalStack.h"
#include "Tests/Web.h"

TestEntry g_testEntries[] =
{
	{"Body Types", BodyTypes::Create},
	{"Ray-Cast", RayCast::Create},
	{"Character Collision", CharacterCollision::Create},
	{"Prismatic", Prismatic::Create},
	{"Edge Shapes", EdgeShapes::Create},
	{"Continuous Test", ContinuousTest::Create},
	{"Time of Impact", TimeOfImpact::Create},
	{"Vertical Stack", VerticalStack::Create},
	{"PolyCollision", PolyCollision::Create},
	{"Polygon Shapes", PolyShapes::Create},
	{"Apply Force", ApplyForce::Create},
	{"Cantilever", Cantilever::Create},
	{"SphereStack", SphereStack::Create},
	{"Confined", Confined::Create},
	{"Bridge", Bridge::Create},
	{"Breakable", Breakable::Create},
	{"Varying Restitution", VaryingRestitution::Create},
	{"Pyramid", Pyramid::Create},
	{"One-Sided Platform", OneSidedPlatform::Create},
	{"Chain", Chain::Create},
	{"Collision Filtering", CollisionFiltering::Create},
	{"Collision Processing", CollisionProcessing::Create},
	{"Compound Shapes", CompoundShapes::Create},
	{"Distance Test", DistanceTest::Create},
	{"Dominos", Dominos::Create},
	{"Dynamic Tree", DynamicTreeTest::Create},
	{"Gears", Gears::Create},
	{"Line Joint", LineJoint::Create},
	{"Pulleys", Pulleys::Create},
	{"Revolute", Revolute::Create},
	{"Sensor Test", SensorTest::Create},
	{"Shape Editing", ShapeEditing::Create},
	{"Slider Crank", SliderCrank::Create},
	{"Theo Jansen's Walker", TheoJansen::Create},
	{"Varying Friction", VaryingFriction::Create},
	{"Web", Web::Create},
};

int g_totalEntries = sizeof(g_testEntries) / sizeof(g_testEntries[0]);

#endif
