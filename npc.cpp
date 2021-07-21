#include "npc.h"

Couple::Couple(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/couple.png"));
    setScale(2);
}

Deadman::Deadman(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/deadman.png"));
    setScale(3);
}

Kids::Kids(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/kids.png"));
    setScale(3);
}

Thinker::Thinker(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/thinker.png"));
}

Tree::Tree(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/kalina.png"));
}

Unicorn::Unicorn(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/unicorn.png"));
}
