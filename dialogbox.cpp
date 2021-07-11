#include "dialogbox.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

DialogBox::DialogBox(QGraphicsItem * parent) : QObject(), QGraphicsItemGroup(parent)
{
    // set the brush
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);

    QGraphicsRectItem * background = new QGraphicsRectItem();
    QGraphicsPixmapItem * avatar = new QGraphicsPixmapItem;
    QGraphicsTextItem * line = new QGraphicsTextItem;
    // set backgroung
    background->setRect(0,450,800,150);
    background->setBrush(brush);

    // set avatar
    avatar->setPixmap(QPixmap(":/images/player.png"));
    avatar->setPos(0,450);

    // set text
    line->setPlainText("Hello\ngsd");
    line->setDefaultTextColor(Qt::white);
    line->setPos(150, 450);
    line->setScale(2);
    line->setTextWidth(700/line->scale());

    // composing
    addToGroup(background);
    addToGroup(avatar);
    addToGroup(line);

    hide();
}

void DialogBox::showbox() {
    show();
}
