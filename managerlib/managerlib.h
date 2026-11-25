#ifndef MANAGERLIB_H
#define MANAGERLIB_H

#include<QtQml/QQmlApplicationEngine>
#include<privatekeytool.h>
#include<jooyax509certificate.h>
class Managerlib
{
public:
    Managerlib();
    static void registerTypes()
    {
        qmlRegisterType<PrivateKeyTool>("Jooya",1,0,"PrivateKeyTool");
        qmlRegisterType<JooyaX509Certificate>("Jooya",1,0,"JooyaX509Certificate");

    }
};

#endif // MANAGERLIB_H
