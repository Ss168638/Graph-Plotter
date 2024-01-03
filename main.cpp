#include "myplotter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyPlotter w;
    w.setWindowTitle("Simple Graph");
    w.show();
    return a.exec();
}
