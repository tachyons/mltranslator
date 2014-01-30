#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QMainWindow>
#include <QComboBox>
#include "about.h"
#include "convertfiles.h"
#include "preferences.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include <iostream>
#include <QSettings>

namespace Ui {
class Translator;
}

class Translator : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Translator(QWidget *parent = 0);
    ~Translator();

    QString UiLanguage;
    QString UiTheme;
    bool IsSplashScreen;
    bool IsShowAmbiguity;
    int SoundAmplitude;
    bool MarkUnknownWords;
    
private slots:
    void on_action_New_triggered();

    void on_action_About_triggered();

    void on_action_Open_triggered();

    void on_action_Translate_triggered();

    void on_action_PLay_triggered();
    QString get_lang();

    void on_action_Exit_triggered();

    void on_action_Convert_file_triggered();

    void on_action_Preferences_triggered();
    void LoadSettings();

private:
    Ui::Translator *ui;
    void initialise_ui();
};

#endif // TRANSLATOR_H
