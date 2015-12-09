#include <QString>
#include <QVector>
#include <algorithm>
#include "xmlfile.h"
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

    void updateSettings(); //what happens here?

    bool isCommand(QString command_string);
    QString extractCommand(QString command_string);
    QString extractId(QString command_string);

    QSqlQueryModel* outputPersons();
    QSqlQueryModel* outputComputers();
    ComputerXPersons outputComputerXPersons(QString cid);
    PersonXComputers outputPersonXComputers(QString pid);
    QSqlQueryModel* searchPersons(QString search_string);
    QSqlQueryModel* searchComputers(QString search_string);

    Person getPerson(QString id);
    Computer getComputer(QString id);

    bool editPerson(Person to_edit, QString id);
    bool editComputer(Computer to_edit, QString id);
    bool deletePerson(QString id);
    bool deleteComputer(QString id);
    bool deleteRelation(QString cid, QString pid);
private:
    XmlFile settings; //xml file connection(settings)
    DbManager data; //sql database connection
};

#endif // REQUESTPROCESSOR_H
