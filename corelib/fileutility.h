#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <QObject>
#include<QFile>
#include<jooyanetworkengine.h>
#include<QByteArray>
#include<QUrl>

class FileUtility : public QObject
{
    Q_OBJECT
public:
    explicit FileUtility(QObject *parent = nullptr);

    void save(QByteArray bytes, QString fileName);

    QByteArray load(QUrl fileName);

//    virtual bool wirteToFile(QJsonObject obj,QString fileName);
//    virtual QString readFromFile(QString fileName);

signals:

public slots:
};

#endif // FILEUTILITY_H
