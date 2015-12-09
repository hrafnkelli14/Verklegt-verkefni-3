#include "computer.h"
#include <iostream>

//========CONSTRUCTOR==========
Computer::Computer()
{
    name = "";
    year_of_build = "";
    type = "";
    was_built = false;
    id = "";
}

Computer::~Computer()
{
    //Intentionally left empty
}

//========PUBLIC FUNCTIONS==========
QString Computer::getName()
{
    return QString::fromStdString(name);
}

QString Computer::getYear()
{
    return QString::fromStdString(year_of_build);
}

QString Computer::getType()
{
    return QString::fromStdString(type);
}

bool Computer::getBuilt()
{
    return was_built;
}

QString Computer::getId()
{
    return QString::fromStdString(id);
}

void Computer::setName(string _name)
{
    name = _name;
}

void Computer::setYear(string _year_of_build)
{
    year_of_build = _year_of_build;
}

void Computer::setType(string _type)
{
    type = _type;
}

void Computer::setBuilt(bool _was_built)
{
    was_built = _was_built;
}

void Computer::setId(string _id)
{
    id = _id;
}

//========PRIVATE FUNCTIONS==========

//NO PRIVATE FUNCTIONS YET

//========FRIEND FUNCTIONS==========
istream& operator >>(std::istream& ins, Computer& comp)
{
    char built;

    cin.ignore(1000, '\n');

    while(comp.name.empty()) //a computer cant have no name
    {
        std::cout << "Enter the name of a computer: ";
        getline(ins, comp.name);
    }


    while(comp.type.empty()) //a computer must have a type
    {
        std::cout << "Enter the computer type: ";
        getline(ins, comp.type);
    }


    while(1)
    {
        std::cout << "Was the computer built(y for yes, n for no): ";
        ins >> built;

        if(built == 'Y' || built == 'y')
        {
            comp.was_built = true;
            break;
        }
        else if(built == 'N' || built == 'n')
        {
            comp.was_built = false;
            break;
        }
        else
        {
            cout << "Illegal character!" << endl;
        }
    }
    if(comp.was_built == true)
    {
        std::cout << "Enter the year it was built (? if unknown): ";
        ins >> comp.year_of_build;
        if(comp.year_of_build == "?")
        {
            comp.year_of_build = "NULL";
        }
    }
    else
    {
        comp.year_of_build = "NULL";
    }
    return ins;
}

ostream& operator <<(std::ostream& os, Computer comp)
{
    os << '#' << comp.id << ": ";
    os << "Name: " << comp.name << ", ";
    os << "Computer type: " << comp.type << ", ";
    if(comp.was_built)
    {
        os << "Build year: ";
        if(comp.year_of_build.empty())
        {
            os << "Unknown";
        }
        else
        {
            os << comp.year_of_build;
        }
    }

    return os;
}
