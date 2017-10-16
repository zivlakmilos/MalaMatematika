#include "wigra.h"

#include <QtGui>

#include "ui_igra.h"

WIgra::WIgra(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FrmIgra()),
      m_tajmer(new QTimer(this)),
      m_igraPokrenuta(false),
      m_generisano(0),
      m_generisanjeZavrseno(false)
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
}

void WIgra::btnStopClick(void)
{
    if(m_igraPokrenuta)
    {
        m_generisano++;
    } else
    {
        m_igraPokrenuta = true;
        m_generisano = 0;
        m_generisanjeZavrseno = false;
        m_formula = "";
        m_tajmer->start(100);
        ui->btnStop->setText("STOP");
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
        m_generisanjeZavrseno = true;
        m_tajmer->stop();
    }
}

void WIgra::dodajBrojUFormulu(void)
{
    if(!m_generisanjeZavrseno)
        return;

    QPushButton *s = (QPushButton*)sender();
    QString vrednost = s->text();
    m_formula.append(vrednost);
    ui->lblFormula1->setText(m_formula);
    s->setDisabled(true);
}

void WIgra::dodajOperacijuUFormulu(void)
{
    if(!m_generisanjeZavrseno)
        return;

    QPushButton *s = (QPushButton*)sender();
    QString vrednost = s->text();
    m_formula.append(vrednost);
    ui->lblFormula1->setText(m_formula);
}
