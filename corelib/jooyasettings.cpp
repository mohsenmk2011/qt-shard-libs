#include "jooyasettings.h"

JooyaSettings::JooyaSettings(QObject *parent) : QObject(parent)
{
}

QVariant JooyaSettings::get(QString key)
{
    QSettings s;
    return s.value(key).toString();
}

void JooyaSettings::set(QString key, QVariant value)
{
    QSettings s;
    s.setValue(key,value);
    s.sync();
}

int JooyaSettings::getInt(QString key)
{    
    QSettings s;
    if(!s.contains(key)){
        qCritical()<<"settings is not contains " <<key;
        return 0;
    }
    QVariant stringInt=s.value(key);
    return stringInt.toInt();
}

void JooyaSettings::setInt(QString key, int value)
{
    QSettings s;
    s.setValue(key,QVariant::fromValue(value));
    s.sync();
}
