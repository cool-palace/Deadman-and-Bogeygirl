#include "dialogbox.h"
#include "game.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QKeyEvent>
#include <QDebug>

extern Game * game; // there is an external global object called game

DialogBox::DialogBox(QGraphicsItem * parent) : QObject(), QGraphicsRectItem (parent)
{
    // set the brush
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);

//    QGraphicsRectItem * background = new QGraphicsRectItem(this);
//    QGraphicsPixmapItem * avatar = new QGraphicsPixmapItem(this);
//    QGraphicsTextItem * line = new QGraphicsTextItem(this);

    // set backgroung
//    background->setRect(0,450,800,150);
//    background->setBrush(brush);

    setRect(0,450,800,150);
    setBrush(brush);

//    // set avatar
//    avatar->setPixmap(QPixmap(speechline->speaker));
//    avatar->setPos(0,450);

//    // set text
//    line->setPlainText(speechline->line);
//    line->setDefaultTextColor(Qt::white);
//    line->setPos(150, 450);
//    line->setScale(2);
//    line->setTextWidth(700/line->scale());

//    // composing
//    addToGroup(background);
//    addToGroup(avatar);
//    addToGroup(line);

//    delete avatar;
//    delete line;
    hide();
}

void DialogBox::showbox(Speechline* speechline) {
    hide();
    QList<QGraphicsItem *> children = childItems();
    for (int i = 0, n = children.size(); i < n; ++i) {
        delete children[i];
    }

    QGraphicsTextItem * line = new QGraphicsTextItem(this);
    QGraphicsPixmapItem * avatar = new QGraphicsPixmapItem(this);

    avatar->setPixmap(QPixmap(speechline->speaker));
    avatar->setPos(0,450);

    line->setPlainText(speechline->line);
    line->setDefaultTextColor(Qt::white);
    line->setPos(150, 450);
    line->setScale(2);
    line->setTextWidth(700/line->scale());

    show();
}

void DialogBox::hidebox() {
    game->player->currentLineIndex = 0;
    hide();
}

