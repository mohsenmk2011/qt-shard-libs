#include "jooyaquickdesign.h"

JooyaQuickDesign::JooyaQuickDesign()
{
}

void JooyaQuickDesign::registerTypes()
{
    qmlRegisterType<WindowSizeManager>("Jooya",1,0,"WindowSizeManager");
    qmlRegisterType<WindowDistanceCalculator>("Jooya",1,0,"WindowDistanceCalculator");

}
