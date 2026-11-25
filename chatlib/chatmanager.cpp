#include "chatmanager.h"

ChatManager::ChatManager(QObject *parent) : ListManager(parent)
{
    m_UnReadTalks=0;
    loadFromFile();
    connect(m_WebSocketHandler,&WebSocketHandler::newInfoReceived,this,&ChatManager::onNewInfoReceived);    
    connect(m_WebSocketHandler,&WebSocketHandler::connectedChanged,this,&ChatManager::onWebSocketConnected);
    m_NewNotification=new File("/Audios/NewNotification1.mp3");
    m_NewNotification->setDisplayCommonErrorMessage(false);
    m_NewNotification->download();
}

ChatManager::~ChatManager()
{
    saveChatsToFile();
}

void ChatManager::loadFromFile(){
    qInfo()<<"Is Reading Chats From Json File => ";
    QJsonArray jsonChats= fromJsonFile("chats");
    for (int i = 0; i < jsonChats.count(); ++i) {
        QJsonObject obj=jsonChats.at(i).toObject();
        Chat* newchat=new Chat(obj);
        //TODO: CHECK if contact and me is added
        addNewChatToList(newchat);
    }
    qInfo()<<jsonChats;
}

ChatListModel* ChatManager::listModel()
{
    return &m_ListModel;
}

ContactManager *ChatManager::contactManager()
{
    return &m_ContactManager;
}

Chat *ChatManager::selectedChat()
{
    if(selectedCount()==1){
        for (int i = 0; i < m_ListModel.rowCount(); ++i) {
            if(m_ListModel.at(i)->isSelected()){
                return m_ListModel.at(i);
            }
        }
    }
    return nullptr;
}

int ChatManager::unReadTalks()
{
    return m_UnReadTalks;
}

void ChatManager::setUnReadTalks(int u)
{
    if(m_UnReadTalks!=u){
        m_UnReadTalks=u;
        emit unReadTalksChanged(m_NewNotification->url().toString());
    }
}

void ChatManager::getList()
{
    qDebug()<<"***[ ChatManager::getList ]***";
    if(!loginInfo()->isLoggedIn())
    {
        return;
    }
    if(listHasCompeleted()){
        qDebug()<<" list Has Compeleted ";
        return;
    }
    QNetworkReply* r=getRequest("api/Chat");
    connect(r,&QNetworkReply::finished,this,&ChatManager::onGetListFinished);
}
void ChatManager::onGetListFinished()
{
    qDebug()<<"***[ ChatManager::onGetListFinished ]***";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonArray chats=jsonUtility()->convertToJsonArray(r->readAll());
        for (int i = 0; i < chats.count(); ++i) {
            Chat* newChat =new Chat(chats.at(i).toObject());
            addNewChatToList(newChat);
        }
        setListHasCompeleted(true);
    }
    else {
        //TODO: emit no chat found for display message "Click Here for nnew chat" in chatspage.qml
        qCritical()<<"Error=>"<<r->readAll();
    }
}

void ChatManager::getTalks()
{
    //TODO: Send websocket request for getting new chats that are in database(when i was not online)
    qWarning()<<"Send websocket request for getting new chats that are in database(when i was not online) ";
    QNetworkReply* r=getRequest("api/Post");
    connect(r,&QNetworkReply::finished,this,&ChatManager::onGetTalksFinished);
}

void ChatManager::onGetTalksFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        readTalks(r->readAll());
    }
    else {
        //TODO: emit no chat found for display message "Click Here for nnew chat" in chatspage.qml
        qCritical()<<"Error=>"<<r->readAll();
    }
}

void ChatManager::sendIAmOnline()
{
    WebSocketInfo* wsi=new WebSocketInfo();
    wsi->setType("IAmOnline");
    if(!m_WebSocketHandler->sendTextMessage(wsi->toJson())){
        m_WebSocketHandler->open();
    }
}

void ChatManager::selectAll()
{
    for (int i = 0; i < m_ListModel.rowCount(); ++i) {
        m_ListModel.at(i)->setIsSelected(true);
    }
}

void ChatManager::deselectAll()
{
    for (int i = 0; i < m_ListModel.rowCount(); ++i) {
        m_ListModel.at(i)->setIsSelected(false);
    }
}

