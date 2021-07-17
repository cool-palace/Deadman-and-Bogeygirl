#ifndef DEADMAN_H
#define DEADMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class Deadman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Deadman(QGraphicsItem *parent = nullptr);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:


signals:


};

#endif // DEADMAN_H
