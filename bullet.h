#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(int dir, QGraphicsItem *parent = nullptr);
    ~Bullet();
    enum directions {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

public slots:
    void move();

signals:
    void hitTarget();
    void dialogCall(int start, int end);

private:
    //static int snakesShot;
    directions direction = LEFT;
    QTimer * timer;
};

#endif // BULLET_H
