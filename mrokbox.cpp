#include "mrokbox.h"

#include <QImage>
#include <QFileInfo>
#include <QDebug>

MRokBox::MRokBox(QObject *parent) : QObject(parent),
    _imageId(0),
    _targetWidth(1024),
    _targetHeight(800),
    _targetQuality(90)
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

void MRokBox::run()
{
    QString albumName = "myalbum";
    QString captionText ="";
    QFileInfo fileInfo(_imageInputPath);
//    QString filename(fileInfo.fileName());
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

    //qDebug() << "filepath: " << filePath;
    QImage inputImage(_imageInputPath);
    QImage outputImage = inputImage.scaled(_targetWidth, _targetHeight, Qt::KeepAspectRatio);

    outputImage.save(filePath,0, _targetQuality);

    QString msg = QString("<a data-rokbox href=\"%1/%2/%3\" data-rokbox-album=\"%4\" data-rokbox-caption=\"%5\" data-rokbox-generate-thumbnail></a>").arg(
                "images/pixc",
                _galleryNamePath,
                filename,
                albumName,
                captionText);

    emit writeToConsole(msg);
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
