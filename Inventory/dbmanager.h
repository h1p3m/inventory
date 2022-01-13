#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "objects.h"
#include <QThread>
#include <QDebug>
#include "inventory.h"
class DbManager : public QThread
{
public:
    DbManager(const QString& path);

   bool addInventory(const QString& imgpath,const QString& imgtype, int stack);

void ClearInv();


void Load(const QString& path, Inventory* inv);

private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
