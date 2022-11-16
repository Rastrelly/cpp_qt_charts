#include "stdafx.h"
#include "cpp_qt_charts.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cpp_qt_charts w;
    w.show();
    return a.exec();
}
