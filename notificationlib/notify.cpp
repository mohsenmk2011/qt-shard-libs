#include "notify.h"

Notify::Notify(QObject *parent) : ImageFile(parent)
{
    setAmount(0);
    setDuration(0);
    setBeVisibleForUsers(false);
    m_Type=NotificationTypes::NotificationTypesEnum::UnKnown;
    ApplicationPath ap;
    setFolderPath(ap.notifyimagesFolderPath());
}

Notify::Notify(NotificationTypes::NotificationTypesEnum type):Notify()
{
    setType(type);
}

Notify::Notify(QJsonObject obj):Notify()
{
    loadFromJson(obj);
}

QString Notify::title()
{
    return m_Title;
}

QString Notify::description()
{
    return m_Description;
}

bool Notify::visible()
{
    return  m_Visible;
}

void Notify::setTitle(QString t)
{
    if(t!=m_Title){
        m_Title=t;
        emit titleChanged();
    }
}

void Notify::setDescription(QString d)
{
    if(d!=m_Description){
        m_Description=d;
        emit descriptionChanged();
    }
}

void Notify::setBeVisibleForUsers(bool visible)
{
    if(visible!=m_Visible){
        m_Visible=visible;
        emit beVisibleForUsersChanged();
    }
}

int Notify::amount()
{
    return m_Amount;
}

void Notify::setAmount(int a)
{
    if(m_Amount!=a){
        m_Amount=a;
        emit amountChanged();
    }
}

QDateTime Notify::date()
{
    return m_Date;
}

void Notify::setDate(QDateTime d)
{
    qWarning()<<"New Date=>"<<d;
    qWarning()<<"Current Date Date=>"<<m_EndDate;
    m_Date=d;
    emit dateChanged();
}

QString Notify::dateString()
{
    return m_DateString;
}

void Notify::setDateString(QString d)
{
    if(m_DateString!=d){
        m_DateString=d;
        emit dateStringChanged();
    }
}

QDateTime Notify::endDate()
{
    return m_EndDate;
}

void Notify::setEndDate(QDateTime ed)
{
    qWarning()<<"New End Date=>"<<ed;
    qWarning()<<"Current End Date Date=>"<<m_EndDate;
    m_EndDate=ed;
    emit endDateChanged();
}

QString Notify::endDateString()
{
    return m_EndDateString;
}

void Notify::setEndDateString(QString e)
{
    if(m_EndDateString!=e){
        m_EndDateString=e;
        emit endDateStringChanged();
    }
}

int Notify::duration()
{
    return m_Duration;
}

void Notify::setDuration(int d)
{
    if(m_Duration!=d){
        m_Duration=d;
        emit durationChanged();
    }
}

NotificationTypes::NotificationTypesEnum Notify::type()
{
    return m_Type;
}

void Notify::setType(NotificationTypes::NotificationTypesEnum t)
{
    if(t!=m_Type){
        m_Type=t;
        emit typeChanged();
    }
}

QString Notify::moreInfoLink()
{
    return m_MoreInfoLink;
}

void Notify::setMoreInfoLink(QString link)
{
    if(m_MoreInfoLink!=link){
        m_MoreInfoLink=link;
        emit moreInfoLinkChanged();
    }
}

Keyword *Notify::selectedKeyword()
{
    return m_SelectedKeyword;
}

void Notify::setSelectedKeyword(Keyword *sk)
{
    m_SelectedKeyword=sk;

}

KeywordTypeListModel *Notify::keywords()
{
    return &m_Keywords;
}

void Notify::save()
{
    if(isFeildsValid()){
        setIsProcssing(true);
        QNetworkReply* r=postRequest("api/Notify",readFeilds());
        connect(r,SIGNAL(finished()),this,SLOT(onSaveFinished()));
    }
}

void Notify::load(int id)
{
    if(id!=0){
        setIsProcssing(true);
        QNetworkReply* r=getRequest(QString("api/Notify/%1").arg(id));
        connect(r,SIGNAL(finished()),this,SLOT(reqLoadFinished()));
    }
}

void Notify::deleteItem()
{
    qInfo()<<"fileId=> "<<fileId();
    if(fileId()<=0){
        qInfo()<<"emit deleteSucceed() and return;";
        emit deleteSucceed();
        return;
    }
    setIsProcssing(true);
    QNetworkReply* r=deleteRequest("api/Notify/"+QString::number(fileId()));
    connect(r,SIGNAL(finished()),this,SLOT(onDeleteItemFinished()));
}

void Notify::loadKeywords()
{
    qInfo()<<"=>Loading Keywords of Notify(id="<<fileId()<<")";
    setIsProcssing(true);
    QNetworkReply*r =getRequest("api/Notify/Keywords/"+QString::number(fileId()));
    connect(r,SIGNAL(finished()),this,SLOT(loadKeywordsFinished()));
}

void Notify::addKeyword(int keywordId)
{
    qInfo()<<"=>Is Adding Keyword To Notify";
    setIsProcssing(true);
    m_SelectedKeyword=m_Keywords.find(keywordId);
    QNetworkReply* r=getRequest(QString("api/Notify/AddKeyword/%1?keywordId=%2").arg(fileId()).arg(keywordId));
    connect(r,SIGNAL(finished()),this,SLOT(addKeywordFinished()));
}

