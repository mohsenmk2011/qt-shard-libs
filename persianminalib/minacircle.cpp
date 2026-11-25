#include "minacircle.h"

MinaCircle::MinaCircle(QObject *parent) : QQuickItem()
{
    m_needUpdate=true;
    setColor(Qt::red);
    setFlag(QQuickItem::ItemHasContents);
    m_Degree=360;
    deg2Rad = 3.14159/180;
}

QColor MinaCircle::color()
{
    return m_Color;
}

void MinaCircle::setColor(QColor c)
{
    if(m_Color != c) {
        m_Color = c;
        //            m_needUpdate = true;
        update();
        colorChanged();
    }
}

float MinaCircle::degree()
{
    return m_Degree;
}

void MinaCircle::setDegree(float d)
{
    if(m_Degree!=d){
        m_Degree=d;
        emit degreeChanged();
    }
}

QSGNode *MinaCircle::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{

    Q_UNUSED(updatePaintNodeData)
    QSGGeometryNode *root = static_cast<QSGGeometryNode *>(oldNode);

    if(!root) {
        root = new QSGGeometryNode;
        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), degree());
        geometry->setDrawingMode(GL_POLYGON);
        drawCircle(width()/2,geometry);

        root->setGeometry(geometry);
        root->setFlag(QSGNode::OwnsGeometry);
        root->setFlag(QSGNode::OwnsMaterial);
    }

    if(m_needUpdate) {
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_Color);
        root->setMaterial(material);
        m_needUpdate = false;
    }

    return root;
}

void MinaCircle::drawCircle(double radius, QSGGeometry *geometry)
{
    for (int i = 0; i < degree(); ++i)
    {
        double rad = (i - 90) * deg2Rad;
        geometry->vertexDataAsPoint2D()[i].set(cos(rad) * radius + width() / 2, sin(rad) * radius + height() / 2);
    }
}
