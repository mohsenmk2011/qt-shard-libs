#ifndef MATERIALSHADES_H
#define MATERIALSHADES_H

#include <QObject>

class MaterialShades : public QObject
{
    Q_OBJECT
public:
    enum class MaterialShadesEnum {
        Shade50,
        Shade100,
        Shade200,
        Shade300,
        Shade400,
        Shade500,
        Shade600,
        Shade700,
        Shade800,
        Shade900,
        ShadeA100,
        ShadeA200,
        ShadeA400,
        ShadeA700,
    };
    Q_ENUM(MaterialShadesEnum)
};

#endif // MATERIALSHADES_H
