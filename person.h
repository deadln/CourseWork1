#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>


class Person
{
    QString surname;
    QString name;
    QString patronimic;
    QDate bday;
    QString sex;
    QString education;
    QString activity;
public:
    Person();
    Person(QString s, QString n, QString p, int d, int m, int y,QString se, QString e, QString a);
};

#endif // PERSON_H
