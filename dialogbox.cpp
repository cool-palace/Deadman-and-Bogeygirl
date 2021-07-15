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

    // if a dialog box is open, player can't move until she presses the space button
//    if (isVisible()) {
        if (event->key() == Qt::Key_Space) {
            if (start == end) {
                hide();
                ungrabKeyboard();
//                setEnabled(false);
//                this->clearFocus();
//                game->player->setFocus();
                qDebug() << "Hiding";
            } else {
                ++start;
                getBox(start, end);
            }
            //++currentLineIndex;
//            emit game->player->next(game->player->currentLineIndex);

            qDebug() << "Trying to get the next line";
            //game->dialogbox->hide();
        }
//        return;
//    }
}

//void DialogBox::showbox(Speechline* speechline) {
void DialogBox::getBox(int in_start, int in_end) {

    start = in_start;
    end = in_end;
//    QList<QGraphicsItem *> children = childItems();
//    for (int i = 0, n = children.size(); i < n; ++i) {
//        delete children[i];
//    }

//    QGraphicsTextItem * line = new QGraphicsTextItem(this);
//    QGraphicsPixmapItem * avatar = new QGraphicsPixmapItem(this);
//    line = new QGraphicsTextItem(this);
//    avatar = new QGraphicsPixmapItem(this);

//    avatar->setPixmap(QPixmap(speechline->speaker));
    avatar->setPixmap(QPixmap(game->speech[start].speaker));
    avatar->setPos(0,450);

//    line->setPlainText(speechline->line);
    line->setPlainText(game->speech[start].line);
    line->setDefaultTextColor(Qt::white);
    line->setPos(150, 450);
    line->setScale(2);
    line->setTextWidth(700/line->scale());

    show();
    grabKeyboard();
}

void DialogBox::hidebox() {
    game->player->currentLineIndex = 0;
    game->deadman->introduced = true;
    hide();
}

