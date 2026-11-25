#include "file.h"

File::File(QObject *parent) : JooyaNetwork (parent)
{
    ApplicationPath u;
    setFolderPath(u.filesFolderPath());
    setImageName("");
    setFileId(0);
    m_IsDownloaded=false;
    m_IsExists= false;
    m_isExistsInServer = true;
    m_DownloadState = FileDownloadStates::FileDownloadStatesEnum::NotStarted;
    m_uploadStatus = FileUploadStatus::FileUploadStatusEnum::Unknown;
    connect(this,&File::downloadLinkChanged,this,&File::refreshPath);
    connect(this,SIGNAL(imageNameChanged()),this,SLOT(refreshPath()));
    connect(this,SIGNAL(extChanged()),this,SLOT(refreshPath()));
    connect(this,SIGNAL(folderPathChanged()),this,SLOT(refreshPath()));
}

File::File(QString link):File()
{
    setDownloadLink(link);
}

File::File(QString link,QString path):File()
{
    setDownloadLink(link);
    setUrl(path);
}

File::File(QString link, QString path, QString extension):File()
{
    setDownloadLink(link);
    setExt(extension);
    setUrl(path);
}

QString File::downloadLink()
{
    return m_DowloadLink;
}

void File::setDownloadLink(QString link)
{
    if(m_DowloadLink!=link){
        m_DowloadLink=link;
        emit downloadLinkChanged();
        QFileInfo file(link);
        setImageName(file.baseName());
        setExt(file.suffix());
        if(ext().contains("?")){
            setExt(ext().split('?').at(0));
        }
    }
}

QUrl File::url()
{
    return m_Url;
}

void File::setUrl(QUrl p)
{
    if(m_Url!=p){
        m_Url=p;
        emit urlChanged();
        if(QFile::exists(m_Url.path())){
            setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileExists);
            qDebug()<<"file exists";
            return;
        }
        qCritical()<<"file not exists";
    }
}

QString File::imageName()
{
    return m_Name;
}

void File::setImageName(QString n)
{
    if(m_Name!=n){
        m_Name=n;
        emit imageNameChanged();
    }
}

int File::fileId()
{
    return m_FileId;
}

void File::setFileId(int id)
{
    if(m_FileId!=id){
        m_FileId=id;
        emit fileIdChanged();
    }
}

qint64 File::bytesSent()
{
    return m_BytesSent;
}

void File::setBytesSent(qint64 t)
{
    if(t!=m_BytesSent){
        m_BytesSent=t;
        emit bytesSentChanged();
    }
}

qint64 File::bytesTotal()
{
    return m_BytesTotal;
}

void File::setBytesTotal(qint64 t)
{
    if(t!=m_BytesTotal){
        m_BytesTotal=t;
        emit bytesTotalChanged();
    }
}

float File::upDownRatio()
{
    return m_UpDownRatio;
}

void File::setUpDownRatio(float ratio)
{
    if(ratio==m_UpDownRatio){
        return;
    }
    if(ratio<0||ratio>1)
    {
        return;
    }
    m_UpDownRatio=ratio;
    emit upDownRatioChanged();
}

QString File::folderPath()
{
    return m_FolderPath;
}

void File::setFolderPath(QString folderPath)
{
    if(folderPath!=m_FolderPath){
        m_FolderPath=folderPath;
        emit folderPathChanged();
        makeSureFolderExsists();
    }
}

QString File::ext()
{
    return m_Extension;
}

void File::setExt(QString ext)
{
    if(m_Extension!=ext){
        m_Extension=ext;
        initializeFolderPath(ext);
        emit extChanged();
    }
}

FileDownloadStates::FileDownloadStatesEnum File::downloadState()
{
    return m_DownloadState;
}

void File::setDownloadState(FileDownloadStates::FileDownloadStatesEnum ds)
{
    if(ds!=m_DownloadState){
        m_DownloadState=ds;
        emit downloadStateChanged();
        setIsDownloaded(ds==FileDownloadStates::FileDownloadStatesEnum::Succeed);
        setIsExists(ds==FileDownloadStates::FileDownloadStatesEnum::FileExists||ds==FileDownloadStates::FileDownloadStatesEnum::Succeed);
    }
}

bool File::exists()
{
    return QFile::exists((url().path()));
}

