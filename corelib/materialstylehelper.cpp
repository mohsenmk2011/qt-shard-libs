#include "materialstylehelper.h"

MaterialStyleHelper::MaterialStyleHelper(QObject *parent) : QObject(parent)
{
    setShowAnimation(true);
    setButtonVisibilityTimeout(27);
    connect(&m_Timer,&QTimer::timeout,this,&MaterialStyleHelper::onTimeOut);
    connect(&m_PageManager,&AppPagesManager::grabbedWindowFinished,this,&MaterialStyleHelper::onGrabbedWindow);
    connect(this,&MaterialStyleHelper::themeChanged,this,&MaterialStyleHelper::onThemeChanged);

    m_Secondary=MaterialColors::MaterialColorsEnum::Pink;
    m_Primary=MaterialColors::MaterialColorsEnum::Pink;
    m_Theme=MaterialThemes::MaterialThemesEnum::Light;
    m_IsDark=false;

    m_WindowCapturedImgPath=QUrl();
    ///below code should be after theme,primary and secondary color setting
    /// for button be unvisible at application startup
    m_ButtonVisible=false;
    refreshBackgroundColors();
}

QColor MaterialStyleHelper::primary50()
{
    return m_Primary50;
}

void MaterialStyleHelper::setPrimary50(QColor bcolor)
{
    m_Primary50=bcolor;
    emit primary50Changed();
}

QColor MaterialStyleHelper::primary100()
{
    return m_Primary100;
}

void MaterialStyleHelper::setPrimary100(QColor c)
{
    if(m_Primary100!=c){
        m_Primary100=c;
        emit primary100Changed();
    }
}

QColor MaterialStyleHelper::primary200()
{
    return m_Primary200;
}

void MaterialStyleHelper::setPrimary200(QColor c)
{
    if(m_Primary200!=c){
        m_Primary200=c;
        emit primary200Changed();
    }
}

QColor MaterialStyleHelper::primary300()
{
    return m_Primary300;
}

void MaterialStyleHelper::setPrimary300(QColor b)
{
    if(m_Primary300!=b){
        m_Primary300=b;
        emit primary300Changed();
    }
}

QColor MaterialStyleHelper::primaryTextColor()
{
    return m_PrimaryTextColor;
}

void MaterialStyleHelper::setPrimaryTextColor(QColor p)
{
    if(m_PrimaryTextColor!=p){
        m_PrimaryTextColor=p;
        emit primaryTextColorChanged();
    }
}

QColor MaterialStyleHelper::secondaryTextColor()
{
    return m_SecondaryTextColor;
}

void MaterialStyleHelper::setSecondaryTextColor(QColor a)
{
    if(m_SecondaryTextColor!=a){
        m_SecondaryTextColor=a;
        emit secondaryTextColorChanged();
    }
}

QColor MaterialStyleHelper::invertedPrimaryTextColor()
{
    return m_InvertedPrimaryTextColor;
}

void MaterialStyleHelper::setInvertedPrimaryTextColor(QColor c)
{
    if(m_InvertedPrimaryTextColor!=c){
        m_InvertedPrimaryTextColor=c;
        emit invertedPrimaryTextColorChanged();
    }
}

QColor MaterialStyleHelper::invertedAccetTextColor()
{
    return m_InvertedAccetTextColor;
}

