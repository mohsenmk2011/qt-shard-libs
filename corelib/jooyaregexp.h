#ifndef JOOYAREGEXP_H
#define JOOYAREGEXP_H

#include <QObject>
#include<QRegularExpression>

class JooyaRegExp : public QObject
{
    Q_OBJECT
public:
    explicit JooyaRegExp(QObject *parent = nullptr);
    bool isDigit(QString str);

signals:

};

#endif // JOOYAREGEXP_H
