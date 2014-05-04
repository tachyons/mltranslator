#ifndef NEWPARADIGM_H
#define NEWPARADIGM_H

#include <QDialog>

namespace Ui {
class newparadigm;
}

class newparadigm : public QDialog
{
    Q_OBJECT

public:
    explicit newparadigm(QWidget *parent = 0);
    ~newparadigm();

private:
    Ui::newparadigm *ui;
};

#endif // NEWPARADIGM_H
