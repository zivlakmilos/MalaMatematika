#ifndef _W_IGRA_H_
#define _W_IGRA_H_

#include <QWidget>

#include <stdint.h>
#include <vector>
#include <thread>

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
    QString pretvoriFormuluUString(const std::vector<ElementOperacije> &formula);
    void pozoviAI(void);

    Ui::FrmIgra *ui;

    std::thread m_aiThread;

    QTimer *m_tajmer;

    bool m_generisanjePokrenuto;
    uint8_t m_generisano;
    std::vector<ElementOperacije> m_formula;
    uint8_t m_brojZagrada;

    uint32_t m_rezultat;
    std::vector<uint32_t> m_ponudjeniBrojevi;
    std::vector<ElementOperacije> m_formula2;

    Random m_random;
    Matematika m_matematika;

private slots:
    void btnStopClick(void);
    void tajmerTimeout(void);
    void dodajBrojUFormulu(void);
    void dodajOperacijuUFormulu(void);
    void btnObrisiClick(void);
    void btnPotvrdiClick(void);
};

#endif // _W_IGRA_H_
