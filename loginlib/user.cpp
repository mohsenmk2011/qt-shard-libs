#include "user.h"

User::User(QObject *parent) : JooyaNetwork(parent)
{
    mId="";
    m_RegisterDate="";
    m_DisplayName="";
    m_LastName="";
    m_FirstName="";
    m_UserName="";
    m_PhoneNumber="";
    m_IsSupporter=false;
    m_Email="";
    m_Gender=false;
    m_ImageBytes="";
    m_CurrentRoleName="";

    m_ImageWidth=300;
    m_ImageHeight=300;
    m_Score = 0;
    QImage img;
    if(img.load(":/images/app/account.png")){
        setImage(img);
    }
}

User::User(QString userId, QString un, QString rd)
{
    setUserId(userId);
    setUserName(un);
    setRegisterDate(rd);
}

QString User::userId()
{
    return mId;
}

void User::setUserId(QString i)
{
    if(i!=mId){
        mId=i;
        emit userIdChanged();
    }
}

QString User::registerDate()
{
    return m_RegisterDate;
}

void User::setRegisterDate(QString rd)
{
    if(rd!=m_RegisterDate){
        m_RegisterDate=rd;
        emit registerDateChanged();
    }
}

QString User::lastName()
{
    return m_LastName;
}

void User::setLastName(QString ln)
{
    if(m_LastName!=ln){
        m_LastName=ln;
        emit lastNameChanged();
    }
}

QString User::firstName()
{
    return m_FirstName;
}

void User::setFirstName(QString fn)
{
    if(m_FirstName!=fn){
        m_FirstName=fn;
        emit firstNameChanged();
    }
}

QString User::displayName()
{
    return m_DisplayName;
}

void User::setDisplayName(QString dn)
{
    if(m_DisplayName!=dn){
        m_DisplayName=dn;
        emit displayNameChanged();
    }
}

QString User::userName()
{
    return m_UserName;
}

void User::setUserName(QString un)
{
    if(m_UserName!=un){
        m_UserName=un;
        emit userNameChanged();
    }
}

QString User::referralCode()
{
    return m_ReferralCode;
}

void User::setReferralCode(QString code)
{
    if(m_ReferralCode!=code){
        m_ReferralCode=code;
        emit referralCodeChanged();
    }
}

int User::score()
{
    return m_Score;
}

void User::setScore(int s)
{
    if(m_Score!=s){
        m_Score=s;
        emit scoreChanged();
    }
}

bool User::isSupporter()
{
    return m_IsSupporter;
}

void User::setIsSupporter(bool is)
{
    if(m_IsSupporter!=is){
        m_IsSupporter=is;
        emit isSupporterChanged();
    }
}

QString User::phoneNumber()
{
    return m_PhoneNumber;
}

void User::setPhoneNumber(QString pn)
{
    if(m_PhoneNumber!=pn){
        m_PhoneNumber=pn;
        emit phoneNumberChanged();
    }
}

QString User::email()
{
    return m_Email;
}

void User::setEmail(QString e)
{
    if(m_Email!=e){
        m_Email=e;
        emit emailChanged();
    }
}

bool User::gender(){
    return m_Gender;
}
void User::setGender(bool g){
    if(g!=m_Gender){
        m_Gender=g;
        emit genderChanged();
    }
}

QImage User::image()
{
    return  m_Image;
}

void User::setImage(QImage img)
{
    m_Image=img;
    qDebug()<<"&&&&&&&&&&&&&&&& Image Width="<<img.width()<<" Height="<<img.height()<<"&&&&&&&&&&&";
    imageChanged();
}

RoleListModel *User::roles()
{
    return &m_ListModel;
}

void User::getRoles()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/User/Roles/"+userId());
    connect(r,SIGNAL(finished()),this,SLOT(getRolesFinished()));
}

void User::getRolesFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QString result=r->readAll();
        qInfo()<<result;
        roles()->loadFromResponse(result);
    }
    else {
        showBadMessage(r->readAll());
    }
    setIsProcssing(false);
}

