#include <QtGui/QApplication>
#include "widget.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP1251"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
