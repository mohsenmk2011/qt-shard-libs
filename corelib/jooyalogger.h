#ifndef JOOYALOGGER_H
#define JOOYALOGGER_H

#include <QObject>

class JooyaLogger : public QObject
{
    Q_OBJECT
public:
    explicit JooyaLogger(QObject *parent = nullptr);

signals:

};

#endif // JOOYALOGGER_H
