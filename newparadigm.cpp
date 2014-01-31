#include "newparadigm.h"
#include "ui_newparadigm.h"

newparadigm::newparadigm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newparadigm)
{
    ui->setupUi(this);
}

newparadigm::~newparadigm()
{
    delete ui;
}
