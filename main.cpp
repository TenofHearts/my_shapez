#include "window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(ICON_DEST));
    Global::w = new Window;
    Global::w->show();
    return a.exec();
}