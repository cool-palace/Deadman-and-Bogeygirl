#ifndef CAVE_H
#define CAVE_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Cave : public QGraphicsPixmapItem
{
public:
    Cave(QGraphicsItem *parent = nullptr);
};

class Entrance : public QGraphicsPixmapItem
{
public:
    Entrance(QGraphicsItem *parent = nullptr);
};

class Exit : public QGraphicsPixmapItem
{
public:
    Exit(QGraphicsItem *parent = nullptr);
};

#endif // CAVE_H
