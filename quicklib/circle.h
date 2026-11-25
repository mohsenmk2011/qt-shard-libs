#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include<quickitem.h>

class Circle : public QuickItem
{
    Q_OBJECT
public:
    explicit Circle(QObject *parent = nullptr);

signals:

};

#endif // CIRCLE_H
