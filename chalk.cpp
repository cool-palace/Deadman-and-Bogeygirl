#include "chalk.h"
#include "game.h"

extern Game * game;

Chalk::Chalk(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/asmr-1.png"));
    setAcceptDrops(true);
}

void Chalk::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    switch (cracksCount) {
    case 0:
        setPixmap(QPixmap(":/images/asmr-2.png"));
        break;
    case 1:
        setPixmap(QPixmap(":/images/asmr-3.png"));
        break;
    case 2:
        setPixmap(QPixmap(":/images/asmr-4.png"));
        break;
    case 3:
        setPixmap(QPixmap(":/images/asmr-5.png"));
        break;
    case 4:
        emit cracked(&game->riddles[0]);
        qDebug() << "Cracked" << cracksCount;
    }
    if (cracksCount < 5) ++cracksCount;
}

//void Chalk::dropEvent(QGraphicsSceneDragDropEvent *event) {
//    qDebug() << event->pos();
//    if (sqrt((start.x()-event->pos().x())*(start.x()-event->pos().x())
//             + (start.y()-event->pos().y())*(start.y()-event->pos().y())) > 100) {
//        setPixmap(QPixmap(":/images/asmr-2.png"));
//        start = event->pos();
//    }

//}
