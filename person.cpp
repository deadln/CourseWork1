#include "person.h"

Person::Person()
{
    surname = "";
    name = "";
    patronimic = "";
    bday.setDate(1,1,1);
    sex = "";
    education = "";
    activity = "";
}

Person::Person(QString s, QString n, QString p, QDate b,QString se, QString e, QString a)
{
    surname = s;
    name = n;
    patronimic = p;
    bday = b;
    sex = se;
    education = e;
    activity = a;
}
