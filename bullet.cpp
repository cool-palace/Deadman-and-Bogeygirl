#include "bullet.h"
#include "npc.h"
#include <QDebug>
#include "game.h"

extern Game * game;

Bullet::Bullet(int dir, qreal size, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/bullet.png"));
    setScale(size);

    direction = static_cast<directions>(dir);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
    ++bullet_count;
    show();
}

Bullet::~Bullet() {
    delete timer;
    --bullet_count;
}

void Bullet::move() {
    int step = 15;

    switch (direction) {
    case UP:
        setPos(x(),y()-step);
        break;
    case DOWN:
        setPos(x(),y()+step);
        break;
    case LEFT:
        setPos(x()-step,y());
        break;
    case RIGHT:
        setPos(x()+step,y());
        break;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Enemy * enemy = dynamic_cast<Enemy*>(colliding_items[i]);
        if (enemy) {
            enemy->shot();
            delete this;
            return;
        } else if (dynamic_cast<Spell*>(colliding_items[i])) {
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    if (x() - boundingRect().width() < 0 || x() > game->scene->width()
            || y() < 0 || y() > game->scene->height()) {
        delete this;
    }
}

int Bullet::bullet_count = 0;

Spell::Spell(QGraphicsItem *parent): QGraphicsTextItem(parent) {
    setDefaultTextColor(Qt::white);
    setFont({"Verdana", 16});
    setHtml(spells[rand()%3]);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
    show();
}

Spell::~Spell() {
    delete timer;
}

void Spell::move() {
    int step = 15;
    setPos(x()+step,y());

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Player* player = dynamic_cast<Player*>(colliding_items[i]);
        if (player) {
            player->shot();
            delete this;
            return;
        }
    }

    if (x() - boundingRect().width() < 0 || x() > game->scene->width()
            || y() < 0 || y() > game->scene->height()) {
        delete this;
    }
}
