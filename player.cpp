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

    // calculating new position

    QPointF diff = {0, 0};
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
//        if (!left) {
//            setScale(3);
//            left = true;
//        }
        if (x() > 0) {
            if (x()-step > 0) {
                diff.setX(-step);
            } else diff.setX(-x());
        }
    }
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
//        if (left) {
//            setScale(-3);
//            left = false;
//        }
        if (x() < game->scene->width() - boundingRect().width()*scale()) {
            if (x()+step < game->scene->width() - boundingRect().width()*scale()) {
                diff.setX(step);
            } else diff.setX(game->scene->width() - boundingRect().width()*scale() - x());
        }
    }
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W){
        if (y() > 0) {
            if (y()-step > 0) {
                diff.setY(-step);
            } else diff.setY(-y());
        }
    }
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S){
        if (y() < game->scene->height() - boundingRect().height()*scale() - 30) {
            if (y() + step < game->scene->height() - boundingRect().height()*scale() - 30) {
                diff.setY(step);
            } else diff.setY(game->scene->height() - boundingRect().height()*scale() - 30 - y());
        }
    }

    // collision detection
    setMovable();
    QPointF newPos = pos() + diff;
    QGraphicsRectItem * rect = new QGraphicsRectItem(newPos.x(), newPos.y(),
                                                     boundingRect().width()*scale(), boundingRect().height()*scale());
    game->scene->addItem(rect);
    rect->hide();

    QList<QGraphicsItem *> colliding_items = rect->collidingItems();

    if (colliding_items.size() > 1) {
        for (int i = 1, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Deadman)){
                setImmobile();
                if (game->dialogbox->end == 0) {
                    emit dialogCall(0,1);
                } else emit dialogCall(2,2);
                    qDebug() << "Trying to get dialog";
            } else if (typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)) {
                emit goingOut();
                return;
            }
        }
    }

    delete rect;

    if (isMovable) {
        setPos(newPos);
        if (game->scene->width() > 800) {
            game->currentViewPos += diff;
            QRectF newView = {game->currentViewPos.x(),game->currentViewPos.y(),800,600};
            game->setSceneRect(newView);
        }
    }

}
