#include "detail.h"


Detail::Detail() :  designation(""), name(""), lenght(0), amountOfDetail(1) {}

Detail::Detail(const QString& designation_, const QString& name_, double lenght_, int amountOfDetail_) : designation(designation_),
                                                                                         name(name_), lenght(lenght_),
                                                                                         amountOfDetail(amountOfDetail_){}

Detail::Detail(const Detail& otherDetail) : designation(otherDetail.designation), name(otherDetail.name),
                                            lenght(otherDetail.lenght), amountOfDetail
(otherDetail.amountOfDetail){}

Detail& Detail::operator=(const Detail &otherDetail)
{
    designation = otherDetail.designation;
    name = otherDetail.name;
    lenght = otherDetail.lenght;
    amountOfDetail = otherDetail.amountOfDetail;
    return *this;
}

QString Detail::getDesignationName() const
{
    QString str(designation + " - " + name);
    return str;
}

double Detail::getLenght() const
{
    return lenght;
}

void Detail::changeDesignation(const QString& designation_)
{
    designation = designation_;
}

void Detail::changeName(const QString& name_)
{
    name = name_;
}

void Detail::changeLenght(double lenght_)
{
    lenght = lenght_;
}

void Detail::print() const
{
    qDebug() << "Обозначение: "<< designation << " Наименование: " << name <<
                " Длина детали: " << lenght << " кол-во деталей: " << amountOfDetail;
}

int Detail::getAmountOfDetail()
{
    return amountOfDetail;
}

bool operator<(const Detail& firstDetail, const Detail& secondDeatil)
{
    if(firstDetail.lenght != secondDeatil.lenght)
        return firstDetail.lenght < secondDeatil.lenght;
    else
    {
        if(firstDetail.designation != secondDeatil.designation)
            return firstDetail.designation < secondDeatil.designation;
        else
        {
            if(firstDetail.name != secondDeatil.name)
                return firstDetail.name < secondDeatil.name;
            else
            {
                if(firstDetail.amountOfDetail != secondDeatil.amountOfDetail)
                    return firstDetail.amountOfDetail < secondDeatil.amountOfDetail;
                else
                    return false;
            }
        }
    }


}

void Detail::setLenghtWithCropping(int sliceThickness)
{
    lenght = lenght + sliceThickness;
}
