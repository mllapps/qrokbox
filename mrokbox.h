/**
 * @file mrokbox.h
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
