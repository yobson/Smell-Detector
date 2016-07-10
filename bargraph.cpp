#include "bargraph.h"

BarGraph::BarGraph(QObject *parent) : QObject(parent)
{
    deleteButton = new QPushButton("Delete");
    statistic = new QPushButton("Get Stats");
    layout = new QVBoxLayout();
    tab = new QTabWidget();
    graph = new QCustomPlot();

    numberOfDataPoints = 0;
    tempx.resize(1);
    tempy.resize(1);

    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    connect(statistic, SIGNAL(clicked()), this, SLOT(statButton()));

    layout->addWidget(graph);
    //layout->addWidget(stats);
    layout->addWidget(statistic);
    layout->addWidget(deleteButton);
    tab->setLayout(layout);

    this->setUpVars();

    mode = 0;
    highest = 0;

    num7 = 0;
    num8 = 0;
    num9 = 0;
    num10 = 0;
    num11 = 0;
    num12 = 0;
    num13 = 0;

    bar7 = new QCPBars(graph->xAxis, graph->yAxis);
    bar8 = new QCPBars(graph->xAxis, graph->yAxis);
    bar9 = new QCPBars(graph->xAxis, graph->yAxis);
    bar10 = new QCPBars(graph->xAxis, graph->yAxis);
    bar11 = new QCPBars(graph->xAxis, graph->yAxis);
    bar12 = new QCPBars(graph->xAxis, graph->yAxis);
    bar13 = new QCPBars(graph->xAxis, graph->yAxis);

    graph->addPlottable(bar7);
    graph->addPlottable(bar8);
    graph->addPlottable(bar9);
    graph->addPlottable(bar10);
    graph->addPlottable(bar11);
    graph->addPlottable(bar12);
    graph->addPlottable(bar13);
}

BarGraph::~BarGraph()
{
    tempx.clear();
    tempy.clear();
    xData.clear();
    yData.clear();
    graph->clearGraphs();
    graph->clearItems();
    delete bar7;
    delete bar8;
    delete bar9;
    delete bar10;
    delete bar11;
    delete bar12;
    delete bar13;

    delete deleteButton;
    delete graph;
    delete layout;
    delete tab;
}

QTabWidget *BarGraph::getGUI()
{
    return tab;
}


void BarGraph::setID(int id)
{
    ID = id;
}

void BarGraph::setChartTitle(QString title)
{
    TITLE = title;
}

void BarGraph::setAxisName(QString name)
{
    graph->yAxis->setLabel(name);
}

void BarGraph::getAllData(DataPoint **allDataArray, int dataPointer)
{
    for (int i = 0; i < dataPointer; i++) {
        this->dataPointToXY(allDataArray[i]);
    }
}

void BarGraph::setInverted(bool invert)
{
    yInverted = invert;
}

void BarGraph::setTimeRef(QDateTime time)
{
    startOfLogging = time;
}

void BarGraph::setType(int type)
{
    TYPE = type;
}

