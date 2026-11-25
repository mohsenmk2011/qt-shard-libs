#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include<QQuickPaintedItem>
#include<qbrush.h>
#include<qpainter.h>
#include<QPainterPath>

class Triangle : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit Triangle(QObject *parent = nullptr);

    QColor color();
    void setColor(QColor c);
    void paint(QPainter *painter);
protected:
signals:
    void colorChanged();

private:
    QColor m_Color;
    bool m_needUpdate;
};

#endif // TRIANGLE_H
