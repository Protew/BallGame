/*
 *  GroundBlock.h
 *  FirstBox2D
 *
 *  Created by PRoTeW on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GROUNDBLOCK_H
#define GROUNDBLOCK_H

#include "Object.h"

#include <vector>

class GroundBlock : public Object {
	GLuint display_list;
public:
	GroundBlock( int, b2World *, b2Vec2 *, b2Vec2 * );
	GroundBlock( int, b2World *, b2Vec2 *, b2Vec2 *, float32 );
	void createDisplayList( void );
	void fillDisplayList( void );
	void draw( void );
	~GroundBlock( void );
	//
	//SETS
	void setObjectType( OBJECT_TYPE );
	//
};

#endif