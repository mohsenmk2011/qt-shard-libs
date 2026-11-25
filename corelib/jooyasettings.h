#ifndef JOOYASETTINGS_H
#define JOOYASETTINGS_H

#include <QObject>
#include <QCoreApplication>
#include<QSettings>
#include<qdebug.h>
#include<datetimeutility.h>

class JooyaSettings : public QObject
{
    Q_OBJECT
public:
    explicit JooyaSettings(QObject *parent = nullptr);

    QVariant get(QString key);
    void set(QString key,QVariant value);

    int getInt(QString key);
    void setInt(QString key,int value);
    DateTimeUtility m_DateTimeUtility;
signals:

private:
};

#endif // JOOYASETTINGS_H
