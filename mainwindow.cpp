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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mrokbox.h"



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


    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(toggleConsole(bool)) );
}

MainWindow::~MainWindow()
{
    delete ui;
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
    int imageIdCnt = 1;
    // Clear the console output before start a new parsing process
    ui->console->clear();

    // Generate the default export path
    QDateTime now = QDateTime::currentDateTime();
    QString exportPathDefault = QString("%1/%2").arg(
                QDir::homePath(),
                now.toString("yyyy-MM-dd_HH-mm-ss")
                );

    //qDebug() << exportPathDefault;

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


    foreach (const QUrl &url, e->mimeData()->urls()) {
        const QString &fileName = url.toLocalFile();
        QDir d = QFileInfo(fileName).absoluteDir();
        QString exportPath = d.path();
        QStringList parts = exportPath.split("/");

        parts.removeAt(parts.count()-1);
        if(parts.at(0).compare("") == 0) {
            parts.removeAt(0);
        }

        exportPath.clear();
        for(int i = 0; i < parts.count(); i++)
        {
            exportPath.append("/").append(parts.at(i));
        }
        qDebug() << "Dropped file:" << fileName;
        //qDebug() << "export path: " << exportPath;

        QThread * thread = new QThread();
        MRokBox * lightbox = new MRokBox();
        lightbox->setImageInputPath(fileName);
        lightbox->setExportPath(exportPathDefault);
        lightbox->setImageId(imageIdCnt++);
        lightbox->setGalleryName(ui->galleryName->text());
        lightbox->setGalleryNamePath(myGalleryName);

        lightbox->moveToThread(thread);

        connect(thread, SIGNAL(finished()),
                thread, SLOT(deleteLater()) );
        connect(thread, SIGNAL(started()),
                lightbox, SLOT(run()));
        connect(lightbox, SIGNAL(finished()),
                thread, SLOT(quit()));
        connect(lightbox, SIGNAL(finished()),
                lightbox, SLOT(deleteLater()));

        connect(lightbox, SIGNAL(writeToConsole(QString)),
                this, SLOT(writeToConsole(QString)));

        thread->start();

        //emit setFilePath(fileName, exportPath);
    }
}

void MainWindow::writeToConsole(const QString &msg)
{
    QString old(msg);
    old.append("\n");

    ui->console->appendPlainText(old);

//    QTextCursor c = ui->console->textCursor();
//    c.movePosition(QTextCursor::End);
//    ui->console->setTextCursor(c);
}

void MainWindow::toggleConsole(bool val)
{
    if(ui->console->isHidden()) {
        ui->labelDropHere->setHidden(true);
        ui->console->setHidden(false);
        ui->galleryName->setReadOnly(true);
    }else {
        ui->labelDropHere->setHidden(false);
        ui->console->setHidden(true);
        ui->galleryName->setReadOnly(false);
    }
}
