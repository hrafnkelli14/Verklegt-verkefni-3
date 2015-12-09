#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QFileInfo>
#include <QVector>
#include <QSqlQueryModel>
#include "person.h"
#include "computer.h"
#include "computerxpersons.h"
#include "personxcomputers.h"

#ifndef DBMANAGER_H
#define DBMANAGER_H

/* NOTE: This code is very easy to SQL inject and the bad guys are free to do so.
 * It's in fact so easy, that you have to watch your inputs to avoid accidentally
 * SQL injecting your database. It's very vulnerable to famous computer scientists like
 * Bobby Tables. We know this could be easily fixed by using placeholders instead of
 * just concatenating strings together. This method will be implemented next week.
 */

class DbManager
{
public:
    DbManager(); //main constructor
    ~DbManager();
    QSqlQueryModel* getAllPersons(QString order_by, QString view_gender); //outputs list according to order_by and view_gender
    QSqlQueryModel* getAllComputers(QString order_by);
    QSqlQueryModel* searchPersons(QString search_type, QString search_query, QString order_by, QString view_gender);
    QSqlQueryModel* searchComputers(QString search_type, QString search_query, QString order_by);
    ComputerXPersons getComputerXPersons(QString cid);
    PersonXComputers getPersonXComputers(QString pid);
    bool addPerson(Person pers); //adds person to Person table
    bool addComputer(Computer comp);
    bool addComputerXPerson(QString cid, QString pid);
    bool deletePerson(QString pid);
    bool deleteComputer(QString cid);
    bool deleteComputerXPerson(QString cid, QString pid);
    bool editPerson(Person pers);
    bool editComputer(Computer comp);
    Person getPerson(QString pid);
    Computer getComputer(QString cid);
private:
    bool execQuery(QString query_string); //executes query.
    void createTables(); //creates needed tables for the program
    QSqlQueryModel* findPersons(QString conditions); //finds persons based on conditions in condition string(they must have an sql syntax)
    QSqlQueryModel* findComputers(QString conditions);

    //helpers
    QString ascOrDesc(QString order_by);
    QString toISO(QString date);
    QString fromISO(QString date);

    QSqlDatabase db;
};

#endif // DBMANAGER_H
