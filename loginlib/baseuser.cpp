#include "baseuser.h"

BaseUser::BaseUser(QObject *parent) : JooyaNetwork(parent)
{
    qInfo()<<"=>>>[ Initialization BaseUser ]<<<=";
    connect(loginInfo(),SIGNAL(stateChanged(LoginStates::LoginStatesEnum)),this,SLOT(userLoginStateChanged(LoginStates::LoginStatesEnum)));
    m_HasImage=true;
    m_CheckedLastImage=false;
    load();
}

void BaseUser::userLoginStateChanged(LoginStates::LoginStatesEnum s)
{
    qDebug()<<"login stat state changed=> "<<s;
    if(s==LoginStates::LoginStatesEnum::LoggedOut){
        qDebug()<<"set default valuse";
        deleteUserImages();
        appSettings.setUserInfo("");
        setInfo();
        return;
    }
    qDebug()<<"load user info";
    load();
}

void BaseUser::setInfo(QString displayName,QString userName,UserRoles::UserRolesEnum role)
{
    setDisplayName(displayName);
    setUserName(userName);
    loginInfo()->setRole(role);
    lastImage()->resetImage();
}

QString BaseUser::displayName()
{
    return m_DisplayName;
}

void BaseUser::setDisplayName(QString l)
{
    if(m_DisplayName!=l){
        m_DisplayName=l;
        emit displayNameChanged();
    }
}

UserImage *BaseUser::lastImage()
{
    return &m_LastImage;
}

QString BaseUser::userName(){
    return m_UserName;
}
void BaseUser::setUserName(QString un){
    if(un!=m_UserName){
        m_UserName=un;
        emit userNameChanged();
    }
}

QString BaseUser::firstName()
{
    return m_FirstName;
}

void BaseUser::setFirstName(QString name)
{
    if(m_FirstName!=name){
        m_FirstName=name;
        emit firstNameChanged();
    }
}

QString BaseUser::lastName()
{
    return m_LastName;
}

void BaseUser::setLastName(QString name)
{
    if(m_LastName!=name){
        m_LastName=name;
        emit lastNameChanged();
    }
}

QString BaseUser::city()
{
    return m_City;
}

void BaseUser::setCity(QString c)
{
    if(m_City!=c){
        m_City=c;
        emit cityChanged();
    }
}

bool BaseUser::hasImage()
{
    return m_HasImage;
}

void BaseUser::setHasImage(bool hi)
{
    if(m_HasImage!=hi){
        m_HasImage=hi;
        emit hasImageChanged();
    }
}

bool BaseUser::isNameIsDefault()
{
    qWarning()<<"&&&&&&& DisplayNameChecking &&&&&";
    qWarning()<<"userName"<<userName();
    //    return userName().isNull()||userName().isEmpty()||userName()=="Guest";
    return displayName().isNull()||displayName().isEmpty();
}

void BaseUser::fromJson(QJsonObject obj)
{
    UserRoles::UserRolesEnum role= static_cast<UserRoles::UserRolesEnum>(obj.value("role").toInt());
    setInfo(obj.value("displayName").toString(),obj.value("userName").toString(),role);
    if(!obj.value("lastImage").isNull()){
        qInfo()<<"=> load Last Image from json ";
        m_LastImage.loadFromJson(obj.value("lastImage").toObject());
        qInfo()<<"=> download Last Image ";
        m_LastImage.download();
    }
    else {
        qInfo()<<"=> get Last Image ";
        getLastImage();
    }
    qInfo()<<"End of BaseUser::fromJson() ";
}

QJsonObject BaseUser::toJson()
{
    QJsonObject obj;
    obj.insert("displayName",displayName());
    obj.insert("userName",userName());
    obj.insert("role",static_cast<int>(loginInfo()->role()));
    obj.insert("lastImage",m_LastImage.toJson());
    return obj;
}