void Notify::removeKeyword(int keywordId)
{
    qInfo()<<"=>Is Removing Keyword To Notify";
    setIsProcssing(true);
    m_SelectedKeyword=m_Keywords.find(keywordId);
    QNetworkReply* r=getRequest(QString("api/Notify/RemoveKeyword/%1?keywordId=%2").arg(fileId()).arg(keywordId));
    connect(r,SIGNAL(finished()),this,SLOT(removeKeywordFinished()));
}

void Notify::removeKeywordFinished()
{
    QNetworkReply* r= convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        qInfo()<<"NoError";
        qInfo()<<"m_SelectedKeyword->selected()->"<<m_SelectedKeyword->selected();
        m_SelectedKeyword->setSelected(false);
        qInfo()<<"m_SelectedKeyword->selected()->"<<m_SelectedKeyword->selected();
    }
    else {
        qCritical()<<"Error";
    }
    showMessage(sender());
}
void Notify::addKeywordFinished()
{
    QNetworkReply* r= convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        m_SelectedKeyword->setSelected(true);
        reSetType(m_SelectedKeyword->value());
    }
    showMessage(sender());
}
void Notify::loadKeywordsFinished()
{
    qInfo()<<"Loading Keywords Finished";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        qInfo()<<"With No Error";
        QJsonArray kts=jsonUtility()->convertToJsonArray(r->readAll());
        for (int i = 0; i < kts.count(); ++i) {
            KeywordType* nk=new KeywordType(kts.at(i).toObject());
            m_Keywords.add(nk);
        }
        qWarning()<<"m_Keywords.rowCount"<<m_Keywords.rowCount();
    }
    else {
        qCritical()<<"Width Error";
    }
}

void Notify::onDeleteItemFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        emit deleteSucceed();
    }
    showMessage(r);
}

void Notify::reSetType(QString t)
{
    if(t=="AppIntro"){
        setType(NotificationTypes::NotificationTypesEnum::AppIntroducing);
    }
    else if (t=="AppUpdate") {
        setType(NotificationTypes::NotificationTypesEnum::AppUpdate);
    }
    else if (t=="Discount") {
        setType(NotificationTypes::NotificationTypesEnum::Discount);
    }
    else {
        setType(NotificationTypes::NotificationTypesEnum::UnKnown);
    }
}

void Notify::loadFromJson(QJsonObject obj)
{
    setFileId(obj.value("id").toInt());
    setType(static_cast<NotificationTypes::NotificationTypesEnum>(obj.value("type").toInt()));
    setTitle(obj.value("title").toString());
    setDescription(obj.value("description").toString());
    setDownloadLink(obj.value("imageUrl").toString());
    setImageName(obj.value("imageName").toString());
    setBeVisibleForUsers(obj.value("visible").toBool());
    //-----------------------------------------
    if(/*type()==NotificationTypes::NotificationTypesEnum::Discount*/true){
        setAmount(obj.value("amount").toInt());
        setDate(m_DateTimeUtility.toDateTime(obj.value("date").toString()));
        setEndDate(m_DateTimeUtility.toDateTime(obj.value("endDate").toString()));
        setDateString(obj.value("persianDate").toString());
        setEndDateString(obj.value("persianEndDate").toString());
    }
    setMoreInfoLink(obj.value("moreInfoLink").toString());
}

void Notify::onSaveFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj= jsonUtility()->convertToJsonObject(r->readAll());
        setFileId(obj.value("id").toInt());
        message()->setContent(obj.value("message").toString(),true);
    }
    else {
        showMessage(r);
    }
}

void Notify::reqLoadFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        loadFromJson(jsonUtility()->convertToJsonObject(r->readAll()));
    }
    else if (r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==404) {
        message()->setContent("معرفی یافت نشد");
    }
    else {
        showMessage(r);
    }
    setIsProcssing(false);
}

bool Notify::isFeildsValid()
{    
    //    if(fileId()==0){
    //        if(m_ImageBytes.isNull()||m_ImageBytes.isEmpty())
    //        {
    //            message()->setContent("عکسی را انتخاب کنید");
    //            return false;
    //        }
    //    }
    if(type()==NotificationTypes::NotificationTypesEnum::UnKnown){
        message()->setContent("نوع هشدار مشخص نشده است");
        return false;
    }
    if(title().isNull()||title().isEmpty()){
        message()->setContent("عنوان را وارد کنید");
        return false;
    }
    if(description().isNull()||description().isEmpty()){
        message()->setContent("توضیحات را وارد کنید");
        return false;
    }
    if(imageName().isNull()||imageName().isEmpty()){
        message()->setContent("نام تصویر را وارد کنید");
        return false;
    }
    if(type()==NotificationTypes::NotificationTypesEnum::Discount){
        if(amount()==0){
            message()->setContent("مقدار را وارد کنید");
            return false;
        }
    }
    return true;
}

QJsonObject Notify::readFeilds(){
    QJsonObject obj;
    obj.insert("id",fileId());
    obj.insert("title",title());
    obj.insert("description",description());
    obj.insert("visible",visible());
    obj.insert("imageName",imageName());

    QString s=m_ImageBytes.toBase64();
    obj.insert("imageBase64",s);
    qWarning()<<"image bytes count=>"<<m_ImageBytes.count();
    obj.insert("amount",amount());
    obj.insert("moreInfoLink",moreInfoLink());
    obj.insert("date",m_DateTimeUtility.fromDateTime(date()));
    obj.insert("endDate",m_DateTimeUtility.fromDateTime(endDate()));
    obj.insert("type",(int)type());
    return obj;
}
