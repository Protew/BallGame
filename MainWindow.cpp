/*
 *  MainWindow.cpp
 *  PDBQuickViewer_04
 *
 *  Created by PRoTeW on 26/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <QtGui>

#include "MainWindow.h"

MainWindow :: MainWindow( QWidget * parent )
:QTabWidget( parent )
{
	initWidgets();
	timer = new QTimer;
	connect( timer, SIGNAL( timeout() ), this, SLOT( turn() ) );
	seconds_counter = 0;
	//timer->start();
	setWindowTitle( tr( " BALL GAME " ) );
	//setFixedSize(sizeHint().width(), sizeHint().height());
}
void MainWindow :: countPlayingTime( void )
{
	if( timer->isActive() )
		timer->stop();
	else
		timer->start( 1000 );
}
void MainWindow :: clearPlayingTime( void )
{
	seconds_counter = 0;
}
void MainWindow :: turn( void )
{
	seconds_counter++;
	char str_seconds[100];
	sprintf( str_seconds, "BALL GAME - %ld segundos de vida perdidos", seconds_counter );
	setWindowTitle( tr( str_seconds ) );
}
void MainWindow :: initWidgets( void )
{
	base_buttons_layout = new QHBoxLayout;
	
	world_widget = new GLWorldWidget( this );
	
	//
	//MAIN LAYOUT
	//
	main_layout = new QVBoxLayout;
	//base_buttons_layout->addWidget( btn_load_protein );
	main_layout->addWidget( world_widget );
	//main_layout->addLayout( base_buttons_layout );
	setLayout( main_layout );
}