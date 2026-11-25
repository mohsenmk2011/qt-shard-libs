#ifndef MINAPATTERN_H
#define MINAPATTERN_H

#include <QObject>
#include<QColor>

class MinaPattern : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
public:
    explicit MinaPattern(QObject *parent = nullptr);

    QColor backColor();
    void setBackColor(QColor bc);
signals:
    void backColorChanged();
private:
    QColor m_BackColor;

};

#endif // MINAPATTERN_H
