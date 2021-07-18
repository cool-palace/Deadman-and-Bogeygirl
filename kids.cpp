#include "kids.h"

Kids::Kids(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/kids.png"));
    setScale(3);
}

