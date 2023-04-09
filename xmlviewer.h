#ifndef XMLVIEWER_H
#define XMLVIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtConcurrent>

QT_BEGIN_NAMESPACE
namespace Ui { class XMLViewer; }
QT_END_NAMESPACE

class XMLViewer : public QMainWindow
{
    Q_OBJECT

public:
    XMLViewer(QWidget *parent = nullptr);
    ~XMLViewer();
private slots:
    void chooseFileImport();
    void addProgress(const QString& fn, QMap<QString, QString> data);
private:
    Ui::XMLViewer *ui;
};
#endif // XMLVIEWER_H
