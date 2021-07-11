#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

class DialogBox : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    DialogBox(QGraphicsItem * parent=0);

public slots:
    void showbox();

signals:

};

#endif // DIALOGBOX_H
