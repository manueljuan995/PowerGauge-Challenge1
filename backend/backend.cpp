#include "backend.h"

#define FILE_DATALIST "dataList5.json"
#define FILE_DATASOURCE "dataSource5.json"

#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "datasource.h"

Backend* Backend::m_instance = Q_NULLPTR;

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    readConfigFiles();
}

Backend::~Backend()
{

}

Backend *Backend::instance()
{
    if (m_instance == Q_NULLPTR)
    {
        m_instance = new Backend();
    }
    return m_instance;
}

void Backend::deleteInstance()
{
    delete m_instance;
    m_instance = Q_NULLPTR;
}

void Backend::readConfigFiles()
{
    m_dataList.clear();

    QFile dataSourceFile(QString(":/%1").arg(FILE_DATASOURCE));
    if (dataSourceFile.open(QFile::ReadOnly)) {
        QTextStream inDataSource(&dataSourceFile);

        QByteArray content = inDataSource.readAll().toUtf8();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(content);
        QVariantList dataSourceList = jsonDoc.array().toVariantList();

        QVariantMap dataSources;
        QListIterator<QVariant> i(dataSourceList);
        while (i.hasNext()) {
            QVariantMap dataSource = i.next().toMap();

            if (dataSource.contains("id")) {
                QString id = dataSource.value("id").toString();

                dataSources[id] = dataSource;
            }
        }

        QFile dataListFile(QString(":/%1").arg(FILE_DATALIST));
        if (dataListFile.open(QFile::ReadOnly)) {
            QTextStream inDataList(&dataListFile);

            QByteArray content = inDataList.readAll().toUtf8();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(content);
            QVariantList dataList = jsonDoc.array().toVariantList();

            QListIterator<QVariant> i(dataList);
            while (i.hasNext()) {
                QVariantMap data = i.next().toMap();

                QString dataSourceId = data.value("dataSource").toString();
                QVariantMap dataSource = dataSources.value(dataSourceId).toMap();
                if (!dataSource.isEmpty()) {
                    int msec = dataSource.value("msec").toInt();
                    int min = dataSource.value("min").toInt();
                    int max = dataSource.value("max").toInt();

                    DataSource *dataSourceObj = new DataSource(
                        dataSourceId,
                        msec,
                        min,
                        max,
                        this);

                    data["dataSource"] = QVariant::fromValue(dataSourceObj);
                    m_dataList << data;
                }
            }
        }
    }
}

QVariantList Backend::dataList() const
{
    return m_dataList;
}
