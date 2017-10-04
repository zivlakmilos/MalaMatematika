#include <QApplication>

#include "wigra.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Mala matematika");
    QCoreApplication::setOrganizationName("Milos Zivlak");
    QCoreApplication::setOrganizationDomain("http://zivlak.ddns.net");

    WIgra wIgra;
    wIgra.show();

    app.exec();
}