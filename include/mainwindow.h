#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow(void);

private:
    void setupMenu(void);
    void setupCentralWidget(void);
    void ucitajStilove(void);

    QAction *m_actionIzgledOsnovni;
    QAction *m_actionIzgledDark;

private slots:
    void promenaIzgleda(QAction *action);
};

#endif // _MAIN_WINDOW_H_
