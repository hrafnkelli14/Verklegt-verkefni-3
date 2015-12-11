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

QSqlQueryModel* RequestProcessor::searchPersons(QString search_string)
{
    QSqlQueryModel *search_results = new QSqlQueryModel();
    QString search_type = "";
    QString search_query = "";

    if(search_string == "*")
    {
        //return outputPersons();
    }

    int i = 0;
    while(1) //finds searchBy
    {
        if(search_string[i] == ' ')
        {
            break;
        }
        else
        {
            search_type += search_string[i];
        }

        if(i > search_string.length())
        {
            return NULL;
        }

        i++;
    }


    if(search_type == "id")
    {
        search_type = "pID";
    }

    search_query = search_string.section(' ', 1); //finds the search query itself
    //search_results = data.searchPersons(search_type, search_query, personOrderingToQStr(), gendertypeToQStr());
    return search_results;
}

QSqlQueryModel* RequestProcessor::searchComputers(QString search_string)
{
    QSqlQueryModel *search_results = new QSqlQueryModel();
    QString search_type = "";
    QString search_query = "";

    if(search_string == "*")
    {
        return outputComputers();
    }

    int i = 0;
    while(1) //finds searchBy
    {
        if(search_string[i] == ' ')
        {
            break;
        }
        else
        {
            search_type += search_string[i];
        }

        if(i > search_string.length())
        {
            return NULL;
        }

        i++;
    }

    if(search_type == "id")
    {
        search_type = "cID";
    }

    search_query = search_string.section(' ', 1); //finds the search query itself
    //search_results = data.searchComputers(search_type, search_query, computerOrderingToQStr());
    return search_results;
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


