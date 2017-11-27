#include <QApplication>

#include "ui/mainwindow.h"

#include <iostream>
#include "algorithm/tree.h"

int main(void)
{
    std::vector<int32_t> brojevi({1, 2, 3, 4, 5, 25, 100});

    std::shared_ptr<Tree> tree = Tree::generateRandomTree(5);
    std::cout << *tree << std::endl;
    //std::cout << tree->calculate() << std::endl;
    std::cout << tree->calculate(brojevi) << std::endl;

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
