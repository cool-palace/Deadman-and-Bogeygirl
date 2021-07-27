#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlaylist>
#include "player.h"
#include "npc.h"
#include "dialogbox.h"
//#include "dialogs.h"
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
    void save();

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
    Portal * portal;
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
    Witch * witch;
    QVector<QMediaPlayer *> crushSound {5};

    Button* playButton;
    Button* quitButton;
    Button* lastButton;

    QGraphicsPixmapItem * treasure_back;
    QGraphicsTextItem * treasure_text;

    QMediaPlaylist * music;
    QMediaPlayer * current_music;

    QTimer * timer;

    enum Progress {
        START,
        INTRO_COMPLETE,
        DOG_QUEST_STARTED,
        DOG_QUEST_COMPLETE,
        FIRST_RIDDLE_SOLVED,
        UNICORN_QUEST_COMPLETE,
        SECOND_RIDDLE_SOLVED,
        DANCE_QUEST_COMPLETE,
        THIRD_RIDDLE_SOLVED,
        SNAKE_FIGHT_STARTED,
        SNAKES_DEFEATED,
        AFTER_SNAKES_DIALOG_OVER,
        TREE_QUEST_COMPLETE,
        FOURTH_RIDDLE_SOLVED,
        PHILOPHOBE_QUEST_COMPLETE,
        FIFTH_RIDDLE_SOLVED,
        OUTSIDE_EMPTINESS_DISCOVERED,
        DEADMAN_REVIVED,
        WITCH_DEFEATED,
        DEADMANS_FAREWELL
    };

    Progress progress = START;

    const static QVector<Riddle> riddles;

    const static QVector<Speechline> speech;

    constexpr static int worldSize = 2760;

    constexpr static int deadmanSeq1Start = 0;
    constexpr static int kidsSeqStart = deadmanSeq1Start + 31;
    constexpr static int deadmanSeq2Start = kidsSeqStart + 19;
    constexpr static int unicornSeqStart = deadmanSeq2Start + 14;
    constexpr static int deadmanSeq3Start = unicornSeqStart + 18;
    constexpr static int coupleSeqStart = deadmanSeq3Start + 12;
    constexpr static int deadmanSeq4Start = coupleSeqStart + 10;
    constexpr static int snakeSeqStart = deadmanSeq4Start + 18;
    constexpr static int deadmanSeq5Start = snakeSeqStart + 19;
    constexpr static int kalinaSeqStart = deadmanSeq5Start + 10;
    constexpr static int deadmanSeq6Start = kalinaSeqStart + 22;
    constexpr static int thinkerSeqStart = deadmanSeq6Start + 11;
    constexpr static int deadmanSeq7Start = thinkerSeqStart + 19;
    constexpr static int witchSeqStart = deadmanSeq7Start + 28;
    constexpr static int deadmanSeq8Start = witchSeqStart + 26;

public slots:
    void start();
    void asmr();
    void outside();
    void snacks_game();
    void dye_game();
    void dance_game();
    void voltorb_game();
    void deadmans_note();
    void displayMainMenu();
};

#endif // GAME_H
