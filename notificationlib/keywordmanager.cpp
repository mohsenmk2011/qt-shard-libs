#include "keywordmanager.h"

KeywordManager::KeywordManager(QObject *parent) : ListManager(parent)
{
    setTakeCount(15);
}

void KeywordManager::getList(int parentId)
{
    if(listHasCompeleted()){
        return;
    }
    QNetworkReply* r=getRequest(QString("api/Keyword?parentId=%1&skipcount=%2&count=%3").arg(parentId).arg(skipCount()).arg(takeCount()));
    connect(r,SIGNAL(finished()),this,SLOT(getListFinished()));
}

KeywordListModel *KeywordManager::listModel()
{
    return &m_ListModel;
}

void KeywordManager::addNewItem(int parentId)
{
    m_ListModel.add(new Keyword(parentId));
}

void KeywordManager::getListFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonArray ja=jsonUtility()->convertToJsonArray(r->readAll());
        for (int i = 0; i < ja.count(); ++i) {
            Keyword* k=new Keyword();
            k->loadFromJson(ja.at(i).toObject());
            m_ListModel.add(k);
        }
    }
    else if (r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==404) {
        setListHasCompeleted(true);
        if(m_ListModel.rowCount()<=0)
        {
            message()->setContent("کلمه کلیدی دیگری یافت نشد");
        }
    }
    else {
        qDebug()<<"Error";
        showMessage(r);
    }
    setIsProcssing(false);
}
