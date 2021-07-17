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
    Chalk(QGraphicsItem* parent=NULL);
    QGraphicsPixmapItem * cracks;
    QVector<QMediaPlayer *> crushSound {5};
    QPointF start = {0, 0};
    int cracksCount = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void cracked(const Riddle * riddle);

};

#endif // CHALK_H
