/*
 *  Object.cpp
 *  FirstBox2D
 *
 *  Created by PRoTeW on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Object.h"

Object :: Object( int object_id, b2World *world, b2Vec2 *position, b2Vec2 *dimension )
{
    this->object_id = object_id;
    this->world = world;
    this->position = position;
    this->dimension = dimension;
	
	selected = false;
}
//SETS
void Object :: setId( int value )
{
	object_id = value;
}
void Object :: setDensity( float32 density )
{
	body->DestroyFixture( &body->GetFixtureList()[0] );
    fixture_definition.density = density;
	body->CreateFixture( &fixture_definition );
}
void Object :: setFriction( float32 friction )
{
	body->DestroyFixture( &body->GetFixtureList()[0] );
    fixture_definition.friction = friction;
	body->CreateFixture( &fixture_definition );
}
//GETS
int Object :: getId( void )
{
	return object_id;
}
b2World* Object :: getWorld( void )
{
	return world;
}
b2Vec2* Object :: getPosition( void )
{
	return new b2Vec2( body->GetWorldCenter().x, body->GetWorldCenter().y );
}
b2Vec2* Object :: getDimension( void )
{
	return dimension;
}
b2PolygonShape Object :: getShape( void )
{
	return shape;
}
b2BodyDef Object :: GetBodyDef( void )
{
	return body_def;
}
b2Body* Object :: getBody( void )
{
	return body;
}
b2Fixture* Object :: getFixture( void )
{
	return fixture;
}
b2Vec2* Object :: circlePoint( float angle, b2Vec2 *center, float ray )
{
    return new b2Vec2( cosf( angle ) * ray + center->x, sinf( angle ) * ray + center->y );
}
void Object :: Destroy( void )
{
	world->DestroyBody( body );
    body = nullptr;
}
void Object :: draw( void ){}
Object :: ~Object( void ){}
