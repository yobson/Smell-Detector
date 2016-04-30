#ifndef LOGEVENT_H
#define LOGEVENT_H

#include <QObject>
#include <QtCore>
#include <QDateTime>

class LogEvent : public QObject
{
    Q_OBJECT
public:
    explicit LogEvent(QObject *parent = 0);
    void setSlotID(int slotID);
    void setClassName(QString className);
    void setYear(int year);
    void setBoys(int boys);
    void setGirls(int girls);
    void setLogDateTime(QDateTime logDateTime);

    void updateForNextLog();

    int slotID();
    QString className();
    int year();
    int boys();
    int girls();
    QDateTime logDateTime();


private:
    int SLOTID;
    QString CLASSNAME;
    int YEAR;
    int BOYS;
    int GIRLS;
    QDateTime LOGDATETIME;


signals:

public slots:
};

#endif // LOGEVENT_H
