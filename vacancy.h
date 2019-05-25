#ifndef VACANCY_H
#define VACANCY_H

#include <QString>
#include <QDate>
#include <QDataStream>
#include <QFile>

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

    friend QDataStream& operator<<(QDataStream &d, const Vacancy &v);
    friend QDataStream& operator>>( QDataStream& d, Vacancy &v);
};

#endif // VACANCY_H
