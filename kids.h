#ifndef KIDS_H
#define KIDS_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Kids : public QObject, public QGraphicsPixmapItem
{
public:
    Kids(QGraphicsItem *parent = nullptr);

signals:

};

#endif // KIDS_H
