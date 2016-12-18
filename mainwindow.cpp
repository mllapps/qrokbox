/**
 * @file mainwindow.cpp
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * This document contains proprietary information belonging to mllapps.com.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorization.
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
#include <QInputDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mrokbox.h"
#include "mproducer.h"

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

    // Load the drag & drop image
    QPixmap drophere;
    QString resource = QString(":/assets/assets/drop-here.png");
    if(drophere.load(resource) == false) {
        qDebug() << "file could not loaded";
    }
    ui->labelDropHere->setPixmap(drophere);
    ui->galleryName->setHidden(true);


    ui->status->setText(tr("Drop here"));


    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(toggleConsole(bool)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::showDialog()
{
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
    }

    ui->console->setHidden(false);
    ui->labelDropHere->setHidden(true);
    ui->galleryName->setReadOnly(true);

    QString myGalleryName = QString("%1%2").arg(
                now.toString("yyyyMMdd"),
                ui->galleryName->text()
                );


    QThread * thread = new QThread();
    MProducer * producer = new MProducer(this);
    producer->setGalleryName(ui->galleryName->text());
    producer->setExportPath(myGalleryName);
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

void MainWindow::writeToConsole(const QString &msg)
{
    QString old(msg);
    ui->console->appendPlainText(old);
}

void MainWindow::toggleConsole(bool val)
{
    if(ui->console->isHidden()) {
        ui->labelDropHere->setHidden(true);
        ui->console->setHidden(false);
        ui->galleryName->setReadOnly(true);
        ui->pushButton->setText(tr("Hide"));
    }else {
        ui->labelDropHere->setHidden(false);
        ui->console->setHidden(true);
        ui->galleryName->setReadOnly(false);
        ui->pushButton->setText(tr("Show"));
    }
}
