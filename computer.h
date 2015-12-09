#include <QString>
#include <string>

#ifndef COMPUTER_H
#define COMPUTER_H

using namespace std;

class Computer
{
public:
    Computer();
    ~Computer();
    //'get' functions
    QString getName();
    QString getYear();
    QString getType();
    bool getBuilt();
    QString getId();

    //'set' functions
    void setName(string _name);
    void setYear(string _year_of_build);
    void setType(string _type);
    void setBuilt(bool _was_built);
    void setId(string _id);

private:
    string name;
    string year_of_build;
    string type;
    bool was_built;
    string id;

    friend std::istream& operator >>(std::istream& ins, Computer& comp);
    friend std::ostream& operator <<(std::ostream& os, Computer comp);
};

#endif // COMPUTER_H
