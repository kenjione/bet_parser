//! [main program]
#include <QWidget>
//#include <QtWidgets>
#include "window.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.setUrl(QUrl("http://www.forexsport.ru"));
    window.setUrl(QUrl("../ticket.html"));
    window.show();
    return app.exec();
}
//! [main program]
