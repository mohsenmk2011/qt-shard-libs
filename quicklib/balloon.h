#ifndef BALLOON_H
#define BALLOON_H

#include <QObject>
#include<QQuickPaintedItem>
#include<quickitem.h>
#include<QColor>
#include<QBrush>
#include<QPainter>
#include<QPainterPath>
#include<roundedpolygon.h>
#include<QPolygonF>

class Balloon : public QuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool rightAligned READ rightAligned WRITE setRightAligned NOTIFY rightAlignedChanged)
    Q_PROPERTY(bool cornerAtTop READ cornerAtTop WRITE setCornerAtTop NOTIFY cornerAtTopChanged)
    Q_PROPERTY(float cornerWidth READ cornerWidth WRITE setCornerWidth NOTIFY cornerWidthChanged)
    Q_PROPERTY(float cornerHeight READ cornerHeight WRITE setCornerHeight NOTIFY cornerHeightChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
public:
    explicit Balloon(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) Q_DECL_OVERRIDE;

    bool rightAligned();
    void setRightAligned(bool r);

    bool cornerAtTop();
    void setCornerAtTop(bool c);

    float cornerWidth();
    void setCornerWidth(float w);

    float cornerHeight();
    void setCornerHeight(float h);

    int radius();
    void setRadius(float r);
signals:
    void rightAlignedChanged();
    void cornerAtTopChanged();
    void cornerWidthChanged();
    void cornerHeightChanged();
    void radiusChanged();

private:
    bool m_RightAligned;
    bool m_CornerAtTop;
    float m_CornerWidth;
    float m_CornerHeight;
    float m_Radius;
    RoundedPolygon getRoundedPath();
};

#endif // BALLOON_H
