#ifndef MANAGERTOOL_H
#define MANAGERTOOL_H

#include <QObject>
#include<jooyanetwork.h>

class PrivateKeyTool : public JooyaNetwork
{
    Q_OBJECT
public:
    explicit PrivateKeyTool(QObject *parent = nullptr);

    Q_INVOKABLE void isPirvateKeyExists();
    Q_INVOKABLE void deletePrivateKey();
    Q_INVOKABLE void createPrivateKey();

signals:

private slots:
    void pirvateKeyRequestFinished();
};

#endif // MANAGERTOOL_H
