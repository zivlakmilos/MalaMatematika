#ifndef _W_IGRA_H_
#define _W_IGRA_H_

#include <QWidget>

#include "random.h"
#include "matematika.h"

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
    void setupHandlers(void);
    void prikaziFormulu(void);

    Ui::FrmIgra *ui;

    QTimer *m_tajmer;

    bool m_igraPokrenuta;
    int m_generisano;
    bool m_generisanjeZavrseno;
    QVector<ElementOperacije> m_formula;
    int m_brojZagrada;

    Random m_random;

private slots:
    void btnStopClick(void);
    void tajmerTimeout(void);
    void dodajBrojUFormulu(void);
    void dodajOperacijuUFormulu(void);
};

#endif // _W_IGRA_H_
