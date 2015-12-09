#include <QFile>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QVector>
#include "person.h"

#ifndef XMLFILE_H
#define XMLFILE_H


class XmlFile {
public:
    XmlFile(); //Constructor
    ~XmlFile();
    QString getPersonOrdering();
    QString getComputerOrdering();
    QString getViewGender();
    void update(QString _person_order_by, QString _computer_order_by, QString _view_gender); //updates order_by and view_gender and calls WriteToFile()
private:
    void writeToFile(); //writes order_by and view_gender to XML file
    void readFile(); //Reads data from XML file
    QString filename; //filename of xml file
    QFile file; //file instance
    QString person_order_by; //will be converted to enum in requestprocessor
    QString computer_order_by;
    QString view_gender; //will be converted to enum in requestprocessor
    QXmlStreamWriter xmlwriter; //QXml library writer
    QXmlStreamReader xmlreader; //QXml library reader
};

#endif // XMLFILE_H
