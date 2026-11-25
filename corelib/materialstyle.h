#ifndef MATERIALSTYLE_H
#define MATERIALSTYLE_H

#include <QObject>
#include<materialstylehelper.h>
#include<jooyaapplication.h>
#include<QtQml>

class MaterialStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MaterialColors::MaterialColorsEnum primary READ primary CONSTANT)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum secondary READ secondary CONSTANT)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum tertiary READ tertiary CONSTANT)
    Q_PROPERTY(MaterialThemes::MaterialThemesEnum theme READ theme CONSTANT)

    Q_PROPERTY(QColor primary50 READ primary50 CONSTANT)
    Q_PROPERTY(QColor primary100 READ primary100 CONSTANT)
    Q_PROPERTY(QColor primary200 READ primary200 CONSTANT)
    Q_PROPERTY(QColor primary300 READ primary300 CONSTANT)
    Q_PROPERTY(QColor secondary50 READ secondary50 CONSTANT)
    Q_PROPERTY(QColor secondary100 READ secondary100 CONSTANT)
    Q_PROPERTY(QColor secondary200 READ secondary200 CONSTANT)
    Q_PROPERTY(QColor secondary300 READ secondary300 CONSTANT)
    Q_PROPERTY(QColor secondary400 READ secondary400 CONSTANT)
    Q_PROPERTY(QColor secondary500 READ secondary500 CONSTANT)
    Q_PROPERTY(QColor secondary600 READ secondary600 CONSTANT)
    Q_PROPERTY(QColor secondary700 READ secondary700 CONSTANT)
    Q_PROPERTY(QColor secondary800 READ secondary800 CONSTANT)
    Q_PROPERTY(QColor secondary900 READ secondary900 CONSTANT)
    Q_PROPERTY(QColor tertiary50 READ tertiary50 CONSTANT)
    Q_PROPERTY(QColor tertiary100 READ tertiary100 CONSTANT)
    Q_PROPERTY(QColor tertiary200 READ tertiary200 CONSTANT)
    Q_PROPERTY(QColor tertiary300 READ tertiary300 CONSTANT)
    Q_PROPERTY(QColor tertiary400 READ tertiary400 CONSTANT)
    Q_PROPERTY(QColor tertiary500 READ tertiary500 CONSTANT)
    Q_PROPERTY(QColor tertiary600 READ tertiary600 CONSTANT)
    Q_PROPERTY(QColor tertiary700 READ tertiary700 CONSTANT)
    Q_PROPERTY(QColor tertiary800 READ tertiary800 CONSTANT)
    Q_PROPERTY(QColor tertiary900 READ tertiary900 CONSTANT)

    Q_PROPERTY(QColor primaryTextColor READ primaryTextColor CONSTANT)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor CONSTANT)
    Q_PROPERTY(bool useWhiteBackColor READ useWhiteBackColor CONSTANT)

    QML_ATTACHED(MaterialStyleHelper)
    QML_ELEMENT
public:
    explicit MaterialStyle(QObject *parent = nullptr);

    static MaterialStyleHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_MaterialStyleHelper;
    }

    MaterialColors::MaterialColorsEnum primary() const;
    MaterialColors::MaterialColorsEnum secondary() const;
    MaterialColors::MaterialColorsEnum tertiary() const;
    MaterialThemes::MaterialThemesEnum theme() const;

    QColor primary50() const;
    QColor primary100() const;
    QColor primary200() const;
    QColor primary300() const;
    QColor secondary50() const;
    QColor secondary100() const;
    QColor secondary200() const;
    QColor secondary300() const;
    QColor secondary400() const;
    QColor secondary500() const;
    QColor secondary600() const;
    QColor secondary700() const;
    QColor secondary800() const;
    QColor secondary900() const;
    QColor tertiary50() const;
    QColor tertiary100() const;
    QColor tertiary200() const;
    QColor tertiary300() const;
    QColor tertiary400() const;
    QColor tertiary500() const;
    QColor tertiary600() const;
    QColor tertiary700() const;
    QColor tertiary800() const;
    QColor tertiary900() const;

    QColor primaryTextColor() const;
    QColor secondaryTextColor() const;
    bool useWhiteBackColor() const;

private:
};

#endif // MATERIALSTYLE_H
