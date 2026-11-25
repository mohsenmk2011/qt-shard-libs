#include "notifymanager.h"

NotifyManager::NotifyManager(QObject *parent) : JooyaNetwork (parent)
{

}

NotificationTypes::NotificationTypesEnum NotifyManager::currentType()
{
    return m_CurrentType;
}

void NotifyManager::setCurrentType(NotificationTypes::NotificationTypesEnum type)
{
    if(m_CurrentType!=type){
        m_CurrentType=type;
        emit currentTypeChanged();
        qDebug()<<"current type changed to =>"<<type;
    }
}

void NotifyManager::getList()
{
    m_ListModel.removeRows();
    QMetaEnum me=QMetaEnum::fromType<NotificationTypes::NotificationTypesEnum>();
    qInfo()<<"Is Getting Notifications of type => "<<me.valueToKey((int)currentType());
    setIsProcssing(true);
    QNetworkReply* r=getRequest(QString("api/Notify?type=%1").arg((int)currentType()));
    connect(r,SIGNAL(finished()),this,SLOT(getListFinished()));
}

void NotifyManager::getListFinished()
{
    QNetworkReply* reply=convertToReply(sender());
    if(reply->error()==QNetworkReply::NoError)
    {
        QJsonArray array=jsonUtility()->convertToJsonArray(reply->readAll());
        for(int i = 0; i < array.count(); ++i) {
            Notify* e=new Notify(jsonUtility()->convertToJsonObject(array.at(i)));
           e->download();
            m_ListModel.addItem(e);
        }
        emit gettingListSucceed();
    }
    else
    {
        showMessage(reply);
    }
}

void NotifyManager::getNewCount(int versionCode)
{
    qInfo()<<"Is Getting new notification count";
    if(!loginInfo()->isLoggedIn()){
        qCritical()<<"%%%[ Is Not Logged In For get Notification]%%%";
        return;
    }
    setIsProcssing(true);
    QNetworkReply* r=getRequest(QString("api/Notify/IsNew?versionCode=%1").arg(versionCode));
    connect(r,SIGNAL(finished()),this,SLOT(getNewCountFinished()));
}
void NotifyManager::getNewCountFinished()
{
    QNetworkReply* reply=convertToReply(sender());
    if(reply->error()==QNetworkReply::NoError)
    {
        QString resp=reply->readAll();
        qInfo()<<resp;
        m_Counts->loadFromJson(jsonUtility()->convertToJsonObject(resp/*reply->readAll()*/));
    }
    else
    {
        showMessage(reply);
    }
}

void NotifyManager::refreshLastViewDate()
{
    if(!loginInfo()->isLoggedIn()){
        qDebug()<<"Is not isLoggedIn so don't need to save last view date";
        emit refreshLastViewSucceed(true);
        return;
    }
    if(m_Counts->getHasSeen(currentType())){
        qDebug()<<"has seen before-> last view date";
        emit refreshLastViewSucceed(true);
        return;
    }
    QNetworkReply* r=getRequest(QString("api/Notify/RefreshViewDate?type=%1").arg((int)currentType()));
    connect(r,SIGNAL(finished()),this,SLOT(refreshViewDateFinished()));
}
void NotifyManager::refreshViewDateFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        qInfo()<<"No Error";
        listModel()->removeRows();
        m_Counts->setHasSeen(currentType());
        emit refreshLastViewSucceed(true);
    }
    else {
        qCritical()<<"Error";
        showMessage(r);
        emit refreshLastViewSucceed(false);
    }
    setIsProcssing(false);
}

void NotifyManager::addNew()
{
    Notify* n=new Notify(currentType());
    listModel()->addItem(n);
    emit selectLastIndex(listModel()->rowCount()-1);
}

NotifyListModel *NotifyManager::listModel()
{
    return &m_ListModel;
}

NotificationCounts* NotifyManager::m_Counts=new NotificationCounts();