void BaseUser::load()
{
    qDebug()<<"^^^^^^^^^^^^^^^^^^^^[ is going to load userinfo(baseuser) ]^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    if(!loginInfo()->isLoggedIn()){
        qDebug()<<"Is Not Loggedin => returned";
        return;
    }

    qDebug()<<"Is Loggedin || Reading UserInfo from QSettings";
    QString userInfo=appSettings.userInfo();
    if(userInfo.isNull()||userInfo.isEmpty()){
        qDebug()<<"UserInfo was not in QSettings => Load BaseUser From Server";
        getUserInfo();
        return;
    }

    qDebug()<<"UserInfo was in QSettings => Initialize BaseUser";
    QJsonObject obj= jsonUtility()->convertToJsonObject(userInfo.toUtf8());
    fromJson(obj);

    if(loginInfo()->role() == UserRoles::UserRolesEnum::Guest){
        qDebug()<<"user info that was loaded from settings is defualt => get UserInfo from server";
        getUserInfo();
    }
}

void BaseUser::getUserInfo(bool refreshImage)
{
    if(!loginInfo()->isLoggedIn()){
        return;
    }
    if(refreshImage){
        m_CheckedLastImage=false;
    }
    QNetworkReply* reply= getRequest("api/User/Info");
    connect(reply,SIGNAL(finished()),this,SLOT(onGetUserInfo()));
}

void BaseUser::onGetUserInfo(){
    QNetworkReply* reply=convertToReply(sender());
    if(reply->error()==QNetworkReply::NoError){
        auto t=reply->readAll();
        qInfo()<<t;
        QJsonObject obj= jsonUtility()->convertToJsonObject(t);
        fromJson(obj);
        appSettings.setUserInfo(t);
    }
    else {
        setInfo();
        showBadMessage(reply->readAll());
    }
}

void BaseUser::getLastImage()
{
    if(!hasImage()){
        qDebug()<<"User Has Not Image IN this app ->return";
        return;
    }
    if(!loginInfo()->isLoggedIn()){
        qDebug()<<"returnd-> User is not logged in";
        m_LastImage.remove();
        m_LastImage.resetImage();
        return;
    }
    if(m_CheckedLastImage){
        qDebug()<<"returnd-> Before Checked Last Image of User";
        return;
    }
    qInfo()<<"last image date => "<<m_DateTimeUtility.fromDateTime(lastImage()->date());
    qInfo()<<"last image date => "<<lastImage()->date();
    setDisplayCommonErrorMessage(false);
    QNetworkReply* reply= getRequest(QString("api/User/LastImage?date=%1").arg(m_DateTimeUtility.fromDateTime(lastImage()->date())));
    connect(reply,SIGNAL(finished()),this,SLOT(getLastImageFinished()));
}

void BaseUser::getLastImageFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(isNotFound(r)) {
        qDebug()<<"user don't have any image,or don't have newer one";
        m_CheckedLastImage=true;
        return;
    }
    if(r->error()==QNetworkReply::NoError){
        m_CheckedLastImage=true;
        qInfo()<<"Reading new user image => and download";
        QString jsonImage=r->readAll();
        m_LastImage.loadFromJson(jsonUtility()->convertToJsonObject(jsonImage));
        appSettings.setUserInfo(jsonUtility()->convertToJsonString(toJson()));
        m_LastImage.download();
    }
}

void BaseUser::deleteUserImages()
{
    ApplicationPath lu;

    QDir userDir=QDir(lu.userFolderPath());
    qDebug()<<"User Picture Folder=>"<<lu.userFolderPath();
    QFileInfoList fl= userDir.entryInfoList(QDir::Files,QDir::Name);
    qDebug()<<"User Picture count=>"<<fl.count();
    for (int i = 0; i < fl.count(); ++i) {
        QFileInfo info=fl.at(i);
        if(info.isFile()){
            QFile file(info.filePath());
            qDebug()<<info.filePath() <<file.remove();
        }
    }
}
