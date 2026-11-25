#ifndef QMLLIVE_H
#define QMLLIVE_H

#include <QObject>
#include<QtQml>
#include<filewatcher.h>
#include<jooyanetworkengine.h>

class QmlLive : public QObject
{
    Q_OBJECT
    QML_ATTACHED(FileWatcher)
    QML_ANONYMOUS
public:

    static FileWatcher *qmlAttachedProperties(QObject *object)
    {
        Q_UNUSED(object)
        qCritical()<<" return new FileWatcher();";
        return JooyaNetworkEngine::m_FileWather;
    }
};

#endif // QMLLIVE_H
