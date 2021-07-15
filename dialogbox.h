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
    int start = 0, end = 0;
    void keyPressEvent(QKeyEvent * event);

public slots:
//    void showbox(Speechline* speechline);
    void getBox(int start, int end);
    void hidebox();

signals:

};

#endif // DIALOGBOX_H
