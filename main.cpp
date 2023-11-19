#include <QtWidgets/QApplication>
#include "collection.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Collection window;
    window.show();
    return a.exec();
}
