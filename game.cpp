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
    setFixedSize(scene->width()+1,scene->height()+1);
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
    scene->addItem(deadman);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);

    // create an exit
    exit = new Exit();
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

    for (int i = 0; i < crushSound.size(); ++i) {
        crushSound[i] = new QMediaPlayer();
        QString str = "qrc:/sounds/crush-%1.wav";
        crushSound[i]->setMedia(QUrl(str.arg(i+1)));
    }

    chalk = new Chalk();
    scene->addItem(chalk);
    chalk->setFlag(QGraphicsItem::ItemIsFocusable);
    chalk->setFocus();

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
    scene->setSceneRect(0,0,worldSize,worldSize);
    setSceneRect(980,0,800,600);
    currentViewPos = {980, 0};

    // create the cave
    cave = new Cave();
    int cxPos = scene->width()/2 - cave->boundingRect().width()*cave->scale()/2;
    int cyPos = 0;
    cave->setPos(cxPos, cyPos);
    entrance = new Entrance(cave);
    entrance->setPos(127,195);
    scene->addItem(cave);

    for (int i = 0; i < 2; ++i) {
        snake[i] = new Snake(i);
        snake[i]->setPos(2053 + snake[i]->boundingRect().width()*2*i, 400);
        scene->addItem(snake[i]);
    }


    tree = new Tree();
    int txPos = 2123;
    int tyPos = 1920;
    tree -> setPos(txPos,tyPos);
    scene->addItem(tree);

    kids = new Kids();
    int kxPos = scene->width()/2 - kids->boundingRect().width()*kids->scale()/2;
    int kyPos = 600;
    kids -> setPos(kxPos,kyPos);
    scene->addItem(kids);

    kb = new RedWhite();
    kb->setPos(2170,1441);
    scene->addItem(kb);
    kb->hide();

    unicorn = new Unicorn();
    int uxPos = 469;
    int uyPos = 409;
    unicorn->setPos(uxPos,uyPos);
    scene->addItem(unicorn);

    couple = new Couple();
    int cpxPos = 457;
    int cpyPos = 1539;
    couple->setPos(cpxPos,cpyPos);
    scene->addItem(couple);

    thinker = new Thinker();
    int thxPos = 700;
    int thyPos = 1963;
    thinker->setPos(thxPos,thyPos);
    scene->addItem(thinker);

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
    connect(dialogbox,SIGNAL(snackgameCall()),this,SLOT(snacks_game()));
    connect(dialogbox,SIGNAL(dyegameCall()),this,SLOT(dye_game()));
    connect(dialogbox,SIGNAL(dancegameCall()),this,SLOT(dance_game()));
    connect(dialogbox,SIGNAL(voltorbgameCall()),this,SLOT(voltorb_game()));

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

void Game::dye_game() {
    //scene->clear();
    //setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
    scene->setSceneRect(0,0,800,600);
    setSceneRect(0,0,800,600);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);

    dyegame = new DyeGame();
    scene->addItem(dyegame);
    scene->addItem(dialogbox);

    connect(dyegame,SIGNAL(result(int, int)),dialogbox,SLOT(getBox(int, int)));
    show();
}

void Game::dance_game() {
    //scene->clear();
    //setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
    scene->setSceneRect(0,0,800,600);
    setSceneRect(0,0,800,600);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);

    dancegame = new DanceGame();
    scene->addItem(dancegame);
    dancegame->setFlag(QGraphicsItem::ItemIsFocusable);
    dancegame->setFocus();

    scene->addItem(dialogbox);

    connect(dancegame,SIGNAL(result(int, int)),dialogbox,SLOT(getBox(int, int)));
    show();
}

void Game::voltorb_game() {
    scene->setSceneRect(0,0,800,600);
    setSceneRect(0,0,800,600);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);

    voltorbgame = new VoltorbGame();
    scene->addItem(voltorbgame);

    scene->addItem(dialogbox);

    connect(voltorbgame,SIGNAL(result(int, int)),dialogbox,SLOT(getBox(int, int)));
    show();
}

const QVector<Riddle> Game::riddles = {
    {"Две средние цифры года твоего рождения, повторённые дважды", "0000"},
    {"Средние две цифры - это последние цифры твоего предыдущего номера телефона, а цифры по краям повторяют соседние для них", "4499"},
    {"Первая цифра - номер дня недели,<br>в который ты получила эту открытку,<br>"
      "а последние две - номер твоего дома", "324"},
    {"Для каждой буквы из своего имени<br>возьми их порядковые номера в алфавите и сложи их все вместе. В полученной сумме поменяй цифры местами", "67"},
    {"Две средние цифры из твоего почтового индекса и две последние цифры из номера твоей медкнижки.", "2515"}

    };

