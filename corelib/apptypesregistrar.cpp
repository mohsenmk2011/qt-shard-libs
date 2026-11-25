#include "apptypesregistrar.h"

AppTypesRegistrar::AppTypesRegistrar(QObject *parent): QObject(parent)
{

}
void AppTypesRegistrar::registerAllQmlTypes()
{
    qDebug() << "=== AppTypesRegistrar::registerAllQmlTypes() ===";
    registerLibQmlTypes();
    registerAppQmlTypes();
}

void AppTypesRegistrar::registerLibQmlTypes()
{
    qDebug() << "=== AppTypesRegistrar::registerLibTypes() ===";

}
void AppTypesRegistrar::registerAppQmlTypes()
{
    qDebug() << "=== AppTypesRegistrar::registerAppQmlTypes() ===";
}
