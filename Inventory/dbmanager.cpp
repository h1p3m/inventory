#include "dbmanager.h"
#include <QVariant>
#include <QDebug>
#include "inventory.h"
DbManager::DbManager(const QString& path)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE inventory(imagepath text, itemtype text, stack integer)");

}



bool DbManager::addInventory(const QString& imgpath,const QString& imgtype, int stack)
{
   bool success = false;
   // you should check if args are ok first...
   QSqlQuery query;



   query.prepare("INSERT INTO inventory (imagepath, itemtype, stack) "
                 "VALUES (?, ?, ?)");

   query.addBindValue(imgpath);
   query.addBindValue(imgtype);
   query.addBindValue(stack);
   query.exec();
   if(query.exec())
   {
       success = true;
   }
   else
   {
//        qDebug() << "addPerson error:"
//                 << query.lastError();
   }

   return success;
}

void DbManager::ClearInv()
{
    QSqlQuery query;
    qDebug() << "clear is";
    query.prepare("DELETE FROM inventory");

    qDebug()<< query.exec();
}

void DbManager::Load(const QString &path, Inventory* inv)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;

    query.exec("SELECT * FROM inventory");
    int size=0;
    while (query.next()) {

        QString* fp=new QString(query.value(0).toString());
        QString* type=new QString(query.value(1).toString());
        Item* item=new Item(fp, type);

          int counter = query.value(2).toInt();


          if(*fp!="empty") {
          inv->Insert(size, item, counter);





          QTableWidgetItem *thumbnail = new QTableWidgetItem;

          //resize img
          QPixmap pix(*fp);
          QPixmap resPix = pix.scaled(90,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

          //set to table cell
          thumbnail->setTextAlignment(Qt::AlignBottom| Qt::AlignRight );

          thumbnail->setData(Qt::DecorationRole,resPix );
thumbnail->setText(QString::number(counter));
                inv->setItem(size/3,size%3,thumbnail);

}
          size++;
         qDebug() << *fp <<*type << counter;
      }








}

//void DbManager::UpdateInv(Inventory* inv)
//{
//qDebug()<< "update";

////qDebug() <<dm->addInventory(*item, 2);




//}
