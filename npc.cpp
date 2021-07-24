#include "npc.h"
#include "game.h"
#include "bullet.h"
#include "qmath.h"

extern Game * game;

Couple::Couple(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/couple.png"));
}

Deadman::Deadman(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    if (game->progress != Game::START && game->progress != Game::OUTSIDE_EMPTINESS_DISCOVERED) {
        setPixmap(QPixmap(":/images/deadman.png"));
    } else if (game->progress == Game::START) {
        setPixmap(QPixmap(":/images/dirt.png"));
    } else setPixmap(QPixmap(":/images/deadman.png"));
}

Dog::Dog(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/dog.png"));

    // make/connect a timer to move() the bullet every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(100);
}

Dog::~Dog(){
    delete timer;
}

void Dog::move(){

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<Player*>(colliding_items[i]) || dynamic_cast<Kids*>(colliding_items[i])){
            emit game->player->dialogCall(Game::kidsSeqStart+11,Game::kidsSeqStart+15);
            this->setParentItem(game->player);;
            setPos(-69,30);
            disconnect(timer,SIGNAL(timeout()),this,SLOT(move()));
            return;
        }
    }

    int theta = rand() % 360;
    double x_diff = 20 * qSin(qDegreesToRadians((double) theta));
    double y_diff = 20 * qCos(qDegreesToRadians((double) theta));

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

    colliding_items = rect->collidingItems();

    if (colliding_items.size() > 1) {
        for (int i = 1, n = colliding_items.size(); i < n; ++i){

            if (dynamic_cast<Cave*>(colliding_items[i])) {
                can_move = false;
            }
        }
    }
    delete rect;

    if (can_move) setPos(newPos);
}

Kids::Kids(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/kids.png"));
}

Snake::Snake(int id, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent), id(id)
{
    QString str = ":/images/snake-%1.png";
    setPixmap(QPixmap(str.arg(id+1)));

    // make/connect a timer to move() the bullet every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

Snake::~Snake(){
    delete timer;
}

int Snake::shotCount = 0;

void Snake::start() {
    // start the timer
    timer->start(100);
    moving = true;
}

void Snake::move(){

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<Player*>(colliding_items[i])){
            emit game->player->dialogCall(Game::snakeSeqStart+15,Game::snakeSeqStart+15);
            setPos(x()+rand()%100, y()+rand()%100);
            return;
        }
    }

    int theta = rand() % 360;
    double x_diff = 20 * qSin(qDegreesToRadians((double) theta));
    double y_diff = 20 * qCos(qDegreesToRadians((double) theta));

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

    colliding_items = rect->collidingItems();

    if (colliding_items.size() > 1) {
        for (int i = 1, n = colliding_items.size(); i < n; ++i){

            if (dynamic_cast<Cave*>(colliding_items[i])) {
                can_move = false;
            }
        }
    }
    delete rect;

    if (can_move) setPos(newPos);
}

void Snake::shot() {
    if (!dead) {
        QString str = ":/images/snake-%1-shot.png";
        setPixmap(QPixmap(str.arg(id+1)));
        moving = false;
        dead = true;
        disconnect(timer,SIGNAL(timeout()),this,SLOT(move()));
        ++shotCount;
        if (Snake::shotCount == 2) emit game->player->dialogCall(Game::snakeSeqStart+18, Game::snakeSeqStart+18);
    }
}

Thinker::Thinker(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/thinker.png"));
}

Tree::Tree(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/kalina.png"));
}

Unicorn::Unicorn(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/unicorn.png"));
}

Witch::Witch(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/witch.png"));

    // make/connect a timer to move() the bullet every so often
    move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    shoot_timer = new QTimer(this);
    connect(shoot_timer,SIGNAL(timeout()),this,SLOT(shoot()));
    hurt_timer = new QTimer(this);
    hurt_timer->setSingleShot(true);
}

Witch::~Witch(){
    delete move_timer;
    delete shoot_timer;
    delete hurt_timer;
}

void Witch::start() {
    // start the timer
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
}

void Witch::shoot() {
     Spell * spell = new Spell();
     spell->setPos(x()+boundingRect().width() - 50,y()+boundingRect().height()/2);
     game->scene->addItem(spell);
}

void Witch::shot() {
     setPixmap(QPixmap(":/images/witch-hurt.png"));
     hurt_timer->start(50);
     connect(hurt_timer,SIGNAL(timeout()),this,SLOT(recover()));
}

void Witch::recover() {
     setPixmap(QPixmap(":/images/witch.png"));
}
