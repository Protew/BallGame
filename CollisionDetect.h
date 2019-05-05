/*
 *  CollisionDetect.h
 *  FirstBox2D_4
 *
 *  Created by PRoTeW on 16/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COLLISIONDETECT_H
#define COLLISIONDETECT_H

#include "Box2D.h"
#include "b2Settings.h"
#include "b2WorldCallbacks.h"
#include <iostream>
#include <cstring>
#include <vector>

struct b2Vec2;
struct b2Transform;
class b2Fixture;
class b2Body;
class b2Joint;
class b2Contact;
struct b2ContactPoint;
struct b2ContactResult;
struct b2Manifold;

class CollisionDetect : public b2ContactListener
{
	std::vector<int> indexes_a;
	std::vector<int> indexes_b;
	b2World *world;
public:
	CollisionDetect( b2World * );
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve( b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve( b2Contact* contact, const b2ContactImpulse* impulse );
};

#endif