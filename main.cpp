#include <QApplication>

#include "MainWindow.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    MainWindow window;
    window.show();
    window.move( 100, 50 );
    return app.exec();
}
