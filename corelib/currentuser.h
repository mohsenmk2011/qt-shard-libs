#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <QObject>
#include<userlogininfo.h>
#include<jooyanetworkengine.h>
#include<QtQml>

class CurrentUser : public QObject
{
    Q_OBJECT
    QML_ATTACHED(UserLoginInfo)
    QML_ANONYMOUS
public:
    static UserLoginInfo *qmlAttachedProperties(QObject *object)
    {
        Q_UNUSED(object)
        return JooyaNetworkEngine::m_loginInfo;
    }
};

//QML_DECLARE_TYPEINFO(CurrentUser, QML_HAS_ATTACHED_PROPERTIES)

#endif // CurrentUser_H
