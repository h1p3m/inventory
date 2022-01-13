#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>
#include <QString>
#include "objects.h"
class QMimeData;

class Inventory: public QTableWidget {
    Q_OBJECT

    public:
        Inventory(QWidget *parent = 0);

        int GetStack(int index) {
            return stacks[index];
        }
        Item* GetItem(int index) {
            return items[index];
        }

        void SetStack(int pos,int stack) {
         stacks[pos]=stack;
        }
        void SetItem(int pos, Item* item) {
            items[pos]=item;
        }
        void Insert(int pos, Item* item, int counter);

        void SetStart(int start) {
            startpos=start;
        }

        bool ContainsStack(int id) {
            return stacks.contains(id);
        }

        bool ContainsItem(int id) {
            return items.contains(id);
        }




int GetStart() {
    return startpos;
}



    public slots:
        void clear();

    signals:
        void changed(const QMimeData *mimeData = 0);
        void dropped(const QMimeData *mimeData = 0);

    protected:

        void mousePressEvent(QMouseEvent *event) override;



        int size=0;
         QMap<int, Item*> items;
            QMap<int, int> stacks;

            bool flag=false;

int startpos=-1;



    private:
        QTableWidget *tablewidget;
};


#endif // INVENTORY_H
