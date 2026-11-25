#include "chat.h"

Chat::Chat(QObject *parent) : ListManager(parent)
{
    m_Image=new ImageFile();
    m_LastTalk="";
    m_LastTalkDate="";
    m_UnReadTalks=0;
    m_Type=ChatTypes::ChatTypesENUM::Conversation;
    m_IsTyping=false;
    m_IsMuted=false;

    m_SendMessageSound=new File("/Audios/SendMessage.wav");
    m_SendMessageSound->download();
    m_SoundFileNewMessage=new File("/Audios/NewMessage.mp3");
    m_SoundFileNewMessage->download();

    m_Timer=new QTimer(this);
    m_Timer->setParent(this);
    m_Timer->setInterval(1800);
    connect(m_Timer,&QTimer::timeout,this,&Chat::typingTimerTimeout);
}

Chat::Chat(QJsonObject obj):Chat()
{
    fromJson(obj);
}

Chat::Chat(ChatTypes::ChatTypesENUM type):Chat()
{
    setType(type);
}

PostListModel *Chat::posts()
{
    return &m_Posts;
}

ContactListModel *Chat::contacts()
{
    return &m_Contacts;
}

Post *Chat::selectedPost()
{
    return posts()->selectedPost();
}

int Chat::selectedPostIndex()
{
    for (int i = 0; i < posts()->rowCount(); ++i) {
        if(posts()->at(i)->isSelected()){
            return i;
        }
    }
}

ImageFile *Chat::image()
{
    return m_Image;
}

QString Chat::chatId()
{
    return m_ChatId;
}

void Chat::setChatId(QString id)
{
    if(m_ChatId!=id){
        m_ChatId=id;
        emit chatIdChanged();
    }
}

QString Chat::userId()
{
    return m_UserId;
}

void Chat::setUserId(QString u)
{
    if(m_UserId!=u){
        m_UserId=u;
        emit
    }
}

QString Chat::description()
{
    return m_Description;
}

void Chat::setDescription(QString d)
{
    if(m_Description!=d){
        m_Description=d;
        emit descriptionChanged();
    }
}

void Chat::typingTimerTimeout()
{
    m_Timer->stop();
    setIsTyping(false);
}

QString Chat::chatName()
{
    return m_ChatName;
}

void Chat::setChatName(QString n)
{
    if(m_ChatName!=n){
        m_ChatName=n;
        emit chatNameChanged();
    }
}

QDateTime Chat::date()
{
    return m_Date;
}

void Chat::setDate(QDateTime d)
{
    if(m_Date!=d){
        m_Date=d;
        emit dateChanged();
    }
}

PersianDateTime *Chat::pDate()
{
    return new PersianDateTime(date());
}

ChatTypes::ChatTypesENUM Chat::type()
{
    return m_Type;
}

void Chat::setType(ChatTypes::ChatTypesENUM t)
{
    if(m_Type!=t){
        m_Type=t;
        emit typeChanged();
    }
}

bool Chat::isMuted()
{
    return m_IsMuted;
}

void Chat::setIsMuted(bool m)
{
    if(m_IsMuted!=m){
        m_IsMuted=m;
        emit isMutedChanged();
    }
}

int Chat::unReadTalks()
{
    return m_UnReadTalks;
}

void Chat::setUnReadTalks(int u)
{
    if(m_UnReadTalks!=u){
        m_UnReadTalks=u;
        emit unReadTalksChanged();
    }
}

QString Chat::lastTalk()
{
    return m_LastTalk;
}

void Chat::setLastTalk(QString l)
{
    if(m_LastTalk!=l){
        m_LastTalk=l.simplified();
        //TODO: USE sliced method in qt6 for clipping text
        emit lastTalkChanged();
    }
}

QString Chat::lastTalkDate()
{
    return m_LastTalkDate;
}

void Chat::setLastTalkDate(QString l)
{
    if(m_LastTalkDate!=l){
        m_LastTalkDate=l;
        emit lastTalkDateChanged();
    }
}

