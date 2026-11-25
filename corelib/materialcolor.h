#ifndef MATERIALCOLOR_H
#define MATERIALCOLOR_H

#include <QObject>
#include<QtGui/QColor>
#include<materialshades.h>
#include<materialcolors.h>

class MaterialColor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MaterialColors::MaterialColorsEnum color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(MaterialShades::MaterialShadesEnum shade READ shade WRITE setShade NOTIFY shadeChanged)
    Q_PROPERTY(QColor colorName READ colorName CONSTANT)

public:
    explicit MaterialColor(QObject *parent = nullptr);
    explicit MaterialColor(MaterialColors::MaterialColorsEnum c);


    MaterialColors::MaterialColorsEnum color();
    void setColor(MaterialColors::MaterialColorsEnum c);


    MaterialShades::MaterialShadesEnum shade();
    void setShade(MaterialShades::MaterialShadesEnum s);

    QColor colorName();
    static QRgb colors[20][14];
    static QRgb darkColors[20];
    Q_INVOKABLE QColor getColor(MaterialColors::MaterialColorsEnum color, MaterialShades::MaterialShadesEnum shade = MaterialShades::MaterialShadesEnum::Shade500);
    Q_INVOKABLE QColor darkColor(MaterialColors::MaterialColorsEnum color);

signals:
    void colorChanged();
    void shadeChanged();
private:
    MaterialColors::MaterialColorsEnum m_Color;
    MaterialShades::MaterialShadesEnum m_Shade;
};

#endif // MATERIALCOLOR_H
