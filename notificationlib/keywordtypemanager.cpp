#include "keywordtypemanager.h"

KeywordTypeManager::KeywordTypeManager(QObject *parent) : JooyaNetwork(parent)
{

}

void KeywordTypeManager::getList()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/KeywordType");
    connect(r,SIGNAL(finished()),this,SLOT(getListFinished()));
}

KeywordTypeListModel *KeywordTypeManager::listModel()
{
    return &m_ListModel;
}

void KeywordTypeManager::addNewItem()
{
    m_ListModel.add(new KeywordType());
}

void KeywordTypeManager::getListFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError)
    {
        QJsonArray kts= jsonUtility()->convertToJsonArray(r->readAll());
        for (int i = 0; i < kts.count(); ++i) {
            m_ListModel.add(new KeywordType(kts.at(i).toObject()));
        }
    }
    else {
        showMessage(r);
    }
    setIsProcssing(false);
}
