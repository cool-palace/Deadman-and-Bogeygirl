#ifndef SNACKGAME_H
#define SNACKGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "snack.h"
#include <QBrush>

class SnackGame : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SnackGame(QGraphicsItem* parent=NULL);
    Snack * snacks[5] = {nullptr};
    QGraphicsRectItem * snack_slots[5] = {nullptr};
//    QGraphicsPixmapItem * snack_slots[5] = {nullptr};
    int last_taste = 0;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void checkAnswer();

signals:
    void result(int, int);

private:
    QBrush brush;
};

#endif // SNACKGAME_H
