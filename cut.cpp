#include "cut.h"
#include <algorithm>
#include "Profile.h"


void copyDetails(const QVector<Detail>& arrayDetails, QVector<Detail>& copyArrayDetails, int sliceThickness)
{
    int amount;
    for(auto i : arrayDetails)
    {
        amount = i.getAmountOfDetail();
        for(int j = 0; j < amount; ++j)
        {
           copyArrayDetails.push_back(i);
           copyArrayDetails[j].setLenghtWithCropping(sliceThickness); //добавляем в массив длину обрезки
        }

    }

}


void lengthOptimizationCalculation(QVector<Detail>& arrayCopyDetail, Barr& arrayCopyBarr, int sliceThickness, Result_st* result_stock)
{
     std::sort(arrayCopyDetail.begin(), arrayCopyDetail.end());
     std::sort(arrayCopyBarr.begin_st(), arrayCopyBarr.end_st(), [](const Barr::Barr_st* a, const Barr::Barr_st* b) ->bool
     {
         return a->lenght < b->lenght;
     });


     QVector<bool> cutDetail(arrayCopyDetail.size(), 1);
     for(int i = 0; i < arrayCopyBarr.size_st(); ++i)
     {
         result_stock->surplus[i] = DynamicProgrammingCut(arrayCopyDetail, sliceThickness, cutDetail, result_stock->cuttingResult[i], arrayCopyBarr.getLenght_st(i)); //еще остаток учесть
         result_stock->lenghtBarr[i] = arrayCopyBarr.getLenght_st(i);
     }
     fullUncutDetail(cutDetail, arrayCopyDetail, result_stock);

}

//перепроверить в отладчике
int DynamicProgrammingCut(const QVector<Detail>& arrayCopyDetail, int sliceThickness,  QVector<bool>& cutDetail, QList<Detail>& cuttingResult, int lenghtBarr)
{
    qDebug() << "45 ";
    int n = arrayCopyDetail.size(); //кол-во деталей
    QVector<QVector<int>> dp(lenghtBarr + 1, QVector<int>(arrayCopyDetail.size()+1, 0));
    QVector<int> detailsAmount(lenghtBarr);
    for (int j = 1; j <= n; ++j)
    {
        for (int w = 1; w <= lenghtBarr; ++w)
        {

            if ((arrayCopyDetail[j-1].getLenght() +  sliceThickness) <= w  && cutDetail[j - 1])
            {
                dp[w][j] = std::max(dp[w][j - 1], dp[w - int(arrayCopyDetail[j - 1].getLenght())][j - 1] + int(arrayCopyDetail[j - 1].getLenght()));
                detailsAmount[w] = j - 1;
            }
            else
            {
                dp[w][j] = dp[w][j - 1];
            }
        }


    }

    return cut(detailsAmount, arrayCopyDetail, lenghtBarr, cuttingResult, cutDetail);


}

int cut(QVector<int>& detailsAmount, const QVector<Detail>& details, int lenght, QList<Detail>& resultList, QVector<bool>& cutPart)
{
    int y = lenght;
    int counterLenght = lenght;
    Detail  k;

    while (detailsAmount[y - 1] > 0)
    {
        if(cutPart[detailsAmount[y - 1] - 1])
        {
            k = details[detailsAmount[y - 1] - 1];
            resultList.push_back(k);
            cutPart[detailsAmount[y - 1] - 1] = 0;
            y = y - int(details[detailsAmount[y - 1] - 1].getLenght());
            counterLenght = counterLenght - k.getLenght();
        }
        else
        {
           y = y - int(details[detailsAmount[y - 1] - 1].getLenght());
        }
    }


    return counterLenght;
}

void fullUncutDetail(const QVector<bool>& cutDetail, const QVector<Detail>& arrayCopyDetail, Result_st* result_stock)
{
    for(int i = 0; i < arrayCopyDetail.size(); ++i)
    {
        if(cutDetail[i])
        {
            result_stock->uncutDetails.push_back(arrayCopyDetail[i]);

        }

    }

}

