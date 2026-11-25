#include "contactmanager.h"

ContactManager::ContactManager(QObject *parent) : ListManager(parent)
{
    m_Me=new Contact();
    m_Me->setIsMe(true);
    qCritical()<<"########################getmenow######################################";
    m_Me->getFromServer();
    loadFromFile();
    connect(m_WebSocketHandler,&WebSocketHandler::newInfoReceived,this,&ContactManager::onNewInfoReceived);
}

void ContactManager::onNewInfoReceived(WebSocketInfo *info)
{
    //when you send this(IAmOnline) a NewConnection will be send to all online users(that you reciced here
    if(info->type()=="NewConnection"){
        qDebug()<<"Receive IAmOnline from";
        qInfo()<<"Update Last View Date Of user";
        QJsonObject talkStatusObj=jsonUtility()->convertToJsonObject(info->information());
        NewConnectionModel* cm=new NewConnectionModel(talkStatusObj);

        for (int i = 0; i < m_ListModel.rowCount(); ++i) {
            if(cm->userId()==m_ListModel.at(i)->userId()){
                Contact* c=m_ListModel.at(i);
                if(cm->isAdded()){
                    c->setIsOnline(true);
                }
                else{
                    c->setIsOffline(true);
                }
                c->setLastActivityDate(QDateTime::currentDateTime());
                break;
            }
        }
    }
}

void ContactManager::loadFromFile()
{
    QJsonArray jsonChats= fromJsonFile("contacts");

    bool isMeFound=false;
    for (int i = 0; i < jsonChats.count(); ++i) {
        qDebug()<<"jsonChats.at(i).toObject() ==> "<<jsonChats.at(i).toObject();
        Contact* item=new Contact(jsonChats.at(i).toObject());
        if(item->isMe()){
            isMeFound=true;
           m_Me=item;
        }
        m_ListModel.add(item);
    }
    if(!isMeFound||(isMeFound&&me()->userId().isEmpty())){
        me()->getFromServer();
    }
}

ContactManager::~ContactManager()
{
    saveInFile();
}

void ContactManager::saveInFile()
{
    qDebug()<<"toJsonArray() ==> "<<toJsonArray();
    toJsonFile("contacts",toJsonArray());
}

QJsonArray ContactManager::toJsonArray()
{
    QJsonArray array;

    for (int i = 0; i < m_ListModel.rowCount(); ++i) {
        Contact* c=m_ListModel.at(i);

        array.append(c->toJson());
    }
    return array;
}

void ContactManager::getList()
{
    QNetworkReply* reply=getRequest("api/Contact");
    connect(reply,&QNetworkReply::finished,this,&ContactManager::onGetListFinished);
}

ContactListModel *ContactManager::listModel()
{
    return &m_ListModel;
}

Contact *ContactManager::me()
{
    return m_Me;
}

void ContactManager::onGetListFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonArray contacts=jsonUtility()->convertToJsonArray(r->readAll());
        qDebug()<<" is adding contacts "<<contacts.count()<<" to listmodel";
        foreach(QJsonValue c,contacts){
            qDebug()<<"find contact by id=> "<<c.toObject().value("userId").toString();
            Contact* currentContact= m_ListModel.find(c.toObject().value("userId").toString());
            if(currentContact==nullptr){
                qDebug()<<"contact not found=> add as new contact";
                Contact* nc=new Contact(c.toObject());
                if(nc->isMe()){
                    qInfo()<<"found isMe=>"<<nc->isMe();
                    m_Me=nc;
                }
                else {
                    m_ListModel.add(nc);
                    nc->download();
                }
            }
            else{
                qInfo()<<"contact found=> update contact";
                currentContact->fromJson(c.toObject());
            }
        }
        qInfo()<<"count of contacts => "<<m_ListModel.rowCount();
    }
    else{
        showMessage(r);
    }
}

