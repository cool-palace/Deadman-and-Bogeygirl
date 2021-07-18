#include "snackgame.h"
#include <QDebug>
#include "game.h"
#include "button.h"

extern Game * game;

SnackGame::SnackGame(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bg.png"));
    //QGraphicsRectItem ** snack_slots = new QGraphicsRectItem*[5];
    QGraphicsTextItem ** number = new QGraphicsTextItem * [5];
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    for (int i = 0; i < 5; ++i) {
        int offset = 110;
        snacks[i] = new Snack(i, this);
        snacks[i]->setPos(i*120+offset,150);
        snacks[i]->setZValue(10);

        offset = 20;
        snack_slots[i] = new QGraphicsRectItem(this);
        snack_slots[i]->setRect(i*156+offset,300, 136, 100);
        snack_slots[i]->setBrush(brush);

        number[i] = new QGraphicsTextItem(snack_slots[i]);
        QString str = "<p style=\"text-align:center;\">#%1</p>";
        number[i]->setHtml(str.arg(5 - i));
        number[i]->setFont({"Comic Sans", 30});
        number[i]->setTextWidth(136);
        number[i]->setPos(i*156+offset,320);
        number[i]->setZValue(11);

        connect(snacks[i],SIGNAL(degustation(int, int)),game->dialogbox,SLOT(getBox(int, int)));
    }

    Button * confirmButton = new Button("Готово",this);
    confirmButton->setPos(boundingRect().width()/2 - confirmButton->boundingRect().width()/2, 475);

    connect(confirmButton,SIGNAL(clicked()),this,SLOT(checkAnswer()));

}

void SnackGame::checkAnswer() {

    if (snack_slots[0]->collidesWithItem(snacks[2])
            && snack_slots[1]->collidesWithItem(snacks[1])
            && snack_slots[2]->collidesWithItem(snacks[4])
            && snack_slots[3]->collidesWithItem(snacks[0])
            && snack_slots[4]->collidesWithItem(snacks[3])) {
        emit result(16,16);
        qDebug() << "right";
        return;
    }
    emit result(15,15);
    qDebug() << "wrong";

}