void Chat::editSelectedPost(QString content)
{
    qDebug()<<"***[ edit Selected Post ]***";
    if(!selectMode()){
        return;
    }
    if(selectedCount()>1){
        message()->setContent("فقط یک پست را انتخاب کنید");
        return;
    }
    if(content.isNull()||content.isEmpty()){
        message()->setContent("متن پست خالی است");
        return;
    }
    selectedPost()->setContent(content);
    if(type()== ChatTypes::ChatTypesENUM::FrequentQuestions){
        specifyQAType(selectedPost());
        selectedPost()->save();
    }
    else{
        qWarning()<<"Edit Post Not implemented for ChatTypes of not FrequentQuestions";
        //selectedPost()->send(chatId());
    }
}

void Chat::specifyQAType(Post* post)
{
    qDebug()<<"***[specify Post is Question or Answer ]***";

    qDebug()<<"get previous post";
    Post* previousPost= posts()->at(selectedPostIndex()-1);
    //Question=> (fromMe is true) &&  (userId is null)
    //Answer=>   (fromMe is false) && (userId is not null)
    if(previousPost==nullptr)
    {
        qDebug()<<"previous post was null=> first post is a question";
        post->setFromMe(true);
        post->setUserId("");
    }
    else {
        qDebug()<<"new post is opisite of previous post(previous is question new is answer ;previous is answer new is question) ";
        if(previousPost->fromMe()){
            qDebug()<<"previous post was question";
            post->setFromMe(false);
            post->setUserId(userId());
        }
        else {
            qDebug()<<"previous post was answer";
            post->setFromMe(true);
            post->setUserId("");
        }
    }
}

void Chat::send(QString content)
{
    qDebug()<<"***[ Is Sending new post ]***";
    content=content.trimmed();
    if(content.isNull()||content.isEmpty()){
        message()->setContent("پیام خود را وارد کنید");
        return;
    }
    if(chatId().isNull()||chatId().isEmpty()){
        message()->setContent("شناسه چت نادرست است");
        return;
    }
    if(userId().isNull()||userId().isEmpty()){
        message()->setContent("شناسه کاربر ارسال کننده نادرست است");
        qDebug()<<"contats.count=> "<<m_Contacts.rowCount();
        return;
    }
    Post* newPost=new Post(userId(), chatId(),content);
    if(type()==ChatTypes::ChatTypesENUM::FrequentQuestions){
        qInfo()<<"Is going to Save new Frequent Questions";        
        if(userId().isNull()||userId().isEmpty()){

            message()->setContent("شناسه کاربر ارسال کننده خالی است");
            return;
        }
        specifyQAType(newPost);
        newPost->save();
        addNewPost(newPost,true);
    }
    else if(type()==ChatTypes::ChatTypesENUM::Conversation){
        qDebug()<<"Is sending new post";
        qDebug()<<"from me(userId => "<<userId()<<" to contact with id=> "<<chatId();

        newPost->send(chatId());
        addNewPost(newPost,true);
    }
//    qDebug()<<"from me(userId => "<<userId()<<" to contact with id=> "<<chatId();
//    Post* newTalk=new Post(userId(), chatId(),talkContent);

//    newTalk->send(chatId());
    //    addNewPost(newTalk,true);
}

void Chat::reloadMe(){
    qDebug()<<"***[ reload Me ]***";
    for (int i = 0; i < contacts()->rowCount(); ++i) {
        if(m_Contacts.at(i)->isMe()){
            m_Contacts.at(i)->getFromServer();
            qDebug()<<"Me founded is reloading";
            break;
        }
    }
}

void Chat::save()
{
    qDebug()<<"***[ Chat Save ]***";
    if(chatName().isNull()||chatName().isEmpty()){
        message()->setContent("نام گفتگو خالی است");
        return;
    }
//    if(chatId().isNull()||chatId().isEmpty()){
//        message()->setContent("شناسه گفتگو خالی است");
//        return;
//    }
    QNetworkReply* r=postRequest("api/Chat",toJson());
    connect(r,&QNetworkReply::finished,this,&Chat::onSaveFinished);
}

void Chat::onSaveFinished(){
    qDebug()<<"***[ on Chat Save Finished ]***";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj=jsonUtility()->convertToJsonObject(r);
        qDebug()<<"chatid=> "<<chatId();
        setChatId(obj.value("id").toString());
        qDebug()<<"chatid=> "<<chatId();
        message()->setContent(obj.value("message").toString(),true);
    }
    else{
        showBadMessage(r->readAll());
    }
}

