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
    QFile save("C:\\Users\\User\\Documents\\build-Postcard-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\debug\\save.txt");
    save.open(QIODevice::ReadOnly);
    QTextStream in(&save);
    QString str;
    in >> str;
    int in_progress = str.toInt();
    save.close();

    if (in_progress >= 0 && in_progress < 18)  {
        progress = static_cast<Progress>(in_progress);
    }

    // clear the screen
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/cave-bg.png")));
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
    if (progress == START || progress == OUTSIDE_EMPTINESS_DISCOVERED) {
        exit->hide();
    } else exit->show();
    scene->addItem(exit);

    // create the player
    player = new Player();
    int pxPos = scene->width()/2 - player->boundingRect().width()*player->scale()/2;
    int pyPos;
    if (progress == START) {
        pyPos = scene->height()/2 - player->boundingRect().height()*player->scale()/2;
    } else pyPos = 450;
    player->setPos(pxPos,pyPos);
    // make the player focusable and set it to be the current focus
    player->setMovable();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    connect(player,SIGNAL(dialogCall(int, int)),dialogbox,SLOT(getBox(int, int)));
    connect(dialogbox,SIGNAL(chalkCall()),this,SLOT(asmr()));
    connect(player,SIGNAL(goingOut()),this,SLOT(outside()));

    switch (progress) {

    case START: {
        dialogbox->getBox(deadmanSeq1Start,deadmanSeq1Start+3);
        break; }

    case Game::PHILOPHOBE_QUEST_COMPLETE: {
        portal = new Portal();
        portal->setPos(0, scene->height()/2-portal->boundingRect().height()/2);
        portal->hide();
        scene->addItem(portal);
        break; }

    case OUTSIDE_EMPTINESS_DISCOVERED: {
        player->canShoot = true;
        player->setPos(scene->width() - player->boundingRect().width(), scene->height()/2-player->boundingRect().height()/2);
        deadman->hide();
        exit->hide();

        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),player,SLOT(shrink_bullet()));
        timer->start(250);

        portal = new Portal();
        portal->setPos(0, scene->height()/2-portal->boundingRect().height()/2);
        scene->addItem(portal);

        witch = new Witch();
        witch->setPos(portal->boundingRect().width()/2,scene->height()/2-witch->boundingRect().height()/2);
        scene->addItem(witch);
        witch->hide();

        dialogbox->getBox(witchSeqStart,witchSeqStart+1);
        break; }

    default:
        break;
    }
    show();
}

void Game::displayMainMenu(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
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

    exit->hide();

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

    if (progress == DOG_QUEST_COMPLETE) dialogbox->getBox(Game::deadmanSeq2Start+5,Game::deadmanSeq2Start+5);
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

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(dialogbox);

    switch (progress) {

    case INTRO_COMPLETE: {
        kids = new Kids();
        int kxPos = scene->width()/2 - kids->boundingRect().width()*kids->scale()/2;
        int kyPos = 600;
        kids -> setPos(kxPos,kyPos);
        scene->addItem(kids);

        kb = new RedWhite();
        kb->setPos(2170,1441);
        scene->addItem(kb);
        kb->hide();
        break; }

    case FIRST_RIDDLE_SOLVED: {
        unicorn = new Unicorn();
        int uxPos = 469;
        int uyPos = 409;
        unicorn->setPos(uxPos,uyPos);
        scene->addItem(unicorn);
        connect(dialogbox,SIGNAL(dyegameCall()),this,SLOT(dye_game()));
        break; }

    case SECOND_RIDDLE_SOLVED: {
        couple = new Couple();
        int cpxPos = 457;
        int cpyPos = 1539;
        couple->setPos(cpxPos,cpyPos);
        scene->addItem(couple);
        connect(dialogbox,SIGNAL(dancegameCall()),this,SLOT(dance_game()));
        break; }

    case THIRD_RIDDLE_SOLVED: {
        for (int i = 0; i < 2; ++i) {
            snake[i] = new Snake(i);
            snake[i]->setPos(2053 + snake[i]->boundingRect().width()*2*i, 400);
            scene->addItem(snake[i]);
        }
        break; }

    case AFTER_SNAKES_DIALOG_OVER: {
        tree = new Tree();
        int txPos = 2123;
        int tyPos = 1920;
        tree -> setPos(txPos,tyPos);
        scene->addItem(tree);
        connect(dialogbox,SIGNAL(snackgameCall()),this,SLOT(snacks_game()));
        break; }

    case FOURTH_RIDDLE_SOLVED: {
        thinker = new Thinker();
        int thxPos = 700;
        int thyPos = 1963;
        thinker->setPos(thxPos,thyPos);
        scene->addItem(thinker);
        connect(dialogbox,SIGNAL(voltorbgameCall()),this,SLOT(voltorb_game()));
        break; }

    case FIFTH_RIDDLE_SOLVED: {
        setBackgroundBrush(QBrush(QImage(":/images/bg-big-dark.png")));
        timer = new QTimer();
        timer->setSingleShot(true);
        timer->start(15000);
        connect(timer,SIGNAL(timeout()),dialogbox,SLOT(monologueCall()));

        break; }

    default:
        break;
    }

    // create the player
    player = new Player();
    int pxPos = scene->width()/2 - player->boundingRect().width()*player->scale()/2;
    int pyPos = height()/2 - player->boundingRect().height()*player->scale()/2;
    player->setPos(pxPos,pyPos);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    connect(player,SIGNAL(dialogCall(int, int)),dialogbox,SLOT(getBox(int, int)));
    connect(player,SIGNAL(goingIn()),this,SLOT(start()));

    show();
}

