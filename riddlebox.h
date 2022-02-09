#ifndef RIDDLEBOX_H
#define RIDDLEBOX_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include "button.h"

class Digit : public QGraphicsTextItem {
    Q_OBJECT
public:
    Digit(int digit, QGraphicsItem* parent = nullptr);
    ~Digit() override = default;

public slots:
    void increase();
    void decrease();
    int val() { return value; }

private:
    int value;
    QString str = "<p style=\"text-align:center;\">%1</p>";
};

class Riddle {
public:
    Riddle(QString question, QString answer) :
        question("<p style=\"text-align:center;\">" + question + "</p>"), answer(answer) {}

    QString question;
    QString answer;
};

class Chalk : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Chalk(QGraphicsItem* parent = nullptr);
    ~Chalk() override;

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

signals:
    void cracked(const Riddle& riddle);

private:
    QGraphicsPixmapItem * cracks;
    QPointF start = {0, 0};
    int cracksCount = 0;
};

class RiddleBox : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    RiddleBox(QGraphicsItem * parent = nullptr);
    ~RiddleBox() override;

public slots:
    void showRiddle(const Riddle& riddle);
    void checkAnswer();

signals:
    void result(int, int);

private:
    QGraphicsTextItem * question;
    int digitsCount;
    Button ** upButtons;
    Button ** downButtons;
    Button * confirmButton;
    Digit ** digits;
    QString answer;
    QMediaPlayer * correctSound;
    QMediaPlayer * wrongSound;
};

#endif // RIDDLEBOX_H