QJsonArray ChatManager::toJsonArray()
{
    QJsonArray array;
    for (int i = 0; i < m_ListModel.rowCount(); ++i)
    {
        Chat* c=m_ListModel.at(i);
        if(c->hasAnyPost())
        {
            array.append(c->toJson());
        }
    }
    return array;
}

void ChatManager::deleteChats()
{
    qInfo()<<"selectedCount()=> "<<selectedCount();
    if(selectedCount()<1){
        setSelectMode(false);
        return;
    }

    for (int i = 0; i < m_ListModel.rowCount(); ++i) {
        Chat* cc=m_ListModel.at(i);
        if(cc->isSelected()){
            cc->deleteItem();
        }
    }
    setSelectMode(false);
}

void ChatManager::onNewTalkReceived(QJsonObject obj, QString senderId , QString receiverId){
    qDebug()<<"add new Post(talk or message) (that received from "<<senderId<<")";
    Post* newTalk=new Post(obj);

    Chat* currentChat=nullptr;
    if(senderId.isNull()||senderId.isEmpty()){
        qDebug()<<"senderId is null=> return";
        return;
    }
    qDebug()<<"find chat with senderId";
    currentChat=m_ListModel.find(senderId);

    if(currentChat==nullptr){
        qDebug()<<"chat not found(this is first post of sender)";
        currentChat= new Chat();
        currentChat->setChatId(senderId);
        currentChat->setUserId(receiverId);
        currentChat->setType(ChatTypes::ChatTypesENUM::Conversation);
        addNewChatToList(currentChat);
    }
    if(currentChat->userId().isNull()){
        currentChat->setUserId(receiverId);
    }
    currentChat->addNewPost(newTalk,true);
    newTalk->setStatus(TalkStatus::TalkStatusEnum::Received);
    qInfo()<<"=> Send status of received post to sender";
    newTalk->sendStatus();
}

void ChatManager::readTalks(QByteArray bytes)
{
    QString res=bytes;
    qInfo()<<"my chats => "<<res;
    QJsonArray talks=jsonUtility()->convertToJsonArray(res/*r->readAll()*/);
    for(int i = 0; i < talks.count(); ++i) {
//        onNewTalkReceived(talks.at(i).toObject());
        qWarning()<<"add post disabled";
    }
}

void ChatManager::addNewChatToList(Chat *newChat)
{
    qDebug()<<"***[ add New Chat To List ]***";
    m_ListModel.append(newChat);
    connect(newChat,&Chat::isSelectedChanged,this,&ChatManager::onChatIsSelectedChanged);
    connect(newChat,&Chat::deleteSucceed,this,&ChatManager::onChatDeleteSucceed);
    connect(newChat,&Chat::unReadTalksChanged,this,&ChatManager::onChatunReadTalksChanged);
    connect(newChat,&Chat::needToSaveInFile,this,&ChatManager::saveChatsToFile);
    addContacts(newChat);
}

void ChatManager::addContacts(Chat *newChat)
{
    qDebug()<<"***[ add Contacts ]***";
    QString senderId="";
    if(newChat->type()==ChatTypes::ChatTypesENUM::Conversation){
        qDebug()<<"chat is Conversation so chatId is senderId";
        senderId=newChat->chatId();
        qDebug()<<"find the contact("<<senderId<<") from contactManager";
        Contact* c=contactManager()->listModel()->find(senderId);
        if(c==nullptr)
        {
            qInfo()<<"contact not found;add new and load from server";
            c=new Contact();
            c->setUserId(senderId);
            contactManager()->listModel()->add(c);
            c->getFromServer();
        }
        else{
            qInfo()<<"founded contact toJson()=> "<<c->toJson();
            qDebug()<<"";
            newChat->addContact(c);
        }
    }
    else{
        qDebug()<<"chat is not Conversation so all contact should be loaded)";
    }
    qDebug()<<"add me to chat";
    newChat->addContact(contactManager()->me());
}

void ChatManager::saveChatsToFile()
{
    qInfo()<<"***[ Chats Is Saving ] ***";
    qInfo()<<toJsonArray();
    toJsonFile("chats",toJsonArray());
}

