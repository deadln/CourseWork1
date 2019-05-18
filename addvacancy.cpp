#include "addvacancy.h"
#include "ui_addvacancy.h"
#include <QDebug>

AddVacancy::AddVacancy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVacancy)
{
    ui->setupUi(this);
    //connect(this, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted()));
}

AddVacancy::~AddVacancy()
{
    delete ui;
}

void AddVacancy::on_buttonBox_rejected()
{

}

void AddVacancy::on_buttonBox_accepted()
{
    Vacancy v(ui->lineEdit->text(), ui->lineEdit_2->text());
    emit sendVacancy(v);
    qDebug() << "Sended: " << v.getName() << " " << v.getId();
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");

}

