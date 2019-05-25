#include "addapplicant.h"
#include "ui_addapplicant.h"
#include "applicant.h"
#include <QFile>
#include <QFileDialog>
#include <QTextCodec>
#include <QDebug>

AddApplicant::AddApplicant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddApplicant)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Мужской");
    ui->comboBox->addItem("Женский");

}

AddApplicant::~AddApplicant()
{
    delete ui;
}

void AddApplicant::getVacList(QMap<QString, Vacancy> m)
{
    ui->comboBox_2->clear();
    VacList = m;

    for(QMap<QString, Vacancy>::const_iterator i = m.constBegin(); i != m.constEnd(); i++)
    {
        ui->comboBox_2->addItem(i.key());
    }
}

void AddApplicant::on_buttonBox_accepted()
{
    Applicant a(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->dateEdit->date(),
                ui->comboBox->currentText(), ui->lineEdit_4->text(),ui->lineEdit_5->text(),
                VacList[ui->comboBox_2->currentText()].getVacancyName(), VacList[ui->comboBox_2->currentText()].getId(),
            ui->lineEdit_6->text(), ui->lineEdit_7->text(), ui->spinBox->value(), ui->spinBox_2->value(),
            ui->spinBox_3->value(), CONSIDERATION, QDate::currentDate());

    emit sendApplicant(a);

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->dateEdit->setDate(QDate(2000,1,1));
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
}

void AddApplicant::on_buttonBox_rejected()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->dateEdit->setDate(QDate(2000,1,1));
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
}

void AddApplicant::on_openFile_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("windows-1251");
    QFile file(QFileDialog::getOpenFileName(this, "Открыть резюме", "", "*.txt"));
    file.open(QIODevice::ReadOnly);
            ui->lineEdit->setText(codec->toUnicode(file.readLine()));
            ui->lineEdit_2->setText(codec->toUnicode(file.readLine()));
            ui->lineEdit_3->setText(codec->toUnicode(file.readLine()));
            ui->dateEdit->setDate(QDate::fromString(codec->toUnicode(file.readLine()), "dd.MM.yyyy"));
            if(codec->toUnicode(file.readLine()) == "Женский")
                ui->comboBox->setCurrentIndex(1);
            else
                ui->comboBox->setCurrentIndex(0);
            ui->lineEdit_4->setText(codec->toUnicode(file.readLine()));
            ui->lineEdit_5->setText(codec->toUnicode(file.readLine()));
            ui->lineEdit_6->setText(codec->toUnicode(file.readLine()));
            ui->lineEdit_7->setText(codec->toUnicode(file.readLine()));
            ui->spinBox->setValue(file.readLine().toInt());
            ui->spinBox_2->setValue(file.readLine().toInt());
            ui->spinBox_3->setValue(file.readLine().toInt());
            QString vac = codec->toUnicode(file.readLine());
            for(int i = 0;i < ui->comboBox_2->count();i++)
            {
                ui->comboBox_2->setCurrentIndex(i);
                if(VacList[ui->comboBox_2->currentText()].getVacancyName() == vac)
                    break;
            }
    file.close();
}
