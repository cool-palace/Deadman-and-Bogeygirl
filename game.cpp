#include "game.h"
#include "button.h"
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include "snackgame.h"

Game::Game(QWidget* parent)
{
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(scene->width(),scene->height());
//    setFixedSize(800,600);
}

void Game::start(){
    // clear the screen
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
    scene->setSceneRect(0,0,800,600);
    setSceneRect(0,0,800,600);
    currentViewPos = {0, 0};

    // create the dead man
    deadman = new Deadman();
    int dxPos = scene->width()/2 - deadman->boundingRect().width()/2*deadman->scale();
    int dyPos = 100;
    deadman->setPos(dxPos, dyPos);
    deadman->setFlag(QGraphicsItem::ItemIsFocusable);

    // add the dead man to the scene
    scene->addItem(deadman);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);

    // create an exit
    exit = new QGraphicsPixmapItem();
    exit->setPixmap(QPixmap(":/images/exit.png"));
    int exPos = scene->width()/2 - exit->boundingRect().width()/2;
    int eyPos = scene->height() - exit->boundingRect().height();
    exit->setPos(exPos, eyPos);
    //exit->hide();
    exit->show();
    scene->addItem(exit);

    // create the player
    player = new Player();
//    int pxPos = scene->width()/2 - player->boundingRect().width()*player->scale()/2;
//    int pyPos = scene->height()/2 - player->boundingRect().height()*player->scale()/2;
//    player->setPos(pxPos,pyPos); // TODO generalize to always be in the middle bottom of screen
    player->setPos(380,450);
    // make the player focusable and set it to be the current focus
    player->setMovable();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    connect(player,SIGNAL(dialogCall(int, int)),dialogbox,SLOT(getBox(int, int)));
    connect(dialogbox,SIGNAL(chalkCall()),this,SLOT(asmr()));
    connect(player,SIGNAL(goingOut()),this,SLOT(outside()));

    // add the player to the scene
    scene->addItem(player);

    show();
}

void Game::displayMainMenu(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Открыточка"));
    QFont titleFont("Comic Sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Играть"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    //connect(playButton,SIGNAL(clicked()),this,SLOT(snacks_game()));
//    connect(playButton,SIGNAL(clicked()),this,SLOT(asmr()));
//    connect(playButton,SIGNAL(clicked()),this,SLOT(outside()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Выйти"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::asmr() {
    //scene->clear();
    chalk = new Chalk();
    scene->addItem(chalk);

    riddlebox = new RiddleBox();
    scene->addItem(riddlebox);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);

    connect(chalk,SIGNAL(cracked(const Riddle *)),riddlebox,SLOT(showRiddle(const Riddle *)));
    connect(riddlebox,SIGNAL(result(int, int)),dialogbox,SLOT(getBox(int, int)));

}

void Game::outside() {
    // clear the screen
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/bg-big.png")));
    scene->setSceneRect(0,0,2400,1800);
    setSceneRect(800,0,800,600);
    currentViewPos = {800, 0};

    // create the cave
    cave = new Cave();
    int cxPos = scene->width()/2 - cave->boundingRect().width()*cave->scale()/2;
    int cyPos = 0;
    cave->setPos(cxPos, cyPos);
    scene->addItem(cave);

    tree = new Tree();
    int txPos = scene->width()/2 - tree->boundingRect().width()*tree->scale()/2;
    int tyPos = 600;
    tree -> setPos(txPos,tyPos);
    scene->addItem(tree);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);

    // create the player
    player = new Player();
    int pxPos = scene->width()/2 - player->boundingRect().width()*player->scale()/2;
    //int pyPos = cyPos + cave->boundingRect().height()*cave->scale()+5;
    int pyPos = cave->boundingRect().height()*cave->scale()+5;
    player->setPos(pxPos,pyPos);
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    //centerOn(player);

    connect(player,SIGNAL(dialogCall(int, int)),dialogbox,SLOT(getBox(int, int)));
    connect(player,SIGNAL(goingIn()),this,SLOT(start()));
    //connect(dialogbox,SIGNAL(chalkCall()),this,SLOT(asmr()));
    connect(dialogbox,SIGNAL(snackgameCall()),this,SLOT(snacks_game()));

    // add the player to the scene
    scene->addItem(player);

    show();
}

void Game::snacks_game() {
    //scene->clear();
    //setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
    scene->setSceneRect(0,0,800,600);
    setSceneRect(0,0,800,600);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);

//    player = new Player();
//    player->hide(); // тут проверить, скорее всего можно убрать и диалог не будет бросать сегфолт

    snackgame = new SnackGame();
    scene->addItem(snackgame);
    scene->addItem(dialogbox);

    connect(snackgame,SIGNAL(result(int, int)),dialogbox,SLOT(getBox(int, int)));
    show();
}

const QVector<Riddle> Game::riddles =
    {{"Две средние цифры года твоего рождения, повторённые дважды", "0000"},
     {"Средние две цифры - это последние цифры твоего предыдущего номера телефона, а цифры по краям повторяют соседние для них", "4499"},
     {"Первая цифра - номер дня недели,<br>в который ты получила эту открытку,<br>"
      "а последние две - номер твоего дома", "324"},
     {"Для каждой буквы из своего имени<br>возьми их порядковые номера в алфавите и сложи их все вместе. В полученной сумме поменяй цифры местами", "67"}


    };

const QVector<Speechline> Game::speech = {{":/images/player.png", "Привет"}, //0//
                             {":/images/player.png", "Как тебя зовут?"},
                             {":/images/player.png", "Я уже видел тебя"},
                             {":/images/deadman.png", "Что-то не совпадает. Попробуй проверить ответ."},
                             {":/images/deadman.png", "Молодец, всё сходится!"},
                             {":/images/player.png", "Вроде вкусно, но надо сравнить..."}, //5
                             {":/images/player.png", "Бе... По сравнению с тем, вообще невкусно!"}, // разница сырков -4
                             {":/images/player.png", "Ну такое..."},
                             {":/images/player.png", "Предыдущий мне понравился больше."},
                             {":/images/player.png", "Ничего, но тот был получше."},
                             {":/images/player.png", "Вкус такой же. Надо попробовать другие."},   //10 разница сырков 0
                             {":/images/player.png", "На вкус чуть получше, чем тот."},
                             {":/images/player.png", "Вкусненько, этот мне нравится больше."},
                             {":/images/player.png", "Очень вкусно, намного лучше предыдущего!"},
                             {":/images/player.png", "Это лучший сырок, который я пробовала!"},
                             {":/images/kalina.png", "Распробуй сырки получше, пока что-то не совсем правильно."}, //15
                             {":/images/kalina.png", "Всё правильно, спасибо за обзор на сырки!"},
                                         };

