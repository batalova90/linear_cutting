#ifndef DETAIL_H
#define DETAIL_H

#endif // DETAIL_H
#pragma once
#include <QString>
#include <QDebug>
class Detail
{
private:
    QString designation;
    QString name;
    double lenght;
    int amountOfDetail;

public:
    Detail();
    Detail(const QString& designation_, const QString& name_, double lenght_, int amountOfDetail_);
    ~Detail(){};
    Detail(const Detail& otherDetail);
    Detail& operator = (const Detail& otherDetail);
    friend bool operator<(const Detail& firstDetail, const Detail& secondDeatil);
    QString getDesignationName() const;
    double getLenght() const;
    void setLenghtWithCropping(int sliceThickness);
    void changeDesignation(const QString& designation_);
    void changeName(const QString& name_);
    void changeLenght(double lenght_);
    void print() const;
    int getAmountOfDetail();
};
