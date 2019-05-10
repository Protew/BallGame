/*
 *  GroundBlock.cpp
 *  FirstBox2D
 *
 *  Created by PRoTeW on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GroundBlock.h"

GroundBlock :: GroundBlock( int ID, b2World * W, b2Vec2 *P, b2Vec2 *D )
: Object( ID, W, P, D ){
	
	angle = 0;
	body_def.type = b2_staticBody;
	
	body_def.position.Set( position->x, position->y );

	body = world->CreateBody( &body_def );
	shape.SetAsBox( dimension->x, dimension->y, body->GetPosition(), angle );

	fixture_definition.shape = &shape;
	fixture_definition.density = 1.0f;
	fixture_definition.friction = 1.0f;
	fixture_definition.userData = new FixData;
    static_cast<FixData*>( fixture_definition.userData)->object_type = WALL;
    static_cast<FixData*>( fixture_definition.userData)->doomed = false;
	fixture = body->CreateFixture( &fixture_definition );
	//
	createDisplayList();
}
GroundBlock :: GroundBlock( int ID, b2World * W, b2Vec2 *P, b2Vec2 *D, float32 A  )
: Object( ID, W, P, D ){
	
	angle = A;
	
	body_def.position.Set( position->x, position->y );
	body = world->CreateBody( &body_def );
	
	shape.SetAsBox( dimension->x, dimension->y, body->GetPosition(), angle );
	//SetAsBox( float32 hx, float32 hy, const b2Vec2& center, float32 angle );
	
	fixture_definition.shape = &shape;
	fixture_definition.density = 1.0f;
	fixture_definition.friction = 0.75f;
	fixture_definition.userData = new FixData;
    static_cast<FixData*>( fixture_definition.userData)->object_type = WALL;
    static_cast<FixData*>( fixture_definition.userData)->doomed = false;
	fixture = body->CreateFixture( &fixture_definition );
	createDisplayList();
}
void GroundBlock :: setObjectType( OBJECT_TYPE obj_type )
{
	body->DestroyFixture( fixture );
	fixture_definition.shape = &shape;
	fixture_definition.density = 1.0f;
	fixture_definition.friction = 0.75f;
	fixture_definition.userData = new FixData;
    static_cast<FixData*>( fixture_definition.userData)->object_type = obj_type;
    static_cast<FixData*>( fixture_definition.userData)->doomed = false;
	fixture = body->CreateFixture( &fixture_definition );
}
void GroundBlock :: createDisplayList( void )
{
	//PEGA UM NUMERO DE LISTA DISPONÍVEL
	display_list = glGenLists( 1 );
	//INVOCA A LISTA
	glNewList( display_list, GL_COMPILE );
	//PREENCHE COM OS VÉRTICES
	fillDisplayList();
	//FIM DA CRIAÇÃO 
	glEndList();
}
void GroundBlock :: fillDisplayList( void )
{
	//glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
	//glBegin( GL_LINE_LOOP );
	//for( int i = 0; i < shape.GetVertexCount(); i++ )
		//glVertex2d( shape.GetVertex(i).x, shape.GetVertex(i).y );
	//glEnd();
	glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
	glBegin( GL_POLYGON );
	for( int i = 0; i < shape.GetVertexCount(); i++ )
        glVertex2d( static_cast<double>( shape.GetVertex(i).x ), static_cast<double>( shape.GetVertex(i).y ) );
	glEnd();
}
void GroundBlock :: draw( void )
{
	glPushMatrix();
	
    glTranslated( static_cast<double>( body->GetPosition().x ), static_cast<double>( body->GetPosition().y ), 0.0 );
	glRotatef( ( body->GetAngle() / b2_pi ) * 180, 0, 0, 1 );
	
	glCallList( display_list );
	
	glPopMatrix(); 
}
GroundBlock :: ~GroundBlock( void ){}
