#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
//#include <QMediaPlayer>

class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void setMovable();
    void setImmobile();
    enum directions {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    bool canShoot = false;

    directions direction = LEFT;

signals:
//    void dialogCall(int i);
    void dialogCall(int start, int end);
    void goingOut();
    void goingIn();

private:
    bool isMovable = true;

};

#endif // PLAYER_H
