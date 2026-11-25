#ifndef JOOYAX509CERTIFICATE_H
#define JOOYAX509CERTIFICATE_H

#include <QObject>
#include<jooyanetwork.h>

class JooyaX509Certificate : public JooyaNetwork
{
    Q_OBJECT
public:
    explicit JooyaX509Certificate(QObject *parent = nullptr);

    Q_INVOKABLE void getInfo();    
    Q_INVOKABLE void save();
signals:

public slots:
private slots:
    void getInfoFinished();
    void saveFinished();
};

#endif // JOOYAX509CERTIFICATE_H
