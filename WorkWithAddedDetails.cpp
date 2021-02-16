#include "dialogadddetail.h"
#include "QDebug"
#include "ui_dialogadddetail.h"


void DialogAddDetail::AddDetailManually()
{
    Detail current(designationDetail, nameDetail, lenghtDetail, amountOfDetail);
        adapterDetails.push_back(current);
        /*qDebug() << "Обозначение: "<< designationDetail << " Наименование: " << nameDetail <<
                    " Длина детали: " << lenghtDetail << " кол-во деталей: " << amountOfDetail;*/
}

void DialogAddDetail::ReadExcelFile()
{
    QAxObject* excel = new QAxObject("Excel.Application", this);
    excel->dynamicCall("SetVisible(bool)", false);
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(QString)", filePath);

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

    //Рисуем таблицу, в которой можно просматривать, что прочиталось из файла
    //tableWidget->setColumnCount(ColsStart + intCols);
    //tableWidget->setRowCount(RowStart + intRows);

    //необходимо проверять на правильность сформированного файла для чтения!!
    for(int row = 1; row < intRows; ++row)
    {
        for(int cols = 0; cols < intCols; cols = cols + 4)
        {
            QAxObject* cellDesignation = worksheet->querySubObject("Cells(int, int)", row + 1, cols + 1);
            QAxObject* cellName = worksheet->querySubObject("Cells(int, int)", row + 1, cols + 2);
            QAxObject* cellLenght = worksheet->querySubObject("Cells(int, int)", row + 1, cols + 3);
            QAxObject* cellAmount = worksheet->querySubObject("Cells(int, int)", row + 1, cols + 4);
            QVariant valueDesignaton = cellDesignation->dynamicCall("Value()");
            QVariant valueName = cellName->dynamicCall("Value()");
            QVariant valueLenght = cellLenght->dynamicCall("Value()");
            QVariant valueAmount = cellAmount->dynamicCall("Value()");
            designationDetail = valueDesignaton.toString();
            nameDetail = valueName.toString();
            lenghtDetail = valueLenght.toDouble();
            amountOfDetail = valueAmount.toInt();
            /*qDebug() << "Обозначение: "<< designationDetail << " Наименование: " << nameDetail <<
                        " Длина детали: " << lenghtDetail << " кол-во деталей: " << amountOfDetail;*/

            if(checkLines())
            {
               QString str("");
               str = "В строке " + QVariant(row + 1).toString() + " неправильно заполнены данные! ";
               QMessageBox::information(0, "Предупреждение", str);
               qDebug() << "Before delete data";
               CheckArrayDetails(); //вывод массив для отладки
               if(counterRow != 0)
                    DeleteAddedDetails(counterRow);
               workbook->dynamicCall("Close");
               excel->dynamicCall("Quit()");
               delete excel;
               CheckArrayDetails(); //вывод массив для отладки
               ui->textDir->clear();
               counterRow = 0;
               qDebug() << "Delete data file";
               return;

            }
            else
            {
                AddDetailManually(); //добавляем полученные данные в массив
                //CheckArrayDetails();
                ++counterRow;
            }

        }

    }
    //qDebug() << intRows;
    //qDebug() << intCols;

    workbook->dynamicCall("Close");
    excel->dynamicCall("Quit()");
    delete excel;
    CheckArrayDetails();
}


 void DialogAddDetail::DeleteAddedDetails(int counter)
 {
     if(counter == adapterDetails.size())
         adapterDetails.clear();
     else
         adapterDetails.erase(adapterDetails.end() - counter, adapterDetails.end());


 }

 void DialogAddDetail::CheckArrayDetails()
 {
     for(int i = 0; i < adapterDetails.size(); ++i)
                adapterDetails[i].print();
 }


