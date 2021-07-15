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

void Deadman::talk(int lineIndex) {
    QVector<Speechline> sp;
    if (!introduced) sp = speech;
    else sp = speech2;
    if (lineIndex < sp.size()) {
        emit getbox(&sp[lineIndex]);
    } else {
        emit over();
    }
}
