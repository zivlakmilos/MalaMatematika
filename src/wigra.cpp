#include "wigra.h"

#include <QtGui>

#include "ui_igra.h"

WIgra::WIgra(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FrmIgra()),
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
}

void WIgra::prikaziFormulu(void)
{
    QString str;
    for(auto it = m_formula.begin(); it != m_formula.end(); it++)
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

    ui->lblFormula1->setText(str);
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

        ui->lblTrazeniBroj1->setText("");
        ui->lblTrazeniBroj2->setText("");
        ui->lblTrazeniBroj3->setText("");
        ui->btnBroj1->setText("");
        ui->btnBroj2->setText("");
        ui->btnBroj3->setText("");
        ui->btnBroj4->setText("");
        ui->btnBroj5->setText("");
        ui->btnBroj6->setText("");

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
    }
}

void WIgra::dodajBrojUFormulu(void)
{
    if(m_generisanjePokrenuto)
        return;
    if(!m_formula.isEmpty())
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
    s->setDisabled(true);

    prikaziFormulu();
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
        if(!m_formula.isEmpty())
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

    prikaziFormulu();
}

void WIgra::btnObrisiClick(void)
{
    if(m_formula.isEmpty())
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
    prikaziFormulu();
}
