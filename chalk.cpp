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

    setAcceptHoverEvents(true);
}

Chalk::~Chalk() {
    delete cracks;
//    for (int i = 0; i < crushSound.size(); ++i) {
//        delete crushSound[i];
//    }
    qDebug() << "chalk deleted";
}

void Chalk::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = start - mapToScene(event->pos());
    if (sqrt(p.x()*p.x() + p.y()*p.y()) > 300) {
        start = mapToScene(event->pos());

        game->crushSound[cracksCount]->play();

        if (cracksCount < 5) {
            // Добавить выбор загадки потом
            if (cracksCount == 4) {
                emit cracked(&game->riddles[0]);
                //setAcceptHoverEvents(false);
                delete this;
                return;
            }
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
    this->setCursor(QCursor(Qt::OpenHandCursor));
    Q_UNUSED(event);
}

void Chalk::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Chalk::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setCursor(QCursor(Qt::ArrowCursor));
}