void Chat::load()
{
    qDebug()<<"***[ Chat Load ]***";
    if(type()==ChatTypes::ChatTypesENUM::FrequentQuestions){
        QNetworkReply* r=getRequest("api/FrequentQuestions");
        connect(r,&QNetworkReply::finished,this,&Chat::onLoadFinished);
    }
    else{
        qWarning()<<"not implemented for other type of chats";
    }
}

void Chat::onLoadFinished()
{
    qDebug()<<"***[ on Chat Load Finished ]***";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj=jsonUtility()->convertToJsonObject(r);
        fromJson(obj);
        emit loadFinishd(true);
    }
    else{
        showBadMessage(r->readAll());
        emit loadFinishd(false);
    }
}

bool Chat::isTyping()
{
    return m_IsTyping;
}

void Chat::setIsTyping(bool i)
{
    if(m_IsTyping!=i){
        m_IsTyping=i;
        emit isTypingChanged();
    }
}

void Chat::displayIsTyping()
{
    if(m_Timer==nullptr){
        return;
    }
    m_Timer->start();
    setIsTyping(true);
}

void Chat::resendMessage()
{    
    for (int i = 0; i < m_Posts.rowCount(); ++i) {
        Post* t=m_Posts.at(i);
        if(t->fromMe()&&t->status()==TalkStatus::TalkStatusEnum::NotSend){
            qDebug()<<"founded a post with status NotSend =>send it again";
            t->send(chatId());
        }
        if(type()==ChatTypes::ChatTypesENUM::Conversation){
        }
        else{
            Post* t=qobject_cast<Post*>(m_Posts.at(i));
            if(t->fromMe()&&t->hasNotReceivedStatus()){
                qDebug()<<"founded a post with status NotSend =>send it again";
                t->send(chatId());
            }
        }
    }
}

void Chat::getPosts()
{
    qDebug()<<"***[ getPosts ]***";
    if(isProcessing()){
        message()->setContent("در حال دریافت لیست پست ها");
        return;
    }
    if(listHasCompeleted()){
        message()->setContent("لیست پست ها پایان یافته است");
        return;
    }
    if(type()==ChatTypes::ChatTypesENUM::FrequentQuestions){
       qDebug()<<"Is going to get new Frequent Questions";
       QNetworkReply* r=getRequest(QString("api/Chat/Posts/%1?skipCount=%2&count=%3").arg(chatId()).arg(skipCount()).arg(takeCount()));
       connect(r,&QNetworkReply::finished,this,&Chat::onGetPostsFinished);
    }
    else if (type()==ChatTypes::ChatTypesENUM::Conversation) {
        //    QNetworkReply* r=getRequest("api/Chat/Talks/"+userId());
        //    connect(r,&QNetworkReply::finished,this,&Chat::onGetTalks);
    }
}

void Chat::onGetPostsFinished()
{
    qDebug()<<"***[ on Get Posts Finished ]***";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonArray posts=jsonUtility()->convertToJsonArray(r->readAll());
        for (int i = 0; i < posts.count(); ++i) {
            Post* newPost=new Post(posts.at(i).toObject());
            addNewPost(newPost);
        }
        setLastTakedCount(posts.count());
    }
    else {

    }
}

void Chat::onGetTalks()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        //qInfo()<<"response=> "<<r->readAll();
        QJsonArray talks= jsonUtility()->convertToJsonArray(r->readAll());
        qInfo()<<"talks.count=> "<<talks.count();
        for (int i = 0; i < talks.count(); ++i) {
            addNewPost(talks.at(i).toObject());
        }
        emit getTalkFinishd(true);
    }
    else {
        emit getTalkFinishd(false);
    }
}

QJsonObject Chat::toJson()
{
    QJsonObject obj;
    obj.insert("id",chatId());
    obj.insert("userId",userId());
    obj.insert("type",(int)type());
    obj.insert("chatName",chatName());
    obj.insert("date",dateTimeUtility()->fromDateTime(date()));
    obj.insert("isMuted",isMuted());

    obj.insert("imageName",image()->imageName());
    obj.insert("imageUrl",image()->downloadLink());
    QJsonArray posts;

    for (int i = 0; i < m_Posts.rowCount(); ++i) {
        if(type()==ChatTypes::ChatTypesENUM::Conversation){
            Post* t=qobject_cast<Post*>(m_Posts.at(i));
            if(!t->isJustDate()){
                posts.append(t->toJson());
            }
        }
        else {
            Post* t=qobject_cast<Post*>(m_Posts.at(i));
            if(!t->isJustDate()){
                posts.append(t->toJson());
            }
        }
    }
    obj.insert("posts",posts);
    return obj;
}

