#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QVariant>

class Backend : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QVariantList dataList READ dataList NOTIFY dataListChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    static Backend* instance();
    static void deleteInstance();

    void readConfigFiles();

    QVariantList dataList() const;

signals:
    void dataListChanged(QVariantList p_list);

private:
    static Backend* m_instance;

    QVariantList    m_dataList;
};

#endif // BACKEND_H
