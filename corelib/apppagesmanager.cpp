#include "apppagesmanager.h"

AppPagesManager::AppPagesManager(QObject *parent) : QObject(parent)
{
    allItems={};
}

void AppPagesManager::toStringObject(QObject *obj)
{
    qDebug()<<"obj=>ToString()==>> "<<obj;
}

QQuickWindow* AppPagesManager::m_MainWindow=nullptr;
QQmlApplicationEngine* AppPagesManager::m_Engine=nullptr;

QQuickWindow *AppPagesManager::mainWindow()
{
    return m_MainWindow;
}

void AppPagesManager::setMainWindow(QQuickWindow *item)
{
    qDebug()<<"(item!=nullptr)"<<(item!=nullptr);
    if(item!=nullptr){
        m_MainWindow=item;
        emit mainWindowChanged();
    }
}

void AppPagesManager::activeFocuseChanged(QObject* obj)
{
    qDebug()<<"############ AppPagesManager::activeFocuseChanged #############";
    if(obj!=nullptr){
        qDebug()<<"obj=>"<<obj;
    }
    qDebug()<<"############ AppPagesManager::activeFocuseChanged #############";
}

QQmlApplicationEngine *AppPagesManager::engine()
{
    return m_Engine;
}

void AppPagesManager::createChatsPageCom()
{
    QObject* stackView=(QQuickView*) m_MainWindow->children().at(2);
    //stackView->setSource("");
    //QQuickView* stackView=(QQuickView*) m_MainWindow->children().at(2);

    if(stackView!=nullptr){
        //        stackView->setProperty("depth",)
        int stackViewDepth= stackView->property("depth").toInt();
        QString stackViewId = stackView->property("id").toString();

        QString stackViewobjectName = stackView->property("objectName").toString();
        qCritical()<<"stackViewDepth =>"<<stackViewDepth;
        qCritical()<<"stackViewId =>"<<stackViewId;
        qCritical()<<"stackViewobjectName =>"<<stackViewobjectName;

        //        QQmlComponent comChatsPage(engine(),QUrl(QStringLiteral("qrc:/pages/chat/ChatsPage.qml")));
        //        QObject *object = comChatsPage.create();
        //        //QVariant arg = QVariant::fromValue(object);

        //        QVariant arg = QVariant::fromValue(QUrl(QStringLiteral("qrc:/pages/chat/ChatsPage.qml")));
        //        if(!QMetaObject::invokeMethod(stackView, "push",Qt::DirectConnection,Q_ARG(QVariant, arg)))
        //        {
        //            qDebug() << "Failed to invoke push";
        //        }
        if(!QMetaObject::invokeMethod(stackView, "pop",Qt::DirectConnection))
        {
            qDebug() << "Failed to invoke pop";
        }
        else{
            qDebug() << "pop invoked";
        }
    }
    else{
        qCritical()<<"stackView is null";

    }
}

QObject* AppPagesManager::getComponent(QString url,QObject* parent)
{
    QQmlComponent com(engine(),QUrl(url),parent);
    //QQmlComponent com(qmlEngine(this),QUrl(url),parent);
    return com.create(engine()->rootContext());
}

void AppPagesManager::loadMainWindow(QString qmlFileUrl)
{
    engine()->load(qmlFileUrl);
}

void AppPagesManager::clearCache()
{
    engine()->clearComponentCache();
}

void AppPagesManager::setWindow(QString qmlFileUrl,QString windowName)
{
    QQuickWindow* item=(QQuickWindow*)getComponent(qmlFileUrl,mainWindow()->parent());

    //    QQuickItem* c=m_MainWindow->contentItem();
    //    c=item->contentItem();

        m_MainWindow=item;
        item->deleteLater();

//    item=m_MainWindow;
//    m_MainWindow->deleteLater();

    //    QQuickItem* c=item->contentItem();
    //    qDebug()<<"new main.qml component.contentItem.childrens=>";
    //    writeChildrens(item);
    //    qDebug()<<"mainWindow() =>";
    //    writeChildrens(mainWindow());
    //    c->setParentItem(m_MainWindow->contentItem());

    //    QQuickItem* c=item->contentItem();
    //    qDebug()<<"new main.qml component.contentItem.childrens=>";
    //    writeChildrens(item);
    //    qDebug()<<"mainWindow() =>";
    //    writeChildrens(mainWindow());
    //    c->setParentItem(m_MainWindow->contentItem());
    //==============================================================
//    QQuickItem* parent=nullptr;

//    if(windowName.isEmpty()){
//        parent=(QQuickItem*)mainWindow();
//    }
//    else{
//        parent=find(windowName);
//    }
//    QQuickItem* item=(QQuickItem*)getComponent(qmlFileUrl);//item->isWindowType()

//    item->setParentItem(parent);
}

