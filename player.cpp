#include "player.h"
#include "deadman.h"
#include "game.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

extern Game * game; // there is an external global object called game
extern Deadman * deadman; // there is an external global object called deadman
int step = 10;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // set graphic
    setPixmap(QPixmap(":/images/player.png"));
    setScale(3);
}

void Player::setMovable() {
    isMovable = true;
}

void Player::setImmobile() {
    isMovable = false;
}

void Player::keyPressEvent(QKeyEvent *event){

    // calculating new position
    QPointF newPos = pos();
    if (event->key() == Qt::Key_Left) {
        if (x() > 0) {
            if (x()-step > 0) {
                newPos.setX(x()-step);
            } else newPos.setX(0);
        }
    }
    else if (event->key() == Qt::Key_Right){
        if (x() < game->scene->width() - boundingRect().width()*scale()) {
            if (x()+step < game->scene->width() - boundingRect().width()*scale()) {
                newPos.setX(x()+step);
            } else newPos.setX(game->scene->width() - boundingRect().width()*scale());
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (y() > 0) {
            if (y()-step > 0) {
                newPos.setY(y()-step);
            } else newPos.setY(0);
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (y() < game->scene->height() - boundingRect().height()*scale()) {
            if (y() + step < game->scene->height() - boundingRect().height()*scale()) {
                newPos.setY(y()+step);
            } else newPos.setY(game->scene->height() - boundingRect().height()*scale());
        qDebug() << y();
        }
    }

    // collision detection
    setMovable();
    QGraphicsRectItem * rect = new QGraphicsRectItem(newPos.x(), newPos.y(), boundingRect().width()*scale(), boundingRect().height()*scale());
    game->scene->addItem(rect);
    rect->hide();
    QList<QGraphicsItem *> colliding_items = rect->collidingItems();
    if (colliding_items.size() > 1) {
        setImmobile();
        for (int i = 1, n = colliding_items.size(); i < n; ++i) {
            if (typeid(*(colliding_items[i])) == typeid(Deadman)) {
            //game->deadman->talk();
                emit inRange();
            }
        }
    }
    delete rect;
    if (isMovable) setPos(newPos);

}
