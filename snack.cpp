#include "snack.h"
#include "QCursor"
#include <QDebug>
#include "game.h"

Snack::Snack(int id, QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent)
{
    QString str = ":/images/syrok-small-%1.png";
    setPixmap(QPixmap(str.arg(id+1)));
    switch (id) {
    case 0:
        taste = 4;
        break;
    case 1:
        taste = 2;
        break;
    case 2:
        taste = 1;
        break;
    case 3:
        taste = 5;
        break;
    case 4:
        taste = 3;
        break;
    }
}

void Snack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos() + m_shiftMouseCoords));
}

void Snack::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_shiftMouseCoords = this->pos() - mapToScene(event->pos());
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Snack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Snack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (last_taste == 0) {
        emit degustation(Game::kalinaSeqStart+7,Game::kalinaSeqStart+7);
    } else {
        int taste_diff = this->taste - last_taste;
        qDebug() << taste_diff;
        emit degustation(taste_diff+Game::kalinaSeqStart+12,taste_diff+Game::kalinaSeqStart+12);
    }
    last_taste = this->taste;
}

int Snack::last_taste = 0;
