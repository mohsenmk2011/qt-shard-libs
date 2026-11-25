#ifndef MATERIALSTYLEHELPER_H
#define MATERIALSTYLEHELPER_H

#include <QObject>
#include<applicationpath.h>
#include<apppagesmanager.h>
#include <QtGui/qcolor.h>
#include<materialcolors.h>
#include<materialshades.h>
#include<materialthemes.h>
#include<colorlistmodel.h>
#include<materialcolor.h>
#include<QtQml>
#include<qjsondocument.h>
#include<QTimer>
#include<applicationsettings.h>

class MaterialStyleHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl windowCapturedImgPath READ windowCapturedImgPath WRITE setWindowCapturedImgPath NOTIFY windowCapturedImgPathChanged)
    Q_PROPERTY(MaterialThemes::MaterialThemesEnum theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum primary READ primary WRITE setPrimary NOTIFY primaryChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum secondary READ secondary WRITE setSecondary NOTIFY secondaryChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum tertiary READ tertiary WRITE setTertiary NOTIFY tertiaryChanged)
    Q_PROPERTY(bool useWhiteBackColor READ useWhiteBackColor WRITE setUseWhiteBackColor NOTIFY useWhiteBackColorChanged FINAL)

    Q_PROPERTY(bool isDark READ isDark WRITE setIsDark NOTIFY isDarkChanged)
    Q_PROPERTY(bool showAnimation READ showAnimation WRITE setShowAnimation NOTIFY showAnimationChanged)

    Q_PROPERTY(QColor primary50 READ primary50 WRITE setPrimary50 NOTIFY primary50Changed)
    Q_PROPERTY(QColor primary100 READ primary100 WRITE setPrimary100 NOTIFY primary100Changed)
    Q_PROPERTY(QColor primary200 READ primary200 WRITE setPrimary200 NOTIFY primary200Changed)
    Q_PROPERTY(QColor primary300 READ primary300 WRITE setPrimary300 NOTIFY primary300Changed)
    Q_PROPERTY(QColor secondary50 READ secondary50 WRITE setSecondary50 NOTIFY secondary50Changed)
    Q_PROPERTY(QColor secondary100 READ secondary100 WRITE setSecondary100 NOTIFY secondary100Changed)
    Q_PROPERTY(QColor secondary200 READ secondary200 WRITE setSecondary200 NOTIFY secondary200Changed)
    Q_PROPERTY(QColor secondary300 READ secondary300 WRITE setSecondary300 NOTIFY secondary300Changed)
    Q_PROPERTY(QColor secondary400 READ secondary400 WRITE setSecondary400 NOTIFY secondary400Changed FINAL)
    Q_PROPERTY(QColor secondary500 READ secondary500 WRITE setSecondary500 NOTIFY secondary500Changed FINAL)
    Q_PROPERTY(QColor secondary600 READ secondary600 WRITE setSecondary600 NOTIFY secondary600Changed FINAL)
    Q_PROPERTY(QColor secondary700 READ secondary700 WRITE setSecondary700 NOTIFY secondary700Changed FINAL)
    Q_PROPERTY(QColor secondary800 READ secondary800 WRITE setSecondary800 NOTIFY secondary800Changed FINAL)
    Q_PROPERTY(QColor secondary900 READ secondary900 WRITE setSecondary900 NOTIFY secondary900Changed FINAL)
    Q_PROPERTY(QColor tertiary50 READ tertiary50 WRITE setTertiary50 NOTIFY tertiary50Changed)
    Q_PROPERTY(QColor tertiary100 READ tertiary100 WRITE setTertiary100 NOTIFY tertiary100Changed)
    Q_PROPERTY(QColor tertiary200 READ tertiary200 WRITE setTertiary200 NOTIFY tertiary200Changed)
    Q_PROPERTY(QColor tertiary300 READ tertiary300 WRITE setTertiary300 NOTIFY tertiary300Changed)
    Q_PROPERTY(QColor tertiary400 READ tertiary400 WRITE setTertiary400 NOTIFY tertiary400Changed FINAL)
    Q_PROPERTY(QColor tertiary500 READ tertiary500 WRITE setTertiary500 NOTIFY tertiary500Changed FINAL)
    Q_PROPERTY(QColor tertiary600 READ tertiary600 WRITE setTertiary600 NOTIFY tertiary600Changed FINAL)
    Q_PROPERTY(QColor tertiary700 READ tertiary700 WRITE setTertiary700 NOTIFY tertiary700Changed FINAL)
    Q_PROPERTY(QColor tertiary800 READ tertiary800 WRITE setTertiary800 NOTIFY tertiary800Changed FINAL)
    Q_PROPERTY(QColor tertiary900 READ tertiary900 WRITE setTertiary900 NOTIFY tertiary900Changed FINAL)


    Q_PROPERTY(QColor primaryTextColor READ primaryTextColor WRITE setPrimaryTextColor NOTIFY primaryTextColorChanged)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor WRITE setSecondaryTextColor NOTIFY secondaryTextColorChanged)

    Q_PROPERTY(QColor invertedPrimaryTextColor READ invertedPrimaryTextColor WRITE setInvertedPrimaryTextColor NOTIFY invertedPrimaryTextColorChanged)
    Q_PROPERTY(QColor invertedAccetTextColor READ invertedAccetTextColor WRITE setInvertedAccetTextColor NOTIFY invertedAccetTextColorChanged)

    Q_PROPERTY(QColor iconColor READ iconColor WRITE setIconColor NOTIFY iconColorChanged)
    Q_PROPERTY(ColorListModel* colors READ colors CONSTANT)
    Q_PROPERTY(int buttonVisibilityTimeout READ buttonVisibilityTimeout WRITE setButtonVisibilityTimeout NOTIFY buttonVisibilityTimeoutChanged)
    Q_PROPERTY(bool buttonVisible READ buttonVisible WRITE setButtonVisible NOTIFY buttonVisibleChanged)
    QML_ANONYMOUS
