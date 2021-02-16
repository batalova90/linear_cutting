#include "barr.h"
#include <QDebug>
Barr::~Barr()
{
    qDebug() << "Barr destructor";
    for(int i = 0; i < arrayStockBarr.size(); ++i)
        delete arrayStockBarr[i];

    for(int i = 0; i < arraySupplierBarr.size(); ++i)
        delete arraySupplierBarr[i];
}

Barr::Barr(const Barr& otherBarr) : diameterOfBarr(otherBarr.diameterOfBarr)
{
    for(int i = 0; i < otherBarr.arrayStockBarr.size(); ++i)
        {
             push_back_st(otherBarr.arrayStockBarr[i]->lenght, otherBarr.arrayStockBarr[i]->amount);
        }

    for(int i = 0; i < otherBarr.arraySupplierBarr.size(); ++i)
        {
             push_back_sup(otherBarr.arraySupplierBarr[i]->lenght, otherBarr.arraySupplierBarr[i]->amount, otherBarr.arraySupplierBarr[i]->cost);
        }
}
Barr& Barr::operator = (const Barr& otherBarr)
{
    for(int i = 0; i < otherBarr.arrayStockBarr.size(); ++i)
    {
        arrayStockBarr[i] = otherBarr.arrayStockBarr[i];
    }

    for(int i = 0; i < otherBarr.arraySupplierBarr.size(); ++i)
    {
        arraySupplierBarr[i] = otherBarr.arraySupplierBarr[i];
    }

    return *this;
}

void Barr::push_back_st(double lenght, int amount)
{
    Barr_st* current = new Barr_st(lenght, amount);
    arrayStockBarr.push_back(current);
}
void Barr::push_back_sup(double lenght, int amount, double cost)
{
    Barr_sup* current = new Barr_sup(lenght, amount, cost);
    arraySupplierBarr.push_back(current);
}

int Barr::size_st()
{
    return arrayStockBarr.size();
}
int Barr::size_sup()
{
    return arraySupplierBarr.size();
}

void Barr::clear_st()
{
    for(int i = 0; i < arrayStockBarr.size(); ++i)
        delete arrayStockBarr[i];
    arrayStockBarr.clear();
}
void Barr::clear_sup()
{
    for(int i = 0; i < arraySupplierBarr.size(); ++i)
        delete arraySupplierBarr[i];
    arraySupplierBarr.clear();
}
void Barr::erase_st(int counter)
{
    for(int i = arrayStockBarr.size() - counter; i < arrayStockBarr.size(); ++i)
        delete arrayStockBarr[i];
    arrayStockBarr.erase(arrayStockBarr.end() - counter, arrayStockBarr.end());
}


void Barr::erase_sup(int counter)
{
    for(int i = arraySupplierBarr.size() - counter; i < arraySupplierBarr.size(); ++i)
        delete arraySupplierBarr[i];
    arraySupplierBarr.erase(arraySupplierBarr.end() - counter, arraySupplierBarr.end());
}

void Barr::print_st() const
{
    qDebug() << "дошли до print\t" << arrayStockBarr.size();
    for(int i = 0; i < arrayStockBarr.size(); ++i)
        qDebug() << arrayStockBarr[i]->lenght << "\tдлина \t" << arrayStockBarr[i]->amount << "\tкол-во \t";

}

void Barr::print_sup() const
{
    qDebug() << "дошли до print\t";
    for(int i = 0; i < arraySupplierBarr.size(); ++i)
        qDebug() << arraySupplierBarr[i]->lenght << "\t длина" << arraySupplierBarr[i]->amount << "\t кол-во" << arraySupplierBarr[i]->cost << "цена";

}


//методы, необходимые для расчета
bool Barr::empty_st()

{
    return arrayStockBarr.empty();
}

bool Barr::empty_sup()
{
    return arraySupplierBarr.empty();
}
//bool operator<(Barr::Barr_st* firstBarr, Barr::Barr_st* secondBarr) {qDebug() << "operator < "; return firstBarr->lenght < secondBarr->lenght;}



