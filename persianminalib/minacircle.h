#ifndef MINACIRCLE_H
#define MINACIRCLE_H

#include <QObject>
#include<QQuickItem>
#include<QSGGeometryNode>
#include<QSGFlatColorMaterial>

class MinaCircle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(float degree READ degree WRITE setDegree NOTIFY degreeChanged)
public:
    explicit MinaCircle(QObject *parent = nullptr);

    QColor color();
    void setColor(QColor c);

    float degree();
    void setDegree(float d);
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
signals:
    void colorChanged();
    void degreeChanged();
private:
    QColor m_Color;
    bool m_needUpdate;
    void drawCircle(double radius, QSGGeometry* geometry);
    float deg2Rad ;
    float m_Degree;

};

#endif // MINACIRCLE_H
