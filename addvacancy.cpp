#include "addvacancy.h"
#include "ui_addvacancy.h"
#include <QDebug>

AddVacancy::AddVacancy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVacancy)
{
    ui->setupUi(this);
}

AddVacancy::~AddVacancy()
{
    delete ui;
}

void AddVacancy::on_buttonBox_rejected()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void AddVacancy::on_buttonBox_accepted()
{
    Vacancy v(ui->lineEdit->text(), ui->lineEdit_2->text());
    emit sendVacancy(v);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");

}

