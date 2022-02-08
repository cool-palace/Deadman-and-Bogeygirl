#ifndef VOLTORBGAME_H
#define VOLTORBGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QMediaPlayer>
#include <QGraphicsSceneMouseEvent>

class Card : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Card(int level, QGraphicsItem *parent = nullptr);

public slots:
    int val() { return value; }
    void flip();
    void change(int level);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void pointCardOpen(int);
    void explode(int);

private:
    int value;
    bool flipped = false;
    bool flagged = false;
};


class VoltorbGame : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    VoltorbGame(QGraphicsItem* parent = nullptr);
    ~VoltorbGame();

public slots:
    void increaseScore(int);
    void reset();
    void open(int);

signals:
    void result(int start, int end);

private:
    QBrush brush;
    QPen pen;
    Card * card[5][5];
    QGraphicsRectItem * cond_bg;
    QGraphicsTextItem * conditions;
    QGraphicsRectItem * score_bg;
    QGraphicsTextItem * score;
    QGraphicsTextItem * level_ind;
    QGraphicsRectItem * point_indicator_bg[10];
    QGraphicsTextItem * point_indicator[10];
    QGraphicsRectItem * bomb_indicator_bg[10];
    QGraphicsTextItem * bomb_indicator[10];
    QGraphicsPixmapItem * bomb_pics[10];
    int offset_x, offset_y, ind_offset_x, ind_offset_y;
    int points_row[5];
    int points_col[5];
    int bombs_row[5];
    int bombs_col[5];
    int pointCardsLeft = 0;
    QString score_str = "<p style=\"text-align:center;\">Счёт:<br>%1</p>";
    QString level_str = "<p style=\"text-align:center;\">Уровень: %1</p>";
    int level = 1;
    long int points = 1;
    QMediaPlayer * correctSound;
    QMediaPlayer * wrongSound;
};

#endif // VOLTORBGAME_H
