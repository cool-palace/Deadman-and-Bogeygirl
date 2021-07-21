#ifndef CHALK_H
#define CHALK_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>
#include "riddle.h"

class Chalk : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Chalk(QGraphicsItem* parent = nullptr);
    ~Chalk();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void cracked(const Riddle * riddle);

private:
    QGraphicsPixmapItem * cracks;
    QPointF start = {0, 0};
    int cracksCount = 0;

};

#endif // CHALK_H
