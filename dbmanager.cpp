#include "dbmanager.h"

//========CONSTRUCTORS==========
DbManager::DbManager()
{
    QFileInfo checkFile(QCoreApplication::applicationDirPath() + "\\data.db");
    bool db_exists = checkFile.exists();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "\\data.db");

    if(!db_exists)
    {
        createTables();
    }

    execQuery("SELECT * FROM *"); //for some reason you have to display the list twice unless you do this

}

DbManager::~DbManager()
{
     //Intentionally left empty
    db.close();
}

//========PUBLIC FUNCTIONS==========
QSqlQueryModel* DbManager::getAllPersons()
{
    return findPersons("");
}

QSqlQueryModel* DbManager::getAllComputers()
{
    return findComputers("");
}

QSqlQueryModel* DbManager::getComputerXPersons(QString cid)
{
    db.open();
    QSqlQuery *qry = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();

    qry->exec("PRAGMA foreign_keys=ON");

    qry->exec("SELECT RP.pID AS 'id', "
              "RP.name AS Name, "
              "RP.gender AS Gender, "
              "RP.dob AS 'Date of Birth', "
              "CASE WHEN dod = 'alive' THEN 'Still alive' ELSE dod END AS 'Date of Death' "
              "FROM (SELECT Persons.pID, name, gender, dob, dod "
                    "FROM ComputersXPersons "
                    "INNER JOIN Persons ON Persons.pID = ComputersXPersons.pID "
                    "WHERE cID = " + cid + ") AS RP");

    model->setQuery(*qry);

    db.close();

    return model;

}

QSqlQueryModel* DbManager::getPersonXComputers(QString pid)
{
    db.open();
    QSqlQuery *qry = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();

    qry->exec("PRAGMA foreign_keys=ON");

    qry->exec("SELECT RP.cID AS 'id', "
              "RP.name AS Name, "
              "CASE WHEN RP.built = 0 THEN 'Not Built' WHEN RP.year IS NULL THEN 'Unknown' ELSE RP.year END AS 'Build Year', "
              "RP.type AS Type, "
              "CASE WHEN RP.built = 1 THEN 'Yes' ELSE 'No' END AS Built "
              "FROM (SELECT Computers.cID, name, year, built, type "
                    "FROM ComputersXPersons "
                    "INNER JOIN Computers ON Computers.cID = ComputersXPersons.cID "
                    "WHERE pID = " + pid + ") AS RP");

    model->setQuery(*qry);

    db.close();

    return model;
}

QSqlQueryModel* DbManager::getNComputerXPersons(QString cid)
{
    db.open();
    QSqlQuery *qry = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();

    qry->exec("PRAGMA foreign_keys=ON");

    qry->exec("SELECT pID AS 'id', " //first finds every person
              "name AS Name, "
              "gender AS Gender, "
              "dob AS 'Date of Birth', "
              "CASE WHEN dod = 'alive' THEN 'Still alive' ELSE dod END AS 'Date of Death' "
              "FROM Persons "
              "EXCEPT " //every person that exists, except those who are related
              "SELECT RP.pID AS 'id', "
              "RP.name AS Name, "
              "RP.gender AS Gender, "
              "RP.dob AS 'Date of Birth', "
              "CASE WHEN RP.dod = 'alive' THEN 'Still alive' ELSE RP.dod END AS 'Date of Death' "
              "FROM (SELECT Persons.pID, name, gender, dob, dod "
                     "FROM ComputersXPersons "
                     "INNER JOIN Persons ON Persons.pID = ComputersXPersons.pID "
                     "WHERE cID = " + cid + ") AS RP");

    model->setQuery(*qry);

    db.close();

    return model;
}

QSqlQueryModel* DbManager::getNPersonXComputers(QString pid)
{
    db.open();
    QSqlQuery *qry = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();

    qry->exec("PRAGMA foreign_keys=ON");

    qry->exec("SELECT cID AS 'id', " //uses same method as ncomputerxpersons
              "name AS Name, "
              "CASE WHEN built = 0 THEN 'Not Built' WHEN year IS NULL THEN 'Unknown' ELSE year END AS 'Build Year', "
              "type AS Type, "
              "CASE WHEN built = 1 THEN 'Yes' ELSE 'No' END AS Built "
              "FROM Computers "
              "EXCEPT "
              "SELECT RP.cID AS 'id', "
              "RP.name AS Name, "
              "CASE WHEN RP.built = 0 THEN 'Not Built' WHEN RP.year IS NULL THEN 'Unknown' ELSE RP.year END AS 'Build Year', "
              "RP.type AS Type, "
              "CASE WHEN RP.built = 1 THEN 'Yes' ELSE 'No' END AS Built "
              "FROM (SELECT Computers.cID, name, year, built, type "
                    "FROM ComputersXPersons "
                    "INNER JOIN Computers ON Computers.cID = ComputersXPersons.cID "
                    "WHERE pID = " + pid + ") AS RP");

    model->setQuery(*qry);

    db.close();

    return model;
}

