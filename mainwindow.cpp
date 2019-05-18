#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addvacancy.h"
#include <QDebug>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "test";

    connect(&addvacancy, SIGNAL(sendVacancy(Vacancy)), this, SLOT(addVac(Vacancy)));
    connect(&addapplicant, SIGNAL(sendApplicant(Applicant)), this, SLOT(addApp(Applicant)));
    connect(this, SIGNAL(sendVacList(QMap<QString, Vacancy>)),
            &addapplicant, SLOT(getVacList(QMap<QString, Vacancy>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QApplication::quit(); //Выход
}

//Открытие окна создания кандидата
void MainWindow::on_addApp_clicked()
{
    emit sendVacList(vacancies);

    addapplicant.setModal(true);
    addapplicant.exec();
}


//Открытие окна создания вакансии
void MainWindow::on_AddVac_clicked()
{
    addvacancy.setModal(true);
    addvacancy.exec();
}

//Добавление вакансии в систему
void MainWindow::addVac(Vacancy v)
{
     srand(time(nullptr));
     for(;;)
     {
         bool f = true;
         int listNumber = rand() % 10000000;
         QString ln = QString::number(listNumber);
         for(int i = 0;i < ui->listWidget_2->count(); i++)
         {
             if(ui->listWidget_2->item(i)->text().startsWith(ln))
             {
                 f = false;
                 break;
             }
         }
         if(f)
         {
             ui->listWidget_2->addItem(ln + ":" + v.getVacancyName());
             vacancies[ln + ":" + v.getVacancyName()] = v;
             break;
         }

     }
}

//Добавление кандидата в систему
void MainWindow::addApp(Applicant a)
{
    srand(time(nullptr));
    for(;;)
    {
        bool f = true;
        int listNumber = rand() % 10000000;
        QString ln = QString::number(listNumber);
        for(int i = 0;i < ui->listWidget->count(); i++)
        {
            if(ui->listWidget->item(i)->text().startsWith(ln))
            {
                f = false;
                break;
            }
        }
        if(f)
        {
            ui->listWidget->addItem(ln + ":" + a.getSurname() + " " + a.getName() + " " + a.getPatronimic());
            applicants[ln + ":" + a.getSurname() + " " + a.getName() + " " + a.getPatronimic()] = a;
            break;
        }
    }

}

//НЕ УДАЛЯТЬ
void MainWindow::on_pushButton_2_clicked()
{

}
//НЕ УДАЛЯТЬ

//Вывод данных о вакансии
void MainWindow::on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr)
    {
        ui->label_2->setText("");
        return;
    }
    Vacancy v = vacancies[current->text()];
    ui->label_2->setText("Специальность вакансии: " + v.getVacancyName() + "\nШифр специальности: " + v.getId());
}

//Удаление вакансии
void MainWindow::on_DelVac_clicked()
{
    if(ui->listWidget_2->count() == 0)
        return;
    if(ui->listWidget_2->count() == 1)
    {
        vacancies.clear();
        ui->listWidget_2->clear();
        return;
    }
    if(ui->listWidget_2->currentItem() != nullptr)
    {
        vacancies.remove(ui->listWidget_2->currentItem()->text());
        ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
    }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr)
    {
        ui->label->setText("");
        return;
    }
    Applicant a = applicants[current->text()];
    ui->label->setText("Фамилия: " + a.getSurname() + "\nИмя: " + a.getName() + "\nОтчество: " + a.getPatronimic() +
                         "\nДата рождения: " + a.getbday().toString("dd.MM.yyyy") + "\nПол: " + a.getSex() +
                       "\nОбразование: " + a.getEducation() + "\nДеятельность: " + a.getSex() +
                       "\nТелефон: " + a.getPhoneNumber() + "\nЭлектронная почта: " + a.getEmail() +
                       "\nТрудовой стаж: " + QString::number(a.getExpYears()) + " лет " +
                       QString::number(a.getExpMonth()) + " месяцев " + QString::number(a.getExpDays()) +
                       " дней\nПретендуемая вакансия: " + a.getVacancyName());
}
