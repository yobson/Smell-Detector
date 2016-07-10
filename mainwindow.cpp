#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include "loggingwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#    Initial Setup    #";
    qDebug() << "#######################";
    qDebug() << " ";
    ui->setupUi(this);
    classArray = new Class*[255];
    timetableClassIndexMap = new int[255];
    boxList = new QComboBox*[255];
    classListModel = new QStringListModel(this);
    numberOfClasses = 0;

    qDebug() << "Populating timetable grid with QComboBoxes";
    int tracker = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            QComboBox *box = new QComboBox(this);
            box->setModel(classListModel);
            boxList[tracker] = box;
            ui->weekOneTable->setCellWidget(j, i, boxList[tracker]);
            tracker++;
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            QComboBox *box = new QComboBox(this);
            box->setModel(classListModel);
            boxList[tracker] = box;
            ui->weekTwoTable->setCellWidget(j, i, boxList[tracker]);
            tracker++;
        }
    }
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "# Finished Setting up #";
    qDebug() << "#######################";
    qDebug() << " ";
}

MainWindow::~MainWindow()
{
    qDebug() << "Deleting dynamic content of classArray and boxList";
    for (int i = 0; i < 255; i++) {

        delete boxList[i];
    }
    for (int i = 0; i < numberOfClasses; i++) {
        delete classArray[i];
    }
    qDebug() << "Deleting all arrays";
    delete[] classArray;
    delete[] boxList;
    delete[] timetableClassIndexMap;

    qDebug() << "Deleting All of MainWindow";
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    ui->classTable->setRowCount(ui->classTable->rowCount()+1);
}

void MainWindow::on_deleteButton_clicked()
{
    ui->classTable->removeRow(ui->classTable->rowCount()-1);
}

void MainWindow::on_saveButton_clicked()
{
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "# Updating Class List #";
    qDebug() << "#######################";
    qDebug() << " ";
    qDebug() << "Deleteing old class array";

    for (int i = 0; i < numberOfClasses; i++) {
        delete classArray[i];
    }
    numberOfClasses = 0;
    qDebug() << "Clearing QComboBox Content List";
    classList.clear();


    qDebug() << "Making Class objects for each row";
    for (int i = 0; i < ui->classTable->rowCount(); i++) {
        classList << ui->classTable->item(i, 0)->text();

        Class *item = new Class(this);
        item->setName(ui->classTable->item(i, 0)->text());
        item->setYear(ui->classTable->item(i, 1)->text().toInt());
        item->setBoys(ui->classTable->item(i, 2)->text().toInt());
        item->setGirls(ui->classTable->item(i, 3)->text().toInt());
        classArray[i] = item;

        numberOfClasses ++;

    }
    classList << "";
    qDebug() << "Updating QStringModel";
    classListModel->setStringList(classList);
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#    Done Updating    #";
    qDebug() << "#######################";
    qDebug() << " ";
}

void MainWindow::on_compleateButton_clicked()
{
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#Setting up Log Window#";
    qDebug() << "#######################";
    qDebug() << " ";
    qDebug() << "Mapping Timetable Data to Classes";
    for (int i = 0; i < 70; i++){
        if (boxList[i]->currentIndex() == numberOfClasses) {
            timetableClassIndexMap[i] = -1;
        } else {
            timetableClassIndexMap[i] = boxList[i]->currentIndex();
        }
    }
    qDebug() << "Instantiating new LoggingWindow and passing data";
    LoggingWindow *logWindow = new LoggingWindow(this);
    logWindow->setClassArray(classArray);
    logWindow->setTimetableIndex(timetableClassIndexMap);
    qDebug() << "Connecting signals and slots";
    connect(logWindow, SIGNAL(showHideWindow()), this, SLOT(showHideWindow()));
    qDebug() << "Showing Window";
    logWindow->show();

    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#Done Log Window Setup#";
    qDebug() << "#######################";
    qDebug() << " ";
}

