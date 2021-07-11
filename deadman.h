#ifndef DEADMAN_H
#define DEADMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
//#include <QMediaPlayer>

class Deadman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Deadman(QGraphicsItem *parent = nullptr);

public slots:
    void talk();

//signals:
    //void talk();

};

#endif // DEADMAN_H
