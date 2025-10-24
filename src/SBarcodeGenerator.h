#ifndef SBARCODEGENERATOR_H
#define SBARCODEGENERATOR_H

#include <QDir>
#include <QImage>
#include <qqml.h>
#include <QQuickItem>
#include <QObject>
#include "BitMatrix.h"
#include "ByteMatrix.h"
#include "SBarcodeFormat.h"


/*!
 * \brief The SBarcodeGenerator class allows you to configure, generate & save barcodes.
 */
class SBarcodeGenerator : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int imageWidth READ imageWidth WRITE setImageWidth NOTIFY imageWidthChanged)
    Q_PROPERTY(int imageHeight READ imageHeight WRITE setImageHeight NOTIFY imageHeightChanged)
    Q_PROPERTY(int imageMargin READ imageMargin WRITE setImageMargin NOTIFY imageMarginChanged)
    Q_PROPERTY(int eccLevel READ eccLevel WRITE setEccLevel NOTIFY eccLevelChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString fileExtension READ fileExtension WRITE setFileExtension NOTIFY fileExtensionChanged)
    Q_PROPERTY(QString outputFile READ outputFile)
    Q_PROPERTY(QString inputText READ inputText WRITE setInputText NOTIFY inputTextChanged)
    Q_PROPERTY(SCodes::SBarcodeFormat format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(QString centerImage READ centerImage WRITE setCenterImage NOTIFY centerImageChanged)
    Q_PROPERTY(int centerImageRatio READ centerImageRatio WRITE setCenterImageRatio NOTIFY centerImageRatioChanged)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:

    /*!
     * \fn explicit SBarcodeGenerator(QObject *parent)
     * \brief Constructor.
     * \param QObject *parent - a pointer to the parent object.
     */
    explicit SBarcodeGenerator(QQuickItem *parent = nullptr);

    /*!
     * \fn ~SBarcodeGenerator() override
     * \brief Destructor.
     */
    ~SBarcodeGenerator() override { }

    /*!
     * \fn SCodes::SBarcodeFormat format() const
     * \brief Returns current barcode format.
     */
    SCodes::SBarcodeFormat format() const;

    /*!
     * \fn void setFormat(SCodes::SBarcodeFormat format)
     * \brief Sets the barcode format.
     * \param SCodes::SBarcodeFormat format - barcode format.
     */
    void setFormat(SCodes::SBarcodeFormat format);

    /*!
     * \fn QString centerImage() const
     * \brief Returns the center image path.
     */
    QString centerImage() const;

    /*!
     * \fn void setCenterImage(const QString &centerImage)
     * \brief Sets the center image path.
     * \param const QString &centerImage - new image path.
     */
    void setCenterImage(const QString &centerImage);

    /*!
     * \fn int centerImageRatio() const
     * \brief Returns the center image ratio.
     */
    int centerImageRatio() const;

    /*!
     * \fn void setCenterImageRatio(int centerImageRatio)
     * \brief Sets the center image ratio.
     * \param const int &centerImageRatio - new image ratio.
     */
    void setCenterImageRatio(int centerImageRatio);
    
    /*!
     * \fn QColor foregroundColor() const
     * \brief Returns foregroundColor.
     */
    QColor foregroundColor() const;

    /*!
     * \fn QColor backgroundColor() const
     * \brief Returns backgroundColor.
     */
    QColor backgroundColor() const;

    /*!
     * \fn int imageWidth() const
     * \brief Returns the image width.
     */
    int imageWidth() const;

    /*!
     * \fn void setImageWidth(int width)
     * \brief Sets the image width.
     * \param int width - image width.
     */
    void setImageWidth(int width);

    /*!
     * \fn int imageHeight() const
     * \brief Returns the image height.
     */
    int imageHeight() const;

    /*!
     * \fn void setImageHeight(int height)
     * \brief Sets the image height.
     * \param int height - image height.
     */
    void setImageHeight(int height);

    /*!
     * \fn int imageMargin() const
     * \brief Returns the image margin.
     */
    int imageMargin() const;

    /*!
     * \fn void setImageMargin(int margin)
     * \brief Sets the image margin.
     * \param int margin - image margin.
     */
    void setImageMargin(int margin);

    /*!
     * \fn int eccLevel() const
     * \brief Returns the ecc level.
     */
    int eccLevel() const;

    /*!
     * \fn void setEccLevel(int eccLevel)
     * \brief Sets the ecc level.
     * \param int eccLevel - ecc level.
     */
    void setEccLevel(int eccLevel);

    /*!
     * \fn QString fileName() const
     * \brief Returns the file name.
     */
    QString fileName() const;

    /*!
     * \fn void setFileName(const QString &fileName)
     * \brief Sets the file name.
     * \param const QString &fileName - file name.
     */
    void setFileName(const QString &fileName);

    /*!
     * \fn QString filePath() const
     * \brief Returns the file path.
     */
    QString filePath() const;

    /*!
     * \fn void setFilePath(const QString &filePath)
     * \brief Sets the file path.
     * \param const QString &filePath - file path.
     */
    void setFilePath(const QString &filePath);

    /*!
     * \fn QString fileExtension() const
     * \brief Returns the fileExtension.
     */
    QString fileExtension() const;

    /*!
     * \fn void setFileExtension(const QString &fileExtension)
     * \brief Sets the fileExtension.
     * \param const QString &fileExtension - fileExtension.
     */
    void setFileExtension(const QString &fileExtension);

    /*!
     * \fn QString outputFile() const
     * \brief Returns the file path.
     */
    QString outputFile() const;

    /*!
     * \fn QString inputText() const
     * \brief Returns the input text.
     */
    QString inputText() const;

    /*!
     * \fn void setInputText(const QString &inputText)
     * \brief Sets the input text.
     * \param const QString &inputText - input text.
     */
    void setInputText(const QString &inputText);

public slots:

    /*!
     * \fn bool generate(const QString &inputString)
     * \brief Function for generating barcodes from given string
     * \param const QString &inputString - string of the barcode
     */
    bool generate(const QString &inputString);

    /*!
     * \fn void setFormat(const QString &formatName)
     * \brief Sets the barcode format.
     * \param const QString &formatName - barcode format string.
     */
    void setFormat(const QString &formatName);

    /*!
     * \fn bool saveImage()
     * \brief Saves the generated barcode image.
     */
    bool saveImage();

    /*!
     * \fn void setForegroundColor(const QColor &newForegroundColor)
     * \brief Sets the foreground.
     * \param const QColor &foreground - foreground color.
     */
    void setForegroundColor(const QColor &foregroundColor);

    /*!
     * \fn void setBackgroundColor(const QColor &backgroundColor)
     * \brief Sets the backgroundColor.
     * \param const QColor &backgroundColor - background color.
     */
    void setBackgroundColor(const QColor &backgroundColor);

signals:

    /*!
     * \brief This signal is emitted when barcode generation is finished. If any error happens, sends the error string to QML.
     * \param const QString &error - error string.
     */
    void generationFinished(const QString &error = "");

    /*!
     * \brief This signal is emitted to send image width to QML.
     * \param int width - image width.
     */
    void imageWidthChanged(int width);

    /*!
     * \brief This signal is emitted to send image height to QML.
     * \param int height - image height.
     */
    void imageHeightChanged(int height);

    /*!
     * \brief This signal is emitted to send image margin to QML.
     * \param int margin - image margin.
     */
    void imageMarginChanged(int margin);

    /*!
     * \brief This signal is emitted to send eccLevel to QML.
     * \param int eccLevel - error correction code level.
     */
    void eccLevelChanged(int eccLevel);

    /*!
     * \brief This signal is emitted to send filePath to QML.
     * \param const QString &filePath - filePath.
     */
    void filePathChanged(const QString &filePath);

    /*!
     * \brief This signal is emitted to send fileName to QML.
     * \param const QString &fileName - fileName.
     */
    void fileNameChanged(const QString &fileName);

    /*!
     * \brief This signal is emitted to send fileExtension to QML.
     * \param const QString &fileExtension - fileExtension.
     */
    void fileExtensionChanged(const QString &fileExtension);

    /*!
     * \brief This signal is emitted to send inputText to QML.
     * \param const QString &inputText - inputText.
     */
    void inputTextChanged(const QString &inputText);

    /*!
     * \brief This signal is emitted to send barcode format to QML.
     * \param SCodes::SBarcodeFormat format - barcode format.
     */
    void formatChanged(SCodes::SBarcodeFormat format);

    /*!
     * \brief This signal is emitted to send image path to QML.
     */
    void centerImageChanged();

    /*!
     * \brief This signal is emitted to send center image ratio to QML.
     */
    void centerImageRatioChanged();

    /*!
     * \brief This signal is emitted to send foregroundColor to QML.
     * \param const QColor &foregroundColor - foregroundColor.
     */
    void foregroundColorChanged();

    /*!
     * \brief This signal is emitted to send backgroundColor to QML.
     * \param const QColor &backgroundColor - backgroundColor.
     */
    void backgroundColorChanged();

private:
    int m_imageWidth    = 500;
    int m_imageHeight   = 500;
    int m_imageMargin   = 10;
    int m_eccLevel = -1;

    // centerImageRatio defines the ratio by which the center image is smaller than the QR code.
    int m_centerImageRatio = 5;

    QString m_filePath  = QDir::tempPath();
    QString m_fileName  = "scode";
    QString m_fileExtension = "png";
    QString m_inputText = "";
    QString m_centerImage = "";
    QString m_outputFile  = "";

    SCodes::SBarcodeFormat m_format = SCodes::SBarcodeFormat::Code128;

    /*!
     * \brief This method draws Rectangle and `imageRatio` smaller Image in the center of that Rectangle.
     * \param QImage *parentImage - Image parent. It is used for Painter constructor.
     * \param QString centerImage - Image path.
     * \param QSize imageSize - Image size.
     * \param int x - X coordinate where Image should be painted.
     * \param Qint y - Y coordinate where Image should be painted.
     */
    void drawCenterImage(QImage *parentImage, const QString &centerImage, QSize imageSize, int x, int y);

    /*!
     * \fn void setEccLvel(int eccLevel)
     * \brief Sets the QR code ecc level.
     * \param int eccLevel - QR code ecc level.
     */
    void setEccLvel(int eccLevel);

    QColor m_foregroundColor = "black";
    QColor m_backgroundColor = "white";
};

#endif // SBARCODEGENERATOR_H
