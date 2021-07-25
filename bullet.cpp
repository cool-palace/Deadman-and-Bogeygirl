#include "bullet.h"
#include "npc.h"
#include <QDebug>
#include "game.h"

extern Game * game;

Bullet::Bullet(int dir, qreal size, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));
    setScale(size);

    direction = static_cast<directions>(dir);

    // make/connect a timer to move() the bullet every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
    ++bullet_count;
    show();
}

Bullet::~Bullet() {
    delete timer;
    --bullet_count;
};

void Bullet::move(){
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
        if (dynamic_cast<Snake*>(colliding_items[i])){
            Snake * snake = dynamic_cast<Snake*>(colliding_items[i]);
            connect(this,SIGNAL(hitTarget()),snake,SLOT(shot()));
            emit hitTarget();
            delete this;
            return;
        } else if (dynamic_cast<Witch*>(colliding_items[i])) {
            Witch * witch = dynamic_cast<Witch*>(colliding_items[i]);
            connect(this,SIGNAL(hitTarget()),witch,SLOT(shot()));
            emit hitTarget();
            if (game->progress == Game::DEADMAN_REVIVED) {
                --witch->lives;
                if (witch->lives == 0) {
                    game->progress = Game::WITCH_DEFEATED;
                    delete witch;
                    game->deadman->show();
                }
            }
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

Spell::Spell(QGraphicsItem *parent): QGraphicsTextItem(parent)
{

    setDefaultTextColor(Qt::white);
    setFont({"Comic Sans", 16});
    setHtml(spells[rand()%3]);

    // make/connect a timer to move() the bullet every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
    show();
}

Spell::~Spell() {
    delete timer;
};

void Spell::move(){
    int step = 15;

    setPos(x()+step,y());

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<Player*>(colliding_items[i])){
            game->player = dynamic_cast<Player*>(colliding_items[i]);
            if (game->player->x()+game->player->boundingRect().width() + 100 < game->scene->width()) {
                game->player->setPos(game->player->x()+100, game->player->y());
            } else game->player->setPos(game->scene->width() - game->player->boundingRect().width(), game->player->y());

            delete this;
            return;
        }
    }

    if (x() - boundingRect().width() < 0 || x() > game->scene->width()
            || y() < 0 || y() > game->scene->height()) {
        delete this;
    }
}