void MaterialStyleHelper::setInvertedAccetTextColor(QColor c)
{
    if(m_InvertedAccetTextColor!=c){
        m_InvertedAccetTextColor=c;
        emit invertedAccetTextColorChanged();
    }
}
void MaterialStyleHelper::refreshBackgroundColors()
{
    switch (theme())
    {
    case MaterialThemes::MaterialThemesEnum::Light:
        if(useWhiteBackColor()){
            setPrimary50(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade100));
            setPrimary100(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade50));
            setPrimary200(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade100));
            setPrimary300(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade200));
        }
        else {
            setPrimary50(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade50));
            setPrimary100(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade100));
            setPrimary200(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade200));
            setPrimary300(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade300));
        }

        setSecondary50(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade50));
        setSecondary100(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade100));
        setSecondary200(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade200));
        setSecondary300(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade300));
        setSecondary400(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade400));
        setSecondary500(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade500));
        setSecondary600(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade600));
        setSecondary700(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade700));
        setSecondary800(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade800));
        setSecondary900(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade900));
        setTertiary50(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade50));
        setTertiary100(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade100));
        setTertiary200(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade200));
        setTertiary300(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade300));
        setTertiary400(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade400));
        setTertiary500(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade500));
        setTertiary600(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade600));
        setTertiary700(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade700));
        setTertiary800(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade800));
        setTertiary900(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade900));

        setIconColor(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade500));
        setPrimaryTextColor(m_Color.darkColor(primary()));
        setSecondaryTextColor(m_Color.darkColor(secondary()));
        setInvertedPrimaryTextColor(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade50));
        setInvertedAccetTextColor(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade50));
        break;
    case MaterialThemes::MaterialThemesEnum::Dark:
        if(useWhiteBackColor()){
            setPrimary50(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade900));
            setPrimary100(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade800));
            setPrimary200(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade700));
            setPrimary300(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade600));
        }
        else{
            setPrimary50(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade900));
            setPrimary100(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade800));
            setPrimary200(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade700));
            setPrimary300(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade600));
        }
        setSecondary50(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade900));
        setSecondary100(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade800));
        setSecondary200(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade700));
        setSecondary300(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade600));
        setSecondary400(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade500));
        setSecondary500(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade400));
        setSecondary600(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade300));
        setSecondary700(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade200));
        setSecondary800(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade100));
        setSecondary900(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade50));
        setTertiary50(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade900));
        setTertiary100(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade800));
        setTertiary200(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade700));
        setTertiary300(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade600));
        setTertiary400(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade500));
        setTertiary500(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade400));
        setTertiary600(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade300));
        setTertiary700(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade200));
        setTertiary800(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade100));
        setTertiary900(m_Color.getColor(tertiary(),MaterialShades::MaterialShadesEnum::Shade50));

        setIconColor(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade50));
        setPrimaryTextColor(m_Color.getColor(primary(),MaterialShades::MaterialShadesEnum::Shade50));
        setSecondaryTextColor(m_Color.getColor(secondary(),MaterialShades::MaterialShadesEnum::Shade50));
        setInvertedPrimaryTextColor(m_Color.darkColor(primary()));
        setInvertedAccetTextColor(m_Color.darkColor(secondary()));
        break;
    default:
        break;
    }
}

void MaterialStyleHelper::saveThemeInSettings()
{
    qInfo()<<"theme style changed=> save in settings";
    ApplicationSettings s;
    qInfo()<<"m_MaterialStyleHelper->toJson()=> "<<toJson();
    s.setTheme(toJson());
}

QUrl MaterialStyleHelper::windowCapturedImgPath()
{
    return m_WindowCapturedImgPath;
}

void MaterialStyleHelper::setWindowCapturedImgPath(QUrl p)
{
    qCritical()<<"new img path=> "<<p;
    qCritical()<<"old img path=> "<<m_WindowCapturedImgPath;
    if(m_WindowCapturedImgPath!=p){
        m_WindowCapturedImgPath=p;
        emit windowCapturedImgPathChanged();
    }
}

bool MaterialStyleHelper::isDark()
{
    return m_IsDark;
    //return theme()==MaterialThemes::MaterialThemesEnum::Dark;
}

void MaterialStyleHelper::setIsDark(bool d)
{
    if(m_IsDark!=d){
        m_IsDark=d;
        emit isDarkChanged();
    }
}

QColor MaterialStyleHelper::iconColor()
{
    return m_IconColor;
}

void MaterialStyleHelper::setIconColor(QColor c)
{
    if(m_IconColor!=c){
        m_IconColor=c;
        emit iconColorChanged();
    }
}

void MaterialStyleHelper::invertTheme()
{
    if(showAnimation()){
        qInfo()<<"showAnimation is enabled so => grabWindow";
        QString newpath=getGrabbedImgPath(theme()).path();
        QFileInfo file=QFileInfo(newpath);
        if(file.exists()){
            QFile::remove(newpath);
        }
        if(!m_PageManager.grabWindow(newpath)){
            qCritical()<<"grab window faild so invert them with no animation";
            setTheme(targetTheme());
        }
    }
    else {
        qInfo()<<"showAnimation is disabled so => invert them with no animation";
        setTheme(targetTheme());
    }
//#if defined(Q_OS_ANDROID)
//    if(showAnimation()){
//        qInfo()<<"=> grabWindow()=> "<<showAnimation();
//        m_PageManager.grabWindow(getGrabbedImgPath(theme()));
//    }
//    else {
//        setTheme(targetTheme());
//    }
//#else
//    setTheme(targetTheme());
//#endif

}

