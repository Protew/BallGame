/*
 *  GLWorldWidget.cpp
 *  3DChallenge
 *
 *  Created by PRoTeW on 13/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <QtGui> 
#include "GLWorldWidget.h"
#include <iostream>

GLWorldWidget :: GLWorldWidget( QWidget * parent )
:QWidget( parent )
{
	initComponents();
	///setMinimumSize( 1200, 600 );
	//setFixedSize(sizeHint().width(), sizeHint().height());
}
void GLWorldWidget :: setLivesLabelText( int lives )
{
	char str_lives[3];
	sprintf( str_lives, "%d", lives );
	lbl_lives->setText( str_lives );
}
void GLWorldWidget :: initComponents()
{
	//VIEWER LAYOUT
	viewer_layout	= new QVBoxLayout;
	//
	//LABEL LIVES
	lbl_lives		= new QLabel;
	viewer_layout->addWidget( lbl_lives );
	//WORLD VIEWER
	world_viewer	= new GLWorldViewer( this, 1000, 500 );
	viewer_layout->addWidget( world_viewer );
	//
	//MAIN LAYOUT
	main_layout		= new QHBoxLayout;
	main_layout->addLayout( viewer_layout );
	this->setLayout( main_layout );
}

