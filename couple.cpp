#include "couple.h"

Couple::Couple(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/couple.png"));
    setScale(2);
}
