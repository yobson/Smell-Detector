#include "statistic.h"
#include "ui_statistic.h"

Statistic::Statistic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistic)
{
    ui->setupUi(this);
}

Statistic::~Statistic()
{
    delete ui;
}

void Statistic::getStats(QVector<double> xData, QVector<double> yData, int numberOfDataPoints, bool discrete)
{
    x = xData;
    y = yData;
    total = numberOfDataPoints;
    dis = discrete;

    ui->mode->setText(QString("Mode: %1").arg(this->findMode()));
    ui->mean->setText(QString("Mean: %1").arg(this->findMean()));
}

double Statistic::findMode()
{
    double highest = 0;
    double mode = 0;

    for (int i = 0; i < total; i++) {
        //qDebug() << "Testing " << y[i] << " from year " << x[i];
        if (y[i] > highest) {
            highest = y[i];
            mode = x[i];
        }
    }
    return mode;
}

double Statistic::findMean()
{
    double sum = 0;
    for (int i = 0; i < total; i++) {
        sum += y[i];
    }
    return (sum / total);
}

