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
    int currentLineIndex = 0;

public slots:
    //void dialog();

signals:
//    void dialogCall(int i);
    void dialogCall(int start, int end);
    void next(int i);
};

#endif // PLAYER_H
