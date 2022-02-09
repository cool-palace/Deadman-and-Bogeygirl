#ifndef SNACKGAME_H
#define SNACKGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <button.h>
#include <QMediaPlayer>

class Snack : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Snack(int id, QGraphicsItem * parent = nullptr);
    ~Snack() override = default;

public slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

signals:
    void degustation(int, int);

private:
    int taste;
    static int last_taste;
    QPointF m_shiftMouseCoords;
};

class SnackGame : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    SnackGame(QGraphicsItem* parent = nullptr);
    ~SnackGame() override;

private slots:
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
    QMediaPlayer * correctSound;
    QMediaPlayer * wrongSound;
};

#endif // SNACKGAME_H
