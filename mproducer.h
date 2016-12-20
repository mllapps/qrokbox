/**
 * @file mproducer.h
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
#ifndef MPRODUCER_H
#define MPRODUCER_H

#include <QObject>
#include <QList>
#include <QUrl>
#include "mainwindow.h"

class MProducer : public QObject
{
    Q_OBJECT
public:
    explicit MProducer(MainWindow * w, QObject *parent = 0);

    QString exportPath() const;
    void setExportPath(const QString &exportPath);

    QString galleryName() const;
    void setGalleryName(const QString &galleryName);

    QString galleryExportPath() const;
    void setGalleryExportPath(const QString &galleryExportPath);

    QList<QUrl> urls() const;
    void setUrls(const QList<QUrl> &urls);

signals:
    void finished();

public slots:
    void run();

private:
    MainWindow * _mainwindow;
    QString _exportPath;
    QString _galleryName;
    QString _galleryExportPath;

    QList<QUrl> _urls;
};

#endif // MPRODUCER_H
