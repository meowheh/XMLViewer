#include "xmlviewer.h"
#include "sqlconnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!SQLConnection::createConnection())
        return EXIT_FAILURE;
    XMLViewer w;
    w.show();
    return a.exec();
}
