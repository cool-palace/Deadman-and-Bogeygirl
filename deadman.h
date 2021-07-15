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
    bool introduced = false;

    QVector<Speechline> wrongAnswer = {{":/images/deadman.png", "Что-то не совпадает. Попробуй проверить ответ."}};
    QVector<Speechline> rightAnswer = {{":/images/deadman.png", "Всё верно!"}};

    QVector<Speechline> speech = {{":/images/player.png", "Привет"},
                                 {":/images/player.png", "Как тебя зовут?"}};
    QVector<Speechline> speech2 = {{":/images/player.png", "Я уже видел тебя"}};

public slots:
    void talk(int lineIndex);

signals:
    void getbox(Speechline* speechline);
    void over();

};

#endif // DEADMAN_H
