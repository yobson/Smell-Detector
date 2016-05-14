#ifndef LOGGINGWINDOW_H
#define LOGGINGWINDOW_H

#include <QMainWindow>
#include "class.h"
#include "logevent.h"
#include "datapoint.h"
#include <QDateTime>
#include <QDate>
#include <QTimer>
#include "graph.h"

namespace Ui {
class LoggingWindow;
}

class LoggingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoggingWindow(QWidget *parent = 0);
    ~LoggingWindow();

    void setClassArray(Class **array);
    void setTimetableIndex(int *index);

private slots:
    void on_getTimeButton_clicked();
    void on_importButton_clicked();
    void on_showHideParentButton_clicked();
    void on_enableBackups_clicked();
    void on_startLoggingButton_clicked();
    void on_Log();
    void on_loadBackupButton_clicked();
    void on_addGraphButton_clicked();
    void removeGraph(int id);

private:
    Ui::LoggingWindow *ui;
    Class **classArray;
    int *timetableIndex;
    DataPoint **data;
    LogEvent **eventList;
    LogEvent *eventToPass;
    Graph **graphs;
    int indexOfNextLog;
    int numberOfEvents;
    int dataPointer;
    int logsSinceLastBackup;
    double lastValue;
    int graphTracker;
    bool parentWindowStatus;
    bool loggingStatus;
    QString backupFolder;
    QDateTime logStart;

    int timetableSlotFromTime(QTime time);
    QTime timeFromTimetableSlot(int i);
    QDate dateFromDay(int day);
    void setupLogTimer(LogEvent *LOGEVENT);
    void saveBackup();
    void addToTable(QString className, double airQuality, double deltaAirQuality, int year, int boys, int girls, QDateTime TimeOfLog);


    QTime *p1;
    QTime *p2;
    QTime *form;
    QTime *p3;
    QTime *p4;
    QTime *lunch;
    QTime *p5;

signals:
    void showHideWindow();
    void updateGraphs(DataPoint *data);

};

#endif // LOGGINGWINDOW_H
