#include "riddle.h"

Riddle::Riddle(QString in_question, QString in_answer) :
    answer(in_answer)
{
    QString str = "<p style=\"text-align:center;\">%1</p>";
    question = str.arg(in_question);
}
