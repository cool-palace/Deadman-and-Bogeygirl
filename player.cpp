#include "player.h"
#include "redwhite.h"
#include "game.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "bullet.h"

extern Game * game; // there is an external global object called game
int step = 24;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // set graphic
    setPixmap(QPixmap(":/images/player-left.png"));
}

void Player::setMovable() {
    isMovable = true;
}

void Player::setImmobile() {
    isMovable = false;
}

void Player::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Space && canShoot) {
        Bullet * bullet = new Bullet(direction);
        switch (direction) {
        case UP:
            bullet->setPos(x()+boundingRect().width()/2,y()-bullet->boundingRect().height());
            break;
        case DOWN:
            bullet->setPos(x()+boundingRect().width()/2,y()+boundingRect().height());
            break;
        case LEFT:
            bullet->setPos(x()-bullet->boundingRect().width(),y()+boundingRect().height()/2);
            break;
        case RIGHT:
            bullet->setPos(x()+boundingRect().width(),y()+boundingRect().height()/2);
            break;
        }
       // bullet->setPos(x()+boundingRect().width()/2, y()+50);
        game->scene->addItem(bullet);
        return;
    }

    // calculating new position

    QPointF diff = {0, 0};
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        if (direction != LEFT) {
            setPixmap(QPixmap(":/images/player-left.png"));
            direction = LEFT;
        }

        if (x() > 0) {
            if (x()-step > 0) {
                diff.setX(-step);
            } else diff.setX(-x());
        }
    }
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
        if (direction != RIGHT) {
            setPixmap(QPixmap(":/images/player-right.png"));
            direction = RIGHT;
        }
        if (x() < game->scene->width() - boundingRect().width()*scale()) {
            if (x()+step < game->scene->width() - boundingRect().width()*scale()) {
                diff.setX(step);
            } else diff.setX(game->scene->width() - boundingRect().width()*scale() - x());
        }
    }
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W){
        direction = UP;
        if (y() > 0) {
            if (y()-step > 0) {
                diff.setY(-step);
            } else diff.setY(-y());
        }
    }
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S){
        direction = DOWN;
        if (y() < game->scene->height() - boundingRect().height()*scale()) {
            if (y() + step < game->scene->height() - boundingRect().height()*scale() ) {
                diff.setY(step);
            } else diff.setY(game->scene->height() - boundingRect().height()*scale() - y());
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
    QList<QGraphicsItem *> child_items = childItems();


    for (int i = 0; i < child_items.size(); ++i) {
        for (int j = 0; j < colliding_items.size(); ++j) {
            if (colliding_items[j] == child_items[i] || colliding_items[j] == this
                    || dynamic_cast<Bullet*>(colliding_items[i])) {
                colliding_items.removeAt(j);
                --j;
            }
        }
    }


    for (int i = 1, n = colliding_items.size(); i < n; ++i){

        if (dynamic_cast<Deadman*>(colliding_items[i])) {
            setImmobile();
            if (game->dialogbox->end == 0) {
                emit dialogCall(0,1);
            } else emit dialogCall(2,2);

        } else if (dynamic_cast<Entrance*>(colliding_items[i])) {
            emit goingIn();
            return;

        } else if (dynamic_cast<Cave*>(colliding_items[i])) {
            setImmobile();

        } else if (dynamic_cast<Tree*>(colliding_items[i])) {
            setImmobile();
            emit dialogCall(Game::kalinaSeqStart,Game::kalinaSeqStart+6);

        } else if (dynamic_cast<Kids*>(colliding_items[i])) {
            if (childItems().empty()) {
                setImmobile();
                emit dialogCall(Game::kidsSeqStart,Game::kidsSeqStart+10);
            }

//            } else if (dynamic_cast<Dog*>(colliding_items[i])) {
//                emit dialogCall(21,21);
//                colliding_items[i]->setParentItem(this);

        } else if (dynamic_cast<RedWhite*>(colliding_items[i])) {
            setImmobile();
            emit dialogCall(Game::kidsSeqStart+16,Game::kidsSeqStart+17);

        } else if (dynamic_cast<Unicorn*>(colliding_items[i])) {
            setImmobile();
            emit dialogCall(Game::unicornSeqStart,Game::unicornSeqStart+3);

        } else if (dynamic_cast<Couple*>(colliding_items[i])) {
            setImmobile();
            emit dialogCall(Game::coupleSeqStart,Game::coupleSeqStart+7);

        } else if (dynamic_cast<Thinker*>(colliding_items[i])) {
            setImmobile();
            emit dialogCall(Game::thinkerSeqStart,Game::thinkerSeqStart+10);

        } else if (dynamic_cast<Snake*>(colliding_items[i])) {
            setImmobile();
            emit dialogCall(Game::snakeSeqStart,Game::snakeSeqStart+14);

        } else if (dynamic_cast<Exit*>(colliding_items[i])) {
            emit goingOut();
            return;
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
