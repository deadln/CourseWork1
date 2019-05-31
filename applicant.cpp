#include "applicant.h"
#include <QDebug>

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
                     QString p, QString e, unsigned int d, unsigned int m, unsigned int y, Status s,
                     QDate dt):
    Person (snm, nm, ptr, bd, sx, edu, act), Vacancy (vnm, vid)
{
    phone_number = p;
    email = e;
    e_days = d;
    e_months = m;
    e_years = y;
    status = s;
    date = dt;
}

//Изменить статус
void Applicant::setStatus(Status s)
{
    status = s;
}

//Получить статус
QString Applicant::getStatus() const
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

QDataStream& operator<<(QDataStream &d, const Applicant &a)
{
    d << a.getSurname() << a.getName() << a.getPatronimic() << a.getbday() << a.getSex() << a.getEducation()
          << a.getActivity() << a.getVacancyName() << a.getId() << a.getPhoneNumber() << a.getEmail()
              << a.getExpDays() << a.getExpMonth() << a.getExpYears() << a.status << a.getDateOfConsideration();
    return d;
}
QDataStream& operator>>( QDataStream& d, Applicant &a)
{
    int s;
    d >> a.surname >> a.Person::name >> a.patronimic >> a.bday >> a.sex >> a.education >> a.activity
             >> a.Vacancy::name >> a.id >> a.phone_number >> a.email >> a.e_days >> a.e_months >> a.e_years >> s
            >> a.date;
    if(s == 0)
        a.setStatus(Status::CONSIDERATION);
    else if(s == 1)
        a.setStatus(Status::APPLIED);
    else if(s == 2)
        a.setStatus(Status::DENIED);
    return d;
}
