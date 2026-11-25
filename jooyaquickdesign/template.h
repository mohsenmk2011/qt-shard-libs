#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QObject>

class Template : public QObject
{
    Q_OBJECT
public:
    explicit Template(QObject *parent = nullptr);
    enum class TemplateTypes :unsigned int
    {
        Background=0,
        Border=1,
        TopBottom=2,//حالتی مثل گل ختایی که یکی در بالا و یکی در پایین قرار می گیرد
    };
    Q_ENUMS(TemplateTypes)

signals:

public slots:
};

#endif // TEMPLATE_H