void Chat::fromJson(QJsonObject json)
{
    setChatId(json.value("id").toString());
    setUserId(json.value("userId").toString());
    setChatName(json.value("chatName").toString());
    setDate(dateTimeUtility()->toDateTime(json.value("date").toString()));
    setDescription(json.value("description").toString());
    setType(static_cast<ChatTypes::ChatTypesENUM>(json.value("type").toInt()));
    image()->setDownloadLink(json.value("imageUrl").toString());

    //"imageBytes\":null,\"imageBase64\":null,\"imageName\":null,\"imageUrl\":null},

    QJsonArray contats=json.value("contacts").toArray();
    if(contats.count()==0){
        qCritical()<<"Chat don't have any contact in json";
    }
    for (int i = 0; i < contats.count(); ++i) {
        Contact* con=new Contact(contats.at(i).toObject());
        addContact(con);
    }
    QJsonArray talks=json.value("posts").toArray();
    for (int i = 0; i < talks.count(); ++i) {
        if(type()==ChatTypes::ChatTypesENUM::Conversation){
            Post* t=new Post(talks.at(i).toObject());
            addNewPost(t);
        }
        else{
            Post* t=new Post(talks.at(i).toObject());
            addNewPost(t);
        }
    }
}

void Chat::deleteItem()
{
    qDebug()<<"***[ Chat::deleteItem ]***";
    if(type()==ChatTypes::ChatTypesENUM::Conversation){
        qDebug()<<"chat was conversation => delete locallly ";
        emit deleteSucceed();
        return;
    }
    else {
        qDebug()<<"chat was not conversation => delete from server ";
        QNetworkReply* r=deleteRequest("api/Chat/"+chatId());
        connect(r,&QNetworkReply::finished,this,&Chat::onDeleteItem);
    }
}

void Chat::onDeleteItem()
{
    qDebug()<<"***[ Chat::onDeleteItem ]***";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        showOkMessage(r->readAll());
        emit deleteSucceed();
    }
    else{
        showBadMessage(r->readAll());
    }
}

void Chat::updateTalkStatus(QJsonObject status)
{
    qInfo()<<"Is updating status of post";
    qWarning()<<"Need to change this depeds on talks and posts";
    Post* t=posts()->find(status.value("id").toString());
    if(t==nullptr){
        qInfo()<<"the post not found -> return";
        return;
    }
    if(t->fromMe()){
        qInfo()<<"the post is from me so update status";
        t->setStatus((TalkStatus::TalkStatusEnum)status.value("status").toInt());
        qInfo()<<"updating status done";
        qInfo()<<"now request your contact for status of your talks";
        for (int i = 0; i < posts()->rowCount(); ++i) {
            Post* myTalk=posts()->at(i);
            if(!myTalk->fromMe()){
                break;
            }
            if(myTalk->waitingForResendStatus()){
                qDebug()<<"request has been send so just wait for that";
                break;
            }
            if(myTalk->status()==TalkStatus::TalkStatusEnum::Send){
                if(myTalk->date().secsTo(t->date())>=9/*||myTalk->date()>=t->date()*/)
                {
                    qInfo()<<"send request for resending status of post.id=> "<<myTalk->id();
                    myTalk->sendStatus(true);
                }
                else {
                    qInfo()<<"don't need for send request for status(not yet passed 9 seconds";
                }
            }
        }
    }
    else{
        qInfo()<<"this is a requset of resending my contact post status";
        qInfo()<<"so I am resending status to my contact again";
        t->sendStatus();
    }
}

