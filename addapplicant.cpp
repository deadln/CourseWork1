#include "addapplicant.h"
#include "ui_addapplicant.h"

AddApplicant::AddApplicant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddApplicant)
{
    ui->setupUi(this);
}

AddApplicant::~AddApplicant()
{
    delete ui;
}
