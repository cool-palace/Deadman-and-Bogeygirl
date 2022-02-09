#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

class Speechline {
public:
    Speechline(QString in_speaker = ":/images/player.png", QString in_line = "hello") :
        speaker(in_speaker), line(in_line) {}

    QString speaker;
    QString line;
};

class DialogBox : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    DialogBox(QGraphicsItem * parent = nullptr);
    ~DialogBox() override;
    static int start;
    static int end;

public slots:
    void getBox(int start, int end);
    void monologueCall();
    void dialog_recharge();
    void keyPressEvent(QKeyEvent * event) override;

signals:
    void chalkCall();
    void snackgameCall();
    void dyegameCall();
    void dancegameCall();
    void voltorbgameCall();

private:
    QGraphicsTextItem * line;
    QGraphicsPixmapItem * avatar;
    QString right_aligned_str = "<p style=\"text-align:right;\">%1</p>";
    QTimer * timer;
    bool ready_to_change = true;
};

#endif // DIALOGBOX_H
