#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(int dir, qreal size, QGraphicsItem *parent = nullptr);
    ~Bullet() override;
    enum directions {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    static int bullet_count;

public slots:
    void move();

signals:
    void hitTarget();
    void dialogCall(int start, int end);

private:
    directions direction = LEFT;
    QTimer * timer;
};

class Spell : public QGraphicsTextItem {
    Q_OBJECT
public:
    Spell(QGraphicsItem *parent = nullptr);
    ~Spell() override;

public slots:
    void move();

signals:
    void hitTarget();

private:
    QTimer * timer;
    const QVector<QString> spells = {"<i>мукакбы</i>", "<i>нукакбы</i>", "<i>молкакбы</i>"};
};

#endif // BULLET_H
