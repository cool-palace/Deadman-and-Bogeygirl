#include "voltorbgame.h"
#include "game.h"
#include <QDebug>

extern Game * game;

Card::Card(int level, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    change(level);
}

void Card::change(int level) {
    setPixmap(QPixmap(":/images/tile.png"));
    flipped = false;
    flagged = false;

    if (level > 3) level = 3;
    int rng = rand() % 100;

    switch (level) {
    case 1:
        if (rng < 25) value = 0; // 25%
        else if (rng < 80 && rng >= 25) value = 1; // 55%
        else if (rng < 95 && rng >= 80) value = 2; // 15%
        else if (rng < 100 && rng >= 95) value = 3; // 5%
        break;
    case 2:
        if (rng < 25) value = 0; // 25%
        else if (rng < 70 && rng >= 25) value = 1; // 45%
        else if (rng < 90 && rng >= 70) value = 2; // 20%
        else if (rng < 100 && rng >= 90) value = 3; // 10%
        break;
    case 3:
        if (rng < 25) value = 0; // 25%
        else if (rng < 65 && rng >= 25) value = 1; // 40%
        else if (rng < 85 && rng >= 65) value = 2; // 20%
        else if (rng < 100 && rng >= 85) value = 3; // 15%
        break;
    }
    setAcceptHoverEvents(true);
}

void Card::flip() {
    flipped = true;
    setAcceptHoverEvents(false);
    QString str = ":/images/tile-%1.png";
    setPixmap(QPixmap(str.arg(value)));
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !flipped) {
        flip();
        if (value > 1) emit pointCardOpen(value);
        else if (value == 0) emit explode(value);
    } else if (event->button() == Qt::RightButton && !flipped) {
        if (!flagged) {
            flagged = true;
            setPixmap(QPixmap(":/images/tile-flag-yellow.png"));
        } else {
            flagged = false;
            setPixmap(QPixmap(":/images/tile-yellow.png"));
        }
    }
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    if (!flagged) {
        setPixmap(QPixmap(":/images/tile-yellow.png"));
    } else setPixmap(QPixmap(":/images/tile-flag-yellow.png"));
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    if (!flagged) {
        setPixmap(QPixmap(":/images/tile.png"));
    } else setPixmap(QPixmap(":/images/tile-flag.png"));
}

VoltorbGame::VoltorbGame(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/bg.png"));

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    pen.setBrush(Qt::white);

    cond_bg = new QGraphicsRectItem(this);
    cond_bg->setRect(50,30, 700, 100);
    cond_bg->setBrush(brush);

    conditions = new QGraphicsTextItem(this);
    QString cond = "???????????? ?????? ???????????????? ???????????????? ?????????? ?????????????? ???????? ?? ?????????????? ????????,<br>?????????? ?????? ???????? ??????????????????. ???????? ??? ???????????? ?????? ????????????.<br>???????????? ?????????????? ?????????? ???????????????? ?????????????? ?????? ?????????????????????? ????????????????.";
    QString str1 = "<p style=\"text-align:center;\">%1</p>";
    conditions->setHtml(str1.arg(cond));
    conditions->setFont({"Calibri", 14});
    conditions->setTextWidth(700);
    conditions->setPos(50,40);

    score_bg = new QGraphicsRectItem(this);
    score_bg->setRect(50,150, 120, 90);
    score_bg->setBrush(brush);

    score = new QGraphicsTextItem(this);
    score->setHtml(score_str.arg(points));
    score->setPos(50,150);
    score->setTextWidth(120);
    score->setFont({"Calibri", 14});

    level_ind = new QGraphicsTextItem(this);
    level_ind->setHtml(level_str.arg(points));
    level_ind->setPos(50,200);
    level_ind->setTextWidth(120);
    level_ind->setFont({"Calibri", 14});

    offset_x = static_cast<int>(game->scene->width()/2 - 150 - 5 * 2);
    offset_y = 150;

    // ???????????????????????????? ???????????????? ????????????????
    for (int i = 0; i < 5; ++i) {
        points_row[i] = 0;
        points_col[i] = 0;
        bombs_row[i] = 0;
        bombs_col[i] = 0;
    }

    // ?????????????? ?????????? ?? ?????????????????? ???????? ?? ?????????? ?? ??????
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            card[i][j] = new Card(level, this);
            card[i][j]->setPos(j*65+offset_x,i*65+offset_y);

            if (card[i][j]->val() > 0) {
                points_row[i] += card[i][j]->val();
                points_col[j] += card[i][j]->val();
                if (card[i][j]->val() > 1) {
                    ++pointCardsLeft;
                    connect(card[i][j],SIGNAL(pointCardOpen(int)),this,SLOT(increaseScore(int)));
                }
            } else {
                ++bombs_row[i];
                ++bombs_col[j];
                connect(card[i][j],SIGNAL(explode(int)),this,SLOT(open(int)));
            }
        }
    }

    // ?????????????? ????????????????????
    ind_offset_x = static_cast<int>(game->scene->width()/2 + 150 + 5 * 3);
    ind_offset_y = 5*65+offset_y;

    for (int i = 0; i < 10; ++i) {
        switch (i % 5) {
        case 0:
            brush.setColor(QColor(222,112,85,255));
            break;
        case 1:
            brush.setColor(QColor(69,167,70,255));
            break;
        case 2:
            brush.setColor(QColor(230,159,67,255));
            break;
        case 3:
            brush.setColor(QColor(55,146,245,255));
            break;
        case 4:
            brush.setColor(QColor(191,101,220,255));
            break;
        }

        point_indicator_bg[i] = new QGraphicsRectItem(this);
        point_indicator_bg[i]->setBrush(brush);
        point_indicator_bg[i]->setPen(pen);

        point_indicator[i] = new QGraphicsTextItem(this);
        point_indicator[i]->setTextWidth(58);
        point_indicator[i]->setFont({"Comic Sans", 14});

        bomb_indicator_bg[i] = new QGraphicsRectItem(this);
        bomb_indicator_bg[i]->setBrush(brush);
        bomb_indicator_bg[i]->setPen(pen);

        bomb_indicator[i] = new QGraphicsTextItem(this);
        bomb_indicator[i]->setTextWidth(58);
        bomb_indicator[i]->setFont({"Calibri", 14});

        bomb_pics[i] = new QGraphicsPixmapItem(this);
        bomb_pics[i]->setPixmap(QPixmap(":/images/bomb.png"));

        QString str = "<p style=\"text-align:right;\">%1</p>";

        if (i < 5) {
            point_indicator_bg[i]->setRect(ind_offset_x + 1,i*65+offset_y + 1,58,25);
            bomb_indicator_bg[i]->setRect(ind_offset_x + 1,i*65+offset_y+25+1,58,33);
            bomb_pics[i]->setPos(ind_offset_x + 2,i*65+offset_y+25+2);
            point_indicator[i]->setHtml(str.arg(points_row[i]));
            point_indicator[i]->setPos(ind_offset_x + 2,i*65+offset_y);
            bomb_indicator[i]->setHtml(str.arg(bombs_row[i]));
            bomb_indicator[i]->setPos(ind_offset_x + 2,i*65+offset_y+25+2);
        } else {
            point_indicator_bg[i]->setRect((i - 5)*65+offset_x+1,ind_offset_y+1,58,25);
            bomb_indicator_bg[i]->setRect((i - 5)*65+offset_x+1,ind_offset_y+25+1,58,33);
            bomb_pics[i]->setPos((i - 5)*65+offset_x+2,ind_offset_y+25+2);
            point_indicator[i]->setHtml(str.arg(points_col[i-5]));
            point_indicator[i]->setPos((i - 5)*65+offset_x+2,ind_offset_y);
            bomb_indicator[i]->setHtml(str.arg(bombs_col[i-5]));
            bomb_indicator[i]->setPos((i - 5)*65+offset_x+2,ind_offset_y+25+2);
        }
    }

    correctSound = new QMediaPlayer();
    correctSound->setMedia(QUrl("qrc:/sounds/correct.wav"));

    wrongSound = new QMediaPlayer();
    wrongSound->setMedia(QUrl("qrc:/sounds/wrong.wav"));
}

