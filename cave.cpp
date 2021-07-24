#include "cave.h"

Cave::Cave(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    // set graphic
    setPixmap(QPixmap(":/images/cave.png"));
}

Entrance::Entrance(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    // set graphic
    setPixmap(QPixmap(":/images/cave-entrance.png"));
}

Exit::Exit(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    // set graphic
    setPixmap(QPixmap(":/images/exit.png"));
}

Portal::Portal(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    // set graphic
    setPixmap(QPixmap(":/images/portal.png"));
}