void BarGraph::updateChart()
{
    //qDebug() << "Chart UPDATE!";
    bar7->clearData();
    bar8->clearData();
    bar9->clearData();
    bar10->clearData();
    bar11->clearData();
    bar12->clearData();
    bar13->clearData();

    start8 = 1.5*num7;
    start9 = start8+(1.5*num8);
    start10 = start9+(1.5*num9);
    start11 = start10+(1.5*num10);
    start12 = start11+(1.5*num11);
    start13 = start12+(1.5*num12);
    start7 = 0;

    QVector<double> ticks;
    QVector<QString> labels;

    //tempx.clear();
    //tempy.clear();

    for (int i = 0; i < numberOfDataPoints; i++) {

        bar7->setWidth(1);
        bar8->setWidth(1);
        bar9->setWidth(1);
        bar10->setWidth(1);
        bar11->setWidth(1);
        bar12->setWidth(1);
        bar13->setWidth(1);
        bar7->setPen(QColor(0, 0, 255));
        bar8->setPen(QColor(0, 255, 0));
        bar9->setPen(QColor(0, 255, 255));
        bar10->setPen(QColor(255, 0, 0));
        bar11->setPen(QColor(255, 0, 255));
        bar12->setPen(QColor(255, 255, 0));
        bar13->setPen(QColor(255, 255, 255));
        bar7->setBrush(QColor(0, 0, 255, 50));
        bar8->setBrush(QColor(0, 255, 0, 50));
        bar9->setBrush(QColor(0, 255, 255, 50));
        bar10->setBrush(QColor(255, 0, 0, 50));
        bar11->setBrush(QColor(255, 0, 255, 50));
        bar12->setBrush(QColor(255, 255, 0, 50));
        bar13->setBrush(QColor(255, 255, 255, 50));

        switch ((int)xData[i]) {
        case 7:
            tempx[0] = (1.5*track7);
            tempy[0] = yData[i];
            bar7->addData(tempx, tempy);
            //if (yData[i] > highest) { mode = 7; highest = yData[i]; }
            track7++;
            break;
        case 8:
            tempx[0] = start8+(1.5*track8);
            tempy[0] = yData[i];
            bar8->addData(tempx, tempy);
            //if (yData[i] > highest) { mode = 8; highest = yData[i]; }
            track8++;
            break;
        case 9:
            tempx[0] = start9+(1.5*track9);
            tempy[0] = yData[i];
            bar9->addData(tempx, tempy);
            //if (yData[i] > highest) { mode = 9; highest = yData[i]; }
            track9++;
            break;
        case 10:
            tempx[0] = start10+(1.5*track10);
            tempy[0] = yData[i];
            bar10->addData(tempx, tempy);
            //if (yData[i] > highest) { mode = 10; highest = yData[i]; }
            track10++;
            break;
        case 11:
            tempx[0] = start11+(1.5*track11);
            tempy[0] = yData[i];
            bar11->addData(tempx, tempy);
            //if (yData[i] > highest) { mode = 11; highest = yData[i]; }
            track11++;
            break;
        case 12:
            tempx[0] = start12+(1.5*track12);
            tempy[0] = yData[i];
            bar12->addData(tempx, tempy);
            //if (yData[i] > highest) { mode = 12; highest = yData[i]; }
            track12++;
            break;
        case 13:
            tempx[0] = start13+(1.5*track13);
            tempy[0] = yData[i];
            bar13->addData(tempx, tempy);
            //if (yData[i] > highest) { mode = 13; highest = yData[i]; }
            track13++;
            break;
        }
        //qDebug() << tempx[0];
        //tempy[i] = yData[i];

    }
    if (num7 > 0) {
        ticks << start7+(1.5*(num7-1))/2;
        labels << "Year 7";
    }
    if (num8 > 0) {
        ticks << start8+(1.5*(num8-1))/2;
        labels << "Year 8";
    }
    if (num9 > 0) {
        ticks << start9+(1.5*(num9-1))/2;
        labels << "Year 9";
    }
    if (num10 > 0) {
        ticks << start10+(1.5*(num10-1))/2;
        labels << "Year 10";
    }
    if (num11 > 0) {
        ticks << start11+(1.5*(num11-1))/2;
        labels << "Year 11";
    }
    if (num12 > 0) {
        ticks << start12+(1.5*(num12-1))/2;
        labels << "Year 12";
    }
    if (num13 > 0) {
        ticks << start13+(1.5*(num13-1))/2;
        labels << "Year 13";
    }

    //qDebug() << ticks;



    graph->xAxis->setAutoTicks(false);
    graph->xAxis->setAutoTickLabels(false);
    graph->xAxis->setTickVector(ticks);
    graph->xAxis->setTickVectorLabels(labels);
    graph->xAxis->setTickLabelRotation(60);
    graph->rescaleAxes();
    this->setUpVars();

}

void BarGraph::dataPointToXY(DataPoint *data)
{
    numberOfDataPoints++;
    xData.resize(numberOfDataPoints);
    yData.resize(numberOfDataPoints);
    //tempx.resize(numberOfDataPoints);
    //tempy.resize(numberOfDataPoints);
    //qDebug() << "Resized X & Y";

    xData[numberOfDataPoints-1] = data->year();

    switch (data->year()) {
    case 7:
        num7++;
        break;
    case 8:
        num8++;
        break;
    case 9:
        num9++;
        break;
    case 10:
        num10++;
        break;
    case 11:
        num11++;
        break;
    case 12:
        num12++;
        break;
    case 13:
        num13++;
        break;
    }

    double Data;
    switch (TYPE) {
    case 0:
        Data = (float)(startOfLogging.secsTo(data->timeOfLog()))/1000;
        break;
    case 1:
        Data = data->airQuality();
        break;
    case 2:
        Data = (data->airQuality())/(data->girls() + data->boys());
        break;
    case 3:
        Data = data->deltaAirQuality();
        break;
    case 4:
        Data = (double)data->year();
        break;
    case 5:
        Data = (double)data->boys();
        break;
    case 6:
        Data = (double)data->girls();
        break;
    }
    //if (yInverted) { Data = 1/Data; }
    yData[numberOfDataPoints-1] = Data;

    this->updateChart();
    graph->replot();


}

void BarGraph::setUpVars()
{


    track7 = 0;
    track8 = 0;
    track9 = 0;
    track10 = 0;
    track11 = 0;
    track12 = 0;
    track13 = 0;

    start7 = 0;
    start8 = 0;
    start9 = 0;
    start10 = 0;
    start11 = 0;
    start12 = 0;
    start13 = 0;
}

void BarGraph::deleteButtonClicked() {
    emit deleteChart(ID);
}

void BarGraph::statButton()
{
    Statistic *statWindow = new Statistic();
    statWindow->getStats(xData, yData, numberOfDataPoints, true);
    //statWindow->setX(xData);
    statWindow->show();
}

void BarGraph::addData(DataPoint *data)
{
    this->dataPointToXY(data);
}
