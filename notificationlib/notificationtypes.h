#ifndef NOTIFICATIONTYPES_H
#define NOTIFICATIONTYPES_H

#include <QObject>

class NotificationTypes : public QObject
{
    Q_OBJECT

//    Q_ENUMS(NotificationTypesEnum)
public:
    enum class NotificationTypesEnum:unsigned int{
        UnKnown=0,
        Discount=1,
        AppIntroducing=2,
        AppUpdate=3,
        Vitreen = 4,
        Story = 5,
    };
    Q_ENUM(NotificationTypesEnum)
};
Q_DECLARE_METATYPE(NotificationTypes::NotificationTypesEnum)

#endif // NOTIFICATIONTYPES_H
