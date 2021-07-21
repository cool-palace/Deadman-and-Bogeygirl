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
}

void DialogBox::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Space) {
        if (start == end) {
            hide();
            game->player->setFocus();
            switch (end) {
            case 1:
                // Первый диалог
                //emit chalkCall();
//                emit snackgameCall();
//                qDebug() << "Trying to get the chalk";
                break;
            case 4:
                // Закрыть загадку
                // Тут можно просто hide() в качестве альтернативы
                delete game->chalk;
                delete game->riddlebox;
                game->exit->show();
                break;

            case 20:
                // Гуляем и ловим собак
                game->kids->setParentItem(game->player);
                game->kids->setScale(1);
                game->kids->setPos(20,3);
                for (int i = 0; i < 1; ++i) {
                    game->dog[i] = new Dog();
                    game->dog[i]->setPos(rand()%2400+180,rand()%1800+250);
                    game->scene->addItem(game->dog[i]);
                }
                break;
            case 21:
                game->kb->show();
                break;
            case 23: {
                QList<QGraphicsItem *> child_items = game->player->childItems();
                for (int i = 0; i < child_items.size(); ++i) {
                    child_items[i]->setParentItem(0);
                }
                break; }
            case 27:
                emit dyegameCall();
                break;
            case 32:
                // Закрыть красители
                delete game->dyegame;
                game->scene->setSceneRect(0,0,2760,2130);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                getBox(33,33);
                break;

            case Game::kalinaSeqStart+6:
                emit snackgameCall();
                break;

            case Game::kalinaSeqStart+19:
                // Зыкрыть сырки
                delete game->snackgame;
                game->scene->setSceneRect(0,0,2760,2130);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                getBox(Game::kalinaSeqStart+20,Game::kalinaSeqStart+20);
                break;

            case Game::coupleSeqStart+7:
                // Открыть танец
                emit dancegameCall();
                break;

            case Game::coupleSeqStart+8:
                // Закрыть танец
                disconnect(game->dancegame->timer,SIGNAL(timeout()),this,SLOT(game->dancegame->change()));
                delete game->dancegame;
                game->scene->setSceneRect(0,0,2760,2130);
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
//                disconnect(game->dancegame->timer,SIGNAL(timeout()),this,SLOT(game->dancegame->change()));
//                delete game->dancegame;
                game->scene->setSceneRect(0,0,2760,2130);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                getBox(Game::thinkerSeqStart+15,Game::thinkerSeqStart+18);
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
        line->setPlainText(game->speech[start].line);
        line->setPos(xPos+150,yPos+10);
    }

    show();
    grabKeyboard();
    grabMouse();
}

