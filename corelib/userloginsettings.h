#ifndef USERLOGINSETTINGS_H
#define USERLOGINSETTINGS_H

#include <QObject>
#include<jooyasettings.h>

class UserLoginSettings : public JooyaSettings
{
    Q_OBJECT
public:
    explicit UserLoginSettings(QObject *parent = nullptr);

    QString token();
    void setToken(QString t);
signals:

};

#endif // USERLOGINSETTINGS_H
