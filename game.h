#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "deadman.h"
#include "dialogbox.h"
#include "chalk.h"
#include "riddlebox.h"
#include "cave.h"
#include <QVector>
#include <riddle.h>
#include "snackgame.h"
#include "dyegame.h"
#include "dancegame.h"
#include "tree.h"
#include "kids.h"
#include "dog.h"
#include "redwhite.h"
#include "unicorn.h"
#include "couple.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget * parent=0);

    // public methods
    void displayMainMenu();
//    void keyPressEvent(QKeyEvent * event);

    // public attributes
    QGraphicsScene * scene;
    Player * player;
    Deadman * deadman;
    DialogBox * dialogbox;
    Chalk * chalk;
    RiddleBox * riddlebox;
    QPointF currentViewPos = {0, 0};
    QGraphicsPixmapItem * exit;
    Cave * cave;
    SnackGame * snackgame;
    DyeGame * dyegame;
    DanceGame * dancegame;
    Tree * tree;
    Kids * kids;
    Dog * dog[1];
    RedWhite * kb;
    Unicorn * unicorn;
    Couple * couple;

//    QGraphicsTextItem * line;
//    QGraphicsPixmapItem * avatar;

    const static QVector<Riddle> riddles;

    const static QVector<Speechline> speech;
    constexpr static int unicornSeqStart = 24;
    constexpr static int kalinaSeqStart = 34;
    constexpr static int coupleSeqStart = 55;


public slots:
    void start();
    void asmr();
    void outside();
    void snacks_game();
    void dye_game();
    void dance_game();

};

#endif // GAME_H
