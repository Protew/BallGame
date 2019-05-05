/*
 *  MessageDialog.h
 *  Ball_Game_Final
 *
 *  Created by PRoTeW on 07/02/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <fstream>

struct RECORD {
	int score;
	std :: string name;
	std :: string date;
};

class MessageDialog : public QDialog
{
	Q_OBJECT
	
public:
	MessageDialog( QWidget*, QString, std :: vector<RECORD*> );
	void initComponents( void );
	//
	void showRecords( void );
	//
	int getLocalId( RECORD * );
	void setEndMessage( RECORD * );
	void saveRecords( std :: string );
	//
	void createFalseRecords( std :: string, int );
	std :: string loadFileContent( std :: string );
	std :: vector< std :: string > returnSplitVector( std :: string, std :: string );
	//
	std :: vector<QLineEdit*> names;
	std :: vector<QLabel*> scores;
	std :: vector<QLabel*> dates;
	
	//
	public slots:
	void ok( void );
	void exit( void );
	
	
private:
	
	std :: vector<RECORD*> records;
	
	//LABEL LIVES
	QLabel			*	lbl_message;
	//
	QPushButton		*	btn_accept;
	QPushButton		*	btn_refuse;
	//MAIN LAYOUT
	QVBoxLayout		*	viewer_layout;
	QHBoxLayout		*	buttons_layout;
	QVBoxLayout		*	main_layout;
};

#endif
