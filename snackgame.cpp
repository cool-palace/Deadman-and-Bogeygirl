#include "snackgame.h"
#include <QDebug>
#include "game.h"

extern Game * game;

Snack::Snack(int id, QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent) {
    QString str = ":/images/syrok-small-%1.png";
    setPixmap(QPixmap(str.arg(id+1)));
    switch (id) {
    case 0:
        taste = 4;
        break;
    case 1:
        taste = 2;
        break;
    case 2:
        taste = 1;
        break;
    case 3:
        taste = 5;
        break;
    case 4:
        taste = 3;
        break;
    }
    setAcceptHoverEvents(true);
}

void Snack::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    setPos(mapToScene(event->pos() + m_shiftMouseCoords));
}

void Snack::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_shiftMouseCoords = pos() - mapToScene(event->pos());
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void Snack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Snack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    if (last_taste == 0) {
        emit degustation(Game::kalinaSeqStart+7,Game::kalinaSeqStart+7);
    } else {
        int taste_diff = taste - last_taste;
        emit degustation(taste_diff+Game::kalinaSeqStart+12,taste_diff+Game::kalinaSeqStart+12);
    }
    last_taste = taste;
}

void Snack::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Snack::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
}

int Snack::last_taste = 0;

SnackGame::SnackGame(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/bg.png"));

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    cond_bg = new QGraphicsRectItem(this);
    cond_bg->setRect(50,30, 700, 100);
    cond_bg->setBrush(brush);

    conditions = new QGraphicsTextItem(this);
    QString cond = "Попробуй сырки двойным кликом и расположи их в порядке улучшения вкуса. При этом вкусовые ощущения от каждого сырка будут зависеть<br>от того, какой из них ты попробовала последним.";
    QString str1 = "<p style=\"text-align:center;\">%1</p>";
    conditions->setHtml(str1.arg(cond));
    conditions->setFont({"Calibri", 14});
    conditions->setTextWidth(700);
    conditions->setPos(50,40);

    for (int i = 0; i < 5; ++i) {
        int offset = 110;
        snacks[i] = new Snack(i, this);
        snacks[i]->setPos(i*120+offset,150+50);
        snacks[i]->setZValue(10);

        offset = 20;
        snack_slots[i] = new QGraphicsRectItem(this);
        snack_slots[i]->setRect(i*156+offset,300+20, 136, 100);
        snack_slots[i]->setBrush(brush);

        number[i] = new QGraphicsTextItem(this);
        QString str = "<p style=\"text-align:center;\">#%1</p>";
        number[i]->setHtml(str.arg(5 - i));
        number[i]->setFont({"Calibri", 30});
        number[i]->setTextWidth(136);
        number[i]->setPos(i*156+offset,320+20);

        connect(snacks[i],SIGNAL(degustation(int, int)),game->dialogbox,SLOT(getBox(int, int)));
    }

    confirmButton = new Button("Готово",this);
    confirmButton->setPos(boundingRect().width()/2 - confirmButton->boundingRect().width()/2, 475);

    connect(confirmButton,SIGNAL(clicked()),this,SLOT(checkAnswer()));

    correctSound = new QMediaPlayer();
    correctSound->setMedia(QUrl("qrc:/sounds/correct.wav"));

    wrongSound = new QMediaPlayer();
    wrongSound->setMedia(QUrl("qrc:/sounds/wrong.wav"));
}

SnackGame::~SnackGame() {
    delete cond_bg;
    delete conditions;
    delete confirmButton;
    delete correctSound;
    delete wrongSound;

    for (int i = 0; i < 5; ++i) {
        delete snacks[i];
        delete snack_slots[i];
        delete number[i];
    }
}

void SnackGame::checkAnswer() {
    bool all_placed = true;

    for (int i = 0; i < 5; ++i) {
        QList<QGraphicsItem *> colliding_items = snack_slots[i]->collidingItems();
        for (int j = 0; j < colliding_items.size(); ++j) {
            if (colliding_items[j]->zValue() < 10) {
                colliding_items.removeAt(j);
                --j;
            }
        }
        if (colliding_items.size() == 0) {
            emit result(Game::kalinaSeqStart+17,Game::kalinaSeqStart+17);
            all_placed = false;
            return;
        } else if (colliding_items.size() > 1) {
            emit result(Game::kalinaSeqStart+18,Game::kalinaSeqStart+18);
            all_placed = false;
            return;
        }
    }

    if (!all_placed) return;

    if (snack_slots[0]->collidesWithItem(snacks[2])
            && snack_slots[1]->collidesWithItem(snacks[1])
            && snack_slots[2]->collidesWithItem(snacks[4])
            && snack_slots[3]->collidesWithItem(snacks[0])
            && snack_slots[4]->collidesWithItem(snacks[3])) {
        emit result(Game::kalinaSeqStart+20,Game::kalinaSeqStart+20);
        correctSound->play();
        return;
    }
    emit result(Game::kalinaSeqStart+19,Game::kalinaSeqStart+19);
    wrongSound->play();
}
