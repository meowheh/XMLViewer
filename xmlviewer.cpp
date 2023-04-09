#include "xmlviewer.h"
#include "xmlreader.h"
#include "ui_xmlviewer.h"

//Основные требования:
//1.	Основное окно пользовательского интерфейса должно представлять из себя таблицу(QTableView(!))
//  и набор кнопок(очистить таблицу, импортировать данные);
//2.	Содержимое таблицы (должно загружаться из БД(SQLite)) должно отображаться благодаря кастомной табличной
//модели данных (QAbstractTableModel(!), не QSqlTableModel), все изменения в таблице(удаление и импорт записей)
//должны обновляться и в БД. Работа с БД должна вестись в отдельном потоке, не блокируя пользовательский интерфейс;
//3.	При импорте записей пользователь выбирает папку с XML-файлами(пример структуры загружаемых файлов в каталоге
//                                                                  TestFolder);
//4.	Импорт файлов должен происходить в отдельном потоке. При парсинге предусмотреть окно прогресса с отображением
//количества успешно импортированных записей, ошибок и имён файлов, содержащих ошибки;
//5.	Используя контекстное меню, записи в таблице должны удаляться, редактироваться, экспортироваться в XML-файл;
//6.	При первом запуске или при отсутствии файла БД(файл должен находиться в том же каталоге, что и исполняемый файл)
//должен создаваться новый.


XMLViewer::XMLViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::XMLViewer)
{
    ui->setupUi(this);
    connect(ui->importDataButton, SIGNAL(clicked(bool)), this, SLOT(chooseFileImport()));

}

XMLViewer::~XMLViewer()
{
    delete ui;
}

void XMLViewer::chooseFileImport()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Импортировать файл"),
                                  "/TestFolder", tr("XML files (*.xml)"));
    for(const QString &fn : fileNames)
    {
        XMLReader reader(fn);
        QFuture<QMap<QString, QString>> future = QtConcurrent::run(&XMLReader::parseData, &reader);
        future.waitForFinished();
        QMap<QString, QString> data = future.result();
        addProgress(fn, data);
    }

}

void XMLViewer::addProgress(const QString& fn, QMap<QString, QString> data)
{
    ui->logXML->append(fn + QString(":\n"));
    if(!data.isEmpty())
    {
        for(const QString& key : data.keys())
        {
            ui->logXML->append(key + QString(": ") + data.value(key));
        }
    }
    else
    {
        ui->logXML->append("Ошибка чтения файла");
    }
    ui->logXML->append("\n");
}

