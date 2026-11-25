#ifndef MATERIALTHEMES_H
#define MATERIALTHEMES_H

#include <QObject>

class MaterialThemes : public QObject
{
    Q_OBJECT
public:
    enum class MaterialThemesEnum:unsigned int
    {
        Light =0,
        Dark=1,
    };
    Q_ENUM(MaterialThemesEnum)
};

#endif // MATERIALTHEMES_H
