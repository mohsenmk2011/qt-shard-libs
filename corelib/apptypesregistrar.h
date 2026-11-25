#ifndef APPTYPESREGISTRAR_H
#define APPTYPESREGISTRAR_H

#include <QQmlEngine>
#include<QObject>

// Base class for registering QML types.
// Every application extends this class and implements registerAppQmlTypes()
// with its own qmlRegisterType calls, then calls registerAllQmlTypes() from main().
class AppTypesRegistrar: public QObject
{
    Q_OBJECT
public:
    explicit AppTypesRegistrar(QObject *parent = nullptr);

    // Entry point: registers the shared jooya libs, then the app-specific types.
    void registerAllQmlTypes();

protected:
    // Registers the common jooya libs (same for every application).
    virtual void registerLibQmlTypes() = 0;

    // Each application implements this with its own qmlRegisterType calls.
    virtual void registerAppQmlTypes() = 0;
};

#endif // APPTYPESREGISTRAR_H
