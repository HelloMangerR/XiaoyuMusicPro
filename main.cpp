#include "mainw.h"
#include "songoperation.h"
#include "lyricoperation.h"
#include "playlogic.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayLogic w;

    return a.exec();
}
