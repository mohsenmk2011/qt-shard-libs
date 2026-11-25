#ifndef DOCUMENTELEMENT_H
#define DOCUMENTELEMENT_H

#include <QObject>
#include<javascriptgenerator.h>

class DocumentElement : public JavaScriptGenerator
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue)
public:
    explicit DocumentElement(QObject *parent = nullptr);

    QString value();
    void setValue(QString value);
signals:

};

#endif // DOCUMENTELEMENT_H
