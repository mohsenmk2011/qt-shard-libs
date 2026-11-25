#ifndef FONTSIZEMANAGER_H
#define FONTSIZEMANAGER_H

#include <QObject>

class FontSizeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float newWidth READ newWidth WRITE setNewWidth NOTIFY heightChanged)
    Q_PROPERTY(float fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(float newFontSize READ newFontSize WRITE setNewFontSize NOTIFY newFontSizeChanged)
public:
    explicit FontSizeManager(QObject *parent = nullptr);

    float width();
    void setWidth(float w);

    float newWidth();
    void setNewWidth(float nw);

    float fontSize();
    void setFontSize(float fs);

    float newFontSize();
    void setNewFontSize(float nfs);

signals:
    void widthChanged();
    void heightChanged();
    void fontSizeChanged();
    void newFontSizeChanged();

public slots:
private:
    float m_Width;
    float m_NewWidth;
    float m_FontSize;
    float m_NewFontSize;
    float m_FixNumber;
    void calculateNewFontSize();
    void calculateFixNumber();
};

#endif // FONTSIZEMANAGER_H
