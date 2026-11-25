#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include<QString>
#include<QDateTime>
#include<chattypes.h>
#include<talklistmodel.h>
#include<jooyanetwork.h>
#include<file.h>
#include<QJsonObject>
#include<QTcpSocket>
#include<QSslSocket>
#include<QAbstractSocket>
#include<QNetworkInterface>
#include<contact.h>
#include<listmanager.h>
#include<imagefile.h>
#include<QLocale>
#include<qcalendar.h>
#include<persiandatetime.h>
#include<talkstates.h>
#include<QUuid>
#include<datetimeutility.h>
#include<postbase.h>
#include<post.h>
#include<contactlistmodel.h>
#include<postlistmodel.h>

using namespace std;
class Chat : public ListManager
{
    Q_OBJECT
    Q_PROPERTY(ContactListModel* contacts READ contacts CONSTANT)
    Q_PROPERTY(Post* selectedPost READ selectedPost CONSTANT)
    Q_PROPERTY(QString chatId READ chatId WRITE setChatId NOTIFY chatIdChanged)
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(ChatTypes::ChatTypesENUM type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString chatName READ chatName WRITE setChatName NOTIFY chatNameChanged)
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(PersianDateTime* pDate READ pDate CONSTANT)
    Q_PROPERTY(bool isMuted READ isMuted WRITE setIsMuted NOTIFY isMutedChanged)
    Q_PROPERTY(bool isTyping READ isTyping WRITE setIsTyping NOTIFY isTypingChanged)
    Q_PROPERTY(ImageFile* image READ image CONSTANT)

    Q_PROPERTY(QString lastTalkDate READ lastTalkDate WRITE setLastTalkDate NOTIFY lastTalkDateChanged)    
    Q_PROPERTY(int unReadTalks READ unReadTalks WRITE setUnReadTalks NOTIFY unReadTalksChanged)
    Q_PROPERTY(QString lastTalk READ lastTalk WRITE setLastTalk NOTIFY lastTalkChanged)

    Q_PROPERTY(PostListModel* posts READ posts CONSTANT)

public:
    explicit Chat(QObject *parent = nullptr);
    explicit Chat(QJsonObject obj);
    explicit Chat(ChatTypes::ChatTypesENUM type);

    PostListModel* posts();

    ContactListModel* contacts();
    Post* selectedPost();
    int selectedPostIndex();
    ImageFile* image();

    QString chatId();
    void setChatId(QString id);

    QString userId();
    void setUserId(QString u);

    QString description();
    void setDescription(QString d);

    QString chatName();
    void setChatName(QString n);

    QDateTime date();
    void setDate(QDateTime d);
    PersianDateTime* pDate();

    ChatTypes::ChatTypesENUM type();
    void setType(ChatTypes::ChatTypesENUM t);

    bool isMuted();
    void setIsMuted(bool m);

    int unReadTalks();
    void setUnReadTalks(int u);

    QString lastTalk();
    void setLastTalk(QString l);

    QString lastTalkDate();
    void setLastTalkDate(QString l);

    Q_INVOKABLE virtual void send(QString content);

    Q_INVOKABLE virtual void save();
    Q_INVOKABLE void load();

    bool isTyping();
    void setIsTyping (bool i);

    Q_INVOKABLE virtual void sendIsTyping();
    virtual bool hasAnyPost();
    Q_INVOKABLE virtual void addContact(Contact *c);
    void displayIsTyping();
    virtual void addNewPost(QJsonObject post);
    virtual void addNewPost(Post *post, bool triggeredByUser=false);

    virtual void resendMessage();
    Q_INVOKABLE virtual void getPosts();

    QJsonObject toJson() override;
    void fromJson(QJsonObject json) override;
    void deleteItem();
    File* m_SendMessageSound;
    //paly when new Message received in chat
    File* m_SoundFileNewMessage;
    void updateTalkStatus(QJsonObject status);

    Q_INVOKABLE void deletePosts();
    Q_INVOKABLE void selectAll() override;
    void deselectAll() override;
    void updateLastTalkOnChatItem();
    Q_INVOKABLE void removeIfIsEmpty();
    Q_INVOKABLE void editSelectedPost(QString content);
    void reloadMe();
signals:
    void chatIdChanged();
    void userIdChanged();
    void descriptionChanged();
    void typeChanged();
    void chatNameChanged();
    void dateChanged();
    void isMutedChanged();
    void isTypingChanged();

    void unReadTalksChanged();
    void lastTalkDateChanged();
    void lastTalkChanged();
    void deleteSucceed();
    void loadFinishd(bool succeed);

    ///new Post Received from contact
    void newTalkReceived(QString soundFileUrl);
    ///emits when current user has been added Post to listmodel
    void newPostIsSended();
    ///Post send to server
    void postSendSucceed(QString soundFileUrl);
    void getTalkFinishd(bool succeed);

    void contactIdChanged();
    void contactChanged();

    //this emits when frist post added to chat
    //after emitting this signal  chat will be addded to chat list
    void firstTalkAdded();
private slots:
    void typingTimerTimeout();
    void onSaveFinished();    
    void onDeleteItem();
    void onLoadFinished();
    void onGetPostsFinished();

    void onDeleteTalks();
    void onTalkDeletedSucceed();
    void onGetTalks();
    void onPostSendSucceed();
    void onTalkIsSelectedChanged();
    void updateLastTalkDate();
    void updateUnReadTalksCount();
    void onContactUpdateFinished();
private:
    QString m_ChatId;
    QString m_UserId;
    QString m_Description;
    QString m_ChatName;
    int m_UnReadTalks;
    QString m_LastTalk;
    bool m_IsMuted;
    QString m_LastTalkDate;
    QDateTime m_Date;
    ChatTypes::ChatTypesENUM m_Type;
    QTimer* m_Timer;
    bool m_IsTyping;
    ImageFile* m_Image;
    ContactListModel m_Contacts;
    PostListModel m_Posts;


    Contact* m_Contact;
//    TalkListModel m_ListModel;S
    QJsonObject toJsonTalkIds();
    void updateFromContact(Contact *c);
    void specifyQAType(Post *post);
};

#endif // CHAT_H
