/**
 * @file mrokbox.cpp
 * @date 2016-12-17
 * @author flomll (mueller@mllapps.com)
 *
 * This document contains proprietary information belonging to mllapps.com.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorization.
 *
 * @brief
 */
#include <QImage>
#include <QFileInfo>
#include <QDebug>

#include "mrokbox.h"
#include "metadata/qexifimageheader.h"

MRokBox::MRokBox(QObject *parent) : QObject(parent),
    _imageId(0),
    _targetWidth(1024),
    _targetHeight(800),
    _targetQuality(100)
{

}

int MRokBox::targetWidth() const
{
    return _targetWidth;
}

void MRokBox::setTargetWidth(int targetWidth)
{
    _targetWidth = targetWidth;
}
int MRokBox::targetHeight() const
{
    return _targetHeight;
}

void MRokBox::setTargetHeight(int targetHeight)
{
    _targetHeight = targetHeight;
}
int MRokBox::targetQuality() const
{
    return _targetQuality;
}

void MRokBox::setTargetQuality(int targetQuality)
{
    _targetQuality = targetQuality;
}
QString MRokBox::imageInputPath() const
{
    return _imageInputPath;
}

void MRokBox::setImageInputPath(const QString &imageInputPath)
{
    _imageInputPath = imageInputPath;
}
QString MRokBox::exportPath() const
{
    return _exportPath;
}

void MRokBox::setExportPath(const QString &exportPath)
{
    _exportPath = exportPath;
}

int MRokBox::imageId() const
{
    return _imageId;
}

void MRokBox::setImageId(int imageId)
{
    _imageId = imageId;
}

QString MRokBox::galleryNamePath() const
{
    return _galleryNamePath;
}

void MRokBox::setGalleryNamePath(const QString &galleryNamePath)
{
    _galleryNamePath = galleryNamePath;
}

QString MRokBox::galleryName() const
{
    return _galleryName;
}

void MRokBox::setGalleryName(const QString &galleryName)
{
    _galleryName = galleryName;
}

QImage * MRokBox::orientationCorrection(const QString& filepath)
{
    QExifValue orientation;
    long orientationValue;
    QImage * item = new QImage();
    QImage * rotated;
    QTransform rotation;
    float scaleFactor = 0.0;
    float scaleFactorHeight = 0.0;
    float scaleFactorWidth = 0.0;


    // Read the exif data from the file and correct the rotation
    QExifImageHeader header(filepath);

    orientation = header.value(QExifImageHeader::Orientation);
    orientationValue = orientation.toLong();
    //qDebug() << "Orientation : " << orientationValue << " for " << filepath;

    item->load(filepath);

    // correct the orientation
    if(orientationValue == 8) {
        int rotationValue = -90;
        rotation.rotate(rotationValue);
        rotated = new QImage(item->transformed(rotation));
        delete item; item = 0;
        item = rotated;
    }else if(orientationValue == 3) {
        int rotationValue = -180;
        rotation.rotate(rotationValue);
        rotated = new QImage(item->transformed(rotation));
        delete item; item = 0;
        item = rotated;
    }else if(orientationValue == 6) {
        int rotationValue = 90;
        rotation.rotate(rotationValue);
        rotated = new QImage(item->transformed(rotation));
        delete item; item = 0;
        item = rotated;
    }

    // respect the ratio and scale the image for the display
    if(_targetWidth > item->width() && _targetHeight > item->height()) {
        //qDebug() << "image is smaller w: " << item->width() << " h: " << item->height();
        scaleFactor = 1.0;
    }else {
        scaleFactorWidth = ( (float)_targetWidth - 40) / (float)item->width();
        scaleFactorHeight = ( (float)_targetHeight - 40) / (float)item->height();

        if(scaleFactorWidth > scaleFactorHeight) {
            scaleFactor = scaleFactorHeight;
        }else {
            scaleFactor = scaleFactorWidth;
        }

        //qDebug() << "scale factor: " << scaleFactor;
        //qDebug() << "pixel ratio: " << qApp->devicePixelRatio();
    }


    //Set the image and invalidate our cached pixmap
    return item;
}

void MRokBox::run()
{
    QString albumName = "myalbum";
    QString captionText ="";
    QFileInfo fileInfo(_imageInputPath);
    QString filename = QString("image_%1.jpg").arg(
                QString::number(_imageId)
                );

    QString filePath = QString("%1/%2").arg(
                _exportPath,
                filename
                );

    if(!_galleryName.isEmpty() && _galleryName.compare("") != 0) {
        albumName = _galleryName;
    }

    QImage * inputImage = orientationCorrection(_imageInputPath);

    QImage outputImage = inputImage->scaled(_targetWidth, _targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    outputImage.save(filePath,0, _targetQuality);

    QString msg = QString("<a data-rokbox href=\"%1/%2/%3\" data-rokbox-album=\"%4\" data-rokbox-caption=\"%5\" data-rokbox-generate-thumbnail></a>").arg(
                "images/pixc",
                _galleryNamePath,
                filename,
                albumName,
                captionText);

    emit writeToConsole(msg);

    delete inputImage; inputImage = 0;
}
