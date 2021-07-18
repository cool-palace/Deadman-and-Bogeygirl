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
#include "tree.h"
//#include "Score.h"
//#include "Health.h"

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
    Tree * tree;

//    QGraphicsTextItem * line;
//    QGraphicsPixmapItem * avatar;

    const static QVector<Riddle> riddles;

    const static QVector<Speechline> speech;

public slots:
    void start();
    void asmr();
    void outside();
    void snacks_game();

};

#endif // GAME_H
