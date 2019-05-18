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
    Applicant(QString snm, QString nm, QString ptr, QDate bd, QString sx, QString edu, QString act,
              QString vnm, QString vid,
              QString p, QString e, unsigned int d, unsigned int m, unsigned int y, Status s);
    void setStatus(Status s);
    QString getPhoneNumber() {return phone_number;}
    QString getEmail() {return email;}
    unsigned int getExpDays() {return e_days;}
    unsigned int getExpMonth() {return e_months;}
    unsigned int getExpYears() {return e_years;}
    QString getStatus();
    QDate getDateOfConsideration() {return date;}

};

#endif // APPLICANT_H
