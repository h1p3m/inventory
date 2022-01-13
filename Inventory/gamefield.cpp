#include "gamefield.h"
#include "ui_gamefield.h"
#include <QDragMoveEvent>
#include <QAbstractItemView>
#include <QDrag>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QObject>
#include "objects.h"
#include "inventory.h"
#include "dbmanager.h"
#include <QHeaderView>
#include <QPushButton>
#include "dialog.h"
#include <QtMath>
#include <QDebug>
#include <QFileInfo>
void GameField::Update()
{
    qDebug()<< "update";



dm->ClearInv();


    for(int i=0; i <9; i++) {


     if((ui->tableWidget->ContainsItem(i) ==false) || (ui->tableWidget->GetStack(i)<1)) {
       // QString* fp=new QString("empty");
        // QString* type=new QString("empty");
        // Item* item=new Item(fp, type);
         dm->addInventory("empty","empty",0);

} else {
      //    dm->addInventory( ui->tableWidget->GetItem(i),ui->tableWidget->GetStack(i));
dm->addInventory( ui->tableWidget->GetItem(i)->GetImagepath(),*ui->tableWidget->GetItem(i)->itemtype,ui->tableWidget->GetStack(i));
     }

    }


}


GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);
    //when dialog starts


    //if db exists - load

    QFileInfo check_file(qApp->applicationDirPath()+"//inventory.db");




//just test db


dm=new DbManager(qApp->applicationDirPath()+"//inventory.db");






//create thread that update bd

  timer = new QTimer(this);
//  timer->moveToThread(dm);
  timer->setInterval(10000);
  connect(dm, SIGNAL(started()), timer, SLOT(start()));
  //connect(timer, &QTimer::timeout, dm, dm->UpdateInv(ui->tableWidget), Qt::DirectConnection);

   connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
timer->start();



//grid preset
    ui-> tableWidget-> horizontalHeader()->hide();
    ui-> tableWidget-> verticalHeader()->hide();

ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui-> tableWidget-> setColumnCount (3);
    ui-> tableWidget-> setColumnWidth (0, ui->tableWidget->width()/3);
    ui-> tableWidget-> setColumnWidth (1, ui->tableWidget->width()/3);
    ui-> tableWidget-> setColumnWidth (2, ui->tableWidget->width()/3);

      ui-> tableWidget-> setRowCount (3);
      ui-> tableWidget-> setRowHeight(0, ui->tableWidget->height()/3);
     ui-> tableWidget-> setRowHeight(1,ui->tableWidget->height()/3);
     ui-> tableWidget-> setRowHeight(2,ui->tableWidget->height()/3);


     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
//set field cells empty for grid
        for(int row=0;row< ui->tableWidget->rowCount(); row++)
          for (int col=0;col<ui->tableWidget->columnCount(); col++)
     ui-> tableWidget->setItem(row,col,new QTableWidgetItem());

        setAcceptDrops(true);

        // check if path exists and if yes: Is it really a file and no directory?
        if( check_file.exists() && check_file.isFile()) {
         dm->Load(qApp->applicationDirPath()+"//inventory.db", ui->tableWidget);
        }


        //items labels set

        QPixmap pix(":/items/apple.png");

     ui->label->setPixmap(pix);


}


GameField::~GameField()
{
    delete ui;
}


//for items

void GameField::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton
       && ui->label->geometry().contains(event->pos())) {
ui->tableWidget->clearSelection();
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

       // mimeData->setText(commentEdit->toPlainText());

      mimeData->setText("Label");
       drag->setMimeData(mimeData);

            QPixmap pix(":/items/apple.png");

        drag->setPixmap(pix);

        //move to cursor position
drag->setHotSpot( QPoint(pix.height()/2, pix.width()/2) );
        Qt::DropAction dropAction = drag->exec();





   }



}



//for field
void GameField::dragEnterEvent(QDragEnterEvent *event) {

    setAcceptDrops(true);
        event->acceptProposedAction();
        emit changed(event->mimeData());






}