QByteArray File::read()
{
    QFile file(url().path());
    if(file.open( QIODevice::ReadOnly|QIODevice::Text))
    {
        QByteArray bytes = file.readAll();
        file.aboutToClose();
        return bytes;
    }
    return QByteArray();
}

/// returns and url that is contatinated with folder, name and extention
QUrl File::getUrl(QString name)
{
    return QUrl::fromLocalFile(folderPath()+name+"."+ext());
}

bool File::isDownloaded()
{
    return m_IsDownloaded;
}

void File::setIsDownloaded(bool isD)
{
    if(m_IsDownloaded!=isD){
        m_IsDownloaded=isD;
        emit isDownloadedChanged();
    }
}

bool File::isExists()
{
    return m_IsExists;
}

void File::setIsExists(bool isD)
{
    if(m_IsExists!=isD){
        m_IsExists=isD;
        emit isExistsChanged();
    }
}

void File::download(bool useApiUrl, bool isFullUrl)
{
    qDebug()<<"is going to download => "<<downloadLink();
    if(!isExistsInServer())
    {
        qInfo()<<"file is not exists in server so don't need to download it";
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileNotFound);
        return;
    }
    if(downloadState()==FileDownloadStates::FileDownloadStatesEnum::Started)
    {
        qDebug()<<"download is started -> return";
        return;
    }
    if(downloadState()==FileDownloadStates::FileDownloadStatesEnum::IsDownloading)
    {
        qDebug()<<"is downloaing the file and not finished yet";
        return;
    }
    if(QFile::exists(url().path())){
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileExists);
        qDebug()<<"the file exists -> return";
        return;
    }
    if(downloadLink().isNull()||downloadLink().isEmpty()){
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Faild);
        qWarning()<<"download link was null->return";
        return;
    }
    setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Started);
    QNetworkReply* r=getRequest(downloadLink(),useApiUrl,isFullUrl);
    connect(r,SIGNAL(finished()),this,SLOT(onDownloadFinishd()));
    connect(r,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updownLoadingProgress(qint64,qint64)));
}

QNetworkReply* File::upload(QString url,QJsonObject obj)
{
    qDebug()<<"is going to upload file";
    if(uploadStatus() == FileUploadStatus::FileUploadStatusEnum::Unknown){
        message()->setContent("فایل انتخاب نشده است");
        return nullptr;
    }
    if(!this->url().isValid()){
        qDebug()<<"file url is not valid";
        message()->setContent("فایل انتخاب نشده است");
        return nullptr;
    }
    qDebug()<<"current file url => "<<this->url();
    setUploadStatus(FileUploadStatus::FileUploadStatusEnum::Started);
    QNetworkReply* r = postRequest(url,obj);
    connect(r,&QNetworkReply::finished,this,&File::onUpload);
    connect(r,&QNetworkReply::uploadProgress,this,&File::onUploadProgress);
    return r;
}

void File::upload()
{
    qDebug()<<"is going to upload file";
    if(uploadStatus() == FileUploadStatus::FileUploadStatusEnum::Unknown){
        message()->setContent("فایل انتخاب نشده است");
        return;
    }
    if(!url().isValid()){
        qDebug()<<"file url is not valid";
        message()->setContent("فایل انتخاب نشده است");
        return;
    }
    qDebug()<<"current file url => "<<url();

    QFile *file = new QFile(url().path());
    if (!file->open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open file";
        message()->setContent("فایل انتخاب نشده است");
        return;
    }
    setUploadStatus(FileUploadStatus::FileUploadStatusEnum::Started);
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    QString fileName = QFileInfo(url().path()).fileName();
    qDebug()<<" file name => "<<fileName;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name=\"formFile\"; filename=\"" + fileName + "\""));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    QHttpPart urlPart;
    urlPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"Url\""));
    urlPart.setBody(downloadLink().toUtf8());
    multiPart->append(urlPart);
    QNetworkReply* r = post("api/File/Upload",multiPart);
    multiPart->setParent(r);
    connect(r,&QNetworkReply::finished,this,&File::onUpload);
    connect(r,&QNetworkReply::uploadProgress,this,&File::onUploadProgress);
}

///remove file from disk
bool File::remove()
{
    if(!url().isValid()){
        return false;
    }
    QFile file(url().path());
    if(!file.exists()){
        setIsExists(false);
        emit deleteSucceed();
        return true;
    }
    if(!file.remove())
    {
        setIsExists(true);
        return false;
    }
    setIsExists(false);
    emit deleteSucceed();
    return true;
}

