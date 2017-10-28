#include "wigra.h"

#include <QtGui>

#include "ui_igra.h"
#include "exceptionzagrada.h"
#include "aithread.h"

WIgra::WIgra(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FrmIgra()),
      m_aiThread(new AIThread(this)),
      m_tajmer(new QTimer(this)),
      m_generisanjePokrenuto(false),
      m_generisano(0),
      m_brojZagrada(0)
{
    ui->setupUi(this);
    setupHandlers();
}

WIgra::~WIgra(void)
{
    if(ui)
        delete ui;
}

void WIgra::setupHandlers(void)
{
    connect(ui->btnStop, SIGNAL(clicked(bool)),
            this, SLOT(btnStopClick()));
    connect(m_tajmer, SIGNAL(timeout()),
            this, SLOT(tajmerTimeout()));

    connect(ui->btnBroj1, SIGNAL(clicked(bool)),
            this, SLOT(dodajBrojUFormulu()));
    connect(ui->btnBroj2, SIGNAL(clicked(bool)),
            this, SLOT(dodajBrojUFormulu()));
    connect(ui->btnBroj3, SIGNAL(clicked(bool)),
            this, SLOT(dodajBrojUFormulu()));
    connect(ui->btnBroj4, SIGNAL(clicked(bool)),
            this, SLOT(dodajBrojUFormulu()));
    connect(ui->btnBroj5, SIGNAL(clicked(bool)),
            this, SLOT(dodajBrojUFormulu()));
    connect(ui->btnBroj6, SIGNAL(clicked(bool)),
            this, SLOT(dodajBrojUFormulu()));
    connect(ui->btnPlus, SIGNAL(clicked(bool)),
            this, SLOT(dodajOperacijuUFormulu()));
    connect(ui->btnMinus, SIGNAL(clicked(bool)),
            this, SLOT(dodajOperacijuUFormulu()));
    connect(ui->btnPuta, SIGNAL(clicked(bool)),
            this, SLOT(dodajOperacijuUFormulu()));
    connect(ui->btnPodeljeno, SIGNAL(clicked(bool)),
            this, SLOT(dodajOperacijuUFormulu()));
    connect(ui->btnZagradaOtvorena, SIGNAL(clicked(bool)),
            this, SLOT(dodajOperacijuUFormulu()));
    connect(ui->btnZagradaZatvorena, SIGNAL(clicked(bool)),
            this, SLOT(dodajOperacijuUFormulu()));

    connect(ui->btnObrisi, SIGNAL(clicked(bool)),
            this, SLOT(btnObrisiClick()));
    connect(ui->btnPotvrdi, SIGNAL(clicked(bool)),
            this, SLOT(btnPotvrdiClick()));

    connect(m_aiThread, SIGNAL(resenjeNadjeno(std::vector<ElementOperacije>)),
            this, SLOT(aiNasaoResenje(std::vector<ElementOperacije>)));
}

QString WIgra::pretvoriFormuluUString(const std::vector<ElementOperacije> &formula)
{
    QString str;
    for(auto it = formula.begin(); it != formula.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperator)
        {
            switch(it->vrednost.operacija)
            {
                case OperatorPlus:
                    str += "+";
                    break;
                case OperatorMinus:
                    str += "-";
                    break;
                case OperatorPuta:
                    str += "*";
                    break;
                case OperatorPodeljeno:
                    str += "/";
                    break;
                case OperatorZagradaOtvorena:
                    str += "(";
                    break;
                case OperatorZagradaZatvorena:
                    str += ")";
                    break;
            }
        } else
        {
            str += QString::number(it->vrednost.operand);
        }
    }

    return str;
}

void WIgra::btnStopClick(void)
{
    if(m_generisanjePokrenuto)
    {
        m_generisano++;
    } else
    {
        m_generisanjePokrenuto = true;
        m_generisano = 0;
        m_brojZagrada = 0;
        m_formula.clear();
        m_formula2.clear();

        ui->lblTrazeniBroj1->setText("");
        ui->lblTrazeniBroj2->setText("");
        ui->lblTrazeniBroj3->setText("");
        ui->btnBroj1->setText("");
        ui->btnBroj2->setText("");
        ui->btnBroj3->setText("");
        ui->btnBroj4->setText("");
        ui->btnBroj5->setText("");
        ui->btnBroj6->setText("");

        ui->btnBroj1->setEnabled(true);
        ui->btnBroj2->setEnabled(true);
        ui->btnBroj3->setEnabled(true);
        ui->btnBroj4->setEnabled(true);
        ui->btnBroj5->setEnabled(true);
        ui->btnBroj6->setEnabled(true);

        ui->lblRezultat1->setText("");
        ui->lblFormula1->setText("");
        ui->lblRezultat2->setText("");
        ui->lblFormula2->setText("");

        m_tajmer->start(100);
        ui->btnStop->setText(tr("STOP"));
    }
}

