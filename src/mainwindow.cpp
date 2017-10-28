#include "mainwindow.h"

#include <QtGui>

#include "wigra.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QCoreApplication::applicationName());

    setupMenu();
    setupCentralWidget();
    ucitajStilove();
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::setupMenu(void)
{
    QMenu *menuIzgled = menuBar()->addMenu(tr("Izgled"));

    m_actionIzgledOsnovni = menuIzgled->addAction(tr("Osnovni"));
    m_actionIzgledOsnovni->setCheckable(true);
    m_actionIzgledOsnovni->setChecked(true);

    m_actionIzgledDark = menuIzgled->addAction(tr("Dark"));
    m_actionIzgledDark->setCheckable(true);

    QActionGroup *actionIzgled = new QActionGroup(this);
    connect(actionIzgled, SIGNAL(triggered(QAction*)),
            this, SLOT(promenaIzgleda(QAction*)));
    actionIzgled->addAction(m_actionIzgledOsnovni);
    actionIzgled->addAction(m_actionIzgledDark);
}

void MainWindow::setupCentralWidget(void)
{
    WIgra *wIgra = new WIgra(this);
    setCentralWidget(wIgra);
    resize(wIgra->size().width(), wIgra->size().height() + 10);
}

void MainWindow::ucitajStilove(void)
{
    m_actionIzgledOsnovni->setData("");

    QFile file("darkorange.qss");
    file.open(QFile::ReadOnly);
    m_actionIzgledDark->setData(QLatin1String(file.readAll()));
}

void MainWindow::promenaIzgleda(QAction *action)
{
    qApp->setStyleSheet(action->data().toString());
}
