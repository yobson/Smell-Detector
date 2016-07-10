#ifndef BARGRAPH_H
#define BARGRAPH_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <datapoint.h>
#include <QVBoxLayout>
#include <qcustomplot.h>
#include <statistic.h>

class BarGraph : public QObject
{
    Q_OBJECT
public:
    explicit BarGraph(QObject *parent = 0);
    ~BarGraph();
    QTabWidget *getGUI();
    void setID(int id);
    void setChartTitle(QString title);
    void setAxisName(QString name);
    void getAllData(DataPoint **allDataArray, int dataPointer);
    void setType(int type);
    void setInverted(bool invert);
    void setTimeRef(QDateTime time);

private:
    QString TITLE;
    QString YAXISTITLE;
    int ID;

    int TYPE;
    bool yInverted;
    QDateTime startOfLogging;


    QCustomPlot *graph;
    QPushButton *deleteButton;
    QVBoxLayout *layout;
    QPushButton *statistic;
    QTabWidget *tab;

    QVector<double> xData;
    QVector<double> yData;
    QVector<double> tempx;
    QVector<double> tempy;
    int numberOfDataPoints;

    int num7;
    int num8;
    int num9;
    int num10;
    int num11;
    int num12;
    int num13;

    float start7;
    float start8;
    float start9;
    float start10;
    float start11;
    float start12;
    float start13;

    int track7;
    int track8;
    int track9;
    int track10;
    int track11;
    int track12;
    int track13;

    QCPBars *bar7;
    QCPBars *bar8;
    QCPBars *bar9;
    QCPBars *bar10;
    QCPBars *bar11;
    QCPBars *bar12;
    QCPBars *bar13;

    float mean;
    float median;
    float mode;
    float variance;
    float standard;

    float highest;
    float sum;

    void updateChart();
    void dataPointToXY(DataPoint *data);
    void setUpVars();

signals:
    void deleteChart(int ID);

public slots:
    void deleteButtonClicked();
    void statButton();
    void addData(DataPoint *data);
};

#endif // BARGRAPH_H
