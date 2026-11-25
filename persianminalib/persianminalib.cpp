#include "persianminalib.h"

PersianMinaLib::PersianMinaLib()
{
}

void PersianMinaLib::registerTypes()
{
    qmlRegisterType<MinaPattern>("Jooya",1,0,"MinaPattern");    
    qmlRegisterType<Triangle>("Jooya",1,0,"Triangle");
    qmlRegisterType<MinaRectangle>("Jooya",1,0,"MinaRectangle");
    qmlRegisterType<MinaCircle>("Jooya",1,0,"MinaCircle");
//    qmlRegisterUncreatableType<PermissionTypes>("Jooya",1,0,"PermissionTypes","Permission Types");
}
