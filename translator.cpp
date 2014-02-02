#include "translator.h"
#include "ui_translator.h"

Translator::Translator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Translator)
{
    ui->setupUi(this);
    initialise_ui();
    QSettings settings("Tachyons Creations", "mltranslator");
    LoadSettings();


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
    ui->source_text->clear();
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
    command+="apertium";
    qDebug()<<MarkUnknownWords;
    if(MarkUnknownWords==false)
    {
        command+=" -u";
    }
    command+=" -d ";
    command+= QDir::homePath();
    command+= "/apertium-mal-eng ";
    command+=pair;
    command+="\"";
    qDebug()<<command;
    target.start(command);
    target.waitForFinished(-1);
    //get output
    QString p_stdout = target.readAllStandardOutput();
    QString p_stderr = target.readAllStandardError();
    QString target_text;
    target_text=p_stdout.append(p_stderr);
    //target_text.remove('*');
    //target_text.remove('#');

    ui->target_text->setText(target_text);
    //ui->target_text->setText("dchf");
    ui->statusBar->showMessage("Translated");
}

void Translator::on_action_PLay_triggered()
{
   QProcess play;
   QString command;
   command+="espeak ";
   command+="-v ml";
   if(SoundGender==0)
   {
       command+="+12";
   }
   command+=" ";
   command+="-a ";
   command+=QString::number(SoundAmplitude);
   command+=" ";
   command+="-g ";
   command+=QString::number(SoundGap);
   command+=" ";
   command+="-p ";
   command+=QString::number(SoundPitch);
   command+=" ";
   command+="-p ";
   command+=QString::number(SoundSpeed);
   command+=" \"";
   command+=ui->target_text->toPlainText();
   command+=" \"";
   command=command.remove('#');
   command=command.remove('*');
   //ui->statusBar->showMessage("playing");
   ui->statusBar->showMessage(command);
   play.start(command);
   play.waitForFinished(-1);
   ui->statusBar->showMessage("ready");
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

void Translator::on_action_Preferences_triggered()
{
    Preferences *dialog = new Preferences();
    //connect(dialog,SIGNAL(destroyed(QObject* )),this,SLOT(LoadSettings()));
    dialog->exec();
    LoadSettings();
    //retranslateUi();
    //dialog->connect(dialog,SIGNAL(destroyed(QObject*)),this,SLOT(LoadSettings()));
}
void Translator::LoadSettings()
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
    qDebug()<<"Loaded to translator";
}

void Translator::on_actionMal_eng_triggered()
{
    QProcess *mal_eng=new QProcess;
    QString workdir=QDir::homePath();
    mal_eng->setWorkingDirectory(workdir.append("/apertium-mal-eng"));
    mal_eng->setWorkingDirectory(workdir);
    //mal_eng.start("gedit");
    QStringList arguments;
    arguments << "apertium-mal-eng.mal-eng.t1x"<<"apertium-mal-eng.mal-eng.t2x"<<"apertium-mal-eng.mal-eng.t3x";
    mal_eng->start("gedit",arguments);
    mal_eng->waitForStarted(-1);
}

void Translator::on_actionEng_mal_triggered()
{
    QProcess eng_mal;
    QString workdir=QDir::homePath();
    eng_mal.setWorkingDirectory(workdir.append("/apertium-mal-eng"));
    eng_mal.setWorkingDirectory(workdir);
    //mal_eng.start("gedit");
    QStringList arguments;
    arguments << "apertium-mal-eng.mal-eng.t1x"<<"apertium-mal-eng.mal-eng.t2x"<<"apertium-mal-eng.mal-eng.t3x";
    eng_mal.start("gedit",arguments);
    eng_mal.waitForStarted(-1);
}

void Translator::on_action_Compile_triggered()
{
    QProcess compile;
    QString workdir=QDir::homePath();
    workdir=workdir.append("/apertium-mal-eng");
    compile.setWorkingDirectory(workdir);
    compile.start("make");
    compile.waitForFinished(-1);
}

void Translator::on_action_Add_New_Word_triggered()
{
    NewWord *new_word=new NewWord;
    new_word->exec();

}

void Translator::on_action_Add_paradigm_triggered()
{
    newparadigm *paradigm=new newparadigm;
    paradigm->exec();
}

void Translator::on_action_Add_a_BiDix_entry_triggered()
{
    QProcess *mal_eng=new QProcess;
    QString workdir=QDir::homePath();
    mal_eng->setWorkingDirectory(workdir.append("/apertium-mal-eng"));
    mal_eng->setWorkingDirectory(workdir);
    QStringList arguments;
    arguments << "apertium-mal-eng.mal-eng.dix";
    mal_eng->start("gedit",arguments);
    mal_eng->waitForStarted(-1);
}
/*void Translator::retranslateUi()
{
    ui->Translator.retranslateUi();
}*/