void Game::snacks_game() {
    scene->setSceneRect(0,0,800,600);
    setSceneRect(0,0,800,600);

    // create a dialog box
    dialogbox = new DialogBox();
    dialogbox->setFlag(QGraphicsItem::ItemIsFocusable);

    snackgame = new SnackGame();
    scene->addItem(snackgame);
    scene->addItem(dialogbox);

    connect(snackgame,SIGNAL(result(int, int)),dialogbox,SLOT(getBox(int, int)));
    show();
}

void Game::dye_game() {
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
    {":/images/player.png", "Где я?.."}, //0//
    {":/images/player.png", "Последнее, что я помню — это букет и та странная открытка. Я открыла её, а дальше... Как я здесь оказалась?"},
    {":/images/player.png", "Здесь так темно и пусто... Только чёрные стены и кучка земли..."},
    {":/images/player.png", "Надо осмотреться, может быть, получится найти выход."}, // +3
    {":/images/player.png", "ААА!!! МЕРТВЕЦ!"}, // +4
    {":/images/deadman.png", "..."},
    {":/images/player.png", "СПАСИТЕ!!!"},
    {":/images/deadman.png", "Эм..."},
    {":/images/deadman.png", "Успокойся, пожалуйста. Я тебя не съем."},
    {":/images/player.png", "Ты кто?! Что это за место?! Как мне попасть домой?"},
    {":/images/deadman.png", "Это немного другой мир. Если ты попала сюда, то вернуться домой будет сложно."},
    {":/images/player.png", "Это ты меня здесь запер?!"},
    {":/images/deadman.png", "Нет, ты чего... Я и сам заперт здесь. Меня заколдовали давным-давно."},
    {":/images/player.png", "Заколдовали?"},
    {":/images/deadman.png", "Да... После этого я и стал выглядеть так... Если не поторопиться, то ты тоже можешь превратиться здесь в кого-то."},
    {":/images/player.png", "В смысле, превратиться? В кого?"},
    {":/images/deadman.png", "Не знаю, как получится. В бабайку или что-то такое."},
    {":/images/player.png", "И что мне теперь делать? Я не хочу быть бабайкой! Я хочу домой!"},
    {":/images/deadman.png", "Я же говорю, это не так просто, иначе я бы сам здесь не сидел. Можно попробовать один способ, конечно, но придётся потрудиться. И я не совсем уверен, что сработает..."},
    {":/images/player.png", "Ну же, расскажи скорее!"},
    {":/images/deadman.png", "Недавно я нашёл старую книгу с заклинаниями, и там было то, которое может нам помочь и открыть дверь обратно в настоящий мир."},
    {":/images/player.png", "Так давай скорее его используем!"},
    {":/images/deadman.png", "Проблема в том, что в книге оно неполное. Чтобы закончить его, надо собрать <b>пять ключей</b>."},
    {":/images/player.png", "А где их найти? И что это за ключи вообще?"},
    {":/images/deadman.png", "Я знаю только то, они спрятаны в брикетах волшебного мела."},
    {":/images/player.png", "Что за бред..."},
    {":/images/deadman.png", "Звучит глупо, но так было написано в книге..."},
    {":/images/deadman.png", "Можешь мне не верить, но лучше попробовать их найти, пока есть время. Если ты превратишься в бабайку, пути назад не будет."},
    {":/images/player.png", "<i>Ничего не поделаешь, придётся попытаться.</i>"},
    {":/images/player.png", "Ладно, но где мне искать эти ключи?"},
    {":/images/deadman.png", "Вот здесь, снизу, есть выход, попробуй посмотреть снаружи."}, //+30

    {":/images/kids.png", "Привет, пойдём гулять!"}, // 31
    {":/images/player.png", "А куда вы идёте?"},
    {":/images/kids.png", "Мы идём в красное и белое!"},
    {":/images/player.png", "<i>А вам не рано ещё?</i>"},
    {":/images/kids.png", "Мы хотим купить колы и чипсов, только есть одна проблема."},
    {":/images/player.png", "Какая?"},
    {":/images/kids.png", "Красное и белое скрывается от посторонних глаз, его можно найти только по запаху."},
    {":/images/kids.png", "Поэтому мы ищем компанию, может быть, кто-то поможет и проводит нас!"},
    {":/images/player.png", "Хорошо, давайте пойдём вместе. Мне всё равно надо осмотреться здесь."},
    {":/images/kids.png", "Ура!"},
    {":/images/player.png", "<i>Странно всё это звучит, но дети вроде хорошие...</i>"}, //+10
    {":/images/player.png", "Смотрите, собачка!"},  // +11
    {":/images/player.png", "Привет! Пойдём с нами!"},
    {":/images/dog.png", "Гав!"},
    {":/images/kids.png", "Собачка, помоги нам найти красное и белое!"},
    {":/images/dog.png", "Гав! Гав!"},   // +15
    {":/images/kids.png", "Ура! Мы дошли до красного и белого!"},
    {":/images/kids.png", "Спасибо, что погуляла с нами! Возьми этот мел."}, //+17
    {":/images/player.png", "Ого, вот и первый ключ. Правда, на ключ вообще не похож... Отнесу мертвецу, пусть он посмотрит."}, // + 18

    {":/images/deadman.png", "О, бабайка! Ты вернулась! Как тебе снаружи?"}, // 50
    {":/images/player.png", "Пустовато, и выхода никакого не видно. И вообще, никакая я не бабайка!"},
    {":/images/deadman.png", "Удалось что-то найти?"},
    {":/images/player.png", "Да, вот один кусок мела. Что теперь с ним делать?"},
    {":/images/deadman.png", "Отлично! Ключ должен быть внутри. Давай попробуем его расколоть."},
    {":/images/deadman.png", "Чтобы мел раскололся, зажми левую кнопку и поводи по нему мышью. Давай, попробуй!"}, // +5
    {":/images/player.png", "И что это такое?"},
    {":/images/deadman.png", "Видимо, ключи ещё и зашифрованы. Ну, в этом есть смысл, иначе ими мог бы воспользоваться кто угодно. Но, кажется, для тебя это не должно быть слишком сложно. Попробуй ввести свой ответ."},
    {":/images/player.png", "<i>Издевательство какое-то...</i>"}, // +8
    {":/images/deadman.png", "Что-то не совпадает. Попробуй проверить ответ."},
    {":/images/deadman.png", "Молодец, всё подошло!"},
    {":/images/deadman.png", "Теперь мы на один шаг ближе к свободе, это радует."}, // +11
    {":/images/player.png", "Очень странная была загадка. Но достаточно лёгкая... Они все такие?"},
    {":/images/deadman.png", "Не знаю. Надеюсь, ещё увидим."}, // +13

    {":/images/unicorn.png", "Ох, что же делать..."}, //
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
    {":/images/unicorn.png", "В этом мире много удивительного. Деревья говорящие, феи... Хочешь, научу кое-чему?"},
    {":/images/player.png", "Чему?"},
    {":/images/unicorn.png", "Когда будешь в опасности, нажми пробел и откроешь новую силу."},
    {":/images/player.png", "... Но я уже нажимаю и ничего особенного..."},
    {":/images/unicorn.png", "Всему своё время. И мне уже тоже пора."},
    {":/images/player.png", "<i>Издевательство... Здесь все загадками говорят, что ли...</i>"},
    {":/images/player.png", "Наверно, этот мел тоже надо отнести мертвецу."}, // +17

    {":/images/deadman.png", "Ого, ты нашла ещё один кусок мела! Давай его расколем, как в прошлый раз!"}, //
    {":/images/deadman.png", "Мы неплохо продвигаемся. Если ты найдёшь ещё три брикета, то у нас будешь шанс спастись."},
    {":/images/player.png", "Почему я должна одна искать этот мел? Почему ты его не ищешь сам?"},
    {":/images/deadman.png", "... Я бы рад, но я не могу."},
    {":/images/player.png", "Не можешь?"},
    {":/images/deadman.png", "Когда меня заколдовали, моё сердце спрятали <b>глубоко под землю</b>. После этого вся жизнь ушла из меня, и с тех пор земля сама постоянно затягивает меня, потому что там место мёртвым."},
    {":/images/deadman.png", "Я не могу выйти наружу и вообще пройти далеко. Моих сил сейчас хватает только на то, чтобы откапывать себя время от времени и держаться на поверхности."},
    {":/images/player.png", "А что случится, если ты уйдёшь под землю?"},
    {":/images/deadman.png", "Я не знаю... Глубина около метра мне ещё не страшна, настолько я опускаюсь за одну ночь, но если будет больше, то я могу просто никогда не откопаться обратно."},
    {":/images/deadman.png", "Проверять на практике мне страшно..."},
    {":/images/player.png", "Как ужасно... Мне так жаль..."},
    {":/images/deadman.png", "Ну, ничего страшного. Только поищи всё-таки ещё ключей, хорошо?"}, // +11

    {":/images/player.png", "Привет, у вас случайно нет мела?"}, //
    {":/images/couple.png", "Ну да, есть немного) Паровоз, паровоз, паровоз..."},
    {":/images/player.png", "А поделитесь со мной? Мне очень надо."},
    {":/images/couple.png", "Хорошо) Паровоз, паровоз, паровоз..."},
    {":/images/player.png", "<i>Такие спокойные... Словно на своей волне... Но что они напевают?</i>"},
    {":/images/couple.png", "Тогда потанцуй для нас немного)"},
    {":/images/player.png", "<i>Эх, не могут просто так отдать...</i>"},
    {":/images/couple.png", "Мы любим песню про паровоз, давай под неё, чтобы было смешнее)"},
    {":/images/couple.png", "Отлично станцевала, молодец)))"},
    {":/images/couple.png", "Держи, заслужила) Вышло очень забавно)))"}, // +9

    {":/images/deadman.png", "У тебя здорово получается, ты уже нашла больше половины ключей! Давай посмотрим и на этот."},
    {":/images/player.png", "Знаешь, что странно? Все, кого я здесь встречала, довольно мило себя ведут."},
    {":/images/deadman.png", "Здесь все разные, как и в настоящем мире. Тебе повезло, что попадались хорошие люди. Или не совсем люди..."},
    {":/images/deadman.png", "Может быть, ты уже и подружилась с кем-нибудь?"},
    {":/images/player.png", "Не то чтобы..."},
    {":/images/deadman.png", "А в реальном мире у тебя есть друзья?"},
    {":/images/player.png", "Да, немного... Но с ними тоже всё бывает непросто."},
    {":/images/deadman.png", "Наверно, они тоже сейчас переживают за тебя и ждут, когда ты вернёшься."},
    {":/images/player.png", "Наверно, да."},
    {":/images/deadman.png", "Что бы ты хотела сделать, когда вернёшься?"},
    {":/images/player.png", "Много чего. Хотела бы увидеться с ними. Хотела бы учиться, развиваться."},
    {":/images/player.png", "Хотела бы быть собой, заботиться о себе и контролировать свою жизнь."},
    {":/images/deadman.png", "Какой хороший у тебя список целей. Я думаю, у тебя всё получится. Главное только выбраться отсюда."},
    {":/images/player.png", "А ты? Что бы ты хотел делать, когда вернёшься в реальный мир?"},
    {":/images/deadman.png", "......"},
    {":/images/deadman.png", "Летать..."},
    {":/images/player.png", "Понятно..."},
    {":/images/player.png", "<i>Мда, как иронично... Пожалуй, не будем терять время и продолжим поиски.</i>"}, // +17

    {":/images/player.png", "<i>Змейки... Страшновато подходить...</i>"}, //
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
    {":/images/snake-1.png", "..."},
    {":/images/snake-2.png", "..."},
    {":/images/player.png", "Фух... Вроде пронесло... Лучше пойду обратно."}, // +18

    {":/images/player.png", "Мертвец..."},
    {":/images/deadman.png", "Что, бабайка? Ты нашла ещё один ключ?"},
    {":/images/player.png", "Я не бабайка! И ничего не нашла пока."},
    {":/images/player.png", "Я встретила каких-то странных змей снаружи. Они говорили про какую-то хозяйку, и что она скоро меня найдёт."},
    {":/images/deadman.png", "... Это нехорошо. У нас может быть не так много времени. Ты не видела, в какую сторону они ушли?"},
    {":/images/player.png", "Я подстрелила их... чем-то... и они больше не двигались."},
    {":/images/deadman.png", "Что ж, это обнадёживает. Ты умница, благодаря тебе у нас всё-таки есть небольшой запас по времени."},
    {":/images/player.png", "А что это за хозяйка? О ком они говорили?"},
    {":/images/deadman.png", "Хозяйка этого мира. Это она заколдовала меня. Она заколдует и тебя, если найдёт."},
    {":/images/deadman.png", "Давай отложим разговоры на потом. Кажется, надо поторопиться с поисками."}, // +9

    {":/images/player.png", "Вспоминается песня из моего детства...<br>Что стоишь, качаясь, тонкая рябина..."}, //
    {":/images/kalina.png", "Я не рябина, я калина!"},
    {":/images/player.png", "Ой... Извини, я не знала... что ты можешь разговаривать..."},
    {":/images/kalina.png", "Да забей, всё норм. Скажи, у тебя же есть язык?"},
    {":/images/player.png", "Что за странный вопрос?"},
    {":/images/kalina.png", "Если да, то помоги мне кое в чём. Мне нужно сделать обзор на сырки, но сама я не могу их попробовать. Можешь сделать это за меня?"},
    {":/images/player.png", "Пробовать сырки? Конечно, помогу!"}, // +6
    {":/images/player.png", "Вроде вкусно, но надо сравнить..."},
    {":/images/player.png", "Бе... По сравнению с тем, вообще невкусно!"}, // разница сырков -4
    {":/images/player.png", "Ну такое..."},
    {":/images/player.png", "Предыдущий мне понравился больше."},
    {":/images/player.png", "Ничего, но тот был получше."},
    {":/images/player.png", "Вкус такой же. Надо попробовать другие."},   // разница сырков 0
    {":/images/player.png", "На вкус чуть получше, чем тот."},
    {":/images/player.png", "Вкусненько, этот мне нравится больше."},
    {":/images/player.png", "Очень вкусно, намного лучше предыдущего!"},
    {":/images/player.png", "Это лучший сырок, который я пробовала!"},
    {":/images/kalina.png", "Похоже, ты ещё не расположила все сырки по местам."}, // +17
    {":/images/kalina.png", "На каждом месте должно быть не больше одного сырка."},
    {":/images/kalina.png", "Распробуй сырки получше, пока мне кажется, что что-то не совсем правильно."}, //
    {":/images/kalina.png", "Всё правильно!"}, //+20
    {":/images/kalina.png", "Спасибо за обзор на сырки! Вот тебе мел за помощь!"}, // +21

    {":/images/deadman.png", "Ты нашла четвёртый ключ! Скорее, давай расколем его!"},
    {":/images/player.png", "Мертвец... А мы точно сможем вернуться?"},
    {":/images/deadman.png", "Конечно, мы близки к этому, как никогда!"},
    {":/images/player.png", "Те змеи говорили, что это невозможно."},
    {":/images/deadman.png", "Ну, я не пробовал раньше, но если верить книге, то шанс есть."},
    {":/images/deadman.png", "Кого ты слушаешь вообще?"},
    {":/images/player.png", "Ещё они говорили, что ты не сможешь выжить, если вернёшься..."},
    {":/images/deadman.png", "В смысле, не смогу?"},
    {":/images/deadman.png", "..."},
    {":/images/deadman.png", "Подожди..."},
    {":/images/deadman.png", "Ладно, пока неважно. Давай найдём последний ключ, а потом будем думать."}, //+10

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

    {":/images/player.png", "Мертвец, вот последний ключ."},
    {":/images/deadman.png", "Отлично, ты знаешь, что делать теперь."},
    {":/images/deadman.png", "Вот он, портал в наш родной мир! Скорее пойдём!"},
    {":/images/player.png", "Тебя ничего не смущает?"},
    {":/images/deadman.png", "Что такое?"},
    {":/images/player.png", "Мы нашли выход, но проклятие ведь всё ещё на тебе. Заклинание не сняло его автоматически."},
    {":/images/deadman.png", "..."},
    {":/images/player.png", "Что будет, если ты вернёшься в наш мир таким... мёртвым?"},
    {":/images/deadman.png", "Я не знаю..."},
    {":/images/deadman.png", "Я не хотел думать об этом..."},
    {":/images/player.png", "Надо думать о таких вещах."},
    {":/images/deadman.png", "Но тебе надо спешить, хозяйка может настигнуть тебя с минуты на минуту."},
    {":/images/player.png", "Если я пройду, что будешь делать ты?"},
    {":/images/deadman.png", "..."},
    {":/images/deadman.png", "В книге написано, что портал закроется сразу после того, как туда зайдёт человек. Наши ключи станут бесполезны, а волшебный мел соберётся снова и рассеется по миру, поэтому мы можем больше его и не найти."},
    {":/images/deadman.png", "Иди без меня. Это может быть твой последний шанс."},
    {":/images/player.png", "Почему ты не хочешь попытаться снять своё проклятие?"},
    {":/images/deadman.png", "А как? Я стал таким после того, как потерял сердце. Ну, хорошо, допустим, я его каким-то чудом найду, но оно лежит на глубине 33 метра под землёй! Как я оттуда выберусь? Меня же завалит и затянет."},
    {":/images/deadman.png", "Я могу умереть прямо насовсем..."},
    {":/images/player.png", "И поэтому ты хотел в портал лезть прямо так?"},
    {":/images/deadman.png", "Ну, это другое..."},
    {":/images/player.png", "Понятно. В общем, ты тоже филофоб. Только какой-то глупый ещё."},
    {":/images/deadman.png", "... Что?"},
    {":/images/player.png", "Ни живой, ни мёртвый, бесцельно существуешь, потому что не можешь сделать выбор. Эрих Фромм писал о таком."},
    {":/images/player.png", "Я пойду наружу, попробую найти что-то, что поможет тебя расколдовать."}, // +24
    {":/images/deadman.png", "..."},
    {":/images/player.png", "Что-то никого не видно и, похоже, ничего я тут не найду."},
    {":/images/player.png", "Ладно, вернусь обратно. Придумаем что-нибудь вместе."}, // +27

    {":/images/player.png", "Мертвец, ты где?"}, //
    {":/images/player.png", "Неужели сам ушёл, без меня? Не может же такого быть!"},
    {":/images/witch.png", "А вот и новенькая..."},
    {":/images/player.png", "!.."},
    {":/images/witch.png", "Иди сюда... Слушай, что я тебе скажу..."},
    {":/images/player.png", "<i>Беда... она же меня сейчас заколдует... </i>"},
    {":/images/player.png", "<i>Надо защищаться... Со змеями получилось, получится и сейчас!</i>"},
    {":/images/player.png", "<i>Мне нехорошо...</i>"},
    {":/images/player.png", "<i>Не могу больше... Кажется, я слабею...</i>"},
    {":/images/player.png", "<i>Эти мрачные стены как будто вытягивают мои силы...</i>"},
    {":/images/player.png", "<i>Такими темпами меня сейчас заколдуют...</i>"},
    {":/images/deadman.png", "Бабайка!"},
    {":/images/player.png", "Мертвец! Или нет?.."},
    {":/images/deadman.png", "Бабайка! Я нашёл его!"},
    {":/images/player.png", "Кого?.."},
    {":/images/deadman.png", "Моё сердце, что же ещё! Смотри, оно сняло проклятие! Я теперь живой!"},
    {":/images/player.png", "И правда, ты выглядишь совсем по-другому... Как тебе удалось?"},
    {":/images/deadman.png", "Я всегда боялся это делать... Боялся уходить под землю. Я думал, что лучше продолжать быть мёртвым, чем на самом деле умереть."},
    {":/images/player.png", "<i>Как это сочетается вообще?</i>"},
    {":/images/deadman.png", "Я думал, что земля меня тянет, потому что там моя смерть. В смысле, настоящая, насовсем."},
    {":/images/deadman.png", "Только сейчас я понял, что это моё забытое сердце звало меня, чтобы я его нашёл."},
    {":/images/deadman.png", "Стоило мне довериться ему, и земля сама довела меня. Без тебя я никогда бы не задумался и не решился на такое."},
    {":/images/player.png", "Это всё очень хорошо, конечно, но я тут вообще-то сражаюсь, и мне нужна помощь."},
    {":/images/deadman.png", "Я освещу эту мрачную пещеру своим сердцем. Твои силы должны увеличиться! Попробуй!"},
    {":/images/player.png", "<i>Как можно сердцем освещать? Ты что, поэт?</i>"},
    {":/images/player.png", "<i>Ладно, неважно. Попробую выстрелить!</i>"}, // +25

    {":/images/deadman.png", "Ты сделала это! Потрясающе! Теперь мы свободны, и сам этот мир теперь свободен."},
    {":/images/player.png", "Спасибо, что пришёл. Я уже думала, ты не вернёшься."},
    {":/images/deadman.png", "Это тебе спасибо, что помогла мне спастись."},
    {":/images/player.png", "Как ты думаешь, когда мы вернёмся, мы сможем увидеться снова?"},
    {":/images/deadman.png", "Сложно сказать. Выйдя из портала мы окажемся там, где были до того, как сюда попали. Скорее всего, это будут разные места, возможно, даже разное время."},
    {":/images/deadman.png", "Но если повезёт и наши пути пересекутся снова, то я бы хотел тебя увидеть там."},
    {":/images/deadman.png", "Я придумал! Я оставлю тебе особый клад в специальном месте, чтобы ты знала, что я рядом."},
    {":/images/player.png", "Особый клад?"},
    {":/images/deadman.png", "Это знак моей благодарности за то, что ты есть. Слушай внимательно."},
    {":/images/deadman.png", "Проспект имени Газеты Красноярский Рабочий, дом 60, офис 71. Вторая от угла белая стеклянная дверь. Этаж - 1, магазин Сеньорита. Твой ориентир — зелёный кружок на красном фоне или виноград."},
    {":/images/deadman.png", "Когда придёшь туда, назови номер — это четыре первых ключа подряд, и код — это последний ключ. И захвати с собой паспорт."},
    {":/images/player.png", "... Зачем так сложно?"},
    {":/images/deadman.png", "Разве так не интереснее?"},
    {":/images/player.png", "Я же не вспомню эти ключи уже!"},
    {":/images/deadman.png", "Не беспокойся, я всё записал на этот случай. Посмотри потом в папке или в главном меню."},
    {":/images/deadman.png", "А теперь пойдём, нам пора возвращаться. Не об этом месте с тобою мечтали мы. Разве нет?)"},
    {":/images/deadman.png", "И кстати, с днём рождения!"}, // + 16
};
