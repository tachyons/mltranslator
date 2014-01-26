#ifndef CONVERTFILES_H
#define CONVERTFILES_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QCompleter>
#include <QDirModel>
#include <QProcess>
#include <QFileInfo>
#include <QDebug>

namespace Ui {
class ConvertFiles;
}

class ConvertFiles : public QDialog
{
    Q_OBJECT

public:
    explicit ConvertFiles(QWidget *parent = 0);
    ~ConvertFiles();

private slots:
    void on_pushButton_clicked();

    

    void on_browse_output_folder_clicked();
    void on_convert_buton_clicked();

    void on_pair_selector_currentIndexChanged(const QString &arg1);

private:
    Ui::ConvertFiles *ui;
    QCompleter *dircompleter;
    QString  InputFileName;
    QString OutputDirPath;
    QString pair;
    QString format;
};

#endif // CONVERTFILES_H
