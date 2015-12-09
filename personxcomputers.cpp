#include "personxcomputers.h"

PersonXComputers::PersonXComputers()
{
    //Intentionally left empty
}

PersonXComputers::PersonXComputers(Person pers, QVector<Computer> comp)
{
    person = pers;
    computers = comp;
}

PersonXComputers::~PersonXComputers()
{
    //Intentionally left empty
}

void PersonXComputers::setPerson(Person pers)
{
    person = pers;
}

void PersonXComputers::setComputers(QVector<Computer> comp)
{
    computers = comp;
}

std::ostream& operator <<(std::ostream& os, PersonXComputers p_x_c)
{
    os << "Person: " << p_x_c.person.getName().toStdString() << endl;
    os << "Related to:" << endl;
    for(int i = 0; i < p_x_c.computers.size(); i++)
    {
        os << p_x_c.computers[i] << endl;
    }

    return os;
}
