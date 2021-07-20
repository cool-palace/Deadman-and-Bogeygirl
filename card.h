#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Card : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Card(int level, QGraphicsItem *parent = nullptr);

    int value;
    bool flipped = false;
    bool flagged = false;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:

};

#endif // CARD_H
