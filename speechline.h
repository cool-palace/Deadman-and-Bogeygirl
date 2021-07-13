#ifndef SPEECHLINE_H
#define SPEECHLINE_H
#include <QString>

class Speechline
{
public:
    Speechline(QString in_speaker = ":/images/player.png", QString in_mood = "21", QString in_line = "hello");

    QString speaker;
    QString mood;
    QString line;
};

#endif // SPEECHLINE_H
