/**
 * @file mproducer.h
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * This document contains proprietary information belonging to mllapps.com.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorization.
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
