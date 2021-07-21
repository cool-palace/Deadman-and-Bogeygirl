#ifndef DYE_H
#define DYE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Dye : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dye(int id, QGraphicsItem *parent = nullptr);
    QPointF m_shiftMouseCoords;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:

};

#endif // DYE_H
