#ifndef DIALOGADDDETAIL_H
#define DIALOGADDDETAIL_H
#pragma once
#include <QDialog>
#include <QRadioButton>
#include <QVector>
#include "detail.h"
#include <QAxObject>
#include <QMessageBox>

//#include "WorkWithAddedDetails.cpp"

namespace Ui {
class DialogAddDetail;
}

class DialogAddDetail : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddDetail(QWidget *parent = nullptr);
    ~DialogAddDetail();
    //friend class MainWindow;
     const QVector<Detail>& copyAdapterDetail() const;
     void clear() {adapterDetails.clear();}
private slots:
    void on_addDetailManually_clicked();

    void on_addFile_clicked();

    void on_pcmDir_clicked();

    void on_addDetailsButton_clicked();

    void on_designationDetail_textEdited(const QString &arg1);

    void on_amountOfDetail_valueChanged(int arg1);

    void on_lenghtDetail_valueChanged(double arg1);

private:
    Ui::DialogAddDetail *ui;
    QString filePath;
    QString designationDetail;
    QString nameDetail;
    double lenghtDetail;
    int amountOfDetail;
    QVector<Detail> adapterDetails; //?????????????выносить надо в отдельный класс
    //QAxObject* excel;
    //Methods
    bool checkLines();
    void getQStrings();
    void lightOnWidget();
    void lightOn(QWidget* changeLightBorder);

    //Method for work with added details
    void AddDetailManually();
    //bool AddDetailFromFile();
    void ReadExcelFile();
    void DeleteAddedDetails(int counter);
    void CheckArrayDetails();


};




#endif // DIALOGADDDETAIL_H
