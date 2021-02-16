#include "dialogaddbar.h"
#include "ui_dialogaddbar.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QAxObject>
DialogAddBar::DialogAddBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddBar), filepath_st(""), filepath_sup(""), lenght_st(0), lenght_sup(0), amountOfbar_st(0), amountOfbar_sup(0),costOfbar_sup(0),
                                barr(nullptr)
{
    ui->setupUi(this);
    //stock
    ui->pcmDir_stock->setEnabled(false);
    ui->textDir_stock->setEnabled(false);
    //supplier
    ui->pcmDir_supplier->setEnabled(false);
    ui->textDir_supplier->setEnabled(false);
    qDebug() << "Dialog add bar constructor";

}

DialogAddBar::~DialogAddBar()
{
    qDebug() << "Dialog add bar destructor";
    if(barr != nullptr)
        delete barr;
    if(ui != nullptr)
        delete ui;
}

void DialogAddBar::on_addFileBar_st_clicked()
{
    ui->pcmDir_stock->setEnabled(true);
    ui->textDir_stock->setEnabled(true);

    ui->amountOfBar_st->setEnabled(false);
    ui->addLenght_st->setEnabled(false);
}

void DialogAddBar::on_addBar_stManually_clicked()
{
    ui->amountOfBar_st->setEnabled(true);
    ui->addLenght_st->setEnabled(true);

    ui->pcmDir_stock->setEnabled(false);
    ui->textDir_stock->setEnabled(false);

}

void DialogAddBar::on_addFileBarr_sup_clicked()
{
    ui->pcmDir_supplier->setEnabled(true);
    ui->textDir_supplier->setEnabled(true);

    ui->amountOfBar_sup->setEnabled(false);
    ui->addLenght_sup->setEnabled(false);
    ui->costOfBar_sup->setEnabled(false);
}

void DialogAddBar::on_addBar_supManually_clicked()
{
    ui->amountOfBar_sup->setEnabled(true);
    ui->addLenght_sup->setEnabled(true);
    ui->costOfBar_sup->setEnabled(true);

    ui->pcmDir_supplier->setEnabled(false);
    ui->textDir_supplier->setEnabled(false);

}

void DialogAddBar::on_pcmDir_stock_clicked()
{
    filepath_st = QFileDialog::getOpenFileName(0, "Select Directory", ui->textDir_stock->text());
     QFileInfo* file_st = new QFileInfo(filepath_st); //Как он уничтожается??? предка то нет
   if ( !filepath_st.isEmpty()) {
       ui->textDir_stock->setText(file_st->baseName());
    }
    delete file_st;
}

void DialogAddBar::on_pcmDir_supplier_clicked()
{
    filepath_sup = QFileDialog::getOpenFileName(0, "Select Directory", ui->textDir_supplier->text());
     QFileInfo* file_sup = new QFileInfo(filepath_sup); //Как он уничтожается??? предка то нет
   if ( !filepath_sup.isEmpty()) {
       ui->textDir_supplier->setText(file_sup->baseName());
    }
    delete file_sup;
}


void DialogAddBar::on_addBarInStock_clicked()
{
    if(ui->addBar_stManually->isChecked())
    {
        getParameter(ui->addBarInStock);
        qDebug() << lenght_st << "\t" << amountOfbar_st;
        //Проверяем, чтобы все поля были заполнены
        if(CheckValue(lenght_st, amountOfbar_st))
        {
           QMessageBox::information(0, "Предупреждение", "Заполните все поля!");
           lightOnWidget(ui->addBarInStock);

        }
        else
        {
            AddBarrManually(true); //реализовать с передачей параметров
        }
    }
    else if(ui->addFileBar_st->isChecked())
    {
        if(!filepath_st.isEmpty())
        {
            ReadExcelFile(true); //реализовать с передачей параметров
        }
        else
        {
            QMessageBox::information(0, "Предупреждение", "Выберите файл");
         }
    }
    qDebug() << "Stock";
    if(barr != nullptr)
        barr->print_st();

}

 void DialogAddBar::getParameter(QWidget* button)
 {
     if(button == ui->addBarInStock)
     {
         lenght_st = ui->addLenght_st->value();
         amountOfbar_st = ui->amountOfBar_st->value();
     }
     else /*if(button == ui->addBarAtSupplier)*/
     {
         lenght_sup = ui->addLenght_sup->value();
         amountOfbar_sup = ui->amountOfBar_sup->value();
         costOfbar_sup = ui->costOfBar_sup->text().toDouble();
     }
 }

 bool DialogAddBar::CheckValue(double lenght, int amount)
 {
     return ((lenght == 0) || (amount == 0));
 }

 bool DialogAddBar::CheckCost()
 {
     return costOfbar_sup == 0;
 }

 void DialogAddBar::lightOnWidget(QWidget* button)
 {
     if(button == ui->addBarInStock)
     {
         if(lenght_st == 0)
             lightOn(ui->addLenght_st);
         if(amountOfbar_st == 0)
             lightOn(ui->amountOfBar_st);
     }
     else if(button == ui->addBarAtSupplier)
     {
         if(lenght_sup == 0)
             lightOn(ui->addLenght_sup);
         if(amountOfbar_sup == 0)
             lightOn(ui->amountOfBar_sup);
     }

 }

 void DialogAddBar::lightOn(QWidget* changeLightBorder)
 {
     changeLightBorder->setStyleSheet("border: 1px solid red");
 }

