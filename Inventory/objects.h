#ifndef OBJECTS_H
#define OBJECTS_H

#include <QString>
#include <QMap>
#include <QList>
class Item
{


public:
    QString *imagepath;
    QString *itemtype;
    Item(QString *imgp, QString *itmtype);
    QString GetImagepath() {
        return *imagepath;
    }
};





#endif // OBJECTS_H
