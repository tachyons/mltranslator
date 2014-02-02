#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
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
    ui->PitchSlider->setValue(SoundPitch);
    ui->WordGapSlider->setValue(SoundGap);
    ui->SpeedSlider->setValue(SoundSpeed);
    ui->gender_selector->setCurrentIndex(SoundGender);
    //connect(this,SIGNAL(destroyed()),parent,SLOT(LoadSettings()));
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
    SoundPitch=settings.value("soundpitch").toInt();
    SoundSpeed=settings.value("soundspeed").toInt();
    SoundGender=settings.value("soundgender").toInt();
    SoundGap=settings.value("soundgap").toInt();
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
    settings.setValue("soundpitch",SoundPitch);
    settings.setValue("soundspeed",SoundSpeed);
    settings.setValue("soundgender",SoundGender);
    settings.setValue("soundgap",SoundGap);
    settings.endGroup();
    qDebug()<<"stored from preferences";
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
    QTranslator translator;
    if(arg1=="Malayalam")
    {
        qDebug()<<"malayalam";
        translator.load("mltranslator_mal");
    }
    else if(arg1=="English")
    {
        qDebug()<<"english";
        translator.load("mltranslator_eng");
    }
    //qApp->removeTranslator()
    qApp->installTranslator(&translator);
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

void Preferences::on_WordGapSlider_sliderMoved(int position)
{
    SoundGap=position;
}

void Preferences::on_PitchSlider_sliderMoved(int position)
{
    SoundPitch=position;
}

void Preferences::on_SpeedSlider_sliderMoved(int position)
{
    SoundSpeed=position;
}

void Preferences::on_ThemeSlector_currentTextChanged(const QString &arg1)
{
    qApp->setStyleSheet(arg1);
}


void Preferences::on_gender_selector_currentIndexChanged(int index)
{
    SoundGender=index;
}
