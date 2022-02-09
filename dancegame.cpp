#include "dancegame.h"
#include "game.h"
#include <QDebug>

extern Game * game;

DanceGame::DanceGame(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/bg.png"));

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    cond_bg = new QGraphicsRectItem(this);
    cond_bg->setRect(50,30, 700, 100);
    cond_bg->setBrush(brush);

    conditions = new QGraphicsTextItem(this);
    QString cond = "Чтобы танцевать, нажимай на стрелки на клавиатуре в такт ритму, подсвечивающиеся подсказки указывают правильное направление.<br>Для полного танца нужно набрать 16 очков.";
    QString str1 = "<p style=\"text-align:center;\">%1</p>";
    conditions->setHtml(str1.arg(cond));
    conditions->setFont({"Calibri", 14});
    conditions->setTextWidth(700);
    conditions->setPos(50,40);

    sprite = new QGraphicsPixmapItem(this);
    sprite->setPixmap(QPixmap(":/images/player-left.png"));
    pxPos = static_cast<int>(game->scene->width()/2 - sprite->boundingRect().width()*sprite->scale()/2);
    pyPos = static_cast<int>(game->scene->height()/2 - sprite->boundingRect().height()*sprite->scale()/2);
    sprite->setPos(pxPos,pyPos);

    score_bg = new QGraphicsRectItem(this);
    score_bg->setRect(game->scene->width()/2 - 50,475, 100, 30);
    score_bg->setBrush(brush);

    score = new QGraphicsTextItem(this);
    score->setHtml(score_str.arg(correctCount));
    score->setPos(game->scene->width()/2 - 50,475);
    score->setTextWidth(100);
    score->setFont({"Calibri", 14});

    int dir_w, dir_h, dxPos, dyPos;
    int off = 30;
    int wid = 150;
    int hei = 50;

    for (int i = 0; i < 4; ++i) {
        directions[i] = new QGraphicsRectItem(this);
        switch (i) {
        case 0:
            dir_w = wid;
            dir_h = hei;
            dxPos = static_cast<int>(game->scene->width()/2 - wid/2);
            dyPos = static_cast<int>(game->scene->height()/2 - wid/2 - off - dir_h);
            break;
        case 1:
            dir_w = wid;
            dir_h = hei;
            dxPos = static_cast<int>(game->scene->width()/2 - wid/2);
            dyPos = static_cast<int>(game->scene->height()/2 + wid/2 + off);
            break;
        case 2:
            dir_w = hei;
            dir_h = wid;
            dxPos = static_cast<int>(game->scene->width()/2 - wid/2 - off - dir_w);
            dyPos = static_cast<int>(game->scene->height()/2 - wid/2);
            break;
        default: // case 3:
            dir_w = hei;
            dir_h = wid;
            dxPos = static_cast<int>(game->scene->width()/2 + wid/2 + off);
            dyPos = static_cast<int>(game->scene->height()/2 - wid/2);
            break;
        }
        directions[i]->setRect(dxPos,dyPos,dir_w,dir_h);
        directions[i]->setBrush(brush);
    }

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(change()));
    timer->start(500);

    correctSound = new QMediaPlayer();
    correctSound->setMedia(QUrl("qrc:/sounds/correct.wav"));
    wrongSound = new QMediaPlayer();
    wrongSound->setMedia(QUrl("qrc:/sounds/wrong.wav"));

    setEnabled(true);
    grabKeyboard();
}

DanceGame::~DanceGame() {
    disconnect(timer,SIGNAL(timeout()),this,SLOT(change()));
    delete sprite;
    delete cond_bg;
    delete conditions;
    delete score;
    delete timer;
    delete correctSound;
    delete wrongSound;

    for (int i = 0; i < 4; ++i) {
        delete directions[i];
    }
}

void DanceGame::keyPressEvent(QKeyEvent * event) {
    if (sprite->x() != pxPos || sprite->y() != pyPos) return;
    bool correct = false;

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        sprite->setPos(sprite->x()-20, sprite->y());
        correct = tact == 2 || tact == 6 || tact == 9 || tact == 13;
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        sprite->setPos(sprite->x()+20, sprite->y());
        correct = tact == 3 || tact == 7 || tact == 11 || tact == 15;
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
        sprite->setPos(sprite->x(), sprite->y()-20);
        correct = tact == 0 || tact == 4 || tact == 8 || tact == 12;
    } else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
        sprite->setPos(sprite->x(), sprite->y()+20);
        correct = tact == 1 || tact == 5 || tact == 10 || tact == 14;
    }

    if (correct) {
        ++correctCount;
        moved_in_this_tact = true;
    } else {
        correctCount = 0;
        wrongSound->play();
    }
    score->setHtml(score_str.arg(correctCount));

    if (correctCount == 16) {
        emit result(Game::coupleSeqStart+8,Game::coupleSeqStart+8);
        correctSound->play();
    }
}

void DanceGame::change() {
    if (!moved_in_this_tact) {
        correctCount = 0;
        score->setHtml(score_str.arg(correctCount));
    }
    moved_in_this_tact = false;

    if (tact < 15) {
        ++tact;
    } else tact = 0;

    brush.setColor(QColor(255,174,201,100));
    for (int i = 0; i < 4; ++i) {
        directions[i]->setBrush(brush);
    }

    sprite->setPos(pxPos,pyPos);

    brush.setColor(QColor(255,174,201,255));

    switch(tact) {
    case 0: case 4: case 8: case 12:
        directions[0]->setBrush(brush);
        break;
    case 1: case 5: case 10: case 14:
        directions[1]->setBrush(brush);
        break;
    case 2: case 6: case 9: case 13:
        directions[2]->setBrush(brush);
        break;
    case 3: case 7: case 11: case 15:
        directions[3]->setBrush(brush);
        break;
    }
}
