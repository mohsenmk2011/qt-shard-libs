#ifndef APPINTRODUCER_H
#define APPINTRODUCER_H

#include <QObject>
#include<jooyanetwork.h>
#include<notifylistmodel.h>
#include<qjsonarray.h>
#include<notificationtypes.h>
#include<notificationcounts.h>
#include<qdebug.h>

class NotifyManager : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(NotifyListModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(NotificationTypes::NotificationTypesEnum currentType READ currentType WRITE setCurrentType NOTIFY currentTypeChanged)

public:
    explicit NotifyManager(QObject *parent = nullptr);

    NotificationTypes::NotificationTypesEnum currentType();
    void setCurrentType(NotificationTypes::NotificationTypesEnum type);

    Q_INVOKABLE void getList();

    Q_INVOKABLE void getNewCount(int versionCode);
    NotifyListModel* listModel();

    Q_INVOKABLE void refreshLastViewDate();
    Q_INVOKABLE void addNew();
    static NotificationCounts* m_Counts;

signals:
    void gettingListSucceed();
    void refreshLastViewSucceed(bool succeed);
    void selectLastIndex(int lastIndex);
    void currentTypeChanged();

private slots:
    void getListFinished();
    void refreshViewDateFinished();
    void getNewCountFinished();
private:
    NotifyListModel m_ListModel;
    NotificationTypes::NotificationTypesEnum m_CurrentType;
};

#endif // APPINTRODUCER_H
