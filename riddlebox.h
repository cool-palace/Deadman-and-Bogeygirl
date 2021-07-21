#ifndef RIDDLEBOX_H
#define RIDDLEBOX_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QSpinBox>
#include "riddle.h"
#include "digit.h"
#include "button.h"

class RiddleBox : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RiddleBox(QGraphicsItem * parent = nullptr);
    ~RiddleBox();

public slots:
    void showRiddle(const Riddle * riddle);
    void checkAnswer();

signals:
    void result(int, int);

private:
    QGraphicsTextItem * question;
    int digitsCount;
    Button ** upButtons;
    Button ** downButtons;
    Button * confirmButton;
    Digit ** digits;
    QString answer;
};

#endif // RIDDLEBOX_H
