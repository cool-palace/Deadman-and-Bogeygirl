#include "voltorbgame.h"
#include "game.h"
#include <QDebug>

extern Game * game;

VoltorbGame::VoltorbGame(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bg.png"));

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,174,201,100));

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    pen.setBrush(Qt::white);

    cond_bg = new QGraphicsRectItem(this);
    cond_bg->setRect(50,30, 700, 100);
    cond_bg->setBrush(brush);

    conditions = new QGraphicsTextItem(this); //
    QString cond = "Открой все бонусные карточки левой кнопкой мыши и избегай бомб,<br>иначе все очки сбросятся. Цель — пройти три уровня.<br>Правой кнопкой можно помечать опасные или бесполезные карточки.";
    QString str1 = "<p style=\"text-align:center;\">%1</p>";
    conditions->setHtml(str1.arg(cond));
    conditions->setFont({"Comic Sans", 14});
    conditions->setTextWidth(700);
    conditions->setPos(50,40);

    score_bg = new QGraphicsRectItem(this);
    score_bg->setRect(50,150, 120, 90);
    score_bg->setBrush(brush);

    score = new QGraphicsTextItem(this);
    score->setHtml(score_str.arg(points));
    score->setPos(50,150);
    score->setTextWidth(120);
    score->setFont({"Comic Sans", 14});

    level_ind = new QGraphicsTextItem(this);
    level_ind->setHtml(level_str.arg(points));
    level_ind->setPos(50,200);
    level_ind->setTextWidth(120);
    level_ind->setFont({"Comic Sans", 14});

    offset_x = game->scene->width()/2 - 150 - 5 * 2;
    offset_y = 150;

    // Инициализируем исходные значения
    for (int i = 0; i < 5; ++i) {
        points_row[i] = 0;
        points_col[i] = 0;
        bombs_row[i] = 0;
        bombs_col[i] = 0;
    }

    // Создаём карты и учитываем очки и бомбы в них
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            card[i][j] = new Card(level, this);
            card[i][j]->setPos(j*65+offset_x,i*65+offset_y);

            if (card[i][j]->value > 0) {
                points_row[i] += card[i][j]->value;
                points_col[j] += card[i][j]->value;
                if (card[i][j]->value > 1) {
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

    // Создаём индикаторы
    ind_offset_x = game->scene->width()/2 + 150 + 5 * 3;
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
        bomb_indicator[i]->setFont({"Comic Sans", 14});

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
}

VoltorbGame::~VoltorbGame() {
    delete cond_bg;
    delete conditions;
    delete score_bg;
    delete score;
    delete level_ind;

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

void VoltorbGame::increaseScore(int val) {
    points *= val;
    score->setHtml(score_str.arg(points));

    --pointCardsLeft;
    if (pointCardsLeft == 0) open(val);
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
    } else {
        ++level;
        level_ind->setHtml(level_str.arg(level));
        result(Game::thinkerSeqStart+10+level, Game::thinkerSeqStart+10+level);
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
            if (card[i][j]->value == 0) disconnect(card[i][j],SIGNAL(explode(int)),this,SLOT(open(int)));
            if (card[i][j]->value > 0) disconnect(card[i][j],SIGNAL(pointCardOpen(int)),this,SLOT(increaseScore(int)));

            card[i][j]->change(level);

            if (card[i][j]->value > 0) {
                points_row[i] += card[i][j]->value;
                points_col[j] += card[i][j]->value;
                if (card[i][j]->value > 1) {
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
