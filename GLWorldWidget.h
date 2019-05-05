/*
 *  GLWorldWidget.h
 *  3DChallenge
 *
 *  Created by PRoTeW on 15/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GLWORLDWIDGET_H
#define GLWORLDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "GLWorldViewer.h"

class GLWorldWidget : public QWidget
{
	Q_OBJECT
	
public:
	GLWorldWidget( QWidget* );
	void initComponents( void );
	void setLivesLabelText( int lives );
public slots:
	

private:
	
	//VIEWER
	GLWorldViewer	*	world_viewer;
	//LABEL LIVES
	QLabel			*	lbl_lives;
	//MAIN LAYOUT
	QVBoxLayout		*	viewer_layout;
	QHBoxLayout		*	main_layout;
};

#endif
