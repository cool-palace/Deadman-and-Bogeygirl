#include "npc.h"
#include "game.h"
#include "bullet.h"
#include <QtMath>

extern Game * game;

GameObject::GameObject(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {}

void GameObject::random_movement() {
    qreal theta = static_cast<qreal>(rand() % 360);
    qreal x_diff = 20 * qSin(qDegreesToRadians(theta));
    qreal y_diff = 20 * qCos(qDegreesToRadians(theta));

    QPointF diff = {x_diff, y_diff};

    if (x()+x_diff < 0) {
        diff.setX(-x());
    }
    if (x()+x_diff > game->scene->width()) {
        diff.setX(game->scene->width() - boundingRect().width()*scale() - x());
    }
    if (y()+y_diff < 0) {
        diff.setY(-y());
    }
    if (y()+y_diff > game->scene->height()) {
        diff.setY(game->scene->height() - boundingRect().height()*scale() - y());
    }

    bool can_move = true;
    QPointF newPos = pos() + diff;
    QGraphicsRectItem * rect = new QGraphicsRectItem(newPos.x(), newPos.y(),
                                                     boundingRect().width()*scale(), boundingRect().height()*scale());
    game->scene->addItem(rect);
    rect->hide();

    QList<QGraphicsItem *> colliding_items = rect->collidingItems();

    if (colliding_items.size() > 1) {
        for (int i = 1, n = colliding_items.size(); i < n; ++i) {
            if (dynamic_cast<Cave*>(colliding_items[i])) {
                can_move = false;
            }
        }
    }
    delete rect;

    if (can_move) setPos(newPos);
}

Enemy::Enemy(QGraphicsItem *parent) : GameObject(parent) {}

Cave::Cave(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/cave.png"));
}

bool Cave::interact() {
    game->player->setImmobile();
    return true;
}

Couple::Couple(QGraphicsItem *parent): GameObject(parent) {
    setPixmap(QPixmap(":/images/couple-sprite.png"));
}

bool Couple::interact() {
    game->player->setImmobile();
    if (game->progress == Game::SECOND_RIDDLE_SOLVED) {
        game->dialogbox->getBox(Game::coupleSeqStart,Game::coupleSeqStart+7);
    }
    return true;
}

Deadman::Deadman(QGraphicsItem *parent): GameObject(parent) {
    if (game->progress != Game::START && game->progress != Game::OUTSIDE_EMPTINESS_DISCOVERED
            && game->progress != Game::DEADMANS_FAREWELL) {
        setPixmap(QPixmap(":/images/deadman-sprite.png"));
    } else if (game->progress == Game::START) {
        setPixmap(QPixmap(":/images/dirt.png"));
    } else setPixmap(QPixmap(":/images/deadman-alive-sprite.png"));
}

bool Deadman::interact() {
    game->player->setImmobile();
    switch (game->progress) {
    case Game::START:
        game->deadman->setPixmap(QPixmap(":/images/deadman-sprite.png"));
        game->deadman->setPos(game->scene->width()/2 - game->deadman->boundingRect().width()/2, 100);
        game->dialogbox->getBox(Game::deadmanSeq1Start+4,Game::deadmanSeq1Start+30);
        break;
    case Game::DOG_QUEST_COMPLETE:
        game->dialogbox->getBox(Game::deadmanSeq2Start,Game::deadmanSeq2Start+4);
        break;
    case Game::UNICORN_QUEST_COMPLETE:
        game->dialogbox->getBox(Game::deadmanSeq3Start,Game::deadmanSeq3Start);
        break;
    case Game::DANCE_QUEST_COMPLETE:
        game->dialogbox->getBox(Game::deadmanSeq4Start,Game::deadmanSeq4Start);
        break;
    case Game::SNAKES_DEFEATED:
        game->dialogbox->getBox(Game::deadmanSeq5Start,Game::deadmanSeq5Start+9);
        break;
    case Game::TREE_QUEST_COMPLETE:
        game->dialogbox->getBox(Game::deadmanSeq6Start,Game::deadmanSeq6Start);
        break;
    case Game::PHILOPHOBE_QUEST_COMPLETE:
        game->dialogbox->getBox(Game::deadmanSeq7Start,Game::deadmanSeq7Start+1);
        break;
    case Game::WITCH_DEFEATED:
        game->dialogbox->getBox(Game::deadmanSeq8Start,Game::deadmanSeq8Start+10);
        break;
    default:
        break;
    }
    return true;
}

Dog::Dog(QGraphicsItem *parent): GameObject(parent) {
    setPixmap(QPixmap(":/images/dog-sprite.png"));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);
}

