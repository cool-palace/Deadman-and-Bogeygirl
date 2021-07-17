#include "cave.h"

Cave::Cave(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    // set graphic
    setPixmap(QPixmap(":/images/cave.png"));
    QGraphicsRectItem * exit = new QGraphicsRectItem(this);
    exit->setRect(43,64,7,16);
    exit->show();
    setScale(3);
}
