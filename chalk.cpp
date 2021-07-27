#include "chalk.h"
#include "game.h"
#include <qmath.h>

extern Game * game;

Chalk::Chalk(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/asmr.png"));
    cracks = new QGraphicsPixmapItem(this);
    cracks->setPixmap(QPixmap(":/images/cracks.png"));
    cracks->setPos(0,5);
    cracks->setOpacity(0);

    game->music->setCurrentIndex(3);
    game->current_music->setVolume(30);
    game->current_music->play();

    setAcceptHoverEvents(true);
}

Chalk::~Chalk() {
    delete cracks;
}

void Chalk::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = start - mapToScene(event->pos());
    if (sqrt(p.x()*p.x() + p.y()*p.y()) > 300) {
        start = mapToScene(event->pos());

        game->crushSound[cracksCount]->play();

        if (cracksCount < 5) {
            if (cracksCount == 4) {
                int riddle_number = 0;
                switch (game->progress) {
                case Game::DOG_QUEST_COMPLETE:
                    riddle_number = 0;
                    game->dialogbox->getBox(Game::deadmanSeq2Start+6,Game::deadmanSeq2Start+8);
                    break;
                case Game::UNICORN_QUEST_COMPLETE:
                    riddle_number = 1;
                    break;
                case Game::DANCE_QUEST_COMPLETE:
                    riddle_number = 2;
                    break;
                case Game::TREE_QUEST_COMPLETE:
                    riddle_number = 3;
                    break;
                case Game::PHILOPHOBE_QUEST_COMPLETE:
                    riddle_number = 4;
                    break;
                default:
                    break;
                }
                emit cracked(&game->riddles[riddle_number]);
                delete this;
                return;
            }
            ++cracksCount;
            cracks->setOpacity((qreal)cracksCount/5);
        }
    }
}

void Chalk::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    start = mapToScene(event->pos());
    Q_UNUSED(event);
}

void Chalk::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::OpenHandCursor));
    Q_UNUSED(event);
}

void Chalk::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Chalk::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setCursor(QCursor(Qt::ArrowCursor));
}
