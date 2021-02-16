#ifndef BARR_H
#define BARR_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDebug>
class Barr
{

public:
    class Barr_st
    {
        /*private:
            double lenght{0};
            int amount{1};*/
        public:
            double lenght{0};
            int amount{1};
            Barr_st() : lenght(0), amount(1) {};
            ~Barr_st() {qDebug() << "Barr stock destructor";}
            Barr_st(double lenght_, int amount_) : lenght(lenght_), amount(amount_) {};
            Barr_st(const Barr_st& otherBarr_st) { lenght = otherBarr_st.lenght; amount = otherBarr_st.amount;}
            Barr_st& operator = (const Barr_st& otherBarr_st) {  lenght = otherBarr_st.lenght; amount = otherBarr_st.amount; return *this;}
            int getLenght() {return lenght;}
            //friend bool operator<(Barr_st* firstBarr, Barr_st* secondBarr) {qDebug() << "operator < "; return firstBarr->lenght < secondBarr->lenght;}
            //bool compare_st(Barr_st& secondBarr) {return lenght < secondBarr.lenght;}
            //friend bool operator<(const Barr_st& firstBarr, const Barr_st& secondBarr); //{qDebug() << "operator < "; return firstBarr.lenght < secondBarr.lenght;}

    };

    class Barr_sup
    {
        /*private:
            double lenght{0};
            int amount{1};
            double cost{0};*/
        public:
            double lenght{0};
            int amount{1};
            double cost{0};
            Barr_sup() : lenght(0), amount(1), cost(0) {qDebug() << "Barr supplier constructor";}
            ~Barr_sup() {qDebug() << "Barr_supplier destructor";}
            Barr_sup(double lenght_, int amount_, double cost_) : lenght(lenght_), amount(amount_), cost(cost_){qDebug() << "Barr supplier constructor";};
            Barr_sup(const Barr_sup& otherBarr_sup) {lenght = otherBarr_sup.lenght; amount = otherBarr_sup.amount; cost = otherBarr_sup.cost; qDebug() << "Barr supplier constructor";}
            Barr_sup& operator = (const Barr_sup& otherBarr_sup) {lenght = otherBarr_sup.lenght; amount = otherBarr_sup.amount;
                                                                  cost = otherBarr_sup.cost; return *this;}
            //friend bool operator<(const Barr_sup& firstBarr, const Barr_sup& secondBarr) {return firstBarr.lenght < secondBarr.lenght;}
            int getLenght() {return lenght;}

    };
    QVector<Barr_st*> arrayStockBarr;
    QVector<Barr_sup*> arraySupplierBarr;
    int diameterOfBarr;
public:
    Barr() : arrayStockBarr(), arraySupplierBarr(), diameterOfBarr(200){qDebug() << "Barr constructor";}
    ~Barr();
    Barr(const Barr& otherBarr);
    Barr& operator = (const Barr& otherBarr);
    void push_back_st(double lenght, int amount);
    void push_back_sup(double lenght, int amount, double cost);
    int size_st();
    int size_sup();
    void clear_st();
    void clear_sup();
    void erase_st(int counter);

    void erase_sup(int counter);
    QVector<Barr_st*>::iterator end_st() {return arrayStockBarr.end();}
    QVector<Barr_sup*>::iterator end_sup() {return arraySupplierBarr.end();}
    QVector<Barr_st*>::iterator begin_st() {return arrayStockBarr.begin();}
    QVector<Barr_sup*>::iterator begin_sup() {return arraySupplierBarr.begin();}
    void print_st() const;
    void print_sup() const;
    void setDiameterOfBarr(int diameter){diameterOfBarr = diameter;}
    int getDiameterOfBarr() const {return diameterOfBarr;}
    int getLenght_st(int i) {return arrayStockBarr[i]->getLenght();}
    int getLenght_sup(int i) {return arraySupplierBarr[i]->getLenght();}
    //методы для расчета
    bool empty_st();
    bool empty_sup();



};

#endif // BARR_H
