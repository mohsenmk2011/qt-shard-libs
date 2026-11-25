#ifndef KEYWORDMANAGER_H
#define KEYWORDMANAGER_H

#include <QObject>
#include<listmanager.h>
#include<keywordlistmodel.h>

class KeywordManager : public ListManager
{
    Q_OBJECT
    Q_PROPERTY(KeywordListModel* listModel READ listModel CONSTANT)
public:
    explicit KeywordManager(QObject *parent = nullptr);
    Q_INVOKABLE void getList(int parentId);
    KeywordListModel* listModel();
    Q_INVOKABLE void addNewItem(int parentId);

signals:

private slots:
    void getListFinished();
private:
    KeywordListModel m_ListModel;
};

#endif // KEYWORDMANAGER_H
