#include "tree.h"

Tree::Tree(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/kalina.png"));
    setScale(1);
}