void AppPagesManager::setParentItem(QString qmlFileUrl,QQuickItem* item)
{
    QQuickItem *newCom =(QQuickItem*)getComponent(qmlFileUrl,item);
    newCom->setParentItem(item);
    qDebug()<<"New Component => "<<newCom;
    qDebug()<<"New Component.parent => "<<newCom->parentItem();
    //object->setParentItem(m_MainWindow->contentItem());
}

void AppPagesManager::setParentItem(QString qmlFileUrl,QString parentName)
{
    QQuickItem* parent=findAsItem(parentName);
    setParentItem(qmlFileUrl,parent);
}

void AppPagesManager::replaceItem(QString qmlFileUrl,QString name)
{
    QQuickItem* item=findAsItem(name);
    item =(QQuickItem*)getComponent(qmlFileUrl);
    // qDebug()<<object;
    //object->setParentItem(item);
    //object->setParentItem(m_MainWindow->contentItem());
}

void AppPagesManager::isSameEngine()
{
    if(qmlContext(this)!=nullptr)
    {
        if(qmlContext(this)->engine()!=nullptr)
        {
            qDebug()<<"engins are same"<<qmlContext(this)->engine();
        }
        else
        {
            qDebug()<<"qmlContext(this) => was null ";
        }
    }
    else
    {
        qDebug()<<"qmlContext(this) => was null ";
    }

    if(engine()==qmlEngine(this)){
        qDebug()<<"engins are same";
    }
    else{
        qDebug()<<"engins are not same";
    }
}
void AppPagesManager::loadQQmlApplicationEngine(QQmlApplicationEngine* obj)
{
    qCritical()<<"############# AppPagesManager::AppPagesManager ##############";
    qDebug()<<"QObjexroot ==>"<<obj;
    m_Engine=obj;
    connect(engine(),SIGNAL(objectCreated(QObject*,const QUrl)),this,SLOT(newObjectCreated(QObject*,const QUrl)));
    for (int i = 0; i < m_Engine->rootObjects().count(); ++i) {
        qDebug()<<i+1<<m_Engine->rootObjects().at(i);
    }
    //setMainWindow(qobject_cast<QQuickWindow *>(m_Engine->rootObjects().first()));
    qCritical()<<"############# AppPagesManager::AppPagesManager ##############";

}

bool AppPagesManager::grabWindow(QString path)
{
    qInfo()<<"is going to grabbed image and save in => "<<path;
    QImage img=grabWindow();
    if(img.isNull()){
        qWarning()<<"grabbed image faild";
        return false;
    }
    bool saved=img.save(path);
    if(!saved){
        qWarning()<<"grabbed image faild";
        return false;
    }
    qInfo()<<"grabbed image succeed";
    emit grabbedWindowFinished(true);
    return true;
}

QImage AppPagesManager::grabWindow()
{
    if(!mainWindow()){
        qCritical()<<"main window is null";
        return QImage();
    }
    qCritical()<<"*** is going to grab window ***";
    return mainWindow()->grabWindow();
}

void AppPagesManager::newObjectCreated(QObject *object, const QUrl &url)
{
    qDebug()<<"############ AppPagesManager::newObjectCreated #############";
    qDebug()<<"New Ojbect =>"<<object;
    qDebug()<<"New Ojbect Url =>"<<url;
    qDebug()<<"#####END####### AppPagesManager::newObjectCreated ##########";
    setMainWindow((QQuickWindow*)object);
}

void AppPagesManager::checkMenuItem(QObject* obj)
{
    qDebug()<<"obj.toString"<<obj;
    //    mainWindow()->findChild<QQuickMenu*>("mainMenu");

}

void AppPagesManager::findMe(QObject* obj)
{    
    qDebug()<<"############ AppPagesManager::findMe #############";
    qDebug()<<"obj=>"<<obj;
    QQuickItem* item=qobject_cast<QQuickItem*>(obj);

    foreach (QObject* i, mainWindow()->children()) {
        qDebug()<< i;
    }

    //    qDebug()<<"obj->metaObject()->className()=>"<<obj->metaObject()->className();

    //    mainWindow()->findChild<QQuickStackView>("mainStackView");
    qDebug()<<"#####END####### AppPagesManager::findMe ##########";
}

