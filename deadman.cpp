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
    if (lineIndex < speech.size()) {
        emit getbox(&speech[lineIndex]);
        qDebug() << "Line get";
    } else {
        emit over();
        qDebug() << "Dialog over";
    }
}
