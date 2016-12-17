/**
 * @file mproducer.cpp
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * This document contains proprietary information belonging to mllapps.com.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorization.
 *
 * @brief
 */
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include "mproducer.h"
#include "mrokbox.h"

MProducer::MProducer(MainWindow * w, QObject *parent) : QObject(parent)
{
    _mainwindow = w;
}

void MProducer::run()
{
    int imageIdCnt = 1;

    foreach (const QUrl &url, _urls) {
        const QString &fileName = url.toLocalFile();

        QThread * thread = new QThread();
        MRokBox * lightbox = new MRokBox();
        lightbox->setImageInputPath(fileName);
        lightbox->setExportPath(_exportPath);
        lightbox->setImageId(imageIdCnt++);
        lightbox->setGalleryName(_galleryName);
        lightbox->setGalleryNamePath(_galleryExportPath);

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
                _mainwindow, SLOT(writeToConsole(QString)));

        thread->start();
        QCoreApplication::processEvents();
    }
}

QList<QUrl> MProducer::urls() const
{
    return _urls;
}

void MProducer::setUrls(const QList<QUrl> &urls)
{
    _urls = urls;
}

QString MProducer::galleryExportPath() const
{
    return _galleryExportPath;
}

void MProducer::setGalleryExportPath(const QString &galleryExportPath)
{
    _galleryExportPath = galleryExportPath;
}

QString MProducer::galleryName() const
{
    return _galleryName;
}

void MProducer::setGalleryName(const QString &galleryName)
{
    _galleryName = galleryName;
}

QString MProducer::exportPath() const
{
    return _exportPath;
}

void MProducer::setExportPath(const QString &exportPath)
{
    _exportPath = exportPath;
}