void MaterialStyleHelper::resetToDefault()
{
    ApplicationSettings s;
    loadFromJson(s.defaultTheme());
}

MaterialThemes::MaterialThemesEnum MaterialStyleHelper::theme()
{
    return m_Theme;
}

void MaterialStyleHelper::setTheme(MaterialThemes::MaterialThemesEnum t)
{
    if(m_Theme!=t){
        m_Theme=t;
        emit themeChanged();
        setIsDark(m_Theme==MaterialThemes::MaterialThemesEnum::Dark);
        refreshBackgroundColors();
        setButtonVisible(true);
        saveThemeInSettings();
    }
}

bool MaterialStyleHelper::showAnimation()
{
    return m_ShowAnimation;
}

void MaterialStyleHelper::setShowAnimation(bool s)
{
    if(m_ShowAnimation!=s){
        m_ShowAnimation=s;
        emit showAnimationChanged();
    }
}

QString MaterialStyleHelper::toJson()
{
    QJsonObject obj;
    obj.insert("theme",static_cast<int>(theme()));
    obj.insert("primary",static_cast<int>(primary()));
    obj.insert("secondary",static_cast<int>(secondary()));
    obj.insert("tertiary",static_cast<int>(tertiary()));
    obj.insert("useWhiteBackColor",static_cast<bool>(useWhiteBackColor()));

    QJsonDocument doc(obj);
    return QString(doc.toJson(QJsonDocument::JsonFormat::Compact));
}

void MaterialStyleHelper::loadFromJson(QString json)
{
    qInfo()<<"theme that was in settings =>"<<json;
    QJsonObject obj=QJsonDocument::fromJson(json.toUtf8()).object();
    setTheme(static_cast<MaterialThemes::MaterialThemesEnum>(obj.value("theme").toInt()));
    setUseWhiteBackColor(static_cast<bool>(obj.value("useWhiteBackColor").toBool()));
    setPrimary(static_cast<MaterialColors::MaterialColorsEnum>(obj.value("primary").toInt()));
    setSecondary(static_cast<MaterialColors::MaterialColorsEnum>(obj.value("secondary").toInt()));
    setTertiary(static_cast<MaterialColors::MaterialColorsEnum>(obj.value("tertiary").toInt()));
}

MaterialColors::MaterialColorsEnum MaterialStyleHelper::primary()
{
    return m_Primary;
}

void MaterialStyleHelper::setPrimary(MaterialColors::MaterialColorsEnum p)
{
    if(m_Primary!=p){
        m_Primary=p;
        emit primaryChanged();
        refreshBackgroundColors();
        saveThemeInSettings();
    }
}

MaterialColors::MaterialColorsEnum MaterialStyleHelper::secondary()
{
    return m_Secondary;
}

void MaterialStyleHelper::setSecondary(MaterialColors::MaterialColorsEnum a)
{
    if(m_Secondary!=a){
        m_Secondary=a;
        emit secondaryChanged();
        refreshBackgroundColors();
        saveThemeInSettings();
    }
}

int MaterialStyleHelper::buttonVisibilityTimeout()
{
    return m_ButtonVisibilityTimeout;
}

void MaterialStyleHelper::setButtonVisibilityTimeout(int t)
{
    if(m_ButtonVisibilityTimeout!=t){
        m_ButtonVisibilityTimeout=t;
        m_Timer.setInterval(t*1000);
        emit buttonVisibilityTimeoutChanged();
    }
}

bool MaterialStyleHelper::buttonVisible()
{
    return m_ButtonVisible;
}

void MaterialStyleHelper::setButtonVisible(bool v)
{
    if(m_ButtonVisible!=v){
        m_ButtonVisible=v;
        emit buttonVisibleChanged();
    }
    //    if(v){
    //        m_Timer.start();
    //    }
    //    else {
    //        m_Timer.stop();
    //    }
}

void MaterialStyleHelper::onGrabbedWindow(bool succeed)
{
    if(!succeed)
    {
        return;
    }
    setWindowCapturedImgPath(getGrabbedImgPath(theme()));
    emit windowCaptureSucceed();
    setTheme(targetTheme());
    qInfo()<<"img grabbed exists=> "<< QFile::exists(windowCapturedImgPath().path());
}

