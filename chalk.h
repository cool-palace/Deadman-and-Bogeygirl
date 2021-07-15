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
    //QPointF start = {0, 0};
    int cracksCount = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void dropEvent(QGraphicsSceneDragDropEvent *event);

signals:
    void cracked(Riddle * riddle);

};

#endif // CHALK_H
