#include "jooyalistitem.h"

JooyaListItem::JooyaListItem(QObject *parent) : JooyaNetwork{parent}
{
    m_IsSelected=false;
    m_IsLastItem=false;
    m_Guid="";
}

bool JooyaListItem::isLastItem()
{
    return m_IsLastItem;
}

void JooyaListItem::setIsLastItem(bool i)
{
    if(m_IsLastItem!=i){
        m_IsLastItem=i;
        emit isLastItemChanged();
    }
}

bool JooyaListItem::isSelected()
{
    return m_IsSelected;
}

void JooyaListItem::setIsSelected(bool selected)
{
    if(m_IsSelected!=selected){
        m_IsSelected=selected;
        emit isSelectedChanged();
    }
}

QString JooyaListItem::guid()
{
    return m_Guid;
}

void JooyaListItem::setGuid(QString g)
{
    if(m_Guid!=g){
        m_Guid=g;
        emit guidChanged();
    }
}
