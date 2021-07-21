#ifndef SNACKGAME_H
#define SNACKGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "snack.h"
#include <QBrush>
#include <button.h>

class SnackGame : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SnackGame(QGraphicsItem* parent = nullptr);
    ~SnackGame();

public slots:
    void checkAnswer();

signals:
    void result(int, int);

private:
    QBrush brush;
    Snack * snacks[5];
    QGraphicsRectItem * snack_slots[5];
    QGraphicsTextItem * number[5];
    QGraphicsRectItem * cond_bg;
    QGraphicsTextItem * conditions;
    Button * confirmButton;
};

#endif // SNACKGAME_H
