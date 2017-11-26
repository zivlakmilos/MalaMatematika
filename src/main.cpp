#include <QApplication>

#include "ui/mainwindow.h"

#include <iostream>
#include "algorithm/tree.h"

int main(void)
{
    std::shared_ptr<Tree> tree = Tree::generateRandomTree(5);

    return 0;
}

/*
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
*/
