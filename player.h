#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = nullptr);
    ~Player();
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

public slots:
    void shrink_bullet();

signals:
//    void dialogCall(int i);
    void dialogCall(int start, int end);
    void goingOut();
    void goingIn();

private:
    QMediaPlayer * bulletSound;
    qreal bullet_size = 1;
    bool isMovable = true;

};

#endif // PLAYER_H
