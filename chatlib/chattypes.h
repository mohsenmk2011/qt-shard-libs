#ifndef CHATTYPES_H
#define CHATTYPES_H

#include <QObject>

class ChatTypes : public QObject
{
    Q_OBJECT
public:
    enum class ChatTypesENUM
    {
        Conversation=0,
        Channal=1,
        Group=2,
        FrequentQuestions=3
    };
    Q_ENUM(ChatTypesENUM)
};

#endif // CHATTYPES_H
