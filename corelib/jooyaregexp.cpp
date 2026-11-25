#include "jooyaregexp.h"

JooyaRegExp::JooyaRegExp(QObject *parent) : QObject(parent)
{

}

bool JooyaRegExp::isDigit(QString str)
{
    QRegularExpression re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.match(str).hasMatch())
    {
        return true;
    }
    return false;
}
