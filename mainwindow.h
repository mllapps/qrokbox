/**
 * @file mainwindow.h
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * This document contains proprietary information belonging to mllapps.com.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorization.
 *
 * @brief
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
