// VS������������Ľ��
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// ��ָ���֧��VS����
#endif

#include "WindowsHelper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowsHelper w;
    w.show();
    return a.exec();
}
