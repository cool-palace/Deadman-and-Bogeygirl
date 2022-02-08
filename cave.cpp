#include "cave.h"

Cave::Cave(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/cave.png"));
}

Entrance::Entrance(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/cave-entrance.png"));
}

Exit::Exit(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/exit.png"));
}

Portal::Portal(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/portal.png"));
}