QSqlQueryModel* DbManager::getOnePerson(QString pid)
{
    return findPersons("WHERE pID = " + pid);
}

QSqlQueryModel* DbManager::getOneComputer(QString cid)
{
    return findComputers("WHERE cID = " + cid);
}

bool DbManager::addPerson(Person pers)
{
    QString dob_iso = toISO(pers.getDoB());
    QString dod_iso = toISO(pers.getDoD());

    return execQuery("INSERT INTO Persons VALUES ( "
                     "NULL, '" +
                     pers.getName() + "','" +
                     pers.getGender() + "','" +
                     dob_iso + "','" +
                     dod_iso + "')");
}

bool DbManager::addComputer(Computer comp)
{
    QString was_built = "";
    switch (comp.getBuilt())
    {
    case 0:
        was_built = "0";
        break;
    case 1:
        was_built = "1";
        break;
    }

    return execQuery("INSERT INTO Computers (name, year, type, built) "
                     "VALUES ( '" +
                     comp.getName() + "'," +
                     comp.getYear() + ",'" +
                     comp.getType() + "', " +
                     was_built + " )");
}

bool DbManager::addComputerXPerson(QString cid, QString pid)
{
    bool executed = false;
    db.open();
    QSqlQuery qry;
    executed = qry.exec("INSERT INTO ComputersXPersons (pID, cID) "
                        "VALUES (" +
                        pid + "," +
                        cid + ")");
    db.close();
    return executed;
}

bool DbManager::deletePerson(QString pid)
{
    bool executed = false;
    db.open();
    QSqlQuery qry;
    executed = qry.exec("DELETE FROM ComputersXPersons "
                        "WHERE pID = " + pid);
    if(!executed)
    {
        db.close();
        return executed;
    }

    executed = qry.exec("DELETE FROM Persons "
                        "WHERE pID = " + pid);

    db.close();
    return executed;
}

bool DbManager::deleteComputer(QString cid)
{
    bool executed = false;
    db.open();
    QSqlQuery qry;
    executed = qry.exec("DELETE FROM ComputersXPersons "
                        "WHERE cID = " + cid);
    if(!executed)
    {
        db.close();
        return executed;
    }

    executed = qry.exec("DELETE FROM Computers "
                        "WHERE cID = " + cid);

    db.close();
    return executed;
}

bool DbManager::deleteComputerXPerson(QString cid, QString pid)
{
    bool executed = false;
    db.open();
    QSqlQuery qry;
    executed = qry.exec("DELETE FROM ComputersXPersons "
                        "WHERE pID = " + pid + " " +
                        "AND cID = " + cid);

    db.close();
    return executed;
}

bool DbManager::editPerson(Person pers)
{
    QString dob_iso = toISO(pers.getDoB());
    QString dod_iso = toISO(pers.getDoD());

    return execQuery("UPDATE Persons "
                     "SET name = '" + pers.getName() + "', "
                     "gender = '" + pers.getGender() + "', "
                     "dob = '" + dob_iso + "', "
                     "dod = '" + dod_iso + "' "
                     "WHERE pID = " + pers.getId());
}

bool DbManager::editComputer(Computer comp)
{
    QString was_built = "";
    switch (comp.getBuilt())
    {
    case 0:
        was_built = "0";
        break;
    case 1:
        was_built = "1";
        break;
    }

    return execQuery("UPDATE Computers "
                     "SET name = '" + comp.getName() + "', "
                     "year = " + comp.getYear() + ", "
                     "type = '" + comp.getType() + "', "
                     "built = " + was_built + " "
                     "WHERE cID = " + comp.getId());
}

