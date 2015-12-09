#include "xmlfile.h"

//========CONSTRUCTORS==========
XmlFile::XmlFile()
{
    person_order_by = "NAME";
    computer_order_by = "NAME";
    view_gender = "BOTH";

    filename = "settings.xml";
    file.setFileName(filename);
    xmlwriter.setDevice(&file);
    xmlreader.setDevice(&file);

    readFile();
}

XmlFile::~XmlFile()
{
     //Intentionally left empty
}

//========PUBLIC FUNCTIONS==========
QString XmlFile::getPersonOrdering()
{
    return person_order_by;
}

QString XmlFile::getComputerOrdering()
{
    return computer_order_by;
}

QString XmlFile::getViewGender()
{
    return view_gender;
}

void XmlFile::update(QString _person_order_by, QString _computer_order_by, QString _view_gender)
{
    person_order_by = _person_order_by;
    computer_order_by = _computer_order_by;
    view_gender = _view_gender;
    writeToFile();
}

//========PRIVATE FUNCTIONS==========
void XmlFile::writeToFile()
{
    file.open(QIODevice::WriteOnly);

    xmlwriter.setAutoFormatting(true);
    xmlwriter.writeStartDocument();

    xmlwriter.writeStartElement("settings");

    xmlwriter.writeStartElement("person");
    xmlwriter.writeTextElement("person_order_by", person_order_by);
    xmlwriter.writeTextElement("view_gender", view_gender);
    xmlwriter.writeEndElement();
    xmlwriter.writeStartElement("computer");
    xmlwriter.writeTextElement("computer_order_by", computer_order_by);
    //TODO COMPUTER VIEW TYPE?
    xmlwriter.writeEndElement();

    xmlwriter.writeEndElement();

    file.close();
}

void XmlFile::readFile()
{
    if(!file.exists())
    {
        return;
    }
    file.open(QIODevice::ReadOnly);
    xmlreader.setDevice(&file);

    xmlreader.readNext();
    while(!xmlreader.atEnd()) //this is super ugly, BUT IT WORKS!. Everything I've tried to clean it up breaks its functionality.. BEWARE
    {
        if(xmlreader.isStartElement())
        {
            // <settings>
            if(xmlreader.name() == "settings")
            {
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "person_order_by")
            {
                person_order_by = xmlreader.readElementText();
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "view_gender")
            {
                view_gender = xmlreader.readElementText();
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "computer_order_by")
            {
                computer_order_by = xmlreader.readElementText();
                xmlreader.readNext();
            }
            // </settings>
       }
       else if (xmlreader.isEndElement())
       {
           xmlreader.readNext();
       }
       xmlreader.readNext();
    }
    file.close();
}
