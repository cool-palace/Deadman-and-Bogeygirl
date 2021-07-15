#ifndef DIGIT_H
#define DIGIT_H

#include <QGraphicsTextItem>

class Digit : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Digit(int digit, QGraphicsItem* parent=NULL);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int value;

public slots:
    void increase();
    void decrease();

};

#endif // DIGIT_H
