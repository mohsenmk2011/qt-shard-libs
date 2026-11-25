#ifndef USERROLES_H
#define USERROLES_H

#include <QObject>

class UserRoles : public QObject
{
    Q_OBJECT
public:
    enum class UserRolesEnum:unsigned int{
        Guest=0,
        Member = 1,
        Admin = 2,
        Admin2 = 3,
        Admin3= 4,
        Admin4= 5
    };
    Q_ENUM(UserRolesEnum)
};

#endif // USERROLES_H
