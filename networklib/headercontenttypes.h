#ifndef HEADERCONTENTTYPES_H
#define HEADERCONTENTTYPES_H

#include <QObject>

class HeaderContentTypes : public QObject
{
    Q_OBJECT
public:
    enum class HeaderContentTypesEnum:unsigned int{
        Json=0,
        Form=1,
        MultiPart=2,
    };
    Q_ENUM(HeaderContentTypesEnum)
};

#endif // HEADERCONTENTTYPES_H
