#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QSettings>
#include<QDebug>

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();
    void LoadSettings();
    void StoreSettings();
    QString UiLanguage;
    QString UiTheme;
    bool IsSplashScreen;
    bool IsShowAmbiguity;
    int SoundAmplitude;
    bool MarkUnknownWords;

    
private slots:
    void on_listWidget_currentRowChanged(int currentRow);

    void on_ThemeSlector_currentIndexChanged(const QString &arg1);

    void on_IsSplashScreen_toggled(bool checked);

    void on_LanguageSelector_currentIndexChanged(const QString &arg1);

    void on_AmplitudeSlider_sliderMoved(int position);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_ShowAmbiguity_toggled(bool checked);

    void on_IsMarkUnknownWords_toggled(bool checked);

private:
    Ui::Preferences *ui;
};

#endif // PREFERENCES_H
