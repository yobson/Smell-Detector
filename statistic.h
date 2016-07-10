#ifndef STATISTIC_H
#define STATISTIC_H

#include <QDialog>
#include <QtCore>

namespace Ui {
class Statistic;
}

class Statistic : public QDialog
{
    Q_OBJECT

public:
    explicit Statistic(QWidget *parent = 0);
    ~Statistic();

    void getStats(QVector<double> xData, QVector<double> yData, int numberOfDataPoints, bool discrete = false);

private:
    Ui::Statistic *ui;
    QVector<double> x;
    QVector<double> y;
    int total;
    bool dis;

    double findMode();
    double findMean();
};

#endif // STATISTIC_H
