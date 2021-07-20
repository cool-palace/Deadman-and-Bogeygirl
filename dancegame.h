#ifndef DANCEGAME_H
#define DANCEGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>

class DanceGame : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    DanceGame(QGraphicsItem *parent = nullptr);
    //~DanceGame();
    //QGraphicsTextItem * text[5] = {nullptr};
    void keyPressEvent(QKeyEvent * event);
    QTimer * timer;

signals:
    void result(int, int);

public slots:
    void change();

private:
    QBrush brush;
    QGraphicsPixmapItem * sprite;
    QGraphicsRectItem * directions[4] = {nullptr};
    QGraphicsRectItem * cond_bg;
    QGraphicsTextItem * conditions;
    QGraphicsRectItem * score_bg;
    QGraphicsTextItem * score;
    QString score_str = "<p style=\"text-align:center;\">Счёт: %1</p>";

    int correctCount = 0;
    int tact = 0;
    int pxPos, pyPos;
    bool moved_in_this_tact = false;
};

#endif // DANCEGAME_H
