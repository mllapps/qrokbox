/**
 * @file main.cpp
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * Copyright (C) 2016  www.mllapps.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @brief QRokBox Generator
 */
#include <QApplication>

#include "mainwindow.h"
#include "mapplication.h"

void myMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & message);

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageHandler);

    MApplication app(argc, argv);
    app.initialize();
    app.defineOptions();

    app.performOptions();

    MainWindow w;
    w.show();

    return app.exec();
}

void myMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & message)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "[debug]: %s %s\n", context.function, message.toStdString().c_str());
        break;
    case QtWarningMsg:
        fprintf(stderr, "[warning]: %s\n", message.toStdString().c_str());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[critical]: %s\n", message.toStdString().c_str());
        break;
    case QtFatalMsg:
        fprintf(stderr, "[fatal]: %s\n", message.toStdString().c_str());
        abort();
    default:
        break;
    }
}
