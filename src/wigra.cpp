#include "wigra.h"

#include "ui_igra.h"

WIgra::WIgra(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FrmIgra())
{
    ui->setupUi(this);
}

WIgra::~WIgra(void)
{
    if(ui)
        delete ui;
}
