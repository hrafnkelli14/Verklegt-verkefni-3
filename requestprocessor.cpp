#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
    //intentionally left empty
}

RequestProcessor::~RequestProcessor()
{
     //Intentionally left empty
}

//========PUBLIC FUNCTIONS==========
bool RequestProcessor::addPerson(Person pers)
{
    return data.addPerson(pers);
}

bool RequestProcessor::addComputer(Computer comp)
{
    return data.addComputer(comp);
}

bool RequestProcessor::addComputerXPerson(QString cid, QString pid)
{
    return data.addComputerXPerson(cid, pid);
}

QSqlQueryModel* RequestProcessor::outputPersons()
{
    return data.getAllPersons();
}

QSqlQueryModel* RequestProcessor::outputComputers()
{
    return data.getAllComputers();
}

QSqlQueryModel* RequestProcessor::outputComputerXPersons(QString cid)
{
    return data.getComputerXPersons(cid);
}

QSqlQueryModel* RequestProcessor::outputPersonXComputers(QString pid)
{
    return data.getPersonXComputers(pid);
}

QSqlQueryModel* RequestProcessor::outputNComputerXPersons(QString cid)
{
    return data.getNComputerXPersons(cid);
}

QSqlQueryModel* RequestProcessor::outputNPersonXComputers(QString pid)
{
    return data.getNPersonXComputers(pid);
}

Person RequestProcessor::getPerson(QString id)
{
    return data.getPerson(id);
}

Computer RequestProcessor::getComputer(QString id)
{
    return data.getComputer(id);
}

bool RequestProcessor::editPerson(Person to_edit, QString pid)
{
    to_edit.setId(pid.toStdString());
    return data.editPerson(to_edit);
}

bool RequestProcessor::editComputer(Computer to_edit, QString cid)
{
    to_edit.setId(cid.toStdString());
    return data.editComputer(to_edit);
}

bool RequestProcessor::deletePerson(QString pid)
{
    return data.deletePerson(pid);
}

bool RequestProcessor::deleteComputer(QString cid)
{
    return data.deleteComputer(cid);
}

bool RequestProcessor::deleteRelation(QString cid, QString pid)
{
    return data.deleteComputerXPerson(cid, pid);
}
//========PRIVATE FUNCTIONS==========


