#ifndef APPLICANT_H
#define APPLICANT_H

#include "person.h"
#include "vacancy.h"
#include <QString>
#include <QDebug>

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
              QString p, QString e, unsigned int d, unsigned int m, unsigned int y, Status s,
              QDate dt);
    void setStatus(Status s);
    QString getPhoneNumber() const {return phone_number;}
    QString getEmail() const {return email;}
    unsigned int getExpDays() const {return e_days;}
    unsigned int getExpMonth() const {return e_months;}
    unsigned int getExpYears() const {return e_years;}
    QString getStatus() const;
    QDate getDateOfConsideration() const {return date;}

    friend QDataStream& operator<<(QDataStream &d, const Applicant &a);
    friend QDataStream& operator>>( QDataStream& d, Applicant &a);
};

#endif // APPLICANT_H
