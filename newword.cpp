#include "newword.h"
#include "ui_newword.h"


NewWord::NewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWord)
{
    ui->setupUi(this);
    loaddix();
    initilise();
    current_pos=ui->pos_selector->currentText();
}

NewWord::~NewWord()
{
    delete ui;
    file.close();
}

void NewWord::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                 tr("Monolingual dictionary (*.dix);;xml files (*.xml"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        //reader.setDevice(&file);
        //doc.setContent("mydocument");
        doc.setContent(&file);
    }
}
void NewWord::loaddix()
{
     dixfile = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                 tr("Monolingual dictionary (*.dix);;xml files (*.xml"));
     if (!dixfile.isEmpty())
     {
         file.setFileName(dixfile);
         if (!file.open(QIODevice::ReadWrite))
         {
             QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
             return;
         }
     }
}

void NewWord::initilise()
{
   // QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),tr("Monolingual dictionary (*.dix);;xml files (*.xml"));

        //reader.setDevice(&file);
        //doc.setContent("mydocument");
    file.seek(0);
    doc.setContent(&file);
    ui->parselection->clear();
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    QDomNodeList paradefs =doc.elementsByTagName("pardef");
    //qDebug()<<"\nlenght:"<<paradefs.length();
    for(uint i=0;i<paradefs.length();i++)
    {
        QDomElement paradef=paradefs.at(i).toElement();
        QString name= paradef.attribute("n");
        //cout<<"\n"<<qPrintable(name);
        try
        {
            if(name.split("__").length()>=2)
            {

                QString par=name.split("__").at(0);
                QString pos=name.split("__").at(1);
                if((pos=="n"&&current_pos=="Noun")||(pos=="vblex"&&current_pos=="Verb")||(pos=="adj"&&current_pos=="Adjective")||(pos=="adv"&&current_pos=="Adverb")||(pos=="prn"&&current_pos=="Pronoun"))
                {
                    //ui->parselection->addItem(par);
                    ui->parselection->addItem(name);
                }
                else
                {
                    //qDebug()<<pos<<current_pos;
                }
            }
        }
        catch(QString)
        {
            std::cout<<"excpetion";
        }

    }
}

void NewWord::on_parselection_currentTextChanged(const QString &arg1)
{
   update_preview();
}

void NewWord::on_add_to_dict_clicked()
{
    int ret = QMessageBox::question(this, tr("ADD to dict"),tr("are you sure"),QMessageBox::Save | QMessageBox::Cancel);
    if(ret==QMessageBox::Cancel)
    {
        return;
    }
    QString word=ui->word->text();
    QString lemma=ui->lemma->text();
    QString paradigm=ui->parselection->currentText();
    QTextStream out(&file);
    QDomNode section=doc.elementsByTagName("section").at(0);
    QDomElement elem = doc.createElement("e");
    elem.setAttribute("lm", lemma);
    section.appendChild(elem);
    QDomElement i= doc.createElement("i");
    QDomText i_value= doc.createTextNode(word);
    i.appendChild(i_value);
    //i.appendChild(text);
    elem.appendChild(i);
    QDomElement par=doc.createElement("par");
    par.setAttribute("n", paradigm);
    elem.appendChild(par);
    //doc.save(out,-1);
    file.close();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to write file";
    }

    QTextStream stream(&file);
    //doc:
    stream << doc.toString(1);
    format_dix();
    file.close();

     qDebug() << "Finished";
}
void NewWord::format_dix()
{
   QProcess *dix_tools=new QProcess;
   QString program="apertium-dixtools";
   QStringList arguments;
   arguments<<"format"<<file.fileName()<<file.fileName()<<" -useTabs";
   dix_tools->execute(program,arguments);
   dix_tools->waitForFinished(-1);
   qDebug()<<file.fileName();

}
void NewWord::on_preview_textChanged()
{
    if(!ui->preview->toPlainText().isEmpty())
    {
        ui->add_to_dict->setEnabled(true);

    }
    else
    {

    }
}


void NewWord::on_pos_selector_currentIndexChanged(const QString &arg1)
{
    current_pos=arg1;
    initilise();
    update_preview();
    qDebug()<<arg1;
}
void NewWord::update_preview()
{
    QDomNodeList paradefs =doc.elementsByTagName("pardef");
    QString word=ui->word->text();
    QString lemma=ui->lemma->text();
    QString preview;
    QString paradigm=ui->parselection->currentText();
    paradefs=doc.elementsByTagName("pardef");
    for(uint i=0;i<paradefs.length();i++)
    {
        QDomElement paradef=paradefs.at(i).toElement();
        QString name= paradef.attribute("n");
        if(name==ui->parselection->currentText())
        {
            QDomNodeList p=paradef.elementsByTagName("l");
            QDomNodeList l_tags=paradef.elementsByTagName("r");
            /*std::cout<<"size"<<p.size();*/
            for(uint i=0;i<p.size();i++)
            {
                QDomNode l=p.at(i);
                QDomNode l_tag=l_tags.at(i);
                /*int length=l_tag.toElement().toText().length();
                QString lemma=word;
                if(length>=1)
                {
                    lemma.remove(word.length()-length,length);
                }
                 lemma=lemma.replace(word.length()-1,1,"");*/
                preview+=lemma;
                QString inflection=l.toElement().text();
                preview+=inflection;
                preview+="\n";
            }
            paradef.childNodes().at(i).toText();
            ui->preview->setText(preview);
            break;
        }
        else
        {
            //ui->preview->setText(ui->parselection->currentText());

        }
    }
    //
}
