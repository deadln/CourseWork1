#include "applicant.h"

Applicant::Applicant()
{
    phone_number = "";
    email = "";
    e_days = 0;
    e_months = 0;
    e_years = 0;
    status = CONSIDERATION;
    date = QDate::currentDate();
}

Applicant::Applicant(QString p, QString e, unsigned int d, unsigned int m, unsigned int y, Status s)
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
