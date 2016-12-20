/**
 * @file mproducer.cpp
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
