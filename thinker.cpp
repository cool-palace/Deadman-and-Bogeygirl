#include "thinker.h"

Thinker::Thinker(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/thinker.png"));
}
