#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QTimerEvent>

class DataSource : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(int val READ val NOTIFY valChanged)

public:
    explicit DataSource(
        QString id,
        int msec = 1000,
        int min = 10,
        int max = 100,
        QObject *parent = nullptr
    );
    ~DataSource();

    void updateVal();

public:
    QString id() const;

    bool active() const;
    void setActive(bool newActive);

    int val() const;

    void timerEvent(QTimerEvent *event);

private:
    QString m_id;
    int m_msec;
    int m_min;
    int m_max;

    bool m_active;
    int m_val;

    int m_timerId;

signals:
    void idChanged(QString p_id);
    void activeChanged(bool p_active);
    void valChanged(int p_val);
};

#endif // DATASOURCE_H
