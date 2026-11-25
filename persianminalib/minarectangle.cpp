#include "minarectangle.h"

MinaRectangle::MinaRectangle(QObject *parent) : QQuickItem()
{
    m_needUpdate=true;
    setColor(Qt::red);
    setFlag(QQuickItem::ItemHasContents);
}

QColor MinaRectangle::color()
{
    return m_Color;
}

void MinaRectangle::setColor(QColor c)
{
    if(m_Color != c) {
        m_Color = c;
        //            m_needUpdate = true;
        update();
        colorChanged();
    }
}

QSGNode *MinaRectangle::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{

    Q_UNUSED(updatePaintNodeData)
    QSGGeometryNode *root = static_cast<QSGGeometryNode *>(oldNode);

    if(!root) {
        root = new QSGGeometryNode;
        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
        geometry->setDrawingMode(GL_TRIANGLE_FAN);
        geometry->vertexDataAsPoint2D()[0].set(0, 0);
        geometry->vertexDataAsPoint2D()[1].set(width(), 0);
        geometry->vertexDataAsPoint2D()[2].set(width(), height());
        geometry->vertexDataAsPoint2D()[3].set(0, height());

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
