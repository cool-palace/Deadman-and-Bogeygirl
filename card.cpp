#include "card.h"
#include <QDebug>

Card::Card(int level, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    change(level);
}

void Card::change(int level) {
    setPixmap(QPixmap(":/images/tile.png"));
    flipped = false;
    flagged = false;

    if (level > 3) level = 3;
    int rng = rand() % 100;

    switch (level) {
    case 1:
        if (rng < 25) value = 0; // 25%
        else if (rng < 80 && rng >= 25) value = 1; // 55%
        else if (rng < 95 && rng >= 80) value = 2; // 15%
        else if (rng < 100 && rng >= 95) value = 3; // 5%
        break;
    case 2:
        if (rng < 25) value = 0; // 25%
        else if (rng < 70 && rng >= 25) value = 1; // 45%
        else if (rng < 90 && rng >= 70) value = 2; // 20%
        else if (rng < 100 && rng >= 90) value = 3; // 10%
        break;
    case 3:
        if (rng < 25) value = 0; // 25%
        else if (rng < 65 && rng >= 25) value = 1; // 40%
        else if (rng < 85 && rng >= 65) value = 2; // 20%
        else if (rng < 100 && rng >= 85) value = 3; // 15%
        break;
    }
    setAcceptHoverEvents(true);
}

void Card::flip() {
    flipped = true;
    setAcceptHoverEvents(false);
    QString str = ":/images/tile-%1.png";
    setPixmap(QPixmap(str.arg(value)));
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if (event->button() == Qt::LeftButton && !flipped) {
        flip();
        if (value > 1) emit pointCardOpen(value);
        else if (value == 0) emit explode(value);

    } else if (event->button() == Qt::RightButton && !flipped) {
        if (!flagged) {
            flagged = true;
            setPixmap(QPixmap(":/images/tile-flag-yellow.png"));
        } else {
            flagged = false;
            setPixmap(QPixmap(":/images/tile-yellow.png"));
        }

    }
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    if (!flagged) {
        setPixmap(QPixmap(":/images/tile-yellow.png"));
    } else setPixmap(QPixmap(":/images/tile-flag-yellow.png"));

}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){

    if (!flagged) {
        setPixmap(QPixmap(":/images/tile.png"));
    } else setPixmap(QPixmap(":/images/tile-flag.png"));

}