void MaterialStyleHelper::onThemeChanged()
{
//    qInfo()<<"MaterialStyleHelper::onThemeChanged()";
//    setIsDark(theme()==MaterialThemes::MaterialThemesEnum::Dark);
//    refreshBackgroundColors();
//    QString t=getGrabbedImgPath(theme());
//    qInfo()<<"t=>"<<t;
//    setWindowCapturedImgPath(t);
//    qInfo()<<" end of MaterialStyleHelper::onThemeChanged()";
//    setButtonVisible(true);saveThemeInSettings
}

void MaterialStyleHelper::onTimeOut()
{
    setButtonVisible(false);
}

MaterialThemes::MaterialThemesEnum MaterialStyleHelper::targetTheme()
{
    switch (theme())
    {
        case MaterialThemes::MaterialThemesEnum::Dark:return MaterialThemes::MaterialThemesEnum::Light;
        case MaterialThemes::MaterialThemesEnum::Light:return MaterialThemes::MaterialThemesEnum::Dark;
        default:return MaterialThemes::MaterialThemesEnum::Light;
    }
}

QUrl MaterialStyleHelper::getGrabbedImgPath(MaterialThemes::MaterialThemesEnum theme)
{
    QString path="";
    ApplicationPath ap;
    QString folderPath=ap.imagesFolderPath();
    qDebug()<<"current theme => "<<theme;
    ap.makeSurePathExsists(folderPath);
    if(theme==MaterialThemes::MaterialThemesEnum::Dark){
        path= folderPath+"dark.png";
    }
    else if(theme==MaterialThemes::MaterialThemesEnum::Light){
        path= folderPath+"light.png";
    }
    qDebug()<<"capture will save in =>"<<path;
    return QUrl::fromLocalFile(path);
}

ColorListModel* MaterialStyleHelper::colors()
{
    return &m_Colors;
}

QColor MaterialStyleHelper::secondary50()
{
    return m_Secondary50;
}

void MaterialStyleHelper::setSecondary50(QColor bcolor)
{
    if(m_Secondary50!=bcolor){
        m_Secondary50=bcolor;
        emit secondary50Changed();
    }
}

QColor MaterialStyleHelper::secondary100()
{
    return m_Secondary100;
}

void MaterialStyleHelper::setSecondary100(QColor c)
{
    if(m_Secondary100!=c){
        m_Secondary100=c;
        emit secondary100Changed();
    }
}

QColor MaterialStyleHelper::secondary200()
{
    return m_Secondary200;
}

void MaterialStyleHelper::setSecondary200(QColor c)
{
    if(m_Secondary200!=c){
        m_Secondary200=c;
        emit secondary200Changed();
    }
}

QColor MaterialStyleHelper::secondary300()
{
    return m_Secondary300;
}

void MaterialStyleHelper::setSecondary300(QColor b)
{
    if(m_Secondary300!=b){
        m_Secondary300=b;
        emit secondary300Changed();
    }
}

QColor MaterialStyleHelper::secondary400() const
{
    return m_secondary400;
}

void MaterialStyleHelper::setSecondary400(const QColor &newSecondary400)
{
    if (m_secondary400 == newSecondary400)
        return;
    m_secondary400 = newSecondary400;
    emit secondary400Changed();
}

QColor MaterialStyleHelper::secondary500() const
{
    return m_secondary500;
}

void MaterialStyleHelper::setSecondary500(const QColor &newSecondary500)
{
    if (m_secondary500 == newSecondary500)
        return;
    m_secondary500 = newSecondary500;
    emit secondary500Changed();
}

QColor MaterialStyleHelper::secondary600() const
{
    return m_secondary600;
}

void MaterialStyleHelper::setSecondary600(const QColor &newSecondary600)
{
    if (m_secondary600 == newSecondary600)
        return;
    m_secondary600 = newSecondary600;
    emit secondary600Changed();
}

QColor MaterialStyleHelper::secondary700() const
{
    return m_secondary700;
}

void MaterialStyleHelper::setSecondary700(const QColor &newSecondary700)
{
    if (m_secondary700 == newSecondary700)
        return;
    m_secondary700 = newSecondary700;
    emit secondary700Changed();
}

QColor MaterialStyleHelper::secondary800() const
{
    return m_secondary800;
}

void MaterialStyleHelper::setSecondary800(const QColor &newSecondary800)
{
    if (m_secondary800 == newSecondary800)
        return;
    m_secondary800 = newSecondary800;
    emit secondary800Changed();
}

