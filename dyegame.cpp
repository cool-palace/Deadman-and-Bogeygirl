#include "dyegame.h"
#include "game.h"
#include "button.h"
#include <QDebug>

extern Game * game;

DyeGame::DyeGame(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bg.png"));
    //QGraphicsRectItem ** snack_slots = new QGraphicsRectItem*[5];

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    int offset = 550;
    dye_slot = new QGraphicsRectItem(this);
    dye_slot->setRect(offset,140, 200, 300);
    dye_slot->setBrush(brush);

    QGraphicsRectItem * cond_bg = new QGraphicsRectItem(this);
    cond_bg->setRect(50,30, 700, 100);
    cond_bg->setBrush(brush);

    QGraphicsTextItem * conditions = new QGraphicsTextItem(this); //
    QString cond = "Всего флаконов с чернилами два, и они стоят рядом друг с другом.<br>При этом в крайних флаконах налито одно и то же,<br>а в самом большом и самом маленьком флаконах — разные жидкости.";
    QString str1 = "<p style=\"text-align:center;\">%1</p>";
    conditions->setHtml(str1.arg(cond));
    conditions->setFont({"Comic Sans", 14});
    conditions->setTextWidth(700);
    conditions->setPos(50,40);

    QGraphicsTextItem * text = new QGraphicsTextItem(dye_slot);
    QString str = "<p style=\"text-align:center;\">Найди чернила и помести их сюда.</p>";
    text->setHtml(str);
    text->setFont({"Comic Sans", 12});
    text->setTextWidth(180);
    text->setPos(offset+10,270);
    text->setZValue(11);

    for (int i = 0; i < 5; ++i) {
        int offset = 60;
        dyes[i] = new Dye(i, this);
        dyes[i]->setPos(i*90+offset,150);
        dyes[i]->setZValue(10);
    }

    Button * confirmButton = new Button("Готово",this);
    confirmButton->setPos(boundingRect().width()/2 - confirmButton->boundingRect().width()/2, 475);
    connect(confirmButton,SIGNAL(clicked()),this,SLOT(checkAnswer()));

    Button * resetButton = new Button("Сбросить",this);
    resetButton->setPos(600, 475);
    connect(resetButton,SIGNAL(clicked()),this,SLOT(reset()));

}

void DyeGame::checkAnswer() {

    QList<QGraphicsItem *> colliding_items = dye_slot->collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        qDebug() << colliding_items[i];
    }
    // Два объекта сталкиваются со слотом изначально, поэтому при правильном решении должно быть всего 4
    if (colliding_items.size() < 3) {
        emit result(28,28);
        return;
    }
    if (colliding_items.size() < 4) {
        emit result(29,29);
        return;
    }
    if (colliding_items.size() > 4) {
        emit result(30,30);
        return;
    }

    if (dyes[2]->collidesWithItem(dye_slot)
            && dyes[3]->collidesWithItem(dye_slot)) {
        emit result(32,32);
        qDebug() << "right";
        return;
    }
    emit result(31,31);
    qDebug() << "wrong";

}

void DyeGame::reset() {
    for (int i = 0; i < 5; ++i) {
        int offset = 60;
        dyes[i]->setPos(i*90+offset,150);
    }
}
