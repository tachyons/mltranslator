#ifndef MODESVIEWER_H
#define MODESVIEWER_H

#include <QDialog>
#include <QFile>
#include <QDomDocument>

namespace Ui {
class ModesViewer;
}

class ModesViewer : public QDialog
{
    Q_OBJECT

public:
    explicit ModesViewer(QWidget *parent = 0);
    ~ModesViewer();
    void loadmode();
    void initialise_ui();
private:
    Ui::ModesViewer *ui;
    QString modefile;
    QFile file;
    QDomDocument doc;
};

#endif // MODESVIEWER_H
