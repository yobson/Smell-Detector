#include "loggingwindow.h"
#include "ui_loggingwindow.h"
#include "QTime"
#include "QtWidgets"
#include <QFileDialog>
#include <QFile>

LoggingWindow::LoggingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoggingWindow)
{
    ui->setupUi(this);
    timetableIndex = new int[255];
    eventList = new LogEvent*[70];
    data = new DataPoint*[2048];
    graphs = new Graph*[255];
    barGraphs = new BarGraph*[255];
    eventToPass = new LogEvent(this);
    parentWindowStatus = true;
    loggingStatus = false;
    dataPointer = 0;
    lastValue = 0;
    logsSinceLastBackup = 0;
    graphTracker = 0;
    barGraphTracker = 0;
    backupFolder = "";
    logStart = QDateTime::currentDateTime();
    barChart = false;

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
        delete graphs[i];
        delete barGraphs[i];
    }
    for (int i = 0; i < 70; i++) {
        delete eventList[i];
    }
    for (int i = 0; i < 2048; i++) {
        delete data[i];
    }
    delete eventToPass;
    delete[] data;
    delete[] classArray;
    delete[] timetableIndex;
    delete[] eventList;
    delete[] graphs;
    delete[] barGraphs;

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
    ui->currentTimeLabel->setText(QDateTime::currentDateTime().toString("hh:mm dd/MM/yy"));
}

