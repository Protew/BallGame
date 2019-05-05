/*
 *  GLWorldViewer.cpp
 *  3DChallenge
 *
 *  Created by PRoTeW on 13/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLWorldViewer.h"
#include "GLWorldWidget.h"
#include "MainWindow.h"

b2Vec2* GLWorldViewer ::QTtoOpenGL( b2Vec2* coord )
{
	//TRANSFORMA COORD QT -> OPENGL
	float32 wx = coord->x;
	float32 vxmax = (float32) xview + width;
	float32 vxmin = (float32) xview;
	float32 wxmax = (float32) width;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) yview;
	float32 vymin = (float32) yview + height;
	float32 wymax = (float32) height;
	float32 wymin = (float32) 0;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLWorldViewer :: OpenGLtoQT( b2Vec2* coord )
{
	//TRANSFORMA OPENGL -> COORD QT
	float32 wx = coord->x;
	float32 vxmax = (float32) width;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) xview + width;
	float32 wxmin = (float32) xview;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) height;
	float32 vymin = (float32) 0;
	float32 wymax = (float32) yview;
	float32 wymin = (float32) yview + height;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLWorldViewer ::OpenGltoBox2d( b2Vec2* coord ) 
{
	//TRANSFORMA COORD OPENGL -> BOX2D
	float32 wx = coord->x;
	float32 vxmax = (float32) width/2;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) width;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) 0;
	float32 vymin = (float32) height/2;
	float32 wymax = (float32) 0;
	float32 wymin = (float32) height;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLWorldViewer :: Box2dtoOpenGl( b2Vec2* coord ) 
{
	//TRANSFORMA COORD BOX2D -> OPENGL
	float32 wx = coord->x;
	float32 vxmax = (float32) width;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) width/2;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) 0;
	float32 vymin = (float32) height;
	float32 wymax = (float32) 0;
	float32 wymin = (float32) height/2;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
GLWorldViewer :: GLWorldViewer( QWidget *parent, double W, double H ) 
: QGLWidget( parent )
{	
	width = W;
	height = H;
	
	clock = 0;
	
	xview = yview = 0;
	
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;
	
	gravity = new b2Vec2( 0.0f, 0.0f );
	world = new b2World( *gravity, true );
	collision_detector = new CollisionDetect( world );
	world->SetContactListener( collision_detector );
	
	timer = new QTimer;
	connect( timer, SIGNAL( timeout() ), this, SLOT( turn() ) );
	//timer->start();
	
	setFormat( QGLFormat( QGL::DoubleBuffer | QGL::DepthBuffer ) );
	setFixedSize( width, height );
	//
	//
	//GAME CONCEPTS
	//
	tickness = 6.0f;
	maximum_records = 5;
	//
	lives = 3;
	balls_counter = 1;
	//
	( ( GLWorldWidget * ) this->parent() )->setLivesLabelText( lives );
	//
	temporary_base = NULL;
	base_shadow_center = NULL;
	shadow_cursor_center = NULL;
	stretching = false;
	vertical = true;
	reach_x = reach_y = false;
	//
	//
	h_stretch = new b2Vec2( tickness, tickness );
	v_stretch = new b2Vec2( tickness, tickness );
	//
	test_point = new b2Vec2( 0, 0 );
	//
	loadRecords();
	dialog = new MessageDialog( this, "RECORDS", records );
	dialog->show();
	setFocus();
	
}
void GLWorldViewer :: loadRecords( void )
{
	records.clear();
	std :: string file_content = dialog->loadFileContent( "ball_game_records.pw" );
	//
	if( file_content.empty() )
	{
		std :: cout << "FIRST TIME USE !" << std :: endl;
		dialog->createFalseRecords( "ball_game_records.pw", maximum_records );
		loadRecords();
	}
	else {
		std :: vector< std :: string > file_lines = dialog->returnSplitVector( file_content, "\n" );
		//
		for( size_t lid = 0; lid < file_lines.size(); lid++ )
		{
			std :: vector< std :: string > line_fields = dialog->returnSplitVector( file_lines[lid], "###" );
			RECORD * temporary = new RECORD;
			temporary->name = line_fields[0];
			temporary->score = atoi( line_fields[1].c_str() );
			temporary->date = line_fields[2];
			records.push_back( temporary );
		}
	}
}
int GLWorldViewer :: getBallsCount( void )
{
	return balls_counter;
}
bool alreadyExist( std :: list < Object* > obj_list, Object * target )
{
	std::list<Object*>::iterator obj_it;
	for ( obj_it = obj_list.begin(); obj_it != obj_list.end(); obj_it++)
		if( ( Object* ) *obj_it  == target )
			return true;
	return false;
}
void GLWorldViewer :: createWall( void )
{
	//PEGA CENTRO E DIMENSAO
	b2Vec2 * center = new b2Vec2( (( base_shadow_center->x - h_stretch->x ) + ( base_shadow_center->x + h_stretch->y ) )/2, (( base_shadow_center->y - v_stretch->x ) + ( base_shadow_center->y + v_stretch->y ) )/2 );
	b2Vec2 * dim = new b2Vec2( fabs(( base_shadow_center->x - h_stretch->x ) - ( base_shadow_center->x + h_stretch->y ) )/2, fabs( ( base_shadow_center->y - v_stretch->x ) - ( base_shadow_center->y + v_stretch->y ) )/2 );
	//CRIA BARREIRA SOLIDA
	new_wall = new GroundBlock( 99, world, OpenGltoBox2d( center ), dim );
	new_wall->setObjectType( FILL );
	//
	objects.push_back( new_wall );
	//
}
void GLWorldViewer :: destroyTemporary( void )
{
	temporary_base->Destroy();
	temporary_base = NULL;
	reach_x = reach_y = stretching = false;
	v_stretch->x = v_stretch->y = h_stretch->x = h_stretch->y = tickness;
	already_collided.clear();
}
bool GLWorldViewer :: fillEnough( void )
{
	float32 total_area = ( ( width - 3.96 * tickness ) * ( height - 3.96 * tickness ) );
	//
	float32 filled_area = 0.0f;
	for ( object_it = objects.begin(); object_it != objects.end(); object_it++)
	{
		Object * target = ( ( Object* ) *object_it );
		if( ( ( FixData* ) target->getFixture()->GetUserData() )->object_type == FILL )
		{
			filled_area += ( 2 * target->getDimension()->x ) * ( 2 * target->getDimension()->y );
		}
	}
	std :: cout << "FILLED " << filled_area << "\nTOTAL " << total_area << "\n% " << filled_area / total_area << std :: endl;
	if( filled_area / total_area >= 1.0f - ( 0.001f * ( int ) balls.size() ) )
		return true;
	return false;
	
}
void GLWorldViewer :: testSuccess( void )
{
	//DERROTA
	if( temporary_base && ( ( FixData* ) temporary_base->getFixture()->GetUserData() )->doomed )
	{
		lives--;
		if( reach_x || reach_y )
		{
			createWall();
		}
		destroyTemporary();
		( ( GLWorldWidget * ) this->parent() )->setLivesLabelText( lives );
	}
	//std :: cout << "LIVES " << lives << std :: endl;
	if( !lives )
	{
		//
		//MOSTRA TELA DERROTA
		//
		std :: cout << "PERDEU !!!" << std :: endl;
		( ( MainWindow * )this->parent()->parent() )->clearPlayingTime();
		RECORD * record = new RECORD;
		record->name =  "";
		record->score = balls_counter;
		//
		dialog->setEndMessage( record );
		dialog->show();
		//
		lives = 2;
		balls_counter = 0;
		loadNextStage();
	}
}
void GLWorldViewer :: testStretch( void )
{
	//TESTA TODOS OS OBJETOS
	bool collides = false;
	for ( object_it = objects.begin(); object_it != objects.end() && !collides; object_it++)
	{
		Object * target = ( ( Object* ) *object_it );
		b2Vec2 * target_center = Box2dtoOpenGl( ( b2Vec2* )&target->getBody()->GetWorldCenter() );
		
		//if( typeid( *target ) == typeid( SphereObject ) )
		
		if ( target != temporary_base && !alreadyExist( already_collided, target ) && typeid( *target ) != typeid( SphereObject ) &&
			base_shadow_center->x - h_stretch->x <= target_center->x + target->getDimension()->x && base_shadow_center->x + h_stretch->y >= target_center->x - target->getDimension()->x &&
			base_shadow_center->y - v_stretch->x <= target_center->y + target->getDimension()->y && base_shadow_center->y + v_stretch->y >= target_center->y - target->getDimension()->y )
		{
			already_collided.push_back( target );
			//
			if( vertical ){
				//BATEU EMBAIXO
				if( !reach_x && base_shadow_center->y > target_center->y )
				{
					reach_x = true;
					std :: cout << "DOWN" << std :: endl;
				}
				//BATEU EM CIMA
				if( !reach_y && base_shadow_center->y < target_center->y )
				{
					reach_y = true;
					std :: cout << "UP" << std :: endl;
				}
			}
			else{
				//BATEU A ESQUERDA
				if( !reach_x && base_shadow_center->x > target_center->x )
				{
					reach_x = true;
					std :: cout << "LEFT" << std :: endl;
				}
				//BATEU A DIREITA
				if( !reach_y && base_shadow_center->x < target_center->x )
				{
					reach_y = true;
					std :: cout << "RIGHT" << std :: endl;
				}
			}
			collides = true;
		}
	}
}
bool GLWorldViewer :: sectorHasBall( b2Vec2 * center, b2Vec2 * dim )
{
	//
	// !!!!!!!!!!!!
	//
	b2Vec2 * real_center = Box2dtoOpenGl( center );
	b2Vec2 * real_dim = new b2Vec2( dim->x * 2, dim->y * 2 );
	//
	for ( object_it = balls.begin(); object_it != balls.end(); object_it++ )
	{
		SphereObject * target = ( ( SphereObject* ) *object_it );
		b2Vec2 * point = target->getPosition();
		//
		std :: cout << "( " << point->x << ", " << point->y << ") " << std :: endl;
		//
		if( point->x <= real_center->x + real_dim->x/2 && point->x >= real_center->x - real_dim->x/2 &&
		   point->y <= real_center->y + real_dim->y/2 && point->y >= real_center->y - real_dim->y/2 )
		{
			return true;
		}
	}
	return false;
}
void GLWorldViewer :: placeWalls( void )
{
	//
	//BASE
	//
	//
	b2Vec2 * center = OpenGltoBox2d( QTtoOpenGL( new b2Vec2( width/2, height - tickness ) ) );
	//BOTTOM
	GroundBlock * bottom = new GroundBlock( 11, world, center, new b2Vec2( width/2, tickness ) );
	//TOP
	center = OpenGltoBox2d( QTtoOpenGL( new b2Vec2( width/2, tickness ) ) );
	GroundBlock * top = new GroundBlock( 22, world, center, new b2Vec2( width/2, tickness ) );
	//LEFT
	center = OpenGltoBox2d( QTtoOpenGL( new b2Vec2( tickness, height/2 ) ) );
	GroundBlock * left = new GroundBlock( 33, world, center, new b2Vec2( tickness, height/2 ) );
	//RIGHT
	center = OpenGltoBox2d( QTtoOpenGL( new b2Vec2( width - tickness, height/2 ) ) );
	GroundBlock * right = new GroundBlock( 44, world, center, new b2Vec2( tickness, height/2 ) );
	//
	objects.push_back( bottom );
	objects.push_back( top );
	objects.push_back( left );
	objects.push_back( right );
}
void GLWorldViewer :: placeBalls( void )
{
	for( int bid = 0; bid < balls_counter; bid++ )
	{
		b2Vec2 * center = OpenGltoBox2d( QTtoOpenGL( new b2Vec2( width/2 + ( bid * ( 2 * tickness ) ), height/2 ) ) );
		SphereObject * ball = new SphereObject( objects.size(), world, center, tickness );
		b2Vec2 * center_effect = new b2Vec2( ball->getBody()->GetWorldCenter().x + ( rand() % (int) ( 2 * tickness ) - tickness ), ball->getBody()->GetWorldCenter().y + ( rand() % (int)( 2 * tickness ) - tickness ) );
		ball->getBody()->ApplyForce( b2Vec2( ( rand() % 2 )? -500 * ball->getBody()->GetMass() : 500 * ball->getBody()->GetMass(), ( rand() % 2 ) ? -500 * ball->getBody()->GetMass() : 500 * ball->getBody()->GetMass() ), *center_effect );
		balls.push_back( ball );
	}
}
void GLWorldViewer :: loadNextStage( void )
{
	timer->stop();
	( ( MainWindow * )this->parent()->parent() )->countPlayingTime();
	balls_counter++;
	lives++;
	//
	temporary_base = NULL;
	base_shadow_center = NULL;
	shadow_cursor_center = NULL;
	stretching = false;
	vertical = true;
	reach_x = reach_y = false;
	//
	h_stretch = new b2Vec2( tickness, tickness );
	v_stretch = new b2Vec2( tickness, tickness );
	//
	test_point = new b2Vec2( 0, 0 );
	//
	//WALLS
	for ( object_it = objects.begin(); object_it != objects.end(); object_it++)
	{
		Object * target = ( ( Object* ) *object_it );
		target->Destroy();
		target = NULL;
	}
	objects.clear();
	//BALLS
	for ( object_it = balls.begin(); object_it != balls.end(); object_it++)
	{
		Object * target = ( ( Object* ) *object_it );
		target->Destroy();
		target = NULL;
	}
	balls.clear();
	placeWalls();
	placeBalls();
	//
	( ( GLWorldWidget * ) this->parent() )->setLivesLabelText( lives );
}
void GLWorldViewer :: properFill( void )
{
	//TESTA TODOS OS OBJETOS
	b2Vec2 * wall_position = new_wall->getPosition();
	GroundBlock * contour_wall = NULL;
	for( int one_time = 0; one_time < 2; one_time++ )
	{
		bool collides = false;
		float32 stretch = 0.0f;
		while( !collides )
		{
			if( vertical )
			{
				switch ( one_time ) {
						//TESTA ESQUERDA
					case 0:
						test_point = new b2Vec2( wall_position->x - stretch, wall_position->y );
						break;
						//TESTA DIREITA
					case 1:
						test_point = new b2Vec2( wall_position->x + stretch, wall_position->y );
						break;
				}
			}
			else {
				switch ( one_time ) {
						//TESTA BAIXO
					case 0:
						test_point = new b2Vec2( wall_position->x, wall_position->y - stretch );
						break;
						//TESTA CIMA
					case 1:
						test_point = new b2Vec2( wall_position->x, wall_position->y + stretch );
						break;
				}
			}
			//
			updateGL();
			//
			for ( object_it = objects.begin(); object_it != objects.end() && !collides; object_it++)
			{
				Object * target = ( ( Object* ) *object_it );
				b2Vec2 * target_center = target->getPosition();
				b2Vec2 * target_dim = target->getDimension();
				
				if ( target != new_wall &&
					test_point->x <= target_center->x + target_dim->x/2 && test_point->x >= target_center->x - target_dim->x/2 &&
					test_point->y <= target_center->y + target_dim->y/2 && test_point->y >= target_center->y - target_dim->y/2 )
				{
					//
					//std :: cout << "ACHOU " << target->getId() << std :: endl;
					contour_wall = ( GroundBlock* ) target;
					collides = true;
				}
			}
			stretch += tickness/5;
		}
		b2Vec2 * dim = NULL, * center = NULL;
		if( contour_wall )
		{
			if( vertical ){
				center = new b2Vec2( ( wall_position->x + contour_wall->getPosition()->x )/ 2, wall_position->y );
				dim = new b2Vec2( stretch, new_wall->getDimension()->y );
			}
			else {
				center = new b2Vec2( wall_position->x, ( wall_position->y + contour_wall->getPosition()->y )/ 2 );
				dim = new b2Vec2( new_wall->getDimension()->x, stretch );
			}
			std :: cout << "[ " << center->x << ", " << center->y << "; " << dim->x << ", " << dim->y << "] " << std :: endl;
			if( !sectorHasBall( center, dim ) )
			{
				std :: cout << "SETOR NAO BOLA" << std :: endl;
				GroundBlock * fill = new GroundBlock( 99, world, center, dim );
				fill->setObjectType( FILL );
				//new_wall->Destroy();
				//objects.remove( new_wall );
				//new_wall = NULL;
				objects.push_back( fill );
			}
			else
				std :: cout << "SETOR TEM BOLA" << std :: endl;
		}
	}
	//PASSOU DE FASE
	if( fillEnough() )
	{
		loadNextStage();
		std :: cout << "PASSOU DE FASE !!!" << std :: endl;
	}
}
void GLWorldViewer :: stretch( void )
{
	//
	//
	if( vertical ){
		if( !reach_x )
			v_stretch->x += 0.2f;
		if( !reach_y )
			v_stretch->y += 0.2f;
	}
	else {
		if( !reach_x )
			h_stretch->x += 0.2f;
		if( !reach_y )
			h_stretch->y += 0.2f;
	}
	//
	testSuccess();
	//
	if( temporary_base )
	{
		temporary_base->Destroy();
		//temporary_base = NULL;
	}
	if( stretching )
	{
		//
		//PEGA CENTRO E DIMENSAO DA BARREIRA TEMPORARIA
		//
		b2Vec2 * center = new b2Vec2( (( base_shadow_center->x - h_stretch->x ) + ( base_shadow_center->x + h_stretch->y ) )/2, (( base_shadow_center->y - v_stretch->x ) + ( base_shadow_center->y + v_stretch->y ) )/2 );
		b2Vec2 * dim = new b2Vec2( fabs(( base_shadow_center->x - h_stretch->x ) - ( base_shadow_center->x + h_stretch->y ) )/2, fabs( ( base_shadow_center->y - v_stretch->x ) - ( base_shadow_center->y + v_stretch->y ) )/2 );
		//
		temporary_base = new GroundBlock( objects.size(), world, OpenGltoBox2d( center ), dim );
		temporary_base->setObjectType( BASE );
		//
		testStretch();
		//
		//SE CHEGOU AOS DOIS LADOS
		if( reach_x && reach_y )
		{
			//CRIA BARREIRA SOLIDA
			createWall();
			//DESTROI BARREIRA TEMPORARIA
			destroyTemporary();
			//PREENCHE OS ESPAÇOS
			properFill();
		}
	}
	//
	
}
//SLOTS
void GLWorldViewer :: turn( void )
{	
	world->Step( timeStep, velocityIterations, positionIterations );
	world->ClearForces();
	//
	if( stretching )
	{
		stretch();
	}
	updateGL();
}
//GETS
void GLWorldViewer :: initializeGL( void )
{
	//PRERROGATIVAS OPENGL
	
	glViewport( 0, 0, width, height );
	
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	
	gluOrtho2D( xview, xview + width, yview, yview + height );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);                 
	glEnable(GL_NORMALIZE);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	
	glShadeModel (GL_SMOOTH);
	
	placeWalls();
	placeBalls();
}
void GLWorldViewer :: resizeGL( int w, int h )
{
	width = w;
	height = h;
	
	glViewport( 0, 0, width, height );
	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	
	gluOrtho2D( xview, xview + width, yview, yview + height );
	
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ();
}
b2Vec2* circlePoint( float angle, b2Vec2 *center, float ray )
{
	return new b2Vec2( cos( angle ) * ray + center->x, sin( angle ) * ray + center->y );
}
void GLWorldViewer :: drawShadowCursor( void )
{
	glColor4f( 0.5f, 0.5f, 0.5f, 0.5f );
	glBegin( GL_POLYGON );
	glVertex2f( shadow_cursor_center->x - tickness, shadow_cursor_center->y - tickness );
	glVertex2f( shadow_cursor_center->x + tickness, shadow_cursor_center->y - tickness );
	glVertex2f( shadow_cursor_center->x + tickness, shadow_cursor_center->y + tickness );
	glVertex2f( shadow_cursor_center->x - tickness, shadow_cursor_center->y + tickness );
	glEnd();
}
void GLWorldViewer :: drawBaseShadow( void )
{
	glColor4f( 0.5f, 0.5f, 0.5f, 0.5f );
	glBegin( GL_POLYGON );
	glVertex2f( base_shadow_center->x - h_stretch->x, base_shadow_center->y - v_stretch->x );
	glVertex2f( base_shadow_center->x + h_stretch->y, base_shadow_center->y - v_stretch->x );
	glVertex2f( base_shadow_center->x + h_stretch->y, base_shadow_center->y + v_stretch->y );
	glVertex2f( base_shadow_center->x - h_stretch->x, base_shadow_center->y + v_stretch->y );
	glEnd();
}
void GLWorldViewer :: paintGL() 
{
	glClearColor ( 0.0, 0.0, 0.0, 1.0);
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//
	//
	//glPushMatrix();
	//glBegin( GL_POINTS );
	//glColor3f( 1, 1, 1 );
	//glVertex2f( Box2dtoOpenGl( test_point )->x, Box2dtoOpenGl( test_point )->y );
	//glEnd();
	//
	//WALLS
	for ( object_it = objects.begin(); object_it != objects.end(); object_it++)
		( ( Object* ) *object_it )->draw();
	//BALLS
	for ( object_it = balls.begin(); object_it != balls.end(); object_it++)
		( ( Object* ) *object_it )->draw();
	//
	if( shadow_cursor_center )
		drawShadowCursor();
	//
	if( stretching )
		drawBaseShadow();
	
	//
	//if( temporary_base )
	//temporary_base->draw();
	//
	glPopMatrix();
	glDisable( GL_BLEND );
	
	//glutSwapBuffers();
}
void GLWorldViewer :: projection( void )
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	
	gluOrtho2D( xview, xview + width, yview, yview + height );
	
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ();
}
void GLWorldViewer :: startStopTimer( void )
{
	if( timer->isActive() )
		timer->stop();
	else
		timer->start();
	
	( ( MainWindow * )this->parent()->parent() )->countPlayingTime();
}
void GLWorldViewer :: keyPressEvent( QKeyEvent * event )
{
	b2Vec2 * center = NULL;
	SphereObject * ball = NULL;
	switch( event->key() )
	{
			//ESC
		case 16777216:  
			exit(0);
			break;
		case 27:
			break;
		case 32:  
			startStopTimer();
			break;
		case '-':
			break;
		case '=':
			break;
		case '1': 
			break;
		case '2': 
			break;
		case '3': 
			break;
		case '4': 
			break;
		case '5': 
			break;
		case '6': 
			break;
		case '7': 
			break;
		case '8': 
			break;
		case '9': 
			break;
		case '0': 
			break;
		case 'a':
		case 'A': 
			break;
		case 'b':
		case 'B': 
			center = OpenGltoBox2d( QTtoOpenGL( new b2Vec2( width/2, height/2 ) ) );
			ball = new SphereObject( objects.size(), world, center, tickness );
			ball->getBody()->ApplyForce( b2Vec2( ( rand() % 2 )? -500 * ball->getBody()->GetMass() : 500 * ball->getBody()->GetMass(), ( rand() % 2 ) ? -500 * ball->getBody()->GetMass() : 500 * ball->getBody()->GetMass() ), ball->getBody()->GetWorldCenter() );
			std::cout << "( " << ball->getPosition()->x << ", " << ball->getPosition()->y << std::endl;
			balls.push_back( ball );
			break;
		case 'c':
		case 'C': 
			break;
		case 'd':
		case 'D': 
			break;
		case 'e':
		case 'E': 
			break;
		case 'f':
		case 'F': 
			break;
		case 'g':
		case 'G':
			break;
		case 'h':
		case 'H':
			break;
		case 'i':
		case 'I':
			break;
		case 'j':
		case 'J':
			break;
		case 'k':
		case 'K':
			break;
		case 'l':
		case 'L':
			break;
		case 'm':
		case 'M':
			break;
		case 'n':
		case 'N':
			break;
		case 'o':
		case 'O':
			break;
		case 'p':
		case 'P':
			break;
		case 'q':
		case 'Q':
			break;
		case 'r':
		case 'R':
			break;
		case 's':
		case 'S':
			break;
		case 't':
		case 'T':
			break;
		case 'u':
		case 'U':
			break;
		case 'v':
		case 'V':
			break;
		case 'w':
		case 'W':
			break;
		case 'x':
		case 'X':
			break;
		case 'y':
		case 'Y':
			break;
		case 'z':
		case 'Z':
			break;
			//RIGHT
		case 16777236:
			xview += 10;
			break;
			//LEFT
		case 16777234:
			if( xview >= 10 )
				xview -= 10;
			else
				xview = 0;
			break;
			//UP
		case 16777235:
			yview += 10;
			break;
			//DOWN
		case 16777237:
			if( yview >= 10 )
				yview -= 10;
			else
				yview = 0;
			break;
	}
	projection();
	if( !timer->isActive() )
		updateGL();
	event->accept();
}
bool GLWorldViewer :: shadowCursorCollides( void )
{
	if( shadow_cursor_center )
	{
		b2Vec2 * center = OpenGltoBox2d( shadow_cursor_center );
		//
		for ( object_it = objects.begin(); object_it != objects.end(); object_it++)
		{
			Object * target = ( ( Object* ) *object_it );
			b2Vec2 * target_center = target->getPosition();
			
			if ( center->x - tickness/2 < target_center->x + target->getDimension()->x/2 && center->x + tickness/2 > target_center->x - target->getDimension()->x/2 &&
				center->y - tickness/2 < target_center->y + target->getDimension()->y/2 && center->y + tickness/2 > target_center->y - target->getDimension()->y/2 )
			{
				std::cout << "CURSOR ENCOSTANDO" << std::endl;
				return true;
			}
		}
		return false;
	}
	return true;
}
void GLWorldViewer :: mousePressEvent( QMouseEvent * event ) 
{
	if( !stretching )
	{
		base_shadow_center = QTtoOpenGL( new b2Vec2( event->x(), event->y() ) );
		if( !shadowCursorCollides() )
		{
			stretching = true;
			//UM DEDO - VERTICAL
			if( event->button() == Qt :: LeftButton )
			{
				vertical = true;
			}
			//DOIS DEDOS - HORIZONTAL
			else
			{
				vertical = false;
			}
		}
	}
	if( !timer->isActive() )
		updateGL();
} 
void GLWorldViewer :: enterEvent( QEvent * event )
{
	setMouseTracking( true );
	
	event->accept();
}
void GLWorldViewer :: leaveEvent( QEvent * event )
{
	setMouseTracking( false );
	
	shadow_cursor_center = NULL;
	
	event->accept();
}
void GLWorldViewer :: mouseMoveEvent( QMouseEvent *  event )
{
	shadow_cursor_center = QTtoOpenGL( new b2Vec2( event->x(), event->y() ) );
	
	event->accept();
	if( !timer->isActive() )
		updateGL();
} 
void GLWorldViewer :: tabletEvent( QTabletEvent * event )
{
	event->accept();
	
	std::cout << "TABLET( " << event->x() << ", " << event->y() << " )" << std::endl;
	
	if( !timer->isActive() )
		updateGL();
}
void GLWorldViewer :: mouseDoubleClickEvent( QMouseEvent * event ) 
{
	event->accept();
	if( !timer->isActive() )
		updateGL();
} 
void GLWorldViewer :: mouseReleaseEvent( QMouseEvent * event )
{
	event->accept();
	if( !timer->isActive() )
		updateGL();
}
