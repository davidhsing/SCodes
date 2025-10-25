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
class SBarcodeGenerator final : public QQuickItem
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
     * \param parent - a pointer to the parent object.
     */
    explicit SBarcodeGenerator(QQuickItem* parent = nullptr);

    /*!
     * \fn ~SBarcodeGenerator() override
     * \brief Destructor.
     */
    ~SBarcodeGenerator() override { }

    /*!
     * \fn SCodes::SBarcodeFormat format() const
     * \brief Returns current barcode format.
     */
    SCodes::SBarcodeFormat format() const {return m_format;}

    /*!
     * \fn void setFormat(SCodes::SBarcodeFormat format)
     * \brief Sets the barcode format.
     * \param format - barcode format.
     */
    void setFormat(SCodes::SBarcodeFormat format);

    /*!
     * \fn QString centerImage() const
     * \brief Returns the center image path.
     */
    QString centerImage() const {return m_centerImage;}

    /*!
     * \fn void setCenterImage(const QString &centerImage)
     * \brief Sets the center image path.
     * \param centerImage - new image path.
     */
    void setCenterImage(const QString& centerImage);

    /*!
     * \fn int centerImageRatio() const
     * \brief Returns the center image ratio.
     */
    int centerImageRatio() const {return m_centerImageRatio;}

    /*!
     * \fn void setCenterImageRatio(int centerImageRatio)
     * \brief Sets the center image ratio.
     * \param centerImageRatio - new image ratio.
     */
    void setCenterImageRatio(int centerImageRatio);

    /*!
     * \fn QColor foregroundColor() const
     * \brief Returns foregroundColor.
     */
    QColor foregroundColor() const {return m_foregroundColor;}

    /*!
     * \fn QColor backgroundColor() const
     * \brief Returns backgroundColor.
     */
    QColor backgroundColor() const {return m_backgroundColor;}

    /*!
     * \fn int imageWidth() const
     * \brief Returns the image width.
     */
    int imageWidth() const {return m_imageWidth;}

    /*!
     * \fn void setImageWidth(int width)
     * \brief Sets the image width.
     * \param width - image width.
     */
    void setImageWidth(int width);

    /*!
     * \fn int imageHeight() const
     * \brief Returns the image height.
     */
    int imageHeight() const {return m_imageHeight;}

    /*!
     * \fn void setImageHeight(int height)
     * \brief Sets the image height.
     * \param height - image height.
     */
    void setImageHeight(int height);

    /*!
     * \fn int imageMargin() const
     * \brief Returns the image margin.
     */
    int imageMargin() const {return m_imageMargin;}

    /*!
     * \fn void setImageMargin(int margin)
     * \brief Sets the image margin.
     * \param margin - image margin.
     */
    void setImageMargin(int margin);

    /*!
     * \fn int eccLevel() const
     * \brief Returns the ecc level.
     */
    int eccLevel() const {return m_eccLevel;}

    /*!
     * \fn void setEccLevel(int eccLevel)
     * \brief Sets the ecc level.
     * \param eccLevel - ecc level.
     */
    void setEccLevel(int eccLevel);

    /*!
     * \fn QString filePath() const
     * \brief Returns the file path.
     */
    QString filePath() const {return m_filePath;}

    /*!
     * \fn void setFilePath(const QString &filePath)
     * \brief Sets the file path.
     * \param filePath - file path.
     */
    void setFilePath(const QString& filePath);

    /*!
     * \fn QString fileName() const
     * \brief Returns the file name.
     */
    QString fileName() const {return m_fileName;}

    /*!
     * \fn void setFileName(const QString &fileName)
     * \brief Sets the file name.
     * \param fileName - file name.
     */
    void setFileName(const QString& fileName);

    /*!
     * \fn QString fileExtension() const
     * \brief Returns the fileExtension.
     */
    QString fileExtension() const {return m_fileExtension;}

    /*!
     * \fn void setFileExtension(const QString &fileExtension)
     * \brief Sets the fileExtension.
     * \param fileExtension - fileExtension.
     */
    void setFileExtension(const QString& fileExtension);

    /*!
     * \fn QString outputFile() const
     * \brief Returns the file path.
     */
    QString outputFile() const {return m_outputFile;}

    /*!
     * \fn QString inputText() const
     * \brief Returns the input text.
     */
    QString inputText() const {return m_inputText;}

    /*!
     * \fn void setInputText(const QString &inputText)
     * \brief Sets the input text.
     * \param inputText - input text.
     */
    void setInputText(const QString& inputText);

