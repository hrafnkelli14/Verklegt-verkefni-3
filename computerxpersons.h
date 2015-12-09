#include "relation.h"

#ifndef COMPUTERXPERSONS_H
#define COMPUTERXPERSONS_H


class ComputerXPersons : public Relation
{
public:
    ComputerXPersons();
    ~ComputerXPersons();
    ComputerXPersons(Computer comp, QVector<Person> pers);
    void setComputer(Computer comp);
    void setPersons(QVector<Person> pers);

    friend std::ostream& operator <<(std::ostream& os, ComputerXPersons c_x_p);
};

#endif // COMPUTERXPERSONS_H
