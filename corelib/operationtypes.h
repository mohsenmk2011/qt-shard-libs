#ifndef OPERATIONTYPES_H
#define OPERATIONTYPES_H

#include <QObject>

class OperationTypes : public QObject
{
    Q_OBJECT
public:
    enum class OperationTypesEnum:unsigned int
    {
        NoOperation=0,
        IsGettingList=1,
        IsAddingNew=2,
        IsEditing=3,
        IsDeleting=4,
    };
    Q_ENUM(OperationTypesEnum)
};

#endif // OPERATIONTYPES_H