void GameField::dragMoveEvent(QDragMoveEvent *event) {

    event->acceptProposedAction();


}

void GameField::dropEvent(QDropEvent *event) {

    event->acceptProposedAction();
   emit dropped(event->mimeData());
    if (ui->tableWidget->geometry().contains(event->pos())) {

        int x=event->pos().x()-25;
        int y=event->pos().y()-25;

int currentrow=y/(ui->tableWidget->height()/3);
int currentcolumn=x/(ui->tableWidget->width()/3);


int oneDindex = (currentrow * 3) + currentcolumn;



QString* fp=new QString(":/items/apple.png");
QString* type=new QString("energy");
Item * item=new Item(fp,type);




QTableWidgetItem *thumbnail = new QTableWidgetItem;

//resize img
QPixmap pix(*fp);
QPixmap resPix = pix.scaled(90,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//set to table cell
thumbnail->setTextAlignment(Qt::AlignBottom| Qt::AlignRight );





this->setWindowTitle(QString::number(ui->tableWidget->GetStart()));


if(ui->tableWidget->GetStart()==-1) {
  //if this from object
//if contains stack counter
   // if(
    if(ui->tableWidget->ContainsStack(oneDindex)) {
            thumbnail->setText(QVariant(ui->tableWidget->GetStack(oneDindex)+1).toString());
ui->tableWidget->Insert(oneDindex,item, ui->tableWidget->GetStack(oneDindex)+1);

    } else { //if not contains
    ui->tableWidget->Insert(oneDindex,item,1 );
    thumbnail->setText(QVariant(1).toString());
    }

} else {
    //if this from inventory


    if(ui->tableWidget->ContainsStack(oneDindex)) {
            thumbnail->setText(QVariant(ui->tableWidget->GetStack(oneDindex)+ui->tableWidget->GetStack(ui->tableWidget->GetStart())).toString());
ui->tableWidget->Insert(oneDindex,item, ui->tableWidget->GetStack(oneDindex)+ui->tableWidget->GetStack(ui->tableWidget->GetStart()));



//insert empty cell to start cell
QTableWidgetItem *thumbnail2 = new QTableWidgetItem;

//clear in table
ui->tableWidget->setItem(ui->tableWidget->GetStart()/3,ui->tableWidget->GetStart()%3,thumbnail2);
//clear in stack
  ui->tableWidget->SetStack(ui->tableWidget->GetStart(), 0);
    } else { //if not contains
        thumbnail->setText(QVariant(ui->tableWidget->GetStack(ui->tableWidget->GetStart())).toString());
ui->tableWidget->Insert(oneDindex,item, ui->tableWidget->GetStack(ui->tableWidget->GetStart()));


//insert empty cell to start cell
QTableWidgetItem *thumbnail2 = new QTableWidgetItem;

//clear in table
ui->tableWidget->setItem(ui->tableWidget->GetStart()/3,ui->tableWidget->GetStart()%3,thumbnail2);
//clear in stack
  ui->tableWidget->SetStack(ui->tableWidget->GetStart(), 0);
delete thumbnail2;
    }



ui->tableWidget->SetStart(-1);
}



thumbnail->setData(Qt::DecorationRole,resPix );

ui-> tableWidget->setItem( currentrow, currentcolumn, thumbnail);


//delete item;

//delete fp;
//delete type;
 }










}

void GameField::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void GameField::clear() {
    emit changed();
}


void GameField::on_pushButton_clicked()
{
    //if main menu off

    QList<QWidget*> buttonsList = this->findChildren<QWidget *>();
      for (int i = 0; i < buttonsList.count(); i++){

          if(ui->pushButton!= buttonsList.at(i))
          buttonsList.at(i)->setEnabled(
                      tableflag);
      }

      if(tableflag==false) {

      dial->show();

      tableflag=true;
      } else {
          tableflag=false;
            dial->close();
      }
      //if main menu on

}
