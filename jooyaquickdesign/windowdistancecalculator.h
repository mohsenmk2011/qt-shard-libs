#ifndef WINDOWDISTANCECALCULATOR_H
#define WINDOWDISTANCECALCULATOR_H

#include <QObject>
#include<QDebug>

class WindowDistanceCalculator : public QObject
{
    Q_OBJECT
public:
    explicit WindowDistanceCalculator(QObject *parent = nullptr);

    Q_PROPERTY(float distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(float newDistance READ newDistance WRITE setNewDistance NOTIFY newDistanceChanged)
    Q_PROPERTY(float baseWidth READ baseWidth WRITE setBaseWidth NOTIFY baseWidthChanged)
    Q_PROPERTY(float currentWidth READ currentWidth WRITE setCurrentWidth NOTIFY currentWidthChanged)
    Q_PROPERTY(float fixNumber READ fixNumber WRITE setFixNumber NOTIFY fixNumberChanged)

    float distance();
    void setDistance(float d);

    float newDistance();
    void setNewDistance(float nm);

    float baseWidth();
    void setBaseWidth(float bw);

    float currentWidth();
    void setCurrentWidth(float cw);

    float fixNumber();
    void setFixNumber(float fn);

signals:
    void distanceChanged();
    void newDistanceChanged();
    void baseWidthChanged();
    void currentWidthChanged();
    void fixNumberChanged();

public slots:
private:
    float m_Distance;
    float m_NewDistance;
    float m_BaseWidth;
    float m_CurrentWidth;
    float m_FixNumber;
    void calculateFixNumber();
    void calculateNewDistance();
};

#endif // WINDOWDISTANCECALCULATOR_H
