#ifndef RIDDLE_H
#define RIDDLE_H
#include <QString>

class Riddle
{
public:
    Riddle(QString in_question, QString in_answer);

    QString question;
    QString answer;
};

#endif // RIDDLE_H
