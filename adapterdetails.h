#ifndef ADAPTERDETAILS_H
#define ADAPTERDETAILS_H
#pragma once
#include <QObject>
#include <QWidget>
#include "detail.h"
#include <vector>
class adapterDetails
{
public:
    adapterDetails();
    ~adapterDetails() {};
    void push_back(const Detail& newDetail);
    bool empty();
    int size();

private:
    std::vector<Detail> arrayDetail;
    int sizeChunk;
};




#endif // ADAPTERDETAILS_H
