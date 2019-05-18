#ifndef ADDAPPLICANT_H
#define ADDAPPLICANT_H

#include <QDialog>
#include <QMap>
#include "applicant.h"

namespace Ui {
class AddApplicant;
}

class AddApplicant : public QDialog
{
    Q_OBJECT

public:
    explicit AddApplicant(QWidget *parent = nullptr);
    ~AddApplicant();

signals:
    void sendApplicant(Applicant a);

public slots:
    void getVacList(QMap<QString, Vacancy> m);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddApplicant *ui;
    QMap<QString, Vacancy> VacList;
};

#endif // ADDAPPLICANT_H
