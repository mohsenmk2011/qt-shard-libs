#ifndef LOGINSTATES_H
#define LOGINSTATES_H

#include <QObject>

class LoginStates : public QObject
{
    Q_OBJECT
public:
    enum class LoginStatesEnum:unsigned int{
        LoggedIn=0,
        LoggedOut=1,

    };
    Q_ENUM(LoginStatesEnum)
};

#endif // LOGINSTATES_H