void AppPagesManager::writeChildrens(QString objectName)
{
    QQuickItem* item=findAsItem(objectName);
    writeChildrens(item);
}

void AppPagesManager::writeChildrens(QObject* item)
{
    if(!item){
        qCritical()<<"item is null";
        return;
    }
    if(!item->objectName().isEmpty()){
        qDebug()<<"item name=> "<<item->objectName();
    }
    for(int i=0;i<item->children().count();i++){
        qDebug()<<i+1<<" => "<<item->children().at(i);
    }
}

QQuickItem* AppPagesManager::findAsItem(QString name)
{
    return (QQuickItem*)find(name);
}

QQuickView* AppPagesManager::findAsView(QString name)
{
    return (QQuickView*)find(name);
}

QObject* AppPagesManager::find(QString name)
{
    if(mainWindow()==nullptr){
        qDebug()<<"mainWindow is null";
        return nullptr;
    }
    //QQuickItem* item= engine()->rootContext()->findChild<QQuickItem*>(name,Qt::FindChildrenRecursively);
    if(mainWindow()->objectName()==name){
        qDebug()<<"Item founed is mainWindow itseldf";
        qDebug() << "founded item=> mainWindow()-> " << mainWindow();
        qDebug() << "founded item=> mainWindow()->parent()-> " << mainWindow()->parent();
        qDebug() << "founded item=> mainWindow()->contentItem()-> " << mainWindow()->contentItem();
        return (QQuickItem*) mainWindow();
    }
    QObject* item=  mainWindow()->findChild<QQuickItem*>(name,Qt::FindChildrenRecursively);

    //QQuickItem* item=  mainWindow()->contentItem()->findChild<QQuickItem*>(name,Qt::FindChildrenRecursively);

    QObject *rootItem = mainWindow()->contentItem();
    qDebug() << "rootItem=> " << rootItem;

    if(item==nullptr){
        qDebug()<<"Item "<<name<<" Not Found";
        return nullptr;
    }
    else
    {
        qDebug() << "founded item-> " << item;
//        qDebug() << "founded item=> parentItem-> " << item->parentItem();
        qDebug() << "founded item=> parent-> " << item->parent();
        return item;
    }
    return nullptr;
    /*
    QObject* objd= engine()->findChild<QObject*>("drawer");
    if(objd==nullptr){
        qDebug()<<"ِDrawer Not Found";
    }
    else {
        qDebug()<<"Drawer Found =>"<<objd;
    }
    objd= engine()->findChild<QObject*>("mainMenuManulal");
    if(objd==nullptr){
        qDebug()<<"mainMenuManulal Not Found";
    }
    else {
        qDebug()<<"mainMenuManulal Found =>"<<objd;
    }
*/
}
//void AppPagesManager::writeAll(){
//    qDebug()<< mainWindow()->findChild<QObject*>("mainWindow");
//    for (int i = 0; i < mainWindow()->children().count(); ++i) {
//        qDebug()<<"object=>"<<mainWindow()->children().at(i);
//        if(i==0){
//            QObject* obj=mainWindow()->children().at(i);
//            for (int j = 0; j < obj->children().count(); ++j) {
//                qDebug()<<"----->objec=->"<<obj->children().at(j);
//                if(j==1){
//                    QObject* jobj=obj->children().at(j);
//                    for (int k = 0; k < jobj->children().count(); ++k) {
//                        qDebug()<<"=================obj=>"<<jobj->children().at(k);

//                    }
//                }
//            }
//        }
//    }

//}

void AppPagesManager::writeAll(){
    allItems={};
    fillListItem(mainWindow());
    qInfo()<<allItems.count();
    for (int i = 0; i < allItems.count(); ++i) {
        qCritical()<<"obj-> "<<allItems.at(i);
    }
}

void AppPagesManager::fillListItem(QObject* obj){
    if(obj==nullptr ||obj->children().count()<=0){
        return;
    }
    if(obj->objectName().isNull()||obj->objectName().isEmpty()){

    }
    else {
        allItems.append(obj);
    }
    for (int i = 0; i < obj->children().count(); ++i) {
        fillListItem(obj->children().at(i));
    }
}
