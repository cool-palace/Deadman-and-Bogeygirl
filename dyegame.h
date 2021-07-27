#ifndef DYEGAME_H
#define DYEGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include "dye.h"
#include "button.h"
#include <QBrush>
#include <QMediaPlayer>

class DyeGame : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    DyeGame(QGraphicsItem *parent = nullptr);
    ~DyeGame();

public slots:
    void checkAnswer();
    void reset();

signals:
    void result(int, int);

private:
    QBrush brush;
    Dye * dyes[5];
    QGraphicsRectItem * dye_slot;
    QGraphicsRectItem * cond_bg;
    QGraphicsTextItem * conditions;
    QGraphicsTextItem * text;
    Button * confirmButton;
    Button * resetButton;
    QMediaPlayer * correctSound;
    QMediaPlayer * wrongSound;
};

#endif // DYEGAME_H
