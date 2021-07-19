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
    QGraphicsTextItem * line;
    QGraphicsPixmapItem * avatar;
    static int start;
    static int end;// Важно: либо перенести потом в Game, либо что-то ещё сделать, чтобы значения сохранялись
    void keyPressEvent(QKeyEvent * event);

public slots:
    void getBox(int start, int end);

signals:
    void chalkCall();
    void snackgameCall();
    void dyegameCall();

};

#endif // DIALOGBOX_H
