#ifndef PACKAGEINFOMANAGER_H
#define PACKAGEINFOMANAGER_H

#include <QObject>
#include<QDebug>
#include<jooyaandroidcontext.h>
#if defined(Q_OS_ANDROID)
#include<QJniObject>
#include<QJniEnvironment>
#include <QCoreApplication>
#endif

class PackageInfoManager : public QObject
{
    Q_OBJECT
public:
    explicit PackageInfoManager(QObject *parent = nullptr);
    Q_INVOKABLE QString getAppSign();
    Q_INVOKABLE QString getApkHash();
    static QString getPackageName(QString charSeperator = "/");
    static QString getApplicationName();

signals:

};

#endif // PACKAGEINFOMANAGER_H
