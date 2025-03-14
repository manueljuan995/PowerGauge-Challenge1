#include "datasource.h"

#include <QRandomGenerator>
#include <QDebug>

DataSource::DataSource(
    QString id,
    int msec,
    int min,
    int max,
    QObject *parent)
    : QObject{parent}
{
    m_id = id;
    m_msec = msec;
    m_min = min;
    m_max = max;

    m_active = false;
    m_val = min;
    m_timerId = -1;
}

DataSource::~DataSource()
{
    if (m_timerId > 0) {
        killTimer(m_timerId);
        m_timerId = -1;
    }
}

void DataSource::updateVal()
{
    m_val = QRandomGenerator::global()->bounded(m_min, m_max);
    emit valChanged(m_val);
    qDebug() << QString("%1 value changed to %2").arg(m_id).arg(m_val);
}

bool DataSource::active() const
{
    return m_active;
}

void DataSource::setActive(bool newActive)
{
    if (m_active != newActive) {
        m_active = newActive;

        if (m_timerId > 0) {
            killTimer(m_timerId);
            m_timerId = -1;
        }

        if (newActive) {
            m_timerId = startTimer(m_msec);
        }

        emit activeChanged(newActive);
    }
}

int DataSource::val() const
{
    return m_val;
}

QString DataSource::id() const
{
    return m_id;
}

void DataSource::timerEvent(QTimerEvent *event)
{
    int timerId = event->timerId();
    if (m_timerId == timerId) {
        updateVal();
    }
}