void lengthOptimizationUncutDetails(Barr& arrayCopyBarr, int sliceThickness, Result_st* result_supplier, const QVector<Detail>& result_stock)
{
    std::sort(arrayCopyBarr.begin_sup(), arrayCopyBarr.end_sup(), [](const Barr::Barr_sup* a, const Barr::Barr_sup* b) ->bool
    {
        return a->lenght < b->lenght;
    });
    //qDebug() << "120";
    QVector<bool> cutDetail(result_stock.size(), 1);
    for(int i = 0; i < arrayCopyBarr.size_sup(); ++i)
    {

            if(checkUncutDetails(cutDetail))
            {
                //qDebug() << "exit " << i << " lenght barr " << arrayCopyBarr.getLenght_sup(i);

                i = arrayCopyBarr.size_sup();

            }
            else
            {


                result_supplier->surplus[i] = DynamicProgrammingCut(result_stock, sliceThickness, cutDetail, result_supplier->cuttingResult[i], arrayCopyBarr.getLenght_sup(i));
                result_supplier->surplus[i] = result_supplier->surplus[i] - (result_supplier->cuttingResult[i].length())*sliceThickness;
                result_supplier->lenghtBarr[i] = arrayCopyBarr.getLenght_sup(i);
                //qDebug() << "Длина бара: " << arrayCopyBarr.getLenght_sup(i);
            }



        //}

    }

    fullUncutDetail(cutDetail, result_stock, result_supplier);

}

bool checkUncutDetails(const QVector<bool>& cutDetail)
{

    for(auto i : cutDetail)
    {
        if(i)
        {
            qDebug() << "162";
            return false;
        }
    }
    qDebug()<<"165";
   return true;


}


void DataOutputToTable(QTableWidget* table, const Result_st* cuttingStockBarr, const Result_st* cuttingSupplierBarr)
{

    table->setColumnCount(4);
    table->insertRow(0);

    QTableWidgetItem* nameColumn = new QTableWidgetItem("Длина заготовки, мм/\nДеталь");
    QFont font;
    font.setBold(true);
    nameColumn->setFont(font);
    table->setItem(0,1,nameColumn);

    QTableWidgetItem* nameColumn2 = new QTableWidgetItem("Остаток, мм/\nДлина детали, мм");

    nameColumn2->setFont(font);
    table->setItem(0,2,nameColumn2);

    int number = 1;
    if(!cuttingStockBarr->cuttingResult.empty())
    {
        number = fullColumn(cuttingStockBarr, number, table);
        number++;
    }


    if(!cuttingSupplierBarr->cuttingResult.empty())
    {
        table->insertRow(number);
        number++;
        table->insertRow(number);
        QTableWidgetItem* suplier = new QTableWidgetItem("Раскрой поставляемых заготовок");

        suplier->setFont(font);
        table->setItem(number,0,suplier);
        number++;
        number = fullColumn(cuttingSupplierBarr, number, table);
    }
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
}

int fullColumn(const Result_st* result, int number, QTableWidget* table)
{
    QFont font;
    font.setBold(true);


        for(int i = 0; i < result->lenghtBarr.size(); ++i)
        {
            if(!result->cuttingResult[i].empty())
            {
                table->insertRow(number);
                number++;
                table->insertRow(number);//( table->rowCount() );
                QTableWidgetItem* barr = new QTableWidgetItem("Заготовка: ");
                QFont font;
                font.setBold(true);
                barr->setFont(font);
                table->setItem(number,0,barr);

                QTableWidgetItem* lenghtBarr = new QTableWidgetItem("Длина: " + QString::number(result->getLenght(i)));
                table->setItem(number,1,lenghtBarr);
                QTableWidgetItem* lenghtSurpuls = new QTableWidgetItem("Остаток: " + QString::number(result->getLenghtSurplus(i)));
                table->setItem(number, 2, lenghtSurpuls);
                //table->resizeColumnsToContents();

                //вставка строки под раскроенные детали
                number++;
                table->insertRow( number);
                QTableWidgetItem* cuttingDetail = new QTableWidgetItem("Раскроенные детали: ");
                table->setItem(number, 0, cuttingDetail);
                for(auto j : result->cuttingResult[i])
                {
                    number++;
                    table->insertRow( number);
                    QTableWidgetItem* designationDetails = new QTableWidgetItem((j.getDesignationName()));
                    table->setItem(number,1,designationDetails);

                    QTableWidgetItem* lenghtDetails = new QTableWidgetItem("Длина " + QString::number(j.getLenght()));
                    table->setItem(number,2,lenghtDetails);
                }
                //number = number + (i + 1) * (cuttingStockBarr.cuttingResult[i].length() + 1);
                number++;
            }

        }




    //number++;

    if(!result->uncutDetails.empty())
    {
        table->insertRow( number);
        number++;
        table->insertRow(number);
        QTableWidgetItem* uncuttingDetail = new QTableWidgetItem("Нераскроенные детали: ");
        uncuttingDetail->setFont(font);
        table->setItem(number, 0, uncuttingDetail);
        for(auto j : result->uncutDetails)
        {
            number++;
            table->insertRow(number);
            QTableWidgetItem* designationUncutDetails = new QTableWidgetItem((j.getDesignationName()));
            table->setItem(number,1,designationUncutDetails);
            QTableWidgetItem* lenghtUncutDetails = new QTableWidgetItem("Длина " + QString::number(j.getLenght()));
            table->setItem(number,2,lenghtUncutDetails);
        }
    }



    return number;
}


