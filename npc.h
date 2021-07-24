#ifndef NPC_H
#define NPC_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Couple : public QGraphicsPixmapItem
{
public:
    Couple(QGraphicsItem *parent = nullptr);
};

class Deadman : public QGraphicsPixmapItem
{
public:
    Deadman(QGraphicsItem *parent = nullptr);
};

class Dog : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dog(QGraphicsItem *parent = nullptr);
    ~Dog();

public slots:
    void move();

private:
    QTimer * timer;
};

class Kids : public QGraphicsPixmapItem
{
public:
    Kids(QGraphicsItem *parent = nullptr);
};

class Snake : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Snake(int id, QGraphicsItem *parent = nullptr);
    ~Snake();
    static int shotCount;
    int id;
    bool dead = false;
    bool moving = false;

public slots:
    void start();
    void move();
    void shot();

private:
    QTimer * timer;
};

class Thinker : public QGraphicsPixmapItem
{
public:
    Thinker(QGraphicsItem * parent = nullptr);
};

class Tree : public QGraphicsPixmapItem
{
public:
    Tree(QGraphicsItem *parent = nullptr);
};

class Unicorn : public QGraphicsPixmapItem
{
public:
    Unicorn(QGraphicsItem *parent = nullptr);
};

class Witch : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Witch(QGraphicsItem *parent = nullptr);
    ~Witch();
    bool dead = false;
    bool moving = false;
    int lives = 10;

public slots:
    void start();
    void move();
    void shoot();
    void shot();
    void recover();

private:
    bool direction_up = true;
    int step = 20;
    QTimer * move_timer;
    QTimer * shoot_timer;
    QTimer * hurt_timer;
};

#endif // NPC_H
