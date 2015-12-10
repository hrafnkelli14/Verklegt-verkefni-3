#ifndef PERSON
#define PERSON

#include <string>
#include <fstream>
#include <iostream>
#include <QString>
#include <QDate>

using namespace std;

class Person
{
public:
    Person();   //default constructor
    ~Person();
    //'get' functions
    QString getName();
    QString getGender();
    QString getDoB();
    QString getDoD();
    QString getId();

    //'set' functions
    void setName(string _name);
    void setGender(string _gender);
    void setDoB(string dob);
    void setDoD(string dod);
    void setId(string _id);

    QDate strToQDate(string date); //QDate has a nice isValid() function

private:
    string name;
    string gender;
    string date_of_birth;
    string date_of_death;
    string id;

    bool checkDateFormat(string date); //needed for input checks (DD/MM/YYYY)

    friend std::istream& operator >>(std::istream& ins, Person& person1);
    friend std::ostream& operator <<(std::ostream& os, Person person1);
    friend bool operator ==(Person& lhs, const Person& rhs);
};
#endif
