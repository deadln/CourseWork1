#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>


class Person
{
protected:
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
    QString getSurname() const {return surname; }
    QString getName() const {return name; }
    QString getPatronimic() const {return patronimic; }
    QDate getbday() const {return bday; }
    QString getSex() const {return sex; }
    QString getEducation() const {return education; }
    QString getActivity() const {return activity; }

};

#endif // PERSON_H
