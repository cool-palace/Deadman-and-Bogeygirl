#include "button.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QDebug>

Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // draw the rect
    //QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    text = new QGraphicsTextItem(name,this);

    if (name != "Больше" && name != "Меньше" && name != "Готово" && name != "Сбросить") {
        setRect(0,0,200,50);
        brush.setColor(Qt::darkGreen);
        // draw the text
        QFont titleFont("Comic Sans",16);
        text->setFont(titleFont);
    } else {
        setRect(0,0,100,30);
        brush.setColor(Qt::darkYellow);
        // draw the text
        QFont titleFont("Comic Sans",12);
        text->setFont(titleFont);
    }

    setBrush(brush);

    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color to cyan
    //QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (brush.color() == Qt::darkGreen) {
        brush.setColor(Qt::green);
    } else brush.setColor(Qt::yellow);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color to dark cyan
    //QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (brush.color() == Qt::green) {
        brush.setColor(Qt::darkGreen);
    } else brush.setColor(Qt::darkYellow);
    setBrush(brush);
}
