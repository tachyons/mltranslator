#include "modesviewer.h"
#include "ui_modesviewer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QLayout>

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
                                                 tr("Mode Files (*.xml)"));
     if (!modefile.isEmpty())
     {
         file.setFileName(modefile);
         if (!file.open(QIODevice::ReadWrite))
         {
             QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
             return;
         }
     }
}
void ModesViewer::initialise_ui()
{
    file.seek(0);
    doc.setContent(&file);
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    QDomNodeList paradefs =doc.elementsByTagName("mode");
    QLabel *label = new QLabel(this);
    label->setText("text");
    ui->verticalLayout->addWidget(label);
}
