#include "userprofile.h"

UserProfile::UserProfile(QObject *parent) : User(parent)
{
    setPhoneNumber("");
    setEmail("");
    setUserName("");
    setGender(false);
    m_ImageBytes="";
    m_ListModel.add(new UserImage());
    connect(&m_ListModel,SIGNAL(deletedItem()),this,SLOT(onImageDeleted()));
}

bool UserProfile::isCurrentDefault()
{
    return m_IsCurrentDefault;
}

void UserProfile::setIsCurrentDefault(bool isDefault)
{
    qDebug()<<"is Default=>"<<isDefault;
    m_IsCurrentDefault=isDefault;
    emit isCurrentDefaultChanged();

}

UserImageListModel *UserProfile::listModel()
{
    return &m_ListModel;
}

//============================================================================
void UserProfile::getProfile(QString userId)
{    
    if(!loginInfo()->isLoggedIn())
    {
        message()->setContent(tr("ابتدا وارد بخش کاربری خود شوید"));
        return;
    }
    QNetworkReply* reply= nullptr;
    if(loginInfo()->isAnyAdmin()){
        reply=getRequest(QString("api/User/Profile?userId=%1").arg(userId));
    }
    else {
        reply=getRequest("api/User/Profile");
    }
    connect(reply,SIGNAL(finished()),this,SLOT(onGetProfile()));
}

void UserProfile::getDisplayName()
{
    if(!loginInfo()->isLoggedIn())
    {
        message()->setContent(tr("ابتدا وارد بخش کاربری خود شوید"));
        return;
    }
    QNetworkReply* reply=getRequest("api/User/DisplayName");
    connect(reply,SIGNAL(finished()),this,SLOT(getDisplayNameFinished()));
}

void UserProfile::getDisplayNameFinished(){
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj=jsonUtility()->convertToJsonObject(r);
        setDisplayName(obj.value("displayName").toString());
        qDebug()<<"DisplayName="<<lastName();
        emit getProfileSucceed();
    }
    else {
        showMessage(r);
    }
}
void UserProfile::getScore()
{
    if(!loginInfo()->isLoggedIn())
    {
        message()->setContent(tr("ابتدا وارد بخش کاربری خود شوید"));
        return;
    }
    QNetworkReply* reply=getRequest("api/User/Score");
    connect(reply,SIGNAL(finished()),this,SLOT(getScoreFinished()));
}

void UserProfile::getScoreFinished(){
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj=jsonUtility()->convertToJsonObject(r);
        setScore(obj.value("score").toInt());
        emit getScoreSucceed();
    }
    else {
        showMessage(r);
    }
}

void UserProfile::saveProfile(QString userId)
{    
    if(!loginInfo()->isLoggedIn())
    {
        message()->setContent(tr("ابتدا وارد بخش کاربری خود شوید"));
        return;
    }
    if(!isFieldsValid())
    {
        return;
    }
    QNetworkReply* reply= nullptr;
    bool userIdIsNull=userId.isNull()||userId.isEmpty();
    if(loginInfo()->isAnyAdmin()&&!userIdIsNull){
        reply= postRequest(QString("api/User/SaveProfile?userId=%1").arg(userId),readFields());
    }
    else {
        reply= postRequest("api/User/SaveProfile",readFields());
    }
    connect(reply,SIGNAL(finished()),this,SLOT(saveProfileFinished()));
}

void UserProfile::saveDisplayName(QString displayName)
{
    if(!loginInfo()->isLoggedIn()){
        message()->setContent(tr("ابتدا وارد حساب کاربری خود شوید"));
        return;
    }
    if(displayName.isNull()||displayName.isEmpty()){
        message()->setContent(tr("نام را وارد کنید"));
        return;
    }
    QNetworkReply* reply= getRequest(QString("api/User/SaveDisplayName?displayName=%1").arg(displayName));
    connect(reply,SIGNAL(finished()),this,SLOT(saveProfileFinished()));
}

bool UserProfile::isFieldsValid(){
    if(displayName().isNull()||displayName().isEmpty()){
        message()->setContent("نام را وارد کنید");
        return false;
    }
//    else if(lastName().isNull()||lastName().isEmpty()) {
//        message()->setContent(tr("نام خانوادگی را وارد کنید"));
//        return false;
//    }
//    else if(phoneNumber().isNull()||phoneNumber().isEmpty()) {
//        message()->setContent(tr("شماره تماس را وارد کنید"));
//        return false;
//    }
    return true;
}

