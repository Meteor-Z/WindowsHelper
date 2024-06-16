#include "WindowsHelper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowsHelper w;
    w.show();
    return a.exec();
}