void MainWindow::on_saveButton_2_clicked()
{
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#    Saving Config    #";
    qDebug() << "#######################";
    qDebug() << " ";
    qDebug() << "Opeing Save Class Dialog Box";
    QString saveClassLocation = QFileDialog::getSaveFileName(
                this,
                tr("Save Class File"),
                QDir::currentPath(),
                tr("Class File (*.class)") );

    if (saveClassLocation != "") {
        qDebug() << "Updating the Class List";
        this->on_saveButton_clicked();
        QFile classFile(saveClassLocation);
        qDebug() << "Trying to open " << saveClassLocation << " file in write-only text mode";
        if (classFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream classInfo(&classFile);
            QString name;
            int year, boys, girls;

            qDebug() << "Moving the content into the file";

            for (int i = 0; i < numberOfClasses; i++) {
                name = classArray[i]->name();
                year = classArray[i]->year();
                boys = classArray[i]->boys();
                girls = classArray[i]->girls();

                classInfo << name << ", "  << year << ", " << boys << ", " << girls << "\n";
            }

            qDebug() << "Closing " << saveClassLocation << " file";
            classFile.flush();
            classFile.close();
        } else { qDebug() << "ERROR - couldn't open " << saveClassLocation << " file in write-only text mode!!!"; }
    }

    qDebug() << "Opening Save Timetable Dialog";
    QString saveTimetableLocation = QFileDialog::getSaveFileName(
                this,
                tr("Save Timetable File"),
                QDir::currentPath(),
                tr("Timetable File (*.timetable)") );

    if (saveTimetableLocation != "") {
        QFile timetableFile(saveTimetableLocation);
        qDebug() << "Trying to open " << saveTimetableLocation << " file in write-only text mode";
        if (timetableFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream timetableData(&timetableFile);

            qDebug() << "Saving timetable into timetableClassMap[]";
            for (int i = 0; i < 70; i++){
                timetableClassIndexMap[i] = boxList[i]->currentIndex();
            }

            qDebug() << "Transfering timetableClassMap[] into file";
            for (int i = 0; i < 70; i++) {
                timetableData << timetableClassIndexMap[i] << "\n";
            }

            qDebug() << "Closing " << saveTimetableLocation << " file";
            timetableFile.flush();
            timetableFile.close();
        } else { qDebug() << "ERROR - couldn't open " << saveTimetableLocation << " file in write-only text mode!!!"; }
    }
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#    Configs Saved    #";
    qDebug() << "#######################";
    qDebug() << " ";
}

void MainWindow::on_loadButton_clicked()
{
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#  Load Config Files  #";
    qDebug() << "#######################";
    qDebug() << " ";
    qDebug() << "Opeing Open Class File Dialog";
    QString openClassLocation = QFileDialog::getOpenFileName(
                this,
                tr("Open Class File"),
                QDir::currentPath(),
                tr("Class File (*.class)") );

    if (openClassLocation != "") {
        QFile classFile(openClassLocation);
        QTextStream classData(&classFile);

        qDebug() << "Trying to open " << openClassLocation << " file in read-only text mode";
        if (classFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Clearing class table";
            ui->classTable->setRowCount(0);

            qDebug() << "Reading " << openClassLocation << "into table line by line";
            while (!classData.atEnd()) {
                QString line = classData.readLine();
                QStringList splitLine = line.split(", ");
                ui->classTable->setRowCount(ui->classTable->rowCount()+1);

                QTableWidgetItem *name = new QTableWidgetItem();
                QTableWidgetItem *year = new QTableWidgetItem();
                QTableWidgetItem *boys = new QTableWidgetItem();
                QTableWidgetItem *girls = new QTableWidgetItem();

                name->setText(splitLine.value(0));
                year->setText(splitLine.value(1));
                boys->setText(splitLine.value(2));
                girls->setText(splitLine.value(3));

                ui->classTable->setItem(ui->classTable->rowCount()-1, 0, name);
                ui->classTable->setItem(ui->classTable->rowCount()-1, 1, year);
                ui->classTable->setItem(ui->classTable->rowCount()-1, 2, boys);
                ui->classTable->setItem(ui->classTable->rowCount()-1, 3, girls);
            }
            qDebug() << "Closing " << openClassLocation << " file";
            classFile.close();
            qDebug() << "Updating the internal class data";
            this->on_saveButton_clicked();
        } else { qDebug() << "ERROR - couldn't open " << openClassLocation << " file in read-only text mode!!!"; }
    }


    qDebug() << "Opening Open Timetable File Dialog";
    QString openTimetableLocation = QFileDialog::getOpenFileName(
                this,
                tr("Open Timetable File"),
                QDir::currentPath(),
                tr("Timetable File (*.timetable)") );
    if (openTimetableLocation != "") {
        QFile timetableFile(openTimetableLocation);
        QTextStream timetableData(&timetableFile);
        int i = 0;

        qDebug() << "Trying to open " << openTimetableLocation << " file in read-only text mode";
        if (timetableFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Loading data into timtable from " << openTimetableLocation << " line by line";
            while (!timetableData.atEnd()) {
                QString line = timetableData.readLine();
                if (line.toInt() > numberOfClasses) {
                        qDebug() << "ERROR - Timetable File doesn't match class list";
                        break;
                }
                boxList[i]->setCurrentIndex(line.toInt());
                i++;
            }
            qDebug() << "Closing " << openTimetableLocation << " file";
            timetableFile.flush();
            timetableFile.close();
        } else { qDebug() << "ERROR - couldn't open " << openTimetableLocation << " file in read-only text mode!!!"; }
    }
    qDebug() << " ";
    qDebug() << "#######################";
    qDebug() << "#    Config Opened    #";
    qDebug() << "#######################";
    qDebug() << " ";
}

void MainWindow::showHideWindow()
{
    this->setVisible(!this->isVisible());
}
