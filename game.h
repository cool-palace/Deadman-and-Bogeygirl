#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "deadman.h"
#include "dialogbox.h"

#include <QVector>
#include <riddle.h>
//#include "Score.h"
//#include "Health.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget * parent=0);

    // public methods
    void displayMainMenu();

    // public attributes
    QGraphicsScene * scene;
    Player * player;
    Deadman * deadman;
    DialogBox * dialogbox;
//    QGraphicsTextItem * line;
//    QGraphicsPixmapItem * avatar;

    QVector<Riddle> riddles =
        {{"Две средние цифры года твоего рождения, повторённые дважды", "0000"}};

public slots:
    void start();
    void asmr();

};

#endif // GAME_H
