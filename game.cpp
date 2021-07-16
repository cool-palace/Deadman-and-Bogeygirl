#include "game.h"
#include "button.h"
#include <QKeyEvent>
#include <QGraphicsTextItem>

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
    setBackgroundBrush(QBrush(QImage(":/images/bg-big.png")));
    scene->setSceneRect(0,0,800,600);
    //setBackgroundBrush(QBrush(QImage(":/images/bg-big.png")));

    // create the dead man
    deadman = new Deadman();
    int dxPos = this->width()/2 - deadman->boundingRect().width()/2;
    int dyPos = 100;
    deadman->setPos(dxPos, dyPos); // TODO generalize to always be in the middle bottom of screen

    // add the dead man to the scene
    scene->addItem(deadman);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);

    // create an exit
    exit = new QGraphicsPixmapItem();
    exit->setPixmap(QPixmap(":/images/exit.png"));
    int exPos = this->width()/2 - exit->boundingRect().width()/2;
    int eyPos = this->height() - exit->boundingRect().height();
    exit->setPos(exPos, eyPos);
    exit->hide();
    scene->addItem(exit);

    // create the player
    player = new Player();
    int pxPos = this->width()/2 - player->boundingRect().width()/2;
    int pyPos = this->height()/2 - player->boundingRect().height()/2;
    player->setPos(pxPos,pyPos); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
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

    // create the dead man
//    deadman = new Deadman();
//    deadman->setPos(400,100);

    // add the dead man to the scene
//    scene->addItem(deadman);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);

    // create the player
    player = new Player();
    int pxPos = this->width()/2 - player->boundingRect().width()/2;
    int pyPos = this->height()/2 - player->boundingRect().height()/2;
    player->setPos(pxPos,pyPos); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    //centerOn(player);

    connect(player,SIGNAL(dialogCall(int, int)),dialogbox,SLOT(getBox(int, int)));
    //connect(dialogbox,SIGNAL(chalkCall()),this,SLOT(asmr()));

    // add the player to the scene
    scene->addItem(player);

    show();
}

const QVector<Riddle> Game::riddles =
    {{"Две средние цифры года твоего рождения, повторённые дважды", "0000"},
     {"Средние две цифры - это последние цифры твоего предыдущего номера телефона, а цифры по краям повторяют соседние для них", "4499"},
     {"Первая цифра - номер дня недели,<br>в который ты получила эту открытку,<br>"
      "а последние две - номер твоего дома", "324"},
     {"Для каждой буквы из своего имени<br>возьми их порядковые номера в алфавите и сложи их все вместе.<br>В результате поменяй цифры местами", "67"}


    };

const QVector<Speechline> Game::speech = {{":/images/player.png", "Привет"},
                             {":/images/player.png", "Как тебя зовут?"},
                             {":/images/player.png", "Я уже видел тебя"},
                             {":/images/deadman.png", "Что-то не совпадает. Попробуй проверить ответ."},
                             {":/images/deadman.png", "Всё верно!"}};

