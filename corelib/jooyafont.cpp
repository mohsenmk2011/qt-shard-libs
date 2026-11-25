#include "jooyafont.h"

JooyaFont::JooyaFont(QObject *parent) : QObject(parent)
{

}

void JooyaFont::installDefaultFont(QString fontPath)
{
    qint32 fontId = QFontDatabase::addApplicationFont(fontPath);
    QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);

    QString family = fontList.at(0);
    QGuiApplication::setFont(QFont(family));
}
