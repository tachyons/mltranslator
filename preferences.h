#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class Preferences;
}

class Preferences : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();
    void LoadSettings();
    void StoreSettings();
    QString UiLanguage;
    
private slots:
    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::Preferences *ui;
};

#endif // PREFERENCES_H
