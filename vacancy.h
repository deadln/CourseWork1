#ifndef VACANCY_H
#define VACANCY_H

#include <QString>
#include <QDate>

using namespace std;

class Vacancy
{
    QString name;
    QString id;
public:
    Vacancy() {name = ""; id = "";}
    Vacancy(QString n, QString i) {name = n; id = i;}
    QString getVacancyName(){return name;}
    QString getId(){return id;}
};

#endif // VACANCY_H
