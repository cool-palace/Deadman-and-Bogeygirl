#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = nullptr);
    ~Player() override;

    enum directions {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

public slots:
    void keyPressEvent(QKeyEvent * event) override;
    void setMovable();
    void setImmobile();
    void shot();
    void enable_shooting();
    void disable_shooting();

private slots:
    void set_direction(directions);
    void shrink_bullet();

signals:
    void dialogCall(int start, int end);
    void goingOut();
    void goingIn();

private:
    QMediaPlayer * bulletSound;
    qreal bullet_size = 1;
    bool isMovable = true;
    bool canShoot = false;
    directions direction = LEFT;
};

#endif // PLAYER_H
