/**
 * @file mapplication.h
 * @date 2016-12-18
 * @author flomll (mueller@mllapps.com)
 *
 * Copyright (C) <year>  <name of author>
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
 * @brief Application interface to group simple basic steps
 */
#ifndef MAPPLICATION_H
#define MAPPLICATION_H

#include <QApplication>
#include <QCommandLineParser>

class MApplication : public QApplication
{
    Q_OBJECT
public:
    MApplication(int &argc, char **argv);
    ~MApplication();

    void initialize();
    void defineOptions();
    void performOptions();

    QString workingDirectory() const;
    QString configFile() const;

public slots:
    void process();

signals:

private:
    QCommandLineParser _parser;

    QString _workingDirectory;
    QString _configFile;
};

#endif // MAPPLICATION_H
