#include "player.h"
#include "redwhite.h"
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
            if (colliding_items[j] == child_items[i]) {
                colliding_items.removeAt(j);
                --j;
            }
        }
    }

    if (colliding_items.size() > 1) {
        for (int i = 1, n = colliding_items.size(); i < n; ++i){
            //react(colliding_items[i]);

            if (dynamic_cast<Deadman*>(colliding_items[i])) {
                setImmobile();
                if (game->dialogbox->end == 0) {
                    emit dialogCall(0,1);
                } else emit dialogCall(2,2);

            } else if (dynamic_cast<Cave*>(colliding_items[i])) {
                setImmobile();
                for (int i = 1, n = colliding_items.size(); i < n; ++i) {
                    // Здесь рект - вход в пещеру
                    if (dynamic_cast<QGraphicsRectItem*>(colliding_items[i]))
                        emit goingIn();
                        return;
                }

            } else if (dynamic_cast<Tree*>(colliding_items[i])) {
                setImmobile();
                emit dialogCall(Game::kalinaSeqStart,Game::kalinaSeqStart+6);

            } else if (dynamic_cast<Kids*>(colliding_items[i])) {
                if (childItems().empty()) {
                    setImmobile();
                    emit dialogCall(17,20);
                }

//            } else if (dynamic_cast<Dog*>(colliding_items[i])) {
//                emit dialogCall(21,21);
//                colliding_items[i]->setParentItem(this);

            } else if (dynamic_cast<RedWhite*>(colliding_items[i])) {
                setImmobile();
                emit dialogCall(22,23);

            } else if (dynamic_cast<Unicorn*>(colliding_items[i])) {
                setImmobile();
                emit dialogCall(24,27);

            } else if (dynamic_cast<Couple*>(colliding_items[i])) {
                setImmobile();
                emit dialogCall(Game::coupleSeqStart,Game::coupleSeqStart+7);

            } else if (dynamic_cast<Thinker*>(colliding_items[i])) {
                setImmobile();
                emit dialogCall(Game::thinkerSeqStart,Game::thinkerSeqStart+10);

            } else if (dynamic_cast<QGraphicsPixmapItem*>(colliding_items[i])) {
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

//template <typename T> void Player::react(T* object) { qDebug() << "template";};

//template <> void Player::react(Deadman* object) {
//    setImmobile();
//    if (game->dialogbox->end == 0) {
//        emit dialogCall(0,1);
//    } else emit dialogCall(2,2);
//};
