#ifndef CUT_H
#define CUT_H

#endif // CUT_H
#pragma once
#include <QVector>
#include "detail.h"
#include "barr.h"
#include <QTableWidget>


struct Result_st
{
    QVector<int> surplus;
    QVector<Detail> uncutDetails;
    QVector<QList<Detail>> cuttingResult;
    QVector<int> lenghtBarr;

    Result_st(int sizeBarr) : surplus(sizeBarr), uncutDetails(), cuttingResult(sizeBarr), lenghtBarr(sizeBarr){};
    Result_st() : surplus(), uncutDetails(), cuttingResult(), lenghtBarr(){};
    int getLenght(int i)  const {return lenghtBarr[i];}
    int getLenghtSurplus(int i) const {return surplus[i];}
    void print()
    {

        qDebug() << "Нераскроенные детали: ";
        for(auto i : uncutDetails)
            i.print();
       qDebug() << "Раскроенные детали: ";
        for(int i = 0; i < cuttingResult.size(); ++i)
        {
            for(auto j : cuttingResult[i])
                j.print();
            qDebug() << "Длина бара" << lenghtBarr[i];
            qDebug() << "Остаток: " << surplus[i];
        }
        /*qDebug() << "Barr: ";
        for(int i = 0; i < lenghtBarr.size(); ++i)
        {
            qDebug() << lenghtBarr[i];
        }*/
    }

};


void lengthOptimizationCalculation(QVector<Detail>& arrayCopyDetail, Barr& arrayCopyBarr, int sliceThickness, Result_st* result_stock);
void copyDetails(const QVector<Detail>& arrayDetails, QVector<Detail>& copyArrayDetails, int sliceThickness);
int DynamicProgrammingCut(const QVector<Detail>&arrayCopyDetail, int sliceThickness,  QVector<bool>& cutDetail, QList<Detail>& cuttingResult, int lenghtBarr); //динамический раскрой для одной заготовки
int cut( QVector<int>& detailsAmount, const QVector<Detail>& details, int lenght, QList<Detail>& resultList, QVector<bool>& cutPart); //восстанавливаем раскрой
void fullUncutDetail(const QVector<bool>& cutDetail, const QVector<Detail>& arrayCopyDetail, Result_st* result_stock);

void lengthOptimizationUncutDetails(Barr& arrayCopyBarr, int sliceThickness, Result_st* result_supplier, const QVector<Detail>& result_stock);

bool checkUncutDetails(const QVector<bool>& cutDetail);

void DataOutputToTable(QTableWidget* table, const Result_st* cuttingStockBarr, const Result_st* cuttingSupplierBarr);

int fullColumn(const Result_st* result, int number, QTableWidget* table);

void gredyAlgorithm(QVector<Detail>& copyAdapterDetail, Barr& copyAdapterBarr, int sliceThickness, Result_st* cuttingStockBarr, bool sort);

void gredyAlgorithmSupplier(QVector<Detail>& copyAdapterDetail, Barr& copyAdapterBarr, int sliceThickness, Result_st *cuttingSupplierBarr, bool sort);
