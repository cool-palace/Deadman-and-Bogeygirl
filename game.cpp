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
    //connect(dialogbox,SIGNAL(chalkCall()),this,SLOT(asmr()));
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

const QVector<Speechline> Game::speech = {
    {":/images/player.png", "Привет"}, //0//
    {":/images/player.png", "Как тебя зовут?"},
    {":/images/player.png", "Я уже видел тебя"},
    {":/images/deadman.png", "Что-то не совпадает. Попробуй проверить ответ."},
    {":/images/deadman.png", "Молодец, всё сходится!"},

    // Отсюда можно переписать
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
    // Досюда можно переписать

    {":/images/kids.png", "Привет, пойдём гулять!"}, // 17
    {":/images/player.png", "А куда вы идёте?"},
    {":/images/kids.png", "В красное и белое!"},
    {":/images/player.png", "Какие хорошие дети... Пойдём."},   // 20
    {":/images/player.png", "Привет! Пойдём с нами!"},   // 21
    {":/images/kids.png", "Ура! Мы дошли до красного и белого!"},
    {":/images/kids.png", "Спасибо, что погуляла с нами вместе! Возьми этот мел."},

    {":/images/unicorn.png", "Ох, что же делать..."}, // 24
    {":/images/player.png", "А что случилось, единорожка?"},
    {":/images/unicorn.png", "Я купила пищевых красителей и чернил, но флакончики у них похожие, и теперь я не могу отличить, что из них можко использовать для коктейлей..."},
    {":/images/unicorn.png", "Помоги мне отделить одно от другого, пожалуйста?"}, // +3
    {":/images/unicorn.png", "Но ты ещё ничего не выбрала..."}, //
    {":/images/unicorn.png", "Чернил было два флакончика, а ты выбрала только один... Добавь ещё, и тогда проверим."}, // +5
    {":/images/unicorn.png", "Похоже, ты выбрала слишком много. Лишних флаконов должно быть только два."}, // +6
    {":/images/unicorn.png", "Хм, нет, что-то не сходится. Попробуй проверить получше."}, //
    {":/images/unicorn.png", "Ура, теперь я могу спокойно использовать красители! Спасибо за помощь!"}, // +8
    {":/images/unicorn.png", "У меня есть мел, можешь его взять. "}, // +9
    {":/images/player.png", "Спасибо! Не знала, что в этом мире есть такие милые создания."},
    {":/images/unicorn.png", "В этом мире много удивительного. Говорящие деревья, феи... Хочешь, научу кое-чему?"},
    {":/images/player.png", "Чему?"},
    {":/images/unicorn.png", "Когда будешь в опасности, нажми пробел и откроешь новую силу."},
    {":/images/player.png", "... Но я уже нажимаю и ничего особенного..."},
    {":/images/unicorn.png", "Всему своё время. И мне уже тоже пора."},
    {":/images/player.png", "<i>Издевательство... Все загадками говорят...</i>"}, // +16

    {":/images/player.png", "Что стоишь, качаясь, тонкая рябина..."}, // 41
    {":/images/kalina.png", "Я не рябина, я калина!"},
    {":/images/player.png", "Ой... Извини, я не знала... что ты можешь разговаривать..."},
    {":/images/kalina.png", "Да забей, всё норм. Скажи, у тебя же есть язык?"},
    {":/images/player.png", "Что за странный вопрос?"},
    {":/images/kalina.png", "Если да, то помоги мне кое в чём. Мне нужно сделать обзор на сырки, но сама я не могу их попробовать. Можешь сделать это за меня?"},
    {":/images/player.png", "Пробовать сырки? Конечно, помогу!"}, // 40
    {":/images/player.png", "Вроде вкусно, но надо сравнить..."},
    {":/images/player.png", "Бе... По сравнению с тем, вообще невкусно!"}, // разница сырков -4
    {":/images/player.png", "Ну такое..."},
    {":/images/player.png", "Предыдущий мне понравился больше."},
    {":/images/player.png", "Ничего, но тот был получше."},
    {":/images/player.png", "Вкус такой же. Надо попробовать другие."},   //46 разница сырков 0
    {":/images/player.png", "На вкус чуть получше, чем тот."},
    {":/images/player.png", "Вкусненько, этот мне нравится больше."},
    {":/images/player.png", "Очень вкусно, намного лучше предыдущего!"},
    {":/images/player.png", "Это лучший сырок, который я пробовала!"},
    {":/images/kalina.png", "Похоже, ты ещё не расположила все сырки по местам."}, // 51
    {":/images/kalina.png", "На каждом месте должно быть не больше одного сырка."},
    {":/images/kalina.png", "Распробуй сырки получше, пока мне кажется, что что-то не совсем правильно."}, //
    {":/images/kalina.png", "Всё правильно!"}, //54
    {":/images/kalina.png", "Спасибо за обзор на сырки! Вот тебе мел за помощь!"}, //

    {":/images/player.png", "Привет, у вас случайно нет мела?"}, // 63
    {":/images/couple.png", "Ну да, есть немного) Паровоз, паровоз..."},
    {":/images/player.png", "А поделитесь со мной? Мне очень надо."},
    {":/images/couple.png", "Хорошо) Паровоз, паровоз..."},
    {":/images/player.png", "Такие спокойные... Словно на своей волне... О чём они говорят?"},
    {":/images/couple.png", "Только тогда потанцуй для нас немного)"},
    {":/images/player.png", "Эх, не могут просто так отдать..."},
    {":/images/couple.png", "Мы любим песню про паровоз, давай под неё, чтобы было смешнее)"},
    {":/images/couple.png", "Отлично станцевала, молодец)))"},
    {":/images/couple.png", "Держи, заслужила) Вышло очень забавно)))"}, // 65

    {":/images/thinker.png", "Если я открою эту клетку, то могу победить. С другой стороны, риск слишком велик... Стоит ли всё же делать этот ход?"}, // 73
    {":/images/thinker.png", "Как же сложно делать выбор..."},
    {":/images/player.png", "Что ты делаешь?"},
    {":/images/thinker.png", "Я играю в одну игру, но уже битый час стою на одном месте, не в силах сходить..."},
    {":/images/player.png", "Почему так?"},
    {":/images/thinker.png", "Это сложно... Если я ошибусь, то проиграю и придётся начинать с самого начала..."},
    {":/images/player.png", "Но ты же не сможешь выиграть, если не будешь ходить?"},
    {":/images/thinker.png", "А в чём заключается победа? Это тоже философский вопрос. Аристотель говорил, что рассудительный стремится к отсутствию страданий, а не к наслаждению. Тогда, выходит, настоящая победа состоит в том, чтобы не проиграть."},
    {":/images/player.png", "Что за бред... Это просто игра!"},
    {":/images/player.png", "Строишь всякие рассуждения, просто чтобы оправдаться за то, что ты боишься. Ты не философ, ты филофоб!"},
    {":/images/player.png", "Давай я тебе покажу, как надо!"}, //+10
    {":/images/player.png", "Ничего, попробую ещё раз!"},
    {":/images/player.png", "Теперь следующий уровень!"},
    {":/images/player.png", "И ещё один разок!"},
    {":/images/thinker.png", "У тебя и правда получилось!"},
    {":/images/thinker.png", "Спасибо, ты и правда помогла мне взглянуть на вещи под другим углом."},
    {":/images/thinker.png", "\"Несчастная судьба многих людей — следствие несделанного ими выбора. Они ни живые, ни мертвые. Жизнь оказывается бременем, бесцельным занятием, а дела — лишь средством защиты от мук бытия в царстве теней.\""},
    {":/images/thinker.png", "Это Эрих Фромм. Я так много думал, но никогда бы мне не пришла в голову мысль о том, что я сам окажусь в подобной ловушке разума."},
    {":/images/thinker.png", "Возьми немного мела в подарок."}, // +18

    {":/images/kids.png", "Привет, пойдём гулять!"}, // 92
    {":/images/player.png", "А куда вы идёте?"},
    {":/images/kids.png", "Мы идём в красное и белое!"},
    {":/images/player.png", "<i>А вам не рано ещё?</i>"},
    {":/images/kids.png", "Мы хотим купить колы и чипсов, только есть одна проблема."},
    {":/images/player.png", "Какая?"},
    {":/images/kids.png", "Красное и белое скрывается от посторонних глаз, его можно найти только по запаху."},
    {":/images/kids.png", "Поэтому мы ищем компанию, может быть, кто-то поможет и проводит нас!"},
    {":/images/player.png", "Хорошо, давайте пойдём вместе. Мне всё равно надо осмотреться здесь."},
    {":/images/kids.png", "Ура!"},
    {":/images/player.png", "<i>Какие хорошие дети...</i>"}, //+10
    {":/images/player.png", "Смотрите, собачка!"},  // +11
    {":/images/player.png", "Привет! Пойдём с нами!"},
    {":/images/dog.png", "Гав!"},
    {":/images/kids.png", "Собачка, помоги нам найти красное и белое!"},
    {":/images/dog.png", "Гав! Гав!"},   // +15
    {":/images/kids.png", "Ура! Мы дошли до красного и белого!"},
    {":/images/kids.png", "Спасибо, что погуляла с нами! Возьми этот мел."}, //+17

    {":/images/player.png", "<i>Змейки... Страшновато подходить...</i>"}, // 110
    {":/images/snake-1.png", "Шшш... кто это такая?..."},
    {":/images/player.png", "Я случайно сюда попала, и я ищу волшебный мел, чтобы выбраться. Вы не знаете, где его можно найти?"},
    {":/images/snake-2.png", "Шшто за волшшшебный мел? Отссюда невозможно выбратьссся."},
    {":/images/player.png", "Но Мертвец мне сказал, что есть такой способ..."},
    {":/images/snake-1.png", "Хахаха! Что за глупоссть он выдумал!"},
    {":/images/snake-2.png", "Он давно потерял то, без чего в насстоящем мире не выжить. Наверно, он исспользует тебя для чего-то."},
    {":/images/snake-1.png", "Проссто кальций ссобирает, чтобы кости не гнили подольшшше!"},
    {":/images/player.png", "<i>Зачем я только подошла...</i>"},
    {":/images/player.png", "Я лучше пойду..."},
    {":/images/snake-2.png", "Хозяйка вссё равно тебя найдёт."},
    {":/images/snake-1.png", "А мы позовём её, шштобы пришшла посмотреть на новенькую."},
    {":/images/player.png", "<i>Ужасно... Надо скорее остановить их. Что там говорила единорожка?</i>"},
    {":/images/unicorn.png", "<i>Когда будешь в опасности, нажми пробел и откроешь новую силу.</i>"},
    {":/images/player.png", "Кажется, пора это попробовать."}, //+14
    {":/images/player.png", "Ай!"},
    {":/images/player.png", "Фух... Вроде пронесло..."},



};

