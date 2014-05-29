#include "modesviewer.h"
#include "ui_modesviewer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QLayout>
#include<QDebug>
#include<QStringList>
#include<math.h>
#include<QProcess>

ModesViewer::ModesViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModesViewer)
{
    ui->setupUi(this);
    loadmode();
    initialise_ui();
}

ModesViewer::~ModesViewer()
{
    file.close();
    delete ui;

}
void ModesViewer::loadmode()
{
     modefile = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                 tr("Mode Files (*.mode)"));
     if (!modefile.isEmpty())
     {
         file.setFileName(modefile);
         if (!file.open(QIODevice::ReadWrite| QIODevice::Text))
         {
             QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
             return;
         }
     }
}
void ModesViewer::initialise_ui()
{    /*doc.setContent(&file);
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    QDomNodeList paradefs =doc.elementsByTagName("mode");*/

    //QLabel *label = new QLabel(this);
    //QByteArray temp =file.readAll();
    file.seek(0);
    ui->modeTable->setColumnCount(2);
    ui->modeTable->setRowCount(0);
    QString output;
    output=ui->inputText->toPlainText();
    //output="hello"; //debug
    while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QList<QByteArray> steps= line.split('|');
           // QTableWidgetItem *newItem[i];
            for(int i=0;i<steps.length();i++)
            {
                qDebug()<<steps[i]<<"\n";

                if(steps[i].length()>10)
                {
                    //$1 fix
                    steps[i].replace("$1","-g");
                    int row = ui->modeTable->rowCount();
                    ui->modeTable->insertRow(row);
                    QTableWidgetItem *processNameItem = new QTableWidgetItem;
                    processNameItem->setText(steps[i]);
                    ui->modeTable->setItem(row, 0, processNameItem);
                    //ui->modeTable->setItem(row, 1, sizeItem);
                    //process
                    QProcess target,source;
                    QString source_text=output;
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
                    command+=steps[i];
                    //command+="\"";
                    qDebug()<<command;
                    target.start(command);
                    target.waitForFinished(-1);
                    QString p_stdout = target.readAllStandardOutput();
                    QString p_stderr = target.readAllStandardError();
                    output=p_stdout.append(p_stderr);
                    QTableWidgetItem *processOutputItem = new QTableWidgetItem;
                    processOutputItem->setText(output);
                    ui->modeTable->setItem(row, 1,processOutputItem);
                }
            }
            //label->setText(steps[0]);
        }

    //ui->verticalLayout->addWidget(label);
}

void ModesViewer::on_inputText_textChanged()
{
   // initialise_ui();
}

void ModesViewer::on_processButton_clicked()
{
    initialise_ui();
}
