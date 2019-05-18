#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "person.h"
#include "vacancy.h"
#include "applicant.h"
#include "addvacancy.h"
#include <QString>
#include <QMap>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_pushButton_2_clicked();

    void on_addApp_clicked();

    void on_AddVac_clicked();

    void addVac(Vacancy v);

    void on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::MainWindow *ui;

    AddVacancy addvacancy;

    QMap<QString , Applicant> applicants;
    QMap<QString , Vacancy> vacancies;
    QMap<QString , Applicant> archive;
};

#endif // MAINWINDOW_H