Dog::~Dog() {
    delete timer;
}

bool Dog::interact() {
    return true;
}

void Dog::move() {
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<Player*>(colliding_items[i]) || dynamic_cast<Kids*>(colliding_items[i])) {
            game->dialogbox->getBox(Game::kidsSeqStart+11,Game::kidsSeqStart+15);
            setParentItem(game->player);;
            setPos(-69,30);
            disconnect(timer,SIGNAL(timeout()),this,SLOT(move()));
            return;
        }
    }
    random_movement();
}

Entrance::Entrance(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/cave-entrance.png"));
}

bool Entrance::interact() {
    switch (game->progress) {
    case Game::DOG_QUEST_STARTED: case Game::SNAKE_FIGHT_STARTED: case Game::FIFTH_RIDDLE_SOLVED:
        game->player->setImmobile();
        return true;
    default:
        emit game->player->goingIn();
        return false;
    }
}

Exit::Exit(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/exit.png"));
}

bool Exit::interact() {
    emit game->player->goingOut();
    return false;
}

Kids::Kids(QGraphicsItem *parent): GameObject(parent) {
    setPixmap(QPixmap(":/images/kids-sprite.png"));
}

bool Kids::interact() {
    if (game->player->childItems().empty()) {
        game->player->setImmobile();
        game->dialogbox->getBox(Game::kidsSeqStart,Game::kidsSeqStart+10);
    }
    return true;
}

Portal::Portal(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/portal.png"));
}

bool Portal::interact() {
    switch (game->progress) {
    case Game::FIFTH_RIDDLE_SOLVED:
        game->player->setImmobile();
        game->dialogbox->getBox(Game::deadmanSeq7Start+3,Game::deadmanSeq7Start+25);
        break;
    case Game::WITCH_DEFEATED:
        game->player->setImmobile();
        break;
    case Game::DEADMANS_FAREWELL:
        game->displayMainMenu();
        return false;
    default:
        break;
    }
    return true;
}

RedWhite::RedWhite(QGraphicsItem *parent): GameObject(parent) {
    setPixmap(QPixmap(":/images/kb.png"));
}

bool RedWhite::interact() {
    game->player->setImmobile();
    if (game->progress == Game::DOG_QUEST_STARTED) {
        game->dialogbox->getBox(Game::kidsSeqStart+16,Game::kidsSeqStart+17);
    }
    return true;
}

Snake::Snake(int id, QGraphicsItem *parent): Enemy(parent), id(id) {
    QString str = ":/images/snake-%1-sprite.png";
    setPixmap(QPixmap(str.arg(id+1)));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

Snake::~Snake() {
    delete timer;
}

bool Snake::interact() {
    if (!moving && !dead) {
        game->player->setImmobile();
        game->dialogbox->getBox(Game::snakeSeqStart,Game::snakeSeqStart+14);
    } else if (dead) {
        game->dialogbox->getBox(Game::snakeSeqStart+16+id,Game::snakeSeqStart+16+id);
    }
    return true;
}

int Snake::shotCount = 0;

void Snake::start() {
    timer->start(100);
    moving = true;
}

void Snake::move() {
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<Player*>(colliding_items[i])){
            game->dialogbox->getBox(Game::snakeSeqStart+15,Game::snakeSeqStart+15);
            setPos(x()+rand()%100, y()+rand()%100);
            return;
        }
    }
    random_movement();
}

