#include "graphic.h"
#include "ui_graphic.h"

graphic::graphic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphic)
{
   ui->setupUi(this);


   qDebug() << "graphic 13";

}

graphic::~graphic()
{
    //delete supplier;
    //delete stock;
    delete ui;
}

void graphic::create(Result_st *result_stock, Result_st* result_supplier)
{
    //Рисуем график y=x*x

        //Сгенерируем данные
        //Для этого создадим два массива точек:
        //один для созранения x координат точек,
        //а второй для y соответственно
        if(result_stock != nullptr)
        {
            double a = 0; //Начало интервала, где рисуем график по оси Ox
            double b =  result_stock->surplus.size(); //Конец интервала, где рисуем график по оси Ox
            double h = 1; //Шаг, с которым будем пробегать по оси Ox

            int N=(b-a)/h + 2; //Вычисляем количество точек, которые будем отрисовывать
            QVector<double> x(N), y(N); //Массивы координат точек

            //Вычисляем наши данные
            int i=0;
            for (int X=a; X<b; X+=h)//Пробегаем по всем точкам
            {
                x[i] = X + 1;
                y[i] = result_stock->surplus[i];//Формула нашей функции
                i++;
            }

            ui->stockGraphic->clearGraphs();//Если нужно, но очищаем все графики
            //Добавляем один график в widget
            ui->stockGraphic->addGraph();
            //Говорим, что отрисовать нужно график по нашим двум массивам x и y
            ui->stockGraphic->graph(0)->setData(x, y);
            ui->stockGraphic->graph(0)->setPen(QColor(Qt::darkRed));//задаем цвет точки
            ui->stockGraphic->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
            //формируем вид точек
            ui->stockGraphic->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));

            //Подписываем оси Ox и Oy
            ui->stockGraphic->xAxis->setLabel("Номер заготовки");
            ui->stockGraphic->yAxis->setLabel("Остаток, мм");

            //Установим область, которая будет показываться на графике
            ui->stockGraphic->xAxis->setRange(a, b + 1);//Для оси Ox

            //Для показа границ по оси Oy сложнее, так как надо по правильному
            //вычислить минимальное и максимальное значение в векторах
            double minY = y[0], maxY = y[0];
            for (int i=1; i<N; i++)
            {
                if (y[i]<minY) minY = y[i];
                if (y[i]>maxY) maxY = y[i];
            }
            ui->stockGraphic->yAxis->setRange(minY, maxY + 5);//Для оси Oy


            //И перерисуем график на нашем widget
            ui->stockGraphic->replot();
            for(int j = 0; j < result_stock->surplus.size(); ++j)
            {
                QCPBars *bars1 = new QCPBars(ui->stockGraphic->xAxis, ui->stockGraphic->yAxis);
                bars1->setWidth(0.2);
                bars1->addData(j + 1, result_stock->surplus[j]);
                bars1->setPen(Qt::NoPen);
                bars1->setBrush(QColor(Qt::darkRed));
                //delete bars1;
            }


            QLinearGradient plotGradient;
            plotGradient.setStart(0, 0);
            plotGradient.setFinalStop(0, 350);
            plotGradient.setColorAt(0, QColor(Qt::gray));
            plotGradient.setColorAt(1, QColor(Qt::darkGray));
            ui->stockGraphic->setBackground(plotGradient);
        }
        else
        {
            QLinearGradient plotGradient;
            plotGradient.setStart(0, 0);
            plotGradient.setFinalStop(0, 350);
            plotGradient.setColorAt(0, QColor(Qt::gray));
            plotGradient.setColorAt(1, QColor(Qt::darkGray));
            ui->stockGraphic->setBackground(plotGradient);
        }

        if(result_supplier != nullptr)
        {
            double a = 0; //Начало интервала, где рисуем график по оси Ox
            double b =  result_supplier->surplus.size(); //Конец интервала, где рисуем график по оси Ox
            double h = 1; //Шаг, с которым будем пробегать по оси Ox

            int N=(b-a)/h + 2; //Вычисляем количество точек, которые будем отрисовывать
            QVector<double> x(N), y(N); //Массивы координат точек

            //Вычисляем наши данные
            int i=0;
            for (int X=a; X < b; X+=h)//Пробегаем по всем точкам
            {
                x[i] = X + 1;
                if(!result_supplier->cuttingResult[i].empty())
                    y[i] = result_supplier->surplus[i];//Формула нашей функции
                else
                    y[i] = 0;
                i++;
            }

            ui->supplierGraphic->clearGraphs();//Если нужно, но очищаем все графики
            //Добавляем один график в widget
            ui->supplierGraphic->addGraph();
            //Говорим, что отрисовать нужно график по нашим двум массивам x и y
            ui->supplierGraphic->graph(0)->setData(x, y);
            ui->supplierGraphic->graph(0)->setPen(QColor(Qt::darkBlue));//задаем цвет точки
            ui->supplierGraphic->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
            //формируем вид точек
            ui->supplierGraphic->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc , 5));
            //Подписываем оси Ox и Oy
            ui->supplierGraphic->xAxis->setLabel("Номер заготовки");
            ui->supplierGraphic->yAxis->setLabel("Остаток, мм");

            //Установим область, которая будет показываться на графике
            ui->supplierGraphic->xAxis->setRange(a, b + 1);//Для оси Ox

            //Для показа границ по оси Oy сложнее, так как надо по правильному
            //вычислить минимальное и максимальное значение в векторах
            double minY = y[0], maxY = y[0];
            for (int i=1; i<N; i++)
            {
                if (y[i]<minY) minY = y[i];
                if (y[i]>maxY) maxY = y[i];
            }
            ui->supplierGraphic->yAxis->setRange(minY, maxY + 5);//Для оси Oy
            for(int j = 0; j < result_supplier->surplus.size(); ++j)
            {
                QCPBars *bars1 = new QCPBars(ui->supplierGraphic->xAxis, ui->supplierGraphic->yAxis);
                bars1->setWidth(0.2);
                bars1->addData(j + 1, result_supplier->surplus[j]);
                bars1->setPen(Qt::NoPen);
                bars1->setBrush(QColor(Qt::darkBlue));
                //delete bars1;
            }
            //И перерисуем график на нашем widget
            ui->supplierGraphic->replot();

            QLinearGradient plotGradient;
            plotGradient.setStart(0, 0);
            plotGradient.setFinalStop(0, 350);
            plotGradient.setColorAt(0, QColor(Qt::gray));
            plotGradient.setColorAt(1, QColor(Qt::darkGray));
            ui->supplierGraphic->setBackground(plotGradient);
        }
        else
        {
            QLinearGradient plotGradient;
            plotGradient.setStart(0, 0);
            plotGradient.setFinalStop(0, 350);
            plotGradient.setColorAt(0, QColor(Qt::gray));
            plotGradient.setColorAt(1, QColor(Qt::darkGray));
            ui->supplierGraphic->setBackground(plotGradient);
        }
    qDebug() << "Create";

}