void Chat::deletePosts()
{
    qDebug()<<"***[ delete Posts ]***";
    if(selectedCount()<=0){
        setSelectMode(false);
        return;
    }
//    WebSocketInfo* wsi=new WebSocketInfo();
//    wsi->setType("DeleteTalks");
//    wsi->setContactId(contactId());
//    wsi->setInformation(jsonUtility()->convertToJsonString(toJsonTalkIds()));
//    if(!m_WebSocketHandler->sendTextMessage(wsi->toJson())){
//        m_WebSocketHandler->open();
//    }
    if(type()==ChatTypes::ChatTypesENUM::FrequentQuestions){
        if(selectedCount()>1){
            setSelectMode(false);
            message()->setContent("برای حذف فقط یکی را انتخاب کنید");
        }
        else {
            for (int i = 0; i < posts()->rowCount(); ++i) {
                if(posts()->at(i)->isSelected()){
                    posts()->at(i)->deleteItem(true);
                    break;
                }
            }
        }
    }
    else {
        if(selectedCount()==1){
            for (int i = 0; i < posts()->rowCount(); ++i) {
                if(posts()->at(i)->isSelected()){
                    posts()->at(i)->deleteItem();
                    break;
                }
            }
        }
        else {
            for (int i = 0; i < posts()->rowCount(); ++i)
            {
                if(posts()->at(i)->isSelected())
                {
                    posts()->removeById(posts()->at(i)->id());
                    i--;
                }
            }
            emit needToSaveInFile();
            setSelectMode(false);
        }
    }
}

void Chat::removeIfIsEmpty()
{
    if(type()!=ChatTypes::ChatTypesENUM::Conversation){
        return;
    }
    if(posts()->rowCount()==0){
        emit deleteSucceed();
    }
}

bool Chat::hasAnyPost()
{
    return posts()->rowCount()>0;
}
//===============================================================================================
void Chat::onDeleteTalks()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        for (int i = 0; i < posts()->rowCount(); ++i) {
            if(posts()->at(i)->isSelected()){
                qInfo()<<"selected index=> "<<i;
                posts()->removeRows(i,1);
            }
        }
        setSelectMode(false);
        showOkMessage(r->readAll());
    }
    else {
        showBadMessage(r->readAll());
    }
}

void Chat::addContact(Contact *c)
{    
    qInfo()<<"***[ add contact ]***";
    if(c==nullptr){
        qInfo()<<"contact is null return";
        return;
    }
    connect(c,&Contact::updateFinished,this,&Chat::onContactUpdateFinished);
    m_Contacts.add(c);
    if(c->isMe()){
        qInfo()<<"contact is me set userID to => "<<c->userId();
        if(c->userId().isNull()||c->userId().isEmpty()){
            c->getFromServer();
        }
        setUserId(c->userId());
    }
    else{
        if(type()==ChatTypes::ChatTypesENUM::Conversation){
            m_Contact=c;
            emit contactChanged();
            updateFromContact(c);
        }
    }
}

void Chat::updateFromContact(Contact *c)
{
    qDebug()<<"***[ Update from contact ]***";
    if(type()!=ChatTypes::ChatTypesENUM::Conversation){
        return;
    }
    if(c->isMe()){
        setUserId(c->userId());
    }
    else{
        setChatName(c->displayName());
        updateLastTalkDate();
        setChatId(c->userId());

        image()->setDownloadLink(c->downloadLink());
        image()->download();
    }
}

void Chat::onContactUpdateFinished()
{
    qDebug()<<"***[ on Contact Update Finished ]***";
    Contact* c=qobject_cast<Contact*>(sender());
    qInfo()<<c->userId();
    qInfo()<<c->displayName();
    qInfo()<<c->toJson();
    updateFromContact(c);
}

void Chat::deselectAll()
{
    for (int i = 0; i < posts()->rowCount(); ++i) {
        posts()->at(i)->setIsSelected(false);
    }
}

void Chat::selectAll()
{
    for (int i = 0; i < posts()->rowCount(); ++i) {
        posts()->at(i)->setIsSelected(true);
    }
}

QJsonObject Chat::toJsonTalkIds()
{
    QJsonObject obj;
    QJsonArray ids;
    for (int i = 0; i < posts()->rowCount(); ++i) {
        if(posts()->at(i)->isSelected()){
            ids.append(posts()->at(i)->id());
        }
    }
    obj.insert("talkIds",ids);
    return obj;
}

