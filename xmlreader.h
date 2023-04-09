#ifndef XMLREADER_H
#define XMLREADER_H

#include <QString>
#include <QDomDocument>
#include <QObject>
#include <QMap>

class XMLReader : public QObject
{
    Q_OBJECT
public:
    XMLReader(const QString& fileName, QObject* parent = nullptr);
public slots:
    QMap<QString, QString> parseData();
signals:
    void dataParsed();
private:
    bool openFile();

    QDomDocument m_doc;
    QString m_fileName;

};

#endif // XMLREADER_H
