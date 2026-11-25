#ifndef JOOYAFONT_H
#define JOOYAFONT_H

#include <QObject>
#include <QFontDatabase>
#include <QGuiApplication>

class JooyaFont : public QObject
{
    Q_OBJECT
public:
    explicit JooyaFont(QObject *parent = nullptr);

    void installDefaultFont(QString fontPath);
signals:

public slots:
};

#endif // JOOYAFONT_H
