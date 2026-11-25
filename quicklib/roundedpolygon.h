#ifndef ROUNDEDPOLYGON_H
#define ROUNDEDPOLYGON_H

#include<QPainterPath>
#include<QPolygonF>
#include<qdebug.h>
#include<QPointF>
#include <math.h>

class RoundedPolygon : public QPolygonF
{
public:
    explicit RoundedPolygon();

    void SetRadius(unsigned int radius);
    const QPainterPath& GetPath();

private:
    QPointF GetLineStart(int i) const;
    QPointF GetLineEnd(int i) const;
    float GetDistance(QPointF pt1, QPointF pt2) const;
    QPainterPath m_path;
    unsigned int m_Radius;

signals:

};

#endif // ROUNDEDPOLYGON_H
