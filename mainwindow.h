#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "class.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_saveButton_clicked();
    void on_compleateButton_clicked();
    void on_saveButton_2_clicked();
    void on_loadButton_clicked();

    void showHideWindow();

private:
    Ui::MainWindow *ui;
    Class **classArray;
    int *timetableClassIndexMap;
    QStringList classList;
    QStringListModel *classListModel;
    QComboBox **boxList;
    int numberOfClasses;
};

#endif // MAINWINDOW_H
