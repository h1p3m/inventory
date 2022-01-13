#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QMimeData>

#include <QStyleOptionViewItem>

#include "objects.h"
#include "inventory.h"
#include "dialog.h"

#include <QThread>
#include <QTimer>
#include "dbmanager.h"
namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

private:
    Ui::GameField *ui;
public slots:
    void clear();
    void Update();
signals:
    void changed(const QMimeData *mimeData = 0);
    void dropped(const QMimeData *mimeData = 0);


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
 void dragMoveEvent(QDragMoveEvent *event) override;
  void dragLeaveEvent(QDragLeaveEvent *event) override;
  void dropEvent(QDropEvent *event) override;

void mousePressEvent(QMouseEvent *event) override;

bool tableflag=false;
Dialog* dial=new Dialog;

QTimer * timer;
DbManager* dm;
private slots:
void on_pushButton_clicked();
};

#endif // GAMEFIELD_H
