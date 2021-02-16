#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), dialogAddDetail(nullptr), dialogAddBar(nullptr), sliceThickness(0), fileName(""),  cuttingStockBarr(), cuttingSupplierBarr()
{
    ui->setupUi(this);
    ui->TableCutting->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(ui->actionInformation, &QAction::triggered, this, &MainWindow::information);
    connect(ui->actionSaveAsExcel, &QAction::triggered, this, &MainWindow::saveFileAsExcel);
    connect(ui->clearResult, &QAction::triggered, this, &MainWindow::clearResult);
    //connect(ui->calculationButton, clicked(), this, &MainWindow::on_calculationButton_clicked);


}

MainWindow::~MainWindow()
{
    //clearResult();
    qDebug() << "MainWindow destr";
    if(ui != nullptr)
        delete ui;

}

void MainWindow::on_AddDetail_clicked()
{
    //если создана форма,не нужно ее создавать
    if(dialogAddDetail == nullptr)
    {
        dialogAddDetail = new DialogAddDetail(this);
        dialogAddDetail->show();
    }
    else
        dialogAddDetail->show();

    //здесь будет сигнал для отображения файлов, деталей и т.д.
}

void MainWindow::on_barInStock_clicked()
{
    if(dialogAddBar == nullptr)
    {
        dialogAddBar = new DialogAddBar(this);
        dialogAddBar->show();
    }
    else
        dialogAddBar->show();
}

void MainWindow::on_calculationButton_clicked()
{


    if(dialogAddDetail == nullptr || dialogAddBar == nullptr)
    {
     QMessageBox::information(0, "Предупреждение", "Заполните необходимые данные для расчета!");
    }
    else
    {
        QVector<Detail> copyAdapterDetail;
        copyDetails(dialogAddDetail->copyAdapterDetail(), copyAdapterDetail, sliceThickness);
        Barr copyAdapterBarr(dialogAddBar->copyAdapterBarr());
        cuttingStockBarr = new Result_st(copyAdapterBarr.size_st());
        cuttingSupplierBarr = new Result_st(copyAdapterBarr.size_sup());

        if(dialogAddBar->getDiameterOfBarr() <= 200)
            sliceThickness = 2;
        else
            sliceThickness = 4;

        if(!dialogAddBar->empty_st())
        {

                gredyAlgorithm(copyAdapterDetail, copyAdapterBarr, sliceThickness, cuttingStockBarr, true);

            if(!(dialogAddBar->empty_sup()) && !cuttingStockBarr->uncutDetails.isEmpty())
            {

               gredyAlgorithmSupplier(cuttingStockBarr->uncutDetails, copyAdapterBarr, sliceThickness ,cuttingSupplierBarr, false);

            }

        }
        else if(!dialogAddBar->empty_sup()) //только то, что есть у поставщиков
        {
            gredyAlgorithmSupplier(copyAdapterDetail, copyAdapterBarr, sliceThickness, cuttingSupplierBarr, true);

        }
       DataOutputToTable(ui->TableCutting, cuttingStockBarr, cuttingSupplierBarr);

        //сохранить результаты в формате Excel








    }



}

void MainWindow::saveFileAsExcel()
{

    if(cuttingStockBarr == nullptr && cuttingStockBarr == nullptr)
    {
        QMessageBox::information(0, "Предупреждение", "Расчет не произведен!");
        return;
    }
    else
    {
        fileName = QFileDialog::getOpenFileName(0, "Выберите файл для записи");
        //QFileInfo* file = new QFileInfo(fileName); //Как он уничтожается??? предка то нет
        ui->statusbar->showMessage(fileName);
        saveCulculationInExcel();
    }
}

void MainWindow::information()
{
    //qDebug() << "Enter Information";
}

void MainWindow::saveCulculationInExcel()
{

    QAxObject *excel = new QAxObject("Excel.Application",this);
    excel->dynamicCall("SetVisible(bool)", false);

    QAxObject *workbooks = excel->querySubObject("Workbooks");

    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", fileName);

    QAxObject* sheets = workbook->querySubObject("Worksheets");
    //открываем первую страницу
    QAxObject* sheet = sheets->querySubObject("Item( int )", 1);
    //QAxObject* rows = sheet->querySubObject("Rows");
    //QAxObject* columns = sheet->querySubObject("Columns");

    //Задание рабочей области
    int columns_counter = 1;
    int rows_counter = 1;

    //Объединить ячейки
    QAxObject* range = sheet->querySubObject("Range(const QVariant&)", QVariant(QString("A1:D1")));
    range->dynamicCall("Select()");//выделяем
    range->dynamicCall("MergeCells", true);//объединяем
    //Заголовок таблицы
    QAxObject* cell = sheet->querySubObject("Cells( int, int )", rows_counter, columns_counter); //1 - строка, 2 - стобец
    cell->dynamicCall("SetValue(const QVariant&)", "Расчет заготовок");
    rows_counter++;
    //Выравнивание по центру
    QAxObject* centr = sheet->querySubObject("Range(const QVariant&)", QVariant(QString("A1:E1")));
    centr->dynamicCall("Select()");
    centr->dynamicCall("HorizontalAlignment", -4108);

    if(cuttingStockBarr != nullptr)
    {
        rows_counter = fullExcelRows(sheet, "Расчет складских заготовок", rows_counter, cuttingStockBarr);

    }
    if(cuttingSupplierBarr != nullptr)
    {
        rows_counter = fullExcelRows(sheet, "Расчет поставляемых заготовок", rows_counter, cuttingSupplierBarr);
    }



    workbook->dynamicCall("Save()");
    workbooks->dynamicCall("Close");
    excel->dynamicCall("Quit()");

    //delete centr; delete cell; delete range; delete sheet; delete sheets;delete workbook;delete workbook; delete workbooks; delete excel;
    delete workbook; delete workbooks; delete excel;
}

