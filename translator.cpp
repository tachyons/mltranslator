#include "translator.h"
#include "ui_translator.h"

Translator::Translator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Translator)
{
    ui->setupUi(this);
    initialise_ui();
}

Translator::~Translator()
{
    delete ui;
}
void Translator::initialise_ui()
{
    ui->mainToolBar->addWidget(ui->langComboBox);
}

void Translator::on_action_New_triggered()
{

}

void Translator::on_action_About_triggered()
{
    About *dialog = new About();
    dialog->show();
}

void Translator::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                 tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

     if (!fileName.isEmpty()) {
         QFile file(fileName);
         if (!file.open(QIODevice::ReadOnly)) {
             QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
             return;
         }
         QTextStream in(&file);
         ui->source_text->setText(in.readAll());
         file.close();
     }
}

void Translator::on_action_Translate_triggered()
{
    ui->statusBar->showMessage("Translating ...");
    QProcess p;
    QProcess source;
    QProcess target;
    QString pair=get_lang();
    QString source_text=ui->source_text->toPlainText();
    //working directory
    QString workdir=QDir::homePath();
    source.setWorkingDirectory(workdir.append("/apertium-mal-eng"));
    target.setWorkingDirectory(workdir);
    //sync
    source.setStandardOutputProcess(&target);
    //run
    source.start(source_text.prepend("echo \""));
    source.waitForFinished(-1);
    QString command;
    command+="apertium -d ";
    command+= QDir::homePath();
    command+= "/apertium-mal-eng ";
    command+=pair;
    command+="\"";
    target.start(command);
    target.waitForFinished(-1);
    //get output
    QString p_stdout = target.readAllStandardOutput();
    QString p_stderr = target.readAllStandardError();
    ui->target_text->setText(p_stdout.append(p_stderr));
    //ui->target_text->setText("dchf");
    ui->statusBar->showMessage("Translated");
}

void Translator::on_action_PLay_triggered()
{
   QProcess play;
   QString command;
   command+="espeak ";
   command+="-v ml \"";
   command+=ui->target_text->toPlainText();
   command+=" \"";
   command=command.remove('#');
   command=command.remove('*');
   ui->statusBar->showMessage(command);
   play.start(command);
   play.waitForFinished(-1);
}
QString Translator::get_lang()
{
   if(ui->langComboBox->currentIndex()==0)
       return "mal-eng";
   else
       return "eng-mal";
}

void Translator::on_action_Exit_triggered()
{
    exit(0);
}

void Translator::on_action_Convert_file_triggered()
{
    ConvertFiles *dialog = new ConvertFiles();
    dialog->show();
}
