#include <QApplication>

#include "wigra.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WIgra wIgra;
    wIgra.show();

    app.exec();
}