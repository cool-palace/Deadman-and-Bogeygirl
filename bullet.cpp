#include "bullet.h"
#include "dog.h"
#include <QDebug>
#include "game.h"

extern Game * game;

Bullet::Bullet(int dir, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));

    direction = static_cast<directions>(dir);

    // make/connect a timer to move() the bullet every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
    show();
}

Bullet::~Bullet() {
    delete timer;
    qDebug() << "bullet deleted";
};

void Bullet::move(){
    int step = 15;

    switch (direction) {
    case UP:
        setPos(x(),y()-step);
        break;
    case DOWN:
        setPos(x(),y()+step);
        break;
    case LEFT:
        setPos(x()-step,y());
        break;
    case RIGHT:
        setPos(x()+step,y());
        break;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<Snake*>(colliding_items[i])){
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    if (x() - boundingRect().width() < 0 || x() > game->scene->width()
            || y() < 0 || y() > game->scene->height()) {
        delete this;
    }
}
