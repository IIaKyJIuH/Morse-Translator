#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":icons/morseIcon"));

    QCoreApplication::setOrganizationName("Pakulin Sergei Leonidovich");
    QCoreApplication::setApplicationName("MorseTranslator");

    MTMainWindow w;
    w.show();
    return a.exec();
}