Person DbManager::getPerson(QString pid)
{
    db.open();
    Person temp;
    QSqlQuery qry;
    qry.exec("PRAGMA foreign_keys=ON");

    qry.exec("SELECT pID, name, gender, dob, dod "
             "FROM Persons "
             "WHERE pID = " + pid);

    int i_id = qry.record().indexOf("pID");
    int i_name = qry.record().indexOf("name");
    int i_gender = qry.record().indexOf("gender");
    int i_dob = qry.record().indexOf("dob");
    int i_dod = qry.record().indexOf("dod");

    while(qry.next())
    {
        temp.setId(qry.value(i_id).toString().toStdString());
        temp.setName(qry.value(i_name).toString().toStdString());
        temp.setGender(qry.value(i_gender).toString().toStdString());
        temp.setDoB(fromISO(qry.value(i_dob).toString()).toStdString());
        temp.setDoD(fromISO(qry.value(i_dod).toString()).toStdString());
    }
    db.close();

    return temp;
}

Computer DbManager::getComputer(QString cid)
{
    db.open();
    Computer temp;
    QSqlQuery qry;
    qry.exec("PRAGMA foreign_keys=ON");

    qry.exec("SELECT cID, name, year, type, built "
             "FROM Computers "
             "WHERE cID = " + cid);

    int i_id = qry.record().indexOf("cID");
    int i_name = qry.record().indexOf("name");
    int i_year = qry.record().indexOf("year");
    int i_type = qry.record().indexOf("type");
    int i_built = qry.record().indexOf("built");

    while(qry.next())
    {
        temp.setId(qry.value(i_id).toString().toStdString());
        temp.setName(qry.value(i_name).toString().toStdString());
        temp.setYear(qry.value(i_year).toString().toStdString());
        temp.setType(qry.value(i_type).toString().toStdString());
        temp.setBuilt(stoi(qry.value(i_built).toString().toStdString())); //stoi to change to bool
    }
    db.close();

    return temp;
}

//========PRIVATE FUNCTIONS==========
bool DbManager::execQuery(QString query_string)
{
    bool executed = false;
    db.open();
    QSqlQuery qry;
    qry.exec("PRAGMA foreign_keys = ON");
    executed = qry.exec(query_string);
    db.close();

    return executed;
}

void DbManager::createTables()
{
    execQuery("CREATE TABLE Persons ( "
              "pID INTEGER PRIMARY KEY AUTOINCREMENT, " //we don't have to worry about ID with autoincrement
              "name VARCHAR[40], "
              "gender VARCHAR[7], " //this might be changed to char
              "dob DATE, "
              "dod DATE, "
              "UNIQUE (name) )");

    execQuery("CREATE TABLE Computers ( "
              "cID INTEGER PRIMARY KEY AUTOINCREMENT, "
              "name VARCHAR[40], "
              "year INT, "
              "type VARCHAR[20], "
              "built BOOLEAN, "
              "UNIQUE (name) )");

    execQuery("CREATE TABLE ComputersXPersons ( "
              "pID INT, "
              "cID INT, "
              "FOREIGN KEY (pID) REFERENCES Persons(pID), "
              "FOREIGN KEY (cID) REFERENCES Computers(cID), "
              "PRIMARY KEY(pID, cID))");
}

QSqlQueryModel* DbManager::findPersons(QString conditions)
{
    db.open();
    QSqlQuery *qry = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    qry->exec("PRAGMA foreign_keys=ON");

    qry->exec("SELECT pID, "
              "name AS Name, "
              "gender AS Gender, "
              "dob AS 'Date of Birth', "
              "CASE WHEN dod = 'alive' THEN 'Still alive' ELSE dod END AS 'Date of Death' "
              "FROM Persons "
              + conditions);

    model->setQuery(*qry);
    db.close();

    return model;
}

QSqlQueryModel* DbManager::findComputers(QString conditions)
{
    db.open();
    QSqlQuery *qry = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    qry->exec("PRAGMA foreign_keys=ON");

    qry->exec("SELECT cID, "
              "name AS Name, "
              "CASE WHEN built = 0 THEN 'Not Built' WHEN year IS NULL THEN 'Unknown' ELSE year END AS 'Build Year', "
              "type AS Type, "
              "CASE WHEN built = 1 THEN 'Yes' ELSE 'No' END AS Built "
              "FROM Computers "
              + conditions);

    model->setQuery(*qry);
    db.close();

    return model;
}

QString DbManager::toISO(QString date)
{
    if(date == "alive")
    {
        return "alive";
    }

    QString year = date.mid(6,4);
    QString month = date.mid(3,2);
    QString day = date.mid(0,2);

    return year + '-' + month + '-' + day;
}

QString DbManager::fromISO(QString date)
{
    if(date == "alive")
    {
        return "alive";
    }

    QString year = date.mid(0,4);
    QString month = date.mid(5,2);
    QString day = date.mid(8,2);

    return day + '/' + month + '/' + year;
}

