#ifndef _W_IGRA_H_
#define _W_IGRA_H_

#include <QWidget>

namespace Ui {
    class FrmIgra;
}

class WIgra : public QWidget
{
    Q_OBJECT

public:
    WIgra(QWidget *parent = 0);
    virtual ~WIgra(void);

private:
    Ui::FrmIgra *ui;
};

#endif // _W_IGRA_H_
