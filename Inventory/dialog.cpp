#include "dialog.h"
#include "ui_dialog.h"
#include "gamefield.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_2_clicked()
{
    reject();
    //exit
}

void Dialog::on_pushButton_clicked()
{
    accept();
    //open game field
    GameField* gf=new GameField();
    gf->show();
}
