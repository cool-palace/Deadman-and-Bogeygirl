#include "dye.h"
#include "QCursor"

Dye::Dye(int id, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    QString str = ":/images/dye-small-%1.png";
    setPixmap(QPixmap(str.arg(id+1)));

    setAcceptHoverEvents(true);
}

void Dye::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos() + m_shiftMouseCoords));
}

void Dye::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_shiftMouseCoords = this->pos() - mapToScene(event->pos());
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Dye::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Dye::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Dye::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setCursor(QCursor(Qt::ArrowCursor));
}
