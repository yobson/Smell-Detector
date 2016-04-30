#include "class.h"

Class::Class(QObject *parent) : QObject(parent)
{

}

void Class::setName(QString name) {
    NAME = name;
}

void Class::setBoys(int boys) {
    BOYS = boys;
}

void Class::setGirls(int girls) {
    GIRLS = girls;
}

void Class::setYear(int year) {
    YEAR = year;
}

QString Class::name() {
    return NAME;
}

int Class::boys() {
    return BOYS;
}

int Class::girls() {
    return GIRLS;
}

int Class::year() {
    return YEAR;
}
