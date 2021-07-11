#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
//#include <QMediaPlayer>

class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    bool isMovable = true;
    void setMovable();
    void setImmobile();

public slots:
    //void dialog();

signals:
    bool inRange();
};

#endif // PLAYER_H
