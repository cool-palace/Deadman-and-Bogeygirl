#ifndef RIDDLEBOX_H
#define RIDDLEBOX_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QSpinBox>
#include "riddle.h"
#include "digit.h"

class RiddleBox : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RiddleBox(QGraphicsItem * parent = nullptr);
    Digit * digits[4] = {nullptr};
    QString answer;

public slots:
    void showRiddle(const Riddle * riddle);
    void checkAnswer();
    //void checkAnswer(Riddle *riddle, Digit *digits[]);
   // void hideRiddle();

signals:
    //void checkAnswer(Riddle *riddle, Digit *digits[]);
    void result(int, int);

};

#endif // RIDDLEBOX_H
