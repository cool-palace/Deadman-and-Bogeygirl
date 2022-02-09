#ifndef DANCEGAME_H
#define DANCEGAME_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>

class DanceGame : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    DanceGame(QGraphicsItem *parent = nullptr);
    ~DanceGame() override;

public slots:
    void keyPressEvent(QKeyEvent * event) override;

signals:
    void result(int, int);

private slots:
    void change();

private:
    QTimer * timer;
    QBrush brush;
    QGraphicsPixmapItem * sprite;
    QGraphicsRectItem * directions[4] = {nullptr};
    QGraphicsRectItem * cond_bg;
    QGraphicsTextItem * conditions;
    QGraphicsRectItem * score_bg;
    QGraphicsTextItem * score;
    QString score_str = "<p style=\"text-align:center;\">Счёт: %1</p>";
    QMediaPlayer * correctSound;
    QMediaPlayer * wrongSound;
    int correctCount = 0;
    int tact = 0;
    int pxPos, pyPos;
    bool moved_in_this_tact = false;
};

#endif // DANCEGAME_H
