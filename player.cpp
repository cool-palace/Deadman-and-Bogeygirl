#include "player.h"
#include "game.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "bullet.h"

extern Game * game;
int step = 24;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/player-left.png"));
    bulletSound = new QMediaPlayer();
    bulletSound->setMedia(QUrl("qrc:/sounds/bullet.wav"));
    bulletSound->setVolume(5);
}

Player::~Player() {
    delete bulletSound;
}

void Player::setMovable() {
    isMovable = true;
}

void Player::setImmobile() {
    isMovable = false;
}

void Player::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && canShoot && Bullet::bullet_count < 10) {
        if (game->progress == Game::OUTSIDE_EMPTINESS_DISCOVERED
                || game->progress == Game::DEADMAN_REVIVED) direction = LEFT;

        if (bulletSound->state() == QMediaPlayer::PlayingState){
            bulletSound->setPosition(0);
        } else if (bulletSound->state() == QMediaPlayer::StoppedState){
            bulletSound->play();
        }

        Bullet * bullet = new Bullet(direction, bullet_size);
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
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        if (direction != RIGHT) {
            setPixmap(QPixmap(":/images/player-right.png"));
            direction = RIGHT;
        }
        if (x() < game->scene->width() - boundingRect().width()*scale()) {
            if (x()+step < game->scene->width() - boundingRect().width()*scale()) {
                diff.setX(step);
            } else diff.setX(game->scene->width() - boundingRect().width()*scale() - x());
        }
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
        direction = UP;
        if (y() > 0) {
            if (y()-step > 0) {
                diff.setY(-step);
            } else diff.setY(-y());
        }
    } else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
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
            if (colliding_items.at(j) == child_items.value(i) || colliding_items.value(j) == this
                    || dynamic_cast<Bullet*>(colliding_items.value(i))) {
                colliding_items.removeAt(j);
                --j;
            }
        }
    }

    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<GameObject*>(colliding_items.at(i))) {
            GameObject * npc = dynamic_cast<GameObject*>(colliding_items.at(i));
            // interact() returns false on passages
            if (!npc->interact()) return;
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

void Player::shrink_bullet() {
    bullet_size *= 0.995;
    if (bullet_size < 0.2) {
        game->dialogbox->getBox(Game::witchSeqStart+7, Game::witchSeqStart+10);
        disconnect(game->timer,SIGNAL(timeout()),this,SLOT(shrink_bullet()));
        bullet_size = 5;
    }
}