void LoggingWindow::on_importButton_clicked()
{
    numberOfEvents = 0;
    ui->logPlanTable->setRowCount(0);
    ui->logPlanTable->setRowCount(70);

    QTableWidgetItem *statusBox = new QTableWidgetItem();
    int today = QDate::currentDate().dayOfWeek();
    bool weekend = false;
    if (today > 5) { today = 5; weekend = true; }
    int nextActiveSlot = (today-1)*7;
    if (!weekend) { nextActiveSlot += this->timetableSlotFromTime(QTime::currentTime()); }
    else { nextActiveSlot = 35; }
    if (ui->week2Button->isChecked()) { nextActiveSlot += 35; }
    if (nextActiveSlot >= 70) { nextActiveSlot = 0; }




    QDate dayOne = this->dateFromDay(1);
    if (ui->week1Button->isChecked()) { dayOne = dayOne.addDays(7); }


    for (int i=0; i < 70; i++) {
        QTableWidgetItem *className = new QTableWidgetItem();
        QTableWidgetItem *nextLog = new QTableWidgetItem();

        if (timetableIndex[i] != -1) {
            className->setText(classArray[timetableIndex[i]]->name());

            int ii = i;
            if (i > 34) {ii = i + 14; }
            int day = ii/7;
            if (i >= nextActiveSlot) { day = day - 14; }
            QDateTime slotDateTime = QDateTime(dayOne.addDays(day), this->timeFromTimetableSlot(i));
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
    statusBox->setText("Next Log Time");
    ui->logPlanTable->setItem(nextActiveSlot, 2, statusBox);
    ui->nextLogLabel->setText(QString("Next Log: %1").arg(eventList[indexOfNextLog]->logDateTime().toString("hh:mm dd/MM")));

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
    int today = QDate::currentDate().dayOfWeek();
    int daysToAdd = day - today;
    if (daysToAdd <= 0) { daysToAdd += 7; }
    return QDate::currentDate().addDays(daysToAdd);
}

void LoggingWindow::setupLogTimer(LogEvent *LOGEVENT)
{
    if (loggingStatus) {
        eventToPass = LOGEVENT;
        QTimer::singleShot(QDateTime::currentDateTime().msecsTo(eventList[indexOfNextLog]->logDateTime()), this, SLOT(on_Log()));
        qDebug() << "Set next log to happen at " << eventList[indexOfNextLog]->logDateTime().toString()
                 << " in " << QDateTime::currentDateTime().msecsTo(eventList[indexOfNextLog]->logDateTime())
                 << " mSecs";
    }
}

void LoggingWindow::saveBackup()
{
    QString fileName = QDateTime::currentDateTime().toString("MM/dd/hh-mm.backup");
    if (ui->overwriteBackups->isChecked()) {
        fileName = "backup.backup";
    }
    QString fullPath = QString("%1/%2").arg(backupFolder, fileName);

    QFile backup(fullPath, this);

    if (QFile::exists(fullPath)) {
        QFile::remove(fullPath);
    }

    QTextStream stream(&backup);

    if (backup.open(QIODevice::WriteOnly | QIODevice::Text)) {
        for (int i = 0; i < dataPointer; i++) {
            stream << data[i]->timeOfLog().toString("hh:mm dd/MM/yy") << ", "
                   << data[i]->airQuality() << ", "
                   << data[i]->deltaAirQuality() << ", "
                   << data[i]->className() << ", "
                   << data[i]->year() << ", "
                   << data[i]->boys() << ", "
                   << data[i]->girls();
        }
        backup.flush();
        backup.close();
        logsSinceLastBackup = 0;
    }
}

void LoggingWindow::addToTable(QString ClassName, double airQuality, double deltaAirQuality, int Year, int boys, int girls, QDateTime TimeOfLog)
{
    int row = ui->logDataTable->rowCount();
    ui->logDataTable->setRowCount(row+1);

    QTableWidgetItem *className = new QTableWidgetItem();
    QTableWidgetItem *qualityOfAir = new QTableWidgetItem();
    QTableWidgetItem *deltaQuality = new QTableWidgetItem();
    QTableWidgetItem *year = new QTableWidgetItem();
    QTableWidgetItem *Boys = new QTableWidgetItem();
    QTableWidgetItem *Girls = new QTableWidgetItem();
    QTableWidgetItem *timeOfLog = new QTableWidgetItem();

    className->setText(ClassName);
    qualityOfAir->setText(QString("%1").arg(airQuality));
    deltaQuality->setText(QString("%1").arg(deltaAirQuality));
    year->setText(QString("%1").arg(Year));
    Boys->setText(QString("%1").arg(boys));
    Girls->setText(QString("%1").arg(girls));
    timeOfLog->setText(TimeOfLog.toString("hh:mm dd/MM/yy"));

    ui->logDataTable->setItem(row, 0, timeOfLog);
    ui->logDataTable->setItem(row, 1, qualityOfAir);
    ui->logDataTable->setItem(row, 2, deltaQuality);
    ui->logDataTable->setItem(row, 3, className);
    ui->logDataTable->setItem(row, 4, year);
    ui->logDataTable->setItem(row, 5, Boys);
    ui->logDataTable->setItem(row, 6, Girls);
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

    if (ui->enableBackups->isChecked()){
        backupFolder = QFileDialog::getExistingDirectory(this, "Backup Folder", QDir::currentPath());
        qDebug() << backupFolder;
        if (backupFolder == "") {
            ui->enableBackups->setChecked(false);
            this->on_enableBackups_clicked();
        }
    }
}

void LoggingWindow::on_startLoggingButton_clicked()
{
    if (!loggingStatus) {
        loggingStatus = true;
        ui->startLoggingButton->setText("Stop Logging");
        this->setupLogTimer(eventList[indexOfNextLog]);
    }
    else if (loggingStatus) {
        loggingStatus = false;
        ui->startLoggingButton->setText("Continue Logging");
    }
}

void LoggingWindow::on_Log()
{
    qDebug() << "Logging! Time of this log is: " << QDateTime::currentDateTime().toString();
    data[dataPointer] = new DataPoint();
    data[dataPointer]->addData(eventToPass, 0, lastValue);
    lastValue = 0;
    emit updateGraphs(data[dataPointer]);

    this->addToTable(data[dataPointer]->className(),
                     data[dataPointer]->airQuality(),
                     data[dataPointer]->deltaAirQuality(),
                     data[dataPointer]->year(),
                     data[dataPointer]->boys(),
                     data[dataPointer]->girls(),
                     data[dataPointer]->timeOfLog());

    QTableWidgetItem *nextCell = new QTableWidgetItem();
    QTableWidgetItem *blankCell = new QTableWidgetItem();
    QTableWidgetItem *nextLog = new QTableWidgetItem();

    nextCell->setText("Next Log Time");
    eventList[indexOfNextLog]->setLogDateTime((eventList[indexOfNextLog]->logDateTime().addDays(14)));
    nextLog->setText(eventList[indexOfNextLog]->logDateTime().toString());

    indexOfNextLog ++;
    if (indexOfNextLog > numberOfEvents) {
        indexOfNextLog = 0;
    }

    ui->logPlanTable->setItem(eventList[indexOfNextLog]->slotID(), 2, nextCell);
    ui->logPlanTable->setItem(eventToPass->slotID(), 2, blankCell);
    ui->logPlanTable->setItem(eventToPass->slotID(), 1, nextLog);

    this->setupLogTimer(eventList[indexOfNextLog]);
    ui->nextLogLabel->setText(QString("Next Log: %1").arg(eventList[indexOfNextLog]->logDateTime().toString("hh:mm dd/MM/yy")));

    dataPointer++;
    logsSinceLastBackup++;
    if (logsSinceLastBackup >= ui->logsPerBackup->text().toInt() && ui->enableBackups->isChecked()) { this->saveBackup(); }
}

void LoggingWindow::on_loadBackupButton_clicked()
{
    QString path = QDir::currentPath();
    if (backupFolder != "") { path = backupFolder; }
    QString fileToOpen = QFileDialog::getOpenFileName(this,
                                                      "Open Backup",
                                                      path,
                                                      tr("Backup File (*.backup)"));
    if (fileToOpen != "") {
        QFile backupFile(fileToOpen);
        QTextStream fileInput(&backupFile);

        if (backupFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while (!fileInput.atEnd()) {
                qDebug() << "Loading line of Backup File";
                QString line = fileInput.readLine();
                data[dataPointer] = new DataPoint(this);
                data[dataPointer]->addBackupData(line);
                emit updateGraphs(data[dataPointer]);

                this->addToTable(data[dataPointer]->className(),
                                 data[dataPointer]->airQuality(),
                                 data[dataPointer]->deltaAirQuality(),
                                 data[dataPointer]->year(),
                                 data[dataPointer]->boys(),
                                 data[dataPointer]->girls(),
                                 data[dataPointer]->timeOfLog());
                lastValue = data[dataPointer]->airQuality();
                dataPointer++;


            }
        }
    }

}

void LoggingWindow::on_addGraphButton_clicked()
{
    if (!barChart) {
        this->addSkatterGraph();
    }
    else {
        this->addBarChart();
    }
}

void LoggingWindow::addSkatterGraph()
{
    graphs[graphTracker] = new Graph(this);
    graphs[graphTracker]->setGraphTitle(ui->graphNameText->text());
    QString x, y;
    x = this->getAxisTitle(ui->xValueBox->currentIndex());
    if (ui->xInverted->isChecked()) {
        x = QString("1 / %1").arg(x);
    }

    y = this->getAxisTitle(ui->yValueBox->currentIndex());
    if (ui->yInverted->isChecked()) {
        y = QString("1 / %1").arg(y);
    }

    qDebug() << "HERE!";

    graphs[graphTracker]->setAxisTitles(x, y);
    graphs[graphTracker]->setAxisTypes(ui->xValueBox->currentIndex(), ui->xInverted->isChecked(), ui->yValueBox->currentIndex(), ui->yInverted->isChecked());
    graphs[graphTracker]->setID(graphTracker);
    graphs[graphTracker]->setTimeRef(logStart);
    graphs[graphTracker]->getAllData(data, dataPointer);

    connect(graphs[graphTracker], SIGNAL(deleteTab(int)), this, SLOT(removeGraph(int)));
    connect(this, SIGNAL(updateGraphs(DataPoint*)), graphs[graphTracker], SLOT(addDataPoint(DataPoint*)));

    ui->graphTabWidget->addTab(graphs[graphTracker]->getGUI(), ui->graphNameText->text());
    graphTracker++;
}

void LoggingWindow::addBarChart() {
    barGraphs[barGraphTracker] = new BarGraph(this);
    barGraphs[barGraphTracker]->setID(barGraphTracker);
    barGraphs[barGraphTracker]->setInverted(ui->yInverted);
    barGraphs[barGraphTracker]->setType(ui->yValueBox->currentIndex());
    barGraphs[barGraphTracker]->setTimeRef(logStart);
    barGraphs[barGraphTracker]->setAxisName(this->getAxisTitle(ui->yValueBox->currentIndex()));
    connect(barGraphs[barGraphTracker], SIGNAL(deleteChart(int)), this, SLOT(removeBarGraph(int)));
    connect(this, SIGNAL(updateGraphs(DataPoint*)), barGraphs[barGraphTracker], SLOT(addData(DataPoint*)));

    barGraphs[barGraphTracker]->getAllData(data, dataPointer);

    ui->graphTabWidget->addTab(barGraphs[barGraphTracker]->getGUI(), ui->graphNameText->text());
    barGraphTracker++;
}

QString LoggingWindow::getAxisTitle(int i)
{
    QString y;
    switch (i) {
    case 0:
        y = "Time";
        break;
    case 1:
        y = "Air Quality";
        break;
    case 2:
        y = "Air Quality per Child";
        break;
    case 3:
        y = "Change in Air Quality";
        break;
    case 4:
        y = "Year";
        break;
    case 5:
        y = "Boys";
        break;
    case 6:
        y = "Girls";
        break;
    }
    return y;
}

void LoggingWindow::removeGraph(int id)
{
    delete graphs[id];
}

void LoggingWindow::removeBarGraph(int id)
{
    delete barGraphs[id];
}

void LoggingWindow::on_xValueBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Year") {
        ui->addGraphButton->setText("Add Bar Chart");
        barChart = true;
    } else {
        ui->addGraphButton->setText("Add Scatter Graph");
        barChart = false;
    }
}
