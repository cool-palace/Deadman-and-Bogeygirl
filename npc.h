#ifndef NPC_H
#define NPC_H

#include <QGraphicsPixmapItem>

class Couple : public QGraphicsPixmapItem
{
public:
    Couple(QGraphicsItem *parent = nullptr);
};

class Deadman : public QGraphicsPixmapItem
{
public:
    Deadman(QGraphicsItem *parent = nullptr);
};

class Kids : public QGraphicsPixmapItem
{
public:
    Kids(QGraphicsItem *parent = nullptr);
};


class Thinker : public QGraphicsPixmapItem
{
public:
    Thinker(QGraphicsItem * parent = nullptr);
};

class Tree : public QGraphicsPixmapItem
{
public:
    Tree(QGraphicsItem *parent = nullptr);
};

class Unicorn : public QGraphicsPixmapItem
{
public:
    Unicorn(QGraphicsItem *parent = nullptr);
};

#endif // NPC_H
