#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QDialog>
#include "qcustomplot.h"
#include "cut.h"
namespace Ui {
class graphic;
}

class graphic : public QDialog
{
    Q_OBJECT

public:
    explicit graphic(QWidget *parent = nullptr);
    ~graphic();

public:
    Ui::graphic *ui;
    QCPBars *stock;
    QCPBars *supplier;
public:
    void create(Result_st *result_stock, Result_st* result_supplier);

};

#endif // GRAPHIC_H
