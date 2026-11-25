#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H

#include <QObject>
#include<message.h>
#include<jooyanetworkengine.h>

class MessageBoard : public QObject
{
    Q_OBJECT
    QML_ATTACHED(Message)
    QML_ANONYMOUS
public:
    static Message* qmlAttachedProperties(QObject *object)
    {
        return JooyaNetworkEngine::m_Message;
    }
};
//QML_DECLARE_TYPEINFO(MessageBoard, QML_HAS_ATTACHED_PROPERTIES)
#endif // MESSAGEBOARD_H
