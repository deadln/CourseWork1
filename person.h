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
    Person(QString s, QString n, QString p, QDate b,QString se, QString e, QString a);
    QString getSurname() {return surname; }
    QString getName() {return name; }
    QString getPatronimic() {return patronimic; }
    QDate getbday() {return bday; }
    QString getSex() {return sex; }
    QString getEducation() {return education; }
    QString getActivity() {return activity; }

};

#endif // PERSON_H
