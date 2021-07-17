#include "deadman.h"
#include "speechline.h"
#include "dialogbox.h"
#include <QGraphicsScene>
#include <QDebug>

Deadman::Deadman(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // set graphic
    setPixmap(QPixmap(":/images/deadman.png"));
    setScale(3);
}

void Deadman::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void Deadman::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Deadman::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
