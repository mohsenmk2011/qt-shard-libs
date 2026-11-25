#include "listmanager.h"

ListManager::ListManager(QObject *parent) : JooyaListItem(parent)
{    
    m_SelectedCount=0;
    m_SelectMode=false;
    m_SkipCount=0;
    m_TakeCount=5;
    m_ListHasCompeleted=false;
    m_LastTakedCount=0;
    m_isSearching = false;
}

void ListManager::toJsonFile(QString fileName, QJsonArray array)
{
    File file;
    file.setImageName(fileName);
    file.setExt("json");
    file.saveJson(array);
}

QJsonArray ListManager::fromJsonFile(QString name)
{
    File file;
    file.setImageName(name);
    file.setExt("json");
    if(file.exists())
    {
        return jsonUtility()->convertToJsonArray(file.read());
    }
    else{
        return QJsonArray();
    }
}

QNetworkReply *ListManager::getListAndReturnArray(QString url)
{
    qDebug()<<"is going to get list of entity";
    QNetworkReply* reply= getRequest(QString(url+"?skipcount=%1&count=%2").arg(skipCount()).arg(takeCount()));
    connect(reply,&QNetworkReply::finished,this,&ListManager::onGetList);
    return reply;
}

bool ListManager::canGetList()
{
    if(isProcessing())
    {
        qDebug()<<"isProcessing -> return";
        return false;
    }
    if(listHasCompeleted())
    {
        qDebug()<<"there is no more entity !!! -> return";
        return false;
    }
    return true;
}

void ListManager::onGetList()
{
    QNetworkReply* r=convertToReply(sender());
    qDebug()<<"getting list of entity finished";
    if(r->error()==QNetworkReply::NoError)
    {
        qInfo()<<"with no error";
        QJsonArray array=jsonUtility()->convertToJsonArray(r->readAll());
        setLastTakedCount(array.count());
        emit requestSucceedWithArray(array);
    }
    else if(isNotFound(r))
    {
        qInfo()<<"entities list finished";
        setListHasCompeleted(true);
        emit noMoreEntity();
    }
    else
    {
        showMessage(r);
    }
}

void ListManager::deselectAll()
{

}

void ListManager::selectAll()
{

}

int ListManager::takeCount()
{
    return m_TakeCount;
}

void ListManager::setTakeCount(int tc)
{
    m_TakeCount = tc;
}

int ListManager::skipCount()
{
    return m_SkipCount;
}
void ListManager::addSkipCount(int val)
{
    m_SkipCount+=val;
}

void ListManager::resetListValues()
{
    m_SelectedCount=0;
    m_LastTakedCount=0;
    setSelectMode(false);

    setSkipCount(0);
    setTakeCount(5);
    setIsSearching(false);
    setListHasCompeleted(false);
}

bool ListManager::selectMode()
{
    return m_SelectMode;
}

void ListManager::setSelectMode(bool s)
{
    if(m_SelectMode!=s){
        m_SelectMode=s;
        if(!s){
            deselectAll();
        }
        emit selectModeChanged();
    }
}

int ListManager::selectedCount()
{
    return m_SelectedCount;
}

void ListManager::setSelectedCount(int s)
{
    if(m_SelectedCount!=s){
        m_SelectedCount=s;
        emit selectedCountChanged();
    }
}

void ListManager::setSkipCount(int sc)
{
    if(sc!=m_SkipCount){
        m_SkipCount=sc;
    }
}

int ListManager::lastTakedCount()
{
    return m_LastTakedCount;
}

void ListManager::setLastTakedCount(int ltc)
{
        m_LastTakedCount=ltc;
        if(!isSearching()){
            addSkipCount(m_LastTakedCount);
        }
        if(m_LastTakedCount<takeCount()){
            setListHasCompeleted(true);
        }
}

bool ListManager::listHasCompeleted()
{
    return m_ListHasCompeleted;
}

void ListManager::setListHasCompeleted(bool lhc)
{
    if(lhc!=m_ListHasCompeleted){
        m_ListHasCompeleted=lhc;
    }
}

bool ListManager::isSearching() const
{
    return m_isSearching;
}

void ListManager::setIsSearching(bool newIsSearching)
{
    if (m_isSearching == newIsSearching)
        return;
    m_isSearching = newIsSearching;
    emit isSearchingChanged();
}