public slots:

    /*!
     * \fn bool generate(const QString &inputString)
     * \brief Function for generating barcodes from given string
     * \param inputString - string of the barcode
     */
    bool generate(const QString& inputString);

    /*!
     * \fn void setFormat(const QString &formatName)
     * \brief Sets the barcode format.
     * \param formatName - barcode format string.
     */
    void setFormat(const QString& formatName);

    /*!
     * \fn bool saveImage()
     * \brief Saves the generated barcode image.
     */
    bool saveImage();

    /*!
     * \fn void setForegroundColor(const QColor &newForegroundColor)
     * \brief Sets the foreground.
     * \param foregroundColor - foreground color.
     */
    void setForegroundColor(const QColor& foregroundColor);

    /*!
     * \fn void setBackgroundColor(const QColor &backgroundColor)
     * \brief Sets the backgroundColor.
     * \param backgroundColor - background color.
     */
    void setBackgroundColor(const QColor& backgroundColor);

signals:

    /*!
     * \brief This signal is emitted when barcode generation is finished. If any error happens, sends the error string to QML.
     * \param error - error string.
     */
    void generationFinished(const QString& error = "");

    /*!
     * \brief This signal is emitted to send image width to QML.
     * \param width - image width.
     */
    void imageWidthChanged(int width);

    /*!
     * \brief This signal is emitted to send image height to QML.
     * \param height - image height.
     */
    void imageHeightChanged(int height);

    /*!
     * \brief This signal is emitted to send image margin to QML.
     * \param margin - image margin.
     */
    void imageMarginChanged(int margin);

    /*!
     * \brief This signal is emitted to send eccLevel to QML.
     * \param eccLevel - error correction code level.
     */
    void eccLevelChanged(int eccLevel);

    /*!
     * \brief This signal is emitted to send filePath to QML.
     * \param filePath - filePath.
     */
    void filePathChanged(const QString& filePath);

    /*!
     * \brief This signal is emitted to send fileName to QML.
     * \param fileName - fileName.
     */
    void fileNameChanged(const QString& fileName);

    /*!
     * \brief This signal is emitted to send fileExtension to QML.
     * \param fileExtension - fileExtension.
     */
    void fileExtensionChanged(const QString& fileExtension);

    /*!
     * \brief This signal is emitted to send inputText to QML.
     * \param inputText - inputText.
     */
    void inputTextChanged(const QString& inputText);

    /*!
     * \brief This signal is emitted to send barcode format to QML.
     * \param format - barcode format.
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
     * \param foregroundColor - foregroundColor.
     */
    void foregroundColorChanged(const QColor& foregroundColor);

    /*!
     * \brief This signal is emitted to send backgroundColor to QML.
     * \param backgroundColor - backgroundColor.
     */
    void backgroundColorChanged(const QColor& backgroundColor);

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
     * \param parentImage - Image parent. It is used for Painter constructor.
     * \param centerImage - Image path.
     * \param imageSize - Image size.
     * \param x - X coordinate where Image should be painted.
     * \param y - Y coordinate where Image should be painted.
     */
    void drawCenterImage(QImage* parentImage, const QString& centerImage, QSize imageSize, int x, int y);

    QColor m_foregroundColor = "black";
    QColor m_backgroundColor = "white";
};

#endif // SBARCODEGENERATOR_H
