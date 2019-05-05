/*
 *  Object.h
 *  FirstBox2D
 *
 *  Created by PRoTeW on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "Box2D/Box2D.h"
#include <GL/gl.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <typeinfo>

enum OBJECT_TYPE { BALL = 0, WALL = 1, BASE = 2, FILL = 3 };

class Object {
protected:
	
	int object_id;
	
	float32 angle;
	
	bool selected;
	
	b2World				*world;
	b2Vec2				*position;
	b2Vec2				*dimension;
	
	float32				density;
	float32				friction;
	
	b2PolygonShape		shape;
	b2BodyDef			body_def;
	b2Body				*body;
	b2FixtureDef fixture_definition;
	
	b2Fixture *fixture;
	
public:
	Object( int, b2World *, b2Vec2 *, b2Vec2 * );
	b2Vec2* circlePoint( float, b2Vec2 *, float );
	//
	virtual void draw( void );
	virtual void Destroy( void );
	virtual ~Object( void );
	
	//GETS
	int getId( void );
	b2World*	getWorld( void );
	b2Vec2*		getPosition( void );
	b2Vec2*		getDimension( void );
	
	b2PolygonShape		getShape( void );
	b2BodyDef			GetBodyDef( void );
	b2Body*				getBody( void );
	b2Fixture*			getFixture( void );
	//SETS
	void setDensity( float32 );
	void setFriction( float32 );
	//GETS
	void setId( int );
};

class FixData {
public:
	OBJECT_TYPE object_type;
	bool doomed;
};

#endif