void WIgra::tajmerTimeout(void)
{
    if(m_generisano < 3)
    {
        int slucajanBroj = m_random.nextInt(10);
        switch(m_generisano)
        {
            case 0:
                ui->lblTrazeniBroj1->setText(QString::number(slucajanBroj));
                break;
            case 1:
                ui->lblTrazeniBroj2->setText(QString::number(slucajanBroj));
                break;
            case 2:
                ui->lblTrazeniBroj3->setText(QString::number(slucajanBroj));
                break;
        }
    } else if(m_generisano < 7)
    {
        int slucajanBroj = m_random.nextInt(9) + 1;
        switch(m_generisano)
        {
            case 3:
                ui->btnBroj1->setText(QString::number(slucajanBroj));
                break;
            case 4:
                ui->btnBroj2->setText(QString::number(slucajanBroj));
                break;
            case 5:
                ui->btnBroj3->setText(QString::number(slucajanBroj));
                break;
            case 6:
                ui->btnBroj4->setText(QString::number(slucajanBroj));
                break;
        }
    } else if(m_generisano == 7)
    {
        int slucajanBroj = m_random.nextInt(3) + 2;
        slucajanBroj *= 5;
        ui->btnBroj5->setText(QString::number(slucajanBroj));
    } else if(m_generisano == 8)
    {
        int slucajanBroj = m_random.nextInt(4) + 1;
        slucajanBroj *= 25;
        ui->btnBroj6->setText(QString::number(slucajanBroj));
    } else
    {
        m_generisanjePokrenuto = false;
        m_tajmer->stop();
        ui->btnStop->setText(tr("NOVA IGRA"));

        uint32_t rezultat = ui->lblTrazeniBroj1->text().toInt() * 100 +
                            ui->lblTrazeniBroj2->text().toInt() * 10 +
                            ui->lblTrazeniBroj3->text().toInt();
        std::vector<uint32_t> ponudjeniBrojevi;
        for(int i = 1; i <= 6; i++)
        {
            QPushButton *btn = findChild<QPushButton*>("btnBroj" + QString::number(i));
            if(btn)
                ponudjeniBrojevi.push_back(btn->text().toInt());
        }
        m_aiThread->pokreni(rezultat, ponudjeniBrojevi);
    }
}

void WIgra::dodajBrojUFormulu(void)
{
    if(m_generisanjePokrenuto)
        return;
    if(!m_formula.empty())
    {
        if(m_formula[m_formula.size() - 1].tip == TipElementaOperacijeOperand ||
            m_formula[m_formula.size() - 1].vrednost.operacija == OperatorZagradaZatvorena)
            return;
    }

    QPushButton *s = (QPushButton*)sender();
    QString vrednost = s->text();

    ElementOperacije element;
    element.tip = TipElementaOperacijeOperand;
    element.vrednost.operand = vrednost.toInt();
    m_formula.push_back(element);
    s->setEnabled(false);

    ui->lblFormula1->setText(pretvoriFormuluUString(m_formula));
}

void WIgra::dodajOperacijuUFormulu(void)
{
    if(m_generisanjePokrenuto)
        return;

    QPushButton *s = (QPushButton*)sender();
    QString vrednost = s->text();

    ElementOperacije element;
    element.tip = TipElementaOperacijeOperator;
    switch(vrednost.at(0).toAscii())
    {
        case '+':
            element.vrednost.operacija = OperatorPlus;
            break;
        case '-':
            element.vrednost.operacija = OperatorMinus;
            break;
        case '*':
            element.vrednost.operacija = OperatorPuta;
            break;
        case '/':
            element.vrednost.operacija = OperatorPodeljeno;
            break;
        case '(':
            element.vrednost.operacija = OperatorZagradaOtvorena;
            break;
        case ')':
            element.vrednost.operacija = OperatorZagradaZatvorena;
            break;
    }

    if(element.vrednost.operacija == OperatorZagradaOtvorena)
    {
        if(!m_formula.empty())
            if(m_formula[m_formula.size() - 1].tip == TipElementaOperacijeOperand)
                return;
        m_brojZagrada++;
    } else
    {
        if(m_formula.empty())
            return;
        if(m_formula[m_formula.size() - 1].tip == TipElementaOperacijeOperator &&
            m_formula[m_formula.size() - 1].vrednost.operand != OperatorZagradaZatvorena)
            return;

        if(element.vrednost.operacija == OperatorZagradaZatvorena)
        {
            if(m_brojZagrada > 0)
                m_brojZagrada--;
            else
                return;
        }
    }

    m_formula.push_back(element);

    ui->lblFormula1->setText(pretvoriFormuluUString(m_formula));
}

void WIgra::btnObrisiClick(void)
{
    if(m_formula.empty())
        return;

    ElementOperacije element = m_formula[m_formula.size() - 1];

    if(element.tip == TipElementaOperacijeOperator)
    {
        if(element.vrednost.operacija == OperatorZagradaOtvorena)
            m_brojZagrada--;
        else if(element.vrednost.operacija == OperatorZagradaZatvorena)
            m_brojZagrada++;
    } else
    {
        for(int i = 1; i <= 6; i++)
        {
            QPushButton *btn = findChild<QPushButton*>("btnBroj" + QString::number(i));
            if(btn)
            {
                if(btn->text() == QString::number(element.vrednost.operand) &&
                    !btn->isEnabled())
                {
                    btn->setEnabled(true);
                    break;
                }
            }
        }
    }

    m_formula.pop_back();
    ui->lblFormula1->setText(pretvoriFormuluUString(m_formula));
}

void WIgra::btnPotvrdiClick(void)
{
    try {
        uint32_t rezultat = m_matematika.racunajInfiksnu(m_formula);
        ui->lblRezultat1->setText(QString::number(rezultat));

        if(!m_formula2.empty())
        {
            rezultat = m_matematika.racunajPostfoksnu(m_formula2);
            ui->lblFormula2->setText(pretvoriFormuluUString(
                m_matematika.pretvoriPostfiksnuUInfiksnu(m_formula2)));
            ui->lblRezultat2->setText(QString::number(rezultat));
        }
    } catch(ExceptionZagrada &ex) {
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Nisu zatvorene sve zagrade"));
    } catch(Exception &ex) {
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Greska prilikom racunanja formule"));
    }
}

void WIgra::aiNasaoResenje(std::vector<ElementOperacije> formula)
{
    m_formula2 = formula;
}