void DialogAddBar::on_addLenght_st_valueChanged(double arg1)
{
    lightOff(ui->addLenght_st);
}

void DialogAddBar::lightOff(QWidget* spinBox)
{
    spinBox->setStyleSheet("border: 1px solid black");
}

void DialogAddBar::on_amountOfBar_st_valueChanged(int arg1)
{
    lightOff(ui->amountOfBar_st);
}

void DialogAddBar::on_addBarAtSupplier_clicked()
{
    if(ui->addBar_supManually->isChecked())
    {

        getParameter(ui->addBarAtSupplier); //реализовать
        qDebug() << lenght_sup << "\t" << amountOfbar_sup;
        //Проверяем, чтобы все поля были заполнены
        if(CheckValue(lenght_sup, amountOfbar_sup))
        {
           QMessageBox::information(0, "Предупреждение", "Заполните все поля!");
           lightOnWidget(ui->addBarAtSupplier);
            }
        else
        {
            AddBarrManually(false);
        }
    }
    else if(ui->addFileBarr_sup->isChecked())
    {
        if(!filepath_sup.isEmpty())
        {
            ReadExcelFile(false);
        }
        else
        {
            QMessageBox::information(0, "Предупреждение", "Выберите файл");
         }
    }
    qDebug() << "supplier";
    if(barr != nullptr)
        barr->print_sup();
}

void DialogAddBar::on_addLenght_sup_valueChanged(double arg1)
{
    lightOff(ui->addLenght_sup);
}

void DialogAddBar::on_amountOfBar_sup_valueChanged(int arg1)
{
     lightOff(ui->amountOfBar_sup);
}

void DialogAddBar::AddBarrManually(bool typeOfBar)
{
    if (typeOfBar) //in stock
      {
        if (barr == nullptr)
        {
             barr = new Barr();
             barr->push_back_st(lenght_st, amountOfbar_st);
        }
       else
        {
             barr->push_back_st(lenght_st, amountOfbar_st);
        }

    }
    else
    { //supplier
        if (barr == nullptr)
        {
             barr = new Barr();
             barr->push_back_sup(lenght_sup, amountOfbar_sup, costOfbar_sup);
        }

        else
        {
             barr->push_back_sup(lenght_sup, amountOfbar_sup, costOfbar_sup);
        }

    }
}


