#ifndef DOG_H
#define DOG_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Dog : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dog(QGraphicsItem *parent = nullptr);
    QTimer * timer;
    static int caught_count;

public slots:
    void move();

//signals:
//    void dialogCall(int start, int end);
};

#endif // DOG_H
