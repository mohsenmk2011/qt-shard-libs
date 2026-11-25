#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<jooyalistitem.h>
#include<file.h>

class ListManager : public JooyaListItem
{
    Q_OBJECT
    Q_PROPERTY(bool selectMode READ selectMode WRITE setSelectMode NOTIFY selectModeChanged)
    Q_PROPERTY(int selectedCount READ selectedCount WRITE setSelectedCount NOTIFY selectedCountChanged)
    Q_PROPERTY(bool isSearching READ isSearching WRITE setIsSearching NOTIFY isSearchingChanged FINAL)
public:
    explicit ListManager(QObject *parent = nullptr);
    virtual void deselectAll();
    virtual void selectAll();
    int takeCount();
    void setTakeCount(int tc);

    int skipCount();
    void setSkipCount(int sc);
    ///آخرین تعداد آیتمی که گرفته شده است
    int lastTakedCount();
    ///آخرین تعداد آیتمی که گرفته شده است را ذخیره می کند
    void setLastTakedCount(int ltc);

    bool listHasCompeleted();
    void setListHasCompeleted(bool lhc);

    void addSkipCount(int val);

    /// will reset the values to default values
    void resetListValues();

    bool selectMode();
    void setSelectMode(bool s);

    int selectedCount();
    void setSelectedCount(int s);
    void toJsonFile(QString fileName,QJsonArray array);
    QJsonArray fromJsonFile(QString name);
    QNetworkReply* getListAndReturnArray(QString url);
    bool canGetList();
    bool isSearching() const;
    void setIsSearching(bool newIsSearching);

signals:
    /// emit this when you have got at least one entity
    void noMoreEntity();
    /// emit this when you have not got any entity yet
    void entityNotFound();
    void selectModeChanged();
    void selectedCountChanged();
    void isSearchingChanged();

public slots:
    void onGetList();
private:
    bool m_SelectMode;
    int m_SelectedCount;
    int m_SkipCount;
    int m_TakeCount;
    int m_LastTakedCount;
    bool m_ListHasCompeleted;
    bool m_isSearching;
};

#endif // LISTMANAGER_H
