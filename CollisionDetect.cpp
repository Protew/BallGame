/*
 *  CollisionDetect.cpp
 *  FirstBox2D_4
 *
 *  Created by PRoTeW on 16/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "CollisionDetect.h"
#include "GroundBlock.h"
#include <typeinfo>
#include <cmath>

CollisionDetect :: CollisionDetect( b2World* W )
{
	world = W;
}
void CollisionDetect :: BeginContact( b2Contact* contact )
{
    FixData *data_a = static_cast<FixData*> ( contact->GetFixtureA()->GetUserData() );
    FixData *data_b = static_cast<FixData*> ( contact->GetFixtureB()->GetUserData() );
	
	if( data_a->object_type == BALL && data_b->object_type == BASE )
	{
		data_b->doomed = true;
	}
	else if( data_a->object_type == BASE && data_b->object_type == BALL )
	{
		data_a->doomed = true;
	}
}
void CollisionDetect :: EndContact( b2Contact* contact )
{	
	contact->IsTouching();
}
void CollisionDetect :: PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{
	contact->IsTouching();
    std::cout << "PreSolve - oldManifold( " << oldManifold->localPoint.x << ", " << oldManifold->localPoint.y << " )" << std::endl;
}
void CollisionDetect :: PostSolve( b2Contact* contact, const b2ContactImpulse* impulse )
{
	contact->IsTouching();
    //
    std::cout << "PostSolve - impulse( " << impulse->normalImpulses[ 0 ] << ", " << impulse->normalImpulses[ 1 ] << " )" << std::endl;

}
