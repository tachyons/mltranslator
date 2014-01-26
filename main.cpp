#include "translator.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("mltranslator_mal");
    a.installTranslator(&translator);
    Translator w;
    w.show();
    
    return a.exec();
}
