#include "logevent.h"

LogEvent::LogEvent(QObject *parent) : QObject(parent)
{

}

void LogEvent::setSlotID(int slotID) {
    SLOTID = slotID;
}

void LogEvent::setClassName(QString className) {
    CLASSNAME = className;
}

void LogEvent::setYear(int year) {
    YEAR = year;
}

void LogEvent::setBoys(int boys) {
    BOYS = boys;
}

void LogEvent::setGirls(int girls) {
    GIRLS = girls;
}

void LogEvent::setLogDateTime(QDateTime logDateTime) {
    LOGDATETIME = logDateTime;
}


void LogEvent::updateForNextLog() {
    if (LOGDATETIME.secsTo(QDateTime::currentDateTime()) < 0) {
        LOGDATETIME.addDays(14);
    }
}


int LogEvent::slotID() {
    return SLOTID;
}

QString LogEvent::className() {
    return CLASSNAME;
}

int LogEvent::year() {
    return YEAR;
}

int LogEvent::boys() {
    return BOYS;
}

int LogEvent::girls() {
    return GIRLS;
}

QDateTime LogEvent::logDateTime() {
    return LOGDATETIME;
}
