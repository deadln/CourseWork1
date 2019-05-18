#include "applicant.h"

Applicant::Applicant(): Person (), Vacancy ()
{
    phone_number = "";
    email = "";
    e_days = 0;
    e_months = 0;
    e_years = 0;
    status = CONSIDERATION;
    date = QDate::currentDate();
}

Applicant::Applicant(QString snm, QString nm, QString ptr, QDate bd, QString sx, QString edu, QString act,
                     QString vnm, QString vid,
                     QString p, QString e, unsigned int d, unsigned int m, unsigned int y, Status s):
    Person (snm, nm, ptr, bd, sx, edu, act), Vacancy (vnm, vid)
{
    phone_number = p;
    email = e;
    e_days = d;
    e_months = m;
    e_years = y;
    status = s;
    date = QDate::currentDate();
}

void Applicant::setStatus(Status s)
{
    status = s;
}

QString Applicant::getStatus()
{
    switch (status)
    {
    case 0:
        return "На рассмотрении";
    case 1:
        return "Принят";
    case 2:
        return "Отклонён";
    }
}
