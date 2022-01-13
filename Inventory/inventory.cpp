#include "inventory.h"

#include <QDropEvent>
#include <QtGui>

#include <QMimeData>

Inventory::Inventory(QWidget *parent) : QTableWidget(parent) {


    //set widget default properties:
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setDragDropMode(QAbstractItemView::DragDrop);
    setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(false);
    setWordWrap(false);
    setAcceptDrops(true);

}

void Inventory::clear()
{

}



void Inventory::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton
         && this->geometry().contains(event->pos())) {
  this->clearSelection();
          QDrag *drag = new QDrag(this);
          QMimeData *mimeData = new QMimeData;

         // mimeData->setText(commentEdit->toPlainText());

        mimeData->setText("Item");
         drag->setMimeData(mimeData);





         int x=event->pos().x()-25;
         int y=event->pos().y()-25;

 int currentrow=y/(this->height()/3);
 int currentcolumn=x/(this->width()/3);

 startpos = (currentrow * 3) + currentcolumn;

//this->hide();
if(this->GetItem(startpos)!=nullptr)
{


         //get from grid
              QPixmap pix(":/items/apple.png");

          drag->setPixmap(pix);

          //move to cursor position
  drag->setHotSpot( QPoint(pix.height()/2, pix.width()/2) );
          Qt::DropAction dropAction = drag->exec();

}
//this->hide();


}

    if (event->button() == Qt::RightButton
         ) {


        int x=event->pos().x()-25;
        int y=event->pos().y()-25;

        int currentrow=y/(this->height()/3);
        int currentcolumn=x/(this->width()/3);

       int oneDindex= (currentrow * 3) + currentcolumn;

if(this->GetItem(oneDindex)==nullptr)
 {      QTableWidgetItem *thumbnail = new QTableWidgetItem;

//clear in table
this->setItem(currentrow,currentcolumn,thumbnail);
//clear in stack
       this->SetStack(oneDindex, 0);
} else {


    QTableWidgetItem *thumbnail = new QTableWidgetItem;

    //resize img
    QPixmap pix(":/items/apple.png");
    QPixmap resPix = pix.scaled(90,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //set to table cell
    thumbnail->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);



 if (this->GetStack(oneDindex)==1){
            this->SetStack(oneDindex, 0);
   }
   else if(this->GetStack(oneDindex)>1){
        thumbnail->setText(QVariant(this->GetStack(oneDindex)-1).toString());
        //clear in stack
               this->SetStack(oneDindex, this->GetStack(oneDindex)-1);
  thumbnail->setData(Qt::DecorationRole,resPix );
 }



        this->setItem(currentrow,currentcolumn,thumbnail);




}


     }

}



//management elements

////inventory

//Inventory::Inventory()
//{

//}

void Inventory::Insert(int pos, Item *item, int counter)
{


          items[pos]=item;
          stacks[pos]=counter;


}





