#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent) : JooyaNetwork(parent)
{
    files={};
    m_CountFailed=0;
    m_CountDownloaded=0;
    m_CountToDownload=0;
#if defined(Q_OS_ANDROID)
    m_DownloadServiceManager = new DownloadServiceManager();
    m_App_or_Service_BroadcastReceiver = downloadService()->registerNativeMethodsAndBroadcastReceiver();
    if(downloadService()->isInService())
    {
        qDebug()<<"*** [is In Service => connect AndroidServiceManager.serviceMessageReceived signal to  DownloadManager.onNewServiceMessage slot ] ***";
        connect(downloadService(),&AndroidServiceManager::serviceMessageReceived,this,&DownloadManager::onNewServiceMessage);
    }
    else{
        qDebug()<<"*** [is In App => connect AndroidServiceManager.appMessageReceived signal to  DownloadManager.onNewAppeMessage slot ] ***";
        connect(downloadService(),&AndroidServiceManager::appMessageReceived,this,&DownloadManager::onNewAppeMessage);
    }
#endif
}

DownloadManager::~DownloadManager()
{
#if defined(Q_OS_ANDROID)
    downloadService()->unregisterNativeMethodsAndBroadcastReceiver(m_App_or_Service_BroadcastReceiver);
#endif
}

void DownloadManager::setNotificationText(QString text)
{
    if(m_NotificationText!=text){
        m_NotificationText=text;
        if(downloadService()->isInService())
        {
            downloadService()->sendToService(QString("DownloadMessage,%1").arg(text));
        }
    }
}

DownloadServiceManager *DownloadManager::downloadService()
{
    return m_DownloadServiceManager;
}

void DownloadManager::add(QList<File*> fls)
{
    foreach (File* f,fls) {
        add(f);
    }
}

void DownloadManager::add(QString link)
{
    add(new File(link));
}

void DownloadManager::add(File *file)
{
#if defined(Q_OS_ANDROID)
    if(downloadService()->isInService())
    {
        qInfo()<<"is in service => is adding link("<<file->downloadLink()<<")";
        File* f=findFile(file->downloadLink());
        if(f==nullptr){
            files.append(file);
        }
    }
    else{
        qInfo()<<"is in qt app => send link to service";
        File* f=findFile(file->downloadLink());
        if(f==nullptr){
            files.append(file);
        }
        downloadService()->sendToService("AddFile,"+file->downloadLink());
    }
#else
    files.append(file);
#endif
    updateDownloadCount();
}

File *DownloadManager::findFile(QString link)
{
    foreach (File* f,files) {
        if(f->downloadLink()==link){
            return f;
        }
    }
    return nullptr;
}

void DownloadManager::download(File* f)
{
    if(f == nullptr)
    {
        return;
    }
    bool startDownload = false;
#if defined(Q_OS_ANDROID)
    if(downloadService()->isInService())
    {
        startDownload = true;
    }
    else
    {
        downloadService()->sendToService("StartDownload");
        return;
    }
#else
    startDownload = true;
#endif
    if(startDownload)
    {
        if(f->isProcessing())
        {
            return;
        }
        connect(f,&File::upDownRatioChanged,this,&DownloadManager::updateRatio);
        connect(f,SIGNAL(downloadStateChanged()),this,SLOT(onDownloadStateChanged()));
        //TODO: should connect download finished signal to dipslay on app for try again,and close download service
        f->download();
    }
}

void DownloadManager::startDownload()
{
    qDebug()<<"is going to download the files";
    foreach (File* f, files) {
        if(f->isExists())
        {
            break;
        }
        if(f->downloadState() == FileDownloadStates::FileDownloadStatesEnum::FileExists
            ||f->downloadState() == FileDownloadStates::FileDownloadStatesEnum::Succeed)
        {
            break;
        }
        if(f->isProcessing())
        {
            return;
        }
        download(f);
    }
}

void DownloadManager::updateRatio()
{
    File* file=qobject_cast<File*>(sender());
    if(downloadService()->isInService()){
        downloadService()->sendToService(QString("Ratio,%1,%2").arg(file->downloadLink()).arg(file->upDownRatio()));
    }
}

void DownloadManager::updateDownloadCount()
{
    m_CountDownloaded = 0;
    m_CountFailed = 0;
    m_CountToDownload = files.count();
    foreach (File* f, files) {
        if(f->isDownloaded()||f->isExists())
        {
            m_CountDownloaded++;
        }
        else if(f->downloadState()==FileDownloadStates::FileDownloadStatesEnum::Faild||f->downloadState()==FileDownloadStates::FileDownloadStatesEnum::ErrorInSaving)
        {
            m_CountFailed++;
        }
    }
    qDebug()<<"Downloaded count => "<<m_CountDownloaded;
    qDebug() <<"Failed count => "<<m_CountFailed;
    qDebug() <<"all files count => "<<m_CountToDownload;

    setNotificationText(QString("در حال دانلود فایل %1 از %2").arg(m_CountDownloaded+1).arg(m_CountToDownload));

    if(m_CountDownloaded+m_CountFailed>=files.count()){
        if(downloadService()->isInService())
        {
            downloadService()->sendToService("TotalFileDownloaded");
        }
        else{
            emit totalFileDownloaded();
        }
    }
}

void DownloadManager::onDownloadStateChanged()
{
    File* file=qobject_cast<File*>(sender());
    //download state in servic is updated => update state in qt app
    if(downloadService()->isInService())
    {
        //should update downloadState => file.isExists and isDownloaded will update too
        downloadService()->sendToService(QString("DownloadState,%1,%2").arg(file->downloadLink()).arg((int)file->downloadState()));
        updateDownloadCount();
        startDownload();
    }
}

void DownloadManager::onNewServiceMessage(QString message)
{
    qCritical()<<"###[(In C++ Service) DownloadManager: message received from app => "<<message<<" ]###";
    if(message.contains("AddFile"))
    {
        add(message.split(",").at(1));
    }
    else if(message.contains("StartDownload"))
    {
        startDownload();
    }
}

void DownloadManager::onNewAppeMessage(QString appMessage)
{
    qCritical()<<"###[(In Qt App) DownloadManager: message received from c++ service => "<<appMessage<<" ]###";
    if(appMessage.contains("Ratio"))
    {
        QString link=appMessage.split(",").at(1);
        File* f=findFile(link);
        if(f!=nullptr){
            f->setUpDownRatio(appMessage.split(",").at(2).toFloat());
        }
    }
    else if(appMessage.contains("DownloadState"))
    {
        QString link=appMessage.split(",").at(1);
        File* f=findFile(link);
        if(f!=nullptr){
            f->setDownloadState(static_cast<FileDownloadStates::FileDownloadStatesEnum>(appMessage.split(",").at(2).toInt()));
        }
    }
    else if(appMessage.contains("TotalFileDownloaded"))
    {
        updateDownloadCount();
    }
}
