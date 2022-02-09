#ifndef NPC_H
#define NPC_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class GameObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    GameObject(QGraphicsItem *parent = nullptr);
    ~GameObject() override = default;

public slots:
    virtual bool interact() = 0;
    void random_movement();
};

class Enemy : public GameObject {
    Q_OBJECT
public:
    Enemy(QGraphicsItem *parent = nullptr);

public slots:
    virtual void shot() = 0;
};

class Cave : public GameObject {
    Q_OBJECT
public:
    Cave(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Couple : public GameObject {
    Q_OBJECT
public:
    Couple(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Deadman : public GameObject {
    Q_OBJECT
public:
    Deadman(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Dog : public GameObject {
    Q_OBJECT
public:
    Dog(QGraphicsItem *parent = nullptr);
    ~Dog() override;

public slots:
    void move();
    bool interact() override;

private:
    QTimer * timer;
};

class Entrance : public GameObject {
    Q_OBJECT
public:
    Entrance(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Exit : public GameObject {
    Q_OBJECT
public:
    Exit(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Kids : public GameObject {
    Q_OBJECT
public:
    Kids(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Portal : public GameObject {
    Q_OBJECT
public:
    Portal(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class RedWhite : public GameObject {
    Q_OBJECT
public:
    RedWhite(QGraphicsItem * parent = nullptr);

public slots:
    bool interact() override;
};

class Snake : public Enemy {
    Q_OBJECT
public:
    Snake(int id, QGraphicsItem *parent = nullptr);
    ~Snake() override;

public slots:
    void start();
    void move();
    void shot() override;
    bool interact() override;

private:
    QTimer * timer;
    static int shotCount;
    int id;
    bool dead = false;
    bool moving = false;
};

class Thinker : public GameObject {
    Q_OBJECT
public:
    Thinker(QGraphicsItem * parent = nullptr);

public slots:
    bool interact() override;
};

class Tree : public GameObject {
    Q_OBJECT
public:
    Tree(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Unicorn : public GameObject {
    Q_OBJECT
public:
    Unicorn(QGraphicsItem *parent = nullptr);

public slots:
    bool interact() override;
};

class Witch : public Enemy {
    Q_OBJECT
public:
    Witch(QGraphicsItem *parent = nullptr);
    ~Witch() override;
    bool dead = false;
    bool moving = false;
    int lives = 10;

public slots:
    void start();
    void move();
    void shoot();
    void shot() override;
    void recover();
    bool interact() override;

private:
    bool direction_up = true;
    int step = 20;
    QTimer * move_timer;
    QTimer * shoot_timer;
    QTimer * hurt_timer;
};

#endif // NPC_H
