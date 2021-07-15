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

public slots:
    void showbox(Speechline* speechline);
    void hidebox();

signals:

};

#endif // DIALOGBOX_H
