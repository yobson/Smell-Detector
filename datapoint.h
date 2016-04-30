#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <QObject>
#include <QtCore>
#include "logevent.h"
#include <QDateTime>

class DataPoint : public QObject
{
    Q_OBJECT
public:
    explicit DataPoint(QObject *parent = 0);


    void addData(LogEvent *logObject, double qualityOfAir, double lastValue);

    double airQuality();
    double deltaAirQuality();
    int year();
    double percentOfBoys();
    QString className();
    QDateTime timeOfLog();


private:

    double AIRQUALITY;
    double DELTAAIRQUALITY;
    int YEAR;
    double PERCENTOFBOYS;
    QString CLASSNAME;
    QDateTime TIMEOFLOG;

signals:

public slots:
};

#endif // DATAPOINT_H
