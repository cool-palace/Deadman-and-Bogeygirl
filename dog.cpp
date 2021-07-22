#include "dog.h"
#include "game.h"
#include "qmath.h"

extern Game * game;

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

Snake::Snake(int id, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
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

void Snake::start() {
    // start the timer
    timer->start(100);
}

void Snake::move(){

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (dynamic_cast<Player*>(colliding_items[i])){
            emit game->player->dialogCall(Game::kidsSeqStart+11,Game::kidsSeqStart+11);
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
