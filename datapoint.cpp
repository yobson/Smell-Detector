#include "datapoint.h"

DataPoint::DataPoint(QObject *parent) : QObject(parent)
{

}

void DataPoint::addData(LogEvent *logObject, double qualityOfAir, double lastValue) {
    AIRQUALITY = qualityOfAir;
    DELTAAIRQUALITY = qualityOfAir - lastValue;
    YEAR = logObject->year();
    BOYS = logObject->boys();
    GIRLS = logObject->girls();
    CLASSNAME = logObject->className();
    TIMEOFLOG = logObject->logDateTime();
}

void DataPoint::addBackupData(QString line)
{
    QStringList splitLine = line.split(", ");
    TIMEOFLOG = QDateTime::fromString(splitLine.value(0), "hh:mm dd/MM");
    AIRQUALITY = QString(splitLine.value(1)).toDouble();
    DELTAAIRQUALITY = QString(splitLine.value(2)).toDouble();
    CLASSNAME = splitLine.value(3);
    YEAR = QString(splitLine.value(4)).toInt();
    BOYS = QString(splitLine.value(5)).toInt();
    GIRLS = QString(splitLine.value(6)).toInt();
}


double DataPoint::airQuality() {
    return AIRQUALITY;
}

double DataPoint::deltaAirQuality() {
    return DELTAAIRQUALITY;
}

int DataPoint::year() {
    return YEAR;
}

int DataPoint::boys()
{
    return BOYS;
}

int DataPoint::girls()
{
    return GIRLS;
}

QString DataPoint::className() {
    return CLASSNAME;
}

QDateTime DataPoint::timeOfLog()
{
    return TIMEOFLOG;
}
