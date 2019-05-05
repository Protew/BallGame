/*
 *  MainWindow.h
 *  PDBQuickViewer_04
 *
 *  Created by PRoTeW on 26/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTabWidget>
#include <QTimer>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "GLWorldWidget.h"

class MainWindow : public QTabWidget
{
	Q_OBJECT
	
	long seconds_counter;
	
public:
	MainWindow( QWidget * parent = 0 );
	void initWidgets( void );
	//
	void clearPlayingTime( void );
	void countPlayingTime( void );
	
	public slots:
	void turn( void );
	
private:
	GLWorldWidget		*	world_widget;
	QTimer				*	timer;
	
	//MAIN WINDOW LAYOUTS
	QHBoxLayout			*	base_buttons_layout;
	QVBoxLayout			*	main_layout;
};

#endif
