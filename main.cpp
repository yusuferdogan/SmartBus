#include <QCoreApplication>
#include <QFile>
#include <QtXml>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<< "jjdjjd";

    QFile *file = new QFile("settings.xml");
    if(!file->open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Could not open the XML File";
        return -1;
    }

    QXmlStreamReader *reader = new QXmlStreamReader(file);
    QXmlStreamWriter *writer = new QXmlStreamWriter(file);

    while(!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->readNext();

        if(token == QXmlStreamReader::StartDocument)
            continue;

        if(token == QXmlStreamReader::StartElement) {
            if(reader->name() == "IsSetting")
            {
                QString str = reader->readElementText();

                if(str == "True")
                {
                    //continue
                }
                else
                {
                   writer->setAutoFormatting(true);
                   writer->writeStartDocument();
                   writer->writeStartElement("Application");
                   writer->writeTextElement("IP", "192.168.2.45");
                }

            }
        }
    }

    return a.exec();
}
