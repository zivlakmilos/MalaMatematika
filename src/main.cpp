#include <QApplication>

#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Mala matematika");
    QCoreApplication::setOrganizationName("Milos Zivlak");
    QCoreApplication::setOrganizationDomain("http://zivlak.ddns.net");

    MainWindow window;
    window.show();

    app.exec();
}