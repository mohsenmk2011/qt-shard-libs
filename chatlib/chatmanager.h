#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<chatlistmodel.h>
#include<chat.h>
#include<tcpserver.h>
#include<QTcpServer>
#include<QTcpSocket>
#include<QHash>
#include<listmanager.h>
#include<contactmanager.h>
#include<fileutility.h>
#include<applicationpath.h>
#include<QMediaPlayer>

class ChatManager : public ListManager
{
    Q_OBJECT
    Q_PROPERTY(ChatListModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(Chat* selectedChat READ selectedChat CONSTANT)
    Q_PROPERTY(ContactManager* contactManager READ contactManager CONSTANT)
    Q_PROPERTY(int unReadTalks READ unReadTalks WRITE setUnReadTalks NOTIFY unReadTalksChanged)
public:
    explicit ChatManager(QObject *parent = nullptr);
    ~ChatManager();
    ChatListModel* listModel();

    ContactManager* contactManager();

    Chat* selectedChat();

    int unReadTalks();
    void setUnReadTalks(int u);

    Q_INVOKABLE void getList();
    Q_INVOKABLE void getTalks();
    Q_INVOKABLE void sendIAmOnline();

    Q_INVOKABLE void selectAll() override;
    Q_INVOKABLE void startNewChat(Contact *contact);
    Q_INVOKABLE void startNewChatWithMyself();
    void deselectAll() override;
    QJsonArray toJsonArray();
    Q_INVOKABLE void deleteChats();
signals:
    void noChatFounded();
    void newChatStarted(Chat* newChat);
    void unReadTalksChanged(QString url);
private slots:
    void onGetListFinished();
    void onGetTalksFinished();
    void onNewInfoReceived(WebSocketInfo* info);
    void onWebSocketConnected();
    void onChatIsSelectedChanged();
    void onChatDeleteSucceed();
    void onChatunReadTalksChanged();
    void onFirstTalkAddedToChat();
    void saveChatsToFile();
private:
    ChatListModel m_ListModel;
    ContactManager m_ContactManager;
    int m_UnReadTalks;
    void onNewTalkReceived(QJsonObject obj, QString senderId, QString receiverId);
    void loadFromFile();
    void readTalks(QByteArray bytes);
    void addNewChatToList(Chat* newChat);
    //paly when new Notification(Message,New Online User,New Paid Order,New User Registerd, received not in chat
    File* m_NewNotification;
    void addContacts(Chat *newChat);
};

#endif // CHATMANAGER_H
