/*
 *  SphereObject.h
 *  FirstBox2D_1
 *
 *  Created by PRoTeW on 11/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SPHEREOBJECT_H
#define SPHEREOBJECT_H

#include "Object.h"

class SphereObject : public Object {
	GLuint display_list;
	float32 ray;
	b2CircleShape circle_shape;
public:
	SphereObject( int, b2World *, b2Vec2 *, float32 );
	void createDisplayList( void );
	void fillDisplayList( void );
	void draw( void );
	~SphereObject( void );
	//GETS
	float32 getRay( void );
};

#endif