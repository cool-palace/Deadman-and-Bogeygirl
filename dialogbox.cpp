#include "dialogbox.h"
#include "game.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QKeyEvent>
#include <QDebug>
#include "redwhite.h"

extern Game * game; // there is an external global object called game

int DialogBox::start = 0;
int DialogBox::end = 0;

DialogBox::DialogBox(QGraphicsItem * parent) : QObject(), QGraphicsRectItem (parent)
{
    // set the brush
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);

    setRect(0,450,800,150);
    setBrush(brush);

    line = new QGraphicsTextItem(this);
    avatar = new QGraphicsPixmapItem(this);

    line->setDefaultTextColor(Qt::white);
    line->setFont({"Comic Sans", 16});
    line->setTextWidth(640);

    setEnabled(true);

    hide();
}

DialogBox::~DialogBox() {
    delete line;
    delete avatar;
    qDebug() << "db del";
}

void DialogBox::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Space) {
        if (start == end) {
            hide();
            game->player->setFocus();
            switch (end) {
            case 1:
                // Первый диалог
                emit chalkCall();
//                qDebug() << "Trying to get the chalk";
                break;
            case 4:
                // Закрыть загадку
                //game->exit->show();
                delete game->riddlebox;
//                game->riddlebox->hide();
                break;

            case Game::kidsSeqStart+10:
                // Гуляем и ловим собак
                game->kids->setParentItem(game->player);
                game->kids->setPos(60,9);
                for (int i = 0; i < 1; ++i) {
                    game->dog = new Dog();
                    game->dog->setPos(300,2000);
                    game->scene->addItem(game->dog);
                }
                break;

            case Game::kidsSeqStart+15:
                game->kb->show();
                break;

            case Game::kidsSeqStart+17: {
                QList<QGraphicsItem *> child_items = game->player->childItems();
                for (int i = 0; i < child_items.size(); ++i) {
                    child_items[i]->setParentItem(0);
                    child_items[i]->hide();
                }
                getBox(Game::kidsSeqStart+18,Game::kidsSeqStart+18);
                break; }

            case Game::unicornSeqStart+3:
                emit dyegameCall();
                break;
            case Game::unicornSeqStart+8:
                // Закрыть красители
                delete game->dyegame;
                game->scene->setSceneRect(0,0,Game::worldSize,Game::worldSize);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                getBox(Game::unicornSeqStart+9,Game::unicornSeqStart+16);
                break;

            case Game::kalinaSeqStart+6:
                emit snackgameCall();
                break;

            case Game::kalinaSeqStart+20:
                // Зыкрыть сырки
                delete game->snackgame;
                game->scene->setSceneRect(0,0,Game::worldSize,Game::worldSize);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                getBox(Game::kalinaSeqStart+21,Game::kalinaSeqStart+21);
                break;

            case Game::coupleSeqStart+7:
                // Открыть танец
                emit dancegameCall();
                break;

            case Game::coupleSeqStart+8:
                // Закрыть танец
                disconnect(game->dancegame->timer,SIGNAL(timeout()),this,SLOT(game->dancegame->change()));
                delete game->dancegame;
                game->scene->setSceneRect(0,0,Game::worldSize,Game::worldSize);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                getBox(Game::coupleSeqStart+9,Game::coupleSeqStart+9);
                break;

            case Game::thinkerSeqStart+10:
                // Открыть сапёра
                emit voltorbgameCall();
                break;

            case Game::thinkerSeqStart+11: case Game::thinkerSeqStart+12: case Game::thinkerSeqStart+13:
                // Открыть сапёра
                game->voltorbgame->reset();
                break;

            case Game::thinkerSeqStart+14:
                // Закрыть сапёра
                delete game->voltorbgame;
                game->scene->setSceneRect(0,0,Game::worldSize,Game::worldSize);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                getBox(Game::thinkerSeqStart+15,Game::thinkerSeqStart+18);
                break;

            case Game::snakeSeqStart+14:
                // Стреляем змей
                game->player->canShoot = true;
                for (int i = 0; i < 2; ++i) {
                    game->snake[i]->start();
                }
                break;
            }


        } else {
            ++start;
            getBox(start, end);
        }

    }
}

void DialogBox::getBox(int in_start, int in_end) {

    start = in_start;
    end = in_end;

    int xPos = 0, yPos = 450;

    if (game->scene->width() > 800) {
        xPos += game->player->x() + game->player->boundingRect().width()*game->player->scale() / 2 - game->sceneRect().width() / 2;
        yPos += game->player->y() + game->player->boundingRect().height()*game->player->scale() / 2 - game->sceneRect().height() / 2 +5;
        setRect(xPos,yPos,800,150);
    }

    avatar->setPixmap(QPixmap(game->speech[start].speaker));

    if (game->speech[start].speaker.contains("player")) {
        avatar->setPos(xPos+650,yPos);
        line->setHtml(right_aligned_str.arg(game->speech[start].line));
        line->setPos(xPos+10,yPos+10);
    } else {
        avatar->setPos(xPos,yPos);
        line->setHtml(game->speech[start].line);
        line->setPos(xPos+150,yPos+10);
    }

    show();
    grabKeyboard();
    grabMouse();
}

