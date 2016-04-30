#include "datapoint.h"

DataPoint::DataPoint(QObject *parent) : QObject(parent)
{

}

void DataPoint::addData(LogEvent *logObject, double qualityOfAir, double lastValue) {
    AIRQUALITY = qualityOfAir;
    DELTAAIRQUALITY = qualityOfAir - lastValue;
    YEAR = logObject->year();
    PERCENTOFBOYS = 100*(logObject->boys()/(logObject->boys()+logObject->girls()));
    CLASSNAME = logObject->className();
    TIMEOFLOG = logObject->logDateTime();
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

double DataPoint::percentOfBoys() {
    return PERCENTOFBOYS;
}

QString DataPoint::className() {
    return CLASSNAME;
}

QDateTime DataPoint::timeOfLog()
{
    return TIMEOFLOG;
}
