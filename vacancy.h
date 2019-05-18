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
    QString getName();
    QString getId();
};

#endif // VACANCY_H
