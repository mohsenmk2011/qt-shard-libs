#ifndef JOOYALISTITEM_H
#define JOOYALISTITEM_H

#include <QObject>
#include<jooyanetwork.h>

class JooyaListItem : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(bool isLastItem READ isLastItem WRITE setIsLastItem NOTIFY isLastItemChanged)
    Q_PROPERTY(bool isSelected READ isSelected WRITE setIsSelected NOTIFY isSelectedChanged)
    Q_PROPERTY(QString guid READ guid WRITE setGuid NOTIFY guidChanged)
public:
    explicit JooyaListItem(QObject *parent = nullptr);

    bool isLastItem();
    void setIsLastItem(bool i);

    bool isSelected();
    void setIsSelected(bool selected);

    QString guid();
    void setGuid(QString g);
signals:
    void isLastItemChanged();
    void isSelectedChanged();
    void needToSaveInFile();
    void guidChanged();
private:
    bool m_IsLastItem;
    bool m_IsSelected;
    QString m_Guid;
};

#endif // JOOYALISTITEM_H
