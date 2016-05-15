#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <datapoint.h>
#include <QVBoxLayout>
#include <qcustomplot.h>

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = 0);
    ~Graph();
    void setAxisTypes(int x, bool invertx, int y, bool inverty);
    void setGraphTitle(QString title);
    void setAxisTitles(QString x, QString y);
    void getAllData(DataPoint **allDataArray, int dataPointer);
    void setTimeRef(QDateTime time);
    void setID(int ID);
    QTabWidget* getGUI();

private:
    //Graph Values
    int id;
    QVector<double> xValues;
    QVector<double> yValues;
    QString GRAPHTITLE;
    QDateTime startOfLogging;

    //Smell Dependent
    int xAxisType;
    int yAxisType;
    bool xInverted;
    bool yInverted;
    int numberOfPoints;
    void dataPointToXY(DataPoint *data);

    //UI Components
    QCustomPlot *graph;
    QPushButton *deleteButton;
    QVBoxLayout *layout;
    QTabWidget *tab;

signals:
    void deleteTab(int ID);

public slots:
    void addDataPoint(DataPoint *newData);
    void onButtonClicked();
};

#endif // GRAPH_H
