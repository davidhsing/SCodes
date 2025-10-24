#include "SBarcodeGenerator.h"
#include <QStandardPaths>
#include <QPainter>

#ifdef Q_OS_ANDROID
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #include <QtAndroid>
#else
    #include <QtCore/private/qandroidextras_p.h>
#endif
#endif

#include "MultiFormatWriter.h"


SBarcodeGenerator::SBarcodeGenerator(QQuickItem* parent) : QQuickItem(parent) {
}

bool SBarcodeGenerator::generate(const QString &inputString)
{
    try {
        if (inputString.isEmpty()) {
            return false;
        } else {
            // Change ecc level to max to generate image on QR code.
            if (m_format == SCodes::SBarcodeFormat::QRCode && !m_centerImage.isEmpty()) {
                if (m_eccLevel < 8) {
                    qDebug() << "To draw image on QR Code use maximum level of ecc. Setting it to 8.";
                    setEccLevel(8);
                }
            }

            ZXing::MultiFormatWriter writer = ZXing::MultiFormatWriter(SCodes::toZXingFormat(m_format)).setMargin(imageMargin()).setEccLevel(m_eccLevel);
            auto qrCodeMatrix = writer.encode(inputString.toStdString(), m_imageWidth, m_imageHeight);
            QImage image(m_imageWidth, m_imageHeight, QImage::Format_ARGB32);

            for (int y = 0; y < m_imageHeight; ++y) {
                for (int x = 0; x < m_imageWidth; ++x) {
                    if (qrCodeMatrix.get(x, y)) {
                        image.setPixelColor(x, y, m_foregroundColor);
                    } else {
                        image.setPixelColor(x, y, m_backgroundColor);
                    }
                }
            }

            // Center images works only on QR codes.
            if (m_format == SCodes::SBarcodeFormat::QRCode && !m_centerImage.isEmpty()) {
                QSize centerImageSize(m_imageWidth / m_centerImageRatio, m_imageHeight / m_centerImageRatio);
                drawCenterImage(&image, m_centerImage, centerImageSize, (image.width() - centerImageSize.width()) / 2, (image.height() - centerImageSize.height()) / 2);
            }
            m_outputFile = m_filePath + "/" + m_fileName;
            if (!m_fileExtension.isEmpty()) {
                m_outputFile += "." + m_fileExtension;
            }
            QFile file{m_outputFile};
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                image.save(&file);
            } else {
                qWarning() << "Could not open file for writing!";
                return false;
            }
            emit generationFinished();
            return true;
        }
    } catch (const std::exception &e) {
        emit generationFinished(e.what());
    } catch (...) {
        emit generationFinished("Unsupported exception thrown");
    }

    return false;
} // SBarcodeGenerator::generate

