#include "person.h"

//========CONSTRUCTORS==========
Person::Person()
{
    name = "";
    gender = "";
    date_of_birth = "";
    date_of_death = "";
    id = "";
}

Person::~Person()
{
    //Intentionally left empty
}

//========PUBLIC FUNCTIONS==========
QString Person::getName()
{
    return QString::fromStdString(name);
}

QString Person::getGender()
{
    return QString::fromStdString(gender);
}

QString Person::getDoB()
{
    return QString::fromStdString(date_of_birth);
}

QString Person::getDoD()
{
    return QString::fromStdString(date_of_death);
}

QString Person::getId()
{
    return QString::fromStdString(id);
}

void Person::setName(string _name)
{
    name = _name;
}

void Person::setGender(string _gender)
{
    gender = _gender;
}

void Person::setDoB(string dob)
{
    date_of_birth = dob;
}

void Person::setDoD(string dod)
{
    date_of_death = dod;
}

void Person::setId(string _id)
{
    id = _id;
}

//========PRIVATE FUNCTIONS==========
bool Person::checkDateFormat(string date)
{
    if(date.size() != 10)
    {
        return false;
    }

    for(unsigned int i=0; i<date.size(); i++)
    {
        if(i == 2 || i == 5)
        {
            if(date[i] != '/')
            {
                return false;
            }
        }
        else
        {
            if(!isdigit(date[i]))
            {
                return false;
            }
        }
    }

    return true;

}

QDate Person::strToQDate(string date)
{
    int day = stoi(date.substr(0,2));
    int month = stoi(date.substr(3,2));
    int year = stoi(date.substr(6,4));

    QDate date_check(year, month, day);

    return date_check;
}


//========FRIEND FUNCTIONS==========
istream& operator >>(istream& ins, Person& person1)
{
    char temp;  //temporary variable to enter a character for the persons gender
    string temp_gender;  //makes the interface easier to read
    QDate bdate, ddate; //for checking valid dates

    cin.ignore(1000, '\n'); //this is needed because cin leaves stuff in the buffer

    while(person1.name.empty()) //a person can't have no name
    {
       cout << "Enter the name of a computer scientist: ";
       getline(ins, person1.name);
    }

    while(1) //input checker
    {
        cout << "Enter that scientists gender (m for male, f for female): ";
        cin >> temp;
        if(temp == 'm')
        {
            person1.gender = "Male";
            temp_gender = "his ";
            break;
        }
        else if(temp == 'f')
        {
            person1.gender = "Female";
            temp_gender = "her ";
            break;
        }
    }

    while(1) //input checker
    {
        cout << "Enter " << temp_gender << "date of birth (DD/MM/YYYY): ";
        ins >> person1.date_of_birth;

        if(person1.checkDateFormat(person1.date_of_birth))
        {
            bdate = person1.strToQDate(person1.date_of_birth);
            if(bdate.isValid() && bdate < QDate::currentDate())
            {
                break;
            }
        }
    }

    while(1) //input checker
    {
        cout << "Enter " << temp_gender << "date of death (DD/MM/YYYY - enter 0 for still alive): ";
        ins >> person1.date_of_death;
        if(person1.date_of_death == "0")
        {
            person1.date_of_death = "alive";
            break;
        }


        if(person1.checkDateFormat(person1.date_of_death))
        {
            ddate = person1.strToQDate(person1.date_of_death);
            if(ddate.isValid() && bdate < ddate && ddate <= QDate::currentDate())
            {
                break;
            }
        }
    }
    return ins;
}

ostream& operator <<(ostream& os, Person person1)
{
    os << '#' << person1.id << ": ";
    os << "Name: " <<  person1.name << ", ";
    os << "Gender: " << person1.gender << ", ";
    os << "Born: " << person1.date_of_birth << ", ";
    if(person1.date_of_death != "alive")
    {
        os << "Died: " << person1.date_of_death;
    }

    return os;
}

bool operator ==(Person& lhs, const Person& rhs)
{
    bool samename = (lhs.name == rhs.name);
    bool samegender = (lhs.gender == lhs.gender);
    bool samedob = (lhs.date_of_birth == rhs.date_of_birth);
    bool samedod = (lhs.date_of_death == rhs.date_of_death);

    if(samename && samegender && samedob && samedod)
    {
        return true;
    }
    else
    {
        return false;
    }
}
