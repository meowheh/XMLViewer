#include "xmlreader.h"
#include <QFile>
#include <QDebug>

XMLReader::XMLReader(const QString& fn, QObject *parent) : QObject(parent), m_fileName(fn)
{

}

bool XMLReader::openFile()
{
    QFile file(m_fileName);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    if(!m_doc.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}

QMap<QString, QString> XMLReader::parseData()
{
    QMap<QString, QString> data;
    bool isOpen = openFile();
    if(isOpen)
    {
        QDomElement docElement = m_doc.documentElement();
        QDomNode node = docElement.firstChild();
        while(!node.isNull())
        {
            QDomElement element = node.toElement();
            if(!element.isNull())
            {
                data.insert(element.tagName(), element.text());
            }
            node = node.nextSibling();
        }
        emit dataParsed();
    }
    return data;
}

