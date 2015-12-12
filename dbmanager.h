#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QFileInfo>
#include <QVector>
#include <QSqlQueryModel>
#include "person.h"
#include "computer.h"

#ifndef DBMANAGER_H
#define DBMANAGER_H

/* NOTE: This code is no longer very easy to SQL inject, since the gui doesn't allow inputs of 'bad' characters
 * the worst you could to, is to comment out your own input. wow.
 */

class DbManager
{
public:
    DbManager(); //main constructor
    ~DbManager();
    QSqlQueryModel* getAllPersons();
    QSqlQueryModel* getAllComputers();
    QSqlQueryModel* getComputerXPersons(QString cid);
    QSqlQueryModel* getPersonXComputers(QString pid);
    QSqlQueryModel* getNComputerXPersons(QString cid);
    QSqlQueryModel* getNPersonXComputers(QString pid);
    QSqlQueryModel* getOnePerson(QString pid);
    QSqlQueryModel* getOneComputer(QString cid);
    bool addPerson(Person pers);
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
    QString toISO(QString date);
    QString fromISO(QString date);

    QSqlDatabase db;
};

#endif // DBMANAGER_H
