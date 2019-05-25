#include "vacancy.h"

QDataStream& operator<<(QDataStream &d, const Vacancy &v)
{
    d << v.name << v.id;
    return d;
}

QDataStream& operator>>( QDataStream& d,  Vacancy &v)
{
    d >> v.name >> v.id;
    return d;
}
