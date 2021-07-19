#ifndef UNICORN_H
#define UNICORN_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Unicorn : public QObject, public QGraphicsPixmapItem
{
public:
    Unicorn(QGraphicsItem *parent = nullptr);

signals:

};

#endif // UNICORN_H
