#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "npc.h"
#include "dialogbox.h"
#include "chalk.h"
#include "riddlebox.h"
#include "cave.h"
#include <QVector>
#include <riddle.h>
#include "snackgame.h"
#include "dyegame.h"
#include "dancegame.h"
#include "voltorbgame.h"
#include "redwhite.h"

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
    Exit * exit;
    Cave * cave;
    Entrance * entrance;
    SnackGame * snackgame;
    DyeGame * dyegame;
    DanceGame * dancegame;
    VoltorbGame * voltorbgame;
    Tree * tree;
    Kids * kids;
    Dog * dog;
    RedWhite * kb;
    Unicorn * unicorn;
    Couple * couple;
    Thinker * thinker;
    Snake * snake[2];
    QVector<QMediaPlayer *> crushSound {5};

    enum Progress {
        START,
        INTRO_COMPLETE,
        DOG_QUEST_COMPLETE,
        FIRST_RIDDLE_SOLVED,
        UNICORN_QUEST_COMPLETE,
        SECOND_RIDDLE_SOLVED,
        DANCE_QUEST_COMPLETE,
        THIRD_RIDDLE_SOLVED,
        SNAKES_DEFEATED,
        AFTER_SNAKES_DIALOG_OVER,
        TREE_QUEST_COMPLETE,
        FOURTH_RIDDLE_SOLVED,
        PHILOPHOBE_QUEST_COMPLETE,
        FIFTH_RIDDLE_SOLVED,
        OUTSIDE_EMPTINESS_DISCOVERED,
        WITCH_DEFEATED
    };

    Progress progress = START;

    const static QVector<Riddle> riddles;

    const static QVector<Speechline> speech;

    constexpr static int worldSize = 2760;
    constexpr static int unicornSeqStart = 24;
    constexpr static int kalinaSeqStart = 41;
    constexpr static int coupleSeqStart = 63;
    constexpr static int thinkerSeqStart = 73;
    constexpr static int kidsSeqStart = 92;
    constexpr static int snakeSeqStart = 110;

public slots:
    void start();
    void asmr();
    void outside();
    void snacks_game();
    void dye_game();
    void dance_game();
    void voltorb_game();

};

#endif // GAME_H
