#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    LoadSettings();
    ui->LanguageSelector->setCurrentText(UiLanguage);
    ui->ThemeSlector->setCurrentText(UiTheme);
    ui->AmplitudeSlider->setValue(SoundAmplitude);
    ui->IsSplashScreen->setChecked(IsSplashScreen);
    ui->ShowAmbiguity->setChecked(IsShowAmbiguity);
    ui->IsMarkUnknownWords->setChecked(MarkUnknownWords);
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::on_listWidget_currentRowChanged(int currentRow)
{
    ui->preferences_tabs->setCurrentIndex(currentRow);
}
void Preferences::LoadSettings()
{
    QSettings settings("tachyons", "mltranslator");
    settings.beginGroup("preferences");
    UiLanguage=settings.value("uilanguage").toString();
    UiTheme=settings.value("theme").toString();
    IsShowAmbiguity=settings.value("ambiguity").toBool();
    IsSplashScreen=settings.value("splashscreen").toBool();
    SoundAmplitude=settings.value("soundamplitude").toInt();
    MarkUnknownWords=settings.value("unknownwords").toBool();
    settings.endGroup();
    qDebug()<<"Loaded";

}
void Preferences::StoreSettings()
{
    QSettings settings("tachyons", "mltranslator");
    settings.beginGroup("preferences");
    settings.setValue("uilanguage",UiLanguage);
    settings.setValue("theme",UiTheme);
    settings.setValue("ambiguity",IsShowAmbiguity);
    settings.setValue("splashscreen",IsSplashScreen);
    settings.setValue("soundamplitude",SoundAmplitude);
    settings.setValue("unknownwords",MarkUnknownWords);
    settings.endGroup();
    qDebug()<<"stored";
}

void Preferences::on_ThemeSlector_currentIndexChanged(const QString &arg1)
{
    UiTheme=arg1;
}

void Preferences::on_IsSplashScreen_toggled(bool checked)
{
    IsSplashScreen=checked;
}

void Preferences::on_LanguageSelector_currentIndexChanged(const QString &arg1)
{
    UiLanguage=arg1;
}

void Preferences::on_AmplitudeSlider_sliderMoved(int position)
{
    SoundAmplitude=position;
}

void Preferences::on_buttonBox_rejected()
{
    LoadSettings();
}

void Preferences::on_buttonBox_accepted()
{
    StoreSettings();
}

void Preferences::on_ShowAmbiguity_toggled(bool checked)
{
    IsShowAmbiguity=checked;
}

void Preferences::on_IsMarkUnknownWords_toggled(bool checked)
{
     MarkUnknownWords=checked;
}
