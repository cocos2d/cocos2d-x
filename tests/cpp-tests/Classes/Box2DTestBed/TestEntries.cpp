/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/
#include <cstring>
using namespace std;

#include "Test.h"
#include "Tests/AddPair.h"
#include "Tests/ApplyForce.h"
#include "Tests/BodyTypes.h"
#include "Tests/Breakable.h"
#include "Tests/Bridge.h"
#include "Tests/BulletTest.h"
#include "Tests/Cantilever.h"
#include "Tests/Car.h"
#include "Tests/ContinuousTest.h"
#include "Tests/Chain.h"
#include "Tests/CharacterCollision.h"
#include "Tests/CollisionFiltering.h"
#include "Tests/CollisionProcessing.h"
#include "Tests/CompoundShapes.h"
#include "Tests/Confined.h"
#include "Tests/ConvexHull.h"
#include "Tests/ConveyorBelt.h"
#include "Tests/DistanceTest.h"
#include "Tests/Dominos.h"
#include "Tests/DumpShell.h"
#include "Tests/DynamicTreeTest.h"
#include "Tests/EdgeShapes.h"
#include "Tests/EdgeTest.h"
#include "Tests/Gears.h"
#include "Tests/Mobile.h"
#include "Tests/MobileBalanced.h"
#include "Tests/MotorJoint.h"
#include "Tests/OneSidedPlatform.h"
#include "Tests/Pinball.h"
#include "Tests/PolyCollision.h"
#include "Tests/PolyShapes.h"
#include "Tests/Prismatic.h"
#include "Tests/Pulleys.h"
#include "Tests/Pyramid.h"
#include "Tests/RayCast.h"
#include "Tests/Revolute.h"
#include "Tests/RopeJoint.h"
#include "Tests/SensorTest.h"
#include "Tests/ShapeEditing.h"
#include "Tests/SliderCrank.h"
#include "Tests/SphereStack.h"
#include "Tests/TheoJansen.h"
#include "Tests/Tiles.h"
#include "Tests/TimeOfImpact.h"
#include "Tests/Tumbler.h"
#include "Tests/VaryingFriction.h"
#include "Tests/VaryingRestitution.h"
#include "Tests/VerticalStack.h"
#include "Tests/Web.h"

TestEntry g_testEntries[] =
{
	{"Ray-Cast", RayCast::Create},
	{"Dump Shell", DumpShell::Create},
	{"Convex Hull", ConvexHull::Create},
	{"Apply Force", ApplyForce::Create},
	{"Continuous Test", ContinuousTest::Create},
	// {"Time of Impact", TimeOfImpact::Create},
	{"Motor Joint", MotorJoint::Create},
	{"One-Sided Platform", OneSidedPlatform::Create},
	{"Mobile", Mobile::Create},
	{"MobileBalanced", MobileBalanced::Create},
	{"Conveyor Belt", ConveyorBelt::Create},
	{"Gears", Gears::Create},
	{"Varying Restitution", VaryingRestitution::Create},
	{"Tumbler", Tumbler::Create},
	{"Tiles", Tiles::Create},
	{"Cantilever", Cantilever::Create},
	{"Character Collision", CharacterCollision::Create},
	{"Edge Test", EdgeTest::Create},
	{"Body Types", BodyTypes::Create},
	{"Shape Editing", ShapeEditing::Create},
	{"Car", Car::Create},
	{"Prismatic", Prismatic::Create},
	{"Vertical Stack", VerticalStack::Create},
	{"SphereStack", SphereStack::Create},
	{"Revolute", Revolute::Create},
	{"Pulleys", Pulleys::Create},
	{"Polygon Shapes", PolyShapes::Create},
	{"Web", Web::Create},
	{"RopeJoint", RopeJoint::Create},
	{"Pinball", Pinball::Create},
	{"Bullet Test", BulletTest::Create},
	{"Confined", Confined::Create},
	{"Pyramid", Pyramid::Create},
	{"Theo Jansen's Walker", TheoJansen::Create},
	{"Edge Shapes", EdgeShapes::Create},
	{"PolyCollision", PolyCollision::Create},
	{"Bridge", Bridge::Create},
	{"Breakable", Breakable::Create},
	{"Chain", Chain::Create},
	{"Collision Filtering", CollisionFiltering::Create},
	{"Collision Processing", CollisionProcessing::Create},
	{"Compound Shapes", CompoundShapes::Create},
	{"Distance Test", DistanceTest::Create},
	{"Dominos", Dominos::Create},
	{"Dynamic Tree", DynamicTreeTest::Create},
	{"Sensor Test", SensorTest::Create},
	{"Slider Crank", SliderCrank::Create},
	{"Varying Friction", VaryingFriction::Create},
	{"Add Pair Stress Test", AddPair::Create},
};

int g_totalEntries = sizeof(g_testEntries) / sizeof(g_testEntries[0]);
