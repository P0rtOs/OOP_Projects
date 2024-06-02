#include "OOP_PMC_IASA_GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OOP_PMC_IASA_GUI w;
    w.show();
    return a.exec();
}
