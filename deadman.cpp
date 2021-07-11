#include "deadman.h"
#include <QGraphicsScene>
#include <QDebug>

Deadman::Deadman(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // set graphic
    setPixmap(QPixmap(":/images/deadman.png"));
    setScale(3);
}

void Deadman::talk() {
    qDebug() << "Talked to a dead man";
}
