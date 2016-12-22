/**
 * @file mainwindow.h
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
 * @brief
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>

#include "widgets/qroundprogressbar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    bool showDialog();
    
public slots:
    void writeToConsole(const QString& msg);
    void toggleConsole(bool val);
    void genIndexHtml(const QString& path);
private:
    Ui::MainWindow *ui;

    QRoundProgressBar * _progressBar;
    double _step;
};

#endif // MAINWINDOW_H
