#include "relation.h"

#ifndef PERSONXCOMPUTERS_H
#define PERSONXCOMPUTERS_H


class PersonXComputers : public Relation
{
public:
    PersonXComputers();
    PersonXComputers(Person pers, QVector<Computer> comp);
    ~PersonXComputers();
    void setPerson(Person pers);
    void setComputers(QVector<Computer> comp);

    friend std::ostream& operator <<(std::ostream& os, PersonXComputers p_x_c);
};

#endif // PERSONXCOMPUTERS_H
