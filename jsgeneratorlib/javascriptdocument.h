#ifndef JAVASCRIPTDOCUMENT_H
#define JAVASCRIPTDOCUMENT_H

#include <QObject>
#include<javascriptgenerator.h>
#include<documentelement.h>

class JavaScriptDocument : public JavaScriptGenerator
{
    Q_OBJECT
    Q_PROPERTY(DocumentElement* documentElement READ documentElement CONSTANT)
public:
    explicit JavaScriptDocument(QObject *parent = nullptr);

    DocumentElement* documentElement();

    Q_INVOKABLE DocumentElement *getElementById(QString id);
    Q_INVOKABLE DocumentElement *getElementsByTagName(QString name);
    Q_INVOKABLE DocumentElement *getElementsByClassName(QString name);

    Q_INVOKABLE void appendScript(QString script);

    QString script();
signals:
private:
    QList<QString> m_Scripts;
};

#endif // JAVASCRIPTDOCUMENT_H
