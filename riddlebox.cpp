#include "riddlebox.h"
#include "button.h"
#include "digit.h"
#include <QGraphicsScene>
#include "game.h"
#include <QDebug>

extern Game * game;

RiddleBox::RiddleBox(QGraphicsItem * parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/parchment.png"));
    setPos(50, 10);
    hide();

//    for (int i = 0; i < 4; ++i) {
//        digits[i] = new Digit(0);
//    }
}

void RiddleBox::showRiddle(Riddle * riddle) {
    // hide();
    //delete digits[4];

    QList<QGraphicsItem *> children = childItems();
    for (int i = 0, n = children.size(); i < n; ++i) {
        delete children[i];
    }

    // writing the question
    QGraphicsTextItem * question = new QGraphicsTextItem(this);
    question->setHtml(riddle->question);
    question->setDefaultTextColor(Qt::black);
    question->setFont({"Comic Sans", 18});
    qreal textWidth = (question->boundingRect().width()-200) / question->scale();
    question->setTextWidth(textWidth);

    // memorizing the answer
    answer = riddle->answer;

    int xPos = boundingRect().width()/2 - question->boundingRect().width()/2;
    int yPos = 100;
    question->setPos(xPos,yPos);

    int digitsCount = riddle->answer.length();

    Button ** upButtons = new Button*[digitsCount];
    Button ** downButtons = new Button*[digitsCount];
    //Digit ** digits = new Digit*[digitsCount];

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

    Button * confirmButton = new Button("Готово",this);
    confirmButton->setPos(boundingRect().width()/2 - confirmButton->boundingRect().width()/2, 475);

    connect(confirmButton,SIGNAL(clicked()),this,SLOT(checkAnswer()));

    //connect(this,SIGNAL(wrongAnswer()),game->deadman,SLOT(game->deadman->talk(int)));

    show();

}

void RiddleBox::checkAnswer() {
    QString s;
    for (int i = 0; i < answer.size(); ++i) {
        s.setNum(digits[i]->value);
        if (s != answer[i]) {
            emit wrongAnswer();
            qDebug() << "wrong";
            return;
        }
    }
    emit rightAnswer();
    qDebug() << "right";
}
