#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    LoadSettings();
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
    QSettings settings("Tachyons Creations", "mltranslator");
   UiLanguage=settings.value("uilanguage").toString();
}
void Preferences::StoreSettings()
{
    QSettings settings("Tachyons Creations", "mltranslator");
    UiLanguage=settings.setValue("uilanguage","english");
}
