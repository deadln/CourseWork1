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
#include "addapplicant.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    inline void rewrite_data();

signals:
    void sendVacList(QMap<QString, Vacancy> m);

private slots:
    void on_action_triggered();

    void on_pushButton_2_clicked();

    void on_addApp_clicked();

    void on_AddVac_clicked();

    void addVac(Vacancy v);

    void addApp(Applicant a);

    void on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_DelVac_clicked();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_NotByVac_clicked();

    void on_delApp_clicked();

private:
    Ui::MainWindow *ui;

    AddVacancy addvacancy;
    AddApplicant addapplicant;

    QMap<QString , Applicant> applicants;
    QMap<QString , Vacancy> vacancies;
    QMap<QString , Applicant> archive;
};

#endif // MAINWINDOW_H
