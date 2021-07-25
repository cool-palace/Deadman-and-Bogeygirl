#ifndef VOLTORBGAME_H
#define VOLTORBGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include "card.h"
#include <QBrush>
#include <QPen>
#include <QFont>

class VoltorbGame : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    VoltorbGame(QGraphicsItem* parent=NULL);
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

};

#endif // VOLTORBGAME_H
