#include "adapterdetails.h"

adapterDetails::adapterDetails() : arrayDetail(10), sizeChunk(10)
{

}


void adapterDetails::push_back(const Detail &newDetail)
{
    if(sizeChunk == 0)
    {
        sizeChunk = 19;
        arrayDetail.resize(arrayDetail.size() + 20);
        arrayDetail.push_back(newDetail);

    }
    else
    {
        --sizeChunk;
        arrayDetail.push_back(newDetail);

    }

}

bool adapterDetails::empty()
{
    return arrayDetail.size() == 0;
}

int adapterDetails::size()
{
    return arrayDetail.size();
}


