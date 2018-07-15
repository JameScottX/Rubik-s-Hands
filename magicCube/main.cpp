#include "magic.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setQuitOnLastWindowClosed(true);
    Magic w;

    w.show();

    return a.exec();
}
