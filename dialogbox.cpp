#include "dialogbox.h"
#include "game.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QKeyEvent>
#include <QDebug>

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

    avatar->setPos(0,450);

    line->setDefaultTextColor(Qt::white);
    line->setPos(150, 450);
    line->setScale(2);
    line->setTextWidth(700/line->scale());

    setEnabled(true);

    hide();
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
                emit snackgameCall();
                qDebug() << "Trying to get the chalk";
                break;
            case 4:
                // Закрыть загадку
                // Тут можно просто hide() в качестве альтернативы
                delete game->chalk;
                delete game->riddlebox;
                game->exit->show();
                break;
            case 16:
                // Зыкрыть сырки
                delete game->snackgame;
                game->scene->setSceneRect(0,0,2400,1800);
                game->setSceneRect(game->currentViewPos.x(),game->currentViewPos.y(),800,600);
                break;
            }



        } else {
            ++start;
            getBox(start, end);
        }
        qDebug() << "Trying to get the next line";
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
    avatar->setPos(xPos,yPos);

    line->setPlainText(game->speech[start].line);
    line->setDefaultTextColor(Qt::white);
    line->setPos(xPos+150,yPos);
    line->setScale(2);
    line->setTextWidth(700/line->scale());

    show();
    grabKeyboard();
    grabMouse();
}

