#ifndef DYEGAME_H
#define DYEGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include "button.h"
#include <QBrush>
#include <QMediaPlayer>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class Dye : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Dye(int id, QGraphicsItem *parent = nullptr);
    ~Dye() override = default;

public slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QPointF m_shiftMouseCoords;
};

class DyeGame : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    DyeGame(QGraphicsItem *parent = nullptr);
    ~DyeGame();

private slots:
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
