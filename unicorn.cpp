#include "unicorn.h"

Unicorn::Unicorn(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/unicorn.png"));
    setScale(1);
}