void Chat::addNewPost(Post* post,bool triggeredByUser){
    qDebug()<<"***[ add New Post ]***";
    connect(post,&Post::isSelectedChanged,this,&Chat::onTalkIsSelectedChanged);
    connect(post,&Post::deleteSucceed,this,&Chat::onTalkDeletedSucceed);
    connect(post,&Post::postSendSucceed,this,&Chat::onPostSendSucceed);
    connect(post,&Post::statusChanged,this,&Chat::updateUnReadTalksCount);
    if(type()==ChatTypes::ChatTypesENUM::FrequentQuestions){
        post->setFromMe(post->userId().isNull()&&post->userId().isEmpty());
        qInfo()<<"post->userId()=> "<<post->userId();
        qInfo()<<"post->fromMe()=> "<<post->fromMe();
        post->setStatus(TalkStatus::TalkStatusEnum::Seen);
    }
    else{
        qDebug()<<"is fromMe userId is CurrentUser.UserID";
        if(post->userId().isNull()){
            qWarning()<<"because post.userId is null , so fromMe will not be specified correctly";
        }
        if(post->userId()==userId()){
            post->setFromMe(true);
        }
    }
    if(posts()->find(post->id())==nullptr){
        posts()->append(post,type()!=ChatTypes::ChatTypesENUM::FrequentQuestions);
    }
    if(type()==ChatTypes::ChatTypesENUM::Conversation){
        if(posts()->rowCount()==2){//the first post is just display date the second is the real post
            emit firstTalkAdded();
        }
    }
    updateLastTalkOnChatItem();
    if(triggeredByUser){//I'm sending new message or new message received from contact
        if(type()==ChatTypes::ChatTypesENUM::FrequentQuestions){
            emit newPostIsSended();
        }
        else{
            if(post->fromMe()){
                emit newPostIsSended();
            }
            else{
                emit newTalkReceived(m_SoundFileNewMessage->url().toString());
            }
        }
    }
}

void Chat::addNewPost(QJsonObject post){
    Post* newTalk=new Post(post);
    addNewPost(newTalk);
}

void Chat::updateUnReadTalksCount(){
    //APPSTEP: set un read talks counts
    if(type()!=ChatTypes::ChatTypesENUM::FrequentQuestions){
        setUnReadTalks(posts()->unReadTalksCount());
    }
}

void Chat::updateLastTalkOnChatItem(){
    updateLastTalkDate();
    if(posts()->rowCount()>0){
        setLastTalk(posts()->at(posts()->rowCount()-1)->content());
    }
    updateUnReadTalksCount();
}

void Chat::onPostSendSucceed()
{
    emit postSendSucceed(m_SendMessageSound->url().toString());
}

void Chat::onTalkIsSelectedChanged()
{
    int count=0;
    for (int i = 0; i < posts()->rowCount(); ++i) {
        if(posts()->at(i)->isSelected()){
            count++;
        }
    }
    setSelectedCount(count);
    setSelectMode(count>0);
}

void Chat::updateLastTalkDate()
{
    PersianDateTime* pdt=nullptr;
    if(posts()->rowCount()<=0){
        //ToDo: set contact last activity date to last post date
        //pdt=new PersianDateTime(image()->lastActivityDate());
    }
    else if(posts()->rowCount()>0){
        pdt= new PersianDateTime(posts()->at(posts()->rowCount()-1)->date());
    }

    if(pdt==nullptr){
        setLastTalkDate("");
    }
    else if(pdt->isToday()){
        setLastTalkDate(pdt->toString(PersianDateTime::TextFormats::ShortTime));
    }
    else if(pdt->isYesterday()){
        setLastTalkDate("دیروز");
    }
    else {
        setLastTalkDate(pdt->toString(PersianDateTime::TextFormats::ShortDate));
    }
}

void Chat::onTalkDeletedSucceed()
{
    setSelectMode(false);
    updateLastTalkOnChatItem();
    emit needToSaveInFile();
}

void Chat::sendIsTyping()
{
    qDebug()<<"Is sending IsTyping";
    if(type()==ChatTypes::ChatTypesENUM::FrequentQuestions){
        qDebug()<<"don't need to send for fq";
        return;
    }
    if(chatId().isNull()||chatId().isEmpty()){
        message()->setContent("شناسه مخاطب خالی است");
        return;
    }
    WebSocketInfo* wsi=new WebSocketInfo();
    wsi->setType("ChatIsTyping");
    wsi->setReceiverId(chatId());
    if(!m_WebSocketHandler->sendTextMessage(wsi->toJson())){
        m_WebSocketHandler->open();
    }
    wsi->deleteLater();
}
