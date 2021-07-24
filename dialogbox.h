#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include "speechline.h"

class DialogBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    DialogBox(QGraphicsItem * parent = nullptr);
    ~DialogBox();
    static int start;
    static int end;// Важно: либо перенести потом в Game, либо что-то ещё сделать, чтобы значения сохранялись
    void keyPressEvent(QKeyEvent * event);

public slots:
    void getBox(int start, int end);
    void monologueCall();

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
};

#endif // DIALOGBOX_H
