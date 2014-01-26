#include "convertfiles.h"
#include "ui_convertfiles.h"

ConvertFiles::ConvertFiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertFiles)
{
    ui->setupUi(this);
    dircompleter =new QCompleter(this);
    dircompleter->setModel(new QDirModel(dircompleter));
    ui->outputfolder->setCompleter(dircompleter);
    ui->outputfolder->setText(QDir::homePath());
    pair=ui->pair_selector->currentText();
}

ConvertFiles::~ConvertFiles()
{
    delete ui;
}


void ConvertFiles::on_pushButton_clicked()
{
    InputFileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                 tr("All supported Documents (*.html *.odt *.tex *.pptx *.rtf);;Html (*.html);;Open Document (*.odt);;Rich Text(*.rtf);;Microsoft PowerPoint(*.pptx);;Latex(*.tex)"));
    ui->input_file_path->setText(InputFileName);
    QFileInfo file_info(InputFileName);
    format=file_info.completeSuffix();
    InputFileName=InputFileName.simplified();
    qDebug()<<InputFileName;
}


void ConvertFiles::on_browse_output_folder_clicked()
{
    OutputDirPath =QFileDialog::getExistingDirectory(this,tr("select directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->outputfolder->setText(OutputDirPath);
}

void ConvertFiles::on_convert_buton_clicked()
{
    QProcess fileconverter;
    QString apertuim_directory=QDir::homePath().append("/apertium-mal-eng");
    fileconverter.setWorkingDirectory(apertuim_directory);
    QString command;
    command+="apertium -d ";
    command+= QDir::homePath();
    command+= "/apertium-mal-eng ";
    command+="-u ";
    command+=pair;
    command+=" -f ";
    command+=format;
    command+=" \"";
    command+=InputFileName;
    command+="\" ";
    command+=OutputDirPath;
    command+="/output.";
    command+=format;
    qDebug()<<command;
    fileconverter.start(command);
    fileconverter.waitForFinished(-1);
}

void ConvertFiles::on_pair_selector_currentIndexChanged(const QString &arg1)
{
    pair=ui->pair_selector->currentText();
}