int MainWindow::fullExcelRows(QAxObject *sheet, QString title, int rowCounter, Result_st* result)
{

    //Заголовок

    QAxObject* tit = sheet->querySubObject("Cells( int, int )", rowCounter, 1); //1 - строка, 2 - стобец
    tit->dynamicCall("SetValue(const QVariant&)", title);
    QAxObject* interior = tit->querySubObject("Interior");
    interior->setProperty("Color", QColor("lightblue"));

    QAxObject* titleColumnsLenght = sheet->querySubObject("Cells( int, int )", rowCounter, 2);
    titleColumnsLenght->dynamicCall("SetValue( const QVariant& )", "Длина, мм");
    delete interior;
    interior = titleColumnsLenght->querySubObject("Interior");
    interior->setProperty("Color", QColor("lightblue"));

    QAxObject* titleColumnsSurplus = sheet->querySubObject("Cells( int, int )", rowCounter, 3);
    titleColumnsSurplus->dynamicCall("SetValue( const QVariant& )", "Остаток, мм");
    delete interior;
    interior = titleColumnsSurplus->querySubObject("Interior");
    interior->setProperty("Color", QColor("lightblue"));
    rowCounter++;

    for(int i = 0; i < result->lenghtBarr.size(); ++i)
    {
        if(!result->cuttingResult[i].empty())
        {
            rowCounter++;
            QAxObject* titleBarr = sheet->querySubObject("Cells( int, int )", rowCounter, 1);
            titleBarr->dynamicCall("SetValue(const QVariant& )", "Заготовка");

            delete interior;
            interior = titleBarr->querySubObject("Interior");
            interior->setProperty("Color", QColor("darkcyan"));

            QAxObject* barr = sheet->querySubObject("Cells(int, int)", rowCounter, 2);
            barr->dynamicCall("SetValue(const QVariant& )", QString::number(result->lenghtBarr[i])); //длина заготовки

            delete interior;
            interior = barr->querySubObject("Interior");
            interior->setProperty("Color", QColor("darkcyan"));

            QAxObject* sur = sheet->querySubObject("Cells(int, int)", rowCounter, 3);
            sur->dynamicCall("SetValue(const QVariant& )", QString::number(result->surplus[i])); //остаток заготовки

            delete interior;
            interior = sur->querySubObject("Interior");
            interior->setProperty("Color", QColor("darkcyan"));

            rowCounter++;

                for(auto j : result->cuttingResult[i])
                {
                    QAxObject* detail = sheet->querySubObject("Cells(int, int)", rowCounter, 1);
                    detail->dynamicCall("SetValue(const QVariant& )", j.getDesignationName());
                    QAxObject* lenghtDetail = sheet->querySubObject("Cells(int, int)", rowCounter, 2);
                    lenghtDetail->dynamicCall("SetValue(const QVariant&)", QString::number(j.getLenght()));
                    rowCounter++;

                    //delete detail; delete lenghtDetail;
                }
            //delete titleBarr;delete barr;delete sur;
        }

    }

    if(!cuttingStockBarr->uncutDetails.empty())
    {
        rowCounter++;
        QAxObject* uncut = sheet->querySubObject("Cells( int, int )", rowCounter, 1);
        uncut->dynamicCall("SetValue(const QVariant& )", "Нераскроенные детали");
        delete interior;
        interior = uncut->querySubObject("Interior");
        interior->setProperty("Color", QColor("lightgray"));
        rowCounter++;
        for(auto i : result->uncutDetails)
        {
            QAxObject* detail = sheet->querySubObject("Cells(int, int)", rowCounter, 1);
            detail->dynamicCall("SetValue(const QVariant& )", i.getDesignationName());
            QAxObject* lenghtDetail = sheet->querySubObject("Cells(int, int)", rowCounter, 2);
            lenghtDetail->dynamicCall("SetValue(const QVariant&)", QString::number(i.getLenght()));
            rowCounter++;

            //delete detail; delete lenghtDetail;
        }
        //delete uncut;
    }
    //delete interior; delete tit; delete titleColumnsLenght; delete titleColumnsSurplus;
    return rowCounter;
}


void MainWindow::clearResult()
{

    if(dialogAddBar != nullptr)
    {
        dialogAddBar->clear_st();
        dialogAddBar->clear_sup();
    }

    if (dialogAddDetail != nullptr)
    {
        dialogAddDetail->clear();
    }
    fileName = "";
    if(cuttingStockBarr != nullptr)
        delete cuttingStockBarr;
    if(cuttingSupplierBarr != nullptr)
        delete cuttingSupplierBarr;


    ui->TableCutting->clearContents();


}


void MainWindow::on_actioncreateGraphic_triggered()
{
    if(cuttingStockBarr == nullptr || cuttingSupplierBarr == nullptr)
    {
     QMessageBox::information(0, "Предупреждение", "Расчет не был произведен");
    }
    else
    {
        createGraphic = new graphic(this);
        createGraphic->create(cuttingStockBarr, cuttingSupplierBarr);
        createGraphic->show();


    }
}
