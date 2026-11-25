#ifndef WEBSOCKETSTATES_H
#define WEBSOCKETSTATES_H

#include <QObject>

class WebSocketStates : public QObject
{
    Q_OBJECT
public:
    enum class WebSocketStatesEnum:unsigned int{        
        Unconnected,
        HostLookup,
        Connecting,
        Connected,
        Bound,
        Listening,
        Closing
    };
    Q_ENUM(WebSocketStatesEnum)

};

#endif // WEBSOCKETSTATES_H
