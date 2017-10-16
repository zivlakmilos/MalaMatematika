#include "wigra.h"

#include <QtGui>

#include "ui_igra.h"

WIgra::WIgra(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FrmIgra()),
      m_tajmer(new QTimer(this)),
      m_igraPokrenuta(false),
      m_generisano(0)
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
}

void WIgra::btnStopClick(void)
{
    if(m_igraPokrenuta)
    {
    } else
    {
        m_igraPokrenuta = true;
        m_tajmer->start(100);
        ui->btnStop->setText("STOP");
    }
}

void WIgra::tajmerTimeout(void)
{
}
