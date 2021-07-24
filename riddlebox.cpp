#include "riddlebox.h"
#include <QGraphicsScene>
#include "game.h"
#include <QDebug>

extern Game * game;

RiddleBox::RiddleBox(QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/parchment.png"));
    setPos(50, 10);
    hide();
}

void RiddleBox::showRiddle(const Riddle * riddle) {

    // writing the question
    question = new QGraphicsTextItem(this);
    question->setHtml(riddle->question);
    question->setDefaultTextColor(Qt::black);
    question->setFont({"Comic Sans", 18});
//    qreal textWidth = (question->boundingRect().width()-200) / question->scale();
    qreal textWidth = 500;
    question->setTextWidth(textWidth);

    // memorizing the answer
    answer = riddle->answer;

    int xPos = boundingRect().width()/2 - question->boundingRect().width()/2;
    int yPos = 100;
    question->setPos(xPos,yPos);

    digitsCount = riddle->answer.length();

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
}

void RiddleBox::checkAnswer() {
    QString s;
    for (int i = 0; i < answer.size(); ++i) {
        s.setNum(digits[i]->value);
        if (s != answer[i]) {
            emit result(Game::deadmanSeq2Start+9,Game::deadmanSeq2Start+9);
            return;
        }
    }
    emit result(Game::deadmanSeq2Start+10,Game::deadmanSeq2Start+10);
}