public:
    explicit MaterialStyleHelper(QObject *parent = nullptr);

    ColorListModel *colors();

    QColor secondary50();
    void setSecondary50(QColor bcolor);
    QColor secondary100();
    void setSecondary100(QColor c);
    QColor secondary200();
    void setSecondary200(QColor c);
    QColor secondary300();
    void setSecondary300(QColor b);

    QColor primary50();
    void setPrimary50(QColor bcolor);
    QColor primary100();
    void setPrimary100(QColor c);
    QColor primary200();
    void setPrimary200(QColor c);
    QColor primary300();
    void setPrimary300(QColor b);

    QColor primaryTextColor();
    void setPrimaryTextColor(QColor p);
    QColor secondaryTextColor();
    void setSecondaryTextColor(QColor a);

    QColor invertedPrimaryTextColor();
    void setInvertedPrimaryTextColor(QColor c);
    QColor invertedAccetTextColor();
    void setInvertedAccetTextColor( QColor c);

    QUrl windowCapturedImgPath();
    void setWindowCapturedImgPath(QUrl p);

    bool isDark();
    void setIsDark(bool d);

    QColor iconColor();
    void setIconColor(QColor c);

    Q_INVOKABLE void invertTheme();

    Q_INVOKABLE void resetToDefault();

    MaterialThemes::MaterialThemesEnum theme();
    void setTheme(MaterialThemes::MaterialThemesEnum t);

    bool showAnimation();
    void setShowAnimation(bool s);

    QString toJson();
    void loadFromJson(QString json);

    MaterialColors::MaterialColorsEnum primary();
    void setPrimary(MaterialColors::MaterialColorsEnum p);
    MaterialColors::MaterialColorsEnum secondary();
    void setSecondary(MaterialColors::MaterialColorsEnum a);

    ///How manay seconds the button of changing theme will be visible in toolbar
    int buttonVisibilityTimeout();
    void setButtonVisibilityTimeout(int t);

    bool buttonVisible();
    void setButtonVisible(bool v);
    QColor secondary400() const;
    void setSecondary400(const QColor &newSecondary400);

    QColor secondary500() const;
    void setSecondary500(const QColor &newSecondary500);

    QColor secondary600() const;
    void setSecondary600(const QColor &newSecondary600);

    QColor secondary700() const;
    void setSecondary700(const QColor &newSecondary700);

    QColor secondary800() const;
    void setSecondary800(const QColor &newSecondary800);

    QColor secondary900() const;
    void setSecondary900(const QColor &newSecondary900);

    bool useWhiteBackColor() const;
    void setUseWhiteBackColor(bool newUseWhiteBackColor);

    MaterialColors::MaterialColorsEnum tertiary() const;
    void setTertiary(const MaterialColors::MaterialColorsEnum &newTertiary);

    QColor tertiary50() const;
    void setTertiary50(const QColor &newTertiary50);

    QColor tertiary100() const;
    void setTertiary100(const QColor &newTertiary100);

    QColor tertiary200() const;
    void setTertiary200(const QColor &newTertiary200);

    QColor tertiary300() const;
    void setTertiary300(const QColor &newTertiary300);

    QColor tertiary400() const;
    void setTertiary400(const QColor &newTertiary400);

    QColor tertiary500() const;
    void setTertiary500(const QColor &newTertiary500);

    QColor tertiary600() const;
    void setTertiary600(const QColor &newTertiary600);

    QColor tertiary700() const;
    void setTertiary700(const QColor &newTertiary700);

    QColor tertiary800() const;
    void setTertiary800(const QColor &newTertiary800);

    QColor tertiary900() const;
    void setTertiary900(const QColor &newTertiary900);

