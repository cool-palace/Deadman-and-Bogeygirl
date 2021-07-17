#ifndef SNACK_H
#define SNACK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Snack : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Snack(int id, QGraphicsItem * parent = nullptr);
    int taste;
    static int last_taste;
    QPointF m_shiftMouseCoords;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void degustation(int, int);
};

#endif // SNACK_H
