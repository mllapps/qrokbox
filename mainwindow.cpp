/**
 * @file mainwindow.cpp
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
#include <QDebug>
#include <QPixmap>
#include <QDir>
#include <QFileDialog>
#include <QDateTime>
#include <QDialog>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QThread>
#include <QMimeData>
#include <QDir>
#include <QProcess>
#include <QInputDialog>
#include <QDesktopServices>
#include <QMenuBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mrokbox.h"
#include "mproducer.h"
#include "aboutdialog.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->console->setHidden(true);

    // Activate the draq & drop event
    setAcceptDrops(true);

    ui->galleryName->setHidden(true);


    ui->status->setText(tr("Drop here..."));
    // Load the drag & drop image
    QImage img = QIcon(QString(":/assets/image.svg")).pixmap(QSize(80,80)).toImage();
    QPixmap drophere;
//        QString resource = QString(":/assets/image.svg");
//        if(drophere.load(resource) == false) {
//            qDebug() << "file could not loaded";
//        }
    drophere.fromImage(img);
    ui->icon->setPixmap(drophere);

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(toggleConsole(bool)) );

    ui->progressBar->setBarStyle(QRoundProgressBar::StyleLine);
    ui->progressBar->setMinimum(0.0);
    ui->progressBar->setValue(0);

    //@todo Currently disabled
    ui->progressBar->setHidden(true);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutBox()));
    menuBar()->addMenu(helpMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::showDialog()
{
    this->activateWindow();
    bool ok;
    QInputDialog dialog;
    dialog.setWindowFlags(Qt::Popup);
    QString text =  dialog.getText(this, tr("Enter the name of the gallery"),
                                   tr("Name of gallery:"), QLineEdit::Normal,
                                   "", &ok);
    //    QString text = QInputDialog::getText(this, tr("Enter the name of the gallery"),
    //                                         tr("Name of gallery:"), QLineEdit::Normal,
    //                                         "", &ok);
    if (ok && !text.isEmpty())
        ui->galleryName->setText(text);

    return ok;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

/**
 * @brief Detect the drop event
 *
 * It generate the export path and the path from the dropped file
 *
 * @param e the drop event
 */
void MainWindow::dropEvent(QDropEvent *e)
{
    if(!showDialog() ) {
        return;
    }

    // Clear the console output before start a new parsing process
    ui->console->clear();

    // Generate the default export path
    QDateTime now = QDateTime::currentDateTime();
    QString exportPathDefault = QString("%1/%2").arg(
                QDir::homePath(),
                now.toString("yyyy-MM-dd_HH-mm-ss")
                );

    QDir dir(exportPathDefault);
    if (!dir.exists()){
        dir.mkdir(exportPathDefault);

        QDesktopServices::openUrl(QUrl::fromLocalFile(exportPathDefault));
        genIndexHtml(exportPathDefault);
    }

    ui->progressBar->setMaximum(e->mimeData()->urls().count());

    _step = 100 / e->mimeData()->urls().count();

    ui->console->setHidden(false);
    ui->status->setHidden(true);
    ui->galleryName->setReadOnly(true);

    QString myGalleryName = QString("%1%2").arg(
                now.toString("yyyyMMdd"),
                ui->galleryName->text()
                );

    QThread * thread = new QThread();
    MProducer * producer = new MProducer(this);
    producer->setGalleryName(ui->galleryName->text());
    producer->setExportPath(exportPathDefault);
    producer->setGalleryExportPath(myGalleryName);
    producer->setUrls(e->mimeData()->urls());

    connect(thread, SIGNAL(finished()),
            thread, SLOT(deleteLater()) );
    connect(thread, SIGNAL(started()),
            producer, SLOT(run()));
    connect(producer, SIGNAL(finished()),
            thread, SLOT(quit()));
    connect(producer, SIGNAL(finished()),
            producer, SLOT(deleteLater()));

    thread->start();
}

void MainWindow::genIndexHtml(const QString& path)
{
    const char* msg = "<!DOCTYPE html><title></title>";
    QFile file;
    QString filePath = QString("%1/%2").arg(
                path,
                "index.html");
    file.setFileName(filePath);
    file.open(QIODevice::WriteOnly);

    file.write(msg, qstrlen(msg));
    file.close();
}

void MainWindow::showAboutBox()
{
    AboutDialog * about = new AboutDialog(this);
    about->exec();

    connect(about, SIGNAL(rejected()),
            about, SLOT(deleteLater()) );
}

void MainWindow::writeToConsole(const QString &msg)
{
    QString old(msg);
    ui->console->appendPlainText(old);

    double v = ui->progressBar->value();
    ui->progressBar->setValue(v+_step);
}

void MainWindow::toggleConsole(bool val)
{
    if(ui->console->isHidden()) {
        ui->status->setHidden(true);
        ui->console->setHidden(false);
        ui->galleryName->setReadOnly(true);
        ui->pushButton->setText(tr("Hide"));
    }else {
        ui->status->setHidden(false);
        ui->console->setHidden(true);
        ui->galleryName->setReadOnly(false);
        ui->pushButton->setText(tr("Show"));
    }
}
