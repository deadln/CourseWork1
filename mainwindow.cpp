#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addvacancy.h"
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>

const QString FILE_NAME("data.bin");
const QString FILE_NAME_2("archive.bin");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    //Загрузка данных из файла
    QFile file(FILE_NAME), file_2(FILE_NAME_2);
    QDataStream stream(&file), stream_2(&file_2);
    file.open(QIODevice::ReadOnly);
    stream >> applicants >> vacancies;
    file.close();

    file_2.open(QIODevice::ReadOnly);
    stream_2 >> archive;
    file_2.close();

    //Заполнение списков в окне
    for(QMap<QString, Applicant>::const_iterator i = applicants.constBegin(); i != applicants.constEnd(); i++)
    {
        ui->listWidget->addItem(i.key());
    }
    for(QMap<QString, Vacancy>::const_iterator i = vacancies.constBegin(); i != vacancies.constEnd(); i++)
    {
        ui->listWidget_2->addItem(i.key());
    }
    for(QMap<QString, Applicant>::const_iterator i = archive.constBegin(); i != archive.constEnd(); i++)
    {
        ui->listWidget_3->addItem(i.key());
    }


    connect(&addvacancy, SIGNAL(sendVacancy(Vacancy)), this, SLOT(addVac(Vacancy)));
    connect(&addapplicant, SIGNAL(sendApplicant(Applicant)), this, SLOT(addApp(Applicant)));
    connect(this, SIGNAL(sendVacList(QMap<QString, Vacancy>)),
            &addapplicant, SLOT(getVacList(QMap<QString, Vacancy>)));

}

MainWindow::~MainWindow()
{
    rewrite_data();
    delete ui;
}

//Перезапись данных
inline void MainWindow::rewrite_data()
{
    QFile file(FILE_NAME), file_2(FILE_NAME_2);
    QDataStream stream(&file), stream_2(&file_2);
    file.open(QIODevice::WriteOnly);
    stream << applicants << vacancies;
    file.close();

    file_2.open(QIODevice::WriteOnly);
    stream_2 << archive;
    file_2.close();
}

//Форматирование строки для нормального отображения
QString MainWindow::format_string(QString s)
{
    for(int i = 0, check = 0;i < s.length(); i++, check++)
    {
        if(check == 48)
        {
            s.insert(i,'\n');
            check = 0;
        }
        else if(s[i] == '\n')
            check = 0;
    }
    return s;
}

//Выход через меню
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

     rewrite_data();
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

    rewrite_data();
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
    ui->label_2->setText(format_string("Специальность вакансии: " + v.getVacancyName() + "\nШифр специальности: " +
                                       v.getId()));
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

    rewrite_data();
}

//Вывод данных о кандидате
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr)
    {
        ui->label->setText("");
        return;
    }
    Applicant a = applicants[current->text()];
    ui->label->setText(format_string("Фамилия: " + a.getSurname() + "\nИмя: " + a.getName() + "\nОтчество: " +
                                     a.getPatronimic() + "\nДата рождения: " + a.getbday().toString("dd.MM.yyyy") +
                                     "\nПол: " + a.getSex() + "\nОбразование: " + a.getEducation() +
                                     "\nДеятельность: " + a.getActivity() + "\nТелефон: " + a.getPhoneNumber() +
                                     "\nЭлектронная почта: " + a.getEmail() + "\nТрудовой стаж: " +
                                     QString::number(a.getExpYears()) + " лет " + QString::number(a.getExpMonth()) +
                                     " месяцев " + QString::number(a.getExpDays()) + " дней\nПретендуемая вакансия: " +
                                     a.getVacancyName() + "\nДата подачи кандидатуры: " +
                                     a.getDateOfConsideration().toString("dd.MM.yyyy") + "\nСтатус кандидата: " +
                                     a.getStatus()));
}

//Уведомление о переподготовке по специальности
void MainWindow::on_NotByVac_clicked()
{
    if(ui->listWidget_2->currentItem() != nullptr)
    {
        Vacancy v = vacancies[ui->listWidget_2->currentItem()->text()];
        for(QMap<QString, Applicant>::const_iterator i = applicants.constBegin(); i != applicants.constEnd(); i++)
        {
            if(i.value().getVacancyName() == v.getVacancyName())
           {
               QMessageBox(QMessageBox::Information, "Уведомление", QString("Кандидат %1 получил уведомление о "
                                                                         "переподготовке по специальности %2\n"
                                                                         "по электронной почте: %3\n"
                                                                         "по телефону: %4")
                        .arg(i.key()).arg(v.getVacancyName()).arg(i.value().getEmail()).arg(i.value().getPhoneNumber()))
                    .exec();
            }
        }
    }
}

//Удаление кандидата
void MainWindow::on_delApp_clicked()
{
    if(ui->listWidget->count() == 0)
        return;
    if(ui->listWidget->count() == 1)
    {
        applicants.clear();
        ui->listWidget->clear();
        return;
    }
    if(ui->listWidget->currentItem() != nullptr)
    {
        applicants.remove(ui->listWidget->currentItem()->text());
        ui->listWidget->takeItem(ui->listWidget->currentRow());
    }

    rewrite_data();
}

