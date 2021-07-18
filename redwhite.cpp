#include "redwhite.h"

RedWhite::RedWhite(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/kb.png"));
    //setScale(1);
//    hide();
}
