/**
 * @file main.cpp
 * @author mueller@mllapps.com
 * @copyright Copyright (c) by www.mllapps.com
 *
 * GPL v3
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
