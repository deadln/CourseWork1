#ifndef APPLICANT_H
#define APPLICANT_H

#include "person.h"
#include "vacancy.h"
#include <QString>

enum Status {CONSIDERATION, APPLIED, DENIED};

class Applicant : public Person, public Vacancy
{
    QString phone_number;
    QString email;
    unsigned int e_days;
    unsigned int e_months;
    unsigned int e_years;
    Status status;
    QDate date;
public:
    Applicant();
    Applicant(QString p, QString e, unsigned int d, unsigned int m, unsigned int y, Status s);
    void setStatus(Status s);
};

#endif // APPLICANT_H
