#ifndef QUICKITEM_H
#define QUICKITEM_H

#include <QObject>
#include<QQuickPaintedItem>
#include<QColor>

class QuickItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit QuickItem(QObject *parent = nullptr);

    QColor color();
    void setColor(QColor c);
signals:
    void colorChanged();
private:
    QColor m_Color;
};

#endif // QUICKITEM_H
