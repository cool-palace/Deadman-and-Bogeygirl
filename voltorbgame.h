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
    //~VoltorbGame();

signals:


private:
    QBrush brush;
    QPen pen;
    Card * card[5][5];
    QGraphicsRectItem * cond_bg;
    QGraphicsTextItem * conditions;
    QGraphicsRectItem * score_bg;
    QGraphicsTextItem * score;
    QGraphicsRectItem * point_indicator_bg[10];
    QGraphicsTextItem * point_indicator[10];
    QGraphicsRectItem * bomb_indicator_bg[10];
    QGraphicsTextItem * bomb_indicator[10];
    QGraphicsPixmapItem * bomb_pics[10];
    int points_row[5];
    int points_col[5];
    int bombs_row[5];
    int bombs_col[5];
    QString score_str = "<p style=\"text-align:center;\">Счёт: %1</p>";
    int level = 1;
    int points = 1;

};

#endif // VOLTORBGAME_H