void User::addToRole(QString roleName)
{
    m_CurrentRoleName=roleName;
    qDebug()<<"UserManager::addToRole";
    setIsProcssing(true);
    QString url=QString("api/User/AddToRole/%1?roleName=%2").arg(userId()).arg(roleName);
    QNetworkReply* r=getRequest(url);
    connect(r,SIGNAL(finished()),this,SLOT(addToRoleFinished()));
}
void User::addToRoleFinished()
{
    qDebug()<<"UserManager::addToRoleFinished";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        m_ListModel.changeSelectedRole(m_CurrentRoleName,true);
        qDebug()<<"with no error";
    }
    showMessage(r);
    setIsProcssing(false);
}

void User::removeFromRole(QString roleName)
{
    m_CurrentRoleName=roleName;
    qDebug()<<"UserManager::removeFromRole";
    setIsProcssing(true);
    QString url=QString("api/User/RemoveFromRole/%1?roleName=%2").arg(userId()).arg(roleName);
    QNetworkReply* r=getRequest(url);
    connect(r,SIGNAL(finished()),this,SLOT(removeFromRoleFinished()));
}

void User::setAsSupporter(bool isSupporter)
{
    qInfo()<<"userid=>"<<userId();

    QNetworkReply* r= getRequest(QString("api/User/Supporter?isSupporter=%1&userId=%2").arg(QVariant(isSupporter).toString()).arg(userId()));
    connect(r,SIGNAL(finished()),this,SLOT(onSetAsSupporter()));
}

void User::onSetAsSupporter()
{
    showMessage(sender());
}

void User::getReferralCode()
{
    if(!(referralCode().isEmpty()||referralCode().isNull())){
        return;
    }
    QNetworkReply* r=getRequest("api/User/ReferralCode");
    connect(r,SIGNAL(finished()),this,SLOT(onGetReferralCode()));
}

void User::signup()
{
    if(isProcessing()){
        return;
    }
    if(phoneNumber().isNull()||phoneNumber().isEmpty())
    {
        message()->setContent("شماره تلفن همراه را وارد کنید");
        return;
    }

    QJsonObject jObj;
    jObj.insert("phoneNumber",phoneNumber());

    QNetworkReply* reply= postRequest("api/User",jObj);
    connect(reply,&QNetworkReply::finished ,this,&User::onSignup);
}

void User::onSignup()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj= jsonUtility()->convertToJsonObject(r->readAll());
        setUserId(obj.value("id").toString());
        emit signupSucceed(userId());
        message()->setContent(obj.value("message").toString(),true);
    }
    else {
        showMessage(r);
    }
}

void User::onGetReferralCode()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj= jsonUtility()->convertToJsonObject(r->readAll());
        QString refLink=baseUrl()+"?ref="+obj.value("referralCode").toString();
        int clicks=obj.value("clicks").toInt();
        int signedUps=obj.value("signedUps").toInt();
        qInfo()<<"clicks-> "<<clicks;
        qInfo()<<"signedUps-> "<<signedUps;
        setReferralCode(refLink);
        emit referralInfoIsReady(refLink,clicks,signedUps);
    }
    else {
        showMessage(r);
    }
}

void User::removeFromRoleFinished()
{
    qDebug()<<"UserManager::removeFromRoleFinished";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        m_ListModel.changeSelectedRole(m_CurrentRoleName,false);
        qDebug()<<"with no error";
    }
    showMessage(r);
    setIsProcssing(false);
}

void User::setFromJson(QString jsonUser)
{
    qDebug()<<"Start Reading User From Json";
    QJsonDocument doc=QJsonDocument::fromJson(jsonUser.toUtf8());
    QJsonObject obj=doc.object();

    setDisplayName(obj.value("fistName").toString());
    qDebug()<<"fistName="<<displayName();

    setLastName(obj.value("lastName").toString());
    qDebug()<<"lastName="<<lastName();

    setGender(obj.value("gender").toBool());
    qDebug()<<"gender="<<gender();

    setPhoneNumber(obj.value("phoneNumber").toString());
    qDebug()<<"phoneNumber="<<phoneNumber();

    setEmail(obj.value("email").toString());
    qDebug()<<"email="<<email();
}
