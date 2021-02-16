#include "dialogadddetail.h"
#include "ui_dialogadddetail.h"
#include <QTextStream> //убрать бибилиотеку
#include <QFileDialog>

#include <QDebug>


void AddDetailManually();

DialogAddDetail::DialogAddDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddDetail), filePath(""), designationDetail(""), nameDetail(""), lenghtDetail(0), amountOfDetail(0), adapterDetails()
    //excel(nullptr)
{
    ui->setupUi(this);
    ui->pcmDir->setEnabled(false);
    ui->textDir->setEnabled(false);

}

DialogAddDetail::~DialogAddDetail()
{

    qDebug() << "Destructor dialog add detail";
    adapterDetails.clear();
    if(ui != nullptr)
        delete ui;
}

void DialogAddDetail::on_addDetailManually_clicked()
{
       ui->pcmDir->setEnabled(false);
       ui->textDir->setEnabled(false);

       ui->designationDetail->setEnabled(true);
       ui->nameDetail->setEnabled(true);
       ui->amountOfDetail->setEnabled(true);
       ui->lenghtDetail->setEnabled(true);

}

void DialogAddDetail::on_addFile_clicked()
{
        ui->pcmDir->setEnabled(true);
        ui->textDir->setEnabled(true);

        ui->designationDetail->setEnabled(false);
        ui->nameDetail->setEnabled(false);
        ui->amountOfDetail->setEnabled(false);
        ui->lenghtDetail->setEnabled(false);


}

void DialogAddDetail::on_pcmDir_clicked()
{
    filePath = QFileDialog::getOpenFileName(0, "Select Directory", ui->textDir->text());
     QFileInfo* file = new QFileInfo(filePath); //Как он уничтожается??? предка то нет
   if ( !filePath.isEmpty()) {
       ui->textDir->setText(file->baseName());
    }
    delete file;
}

void DialogAddDetail::on_addDetailsButton_clicked()
{
    if(ui->addDetailManually->isChecked())
    {
        getQStrings();
        //Проверяем, чтобы все поля были заполнены
        if(checkLines())
        {
           QMessageBox::information(0, "Предупреждение", "Заполните все поля!");
           lightOnWidget();
        }
        else
        {
            AddDetailManually();
        }
    }
    else if(ui->addFile->isChecked())
    {
        if(!filePath.isEmpty())
        {
            ReadExcelFile();
        }
        else
        {
            QMessageBox::information(0, "Предупреждение", "Выберите файл");
         }
    }


}

bool DialogAddDetail::checkLines()
{
    bool check = ((designationDetail.isEmpty()) || (lenghtDetail == 0) || (amountOfDetail == 0));
    return check;
}

void DialogAddDetail::getQStrings()
{
    designationDetail = ui->designationDetail->text();
    nameDetail = ui->nameDetail->text();
    lenghtDetail = ui->lenghtDetail->value();
    amountOfDetail = ui->amountOfDetail->value();
    //designationDetail(""), nameDetail(""), lenghtDetail(0), amountOfDetail(0)
}

void DialogAddDetail::lightOnWidget()
{
    if(designationDetail.isEmpty())
        lightOn(ui->designationDetail);

    if(lenghtDetail == 0)
        lightOn(ui->lenghtDetail);
    if(amountOfDetail == 0)
        lightOn(ui->amountOfDetail);
}

void DialogAddDetail::lightOn(QWidget* changeLightBorder)
{
    changeLightBorder->setStyleSheet("border: 1px solid red");
}

void DialogAddDetail::on_designationDetail_textEdited(const QString &arg1)
{
    ui->designationDetail->setStyleSheet("border: 1px solid black");
}



void DialogAddDetail::on_amountOfDetail_valueChanged(int arg1)
{
    ui->amountOfDetail->setStyleSheet("border: 1px solid black");
}

void DialogAddDetail::on_lenghtDetail_valueChanged(double arg1)
{
    ui->lenghtDetail->setStyleSheet("border: 1px solid black");
}

const QVector<Detail>& DialogAddDetail::copyAdapterDetail() const
{
    return adapterDetails;
}


