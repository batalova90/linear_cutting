#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include "dialogadddetail.h"
#include "dialogaddbar.h"
#include "graphic.h"
#include "detail.h"
#include <QVector>
#include "cut.h"
#include "Profile.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QAxObject>
#include <QAxWidget>
#include <QApplication>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_AddDetail_clicked();

    void on_barInStock_clicked();

    void on_calculationButton_clicked();

    void saveFileAsExcel();

    void information();

    void clearResult();



    void on_actioncreateGraphic_triggered();

private:
    Ui::MainWindow *ui;

    DialogAddDetail* dialogAddDetail;
    DialogAddBar* dialogAddBar;
    graphic* createGraphic;
    int sliceThickness;
    QString fileName;
    Result_st* cuttingStockBarr;
    Result_st* cuttingSupplierBarr;
    void saveCulculationInExcel();
    int fullExcelRows(QAxObject* sheet, QString title, int rowCounter, Result_st* result);
    //void saveFile();


};
#endif // MAINWINDOW_H
