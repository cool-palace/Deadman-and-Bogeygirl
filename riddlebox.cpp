#include "riddlebox.h"
#include <QGraphicsScene>
#include "game.h"
#include <QDebug>
#include <QtMath>

extern Game * game;

Chalk::Chalk(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/asmr.png"));
    cracks = new QGraphicsPixmapItem(this);
    cracks->setPixmap(QPixmap(":/images/cracks.png"));
    cracks->setPos(0,5);
    cracks->setOpacity(0);

    game->music->setCurrentIndex(3);
    game->current_music->setVolume(30);
    game->current_music->play();

    setAcceptHoverEvents(true);
}

Chalk::~Chalk() {
    delete cracks;
}

void Chalk::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF p = start - mapToScene(event->pos());
    if (sqrt(p.x()*p.x() + p.y()*p.y()) > 300) {
        start = mapToScene(event->pos());

        game->crushSound[cracksCount]->play();

        if (cracksCount < 5) {
            if (cracksCount == 4) {
                int riddle_number = 0;
                switch (game->progress) {
                case Game::DOG_QUEST_COMPLETE:
                    riddle_number = 0;
                    game->dialogbox->getBox(Game::deadmanSeq2Start+6,Game::deadmanSeq2Start+8);
                    break;
                case Game::UNICORN_QUEST_COMPLETE:
                    riddle_number = 1;
                    break;
                case Game::DANCE_QUEST_COMPLETE:
                    riddle_number = 2;
                    break;
                case Game::TREE_QUEST_COMPLETE:
                    riddle_number = 3;
                    break;
                case Game::PHILOPHOBE_QUEST_COMPLETE:
                    riddle_number = 4;
                    break;
                default:
                    break;
                }
                emit cracked(game->riddles[riddle_number]);
                delete this;
                return;
            }
            ++cracksCount;
            cracks->setOpacity(static_cast<qreal>(cracksCount)/5);
        }
    }
}

void Chalk::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    setCursor(QCursor(Qt::ClosedHandCursor));
    start = mapToScene(event->pos());
}

void Chalk::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Chalk::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Chalk::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
}

Digit::Digit(int digit, QGraphicsItem* parent) : QGraphicsTextItem(parent) {
    if (digit < 0 || digit > 9) return;
    value = digit;

    setHtml(str.arg(value));
    setFont({"Calibri", 60});
    setTextWidth(100);
    setPos(0,(120 - boundingRect().height())/2 + 30);

    setEnabled(false);
    setAcceptHoverEvents(false);
}

void Digit::increase() {
    if (value < 9) {
        ++value;
    } else value = 0;
    setHtml(str.arg(value));
}

void Digit::decrease() {
    if (value > 0) {
        --value;
    } else value = 9;
    setHtml(str.arg(value));
}

RiddleBox::RiddleBox(QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/parchment.png"));
    setPos(50, 10);
    hide();

    correctSound = new QMediaPlayer();
    correctSound->setMedia(QUrl("qrc:/sounds/correct.wav"));

    wrongSound = new QMediaPlayer();
    wrongSound->setMedia(QUrl("qrc:/sounds/wrong.wav"));
}

void RiddleBox::showRiddle(const Riddle& riddle) {
    // writing the question
    question = new QGraphicsTextItem(this);
    question->setHtml(riddle.question);
    question->setDefaultTextColor(Qt::black);
    question->setFont({"Calibri", 18});
    qreal textWidth = 500;
    question->setTextWidth(textWidth);

    // memorizing the answer
    answer = riddle.answer;

    int xPos = static_cast<int>(boundingRect().width()/2 - question->boundingRect().width()/2);
    int yPos = 100;
    question->setPos(xPos,yPos);

    digitsCount = riddle.answer.length();

    upButtons = new Button*[digitsCount];
    downButtons = new Button*[digitsCount];
    digits = new Digit*[digitsCount];

    for (int i = 0; i < digitsCount; ++i) {
        qreal offset = xPos + (textWidth - 100 * digitsCount - 20 * (digitsCount - 1)) / 2;
        upButtons[i] = new Button("Больше",this);
        upButtons[i]->setPos(i*120+offset,250);

        downButtons[i] = new Button("Меньше",this);
        downButtons[i]->setPos(i*120+offset,400);

        digits[i] = new Digit(rand()%10,upButtons[i]);

        connect(upButtons[i],SIGNAL(clicked()),digits[i],SLOT(increase()));
        connect(downButtons[i],SIGNAL(clicked()),digits[i],SLOT(decrease()));
    }

    confirmButton = new Button("Готово",this);
    confirmButton->setPos(boundingRect().width()/2 - confirmButton->boundingRect().width()/2, 475);

    connect(confirmButton,SIGNAL(clicked()),this,SLOT(checkAnswer()));

    show();
}

RiddleBox::~RiddleBox() {
    delete[] upButtons;
    delete[] downButtons;
    delete[] digits;
    delete question;
    delete confirmButton;
    delete correctSound;
    delete wrongSound;
}

void RiddleBox::checkAnswer() {
    QString s;
    for (int i = 0; i < answer.size(); ++i) {
        s.setNum(digits[i]->val());
        if (s != answer[i]) {
            wrongSound->play();
            emit result(Game::deadmanSeq2Start+9,Game::deadmanSeq2Start+9);
            return;
        }
    }
    emit result(Game::deadmanSeq2Start+10,Game::deadmanSeq2Start+10);
    correctSound->play();
}
