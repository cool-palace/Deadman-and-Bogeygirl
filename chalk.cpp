#include "chalk.h"
#include "game.h"
#include <qmath.h>

extern Game * game;

Chalk::Chalk(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/asmr.png"));
    cracks = new QGraphicsPixmapItem(this);
    cracks->setPixmap(QPixmap(":/images/cracks.png"));
    cracks->setOpacity(0);

    for (int i = 0; i < crushSound.size(); ++i) {
        crushSound[i] = new QMediaPlayer();
        QString str = "qrc:/sounds/crush-%1.wav";
        crushSound[i]->setMedia(QUrl(str.arg(i+1)));
    }
}


void Chalk::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = start - mapToScene(event->pos());
    if (sqrt(p.x()*p.x() + p.y()*p.y()) > 300) {
        start = mapToScene(event->pos());

        crushSound[cracksCount]->play();

        if (cracksCount < 5) {
            // Добавить выбор загадки потом
            if (cracksCount == 4) emit cracked(&game->riddles[3]);
            ++cracksCount;
            cracks->setOpacity((qreal)cracksCount/5);

        }
    }
}

void Chalk::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    start = mapToScene(event->pos());
    Q_UNUSED(event);
}

void Chalk::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

