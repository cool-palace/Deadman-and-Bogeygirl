#ifndef DYEGAME_H
#define DYEGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include "dye.h"
#include <QBrush>

class DyeGame : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    DyeGame(QGraphicsItem *parent = nullptr);
    Dye * dyes[5] = {nullptr};
    QGraphicsRectItem * dye_slot;

public slots:
    void checkAnswer();
    void reset();

signals:
    void result(int, int);

private:
    QBrush brush;
};

#endif // DYEGAME_H
