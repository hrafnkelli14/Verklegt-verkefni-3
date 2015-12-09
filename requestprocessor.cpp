#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
    readSettings();
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

void RequestProcessor::updateSettings()
{
    settings.update(personOrderingToQStr(), computerOrderingToQStr(), gendertypeToQStr());
}

bool RequestProcessor::isCommand(QString command_string)
{
    QString command = "";

    int i = 0;
    while(1) //finds command
    {
        if(command_string[i] == ' ')
        {
            break;
        }
        else
        {
            command += command_string[i];
        }

        if(i > command_string.length())
        {
            return false;
        }

        i++;
    }

    if(command == "edit")
    {
        return true;
    }
    else if(command == "delete")
    {
        return true;
    }
    else if(command == "addr")
    {
        return true;
    }
    else if(command == "viewr")
    {
        return true;
    }

    return false;
}

QString RequestProcessor::extractCommand(QString command_string)
{
    QString command = "";
    int i = 0;
    while(1) //finds command
    {
        if(command_string[i] == ' ')
        {
            break;
        }
        else
        {
            command += command_string[i];
        }

        if(i > command_string.length())
        {
            return ""; //redundant
        }

        i++;
    }

    return command;
}

QString RequestProcessor::extractId(QString command_string)
{
    return command_string.section(' ', 1);
}

QVector<Person> RequestProcessor::outputPersons()
{
    return data.getAllPersons(personOrderingToQStr(), gendertypeToQStr());
}

QVector<Computer> RequestProcessor::outputComputers()
{
    return data.getAllComputers(computerOrderingToQStr());
}

ComputerXPersons RequestProcessor::outputComputerXPersons(QString cid)
{
    return data.getComputerXPersons(cid);
}

PersonXComputers RequestProcessor::outputPersonXComputers(QString pid)
{
    return data.getPersonXComputers(pid);
}

QVector<Person> RequestProcessor::searchPersons(QString search_string)
{
    QVector<Person> search_results;
    Person temp;
    QString search_type = "";
    QString search_query = "";

    if(search_string == "*")
    {
        return outputPersons();
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
            return QVector<Person>();
        }

        i++;
    }


    if(search_type == "id")
    {
        search_type = "pID";
    }

    search_query = search_string.section(' ', 1); //finds the search query itself
    search_results = data.searchPersons(search_type, search_query, personOrderingToQStr(), gendertypeToQStr());
    return search_results;
}

QVector<Computer> RequestProcessor::searchComputers(QString search_string)
{
    QVector<Computer> search_results;
    Computer temp;
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
            return QVector<Computer>();
        }

        i++;
    }

    if(search_type == "id")
    {
        search_type = "cID";
    }

    search_query = search_string.section(' ', 1); //finds the search query itself
    search_results = data.searchComputers(search_type, search_query, computerOrderingToQStr());
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

void RequestProcessor::setPersonOrdering(personordering _order_by)
{
    person_order_by = _order_by;
}

void RequestProcessor::setComputerOrdering(computerordering _order_by)
{
    computer_order_by = _order_by;
}

void RequestProcessor::setGenderView(gendertype _view_gender)
{
    view_gender = _view_gender;
}

personordering RequestProcessor::getPersonOrdering()
{
    return person_order_by;
}

computerordering RequestProcessor::getComputerOrdering()
{
    return computer_order_by;
}

gendertype RequestProcessor::getGenderView()
{
    return view_gender;
}

//========PRIVATE FUNCTIONS==========
//--settings functions--
QString RequestProcessor::personOrderingToQStr()
{
    switch(person_order_by)
    {
    case NAME:
        return "NAME";
        break;
    case NAME_R:
        return "NAME_R";
        break;
    case DOB:
        return "DOB";
        break;
    case DOB_R:
        return "DOB_R";
        break;
    case DOD:
        return "DOD";
        break;
    case DOD_R:
        return "DOD_R";
        break;
    case pID:
        return "pID";
        break;
    case pID_R:
        return "pID_R";
        break;
    }

    return "";
}

QString RequestProcessor::computerOrderingToQStr()
{
    switch(computer_order_by)
    {
    case CNAME:
        return "NAME";
        break;
    case CNAME_R:
        return "NAME_R";
        break;
    case YEAR:
        return "YEAR";
        break;
    case YEAR_R:
        return "YEAR_R";
        break;
    case TYPE:
        return "TYPE";
        break;
    case TYPE_R:
        return "TYPE_R";
        break;
    case cID:
        return "cID";
        break;
    case cID_R:
        return "cID_R";
        break;
    }

    return "";
}

QString RequestProcessor::gendertypeToQStr()
{
    switch(view_gender)
    {
    case MALE:
        return "MALE";
        break;
    case FEMALE:
        return "FEMALE";
        break;
    case BOTH:
        return "BOTH";
        break;
    }

    return "";
}

void RequestProcessor::readPersonOrdering()
{
    QString orderingQStr = settings.getPersonOrdering();
    if(orderingQStr == "NAME")
    {
        person_order_by = NAME;
    }
    else if(orderingQStr == "NAME_R")
    {
        person_order_by = NAME_R;
    }
    else if(orderingQStr == "DOB")
    {
        person_order_by = DOB;
    }
    else if(orderingQStr == "DOB_R")
    {
        person_order_by = DOB_R;
    }
    else if(orderingQStr == "DOD")
    {
        person_order_by = DOD;
    }
    else if(orderingQStr == "DOD_R")
    {
        person_order_by = DOD_R;
    }
    else if(orderingQStr == "pID")
    {
        person_order_by = pID;
    }
    else if(orderingQStr == "pID_R")
    {
        person_order_by = pID_R;
    }
    else
    {
        person_order_by = NAME; //defaults to name
    }
}

void RequestProcessor::readComputerOrdering()
{
    QString orderingQStr = settings.getComputerOrdering();
    if(orderingQStr == "NAME")
    {
        computer_order_by = CNAME;
    }
    else if(orderingQStr == "NAME_R")
    {
        computer_order_by = CNAME_R;
    }
    else if(orderingQStr == "YEAR")
    {
        computer_order_by = YEAR;
    }
    else if(orderingQStr == "YEAR_R")
    {
        computer_order_by = YEAR_R;
    }
    else if(orderingQStr == "TYPE")
    {
        computer_order_by = TYPE;
    }
    else if(orderingQStr == "TYPE_R")
    {
        computer_order_by = TYPE_R;
    }
    else if(orderingQStr == "cID")
    {
        computer_order_by = cID;
    }
    else if(orderingQStr == "cID_R")
    {
        computer_order_by = cID_R;
    }
    else
    {
        computer_order_by = CNAME; //defaults to name
    }
}

void RequestProcessor::readGenderView()
{
    QString genderViewQStr = settings.getViewGender();
    if(genderViewQStr == "MALE")
    {
        view_gender = MALE;
    }
    else if(genderViewQStr == "FEMALE")
    {
        view_gender = FEMALE;
    }
    else if(genderViewQStr == "BOTH")
    {
        view_gender = BOTH;
    }
    else
    {
        view_gender = BOTH; //defaults to both
    }
}

void RequestProcessor::readSettings()
{
    readPersonOrdering();
    readComputerOrdering();
    readGenderView();
}