VoltorbGame::~VoltorbGame() {
    delete cond_bg;
    delete conditions;
    delete score_bg;
    delete score;
    delete level_ind;
    delete correctSound;
    delete wrongSound;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            delete card[i][j];
        }
    }

    for (int i = 0; i < 10; ++i) {
        delete bomb_indicator[i];
        delete bomb_indicator_bg[i];
        delete point_indicator[i];
        delete point_indicator_bg[i];
        delete bomb_pics[i];
    }
}

void VoltorbGame::increaseScore(int value) {
    points *= value;
    score->setHtml(score_str.arg(points));

    --pointCardsLeft;
    if (pointCardsLeft == 0) open(value);
}

void VoltorbGame::open(int value) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            card[i][j]->flip();
        }
    }

    if (value == 0) {
        pointCardsLeft = 0;
        points = 1;
        score->setHtml(score_str.arg(points));
        level = 1;
        level_ind->setHtml(level_str.arg(level));
        emit result(Game::thinkerSeqStart+11,Game::thinkerSeqStart+11);
        wrongSound->play();
    } else {
        ++level;
        level_ind->setHtml(level_str.arg(level));
        emit result(Game::thinkerSeqStart+10+level, Game::thinkerSeqStart+10+level);
        correctSound->play();
    }
}

void VoltorbGame::reset() {
    for (int i = 0; i < 5; ++i) {
        points_row[i] = 0;
        points_col[i] = 0;
        bombs_row[i] = 0;
        bombs_col[i] = 0;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (card[i][j]->val() == 0) disconnect(card[i][j],SIGNAL(explode(int)),this,SLOT(open(int)));
            if (card[i][j]->val() > 0) disconnect(card[i][j],SIGNAL(pointCardOpen(int)),this,SLOT(increaseScore(int)));

            card[i][j]->change(level);

            if (card[i][j]->val() > 0) {
                points_row[i] += card[i][j]->val();
                points_col[j] += card[i][j]->val();
                if (card[i][j]->val() > 1) {
                    ++pointCardsLeft;
                    connect(card[i][j],SIGNAL(pointCardOpen(int)),this,SLOT(increaseScore(int)));
                }
            } else {
                ++bombs_row[i];
                ++bombs_col[j];
                connect(card[i][j],SIGNAL(explode(int)),this,SLOT(open(int)));
            }
        }
    }

    QString str = "<p style=\"text-align:right;\">%1</p>";
    for (int i = 0; i < 10; ++i) {
        if (i < 5) {
            point_indicator[i]->setHtml(str.arg(points_row[i]));
            bomb_indicator[i]->setHtml(str.arg(bombs_row[i]));
        } else {
            point_indicator[i]->setHtml(str.arg(points_col[i-5]));
            bomb_indicator[i]->setHtml(str.arg(bombs_col[i-5]));
        }
    }
}