QJsonObject UserProfile::readFields(){
    QJsonObject jObj;
    jObj.insert("displayName",displayName());

//    jObj.insert("firstName",displayName());
//    jObj.insert("lastName",lastName());
//    jObj.insert("gender",gender()?"true":"false");
//    jObj.insert("phoneNumber",phoneNumber());
       jObj.insert("userName",userName());
       jObj.insert("email",email());
    return jObj;
}

void UserProfile::onGetProfile(){
    QNetworkReply* reply=convertToReply(sender());
    if(reply->error()==QNetworkReply::NoError){
        QString response=reply->readAll();
        qDebug()<<response;
        fromJson(jsonUtility()->convertToJsonObject(response));
        emit getProfileSucceed();
    }
    else {
        showMessage(reply);
    }
}

void UserProfile::saveProfileFinished()
{
    QNetworkReply* reply=convertToReply(sender());
    if(reply->error()==QNetworkReply::NoError)
    {
        emit profileChanged();
    }
    showMessage(reply);
}

void UserProfile::fromJson(QJsonObject obj){
    setUserId(obj.value("id").toString());
    setDisplayName(obj.value("displayName").toString());

//    setLastName(obj.value("lastName").toString());
//    setGender(obj.value("gender").toBool());
    setPhoneNumber(obj.value("phoneNumber").toString());
    setEmail(obj.value("email").toString());
    setUserName(obj.value("userName").toString());

    setIsSupporter(obj.value("isSupporter").toBool());
    QJsonArray array=obj.value("images").toArray();

    if(array.count()>0){
        m_ListModel.removeRows();
        for (int i = array.count()-1; i >= 0; --i) {
            QJsonObject obj=array.at(i).toObject();
            UserImage* img=new UserImage(obj);
            img->setWidth(225);
            img->setHeight(225);
            m_ListModel.insert(img,0);
            img->download();
        }
        qInfo()<<"is adding default image at the end of user images list";
        m_ListModel.add(new UserImage());
    }
}

void UserProfile::loadImage(int angle,QString path)
{
    ImageUtility im;

    if(path.isNull()||path.isEmpty())
    {
        im.loadFromPath(path);
    }
    else {
        QQmlEngine* myQmlEngine = QQmlEngine::contextForObject(this)->engine();

        if(myQmlEngine==nullptr)
        {
            message()->setContent("انجین تهی است");
            return;
        }

        QUrl imageUrl(path);
        auto provider = reinterpret_cast<QQuickImageProvider*>( myQmlEngine->imageProvider(imageUrl.host()));
        QImage img = provider->requestImage(imageUrl.path().remove(0,1),nullptr,QSize());
        if(img.isNull()){
            message()->setContent("تصویر بار گذاری نشد");
        }
        im.setImage(img);
    }
    rezieRotatImage(&im,angle);
    setImage(im.image());
    m_ImageBytes=im.imageBytes();

    qDebug()<<"m_ImageBytes=>"<<m_ImageBytes.length();
    emit imageLoadingChanged(true);
}

void UserProfile::rezieRotatImage(ImageUtility* im,int rotationAngle)
{
    im->crop(0,0,im->imgWidth(),im->imgWidth());
    int newWidth=0;
    if(im->imgWidth()>900)
    {
        newWidth=900;
    }
    else  {
        newWidth=im->imgWidth();
    }
    im->resize(newWidth,newWidth);
    qDebug()<<"%%% Angle =>>>>"<<rotationAngle;
    //im->rotate(rotationAngle);
}

void UserProfile::uploadProfileImage(){
    if(m_ImageBytes.isNull()||m_ImageBytes.count()==0){
        message()->setContent("تصویر بارگذاری نشده است");
        emit imageWasUploaded(false);
        return;
    }
    QNetworkReply* r=postRequest("api/User/SaveImageProfile",readProfileImage());
    connect(r,SIGNAL(finished()),this,SLOT(uploadProfileImageFinishded()));
}

QJsonObject UserProfile::readProfileImage(){
    QJsonObject obj;
    QString t=m_ImageBytes.toBase64();
    obj.insert("imageBase64",t);
    return  obj;
}
void UserProfile::uploadProfileImageFinishded(){
    qDebug()<<"uploadProfileImageFinishded";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        m_ImageBytes.clear();
        QJsonDocument doc=QJsonDocument::fromJson(r->readAll());
        UserImage* ui=new UserImage(doc.object());
        m_ListModel.removeDefualts();
        m_ListModel.add(ui);
        ui->download();
        emit imageWasUploaded(true);
    }
    else {
        showMessage(r);
        emit imageWasUploaded(false);
    }
}

void UserProfile::onImageDeleted()
{
    qDebug()<<"listModel()->rowCount()"<<listModel()->rowCount();
    if(listModel()->rowCount()==0){
        m_ListModel.add(new UserImage());
        emit imageDeleted();
    }
}
