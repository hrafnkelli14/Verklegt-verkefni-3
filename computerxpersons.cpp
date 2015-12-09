#include "computerxpersons.h"

ComputerXPersons::ComputerXPersons()
{
    //Intentionally left empty
}

ComputerXPersons::ComputerXPersons(Computer comp, QVector<Person> pers)
{
    computer = comp;
    persons = pers;
}

ComputerXPersons::~ComputerXPersons()
{
     //Intentionally left empty
}

void ComputerXPersons::setComputer(Computer comp)
{
    computer = comp;
}

void ComputerXPersons::setPersons(QVector<Person> pers)
{
    persons = pers;
}

std::ostream& operator <<(std::ostream& os, ComputerXPersons c_x_p)
{
    os << "Computer: " << c_x_p.computer.getName().toStdString() << endl;
    os << "Related to:" << endl;
    for(int i = 0; i < c_x_p.persons.size(); i++)
    {
        os << c_x_p.persons[i] << endl;
    }

    return os;
}
