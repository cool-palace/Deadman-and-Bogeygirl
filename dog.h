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
    ~Dog();

public slots:
    void move();

private:
    QTimer * timer;
};

class Snake : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Snake(int id, QGraphicsItem *parent = nullptr);
    ~Snake();

public slots:
    void start();
    void move();

private:
    QTimer * timer;
};

#endif // DOG_H