signals:
    void windowCapturedImgPathChanged();
    void iconColorChanged();
    void themeChanged();
    void showAnimationChanged();
    void isDarkChanged();
    void windowCaptureSucceed();

    void secondary50Changed();
    void secondary100Changed();
    void secondary200Changed();
    void secondary300Changed();

    void primary50Changed();
    void primary100Changed();
    void primary200Changed();
    void primary300Changed();

    void primaryTextColorChanged();
    void secondaryTextColorChanged();
    void invertedPrimaryTextColorChanged();
    void invertedAccetTextColorChanged();

    void primaryChanged();
    void secondaryChanged();
    void shadeChanged();
    void buttonVisibilityTimeoutChanged();
    void buttonVisibleChanged();
    void secondary400Changed();

    void secondary500Changed();

    void secondary600Changed();

    void secondary700Changed();

    void secondary800Changed();

    void secondary900Changed();

    void useWhiteBackColorChanged();

    void tertiaryChanged();

    void tertiary50Changed();

    void tertiary100Changed();

    void tertiary200Changed();

    void tertiary300Changed();

    void tertiary400Changed();

    void tertiary500Changed();

    void tertiary600Changed();

    void tertiary700Changed();

    void tertiary800Changed();

    void tertiary900Changed();

private slots:
    void onGrabbedWindow(bool succeed);
    void onThemeChanged();
    void onTimeOut();
private:
    bool m_IsDark;
    int m_ButtonVisibilityTimeout;
    bool m_ButtonVisible;
    QColor m_Secondary50;
    QColor m_Secondary100;
    QColor m_Secondary200;
    QColor m_Secondary300;

    QColor m_Primary50;
    QColor m_Primary100;
    QColor m_Primary200;
    QColor m_Primary300;

    QColor m_PrimaryTextColor;
    QColor m_SecondaryTextColor;
    QColor m_InvertedPrimaryTextColor;
    QColor m_InvertedAccetTextColor;
    QColor m_IconColor;
    MaterialThemes::MaterialThemesEnum targetTheme();
    QUrl getGrabbedImgPath(MaterialThemes::MaterialThemesEnum targetTheme);
    QUrl m_WindowCapturedImgPath;
    MaterialThemes::MaterialThemesEnum m_Theme;
    MaterialColors::MaterialColorsEnum m_Primary;
    MaterialColors::MaterialColorsEnum m_Secondary;
    AppPagesManager m_PageManager;
    bool m_ShowAnimation;
    ColorListModel m_Colors;
    MaterialColor m_Color;
    QTimer m_Timer;
    void refreshBackgroundColors();
    void saveThemeInSettings();
    QColor m_secondary400;
    QColor m_secondary500;
    QColor m_secondary600;
    QColor m_secondary700;
    QColor m_secondary800;
    QColor m_secondary900;
    bool m_useWhiteBackColor;
    MaterialColors::MaterialColorsEnum m_tertiary;
    QColor m_tertiary50;
    QColor m_tertiary100;
    QColor m_tertiary200;
    QColor m_tertiary300;
    QColor m_tertiary400;
    QColor m_tertiary500;
    QColor m_tertiary600;
    QColor m_tertiary700;
    QColor m_tertiary800;
    QColor m_tertiary900;
};
#endif // MATERIALSTYLEHELPER_H
