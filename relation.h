#include <QVector>
#include <QString>
#include "person.h"
#include "computer.h"

#ifndef RELATION_H
#define RELATION_H


class Relation
{
public:
    Relation();
    ~Relation();
protected:
    QVector<Person> persons;
    QVector<Computer> computers;
    Person person;
    Computer computer;
};

#endif // RELATION_H
