#include "tree.h"

Tree::Tree(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/tree.png"));
    setScale(1);
}
