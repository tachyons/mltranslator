#ifndef NEWWORD_H
#define NEWWORD_H

#include <QDialog>
#include <QDomDocument>
#include<QFile>
#include<iostream>
#include<QXmlStreamReader>
#include<QFileDialog>
#include<QMessageBox>
#include <QTextStream>
#include<QDebug>
#include <QProcess>
namespace Ui {
class NewWord;
}

class NewWord : public QDialog
{
    Q_OBJECT
    
public:
    QDomDocument doc;
    QFile file;
    explicit NewWord(QWidget *parent = 0);
    ~NewWord();
    QString dixfile;
    void format_dix();
    void update_preview();
private slots:
    void on_action_Open_triggered();
    void initilise();
    void loaddix();

    void on_parselection_currentTextChanged(const QString &arg1);

    void on_add_to_dict_clicked();

    void on_preview_textChanged();


    void on_pos_selector_currentIndexChanged(const QString &arg1);

private:
    QString current_pos;
    Ui::NewWord *ui;
};

#endif // TRANSTOOLW_H