void gredyAlgorithm(QVector<Detail> &copyAdapterDetail, Barr &copyAdapterBarr, int sliceThickness, Result_st *cuttingStockBarr, bool sort)
{
    if(sort)
    {
        std::sort(copyAdapterBarr.begin_st(), copyAdapterBarr.end_st(), [](const Barr::Barr_st* a, const Barr::Barr_st* b) ->bool
        {
            return a->lenght < b->lenght;
        });
        std::sort(copyAdapterDetail.begin(), copyAdapterDetail.end());

        std::sort(copyAdapterBarr.begin_sup(), copyAdapterBarr.end_sup(), [](const Barr::Barr_sup* a, const Barr::Barr_sup* b) ->bool
        {
            return a->lenght < b->lenght;
        });
    }


    QVector<bool> Cut(copyAdapterDetail.size(), 1);
    int lenghtBarr = 0;
    for(int i = 0; i< copyAdapterBarr.size_st(); ++i)
    {
        lenghtBarr = copyAdapterBarr.getLenght_st(i);
        for(int j = 0; j < copyAdapterDetail.size(); ++j)
        {
            if(Cut[j])
            {
                if(lenghtBarr > copyAdapterDetail[j].getLenght() + sliceThickness)
                {
                    Cut[j] = 0;
                    cuttingStockBarr->cuttingResult[i].push_back(copyAdapterDetail[j]);
                    lenghtBarr = lenghtBarr - copyAdapterDetail[j].getLenght() - sliceThickness;
                }
                else
                {

                    cuttingStockBarr->surplus[i] = lenghtBarr;
                    cuttingStockBarr->lenghtBarr[i] = copyAdapterBarr.getLenght_st(i);

                }


            }

        }

    }

    fullUncutDetail(Cut, copyAdapterDetail,cuttingStockBarr);
}


void gredyAlgorithmSupplier(QVector<Detail> &copyAdapterDetail, Barr &copyAdapterBarr, int sliceThickness, Result_st *cuttingStockBarr, bool sort)
{

    if(sort)
    {
        std::sort(copyAdapterBarr.begin_st(), copyAdapterBarr.end_st(), [](const Barr::Barr_st* a, const Barr::Barr_st* b) ->bool
        {
            return a->lenght < b->lenght;
        });
        std::sort(copyAdapterDetail.begin(), copyAdapterDetail.end());

        std::sort(copyAdapterBarr.begin_sup(), copyAdapterBarr.end_sup(), [](const Barr::Barr_sup* a, const Barr::Barr_sup* b) ->bool
        {
            return a->lenght < b->lenght;
        });
    }


    QVector<bool> Cut(copyAdapterDetail.size(), 1);
    int lenghtBarr = 0;
    for(int i = 0; i< copyAdapterBarr.size_sup(); ++i)
    {
        lenghtBarr = copyAdapterBarr.getLenght_sup(i);
        for(int j = 0; j < copyAdapterDetail.size(); ++j)
        {
            if(Cut[j])
            {
                if(lenghtBarr > copyAdapterDetail[j].getLenght() + sliceThickness)
                {
                    Cut[j] = 0;
                    cuttingStockBarr->cuttingResult[i].push_back(copyAdapterDetail[j]);
                    lenghtBarr = lenghtBarr - copyAdapterDetail[j].getLenght() - sliceThickness;
                }

                cuttingStockBarr->surplus[i] = lenghtBarr;
                cuttingStockBarr->lenghtBarr[i] = copyAdapterBarr.getLenght_sup(i);
            }

        }

    }

    fullUncutDetail(Cut, copyAdapterDetail,cuttingStockBarr);
}
