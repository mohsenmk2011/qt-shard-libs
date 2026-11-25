#ifndef MINARECTANGLE_H
#define MINARECTANGLE_H

#include <QObject>
#include<QQuickItem>
#include<QSGGeometryNode>
#include<QSGFlatColorMaterial>

class MinaRectangle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit MinaRectangle(QObject *parent = nullptr);

    QColor color();
    void setColor(QColor c);
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
signals:
    void colorChanged();

private:
    QColor m_Color;
    bool m_needUpdate;
};

#endif // MINARECTANGLE_H
