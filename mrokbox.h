#ifndef MLIGHTBOX_H
#define MLIGHTBOX_H

#include <QObject>

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

#endif // MLIGHTBOX_H
