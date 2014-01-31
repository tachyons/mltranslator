#ifndef TRANSTOOLW_H
#define TRANSTOOLW_H

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
    void format_dix();
private slots:
    void on_action_Open_triggered();
    void initilise();

    void on_parselection_currentTextChanged(const QString &arg1);

    void on_add_to_dict_clicked();

private:
    Ui::NewWord *ui;
};

#endif // TRANSTOOLW_H
