/*
 *  MessageDialog.cpp
 *  Ball_Game_Final
 *
 *  Created by PRoTeW on 07/02/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include <QtGui> 
#include <iostream>

#include "MessageDialog.h"
#include "GLWorldViewer.h"

MessageDialog :: MessageDialog( QWidget * parent, QString msg, std :: vector<RECORD*> recs )
:QDialog( parent )
{
	initComponents();
	lbl_message->setText( "<h1>" + msg + "</h1>" );
	records = recs;
	showRecords();
}
//SLOTS
void MessageDialog :: ok( void )
{
	saveRecords( "ball_game_records.pw" );
	( ( GLWorldViewer* ) parent() )->startStopTimer();
}
void MessageDialog :: exit( void )
{
	saveRecords( "ball_game_records.pw" );
	(( QWidget* )parent()->parent()->parent())->close();
}
int MessageDialog :: getLocalId( RECORD * record )
{
	int founded_id = -1;
	for ( size_t best_id = 0; best_id < records.size() && founded_id == -1; best_id++ )
	{
		if( record->score > records[ best_id ]->score )
		{
			founded_id = ( int ) best_id;
		}
	}
	return founded_id;
}
void MessageDialog :: setEndMessage( RECORD * record )
{
	//BATEU RECORDE
	int local_id = getLocalId( record );
	if( local_id != -1 )
	{
		lbl_message->setText( "<h1>BATEU RECORD !! COLOQUE SEU NOME</h1>" );
		
		for ( int id = dates.size() - 1; id > local_id; id-- )
			dates[ id ]->setText( dates[ id - 1 ]->text() );
		for ( int id = names.size() - 1; id > local_id; id-- )
			names[ id ]->setText( names[ id - 1 ]->text() );
		for ( int id = scores.size() - 1; id > local_id; id-- )
			scores[ id ]->setText( scores[ id - 1 ]->text() );
		
		names[ local_id ]->setEnabled( true );
		//
		QTime now = QTime :: currentTime();
		QDate today = QDate :: currentDate();
		char str_auxiliar[100];
		sprintf( str_auxiliar, "%d/%d/%d-%d:%d", today.day(), today.month(), today.year(), now.hour(), now.minute() );
		dates[ local_id ]->setText( str_auxiliar );
		//
		sprintf( str_auxiliar, "<h3> %d Balls </h3>", ( ( GLWorldViewer* ) parent() )->getBallsCount() );
		scores[ local_id ]->setText( str_auxiliar );
	}
	//APENAS ACABOU
	else {
		lbl_message->setText( "<h1>GAME OVER !!!</h1>" );
	}
}
void MessageDialog :: createFalseRecords( std :: string file_name, int maximum_records )
{
	std :: ofstream out( file_name.c_str(), std::ios::out );
	//
	for( int rid = 0; rid < maximum_records; rid++ )
	{
		out << "BARBARA STRAISSAND###" << maximum_records - rid << "###11/09/00-09:15" << std :: endl;
	}
}
void MessageDialog :: saveRecords( std :: string file_name )
{
	for ( size_t nid = 0; nid < names.size(); nid++ )
		names[ nid ]->setEnabled( false );
	
	std :: ofstream out( file_name.c_str(), std::ios::out );
	if( out.good() )
	{
	
	for ( size_t rid = 0; rid < records.size(); rid++ ) {
		//
		RECORD * record = new RECORD;
		//
		record->name = names[ rid ]->text().toStdString();
		//
		std :: vector< std :: string > score_parts = returnSplitVector( scores[ rid ]->text().toStdString(), " " );
		record->score = atoi( score_parts[1].c_str() );
		//
		record->date = dates[ rid ]->text().toStdString();
		//
		out << record->name << "###" << record->score << "###" << record->date << std :: endl;
	}
	}
		else {
			std::cout << "NAO ROLOU ARQUIVO '" << file_name << "'" << std::endl;
		}
}
void MessageDialog :: showRecords( void )
{
	for ( size_t rid = 0; rid < records.size(); rid++ ) {
		char str_entry[100];
		//
		sprintf( str_entry, "<h3> %d Balls </h3>", records[ rid ]->score );
		QLabel * score_entry = new QLabel( str_entry );
		scores.push_back( score_entry );
		//
		QLineEdit * name_entry = new QLineEdit( records[ rid ]->name.c_str() );
		name_entry->setEnabled( false );
		names.push_back( name_entry );
		//
		QLabel * date_entry = new QLabel( records[ rid ]->date.c_str() );
		dates.push_back( date_entry );
		//
		QHBoxLayout	* entry_layout = new QHBoxLayout;
		entry_layout->addWidget( score_entry );
		entry_layout->addWidget( name_entry );
		entry_layout->addWidget( date_entry );
		viewer_layout->addLayout( entry_layout );
	}
}
std :: string MessageDialog :: loadFileContent( std :: string file_name )
{
	std :: ifstream file( file_name.c_str() );
	std :: string content = "";
	if( file.good() )
	{
		char file_character;
		file.get( file_character );
		while( !file.eof() )
		{
			content += file_character;
			file.get( file_character );
		}
		file.close();
		return content;
	}
	else {
		std::cout << "NAO ROLOU ARQUIVO '" << file_name << "'" << std::endl;
		return "";
	}
}
std :: vector< std :: string > MessageDialog :: returnSplitVector( std :: string line, std :: string separator )
{
	std::vector< std :: string > line_elements;
	std :: string accumulator = "";
	int separator_size = separator.size();
	for ( size_t id = 0; id < line.size(); id++) {
		int matches_count = 0;
		for ( int id_sep = 0; id_sep < separator_size; id_sep++) 
		{
			if( line[ id + id_sep ] == separator[ id_sep ] )
			{
				matches_count++;
			}
		}
		if( matches_count == separator_size )
		{
			if( !accumulator.empty() )
				line_elements.push_back( accumulator );
			accumulator = "";
			id += separator_size - 1;
		}
		else {
			accumulator += line[id];
		}
	}
	if( !accumulator.empty() )
		line_elements.push_back( accumulator );
	return line_elements;
}
void MessageDialog :: initComponents()
{
	connect( this, SIGNAL( accepted() ), this, SLOT( ok() ) );
	connect( this, SIGNAL( rejected() ), this, SLOT( exit() ) );
	//
	//VIEWER LAYOUT
	viewer_layout	= new QVBoxLayout;
	//
	//LABEL MESSAGE
	lbl_message		= new QLabel;
	viewer_layout->addWidget( lbl_message );
	//BUTTONS LAYOUT
	buttons_layout = new QHBoxLayout;
	//
	btn_accept = new QPushButton( "START" );
	connect( btn_accept, SIGNAL( clicked() ), this, SLOT( accept() ) );
	buttons_layout->addWidget( btn_accept );
	//
	btn_refuse = new QPushButton( "EXIT" );
	connect( btn_refuse, SIGNAL( clicked() ), this, SLOT( reject() ) );
	buttons_layout->addWidget( btn_refuse );
	//
	//MAIN LAYOUT
	main_layout		= new QVBoxLayout;
	main_layout->addLayout( viewer_layout );
	main_layout->addLayout( buttons_layout );
	this->setLayout( main_layout );
}


