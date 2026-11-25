#ifndef MATERIALCOLORS_H
#define MATERIALCOLORS_H

#include <QObject>

class MaterialColors : public QObject
{
    Q_OBJECT
public:
    enum class MaterialColorsEnum:unsigned int
    {
        Red=0,
        Pink,
        Purple,
        DeepPurple,
        Indigo,
        Blue,
        LightBlue,
        Cyan,
        Teal,
        Green,
        LightGreen,
        Lime,
        Yellow,
        Amber,
        Orange,
        DeepOrange,
        Brown,
        Grey,
        BlueGrey,
        White,
    };
    Q_ENUM(MaterialColorsEnum)

};

#endif // MATERIALCOLORS_H