void ChatManager::onChatIsSelectedChanged()
{
    int count=0;
    for (int i = 0; i < m_ListModel.rowCount(); ++i) {
        if(m_ListModel.at(i)->isSelected()){
            count++;
        }
    }
    setSelectedCount(count);
    setSelectMode(count>0);
}

void ChatManager::onChatDeleteSucceed()
{
    qDebug()<<"***[ on Chat Delete Succeed ]***";
    qDebug()<<"save chats to file=>";
    saveChatsToFile();
}

void ChatManager::onChatunReadTalksChanged()
{
    int c=0;
    for (int i = 0; i < m_ListModel.rowCount(); ++i) {
        c+=m_ListModel.at(i)->unReadTalks();
    }
    setUnReadTalks(c);
}

void ChatManager::startNewChat(Contact* contact)
{
    if(contact==nullptr){
        message()->setContent("مخاطب ارسال شده تهی است");
        return;
    }
    try {
        qDebug()<<"find chat of this contact with userid=> "<<contact->userId();
        Chat* newChat=m_ListModel.find(contact->userId());
        if(newChat==nullptr)
        {
            qDebug()<<"chat not found -> so create a new chat";
            newChat=new Chat();
            newChat->setType(ChatTypes::ChatTypesENUM::Conversation);
        }
        //TODO: if founded chat donn't have any contact? so add contact and me to that
        //TODO: The above has done: test it works or not(after receiving new post , click on contact so the image and name of chat should change
        newChat->addContact(contact);
        newChat->addContact(contactManager()->me());
        connect(newChat,&Chat::firstTalkAdded,this,&ChatManager::onFirstTalkAddedToChat);
        emit newChatStarted(newChat);
    }
    catch (std::exception & e)
    {
      // do something with what...
        qCritical()<<"Error=> "<<e.what();
    }
    catch (...)
    {
        qCritical()<<"Error=> ";
    }
}

void ChatManager::startNewChatWithMyself()
{
    startNewChat(contactManager()->me());
}

void ChatManager::onFirstTalkAddedToChat()
{
    Chat* newChat=qobject_cast<Chat*>(sender());
    addNewChatToList(newChat);
}

void ChatManager::onNewInfoReceived(WebSocketInfo *info)
{
//    qInfo()<<"information => "<<info->information();
//    qInfo()<<"cotactId => "<<info->contactId();
    qInfo()<<"info => "<<info->toJson();
    if(info->type()=="NewTalk"){
        qInfo()<<"New Info is New Post=> is adding";
        onNewTalkReceived(jsonUtility()->convertToJsonObject(info->information()),info->senderId(),info->receiverId());
    }
    //TODO: Managing error of reconnect socket
    else if(info->type()=="ChatIsTyping"){
        //APPSTEP: Display Istyping on chat
        Chat* currentChat=m_ListModel.find(info->senderId());
        if(currentChat!=nullptr){
            currentChat->displayIsTyping();
        }
    }
    else if(info->type()=="TalkStatus"){
        qInfo()<<"New TalkStatus received from  my contact => "<<info->senderId();
        QJsonObject talkStatusObj=jsonUtility()->convertToJsonObject(info->information());
        Chat* currentChat=m_ListModel.find(info->senderId());
        if(currentChat!=nullptr){
            qInfo()<<"chat found(update status of my post that recicec with ->??? ";//<<currentChat->contact()->displayName()<<")";
            currentChat->updateTalkStatus(talkStatusObj);
        }
        else {
            qWarning()<<"chat not found(contactid-> "<<info->senderId()<<")";
        }
    }
//    else if(info->type()=="NewConnection"){
//        QJsonObject talkStatusObj=jsonUtility()->convertToJsonObject(info->information());
//        qDebug()<<"Info isNewConnection from"<<info->senderId();
//        qInfo()<<"Update Last View Date Of user";
//        NewConnectionModel* cm=new NewConnectionModel(talkStatusObj);
//        contactManager()->getList()
//    }
}

void ChatManager::onWebSocketConnected()
{
    qDebug()<<"m_WebSocketHandler connected";
    if(m_WebSocketHandler->connected()){
        qDebug()<<"=> calling Chat.resendMessage for resending NotSend talks";
        for (int i = 0; i < m_ListModel.rowCount(); ++i) {
            m_ListModel.at(i)->resendMessage();
        }
    }
}
