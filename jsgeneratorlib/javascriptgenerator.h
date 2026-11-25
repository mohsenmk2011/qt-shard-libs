#ifndef JAVASCRIPTGENERATOR_H
#define JAVASCRIPTGENERATOR_H

#include <QObject>

class JavaScriptGenerator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString isNull READ isNull CONSTANT)

    Q_PROPERTY(QString outerHTML READ outerHTML CONSTANT)
    Q_PROPERTY(QString innerHTML READ innerHTML CONSTANT)
public:
    explicit JavaScriptGenerator(QObject *parent = nullptr);

    QString outerHTML();
    QString innerHTML();
    QString isNull();

    Q_INVOKABLE QString convertToString();

    QString m_CurrentJavaScript;    

    Q_INVOKABLE QString click();
signals:

};

#endif // JAVASCRIPTGENERATOR_H
