#include "graph.h"
#include "qcustomplot.h"

Graph::Graph(QObject *parent) : QObject(parent)
{
    xValues.resize(2048);
    yValues.resize(2048);
    numberOfPoints = 0;

    deleteButton = new QPushButton();
    graph = new QCustomPlot();
    layout = new QVBoxLayout();
    tab = new QTabWidget();

    graph->addGraph();
    graph->graph(0)->setData(xValues, yValues);
    deleteButton->setText("Remove Graph");
    layout->addWidget(graph);
    layout->addWidget(deleteButton);
    tab->setLayout(layout);

    connect(deleteButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

Graph::~Graph()
{
    xValues.clear();
    yValues.clear();

    delete graph;
    delete deleteButton;
    delete layout;
    delete tab;
}

void Graph::setAxisTypes(int x, bool invertx, int y, bool inverty) {
    xAxisType = x;
    yAxisType = y;
    xInverted = invertx;
    yInverted = inverty;
}

void Graph::setGraphTitle(QString title) {
    GRAPHTITLE = title;    
}

void Graph::setAxisTitles(QString x, QString y) {
    graph->xAxis->setLabel(x);
    graph->yAxis->setLabel(y);
}

void Graph::getAllData(DataPoint **allDataArray, int dataPointer) {
    for (int i = 0; i < dataPointer; i++) {
        this->dataPointToXY(allDataArray[i]);
    }
}

void Graph::setTimeRef(QDateTime time)
{
    startOfLogging = time;
}

void Graph::setID(int ID)
{
    id = ID;
}

QTabWidget *Graph::getGUI()
{
    return tab;
}



void Graph::dataPointToXY(DataPoint *data) {
    double Data = 0;
    switch (xAxisType) {
    case 0:
        Data = (float)startOfLogging.secsTo(data->timeOfLog());
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
    if (xInverted) { Data = 1/Data; }
    xValues[numberOfPoints] = Data;


    switch (yAxisType) {
    case 0:
        Data = (float)startOfLogging.secsTo(data->timeOfLog());
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
    if (yInverted) { Data = 1/Data; }
    yValues[numberOfPoints] = Data;

    numberOfPoints++;
    graph->graph(0)->setData(xValues, yValues);
    graph->rescaleAxes();
    graph->replot();
}

void Graph::addDataPoint(DataPoint *newData) {
    this->dataPointToXY(newData);
}

void Graph::onButtonClicked()
{
    emit deleteTab(id);
}
