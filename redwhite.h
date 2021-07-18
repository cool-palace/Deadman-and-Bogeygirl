#ifndef REDWHITE_H
#define REDWHITE_H

#include <QGraphicsPixmapItem>

class RedWhite : public QObject, public QGraphicsPixmapItem
{
public:
    RedWhite(QGraphicsItem * parent=0);
};

#endif // REDWHITE_H