bool File::isVideo(QString ext)
{
    if(ext=="mp4"){
        return true;
    }
    return false;
}

bool File::isAudio(QString ext)
{
    if(ext=="mp3"||ext=="wav"){
        return true;
    }
    return false;
}

void File::updownLoadingProgress(qint64 bytesSent,qint64 bytesTotal)
{
    setDownloadState(FileDownloadStates::FileDownloadStatesEnum::IsDownloading);
    setBytesSent(bytesSent);
    setBytesTotal(bytesTotal);
    setUpDownRatio((float)bytesSent/bytesTotal);
    qInfo()<<"download ratio=>"<<m_UpDownRatio;
}

void File::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    setUploadStatus(FileUploadStatus::FileUploadStatusEnum::IsUploding);
    setBytesSent(bytesSent);
    setBytesTotal(bytesTotal);
    setUpDownRatio((float)bytesSent/bytesTotal);
}

void File::onDownloadFinishd()
{
    QNetworkReply* r=convertToReply(sender());
    qDebug()<<"image download findish";
    if(r->error()==QNetworkReply::NoError)
    {
        qInfo()<<"with no error => url=>"<<url();
        qInfo()<<"NoError=> path=>"<<url().path();
        save(r->readAll());
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Succeed);
    }
    else if(isNotFound(r)){
        qCritical()<<"File not found in remote";
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileNotFound);
    }
    else {
        qCritical()<<"Error";
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Faild);
        int HttpCode= getHttpCode(r);
        if(HttpCode==404){
            message()->setContent("فایل یافت نشد");
        }
        else {
            showMessage(r);
        }
    }
    setIsProcssing(false);
}

bool File::saveJson(QJsonArray array){
    QJsonDocument doc(array);
    return save(doc.toJson());
}

bool File::save(QByteArray textContent){
    qDebug()<<"is going to save the file with size=> "<<textContent.count();
    if(url().isEmpty()||!url().isValid()){
        qWarning()<<"path of file was null";
        return false;
    }
    QFile f(url().path());
    if(!f.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        message()->setContent("فایل ذخیره نشد");
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::ErrorInSaving);
        return false;
    }
    f.write(textContent);
    f.close();
    if(f.exists()) {
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileExists);
        emit urlChanged();
        qInfo()<<"file downloaded successfully";
        return true;
    }
    else {
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::ErrorInSaving);
        return false;
    }
}

void File::refreshPath()
{
    if(folderPath().isNull()||folderPath().isEmpty()){
        return;
    }
    if(imageName().isNull()||imageName().isEmpty()){
        return;
    }
    if(ext().isNull()||ext().isEmpty()){
        return;
    }
    setUrl(QUrl::fromLocalFile(folderPath()+imageName()+"."+ext()));
}

void File::onUpload()
{
    qDebug()<<"file upload finished";
    QNetworkReply* r = convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        qInfo()<<"with no error";
        setUploadStatus(FileUploadStatus::FileUploadStatusEnum::Succeed);
    }
    else{
        qCritical()<<"with error";
        setUploadStatus(FileUploadStatus::FileUploadStatusEnum::Faild);
    }
}
void File::makeSureFolderExsists()
{
    QDir dir(folderPath());

    if(!dir.exists()){
        dir.mkpath(folderPath());
    }
    if(dir.exists()){
    }
    else {
    }
}

void File::initializeFolderPath(QString ext)
{
    ApplicationPath u;
    if(isVideo(ext)){
        setFolderPath(u.videoFolderPath());
    }
    else if (isAudio(ext)) {
        setFolderPath(u.soundFolderPath());
    }
}

const FileUploadStatus::FileUploadStatusEnum &File::uploadStatus() const
{
    return m_uploadStatus;
}

void File::setUploadStatus(const FileUploadStatus::FileUploadStatusEnum &newUploadStatus)
{
    if (m_uploadStatus == newUploadStatus)
        return;
    m_uploadStatus = newUploadStatus;
    emit uploadStatusChanged();
}

bool File::isExistsInServer() const
{
    return m_isExistsInServer;
}

void File::setIsExistsInServer(bool newIsExistsInServer)
{
    if (m_isExistsInServer == newIsExistsInServer)
        return;
    m_isExistsInServer = newIsExistsInServer;
    emit isExistsInServerChanged();
}
