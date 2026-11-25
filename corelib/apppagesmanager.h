#ifndef APPPAGESMANAGER_H
#define APPPAGESMANAGER_H

#include<QObject>
#include<QQuickItem>
#include<QQuickWindow>
#include<QQuickView>
//#include<QQuickMenu>
#include<QQmlEngine>
#include<QQmlContext>
#include<QQmlApplicationEngine>
#include<QImage>
#include<QMetaObject>
#include<QQmlComponent>
#include<QVariant>
#include<QMetaType>

class AppPagesManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickWindow* mainWindow READ mainWindow WRITE setMainWindow NOTIFY mainWindowChanged)
    Q_PROPERTY(QQmlApplicationEngine* engine READ engine CONSTANT)

public:
    explicit AppPagesManager(QObject *parent = nullptr);
    Q_INVOKABLE void toStringObject(QObject* obj);

    QQuickWindow* mainWindow();
    void setMainWindow(QQuickWindow *item);

    static QQuickWindow *m_MainWindow;

    static QQmlApplicationEngine *m_Engine;
    QQmlApplicationEngine* engine();
    Q_INVOKABLE void loadQQmlApplicationEngine(QQmlApplicationEngine *obj);
    Q_INVOKABLE bool grabWindow(QString path);
    Q_INVOKABLE QImage grabWindow();

    void closePage();

    Q_INVOKABLE QObject *find(QString name);
    QQuickItem *findAsItem(QString name);
    QQuickView *findAsView(QString name);

    Q_INVOKABLE void checkMenuItem(QObject *obj);

    Q_INVOKABLE void findMe(QObject *obj);
    Q_INVOKABLE void writeAll();
    void fillListItem(QObject *obj);
    void isSameEngine();
    void createChatsPageCom();

    void writeChildrens(QObject *item);
    void writeChildrens(QString objectName);
    QObject *getComponent(QString url, QObject *parent=nullptr);
    /// create component from url and set the item as the new component parent
    /// create a new component and add to item's childrens
    void setParentItem(QString qmlFileUrl, QString name="ApplicationWindow");
    void replaceItem(QString qmlFileUrl, QString name);
    void setParentItem(QString qmlFileUrl, QQuickItem *item);
   Q_INVOKABLE void setWindow(QString qmlFileUrl, QString windowName="");
    Q_INVOKABLE void loadMainWindow(QString qmlFileUrl);
    Q_INVOKABLE void clearCache();
signals:
    void mainWindowChanged();
    void grabbedWindowFinished(bool succeed);

private slots:
    void newObjectCreated(QObject* object, const QUrl &url);
    void activeFocuseChanged(QObject* obj);
private:
    QList<QObject*> allItems;
};

#endif // APPPAGESMANAGER_H
