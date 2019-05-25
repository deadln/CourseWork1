#ifndef ADDVACANCY_H
#define ADDVACANCY_H

#include <QDialog>
#include "vacancy.h"

namespace Ui {
class AddVacancy;
}

class AddVacancy : public QDialog
{
    Q_OBJECT

public:
    explicit AddVacancy(QWidget *parent = nullptr);
    ~AddVacancy();

signals:
    void sendVacancy(Vacancy v);

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::AddVacancy *ui;
};

#endif // ADDVACANCY_H