void DialogAddBar::ReadExcelFile( bool typeOfBar)
{
    QAxObject* excel = new QAxObject("Excel.Application", this);
    excel->dynamicCall("SetVisible(bool)", false);
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook;
    if(typeOfBar)
        workbook = workbooks->querySubObject("Open(QString)", filepath_st);
    else
        workbook = workbooks->querySubObject("Open(QString)", filepath_sup);

    QAxObject* worksheet = workbook->querySubObject("WorkSheets(int)", 1);
    //кол-во используемых строк и столбцов
    QAxObject* usedrange = worksheet->querySubObject("UsedRange");
    QAxObject* rows = usedrange->querySubObject("Rows");
    QAxObject* columns = usedrange->querySubObject("Columns");

    int intRows = rows->property("Count").toInt();
    int intCols = columns->property("Count").toInt();
    int RowStart = usedrange->property("Row").toInt();
    int ColsStart = usedrange->property("Column").toInt();

    int counterRow = 0;
    int counterRowSup = 0;
    //Рисуем таблицу, в которой можно просматривать, что прочиталось из файла
    //tableWidget->setColumnCount(ColsStart + intCols);
    //tableWidget->setRowCount(RowStart + intRows);

    //необходимо проверять на правильность сформированного файла для чтения!!
    if(typeOfBar)
    {
        for(int row = 1; row < intRows; ++row)
        {
            for(int cols = 0; cols < intCols; cols = cols + 4)
            {
                QAxObject* celllenght_st= worksheet->querySubObject("Cells(int, int)", row + 1, cols + 1);
                QAxObject* cellamountOfbar_st = worksheet->querySubObject("Cells(int, int)", row + 1, cols + 2);
                QVariant valuelenght_st = celllenght_st->dynamicCall("Value()");
                QVariant valueamountOfbar_st = cellamountOfbar_st->dynamicCall("Value()");

                lenght_st = valuelenght_st.toDouble();
                amountOfbar_st = valueamountOfbar_st.toInt();

                //qDebug() << "Длина заготовки: "<<  lenght_st << " кол-во заготовки: " << amountOfbar_st;

                if(CheckValue(lenght_st, amountOfbar_st))
                {
                   QString str("");
                   str = "В строке " + QVariant(row + 1).toString() + " неправильно заполнены данные! ";
                   QMessageBox::information(0, "Предупреждение", str);
                   qDebug() << "Before delete data";
                   if(counterRow != 0)
                        DeleteAddedBar(typeOfBar, counterRow); //реализовать
                   workbook->dynamicCall("Close");
                   excel->dynamicCall("Quit()");
                   delete excel;

                   ui->textDir_stock->clear();
                   counterRow = 0;
                   qDebug() << "Delete data file";
                   return;

                }
                else
                {
                    AddBarrManually(true); //добавляем полученные данные в массив
                    //CheckArrayDetails();
                    ++counterRow;
                }

            }

        }


    }
    else
    {
        for(int row = 1; row < intRows; ++row)
        {
            for(int cols = 0; cols < intCols; cols = cols + 4)
            {
                QAxObject* celllenght_sup= worksheet->querySubObject("Cells(int, int)", row + 1, cols + 1);
                QAxObject* cellamountOfbar_sup = worksheet->querySubObject("Cells(int, int)", row + 1, cols + 2);
                QAxObject* cellcost_sup = worksheet->querySubObject("Cells(int, int)", row + 1, cols + 3);
                QVariant valuelenght_sup = celllenght_sup->dynamicCall("Value()");
                QVariant valueamountOfbar_sup = cellamountOfbar_sup->dynamicCall("Value()");
                QVariant valuecost_sup = cellcost_sup->dynamicCall("Value()");
                lenght_sup = valuelenght_sup.toDouble();
                amountOfbar_sup = valueamountOfbar_sup.toInt();
                costOfbar_sup = valuecost_sup.toDouble();

                qDebug() << "Длина заготовки: "<<  lenght_sup << " кол-во заготовки: " << amountOfbar_sup;

                if(CheckValue(lenght_sup, amountOfbar_sup))
                {
                   QString str("");
                   str = "В строке " + QVariant(row + 1).toString() + " неправильно заполнены данные! ";
                   QMessageBox::information(0, "Предупреждение", str);
                   qDebug() << "Before delete data";
                   if(counterRowSup != 0)
                        DeleteAddedBar(typeOfBar, counterRowSup); //реализовать
                   workbook->dynamicCall("Close");
                   excel->dynamicCall("Quit()");
                   delete excel;

                   ui->textDir_supplier->clear();
                   counterRowSup = 0;


                   //qDebug() << "Delete data file";
                   return;

                }
                else
                {
                    AddBarrManually(false); //добавляем полученные данные в массив
                    //CheckArrayDetails();
                    ++counterRowSup;
                }


            }

        }

    }
    workbook->dynamicCall("Close");
    excel->dynamicCall("Quit()");

    delete excel;

 }

void DialogAddBar::DeleteAddedBar(bool typeOfBar, int counter)
{
    if(typeOfBar)
    {
        if(counter == barr->size_st())
            barr->clear_st();
        else
            barr->erase_st(counter);
    }
    else
    {
        if(counter == barr->size_sup())
            barr->clear_sup();
        else
            barr->erase_sup(counter);
    }

}

bool DialogAddBar::empty_st()
{
    return barr->empty_st();
}

bool DialogAddBar::empty_sup()
{
    return barr->empty_sup();
}

void DialogAddBar::on_diameterLess200_clicked()
{
    barr->setDiameterOfBarr(200);
}

void DialogAddBar::on_diameterMore200_clicked()
{
    barr->setDiameterOfBarr(201);
}

int DialogAddBar::getDiameterOfBarr()
{
   return barr->getDiameterOfBarr();
}

const Barr& DialogAddBar::copyAdapterBarr() const
{
    return *barr;
}
