/*
* Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com
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

#ifndef BOX2D_H
#define BOX2D_H

/**
\mainpage Box2D API Documentation

\section intro_sec Getting Started

For documentation please see http://box2d.org/documentation.html

For discussion please visit http://box2d.org/forum
*/

// These include files constitute the main Box2D API

#include "Common/b2Settings.h"

#include "Collision/Shapes/b2CircleShape.h"
#include "Collision/Shapes/b2PolygonShape.h"

#include "Collision/b2BroadPhase.h"
#include "Collision/b2Distance.h"
#include "Collision/b2DynamicTree.h"
#include "Collision/b2TimeOfImpact.h"

#include "Dynamics/b2Body.h"
#include "Dynamics/b2Fixture.h"
#include "Dynamics/b2WorldCallbacks.h"
#include "Dynamics/b2TimeStep.h"
#include "Dynamics/b2World.h"

#include "Dynamics/Contacts/b2Contact.h"

#include "Dynamics/Joints/b2DistanceJoint.h"
#include "Dynamics/Joints/b2FrictionJoint.h"
#include "Dynamics/Joints/b2GearJoint.h"
#include "Dynamics/Joints/b2LineJoint.h"
#include "Dynamics/Joints/b2MouseJoint.h"
#include "Dynamics/Joints/b2PrismaticJoint.h"
#include "Dynamics/Joints/b2PulleyJoint.h"
#include "Dynamics/Joints/b2RevoluteJoint.h"
#include "Dynamics/Joints/b2WeldJoint.h"

#endif