QColor MaterialStyleHelper::secondary900() const
{
    return m_secondary900;
}

void MaterialStyleHelper::setSecondary900(const QColor &newSecondary900)
{
    if (m_secondary900 == newSecondary900)
        return;
    m_secondary900 = newSecondary900;
    emit secondary900Changed();
}

bool MaterialStyleHelper::useWhiteBackColor() const
{
    return m_useWhiteBackColor;
}

void MaterialStyleHelper::setUseWhiteBackColor(bool newUseWhiteBackColor)
{
    if (m_useWhiteBackColor == newUseWhiteBackColor)
        return;
    m_useWhiteBackColor = newUseWhiteBackColor;
    emit useWhiteBackColorChanged();
    refreshBackgroundColors();
    saveThemeInSettings();
}

MaterialColors::MaterialColorsEnum MaterialStyleHelper::tertiary() const
{
    return m_tertiary;
}

void MaterialStyleHelper::setTertiary(const MaterialColors::MaterialColorsEnum &newTertiary)
{
    if (m_tertiary == newTertiary)
        return;
    m_tertiary = newTertiary;
    emit tertiaryChanged();
    refreshBackgroundColors();
    saveThemeInSettings();
}

QColor MaterialStyleHelper::tertiary50() const
{
    return m_tertiary50;
}

void MaterialStyleHelper::setTertiary50(const QColor &newTertiary50)
{
    if (m_tertiary50 == newTertiary50)
        return;
    m_tertiary50 = newTertiary50;
    emit tertiary50Changed();
}

QColor MaterialStyleHelper::tertiary100() const
{
    return m_tertiary100;
}

void MaterialStyleHelper::setTertiary100(const QColor &newTertiary100)
{
    if (m_tertiary100 == newTertiary100)
        return;
    m_tertiary100 = newTertiary100;
    emit tertiary100Changed();
}

QColor MaterialStyleHelper::tertiary200() const
{
    return m_tertiary200;
}

void MaterialStyleHelper::setTertiary200(const QColor &newTertiary200)
{
    if (m_tertiary200 == newTertiary200)
        return;
    m_tertiary200 = newTertiary200;
    emit tertiary200Changed();
}

QColor MaterialStyleHelper::tertiary300() const
{
    return m_tertiary300;
}

void MaterialStyleHelper::setTertiary300(const QColor &newTertiary300)
{
    if (m_tertiary300 == newTertiary300)
        return;
    m_tertiary300 = newTertiary300;
    emit tertiary300Changed();
}

QColor MaterialStyleHelper::tertiary400() const
{
    return m_tertiary400;
}

void MaterialStyleHelper::setTertiary400(const QColor &newTertiary400)
{
    if (m_tertiary400 == newTertiary400)
        return;
    m_tertiary400 = newTertiary400;
    emit tertiary400Changed();
}

QColor MaterialStyleHelper::tertiary500() const
{
    return m_tertiary500;
}

void MaterialStyleHelper::setTertiary500(const QColor &newTertiary500)
{
    if (m_tertiary500 == newTertiary500)
        return;
    m_tertiary500 = newTertiary500;
    emit tertiary500Changed();
}

QColor MaterialStyleHelper::tertiary600() const
{
    return m_tertiary600;
}

void MaterialStyleHelper::setTertiary600(const QColor &newTertiary600)
{
    if (m_tertiary600 == newTertiary600)
        return;
    m_tertiary600 = newTertiary600;
    emit tertiary600Changed();
}

QColor MaterialStyleHelper::tertiary700() const
{
    return m_tertiary700;
}

void MaterialStyleHelper::setTertiary700(const QColor &newTertiary700)
{
    if (m_tertiary700 == newTertiary700)
        return;
    m_tertiary700 = newTertiary700;
    emit tertiary700Changed();
}

QColor MaterialStyleHelper::tertiary800() const
{
    return m_tertiary800;
}

void MaterialStyleHelper::setTertiary800(const QColor &newTertiary800)
{
    if (m_tertiary800 == newTertiary800)
        return;
    m_tertiary800 = newTertiary800;
    emit tertiary800Changed();
}

QColor MaterialStyleHelper::tertiary900() const
{
    return m_tertiary900;
}

void MaterialStyleHelper::setTertiary900(const QColor &newTertiary900)
{
    if (m_tertiary900 == newTertiary900)
        return;
    m_tertiary900 = newTertiary900;
    emit tertiary900Changed();
}
