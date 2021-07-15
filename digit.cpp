#include "digit.h"
#include <QGraphicsRectItem>
#include <QFont>
#include <QDebug>

Digit::Digit(int digit,  QGraphicsItem* parent) : QGraphicsTextItem(parent)
{
    if (digit < 0 || digit > 9) return;
    value = digit;

    QString str = "<p style=\"text-align:center;\">%1</p>";
    setHtml(str.arg(value));
    setFont({"Comic Sans", 60});
    setTextWidth(100);
    setPos(0,(120 - boundingRect().height())/2 + 30);

    setEnabled(false);
    setAcceptHoverEvents(false);
}

void Digit::increase() {
    if (value < 9) ++value;
    else value = 0;
    QString str = "<p style=\"text-align:center;\">%1</p>";
    setHtml(str.arg(value));
}

void Digit::decrease() {
    if (value > 0) --value;
    else value = 9;
    QString str = "<p style=\"text-align:center;\">%1</p>";
    setHtml(str.arg(value));

}
