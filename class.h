#ifndef CLASS_H
#define CLASS_H

#include <QObject>
#include <QtCore>

class Class : public QObject
{
    Q_OBJECT
public:
    explicit Class(QObject *parent = 0);
    void setName(QString name);
    void setBoys(int boys);
    void setGirls(int girls);
    void setYear(int year);

    QString name();
    int boys();
    int girls();
    int year();

private:
    QString NAME;
    int BOYS;
    int GIRLS;
    int YEAR;

signals:

public slots:
};

#endif // CLASS_H
