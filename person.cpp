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

Person::Person(QString s, QString n, QString p, int d, int m, int y,QString se, QString e, QString a)
{
    surname = s;
    name = n;
    patronimic = p;
    bday.setDate(y,m,d);
    sex = se;
    education = e;
    activity = a;
}
