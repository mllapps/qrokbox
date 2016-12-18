/**
 * @file mrokbox.h
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * This document contains proprietary information belonging to mllapps.com.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorization.
 *
 * @brief
 */
#ifndef MROKBOX_H
#define MROKBOX_H

#include <QObject>
#include <QImage>

class MRokBox : public QObject
{
    Q_OBJECT
public:
    explicit MRokBox(QObject *parent = 0);

    int targetWidth() const;
    void setTargetWidth(int targetWidth);

    int targetHeight() const;
    void setTargetHeight(int targetHeight);

    int targetQuality() const;
    void setTargetQuality(int targetQuality);

    QString imageInputPath() const;
    void setImageInputPath(const QString &imageInputPath);

    QString exportPath() const;
    void setExportPath(const QString &exportPath);

    int imageId() const;
    void setImageId(int imageId);

    QString galleryName() const;
    void setGalleryName(const QString &galleryName);

    QString galleryNamePath() const;
    void setGalleryNamePath(const QString &galleryNamePath);

    QImage * orientationCorrection(const QString& filepath);
    
signals:
    void finished();
    void writeToConsole(const QString& msg);

public slots:

    void run();

private:
    int _imageId;
    int _targetWidth;
    int _targetHeight;
    int _targetQuality;
    QString _imageInputPath;
    QString _exportPath;
    QString _galleryName;
    QString _galleryNamePath;

};

#endif // MROKBOX_H
