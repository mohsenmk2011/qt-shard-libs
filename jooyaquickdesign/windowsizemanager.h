#ifndef WINDOWSIZEMANAGER_H
#define WINDOWSIZEMANAGER_H

#include <QObject>
#include<QDebug>

class WindowSizeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tTest READ tTest WRITE setTTest NOTIFY tTestChanged)

    Q_PROPERTY(double rootWidth READ rootWidth WRITE setRootWidth)
    Q_PROPERTY(double rootHeight READ rootHeight WRITE setRootHeight)


    Q_PROPERTY(double width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged)

    Q_PROPERTY(int xsWidth READ xsWidth WRITE setXsWidth)
    Q_PROPERTY(int smWidth READ smWidth WRITE setSmWidth)
    Q_PROPERTY(int mdWidth READ mdWidth WRITE setMdWidth)
    Q_PROPERTY(int lgWidth READ lgWidth WRITE setLgWidth)
    Q_PROPERTY(int xlWidth READ xlWidth WRITE setXlWidth)

    Q_PROPERTY(int xsHeight READ xsHeight WRITE setXsHeight)
    Q_PROPERTY(int smHeight READ smHeight WRITE setSmHeight)
    Q_PROPERTY(int mdHeight READ mdHeight WRITE setMdHeight)
    Q_PROPERTY(int lgHeight READ lgHeight WRITE setLgHeight)
    Q_PROPERTY(int xlHeight READ xlHeight WRITE setXlHeight)

    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)

public:
    explicit WindowSizeManager(QObject *parent = nullptr);

    QString tTest();
    void setTTest(QString tt);
    double rootWidth();
    void setRootWidth(double w);

    double rootHeight();
    void setRootHeight(double h);

    double width();
    void setWidth(double w);

    double height();
    void setHeight(double h);

    int xsWidth();
    void setXsWidth(int v);

    int smWidth();
    void setSmWidth(int v);
    int mdWidth();
    void setMdWidth(int v);
    int lgWidth();
    void setLgWidth(int v);
    int xlWidth();
    void setXlWidth(int v);
    int xsHeight();
    void setXsHeight(int v);
    int smHeight();
    void setSmHeight(int v);
    int mdHeight();
    void setMdHeight(int v);
    int lgHeight();
    void setLgHeight(int v);
    int xlHeight();
    void setXlHeight(int v);

    int x();
    void setX(int v);

    int y();
    void setY(int v);

    void refreshX();
    void refreshY();

signals:
    void widthChanged();
    void heightChanged();
    void tTestChanged();
    void xChanged();
    void yChanged();
public slots:
private:
    double m_RootWidth;
    double m_RootHeight;

    double m_Width;
    double m_Height;

    int m_XsWidth;
    int m_SmWidth;
    int m_MdWidth;
    int m_LgWidth;
    int m_XlWidth;

    int m_XsHeight;
    int m_SmHeight;
    int m_MdHeight;
    int m_LgHeight;
    int m_XlHeight;

    int m_X;
    int m_Y;

    QString t;
    void refreshWidth();
    void refreshHeight();

    double calculateSize(int v, double rootSize);
};

#endif // WINDOWSIZEMANAGER_H