//Уведомление о переподготовке конкретного кандидата
void MainWindow::on_notifyApp_clicked()
{
    if(ui->listWidget->currentItem() != nullptr)
    {
        Applicant a = applicants[ui->listWidget->currentItem()->text()];
        QMessageBox(QMessageBox::Information, "Уведомление", QString("Кандидат %1 получил уведомление о "
                                                                     "переподготовке по специальности %2\n"
                                                                     "по электронной почте: %3\n"
                                                                     "по телефону: %4")
                    .arg(ui->listWidget->currentItem()->text()).arg(a.getVacancyName()).arg(a.getEmail())
                    .arg(a.getPhoneNumber())).exec();
    }
}

//Принять кандидата
void MainWindow::on_AcApp_clicked()
{
    if(ui->listWidget->currentItem() != nullptr)
    {
        Applicant a = applicants[ui->listWidget->currentItem()->text()];
        bool b = false;
        for(QMap<QString, Vacancy>::const_iterator i = vacancies.constBegin(); i != vacancies.constEnd(); i++)
        {
            if(a.getVacancyName() == i.value().getVacancyName() && a.getId() == i.value().getId())
            {
                for(int j = 0;j < ui->listWidget_2->count(); j++)
                {
                    if(ui->listWidget_2->item(j)->text() == i.key())
                    {
                        ui->listWidget_2->takeItem(j);
                        break;
                    }

                }
                vacancies.remove(i.key());
                b = true;
                break;
            }
        }
        if(!b)
        {
            QMessageBox(QMessageBox::Critical, "Ошибка", QString("Кандидат %1 не может быть добавлен - вакансия не "
                                                                      "существует")
                        .arg(ui->listWidget->currentItem()->text())).exec();
            return;
        }
        a.setStatus(Status::APPLIED);
        archive[ui->listWidget->currentItem()->text()] = a;
        //Вывод в архиве
        ui->listWidget_3->addItem(ui->listWidget->currentItem()->text());

        applicants.remove(ui->listWidget->currentItem()->text());
        ui->listWidget->takeItem(ui->listWidget->currentRow());


    }

    rewrite_data();
}

//Отказать кандидату
void MainWindow::on_DecApp_clicked()
{
    if(ui->listWidget->currentItem() != nullptr)
    {
        Applicant a = applicants[ui->listWidget->currentItem()->text()];
        a.setStatus(Status::DENIED);
        archive[ui->listWidget->currentItem()->text()] = a;
        //Вывод в архиве
        ui->listWidget_3->addItem(ui->listWidget->currentItem()->text());

        applicants.remove(ui->listWidget->currentItem()->text());
        ui->listWidget->takeItem(ui->listWidget->currentRow());
    }

    rewrite_data();
}

//Вывод кандидатов в архиве
void MainWindow::on_listWidget_3_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr)
    {
        ui->label_3->setText("");
        return;
    }
    Applicant a = archive[current->text()];
    ui->label_3->setText(format_string("Фамилия: " + a.getSurname() + "\nИмя: " + a.getName() + "\nОтчество: " +
                                       a.getPatronimic() + "\nДата рождения: " + a.getbday().toString("dd.MM.yyyy") +
                                       "\nПол: " + a.getSex() + "\nОбразование: " + a.getEducation() +
                                       "\nДеятельность: " + a.getActivity() + "\nТелефон: " + a.getPhoneNumber() +
                                       "\nЭлектронная почта: " + a.getEmail() + "\nТрудовой стаж: " +
                                       QString::number(a.getExpYears()) + " лет " + QString::number(a.getExpMonth()) +
                                       " месяцев " + QString::number(a.getExpDays()) +
                                       " дней\nПретендуемая вакансия: " + a.getVacancyName() +
                                       "\nДата подачи кандидатуры: " +
                                       a.getDateOfConsideration().toString("dd.MM.yyyy") + "\nСтатус кандидата: " +
                                       a.getStatus()));
}

//Удаление записи из архива
void MainWindow::on_DelArch_clicked()
{
    if(ui->listWidget_3->count() == 0)
        return;
    if(ui->listWidget_3->count() == 1)
    {
        archive.clear();
        ui->listWidget_3->clear();
        return;
    }
    if(ui->listWidget_3->currentItem() != nullptr)
    {
        archive.remove(ui->listWidget_3->currentItem()->text());
        ui->listWidget_3->takeItem(ui->listWidget_3->currentRow());
    }

    rewrite_data();
}

//Удаление всех записей из архива
void MainWindow::on_DelAllArch_clicked()
{
    archive.clear();
    ui->listWidget_3->clear();
    rewrite_data();
}

//Удаление принятых кандидатов
void MainWindow::on_DelAc_clicked()
{
    for(int i = 0;i < ui->listWidget_3->count(); i++)
    {
        if(archive[ui->listWidget_3->item(i)->text()].getStatus() == "Принят")
        {
            archive.remove(ui->listWidget_3->item(i)->text());
            ui->listWidget_3->takeItem(i);
            i--;
        }
    }
    rewrite_data();
}

//Удаление отклонённых кандидатов
void MainWindow::on_DelDec_clicked()
{
    for(int i = 0;i < ui->listWidget_3->count(); i++)
    {
        if(archive[ui->listWidget_3->item(i)->text()].getStatus() == "Отклонён")
        {
            archive.remove(ui->listWidget_3->item(i)->text());
            ui->listWidget_3->takeItem(i);
            i--;
        }
    }
    rewrite_data();
}
