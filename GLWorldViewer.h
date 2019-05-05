/*
 *  GLWorldViewer.h
 *  3DChallenge
 *
 *  Created by PRoTeW on 13/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GLWORLDVIEWER_H
#define GLWORLDVIEWER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <list>

#include <QGLWidget>
#include <QTimer>
#include <QTabletEvent>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Box2D.h"
#include "CollisionDetect.h"
#include "GroundBlock.h"
#include "SphereObject.h"
#include "MessageDialog.h"

class GLWorldViewer : public QGLWidget {
	
	Q_OBJECT
	
private: 
	//
	//PHYSICS
	//
	b2Vec2	* gravity;
	b2World * world;

	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	//
	MessageDialog * dialog;
	//
	//
	//GAME LOGICS
	//
	int					lives;
	int					balls_counter;
	//
	float32				tickness;
	GroundBlock *		temporary_base;
	//
	b2Vec2		*		base_shadow_center;
	b2Vec2		*		shadow_cursor_center;
	GroundBlock *		new_wall;
	//
	b2Vec2		*		h_stretch;
	b2Vec2		*		v_stretch;
	bool				stretching;
	bool				vertical;
	bool				reach_x, reach_y;
	CollisionDetect *	collision_detector;
	
	int					maximum_records;
	std :: vector<RECORD*> records;
	//
	//
	float32 xview;
	float32 yview;
	//
	long clock;
	QTimer * timer;
	
	double width;
	double height;
	
	b2MouseJoint *mouse_joint;
	
	std::list<Object*> objects;
	std::list<Object*> balls;
	std::list<Object*>::iterator object_it;
	//
	std::list<Object*> already_collided;
	//
	//
	b2Vec2 * test_point;
	//
	public slots:
	void turn( void );

public: 
	GLWorldViewer( QWidget *, double, double );
	//
	void projection( void );
	void drawTemporary( void );
	void createObject( b2Vec2* );
	Object* objectHited( b2Vec2 );
	//
	b2Vec2* QTtoOpenGL( b2Vec2* );
	b2Vec2* OpenGLtoQT( b2Vec2* );
	b2Vec2* OpenGltoBox2d( b2Vec2* );
	b2Vec2* Box2dtoOpenGl( b2Vec2* );
	//
	//
	void stretch( void );
	void testSuccess( void );
	void testStretch( void );
	//
	bool shadowCursorCollides( void );
	void drawShadowCursor( void );
	void drawBaseShadow( void );
	void createWall( void );
	void destroyTemporary( void );
	void properFill( void );
	bool sectorHasBall( b2Vec2 *, b2Vec2 * );
	bool fillEnough( void );
	//
	void placeWalls( void );
	void placeBalls( void );
	void loadNextStage( void );
	//
	void loadRecords( void );
	//
	void startStopTimer( void );
	int getBallsCount( void );
	
protected: 
	void initializeGL( void ); 
	void resizeGL( int, int ); 
	void paintGL( void ); 
	void keyPressEvent( QKeyEvent * );
	void mousePressEvent( QMouseEvent * );
	void enterEvent( QEvent * );
	void leaveEvent( QEvent * );
	void mouseMoveEvent( QMouseEvent * ); 
	void mouseReleaseEvent( QMouseEvent * );
	void mouseDoubleClickEvent( QMouseEvent * );
	void tabletEvent( QTabletEvent * );
	void initComponents( void );
};

#endif
