#ifndef TREE_H
#define TREE_H
#include <QObject>
#include <QGraphicsPixmapItem>

class Tree : public QObject, public QGraphicsPixmapItem
{
public:
    Tree(QGraphicsItem *parent = nullptr);

};

#endif // TREE_H
