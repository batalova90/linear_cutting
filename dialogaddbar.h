#ifndef DIALOGADDBAR_H
#define DIALOGADDBAR_H

#include <QDialog>
#include <QString>
#include "barr.h"
namespace Ui {
class DialogAddBar;
}

class DialogAddBar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddBar(QWidget *parent = nullptr);
    ~DialogAddBar();
    bool CheckCost();
    void sort_st();
    bool empty_st();
    bool empty_sup();
    int getDiameterOfBarr();
    const Barr& copyAdapterBarr() const;
    void clear_st(){barr->arrayStockBarr.clear();}
    void clear_sup(){barr->arraySupplierBarr.clear();}
private slots:
    void on_addFileBar_st_clicked();

    void on_addBar_stManually_clicked();

    void on_addFileBarr_sup_clicked();

    void on_addBar_supManually_clicked();

    void on_pcmDir_stock_clicked();

    void on_pcmDir_supplier_clicked();

    void on_addBarInStock_clicked();

    void on_addLenght_st_valueChanged(double arg1);

    void on_amountOfBar_st_valueChanged(int arg1);

    void on_addBarAtSupplier_clicked();

    void on_addLenght_sup_valueChanged(double arg1);

    void on_amountOfBar_sup_valueChanged(int arg1);

    void on_diameterLess200_clicked();

    void on_diameterMore200_clicked();

private:
    Ui::DialogAddBar *ui;
    QString filepath_st;
    QString filepath_sup;
    double lenght_st;
    double lenght_sup;
    int amountOfbar_st;
    int amountOfbar_sup;
    double costOfbar_sup;
    Barr* barr;

    void getParameter(QWidget* button);
    bool CheckValue(double lenght, int amount);

    void lightOn(QWidget* changeLightBorder);
    void lightOnWidget(QWidget* button);
    void lightOff(QWidget* spinBox);

    void AddBarrManually(bool typeOfBar);
    void ReadExcelFile(bool typeOfBar);

    void DeleteAddedBar(bool typeOfBar, int counter);
};

#endif // DIALOGADDBAR_H
