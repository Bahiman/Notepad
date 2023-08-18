#include "Notepad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // малиновый закат стекает по стене 
    Notepad w;
    w.show();
    return a.exec();
}
