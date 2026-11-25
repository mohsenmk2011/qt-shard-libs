#ifndef TALKSTATES_H
#define TALKSTATES_H

#include <QObject>

class TalkStatus : public QObject
{
    Q_OBJECT
public:
    enum class TalkStatusEnum
    {
        NotSend=0,
        Send=1,
        Received=2,
        Seen=3,
        Deleted=4,
    };
    Q_ENUM(TalkStatusEnum)
};

#endif // TALKSTATES_H
