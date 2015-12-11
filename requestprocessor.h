#include <QString>
#include <QVector>
#include <algorithm>
#include "dbmanager.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

class RequestProcessor
{
public:
    RequestProcessor();
    ~RequestProcessor();
    bool addPerson(Person pers); //contains the famous middle-out compression algorithm
    bool addComputer(Computer comp);
    bool addComputerXPerson(QString cid, QString pid);

    QSqlQueryModel* outputPersons();
    QSqlQueryModel* outputComputers();
    QSqlQueryModel* outputComputerXPersons(QString cid);
    QSqlQueryModel* outputPersonXComputers(QString pid);
    QSqlQueryModel* outputNComputerXPersons(QString cid);
    QSqlQueryModel* outputNPersonXComputers(QString pid);

    Person getPerson(QString id);
    Computer getComputer(QString id);

    bool editPerson(Person to_edit, QString id);
    bool editComputer(Computer to_edit, QString id);
    bool deletePerson(QString id);
    bool deleteComputer(QString id);
    bool deleteRelation(QString cid, QString pid);
private:
    DbManager data; //sql database connection
};

#endif // REQUESTPROCESSOR_H