bool SBarcodeGenerator::saveImage()
{
    if (m_outputFile.isEmpty()) {
        return false;
    }
    #ifdef Q_OS_ANDROID
        #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        if (QtAndroid::checkPermission(QString("android.permission.WRITE_EXTERNAL_STORAGE")) == QtAndroid::PermissionResult::Denied)
        {
            QtAndroid::PermissionResultMap resultHash =
              QtAndroid::requestPermissionsSync(QStringList({ "android.permission.WRITE_EXTERNAL_STORAGE" }));
            if (resultHash["android.permission.WRITE_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied) {
                return false;
            }
        }
        #else
            QtAndroidPrivate::requestPermission(QString("android.permission.WRITE_EXTERNAL_STORAGE"));
        #endif
    #endif
    QString docFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + m_fileName;
    if (!m_fileExtension.isEmpty()) {
        docFolder += "." + m_fileExtension;
    }
    QFile::copy(m_outputFile, docFolder);
    return true;
}

void SBarcodeGenerator::drawCenterImage(QImage *parentImage, const QString &centerImage, QSize imageSize, int x, int y)
{
    QImage loadedImage(imageSize, QImage::Format_RGB32);
    loadedImage.load(centerImage);
    if (loadedImage.isNull()) {
        qWarning() << "Center image could not be loaded!";
        return;
    }
    // Create a painter to overlay the center image on the parentImage.
    QPainter painter(parentImage);
    // Draw background rectangle.
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRect(x, y, imageSize.width(), imageSize.height());

    // Scale the center image to be smaller than background rectangle.
    float imageRatio = 0.8;
    loadedImage = loadedImage.scaled(imageSize.width() * imageRatio,
                                     imageSize.height() * imageRatio,
                                     Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Draw image.
    painter.drawImage(x + (imageSize.width() - loadedImage.width()) / 2,
                      y + (imageSize.height() - loadedImage.height()) / 2,
                      loadedImage);
    painter.end();
}

int SBarcodeGenerator::imageWidth() const
{
    return m_imageWidth;
}

void SBarcodeGenerator::setImageWidth(int width)
{
    if (m_imageWidth == width) {
        return;
    }
    m_imageWidth = width;
    emit imageWidthChanged(m_imageWidth);
}

int SBarcodeGenerator::imageHeight() const
{
    return m_imageHeight;
}

void SBarcodeGenerator::setImageHeight(int height)
{
    if (m_imageHeight == height) {
        return;
    }
    m_imageHeight = height;
    emit imageHeightChanged(m_imageHeight);
}

int SBarcodeGenerator::imageMargin() const
{
    return m_imageMargin;
}

void SBarcodeGenerator::setImageMargin(int margin)
{
    if (m_imageMargin == margin) {
        return;
    }
    m_imageMargin = margin;
    emit imageMarginChanged(m_imageMargin);
}

int SBarcodeGenerator::eccLevel() const
{
    return m_eccLevel;
}

void SBarcodeGenerator::setEccLevel(int eccLevel)
{
    if (m_eccLevel == eccLevel) {
        return;
    }
    m_eccLevel = eccLevel;
    emit eccLevelChanged(m_eccLevel);
}

SCodes::SBarcodeFormat SBarcodeGenerator::format() const
{
    return m_format;
}

void SBarcodeGenerator::setFormat(SCodes::SBarcodeFormat format)
{
    if (m_format != format) {
        switch (format) {
            case SCodes::SBarcodeFormat::None:
                qWarning() << "You need to set a specific format";
                return;
            case SCodes::SBarcodeFormat::Any:
            case SCodes::SBarcodeFormat::OneDCodes:
            case SCodes::SBarcodeFormat::TwoDCodes:
                qWarning() << "Multiple formats can't be used to generate a barcode";
                return;
            default:
                m_format = format;
                emit formatChanged(m_format);
        }
    }
}

void SBarcodeGenerator::setFormat(const QString &formatName)
{
    setFormat(SCodes::fromString(formatName));
}

QString SBarcodeGenerator::centerImage() const
{
    return m_centerImage;
}

void SBarcodeGenerator::setCenterImage(const QString &centerImage)
{
    if (m_centerImage == centerImage) {
        return;
    }
    m_centerImage = centerImage;
    emit centerImageChanged();
}

int SBarcodeGenerator::centerImageRatio() const
{
    return m_centerImageRatio;
}

void SBarcodeGenerator::setCenterImageRatio(int centerImageRatio)
{
    if (m_centerImageRatio == centerImageRatio) {
        return;
    }
    m_centerImageRatio = centerImageRatio;
    emit centerImageRatioChanged();
}

QColor SBarcodeGenerator::foregroundColor() const
{
    return m_foregroundColor;
}

void SBarcodeGenerator::setForegroundColor(const QColor &foregroundColor)
{
    if (m_foregroundColor == foregroundColor) {
        return;
    }
    m_foregroundColor = foregroundColor;
    emit foregroundColorChanged();
}

QColor SBarcodeGenerator::backgroundColor() const
{
    return m_backgroundColor;
}

void SBarcodeGenerator::setBackgroundColor(const QColor &backgroundColor)
{
    if (m_backgroundColor == backgroundColor) {
        return;
    }
    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged();
}

QString SBarcodeGenerator::filePath() const
{
    return m_filePath;
}

void SBarcodeGenerator::setFilePath(const QString &filePath)
{
    if (m_filePath == filePath) {
        return;
    }
    emit filePathChanged(m_filePath);
    m_filePath = filePath;
}

QString SBarcodeGenerator::fileName() const
{
    return m_fileName;
}

void SBarcodeGenerator::setFileName(const QString &fileName)
{
    if (m_fileName == fileName) {
        return;
    }
    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

QString SBarcodeGenerator::fileExtension() const
{
    return m_fileExtension;
}

void SBarcodeGenerator::setFileExtension(const QString &fileExtension)
{
    if (m_fileExtension == fileExtension) {
        return;
    }
    m_fileExtension = fileExtension;
    emit fileExtensionChanged(m_fileExtension);
}

QString SBarcodeGenerator::outputFile() const
{
    return m_outputFile;
}

QString SBarcodeGenerator::inputText() const
{
    return m_inputText;
}

void SBarcodeGenerator::setInputText(const QString &inputText)
{
    if (m_inputText == inputText) {
        return;
    }
    m_inputText = inputText;
    emit inputTextChanged(m_inputText);
}
