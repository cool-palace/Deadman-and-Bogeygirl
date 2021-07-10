#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // set graphic
    setPixmap(QPixmap(":/images/player.png"));
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Left) {
        if (pos().x() > 10)
            setPos(x()-10,y());
        else if (pos().x() > 0)
            setPos(0, y());
        }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 10 < 800 - 16)
            setPos(x()+10,y());
        else if (pos().x() + 10 < 800)
            setPos(800 - 16, y());
    }
    else if (event->key() == Qt::Key_Up){
        if (pos().y() > 10)
            setPos(x(),y()-10);
        else if (pos().y() > 0)
            setPos(x(), 0);
        qDebug() << y();
    }
    else if (event->key() == Qt::Key_Down){
        if (pos().y() < 600 - 32 - 10)
            setPos(x(),y()+10);
        else if (pos().y() < 600 - 32)
            setPos(x(),600-32);
        qDebug() << y();
    }

}

