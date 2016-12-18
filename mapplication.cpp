/**
 * @file mapplication.cpp
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * Copyright (C) 2016  flomll
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
 * @brief Application implementation to group simple basic steps
 */
#include <QFile>
#include <QDir>
#include <QThread>
#include <QSettings>

#include "mapplication.h"

/**
 * @brief Create a instace of the PFApplication object
 *
 * @param argc Number of arguments
 * @param argv Array of string arguments to parse
 */
MApplication::MApplication(int &argc, char **argv) : QApplication(argc, argv)
{
}

/**
 * @brief Free allocated memory
 */
MApplication::~MApplication()
{
}

/**
 * @brief Initialize the application class with some values for the base clases
 */
void MApplication::initialize()
{
    QCoreApplication::setOrganizationName("mllapps");
    QCoreApplication::setOrganizationDomain("mllapps.com");
    QCoreApplication::setApplicationName("QRokBox Generator");
    QCoreApplication::setApplicationVersion(VERSION_STRING);
}

/**
 * @brief Define and parse given command line arguments
 */
void MApplication::defineOptions()
{
    // handling the command line arguments
    _parser.setApplicationDescription("slide show for online images from mllapps.com");
    _parser.addHelpOption();
    _parser.addVersionOption();

    // Option to set the working directory
    QCommandLineOption workingDirectoryOption(QStringList() << "w" << "working-directory",
                                              QCoreApplication::translate("main", "Save all downloaded files into <directory>."),
                                              QCoreApplication::translate("main", "directory"),
                                              QDir::homePath());
    _parser.addOption(workingDirectoryOption);

    // Option to set the config file path
    QCommandLineOption configFileOption(QStringList() << "c" << "config-file",
                                        QCoreApplication::translate("main", "Configuration file. Default value is /etc/qrokbox.ini"),
                                        QCoreApplication::translate("main", "file"),
                                        "/etc/qrokbox.ini");
    _parser.addOption(configFileOption);

    // Process the actual command line arguments given by the user
    _parser.process(*this);

    _workingDirectory = _parser.value(workingDirectoryOption);
    _configFile = _parser.value(configFileOption);
}

/**
 * @brief Overwrite exitsing values by the given config file
 */
void MApplication::performOptions()
{
    if(QFile(_configFile).exists())
    {
        QSettings settings(_configFile, QSettings::IniFormat);
    }else {
        /// @todo Create a factory settings file
        qCritical("settings file does not exists!");
    }


    // Load an application style
    QFile styleFile(":/styles/assets/styles/default.qss");
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    setStyleSheet( style );
}

void MApplication::process()
{
}

/*------------------------------------------------------------------------------
 * SETTER / GETTER
 *----------------------------------------------------------------------------*/
QString MApplication::workingDirectory() const
{
    return _workingDirectory;
}

QString MApplication::configFile() const
{
    return _configFile;
}
