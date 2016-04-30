#include "loggingwindow.h"
#include "ui_loggingwindow.h"
#include "QTime"
#include "QtWidgets"

LoggingWindow::LoggingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoggingWindow)
{
    ui->setupUi(this);
    timetableIndex = new int[255];
    eventList = new LogEvent*[70];
    data = new DataPoint*[2048];
    numberOfEvents = 0;
    parentWindowStatus = true;
    loggingStatus = false;
    dataPointer = 0;

    p1 = new QTime(9,15,0,0);
    p2 = new QTime(10,15,0,0);
    form = new QTime(10,40,0,0);
    p3 = new QTime(11,55,0,0);
    p4 = new QTime(12,55,0,0);
    lunch = new QTime(13,45,0,0);
    p5 = new QTime(14,45,0,0);
}

LoggingWindow::~LoggingWindow()
{
    for (int i=0; i < 255; i++) {
        delete classArray[i];
    }
    for (int i = 0; i < 70; i++) {
        delete eventList[i];
    }
    for (int i = 0; i < 2048; i++) {
        delete data[i];
    }
    delete[] data;
    delete[] classArray;
    delete[] timetableIndex;
    delete[] eventList;

    delete ui;
}

void LoggingWindow::setClassArray(Class **array) {
    classArray = new Class*[255];
    for (int i = 0; i < 255; i++) {
        classArray[i] = array[i];
    }
}

void LoggingWindow::setTimetableIndex(int *index) {
    timetableIndex = index;
}


void LoggingWindow::on_getTimeButton_clicked()
{
    ui->currentTimeLabel->setText(QTime::currentTime().toString());
}

void LoggingWindow::on_importButton_clicked()
{
    ui->logPlanTable->setRowCount(0);
    ui->logPlanTable->setRowCount(70);

    QTableWidgetItem *statusBox = new QTableWidgetItem();
    int today = QDate::currentDate().dayOfWeek();
    int nextActiveSlot = 0;
    if (ui->week2Button->isChecked()) { today += 5; }
    int slot = timetableSlotFromTime(QTime::currentTime());
    if (slot == 7) {
            today ++;
            slot = 0;
    }
    if (today < 11) {
        nextActiveSlot = ((today-1)*7)+slot;
    }


    for (int i=0; i < 70; i++) {
        QTableWidgetItem *className = new QTableWidgetItem();
        QTableWidgetItem *nextLog = new QTableWidgetItem();

        if (timetableIndex[i] != -1) {
            className->setText(classArray[timetableIndex[i]]->name());
            QDateTime slotDateTime;
            QDate slotDate;
            int ii = i;
            if (i > 34) { ii = i - 35; }
            int day = (ii/7)+1;
            if (i < nextActiveSlot) { slotDate = QDate(this->dateFromDay(day)).addDays(7); }
            else { slotDate = QDate(this->dateFromDay(day)); }
            slotDateTime = QDateTime(slotDate, this->timeFromTimetableSlot(i));
            nextLog->setText(slotDateTime.toString());
            ui->logPlanTable->setItem(i, 1, nextLog);
            eventList[numberOfEvents] = new LogEvent(this);
            eventList[numberOfEvents]->setSlotID(i);
            eventList[numberOfEvents]->setClassName(classArray[timetableIndex[i]]->name());
            eventList[numberOfEvents]->setYear(classArray[timetableIndex[i]]->year());
            eventList[numberOfEvents]->setBoys(classArray[timetableIndex[i]]->boys());
            eventList[numberOfEvents]->setGirls(classArray[timetableIndex[i]]->girls());
            eventList[numberOfEvents]->setLogDateTime(slotDateTime);
            numberOfEvents++;
        } else {
            className->setText("FREE");
        }
        ui->logPlanTable->setItem(i, 0, className);
    }

    for (int i=0; i < numberOfEvents; i++) {
        if (eventList[i]->slotID() >= nextActiveSlot) {
            nextActiveSlot = eventList[i]->slotID();
            indexOfNextLog = i;
            break;
        }
    }
    statusBox->setText("x");
    ui->logPlanTable->setItem(nextActiveSlot, 2, statusBox);
    ui->nextLogLabel->setText(QString("Next Log: %1").arg(eventList[indexOfNextLog]->logDateTime().toString("hh:mm dd/MM/yy")));

    ui->startLoggingButton->setEnabled(true);
}

int LoggingWindow::timetableSlotFromTime(QTime time) {
    int returnInt;
    if (time.secsTo(*this->p1) > 0) {
        returnInt = 0;
    }
    else if (time.secsTo(*this->p2) > 0) {
        returnInt = 1;
    }
    else if (time.secsTo(*this->form) > 0) {
        returnInt = 2;
    }
    else if (time.secsTo(*this->p3) > 0) {
        returnInt = 3;
    }
    else if (time.secsTo(*this->p4) > 0) {
        returnInt = 4;
    }
    else if (time.secsTo(*this->lunch) > 0) {
        returnInt = 5;
    }
    else if (time.secsTo(*this->p5) > 0) {
        returnInt = 6;
    }
    else {
        returnInt = 7;
    }

    return returnInt;
}

QTime LoggingWindow::timeFromTimetableSlot(int i) {
    int period = i % 7;
    QTime returnTime;
    switch (period) {
    case 0:
        returnTime = *this->p1;
        break;
    case 1:
        returnTime = *this->p2;
        break;
    case 2:
        returnTime = *this->form;
        break;
    case 3:
        returnTime = *this->p3;
        break;
    case 4:
        returnTime = *this->p4;
        break;
    case 5:
        returnTime = *this->lunch;
        break;
    case 6:
        returnTime = *this->p5;
        break;
    }
    return returnTime;
}

QDate LoggingWindow::dateFromDay(int day)
{
    int daysToAdd = day - QDate::currentDate().dayOfWeek();
    if (daysToAdd < 0) { daysToAdd += 7; }
    return QDate::currentDate().addDays(daysToAdd);
}

void LoggingWindow::setupLogTimer(LogEvent *logEvent)
{

}

void LoggingWindow::on_showHideParentButton_clicked()
{
    emit showHideWindow();
    if ( parentWindowStatus) { ui->showHideParentButton->setText("Show Timetable Input Window"); }
    if (!parentWindowStatus) { ui->showHideParentButton->setText("Hide Timetable Input Window"); }
    parentWindowStatus = !parentWindowStatus;
}

void LoggingWindow::on_enableBackups_clicked()
{
    ui->backupLabel->setEnabled(!ui->backupLabel->isEnabled());
    ui->overwriteBackups->setEnabled(!ui->overwriteBackups->isEnabled());
    ui->logsPerBackup->setEnabled(!ui->logsPerBackup->isEnabled());
    ui->loadBackupButton->setEnabled(!ui->loadBackupButton->isEnabled());
    ui->setBackupFrequency->setEnabled(!ui->setBackupFrequency->isEnabled());
}

void LoggingWindow::on_startLoggingButton_clicked()
{
    if (!loggingStatus) {
        loggingStatus = true;
        ui->startLoggingButton->setText("Stop Logging");
    }
    else if (loggingStatus) {
        loggingStatus = false;
        ui->startLoggingButton->setText("Continue Logging");
    }
}

void LoggingWindow::on_Log(LogEvent *logEvent)
{

}
