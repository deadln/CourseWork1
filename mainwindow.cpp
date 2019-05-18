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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QApplication::quit();
}


void MainWindow::on_addApp_clicked()
{

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
     srand(time(NULL));
     qDebug() << "Accepted: " << v.getName() << " " << v.getId();
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
             ui->listWidget_2->addItem(ln + "." + v.getName());
             vacancies[ln + "." + v.getName()] = v;
             break;
         }

     }
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Vacancy v = vacancies[current->text()];
    ui->label_2->setText("Специальность вакансии: " + v.getName() + "\nШифр специальности: " + v.getId());
}
