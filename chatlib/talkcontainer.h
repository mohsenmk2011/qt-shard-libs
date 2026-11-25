#ifndef TALKCONTAINER_H
#define TALKCONTAINER_H

#include <QObject>

class TalkContainer : public QObject
{
    Q_OBJECT
public:
    explicit TalkContainer(QObject *parent = nullptr);

signals:

};

#endif // TALKCONTAINER_H
