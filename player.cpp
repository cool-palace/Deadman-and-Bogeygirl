#include "player.h"
#include "deadman.h"
#include "game.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

extern Game * game; // there is an external global object called game
extern Deadman * deadman; // there is an external global object called deadman
int step = 32;

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

    // if a dialog box is open, player can't move until she presses the space button
    if (game->dialogbox->isVisible()) {
        if (event->key() == Qt::Key_Space) {
            ++currentLineIndex;
            emit next(currentLineIndex);
            qDebug() << "Trying to get the next line";
            //game->dialogbox->hide();
        }
        return;
    }

    // calculating new position

    QPointF newPos = pos();
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        if (x() > 0) {
            if (x()-step > 0) {
                newPos.setX(x()-step);
            } else newPos.setX(0);
        }
    }
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
        if (x() < game->scene->width() - boundingRect().width()*scale()) {
            if (x()+step < game->scene->width() - boundingRect().width()*scale()) {
                newPos.setX(x()+step);
            } else newPos.setX(game->scene->width() - boundingRect().width()*scale());
        }
    }
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W){
        if (y() > 0) {
            if (y()-step > 0) {
                newPos.setY(y()-step);
            } else newPos.setY(0);
        }
    }
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S){
        if (y() < game->scene->height() - boundingRect().height()*scale()) {
            if (y() + step < game->scene->height() - boundingRect().height()*scale()) {
                newPos.setY(y()+step);
            } else newPos.setY(game->scene->height() - boundingRect().height()*scale());
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
                emit dialogCall(0);
                qDebug() << "Trying to get dialog";
            }
        }
    }
    delete rect;
    if (isMovable) setPos(newPos);


}
