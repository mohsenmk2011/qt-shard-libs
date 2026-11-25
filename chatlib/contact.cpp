#include "contact.h"

Contact::Contact(QObject *parent) : ImageFile(parent)
{
    m_IsMe=false;
    m_IsOnline=false;
    m_IsOffline=false;
    m_UserId="";
    m_LastActivityDate=QDateTime();
    m_PersianDateTime =new PersianDateTime(m_LastActivityDate);
    setWidth(72);
    setHeight(72);
    ApplicationPath appPath;
    setFolderPath(appPath.userFolderPath());

    m_TimerIsOnline=new QTimer(this);
    m_TimerIsOnline->setParent(this);
    m_TimerIsOnline->setInterval(9999);
    m_TimerIsOnline->setSingleShot(true);
    connect(m_TimerIsOnline,&QTimer::timeout,this,&Contact::timerIsOnlineTimeout);
}

Contact::Contact(QJsonObject obj):Contact()
{
    fromJson(obj);
}

bool Contact::isMe()
{
    return m_IsMe;
}

void Contact::setIsMe(bool me)
{
    if(m_IsMe!=me){
        m_IsMe=me;
        emit isMeChanged();
    }
}

bool Contact::isOnline()
{
    return m_IsOnline;
}

void Contact::setIsOnline(bool o)
{
    if(m_IsOnline!=o){
        m_IsOnline=o;
        if(o)
        {
            m_TimerIsOnline->start();
            if(isOffline()){
                setIsOffline(false);
            }
        }
        emit isOnlineChanged();
    }
}

bool Contact::isOffline()
{
    return m_IsOffline;
}

void Contact::setIsOffline(bool o)
{
    if(m_IsOffline!=o){
        m_IsOffline=o;
        if(o)
        {
            m_TimerIsOnline->start();
            if(isOnline()){
                setIsOnline(false);
            }
        }
        emit isOfflineChanged();
    }
}

QString Contact::userId()
{
    return m_UserId;
}

void Contact::setUserId(QString userId)
{
    if(m_UserId!=userId){
        m_UserId=userId;
        emit userIdChanged();
    }
}

QString Contact::displayName()
{
    return m_DisplayName;
}

void Contact::setDisplayName(QString name)
{
    if(m_DisplayName!=name){
        m_DisplayName=name;
        emit displayNameChanged();
    }
}

QString Contact::ip()
{
    return m_Ip;
}

void Contact::setIp(QString ip)
{
    if(ip!=m_Ip){
        m_Ip=ip;
        emit ipChanged();
    }
}

QDateTime Contact::lastActivityDate()
{
    return m_LastActivityDate;
}

void Contact::setLastActivityDate(QDateTime date)
{
    m_LastActivityDate=date;
    m_PersianDateTime->setDate(date);
    updateLastActivityText();
    emit lastActivityDateChanged();
}

QString Contact::lastActivityText()
{
    return m_LastActivityText;
}

void Contact::setLastActivityText(QString l)
{
    if(m_LastActivityText!=l){
        m_LastActivityText=l;
        emit lastActivityTextChanged();
    }
}

void Contact::fromJson(QJsonObject obj)
{
    qInfo()<<"contact json=> "<<obj;
    setUserId(obj.value("userId").toString());
    setIp(obj.value("ip").toString());
    setIsMe(obj.value("isMe").toBool());
    setDownloadLink(obj.value("imageLink").toString());
    setDisplayName(obj.value("displayName").toString());
    setLastActivityDate(dateTimeUtility()-> toDateTime(obj.value("lastActivityDate").toString()));
    setImageName(obj.value("imageName").toString());
}

QJsonObject Contact::toJson()
{
   QJsonObject obj;
   obj.insert("userId",userId());
   obj.insert("ip",ip());
   obj.insert("isMe",isMe());
   obj.insert("imageLink",downloadLink());
   obj.insert("displayName",displayName());
   obj.insert("lastActivityDate",dateTimeUtility()->fromDateTime(lastActivityDate()));
   obj.insert("imageName",imageName());
   return obj;
}

void Contact::getFromServer()
{
    qWarning()<<"***[ getFromServer ]***";
    if(!loginInfo()->isLoggedIn()){
        return;
    }
    QNetworkReply* reply=nullptr;
    if(isMe()){
        reply=getRequest("api/Contact/Me");
    }
    else{
        reply=getRequest(QString("api/Contact/%1").arg(m_UserId));
    }
    connect(reply,&QNetworkReply::finished,this,&Contact::onGetContactFinished);
}

void Contact::onGetContactFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj=jsonUtility()->convertToJsonObject(r->readAll());
        fromJson(obj);
        qWarning()<<"contact is updated";
        emit updateFinished();
        download();
    }
    else{
        showMessage(r);
    }
}

void Contact::timerIsOnlineTimeout()
{
    if(isOnline()){
        setIsOnline(false);
    }
    if(isOffline())
    {
        setIsOffline(false);
    }
}

void Contact::updateLastActivityText()
{
    QString output="آخرین بازدید ";
    QDateTime today=QDateTime::currentDateTime();
    int days=lastActivityDate().daysTo(today);
    if(days<=0){
        int minuts=lastActivityDate().secsTo(today)/60;
        if (minuts<=3) {
            output="آنلاین";
        }
        else if(minuts<60){
            output+=QString("%1 دقیقه پیش").arg(minuts);
        }
        else {
            output+=QString("امروز در ساعت %1:%2").arg(lastActivityDate().time().hour()).arg(lastActivityDate().time().minute());
        }
    }
    else if (days==1) {
        output+=QString("دیروز در ساعت %1:%2").arg(lastActivityDate().time().hour()).arg(lastActivityDate().time().minute());
    }
    else {
        output =m_PersianDateTime->shortDate();
    }    
    setLastActivityText(output);
}
