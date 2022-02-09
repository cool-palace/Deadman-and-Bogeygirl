#include "dyegame.h"
#include "game.h"
#include <QDebug>

extern Game * game;

Dye::Dye(int id, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    QString str = ":/images/dye-small-%1.png";
    setPixmap(QPixmap(str.arg(id+1)));
    setAcceptHoverEvents(true);
}

void Dye::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos() + m_shiftMouseCoords));
}

void Dye::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    m_shiftMouseCoords = pos() - mapToScene(event->pos());
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void Dye::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
}

void Dye::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Dye::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
}

DyeGame::DyeGame(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/bg.png"));

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    int offset = 550;
    dye_slot = new QGraphicsRectItem(this);
    dye_slot->setRect(offset,140, 200, 300);
    dye_slot->setBrush(brush);

    cond_bg = new QGraphicsRectItem(this);
    cond_bg->setRect(50,30, 700, 100);
    cond_bg->setBrush(brush);

    conditions = new QGraphicsTextItem(this); //
    QString cond = "Всего флаконов с чернилами два, и они стоят рядом друг с другом.<br>При этом известно, что в крайних флаконах налито одно и то же,<br>а в самом большом и самом маленьком флаконах — разные жидкости.";
    QString str1 = "<p style=\"text-align:center;\">%1</p>";
    conditions->setHtml(str1.arg(cond));
    conditions->setFont({"Calibri", 14});
    conditions->setTextWidth(700);
    conditions->setPos(50,40);

    text = new QGraphicsTextItem(this);
    QString str = "<p style=\"text-align:center;\">Найди чернила и помести их сюда.</p>";
    text->setHtml(str);
    text->setFont({"Calibri", 12});
    text->setTextWidth(180);
    text->setPos(offset+10,270);

    for (int i = 0; i < 5; ++i) {
        int offset = 60;
        dyes[i] = new Dye(i, this);
        dyes[i]->setPos(i*90+offset,150);
        dyes[i]->setZValue(10);
    }

    confirmButton = new Button("Готово",this);
    confirmButton->setPos(boundingRect().width()/2 - confirmButton->boundingRect().width()/2, 475);
    connect(confirmButton,SIGNAL(clicked()),this,SLOT(checkAnswer()));

    resetButton = new Button("Сбросить",this);
    resetButton->setPos(600, 475);
    connect(resetButton,SIGNAL(clicked()),this,SLOT(reset()));

    correctSound = new QMediaPlayer();
    correctSound->setMedia(QUrl("qrc:/sounds/correct.wav"));

    wrongSound = new QMediaPlayer();
    wrongSound->setMedia(QUrl("qrc:/sounds/wrong.wav"));
}

DyeGame::~DyeGame() {
    delete dye_slot;
    delete cond_bg;
    delete conditions;
    delete text;
    delete confirmButton;
    delete resetButton;
    delete correctSound;
    delete wrongSound;

    for (int i = 0; i < 5; ++i) {
        delete dyes[i];
    }
}

void DyeGame::checkAnswer() {
    QList<QGraphicsItem *> colliding_items = dye_slot->collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (colliding_items[i]->zValue() < 10) {
            colliding_items.removeAt(i);
            --i;
        }
    }

    switch (colliding_items.size()) {
    case 0:
        emit result(Game::unicornSeqStart+4,Game::unicornSeqStart+4);
        break;
    case 1:
        emit result(Game::unicornSeqStart+5,Game::unicornSeqStart+5);
        break;
    case 2:
        if (dyes[2]->collidesWithItem(dye_slot) && dyes[3]->collidesWithItem(dye_slot)) {
            emit result(Game::unicornSeqStart+8,Game::unicornSeqStart+8);
            correctSound->play();
        } else {
            emit result(Game::unicornSeqStart+7,Game::unicornSeqStart+7);
            wrongSound->play();
        }
        break;
    default:
        emit result(Game::unicornSeqStart+6,Game::unicornSeqStart+6);
        break;
    }
}

void DyeGame::reset() {
    for (int i = 0; i < 5; ++i) {
        int offset = 60;
        dyes[i]->setPos(i*90+offset,150);
    }
}
