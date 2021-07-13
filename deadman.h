#ifndef DEADMAN_H
#define DEADMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QVector>
#include <speechline.h>
//#include <QMediaPlayer>

class Deadman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Deadman(QGraphicsItem *parent = nullptr);
    QVector<Speechline> speech = {{":/images/player.png", "happy", "Hello"},
                                 {":/images/player.png", "happy", "What's your name?"}};

public slots:
    void talk(int lineIndex);

signals:
    void getbox(Speechline* speechline);
    void over();

};

#endif // DEADMAN_H