void Snake::shot() {
    if (!dead) {
        QString str = ":/images/snake-%1-shot.png";
        setPixmap(QPixmap(str.arg(id+1)));
        moving = false;
        dead = true;
        disconnect(timer,SIGNAL(timeout()),this,SLOT(move()));
        ++shotCount;
        if (Snake::shotCount == 2) game->dialogbox->getBox(Game::snakeSeqStart+18, Game::snakeSeqStart+18);
    }
}

Thinker::Thinker(QGraphicsItem *parent): GameObject(parent) {
    setPixmap(QPixmap(":/images/thinker-sprite.png"));
}

bool Thinker::interact() {
    game->player->setImmobile();
    if (game->progress == Game::FOURTH_RIDDLE_SOLVED) {
        game->dialogbox->getBox(Game::thinkerSeqStart,Game::thinkerSeqStart+10);
    }
    return true;
}

Tree::Tree(QGraphicsItem *parent): GameObject(parent) {
    setPixmap(QPixmap(":/images/kalina-sprite.png"));
}

bool Tree::interact() {
    game->player->setImmobile();
    if (game->progress == Game::AFTER_SNAKES_DIALOG_OVER) {
        game->dialogbox->getBox(Game::kalinaSeqStart,Game::kalinaSeqStart+6);
    }
    return true;
}

Unicorn::Unicorn(QGraphicsItem *parent) : GameObject(parent) {
    setPixmap(QPixmap(":/images/unicorn-sprite.png"));
}

bool Unicorn::interact() {
    game->player->setImmobile();
    if (game->progress == Game::FIRST_RIDDLE_SOLVED) {
        game->dialogbox->getBox(Game::unicornSeqStart,Game::unicornSeqStart+3);
    }
    return true;
}

Witch::Witch(QGraphicsItem *parent): Enemy(parent) {
    setPixmap(QPixmap(":/images/witch-sprite.png"));
    move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    shoot_timer = new QTimer(this);
    connect(shoot_timer,SIGNAL(timeout()),this,SLOT(shoot()));
    hurt_timer = new QTimer(this);
    hurt_timer->setSingleShot(true);
    connect(hurt_timer,SIGNAL(timeout()),this,SLOT(recover()));
}

Witch::~Witch() {
    delete move_timer;
    delete shoot_timer;
    delete hurt_timer;
}

bool Witch::interact() {

    return true;
}

void Witch::start() {
    move_timer->start(100);
    shoot_timer->start(1000);
}

void Witch::move() {
if (direction_up) {
        if (pos().y() - step > 0) {
           setPos(pos().x(), pos().y() - step);
        } else {
            setPos(pos().x(), 0);
            direction_up = false;
        }
    } else if (pos().y() + step + boundingRect().height() < game->scene->height()) {
        setPos(pos().x(), pos().y() + step);
     } else {
         setPos(pos().x(), game->scene->height() - boundingRect().height());
         direction_up = true;
     }

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0; i < colliding_items.size(); ++i) {
        if (dynamic_cast<Player*>(colliding_items.value(i))) {
            colliding_items[i]->setPos(game->scene->width() - colliding_items[i]->boundingRect().width(), colliding_items[i]->y());
        }
    }
}

void Witch::shoot() {
     Spell * spell = new Spell();
     spell->setPos(x()+boundingRect().width() - 50,y()+boundingRect().height()/2);
     game->scene->addItem(spell);
}

void Witch::shot() {
    lives -= game->progress == Game::DEADMAN_REVIVED ? 1 : 0;

    if (lives > 0) {
        setPixmap(QPixmap(":/images/witch-hurt.png"));
        hurt_timer->start(50);
    } else {
        game->progress = Game::WITCH_DEFEATED;
        delete this;
        game->deadman->show();
    }
}

void Witch::recover() {
     setPixmap(QPixmap(":/images/witch-sprite.png"));
}
