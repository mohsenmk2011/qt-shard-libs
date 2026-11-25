#ifndef ISOSCELESTRIANGLEMATH_H
#define ISOSCELESTRIANGLEMATH_H

#include <QObject>
#include <QtMath>

class IsoscelesTriangleMath : public QObject
{
    Q_OBJECT
public:
    explicit IsoscelesTriangleMath(QObject *parent = nullptr);

    Q_INVOKABLE qreal calculateSideLength(qreal chord, qreal angle);
signals:

};

#endif // ISOSCELESTRIANGLEMATH_H
